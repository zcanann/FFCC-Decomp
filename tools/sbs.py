#!/usr/bin/env python3
import json,sys,subprocess

unit="main/menu_letter"
sym=sys.argv[1]
start=int(sys.argv[2]) if len(sys.argv)>2 else 0
end=int(sys.argv[3]) if len(sys.argv)>3 else 100000

out=subprocess.check_output(["./tools/objdiff-cli","diff","-u",unit,"-p",".",sym,"-o","-","--format","json"])
d=json.loads(out)

def insns(side):
    for s in d[side]['symbols']:
        if s['name']==sym:
            return s['instructions']
    return []

L=insns('left')   # target
R=insns('right')  # base (ours)

def fmt(ins):
    if ins is None: return ""
    i=ins.get('instruction')
    if i is None: return "<gap>"
    return i.get('formatted','')

def kind(ins):
    if ins is None: return ''
    return ins.get('diff_kind','')

# align by row index (objdiff already aligns)
n=max(len(L),len(R))
for idx in range(n):
    li=L[idx] if idx<len(L) else None
    ri=R[idx] if idx<len(R) else None
    lk=kind(li); rk=kind(ri)
    marker=' '
    if lk or rk:
        marker='|'
    if idx<start or idx>end:
        continue
    ls=fmt(li); rs=fmt(ri)
    print(f"{idx:4} {marker} {ls:<40} {rs}")
