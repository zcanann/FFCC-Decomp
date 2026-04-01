#!/usr/bin/env python3
"""Check match percentages for all __sinit functions."""
import json, subprocess, re

with open('config/GCCP01/symbols.txt') as f:
    syms = f.read()

sinits = re.findall(
    r'(__sinit_(\w+)_cpp)\s*=\s*\.text:(0x[0-9A-Fa-f]+);\s*//\s*type:function\s*size:(0x[0-9A-Fa-f]+)',
    syms
)

for name, unit, addr, size in sinits:
    try:
        result = subprocess.run(
            ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', f'main/{unit}', '-o', '-', name],
            capture_output=True, text=True, timeout=10
        )
        if result.returncode == 0:
            data = json.loads(result.stdout)
            # Look for the symbol in left side
            match_pct = 0
            right_found = False
            for sym in data.get('left', {}).get('symbols', []):
                if sym.get('name') == name:
                    match_pct = sym.get('match_percent', 0)
                    break
            for sym in data.get('right', {}).get('symbols', []):
                if sym.get('name') == name:
                    right_found = True
                    break
            status = "GEN" if right_found else "MISS"
            print(f'{match_pct:6.1f}%  [{status:4s}]  {name:45s} size={int(size,16):5d}b')
        else:
            print(f'  ERR          {name:45s} size={int(size,16):5d}b  {result.stderr[:80].strip()}')
    except Exception as e:
        print(f'  EXC          {name:45s} size={int(size,16):5d}b  {str(e)[:80]}')
