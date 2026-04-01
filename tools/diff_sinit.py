#!/usr/bin/env python3
"""Show detailed instruction diff for __sinit functions that aren't at 100%."""
import json, subprocess, re, sys

with open('config/GCCP01/symbols.txt') as f:
    syms = f.read()

sinits = re.findall(
    r'(__sinit_(\w+)_cpp)\s*=\s*\.text:(0x[0-9A-Fa-f]+);\s*//\s*type:function\s*size:(0x[0-9A-Fa-f]+)',
    syms
)

targets = sys.argv[1:] if len(sys.argv) > 1 else None

for name, unit, addr, size in sinits:
    if targets and unit not in targets:
        continue
    try:
        result = subprocess.run(
            ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', f'main/{unit}', '-o', '-', name],
            capture_output=True, text=True, timeout=10
        )
        if result.returncode != 0:
            continue
        data = json.loads(result.stdout)
        
        match_pct = 0
        left_insns = []
        right_insns = []
        for sym in data.get('left', {}).get('symbols', []):
            if sym.get('name') == name:
                match_pct = sym.get('match_percent', 0)
                left_insns = sym.get('instructions', [])
                break
        for sym in data.get('right', {}).get('symbols', []):
            if sym.get('name') == name:
                right_insns = sym.get('instructions', [])
                break
        
        if match_pct >= 99.0 and not targets:
            continue
            
        print(f'\n{"="*80}')
        print(f'{match_pct:.1f}%  {name}  ({int(size,16)}b)')
        print(f'{"="*80}')
        
        def fmt_insn(i):
            mn = i.get('mnemonic', '')
            args = []
            for a in i.get('arguments', []):
                args.append(a.get('text', ''))
            diff = i.get('diff_kind', '')
            return f'{mn:10s} {", ".join(args):40s} [{diff}]'
        
        max_len = max(len(left_insns), len(right_insns))
        print(f'  {"ORIGINAL":55s} CURRENT')
        for idx in range(max_len):
            l = fmt_insn(left_insns[idx]) if idx < len(left_insns) else ''
            r = fmt_insn(right_insns[idx]) if idx < len(right_insns) else ''
            marker = ' ' if idx < len(left_insns) and idx < len(right_insns) and left_insns[idx].get('diff_kind') == 'NONE' else '*'
            print(f'{marker} {l:55s} {r}')
            
    except Exception as e:
        print(f'  ERROR: {name} - {e}')
