#!/usr/bin/env python3
"""Readable per-symbol asm diff for menu_letter. Usage: sdiff.py <symbol>"""
import json, subprocess, sys

sym = sys.argv[1]
tgt = "build/GCCP01/obj/menu_letter.o"
base = "build/GCCP01/src/menu_letter.o"
out = subprocess.run(["tools/objdiff-cli","diff","-1",tgt,"-2",base,sym,"-o","-","--format","json"],
                     capture_output=True,text=True).stdout
d = json.loads(out)

def instrs(side):
    for s in d[side]["symbols"]:
        if s["name"]==sym:
            res=[]
            for it in s.get("instructions",[]):
                dk=it.get("diff_kind","")
                ins=it.get("instruction",{})
                res.append((dk, ins.get("formatted","")))
            return res, s.get("match_percent",0)
    return [],0

L,lp=instrs("left")
R,rp=instrs("right")
print(f"# {sym}  target_match={lp:.2f}%")
i=j=0
while i<len(L) or j<len(R):
    l=L[i] if i<len(L) else ("","")
    r=R[j] if j<len(R) else ("","")
    ldk=l[0]; rdk=r[0]
    # DIFF_DELETE = only in target(left); DIFF_INSERT only in base(right)
    if ldk=="DIFF_DELETE" and rdk!="DIFF_INSERT":
        print(f"{'DEL':4} {l[1]:40} <         ")
        i+=1; continue
    if rdk=="DIFF_INSERT" and ldk!="DIFF_DELETE":
        print(f"{'':4} {'':40} >    {'INS':4} {r[1]}")
        j+=1; continue
    mark="|" if l[1]!=r[1] else " "
    flag=ldk[:3] if ldk else ""
    print(f"{flag:4} {l[1]:40} {mark}    {r[1]}")
    i+=1; j+=1
