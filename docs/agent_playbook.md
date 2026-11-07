# Agent playbook — the shortest path from a residual diff to a landed score

Written from 45 automated loop jobs on this repository (11 produced a landed delta). It assumes you
have already read [`AGENTS.md`](../AGENTS.md) and the lever catalog in [`WORK_SPLIT.md`](../WORK_SPLIT.md);
this file is about *how to work fast*, not about what the code should look like.

## 1. Measure one object, not the project

The single biggest difference between a job that lands a delta and one that does not is how many
measured experiments it fits in its budget. Numbers measured on this machine:

| what | command | cost |
|---|---|---|
| one translation unit | `ninja build/GCCP01/src/<file>.o` | ~1.5 s |
| unit score, no report | `build/tools/objdiff-cli diff -p . -u <unit> -o -` then read `.left.sections[] | select(.name==".text").match_percent` | ~0.1 s |
| project report | `ninja` (steady state) | ~1–3 s per touched TU |
| switching region | `python3 configure.py --version <V>` | **~38 s**, and it invalidates every edge |

`objdiff-cli`'s `.text` `match_percent` for a unit equals that unit's `fuzzy_match_percent` in
`build/<version>/report.json` (verified exact on several units), so it is a valid gate for a search
loop. For cross-region work, make one clone per region and configure each once — never switch
regions inside the measurement loop.

Two traps that cost other agents real time:

- A **failed build leaves a stale `report.json`** (the units list comes back empty). Check the build's
  exit status before you read a score, otherwise you measure noise or crash on a `KeyError`.
- Switching regions mid-experiment silently rebuilds everything; if a measurement suddenly takes 40 s
  instead of 2 s, that is why.

## 2. Classify the residual before you touch the source (5 minutes, saves hours)

Dump the whole-unit diff and bucket it. The bucket tells you which lever can possibly work:

| what the diff shows | what it is | what to do |
|---|---|---|
| `@NNN` vs a named pool symbol, same address and bytes | cosmetic anon-pool noise | ignore; zero score weight |
| same opcodes, same order, only register numbers differ | register-allocation wall | live-range / value-form edits, not declaration order |
| one instruction pair exchanged, same count, same frame | rank swap (GPR or FPR) | move the *first use* of one of the two values |
| extra or missing instructions/blocks | real source gap | fix this first — biggest wins |
| independent statements emitted in a different order | scheduling | statement/declaration order permutation |

`tools/classify_diff.py` buckets a unit; `tools/unit_funcs.py` lists the functions to attack.

## 3. Levers ranked by measured hit rate

From the loop campaign (45 jobs, 11 landed):

1. **Address/index form.** Rewrite a pointer walk as the array subscript the retail build folds:
   `CClass* cls = m_classes; cls += idx; cls->table[i]` → `m_classes[idx].table[i]` gives
   `addi r0,r4,0x24; lwzx` instead of `add r4,r4,r0; lwz` (cflat_runtime `objectFrame` 99.700→99.725).
2. **Live range of an induction pointer.** Assign it where it is first read, not in the loop header,
   so its live range starts where retail's does (pppScreenBreak `InitPieceData` 99.49→100: one
   statement moved, the r27/r28 pair snapped into place).
3. **Split a shared value into two reads.** The retail build often keeps two temporaries where the
   decomp caches one; two locals reading the same field can be the pair the allocator wanted
   (pppCrystal2 `pppRenderCrystal2` 99.90→100).
4. **Give a second scan its own counter.** A counter reused across two loops is usually decompiler
   economy; `int j` for the second scan is source-plausible and moves the saved-register ring
   (p_chara `correctLoadAnimAmem` 99.30→99.47).
5. **Bind a repeatedly-reloaded global base to a local** (declaration and assignment split is the
   documented MWCC idiom) — map `ReadMid` 99.747→99.880.
6. **Loop-scope float declaration order** — only for FPR webs, and only after 1–5 are exhausted.
   It can conflict across regions (see §5); ringmenu `onDraw` 98.931→99.127, menu_letter 95.843→95.874.
7. **Type erasure at the use site** (`void*` handle cast at the draw call) to control spill-slot
   assignment — pppYmMegaBirthShpTail3 99.991→100. Justify it by byte-exactness and say so.
8. **Statement-order permutation** of independent statements — the cheapest way to rotate FPR
   numbering, but re-sweep only after a structural change.
9. **`tools/permute2.py`** on a single function (a real win on pppCrystal2 after the manual guess
   failed); `tools/permute_fn.py` for signedness/width sweeps (no wins in this campaign, one pass max).

## 4. Sweeps: automate them or do not start one

By hand you get ~10 candidates per turn; a script gets 400+ in five minutes. Write one loop that
mutates, builds the object, scores it, and keeps the best:

```sh
# skeleton: same shape as the scripts that found p_chara and ringmenu deltas
for cand in "$@"; do ... ; ninja build/GCCP01/src/unit.o >/dev/null || continue
  score=$(build/tools/objdiff-cli diff -p . -u <unit> -o - | python3 -c 'import json,sys;print([s["match_percent"] for s in json.load(sys.stdin)["left"]["sections"] if s["name"]==".text"][0])')
```

Lock the best score, keep the best source in a variable (not in git), and stop after N consecutive
failures. Random restarts plus a hill climb beat a single greedy pass. If a candidate produces a
**bit-identical object** the axis is dead for that function — check `md5` of the `.o` and move on
instead of measuring it.

## 5. Regions are a hard gate

A change must leave the unit's fuzzy score `>=` its baseline in **GCCP01, GCCE01 and GCCJGC**, and
must not change any other unit's score in any region. The automated driver enforces this and will
throw the work away otherwise.

- Many units compile different code per region under `#ifdef VERSION_GCCJGC`, so register pressure
  differs; a PAL/EN win can regress Japan (ringmenu `onDraw` did). Measure the unit in the other
  regions *early*, before investing an hour.
- Do **not** add a region `#ifdef` to change codegen. Region ifdefs exist for behavioural
  differences; a per-region declaration order is compiler coaxing and will be rejected.
- If no source variant satisfies all three regions, revert and report the conflict. That is a
  legitimate outcome, and the unit gets parked.

## 6. Working style

- Work the whole budget. An agent that stops after five minutes typically lands nothing; the same
  agent nudged for two more turns did 20–50 measured cycles per turn.
- Keep the tree clean and commits small: commit as soon as a candidate measures better, so a later
  dead end costs one `git checkout`.
- Scratch scripts and dumps go in `/tmp`, never in the repo. Do not `git add -A`.
- Report evidence a reviewer can check: per-function before → after, per-region unit rows, the dead
  ends you measured and reverted, and what you did **not** check.
