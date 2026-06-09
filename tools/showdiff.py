import json,sys,subprocess,os
unit=sys.argv[1]
sym=sys.argv[2] if len(sys.argv)>2 else unit
tgt=f'build/GCCP01/obj/{unit}.o'
base=f'build/GCCP01/src/{unit}.o'
out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',tgt,'-2',base,sym,'-o','-','--format','json'],capture_output=True,text=True)
d=json.loads(out.stdout)
def getsym(side):
    for s in side['symbols']:
        if s.get('name')==sym:
            return s
    return None
L=getsym(d['left']); R=getsym(d['right'])
li=L.get('instructions',[]); ri=R.get('instructions',[])
print(f"match={L.get('match_percent')}")
n=max(len(li),len(ri))
for i in range(n):
    l=li[i] if i<len(li) else None
    r=ri[i] if i<len(ri) else None
    lk=l.get('diff_kind') if l else None
    rk=r.get('diff_kind') if r else None
    lf=l['instruction']['formatted'] if l else ''
    rf=r['instruction']['formatted'] if r else ''
    mark='' if (lk in (None,'DIFF_NONE') and rk in (None,'DIFF_NONE')) else ' <<<'
    if mark:
        la=l['instruction'].get('address') if l else ''
        print(f"{i:3} T:{lf:40} | B:{rf:40}{mark} ({lk}/{rk})")
