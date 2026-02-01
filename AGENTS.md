# AGENTS.md - Agent Runbook (FFCC-Decomp)

This file is the canonical, step-by-step runbook for automated contributions to **FFCC-Decomp**.

Goal: improve match scores by editing C/C++ source, rebuilding, diffing, and submitting clean PRs when progress is real.

## Ghidra Decompilation Reference

### Decomp Resources
- **Current decomp location**: `resources/ghidra-decomp-1-31-2026/`
- **File naming format**: `{PAL_VERSION_ADDRESS}_{METROWERKS_MANGLED_FUNCTION_NAME}`
- **Purpose**: Aid in debugging and reverse engineering

### Symbol Files
The EN and PAL versions accidentally shipped with build logs, containing symbol names for data sections and function names. High level symbols only, not granular.

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

**⚡ Context-Safe Symbol Lookup:**
To avoid loading massive MAP files (1-3MB), use the symbol extraction script:

**🚀 Comprehensive object analysis (recommended):**
```sh
python3 extract_symbols.py ME_USB_process.o     # Everything for this object file
python3 extract_symbols.py chunkfile.o          # All functions, globals, sections
```

**Function lookup:**
```sh
python3 extract_symbols.py pppMatrixXZY
python3 extract_symbols.py "SetUSBData__18CMaterialEditorPcsFv" main/ME_USB_process
```

**Section information (for data layout):**
```sh
python3 extract_symbols.py .data --section     # Data section layout
python3 extract_symbols.py .bss --section      # Uninitialized globals
python3 extract_symbols.py .text --section     # Code section
```

**Global variables (for struct layout/globals):**
```sh
python3 extract_symbols.py ME_USB_process.o --globals    # All globals in object
python3 extract_symbols.py Game --globals                # Globals containing "Game"
python3 extract_symbols.py Game                          # All symbols containing "Game"
```

This outputs only relevant symbol information (~5-15 lines) instead of megabytes.

### Symbol Usage

- **Object analysis**: `python3 extract_symbols.py <object>.o`
- **Function lookup**: `python3 extract_symbols.py "<function_name>"`
- **Section info**: `python3 extract_symbols.py .data --section`
- **Globals**: `python3 extract_symbols.py <object>.o --globals`

### Function Documentation Format
When updating functions, include version-specific address and size information:

```
/*
 * --INFO--
 * PAL Address: 0x80001234
 * PAL Size: 128b
 * EN Address: 0x80001234
 * EN Size: 128b
 * JP Address: 0x80001234
 * JP Size: 128b
 */
```

**Note**: PAL Addresses and sizes are exported in the Ghidra decomp as part of the header. Leave the other versions as TODO for now.

**Important for 0% matches**: Ghidra decomp provides full reference implementations that can be adapted to match the original source style. Even 0% match functions are highly viable targets.
Additionally, if the `config/GCCP01/splits.txt` contains a different function signature than the C++, the match scores may falsely report 0%. Is is highly unlikely that splits.txt is wrong, given that this file was populated from the debug/release game.MAP build trace files with function symbol information.

Unsolved problem 1) Many of the particle ppp functions seem to have parameters in Ghidra, but not in the .MAP file. This makes these falsely report sizes. The game.MAP files do not show a Metrowerks mangled name. These are also not called in a normal manner, these functions have no XREFs in Ghidra. It is unclear if:
A) These are truly parameterless functions or
B) These have parameters, but the game.MAP files missed these parameters due to a strange build setup (ie some sort of asm-inline function table or low-level trickery), which means the splits.txt actually does need updating.

Try not to "solve" this problem unless absolutely confident.

Unsolved problem 2) `configure.py` has several build flags which can influence binary output. This is just as important to code matching as the code itself! The exact compiler version and flags for each module is not known yet.

**Key relationships:** Unit → Object file → Source file. Use symbols for context, Ghidra decomp for 0% functions.

## State Tracking & Memory

### Automation Notes
- **Main log**: `~/.openclaw/workspace/memory/ffcc-decomp-notes.md`
- **Session state**: `~/.openclaw/workspace/memory/decomp-state.json`

Update these files to track progress and avoid cycling through failed targets.

### Cycle Avoidance Strategy
1. **Track attempts** per unit with timestamps
2. **Avoid units** with frequent recent abandonments
3. **Rotate targets** using semi-random selection from viable candidates
4. **Periodically reassess** avoided units to give them another chance

## Scope (current)
- **Target version:** **PAL** (`GCCP01`) - required for now.
  - Do not attempt other versions until PAL is substantially complete.

## Preconditions (one-time setup)

### 0) Repo + assets
- Repo directory (on Zac's Mac):
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

### 4) Objdiff CLI (required for automation)
The CLI tool can be downloaded into the repo. **Use v3.6.1+ for JSON oneshot mode**:
```sh
python3 tools/download_tool.py objdiff-cli build/tools/objdiff-cli --tag v3.6.1
```
Or download manually:
```sh
curl -L https://github.com/encounter/objdiff/releases/download/v3.6.1/objdiff-cli-macos-arm64 -o build/tools/objdiff-cli
chmod +x build/tools/objdiff-cli
```
Verify:
```sh
build/tools/objdiff-cli --version  # Should show v3.6.1+
```

---

## The contribution loop (repeatable)

### Step 1 - Select Target & Gather Context (automated)
**Complete target selection and context gathering in 3 steps:**

```sh
# 1. Pick a target unit
python3 agent_select_target.py
```

**Example output:**
```
SELECTED TARGET:
Unit: main/pppMove
Gap: 100.0% (current: 0.0%)
Source: src/pppMove.cpp
Functions: 0/2
Target functions:
  - pppMoveCon (0.0% match, 36b)
  - pppMove (0.0% match, 156b)
```

```sh
# 2. Get comprehensive symbol information
python3 extract_symbols.py pppMove.o
```

**Example output:**
```
📦 PAL Comprehensive Analysis (pppMove.o):
  ⚡ Functions (2):
     1. pppMoveCon (36b at 80065b18)
     2. pppMove (156b at 80065b3c)
  📊 Summary: 2 functions, 0 globals
```

**Key derivations:** Unit → Object file → Source file. Use Ghidra decomp for 0% functions, objdiff for partial matches.

### Step 2 - Create branch: `git checkout -b pr/<unit>`

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
- changes that preserve output but reduce readability without a clear original-source rationale
- **explanatory comments that add no real information** (e.g., "Plausible original behavior: …")

Prefer changes that are source-plausible:
- fixing signedness / types to match ABI expectations
- using idiomatic control flow the codebase uses elsewhere
- removing obviously redundant variables/branches
- matching struct/field semantics (names and meaning)

### Step 8 - Create Pull Request (if improvement is real + plausible)

**Required steps to create PR:**
1. **Commit changes**: `git commit -m "Descriptive message"`
2. **Push branch**: `git push origin pr/<unit>`
3. **Create PR**: `gh pr create --title "..." --body "..."`

**PR description must include:**
- **Summary**: What changed (types/control flow/constants/etc.)
- **Functions improved**: Which unit(s)/symbol(s) and their improvement metrics
- **Match evidence**: Before/after percentages, assembly analysis results
- **Plausibility rationale**: Why the new code represents *plausible original source* (not just "score went up")
- **Technical details**: Key insights from objdiff analysis, implementation approach

---

## 🚨 Critical Automation Rules

**Follow these rules to avoid contaminated PRs and cleanup work:**

### 🌿 Branch Management - ALWAYS FROM MAIN!
- **ALWAYS branch from `main`**, never from existing PRs
- Before creating new branch: `git checkout main && git pull origin main`
- Branch naming: `pr/unit_name` (e.g., `pr/main_pppMove`)
- **Why this matters**: Branching from PRs creates dependency chains that contaminate later PRs with unmerged changes

### 📝 Memory Location - AGENT WORKSPACE ONLY!
- **NEVER write notes/memories to the project directory** (`Documents/projects/FFCC-Decomp/`)
- **ALWAYS write to agent workspace**: `~/.openclaw/workspace/memory/`
- Project work notes → `memory/YYYY-MM-DD.md` or `memory/ffcc-decomp-notes.md`
- State tracking → `memory/decomp-state.json`
- **Why this matters**: Project directory is for source code only, not agent notes

### 🧹 Code Quality - Clean Source Only!
- **NO junk comments** in submitted code (no original assembly, no debug notes)
- **NO commented-out code** unless specifically needed
- **NO "TODO" or "FIXME" comments** - either implement it or don't include it
- Code should look like **plausible original source** that a game developer would write
- **Why this matters**: PRs should contain production-quality code, not analysis artifacts

### ✅ Pre-Submit Checklist
Before creating any FFCC-Decomp PR:
1. ✅ Branched from clean `main`?
2. ✅ All notes written to agent workspace (not project directory)?  
3. ✅ Code is clean (no assembly comments, debug prints, etc.)?
4. ✅ Real improvement achieved (size match or functionality)?
5. ✅ Build passes with `ninja`?

### 🚨 If You Break These Rules
- **Stop immediately** and fix the issues
- Clean up the branch/PR before continuing
- Update your automation scripts to prevent recurrence
- Document the fix in your memory files

**These rules exist because overnight automation created several contaminated PRs that required manual cleanup. Following them keeps the project clean and maintainable.**

---

## Automation workflow

1. **Select target**: `python3 agent_select_target.py`
2. **Extract symbols**: `python3 extract_symbols.py <object>.o`  
3. **Create branch from clean main**: `git checkout main && git pull origin main && git checkout -b pr/<unit>`
4. **Update state files** (in agent workspace, not project directory)
5. **Edit source** (use Ghidra decomp for 0% functions)
6. **Build**: `ninja`
7. **Analyze**: `build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol>`
8. **If real improvement**: commit, push, create PR with technical details

**Constraints**: One branch per unit, 30-60 min time limit.

---

## Notes / troubleshooting

### Missing `main.dol`
If you see:
- `orig/GCCP01/sys/main.dol not found`
You haven't synced the original files into `orig/GCCP01/`.

### Endpoint gotcha (Moltbook-style)
Not applicable here.
