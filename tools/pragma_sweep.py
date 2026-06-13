#!/usr/bin/env python3
"""Per-function pragma sweep (self-serve, no agent tokens).

For each high-impact unmatched function in a unit, try wrapping it with each
optimization pragma (#pragma X off ... #pragma X reset), rebuild via ninja,
and keep the pragma that raises THAT function's fuzzy match without regressing
any other function in the unit and while keeping the DOL byte-exact (if a
build/GCCP01/ok target exists for it).

Usage: python3 tools/pragma_sweep.py <unit> <src.cpp> [topN] [--apply]
  <unit>   e.g. menu_compa  (report unit is main/<unit>)
  topN     number of top-impact unmatched funcs to sweep (default 4)
  --apply  leave the best pragmas applied in the file (default: report only,
           file restored)
Only the 5 pragmas that have historically produced REAL wins are tried.
"""
import json, subprocess, sys, re, os

UNIT = sys.argv[1]
SRC = sys.argv[2]
TOPN = int(sys.argv[3]) if len(sys.argv) > 3 and not sys.argv[3].startswith('--') else 4
APPLY = '--apply' in sys.argv
REPORT = 'build/GCCP01/report.json'
PRAGMAS = ['opt_lifetimes', 'opt_propagation', 'opt_common_subs',
           'opt_strength_reduction', 'opt_dead_assignments']


def build_and_report():
    r = subprocess.run(['ninja'], capture_output=True, text=True)
    if r.returncode != 0:
        return None, 'BUILDFAIL:' + (r.stderr or r.stdout)[-300:]
    subprocess.run(['build/tools/objdiff-cli', 'report', 'generate', '-o', REPORT],
                   capture_output=True, text=True)
    d = json.load(open(REPORT))
    for u in d['units']:
        if u['name'] == 'main/' + UNIT:
            return {f['name']: f['fuzzy_match_percent'] for f in u.get('functions', [])}, None
    return None, 'UNIT_NOT_IN_REPORT'


def dol_ok():
    # if a byte-exact ok target exists, require it; else accept
    r = subprocess.run(['ninja', 'build/GCCP01/ok'], capture_output=True, text=True)
    return r.returncode == 0


def src_name(mangled):
    """Turn a mangled symbol into a source-searchable 'Class::func' or 'func'."""
    base = mangled.split('__', 1)[0]
    return base


def find_func_span(lines, fname):
    """Return (start_idx, end_idx) covering the function definition whose name
    matches fname, or None. start_idx is the signature line; end_idx is the line
    of the matching closing brace."""
    pat = re.compile(r'\b' + re.escape(fname) + r'\s*\(')
    for i, ln in enumerate(lines):
        if not pat.search(ln):
            continue
        # must be a definition: find the '{' that opens the body within a few lines
        # and the line must not be a prototype ending in ';'
        joined = ''
        opb = None
        for j in range(i, min(i + 12, len(lines))):
            joined = lines[j]
            if ';' in joined and '{' not in ''.join(lines[i:j + 1]):
                opb = None
                break
            if '{' in lines[j]:
                opb = j
                break
        if opb is None:
            continue
        # brace match from opb
        depth = 0
        for j in range(opb, len(lines)):
            depth += lines[j].count('{') - lines[j].count('}')
            if depth <= 0 and j >= opb:
                return (i, j)
    return None


def main():
    base, err = build_and_report()
    if base is None:
        print('baseline build failed:', err); return
    has_ok = dol_ok()
    # rank unmatched funcs by impact (size unknown here; use (100-fuzzy))
    d = json.load(open(REPORT))
    u = [x for x in d['units'] if x['name'] == 'main/' + UNIT][0]
    funcs = [(f['name'], f['fuzzy_match_percent'], int(str(f.get('size', 0))))
             for f in u['functions'] if f['fuzzy_match_percent'] < 99.99]
    funcs.sort(key=lambda t: -(t[2] * (100 - t[1])))
    targets = funcs[:TOPN]
    print(f'{UNIT}: baseline funcs<100={len(funcs)}; sweeping top {len(targets)} '
          f'(DOL-ok-gate={"yes" if has_ok else "no"})')
    orig = open(SRC).read()
    cur = orig
    wins = []
    for fname_m, fbase, fsize in targets:
        sname = src_name(fname_m)
        lines = cur.split('\n')
        # use the LAST path component of Class::func for matching the definition
        search = sname.split('::')[-1] if '::' in sname else sname
        span = find_func_span(lines, search)
        if not span:
            print(f'  {sname}: span NOT FOUND (skip)')
            continue
        s, e = span
        best = (None, base.get(fname_m, fbase))
        for pr in PRAGMAS:
            test = lines[:s] + [f'#pragma {pr} off'] + lines[s:e + 1] + \
                [f'#pragma {pr} reset'] + lines[e + 1:]
            open(SRC, 'w').write('\n'.join(test))
            rep, err = build_and_report()
            if rep is None:
                continue
            newf = rep.get(fname_m, 0)
            # no other function may regress
            regress = any(rep.get(k, 100) < base.get(k, 100) - 0.001
                          for k in base if k != fname_m)
            okdol = dol_ok() if has_ok else True
            tag = ''
            if newf > best[1] + 0.001 and not regress and okdol:
                best = (pr, newf); tag = ' <= BEST'
            print(f'  {search} +{pr}: {newf:.3f} '
                  f'{"REGRESS" if regress else ""}{"DOLDIFF" if not okdol else ""}{tag}')
        if best[0]:
            cur = '\n'.join(lines[:s] + [f'#pragma {best[0]} off'] + lines[s:e + 1] +
                            [f'#pragma {best[0]} reset'] + lines[e + 1:])
            base[fname_m] = best[1]
            wins.append((search, best[0], fbase, best[1]))
            print(f'  => {search}: KEEP {best[0]} ({fbase:.2f} -> {best[1]:.2f})')
        open(SRC, 'w').write(cur)
    # finalize
    if APPLY and wins:
        open(SRC, 'w').write(cur)
        build_and_report()
        print('APPLIED', len(wins), 'pragma wins')
    else:
        open(SRC, 'w').write(orig)
        build_and_report()
    print('\nWINS:')
    for s, pr, a, b in wins:
        print(f'  {s}: {pr}  {a:.2f} -> {b:.2f}')
    if not wins:
        print('  (none)')


if __name__ == '__main__':
    main()
