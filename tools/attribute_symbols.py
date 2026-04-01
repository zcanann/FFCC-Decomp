#!/usr/bin/env python3
"""
Identify BSS symbols that can be attributed to source files based on naming.
BSS is the biggest opportunity - these are just zero-initialized globals.
If we can figure out which source file each BSS variable belongs to, we can
define them there and claim the address range.

Strategy:
1. Parse symbols.txt for unclaimed .bss symbols
2. Match symbol names to source files using naming patterns
3. Group consecutive symbols that belong to the same file
4. Output actionable recommendations with address ranges
"""
import re
import os
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(REPO, "config/GCCP01/symbols.txt")
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")
SRC_DIR = os.path.join(REPO, "src")

def parse_symbols():
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
                syms.append((name, section, addr, size, rest))
    return syms

def parse_splits():
    claimed = defaultdict(list)  # section -> [(start, end, filename)]
    current = None
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':') and not line.startswith('Sections'):
                current = line.rstrip(':')
            elif current and line.strip():
                m = re.search(r'(\.\w+)\s+start:(0x[\da-fA-F]+)\s+end:(0x[\da-fA-F]+)', line.strip())
                if m:
                    claimed[m.group(1)].append((int(m.group(2), 16), int(m.group(3), 16), current))
    for sec in claimed:
        claimed[sec].sort()
    return claimed

def get_source_files():
    files = set()
    for f in os.listdir(SRC_DIR):
        if f.endswith('.cpp') or f.endswith('.c'):
            files.add(f.replace('.cpp', '').replace('.c', ''))
    return files

def guess_owner(sym_name, source_files):
    """Try to guess which source file a symbol belongs to based on naming"""
    name = sym_name.lower()
    
    # Direct class/module prefixes
    prefixes = {
        'game': 'game', 'Game': 'game',
        'graphic': 'graphic', 'Graphic': 'graphic',
        'map': 'map', 'Map': 'map',
        'chara': 'chara', 'Chara': 'chara',
        'sound': 'sound', 'Sound': 'sound',
        'menu': 'menu', 'Menu': 'menu',
        'file': 'file', 'File': 'file', 'CFile': 'file',
        'memory': 'memory', 'Memory': 'memory',
        'math': 'math', 'Math': 'math',
        'color': 'color', 'Color': 'color',
        'cmake': 'cmake', 'CMake': 'cmake',
        'gbaque': 'gbaque',
        'joybus': 'joybus',
        'pad': 'pad', 'Pad': 'pad',
        'gobject': 'gobject',
        'gobjwork': 'gobjwork',
        'goout': 'goout',
        'partmng': 'partMng', 'PartMng': 'partMng',
        'partyobj': 'partyobj',
        'monobj': 'monobj',
        'itemobj': 'itemobj',
        'baseobj': 'baseobj',
        'charaobj': 'charaobj',
        'fontman': 'fontman',
        'materialman': 'materialman',
        'memorycard': 'memorycard',
        'astar': 'astar',
        'wind': 'wind',
        'bonus_menu': 'bonus_menu',
        'gxfunc': 'gxfunc',
        'mes': 'mes', 'Mes': 'mes',
        'mesmenu': 'mesmenu',
        'textureman': 'textureman',
    }
    
    for prefix, src in prefixes.items():
        if sym_name.startswith(prefix) or sym_name.startswith('g' + prefix[0].upper() + prefix[1:]):
            if src in source_files:
                return src
    
    # Check for class names: __vt__N means vtable for class N
    vtm = re.match(r'__vt__\d*(\w+)', sym_name)
    if vtm:
        class_name = vtm.group(1).lower()
        for sf in source_files:
            if class_name == sf.lower() or class_name in sf.lower():
                return sf
    
    return None

def main():
    syms = parse_symbols()
    claimed = parse_splits()
    source_files = get_source_files()
    
    # Find unclaimed symbols in each data section
    for section in ['.bss', '.data', '.rodata', '.sdata2', '.sdata', '.sbss']:
        sec_syms = [(n, s, a, sz, r) for n, s, a, sz, r in syms if s == section]
        sec_syms.sort(key=lambda x: x[2])
        
        # Filter to unclaimed
        unclaimed = []
        for name, sec, addr, size, rest in sec_syms:
            is_claimed = False
            for s, e, f in claimed.get(section, []):
                if s <= addr < e:
                    is_claimed = True
                    break
            if not is_claimed:
                owner = guess_owner(name, source_files)
                unclaimed.append((name, addr, size, owner))
        
        if not unclaimed:
            continue
        
        # Group by guessed owner
        by_owner = defaultdict(list)
        for name, addr, size, owner in unclaimed:
            by_owner[owner or '???'].append((addr, size, name))
        
        total_unclaimed = sum(sz for _, _, sz, _ in unclaimed)
        total_attributed = sum(sz for _, _, sz, o in unclaimed if o)
        
        print(f"\n{'='*90}")
        print(f"SECTION: {section} - {total_unclaimed} bytes unclaimed, {total_attributed} bytes attributed")
        print(f"{'='*90}")
        
        # Print by owner, sorted by total bytes
        owner_totals = []
        for owner, sym_list in by_owner.items():
            total = sum(sz for _, sz, _ in sym_list)
            owner_totals.append((total, owner, sym_list))
        owner_totals.sort(reverse=True)
        
        for total, owner, sym_list in owner_totals[:30]:
            sym_list.sort()
            first_addr = sym_list[0][0]
            last_addr = sym_list[-1][0] + sym_list[-1][1]
            print(f"\n  {owner} ({total} bytes, {len(sym_list)} symbols, 0x{first_addr:08X}-0x{last_addr:08X}):")
            for addr, size, name in sym_list[:8]:
                print(f"    0x{addr:08X} [{size:>5}] {name}")
            if len(sym_list) > 8:
                print(f"    ... and {len(sym_list) - 8} more")

if __name__ == '__main__':
    main()
