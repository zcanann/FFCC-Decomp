#!/usr/bin/env python3
"""
Map BSS symbols to source files using link order from splits.txt.
Metrowerks linker places BSS from each TU in link order.
We know the BSS data boundaries from symbols.txt, and the link order from splits.txt.
"""
import re
import os
from collections import defaultdict, OrderedDict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(REPO, "config/GCCP01/symbols.txt")
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")

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
                syms.append((name, section, addr, size))
    return syms

def parse_splits_file_order_and_claims():
    """Parse splits.txt for file order and existing section claims"""
    files_order = []
    claimed = {}  # file -> {section -> [(start, end)]}
    current_file = None
    
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':'):
                name = line.rstrip(':')
                if name != 'Sections':
                    current_file = name
                    files_order.append(name)
                    claimed[name] = defaultdict(list)
            elif current_file and line.strip():
                m = re.match(r'\s+(\.\w+)\s+start:(0x[\da-fA-F]+)\s+end:(0x[\da-fA-F]+)', line)
                if m:
                    sec = m.group(1)
                    s = int(m.group(2), 16)
                    e = int(m.group(3), 16)
                    claimed[current_file][sec].append((s, e))
    
    return files_order, claimed

def main():
    syms = parse_symbols()
    files_order, claimed = parse_splits_file_order_and_claims()
    
    # Get all .bss symbols sorted by address
    bss_syms = [(n, a, sz) for n, s, a, sz in syms if s == '.bss']
    bss_syms.sort(key=lambda x: x[1])
    
    # Get existing .bss claims
    bss_claims = []
    for f, secs in claimed.items():
        for s, e in secs.get('.bss', []):
            bss_claims.append((s, e, f))
    bss_claims.sort()
    
    print("=== EXISTING .bss CLAIMS ===")
    for s, e, f in bss_claims:
        print(f"  0x{s:08X}-0x{e:08X} ({e-s:>6} bytes) {f}")
    
    print(f"\n=== ALL .bss SYMBOLS ({len(bss_syms)} total, {sum(sz for _,_,sz in bss_syms)} bytes) ===")
    
    # Figure out which symbols are claimed vs unclaimed
    unclaimed_syms = []
    for name, addr, size in bss_syms:
        is_claimed = False
        for s, e, f in bss_claims:
            if s <= addr < e:
                is_claimed = True
                break
        if not is_claimed:
            unclaimed_syms.append((name, addr, size))
    
    print(f"  Unclaimed: {len(unclaimed_syms)} symbols, {sum(sz for _,_,sz in unclaimed_syms)} bytes")
    
    # Now try to attribute using link order logic
    # The game source files (not SDK/runtime) have BSS in link order
    game_files = [f for f in files_order if not any(f.startswith(p) for p in 
        ['Runtime.', 'MSL_C/', 'TRK_', 'OdemuExi2/', 'amcstubs/', 'odenotstub/', 'RedSound/', 'thp/', 'dolphin/'])]
    
    # For each game file, find the first .text address to establish link order
    file_text_start = {}
    for f, secs in claimed.items():
        if f in game_files and '.text' in secs:
            starts = [s for s, e in secs['.text']]
            if starts:
                file_text_start[f] = min(starts)
    
    # Sort game files by text address (= link order)
    game_files_sorted = sorted([f for f in game_files if f in file_text_start], 
                                key=lambda f: file_text_start[f])
    
    print(f"\n=== GAME FILES LINK ORDER ({len(game_files_sorted)}) ===")
    for i, f in enumerate(game_files_sorted):
        has_bss = '.bss' in claimed.get(f, {})
        marker = " [HAS BSS]" if has_bss else ""
        print(f"  {i+1:>3}. {f}{marker}")
    
    # Now map BSS ranges. Strategy: 
    # For each pair of consecutive files in link order, the BSS between them belongs to the first file.
    # But some files might not have BSS at all.
    # 
    # Known BSS ownership (from symbol names):
    known_ownership = {
        'File': 'file.cpp',
        'GameDtorChain': 'game.cpp',
        'Game': 'game.cpp', 
        'Graphic': 'graphic.cpp',
        'GraphicsPcs': 'p_graphic.cpp',
        'm_thread': 'main.cpp',  # reasonable guess
        'm_threadStack': 'main.cpp',  # reasonable guess
        'Math': 'math.cpp',
        's_f_vpos': 'math.cpp',  # static float in math
        's_f_lvmtx': 'math.cpp',  # static float matrix in math
        'Memory': 'memory.cpp',
        'MemoryCardMan': 'memorycard.cpp',
        'Pad': 'pad.cpp',
        'System': 'system.cpp',
        'USB': 'usb.cpp',
        'MapMng': 'map.cpp',
        'MapPcs': 'p_map.cpp',
        'PartMng': 'partMng.cpp',
        'Chara': 'chara.cpp',
        'CharaPcs': 'p_chara.cpp',
        'MenuPcs': 'p_menu.cpp',
        'Sound': 'sound.cpp',
    }
    
    print(f"\n=== PROPOSED .bss CLAIMS ===")
    print("(Based on known symbol ownership + link order adjacency)")
    
    # Group consecutive unclaimed syms by owner
    file_bss_ranges = defaultdict(list)  # file -> [(addr, size, name)]
    
    for name, addr, size in unclaimed_syms:
        owner = known_ownership.get(name)
        if owner:
            file_bss_ranges[owner].append((addr, size, name))
    
    # Print proposed ranges
    total_claimable = 0
    for f in game_files_sorted:
        if f in file_bss_ranges:
            syms_list = sorted(file_bss_ranges[f])
            start = syms_list[0][0]
            end = syms_list[-1][0] + syms_list[-1][1]
            total_bytes = end - start
            total_claimable += total_bytes
            
            # Check for gaps in the range
            has_gaps = False
            for i in range(len(syms_list)-1):
                expected_next = syms_list[i][0] + syms_list[i][1]
                actual_next = syms_list[i+1][0]
                if expected_next != actual_next:
                    has_gaps = True
                    break
            
            gap_note = " [HAS GAPS - NEED INVESTIGATION]" if has_gaps else " [CONTIGUOUS]"
            print(f"\n  {f}: .bss start:0x{start:08X} end:0x{end:08X} ({total_bytes} bytes){gap_note}")
            for addr, size, name in syms_list:
                print(f"    0x{addr:08X} [{size:>6}] {name}")
    
    print(f"\n=== SUMMARY ===")
    print(f"Total claimable via known symbols: {total_claimable} bytes")
    
    # Now check for unknown symbols between known ones
    print(f"\n=== UNKNOWN .bss SYMBOLS (between known boundaries) ===")
    for name, addr, size in unclaimed_syms:
        if name not in known_ownership:
            # Find surrounding known symbols
            prev_known = None
            next_known = None
            for kn, ka, ks in unclaimed_syms:
                if kn in known_ownership:
                    if ka < addr:
                        prev_known = (kn, ka, ks, known_ownership[kn])
                    elif ka > addr and next_known is None:
                        next_known = (kn, ka, ks, known_ownership[kn])
                        break
            
            prev_info = f"after {prev_known[0]}({prev_known[3]})" if prev_known else "???"
            next_info = f"before {next_known[0]}({next_known[3]})" if next_known else "???"
            print(f"  0x{addr:08X} [{size:>6}] {name:40s} {prev_info}, {next_info}")

if __name__ == '__main__':
    main()
