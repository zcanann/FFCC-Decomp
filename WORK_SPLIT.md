# Multiplexed Decomp Work Split v2 — drive every unit to 100%

Generated against `build/GCCP01/report.json` on latest `main` (overall ~91%). Scope: **all 132 units below 100% match** (~165,408 unmatched code bytes), split into 4 domain-coherent buckets, load-balanced by unmatched bytes. **Goal: 100% match on everything — by any means (source, brute force, tooling, intellect).**

## Model
- **4 employees**, each runs its own **Claude**, each spawns **N worktree-isolated background agents** (~one per unit, waves of ~5-6 concurrent).
- Per-unit loop: branch from latest `main` -> configure+build -> diff -> fix -> rebuild+remeasure -> **commit/push every net-positive plausible change** -> one PR per unit -> **merge at a good-sized checkpoint, relaunch from fresh main**. Repeat until the unit's source-reachable frontier is closed.

## Coordination policy (UPDATED)
1. Buckets are domain-grouped to minimize file overlap — stay in your bucket by default.
2. **Cross-unit fixes are ALLOWED.** If a fix needs a shared header/struct/symbol touching other buckets: keep it minimal, prefix the PR title `[cross]`, and **merge it FAST** so the other 3 orchestrators rebase/resolve quickly. Don't sit on cross-unit changes.
3. **report.json is the source of truth** for match percent (diverges from on-demand `objdiff-cli diff` by ~0.1 to 0.5 points — always gate on report.json).
4. orig/ hygiene: symlink only individual files INSIDE `orig/<ver>/`; never replace an `orig/<ver>` dir with a symlink; never `git add -A` under `orig/`.
5. Confirm `ninja build/GCCP01/ok` (DOL sha1) after shared-header/struct changes.

## Lever catalog (battle-tested; try roughly in this order)
**Structure first (biggest wins):**
- **Switch case-body order from the jumptable** — decode the target's case emission order (DOL vaddr->file offset, sort case bodies by address), reorder source cases to match. (cflat onSystemFunc 11->62; mes addString 42->76; materialman Create 60->85.)
- **Recover missing/wrong code** — a function smaller than target means a missing inlined block / chunk case (mapobj SHKI/LSDW; menu_cmd CmdDraw blocks).
- **Struct-group a function's locals** to match the target stack layout, object ptr first (gobject objectCollision 82->98).
- **Wrong struct/wrapper or field offset** — verify member offsets vs target stores (gobject CMapCylinder wrapper; ModelNodeMtx +0x6C; materialman m_materialColor 0x38).
- **Inline UNUSED functions** (mark inline, move def before caller); **switch for small-int dispatch** (gobject InitWork 80->98).
- **Block-ordering via goto / shared-tail + condition-sense inversion** (maphit CheckHitFaceCylinder 67->90, FindIntersection 73->93; goout/cmake branch-order inversion).
- **Reconstruct missing whole-function logic / loop bodies** from target asm (joybus ThreadMain cases).

**Idioms (mid-game):**
- **signed vs unsigned** typing flips cmplw<->cmpw, lhz<->lha, divwu<->divw (crossed mes 80 percent; pervasive).
- **re-read-don't-cache** member/param fields (joybus m_portIndex; gobject model handle).
- **inline member-array INDEX form** m_arr[i] (base+offset) vs pointer-walk (map, mapobj, gobjwork).
- **2D-array indexing** m_buf[port][k] folds offset into the load/store displacement (joybus).
- **counted for** -> mtctr/bdnz (or keep do/while where the target does).
- **single-vs-double precision** (fmuls/fsubs/fdivs/frsp); **fmadds/fnmsubs fusion** via temps / left-assoc subtraction; parenthesize to control the FP tree.
- **non-mutating fallback ternary** (use a ? a : fallback; don't reassign the param) (memory alloc 84->96).
- **brace-init GXColor** with a literal aggregate (not assignment from a named const) to defeat LICM hoist into a callee-saved reg (p_MaterialEditor drawViewer +1.5pp); **declare a var inside the loop** to defeat hoist (graphic RenderBlur).
- **field-by-field GXColor** byte-store vs pooled word (shopmenu); reinterpret-cast byte copies for rgba; **raw-int store into a zero float field**.
- **result=0 in the success-else**, **cmd=0 before the Get call**, **hoist cmd=0 above an early return** (joybus — avoid callee-saved spills).
- **declaration-only extern const float k;** (no in-TU initializer) so uses reference the named symbol (p_camera).
- **component-wise Vec copy** forces float lfs/stfs vs int lwz/stw; **shared loop-scope Vec** (disjoint lifetimes) shrinks the frame.
- **tools/permute_fn.py** — automated signedness/width brute-forcer; run on every sub-100% fn, **re-verify each hit on report.json**.

**Frame-size matching:** duplicate shared expressions/multiplies into each branch, or give by-value struct args their own temporaries, to match the target stack frame (pppRyj set_matrix 80->97; gobject update 0x3d0->0x2b0).

**FP-register-pressure matching (NEW — partially defeats the "register wall"):** when a function is opcode-correct but the target saves MORE callee-saved FP registers than your build (compare the prologue `stfd f18..f31` count + frame size vs `build/GCCP01/asm/<unit>.s`), **hoist the loop-invariant float/double layout constants/colors/coords into named function-scope `float`/`double` locals and reuse them across the draw loops** — MWCC then promotes them into callee-saved FP regs (f18-f31) and the prologue+frame converge to the target, snapping the body register-numbering into alignment. Decode WHICH values the target pins (trace each `stfd f29/f30/...`) and pin exactly those — over-promoting past the target's live range REGRESSES. (wm_menu DrawMCList 54->60.) NOTE: this only fixes an FP-SAVE-COUNT mismatch; pure FP-NUMBERING (f30 vs f31 with equal counts), GPR-numbering, and frame-size-from-an-extra-int-temp remain register walls.

**Re-derive from target asm — the source may be WRONG (NEW, the mega-lever):** on functions stuck far below ~75%, do not assume the decompiled C++ is behaviorally correct. Dump the full instruction diff and audit ARGUMENTS and EXPRESSIONS against the target: garbled/transposed call arguments, wrong constants, missing/extra subexpressions, invented gates that aren't in the binary. Fixing source-vs-binary divergence is worth 10-25pp at a stroke and unblocks every other lever. The binary is ground truth — even original-code BUGS (reading stale/uninitialized locals) must be reproduced. (wm_menu DrawMCList 59->85: 17 DrawRect call sites had first/last args garbled; menu_cmd CmdDraw 71.6->93.8: wrong cursor math, missing icon offsets.)

**Whole-function register webs via shared mutable locals (NEW):** when the target saves one MORE callee-saved FP/GPR than you and constant-hoisting fails, the original likely declares a few function-scope mutable locals (x, y, w, t...) REUSED by assignment in every block, instead of fresh block-scoped locals per section. These whole-function webs each pin a callee-saved register and push block locals outward (menu_cmd CmdDraw: t/x/y/w occupy f26-f29, pushing h to f24 → 8 FP saves, frame 0x170). Re-using one variable for several roles (fill reuses w; rowY reused for dateY/playY) is common in the original code.

**MWCC micro-idioms (menu_cmd campaign, battle-tested):** down-counting `for (i=n; i>0; i--)` auto-unrolls into the srwi./mtctr/andi./residual shape (don't hand-unroll); scalar locals get registers in DECLARATION ORDER and stack arrays lay out top-down in declaration order (reorder declarations to fix frames); `&storage->entries[idx]` written through a pointer var folds the +field-offset into the INDEX (addi idx,8; lhax) — caching a decayed pointer or inlining the access yields add+disp instead; re-evaluation-vs-caching is region-sensitive (cache only what the target keeps in a nonvolatile, re-derive at call sites); check array dims against actual writers (ChkUnite writes 5 pairs -> combo[5][2], the decomp's [2][2] was a real stack overflow).

**The unfolded-constant wall is BROKEN (wm_menu campaign):** (1) dead loop counters (`addi rX,rX,1` alongside `bdnz`) are COMPILER-UNROLL residue — the original source is a plain single-body loop that mwcc unrolls x2, leaving the counter's li/addi; DE-UNROLL hand-unrolled source, never hand-unroll. (2) The `li rX,k`+`slwi`+`lwzx` cluster = scoped `opt_propagation off` + `opt_lifetimes off` + manual unroll with a REASSIGNED index variable (`ti = 5; a[0]=t[ti]; ti = 6; ...`) — lifetimes-off forces serial register reuse, prop-off keeps the li from folding; the index must flow through a variable. (3) GPR saved-reg allocation follows a wrap-rotation rule: function-scope locals rank r31->r26 in declaration order but the FIRST-declared of the interference group wraps to the leftover volatile (r12) — declare the wrapped variable first. (4) drop `const` from short locals to flip lha/extsh orientation; split float decl/init to control f-reg assignment and load order.

**Saved-register ROTATION trigger decoded (bonus_menu CalcResultCloseAnim):** when a function-scope variable is REASSIGNED inside multiple (unrolled) loops, MWCC rotates the callee-saved assignment ring (another web steals r31, everything shifts). Fix: ONE function-scope web variable declared first (assigned the index count, with a block-scope byte-offset hoist), and give each later loop its OWN block-scope counter — reassigning the shared one rotates; per-loop block-scoped counters un-rotate, snapping this/apc/web and stmw into target positions. Probe-TU bisecting works for some functions (full-function standalone probe matches real prologue) but diverges for others — verify probe fidelity before trusting it. (CalcResultOpenAnim has a different, unidentified rotation trigger — still wedged.)

**Statement-order permutation rotates FPR vreg assignment (cheap, high-yield):** independent adjacent statements (e.g. four int->float round-trip conversions) sweep FPR numbering with their ORDER — a 20-permutation sweep of sx/sy/sw/sh order took DrawMcWin 87.3->90.2. Sweep orderings of adjacent independent statements before declaring a function register-walled. Also: manual DOUBLE_80331408-bias conversions pay only at fsub (int->double) sites — hoist the bias as a preheader const in loops (target keeps it in a callee-saved FPR), write lo word before hi, and read aliased members in the [1]= RHS before any union store; int->float (fsubs) sites must stay automatic casts.

**MWCC saved-register RANKING RULE decoded (bonus_menu probe campaign):** callee-saved GPRs assign descending from r31 in this priority: (1) "maybe-undef" stealer webs — a var assigned in only one branch and read later under the same condition steals r31 and rotates the ring (fix: merge it with its else-branch twin into ONE variable defined on both paths); (2) `this`; (3) address-constant webs (anchor = lbl_*); (4) function-scope locals in DECLARATION order (verified to 8/11 register positions); (5) block-scope webs in creation order. CLOSED AS DEAD-END: some targets rank a hot loop-bound local ABOVE this+anchor — a full 128-combo sweep of all 7 opt-pragma regimes plus ~20 source perturbations never flips the top-3; unreachable from this mwcc config. Accept the ~1-3pp residual on affected functions. Tooling: /tmp/apcwrap_regmap.sh, /tmp/apcwrap_webs.sh, /tmp/apcwrap_stateF.cpp (a CalcSelectCloseAnim body with the lower 8 regs already correct — any regime that flips the top-3 wins ~3pp).

**Ranking-rule refinements (bonus rank-pass):** merged branch-defined webs sink to the BOTTOM saved reg; ranking is post-DCE (dead initializers don't unsink); `idx++` chaining (instead of `idx = N` per block) merges serial block webs into ONE register; target `mr`-copies of zero-valued vars come from strength-reduction induction temps of ARRAY INDEXING (a[i] forms), never from explicit copies (those always fold to li) — rewrite explicit byte-offset arithmetic as array indexing to reproduce them.

**Literal-vs-extern float refs steer FPR webs AND scheduling (bidirectional):** named FLOAT_/DOUBLE_ extern refs create USER webs (forward-decl order, never hoisted in loops); plain literals create COMPILER constant webs (reverse-first-use rank, hoisted) — choose per-site to match the target. extern->literal flipped a 12-insn scheduling cluster wholesale (DrawWMFrame0 86->100); literal->extern snapped CalcMcObj f24-f31. Also: decouple decl order from init order (`int a; int b = 0; a = X;`) to keep decl-rank webs with target init emission order; GetFcvValue(FCV,float) is inlined by MWCC (dead stw pairs = by-value FCV param homes) — use the call form at spline sites.

**Orphaned .sdata2 literal-pool re-attribution (project-level mega-lever, wm_menu +1.18pp unit):** if a unit's targets reference named FLOAT_/DOUBLE_ pool symbols that no split owns (check for a gap right after the unit's .sdata2 range in config/GCCP01/splits.txt), the gap is likely the unit's original literal pool: extend the split end over the gap and DEFINE all the pool symbols in the .cpp in address order (values byte-exact from the DOL, defs at TOP of file — late defs land in wrong sections). mwcc folds visible-initializer extern consts back to @anon literals which objdiff matches BY VALUE — code relocs then match. wm_menu claimed 0x803311BC-0x80331848 (267 symbols): +1.18pp, 4 functions to 100%, ~9 functions regress slightly where folding lets mwcc CSE equal-valued distinct symbols (recoverable per-function). KNOWN REMAINING GAPS worth checking by their bucket owners: p_chara +0x228, gobjwork +0x138, menu.cpp +0xe0, map.cpp +0xe0, pppYmMelt +0xac, maphit +0x7c, p_gba +0x40, pppShape +0x28.

**Anti-folding named-pointer lever (post-pool-claim; WmInit/DrawFilter -> 100%):** after a literal pool is claimed (defs visible), force a NAMED reloc with `const float* p = &FLOAT_x;` declared IMMEDIATELY before the consuming statement, then `*p` — compiles to direct lfs sym@sda21 (inline `*&FLOAT_x` folds; early decls before calls get materialized li+pinned; loop-invariant derefs hoist into spare FPRs — if ours has a spare reg where target loads fresh, keep the folded literal instead). Manual raw-bit int->double conversions are now a NET LOSS post-pool (temp leaves the conversion-temp stack area); plain casts win. Re-score known inliner-callers after editing small shared functions (inline-size threshold: GetFcvValue + pointer locals silently became a call, -40pp in a caller). Stale scoped pragmas can become harmful after structural changes — retest removing them (WmInit's peephole-off was the last blocker to 100).

**Statement-order sweeps are the top payer on register/scheduling residue (re-sweep after every structural win — results are base-sensitive):** 24-permutation sweep of 4 GXColor component assignments +1.34; init-order swap +1.30 (DrawCMLife 89.6->93.0). FPR decl/init decoupling fixes pairwise FPR swaps but rank direction is region-inconsistent — always measure. The `fmr fX-vs-fY same source + stfs stack-arg swap` signature detects transposed float args cheaply. CAUTION: tools/permute_drive_safe.sh resets the branch to origin/main — destructive for local commit stacks; run tools/permute2.py directly when stacking.

## CONFIRMED DEAD-ENDS (do not spend time here)
- **MWCC optimizer-budget walls on huge functions** (bonus_menu CalcResultOpenAnim ~81%): the target mixes propagation-ON folds (folded unroll entry tests, folded IV inits) with propagation-OFF materializations (`li 0; slwi`, `mr` copy-inits) in ONE function — impossible from any single pragma config; rigorously swept (all opt pragmas x both propagation settings). Likely the global optimizer's budget partially processing 8KB+ functions. Do not burn agent rounds on pragma hunting here; only close source-structure recovery moves these. Probe tooling: /tmp/croa_lab/.
- **.rodata/.sdata2 pool ORDER is score-irrelevant** — objdiff matches relocations by target SYMBOL name, not numeric offset. Reordering string/const declarations does nothing. (Proven: map .sdata2 made byte-identical -> 0 score change.)
- **CColor ctor inlining** — the original calls it out-of-line; inlining breaks linkage. Copy-ctor is non-const-ref (__ct__6CColorFR6CColor) and correct as-is.
- **Anonymous compiler-pool conversion magics** (@NNNN int->double bias) cannot be forced to a named symbol.
- **Pure register-allocation/numbering & instruction-scheduling cascades** (this in r30 vs r31, one extra callee-saved reg, mtctr vs subic when the target chose it, FIFO base-register choice) — not reachable from plausible C with this MWCC; the true ceiling. Would need a C++ register-allocation permuter (decomp-permuter cannot parse C++).

---
## B1 Menus (primary)
**4 units · 40,103 unmatched bytes**

| unit | % | code | unmatched |
|---|---:|---:|---:|
| `src/wm_menu.cpp` | 86.2 | 115740 | 15996 |
| `src/bonus_menu.cpp` | 70.2 | 45452 | 13555 |
| `src/menu_cmd.cpp` | 76.0 | 23176 | 5571 |
| `src/MenuUtil.cpp` | 72.5 | 18136 | 4981 |

## B2 Menus (secondary) + cflat + sound
**30 units · 41,236 unmatched bytes**

| unit | % | code | unmatched |
|---|---:|---:|---:|
| `src/shopmenu.cpp` | 85.9 | 37516 | 5294 |
| `src/cflat_r2system.cpp` | 83.7 | 31244 | 5085 |
| `src/menu_letter.cpp` | 77.9 | 17544 | 3886 |
| `src/gbaque.cpp` | 90.1 | 35712 | 3549 |
| `src/cflat_runtime.cpp` | 80.2 | 15964 | 3155 |
| `src/cflat_runtime2.cpp` | 88.9 | 20476 | 2281 |
| `src/mesmenu.cpp` | 80.6 | 11484 | 2233 |
| `src/singmenu.cpp` | 90.2 | 21836 | 2136 |
| `src/ringmenu.cpp` | 78.6 | 9656 | 2063 |
| `src/menu_equip.cpp` | 80.9 | 9792 | 1873 |
| `src/mes.cpp` | 86.1 | 12740 | 1777 |
| `src/cflat_r2class.cpp` | 90.5 | 13644 | 1302 |
| `src/p_minigame.cpp` | 91.6 | 14040 | 1182 |
| `src/menu_compa.cpp` | 84.7 | 5252 | 804 |
| `src/menu_money.cpp` | 87.6 | 5804 | 720 |
| `src/p_menu.cpp` | 95.2 | 14688 | 708 |
| `src/menu_favo.cpp` | 89.2 | 5612 | 604 |
| `src/menu_item.cpp` | 91.4 | 6916 | 595 |
| `src/menu_arti.cpp` | 90.2 | 5300 | 518 |
| `src/RedSound/RedExecute.cpp` | 98.0 | 17588 | 353 |
| `src/sound.cpp` | 97.9 | 15028 | 322 |
| `src/RedSound/RedCommand.cpp` | 96.6 | 6404 | 221 |
| `src/RedSound/RedDriver.cpp` | 98.8 | 12328 | 149 |
| `src/menu_lst.cpp` | 96.6 | 3476 | 117 |
| `src/menu_tmparti.cpp` | 96.7 | 3044 | 102 |
| `src/p_dbgmenu.cpp` | 98.9 | 7404 | 82 |
| `src/RedSound/RedEntry.cpp` | 99.5 | 10700 | 55 |
| `src/THPSimple.cpp` | 99.4 | 6324 | 39 |
| `src/RedSound/RedStream.cpp` | 99.4 | 4344 | 27 |
| `src/wmm_str.cpp` | 99.8 | 1408 | 3 |

## B3 Characters, Objects & Particles
**62 units · 47,878 unmatched bytes**

| unit | % | code | unmatched |
|---|---:|---:|---:|
| `src/chara_fur.cpp` | 62.6 | 20676 | 7732 |
| `src/partyobj.cpp` | 85.2 | 42020 | 6225 |
| `src/charaobj.cpp` | 84.7 | 30452 | 4661 |
| `src/p_chara.cpp` | 86.1 | 32924 | 4575 |
| `src/partMng.cpp` | 88.7 | 32648 | 3689 |
| `src/monobj.cpp` | 88.0 | 30752 | 3676 |
| `src/chara.cpp` | 84.8 | 20464 | 3116 |
| `src/pppRyjMegaBirthModel.cpp` | 84.1 | 15628 | 2488 |
| `src/pppYmMegaBirthShpTail3.cpp` | 81.0 | 8712 | 1659 |
| `src/pppYmMegaBirthShpTail2.cpp` | 81.7 | 7636 | 1396 |
| `src/pppPart.cpp` | 91.0 | 14992 | 1352 |
| `src/pppRyjMegaBirth.cpp` | 84.5 | 8044 | 1245 |
| `src/itemobj.cpp` | 91.1 | 9360 | 830 |
| `src/monobj_boss.cpp` | 95.7 | 19244 | 827 |
| `src/pppYmMana.cpp` | 94.8 | 14996 | 782 |
| `src/FunnyShape.cpp` | 88.4 | 6684 | 776 |
| `src/pppMana2.cpp` | 95.5 | 12376 | 563 |
| `src/pppKeShpTail3X.cpp` | 91.7 | 4448 | 371 |
| `src/pppKeShpTail2X.cpp` | 88.7 | 2964 | 335 |
| `src/p_tina.cpp` | 96.7 | 7628 | 252 |
| `src/pppCharaBreak.cpp` | 96.9 | 6196 | 192 |
| `src/pppYmEnv.cpp` | 98.0 | 6532 | 133 |
| `src/pppYmDeformationShp.cpp` | 98.2 | 5908 | 105 |
| `src/pppScreenBreak.cpp` | 98.0 | 4484 | 91 |
| `src/pppLaser.cpp` | 98.5 | 4956 | 76 |
| `src/pppYmLaser.cpp` | 98.4 | 4612 | 75 |
| `src/pppYmTracer.cpp` | 97.6 | 3032 | 72 |
| `src/pppYmChangeTex.cpp` | 97.4 | 2596 | 68 |
| `src/p_chara_viewer.cpp` | 99.1 | 7640 | 65 |
| `src/p_FunnyShape.cpp` | 97.4 | 2364 | 62 |
| `src/pppMiasma.cpp` | 99.0 | 6176 | 59 |
| `src/pppChangeTex.cpp` | 97.9 | 2620 | 55 |
| `src/LocationTitle2.cpp` | 98.6 | 2184 | 31 |
| `src/pppYmMelt.cpp` | 99.2 | 3136 | 26 |
| `src/pppYmBreath.cpp` | 99.6 | 6464 | 24 |
| `src/pppRain.cpp` | 98.7 | 1748 | 22 |
| `src/chara_anim.cpp` | 99.1 | 2136 | 20 |
| `src/pppBreathModel.cpp` | 99.7 | 6412 | 20 |
| `src/pppLocationTitle.cpp` | 99.1 | 1760 | 16 |
| `src/pppYmTracer2.cpp` | 99.3 | 2276 | 15 |
| `src/pppCrystal.cpp` | 99.5 | 2692 | 13 |
| `src/prgobj.cpp` | 99.5 | 2892 | 13 |
| `src/pppCrystal2.cpp` | 99.5 | 2304 | 12 |
| `src/pppYmDrawMdlTexAnm.cpp` | 99.5 | 2100 | 10 |
| `src/pppColum.cpp` | 99.5 | 1732 | 8 |
| `src/pppYmDeformationMdl.cpp` | 99.6 | 1808 | 7 |
| `src/pppShape.cpp` | 99.7 | 1588 | 5 |
| `src/pppYmMoveParabola.cpp` | 99.5 | 1028 | 5 |
| `src/quadobj.cpp` | 99.5 | 956 | 5 |
| `src/pppRandCV.cpp` | 99.5 | 540 | 3 |
| `src/pppRandHCV.cpp` | 99.5 | 524 | 3 |
| `src/pppRandIV.cpp` | 99.5 | 456 | 2 |
| `src/pppRandDownHCV.cpp` | 99.6 | 456 | 2 |
| `src/pppRandUpHCV.cpp` | 99.6 | 456 | 2 |
| `src/pppRandDownCV.cpp` | 99.6 | 472 | 2 |
| `src/pppRandUpCV.cpp` | 99.6 | 472 | 2 |
| `src/pppRandDownIV.cpp` | 99.6 | 404 | 2 |
| `src/pppRandUpIV.cpp` | 99.6 | 404 | 2 |
| `src/pppYmMiasma.cpp` | 100.0 | 3544 | 1 |
| `src/pppConstrainCameraDir.cpp` | 99.8 | 584 | 1 |
| `src/pppRandDownFV.cpp` | 99.7 | 304 | 1 |
| `src/pppRandUpFV.cpp` | 99.7 | 304 | 1 |

## B4 Engine / Graphics / Map / Memory / System
**36 units · 36,191 unmatched bytes**

| unit | % | code | unmatched |
|---|---:|---:|---:|
| `src/joybus.cpp` | 86.7 | 51292 | 6796 |
| `src/cmake.cpp` | 83.2 | 31248 | 5256 |
| `src/gobject.cpp` | 88.4 | 25656 | 2976 |
| `src/p_camera.cpp` | 83.3 | 17260 | 2885 |
| `src/p_graphic.cpp` | 72.2 | 10168 | 2830 |
| `src/goout.cpp` | 86.7 | 18616 | 2472 |
| `src/map.cpp` | 89.9 | 21804 | 2196 |
| `src/materialman.cpp` | 93.3 | 31576 | 2116 |
| `src/mapobj.cpp` | 90.1 | 16180 | 1608 |
| `src/gobjwork.cpp` | 93.4 | 19476 | 1286 |
| `src/graphic.cpp` | 94.6 | 15240 | 822 |
| `src/memory.cpp` | 94.8 | 15236 | 797 |
| `src/memorycard.cpp` | 94.8 | 13856 | 715 |
| `src/p_light.cpp` | 95.1 | 9888 | 486 |
| `src/maphit.cpp` | 95.6 | 10516 | 465 |
| `src/astar.cpp` | 95.1 | 6984 | 344 |
| `src/p_map.cpp` | 95.1 | 6408 | 314 |
| `src/mapocttree.cpp` | 98.0 | 11608 | 228 |
| `src/p_MaterialEditor.cpp` | 95.9 | 5376 | 222 |
| `src/game.cpp` | 97.8 | 9616 | 214 |
| `src/textureman.cpp` | 97.1 | 7100 | 203 |
| `src/ME_USB_process.cpp` | 96.1 | 4832 | 188 |
| `src/util.cpp` | 98.2 | 10044 | 177 |
| `src/pad.cpp` | 94.9 | 3392 | 174 |
| `src/fontman.cpp` | 97.5 | 4820 | 118 |
| `src/gxfunc.cpp` | 93.7 | 1576 | 99 |
| `src/wind.cpp` | 97.7 | 3512 | 82 |
| `src/FS_USB_Process.cpp` | 99.1 | 3524 | 32 |
| `src/p_usb.cpp` | 97.6 | 1320 | 31 |
| `src/maptexanim.cpp` | 99.1 | 2796 | 24 |
| `src/texanim.cpp` | 99.7 | 5128 | 14 |
| `src/file.cpp` | 99.8 | 4548 | 7 |
| `src/mapanim.cpp` | 99.8 | 3376 | 6 |
| `src/math.cpp` | 100.0 | 8384 | 4 |
| `src/main.cpp` | 99.5 | 680 | 4 |
| `src/ME_AppRequest.cpp` | 99.7 | 744 | 2 |
## Balance
| Bucket | units | unmatched |
|---|---:|---:|
| B1 Menus (primary) | 4 | 40,103 |
| B2 Menus (secondary) + cflat + sound | 30 | 41,236 |
| B3 Characters, Objects & Particles | 62 | 47,878 |
| B4 Engine / Graphics / Map / Memory / System | 36 | 36,191 |
| **Total** | **132** | **165,408** |

Notes: B1 is only 4 units but huge (wm_menu alone 116KB) — few long agents. B3 has the most units (62, many tiny ppp*) — most agents, run in waves. Likely cross-unit shared headers: menu (B1/B2), chara/particle bases (B3), gobject.h/map.h/vector.h (B4) — coordinate via [cross] fast-merges.
