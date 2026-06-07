#!/usr/bin/env python3
"""Show per-instruction diff for one symbol. Usage: symdiff.py <unit> <symbol> [start] [count]"""
import json, subprocess, sys

unit = sys.argv[1]
sym = sys.argv[2]
start = int(sys.argv[3]) if len(sys.argv) > 3 else 0
count = int(sys.argv[4]) if len(sys.argv) > 4 else 80

out = subprocess.run(
    ["./build/tools/objdiff-cli", "diff", "-p", ".", "-u", unit, "-o", "-",
     "--format", "json", sym],
    capture_output=True, text=True)
d = json.loads(out.stdout)


def find(side):
    for s in d[side]["symbols"]:
        if s.get("name") == sym:
            return s
    return None


L = find("left")
R = find("right")
print(f"match={L.get('match_percent'):.3f}%  target_instrs={len(L['instructions'])} base_instrs={len(R['instructions']) if R else 0}")
li = L["instructions"]
ri = R["instructions"] if R else []


def fmt(ins):
    return ins.get("instruction", {}).get("formatted", "?")


def kind(ins):
    return ins.get("diff_kind", "")


nmis = 0
for i, ins in enumerate(li):
    k = kind(ins)
    if k not in ("DIFF_NONE", "", None):
        nmis += 1
print(f"mismatched rows: {nmis}")

end = min(start + count, len(li))
for i in range(start, end):
    lins = li[i]
    rins = ri[i] if i < len(ri) else None
    k = kind(lins)
    mark = " " if k in ("DIFF_NONE", "", None) else "X"
    lf = fmt(lins)
    rf = fmt(rins) if rins else "----"
    print(f"{mark} {i:4} {lf:38} | {rf}")
