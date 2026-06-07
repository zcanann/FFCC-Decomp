#!/usr/bin/env python3
import json, sys, subprocess, os

unit = sys.argv[1]
sym = sys.argv[2]
cli = "build/tools/objdiff-cli"
out = subprocess.check_output([cli, "diff", "-p", ".", "-u", unit, "-o", "-", sym], stderr=subprocess.DEVNULL)
d = json.loads(out)

def get(side):
    s = [x for x in d[side]['symbols'] if x['name'] == sym]
    return s[0] if s else None

L = get('left')   # target
R = get('right')  # ours

def rows(sym):
    if not sym: return []
    res = []
    for it in sym.get('instructions', []):
        ins = it.get('instruction')
        dk = it.get('diff_kind', '')
        if ins:
            res.append((ins.get('formatted',''), dk, ins.get('address')))
        else:
            res.append(('<gap>', dk, None))
    return res

lr = rows(L)
rr = rows(R)
print(f"TARGET match={L['match_percent'] if L else '?'}  OURS match={R['match_percent'] if R else '?'}")
n = max(len(lr), len(rr))
for i in range(n):
    lt = lr[i][0] if i < len(lr) else ''
    rt = rr[i][0] if i < len(rr) else ''
    lk = lr[i][1] if i < len(lr) else ''
    rk = rr[i][1] if i < len(rr) else ''
    mark = '   ' if lt == rt and lt else ' | '
    if lt != rt:
        mark = ' X '
    print(f"{lt:<40}{mark}{rt:<40}")
