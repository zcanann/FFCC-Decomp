import subprocess, json, re, os
UNIT='pppRandUpIV'; SYM=UNIT; SRC=f'src/{UNIT}.cpp'
orig=open(SRC,encoding='utf-8').read()
m=re.search(r'(    s32\* target = .*?target\[2\] \+= randint.*?;\n)', orig, re.S)
# also allow replacing the else-branch tail; we'll replace from 'else {' return block to end-of-func body
# Simpler: replace the region from after the if/else merge. Capture group: the 3-line block + scale decl
head=orig[:m.start(1)]; tail=orig[m.end(1):]

def run(block):
    open(SRC,'w',encoding='utf-8',newline='\n').write(head+block+tail)
    r=subprocess.run(['ninja',f'build/GCCP01/src/{UNIT}.o'],capture_output=True,text=True)
    if r.returncode!=0: return ('BUILDFAIL',None)
    out=subprocess.run(['./tools/objdiff-cli.exe','diff','-1',f'build/GCCP01/obj/{UNIT}.o','-2',f'build/GCCP01/src/{UNIT}.o',SYM,'-o','-','--format','json'],capture_output=True,text=True)
    try: j=json.loads(out.stdout)
    except: return ('NODIFF',None)
    s=next((x for x in j['right']['symbols'] if x['name']==SYM),None)
    pct=s.get('match_percent') if s else None
    creg=None
    for ins in (s.get('instructions',[]) if s else []):
        f=ins.get('instruction',{}).get('formatted','')
        if 'lfd f' in f and '@' in f: creg=f.split()[1].rstrip(','); break
    return (pct,creg)

T='    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);\n'
def loop(v): return ''.join(f'    target[{i}] += randint(in->blend[{i}], {v});\n' for i in range(3))

blocks={
 'base':                 T+'    f32 scale = *valuePtr;\n'+loop('scale'),
 'scale_before_target':  '    f32 scale = *valuePtr;\n'+T+loop('scale'),
 'scale_v0':             T+'    f32 scale = valuePtr[0];\n'+loop('scale'),
 'inline_deref':         T+loop('*valuePtr'),
 'scale_then_neg':       T+'    f32 scale = *valuePtr;\n'+loop('scale'),
 'no_target_local':      '    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(basePtr->m_workArea + in->sourceOffset);\n    f32 scale = *valuePtr;\n'+loop('scale'),
 'scale_first_operand':  T+'    f32 scale = *valuePtr;\n'+''.join(f'    target[{i}] += (s32)(scale * (f32)in->blend[{i}]);\n' for i in range(3)),
}
for n,b in blocks.items():
    pct,creg=run(b)
    flag='  <<< const=f2!' if creg=='f2' else ''
    print(f'{n:22} match={pct} const={creg}{flag}')
open(SRC,'w',encoding='utf-8',newline='\n').write(orig)
print('restored')
