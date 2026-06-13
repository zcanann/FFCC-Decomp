#!/usr/bin/env python3
# Classify a function's (or whole unit's) objdiff mismatches to direct effort.
# Usage: python3 tools/classify_diff.py main/<unit> [FUNC_MANGLED]
#   no FUNC -> rank all sub-100 functions by STRUCTURAL-fixable mismatch count.
import json, sys, subprocess, re
unit = sys.argv[1]; only = sys.argv[2] if len(sys.argv) > 2 else None
def diff(sym):
    out = subprocess.run(['./tools/objdiff-cli','diff','-p','.','-u',unit,sym,'-o','-','--format','json'],
                         capture_output=True, text=True)
    if out.returncode != 0: return None
    return json.loads(out.stdout)
REG = re.compile(r'\br\d+\b|\bf\d+\b')
def classify(L, R):
    li = L.get('instructions') or []; ri = R.get('instructions') or []
    cats = {'missing_code':0,'extra_code':0,'structural':0,'arg_reloc':0,'register':0,'ok':0}
    n = max(len(li), len(ri))
    for i in range(n):
        a = li[i] if i < len(li) else None
        b = ri[i] if i < len(ri) else None
        ak = a.get('diff_kind') if a else None; bk = b.get('diff_kind') if b else None
        if (ak in (None,'DIFF_NONE')) and (bk in (None,'DIFF_NONE')): cats['ok']+=1; continue
        af = a['instruction']['formatted'] if a and a.get('instruction') else None
        bf = b['instruction']['formatted'] if b and b.get('instruction') else None
        if af is None: cats['missing_code']+=1; continue   # target has insn we lack (we deleted)
        if bf is None: cats['extra_code']+=1; continue
        amn = af.split()[0] if af else ''; bmn = bf.split()[0] if bf else ''
        if amn != bmn: cats['structural']+=1; continue      # different opcode = structural/scheduling
        # same mnemonic: is the only difference register names?
        a_noreg = REG.sub('#', af); b_noreg = REG.sub('#', bf)
        if a_noreg == b_noreg: cats['register']+=1          # pure register rename
        else: cats['arg_reloc']+=1                          # immediate/reloc/arg differs
    return cats
def get(side,d,sym):
    for s in d[side]['symbols']:
        if s.get('name')==sym: return s
    return None
if only:
    d = diff(only)
    L=get('left',d,only); R=get('right',d,only)
    c = classify(L,R)
    print(f"{only}  match={L.get('match_percent')}")
    for k in ('missing_code','extra_code','structural','arg_reloc','register','ok'):
        print(f"  {k:14}{c[k]}")
    print("  >>> FIXABLE (missing/extra/structural/arg):", c['missing_code']+c['extra_code']+c['structural']+c['arg_reloc'])
else:
    rep = json.load(open('build/GCCP01/report.json'))
    u = [x for x in rep['units'] if x['name']==unit][0]
    res=[]
    for it in u.get('functions',[]):
        f = it.get('fuzzy_match_percent')
        if f is None or float(f) >= 99.99: continue
        d = diff(it['name'])
        if not d: continue
        L=get('left',d,it['name']); R=get('right',d,it['name'])
        if not L or not R: continue
        c = classify(L,R)
        fix = c['missing_code']+c['extra_code']+c['structural']+c['arg_reloc']
        res.append((fix, c['register'], float(f), it['name'], c))
    res.sort(reverse=True)
    print(f"{unit}: functions ranked by STRUCTURALLY-FIXABLE mismatch count (high = go here first)")
    print(f"{'fixable':>7} {'reg':>5} {'fuzzy':>6}  function   [miss/extra/struct/arg]")
    for fix,reg,f,nm,c in res:
        print(f"{fix:7d} {reg:5d} {f:6.2f}  {nm}  [{c['missing_code']}/{c['extra_code']}/{c['structural']}/{c['arg_reloc']}]")
