#!/usr/bin/env python3
"""Per-function fuzzy breakdown for given units from report.json."""
import json, sys

report = "build/GCCP01/report.json"
data = json.load(open(report))
targets = set(sys.argv[1:]) if len(sys.argv) > 1 else None

for u in data["units"]:
    if targets and u["name"] not in targets:
        continue
    m = u["measures"]
    fuzzy = m.get("fuzzy_match_percent", 0)
    if targets is None and fuzzy >= 100:
        continue
    name = u["name"]
    mf = m.get("matched_functions", 0)
    tf = m.get("total_functions", 0)
    code = m.get("matched_code_percent", 0)
    dpct = m.get("matched_data_percent", 0)
    print(f"\n### {name}  fuzzy={fuzzy:.2f}%  funcs={mf}/{tf}  code={code:.1f}%  data={dpct:.1f}%")
    funcs = u.get("functions", [])
    def fpct(f):
        return f.get("fuzzy_match_percent", 0) or 0
    def fsize(f):
        try:
            return int(f.get("size", 0) or 0)
        except (TypeError, ValueError):
            return 0
    notdone = [f for f in funcs if fpct(f) < 100]
    # impact = unmatched bytes = size * (1 - match). Sort by impact desc so agents
    # see the highest-payoff functions first.
    notdone.sort(key=lambda f: fsize(f) * (1 - fpct(f) / 100.0), reverse=True)
    total_unmatched_bytes = sum(fsize(f) * (1 - fpct(f) / 100.0) for f in notdone)
    print(f"   {len(notdone)} unmatched funcs (sorted by unmatched-byte impact; ~{int(total_unmatched_bytes)} bytes to recover):")
    for f in notdone:
        impact = int(fsize(f) * (1 - fpct(f) / 100.0))
        print(f"     {fpct(f):6.2f}%  size={fsize(f):>6}  impact~{impact:>6}  {f['name']}")
