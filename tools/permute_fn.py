#!/usr/bin/env python3
"""
permute_fn.py - greedy brute-force matcher for FFCC-Decomp.

Mutates signedness / integer-width tokens inside a single function's source
region, rebuilds the affected object, scores the named symbol via objdiff-cli,
and keeps any mutation that strictly improves the fuzzy match percent.

Usage:
  python3 tools/permute_fn.py --unit main/chara_fur \
      --symbol '<MANGLED>' --file src/chara_fur.cpp --func <name> --passes 4
"""
import argparse, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJDIFF = os.path.join(ROOT, "build", "tools", "objdiff-cli")

def run_ninja(targets=None):
    cmd = ["ninja"] + (targets or [])
    r = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    return r.returncode == 0, r.stderr + r.stdout

def score(unit, symbol):
    """Score via objdiff-cli (fast, no full report regen)."""
    r = subprocess.run([OBJDIFF, "diff", "-p", ".", "-u", unit, "-o", "-", symbol],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        return None
    try:
        d = json.loads(r.stdout)
    except Exception:
        return None
    for s in d.get("left", {}).get("symbols", []):
        if s.get("name") == symbol:
            return s.get("match_percent")
    return None

def find_func_region(text, func):
    """Return (start, end) char offsets of the function body region."""
    pat = re.compile(r"(^|\n)[^\n;]*\b" + re.escape(func) + r"\s*\(")
    best = None
    for m in re.finditer(pat, text):
        idx = m.end()
        brace = text.find("{", idx)
        semi = text.find(";", idx)
        if brace == -1:
            continue
        if semi != -1 and semi < brace:
            continue
        best = brace
        break
    if best is None:
        return None
    depth = 0
    i = best
    while i < len(text):
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return (best, i + 1)
        i += 1
    return None

# Signedness / width toggles applied token-by-token within the region.
SIGN_MUT = [
    ("unsigned char", "signed char"), ("unsigned char", "char"),
    ("signed char", "unsigned char"),
    ("unsigned short", "short"), ("short", "unsigned short"),
    ("unsigned int", "int"), ("int", "unsigned int"),
    ("unsigned long", "long"), ("long", "unsigned long"),
    ("u8", "s8"), ("s8", "u8"),
    ("u16", "s16"), ("s16", "u16"),
    ("u32", "s32"), ("s32", "u32"),
]

def gen_candidates(region):
    seen = set()
    for src, dst in SIGN_MUT:
        pat = re.compile(r"\b" + re.escape(src) + r"\b")
        for m in pat.finditer(region):
            key = (m.start(), src, dst)
            if key in seen:
                continue
            seen.add(key)
            new = region[:m.start()] + dst + region[m.end():]
            if new != region:
                yield (f"{src}->{dst}@{m.start()}", new)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--unit", required=True)
    ap.add_argument("--symbol", required=True)
    ap.add_argument("--file", required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--passes", type=int, default=2)
    args = ap.parse_args()

    fpath = os.path.join(ROOT, args.file)
    orig_text = open(fpath).read()

    ok, log = run_ninja()
    if not ok:
        print("Baseline build FAILED:\n", log[-2000:]); sys.exit(1)
    base = score(args.unit, args.symbol)
    if base is None:
        print("Could not score symbol", args.symbol); sys.exit(1)
    print(f"Baseline {args.func}: {base:.3f}%")

    best_text = orig_text
    best_score = base

    for p in range(args.passes):
        improved = False
        region_span = find_func_region(best_text, args.func)
        if region_span is None:
            print("Could not locate function region for", args.func); break
        rs, re_ = region_span
        region = best_text[rs:re_]
        cands = list(gen_candidates(region))
        print(f"Pass {p+1}: {len(cands)} candidate mutations")
        for desc, new_region in cands:
            new_text = best_text[:rs] + new_region + best_text[re_:]
            open(fpath, "w").write(new_text)
            ok, log = run_ninja()
            if not ok:
                continue
            s = score(args.unit, args.symbol)
            if s is not None and s > best_score + 1e-6:
                print(f"  + {desc}: {best_score:.3f} -> {s:.3f}")
                best_score = s
                best_text = new_text
                improved = True
                break
        if not improved:
            print(f"Pass {p+1}: no improvement")
            break

    open(fpath, "w").write(best_text)
    run_ninja()
    final = score(args.unit, args.symbol)
    print(f"Final {args.func}: {final:.3f}% (was {base:.3f}%)")

if __name__ == "__main__":
    main()
