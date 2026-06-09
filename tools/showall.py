import json,sys,subprocess
unit=sys.argv[1]
sym=sys.argv[2] if len(sys.argv)>2 else unit
lo=int(sys.argv[3]) if len(sys.argv)>3 else 0
hi=int(sys.argv[4]) if len(sys.argv)>4 else 9999
tgt=f'build/GCCP01/obj/{unit}.o'; base=f'build/GCCP01/src/{unit}.o'
out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',tgt,'-2',base,sym,'-o','-','--format','json'],capture_output=True,text=True)
d=json.loads(out.stdout)
def getsym(side):
    for s in side['symbols']:
        if s.get('name')==sym: return s
L=getsym(d['left']); R=getsym(d['right'])
li=L.get('instructions',[]); ri=R.get('instructions',[])
for i in range(max(len(li),len(ri))):
    if i<lo or i>hi: continue
    l=li[i] if i<len(li) else None; r=ri[i] if i<len(ri) else None
    lf=l['instruction']['formatted'] if l else ''
    rf=r['instruction']['formatted'] if r else ''
    lk=l.get('diff_kind') if l else None; rk=r.get('diff_kind') if r else None
    mark=' <<<' if not(lk in (None,'DIFF_NONE') and rk in (None,'DIFF_NONE')) else ''
    print(f"{i:3} T:{lf:38} | B:{rf:38}{mark}")
