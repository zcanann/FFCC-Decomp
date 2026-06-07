#!/usr/bin/env python3
import json, sys, subprocess, os

SYM = sys.argv[1]
T = "build/GCCP01/obj/monobj.o"
B = "build/GCCP01/src/monobj.o"
out = subprocess.check_output(["./tools/objdiff-cli","diff","-1",T,"-2",B,"-o","-","--format","json",SYM])
d = json.loads(out)

def find(side, name):
    for s in d[side]['symbols']:
        if s.get('name')==name:
            return s
    return None

L = find('left', SYM)
R = find('right', SYM)

def fmt_instrs(sym):
    res=[]
    for it in sym.get('instructions',[]):
        ins=it.get('instruction',{})
        res.append((ins.get('address'), ins.get('formatted',''), it.get('diff_kind','')))
    return res

print(f"# {SYM}  TARGET-match%={L.get('match_percent'):.2f}")
li = fmt_instrs(L)
ri = fmt_instrs(R)
n = max(len(li), len(ri))
for i in range(n):
    la = li[i] if i < len(li) else ('','','')
    ra = ri[i] if i < len(ri) else ('','','')
    mark = ' '
    if la[1]!=ra[1]:
        mark='|'
    elif la[2] or ra[2]:
        mark='~'
    print(f"{mark} {la[1]:<40} {ra[1]:<40}")
