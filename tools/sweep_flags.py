import subprocess, json, os, sys, shlex
UNIT = sys.argv[1] if len(sys.argv)>1 else 'pppRandUpIV'
SYM=UNIT; SRC=f'src/{UNIT}.cpp'
EXE=os.path.normpath('build/compilers/GC/1.3.2/mwcceppc.exe')
BASE='-nodefaults -proc gekko -align powerpc -enum int -fp hardware -O4,p -inline auto -pragma "cats off" -pragma "warn_notinlined off" -maxerrors 1 -nosyspath -RTTI off -fp_contract on -str reuse -multibyte -i include -i build/GCCP01/include -DBUILD_VERSION=1 -DVERSION_GCCP01 -DNDEBUG=1 -use_lmw_stmw on -Cpp_exceptions on -lang=c++'
TGT=f'build/GCCP01/obj/{UNIT}.o'; OUT=f'build/_swf_{UNIT}.o'
def measure(extra, repl=None):
    flags=BASE
    if repl:
        for a,b in repl: flags=flags.replace(a,b)
    args=shlex.split(flags)+shlex.split(extra)+['-c',SRC,'-o',OUT]
    r=subprocess.run([EXE]+args,capture_output=True,text=True)
    if r.returncode!=0 or not os.path.exists(OUT): return 'FAIL'
    d=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',TGT,'-2',OUT,SYM,'-o','-','--format','json'],capture_output=True,text=True)
    try: j=json.loads(d.stdout)
    except: return 'nodiff'
    for s in j['left']['symbols']:
        if s['name']==SYM: return s.get('match_percent')
    return 'nosym'
tests = {
 'base':('',None),
 'fp_contract_off':('',[('-fp_contract on','-fp_contract off')]),
 'fp_fmadd':('',[('-fp hardware','-fp fmadd')]),
 'fp_off':('',[('-fp hardware','-fp software')]),
 'inline_on':('',[('-inline auto','-inline on')]),
 'inline_off':('',[('-inline auto','-inline off')]),
 'inline_all':('',[('-inline auto','-inline all')]),
 'inline_noauto':('',[('-inline auto','-inline on,noauto')]),
 'O4':('',[('-O4,p','-O4')]),
 'O3p':('',[('-O4,p','-O3,p')]),
 'O2p':('',[('-O4,p','-O2,p')]),
 'O4s':('',[('-O4,p','-O4,s')]),
 'str_pool':('',[('-str reuse','-str pool')]),
 'no_lmw':('',[('-use_lmw_stmw on','-use_lmw_stmw off')]),
 'sched_off':('-pragma "scheduling off"',None),
 'sched_on':('-pragma "scheduling on"',None),
 'opt_nopeep':('-pragma "opt_peephole off"',None),
 'no_fp_contract_pragma':('-pragma "fp_contract off"',None),
 'ipa_off':('-ipa off',None),
 'inline_deferred':('-inline deferred',None),
 'volatile_pragma':('-pragma "volatile_asm off"',None),
 'peephole_off':('-disable_registers',None),
}
best=(-1,None)
for n,(ex,rp) in tests.items():
    m=measure(ex,rp)
    print(f'{n:22} {m}')
    if isinstance(m,(int,float)) and m>best[0]: best=(m,n)
if os.path.exists(OUT): os.remove(OUT)
print('best',best)
