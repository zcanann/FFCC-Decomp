#!/usr/bin/env python3
"""Propose GBA ownership from compiled ARM ELF objects and a regional retail image.

Example (JSON only; neither configuration nor linkage claims are changed):
  python gba/tools/recover_splits.py --image orig/GCCE01/gba/ffcc_cli.bin \
    --config gba/config/GCCE01/cli --object crt0=build/GCCE01/gba/cli/src/crt0.o

Repeat --object UNIT=PATH to audit a batch. Whole initialized sections must have
one placement and reproduce every byte, including supported relocations. ELF
mapping symbols distinguish literal data from function entries. NOBITS/COMMON
sizes describe this source object, not independently verified retail extents.
Requires pyelftools and capstone (pip install pyelftools capstone). Unknown
relocations and unknown external targets are reported, never masked and accepted.
Alternatively, --project objdiff.json --program cli selects configured whole
source objects, replacing synthetic COMMON comparison views with their originals.
"""

import argparse
from collections import defaultdict
from dataclasses import dataclass
import hashlib
import io
import json
from pathlib import Path
import struct
import sys

from elftools.elf.elffile import ELFFile

sys.path.insert(0, str(Path(__file__).parent))
from split import parse_splits, parse_symbols  # noqa: E402

BASE = 0x02000000
SUPPORTED = {1, 2, 10, 28, 29, 40}


@dataclass
class Section:
    index: int
    name: str
    size: int
    alignment: int
    nobits: bool
    data: bytes
    symbols: list
    relocations: list


def read_object(path):
    raw = path.read_bytes()
    elf = ELFFile(io.BytesIO(raw))
    if (elf.elfclass != 32 or not elf.little_endian
            or elf['e_machine'] != 'EM_ARM' or elf['e_type'] != 'ET_REL'):
        raise ValueError(f'{path}: expected little-endian ARM ELF32 relocatable object')
    symtab = elf.get_section_by_name('.symtab')
    if symtab is None:
        raise ValueError(f'{path}: missing symbol table')
    symbols = [dict(name=s.name, value=s['st_value'], size=s['st_size'],
                    section=s['st_shndx'], kind=s['st_info']['type'],
                    binding=s['st_info']['bind']) for s in symtab.iter_symbols()]
    sections = {}
    for index, section in enumerate(elf.iter_sections()):
        if section['sh_flags'] & 2 and section['sh_size']:
            nobits = section['sh_type'] == 'SHT_NOBITS'
            sections[index] = Section(index, section.name, section['sh_size'],
                                      max(1, section['sh_addralign']), nobits,
                                      b'' if nobits else section.data(),
                                      [s for s in symbols if s['section'] == index], [])
    for section in elf.iter_sections():
        if section['sh_type'] in ('SHT_REL', 'SHT_RELA') and section['sh_info'] in sections:
            if (section['sh_type'] != 'SHT_REL'
                    or section['sh_link'] != elf.get_section_index('.symtab')):
                raise ValueError(f'{path}: unsupported relocation table {section.name}')
            for rel in section.iter_relocations():
                sections[section['sh_info']].relocations.append(
                    dict(offset=rel['r_offset'], type=rel['r_info_type'],
                         symbol=symbols[rel['r_info_sym']]))
    return raw, sections, [s for s in symbols if s['section'] == 'SHN_COMMON']


def symbol_offset(symbol):
    return symbol['value'] & ~1 if symbol['kind'] == 'STT_FUNC' else symbol['value']


def known_symbols(symbols, splits, unit):
    values = defaultdict(set)
    for symbol in symbols:
        owners = {s.unit for s in splits if s.start <= symbol.address < s.end}
        if not symbol.local or owners == {unit}:
            values[symbol.name].add((symbol.address | int(symbol.thumb),
                                     symbol.kind == 'function' and symbol.thumb))
    return {name: next(iter(addresses)) for name, addresses in values.items()
            if len(addresses) == 1}


def fixed_ranges(section):
    masked = set()
    for rel in section.relocations:
        if rel['type'] not in SUPPORTED:
            raise ValueError(f"unsupported relocation {rel['type']} at 0x{rel['offset']:X}")
        offset = rel['offset']
        if offset < 0 or offset + 4 > section.size:
            raise ValueError('relocation extends outside its section')
        if rel['type'] != 40:
            if masked.intersection(range(offset, offset + 4)):
                raise ValueError('overlapping relocation sites')
            masked.update(range(offset, offset + 4))
    ranges = []
    start = None
    for i in range(section.size + 1):
        if i < section.size and i not in masked:
            if start is None:
                start = i
        elif start is not None:
            ranges.append((start, i))
            start = None
    return ranges


def candidate_addresses(section, image, base, known, hints, limit):
    ranges = fixed_ranges(section)
    anchors = {((known[s['name']][0] & ~1 if s['kind'] == 'STT_FUNC'
                 else known[s['name']][0]) - symbol_offset(s))
               for s in section.symbols if s['name'] in known
               and s['kind'] in ('STT_FUNC', 'STT_OBJECT')}
    if len(anchors) > 1:
        raise ValueError('known symbol placements disagree on section base')
    if hints and anchors and set(hints) != anchors:
        raise ValueError('pointer references disagree with known section placement')
    candidates = set(hints) or anchors
    fixed_bytes = sum(end - start for start, end in ranges)
    if not candidates:
        if fixed_bytes < 12 or not ranges:
            return [], fixed_bytes, 'insufficient fixed bytes without an identity/reference anchor'
        start, end = max(ranges, key=lambda r: r[1] - r[0])
        needle = section.data[start:end]
        position = 0
        while True:
            position = image.find(needle, position)
            if position < 0:
                break
            address = base + position - start
            position += 1
            if address % section.alignment == 0:
                candidates.add(address)
    matches = []
    for address in sorted(candidates):
        offset = address - base
        if (address % section.alignment or offset < 0
                or offset + section.size > len(image)):
            continue
        if all(image[offset + lo:offset + hi] == section.data[lo:hi] for lo, hi in ranges):
            matches.append(address)
            if len(matches) > limit:
                return matches, fixed_bytes, 'candidate limit exceeded; ambiguity retained'
    return matches, fixed_bytes, None


def signed(value, bits):
    return value - (1 << bits) if value & (1 << (bits - 1)) else value


def symbol_value(symbol, placements, known):
    section = symbol['section']
    if section == 'SHN_ABS':
        return symbol['value'], False
    if isinstance(section, int) and section in placements:
        return (placements[section] + symbol['value'],
                symbol['kind'] == 'STT_FUNC' and bool(symbol['value'] & 1))
    return known.get(symbol['name'])


def relocated_bytes(section, address, placements, known):
    result = bytearray(section.data)
    evidence = []
    for rel in section.relocations:
        offset, kind, symbol = rel['offset'], rel['type'], rel['symbol']
        if kind == 40:  # R_ARM_V4BX does not change ARMv4T BX instructions.
            continue
        resolved = symbol_value(symbol, placements, known)
        if resolved is None:
            raise ValueError(f"unresolved relocation {kind} to {symbol['name'] or symbol['section']}")
        target, thumb = resolved
        word = struct.unpack_from('<I', result, offset)[0]
        place = address + offset
        if kind == 2:  # R_ARM_ABS32
            value = (((target & ~1 if thumb else target) + word) | int(thumb)) & 0xFFFFFFFF
        elif kind in (1, 28, 29):  # ARM PC24/CALL/JUMP24, no interworking veneers.
            if word & 0x0E000000 != 0x0A000000 or thumb or target & 3:
                raise ValueError('unsupported ARM branch/interworking relocation')
            displacement = target + signed(word & 0xFFFFFF, 24) * 4 - place
            if displacement % 4 or not -(1 << 25) <= displacement < (1 << 25):
                raise ValueError('ARM branch requires a veneer')
            value = (word & 0xFF000000) | ((displacement >> 2) & 0xFFFFFF)
        elif kind == 10:  # Thumb-1 BL; Thumb-2/BLX encodings are not accepted.
            lo, hi = word & 0xFFFF, word >> 16
            if lo & 0xF800 != 0xF000 or hi & 0xF800 != 0xF800 or not thumb:
                raise ValueError('unsupported Thumb branch/interworking relocation')
            addend = signed(((lo & 0x7FF) << 12) | ((hi & 0x7FF) << 1), 23)
            displacement = (target & ~1) + addend - place
            if displacement % 2 or not -(1 << 22) <= displacement < (1 << 22):
                raise ValueError('Thumb branch requires a veneer')
            value = (0xF000 | ((displacement >> 12) & 0x7FF)
                     | ((0xF800 | ((displacement >> 1) & 0x7FF)) << 16))
        else:
            raise ValueError(f'unsupported relocation {kind}')
        struct.pack_into('<I', result, offset, value)
        evidence.append(dict(offset=offset, type=kind, symbol=symbol['name'], target=target))
    return bytes(result), evidence


def mapping_ranges(section, address):
    mappings = sorted((s['value'], s['name'][1]) for s in section.symbols
                      if s['name'].split('.')[0] in ('$a', '$t', '$d'))
    return [dict(start=address + start,
                 end=address + (mappings[i + 1][0] if i + 1 < len(mappings) else section.size),
                 kind=kind) for i, (start, kind) in enumerate(mappings)]


def symbol_line(symbol, section, address):
    kind = 'function' if symbol['kind'] == 'STT_FUNC' else 'object'
    flags = ' thumb' if kind == 'function' and symbol['value'] & 1 else ''
    if symbol['binding'] == 'STB_LOCAL':
        flags += ' scope:local'
    return (f"{symbol['name']} = {section}:0x{address:08X}; // type:{kind} "
            f"size:0x{symbol['size']:X}{flags}")


def proposals(unit, section, address, symbols, splits):
    end = address + section.size
    overlaps = [s for s in splits if s.start < end and address < s.end]
    blockers = [s for s in overlaps if s.unit != unit and not s.unit.startswith('regional_')]
    if blockers:
        return dict(blocked='range overlaps another named unit',
                    conflicts=[dict(unit=s.unit, section=s.section, start=s.start, end=s.end)
                               for s in blockers])
    edits = []
    for s in overlaps:
        edits.append(dict(action='remove_range', unit=s.unit, section=s.section,
                          start=s.start, end=s.end))
        for lo, hi in ((s.start, address), (end, s.end)):
            if lo < hi:
                edits.append(dict(action='add_range', unit=s.unit, section=s.section,
                                  start=lo, end=hi, alignment=s.alignment))
    edits.append(dict(action='add_range', unit=unit, section=section.name,
                      start=address, end=end, alignment=section.alignment))
    mappings = mapping_ranges(section, address)
    definitions = []
    for symbol in section.symbols:
        if symbol['kind'] not in ('STT_FUNC', 'STT_OBJECT') or not symbol['size']:
            continue
        at = address + symbol_offset(symbol)
        if at < address or at + symbol['size'] > end:
            continue
        old = [s for s in symbols if s.address == at and s.kind ==
               ('function' if symbol['kind'] == 'STT_FUNC' else 'object')]
        definitions.append(dict(action='replace_symbol' if old else 'define_symbol',
                                name=symbol['name'], address=at,
                                existing_names=[s.name for s in old],
                                line=symbol_line(symbol, section.name, at)))
    false_entries = []
    for symbol in symbols:
        if symbol.kind != 'function':
            continue
        if any(m['kind'] == 'd' and m['start'] <= symbol.address < m['end'] for m in mappings):
            false_entries.append(dict(action='remove_function_boundary', name=symbol.name,
                                      address=symbol.address, reason='verified ELF $d mapping'))
    return dict(application_scope='independent; use top-level batch_split_edits for a batch',
                split_edits=edits, symbol_edits=definitions + false_entries,
                mapping_ranges=mappings)


def audit_object(unit, path, image, base, symbols, splits, limit=128):
    raw, sections, common = read_object(path)
    known = known_symbols(symbols, splits, unit)
    candidates, reasons, fixed = {}, {}, {}
    hints = defaultdict(set)
    hint_sources = defaultdict(set)
    # Repeated rounds allow an ABS32 reference in a uniquely placed section to
    # locate this object's initialized data. Such hints remain conditional until
    # both sections pass complete relocation/byte validation below.
    for _ in range(len(sections) + 1):
        old_hints = {k: set(v) for k, v in hints.items()}
        for index, section in sections.items():
            if section.nobits:
                continue
            try:
                candidates[index], fixed[index], reason = candidate_addresses(
                    section, image, base, known, hints[index], limit)
                reasons[index] = reason
            except ValueError as error:
                candidates[index], reasons[index] = [], str(error)
            if len(candidates[index]) != 1:
                continue
            at = candidates[index][0]
            for rel in section.relocations:
                symbol = rel['symbol']
                if rel['type'] == 2 and isinstance(symbol['section'], int) and symbol['section'] in sections:
                    value = struct.unpack_from('<I', image, at - base + rel['offset'])[0]
                    addend = struct.unpack_from('<I', section.data, rel['offset'])[0]
                    if symbol['kind'] == 'STT_FUNC' and symbol['value'] & 1:
                        inferred = (value & ~1) - (addend & ~1) - (symbol['value'] & ~1)
                    else:
                        inferred = value - addend - symbol['value']
                    hints[symbol['section']].add(inferred & 0xFFFFFFFF)
                    hint_sources[symbol['section']].add(index)
        if dict(hints) == old_hints:
            break
    placements = {i: addresses[0] for i, addresses in candidates.items() if len(addresses) == 1}
    for index, section in sections.items():
        if section.nobits and len(hints[index]) == 1:
            placements[index] = next(iter(hints[index]))
    records = []
    verified = set()
    for index, section in sections.items():
        row = dict(section=section.name, size=section.size, alignment=section.alignment,
                   fixed_bytes=fixed.get(index, 0), candidates=candidates.get(index, []))
        if section.nobits:
            row.update(status='unverified_storage_extent', references=sorted(hints[index]),
                       reason='source NOBITS size does not prove retail allocation extent')
        elif len(candidates.get(index, [])) != 1:
            row.update(status='ambiguous' if candidates.get(index) else 'unresolved',
                       reason=reasons.get(index) or 'no unique placement')
        else:
            address = placements[index]
            try:
                expected, relocations = relocated_bytes(section, address, placements, known)
                actual = image[address - base:address - base + section.size]
                if expected != actual:
                    raise ValueError('relocated bytes differ from retail')
                row.update(status='verified', address=address, relocations=relocations,
                           verified_bytes=section.size)
                verified.add(index)
            except ValueError as error:
                row.update(status='unresolved', reason=str(error))
        records.append(row)
    # Reference-derived placements are conditional on their referring section.
    # Close dependencies transitively so a rejected caller cannot lend apparent
    # ownership to data merely because the bytes at its pointer happen to match.
    dependencies = {}
    for index, section in sections.items():
        dependencies[index] = ({r['symbol']['section'] for r in section.relocations
                               if isinstance(r['symbol']['section'], int)
                               and r['symbol']['section'] in sections}
                              | hint_sources[index]) - {index}
    accepted = set(verified)
    while True:
        rejected = {i for i in accepted if dependencies[i] - accepted}
        if not rejected:
            break
        accepted -= rejected
    for index, row in zip(sections, records):
        if row['status'] != 'verified':
            continue
        section = sections[index]
        row['unverified_dependencies'] = [sections[i].name for i in sorted(dependencies[index] - accepted)]
        if row['unverified_dependencies']:
            row['status'] = 'conditional'
            row['reason'] = 'referenced source sections lack verified regional extents'
        else:
            row['proposal'] = proposals(unit, section, row['address'], symbols, splits)
        row['dependencies'] = [sections[i].name for i in sorted(dependencies[index])]
    return dict(unit=unit, object=str(path), sha256=hashlib.sha256(raw).hexdigest(),
                sections=records, common=[dict(name=s['name'], source_size=s['size'],
                    alignment=s['value'], known_start=known.get(s['name'], (None, False))[0],
                    status='unverified_storage_extent') for s in common])


def batch_split_edits(rows, splits):
    ranges = []
    for unit in rows:
        for section in unit['sections']:
            proposal = section.get('proposal', {})
            if section['status'] == 'verified' and proposal and 'blocked' not in proposal:
                ranges.append((section['address'], section['address'] + section['size'],
                               unit['unit'], section['section'], section['alignment']))
    edits = []
    for split in splits:
        residuals = [(split.start, split.end)]
        for lo, hi, _, _, _ in sorted(ranges):
            remaining = []
            for start, end in residuals:
                if lo < end and start < hi:
                    if start < lo:
                        remaining.append((start, lo))
                    if hi < end:
                        remaining.append((hi, end))
                else:
                    remaining.append((start, end))
            residuals = remaining
        if residuals != [(split.start, split.end)]:
            edits.append(dict(action='remove_range', unit=split.unit, section=split.section,
                              start=split.start, end=split.end))
            for start, end in residuals:
                edits.append(dict(action='add_range', unit=split.unit, section=split.section,
                                  start=start, end=end,
                                  alignment=split.alignment if start == split.start else None))
    edits.extend(dict(action='add_range', unit=unit, section=section, start=lo, end=hi,
                      alignment=alignment) for lo, hi, unit, section, alignment in sorted(ranges))
    return edits


def audit(objects, image, symbols, splits, base=BASE, limit=128):
    rows = [audit_object(unit, path, image, base, symbols, splits, limit)
            for unit, path in sorted(objects)]
    ranges = [(unit, section) for unit in rows for section in unit['sections']
              if section['status'] == 'verified']
    for i, (unit, section) in enumerate(ranges):
        conflicts = []
        for other, candidate in ranges[:i] + ranges[i + 1:]:
            if max(section['address'], candidate['address']) < min(
                    section['address'] + section['size'], candidate['address'] + candidate['size']):
                conflicts.append(dict(unit=other['unit'], section=candidate['section']))
        if conflicts:
            section['proposal'] = dict(blocked='overlapping object proposals', conflicts=conflicts)
    # A reference from a section whose ownership is blocked cannot authorize a
    # dependent data carve, even when both sections happen to reproduce bytes.
    for unit in rows:
        by_name = {s['section']: s for s in unit['sections']}
        while True:
            changed = False
            for section in unit['sections']:
                proposal = section.get('proposal', {})
                if section['status'] != 'verified' or not proposal or 'blocked' in proposal:
                    continue
                rejected = [name for name in section.get('dependencies', [])
                            if by_name[name]['status'] != 'verified'
                            or 'blocked' in by_name[name].get('proposal', {})]
                if rejected:
                    section['proposal'] = dict(blocked='referenced ownership is unverified',
                                               dependencies=rejected)
                    changed = True
            if not changed:
                break
    return dict(schema_version=1, image_sha256=hashlib.sha256(image).hexdigest(),
                image_base=base, source_linkage_claims=False, objects=rows,
                batch_split_edits=batch_split_edits(rows, splits))


def objects_from_project(path, program):
    prefix = f'gba/{program}/'
    objects = []
    for row in json.loads(path.read_text(encoding='utf-8')).get('units', []):
        if not row['name'].startswith(prefix) or not row.get('base_path'):
            continue
        unit = row['name'][len(prefix):]
        obj = Path(row['base_path'])
        if not obj.is_absolute():
            obj = path.parent / obj
        if obj.name.endswith('.common.o'):
            obj = obj.with_name(obj.name[:-len('.common.o')] + '.o')
        if obj.name != Path(unit).name + '.o':
            raise ValueError(f'{unit}: unsupported comparison view {obj}; specify original --object')
        if not obj.is_file():
            raise ValueError(f'{obj}: configured source object missing; build this region first')
        objects.append((unit, obj))
    return objects


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--image', required=True, type=Path)
    parser.add_argument('--config', required=True, type=Path)
    parser.add_argument('--object', action='append', default=[], metavar='UNIT=PATH')
    parser.add_argument('--project', type=Path, help='objdiff.json for automatic whole-unit discovery')
    parser.add_argument('--program', choices=('cli', 'mgr'), help='GBA program selected from --project')
    parser.add_argument('--base', type=lambda v: int(v, 0), default=BASE)
    parser.add_argument('--max-candidates', type=int, default=128)
    parser.add_argument('--output', type=Path, help='JSON output (default: stdout)')
    args = parser.parse_args()
    objects = []
    if args.project:
        if not args.program:
            parser.error('--project requires --program')
        objects += objects_from_project(args.project, args.program)
    for item in args.object:
        unit, separator, path = item.partition('=')
        if not separator or not unit or not path:
            parser.error('--object requires UNIT=PATH')
        objects.append((unit, Path(path)))
    if not objects:
        parser.error('supply --object or a --project with configured GBA source objects')
    if len({u for u, _ in objects}) != len(objects) or args.max_candidates < 1:
        parser.error('units must be unique and --max-candidates must be positive')
    result = audit(objects, args.image.read_bytes(), parse_symbols(args.config / 'symbols.txt'),
                   parse_splits(args.config / 'splits.txt'), args.base, args.max_candidates)
    result['configuration'] = {name: dict(path=str(args.config / name),
        sha256=hashlib.sha256((args.config / name).read_bytes()).hexdigest())
        for name in ('symbols.txt', 'splits.txt')}
    output = json.dumps(result, indent=2, sort_keys=True) + '\n'
    if args.output:
        args.output.write_text(output, encoding='utf-8')
    else:
        sys.stdout.write(output)


if __name__ == '__main__':
    main()
