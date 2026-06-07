#!/usr/bin/env python3
import json, subprocess, sys, difflib

sym = sys.argv[1]
unit = sys.argv[2] if len(sys.argv) > 2 else "main/materialman"
root = "/Users/zcanann/Documents/Projects/ffcc-grind-materialman"
out = subprocess.run(["tools/objdiff-cli","diff","-p",".","-u",unit,"-o","-","--format","json",sym],
                     cwd=root, capture_output=True, text=True)
d = json.loads(out.stdout)

def get_sym(side):
    for s in side.get("symbols", []):
        if s.get("name") == sym:
            return s
    return None

def fmt(side):
    s = get_sym(side)
    if not s: return None, None
    lines = []
    for w in s.get("instructions", []):
        ins = w.get("instruction")
        if not ins:
            continue
        lines.append(ins.get("formatted",""))
    return lines, s.get("match_percent")

L, lp = fmt(d["left"])   # target
R, rp = fmt(d["right"])  # base (our build)
print(f"TARGET match={lp}")
if L is None: print("left not found"); sys.exit(1)
if R is None: print("right not found"); R=[]

# strip leading addresses in branch ops for alignment readability
def norm(lst):
    res=[]
    for x in lst:
        # remove "-> 0x...." style and absolute addrs after b/bl etc kept
        res.append(x)
    return res

sm = difflib.SequenceMatcher(a=norm(R), b=norm(L))
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag=="equal":
        if i2-i1>3:
            print(f"  = [{i1}:{i2}] ...{i2-i1} matching...")
        else:
            for k in range(i1,i2): print(f"  = {R[k]}")
    elif tag=="replace":
        for k in range(i1,i2): print(f"  - {R[k]}")
        for k in range(j1,j2): print(f"  + {L[k]}")
    elif tag=="delete":
        for k in range(i1,i2): print(f"  - {R[k]}")
    elif tag=="insert":
        for k in range(j1,j2): print(f"  + {L[k]}")
print(f"\n(- = our build / base, + = target)  TARGET match={lp}")
