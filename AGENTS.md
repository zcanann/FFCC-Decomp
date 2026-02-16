# AGENTS.md - Agent Runbook (FFCC-Decomp)

This file is the canonical, step-by-step runbook for automated contributions to **FFCC-Decomp**.

Goal: improve match scores by editing C/C++ source, rebuilding, diffing, and submitting clean PRs when progress is real.

## Ghidra Decompilation Reference
WARNING: Do not fully trust Ghidra for anything other than address and sizes. The existing decomp is based off of a snapshot and guesswork. The function names however are 99% accurate and were reconstructed from Metrowerks build symbol files.

In other words, function parameters can be wrong in Ghidra, unless there is Metrowerks mangling in the function name to indicate the true parameters.

### Decomp Resources
- **Current decomp location**: `resources/ghidra-decomp-1-31-2026/`
- **File naming format**: `{PAL_VERSION_ADDRESS}_{METROWERKS_MANGLED_FUNCTION_NAME}`
- **Purpose**: Aid in debugging and reverse engineering

### Symbol Files
The EN and PAL versions accidentally shipped with build logs, containing symbol names in mangled Metrowerks format for data sections and function names. High level symbols only, not granular.

#### PAL Release (Metrowerks Release Build)
- **Location**: `orig/GCCP01/game.MAP`
- **Note**: Contains Metrowerks Release build output from a prior build
- **Important**: Addresses do not match current decomp, but function symbols have ~99% accuracy

#### EN Release (Debug Build)
- **Location**: `orig/GCCE01/game.MAP`
- **Note**: Contains old Debug build symbols
- **Cross-reference**: Can be used for any version (e.g., EN symbols to aid PAL decompilation)

### Symbol File Usage
Symbol files are helpful for determining:
- Class hierarchies
- Function arguments and parameters
- Global variables (especially .bss section data)
- Function relationships and dependencies
To avoid loading massive MAP files (1-3MB), use the symbol extraction script when you need a deeper dive.
NOTE: `tools/agent_select_target.py` already includes symbol summaries for each random target, so this step is optional.

**Example usage (manual, optional):**
```sh
python3 tools/extract_symbols.py ME_USB_process.o     # Everything for this object file
python3 tools/extract_symbols.py chunkfile.o          # All functions, globals, sections
```

This outputs only relevant symbol information instead of having to sift through MBs of data.

### Function Documentation Format
When updating functions, include version-specific address and size information:

```
/*
 * --INFO--
 * PAL Address: 0x80001234
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
```

**Note**: PAL Addresses and sizes are exported in the Ghidra decomp as part of the header. Leave the other versions as TODO for now.

**Important for 0% matches**: Ghidra decomp provides full reference implementations that can be adapted to match the original source style. Even 0% match functions are highly viable targets. For large functions, even small incremental gains in match score can be considered valuable progress.

**Important for near matches** `configure.py` has several build flags which can influence binary output. This is just as important to code matching as the code itself! The exact compiler version and flags for each module is not known yet. For this reason, high matches like 97% are sometimes acceptable and not worth dealing with because it could be build system related.

**Key relationships:** Unit -> Object file -> Source file. Use symbols for context, Ghidra decomp for low match score functions.

## Preconditions (one-time setup)
Skip the preconditions step unless errors are encountered indicating lack of initial setup.

### 0) Repo + assets
- Repo directory (default location):
  - `~/Documents/projects/FFCC-Decomp`
- Required assets are **not** in git. Your owner will have already given you the original files locally:
  - `orig/GCCP01/...` (at minimum `orig/GCCP01/sys/main.dol`).

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
Note: GCCP01 is PAL, which is the only version we are working on currently. Do not attempt to swtich versions.

### 3) Build once
```sh
ninja
```
Success criteria: build completes and verifies:
- `build/GCCP01/main.dol: OK`

### 4) Objdiff CLI (required for automation)
The CLI tool can be downloaded into the repo. **Use v3.6.1+ for JSON oneshot mode**:
```sh
python3 tools/download_tool.py objdiff-cli tools/objdiff-cli --tag v3.6.1
```
Or download manually:
```sh
curl -L https://github.com/encounter/objdiff/releases/download/v3.6.1/objdiff-cli-macos-arm64 -o tools/objdiff-cli
chmod +x tools/objdiff-cli
```
Verify:
```sh
tools/objdiff-cli --version  # Should show v3.6.1+
```

---

## The contribution loop (repeatable)
This is likely the starting point for the agent.

### Step 1 - Select Target & Gather Context (automated)
Run the selector once. It prints several random viable targets with symbol summaries. You should strongly bias towards functions that are large and have 0% match scores. There is the most to be gained from these.

```sh
python3 tools/agent_select_target.py
```

**Example output (abridged):**
```
RANDOM TARGETS:
 1. Unit: main/pppMove (gap: 100.0%, current: 0.0%)
    Source: src/pppMove.cpp
    Object: pppMove.o
    Functions: 0/2 (0.0%)
    Targets:
      - pppMoveCon (0.0% match, 36b)
      - pppMove (0.0% match, 156b)
    PAL symbols: 2 funcs, 0 globals (showing up to 5 funcs)
      - pppMoveCon (0x24b at 80065b18)
      - pppMove (0x9cb at 80065b3c)
```

WARNING: If the function parameters do not match, the match score cannot be improved beyond 0%! This is very common for ppp* functions as mentioned earlier, which may need C linkage or some other remedy to prevent Metrowerks mangled names (thus allowing objdiff to match these).

DO NOT TRUST GHIDRA BEYOND GETTING A FEEL FOR THE FUNCTION. GHIDRA IS A GUIDELINE. OBJDIFF IS THE REAL SOURCE OF TRUTH FOR HOW CLOSE WE ARE.

### Step 2 - Create branch: `git checkout -b pr/<unit>/$(date -u +%s)`

### Step 3 - Edit source files in `src/` and `include/`
Make small changes: types, signedness, struct layout, control flow, constants.

### Step 4 - Build: `ninja`

### Step 5 - Analyze with objdiff
```sh
build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol> > diff_result.json
```
Parse JSON to assess real assembly improvements vs formatting changes.

### Step 6 - Check overall progress with `ninja` output

### Step 7 - Decide whether to create PR (match + plausibility)
A higher match score is **necessary but not sufficient**.

Make a PR only if **both** are true:

**A) Match improves meaningfully**
- objdiff shows real alignment improvement (not just formatting/renames)
- preferably improves one or more specific functions, not just global noise

**B) The resulting C/C++ is plausible original source**
The goal is to match what the **original FFCC authors likely wrote**, not merely to coax the compiler.

Reject/avoid changes that look like "compiler coaxing," e.g.:
- contrived temporaries and reordering that a human wouldn't naturally write
- intentionally odd sequencing unless there's strong evidence
- using hardcoded offsets to objects instead of making member variables
- changes that preserve output but reduce readability without a clear original-source rationale
- **explanatory comments that add no real information** (e.g., "Plausible original behavior: ...")

Prefer changes that are source-plausible:
- fixing signedness / types to match ABI expectations
- using idiomatic control flow the codebase uses elsewhere
- removing obviously redundant variables/branches
- matching struct/field semantics (names and meaning)

EXCEPTION: If making a first pass at a large function, mangled code is tolerable.

### Step 8 - Create Pull Request (if improvement is real + plausible)

**Required steps to create PR:**
1. **Commit changes**: `git commit -m "Descriptive message"`
2. **Push branch**: `git push -u origin HEAD`
3. **Create PR**: `gh pr create --title "..." --body "..."`

**PR description must include:**
- **Summary**: What changed (types/control flow/constants/etc.)
- **Functions improved**: Which unit(s)/symbol(s) and their improvement metrics
- **Match evidence**: Before/after percentages, assembly analysis results
- **Plausibility rationale**: Why the new code represents *plausible original source* (not just "score went up")
- **Technical details**: Key insights from objdiff analysis, implementation approach

---

## Critical Automation Rules

**Follow these rules to avoid contaminated PRs and cleanup work:**

### Branch Management - ALWAYS FROM MAIN!
- **ALWAYS branch from `main`**, never from existing PRs
- Before creating new branch: `git checkout main && git pull origin main`
- Branch naming: `pr/<unit>/$(date -u +%s)` (example: `pr/main/pppMove/1739481600`)
- **Why this matters**: Branching from PRs creates dependency chains that contaminate later PRs with unmerged changes

### Code Quality - Clean Source Only!
- **NO junk comments** in submitted code (no original assembly, no debug notes)
- **NO commented-out code** unless specifically needed
- Code should look like **plausible original source** that a game developer would write, unless making an early attempt at a complex function
- **Why this matters**: PRs should contain production-quality code, not analysis artifacts

### Pre-Submit Checklist
Before creating any FFCC-Decomp PR:
1. Branched from clean `main`?
2. All notes written to agent workspace (not project directory)?  
3. Code is clean (no assembly comments, debug prints, etc.)?
4. Real improvement achieved (size match or functionality)?
5. Build passes with `ninja`?

### If You Break These Rules
- **Stop immediately** and fix the issues
- Clean up the branch/PR before continuing
- Update your automation scripts to prevent recurrence
- Document the fix in your memory files

**These rules exist because overnight automation created several contaminated PRs that required manual cleanup. Following them keeps the project clean and maintainable.**

---

## Automation workflow

1. **Select target**: `python3 tools/agent_select_target.py`
2. **Symbols are included** in the selector output (manual extract is optional)  
3. **Create branch from clean main**: `git checkout main && git pull origin main && git checkout -b pr/<unit>/$(date -u +%s)`
4. **Update state files** (in agent workspace, not project directory)
5. **Edit source** (use Ghidra decomp for low-match functions)
6. **Build**: `ninja`
7. **Analyze**: `build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol>`
8. **If real improvement**: commit, push, create PR with technical details
