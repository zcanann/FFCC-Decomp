#!/usr/bin/env python3
"""Show fuzzy match percent for symbols in menu_letter from report.json."""
import json, sys

syms = sys.argv[1:]
d = json.load(open("build/GCCP01/report.json"))
for u in d["units"]:
    if u["name"] != "main/menu_letter":
        continue
    fuzzy = u["measures"].get("fuzzy_match_percent", 0)
    print(f"UNIT fuzzy={fuzzy:.3f}%")
    for f in u["functions"]:
        if not syms or any(s in f["name"] for s in syms):
            print(f"  {f.get('fuzzy_match_percent',0):7.3f}%  {f['name']}")
