#!/usr/bin/env python3
"""
Safely add .sdata2 claims by filling gaps between existing claims.
The key is to NOT create new auto blocks with relocations.

Strategy: 
1. Find the gaps between existing .sdata2 claims
2. For each gap, check if all files in link order between the boundary files 
   have matching .sdata2 sizes that fill the gap exactly
3. Only claim if we can fill the ENTIRE gap (so no new auto blocks are created)
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
    files = {}
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
    for start_idx in range(start_from, len(unclaimed)):
        running_total = 0
        for end_idx in range(start_idx, len(unclaimed)):
            running_total += unclaimed[end_idx][2]
            if running_total == compiled_size:
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
    
    sdk_prefixes = ['Runtime.', 'MSL_C/', 'TRK_', 'OdemuExi2/', 'amcstubs/', 'odenotstub/', 
                    'RedSound/', 'thp/', 'dolphin/', 'base/', 'db/', 'os/', 'exi/', 'si/', 
                    'mtx/', 'dvd/', 'vi/', 'pad/', 'ai/', 'ar/', 'ax/', 'axfx/', 'mix/', 
                    'axart/', 'dsp/', 'card/', 'gx/', 'gba/']
    
    game_files = []
    for f in file_order:
        if any(f.startswith(p) for p in sdk_prefixes):
            continue
        if '.text' in splits.get(f, {}):
            starts = [s for s, e in splits[f]['.text']]
            if starts:
                game_files.append((min(starts), f))
    game_files.sort()
    game_files = [f for _, f in game_files]
    
    # Get all .sdata2 symbols
    sec_syms = [(n, a, sz) for n, s, a, sz in syms if s == '.sdata2']
    sec_syms.sort(key=lambda x: x[1])
    
    # Get existing .sdata2 claims sorted
    all_claims = []
    for fname, secs in splits.items():
        for s, e in secs.get('.sdata2', []):
            all_claims.append((s, e, fname))
    all_claims.sort()
    
    # Find gaps between claims  
    # First, find the overall .sdata2 range
    sdata2_start = sec_syms[0][1]
    sdata2_end = sec_syms[-1][1] + sec_syms[-1][2]
    
    print(f"Overall .sdata2: 0x{sdata2_start:08X}-0x{sdata2_end:08X} ({sdata2_end-sdata2_start} bytes)")
    print(f"Existing claims: {len(all_claims)}")
    
    # Find gaps
    gaps = []
    prev_end = sdata2_start
    for s, e, fname in all_claims:
        if s > prev_end:
            gaps.append((prev_end, s))
        prev_end = max(prev_end, e)
    if prev_end < sdata2_end:
        gaps.append((prev_end, sdata2_end))
    
    print(f"\nGaps in .sdata2 claims:")
    for gs, ge in gaps:
        gap_size = ge - gs
        print(f"  0x{gs:08X}-0x{ge:08X} ({gap_size} bytes)")
    
    # For each gap, try to fill it completely with file claims
    # Get unclaimed symbols
    unclaimed = []
    for name, addr, size in sec_syms:
        is_claimed = any(s <= addr < e for s, e, _ in all_claims)
        if not is_claimed:
            unclaimed.append((name, addr, size))
    
    # Try to fill each gap
    print(f"\nAttempting to fill gaps:")
    fillable_claims = []
    
    for gap_start, gap_end in gaps:
        gap_size = gap_end - gap_start
        
        # Get unclaimed symbols in this gap
        gap_syms = [(n, a, sz) for n, a, sz in unclaimed if gap_start <= a < gap_end]
        gap_sym_total = sum(sz for _, _, sz in gap_syms)
        
        # Try to match files in link order to this gap's symbols
        sym_idx = 0
        gap_claims = []
        
        for fname in game_files:
            if '.sdata2' in splits.get(fname, {}):
                continue
            compiled_size = get_compiled_section_size(fname, '.sdata2')
            if compiled_size is None or compiled_size == 0:
                continue
            
            result = find_matching_range(gap_syms, compiled_size, sym_idx)
            if result:
                start_idx, end_idx, range_start, range_end = result
                if range_start >= gap_start and range_end <= gap_end:
                    gap_claims.append((fname, range_start, range_end))
                    sym_idx = end_idx
        
        # Check if we filled the entire gap
        filled = sum(e - s for _, s, e in gap_claims)
        
        if filled == gap_sym_total and gap_sym_total == gap_size:
            print(f"  Gap 0x{gap_start:08X}-0x{gap_end:08X}: COMPLETELY FILLED ({filled} bytes, {len(gap_claims)} files)")
            fillable_claims.extend(gap_claims)
        elif gap_claims:
            print(f"  Gap 0x{gap_start:08X}-0x{gap_end:08X}: PARTIALLY filled {filled}/{gap_size} bytes ({len(gap_claims)} files)")
            # Even partial is OK if we claim contiguously from the start
            # Check if claims are contiguous from gap_start
            contiguous_end = gap_start
            contiguous_claims = []
            for fname, s, e in gap_claims:
                if s == contiguous_end:
                    contiguous_claims.append((fname, s, e))
                    contiguous_end = e
                else:
                    break
            
            if contiguous_claims:
                filled_contiguous = sum(e - s for _, s, e in contiguous_claims)
                print(f"    Contiguous from start: {filled_contiguous} bytes, {len(contiguous_claims)} files")
                # Only add if they extend to an already-claimed boundary
                # This avoids creating auto blocks
                # Actually let's just output and let the user decide
                for fname, s, e in contiguous_claims:
                    print(f"      {fname}: 0x{s:08X}-0x{e:08X} ({e-s} bytes)")
                fillable_claims.extend(contiguous_claims)
        else:
            print(f"  Gap 0x{gap_start:08X}-0x{gap_end:08X}: NO MATCHES ({gap_size} bytes)")
    
    print(f"\n=== FILLABLE CLAIMS ===")
    total = 0
    for fname, s, e in fillable_claims:
        print(f"  {fname}: 0x{s:08X}-0x{e:08X} ({e-s} bytes)")
        total += e - s
    print(f"Total: {total} bytes across {len(fillable_claims)} files")

if __name__ == '__main__':
    main()
