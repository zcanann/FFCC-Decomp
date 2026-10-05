#!/usr/bin/env python3
"""Find regional function counterparts in compiled ARM ELF objects (dry run).

Unlike recover_splits, this audit never assumes that functions or pooled data
retain their order within a section. It verifies individual ELF function extents
and reports identity/ownership conflicts, not split edits or completion claims.
The source --object or --project may belong to a different region or program.
"""

import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import struct
import sys

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, CS_GRP_JUMP, CS_GRP_CALL, Cs
from capstone.arm import ARM_INS_SVC, ARM_OP_IMM, ARM_OP_MEM, ARM_OP_REG, ARM_REG_PC

sys.path.insert(0, str(Path(__file__).parent))
from recover_splits import (BASE, Section, candidate_addresses, fixed_ranges,
                            known_symbols, mapping_ranges, objects_from_project,
                            read_object, relocated_bytes, symbol_offset, symbol_value)
from split import parse_splits, parse_symbols


def slice_function(section, aliases, sections):
    """Rebase only this function; all other definitions need their own identity."""
    start = symbol_offset(aliases[0])
    end = start + aliases[0]['size']
    if not aliases[0]['size'] or start < 0 or end > section.size or section.nobits:
        raise ValueError('empty function or extent outside initialized section')
    other_functions = [s for s in section.symbols if s['kind'] == 'STT_FUNC'
                       and s not in aliases and symbol_offset(s) < end
                       and start < symbol_offset(s) + max(s['size'], 1)]
    if other_functions:
        raise ValueError('overlapping source function extents')
    data = bytearray(section.data[start:end])
    symbols = [dict(s, value=s['value'] - start) for s in aliases]
    mappings = [m for m in mapping_ranges(section, 0)
                if m['start'] < end and start < m['end']]
    if not mappings or mappings[0]['start'] > start:
        raise ValueError('missing ELF code/data mapping at function entry')
    if mappings[0]['kind'] != ('t' if aliases[0]['value'] & 1 else 'a'):
        raise ValueError('function entry disagrees with ELF code/data mapping')
    for m in mappings:
        symbols.append(dict(name='$' + m['kind'], value=max(start, m['start']) - start,
                            size=0, section=section.index, kind='STT_NOTYPE', binding='STB_LOCAL'))
    relocations = []
    for rel in section.relocations:
        if rel['offset'] >= end or rel['offset'] + 4 <= start:
            continue
        if rel['offset'] < start or rel['offset'] + 4 > end:
            raise ValueError('relocation crosses function boundary')
        offset = rel['offset'] - start
        target = dict(rel['symbol'])
        internal = False
        # Assemblers often reduce local references to section + addend. Recover
        # a named owning object, rather than assuming its old section placement.
        if rel['type'] == 2 and target['kind'] in ('STT_SECTION', 'STT_NOTYPE'):
            addend = struct.unpack_from('<I', data, offset)[0]
            effective = (target['value'] + addend) & 0xFFFFFFFF
            if target['section'] == section.index and start <= effective < end:
                target.update(value=effective - start, kind='STT_OBJECT')
                struct.pack_into('<I', data, offset, 0)
                internal = True
            elif target['section'] in sections:
                owners = [s for s in sections[target['section']].symbols
                          if s['kind'] in ('STT_OBJECT', 'STT_FUNC') and s['size']
                          and symbol_offset(s) <= effective < symbol_offset(s) + s['size']]
                if len(owners) == 1:
                    target = dict(owners[0], section='SHN_UNDEF')
                    struct.pack_into('<I', data, offset, effective - symbol_offset(owners[0]))
                else:
                    target.update(name=f"@section:{target['section']}+0x{effective:X}",
                                  section='SHN_UNDEF')
        elif target['section'] == section.index and start <= symbol_offset(target) < end:
            target['value'] -= start
            internal = True
        if isinstance(target['section'], int) and not internal:
            target['section'] = 'SHN_UNDEF'
        relocations.append(dict(offset=offset, type=rel['type'], symbol=target))
    return Section(section.index, section.name, end - start, 2 if aliases[0]['value'] & 1 else 4,
                   False, bytes(data), symbols, relocations)


def implicit_references(section, fragment, start):
    """Find PC-relative dependencies the assembler resolved without relocations."""
    references = []
    for mapping in mapping_ranges(fragment, 0):
        if mapping['kind'] == 'd':
            continue
        thumb = mapping['kind'] == 't'
        decoder = Cs(CS_ARCH_ARM, CS_MODE_THUMB if thumb else CS_MODE_ARM)
        decoder.detail = True
        lo, hi = mapping['start'], mapping['end']
        decoded = 0
        for ins in decoder.disasm(fragment.data[lo:hi], start + lo):
            decoded += ins.size
            offset = ins.address - start
            if any(r['offset'] < offset + ins.size and offset < r['offset'] + 4
                   and r['type'] != 40 for r in fragment.relocations):
                continue
            target = None
            size = 1
            if ins.group(CS_GRP_JUMP) or ins.group(CS_GRP_CALL):
                immediate = [o.imm for o in ins.operands if o.type == ARM_OP_IMM]
                if immediate:
                    target = immediate[0]
            for op in ins.operands:
                if op.type == ARM_OP_MEM and op.mem.base == ARM_REG_PC:
                    if op.mem.index:
                        raise ValueError('indexed PC-relative access requires manual verification')
                    target = ((ins.address + 4) & ~3 if thumb else ins.address + 8) + op.mem.disp
                    size = 4
            if ins.mnemonic == 'adr' and ins.operands[-1].type == ARM_OP_IMM:
                target = ins.operands[-1].imm
            elif ins.mnemonic in ('add', 'sub') and len(ins.operands) >= 3:
                if ins.operands[1].type == ARM_OP_REG and ins.operands[1].reg == ARM_REG_PC:
                    if ins.operands[2].type != ARM_OP_IMM:
                        raise ValueError('computed PC-relative access requires manual verification')
                    delta = ins.operands[2].imm * (-1 if ins.mnemonic == 'sub' else 1)
                    target = ((ins.address + 4) & ~3 if thumb else ins.address + 8) + delta
            elif ins.mnemonic == 'mov' and len(ins.operands) == 2:
                if ins.operands[1].type == ARM_OP_REG and ins.operands[1].reg == ARM_REG_PC:
                    target = ins.address + (4 if thumb else 8)
            # SVC's implicit PC read supplies the BIOS return address; its
            # encoded service number is fixed, not a regional symbol reference.
            if target is None and ins.id != ARM_INS_SVC and ARM_REG_PC in ins.regs_access()[0]:
                raise ValueError('unclassified PC-relative access requires manual verification')
            if target is not None and not start <= target < target + size <= start + fragment.size:
                owners = [s for s in section.symbols if s['kind'] in ('STT_FUNC', 'STT_OBJECT')
                          and symbol_offset(s) <= target < symbol_offset(s) + s['size']]
                references.append(dict(offset=offset, target=target,
                                       symbol=owners[0]['name'] if len(owners) == 1 else None,
                                       addend=target - symbol_offset(owners[0]) if len(owners) == 1 else 0))
        if decoded != hi - lo:
            raise ValueError('incomplete disassembly of ELF code mapping')
    return references


def evaluate(fragment, address, known, implicit, start, image, base):
    """A masked match alone is never enough to verify a function."""
    unresolved = [dict(offset=r['offset'], type=r['type'], symbol=r['symbol']['name'])
                  for r in fragment.relocations if r['type'] != 40 and
                  symbol_value(r['symbol'], {fragment.index: address}, known) is None]
    unresolved += [dict(ref, type='implicit_pc_relative') for ref in implicit
                   if ref['symbol'] not in known]
    if unresolved:
        return dict(address=address, status='unresolved', reason='unresolved references',
                    unresolved_references=unresolved)
    try:
        expected, evidence = relocated_bytes(fragment, address, {fragment.index: address}, known)
        for ref in implicit:
            resolved = known.get(ref['symbol'])
            if resolved is None:
                raise ValueError('unresolved unrelocated PC-relative reference at '
                                 f"0x{ref['offset']:X} to {ref['symbol'] or hex(ref['target'])}")
            target = (resolved[0] & ~1 if resolved[1] else resolved[0]) + ref['addend']
            if address + ref['target'] - start != target:
                return dict(address=address, status='rejected', reason='unrelocated PC-relative target differs')
            evidence.append(dict(ref, type='implicit_pc_relative', target=target))
    except ValueError as error:
        return dict(address=address, status='unresolved', reason=str(error))
    if expected != image[address - base:address - base + fragment.size]:
        return dict(address=address, status='rejected', reason='relocation replay differs from retail')
    return dict(address=address, status='verified', verified_bytes=fragment.size, relocations=evidence)


def audit(objects, image, symbols, splits, base=BASE, limit=128):
    if limit < 1 or len({u for u, _ in objects}) != len(objects):
        raise ValueError('units must be unique and candidate limit positive')
    rows, pending = [], []
    for unit, path in objects:
        raw, sections, common = read_object(path)
        row = dict(unit=unit, object=str(path), sha256=hashlib.sha256(raw).hexdigest(), functions=[],
                   unverified_storage=[dict(section=s.name, size=s.size) for s in sections.values() if s.nobits],
                   common=[dict(s, status='unverified_storage_extent') for s in common])
        rows.append(row)
        known = known_symbols(symbols, splits, unit)
        # A source-local name must not bind to another unit's regional global.
        local_names = {s['name'] for section in sections.values() for s in section.symbols
                       if s['binding'] == 'STB_LOCAL' and s['kind'] in ('STT_FUNC', 'STT_OBJECT')}
        for name in local_names:
            owned = [s for s in symbols if s.name == name and
                     {p.unit for p in splits if p.start <= s.address < p.end} == {unit}]
            if len({(s.address, s.thumb) for s in owned}) != 1:
                known.pop(name, None)
        identity_values = defaultdict(set)
        for symbol in symbols:
            if not symbol.local or {p.unit for p in splits if p.start <= symbol.address < p.end} == {unit}:
                identity_values[symbol.name].add((symbol.address, symbol.thumb, symbol.kind))
        ambiguous_names = {name for name, values in identity_values.items() if len(values) > 1}
        row['ambiguous_regional_identities'] = sorted(ambiguous_names)
        for section in sections.values():
            groups = defaultdict(list)
            for symbol in section.symbols:
                if symbol['kind'] == 'STT_FUNC':
                    groups[(symbol_offset(symbol), symbol['size'], bool(symbol['value'] & 1))].append(symbol)
            for (start, size, thumb), aliases in sorted(groups.items()):
                entry = dict(names=sorted(s['name'] for s in aliases), section=section.name,
                             source_offset=start, size=size, thumb=thumb, candidates=[])
                row['functions'].append(entry)
                try:
                    fragment = slice_function(section, aliases, sections)
                    implicit = implicit_references(section, fragment, start)
                    # Search widely enough to expose stale identities. Tiny
                    # functions still need an existing regional identity anchor.
                    fixed = sum(hi - lo for lo, hi in fixed_ranges(fragment))
                    addresses, _, reason = candidate_addresses(fragment, image, base,
                                                               known if fixed < 12 else {}, set(), limit)
                    addresses = [a for a in addresses if (a - start) % 4 == 0]
                    entry.update(fixed_bytes=fixed, search_reason=reason,
                                 placement_basis='configured_identity' if fixed < 12 else 'fixed_bytes')
                    pending.append((unit, entry, fragment, known, implicit, addresses, ambiguous_names, local_names))
                except ValueError as error:
                    entry.update(status='unsupported', reason=str(error))
    # Only independently verified identities seed a later round. This is
    # intentionally conservative about cycles and unresolved pooled literals.
    discovered = defaultdict(set)
    global_names = Counter(s['name'] for _, _, fragment, _, _, _, _, _ in pending
                           for s in fragment.symbols
                           if s['kind'] == 'STT_FUNC' and s['binding'] != 'STB_LOCAL')
    # Do not let an identity with competing batch ownership resolve another
    # function's relocations, even if the competing candidate is unresolved.
    overlaps = set()
    for i, (_, entry, _, _, _, addresses, _, _) in enumerate(pending):
        for _, other, _, _, _, alternatives, _, _ in pending[i + 1:]:
            if any(a < b + other['size'] and b < a + entry['size']
                   for a in addresses for b in alternatives):
                overlaps.update((id(entry), id(other)))
    while True:
        previous = {name: set(values) for name, values in discovered.items()}
        for unit, entry, fragment, known, implicit, addresses, ambiguous_names, local_names in pending:
            for field in ('reason', 'address', 'verified_bytes', 'mapping_ranges', 'conflicts'):
                entry.pop(field, None)
            resolved = dict(known)
            for (owner, name), values in previous.items():
                if (owner == (unit if name in local_names else '*') and len(values) == 1
                        and name not in resolved and name not in ambiguous_names):
                    resolved[name] = next(iter(values))
            entry['candidates'] = [evaluate(fragment, a, resolved, implicit, entry['source_offset'], image, base)
                                   for a in addresses]
            possible = [c for c in entry['candidates'] if c['status'] != 'rejected']
            verified = [c for c in possible if c['status'] == 'verified']
            if entry['search_reason']:
                entry.update(status='ambiguous' if addresses else 'unresolved', reason=entry['search_reason'])
            elif len(possible) > 1:
                entry.update(status='ambiguous', reason='multiple surviving placements')
            elif len(verified) == 1:
                address = verified[0]['address']
                entry.update(status='verified', address=address, verified_bytes=fragment.size)
                entry['mapping_ranges'] = mapping_ranges(fragment, address)
                conflicts = []
                for s in splits:
                    if s.start < address + fragment.size and address < s.end and s.unit != unit and not s.unit.startswith('regional_'):
                        conflicts.append(dict(kind='ownership', unit=s.unit, start=s.start, end=s.end))
                for s in symbols:
                    if s.name in entry['names'] and (not s.local or any(
                            p.unit == unit and p.start <= s.address < p.end for p in splits)):
                        if s.address != address or s.kind != 'function' or s.thumb != entry['thumb']:
                            conflicts.append(dict(kind='identity', name=s.name, address=s.address, thumb=s.thumb))
                    elif s.kind == 'function' and s.address == address:
                        conflicts.append(dict(kind='different_name_at_entry', name=s.name, address=s.address))
                    elif s.kind == 'function' and address < s.address < address + fragment.size:
                        conflicts.append(dict(kind='interior_function_boundary', name=s.name, address=s.address))
                    elif s.kind == 'object' and any(m['kind'] != 'd' and
                            s.address < m['end'] and m['start'] < s.address + s.size
                            for m in entry['mapping_ranges']):
                        conflicts.append(dict(kind='code_overlaps_configured_object', name=s.name, address=s.address))
                entry['conflicts'] = conflicts
                if not conflicts and id(entry) not in overlaps:
                    for s in fragment.symbols:
                        if s['kind'] == 'STT_FUNC':
                            owner = unit if s['binding'] == 'STB_LOCAL' else '*'
                            if owner != '*' or global_names[s['name']] == 1:
                                discovered[(owner, s['name'])].add((address | int(entry['thumb']), entry['thumb']))
            else:
                entry.update(status='unresolved' if possible else 'unmatched',
                             reason=possible[0]['reason'] if possible else 'no relocation-verified placement')
        if dict(discovered) == previous:
            break
    verified = [(r['unit'], f) for r in rows for f in r['functions'] if f['status'] == 'verified']
    for i, (unit, entry) in enumerate(verified):
        for other_unit, other in verified[i + 1:]:
            if entry['address'] < other['address'] + other['size'] and other['address'] < entry['address'] + entry['size']:
                entry['conflicts'].append(dict(kind='candidate_overlap', unit=other_unit, names=other['names'], address=other['address']))
                other['conflicts'].append(dict(kind='candidate_overlap', unit=unit, names=entry['names'], address=entry['address']))
    for _, entry in verified:
        entry['identity_status'] = 'conflicting' if entry['conflicts'] else 'candidate'
    return dict(schema_version=1, image_sha256=hashlib.sha256(image).hexdigest(), image_base=base,
                source_linkage_claims=False, storage_extent_claims=False, configuration_edits=False,
                identity_basis='regional configuration plus independently verified function candidates',
                duplicate_source_identities=sorted(n for n, count in global_names.items() if count > 1),
                summary=dict(Counter(f['status'] for r in rows for f in r['functions'])), objects=rows)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--image', required=True, type=Path)
    parser.add_argument('--config', required=True, type=Path)
    parser.add_argument('--object', action='append', default=[], metavar='UNIT=PATH')
    parser.add_argument('--project', type=Path, help='source objdiff.json; may select another region')
    parser.add_argument('--program', choices=('cli', 'mgr'))
    parser.add_argument('--base', type=lambda v: int(v, 0), default=BASE)
    parser.add_argument('--max-candidates', type=int, default=128)
    parser.add_argument('--output', type=Path)
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
    if not objects or len({u for u, _ in objects}) != len(objects) or args.max_candidates < 1:
        parser.error('supply unique source units and a positive candidate limit')
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
