import json, sys
name=sys.argv[1]
d=json.load(open('d.json'))
def get(side):
    for s in d[side]['symbols']:
        if name in s.get('demangled_name','') or name in s.get('name',''):
            return s
    return None
L=get('left'); R=get('right')
def fmt(sym):
    out=[]
    for i in sym['instructions']:
        ins=i.get('instruction')
        out.append((i.get('diff_kind',''), ins['formatted'] if ins else ''))
    return out
lf=fmt(L); rf=fmt(R)
print('%-42s | %-42s'%('=== ORIG (target/L) ===','=== MINE (base/R) ==='))
for i in range(max(len(lf),len(rf))):
    l=lf[i] if i<len(lf) else ('','')
    r=rf[i] if i<len(rf) else ('','')
    mark='' if l[1]==r[1] else '  <<<'
    print('%-42s | %-42s%s'%(l[1][:42], r[1][:42], mark))
