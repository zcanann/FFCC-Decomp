# AGENTS.md - Agent Runbook (FFCC-Decomp)

This is the concise runbook for automated contributions to **FFCC-Decomp**.

> **Parallel campaign:** when work is multiplexed across multiple Claude operators, see [`WORK_SPLIT.md`](WORK_SPLIT.md) for the 4-employee bucket assignments (units < 95% match divided by domain), coordination rules, and the proven toolbox (`tools/permute_fn.py`, switch-case-order extraction, MWCC idioms). Each employee owns one bucket and spawns one agent per unit.

Goal: maximize real progress by improving C/C++ source, linkage, headers, types, data layout, and adjacent code where needed, then rebuilding, diffing, and checkpointing work only when the result is both better and plausible.

## Integration Workflow
- **Contributors with direct write access:** work on the permanent `staging` branch and push validated checkpoints to `origin/staging`. Keep using that branch across targets and sessions; routine work does not need a PR.
- **Outside contributors without write access:** work on a topic branch in a fork and open a PR against this repository's `staging` branch.
- Maintainers periodically integrate `staging` into `main` with a normal merge commit, preserving the individual checkpoints. After integration, fast-forward `staging` to the new `main` merge commit. Do not rotate or date the staging branch.
- If work lands directly on `main`, reconcile it into `staging` before the next staging push, preserving both sides. Routine development checkpoints go to `staging`.

## Source Of Truth
- **Objdiff is the source of truth** for progress.
- **Ghidra is a guide**, mainly for addresses, sizes, and rough function shape.
- Function names from shipped Metrowerks symbols are usually correct. Parameters from Ghidra may not be.

Game code uses **GC/2.5** as its shared compiler baseline. This is a working assumption supported by comparison, not proof of the exact retail compiler. Prefer recovering plausible source and removing temporary tuning over adding per-unit compiler overrides. Revisit existing optimization overrides against this baseline. If a previously `Matching` unit stops linking exactly, mark it `NonMatching` while repairing it; do not preserve the label with compiler exceptions. SDK and middleware compiler choices are independent.

Useful references:
- Ghidra decomp: `resources/ghidra-decomp-1-31-2026/`
- PAL map: `orig/GCCP01/game.MAP`
- EN map: `orig/GCCE01/game.MAP`
- Symbol extractor: `python3 tools/extract_symbols.py <object>.o`

Useful tooling:
- `python3 tools/agent_select_target.py` picks code/data targets and shows PAL/EN symbol hints.
- `python3 tools/map/claim_doctor.py [source.cpp]` compares current compiled section sizes, current claims, and PAL/EN MAP ownership hints.
- `python3 tools/map_symbols_to_files.py` groups currently unclaimed PAL symbols by MAP-attributed object file.

When updating functions, keep the version header block:

```c
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

## Preconditions
Skip setup unless the repo is not already prepared.

```sh
python3 configure.py --version GCCP01
ninja
python3 tools/download_tool.py objdiff-cli tools/objdiff-cli --tag v3.6.1
tools/objdiff-cli --version
```

PAL (`GCCP01`) is the only active target.

## Contribution Loop

### 1. Select a target
Choose a target using objdiff, MAP evidence, and your judgment about where plausible source changes can make progress. Continue with a promising dependency cluster when appropriate. The automatic selector is optional:

```sh
python3 tools/agent_select_target.py
```

### 2. Start from current `staging`
With direct write access, reuse the local staging branch:

```sh
git fetch origin staging
git switch staging
git rebase origin/staging
```

On the first checkout, use `git switch --track -c staging origin/staging`. If the repository has no staging branch yet, a contributor with write access can create it from fresh `origin/main` and publish it once.

Outside contributors use `upstream` for this repository and `origin` for their fork:

```sh
git fetch upstream staging
git switch -c <topic> upstream/staging
```

Inspect existing changes before switching or rebasing. Preserve unfinished work and other contributors' changes; discard only experiments you have identified as unsuccessful. Rebase only unpublished local commits. Never force-push the shared staging branch or resolve conflicts by blindly taking one side; abort and re-derive the affected change if necessary.

### 3. Work the target, then work outward
Start from the selected mismatched function or data, but do not stay artificially narrow if the real blocker is adjacent.

Agents are explicitly allowed, and expected, to go on a **crusade around the target** when it helps matching:
- fix headers, forward declarations, and includes
- correct function signatures and class layouts
- replace `extern` hacks with real definitions and linkage where practical
- NEVER use hacks to manually define vtables, RTTI, ctors, dtors, etc. These should be generated by the compiler from configure flags or normal C++.
- fix signedness, typedefs, enums, constants, and ABI-relevant types
- replace hard-coded offsets with real member variables and member access
- repair nearby structs, globals, constructors, vtables, and helper functions
- update `config/GCCP01/symbols.txt` when symbol naming is the real issue
- adjust `configure.py` flags when flags are the blocker, not the source
- If working on data, ALWAYS reference .MAP files as ground-truth for how data was laid out (.sdata, .bss, .rodata, etc. appear in these)

Do not optimize only for the named symbol if the surrounding code is what prevents a real match.

### 4. Build
```sh
ninja
```

### 5. Diff
```sh
build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol> > diff_result.json
```

### 6. Evaluate net progress
Treat these as first-class wins:
- code match
- data match
- linkage progress
- cleaner, more correct declarations that unblock future matching

Small local regressions are acceptable if they unlock larger real gains nearby.

### 7. Decide to checkpoint or do more work
Before checkpointing, ensure that:
**A) Real net progress**
- objdiff or build output improved in code, data, or linkage
- gains are real, not formatting, renames, or temporary hacks
- minor score regressions are ONLY acceptable if the code is closer to plausible source (ie if a change was made that is backed up by the .MAP files)

**B) Plausible original source**
- the code looks like something the FFCC developers could have written
- types, fields, control flow, and linkage are more coherent than before

If these are true, make a coherent checkpoint and continue with the next target or dependency cluster. Do not create a new branch or PR for each small gain when you have direct write access.

### 8. Publish the checkpoint
Stage only the intended files and record the result:

```sh
git add <changed-files>
git commit -m "Descriptive message"
```

With direct write access, fetch and rebase unpublished work onto fresh staging before every push:

```sh
git fetch origin staging
git rebase origin/staging
ninja
# Repeat objdiff for the affected units after rebasing.
git push origin HEAD:staging
```

If the remote advances and rejects the push, fetch, rebase, and validate again. Never force-push to bypass it. Both the source build and PAL checksum check must pass; a successful retail-object link alone is not sufficient validation of changed C/C++.

Outside contributors push the topic branch to their fork and open or update a coherent PR:

```sh
git push -u origin HEAD
gh pr create --repo zcanann/FFCC-Decomp --base staging --head <fork-owner>:<topic> --title "..." --body-file <description-file>
```

Checkpoint commit bodies and PR descriptions should summarize:
- what changed
- which units or symbols improved
- before/after evidence
- why the result is plausible source, not compiler coaxing

## Critical Rules
- Prefer defining & linking things over using `extern` as a crutch.
- If its not clear where something is defined, try using the .MAP files.
- Do not manually force sections like `__declspec(section ".ctors")`.
- Do not manually write dtor/ctor/sinit functions that are likley generated.
- Do not hardcode addresses or use fake `lbl_` / `fn_` names to chase output.
- Use real member access instead of pointer-offset tricks.
- Keep code clean: no junk comments, no analysis debris, no commented-out experiments.
- Notes belong in the agent workspace, not the project tree.
- Base routine work on current `staging`. Direct-write contributors reuse staging; outside contributors use fork topic branches and PRs. Never build a new contribution on an unrelated PR branch.
- When in doubt, bias towards what the actual source code looked like.
- UNUSED functions should be marked as inline if they cause extab regressions. This trick allows us to keep functions we know exist and are UNUSED without score regressions.

## Operating Principle
Do not treat the selected symbol as a tiny sandbox. Treat it as the center of a dependency cluster.

If matching the target requires fixing adjacent linkage, includes, headers, structs, globals, constructors, or helper functions, do that work. Recovering coherent original source is the goal, not narrowly editing one function while leaving the surrounding code obviously wrong.

## Minimal Workflow
1. Choose a target from evidence and judgment; optionally use `python3 tools/agent_select_target.py`
2. Sync `staging` (direct write access), or branch from upstream staging in a fork (outside contributor)
3. Fix the target and any adjacent blockers
4. `ninja`
5. `build/tools/objdiff-cli diff -p . -u <unit> -o - <symbol>`
6. If net progress is real and plausible, commit; with direct write access, sync, revalidate, and push to staging; otherwise push to your fork and open or update a PR against staging
7. Direct-write contributors continue on staging for the next target; outside contributors keep each PR coherent
