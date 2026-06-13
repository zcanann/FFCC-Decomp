#!/usr/bin/env python3
"""asm_match.py - decomp matching helper for FFCC-Decomp.

Usage:
  # list every code symbol in a unit with its match %, worst first
  python3 /private/tmp/asm_match.py <worktree_dir> <unit>

  # show an index-aligned TARGET(original) vs OURS(current build) asm diff for one
  # function, with only mismatching regions printed (plus context). <sym> is a
  # substring match against the (possibly mangled) symbol name.
  python3 /private/tmp/asm_match.py <worktree_dir> <unit> <sym> [context]

Notes:
  - TARGET = the original/goal object (does NOT change when you edit source).
  - OURS   = compiled from current source (this is what your edits move).
  - Lines flagged ">>" carry a diff_kind (a real, counted mismatch). Branch-offset
    differences without a diff_kind are just layout and are NOT penalized.
  - DIFF_ARG_MISMATCH = identical opcode, different operand (usually register
    allocation / a wrong local lifetime / wrong type). These ARE source-fixable.
  - <none> on one side = an insert/delete (instruction count diverged).
Run objdiff-cli first via this tool; it shells out to build/tools/objdiff-cli.
"""
import json, subprocess, sys, os

def get_diff(wt, unit, sym=None):
    cmd = [os.path.join(wt, "build/tools/objdiff-cli"), "diff",
           "-p", ".", "-u", unit, "-o", "-"]
    if sym:
        cmd.append(sym)
    r = subprocess.run(cmd, cwd=wt, capture_output=True, text=True)
    if r.returncode != 0 and not r.stdout:
        sys.exit(f"objdiff-cli failed:\n{r.stderr}")
    return json.loads(r.stdout)

def code_syms(side):
    return {s["name"]: s for s in side["symbols"] if s.get("instructions")}

def fmt(ins):
    if not ins:
        return "<none>"
    i = ins.get("instruction")
    if not i:
        return "<none>"
    return i.get("formatted", "<none>")

def list_funcs(d):
    L = code_syms(d["left"]); R = code_syms(d["right"])
    names = set(L) | set(R)
    rows = []
    for n in names:
        # match % lives on the section symbol entries; pull from whichever side has it
        mp = None
        for side in (d["left"], d["right"]):
            for s in side["symbols"]:
                if s["name"] == n and s.get("match_percent") is not None:
                    mp = s["match_percent"]; break
            if mp is not None: break
        sz = (L.get(n) or R.get(n) or {}).get("size", "?")
        rows.append((mp if mp is not None else -1.0, sz, n))
    rows.sort(key=lambda x: x[0])
    print(f"{'match%':>7}  {'size':>6}  symbol")
    for mp, sz, n in rows:
        print(f"{mp:7.2f}  {str(sz):>6}  {n}")

def show_diff(d, sym, ctx):
    L = code_syms(d["left"]); R = code_syms(d["right"])
    cand = [n for n in (set(L) | set(R)) if sym in n]
    if not cand:
        sys.exit(f"no symbol matching {sym!r}. Run without <sym> to list symbols.")
    name = sym if sym in cand else (max(cand, key=len) if len(cand) > 1 else cand[0])
    l = L.get(name, {}).get("instructions", [])
    r = R.get(name, {}).get("instructions", [])
    n = max(len(l), len(r))
    def diffkind(a, b):
        return (a or {}).get("diff_kind") or (b or {}).get("diff_kind")
    flagged = []
    for i in range(n):
        a = l[i] if i < len(l) else None
        b = r[i] if i < len(r) else None
        # Only diff_kind lines are real, scored mismatches. Pure branch-target
        # offset differences (no diff_kind) are layout and objdiff ignores them.
        if diffkind(a, b) is None and a is not None and b is not None:
            continue
        flagged.append(i)
    keep = set()
    for i in flagged:
        for j in range(i - ctx, i + ctx + 1):
            if 0 <= j < n: keep.add(j)
    print(f"# {name}")
    print(f"# TARGET(original) | OURS(current)   flagged lines = {len(flagged)} of {n}")
    last = -2
    for i in range(n):
        if i not in keep:
            continue
        if i != last + 1:
            print("        ...")
        a = l[i] if i < len(l) else None
        b = r[i] if i < len(r) else None
        dk = (a or {}).get("diff_kind") or (b or {}).get("diff_kind")
        is_flag = dk is not None or a is None or b is None
        mark = ">>" if is_flag else "  "
        tag = f" [{dk}]" if dk else (" [INS/DEL]" if (a is None or b is None) else "")
        print(f"{mark}{i:5} {fmt(a):34} | {fmt(b):34}{tag}")
        last = i

def main():
    if len(sys.argv) < 3:
        print(__doc__); sys.exit(1)
    wt, unit = sys.argv[1], sys.argv[2]
    sym = sys.argv[3] if len(sys.argv) > 3 else None
    ctx = int(sys.argv[4]) if len(sys.argv) > 4 else 3
    d = get_diff(wt, unit, sym)
    if sym:
        show_diff(d, sym, ctx)
    else:
        list_funcs(d)

if __name__ == "__main__":
    main()
