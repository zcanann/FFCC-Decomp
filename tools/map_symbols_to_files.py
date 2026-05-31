#!/usr/bin/env python3
"""
Map auto block symbols to source files using the MAP file and link order.
For each auto block, find the symbols it contains and try to attribute them
to specific source files based on the MAP file's object file associations.
"""
import re
import os
import sys
from collections import defaultdict
from pathlib import Path

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, REPO)

from tools.map.map_index import default_game_map_path, load_map_index

SYMBOLS = os.path.join(REPO, "config/GCCP01/symbols.txt")
MAP_FILE = str(default_game_map_path(Path(REPO), "GCCP01"))
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")

DATA_SECTIONS = {'.data', '.rodata', '.bss', '.sbss', '.sdata', '.sdata2'}
LOCAL_GENERATED_NAME_RE = re.compile(r'@|lbl_|gap_|pad_|jumptable_|FLOAT_|DOUBLE_|DAT_')

def parse_symbols():
    """Parse symbols.txt -> list of (name, section, addr, size, line_info)"""
    syms = []
    with open(SYMBOLS) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#') or line.startswith('//'):
                continue
            m = re.match(r'(\S+)\s*=\s*(\.\w+):(0x[\da-fA-F]+)\s*;(.*)', line)
            if m:
                name = m.group(1)
                section = m.group(2)
                addr = int(m.group(3), 16)
                rest = m.group(4)
                sm = re.search(r'size:(0x[\da-fA-F]+)', rest)
                size = int(sm.group(1), 16) if sm else 0
                syms.append((name, section, addr, size, rest.strip()))
    return syms

def parse_splits():
    """Parse splits.txt -> dict: filename -> list of (section, start, end)"""
    claimed = {}
    current = None
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':') and not line.startswith('Sections'):
                current = line.rstrip(':')
                claimed.setdefault(current, [])
            elif current and line.strip():
                m = re.search(r'(\.\w+)\s+start:(0x[\da-fA-F]+)\s+end:(0x[\da-fA-F]+)', line.strip())
                if m:
                    sec = m.group(1)
                    s = int(m.group(2), 16)
                    e = int(m.group(3), 16)
                    claimed[current].append((sec, s, e))
    return claimed

def extract_map_symbols():
    """Extract symbol -> object file mappings from MAP file"""
    exact = {}
    by_name = defaultdict(set)
    if not os.path.exists(MAP_FILE):
        return exact, {}

    index = load_map_index(MAP_FILE)
    for records in index.layout_by_symbol.values():
        for record in records:
            if record.virtual_address is None or record.symbol_name == record.section:
                continue
            key = (record.section, record.virtual_address, record.symbol_name)
            exact[key] = record.object_file
            by_name[record.symbol_name].add(record.object_file)

    unique_by_name = {
        name: next(iter(objects))
        for name, objects in by_name.items()
        if len(objects) == 1
    }
    return exact, unique_by_name

def can_use_unique_name_fallback(name):
    """Avoid attributing compiler-local/generated names by name alone.

    MAP files contain many unrelated local symbols named like @234 or lbl_....
    Those are only trustworthy when the section/address also matches.
    """
    return LOCAL_GENERATED_NAME_RE.match(name) is None

def main():
    syms = parse_symbols()
    splits = parse_splits()
    
    # Build set of all claimed address ranges per section
    claimed_ranges = defaultdict(list)  # section -> [(start, end, filename)]
    for fname, entries in splits.items():
        for sec, s, e in entries:
            claimed_ranges[sec].append((s, e, fname))
    for sec in claimed_ranges:
        claimed_ranges[sec].sort()
    
    def is_claimed(section, addr):
        for s, e, fname in claimed_ranges.get(section, []):
            if s <= addr < e:
                return fname
        return None
    
    # Find unclaimed symbols in data sections, grouped by potential source
    unclaimed = defaultdict(list)  # section -> list of (addr, size, name, info)
    for name, section, addr, size, info in syms:
        if section not in DATA_SECTIONS:
            continue
        owner = is_claimed(section, addr)
        if owner is None:
            unclaimed[section].append((addr, size, name, info))
    
    # Try to map to object files using MAP
    print("Loading MAP file for symbol->object mapping...")
    exact_map, unique_name_map = extract_map_symbols()
    print(f"  Found {len(exact_map)} address-qualified symbol mappings")
    print(f"  Found {len(unique_name_map)} unique-name fallback mappings\n")
    
    # Group unclaimed symbols by potential object file
    by_obj = defaultdict(lambda: defaultdict(list))  # obj_file -> section -> [(addr, size, name)]
    unresolved = defaultdict(list)
    
    for section, sym_list in unclaimed.items():
        for addr, size, name, info in sym_list:
            obj = exact_map.get((section, addr, name))
            if obj is None and can_use_unique_name_fallback(name):
                obj = unique_name_map.get(name)
            if obj:
                by_obj[obj][section].append((addr, size, name))
            else:
                unresolved[section].append((addr, size, name))
    
    # Print results grouped by object file
    print("=" * 90)
    print("UNCLAIMED SYMBOLS MAPPED TO OBJECT FILES (from MAP)")
    print("=" * 90)
    
    obj_totals = []
    for obj_file, sections in sorted(by_obj.items()):
        total = sum(size for sym_list in sections.values() for _, size, _ in sym_list)
        obj_totals.append((total, obj_file, sections))
    
    obj_totals.sort(reverse=True)
    
    for total, obj_file, sections in obj_totals[:50]:
        print(f"\n  {obj_file} ({total} bytes unclaimed):")
        for sec_name in sorted(sections.keys()):
            sym_list = sections[sec_name]
            sec_total = sum(s for _, s, _ in sym_list)
            print(f"    {sec_name}: {sec_total} bytes ({len(sym_list)} symbols)")
            for addr, size, name in sorted(sym_list)[:5]:
                print(f"      0x{addr:08X} [{size:>5}] {name}")
            if len(sym_list) > 5:
                print(f"      ... and {len(sym_list) - 5} more")
    
    grand_total_mapped = sum(t for t, _, _ in obj_totals)
    print(f"\n  TOTAL MAPPED: {grand_total_mapped} bytes across {len(obj_totals)} object files")
    
    # Print unresolved symbols summary
    print(f"\n{'='*90}")
    print("UNCLAIMED SYMBOLS NOT MAPPED TO ANY OBJECT FILE")
    print("=" * 90)
    for section in sorted(unresolved.keys()):
        sym_list = unresolved[section]
        total = sum(s for _, s, _ in sym_list)
        print(f"  {section}: {total} bytes ({len(sym_list)} symbols)")
        for addr, size, name in sorted(sym_list)[:5]:
            print(f"    0x{addr:08X} [{size:>5}] {name}")
        if len(sym_list) > 5:
            print(f"    ... and {len(sym_list) - 5} more")

if __name__ == '__main__':
    main()
