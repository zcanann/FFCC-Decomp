#!/usr/bin/env python3
"""Show side-by-side assembly diff for a specific __sinit function."""
import json, subprocess, sys

if len(sys.argv) < 2:
    print("Usage: python3 tools/asm_sinit.py <unit_name> [symbol]")
    sys.exit(1)

unit = sys.argv[1]
symbol = sys.argv[2] if len(sys.argv) > 2 else f'__sinit_{unit}_cpp'

result = subprocess.run(
    ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', f'main/{unit}', '-o', '-', symbol],
    capture_output=True, text=True, timeout=10
)
if result.returncode != 0:
    print(f'Error: {result.stderr.strip()}')
    sys.exit(1)

data = json.loads(result.stdout)

left_insns = []
right_insns = []
for sym in data.get('left', {}).get('symbols', []):
    if sym.get('name') == symbol:
        left_insns = sym.get('instructions', [])
        print(f'Original: {sym.get("match_percent", 0):.1f}% match, {sym.get("size", 0)}b')
        break
for sym in data.get('right', {}).get('symbols', []):
    if sym.get('name') == symbol:
        right_insns = sym.get('instructions', [])
        break

def fmt(insn):
    mn = insn.get('mnemonic', '')
    args = []
    for a in insn.get('arguments', []):
        t = a.get('text', '')
        args.append(t)
    return f'{mn:10s} {", ".join(args)}'

max_len = max(len(left_insns), len(right_insns))
print(f'\n{"ORIGINAL":<50s}  {"CURRENT":<50s}  DIFF')
print('-' * 120)
for i in range(max_len):
    l = fmt(left_insns[i]) if i < len(left_insns) else '<missing>'
    r = fmt(right_insns[i]) if i < len(right_insns) else '<missing>'
    dk = ''
    if i < len(left_insns):
        dk = left_insns[i].get('diff_kind', '')
    elif i < len(right_insns):
        dk = 'EXTRA'
    marker = '  ' if dk == 'NONE' else '* '
    print(f'{marker}{l:<50s}  {r:<50s}  {dk}')
