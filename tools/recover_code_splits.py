#!/usr/bin/env python3
"""Dry-run recovery of complete GameCube code-only objects.

This conservative pass rejects data, BSS and COMMON. Relocations
are rejected by default; --allow-relocations replays supported PPC relocations
using existing symbol identities, never guessed destinations or masked bytes.
It searches executable DOL sections for every byte of the complete ELF section,
requires unique, nonoverlapping aligned placements for all allocated .text and
.init sections, and checks existing named function anchors.
It produces reviewable split/symbol snippets, never completion claims or edits.
Requires pyelftools. Example:
  python tools/recover_code_splits.py --dol orig/GCCE01/sys/main.dol \
    --symbols config/GCCE01/symbols.txt \
    --object Runtime.PPCEABI.H/__va_arg.c=build/GCCE01/src/Runtime.PPCEABI.H/__va_arg.o
"""

import argparse
import hashlib
import io
import json
from pathlib import Path
import re
import struct

from elftools.elf.elffile import ELFFile


def dol_sections(data):
    if len(data) < 0x100:
        raise ValueError('truncated DOL header')
    offsets = struct.unpack_from('>18I', data)
    addresses = struct.unpack_from('>18I', data, 0x48)
    sizes = struct.unpack_from('>18I', data, 0x90)
    sections = []
    for index, (offset, address, size) in enumerate(zip(offsets, addresses, sizes)):
        if not size:
            continue
        if offset < 0x100 or offset + size > len(data) or address + size > 0x100000000:
            raise ValueError('invalid DOL section bounds')
        if any(address < s['address'] + s['size'] and s['address'] < address + size
               for s in sections):
            raise ValueError('overlapping DOL section addresses')
        sections.append(dict(index=index, offset=offset, address=address, size=size))
    return sections


def read_symbols(text):
    result = {}
    for line in text.splitlines():
        match = re.match(r'(\S+)\s*=\s*(\S+):0x([0-9A-Fa-f]+);\s*//\s*(.*)', line)
        if match:
            attrs = dict(part.split(':', 1) for part in match[4].split() if ':' in part)
            result[match[1]] = dict(address=int(match[3], 16), section=match[2],
                                   kind=attrs.get('type'), size=int(attrs.get('size', '0'), 0))
    return result


def is_placeholder(name, address):
    return bool(re.fullmatch(r'fn_[0-9A-Fa-f]{8}', name)) and int(name[3:], 16) == address


def code_relocations(elf, index, section, symtab, known):
    """Resolve all inputs before searching; retain section-relative definitions."""
    result, occupied = [], set()
    for table in elf.iter_sections():
        if table['sh_type'] not in ('SHT_REL', 'SHT_RELA') or table['sh_info'] != index:
            continue
        if table['sh_type'] != 'SHT_RELA' or table['sh_link'] != elf.get_section_index('.symtab'):
            raise ValueError('unsupported relocation table')
        for rel in table.iter_relocations():
            kind, offset = rel['r_info_type'], rel['r_offset']
            if kind not in (4, 5, 6, 10):
                raise ValueError(f'unsupported PowerPC relocation {kind}')
            width = 4 if kind == 10 else 2
            span = set(range(offset, offset + width))
            if offset + width > section['sh_size'] or offset % width or span & occupied:
                raise ValueError('invalid or overlapping code relocation extent')
            occupied.update(span)
            if kind == 10:
                word = int.from_bytes(section.data()[offset:offset + 4], 'big')
                if word >> 26 != 18 or word & 2:
                    raise ValueError('REL24 requires a relative branch instruction')
            symbol = symtab.get_symbol(rel['r_info_sym'])
            relative = symbol['st_shndx'] == index
            if relative or symbol['st_shndx'] == 'SHN_ABS':
                value = symbol['st_value']
            elif symbol['st_shndx'] == 'SHN_UNDEF' and symbol.name in known:
                value = known[symbol.name]['address']
            else:
                raise ValueError('unresolved relocation target: ' + symbol.name)
            result.append(dict(kind=kind, offset=offset, value=value + rel['r_addend'],
                               relative=relative, symbol=symbol.name))
    return result, occupied


def relocate_code(body, address, relocations):
    output = bytearray(body)
    for rel in relocations:
        offset, kind = rel['offset'], rel['kind']
        value = rel['value'] + (address if rel['relative'] else 0)
        if kind == 10:
            displacement = value - address - offset
            if displacement % 4 or not -0x2000000 <= displacement < 0x2000000:
                raise ValueError('REL24 destination is unaligned or out of range')
            word = int.from_bytes(body[offset:offset + 4], 'big')
            output[offset:offset + 4] = ((word & ~0x3FFFFFC) | (displacement & 0x3FFFFFC)).to_bytes(4, 'big')
        else:
            if kind == 5:
                value >>= 16
            elif kind == 6:
                value = (value + 0x8000) >> 16
            output[offset:offset + 2] = (value & 0xFFFF).to_bytes(2, 'big')
    return bytes(output)


def recover(unit, object_bytes, dol, known, allow_relocations=False):
    row = dict(unit=unit, object_sha256=hashlib.sha256(object_bytes).hexdigest(),
               status='rejected')
    elf = ELFFile(io.BytesIO(object_bytes))
    if elf.elfclass != 32 or elf.little_endian or elf['e_machine'] != 'EM_PPC' or elf['e_type'] != 'ET_REL':
        row['reason'] = 'requires big-endian ELF32 PowerPC relocatable object'
        return row
    allocated = [(i, s) for i, s in enumerate(elf.iter_sections()) if s['sh_flags'] & 2 and s['sh_size']]
    if (not allocated or any(s.name not in ('.text', '.init') or not s['sh_flags'] & 4 for _, s in allocated)
            or len({s.name for _, s in allocated}) != len(allocated)):
        row['reason'] = 'requires only distinct allocated executable .text and .init sections'
        return row
    symtab = elf.get_section_by_name('.symtab')
    if symtab is None or any(s['st_shndx'] == 'SHN_COMMON' for s in symtab.iter_symbols()):
        row['reason'] = 'missing symbol table or unverified COMMON storage'
        return row
    if len(allocated) == 1:
        index, section = allocated[0]
        return recover_section(row, unit, elf, index, section, symtab, dol, known, allow_relocations)
    sections = [recover_section(dict(status='rejected', section=s.name), unit, elf, i, s, symtab,
                                dol, known, allow_relocations) for i, s in allocated]
    row['sections'] = sections
    failed = next((s for s in sections if s['status'] != 'verified'), None)
    if failed:
        row['reason'] = f"{failed['section']}: {failed['reason']}"
        return row
    ordered = sorted(sections, key=lambda s: s['address'])
    if any(a['address'] + a['size'] > b['address'] for a, b in zip(ordered, ordered[1:])):
        row['reason'] = 'recovered executable sections overlap'
        return row
    row.update(status='verified', verified_bytes=sum(s['verified_bytes'] for s in sections),
               relocation_count=sum(s['relocation_count'] for s in sections),
               functions=[f for s in sections for f in s['functions']],
               split_snippet=f'{unit}:\n' + ''.join(
                   f"\t{s['section']} start:0x{s['address']:08X} end:0x{s['address'] + s['size']:08X}\n"
                   for s in sections))
    return row


def recover_section(row, unit, elf, index, section, symtab, dol, known, allow_relocations):
    """Verify one complete executable section without certifying other storage."""
    has_relocations = any(s['sh_type'] in ('SHT_REL', 'SHT_RELA') and s['sh_info'] == index and s.num_relocations()
                          for s in elf.iter_sections())
    if has_relocations and not allow_relocations:
        row['reason'] = 'content relocations require separate verification'
        return row
    try:
        relocations, occupied = code_relocations(elf, index, section, symtab, known) if has_relocations else ([], set())
    except ValueError as error:
        row['reason'] = str(error)
        return row
    body = section.data()
    if len(body) < 16:
        row['reason'] = 'insufficient complete code bytes for unanchored identity'
        return row
    # An unchanged byte run locates candidates cheaply; every relocation and
    # every other byte must then agree. Never accept wildcard-only comparisons.
    runs = []
    start = 0
    for offset in sorted(occupied) + [len(body)]:
        if start < offset:
            runs.append((start, body[start:offset]))
        start = offset + 1
    if not runs:
        row['reason'] = 'no unchanged code bytes to establish placement'
        return row
    anchor_offset, anchor = max(runs, key=lambda run: len(run[1]))
    candidates = []
    for segment in dol_sections(dol):
        if segment['index'] >= 7:
            continue
        image = dol[segment['offset']:segment['offset'] + segment['size']]
        start = 0
        while (hit := image.find(anchor, start)) >= 0:
            start = hit + 1
            at = hit - anchor_offset
            if at < 0 or at + len(body) > len(image):
                continue
            address = segment['address'] + at
            if address % max(4, section['sh_addralign']) == 0:
                try:
                    expected = relocate_code(body, address, relocations)
                except ValueError:
                    continue
                if image[at:at + len(body)] != expected:
                    continue
                candidates.append(address)
                if len(candidates) == 2:
                    break
        if len(candidates) == 2:
            break
    row['candidates'] = candidates
    if len(candidates) != 1:
        row['reason'] = 'no exact placement' if not candidates else 'multiple exact placements (first two shown)'
        return row
    address = candidates[0]
    functions = []
    for symbol in symtab.iter_symbols():
        if symbol['st_shndx'] != index or symbol['st_info']['type'] != 'STT_FUNC':
            continue
        at, size = address + symbol['st_value'], symbol['st_size']
        if not size or symbol['st_value'] + size > len(body):
            row['reason'] = 'function extent is missing or exceeds complete section'
            return row
        old = known.get(symbol.name)
        if old and (old['address'] != at or old['section'] != section.name or old['kind'] != 'function'
                    or old['size'] not in (0, size)):
            row['reason'] = 'existing named function disagrees: ' + symbol.name
            return row
        aliases = [name for name, s in known.items() if s['address'] == at and s['kind'] == 'function']
        if any(name != symbol.name and not is_placeholder(name, at) for name in aliases):
            row['reason'] = 'another named function owns address of ' + symbol.name
            return row
        scope = {'STB_LOCAL': 'local', 'STB_WEAK': 'weak'}.get(symbol['st_info']['bind'], 'global')
        functions.append(dict(name=symbol.name, address=at, size=size, existing_names=aliases,
            symbol_line=f'{symbol.name} = {section.name}:0x{at:08X}; // type:function size:0x{size:X} scope:{scope}'))
    if not functions:
        row['reason'] = 'no function identities in source object'
        return row
    # Equal bytes do not override contradictory ownership. Check the complete
    # candidate range, including padding and known definitions that begin before
    # it. A zero-size definition establishes only its start, not an unknown span.
    # Ordinary labels inside functions are branch targets rather than owners.
    for name, old in known.items():
        if old['kind'] not in ('function', 'object'):
            continue
        if old['address'] >= address + len(body) or old['address'] + max(old['size'], 1) <= address:
            continue
        consistent = old['kind'] == 'function' and old['section'] == section.name and any(
            old['address'] == f['address'] and old['size'] in (0, f['size'])
            and (name == f['name'] or is_placeholder(name, f['address'])) for f in functions)
        if not consistent:
            row['reason'] = 'overlapping known definition disagrees: ' + name
            return row
    row.update(status='verified', section=section.name, address=address, size=len(body),
               verified_bytes=len(body), relocation_count=len(relocations), functions=functions,
               split_snippet=f'{unit}:\n\t{section.name} start:0x{address:08X} end:0x{address + len(body):08X}\n')
    return row


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--dol', type=Path, required=True)
    parser.add_argument('--symbols', type=Path, required=True)
    parser.add_argument('--object', action='append', required=True, metavar='UNIT=OBJECT')
    parser.add_argument('--output', type=Path)
    parser.add_argument('--allow-relocations', action='store_true',
                        help='replay ADDR16_LO/HI/HA and REL24 using known or local targets')
    args = parser.parse_args()
    dol = args.dol.read_bytes()
    dol_sections(dol)
    symbols = read_symbols(args.symbols.read_text(encoding='utf-8'))
    records = []
    for item in sorted(args.object):
        unit, path = item.split('=', 1)
        record = recover(unit, Path(path).read_bytes(), dol, symbols, args.allow_relocations)
        record['object'] = path
        records.append(record)
    result = dict(schema_version=1, dol_sha1=hashlib.sha1(dol).hexdigest(),
                  source_linkage_claims=False, objects=records)
    text = json.dumps(result, indent=2) + '\n'
    if args.output:
        args.output.write_text(text, encoding='utf-8')
    else:
        print(text, end='')


if __name__ == '__main__':
    main()
