import subprocess, json, os, re
EXE=os.path.normpath('build/compilers/GC/1.3.2/mwcceppc.exe')
FLAGS='-nodefaults -proc gekko -align powerpc -enum int -fp hardware -O4,p -inline auto -maxerrors 1 -nosyspath -fp_contract on -str reuse'.split()
SRC='build/_probe.c'; OBJ='build/_probe.o'
HDR='typedef int s32; typedef float f32; typedef unsigned char u8;\nextern float ERF(void);\n'

def regorder(body, fn='F'):
    open(SRC,'w').write(HDR+body)
    r=subprocess.run([EXE]+FLAGS+['-c',SRC,'-o',OBJ],capture_output=True,text=True)
    if r.returncode!=0 or not os.path.exists(OBJ):
        return 'FAIL:'+(r.stdout or r.stderr).strip().split(chr(10))[0][:50]
    out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',OBJ,'-2',OBJ,fn,'-o','-','--format','json'],capture_output=True,text=True)
    os.remove(OBJ)
    try: j=json.loads(out.stdout)
    except: return 'NODIFF'
    s=next((x for x in j['left']['symbols'] if x['name']==fn),None)
    if not s: return 'NOSYM'
    const=scale=None
    for ins in s.get('instructions',[]):
        f=ins['instruction']['formatted']
        if const is None and re.search(r'lfd f\d+, @',f): const=f.split()[1].rstrip(',')
        if scale is None and re.search(r'lfs f\d+, 0x0\(r',f): scale=f.split()[1].rstrip(',')
        if 'fmuls' in f and scale is None:
            # scale may be the 2nd src in fmuls
            pass
    return f'const={const} scale={scale}' + ('  <<< FLIP!' if const=='f2' and scale=='f1' else '')

# Variants: each defines F doing 3x  target[i] += (int)((f32)blend[i] * scale)
def mk(setup, mul='(int)((f32)blend[{i}] * scale)', n=3, args='s32* target, int* blend, f32* vp'):
    body=f'void F({args}){{\n  {setup}\n'
    for i in range(n): body+=f'  target[{i}] += {mul.format(i=i)};\n'
    return body+'}\n'

variants={
 'base':                 mk('f32 scale = *vp;'),
 'scale_first_mul':      mk('f32 scale = *vp;', '(int)(scale * (f32)blend[{i}])'),
 'scale_param':          mk('', args='s32* target, int* blend, f32 scale'),
 'scale_global':         'extern f32 gS;\n'+mk('f32 scale = gS;'),
 'scale_computed':       mk('f32 scale = ERF();'),
 'scale_2ops':           mk('f32 scale = *vp; f32 d = scale + scale; (void)d;'),
 'conv_temp':            mk('f32 scale = *vp;', '(int)(((f32)blend[{i}]) * scale)'),
 'named_conv':           'static inline int ri(int v,f32 s){f32 c=(f32)v; return (int)(c*s);}\n'+mk('f32 scale=*vp;','target[{i}]') .replace('target[{i}] += target[{i}];','') if False else 'X',
 'n2':                   mk('f32 scale=*vp;', n=2),
 'n4':                   mk('f32 scale=*vp;', n=4),
 'scale_minus':          mk('f32 scale = -*vp;', '(int)((f32)blend[{i}] * scale)'),
 'reverse_idx':          'void F(s32* target,int* blend,f32* vp){\n  f32 scale=*vp;\n  target[2]+=(int)((f32)blend[2]*scale);\n  target[1]+=(int)((f32)blend[1]*scale);\n  target[0]+=(int)((f32)blend[0]*scale);\n}\n',
 'scale_used_in_cond':   'void F(s32* target,int* blend,f32* vp){\n  f32 scale=*vp;\n  if(scale>0.0f){}\n  target[0]+=(int)((f32)blend[0]*scale);\n  target[1]+=(int)((f32)blend[1]*scale);\n  target[2]+=(int)((f32)blend[2]*scale);\n}\n',
 'double_scale':         mk('double scale = *vp;', '(int)((f32)blend[{i}] * (f32)scale)'),
 'extra_float_live':     'void F(s32* target,int* blend,f32* vp,f32* o){\n  f32 scale=*vp; f32 k=*o;\n  target[0]+=(int)((f32)blend[0]*scale)+(int)k;\n  target[1]+=(int)((f32)blend[1]*scale);\n  target[2]+=(int)((f32)blend[2]*scale);\n}\n',
}
for name,body in variants.items():
    if body=='X': continue
    print(f'{name:22} {regorder(body)}')
if os.path.exists(SRC): os.remove(SRC)
