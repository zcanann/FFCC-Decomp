#!/usr/bin/env python3
# Rank functions across B1 units by RECONSTRUCTABLE mismatch (missing+extra+structural),
# excluding arg_reloc (often anon-reloc noise) and register (compiler-internal).
import json, subprocess, re, sys
UNITS = sys.argv[1:] or ['main/wm_menu','main/bonus_menu','main/menu_cmd','main/MenuUtil','main/shopmenu','main/singmenu']
REG = re.compile(r'\br\d+\b|\bf\d+\b')
def diff(u, sym):
    o = subprocess.run(['./tools/objdiff-cli','diff','-p','.','-u',u,sym,'-o','-','--format','json'],capture_output=True,text=True)
    return json.loads(o.stdout) if o.returncode==0 else None
def cls(L,R):
    li=L.get('instructions') or []; ri=R.get('instructions') or []; c={'m':0,'e':0,'s':0}
    for i in range(max(len(li),len(ri))):
        a=li[i] if i<len(li) else None; b=ri[i] if i<len(ri) else None
        ak=a.get('diff_kind') if a else None; bk=b.get('diff_kind') if b else None
        if ak in (None,'DIFF_NONE') and bk in (None,'DIFF_NONE'): continue
        af=a['instruction']['formatted'] if a and a.get('instruction') else None
        bf=b['instruction']['formatted'] if b and b.get('instruction') else None
        if af is None: c['m']+=1
        elif bf is None: c['e']+=1
        elif af.split()[0]!=bf.split()[0]: c['s']+=1
    return c
rep=json.load(open('build/GCCP01/report.json'))
rows=[]
for u in UNITS:
    un=[x for x in rep['units'] if x['name']==u]
    if not un: continue
    for it in un[0].get('functions',[]):
        f=it.get('fuzzy_match_percent')
        if f is None or float(f)>=99.99: continue
        d=diff(u,it['name'])
        if not d: continue
        L=[s for s in d['left']['symbols'] if s['name']==it['name']]; R=[s for s in d['right']['symbols'] if s['name']==it['name']]
        if not L or not R: continue
        c=cls(L[0],R[0]); recon=c['m']+c['e']+c['s']
        if recon>0: rows.append((recon,float(f),u.replace('main/',''),it['name'],c))
rows.sort(reverse=True)
print("RECONSTRUCTABLE (missing+extra+structural) across B1 — go here for real source bugs:")
print(f"{'recon':>5} {'fuzzy':>6} {'unit':12} fn  [m/e/s]")
for r,f,u,n,c in rows[:30]:
    print(f"{r:5d} {f:6.2f} {u:12} {n}  [{c['m']}/{c['e']}/{c['s']}]")
