#!/usr/bin/env python3
"""
Automatically add matched section claims to splits.txt.
This script:
1. Finds all section ranges where compiled size matches an unclaimed symbol range
2. Adds those ranges to splits.txt
3. Reports what was added
"""
import re
import os
import subprocess
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(REPO, "config/GCCP01/symbols.txt")
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")
OBJDUMP = os.path.join(REPO, "build/binutils/powerpc-eabi-objdump")

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

def parse_splits():
    files = {}  # file -> {section -> [(start, end)]}
    file_order = []
    current = None
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':') and not line.startswith('Sections'):
                current = line.rstrip(':')
                file_order.append(current)
                files[current] = {}
            elif current and line.strip():
                m = re.match(r'\s+(\.\w+)\s+start:(0x[\da-fA-F]+)\s+end:(0x[\da-fA-F]+)', line)
                if m:
                    sec = m.group(1)
                    s = int(m.group(2), 16)
                    e = int(m.group(3), 16)
                    if sec not in files[current]:
                        files[current][sec] = []
                    files[current][sec].append((s, e))
    return files, file_order

def get_compiled_section_size(fname, section):
    obj_path = os.path.join(REPO, f"build/GCCP01/src/{fname.replace('.cpp', '.o').replace('.c', '.o')}")
    if not os.path.exists(obj_path):
        return None
    try:
        r = subprocess.run([OBJDUMP, '-h', obj_path], capture_output=True, text=True)
        for line in r.stdout.split('\n'):
            parts = line.split()
            if len(parts) >= 3 and parts[1] == section:
                return int(parts[2], 16)
    except:
        pass
    return None

def find_matching_range(unclaimed, compiled_size, start_from=0):
    """Find a contiguous block of unclaimed symbols that totals compiled_size"""
    for start_idx in range(start_from, len(unclaimed)):
        running_total = 0
        for end_idx in range(start_idx, len(unclaimed)):
            running_total += unclaimed[end_idx][2]  # size
            if running_total == compiled_size:
                # Check contiguous
                range_start = unclaimed[start_idx][1]
                range_end = unclaimed[end_idx][1] + unclaimed[end_idx][2]
                contiguous = True
                for j in range(start_idx, end_idx):
                    expected = unclaimed[j][1] + unclaimed[j][2]
                    actual = unclaimed[j+1][1]
                    if expected != actual:
                        contiguous = False
                        break
                if contiguous:
                    return start_idx, end_idx + 1, range_start, range_end
                break
            elif running_total > compiled_size:
                break
    return None

def main():
    syms = parse_symbols()
    splits, file_order = parse_splits()
    
    # Game source files
    game_files = []
    for f in file_order:
        if any(f.startswith(p) for p in 
            ['Runtime.', 'MSL_C/', 'TRK_', 'OdemuExi2/', 'amcstubs/', 'odenotstub/', 'RedSound/', 'thp/', 
             'dolphin/', 'base/', 'db/', 'os/', 'exi/', 'si/', 'mtx/', 'dvd/', 'vi/', 'pad/', 'ai/', 
             'ar/', 'ax/', 'axfx/', 'mix/', 'axart/', 'dsp/', 'card/', 'gx/', 'gba/']):
            continue
        if '.text' in splits.get(f, {}):
            starts = [s for s, e in splits[f]['.text']]
            if starts:
                game_files.append((min(starts), f))
    game_files.sort()
    game_files = [f for _, f in game_files]
    
    # For each data section, find matchable ranges
    new_claims = {}  # file -> {section -> (start, end)}
    
    for section in ['.sdata2', '.data', '.rodata', '.sdata', '.sbss']:
        sec_syms = [(n, a, sz) for n, s, a, sz in syms if s == section]
        sec_syms.sort(key=lambda x: x[1])
        
        # Get existing claims
        all_claims = []
        for fname, secs in splits.items():
            for s, e in secs.get(section, []):
                all_claims.append((s, e, fname))
        all_claims.sort()
        
        # Find unclaimed symbols
        unclaimed = []
        for name, addr, size in sec_syms:
            is_claimed = any(s <= addr < e for s, e, _ in all_claims)
            if not is_claimed:
                unclaimed.append((name, addr, size))
        
        if not unclaimed:
            continue
        
        # Walk files in link order, matching to unclaimed symbol ranges
        sym_idx = 0
        for fname in game_files:
            if section in splits.get(fname, {}):
                continue  # already claimed
            
            compiled_size = get_compiled_section_size(fname, section)
            if compiled_size is None or compiled_size == 0:
                continue
            
            result = find_matching_range(unclaimed, compiled_size, sym_idx)
            if result:
                start_idx, end_idx, range_start, range_end = result
                if fname not in new_claims:
                    new_claims[fname] = {}
                new_claims[fname][section] = (range_start, range_end)
                sym_idx = end_idx
    
    # Now apply new claims to splits.txt
    if not new_claims:
        print("No new claims found!")
        return
    
    total_bytes = 0
    total_claims = 0
    for fname, secs in sorted(new_claims.items()):
        for sec, (s, e) in sorted(secs.items()):
            total_bytes += e - s
            total_claims += 1
    
    print(f"Found {total_claims} new section claims totaling {total_bytes} bytes across {len(new_claims)} files")
    
    # Read and modify splits.txt
    with open(SPLITS) as f:
        lines = f.readlines()
    
    # Build a map of file -> line index of last section entry
    file_ranges = {}
    current_file = None
    current_start = None
    for i, line in enumerate(lines):
        stripped = line.rstrip('\n')
        if stripped and not stripped[0].isspace() and stripped.endswith(':') and not stripped.startswith('Sections'):
            if current_file and current_start is not None:
                file_ranges[current_file] = (current_start, i - 1)
            current_file = stripped.rstrip(':')
            current_start = i
    if current_file and current_start is not None:
        file_ranges[current_file] = (current_start, len(lines) - 1)
    
    # Section order for insertion
    section_order = ['.init', 'extab', 'extabindex', '.text', '.ctors', '.dtors', 
                     '.rodata', '.data', '.bss', '.sdata', '.sbss', '.sdata2', '.sbss2']
    
    # For each file with new claims, insert lines at the right position
    insertions = []  # (line_number, text)
    
    for fname, secs in new_claims.items():
        if fname not in file_ranges:
            continue
        
        start_line, end_line = file_ranges[fname]
        
        # Find existing sections and their line numbers
        existing_secs = {}
        for i in range(start_line + 1, end_line + 1):
            if i < len(lines):
                m = re.match(r'\s+(\.\w+|extab\w*)\s+', lines[i])
                if m:
                    existing_secs[m.group(1)] = i
        
        for sec, (s, e) in secs.items():
            new_line = f"\t{sec:12s}start:0x{s:08X} end:0x{e:08X}\n"
            
            # Find where to insert (after the last existing section that comes before this one in order)
            insert_after = start_line  # default: after file header
            
            sec_idx = section_order.index(sec) if sec in section_order else len(section_order)
            for existing_sec, line_num in existing_secs.items():
                existing_idx = section_order.index(existing_sec) if existing_sec in section_order else len(section_order)
                if existing_idx < sec_idx:
                    insert_after = max(insert_after, line_num)
            
            insertions.append((insert_after + 1, new_line, fname, sec, s, e))
    
    # Sort insertions by line number (reverse to preserve line numbers)
    insertions.sort(key=lambda x: x[0], reverse=True)
    
    for line_num, text, fname, sec, s, e in insertions:
        lines.insert(line_num, text)
        print(f"  Added {fname} {sec} start:0x{s:08X} end:0x{e:08X} ({e-s} bytes)")
    
    with open(SPLITS, 'w') as f:
        f.writelines(lines)
    
    print(f"\nDone! Added {total_claims} claims ({total_bytes} bytes) to splits.txt")

if __name__ == '__main__':
    main()
