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

### Common Symbol Workflow Use Cases

**🔍 When implementing a 0% function:**
```sh
# 1. Get EVERYTHING for the object file in one call (recommended)
python3 extract_symbols.py chunkfile.o

# 2. Or get specific function details
python3 extract_symbols.py "pppMatrixXZY"

# 3. Or check data sections if needed
python3 extract_symbols.py .data --section
```

**🏗️ When working on C++ classes:**
```sh
# Find vtables for the class
python3 extract_symbols.py "__vt__5CGame"

# Check all symbols for the class
python3 extract_symbols.py "CGame"

# Look at class data layout
python3 extract_symbols.py game.o --globals
```

**📊 When debugging data structures:**
```sh
# Check .bss for large uninitialized arrays
python3 extract_symbols.py .bss --section

# Find specific global variables
python3 extract_symbols.py "Game" --globals

# Check data section organization
python3 extract_symbols.py .data --section
```

**🔧 When validating function size:**
```sh
# Compare your function size with symbol info
python3 extract_symbols.py "SetUSBData__18CMaterialEditorPcsFv"
# Look for: Size: XXXX bytes - should match your implementation
```

**💡 When looking for string literals or constants:**
```sh
# Find compiler-generated symbols (often string literals)
python3 extract_symbols.py "@"

# Look for specific strings in symbol names
python3 extract_symbols.py "Error"
```

### Function Documentation Format
When updating functions, include version-specific address and size information:

```c
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

## Quick Workflow Reference

**🎯 Complete automation workflow:**
```sh
# 1. Target selection → Get unit name, source file, functions
python3 agent_select_target.py

# 2. Symbol analysis → Get function addresses, sizes, globals  
python3 extract_symbols.py <object_file.o>

# 3. Create branch
git checkout -b pr/<unit>

# 4. Edit source files in src/ (use Ghidra decomp for 0% functions)
# 5. Build & test with ninja + objdiff
# 6. Commit & push if improvement is meaningful + plausible
```

**📊 Key file relationships:**
- **Unit**: `main/pppMove` → **Object**: `pppMove.o` → **Source**: `src/pppMove.cpp`
- **Functions**: Get from symbol analysis (address + size)
- **Ghidra decomp**: `resources/ghidra-decomp-*/<address>_<mangled_name>.c`

## State Tracking & Memory

### Automation Notes
- **Main log**: `~/.openclaw/workspace/memory/ffcc-decomp-notes.md`
- **Session state**: `~/.openclaw/workspace/memory/decomp-state.json`

**Notes format** (append to markdown):
```markdown
## 2026-01-31 - main/chunkfile
- **Target functions**: `Align__10CChunkFileFUl`, `Read__10CChunkFileFv`
- **Attempts**: Tried changing padding in CChunkFile struct - no improvement
- **Result**: No progress, need different approach
- **Next**: Try inlining barriers or signedness changes
```

**State format** (JSON):
```json
{
  "currentTarget": "main/chunkfile",
  "lastAttempt": "2026-01-31T19:06:00Z",
  "recentFailures": ["main/chunkfile", "audio/stream"],
  "blacklisted": [],
  "nextCheck": "2026-02-01T10:00:00Z"
}
```

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

```sh
# 3. Reference Ghidra decomp for 0% functions (as needed)
ls resources/ghidra-decomp-*/80065b18_*  # Find decompiled reference
```

**Key derivations from target selection:**
- **Unit**: `main/pppMove` → **Object file**: `pppMove.o` 
- **Source exists**: `src/pppMove.cpp` (ready to edit)
- **Symbol info**: Addresses, sizes, function names
- **Ghidra decomp**: Available for 0% match functions

**Record in notes:**
- **Unit name**: From script output
- **Target functions**: With sizes and addresses  
- **Approach**: 0% = implement from Ghidra, partial = incremental fix

### Step 2 - Create branch for the target
Once target is identified, create a branch:
```sh
git checkout -b pr/<unit>
```
Example: `pr/main/chunkfile`

### Step 3 - Open the relevant source
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

### Step 4 - Rebuild
From repo root:
```sh
ninja
```

If build fails, fix and rebuild. Do not proceed to diffing with a broken build.

### Step 5 - Diff with objdiff (JSON oneshot mode)
Objdiff diffs **expected object** (`build/GCCP01/src/...`) vs **current object** (`build/GCCP01/obj/...`).

**Important:** Don't treat "percent match" as magic. You should be looking at the **raw assembly**.
Match work is ultimately about making *the compiler emit the same instructions* from plausible source.

#### 5a) Find a symbol name in the expected object
Example (for `main/chunkfile`):
```sh
nm -g build/GCCP01/src/chunkfile.o | head
```
Pick a function symbol, e.g. `Align__10CChunkFileFUl`.

#### 5b) Run objdiff in JSON oneshot mode (automation-friendly)
**Recommended for automation:** JSON oneshot mode provides structured data without requiring a TTY.

```sh
build/tools/objdiff-cli diff -p . -u main/chunkfile -o - Align__10CChunkFileFUl > diff_result.json
```

The JSON output includes:
- **Per-instruction assembly comparison** (left vs right)
- **Symbol mappings** and relocation data
- **Match percentages** and diff analysis
- **Formatted assembly** with highlighting

#### 5c) Parse JSON results programmatically
Parse the JSON to assess:
- **Real improvements**: instruction sequence changes, not just formatting
- **Match quality**: function-level progress vs global noise
- **Specific mismatches**: register allocation, load/store ordering, branching, constants

Example analysis:
```bash
# Check if there are actual instruction differences
jq '.left.symbols[].instructions | length' diff_result.json
# Get match percentage for the target function
jq '.left.symbols[] | select(.name == "target_symbol") | .match_percent' diff_result.json
```

#### 5d) Interactive mode (optional)
For manual analysis, the interactive UI is still available:
```sh
build/tools/objdiff-cli diff -p . -u main/chunkfile Align__10CChunkFileFUl
```
Quit with `q`.

### Step 6 - Check progress summary
At the end of `ninja`, a progress report is printed.
Example tail:
- `All: 8.88% matched, 0.00% linked (0 / 480 files)`

Optional: generate a JSON report:
```sh
build/tools/objdiff-cli report generate -p . -o build/GCCP01/report.json -f json-pretty
```

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

## Operational guidance for automation

A cron-driven agent should:
1) Ensure PAL config (`python3 configure.py --version GCCP01`) is in effect.
2) **Select target**: `python3 agent_select_target.py` → get unit name, source path, target functions
3) **Extract symbols**: `python3 extract_symbols.py <object>.o` → get comprehensive symbol info  
4) **Create branch** for that specific unit (`pr/<unit>`).
5) **Update state files** with current attempt.
6) **Reference resources as needed**:
   - **0% functions**: Use Ghidra decomp from `resources/ghidra-decomp-*`
   - **Partial functions**: Focus on objdiff analysis for specific mismatches
7) Attempt a small number of edits.
8) Rebuild with `ninja`.
9) **Run objdiff JSON analysis** on 1–3 target symbols:
   ```sh
   build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol> > diff_analysis.json
   ```
10) **Parse JSON results** to determine if changes represent real progress:
    - Instruction-level improvements, not just formatting
    - Function match percentage increases
    - Meaningful assembly differences (register allocation, branching, etc.)
11) **If improvement is real and plausible, create PR**:
    - Commit: `git commit -m "Descriptive message with metrics"`
    - Push: `git push origin pr/<unit>`
    - Create PR: `gh pr create --title "..." --body "..."`
    - **Required in PR description:**
      - Summary of technical changes
      - Before/after match percentages 
      - Why changes represent plausible original source
      - objdiff analysis highlights

Branching policy:
- **Do not stack unrelated work** on one branch.
- One branch = one unit/PR.
- If you need to switch units, commit or discard changes, then switch branches.

Time-boxing recommendation:
- 30-60 minutes per tick max.

---

## Notes / troubleshooting

### Missing `main.dol`
If you see:
- `orig/GCCP01/sys/main.dol not found`
You haven't synced the original files into `orig/GCCP01/`.

### Endpoint gotcha (Moltbook-style)
Not applicable here.
