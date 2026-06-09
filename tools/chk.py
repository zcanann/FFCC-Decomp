import json,sys,subprocess
unit=sys.argv[1]; sym=sys.argv[2] if len(sys.argv)>2 else unit
r=subprocess.run(['ninja',f'build/GCCP01/src/{unit}.o'],capture_output=True,text=True)
if r.returncode!=0:
    print("BUILD FAIL"); print(r.stdout[-1500:]); print(r.stderr[-1500:]); sys.exit(1)
tgt=f'build/GCCP01/obj/{unit}.o'; base=f'build/GCCP01/src/{unit}.o'
out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',tgt,'-2',base,sym,'-o','-','--format','json'],capture_output=True,text=True)
d=json.loads(out.stdout)
for s in d['left']['symbols']:
    if s.get('name')==sym:
        print(f"{sym}: {s.get('match_percent')}")
