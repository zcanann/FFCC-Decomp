#!/usr/bin/env python3
"""
Generic brute-force source permuter for FFCC-Decomp (MWCC / GameCube).

Unlike decomp-permuter (which mutates a single function's C and re-assembles),
this tool drives the project's real ninja build + objdiff report, so every
candidate it scores is guaranteed to compile, link (main.dol produced) and be
measured with the *exact* same fuzzy_match_percent the project uses.

HOW IT WORKS
------------
You point it at a source file and a function (by demangled-name substring or
mangled symbol). You provide a list of "edits": each edit is a (find, replace)
pair applied to the source file. The permuter, for each candidate:

  1. writes the candidate source,
  2. runs `ninja` (recompiles the unit + regenerates build/GCCP01/report.json),
  3. reads the target function's fuzzy_match_percent from report.json,
  4. ALSO reads the unit fuzzy and project fuzzy to guarantee no regression,
  5. keeps the edit only if the function improved AND neither the unit's other
     functions nor the project-wide fuzzy regressed; otherwise reverts.

It does greedy hill-climbing: edits that help are kept (composed), edits that
hurt or break the build are reverted. Optionally random-restart ordering.

This is intentionally *build-driven* rather than asm-snippet-driven because the
register-allocation / scheduling effects we are chasing only reproduce under the
real MWCC invocation + link, and report.json is the metric the mandate cares
about.

USAGE
-----
  # List candidate edit-sets defined for a function and dry-run them:
  python3 tools/permute.py --unit main/menu_letter \
      --src src/menu_letter.cpp \
      --func LetterReplyWinOpen \
      --edits tools/permute_edits/reply_win_open.json

An edits JSON file is a list of "variants". Each variant is a list of
[find, replace] string pairs that are ALL applied together (an atomic candidate).
The permuter tries each variant independently against the pristine baseline and
keeps the single best. With --hill-climb it instead composes winning variants.

  edits.json:
  [
    { "name": "size-last-via-temp",
      "edits": [["char* srcText = new (stage, ...) char[kLetterTextScratchSize];",
                 "..."]] },
    ...
  ]

POINTING IT AT ANOTHER UNIT/FUNCTION
------------------------------------
  --unit   objdiff unit name (e.g. main/menu_favo)  -> from objdiff.json
  --src    the .cpp/.c file that defines the function
  --func   demangled-name substring OR mangled symbol; used to read the
           per-function fuzzy from report.json
  --edits  a JSON file of variants (see format above). Write these by hand for
           the specific scheduling/allocation lever you are attacking, OR use
           the built-in generators (--auto) which emit common semantics-
           preserving transforms for the whole file region around the function.

The build/score plumbing is fully generic; only the edits are unit-specific.
"""

import argparse
import json
import os
import shutil
import subprocess
import sys
import time

REPORT = "build/GCCP01/report.json"


def run_ninja(timeout=180):
    r = subprocess.run(["ninja"], capture_output=True, text=True, timeout=timeout)
    return r.returncode == 0, r.stderr + r.stdout


def read_report():
    with open(REPORT) as f:
        return json.load(f)


def project_fuzzy(rep):
    return rep["measures"]["fuzzy_match_percent"]


def unit_record(rep, unit):
    for u in rep["units"]:
        if u.get("name") == unit:
            return u
    return None


def unit_fuzzy(rep, unit):
    u = unit_record(rep, unit)
    return u["measures"]["fuzzy_match_percent"] if u else None


def func_fuzzy(rep, unit, func):
    u = unit_record(rep, unit)
    if not u:
        return None
    for fn in u.get("functions", []):
        dem = fn.get("metadata", {}).get("demangled_name", "")
        if fn["name"] == func or func in fn["name"] or func in dem:
            return fn["fuzzy_match_percent"]
    return None


def all_unit_func_fuzzies(rep, unit):
    """Map mangled-name -> fuzzy, to detect per-function regressions."""
    u = unit_record(rep, unit)
    out = {}
    if u:
        for fn in u.get("functions", []):
            out[fn["name"]] = fn["fuzzy_match_percent"]
    return out


def apply_edits(src, edits):
    out = src
    for find, replace in edits:
        if find not in out:
            return None  # edit not applicable -> invalid candidate
        out = out.replace(find, replace, 1)
    return out


def measure(src_path, content):
    """Write content, build, return (ok, report) or (False, errmsg)."""
    with open(src_path, "w") as f:
        f.write(content)
    ok, log = run_ninja()
    if not ok:
        return False, log
    return True, read_report()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--unit", required=True)
    ap.add_argument("--src", required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--edits", required=True, help="JSON file of variants")
    ap.add_argument("--hill-climb", action="store_true",
                    help="compose winning variants instead of best-single")
    ap.add_argument("--keep-best", action="store_true",
                    help="leave the best variant written to the source on exit")
    args = ap.parse_args()

    with open(args.src) as f:
        baseline_src = f.read()
    with open(args.edits) as f:
        variants = json.load(f)

    # Establish baseline metrics.
    ok, rep = measure(args.src, baseline_src)
    if not ok:
        print("BASELINE BUILD FAILED:\n", rep[-2000:])
        sys.exit(1)
    base_func = func_fuzzy(rep, args.unit, args.func)
    base_unit = unit_fuzzy(rep, args.unit)
    base_proj = project_fuzzy(rep)
    base_funcs = all_unit_func_fuzzies(rep, args.unit)
    print(f"BASELINE  func={base_func:.4f}  unit={base_unit:.4f}  project={base_proj:.4f}")
    print(f"Testing {len(variants)} variants on {args.func}\n")

    current_src = baseline_src
    cur_func, cur_unit, cur_proj = base_func, base_unit, base_proj
    cur_funcs = base_funcs
    best_src = baseline_src
    best_func = base_func
    accepted = []

    EPS = 1e-6
    t0 = time.time()
    try:
        for i, v in enumerate(variants):
            name = v.get("name", f"variant{i}")
            cand = apply_edits(current_src if args.hill_climb else baseline_src, v["edits"])
            if cand is None:
                print(f"[{i+1}/{len(variants)}] {name}: SKIP (edit not applicable)")
                continue
            ok, rep = measure(args.src, cand)
            if not ok:
                print(f"[{i+1}/{len(variants)}] {name}: BUILD FAIL")
                continue
            f = func_fuzzy(rep, args.unit, args.func)
            un = unit_fuzzy(rep, args.unit)
            pj = project_fuzzy(rep)
            funcs = all_unit_func_fuzzies(rep, args.unit)

            # Regression guard: no OTHER function in unit may drop; project may not drop.
            regressed = []
            for k, vbase in base_funcs.items():
                if k == args.func or args.func in k:
                    continue
                if funcs.get(k, vbase) < vbase - EPS:
                    regressed.append((k, vbase, funcs.get(k)))
            proj_regress = pj < base_proj - EPS

            tag = ""
            ref = cur_func if args.hill_climb else base_func
            improved = f > ref + EPS
            if improved and not regressed and not proj_regress:
                tag = " *** ACCEPT ***"
                if args.hill_climb:
                    current_src = cand
                    cur_func, cur_unit, cur_proj, cur_funcs = f, un, pj, funcs
                    accepted.append(name)
                if f > best_func + EPS:
                    best_func = f
                    best_src = cand
            elif improved and (regressed or proj_regress):
                tag = f" REJECT(regress proj={proj_regress} fns={regressed[:2]})"
            print(f"[{i+1}/{len(variants)}] {name}: func={f:.4f} unit={un:.4f} proj={pj:.4f}{tag}")
            if f >= 100.0 - EPS and not regressed and not proj_regress:
                print("*** 100% MATCH ***")
                best_src = cand
                best_func = f
                break
    except KeyboardInterrupt:
        print("\nInterrupted.")

    final_src = best_src if args.keep_best else baseline_src
    with open(args.src, "w") as f:
        f.write(final_src)
    measure(args.src, final_src)  # restore build state consistent with source

    print(f"\n{'='*60}")
    print(f"Done in {(time.time()-t0)/60:.1f} min")
    print(f"baseline func={base_func:.4f}  best func={best_func:.4f}  (+{best_func-base_func:.4f})")
    if args.hill_climb:
        print("accepted:", accepted)
    if args.keep_best and best_func > base_func + EPS:
        print(f"BEST variant left written to {args.src}")
    else:
        print("Source restored to baseline.")


if __name__ == "__main__":
    main()
