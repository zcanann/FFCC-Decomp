#!/usr/bin/env python3
"""
Apply section claims incrementally - BSS (safe) and .sdata2 in batches.
Test each batch to find which ones cause build issues.
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

def add_claim_to_lines(lines, fname, section, start_addr, end_addr):
    """Add a section claim to the file's entry in splits.txt"""
    section_order = ['.init', 'extab', 'extabindex', '.text', '.ctors', '.dtors', 
                     '.rodata', '.data', '.bss', '.sdata', '.sbss', '.sdata2', '.sbss2']
    
    # Find the file's entry
    file_start = None
    for i, line in enumerate(lines):
        stripped = line.rstrip('\n')
        if stripped == f"{fname}:":
            file_start = i
            break
    
    if file_start is None:
        return False
    
    # Find last section line for this file
    insert_after = file_start
    sec_idx = section_order.index(section) if section in section_order else len(section_order)
    
    for i in range(file_start + 1, len(lines)):
        stripped = lines[i].rstrip('\n')
        if stripped and not stripped[0].isspace():
            break  # next file entry
        m = re.match(r'\s+(\.\w+|extab\w*)\s+', stripped)
        if m:
            existing_sec = m.group(1)
            existing_idx = section_order.index(existing_sec) if existing_sec in section_order else len(section_order)
            if existing_idx < sec_idx:
                insert_after = i
    
    new_line = f"\t{section:12s}start:0x{start_addr:08X} end:0x{end_addr:08X}\n"
    lines.insert(insert_after + 1, new_line)
    return True

def main():
    import sys
    mode = sys.argv[1] if len(sys.argv) > 1 else 'bss_only'
    
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
    
    with open(SPLITS) as f:
        lines = f.readlines()
    
    claims_added = 0
    bytes_added = 0
    
    # Always add BSS claims (guaranteed safe)
    bss_ranges = {
        'file.cpp': (0x8021ED40, 0x8021EEB0),
        'pad.cpp': (0x80244140, 0x8024430C),
        'usb.cpp': (0x802455C0, 0x80245640),
    }
    for fname, (s, e) in bss_ranges.items():
        compiled = get_compiled_section_size(fname, '.bss')
        if compiled == e - s:
            if add_claim_to_lines(lines, fname, '.bss', s, e):
                print(f"  BSS: {fname} 0x{s:08X}-0x{e:08X} ({e-s} bytes)")
                claims_added += 1
                bytes_added += e - s
    
    # Add .sdata2 claims if requested
    if mode in ['sdata2', 'all']:
        sec_syms = [(n, a, sz) for n, s, a, sz in syms if s == '.sdata2']
        sec_syms.sort(key=lambda x: x[1])
        
        # Re-parse splits after BSS additions
        all_claims_s2 = []
        # Check existing claims from the original file
        for fname2, secs in splits.items():
            for s, e in secs.get('.sdata2', []):
                all_claims_s2.append((s, e, fname2))
        all_claims_s2.sort()
        
        unclaimed = []
        for name, addr, size in sec_syms:
            is_claimed = any(s <= addr < e for s, e, _ in all_claims_s2)
            if not is_claimed:
                unclaimed.append((name, addr, size))
        
        # Only claim .sdata2 for a subset of files to avoid cycles
        # Strategy: claim from the beginning of the .sdata2 section
        # Stop at the first gap where a problematic auto block might form
        safe_files = set()
        if mode == 'sdata2':
            # Only early files (before the ppp files that already have claims)
            safe_files = {
                'file.cpp', 'game.cpp', 'graphic.cpp', 'main.cpp', 'math.cpp',
                'memory.cpp', 'pad.cpp', 'system.cpp', 'util.cpp',
                'maphit.cpp', 'mapmesh.cpp', 'mapobj.cpp', 'mapocttree.cpp',
                'map.cpp', 'p_camera.cpp', 'textureman.cpp', 'materialman.cpp',
                'texanim.cpp', 'p_graphic.cpp', 'p_light.cpp', 'mapanim.cpp',
                'p_MaterialEditor.cpp', 'mapshadow.cpp', 'maptexanim.cpp',
                'FunnyShape.cpp', 'p_tina.cpp', 'pppPart.cpp', 'partMng.cpp',
                # ppp files that follow the existing claimed ppp files
                'pppGetRotMatrixX.cpp', 'pppGetRotMatrixY.cpp', 'pppGetRotMatrixZ.cpp',
                'pppColor.cpp', 'pppPoint.cpp',
                'pppVertexAp.cpp', 'pppVertexApAt.cpp', 'pppVertexApLc.cpp',
                'pppShape.cpp',
                # Later files after ppp claims
                'cflat_runtime2.cpp', 'chara.cpp', 'p_chara.cpp',
                'gobject.cpp',
                'pppRyjMegaBirth.cpp', 'pppRyjMegaBirthModel.cpp',
                'pppDrawMdlTs.cpp', 'pppKeZCrctShp.cpp',
                'pppKeShpTail2X.cpp', 'pppKeShpTail3X.cpp',
                'pppYmMegaBirthShpTail2.cpp', 'pppYmMegaBirthShpTail3.cpp',
                'pppYmDeformationShp.cpp', 'pppParMoveLine.cpp',
                'pppYmMiasma.cpp', 'pppYmDeformationScreen.cpp',
                'fontman.cpp', 'pppYmTracer.cpp',
                'p_menu.cpp', 'p_gba.cpp',
                'mes.cpp', 'mesmenu.cpp', 'gobjwork.cpp', 'ringmenu.cpp',
            }
        else:
            safe_files = set(game_files)
        
        sym_idx = 0
        for fname in game_files:
            if fname not in safe_files:
                continue
            if '.sdata2' in splits.get(fname, {}):
                continue
            compiled_size = get_compiled_section_size(fname, '.sdata2')
            if compiled_size is None or compiled_size == 0:
                continue
            result = find_matching_range(unclaimed, compiled_size, sym_idx)
            if result:
                start_idx, end_idx, range_start, range_end = result
                if add_claim_to_lines(lines, fname, '.sdata2', range_start, range_end):
                    print(f"  SDATA2: {fname} 0x{range_start:08X}-0x{range_end:08X} ({range_end-range_start} bytes)")
                    claims_added += 1
                    bytes_added += range_end - range_start
                sym_idx = end_idx
    
    with open(SPLITS, 'w') as f:
        f.writelines(lines)
    
    print(f"\nTotal: {claims_added} claims, {bytes_added} bytes")

if __name__ == '__main__':
    main()
