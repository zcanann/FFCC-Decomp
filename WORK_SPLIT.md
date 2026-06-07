# Multiplexed Decomp Work Split — 4 Employees × N Agents

Generated against `build/GCCP01/report.json` on latest `main`. Scope: **all 60 units below 95% fuzzy match** (total remaining workload ≈ **236,888 unmatched code bytes**), divided into 4 domain-coherent buckets, balanced by unmatched-byte workload.

## Model
- **4 employees**, each runs its own **Claude** session.
- Each employee **spawns N_i background agents** (worktree-isolated), roughly **one agent per unit** in its bucket (batch in waves of ~4–6 concurrent to keep CPU sane).
- Every agent follows the **`AGENTS.md` runbook** (configure → build → diff → commit → PR), one PR per unit.

## Hard coordination rules (avoid cross-employee collisions)
1. **Stay in your bucket.** Only edit the `.cpp` units assigned to you. The buckets are domain-grouped so each employee owns a coherent subsystem and its `.cpp` files.
2. **Shared headers are the only collision risk.** If you must change a shared header (`menu.h`, `MenuUtil.h`, `chara.h`, `gobject.h`, `vector.h`, `color.h`, `symbols.txt`, `splits.txt`, `configure.py`), keep it minimal and call it out in the PR title with `[shared]` so reviewers serialize those merges. Do **not** rename global symbols another bucket depends on without coordinating.
3. **Branch naming:** `pr/<unit>/emp<N>` (e.g. `pr/joybus/emp1`). One unit per branch/PR.
4. **Worktree hygiene:** symlink only individual files *inside* `orig/<ver>/` for building — **never** replace an `orig/<ver>` directory with a symlink, and never `git add -A` anything under `orig/`.
5. **report.json is the source of truth** for match %, not the on-demand `objdiff-cli diff` (it reads ~0.1% lower).

## Toolbox & proven techniques (battle-tested this campaign)
- **Deterministic switch-case-order extraction** — for any big `switch`, map the jumptable's DOL vaddr→file offset, read the entries, sort case bodies by target address to recover MWCC's source emission order, reorder the `case` blocks to match. (Took cflat 74→81% and mes addString 42→76% in single commits.)
- **`tools/permute_fn.py`** — greedy signedness/int-width brute-forcer; run on every sub-100% function: `python3 tools/permute_fn.py --unit main/<u> --symbol '<MANGLED>' --file src/<u>.cpp --func <name>`.
- **`unsigned→signed` field typing** flips `cmplw`→`cmpw`; **field-by-field GXColor init** byte-stores instead of pooling; **counted `for` loops** emit `bdnz`; **re-read-don't-cache** matches MWCC aliasing reloads; **duplicate** shared expressions/multiplies into each branch to grow the stack frame; **inline UNUSED functions** (mark `inline`, move definition before caller); **reciprocal-multiply** division form `1.0 - (1.0/d)*t`.
- **"Register-allocation wall" ≈ undiscovered structure.** Before declaring a wall, hunt for: missing inlined code (function smaller than target), branch duplication, inlined-UNUSED helpers, switch case-order, frame-size drivers. Genuine pure-numbering/CSE walls exist but are the exception.
- Refs: Ghidra `resources/ghidra-decomp-1-31-2026/`, PAL map `orig/GCCP01/game.MAP`, EN map `orig/GCCE01/game.MAP`, target asm `build/GCCP01/asm/<unit>.s` (objdiff single-symbol diff: **TARGET=left**, ours=right).

## Per-agent loop (give this to each spawned agent)
1. Branch from latest `main`: `git checkout -b pr/<unit>/emp<N>`.
2. `python3 configure.py --version GCCP01 && ninja`.
3. Find lowest-% functions (per-function listing from report.json), attack structure first, then `permute_fn.py`, then idioms.
4. Rebuild + remeasure after each change; **commit + push every net-positive, plausible change** (no batch-revert).
5. Open a PR per unit when it's improved (80%+ ideal; net progress acceptable per AGENTS.md).

---
## E1 — Engine / Graphics / Map / Memory / System
**Units: 17  ·  Workload: 59,419 unmatched bytes  ·  Suggested N_i ≈ 17 agents** (run in waves of ~5 concurrent)

| unit | fuzzy % | code | unmatched | suggested |
|---|---:|---:|---:|---|
| `src/joybus.cpp` | 71.42% | 51,292 | 14,658 | structural+brute-force |
| `src/gobject.cpp` | 70.80% | 25,656 | 7,491 | structural+brute-force |
| `src/cmake.cpp` | 80.61% | 31,248 | 6,058 | structural+brute-force |
| `src/p_camera.cpp` | 74.26% | 17,260 | 4,443 | structural+brute-force |
| `src/goout.cpp` | 80.42% | 18,616 | 3,644 | structural+brute-force |
| `src/map.cpp` | 84.17% | 21,804 | 3,451 | brute-force+idioms |
| `src/materialman.cpp` | 89.32% | 31,576 | 3,373 | brute-force+idioms |
| `src/p_graphic.cpp` | 68.42% | 10,168 | 3,211 | rewrite/structural |
| `src/mapobj.cpp` | 80.55% | 16,180 | 3,147 | structural+brute-force |
| `src/gobjwork.cpp` | 87.63% | 19,476 | 2,410 | brute-force+idioms |
| `src/memory.cpp` | 85.12% | 15,236 | 2,267 | brute-force+idioms |
| `src/maphit.cpp` | 81.03% | 10,516 | 1,995 | structural+brute-force |
| `src/memorycard.cpp` | 91.23% | 13,856 | 1,215 | brute-force+idioms |
| `src/graphic.cpp` | 93.70% | 15,240 | 959 | brute-force+idioms |
| `src/p_MaterialEditor.cpp` | 84.71% | 5,376 | 822 | brute-force+idioms |
| `src/pad.cpp` | 94.87% | 3,392 | 174 | brute-force+idioms |
| `src/gxfunc.cpp` | 93.69% | 1,576 | 99 | brute-force+idioms |

## E2 — Characters, Objects & Particle Effects
**Units: 19  ·  Workload: 66,779 unmatched bytes  ·  Suggested N_i ≈ 19 agents** (run in waves of ~5 concurrent)

| unit | fuzzy % | code | unmatched | suggested |
|---|---:|---:|---:|---|
| `src/p_chara.cpp` | 71.92% | 32,924 | 9,244 | structural+brute-force |
| `src/chara_fur.cpp` | 58.18% | 20,676 | 8,647 | rewrite/structural |
| `src/partyobj.cpp` | 80.15% | 42,020 | 8,341 | structural+brute-force |
| `src/partMng.cpp` | 80.13% | 32,648 | 6,487 | structural+brute-force |
| `src/charaobj.cpp` | 80.32% | 30,452 | 5,994 | structural+brute-force |
| `src/monobj.cpp` | 81.70% | 30,752 | 5,628 | structural+brute-force |
| `src/monobj_boss.cpp` | 76.50% | 19,244 | 4,521 | structural+brute-force |
| `src/chara.cpp` | 80.12% | 20,464 | 4,067 | structural+brute-force |
| `src/pppRyjMegaBirthModel.cpp` | 84.07% | 15,628 | 2,490 | brute-force+idioms |
| `src/pppPart.cpp` | 85.88% | 14,992 | 2,117 | brute-force+idioms |
| `src/pppYmMegaBirthShpTail3.cpp` | 80.84% | 8,712 | 1,670 | structural+brute-force |
| `src/pppYmMegaBirthShpTail2.cpp` | 81.72% | 7,636 | 1,396 | structural+brute-force |
| `src/pppRyjMegaBirth.cpp` | 84.44% | 8,044 | 1,251 | brute-force+idioms |
| `src/pppYmMana.cpp` | 91.92% | 14,996 | 1,211 | brute-force+idioms |
| `src/itemobj.cpp` | 87.87% | 9,360 | 1,135 | brute-force+idioms |
| `src/pppMana2.cpp` | 92.19% | 12,376 | 967 | brute-force+idioms |
| `src/FunnyShape.cpp` | 87.31% | 6,684 | 848 | brute-force+idioms |
| `src/pppKeShpTail3X.cpp` | 90.59% | 4,448 | 418 | brute-force+idioms |
| `src/pppKeShpTail2X.cpp` | 88.34% | 2,964 | 346 | brute-force+idioms |

## E3 — Big Menu Screens
**Units: 5  ·  Workload: 59,866 unmatched bytes  ·  Suggested N_i ≈ 5 agents** (run in waves of ~5 concurrent)

| unit | fuzzy % | code | unmatched | suggested |
|---|---:|---:|---:|---|
| `src/wm_menu.cpp` | 82.30% | 115,740 | 20,483 | brute-force+idioms |
| `src/bonus_menu.cpp` | 62.83% | 45,452 | 16,894 | rewrite/structural |
| `src/shopmenu.cpp` | 72.56% | 37,516 | 10,293 | structural+brute-force |
| `src/menu_cmd.cpp` | 69.73% | 23,176 | 7,015 | rewrite/structural |
| `src/MenuUtil.cpp` | 71.43% | 18,136 | 5,181 | structural+brute-force |

## E4 — Small Menus + cflat Minigame Runtime + Text
**Units: 19  ·  Workload: 50,824 unmatched bytes  ·  Suggested N_i ≈ 19 agents** (run in waves of ~5 concurrent)

| unit | fuzzy % | code | unmatched | suggested |
|---|---:|---:|---:|---|
| `src/gbaque.cpp` | 81.71% | 35,712 | 6,533 | structural+brute-force |
| `src/cflat_r2system.cpp` | 80.92% | 31,244 | 5,962 | structural+brute-force |
| `src/cflat_runtime2.cpp` | 76.66% | 20,476 | 4,780 | structural+brute-force |
| `src/cflat_runtime.cpp` | 72.54% | 15,964 | 4,384 | structural+brute-force |
| `src/singmenu.cpp` | 80.12% | 21,836 | 4,340 | structural+brute-force |
| `src/menu_letter.cpp` | 75.51% | 17,544 | 4,297 | structural+brute-force |
| `src/mesmenu.cpp` | 71.90% | 11,484 | 3,227 | structural+brute-force |
| `src/cflat_r2class.cpp` | 80.05% | 13,644 | 2,721 | structural+brute-force |
| `src/ringmenu.cpp` | 72.24% | 9,656 | 2,681 | structural+brute-force |
| `src/mes.cpp` | 80.50% | 12,740 | 2,484 | structural+brute-force |
| `src/menu_equip.cpp` | 80.05% | 9,792 | 1,953 | structural+brute-force |
| `src/p_minigame.cpp` | 86.24% | 14,040 | 1,931 | brute-force+idioms |
| `src/menu_compa.cpp` | 75.23% | 5,252 | 1,301 | structural+brute-force |
| `src/menu_item.cpp` | 83.45% | 6,916 | 1,144 | brute-force+idioms |
| `src/menu_money.cpp` | 81.20% | 5,804 | 1,091 | structural+brute-force |
| `src/menu_favo.cpp` | 83.94% | 5,612 | 901 | brute-force+idioms |
| `src/menu_arti.cpp` | 88.62% | 5,300 | 603 | brute-force+idioms |
| `src/menu_tmparti.cpp` | 89.99% | 3,044 | 305 | brute-force+idioms |
| `src/menu_lst.cpp` | 94.67% | 3,476 | 185 | brute-force+idioms |
---
## Balance summary
| Employee | units | workload (unmatched bytes) |
|---|---:|---:|
| E1 Engine / Graphics / Map / Memory / System | 17 | 59,419 |
| E2 Characters, Objects & Particle Effects | 19 | 66,779 |
| E3 Big Menu Screens | 5 | 59,866 |
| E4 Small Menus + cflat Minigame Runtime + Text | 19 | 50,824 |
| **Total** | **60** | **236,888** |

Notes:
- **E2 is the heaviest** (most units + the hardest unit `chara_fur`, which needs a multi-session ground-up reconstruction of `makeFurTex`/`PickFur`). Give it the most agents / most wall-clock.
- **E4 is the lightest** but `cflat_r2system` (already 80.9%) and the small menus benefit hugely from the case-order + signedness tools.
- E1 and E3 are near-identical workloads; E3 is only 5 units but they are *large* (wm_menu alone is 115KB) — fewer, longer-running agents.
