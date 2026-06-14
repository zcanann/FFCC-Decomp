#!/usr/bin/env python3
"""Self-serve per-object COMPILER-FLAG sweep (no agent tokens).

The recurring B2 walls are mwcc register-allocation / instruction-scheduling /
callee-saved-register-count cascades — which are driven by the per-object
compiler FLAGS in configure.py, not just source. This sweeps candidate
extra_cflags for ONE object, rebuilds, and reports the TOTAL structural misalign
(DIFF_INSERT/DELETE/REPLACE summed over the unit's functions) for each flag set.
A flag set that lowers total misalign = the compiler now matches the target's
codegen better. Run locally via configure.py -v GCCP01 + ninja.

Usage: python3 tools/cflag_sweep.py <unit> <src_basename.cpp>
  e.g. python3 tools/cflag_sweep.py menu_favo menu_favo.cpp
Restores configure.py afterward (report-only). Run inside a worktree.
"""
import json, subprocess, sys, re, os, shutil

UNIT = sys.argv[1]
SRC = sys.argv[2]
CFG = 'configure.py'

# candidate extra_cflags sets to try (each OVERRIDES the base where flags repeat;
# mwcc takes the LAST occurrence of a repeated flag)
CANDIDATES = [
    ['-use_lmw_stmw off'],
    ['-inline auto,deferred'],
    ['-inline deferred'],
    ['-inline deferred,auto'],
    ['-inline all'],
    ['-O3,p'],
    ['-fp_contract off'],
    ['-sdata 0'],
    ['-sdata 8'],
    ['-sdata2 8'],
    ['-str reuse,pool,readonly'],
    ['-RTTI on', '-sdata 8', '-str reuse,pool,readonly'],
    ['-RTTI on', '-sdata 8', '-inline auto,deferred', '-str reuse,pool,readonly'],
    ['-sdata 8', '-sdata2 8'],
    ['-inline auto,deferred', '-use_lmw_stmw off'],
    ['-O3,p', '-inline auto,deferred'],
    ['-fp_contract off', '-inline auto,deferred'],
]


def total_misalign():
    r = subprocess.run(['build/tools/objdiff-cli', 'diff', '-p', '.', '-u', 'main/' + UNIT,
                        '--format', 'json', '-o', '-'], capture_output=True, text=True)
    try:
        d = json.loads(r.stdout)
    except Exception:
        return None
    tot = 0
    for s in d['left'].get('symbols', []):
        if 'instructions' not in s:
            continue
        tot += sum(1 for row in s['instructions']
                   if row.get('diff_kind') not in (None, 'DIFF_NONE', 'DIFF_ARG_MISMATCH'))
    return tot


def reconfig_build():
    c = subprocess.run(['python3', CFG, '-v', 'GCCP01'], capture_output=True, text=True)
    if c.returncode != 0:
        return 'CONFIGFAIL:' + (c.stderr or c.stdout)[-200:]
    b = subprocess.run(['ninja'], capture_output=True, text=True)
    if b.returncode != 0:
        return 'BUILDFAIL:' + (b.stderr or b.stdout)[-200:]
    return None


def set_extra_cflags(orig_src, flags):
    """Return modified configure.py text with the Object(...,"SRC"...) extra_cflags set."""
    s = orig_src
    # find the Object(...) call containing the quoted SRC basename
    idx = s.find('"' + SRC + '"')
    if idx < 0:
        return None
    # find the enclosing Object( ... ) — search back for 'Object(' and forward for matching ')'
    start = s.rfind('Object(', 0, idx)
    # find matching close paren
    depth = 0
    i = start + len('Object')
    while i < len(s):
        if s[i] == '(':
            depth += 1
        elif s[i] == ')':
            depth -= 1
            if depth == 0:
                break
        i += 1
    call = s[start:i + 1]
    flagstr = ', '.join('"%s"' % f for f in flags)
    if 'extra_cflags' in call:
        newcall = re.sub(r'extra_cflags\s*=\s*\[[^\]]*\]', 'extra_cflags=[%s]' % flagstr, call)
    else:
        # insert before the closing paren
        newcall = call[:-1].rstrip()
        if not newcall.endswith(','):
            newcall += ','
        newcall += ' extra_cflags=[%s])' % flagstr
    return s[:start] + newcall + s[i + 1:]


def main():
    orig = open(CFG).read()
    # baseline
    err = reconfig_build()
    if err:
        print('baseline build failed:', err); return
    base = total_misalign()
    print(f'{UNIT}: baseline total structural misalign = {base}')
    results = [('<baseline>', base)]
    try:
        for flags in CANDIDATES:
            mod = set_extra_cflags(orig, flags)
            if mod is None:
                print('  could not locate Object for', SRC); break
            open(CFG, 'w').write(mod)
            err = reconfig_build()
            if err:
                print(f'  {flags}: {err[:60]}')
                continue
            m = total_misalign()
            tag = ' <== BETTER' if m is not None and m < base else ''
            print(f'  {str(flags):55} misalign={m}{tag}')
            results.append((str(flags), m))
    finally:
        open(CFG, 'w').write(orig)
        reconfig_build()
    results = [r for r in results if r[1] is not None]
    results.sort(key=lambda x: x[1])
    print('\nBEST:')
    for name, m in results[:5]:
        print(f'  {m:5}  {name}')


if __name__ == '__main__':
    main()
