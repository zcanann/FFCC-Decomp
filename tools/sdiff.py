#!/usr/bin/env python3
import json, sys, subprocess, difflib

unit = sys.argv[1]
sym = sys.argv[2]
cli = "build/tools/objdiff-cli"
out = subprocess.check_output([cli, "diff", "-p", ".", "-u", unit, "-o", "-", sym], stderr=subprocess.DEVNULL)
d = json.loads(out)

def get(side):
    s = [x for x in d[side]['symbols'] if x['name'] == sym]
    return s[0] if s else None

L = get('left'); R = get('right')

def rows(sym):
    if not sym: return []
    res = []
    for it in sym.get('instructions', []):
        ins = it.get('instruction')
        if ins:
            res.append(ins.get('formatted',''))
        else:
            res.append('<gap>')
    return res

# normalize: strip branch targets (hex addresses) so alignment isn't thrown off
import re
def norm(s):
    s = re.sub(r'\b0x[0-9a-f]+\b', 'ADDR', s)
    s = re.sub(r'\br\d+\b', 'rN', s)
    s = re.sub(r'\bf\d+\b', 'fN', s)
    s = re.sub(r'@\d+', '@SYM', s)
    return s

lr = rows(L); rr = rows(R)
print(f"TARGET match={L['match_percent'] if L else '?'}  OURS match={R['match_percent'] if R else '?'}")
sm = difflib.SequenceMatcher(None, [norm(x) for x in lr], [norm(x) for x in rr])
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        for k in range(i2-i1):
            pass # skip equals for brevity
        print(f"  ... {i2-i1} equal ...")
    elif tag == 'replace':
        n = max(i2-i1, j2-j1)
        for k in range(n):
            lt = lr[i1+k] if i1+k < i2 else ''
            rt = rr[j1+k] if j1+k < j2 else ''
            print(f"X {lt:<42}| {rt}")
    elif tag == 'delete':
        for k in range(i1, i2):
            print(f"- {lr[k]:<42}|")
    elif tag == 'insert':
        for k in range(j1, j2):
            print(f"+ {'':<42}| {rr[k]}")
