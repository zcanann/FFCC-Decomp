#!/usr/bin/env python3
"""Read-only regional placement solver for compiled PowerPC objects.

PAL target objects supply optional retained-function hypotheses, never regional
completion claims. Every reported initialized section is replayed against the
selected retail DOL. Unresolved ownership and BSS remain explicit review items.
"""

import argparse
from collections import defaultdict
from dataclasses import dataclass, field
import fnmatch
import hashlib
import io
import json
from pathlib import Path
import re
import struct

from elftools.elf.elffile import ELFFile

try:
    from .recover_code_splits import dol_sections, is_placeholder
except ImportError:
    from recover_code_splits import dol_sections, is_placeholder


def symbol_records(text):
    """Preserve local duplicates; they cannot anchor another object's externs."""
    result = []
    for line in text.splitlines():
        match = re.match(r'(\S+)\s*=\s*(\S+):0x([\dA-Fa-f]+);\s*//\s*(.*)', line)
        if match:
            attrs = dict(p.split(':', 1) for p in match[4].split() if ':' in p)
            result.append(dict(name=match[1], section=match[2], address=int(match[3], 16),
                               size=int(attrs.get('size', '0'), 0), kind=attrs.get('type'),
                               local=attrs.get('scope') == 'local'))
    return result


def map_objects(text):
    """Read names, sizes, alignment and ownership, deliberately ignoring addresses."""
    result, section = [], None
    scopes = {}
    for line in text.splitlines():
        m = re.search(r'] (\S+) \(object,(local|global)\) found in \S+ (\S+)', line)
        if m:
            scopes[(m[3], m[1])] = m[2] == 'local'
    for line in text.splitlines():
        m = re.match(r'(\.\S+) section layout', line)
        if m:
            section = m[1]
        m = re.match(r'\s+[\dA-Fa-f]{8}\s+([\dA-Fa-f]{6,8})\s+[\dA-Fa-f]{8}\s+(\d+)\s+(\S+)\s+\S+\s+(\S+)\s*$', line)
        if m and section and not m[3].startswith('.'):
            result.append(dict(section=section, size=int(m[1], 16), align=int(m[2]),
                               name=m[3], owner=m[4], local=scopes.get((m[4], m[3]))))
    return result


def retail_bytes(dol, address, size, executable=None):
    for sec in dol_sections(dol):
        if executable is not None and (sec['index'] < 7) != executable:
            continue
        if sec['address'] <= address and address + size <= sec['address'] + sec['size']:
            offset = sec['offset'] + address - sec['address']
            return dol[offset:offset + size]
    raise ValueError('placement is outside the appropriate initialized DOL section')


def sda_bases(elf_bytes, dol):
    """Trust linker SDA symbols only after checking all retail initialized bytes."""
    elf = ELFFile(io.BytesIO(elf_bytes))
    if elf.elfclass != 32 or elf.little_endian or elf['e_machine'] != 'EM_PPC' or elf['e_type'] != 'ET_EXEC':
        raise ValueError('SDA bases require a big-endian PowerPC ELF32 executable')
    sections = [s for s in elf.iter_sections() if s['sh_flags'] & 2
                and s['sh_type'] != 'SHT_NOBITS' and s['sh_size']]
    for ds in dol_sections(dol):
        cursor, end = ds['address'], ds['address'] + ds['size']
        while cursor < end:
            sec = next((s for s in sections if s['sh_addr'] <= cursor < s['sh_addr'] + s['sh_size']), None)
            if sec is None:
                # ELF-to-DOL pads each initialized section to a 32-byte end.
                previous = next((s for s in sections if s['sh_addr'] == ds['address']
                                 and s['sh_addr'] + s['sh_size'] == cursor), None)
                if previous is not None and end == ((cursor + 31) & ~31) and retail_bytes(dol, cursor, end - cursor) == bytes(end - cursor):
                    break
                raise ValueError('linked ELF does not cover retail DOL')
            count = min(end, sec['sh_addr'] + sec['sh_size']) - cursor
            off = cursor - sec['sh_addr']
            if sec.data()[off:off + count] != retail_bytes(dol, cursor, count):
                raise ValueError('linked ELF differs from retail DOL')
            cursor += count
    symbols = elf.get_section_by_name('.symtab')
    if symbols is None:
        raise ValueError('linked ELF is missing its symbol table')
    result = {s.name: s['st_value'] for s in symbols.iter_symbols()
              if s.name in ('_SDA_BASE_', '_SDA2_BASE_')}
    if len(result) != 2:
        raise ValueError('linked ELF is missing SDA bases')
    return {13: result['_SDA_BASE_'], 2: result['_SDA2_BASE_']}


@dataclass
class Section:
    index: int
    name: str
    body: bytes
    size: int
    align: int
    bss: bool
    code: bool
    symbols: list
    ranges: list = field(default_factory=list)
    relocs: list = field(default_factory=list)

    def project(self, offset):
        if not self.ranges:
            return offset if 0 <= offset < self.size else None
        return next((dest + offset - lo for lo, hi, dest in self.ranges
                     if lo <= offset < hi), None)


def read_object(data, retained=None, retained_sections=None):
    elf = ELFFile(io.BytesIO(data))
    if elf.elfclass != 32 or elf.little_endian or elf['e_machine'] != 'EM_PPC' or elf['e_type'] != 'ET_REL':
        raise ValueError('requires a big-endian PowerPC ELF32 relocatable object')
    symtab = elf.get_section_by_name('.symtab')
    if symtab is None:
        raise ValueError('missing symbol table')
    symbols = [dict(name=s.name, index=s['st_shndx'], offset=s['st_value'], size=s['st_size'],
                    kind=s['st_info']['type'], local=s['st_info']['bind'] == 'STB_LOCAL')
               for s in symtab.iter_symbols()]
    if any(s['index'] == 'SHN_COMMON' for s in symbols):
        raise ValueError('COMMON storage needs an independent ownership audit')
    sections = {}
    discarded = []
    for index, sec in enumerate(elf.iter_sections()):
        if not sec['sh_flags'] & 2 or not sec['sh_size']:
            continue
        if sec['sh_type'] not in ('SHT_PROGBITS', 'SHT_NOBITS'):
            raise ValueError('unsupported allocated section type')
        model = Section(index, sec.name, sec.data(), sec['sh_size'], max(sec['sh_addralign'], 1),
                        sec['sh_type'] == 'SHT_NOBITS', bool(sec['sh_flags'] & 4),
                        [s for s in symbols if s['index'] == index])
        if any(s['offset'] + s['size'] > model.size for s in model.symbols):
            raise ValueError('symbol extent exceeds its allocated section')
        if retained is not None and model.code:
            funcs = sorted((s for s in model.symbols if s['kind'] == 'STT_FUNC' and s['size']),
                           key=lambda s: s['offset'])
            cursor = output = 0
            for f in funcs:
                if f['offset'] != cursor:
                    raise ValueError('retained hypothesis requires a complete function partition')
                cursor += f['size']
                if f['name'] in retained:
                    model.ranges.append((f['offset'], cursor, output))
                    output += f['size']
                else:
                    discarded.append(f['name'])
            if cursor != model.size or not output:
                raise ValueError('retained hypothesis has missing or empty code ownership')
            model.body = b''.join(model.body[lo:hi] for lo, hi, dest in model.ranges)
            model.size = output
        sections[index] = model
    if not sections:
        raise ValueError('object has no nonempty allocated sections')
    if retained is not None:
        names = {s['name'] for s in symbols if s['kind'] == 'STT_FUNC'}
        if not retained <= names:
            raise ValueError('PAL retained names are absent from the compiled source')
    # A PAL-absent section is only an omission hypothesis. No retained relocation
    # may point into it, and exported data is not silently discarded.
    omitted = []
    if retained_sections is not None:
        for index, sec in list(sections.items()):
            if not sec.code and sec.name not in retained_sections and all(
                    s['local'] or s['kind'] == 'STT_SECTION' for s in sec.symbols):
                omitted.append(sec.name)
                del sections[index]
    for table in elf.iter_sections():
        if table['sh_type'] not in ('SHT_REL', 'SHT_RELA') or table['sh_info'] not in sections:
            continue
        if table['sh_type'] != 'SHT_RELA' or table['sh_link'] != elf.get_section_index('.symtab'):
            raise ValueError('unsupported relocation table')
        sec = sections[table['sh_info']]
        occupied = set()
        for r in table.iter_relocations():
            kind = r['r_info_type']
            if kind not in (1, 4, 5, 6, 10, 109):
                raise ValueError(f'unsupported PowerPC relocation {kind}')
            original_offset = r['r_offset']
            # Old MWCC points SDA21 at the immediate halfword, GNU at the word.
            if kind == 109:
                if original_offset % 4 not in (0, 2):
                    raise ValueError('invalid SDA21 offset')
                original_offset &= ~3
            width = 4 if kind in (1, 10, 109) else 2
            span = set(range(original_offset, original_offset + width))
            original_size = elf.get_section(table['sh_info'])['sh_size']
            if original_offset % width or original_offset + width > original_size or occupied & span:
                raise ValueError('invalid or overlapping relocation extent')
            occupied.update(span)
            offset = sec.project(original_offset)
            last = sec.project(original_offset + width - 1)
            if (offset is None) != (last is None) or offset is not None and last != offset + width - 1:
                raise ValueError('relocation crosses a retained/discarded boundary')
            if offset is None:
                continue
            if kind == 10:
                word = int.from_bytes(sec.body[offset:offset + 4], 'big')
                if word >> 26 != 18 or word & 2:
                    raise ValueError('REL24 requires a relative branch instruction')
            sym = symbols[r['r_info_sym']]
            value = sym['offset'] + r['r_addend']
            if sym['index'] in sections:
                target = sections[sym['index']]
                # Section-end pointers are valid, but discarded code is not.
                value = target.project(value) if target.code else value
                if value is None:
                    raise ValueError('retained relocation references a discarded function')
                key = ('section', sym['index'])
            elif sym['index'] == 'SHN_ABS':
                key = ('absolute', 0)
            elif sym['index'] == 'SHN_UNDEF' and sym['name']:
                key, value = ('global', sym['name']), r['r_addend']
            else:
                raise ValueError('unsupported relocation target')
            sec.relocs.append(dict(offset=offset, kind=kind, key=key, value=value, symbol=sym))
    return sections, discarded, omitted


def masks(sec):
    mask = bytearray(b'\xff' * sec.size)
    for r in sec.relocs:
        offset, kind = r['offset'], r['kind']
        bits = {1: 0xffffffff, 4: 0xffff, 5: 0xffff, 6: 0xffff,
                10: 0x03fffffc, 109: 0x001fffff}[kind]
        width = 2 if kind in (4, 5, 6) else 4
        mask[offset:offset + width] = ((~bits) & ((1 << (width * 8)) - 1)).to_bytes(width, 'big')
    return bytes(mask)


def placements(sec, dol, limit=32):
    """Find all masked placements, including overlapping matches; never choose first."""
    mask = masks(sec)
    runs = list(re.finditer(b'\xff+', mask))
    anchor = max(runs, key=lambda m: m.end() - m.start(), default=None)
    if anchor is None or anchor.end() - anchor.start() < 4:
        return [], 'insufficient fixed bytes'
    pattern = sec.body[anchor.start():anchor.end()]
    result = []
    for ds in dol_sections(dol):
        if (ds['index'] < 7) != sec.code:
            continue
        body = dol[ds['offset']:ds['offset'] + ds['size']]
        cursor = 0
        while True:
            hit = body.find(pattern, cursor)
            if hit < 0:
                break
            cursor = hit + 1
            start = hit - anchor.start()
            if start < 0 or start + sec.size > len(body) or (ds['address'] + start) % sec.align:
                continue
            actual = body[start:start + sec.size]
            if all((a & m) == (b & m) for a, b, m in zip(sec.body, actual, mask)):
                result.append(ds['address'] + start)
                if len(result) >= limit:
                    return result, 'candidate limit reached; ambiguity is unresolved'
    return result, None


def inferred_constraints(sec, address, actual, bases):
    result = []
    for r in sec.relocs:
        off, kind = r['offset'], r['kind']
        value = None
        if kind in (1, 10, 109):
            word = int.from_bytes(actual[off:off + 4], 'big')
            if kind == 1:
                value = word
            elif kind == 10:
                disp = word & 0x03fffffc
                value = address + off + (disp - 0x04000000 if disp & 0x02000000 else disp)
            else:
                reg, disp = (word >> 16) & 31, word & 0xffff
                if reg not in bases:
                    continue
                if r['key'][0] == 'global':
                    result.append((('sda_register', r['key'][1]), reg))
                value = bases[reg] + (disp - 0x10000 if disp & 0x8000 else disp)
        elif kind in (4, 6):
            others = [q for q in sec.relocs if q['key'] == r['key'] and q['value'] == r['value']
                      and q['kind'] == (4 if kind == 6 else 6)]
            values = set()
            for q in others:
                hi_off, lo_off = (off, q['offset']) if kind == 6 else (q['offset'], off)
                hi = int.from_bytes(actual[hi_off:hi_off + 2], 'big')
                lo = int.from_bytes(actual[lo_off:lo_off + 2], 'big')
                values.add(((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo)) & 0xffffffff)
            if len(values) == 1:
                value = values.pop()
        if value is not None:
            result.append((r['key'], (value - r['value']) & 0xffffffff))
    return result


def replay(sec, address, values, bases, sections):
    body = bytearray(sec.body)
    for r in sec.relocs:
        offset, kind = r['offset'], r['kind']
        if r['key'] not in values:
            raise ValueError(f'unresolved relocation target {r["key"]}')
        target = (values[r['key']] + r['value']) & 0xffffffff
        if kind in (4, 5, 6):
            part = {4: target & 65535, 5: target >> 16, 6: ((target + 0x8000) >> 16) & 65535}[kind]
            body[offset:offset + 2] = part.to_bytes(2, 'big')
        elif kind == 1:
            body[offset:offset + 4] = target.to_bytes(4, 'big')
        else:
            word = int.from_bytes(body[offset:offset + 4], 'big')
            if kind == 10:
                disp = target - address - offset
                if disp % 4 or not -0x2000000 <= disp < 0x2000000:
                    raise ValueError('REL24 target is out of range')
                word = (word & ~0x03fffffc) | (disp & 0x03fffffc)
            else:
                if r['key'][0] == 'section':
                    name = sections[r['key'][1]].name
                    reg = 13 if name in ('.sdata', '.sbss') else 2 if name in ('.sdata2', '.sbss2') else None
                else:
                    # SDA windows overlap: distance alone cannot select r2/r13.
                    # Regional section anchors or the retail relocation constrain it.
                    reg = values.get(('sda_register', r['key'][1]))
                if reg not in bases or not -32768 <= target - bases[reg] <= 32767:
                    raise ValueError('SDA21 target is outside its small-data section')
                word = (word & ~0x001fffff) | (reg << 16) | ((target - bases[reg]) & 65535)
            body[offset:offset + 4] = word.to_bytes(4, 'big')
    return bytes(body)


def constrain(values, key, value):
    if key in values and values[key] != value:
        raise ValueError(f'conflicting address constraints for {key}: {values[key]:#x} versus {value:#x}')
    changed = key not in values
    values[key] = value
    return changed


def bss_ownership(unit, sec, address, maps):
    """Prove every storage byte or alignment gap, not merely a subset of names."""
    objects = sorted((s for s in sec.symbols if s['kind'] == 'STT_OBJECT' and s['size']),
                     key=lambda s: s['offset'])
    cursor, unsupported, padding, alignments = 0, [], [], []
    for sym in objects:
        evidence = [m for m in maps if m['owner'] == Path(unit).name and m['name'] == sym['name']
                    and m['section'] == sec.name and m['size'] == sym['size']
                    and m['local'] == sym['local']]
        if not evidence:
            unsupported.append(sym['name'])
            continue
        aligns = {m['align'] for m in evidence}
        if len(aligns) != 1:
            unsupported.append(f'{sym["name"]}: conflicting MAP alignment')
            continue
        align = aligns.pop()
        alignments.append(align)
        if not align or align & (align - 1) or (address + sym['offset']) % align:
            unsupported.append(f'{sym["name"]}: unsupported alignment')
        elif sym['offset'] != ((cursor + align - 1) & -align):
            unsupported.append(f'{sym["name"]}: unexplained gap or overlapping storage')
        elif sym['offset'] > cursor:
            padding.append(dict(offset=cursor, size=sym['offset'] - cursor))
        cursor = sym['offset'] + sym['size']
    if not objects:
        unsupported.append('no complete object ownership')
    if cursor != sec.size:
        if (cursor < sec.size and sec.align <= max(alignments, default=0)
                and sec.size == ((cursor + sec.align - 1) & -sec.align)):
            padding.append(dict(offset=cursor, size=sec.size - cursor))
        else:
            unsupported.append('unexplained trailing storage')
    return unsupported, padding


def solve_hypothesis(unit, sections, discarded, dol, records, bases, maps, globals_):
    values = {('absolute', 0): 0, **{('global', k): v for k, v in globals_.items()}}
    for sym in records:
        if not sym['local'] and sym['section'] in ('.sdata', '.sbss', '.sdata2', '.sbss2'):
            constrain(values, ('sda_register', sym['name']),
                      13 if sym['section'] in ('.sdata', '.sbss') else 2)
    choices, search_notes = {}, {}
    named_bases = set()
    for index, sec in sections.items():
        if sec.bss:
            continue
        choices[index], reason = placements(sec, dol)
        if reason:
            search_notes[index] = reason
    # Unique structural matches seed constraints. Known named source definitions
    # can also locate sections whose bytes contain no useful fixed anchor.
    for index, sec in sections.items():
        for sym in sec.symbols:
            off = sec.project(sym['offset'])
            if off is None or sym['local'] or not sym['size']:
                continue
            if sym['name'] in globals_:
                constrain(values, ('section', index), globals_[sym['name']] - off)
                named_bases.add(index)
    for _ in range(len(sections) + 2):
        changed = False
        for index, sec in sections.items():
            if sec.bss:
                continue
            key = ('section', index)
            if search_notes.get(index, '').startswith('candidate limit') and index not in named_bases:
                continue
            addresses = [values[key]] if key in values else choices[index]
            valid = []
            for address in addresses:
                try:
                    actual = retail_bytes(dol, address, sec.size, sec.code)
                    if any((a & m) != (b & m) for a, b, m in zip(sec.body, actual, masks(sec))):
                        continue
                    trial = dict(values)
                    constrain(trial, key, address)
                    for target, value in inferred_constraints(sec, address, actual, bases):
                        constrain(trial, target, value)
                    valid.append((address, trial))
                except ValueError:
                    continue
            if len(valid) == 1:
                for target, value in valid[0][1].items():
                    changed |= constrain(values, target, value)
            elif not valid and key in values:
                raise ValueError(f'{sec.name}: inferred placement disagrees with retail bytes or anchors')
        if not changed:
            break
    result = dict(unit=unit, discarded_functions=discarded, sections=[], inferred_globals={},
                  review_issues=[], initialized_bytes=0, relocation_count=0)
    definitions = {}
    for index, sec in sections.items():
        key = ('section', index)
        address = values.get(key)
        row = dict(section=sec.name, size=sec.size, address=address, status='unresolved')
        if search_notes.get(index, '').startswith('candidate limit') and index not in named_bases:
            result['review_issues'].append(f'{sec.name}: truncated search needs an independent named base anchor')
        if address is None:
            row['candidates'] = choices.get(index, [])
            if index in search_notes:
                row['search_note'] = search_notes[index]
            result['review_issues'].append(f'{sec.name}: no unique supported placement')
        elif address % sec.align:
            raise ValueError(f'{sec.name}: inferred base violates object alignment')
        elif sec.bss:
            start, size = struct.unpack_from('>II', dol, 0xd8)
            if not start <= address or address + sec.size > start + size:
                raise ValueError('BSS placement is outside retail BSS')
            unsupported, padding = bss_ownership(unit, sec, address, maps)
            row['status'] = 'map_supported_bss' if not unsupported else 'unverified_bss'
            row['unsupported_objects'] = unsupported
            row['alignment_padding'] = padding
            if row['status'] != 'map_supported_bss':
                result['review_issues'].append(f'{sec.name}: BSS needs independent MAP ownership, scope and extent evidence')
        else:
            try:
                actual = retail_bytes(dol, address, sec.size, sec.code)
                if replay(sec, address, values, bases, sections) != actual:
                    raise ValueError('full relocation replay differs from retail')
                row['status'] = 'byte_verified'
                row['sha256'] = hashlib.sha256(actual).hexdigest()
                result['initialized_bytes'] += sec.size
                result['relocation_count'] += len(sec.relocs)
            except ValueError as exc:
                row['reason'] = str(exc)
                result['review_issues'].append(f'{sec.name}: {exc}')
        row['symbols'] = []
        if address is not None:
            for sym in sec.symbols:
                off = sec.project(sym['offset'])
                if off is None or not sym['name'] or sym['kind'] not in ('STT_FUNC', 'STT_OBJECT') or not sym['size']:
                    continue
                entry = dict(name=sym['name'], address=address + off, size=sym['size'], local=sym['local'],
                             kind='function' if sym['kind'] == 'STT_FUNC' else 'object')
                row['symbols'].append(entry)
                if not sym['local']:
                    definitions[sym['name']] = address + off
                for known in records:
                    if known['kind'] not in ('function', 'object'):
                        continue
                    if known['address'] < entry['address'] + entry['size'] and entry['address'] < known['address'] + max(known['size'], 1):
                        anonymous = is_placeholder(known['name'], known['address']) or bool(re.fullmatch(r'lbl_[\dA-Fa-f]{8}', known['name'])) or known['name'].startswith('@')
                        compatible = known['address'] == entry['address'] and known['size'] == entry['size'] and known['section'] == sec.name and known['kind'] == entry['kind'] and (anonymous or known['name'] == entry['name'] and known['local'] == entry['local'])
                        if not compatible:
                            result['review_issues'].append(f'{sec.name}: existing ownership overlaps {entry["name"]}: {known["name"]}')
        result['sections'].append(row)
    for key, value in values.items():
        if key[0] == 'global' and key[1] not in globals_:
            result['inferred_globals'][key[1]] = value
    if result['inferred_globals']:
        result['review_issues'].append('inferred external identities need a verified defining object or regional symbol anchor')
    result['definitions'] = definitions
    result['review_issues'] = sorted(set(result['review_issues']))
    result['status'] = 'review_ready' if not result['review_issues'] else 'hypothesis'
    result['split_snippet'] = unit + ':\n' + ''.join(
        f'\t{s["section"]}\tstart:0x{s["address"]:08X} end:0x{s["address"] + s["size"]:08X}\n'
        for s in result['sections'] if s['address'] is not None and s['status'] in ('byte_verified', 'map_supported_bss'))
    result['symbol_snippet'] = '\n'.join(
        f'{sym["name"]} = {sec["section"]}:0x{sym["address"]:08X}; // type:{sym["kind"]} size:0x{sym["size"]:X}'
        + (' scope:local' if sym['local'] else '')
        for sec in result['sections'] if sec['status'] in ('byte_verified', 'map_supported_bss')
        for sym in sec['symbols'])
    return result


def solve(objects, dol, records=(), bases=None, maps=()):
    """Batch solve; conflicting regional/global anchors never get overwritten."""
    bases = bases or {}
    known = {}
    for sym in records:
        if not sym['local']:
            if sym['name'] in known and known[sym['name']] != sym['address']:
                raise ValueError(f'conflicting global configuration symbol {sym["name"]}')
            known[sym['name']] = sym['address']
    prepared, rejected = [], []
    for obj in objects:
        hypotheses = [('complete_source', None, None)]
        if obj.get('pal_object'):
            pe = ELFFile(io.BytesIO(obj['pal_object']))
            retained = {s.name for s in pe.get_section_by_name('.symtab').iter_symbols()
                        if s['st_info']['type'] == 'STT_FUNC' and isinstance(s['st_shndx'], int) and s['st_size']}
            if retained:
                retained_sections = {s.name for s in pe.iter_sections() if s['sh_flags'] & 2 and s['sh_size']}
                hypotheses.append(('pal_retained_hint', retained, retained_sections))
        seen = set()
        for label, retained, retained_sections in hypotheses:
            try:
                sections, discarded, omitted = read_object(obj['data'], retained, retained_sections)
                signature = (tuple(discarded), tuple(omitted))
                if signature in seen:
                    continue
                seen.add(signature)
                prepared.append((obj, label, sections, discarded, omitted))
            except (ValueError, KeyError) as exc:
                rejected.append(dict(unit=obj['unit'], hypothesis=label, status='rejected', reason=str(exc)))
    # Start at independently review-ready leaves. A pair of callers with only
    # inferred external identities cannot certify each other in a cycle.
    regional_known = dict(known)
    conflicts = {}
    results = []
    converged = False
    for _ in range(2 * len(objects) + 2):
        results, proposals = [], defaultdict(set)
        for obj, label, sections, discarded, omitted in prepared:
            try:
                own_names = {s['name'] for sec in sections.values() for s in sec.symbols
                             if not s['local'] and s['kind'] in ('STT_FUNC', 'STT_OBJECT')}
                # Never let an earlier inferred definition of this same name
                # bias the search and hide a conflicting defining object.
                anchors = {n: a for n, a in known.items() if n in regional_known or n not in own_names}
                row = solve_hypothesis(obj['unit'], sections, discarded, dol, records, bases, maps, anchors)
                row.update(hypothesis=label, object_sha256=hashlib.sha256(obj['data']).hexdigest())
                row['discarded_sections'] = omitted
                if obj.get('source') is not None:
                    row['source_sha256'] = hashlib.sha256(obj['source']).hexdigest()
                    if re.search(rb'^\s*#pragma\s+(?:optimization_level|scheduling|dont_inline|inline_max_size)\b', obj['source'], re.M):
                        row['review_issues'].append('source contains optimizer pragmas; do not promote without runbook-compliant source repair')
                        row['status'] = 'hypothesis'
                for sec in row['sections']:
                    if row['status'] == 'review_ready' and sec['status'] == 'byte_verified':
                        for sym in sec['symbols']:
                            if not sym['local'] and sym['name'] not in conflicts:
                                proposals[sym['name']].add(sym['address'])
                results.append(row)
            except ValueError as exc:
                results.append(dict(unit=obj['unit'], hypothesis=label, status='rejected', reason=str(exc)))
        new = dict(regional_known)
        for name, addresses in proposals.items():
            if len(addresses) != 1 or name in regional_known and regional_known[name] not in addresses:
                conflicts[name] = sorted(addresses | ({regional_known[name]} if name in regional_known else set()))
            elif name not in conflicts and name not in regional_known:
                new[name] = next(iter(addresses))
        # Rebuild, rather than accumulate, derived anchors so rejected evidence
        # also retracts all downstream identities on subsequent passes.
        if new == known:
            converged = True
            break
        known = new
    for row in results:
        if conflicts and row.get('definitions', {}).keys() & conflicts.keys():
            row['status'] = 'hypothesis'
            row.setdefault('review_issues', []).append('conflicting cross-unit symbol definitions')
        if not converged and row['status'] != 'rejected':
            row['status'] = 'hypothesis'
            row.setdefault('review_issues', []).append('batch constraints did not converge')
    return dict(schema_version=1, source_linkage_claims=False, dol_sha1=hashlib.sha1(dol).hexdigest(),
                conflicts=conflicts, objects=results + rejected)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dol', type=Path, required=True)
    parser.add_argument('--symbols', type=Path, required=True)
    parser.add_argument('--linked-elf', type=Path, help='Retail-matching ELF providing validated SDA bases')
    parser.add_argument('--map', type=Path, action='append', default=[])
    parser.add_argument('--object', action='append', default=[], metavar='UNIT=OBJECT')
    parser.add_argument('--source-dir', type=Path, help='Batch all compiled *.o below this directory')
    parser.add_argument('--source-root', type=Path, default=Path('src'))
    parser.add_argument('--include', action='append', default=[], metavar='GLOB',
                        help='Limit --source-dir to source unit paths, e.g. gx/* (repeatable)')
    parser.add_argument('--pal-target-dir', type=Path, help='Optional target objects supplying retain-set hypotheses')
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    inputs = [item.split('=', 1) for item in args.object]
    if args.source_dir:
        for path in sorted(args.source_dir.rglob('*.o')):
            relative = path.relative_to(args.source_dir)
            sources = [relative.with_suffix(ext) for ext in ('.c', '.cpp', '.s')
                       if (args.source_root / relative.with_suffix(ext)).is_file()]
            if len(sources) == 1:
                unit = sources[0].as_posix()
                if not args.include or any(fnmatch.fnmatchcase(unit, pattern) for pattern in args.include):
                    inputs.append((unit, str(path)))
    if not inputs or any(len(item) != 2 for item in inputs):
        parser.error('provide --object UNIT=OBJECT or --source-dir with identifiable source files')
    objects = []
    for unit, filename in inputs:
        row = dict(unit=unit, data=Path(filename).read_bytes())
        source = args.source_root / unit
        if source.is_file():
            row['source'] = source.read_bytes()
        if args.pal_target_dir:
            hint = args.pal_target_dir / Path(unit).with_suffix('.o')
            if hint.is_file():
                row['pal_object'] = hint.read_bytes()
        objects.append(row)
    dol = args.dol.read_bytes()
    bases = sda_bases(args.linked_elf.read_bytes(), dol) if args.linked_elf else {}
    maps = [record for path in args.map for record in map_objects(path.read_text(errors='replace'))]
    report = solve(objects, dol, symbol_records(args.symbols.read_text()), bases, maps)
    report['inputs'] = dict(symbols_sha256=hashlib.sha256(args.symbols.read_bytes()).hexdigest(),
                           maps=[dict(path=str(p), sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in args.map],
                           sda_bases=bases)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    counts = defaultdict(int)
    for row in report['objects']:
        counts[row['status']] += 1
    print(json.dumps(dict(objects=len(objects), hypotheses=dict(counts), output=str(args.output))))


if __name__ == '__main__':
    main()
