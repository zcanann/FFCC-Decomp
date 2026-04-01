#!/usr/bin/env python3
"""Compare two sinit functions side by side."""
import json, subprocess, sys

units = sys.argv[1:]
for unit in units:
    symbol = f'__sinit_{unit}_cpp'
    result = subprocess.run(
        ['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', f'main/{unit}', '-o', '-', symbol],
        capture_output=True, text=True, timeout=10
    )
    if result.returncode != 0:
        print(f'Error for {unit}: {result.stderr.strip()}')
        continue
    data = json.loads(result.stdout)
    
    for side in ['left', 'right']:
        for sym in data.get(side, {}).get('symbols', []):
            if sym.get('name') == symbol:
                pct = sym.get('match_percent', 0)
                sz = sym.get('size', 0)
                print(f'\n=== {side} ({unit}): {pct:.1f}%, {sz}b ===')
                for i in sym.get('instructions', []):
                    fmt = i.get('instruction', {}).get('formatted', '')
                    dk = i.get('diff_kind', '')
                    print(f'  {dk:25s} {fmt}')
