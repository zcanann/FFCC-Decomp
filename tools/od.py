#!/usr/bin/env python3
"""Render objdiff side-by-side asm for a symbol. Usage: od.py <unit> <symbol> [maxrows]"""
import json, subprocess, sys, os

unit = sys.argv[1]
sym = sys.argv[2]
maxrows = int(sys.argv[3]) if len(sys.argv) > 3 else 10000

root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
cli = os.path.join(root, "tools", "objdiff-cli")
out = subprocess.run([cli, "diff", "-p", root, "-u", unit, sym, "-o", "-", "--format", "json"],
                     capture_output=True, text=True)
d = json.loads(out.stdout)


def find(side):
    for s in d[side]["symbols"]:
        if s.get("name") == sym:
            return s
    # fallback: substring
    for s in d[side]["symbols"]:
        if sym in s.get("name", ""):
            return s
    return None


L = find("left")   # target (what we want to match)
R = find("right")  # base (our compiled output)
print(f"left(target) match={L.get('match_percent'):.2f}  right(base) match={R.get('match_percent'):.2f}")
li = L.get("instructions", [])
ri = R.get("instructions", [])


def fmt(ins):
    if ins is None:
        return ""
    i = ins.get("instruction")
    if i is None:
        return ins.get("formatted", "?")
    return i.get("formatted", "?")


def kind(ins):
    if ins is None:
        return ""
    k = ins.get("diff_kind", "")
    return k.replace("DIFF_", "")


n = max(len(li), len(ri))
for i in range(min(n, maxrows)):
    a = li[i] if i < len(li) else None
    b = ri[i] if i < len(ri) else None
    la = fmt(a)
    lb = fmt(b)
    mark = " "
    ka = kind(a)
    kb = kind(b)
    if la != lb or ka not in ("", "NONE") or kb not in ("", "NONE"):
        mark = "|"
    print(f"{i:4} {la:<40}{mark} {lb:<40} {ka or kb}")
