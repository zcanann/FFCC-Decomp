#!/usr/bin/env python3
"""
Compare compiled .o section sizes against original DOL ranges.
For each source file in splits.txt that already claims data sections,
check if our compiled sizes match.

Also identify unclaimed sections that COULD be claimed based on compiled sizes.
"""
import re
import os
import subprocess
from collections import defaultdict

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SYMBOLS = os.path.join(REPO, "config/GCCP01/symbols.txt")
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")
OBJDUMP = os.path.join(REPO, "build/binutils/powerpc-eabi-objdump")

def get_compiled_sections(obj_path):
    """Get sections from compiled .o file"""
    try:
        r = subprocess.run([OBJDUMP, '-h', obj_path], capture_output=True, text=True)
        secs = {}
        for line in r.stdout.split('\n'):
            parts = line.split()
            if len(parts) >= 3:
                for sec_name in ['.bss', '.data', '.rodata', '.sdata', '.sdata2', '.sbss', '.sbss2']:
                    if parts[1] == sec_name:
                        size = int(parts[2], 16)
                        secs[sec_name] = size
                        break
        return secs
    except:
        return {}

def parse_splits():
    """Parse splits.txt for file entries and their claimed section ranges"""
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

def parse_symbols_by_section():
    """Parse symbols.txt and group by section"""
    syms = defaultdict(list)
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
                syms[section].append((name, addr, size))
    for sec in syms:
        syms[sec].sort(key=lambda x: x[1])
    return syms

def get_known_bss_ranges():
    """Return known BSS ownership based on symbol names"""
    return {
        'file.cpp': (0x8021ED40, 0x8021EEB0),
        'game.cpp': (0x8021EEB0, 0x80230E48),
        'graphic.cpp': (0x80230E48, 0x802381C0),
        'main.cpp': (0x802381C0, 0x8023C4D8),
        'math.cpp': (0x8023C4D8, 0x8023C888),
        'memory.cpp': (0x8023C888, 0x80244028),
        'pad.cpp': (0x80244140, 0x8024430C),
        'system.cpp': (0x80244340, 0x802455C0),
        'usb.cpp': (0x802455C0, 0x80245640),
        'map.cpp': (0x80245764, 0x802681E0),
        'p_map.cpp': (0x802685E0, 0x80268790),
        'p_graphic.cpp': (0x80268E90, 0x80268F88),
        'partMng.cpp': (0x80275EE8, 0x80299EC0),
        'chara.cpp': (0x802E78E0, 0x802E9958),
        'p_chara.cpp': (0x802E9964, 0x802EA080),
        'p_menu.cpp': (0x802EA1C0, 0x802EAA60),
        'memorycard.cpp': (0x802F2628, 0x802F26C8),
        'sound.cpp': (0x802F26D4, 0x802F49B0),
    }

def main():
    splits = parse_splits()
    syms = parse_symbols_by_section()
    bss_ranges = get_known_bss_ranges()
    
    # Game source files
    game_files = [f for f in splits.keys() if not any(f.startswith(p) for p in 
        ['Runtime.', 'MSL_C/', 'TRK_', 'OdemuExi2/', 'amcstubs/', 'odenotstub/', 'RedSound/', 'thp/', 
         'dolphin/', 'base/', 'db/', 'os/', 'exi/', 'si/', 'mtx/', 'dvd/', 'vi/', 'pad/', 'ai/', 
         'ar/', 'ax/', 'axfx/', 'mix/', 'axart/', 'dsp/', 'card/', 'gx/', 'gba/'])]
    
    data_sections = ['.bss', '.data', '.rodata', '.sdata', '.sdata2', '.sbss']
    
    exact_matches = []
    close_matches = []
    size_mismatches = []
    unclaimed_matching = []
    
    for fname in game_files:
        obj_path = os.path.join(REPO, f"build/GCCP01/src/{fname.replace('.cpp', '.o').replace('.c', '.o')}")
        if not os.path.exists(obj_path):
            continue
        
        compiled = get_compiled_sections(obj_path)
        claimed = splits[fname]
        
        for sec in data_sections:
            compiled_size = compiled.get(sec, 0)
            if compiled_size == 0:
                continue
            
            # Check if this section is already claimed
            if sec in claimed:
                claimed_size = sum(e - s for s, e in claimed[sec])
                if compiled_size == claimed_size:
                    exact_matches.append((fname, sec, compiled_size, claimed_size, "ALREADY CLAIMED + MATCH"))
                else:
                    size_mismatches.append((fname, sec, compiled_size, claimed_size, "ALREADY CLAIMED + MISMATCH"))
            elif sec == '.bss' and fname in bss_ranges:
                original_size = bss_ranges[fname][1] - bss_ranges[fname][0]
                if compiled_size == original_size:
                    unclaimed_matching.append((fname, sec, compiled_size, original_size, 
                        f"UNCLAIMED EXACT: claim 0x{bss_ranges[fname][0]:08X}-0x{bss_ranges[fname][1]:08X}"))
                else:
                    diff = compiled_size - original_size
                    status = f"UNCLAIMED OFF BY {diff:+d}"
                    if abs(diff) <= compiled_size * 0.02:  # within 2%
                        close_matches.append((fname, sec, compiled_size, original_size, status))
                    else:
                        size_mismatches.append((fname, sec, compiled_size, original_size, status))
            else:
                # Section exists in compiled but not claimed in splits
                # For non-BSS sections, we need to find the original range from symbols
                pass
    
    print("=" * 100)
    print("EXACT MATCHES (free wins!)")
    print("=" * 100)
    for fname, sec, compiled, original, status in exact_matches + unclaimed_matching:
        print(f"  {fname:30s} {sec:10s} compiled={compiled:>6} original={original:>6} {status}")
    
    print(f"\n{'=' * 100}")
    print("CLOSE MATCHES (within 2%)")
    print("=" * 100)
    for fname, sec, compiled, original, status in close_matches:
        print(f"  {fname:30s} {sec:10s} compiled={compiled:>6} original={original:>6} {status}")
    
    print(f"\n{'=' * 100}")
    print("SIZE MISMATCHES")
    print("=" * 100)
    for fname, sec, compiled, original, status in size_mismatches:
        diff = compiled - original
        print(f"  {fname:30s} {sec:10s} compiled={compiled:>6} original={original:>6} diff={diff:+6d} {status}")
    
    # Now also check all compiled .o files for ALL their data sections
    print(f"\n{'=' * 100}")
    print("ALL COMPILED DATA SECTIONS (game files)")
    print("=" * 100)
    for fname in game_files:
        obj_path = os.path.join(REPO, f"build/GCCP01/src/{fname.replace('.cpp', '.o').replace('.c', '.o')}")
        if not os.path.exists(obj_path):
            continue
        compiled = get_compiled_sections(obj_path)
        if any(compiled.get(s, 0) > 0 for s in data_sections):
            claimed = splits[fname]
            lines = []
            for sec in data_sections:
                c = compiled.get(sec, 0)
                if c > 0:
                    is_claimed = sec in claimed
                    marker = "CLAIMED" if is_claimed else "UNCLAIMED"
                    lines.append(f"    {sec:10s} {c:>8} bytes [{marker}]")
            if lines:
                print(f"  {fname}:")
                for l in lines:
                    print(l)

if __name__ == '__main__':
    main()
