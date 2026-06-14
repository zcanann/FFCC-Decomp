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

**DATA matching (escalation axis when code is walled):** raises matched_data_percent toward byte-identical but typically does NOT move fuzzy_match_percent (unit fuzzy is code-weighted) — it's free correctness, not a headline-number lever. Mechanics: (1) section placement is part of symbol identity — a symbol with identical name+bytes still mismatches if it's in .sdata2 vs .rodata; match config/GCCP01/symbols.txt's section attribute via `extern "C" __declspec(section ".rodata") const ...` (extern "C" MUST precede __declspec; MWCC defaults small strings to .sdata2 — the #1 data bug). (2) one named `lbl_XXXX[N]` blob beats N individually-named sub-strings where the target has one symbol. (3) pad section ends to alignment with a sized static array. (4) data relocs match by symbol NAME. (MenuUtil data 32.5->95.5 via a 2-line section-attribute fix.)

## CONFIRMED DEAD-ENDS (do not spend time here)

**sdata2/reloc avenue CLOSED (both experiments negative + calibration):** sdata2-layout-reorder cascade hypothesis DISPROVEN on bonus_menu AND singmenu (unit fuzzy unchanged). Crucial calibration: objdiff CODE-reloc matching keys on the reloc's TARGET VALUE/address, not the symbol NAME — so @NNN-vs-named on the same address does NOT cost TEXT fuzzy (it shows as a cosmetic "arg_reloc" in classify_diff but isn't a real text-fuzzy loss). Implication: STOP treating arg_reloc/@NNN counts as opportunities; the real remaining text gap is register-allocation + scheduling + missing/extra code ONLY. Do NOT pursue the separate-real-TU architectural swing (the gap it targets doesn't score). classify_diff's arg_reloc column = mostly noise; focus on its miss/extra/struct columns.

**#1 CROSS-BUCKET LEAD — the @NNN float-reloc root cause (dominates the remaining gap project-wide):** MWCC's `-str pool` interns the VALUES of `extern const float/double` definitions into anonymous `@NNN@sda21` pool slots WHENEVER the definitions are visible in the same TU. So our float/double loads reference `@NNN` while the TARGET references the NAMED symbol (kX@sda21) — every float-heavy function loses points on this, the single biggest residual across wm_menu/bonus_menu/menu_cmd/shopmenu/singmenu/MenuUtil. Confirmed: the .sdata2 DATA layout itself already matches 100% (reorder/section/`-str pool` removal do NOT fix the CODE relocs). The target emits NAMED refs because its constants were NOT defined-with-initializer in the referencing TU. FLAG TEST DONE (negative): toggling bonus_menu's `-str reuse,pool,readonly` -> `-str reuse` is SCORE-NEUTRAL — the @NNN interning is NOT controlled by -str pool; it is intrinsic MWCC fp-constant codegen. Only escape would be declaration-only externs with defs in a separate REAL TU owning the .sdata2 (the variant-B un-claim test was net-negative via data-accounting). Treat the @NNN fp-reloc gap as a genuine toolchain wall unless someone proves the separate-real-TU architecture; do NOT chase -str flags (confirmed no-op).
- **bonus_menu CalcResultOpenAnim 80% = compiler-version spill-strategy wall (root cause, 3 agents confirm):** the TARGET frame is 64 bytes LARGER (0x1f0 vs our 0x1b0) because its MWCC gave each fctiwz->stfd->lwz intermediate in the 8x-unrolled board-coord loop (src ~3704-3721) a UNIQUE spill slot (16 extra), while our allocator reuses slots across iterations. This frame delta is the ROOT of the activePartyCount r30-vs-r31 cascade. Not source-reachable (pragmas no-effect/regress). RETIRED — do not re-grind.
- **GXColor "param-home" stack placement = characterized scheduling wall (not source-fixable):** the plain idiom `GXColor c; c.r=..; GXSetChanMatColor(id, c);` DOES build the color in the outgoing-param scratch (matches target — see wm_menu DrawFilter 100%). BUT when the color feeds a call with a `this`/r3 arg (e.g. `font->SetColor(...)` virtual dispatch), MWCC's `addi r4,r1,<scratch>` vs `mr r3,<this>` scheduling order diverges from target and is tied to opt_propagation (toggling regresses the function's loops). Intrinsic to this MWCC version. Dominant residual in shopmenu Draw* and recurs in wm/menu_cmd — accept it. DOUBLE_80332D20-vs-@702 anon-reloc on int->double bias is the other shopmenu floor.

**Source-has-EXTRA-logic the binary lacks (structural, recurring):** the decomp sometimes adds defensive null-checks / guards / branches that the ORIGINAL binary does NOT have (it dereferences unconditionally, or the check was in a different form). High extra_code count in classify_diff = look for invented guards to REMOVE. (wm_menu CalcMainMenuSub: removing spurious null checks on world handles +1.57; bonus createBonus earlier: missing s_Rinfo null-check the binary HAS — works both directions: add what's missing, remove what's invented.) Also winning repeatedly: bool/void/unsigned->s32/int type-correction (target cmpwi/mr where ours clrlwi./extsh — decomp mis-guesses types), compare-operand swap (`x==C`->`C==x` for cmpw order), hoist-local-before-call, unsigned-cast->int-cast (kills __cvt_fp2unsigned bl).

**classify_diff.py caveat + unsigned-cast lever:** the tool's "fixable" count is a HEURISTIC (mismatch categories), NOT the score — a change can lower fixable-count yet REGRESS fuzzy (GXColor-local->param-home reduced Draw's mismatch count but dropped it -0.5). Always gate on report.json fuzzy, never on the classifier count. WIN found: `static_cast<float>(static_cast<unsigned int>(x))` emits a `__cvt_fp2unsigned` library CALL; if the value is non-negative, use `static_cast<float>(static_cast<int>(x))` (plain fctiwz) — and declare the int BEFORE the next call so the convert schedules ahead of it (shopmenu DrawBuySellInfo +1.37). GXColor param-home (target builds GXColor temporaries at sp+0x8 outgoing-param area vs our named locals) resisted inline-construction attempts — still OPEN, not confirmed dead.
- **B1 source-reachable ceiling reached (~98.0% overall):** wm_menu 94.89, menu_cmd 96.53, MenuUtil 96.21, bonus_menu 90.87. Exhausted across ALL axes by many independent agents: code (register/scheduling/named-vs-anon walls), data (only MenuUtil string-sections + wm DAT-case were fixable; rest are code-artifacts), pragmas (only WMChgMenu +0.58), permuter (tapped on every unit), structural pool experiments (wm_menu CLAIM orphaned pool = +1.18 MERGED; bonus_menu UN-CLAIM = net-negative REVERTED). Dominant residual = MWCC int->double bias magic (@NNN anon pool, e.g. 0x4330000080000000) which the compiler emits anonymously regardless of external decl — the documented hard dead-end — plus register-allocation cascades not reachable from plausible C++. Further gains here require toolchain/objdiff symbol-attribution changes (maintainer-level), not source edits.
- **DATA axis exhausted across B1 (only MenuUtil had fixable data):** menu_cmd (52.8%) and bonus_menu (83.2%) data ceilings are already hit — all remaining data mismatches are CODE ARTIFACTS (extab/extabindex entries encode each function's size, sdata2 holds anon @NNN float literals from function bodies). They only move when the FUNCTIONS reach 100%. Don't spawn data agents on these. MenuUtil (string section-attrs) and wm_menu DAT-case were the only fixable data wins in B1.
- **operand-eval-order / subexpr-reuse / literal-arg levers (NEW — biggest fresh-surface wins: BindEffect +5.8, DrawRect2 +3.0, DrawRect3d +1.6, DrawMcWin +1.5):** the target's exact EXPRESSION STRUCTURE often differs from ours in ways that change codegen:
  (a) **operand-eval-order via named temp:** hoist a subexpression into a named local so it evaluates BEFORE its sibling operand — e.g. BindEffect `(effectNoXor>>1) - (effectNoXor & effectNo)` -> `const int half = effectNoXor>>1; half - (effectNoXor & effectNo)` forces the shift first (matching target), +5.8pp.
  (b) **non-const-int to force li+op:** `effectNo ^ 100` (xori) vs target `li r,100; xor` -> use `int hundred=100; effectNo ^ hundred`.
  (c) **literal-not-field const arg:** a call argument that is a hard constant in the binary but a field-read in our source — DrawRect2 passed `out[i].z` where the target uses literal `0.0f` (FLOAT_803313dc); hoist the literal to a named local above the loop so it pins once (+3.0pp). Check every draw-call coordinate/flag arg: is it really a field, or a constant?
  (d) **subexpression reuse:** target reuses a just-computed value where ours recomputes from the original — DrawRect3d `v0 = (v1 + h) - halfTexel` REUSES v1, not `(ty + h) - halfTexel` (+1.6pp).
  (e) **int->double conversion statement order:** reorder the conversions (e.g. sx/sy/sw/sh) to match the target's stack-temp slot assignment (DrawMcWin +1.5pp).
  These are the highest-yield structural levers for draw/arithmetic functions — look for them before declaring a register wall.
- **scoped `#pragma opt_propagation off` lever (NEW, +2.53 on menu_cmd UniteCloseAnim):** when the TARGET materializes an index/address (e.g. `li r12,0; slwi r6,r12,2; add r7,r4,r6` for `&arr[i]` with i provably 0) but OURS constant-FOLDS it to the bare base (`mr r8,r4`), wrap the function in `#pragma push` / `#pragma opt_propagation off` ... `#pragma pop`. This defeats MWCC's constant-propagation so the index materializes like the target. Apply to functions whose diff shows target `li/slwi/add` (or `li N` then compute) where ours emits a folded `mr`/bare-base. CAUTION: opt_propagation off ALSO changes float-literal-pool behavior (function-local @NNN bias literals) and register pressure — gate on the UNIT score, it can regress other parts of the same function. This is the legitimate scoped-pragma lever (different from global pragma hacks); it reproduces the original's actual codegen regime. Candidates to try: bonus DrawSelectOpenAnim/CalcResultCountAnim (frozen `__p3=i` index guards), menu_cmd CmdInit1, any function with a folded-index-vs-materialized-index mismatch.
- **branch-layout + adjacent-buffer-read lever (NEW, +2.18 on wm ChkNowData):** (1) `if (cond) {error; return;} success;` where the binary puts SUCCESS as fall-through -> rewrite as `if (!cond) {success} else {error; return;}` to match the target's block order (same class as shopmenu CanTrade). (2) A struct field written from a separate uninitialized local (`m_serialHi = serialHi;`) where the target reads an ADJACENT buffer word -> `m_serialHi = *(&serialLo + 1);` (read the high word the way the sibling cases do). Hunt for uninitialized-local writes that should be adjacent-buffer reads.
- **volatile-loop-start lever (NEW, +0.81 on wm CalcCharaSelect — potentially cracks "loop-form walls"):** when the TARGET uses a counted `mtctr`/`bdnz` loop (often 8-way unrolled + a remainder loop with `subfic rN,rN,0x4` trip-count) but OURS FULLY UNROLLS, the cause is MWCC proving the loop's START value is a compile-time constant (e.g. `for (int i = anyTrig; i<4; ...)` where anyTrig folds to 0). Mark the start variable `volatile` (e.g. `volatile ... requestCancel`) so MWCC can no longer fold it and emits the target's counted loop. RE-TEST this on every "loop-form / subic.-vs-bdnz / full-unroll-vs-counted" wall: menu_cmd ChkUnite (88.96, the documented loop-fusion wall), bonus CalcResultOpenAnim/CloseAnim (unrolled-loop spill core — if target's loop is counted and ours unrolls, volatile may collapse the frame-size delta), wm DrawCMakeMenu (loop IV mr-vs-mulli). This DISPROVES "loop-form is an unreachable compiler choice" for the constant-foldable-start case.
- **named-pointer anti-folding lever (NEW, +0.11 on wm DrawMainMenuSub — @NNN is NOT always cosmetic):** referencing an inline float/double constant via `const float* p = &FLOAT_x; ... *p` (instead of the bare `FLOAT_x`) forces MWCC to emit a NAMED `FLOAT_/DOUBLE_@sda21` reloc instead of interning the value into an anonymous `@NNN` pool slot. CORRECTION (confirmed on wm round-3): report.json's fuzzy scorer treats `@NNN@sda21` and `named@sda21` as EQUIVALENT (same reloc type + target value) — converting @NNN->named is a NO-OP on report.json (verified byte-identical on DrawTitleMenu/CalcLoadMenu). DrawMainMenuSub's small gain came from the `*p` deref incidentally changing instruction SCHEDULING, not the naming. So: do NOT chase @NNN-vs-named for the reloc naming itself (cosmetic on report.json, matching the original calibration); only useful as a scheduling perturbation, which is unpredictable — gate per-edit and don't rely on it.
- **modulo-as-subtraction lever (NEW, +0.88 on wm CalcMCardMenu):** where the source computes a round-up via the already-computed quotient — `iLines = x / N; if (x - iLines*N != 0) iLines++;` — MWCC reuses the single quotient, but the TARGET computes the quotient TWICE (a `/N` and an independent `%N`, visible as duplicate srawi/add quotient sequences). Rewrite the remainder test using the real `%` operator: `if (x % N != 0) iLines++;`. This forces MWCC to emit the second quotient and matches the target. SCAN for hand-rolled `x - (x/N)*N` remainder patterns and replace with `x % N`.
- **GetItemType-style redundant-complement-if lever (NEW, singmenu GetItemType 94->100):** a terminal `if (x <= K) return A; return B;` returning constants differing by 1 folds into MWCC's branchless carry trick (xoris/subfic/addc/subfe). To force the target's BRANCHY form, add a redundant complementary tier: `if (x < K+1) return A; if (x >= K+1) return B; return B;` — the redundant second `if` defeats the carry-fold and MWCC elides the now-provably-redundant compare, leaving clean branchy code. Use when a tail two-way constant-return compiles branchless but the target is branchy.
- **segW conversion-hoist lever (NEW, +2pp each on bonus DrawResultOpenAnim/CloseAnim):** an inline DrawRect/call argument of the form `(float)(DOUBLE_x / (double)field) * (float)field2` (int->double bias conversions inline in the arg list) makes MWCC stage the `lha/xoris/stw/lfd/fsub/fdiv/fmuls/fctiwz` conversion cluster in a different order/slot layout than the target. HOISTING it into a named local `float segW = ...;` immediately before the call forces the target's conversion ordering. SCAN every unit for inline `(float)(double-expr) * (float)field` (or similar conversion-heavy) call args and hoist them to named temporaries. This is the transferable structural lever that disproves the "it's just scheduling" framing — the scheduling IS steerable via the temporary.
- **Pure operand-identical signed/unsigned opcode-fix lever SWEPT PROJECT-WIDE (exhausted this round):** scanned all 6 B1 units for rows where TARGET and OURS differ ONLY in a signed/unsigned opcode variant (lha/lhz, cmpw/cmplw, cmpwi/cmplwi, srawi/srwi) with IDENTICAL operands — these are the only type-fixes that can win without triggering a register cascade. Found exactly 5 in all of B1; all dispositioned: DrawCMakeMenu insn589 `srwi r4,r0,31` (m_nextMenuMode>>31 unsigned) — fixing it via triple-cast REGRESSED -0.5 (cascade); UniteOpenAnim insn90/123 `cmpwi r11,0` (loop var j) — `unsigned int j`->`int j` REGRESSED (prior agent + confirmed); DrawHelpMessageUS insn679 `cmplwi r0,1` — MWCC folding-cast wall (per MenuUtil agent); CalcFukidashi insn79 `lha 0x1c` — source read is already `short` (signed), the lhz originates elsewhere/ambiguous. NET: the localized type-fix wins were already harvested (MenuUtil m_cmdLayoutFlag, shopmenu canTrade polarity, singmenu, bonus s_ArtiTop, wm CalcFukidashi/DrawMCList unsigned, DrawSingleStat y-4, DrawBonusFrame 8->32/16->64). Remaining type-opcode mismatches all sit inside register cascades (operands differ too) = not isolable. STOP re-scanning signed/unsigned; the lever is dry.
- **B1 ROUND EXHAUSTION RECORD (evidence-based, NOT premature):** every B1 unit explored via 10+ deep agent passes + all free-permuter lanes (every unit, multiple function sets, all noop) + a Haiku structural-triage pass + project-wide type-fix sweep + direct analysis. Residual gap is the documented compiler-version wall floor: address-materialization-into-callee-saved cascades (most wm Calc/Draw + DrawOptionMenu + CalcMCardMenu), spill-strategy frame size (bonus CalcResult*Anim), GXColor param-home scheduling (shopmenu), loop-form fusion (menu_cmd ChkUnite), terminal branchless-select (GetItemType), @NNN fp-reloc (cosmetic). Resuming the structural agent fleet requires the Sonnet quota reset (was rate-limited mid-round) or toolchain/objdiff-attribution changes (maintainer-level). All source-reachable wins for this round are merged to pr/B1/1781314927.
- **Address-materialization-into-callee-saved cascade wall (MenuUtil DrawOptionMenu 94.57%, recurring class for float+string-table functions):** a near-equal miss≈extra split (here 49/50, +25 struct, +739 arg_mismatch) is a SINGLE-ROOT cascade, not many independent issues. Root-caused to ONE instruction: target does `lis r5, SYM@ha` (volatile scratch, address recomputed near use, callee-saved web only live late) while our MWCC does `lis r17, SYM@ha` (callee-saved, web live ~38 insns earlier). That extended live-range shifts the whole callee-saved chain by 2 (font ptr r16→r18), pushes slwi chains onto volatiles r3/r4, spills the 0x4330 int->double bias to r30, and cascades GPR mismatches across the entire function. NOT source-reachable: pre-computing the sin/cos argument to mimic the target's store-the-arg pattern REGRESSED -0.09 via adjacent scheduling. The address-constant web ranks #3 in the saved-GPR ranking rule but we cannot force it to a volatile from C++. When you see a big miss≈extra split, FIND the first real divergence (it collapses the rest) — but if the root is this address-materialization or a register-number-only shift, it is a wall; do not force regressions chasing the phantom downstream pairs.
- **Terminal branchless-select codegen wall (singmenu GetItemType 94.1%, recurring class):** a final `if (x <relop> K) return A; return B;` as the LAST two statements of a function returning small constants triggers MWCC's branchless-select (xoris/subfic/addc/subfe/addi or li/srwi/subfc/subfe/addi) even though the TARGET kept it branchy (cmpwi K; bge/bgt; li A; blr; li B; blr). All earlier tiers in such a chain stay branchy only because each is followed by more code (non-terminal). Source-form attempts ALL fail/regress: `<=K`→94.1 (baseline branchless), `<K+1`→87.7, `>K`→85.8 — every relop/operand-swap still selects. No plausible C++ suppresses the terminal-two-way select in this MWCC config. Accept the ~5-instruction residual. Sibling pure-register cascades in same unit (GetSmithItem 95.8, GetRaceStr 99.4, ChkEquipPossible 97.2) have 0 reconstructable mismatches (opcodes/operands identical, only register NUMBERS differ from an early temp-allocation shift; source statement-reorder is codegen-neutral — MWCC reorders internally). Do not re-grind these.
- **wm_menu DATA axis is a dead-end (3.6%, unfixable from data defs):** the .data jumptables + .sdata2/.extab bloat are CODE artifacts — McCtrl methods (EraseDat/SaveDataBuffer/etc.) share the TU and emit switch jumptables + anon float literals as raw @NNN symbols; only improving those FUNCTIONS' code match (or splitting the TU) moves it. Contrast MenuUtil data (string section-attributes) which WAS fixable. Pending micro-fix needing paired def+ref edit: DAT_8032e8c8/cc case vs symbols.txt (referenced in WM_MENU_EVAL_SPLINE at ~lines 7686/7698).
- **MWCC optimizer-budget walls on huge functions** (bonus_menu CalcResultOpenAnim ~81%): the target mixes propagation-ON folds (folded unroll entry tests, folded IV inits) with propagation-OFF materializations (`li 0; slwi`, `mr` copy-inits) in ONE function — impossible from any single pragma config; rigorously swept (all opt pragmas x both propagation settings). Likely the global optimizer's budget partially processing 8KB+ functions. Do not burn agent rounds on pragma hunting here; only close source-structure recovery moves these. Probe tooling: /tmp/croa_lab/.
- **.rodata/.sdata2 pool ORDER is score-irrelevant** — objdiff matches relocations by target SYMBOL name, not numeric offset. Reordering string/const declarations does nothing. (Proven: map .sdata2 made byte-identical -> 0 score change.)
- **CColor ctor inlining** — the original calls it out-of-line; inlining breaks linkage. Copy-ctor is non-const-ref (__ct__6CColorFR6CColor) and correct as-is.
- **Anonymous compiler-pool conversion magics** (@NNNN int->double bias) cannot be forced to a named symbol.
- **Pure register-allocation/numbering & instruction-scheduling cascades** (this in r30 vs r31, one extra callee-saved reg, mtctr vs subic when the target chose it, FIFO base-register choice) — not reachable from plausible C with this MWCC; the true ceiling. Would need a C++ register-allocation permuter (decomp-permuter cannot parse C++).

---

## Buckets v3 — rebalanced  on latest main (project 98.00%)
Every unit below 100% reassigned from scratch; ~1052664 unmatched code bytes total, ~263k/bucket target. Domain-coherent to minimize shared-header conflicts; gate every change on report.json fuzzy.

### B1 — Menus core (deep) — 6 units, ~246668 bytes
| unit | fuzzy | unmatched |
|---|---:|---:|
| wm_menu | 94.89% | 108280 |
| bonus_menu | 90.87% | 44716 |
| shopmenu | 97.21% | 37516 |
| menu_cmd | 96.53% | 22320 |
| MenuUtil | 96.21% | 17000 |
| singmenu | 98.39% | 16836 |

### B2 — Menus rest + Birth/effects particles — 28 units, ~239316 bytes
| unit | fuzzy | unmatched |
|---|---:|---:|
| cmake | 99.34% | 29436 |
| menu_letter | 95.10% | 17016 |
| goout | 99.63% | 16800 |
| pppRyjMegaBirthModel | 98.06% | 14536 |
| mes | 94.51% | 11984 |
| p_menu | 96.27% | 11728 |
| pppPart | 97.22% | 10680 |
| mesmenu | 95.58% | 10032 |
| menu_equip | 95.86% | 9792 |
| pppYmMana | 97.98% | 9676 |
| pppMana2 | 97.53% | 9204 |
| ringmenu | 92.98% | 9036 |
| pppYmMegaBirthShpTail3 | 98.55% | 7640 |
| menu_item | 96.86% | 6656 |
| pppYmMegaBirthShpTail2 | 96.83% | 6616 |
| pppRyjMegaBirth | 98.99% | 5784 |
| pppMiasma | 99.06% | 5604 |
| pppYmDeformationShp | 98.88% | 5488 |
| menu_arti | 97.02% | 5216 |
| pppYmBreath | 99.62% | 5208 |
| menu_money | 96.35% | 5168 |
| menu_compa | 93.84% | 4440 |
| pppCharaBreak | 98.19% | 4432 |
| p_dbgmenu | 99.30% | 4388 |
| menu_favo | 95.81% | 4184 |
| menu_lst | 97.29% | 3476 |
| menu_tmparti | 97.01% | 3044 |
| LocationTitle2 | 98.56% | 2052 |

### B3 — Characters & objects (deep) — 16 units, ~244796 bytes
| unit | fuzzy | unmatched |
|---|---:|---:|
| partyobj | 98.30% | 31612 |
| monobj | 97.41% | 27072 |
| charaobj | 97.74% | 26888 |
| partMng | 97.39% | 26140 |
| p_chara | 96.93% | 23444 |
| chara_fur | 91.62% | 20276 |
| gobject | 99.13% | 17848 |
| materialman | 99.63% | 17460 |
| chara | 97.68% | 14512 |
| gobjwork | 98.32% | 11268 |
| monobj_boss | 98.32% | 10640 |
| itemobj | 97.91% | 7904 |
| p_chara_viewer | 99.38% | 7060 |
| chara_anim | 99.13% | 1772 |
| prgobj | 99.98% | 476 |
| quadobj | 99.50% | 424 |

### B4 — Engine / cflat / map / sound / system + ppp tail (wide, mostly >99%) — 75 units, ~321884 bytes
| unit | fuzzy | unmatched |
|---|---:|---:|
| joybus | 99.18% | 29940 |
| gbaque | 96.71% | 25940 |
| cflat_r2system | 94.92% | 25076 |
| cflat_r2class | 96.40% | 13644 |
| cflat_runtime2 | 98.48% | 13000 |
| cflat_runtime | 96.67% | 12824 |
| RedSound/RedExecute | 98.10% | 12100 |
| p_minigame | 98.25% | 11828 |
| map | 99.46% | 11320 |
| memory | 99.65% | 10576 |
| p_camera | 96.76% | 9040 |
| mapobj | 99.71% | 8512 |
| p_graphic | 98.77% | 7664 |
| maphit | 99.59% | 6564 |
| memorycard | 99.76% | 6420 |
| sound | 98.82% | 5772 |
| astar | 99.31% | 5736 |
| ME_USB_process | 98.72% | 4784 |
| game | 99.33% | 4600 |
| pppLaser | 98.49% | 4476 |
| pppYmLaser | 98.40% | 4316 |
| FunnyShape | 96.46% | 4212 |
| RedSound/RedEntry | 99.49% | 4136 |
| graphic | 97.94% | 3976 |
| pppYmEnv | 98.24% | 3584 |
| RedSound/RedCommand | 96.56% | 3576 |
| pppBreathModel | 99.69% | 3536 |
| FS_USB_Process | 99.71% | 3524 |
| THPSimple | 99.39% | 3468 |
| p_light | 99.71% | 3072 |
| pppYmMelt | 99.21% | 3020 |
| pad | 98.69% | 2844 |
| pppKeShpTail3X | 99.19% | 2624 |
| pppCrystal | 99.51% | 2524 |
| pppYmChangeTex | 98.18% | 2436 |
| pppChangeTex | 98.39% | 2420 |
| pppCrystal2 | 99.49% | 2136 |
| p_tina | 96.70% | 1996 |
| RedSound/RedStream | 99.39% | 1964 |
| pppYmTracer | 99.04% | 1944 |
| pppScreenBreak | 98.56% | 1920 |
| RedSound/RedDriver | 98.79% | 1836 |
| pppKeShpTail2X | 96.61% | 1796 |
| file | 99.84% | 1696 |
| pppRain | 98.97% | 1620 |
| fontman | 98.81% | 1572 |
| wind | 98.73% | 1560 |
| pppYmDeformationMdl | 99.63% | 1384 |
| pppColum | 99.54% | 1292 |
| textureman | 99.65% | 1272 |
| pppLocationTitle | 99.08% | 1228 |
| util | 99.40% | 1160 |
| pppYmDrawMdlTexAnm | 99.51% | 1152 |
| mapanim | 99.83% | 996 |
| p_map | 95.52% | 976 |
| p_FunnyShape | 98.64% | 816 |
| pppYmMiasma | 99.96% | 748 |
| math | 99.95% | 628 |
| pppRandCV | 99.48% | 540 |
| pppRandHCV | 99.47% | 524 |
| pppConstrainCameraDir | 99.79% | 508 |
| pppShape | 99.70% | 480 |
| pppRandDownCV | 99.58% | 472 |
| pppRandUpCV | 99.58% | 472 |
| gxfunc | 97.82% | 460 |
| pppRandDownHCV | 99.56% | 456 |
| pppRandIV | 99.52% | 456 |
| pppRandUpHCV | 99.56% | 456 |
| pppRandDownIV | 99.60% | 404 |
| pppRandUpIV | 99.60% | 404 |
| ME_AppRequest | 99.68% | 316 |
| pppRandDownFV | 99.74% | 304 |
| pppRandUpFV | 99.74% | 304 |
| p_MaterialEditor | 98.96% | 280 |
| mapocttree | 99.97% | 272 |

## Balance & notes (v3)
| Bucket | units | ~unmatched | character |
|---|---:|---:|---|
| B1 Menus core | 6 | 246,668 | few deep units (wm_menu 108k dominates) — long focused agents |
| B2 Menus rest + Birth/effects | 28 | 239,316 | mixed; many mid-size menu_* + the MegaBirth/Mana/Miasma ppp families |
| B3 Characters & objects | 16 | 244,796 | concentrated/deep (~15k/unit) — chara/obj/gobject/material/cflat-adjacent |
| B4 Engine/cflat/map/sound/system + ppp tail | 75 | 321,884 | WIDE & shallow (~4.3k/unit, most >99%) — fan many small agents in waves |
| **Total** | **125** | **1,052,664** | |

- Byte totals over-state B4's effort: it's a long tail of near-100% units (fan-out friendly), while B3 is fewer/deeper. Real effort is closer than bytes.
- Shared-header conflict zones to coordinate via `[cross]` fast-merge: menu headers (B1/B2), chara/gobject/particle bases (B3 + B2's ppp), map/vector/gobject (B4). cflat_* lives in B4 — keep its 4 units together (shared cflat headers).
- Per-operator loop unchanged: branch from latest main → diff → apply lever-catalog → rebuild+remeasure → commit/push every net-positive change (gate on report.json) → merge at checkpoints. The full battle-tested lever catalog + dead-ends above apply to ALL buckets.
