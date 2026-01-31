# ROBOTS.md — Agent Runbook (FFCC-Decomp)

This file is the canonical, step-by-step runbook for automated contributions to **FFCC-Decomp**.

Goal: improve match scores by editing C/C++ source, rebuilding, diffing, and submitting clean PRs when progress is real.

## Scope (current)
- **Target version:** **PAL** (`GCCP01`) — required for now.
  - Do not attempt other versions until PAL is substantially complete.

## Preconditions (one-time setup)

### 0) Repo + assets
- Repo directory (on Zac’s Mac):
  - `~/Documents/projects/FFCC-Decomp`
- Required assets are **not** in git. You must have the original files locally:
  - `orig/GCCP01/...` must exist (at minimum `orig/GCCP01/sys/main.dol`).

### 1) Tooling
- Install ninja:
  ```sh
  brew install ninja
  ```
- Project will download required helper tools during build (DTK, wibo, etc.)

### 2) Configure PAL build
From repo root:
```sh
python3 configure.py --version GCCP01
```

### 3) Build once
```sh
ninja
```
Success criteria: build completes and verifies:
- `build/GCCP01/main.dol: OK`

### 4) Objdiff CLI (optional, but recommended)
The CLI tool can be downloaded into the repo (example tag):
```sh
python3 tools/download_tool.py objdiff-cli build/tools/objdiff-cli --tag v3.0.0
```
Verify:
```sh
build/tools/objdiff-cli --version
```

---

## The contribution loop (repeatable)

### Step 1 — Pick a target unit
Pick work from the progress tracker:
- https://decomp.dev/zcanann/FFCC-Decomp

Prefer:
- units that are partially matched (30–99%)
- high-leverage units (core gameplay/system code)
- smaller, self-contained units first

Avoid:
- auto-generated units (`auto_*` in `objdiff.json`) unless you know why
- “mass refactors” that change formatting without matching improvement

Write down:
- the **unit name** (e.g. `main/chunkfile`)
- 1–3 candidate **symbols/functions** in that unit to focus on

### Step 2 — Open the relevant source
Edit the corresponding `.c/.cpp/.h` under:
- `src/`
- `include/`

Make small, explainable changes:
- types / signedness
- struct layout / padding
- inlining barriers
- control flow shape
- constant forms
- call ordering

### Step 3 — Rebuild
From repo root:
```sh
ninja
```

If build fails, fix and rebuild. Do not proceed to diffing with a broken build.

### Step 4 — Diff with objdiff (function-level, ASM-first)
Objdiff diffs **expected object** (`build/GCCP01/src/...`) vs **current object** (`build/GCCP01/obj/...`).

**Important:** Don’t treat “percent match” as magic. You should be looking at the **raw assembly**.
Match work is ultimately about making *the compiler emit the same instructions* from plausible source.

#### 4a) Find a symbol name in the expected object
Example (for `main/chunkfile`):
```sh
nm -g build/GCCP01/src/chunkfile.o | head
```
Pick a function symbol, e.g. `Align__10CChunkFileFUl`.

#### 4b) Run objdiff for that symbol (interactive ASM view)
**Note:** `objdiff-cli diff` is interactive and requires a real TTY.

Run:
```sh
build/tools/objdiff-cli diff -p . -u main/chunkfile Align__10CChunkFileFUl
```
Quit with `q`.

Interpretation:
- Use the ASM view to identify *why* it mismatches (register allocation differences, load/store ordering, constant materialization, branching shape, etc.).
- Iterate: adjust source, rebuild, re-run diff.

#### 4c) If objdiff UI is unavailable (fallback): dump ASM and diff it yourself
If you’re running headless automation (cron) or can’t use the interactive UI, you can still inspect ASM by dumping disassembly for both objects and diffing.

Tooling options:
- If the project provides a PowerPC objdump via its toolchain, use it.
- As a last resort, use whatever objdump is available, but ensure it supports PPC.

Suggested approach:
1) Identify the base + target object paths from `objdiff.json` for the unit.
2) Dump function disassembly for both.
3) Compare with `diff`.

(Exact commands depend on the available binutils/objdump in this environment.)

### Step 5 — Check progress summary
At the end of `ninja`, a progress report is printed.
Example tail:
- `All: 8.88% matched, 0.00% linked (0 / 480 files)`

Optional: generate a JSON report:
```sh
build/tools/objdiff-cli report generate -p . -o build/GCCP01/report.json -f json-pretty
```

### Step 6 — Decide whether to PR (match + plausibility)
A higher match score is **necessary but not sufficient**.

Make a PR only if **both** are true:

**A) Match improves meaningfully**
- objdiff shows real alignment improvement (not just formatting/renames)
- preferably improves one or more specific functions, not just global noise

**B) The resulting C/C++ is plausible original source**
The goal is to match what the **original FFCC authors likely wrote**, not merely to coax the compiler.

Reject/avoid changes that look like “compiler coaxing,” e.g.:
- contrived temporaries and reordering that a human wouldn’t naturally write
- intentionally odd sequencing (load x/y, store x, load z, store y/z) unless there’s strong evidence
- changes that preserve output but reduce readability without a clear original-source rationale

Prefer changes that are source-plausible:
- fixing signedness / types to match ABI expectations
- using idiomatic control flow the codebase uses elsewhere
- removing obviously redundant variables/branches
- matching struct/field semantics (names and meaning)

PR checklist:
- describe what changed (types/control flow/constants/etc.)
- specify which unit(s)/symbol(s) improved
- include before/after match evidence (objdiff screenshot or brief notes)
- explain why the new code is *plausibly original* (not just “score went up”)

---

## Operational guidance for automation

A cron-driven agent should:
1) Ensure PAL config (`python3 configure.py --version GCCP01`) is in effect.
2) Select **one** unit to work on (time-boxed).
3) **Create a branch immediately** for that unit so work never lands on `main` accidentally.
   - Branch naming: `pr/<unit>` (unit path is sufficient; avoid extra task text).
   - Example: `pr/main/chunkfile`
   - Note: git branch names can contain slashes; that’s fine.
4) Attempt a small number of edits.
5) Rebuild with `ninja`.
6) Run objdiff on 1–3 symbols to validate direction.
7) If improvement is real, prepare/open a PR.

Branching policy:
- **Do not stack unrelated work** on one branch.
- One branch = one unit/PR.
- If you need to switch units, commit or discard changes, then switch branches.

Time-boxing recommendation:
- 30–60 minutes per tick max.

---

## Notes / troubleshooting

### Missing `main.dol`
If you see:
- `orig/GCCP01/sys/main.dol not found`
You haven’t synced the original files into `orig/GCCP01/`.

### Endpoint gotcha (Moltbook-style)
Not applicable here.
