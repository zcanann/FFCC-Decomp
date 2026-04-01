#!/usr/bin/env python3
"""
Map .sdata2 symbols to source files using link order.
.sdata2 contains small read-only data (float/double constants, short strings).
Like BSS, .sdata2 from each TU appears in link order.
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
    current = None
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':') and not line.startswith('Sections'):
                current = line.rstrip(':')
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
    return files

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

def main():
    syms = parse_symbols()
    splits = parse_splits()
    
    # Game source files in link order (from .text address)
    game_files = []
    for f, secs in splits.items():
        if any(f.startswith(p) for p in 
            ['Runtime.', 'MSL_C/', 'TRK_', 'OdemuExi2/', 'amcstubs/', 'odenotstub/', 'RedSound/', 'thp/', 
             'dolphin/', 'base/', 'db/', 'os/', 'exi/', 'si/', 'mtx/', 'dvd/', 'vi/', 'pad/', 'ai/', 
             'ar/', 'ax/', 'axfx/', 'mix/', 'axart/', 'dsp/', 'card/', 'gx/', 'gba/']):
            continue
        if '.text' in secs:
            starts = [s for s, e in secs['.text']]
            if starts:
                game_files.append((min(starts), f))
    game_files.sort()
    game_files = [f for _, f in game_files]
    
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
        
        total_unclaimed = sum(sz for _, _, sz in unclaimed)
        print(f"\n{'='*100}")
        print(f"SECTION: {section} - {len(unclaimed)} unclaimed symbols, {total_unclaimed} bytes")
        print(f"{'='*100}")
        
        # Map symbols to files by address proximity
        # Use link order: between file A and file B's claimed sections, 
        # unclaimed symbols belong to files between A and B in link order.
        
        # For each game file, check what .sdata2 our compiler actually emits
        proposed = []
        for i, fname in enumerate(game_files):
            compiled_size = get_compiled_section_size(fname, section)
            if compiled_size is None or compiled_size == 0:
                continue
            
            already_claimed = section in splits.get(fname, {})
            if already_claimed:
                continue
            
            # Find the range of unclaimed symbols that could belong to this file
            # Use the file's position in link order and neighboring files
            proposed.append((fname, compiled_size))
        
        # Now, attribute unclaimed address ranges to files
        # Strategy: walk the unclaimed symbols in address order
        # Assign them to files by matching the compiled section sizes
        
        print(f"\nFiles with unclaimed {section} (compiled sizes):")
        total_proposed = 0
        for fname, csize in proposed:
            print(f"  {fname:40s} compiled {section}: {csize:>6} bytes")
            total_proposed += csize
        print(f"  Total compiled: {total_proposed} bytes (original unclaimed: {total_unclaimed} bytes)")
        
        # Try to find contiguous blocks in the unclaimed symbols
        # that match each file's compiled size
        print(f"\nAttempting range attribution by link order + size matching...")
        
        # Walk unclaimed symbols and try to match them to files
        sym_idx = 0
        matched_ranges = []
        for fname, csize in proposed:
            # Find a contiguous block of unclaimed symbols that totals csize
            # Starting from where we are in the symbol list
            best_start = None
            best_end = None
            
            for start_idx in range(sym_idx, len(unclaimed)):
                running_total = 0
                for end_idx in range(start_idx, len(unclaimed)):
                    running_total += unclaimed[end_idx][2]
                    if running_total == csize:
                        # Exact match!
                        range_start = unclaimed[start_idx][1]
                        range_end = unclaimed[end_idx][1] + unclaimed[end_idx][2]
                        # Check contiguous
                        contiguous = True
                        for j in range(start_idx, end_idx):
                            expected = unclaimed[j][1] + unclaimed[j][2]
                            actual = unclaimed[j+1][1]
                            if expected != actual:
                                contiguous = False
                                break
                        if contiguous:
                            best_start = start_idx
                            best_end = end_idx + 1
                            break
                    elif running_total > csize:
                        break
                if best_start is not None:
                    break
            
            if best_start is not None:
                range_start = unclaimed[best_start][1]
                range_end = unclaimed[best_end - 1][1] + unclaimed[best_end - 1][2]
                matched_ranges.append((fname, range_start, range_end, csize))
                syms_in_range = unclaimed[best_start:best_end]
                print(f"  MATCH: {fname:40s} {section} start:0x{range_start:08X} end:0x{range_end:08X} ({csize} bytes)")
                for name, addr, size in syms_in_range[:5]:
                    print(f"    0x{addr:08X} [{size:>4}] {name}")
                if len(syms_in_range) > 5:
                    print(f"    ... +{len(syms_in_range)-5} more")
                sym_idx = best_end
            else:
                print(f"  NO MATCH: {fname:40s} compiled={csize}, no contiguous block found")
        
        if matched_ranges:
            total_matched = sum(sz for _, _, _, sz in matched_ranges)
            print(f"\n  Total matched: {total_matched} bytes across {len(matched_ranges)} files")

if __name__ == '__main__':
    main()
