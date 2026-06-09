import subprocess, json, os, sys

UNIT = sys.argv[1] if len(sys.argv)>1 else 'pppRandUpIV'
SYM = UNIT
SRC = f'src/{UNIT}.cpp'
CFLAGS = '-nodefaults -proc gekko -align powerpc -enum int -fp hardware -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i build/GCCP01/include -DBUILD_VERSION=1 -DVERSION_GCCP01 -DNDEBUG=1 -use_lmw_stmw on -Cpp_exceptions on -lang=c++'.split()
# crude split keeps quoted pragmas wrong; rebuild with shlex-like handling
import shlex
CFLAGS = shlex.split('-nodefaults -proc gekko -align powerpc -enum int -fp hardware -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i build/GCCP01/include -DBUILD_VERSION=1 -DVERSION_GCCP01 -DNDEBUG=1 -use_lmw_stmw on -Cpp_exceptions on -lang=c++')

vers = ['1.0','1.1','1.1p1','1.2.5','1.2.5n','1.3','1.3.2','1.3.2r','2.0','2.0p1','2.5','2.6','2.7']
TGT = f'build/GCCP01/obj/{UNIT}.o'
OUT = f'build/_sweep_{UNIT}.o'

def match(ver):
    exe = os.path.normpath(f'build/compilers/GC/{ver}/mwcceppc.exe')
    if not os.path.exists(exe): return ('no-exe',None)
    r = subprocess.run([exe]+CFLAGS+['-c',SRC,'-o',OUT], capture_output=True, text=True)
    if r.returncode!=0 or not os.path.exists(OUT):
        return ('BUILDFAIL', (r.stderr or r.stdout)[-200:])
    d = subprocess.run(['./tools/objdiff-cli.exe','diff','-1',TGT,'-2',OUT,SYM,'-o','-','--format','json'],capture_output=True,text=True)
    try: j=json.loads(d.stdout)
    except: return ('nodiff',None)
    for s in j['left']['symbols']:
        if s['name']==SYM: return (s.get('match_percent'),None)
    return ('nosym',None)

for v in vers:
    m,err = match(v)
    print(f'{v:8} {m}' + (f'   {err}' if err else ''))
if os.path.exists(OUT): os.remove(OUT)
