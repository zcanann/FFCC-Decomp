import json,subprocess,sys,re

UNIT=sys.argv[1]; SYM=UNIT
VARMOD=sys.argv[2]  # python file defining `bodies` dict and `marker_re`
SRC=f'src/{UNIT}.cpp'
orig=open(SRC,encoding='utf-8').read()

ns={}
exec(open(VARMOD,encoding='utf-8').read(),ns)
marker_re=ns['MARKER']
bodies=ns['bodies']

m=re.search(marker_re, orig, re.S)
if not m:
    print("MARKER NOT FOUND"); sys.exit(1)
head=orig[:m.start(1)]; tail=orig[m.end(1):]

def measure(body):
    open(SRC,'w',encoding='utf-8',newline='\n').write(head+body+tail)
    r=subprocess.run(['ninja',f'build/GCCP01/src/{UNIT}.o'],capture_output=True,text=True)
    if r.returncode!=0: return None
    out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',f'build/GCCP01/obj/{UNIT}.o','-2',f'build/GCCP01/src/{UNIT}.o',SYM,'-o','-','--format','json'],capture_output=True,text=True)
    try: d=json.loads(out.stdout)
    except: return None
    for s in d['left']['symbols']:
        if s.get('name')==SYM: return s.get('match_percent')
    return None

best=(-1,None)
try:
    for name,body in bodies.items():
        p=measure(body)
        print(f'{p}  {name}' if p is not None else f'BUILDFAIL  {name}')
        if p is not None and p>best[0]: best=(p,name)
finally:
    open(SRC,'w',encoding='utf-8',newline='\n').write(orig)
print('--- restored --- best:',best)
