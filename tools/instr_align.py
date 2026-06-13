#!/usr/bin/env python3
"""Print real instruction alignment for a unit's functions from objdiff JSON.

matched = rows with no diff_kind (exact-aligned, same bytes)
argmm   = DIFF_ARG_MISMATCH (aligned instruction, only reloc-label/arg differs — cosmetic)
misalign= DIFF_INSERT + DIFF_DELETE + DIFF_REPLACE (REAL structural misalignment)

A pragma/source change is a PURE win only if it does not raise `misalign` (ideally
lowers it / raises `matched`). Fuzzy% rising while misalign rises = byte-score noise.

Usage: python3 tools/instr_align.py <unit> [name_substr]
"""
import json, subprocess, sys

UNIT = sys.argv[1]
SUB = sys.argv[2] if len(sys.argv) > 2 else ''
r = subprocess.run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/' + UNIT,
                    '--format', 'json', '-o', '-'], capture_output=True, text=True)
d = json.loads(r.stdout)
rows = []
for s in d['left']['symbols']:
    if 'instructions' not in s:
        continue
    n = s.get('name', '')
    if SUB and SUB not in n:
        continue
    matched = argmm = mis = 0
    for row in s['instructions']:
        k = row.get('diff_kind')
        if k is None or k == 'DIFF_NONE':
            matched += 1
        elif k == 'DIFF_ARG_MISMATCH':
            argmm += 1
        else:
            mis += 1
    rows.append((mis, argmm, matched, s.get('match_percent', 0), n.split('__')[0], n))
rows.sort(key=lambda t: -t[0])
print(f"{'misalign':>8} {'argmm':>5} {'match':>5} {'fuzzy':>6}  function")
for mis, argmm, matched, fz, short, full in rows:
    print(f"{mis:>8} {argmm:>5} {matched:>5} {fz:>6.2f}  {short}")
print(f"TOTALS misalign={sum(r[0] for r in rows)} argmm={sum(r[1] for r in rows)} "
      f"matched={sum(r[2] for r in rows)}")
