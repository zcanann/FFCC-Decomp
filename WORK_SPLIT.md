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

## CONFIRMED DEAD-ENDS (do not spend time here)
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
