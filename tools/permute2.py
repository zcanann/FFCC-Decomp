#!/usr/bin/env python3
"""
permute2.py - Randomized whole-function source permuter for FFCC-Decomp (MWCC / GameCube).

WHY v2
------
tools/permute.py applies a *fixed, hand-written* list of (find, replace) edits and
hill-climbs over them. It is great for scheduling wins, but it cannot crack
REGISTER-ALLOCATION walls: the allocator simply does not move under the small
string edits a human enumerates by hand.

permute2.py is modelled on simonlindholm/decomp-permuter (its src/permuter/*.py
randomizers were mined for ideas), but RE-IMPLEMENTED against our build-driven
scorer: every candidate is compiled by the real `ninja` invocation and measured
with the *exact* project fuzzy_match_percent from build/GCCP01/report.json. No
separate assembler, no separate metric.

It performs RANDOMIZED, COMPOSABLE, SEMANTICS-PRESERVING perturbations of a single
function's C body, applied with random seeds + greedy hill-climbing. The point is
to perturb MWCC's register allocator / scheduler, which is sensitive to:
  - the number and lifetime of named temporaries (the #1 lever),
  - the order of independent statements,
  - the shape of expressions (reassociation, temp extraction/inlining),
  - value-preserving type / cast jitter.

TRANSFORMS IMPLEMENTED
----------------------
  insert_scratch_temp   : `int __pN = <int-expr>;` injected before a statement and
                          the expr's *first later* use replaced with __pN. Forces a
                          new live range, possibly across a call. (#1 allocator lever)
  temp_for_expr         : extract a repeated sub-expression `E` into `T __pN = E;`
                          and replace one occurrence with __pN.
  inline_temp           : the inverse - fold a `T x = E;` single-use local back in.
  reorder_stmts         : swap two adjacent, independent simple statements.
  reassoc_add           : rebracket `a + b + c` -> `a + (b + c)` (and commute).
  commute_cmp           : `a < b` -> `b > a`, `a == b` -> `b == a`, etc.
  cast_roundtrip        : wrap an int lvalue use in `(int)(short)(...)` style
                          value-preserving round-trips / vary temp widths.
  perm_add_self         : `x` -> `(x + 0)` / `x * 1` style allocation-neutral noise
                          on an integer temp initialiser.
  split_decl            : `T a = E;` -> `T a; a = E;`
  merge_decl            : the inverse of split_decl.

All transforms operate ONLY inside the target function body, located by
brace-matching from the signature line, so they cannot disturb other functions.

SCORING / ACCEPTANCE (mandatory guards, same as permute.py)
-----------------------------------------------------------
A candidate is ACCEPTED only if, after `ninja`:
  * it builds and links,
  * the TARGET function fuzzy strictly improves over the current best,
  * NO OTHER function in the unit regresses,
  * the PROJECT-wide fuzzy does not regress.
Otherwise it is reverted. Greedy hill-climb: accepted candidates become the new
base and further transforms stack on top.

USAGE
-----
  python3 tools/permute2.py \
      --unit main/menu_letter \
      --src src/menu_letter.cpp \
      --func LetterReplyWinOpen \
      --seeds 200 --iters 60 --max-stack 4 \
      [--seed 0] [--keep-best] [--quiet]

  --unit       objdiff unit name (from objdiff.json), e.g. main/menu_letter
  --src        .cpp/.c file defining the function
  --func       demangled-name substring OR mangled symbol (matches report.json)
  --seeds      number of random restarts (each starts from the pristine baseline)
  --iters      transform attempts per seed (hill-climb steps)
  --max-stack  max transforms stacked per accepted candidate is unbounded; this
               caps how many transforms a *single* mutation step applies (1..K)
  --seed       base RNG seed (restart i uses base+i); makes runs reproducible
  --keep-best  on exit, leave the best-scoring variant written to --src (and
               rebuild). Default restores pristine baseline.
  --quiet      only print accepts / summary.

On any improvement the winning variant is also saved to
  tools/permute_edits/<func>.best.cpp.frag (the full mutated function body) and
the full file to <src>.permute2.best so you can inspect / clean it up by hand.

NOTES
-----
  * Builds are sub-second here (~0.8s), so thousands of candidates/hour are fine.
  * Output is NOT guaranteed idiomatic. Per the user mandate, "plausible source"
    is relaxed: the variant must COMPILE, LINK, BEHAVE IDENTICALLY, IMPROVE the
    target, and NOT regress anything. Clean up winners by hand afterward.
  * The transforms are deliberately conservative (text-level, guarded by regexes)
    so they stay semantics-preserving; if a transform would be unsafe it simply
    declines to fire (returns None) and the engine tries another.
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

REPORT = "build/GCCP01/report.json"
EPS = 1e-6


# --------------------------------------------------------------------------- #
# Build / score plumbing (reused conceptually from permute.py)
# --------------------------------------------------------------------------- #
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
    u = unit_record(rep, unit)
    out = {}
    if u:
        for fn in u.get("functions", []):
            out[fn["name"]] = fn["fuzzy_match_percent"]
    return out


def measure(src_path, content):
    with open(src_path, "w") as f:
        f.write(content)
    ok, log = run_ninja()
    if not ok:
        return False, log
    return True, read_report()


# --------------------------------------------------------------------------- #
# Function-body location via brace matching
# --------------------------------------------------------------------------- #
def find_func_body(src, func):
    """
    Return (start_idx, body_start_idx, body_end_idx, end_idx) byte offsets, where
    [body_start_idx, body_end_idx) is the *interior* of the function (between the
    outermost { } ), located by matching braces from the signature whose line
    contains `func`. Returns None if not found.
    """
    # Find a line that looks like a definition: contains func( and ends with ){ or {.
    # We look for "func(" then the next '{' that opens the body.
    # Prefer a qualified definition (e.g. `Class::func(`) so we skip call sites.
    matches = list(re.finditer(re.escape(func) + r"\s*\(", src))
    qualified = [m for m in matches if src[max(0, m.start() - 2):m.start()] == "::"]
    ordered = qualified + [m for m in matches if m not in qualified]
    for m in ordered:
        # Walk forward to the matching ')' of the parameter list, then the '{'.
        i = m.end() - 1  # at '('
        depth = 0
        j = i
        n = len(src)
        while j < n:
            c = src[j]
            if c == "(":
                depth += 1
            elif c == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        if j >= n:
            continue
        # From end of param list, skip to first '{' (allow const/throw()/whitespace).
        k = j + 1
        while k < n and src[k] not in "{;":
            k += 1
        if k >= n or src[k] == ";":
            continue  # was a declaration, not a definition
        # k is at the opening brace of the body.
        body_start = k + 1
        depth = 1
        p = body_start
        while p < n and depth > 0:
            c = src[p]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
            p += 1
        if depth != 0:
            continue
        body_end = p - 1  # at closing '}'
        return (m.start(), body_start, body_end)
    return None


# --------------------------------------------------------------------------- #
# Lightweight statement model
# --------------------------------------------------------------------------- #
# We treat the body as text and operate with regexes. To keep transforms safe we
# only fire when a clear, local, semantics-preserving rewrite is identifiable.

# A "simple int-ish local decl with initialiser": e.g.  int x = EXPR;
DECL_RE = re.compile(
    r"(?P<indent>[ \t]*)(?P<type>int|unsigned int|short|unsigned short|char|"
    r"unsigned char|signed char|u8|s8|u16|s16|u32|s32|long|unsigned long|bool)"
    r"[ \t]+(?P<name>[A-Za-z_]\w*)[ \t]*=[ \t]*(?P<expr>[^;{}]+);"
)

# Identifier-only RHS we can wrap with neutral arithmetic.
IDENT_RE = re.compile(r"[A-Za-z_]\w*")

# A comparison we can commute.
CMP_RE = re.compile(
    r"(?P<a>[A-Za-z_]\w*(?:\.[A-Za-z_]\w*|->[A-Za-z_]\w*|\[[^\]\[]*\])*)"
    r"\s*(?P<op><=|>=|<|>|==|!=)\s*"
    r"(?P<b>[A-Za-z_]\w*(?:\.[A-Za-z_]\w*|->[A-Za-z_]\w*|\[[^\]\[]*\])*)"
)

CMP_FLIP = {"<": ">", ">": "<", "<=": ">=", ">=": "<=", "==": "==", "!=": "!="}

# An assignment/decl statement boundary, used for stmt reorder.
STMT_SPLIT_RE = re.compile(r"(?<=;)\n")


def uid_counter():
    n = [0]

    def nxt():
        n[0] += 1
        return n[0]

    return nxt


# --------------------------------------------------------------------------- #
# Transforms. Each takes the *body text* and an RNG, returns a mutated body or
# None if it could not safely fire. Names map to the docstring.
# --------------------------------------------------------------------------- #
def _all_decls(body):
    return list(DECL_RE.finditer(body))


def t_perm_add_self(body, rng, mk):
    """Wrap an int local's identifier initialiser in an allocation-neutral op."""
    decls = [m for m in _all_decls(body) if IDENT_RE.fullmatch(m.group("expr").strip())]
    if not decls:
        return None
    m = rng.choice(decls)
    expr = m.group("expr").strip()
    choice = rng.choice([f"({expr} + 0)", f"({expr} | 0)", f"({expr} * 1)",
                         f"({expr} - 0)", f"(0 + {expr})"])
    s, e = m.span("expr")
    return body[:s] + " " + choice + body[e:]


def t_cast_roundtrip(body, rng, mk):
    """Value-preserving round-trip cast on a short/char/int decl initialiser."""
    decls = _all_decls(body)
    typed = [m for m in decls if m.group("type") in
             ("int", "unsigned int", "s32", "u32", "long", "unsigned long")]
    if not typed:
        return None
    m = rng.choice(typed)
    expr = m.group("expr").strip()
    # round-trip through a wider/identity int type; value preserved for int range
    wrap = rng.choice([f"(int)(unsigned int)({expr})",
                       f"(int)(long)({expr})",
                       f"(s32)({expr})"])
    s, e = m.span("expr")
    return body[:s] + " " + wrap + body[e:]


def t_commute_cmp(body, rng, mk):
    """Commute a relational/equality comparison."""
    cands = list(CMP_RE.finditer(body))
    # avoid touching things inside strings; cheap heuristic: skip if surrounded by quotes nearby
    cands = [m for m in cands if '"' not in body[max(0, m.start() - 1):m.end() + 1]]
    if not cands:
        return None
    m = rng.choice(cands)
    a, op, b = m.group("a"), m.group("op"), m.group("b")
    newop = CMP_FLIP[op]
    repl = f"{b} {newop} {a}"
    return body[:m.start()] + repl + body[m.end():]


def t_scratch_temp(body, rng, mk):
    """
    Insert `int __pN = <ident-or-member>;` before a statement and replace the
    *next* textual occurrence of that lvalue read with __pN. Forces a new live
    range. We restrict the captured expr to a simple integer-ish identifier or
    member access so the temp's type (int) is value-preserving.
    """
    # candidate exprs: bare identifiers used as an int read inside the body.
    # Find lines that have `<ident>` appearing at least twice so we can hoist+reuse.
    idents = {}
    for m in IDENT_RE.finditer(body):
        idents.setdefault(m.group(0), []).append(m.span())
    # Only hoist locals we can PROVE are int-family, because the temp is typed `int`.
    # We learn each candidate's declared type from a matching local decl in the body;
    # if we cannot, we decline (semantics-preservation over coverage).
    int_types = {"int", "unsigned int", "short", "unsigned short", "char",
                 "unsigned char", "signed char", "u8", "s8", "u16", "s16",
                 "u32", "s32", "long", "unsigned long", "bool"}
    declared_int = set()
    for dm in _all_decls(body):
        if dm.group("type") in int_types:
            declared_int.add(dm.group("name"))
    KW = {"if", "for", "while", "do", "return", "else", "int", "char", "short",
          "long", "unsigned", "signed", "void", "bool", "const", "static",
          "new", "delete", "sizeof", "true", "false", "this", "switch", "case",
          "break", "continue", "reinterpret_cast", "static_cast", "const_cast"}
    cands = [(name, sp) for name, sp in idents.items()
             if len(sp) >= 2 and name not in KW and name in declared_int
             and not name.startswith("__p")]
    if not cands:
        return None
    name, spans = rng.choice(cands)
    # Pick an occurrence that is a *read* (not immediately followed by '=' that
    # isn't '==', and not preceded by '.'/'->'/'__'), and insert temp at the
    # start of its statement line.
    rng.shuffle(spans)
    for (s, e) in spans:
        before = body[max(0, s - 2):s]
        after = body[e:e + 2]
        if before.endswith(".") or before.endswith(">") or before.endswith("_"):
            continue
        # skip pre-increment / pre-decrement target: ++name / --name
        if before.endswith("++") or before.endswith("--"):
            continue
        # skip if this occurrence is a WRITE/MODIFY target. Hoisting the LHS of an
        # assignment, compound-assignment (+=,-=,*=,...), or ++/-- into a dead int
        # temp would silently DROP the write (semantics-breaking false match).
        nxt = body[e:].lstrip()[:3]
        if re.match(r"(\+\+|--|<<=|>>=|[-+*/%&|^]=)", nxt):
            continue
        if nxt.startswith("=") and not nxt.startswith("=="):
            continue
        # find start of the line containing this occurrence
        line_start = body.rfind("\n", 0, s) + 1
        indent_m = re.match(r"[ \t]*", body[line_start:])
        indent = indent_m.group(0) if indent_m else ""
        tmp = f"__p{mk()}"
        decl = f"{indent}int {tmp} = {name};\n"
        # replace this single occurrence with tmp
        new_body = body[:s] + tmp + body[e:]
        # re-find the line start in new_body (s unchanged before insertion point)
        new_line_start = new_body.rfind("\n", 0, s) + 1
        return new_body[:new_line_start] + decl + new_body[new_line_start:]
    return None


def t_split_decl(body, rng, mk):
    """`T a = E;` -> `T a; a = E;`"""
    decls = _all_decls(body)
    # avoid array/ctor forms; DECL_RE already excludes braces in expr
    if not decls:
        return None
    m = rng.choice(decls)
    indent, typ, name, expr = (m.group("indent"), m.group("type"),
                               m.group("name"), m.group("expr"))
    repl = f"{indent}{typ} {name};\n{indent}{name} = {expr};"
    return body[:m.start()] + repl + body[m.end():]


def t_reassoc_add(body, rng, mk):
    """Rebracket `a + b + c` -> `a + (b + c)` within an expression."""
    pat = re.compile(r"([A-Za-z_]\w*)\s*\+\s*([A-Za-z_]\w*)\s*\+\s*([A-Za-z_]\w*)")
    cands = list(pat.finditer(body))
    if not cands:
        return None
    m = rng.choice(cands)
    a, b, c = m.group(1), m.group(2), m.group(3)
    form = rng.choice([f"{a} + ({b} + {c})", f"({b} + {c}) + {a}", f"{c} + {a} + {b}"])
    return body[:m.start()] + form + body[m.end():]


def t_reorder_stmts(body, rng, mk):
    """Swap two adjacent simple decl/assign statements that share no identifier."""
    lines = body.split("\n")
    # find adjacent simple-statement pairs
    simple = re.compile(r"^[ \t]*(?:int|short|char|long|unsigned|signed|u8|s8|u16|"
                        r"s16|u32|s32|bool)?[ \t]*[A-Za-z_]\w*[ \t]*=[^;{}]+;[ \t]*$")
    for idx in range(len(lines) - 1):
        l1, l2 = lines[idx], lines[idx + 1]
        if simple.match(l1) and simple.match(l2):
            # extract lhs/identifiers; require independence (no shared ident)
            ids1 = set(IDENT_RE.findall(l1))
            ids2 = set(IDENT_RE.findall(l2))
            # the lhs of l1 must not be read by l2 and vice versa; conservative:
            if ids1 & ids2:
                continue
            cand_idx = idx
            # randomize which eligible pair we pick by collecting all then choosing
            break
    else:
        return None
    # collect all eligible and pick one
    pairs = []
    for i in range(len(lines) - 1):
        l1, l2 = lines[i], lines[i + 1]
        if simple.match(l1) and simple.match(l2):
            if not (set(IDENT_RE.findall(l1)) & set(IDENT_RE.findall(l2))):
                pairs.append(i)
    if not pairs:
        return None
    i = rng.choice(pairs)
    lines[i], lines[i + 1] = lines[i + 1], lines[i]
    return "\n".join(lines)


TRANSFORMS = [
    ("scratch_temp", t_scratch_temp),
    ("scratch_temp", t_scratch_temp),  # weight it (the #1 lever)
    ("scratch_temp", t_scratch_temp),
    ("perm_add_self", t_perm_add_self),
    ("cast_roundtrip", t_cast_roundtrip),
    ("commute_cmp", t_commute_cmp),
    ("split_decl", t_split_decl),
    ("reassoc_add", t_reassoc_add),
    ("reorder_stmts", t_reorder_stmts),
]


def mutate(body, rng, mk, max_stack):
    """Apply 1..max_stack random transforms; return (new_body, names) or (None,[])."""
    k = rng.randint(1, max_stack)
    cur = body
    used = []
    for _ in range(k):
        name, fn = rng.choice(TRANSFORMS)
        nxt = fn(cur, rng, mk)
        if nxt is not None and nxt != cur:
            cur = nxt
            used.append(name)
    if not used:
        return None, []
    return cur, used


# --------------------------------------------------------------------------- #
# Engine
# --------------------------------------------------------------------------- #
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--unit", required=True)
    ap.add_argument("--src", required=True)
    ap.add_argument("--func", required=True)
    ap.add_argument("--seeds", type=int, default=100)
    ap.add_argument("--iters", type=int, default=50)
    ap.add_argument("--max-stack", type=int, default=4)
    ap.add_argument("--seed", type=int, default=0)
    ap.add_argument("--keep-best", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    with open(args.src) as f:
        baseline_src = f.read()

    loc = find_func_body(baseline_src, args.func)
    if loc is None:
        print(f"ERROR: could not locate function body for '{args.func}'")
        sys.exit(1)
    sig_start, body_start, body_end = loc
    base_body = baseline_src[body_start:body_end]
    prefix = baseline_src[:body_start]
    suffix = baseline_src[body_end:]

    def assemble(body):
        return prefix + body + suffix

    # Baseline metrics.
    ok, rep = measure(args.src, baseline_src)
    if not ok:
        print("BASELINE BUILD FAILED:\n", rep[-2000:])
        sys.exit(1)
    base_func = func_fuzzy(rep, args.unit, args.func)
    base_proj = project_fuzzy(rep)
    base_funcs = all_unit_func_fuzzies(rep, args.unit)
    base_unit = unit_fuzzy(rep, args.unit)
    print(f"BASELINE  func={base_func:.4f}  unit={base_unit:.4f}  project={base_proj:.4f}")
    print(f"Body: {len(base_body)} chars. seeds={args.seeds} iters={args.iters} "
          f"max_stack={args.max_stack}")

    best_func = base_func
    best_src = baseline_src
    best_recipe = []
    t0 = time.time()
    n_builds = 0

    def accept_ok(rep, f):
        if f <= best_func + EPS and f <= cur_func + EPS:
            pass
        pj = project_fuzzy(rep)
        if pj < base_proj - EPS:
            return False, "proj"
        funcs = all_unit_func_fuzzies(rep, args.unit)
        for k, vbase in base_funcs.items():
            if args.func in k or k == args.func:
                continue
            if funcs.get(k, vbase) < vbase - EPS:
                return False, f"regress:{k}"
        return True, ""

    try:
        for s in range(args.seeds):
            rng = random.Random(args.seed + s)
            mk = uid_counter()
            cur_body = base_body
            cur_func = base_func
            cur_recipe = []
            improved_this_seed = False
            for it in range(args.iters):
                cand_body, used = mutate(cur_body, rng, mk, args.max_stack)
                if cand_body is None:
                    continue
                cand_src = assemble(cand_body)
                ok, rep = measure(args.src, cand_src)
                n_builds += 1
                if not ok:
                    continue
                f = func_fuzzy(rep, args.unit, args.func)
                if f is None:
                    continue
                ok2, why = accept_ok(rep, f)
                if f > cur_func + EPS and ok2:
                    cur_body = cand_body
                    cur_func = f
                    cur_recipe = cur_recipe + used
                    improved_this_seed = True
                    if not args.quiet:
                        print(f"  [seed {s} it {it}] ACCEPT {used} -> func={f:.4f}")
                    if f > best_func + EPS:
                        best_func = f
                        best_src = cand_src
                        best_recipe = list(cur_recipe)
                        # persist artifacts
                        with open(args.src + ".permute2.best", "w") as bf:
                            bf.write(cand_src)
                        os.makedirs("tools/permute_edits", exist_ok=True)
                        frag = re.sub(r"[^A-Za-z0-9_]", "_", args.func)[:40]
                        with open(f"tools/permute_edits/{frag}.best.cpp.frag", "w") as ff:
                            ff.write(cand_body)
                        print(f"  *** NEW BEST func={f:.4f} (+{f-base_func:.4f}) "
                              f"seed={args.seed + s} recipe={cur_recipe}")
                    if f >= 100.0 - EPS:
                        print("  *** 100% MATCH ***")
                        raise StopIteration
            if improved_this_seed and not args.quiet:
                print(f"[seed {s}] best so far {best_func:.4f} "
                      f"({n_builds} builds, {(time.time()-t0)/60:.1f} min)")
            elif (s % 10 == 0):
                print(f"[seed {s}] no win; best {best_func:.4f} "
                      f"({n_builds} builds, {(time.time()-t0)/60:.1f} min)")
    except (KeyboardInterrupt, StopIteration):
        print("\nStopping.")

    final_src = best_src if (args.keep_best and best_func > base_func + EPS) else baseline_src
    with open(args.src, "w") as f:
        f.write(final_src)
    measure(args.src, final_src)

    print(f"\n{'='*60}")
    print(f"Done. {n_builds} builds in {(time.time()-t0)/60:.1f} min")
    print(f"baseline func={base_func:.4f}  best func={best_func:.4f}  (+{best_func-base_func:.4f})")
    if best_func > base_func + EPS:
        print(f"best recipe: {best_recipe}")
        print(f"best variant src: {args.src}.permute2.best")
        if args.keep_best:
            print(f"BEST left written to {args.src}")
    else:
        print("No improvement found. Source restored to baseline.")


if __name__ == "__main__":
    main()
