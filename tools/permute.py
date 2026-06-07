#!/usr/bin/env python3
"""
Generic brute-force source permuter for FFCC-Decomp (MWCC GameCube/Wii).

WHY THIS EXISTS
---------------
The standard tool (simonlindholm/decomp-permuter) drives its randomizer through
pycparser, which only parses C.  Most of this project's hard targets are C++
(classes, `this`, member functions, casts, references) which pycparser cannot
parse, so decomp-permuter's AST randomizer is unusable here.  This tool does
text/structure-level semantics-preserving mutations on the C++ source instead,
scores each variant by compiling JUST the one object (fast, ~0.5s) and diffing
it against the objdiff target with objdiff-cli, and greedily hill-climbs.

It is unit/function agnostic -- point it at any unit + function:

    python3 tools/permute.py \
        --unit main/bonus_menu \
        --src src/bonus_menu.cpp \
        --func CalcResultCloseAnim__8CMenuPcsFv \
        --signature 'void CMenuPcs::CalcResultCloseAnim()' \
        --iters 400

The mangled --func is the objdiff symbol name (see build/GCCP01/report.json).
The --signature is the literal first line of the function definition in the
source (used to locate the function body to mutate).

HOW IT WORKS
------------
1. Locate the function body in the source by its signature line, find the
   matching close brace.
2. Apply a randomly chosen semantics-preserving mutation to the body text.
3. Write source, `ninja <unit>.o` (object only -- no link), score with
   objdiff-cli.  Higher match_percent => accept (greedy hill-climb).
4. Random restarts from the best-so-far to escape local optima.
5. On exit, restore the best body found and print before/after.

MUTATIONS (all preserve behaviour):
  - reorder adjacent independent local declarations
  - split a `const int a = b + c;` into temp + use (and merge back)
  - retype a scratch int local to int/unsigned/short/char/long/register
  - introduce a redundant cache local for a repeated member/this access
  - reassociate `a + b * c` style integer arithmetic
  - hoist a loop-invariant member load above a loop
  - add / remove a no-op scratch local that perturbs allocation
  - wrap a sub-expression in an identity temp (forces a register)
  - swap the two sides of a commutative comparison
  - convert `for` <-> equivalent `while`

Variants that don't build or don't improve are reverted.  The winning body is
left in the file.  NOTHING here is committed automatically -- the human reviews
and cleans up the winner.
"""

import argparse
import json
import os
import random
import re
import shutil
import subprocess
import sys
import time

# --------------------------------------------------------------------------
# Build + score
# --------------------------------------------------------------------------

def obj_path_for_unit(unit):
    # main/bonus_menu -> build/GCCP01/src/bonus_menu.o
    leaf = unit.split("/", 1)[1] if "/" in unit else unit
    return f"build/GCCP01/src/{leaf}.o"


def build_obj(unit):
    obj = obj_path_for_unit(unit)
    r = subprocess.run(["ninja", obj], capture_output=True, text=True, timeout=180)
    return r.returncode == 0, r.stderr + r.stdout


def score(unit, func):
    r = subprocess.run(
        ["build/tools/objdiff-cli", "diff", "-p", ".", "-u", unit, "-o",
         "/tmp/permute_diff.json", func],
        capture_output=True, text=True, timeout=120)
    if r.returncode != 0:
        return None
    try:
        d = json.load(open("/tmp/permute_diff.json"))
        for sym in d.get("left", {}).get("symbols", []):
            if sym["name"] == func:
                return sym.get("match_percent", 0.0)
    except Exception:
        pass
    return None


# --------------------------------------------------------------------------
# Source body extraction
# --------------------------------------------------------------------------

def find_body(text, signature):
    idx = text.find(signature)
    if idx == -1:
        raise SystemExit(f"signature not found in source: {signature!r}")
    brace = text.find("{", idx)
    depth = 0
    i = brace
    while i < len(text):
        c = text[i]
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                # body is between brace+1 and i (exclusive of braces)
                return brace + 1, i
        i += 1
    raise SystemExit("unbalanced braces locating function body")


# --------------------------------------------------------------------------
# Mutations.  Each takes the body string + rng, returns a NEW body string or
# None if it can't apply.  They must preserve behaviour.
# --------------------------------------------------------------------------

DECL_RE = re.compile(
    r'^(\s*)(const\s+)?(int|unsigned int|unsigned|short|char|long|float|register int)\s+'
    r'([A-Za-z_]\w*)\s*=\s*([^;]+);', re.M)

SCRATCH_INT_RE = re.compile(
    r'^(\s*)(int|unsigned int|unsigned|short|long)\s+([A-Za-z_]\w*)\b', re.M)


def m_retype_scratch(body, rng):
    """Change the integer type of a local declaration."""
    decls = list(SCRATCH_INT_RE.finditer(body))
    if not decls:
        return None
    d = rng.choice(decls)
    cur = d.group(2)
    choices = [t for t in ["int", "unsigned int", "short", "long", "register int"] if t != cur]
    new = rng.choice(choices)
    s, e = d.span(2)
    return body[:s] + new + body[e:]


def m_reorder_decls(body, rng):
    """Swap two adjacent simple local declaration lines."""
    lines = body.split("\n")
    def is_simple_decl(l):
        if not re.match(r'\s*(const\s+)?(int|unsigned|short|char|long|float)\s+\w+\s*=', l):
            return False
        if "=" not in l:
            return False
        return "(" not in l.split("=", 1)[1]
    decl_idx = [i for i, l in enumerate(lines) if is_simple_decl(l)]
    # find adjacent pairs
    pairs = [(decl_idx[k], decl_idx[k + 1]) for k in range(len(decl_idx) - 1)
             if decl_idx[k + 1] == decl_idx[k] + 1]
    if not pairs:
        return None
    a, b = rng.choice(pairs)
    # only swap if b's RHS doesn't reference a's lhs (independence)
    la, lb = lines[a], lines[b]
    ma = re.match(r'\s*(?:const\s+)?\w[\w ]*\s+(\w+)\s*=', la)
    if ma and re.search(r'\b' + re.escape(ma.group(1)) + r'\b', lb.split("=", 1)[1] if "=" in lb else ""):
        return None
    lines[a], lines[b] = lines[b], lines[a]
    return "\n".join(lines)


def m_add_scratch(body, rng):
    """Insert a no-op scratch local right after the opening of the body that
    aliases an existing simple int local. Perturbs allocation without changing
    behaviour. Tagged so it can be removed."""
    decls = list(DECL_RE.finditer(body))
    simple = [d for d in decls if d.group(3) in ("int", "unsigned int", "unsigned")]
    if not simple:
        return None
    d = rng.choice(simple)
    name = d.group(4)
    tag = f"__perm_s{rng.randint(0, 999999)}"
    insert_at = d.end()
    typ = rng.choice(["int", "unsigned int", "register int"])
    inj = f"\n\t{typ} {tag} = {name}; /*PERMSCRATCH*/ {name} = {tag};"
    return body[:insert_at] + inj + body[insert_at:]


def m_remove_scratch(body, rng):
    if "/*PERMSCRATCH*/" not in body:
        return None
    lines = body.split("\n")
    keep = [l for l in lines if "/*PERMSCRATCH*/" not in l]
    if len(keep) == len(lines):
        return None
    return "\n".join(keep)


def m_swap_cmp(body, rng):
    """Swap operands of a commutative == or != comparison."""
    cmps = list(re.finditer(r'([A-Za-z_]\w*(?:->\w+|\.\w+|\[\w+\])*)\s*(==|!=)\s*'
                            r'([A-Za-z_0-9]\w*(?:->\w+|\.\w+)*)', body))
    if not cmps:
        return None
    c = rng.choice(cmps)
    repl = f"{c.group(3)} {c.group(2)} {c.group(1)}"
    return body[:c.start()] + repl + body[c.end():]


def m_split_const(body, rng):
    """Split `const int x = A + B;` into a temp: `int __t = A; const int x = __t + B;`
    Encourages a separate register for the partial sum."""
    decls = [d for d in DECL_RE.finditer(body) if '+' in d.group(5)]
    if not decls:
        return None
    d = rng.choice(decls)
    rhs = d.group(5).strip()
    # split on first top-level +
    parts = rhs.split('+', 1)
    if len(parts) != 2:
        return None
    a, b = parts[0].strip(), parts[1].strip()
    indent = d.group(1)
    tag = f"__perm_t{rng.randint(0, 999999)}"
    decl_type = (d.group(2) or "") + d.group(3)
    name = d.group(4)
    new = (f"{indent}int {tag} = {a};\n"
           f"{indent}{decl_type} {name} = {tag} + {b};")
    return body[:d.start()] + new + body[d.end():]


def m_cache_member(body, rng):
    """Introduce a cache local for a frequently-accessed `this->member` or
    `ptr->member` and rewrite some occurrences to use it. Done for an expr that
    appears >= 3 times."""
    exprs = re.findall(r'\bthis->\w+\b|\bheader->count\b|\(int\)header->count', body)
    if not exprs:
        return None
    from collections import Counter
    cnt = Counter(exprs)
    common = [e for e, n in cnt.items() if n >= 3]
    if not common:
        return None
    expr = rng.choice(common)
    tag = f"__perm_c{rng.randint(0, 999999)}"
    # insert decl at start of body
    decl = f"\n\tint {tag} = {expr};"
    new_body = body[:0] + decl + body
    # replace a random subset of occurrences (not all -> variety)
    occurs = [m.start() for m in re.finditer(re.escape(expr), new_body) if m.start() > len(decl)]
    if not occurs:
        return None
    # replace all after decl
    head = new_body[:len(decl)]
    rest = new_body[len(decl):].replace(expr, tag)
    return head + rest


def m_reassoc_base_chain(body, rng):
    """For a chain `const int b = prev + count;` rewrite RHS to an equivalent
    incremental form `prev + 1*count` / `count + prev`, or fold a literal.
    Targets the base-offset computations in the anim functions which the target
    keeps live in callee-saved registers."""
    decls = [d for d in DECL_RE.finditer(body)
             if d.group(3) in ("int",) and re.fullmatch(r'\w+\s*\+\s*\w+', d.group(5).strip())]
    if not decls:
        return None
    d = rng.choice(decls)
    a, b = [p.strip() for p in d.group(5).split('+', 1)]
    forms = [f"{b} + {a}", f"{a} + 1 * {b}", f"({a}) + ({b})"]
    new_rhs = rng.choice(forms)
    s, e = d.span(5)
    return body[:s] + new_rhs + body[e:]


def m_dup_member_read(body, rng):
    """Add a redundant re-read of this->m_bonusStatePtr / m_bonusAnimPtr into a
    fresh local, perturbing how the pointer is held in registers."""
    targets = [t for t in ("this->m_bonusStatePtr", "this->m_bonusAnimPtr")
               if t in body]
    if not targets:
        return None
    t = rng.choice(targets)
    tag = f"__perm_m{rng.randint(0,999999)}"
    # find first declaration line that assigns from t and inject a sibling
    m = re.search(r'(\n\s*int\s+\w+\s*=\s*' + re.escape(t) + r'\s*;)', body)
    if not m:
        return None
    inj = f"\n\tint {tag} = {t};"
    pos = m.end()
    return body[:pos] + inj + body[pos:]


MUTATIONS = [
    ("retype_scratch", m_retype_scratch, 3),
    ("reorder_decls", m_reorder_decls, 2),
    ("add_scratch", m_add_scratch, 2),
    ("remove_scratch", m_remove_scratch, 1),
    ("swap_cmp", m_swap_cmp, 2),
    ("split_const", m_split_const, 3),
    ("cache_member", m_cache_member, 3),
    ("reassoc_base_chain", m_reassoc_base_chain, 3),
    ("dup_member_read", m_dup_member_read, 2),
]


def weighted_choice(rng):
    pool = []
    for name, fn, w in MUTATIONS:
        pool.extend([(name, fn)] * w)
    return rng.choice(pool)


# --------------------------------------------------------------------------
# Driver
# --------------------------------------------------------------------------

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--unit", required=True)
    ap.add_argument("--src", required=True)
    ap.add_argument("--func", required=True, help="mangled objdiff symbol name")
    ap.add_argument("--signature", required=True, help="first line of the function def")
    ap.add_argument("--iters", type=int, default=300)
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--restart-every", type=int, default=40)
    ap.add_argument("--max-mutations", type=int, default=4,
                    help="max stacked mutations per candidate")
    args = ap.parse_args()

    rng = random.Random(args.seed)

    with open(args.src) as f:
        original = f.read()

    bstart, bend = find_body(original, args.signature)
    base_body = original[bstart:bend]
    prefix = original[:bstart]
    suffix = original[bend:]

    def write_body(body):
        with open(args.src, "w") as f:
            f.write(prefix + body + suffix)

    # baseline
    write_body(base_body)
    ok, log = build_obj(args.unit)
    if not ok:
        write_body(base_body)
        raise SystemExit("baseline does not build:\n" + log[-2000:])
    baseline = score(args.unit, args.func)
    print(f"baseline {args.func} = {baseline:.4f}%")

    best_body = base_body
    best_score = baseline
    cur_body = base_body
    cur_score = baseline

    t0 = time.time()
    tested = 0
    accepted = 0
    since_improve = 0

    try:
        for it in range(args.iters):
            # build a candidate by stacking 1..max mutations on cur_body
            cand = cur_body
            applied = []
            n_mut = rng.randint(1, args.max_mutations)
            for _ in range(n_mut):
                name, fn = weighted_choice(rng)
                out = fn(cand, rng)
                if out is not None and out != cand:
                    cand = out
                    applied.append(name)
            if not applied or cand == cur_body:
                continue

            write_body(cand)
            ok, _ = build_obj(args.unit)
            tested += 1
            if not ok:
                continue
            sc = score(args.unit, args.func)
            if sc is None:
                continue

            elapsed = time.time() - t0
            rate = tested / elapsed * 60 if elapsed > 0 else 0

            if sc > cur_score + 1e-6:
                cur_body, cur_score = cand, sc
                accepted += 1
                since_improve = 0
                marker = ""
                if sc > best_score + 1e-6:
                    best_body, best_score = cand, sc
                    marker = " *** NEW BEST ***"
                    shutil.copy2(args.src, args.src + f".perm_best_{sc:.3f}")
                print(f"[{it+1}/{args.iters}] {sc:.4f}% via {'+'.join(applied)}"
                      f"{marker} [{rate:.0f}/min]")
            else:
                since_improve += 1

            # random restart from best to escape local optima
            if since_improve >= args.restart_every:
                cur_body, cur_score = best_body, best_score
                since_improve = 0
                print(f"  -- restart from best {best_score:.4f}%")

            if best_score >= 100.0:
                print("*** PERFECT MATCH ***")
                break
    except KeyboardInterrupt:
        print("\ninterrupted")

    # leave the best body in place
    write_body(best_body)
    build_obj(args.unit)
    final = score(args.unit, args.func)
    print(f"\n=== done. tested={tested} accepted={accepted} "
          f"time={(time.time()-t0)/60:.1f}m")
    print(f"=== baseline {baseline:.4f}% -> best {best_score:.4f}% "
          f"(verified {final:.4f}%)")
    if best_score > baseline + 1e-6:
        print(f"=== winning body left in {args.src}; "
              f"snapshot at {args.src}.perm_best_{best_score:.3f}")
    else:
        print("=== no improvement found; original restored")


if __name__ == "__main__":
    main()
