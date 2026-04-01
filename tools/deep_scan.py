#!/usr/bin/env python3
"""
Find data matching opportunities by comparing compiled src .o against original obj .o.
"""
import subprocess
import os
import re

REPO = "/Users/zcanann/Documents/GitHub/FFCC-Decomp"
SRC_DIR = os.path.join(REPO, "build/GCCP01/src")
OBJ_DIR = os.path.join(REPO, "build/GCCP01/obj")
OBJDUMP = os.path.join(REPO, "build/binutils/powerpc-eabi-objdump")
SPLITS = os.path.join(REPO, "config/GCCP01/splits.txt")

DATA_SECTIONS = ['.data', '.rodata', '.bss', '.sbss', '.sdata', '.sdata2']

def run(cmd):
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=10)
    return r.stdout

def get_sections(obj_path):
    out = run([OBJDUMP, '-h', obj_path])
    sections = {}
    for line in out.split('\n'):
        line = line.strip()
        if not line or not line[0].isdigit():
            continue
        parts = line.split()
        if len(parts) >= 3:
            sections[parts[1]] = int(parts[2], 16)
    return sections

def get_section_hex(obj_path, section):
    out = run([OBJDUMP, '-s', '-j', section, obj_path])
    hex_str = ''
    in_contents = False
    for line in out.split('\n'):
        if 'Contents of section' in line:
            in_contents = True
            continue
        if not in_contents:
            continue
        line = line.strip()
        if not line:
            continue
        parts = line.split()
        if not parts:
            continue
        for p in parts[1:]:
            if all(c in '0123456789abcdef' for c in p) and 2 <= len(p) <= 8:
                hex_str += p
            else:
                break
    return hex_str

def parse_splits():
    claimed = {}
    current_file = None
    with open(SPLITS) as f:
        for line in f:
            line = line.rstrip('\n')
            if line and not line[0].isspace() and line.endswith(':') and not line.startswith('Sections'):
                current_file = line.rstrip(':')
                claimed.setdefault(current_file, set())
            elif current_file and line.strip():
                stripped = line.strip()
                for sec in DATA_SECTIONS:
                    if stripped.startswith(sec) and 'start:' in stripped:
                        claimed[current_file].add(sec)
    return claimed

def main():
    claimed = parse_splits()
    src_files = sorted(f for f in os.listdir(SRC_DIR) if f.endswith('.o') and not f.startswith('auto_'))
    obj_set = set(os.listdir(OBJ_DIR))

    free_gains = []
    bss_matches = []
    content_close = []
    size_diff = []
    obj_only = []
    src_only = []

    for fname in src_files:
        if fname not in obj_set:
            continue
        src_path = os.path.join(SRC_DIR, fname)
        obj_path = os.path.join(OBJ_DIR, fname)
        base = fname[:-2]
        splits_name = None
        for ext in ['.cpp', '.c']:
            if base + ext in claimed:
                splits_name = base + ext
                break

        try:
            src_secs = get_sections(src_path)
            obj_secs = get_sections(obj_path)
        except:
            continue

        for sec in DATA_SECTIONS:
            obj_size = obj_secs.get(sec, 0)
            src_size = src_secs.get(sec, 0)
            if obj_size == 0 and src_size == 0:
                continue
            is_claimed = splits_name and sec in claimed.get(splits_name, set())
            if is_claimed:
                continue
            entry = {'file': fname, 'section': sec, 'obj_size': obj_size, 'src_size': src_size}

            if obj_size > 0 and src_size == 0:
                obj_only.append(entry)
            elif obj_size == 0 and src_size > 0:
                src_only.append(entry)
            elif sec in ['.bss', '.sbss']:
                if obj_size == src_size:
                    bss_matches.append(entry)
                else:
                    size_diff.append(entry)
            elif obj_size != src_size:
                size_diff.append(entry)
            else:
                try:
                    oh = get_section_hex(obj_path, sec)
                    sh = get_section_hex(src_path, sec)
                    if oh == sh:
                        free_gains.append(entry)
                    else:
                        ml = min(len(oh), len(sh))
                        if ml > 0:
                            match = sum(1 for i in range(0, ml, 2) if oh[i:i+2] == sh[i:i+2])
                            entry['match_pct'] = match / (ml // 2) * 100
                        content_close.append(entry)
                except:
                    pass

    print("=" * 80)
    print("FREE DATA GAINS: Content matches, just need splits.txt entry")
    print("=" * 80)
    free_gains.sort(key=lambda x: -x['obj_size'])
    for e in free_gains:
        print(f"  {e['file']:<40} {e['section']:<10} {e['obj_size']:>6} bytes")
    print(f"  TOTAL: {sum(e['obj_size'] for e in free_gains)} bytes\n")

    print("=" * 80)
    print("BSS/SBSS MATCHES: Same size, just need splits.txt entry")
    print("=" * 80)
    bss_matches.sort(key=lambda x: -x['obj_size'])
    for e in bss_matches:
        print(f"  {e['file']:<40} {e['section']:<10} {e['obj_size']:>6} bytes")
    print(f"  TOTAL: {sum(e['obj_size'] for e in bss_matches)} bytes\n")

    print("=" * 80)
    print("CONTENT CLOSE (same size, slightly different content)")
    print("=" * 80)
    content_close.sort(key=lambda x: -x.get('match_pct', 0))
    for e in content_close[:30]:
        print(f"  {e['file']:<40} {e['section']:<10} {e['obj_size']:>6} bytes  {e.get('match_pct',0):.1f}% match")

    print(f"\n{'='*80}")
    print("SIZE MISMATCHES (both have section, different sizes)")
    print("=" * 80)
    size_diff.sort(key=lambda x: -x['obj_size'])
    for e in size_diff[:30]:
        print(f"  {e['file']:<40} {e['section']:<10} obj:{e['obj_size']:>6}  src:{e['src_size']:>6}")

    print(f"\n{'='*80}")
    print("ORIGINAL ONLY (original has section we don't generate)")
    print("=" * 80)
    obj_only.sort(key=lambda x: -x['obj_size'])
    for e in obj_only[:30]:
        print(f"  {e['file']:<40} {e['section']:<10} {e['obj_size']:>6} bytes")
    total_obj_only = sum(e['obj_size'] for e in obj_only)
    print(f"  ... ({len(obj_only)} entries) TOTAL: {total_obj_only} bytes")

    print(f"\n{'='*80}")
    print("WE GENERATE BUT ORIGINAL DOESN'T (junk in our source)")
    print("=" * 80)
    src_only.sort(key=lambda x: -x['src_size'])
    for e in src_only[:30]:
        print(f"  {e['file']:<40} {e['section']:<10} {e['src_size']:>6} bytes")
    total_src_only = sum(e['src_size'] for e in src_only)
    print(f"  ... ({len(src_only)} entries) TOTAL: {total_src_only} bytes unwanted")

if __name__ == '__main__':
    main()
