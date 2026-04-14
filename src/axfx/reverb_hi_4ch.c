#include <dolphin.h>
#include <dolphin/ax.h>
#include <dolphin/axfx.h>

#include "dolphin/axfx/__axfx.h"

extern const double reverb_hi_4ch_handle_i2fMagic;

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - ReverbHICreateDpl2 and ReverbHIModifyDpl2 are still almost entirely down to
 *   stack-slot / temporary-lifetime / constant-binding shape rather than missing
 *   control flow
 *
 * Most useful probes so far:
 * - the shared Dolphin source copies in reference_projects/super_mario_strikers
 *   and reference_projects/twilight_princess agree on two obvious shape
 *   differences from this file: no separate timeFactor local in Create and no
 *   block-scoped damp temporary in either function
 * - those cleanups were flat before the unit owned its target-style .sdata2,
 *   but became real progress once reverb_hi_4ch.c claimed .sdata2
 *   0x803337E0..0x80333818 and the handle-side constant labels were corrected
 * - a follow-up constant-ownership cleanup removed the bogus local handle-side
 *   double, added the target-style local 0.1f bound for Modify, and relabeled
 *   the 0.3f / 0.6f / external i2f-magic tail accordingly; that moved .sdata2
 *   from 92.85714% to 96.0% and nudged .text to 99.47125%
 * - the built source object now already carries the target-style local .sdata2
 *   layout for these functions (`@111`..`@120`, 0x30 bytes total), so the
 *   remaining gap is no longer constant ownership inside reverb_hi_4ch.o
 * - removing the inner parentheses from `0.05f + (0.8f * rv->damping)` held
 *   completely flat, so the remaining damping-expression miss is not just the
 *   obvious precedence spelling
 * - reordering the sum to `1.0f - ((0.8f * rv->damping) + 0.05f)` also stayed
 *   completely flat
 * - forcing the named local `reverb_hi_4ch_value0_1` through every visible
 *   `preDelay <= 0.1f` / `preDelay > 0.1f` check in Create and Modify was also
 *   completely flat: the built object still emitted the same `0x30` .sdata2
 *   with no extra local float symbol between `@120` and the `0.3f` / `0.6f`
 *   tail
 * - even promoting `reverb_hi_4ch_value0_1` / `0_3` / `0_6` from `static const`
 *   to plain file-scope `const` was completely flat on the fresh branch: MWCC
 *   still folded `0.1f` into the earlier local pool, kept source `.sdata2` at
 *   0x30 bytes, and did not materialize the target-style extra `0.1f` symbol
 * - a follow-up retest on the fresh branch corrected the stale assumption about
 *   contraction: for these damping blocks the target actually keeps separate
 *   `fmuls` + `fadds` + `fsubs`, while the baseline source is the one that
 *   contracts to `fmadds`
 * - an explicit stepwise rewrite through repeated `rv->damping = ...` updates
 *   did force the separate ops, but regressed hard overall
 *   (Create 99.40% -> 97.85%, Modify 97.30% -> 93.36%), so the remaining
 *   blocker is not "just spell out the three statements" either
 * - a narrower `f32 damp = 0.8f * rv->damping; rv->damping = 1.0f - (0.05f +
 *   damp);` probe also forced the exact target-side `fmuls` + `fadds` +
 *   `fsubs` sequence in both functions, but still held completely flat
 *   (Create stayed 99.40129%, Modify stayed 97.29508%), so the remaining miss
 *   is now the nearby temporary/register lifetime around that block rather
 *   than the arithmetic opcode shape itself
 * - matching the shared reference-project spelling more literally by adding
 *   the outer parentheses around `rv->damping = (1.0f - (...))` in both
 *   functions and changing Modify's range check back to a direct `0.1f`
 *   literal was also completely flat, so this unit is not blocked on that
 *   last visible source-family spelling difference either
 * - the extracted target object really does carry a standalone global
 *   `reverb_hi_4ch_value0_1` symbol after the local `@111`..`@120` pool, but
 *   simply promoting `reverb_hi_4ch_value0_1 / 0_3 / 0_6` to plain file-scope
 *   `const` front-loads them to the start of `.sdata2` (`0x0 / 0x4 / 0x8`),
 *   regresses section match from 96.0% to 74.07%, and drops
 *   `ReverbHICreateDpl2` from 99.40% to 99.16%; so "make value0_1 global"
 *   alone is not the fix
 * - a newer keepable probe did find the right arithmetic shape without the old
 *   stack-lifetime regression: rewriting the damping normalization through a
 *   local `f32 damp`, then `damp = 0.05f + damp`, then
 *   `rv->damping = 1.0f - damp` forces the target-style separate
 *   `fmuls` / `fadds` / `fsubs` chain in both functions and moves
 *   `ReverbHICreateDpl2` from 99.40129% to 99.83819% and
 *   `ReverbHIModifyDpl2` from 97.29508% to 99.54918%
 * - after that keepable rewrite, the remaining function-body gap is down to a
 *   tiny register-allocation seam inside the same damping block plus the older
 *   `reverb_hi_4ch_value0_1` symbol-identity mismatch in Modify's range check;
 *   no broader control-flow difference remains there
 * - a follow-up probe that kept the same `damp` temporary but moved the
 *   `0.05f` clamp onto the local before the final store was completely flat;
 *   `ReverbHICreateDpl2` stayed at 99.83819%, so the remaining seam is not
 *   just "avoid the early rv->damping store" either
 * - a newer probe tested the odd GCCP01-looking possibility from the current
 *   extracted target object that only `ReverbHIModifyDpl2` wants a `100.0f`
 *   preDelay upper bound instead of the shared Dolphin-family `0.1f`; that
 *   did nudge Modify from 99.54918% to 99.59016%, but MWCC duplicated the
 *   whole constant run and blew `.sdata2` out from `0x38` to `0x60`, so that
 *   spelling is not keepable
 * - a tighter follow-up also ruled out the simplest symbol-identity fix:
 *   making only `reverb_hi_4ch_value0_1` a plain file-scope `const` while
 *   leaving the already-correct `0.3f` / `0.6f` tail alone was completely
 *   flat; rebuilt source `reverb_hi_4ch.o` stayed at `.sdata2 0x30` instead
 *   of growing to the target `.sdata2 0x38`, so MWCC still folded the `0.1f`
 *   bound into the earlier local pool instead of materializing the missing
 *   standalone float symbol
 * - on the current branch, removing `reverb_hi_4ch_value0_1` entirely and
 *   switching Modify back to a direct `0.1f` literal was also completely flat:
 *   `ReverbHIModifyDpl2` stayed at 99.59016% and `.sdata2` stayed at 88.88889%,
 *   so the remaining miss is not just the named-vs-literal `0.1f` choice in
 *   Modify either
 * - the remaining miss is still concentrated in the damping rewrite in Create
 *   and Modify rather than sdata2 ownership, but the next probe should bias
 *   toward preserving the target load/order shape without the heavy repeated
 *   store/reload lifetime introduced by the naive stepwise form
 */

extern f32 powf(f32 x, f32 y);

static s32 axfx_reverb_hi_dpl2_lens[10] = {
    0x000006FD, 0x000007CF, 0x0000091D, 0x000001B1, 0x00000095,
    0x0000002F, 0x00000049, 0x00000043, 0x00000047, 0x00000000,
};

const static f32 reverb_hi_4ch_value0_1 = 0.1f;
const static f32 reverb_hi_4ch_value0_3 = 0.3f;
const static f32 reverb_hi_4ch_value0_6 = 0.6f;

static inline void DLsetdelayDpl2(AXFX_REVHI_DELAYLINE* dl, s32 lag) {
    dl->outPoint = dl->inPoint - (lag * 4);
    while (dl->outPoint < 0) {
        dl->outPoint += dl->length;
    }
}

static inline int DLcreateDpl2(AXFX_REVHI_DELAYLINE* dl, s32 max_length) {
    dl->length = (max_length * 4);
    dl->inputs = __AXFXAlloc(max_length << 2);
    ASSERTMSGLINE(62, dl->inputs, "Can't allocate the memory.");

    memset(dl->inputs, 0, max_length << 2);
    dl->lastOutput = 0.0f;
    DLsetdelayDpl2(dl, max_length >> 1);
    dl->inPoint = 0;
    dl->outPoint = 0;
    return 1;
}

static inline void DLdeleteDpl2(AXFX_REVHI_DELAYLINE* dl) {
    __AXFXFree(dl->inputs);
}

/*
 * --INFO--
 * PAL Address: 0x80196A20
 * PAL Size: 1236b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int ReverbHICreateDpl2(AXFX_REVHI_WORK_DPL2* rv, f32 coloration, f32 time, f32 mix, f32 damping, f32 preDelay) {
    u8 i;
    u8 k;

    ASSERTMSGLINE(117, coloration >= 0.0f && coloration <= 1.0f &&
                           time >= 0.01f && time <= 10.0f &&
                           mix >= 0.0f && mix <= 1.0f &&
                           damping >= 0.0f && damping <= 1.0f &&
                           preDelay >= 0.0f && preDelay <= 0.1f,
                           "The value of specified parameter is out of range.");

    if ((coloration < 0.0f) || (coloration > 1.0f)
     || (time < 0.01f) || (time > 10.0f)
     || (mix < 0.0f) || (mix > 1.0f)
     || (damping < 0.0f) || (damping > 1.0f)
     || (preDelay < 0.0f) || (preDelay > 0.1f)) {
        return 0;
    }

    memset(rv, 0, sizeof(AXFX_REVHI_WORK_DPL2));
    for (k = 0; k < 4; k++) {
        for (i = 0; i < 3; i++) {
            DLcreateDpl2(&rv->C[i + (k * 3)], axfx_reverb_hi_dpl2_lens[i] + 2);
            DLsetdelayDpl2(&rv->C[i + (k * 3)], axfx_reverb_hi_dpl2_lens[i]);
            rv->combCoef[i + (k * 3)] = powf(10.0f, (axfx_reverb_hi_dpl2_lens[i] * -3) / (32000.0f * time));
        }

        for (i = 0; i < 2; i++) {
            DLcreateDpl2(&rv->AP[i + (k * 3)], axfx_reverb_hi_dpl2_lens[i + 3] + 2);
            DLsetdelayDpl2(&rv->AP[i + (k * 3)], axfx_reverb_hi_dpl2_lens[i + 3]);
        }

        DLcreateDpl2(&rv->AP[2 + (k * 3)], axfx_reverb_hi_dpl2_lens[k + 5] + 2);
        DLsetdelayDpl2(&rv->AP[2 + (k * 3)], axfx_reverb_hi_dpl2_lens[k + 5]);
        rv->lpLastout[k] = 0.0f;
    }

    rv->allPassCoeff = coloration;
    rv->level = mix;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    {
        f32 damp = 0.8f * rv->damping;
        damp = 0.05f + damp;
        rv->damping = 1.0f - damp;
    }

    if (0.0f != preDelay) {
        rv->preDelayTime = 32000.0f * preDelay;
        for (i = 0; i < 4; i++) {
            rv->preDelayLine[i] = __AXFXAlloc(rv->preDelayTime * 4);
            ASSERTMSGLINE(188, rv->preDelayLine[i], "Can't allocate the memory.");

            memset(rv->preDelayLine[i], 0, rv->preDelayTime * 4);
            rv->preDelayPtr[i] = rv->preDelayLine[i];
        }
    } else {
        rv->preDelayTime = 0;
        for (i = 0; i < 4; i++) {
            rv->preDelayPtr[i] = 0;
            rv->preDelayLine[i] = 0;
        }
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80196EF4
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int ReverbHIModifyDpl2(AXFX_REVHI_WORK_DPL2* rv, f32 coloration, f32 time, f32 mix, f32 damping, f32 preDelay) {
    u8 i;

    ASSERTMSGLINE(222, coloration >= 0.0f && coloration <= 1.0f &&
                  time >= 0.01f && time <= 10.0f &&
                  mix >= 0.0f && mix <= 1.0f &&
                  damping >= 0.0f && damping <= 1.0f &&
                  preDelay >= 0.0f && preDelay <= 0.1f,
                  "The value of specified parameter is out of range.");

    if ((coloration < 0.0f) || (coloration > 1.0f)
     || (time < 0.01f) || (time > 10.0f)
     || (mix < 0.0f) || (mix > 1.0f)
     || (damping < 0.0f) || (damping > 1.0f)
     || (preDelay < 0.0f) || (preDelay > reverb_hi_4ch_value0_1)) {
        return 0;
    }

    rv->allPassCoeff = coloration;
    rv->level = mix;
    rv->damping = damping;
    if (rv->damping < 0.05f) {
        rv->damping = 0.05f;
    }
    {
        f32 damp = 0.8f * rv->damping;
        damp = 0.05f + damp;
        rv->damping = 1.0f - damp;
    }

    for (i = 0; i < 12; i++) {
        DLdeleteDpl2(&rv->AP[i]);
    }

    for (i = 0; i < 12; i++) {
        DLdeleteDpl2(&rv->C[i]);
    }

    if (rv->preDelayTime) {
        for (i = 0; i < 4; i++) {
            __AXFXFree(rv->preDelayLine[i]);
        }
    }

    return ReverbHICreateDpl2(rv, coloration, time, mix, damping, preDelay);
}


asm static void HandleReverbDpl2(register s32* sptr, register AXFX_REVHI_WORK_DPL2* rv, register s32 k) {
    nofralloc
	stwu r1, -0xc0(r1)
	stmw r14, 0x8(r1)
	stfd f14, 0x60(r1)
	stfd f15, 0x68(r1)
	stfd f16, 0x70(r1)
	stfd f17, 0x78(r1)
	stfd f18, 0x80(r1)
	stfd f19, 0x88(r1)
	stfd f20, 0x90(r1)
	stfd f21, 0x98(r1)
	stfd f22, 0xa0(r1)
	stfd f23, 0xa8(r1)
	stfd f24, 0xb0(r1)
	stfd f25, 0xb8(r1)
	stw k, 0x50(r1)
	stw rv, 0x54(r1)
	lis r31, reverb_hi_4ch_value0_3@ha
	lfs f6, reverb_hi_4ch_value0_3@l(r31)
	lis r31, reverb_hi_4ch_value0_6@ha
	lfs f9, reverb_hi_4ch_value0_6@l(r31)
	lis r31, reverb_hi_4ch_handle_i2fMagic@ha
	lfd f5, reverb_hi_4ch_handle_i2fMagic@l(r31)
	lfs f2, AXFX_REVHI_WORK_DPL2.allPassCoeff(rv)
	lfs f15, AXFX_REVHI_WORK_DPL2.damping(rv)
	lfs f8, AXFX_REVHI_WORK_DPL2.level(rv)
	fmuls f3, f8, f9
	fsubs f4, f9, f3
	slwi r30, k, 1
	add r30, r30, k
	mulli r31, r30, 0x14
	addi r29, rv, AXFX_REVHI_WORK_DPL2.C
	add r29, r29, r31
	addi r27, rv, AXFX_REVHI_WORK_DPL2.AP
	add r27, r27, r31
	slwi r31, r30, 2
	add r31, r31, rv
	lfs f22, AXFX_REVHI_WORK_DPL2.combCoef[0](r31)
	lfs f23, AXFX_REVHI_WORK_DPL2.combCoef[1](r31)
	lfs f24, AXFX_REVHI_WORK_DPL2.combCoef[2](r31)
	slwi r31, k, 2
	add r31, r31, rv
	lfs f25, AXFX_REVHI_WORK_DPL2.lpLastout[0](r31)
	lwz r31, AXFX_REVHI_WORK_DPL2.preDelayTime(rv)
	lis r30, 0x4330
	stw r30, 0x58(r1)
	subi r22, r31, 1
	slwi r22, r22, 2
	slwi r28, k, 2
	add r28, r28, rv
	cmpwi cr7, r31, 0
	lwz r21, AXFX_REVHI_DELAYLINE.inPoint    + 0x00(r29) // C[0]
	lwz r20, AXFX_REVHI_DELAYLINE.outPoint   + 0x00(r29) // C[0]
	lwz r19, AXFX_REVHI_DELAYLINE.inPoint    + 0x14(r29) // C[1]
	lwz r18, AXFX_REVHI_DELAYLINE.outPoint   + 0x14(r29) // C[1]
	lwz r17, AXFX_REVHI_DELAYLINE.inPoint    + 0x28(r29) // C[2]
	lwz r16, AXFX_REVHI_DELAYLINE.outPoint   + 0x28(r29) // C[2]
	lfs f16, AXFX_REVHI_DELAYLINE.lastOutput + 0x00(r29) // C[0]
	lfs f17, AXFX_REVHI_DELAYLINE.lastOutput + 0x14(r29) // C[1]
	lfs f18, AXFX_REVHI_DELAYLINE.lastOutput + 0x28(r29) // C[2]
	lwz r25, AXFX_REVHI_DELAYLINE.length     + 0x00(r29) // C[0]
	lwz r24, AXFX_REVHI_DELAYLINE.length     + 0x14(r29) // C[1]
	lwz r23, AXFX_REVHI_DELAYLINE.length     + 0x28(r29) // C[2]
	lwz r4,  AXFX_REVHI_DELAYLINE.inputs     + 0x00(r29) // C[0]
	lwz r5,  AXFX_REVHI_DELAYLINE.inputs     + 0x14(r29) // C[1]
	lwz r6,  AXFX_REVHI_DELAYLINE.inputs     + 0x28(r29) // C[2]
	lwz r12, AXFX_REVHI_DELAYLINE.inPoint    + 0x00(r27) // AP[0]
	lwz r11, AXFX_REVHI_DELAYLINE.outPoint   + 0x00(r27) // AP[0]
	lwz r10, AXFX_REVHI_DELAYLINE.inPoint    + 0x14(r27) // AP[1]
	lwz r9,  AXFX_REVHI_DELAYLINE.outPoint   + 0x14(r27) // AP[1]
	lwz r8,  AXFX_REVHI_DELAYLINE.inPoint    + 0x28(r27) // AP[2]
	lwz r7,  AXFX_REVHI_DELAYLINE.outPoint   + 0x28(r27) // AP[2]
	lfs f19, AXFX_REVHI_DELAYLINE.lastOutput + 0x00(r27) // AP[0]
	lfs f20, AXFX_REVHI_DELAYLINE.lastOutput + 0x14(r27) // AP[1]
	lfs f21, AXFX_REVHI_DELAYLINE.lastOutput + 0x28(r27) // AP[2]
	lwz r15, AXFX_REVHI_DELAYLINE.length     + 0x00(r27) // AP[0]
	lwz r14, AXFX_REVHI_DELAYLINE.length     + 0x14(r27) // AP[1]
    //? missing load for length of AP[3]? Maybe intentional?
	lwz r30, 0(r3)
	xoris r30, r30, 0x8000
	stw r30, 0x5c(r1)
	lfd f12, 0x58(r1)
	fsubs f12, f12, f5
	li r31, 159
	mtctr r31
L_00000964:
	fmr f13, f12
	beq cr7, L_00000994
	lwz r30, AXFX_REVHI_WORK_DPL2.preDelayLine(r28)
	lwz r29, AXFX_REVHI_WORK_DPL2.preDelayPtr(r28)
	add r31, r22, r30
	addi r29, r29, 4
	lfs f13, -4(r29)
	cmpw r29, r31
	stfs f12, -4(r29)
	bne+ L_00000990
	mr r29, r30
L_00000990:
	stw r29, AXFX_REVHI_WORK_DPL2.preDelayPtr(r30)
L_00000994:
	fmadds f8, f22, f16, f13
	lwzu r29, 4(r3)
	fmadds f9, f23, f17, f13
	stfsx f8, rv, r21
	addi r21, r21, 4
	stfsx f9, k, r19
	lfsx f14, rv, r20
	addi r20, r20, 4
	lfsx f17, k, r18
	cmpw r21, r25
	cmpw cr1, r20, r25
	addi r19, r19, 4
	addi r18, r18, 4
	fmr f16, f14
	cmpw cr5, r19, r24
	fadds f14, f14, f17
	cmpw cr6, r18, r24
	bne+ L_000009E0
	li r21, 0
L_000009E0:
	fmadds f8, f24, f18, f13
	bne+ cr1, L_000009EC
	li r20, 0
L_000009EC:
	stfsx f8, r6, r17
	addi r17, r17, 4
	bne+ cr5, L_000009FC
	li r19, 0
L_000009FC:
	lfsx f18, r6, r16
	addi r16, r16, 4
	cmpw r17, r23
	bne+ cr6, L_00000A10
	li r18, 0
L_00000A10:
	fadds f14, f14, f18
	cmpw cr1, r16, r23
	lwz r26, AXFX_REVHI_DELAYLINE.inputs(r27)
	fmadds f9, f2, f19, f14
	bne+ L_00000A28
	li r17, 0
L_00000A28:
	bne+ cr1, L_00000A30
	li r16, 0
L_00000A30:
	xoris r29, r29, 0x8000
	stfsx f9, r26, r12
	fnmsubs f14, f2, f9, f19
	addi r12, r12, 4
	lfsx f19, r26, r11
	cmpw cr5, r12, r15
	addi r11, r11, 4
	lwz r26, AXFX_REVHI_DELAYLINE.inputs + 0x14(r27)
	cmpw cr6, r11, r15
	fmadds f8, f2, f20, f14
	bne+ cr5, L_00000A60
	li r12, 0x0
L_00000A60:
	stw r29, 0x5c(r1)
	stfsx f8, r26, r10
	fnmsubs f14, f2, f8, f20
	addi r10, r10, 4
	bne+ cr6, L_00000A78
	li r11, 0
L_00000A78:
	lfsx f20, r26, r9
	cmpw r10, r14
	fmuls f14, f14, f6
	addi r9, r9, 4
	cmpw cr1, r9, r14
	lfd f10, 0x58(r1)
	fmadds f14, f15, f25, f14
	bne+ L_00000A9C
	li r10, 0
L_00000A9C:
	lwz r26, AXFX_REVHI_DELAYLINE.inputs + 0x28(r27)
	fmadds f9, f2, f21, f14
	fmr f25, f14
	bne+ cr1, L_00000AB0
	li r9, 0
L_00000AB0:
	stfsx f9, r26, r8
	fnmsubs f14, f2, f9, f21
	lwz r31, AXFX_REVHI_DELAYLINE.length + 0x28(r27)
	fmuls f8, f4, f12
	lfsx f21, r26, r7
	addi r8, r8, 4
	addi r7, r7, 4
	fmadds f14, f3, f14, f8
	cmpw cr5, r8, r31
	cmpw cr6, r7, r31
	fctiwz f14, f14
	bne+ cr5, L_00000AE4
	li r8, 0
L_00000AE4:
	bne+ cr6, L_00000AEC
	li r7, 0
L_00000AEC:
	li r31, -4
	fsubs f12, f10, f5
	stfiwx f14, sptr, r31
	bdnz L_00000964
	fmr f13, f12
	beq cr7, L_00000B2C
	lwz r30, AXFX_REVHI_WORK_DPL2.preDelayLine(r28)
	lwz r29, AXFX_REVHI_WORK_DPL2.preDelayPtr(r28)
	add r31, r22, r30
	addi r29, r29, 4
	lfs f13, -4(r29)
	cmpw r29, r31
	stfs f12, -4(r29)
	bne+ L_00000B28
	mr r29, r30
L_00000B28:
	stw r29, AXFX_REVHI_WORK_DPL2.preDelayPtr(r30)
L_00000B2C:
	fmadds f8, f22, f16, f13
	fmadds f9, f23, f17, f13
	stfsx f8, rv, r21
	addi r21, r21, 4
	stfsx f9, k, r19
	lfsx f14, rv, r20
	addi r20, r20, 4
	lfsx f17, k, r18
	cmpw r21, r25
	cmpw cr1, r20, r25
	addi r19, r19, 4
	addi r18, r18, 4
	fmr f16, f14
	cmpw cr5, r19, r24
	fadds f14, f14, f17
	cmpw cr6, r18, r24
	bne+ L_00000B74
	li r21, 0
L_00000B74:
	fmadds f8, f24, f18, f13
	bne+ cr1, L_00000B80
	li r20, 0
L_00000B80:
	stfsx f8, r6, r17
	addi r17, r17, 4
	bne+ cr5, L_00000B90
	li r19, 0
L_00000B90:
	lfsx f18, r6, r16
	addi r16, r16, 4
	cmpw r17, r23
	bne+ cr6, L_00000BA4
	li r18, 0
L_00000BA4:
	fadds f14, f14, f18
	cmpw cr1, r16, r23
	lwz r26, AXFX_REVHI_DELAYLINE.inputs(r27)
	fmadds f9, f2, f19, f14
	bne+ L_00000BBC
	li r17, 0
L_00000BBC:
	bne+ cr1, L_00000BC4
	li r16, 0
L_00000BC4:
	stfsx f9, r26, r12
	fnmsubs f14, f2, f9, f19
	addi r12, r12, 4
	lfsx f19, r26, r11
	cmpw cr5, r12, r15
	addi r11, r11, 4
	lwz r26, AXFX_REVHI_DELAYLINE.inputs + 0x14(r27)
	cmpw cr6, r11, r15
	fmadds f8, f2, f20, f14
	bne+ cr5, L_00000BF0
	li r12, 0
L_00000BF0:
	stfsx f8, r26, r10
	fnmsubs f14, f2, f8, f20
	addi r10, r10, 4
	bne+ cr6, L_00000C04
	li r11, 0
L_00000C04:
	lfsx f20, r26, r9
	cmpw r10, r14
	fmuls f14, f14, f6
	addi r9, r9, 4
	cmpw cr1, r9, r14
	fmadds f14, f15, f25, f14
	bne+ L_00000C24
	li r10, 0
L_00000C24:
	lwz r26, AXFX_REVHI_DELAYLINE.inputs + 0x28(r27)
	lwz k, 0x50(r1)
	lwz rv, 0x54(r1)
	fmadds f9, f2, f21, f14
	fmr f25, f14
	bne+ cr1, L_00000C40
	li r9, 0
L_00000C40:
	stfsx f9, r26, r8
	fnmsubs f14, f2, f9, f21
	lwz r29, AXFX_REVHI_DELAYLINE.length + 0x28(r27)
	fmuls f8, f4, f12
	lfsx f21, r26, r7
	addi r8, r8, 4
	addi r7, r7, 4
	fmadds f14, f3, f14, f8
	cmpw cr5, r8, r29
	cmpw cr6, r7, r29
	fctiwz f14, f14
	bne+ cr5, L_00000C74
	li r8, 0
L_00000C74:
	bne+ cr6, L_00000C7C
	li r7, 0
L_00000C7C:
	slwi r30, k, 1
	add r30, r30, k
	mulli r31, r30, 0x14 // sizeof AXFX_REVHI_DELAYLINE
	stfiwx f14, r0, sptr
	addi r29, rv, AXFX_REVHI_WORK_DPL2.C
	add r29, r29, r31
	stw r21,  AXFX_REVHI_DELAYLINE.inPoint    + 0x00(r29) // C[0]
	stw r20,  AXFX_REVHI_DELAYLINE.outPoint   + 0x00(r29) // C[0]
	stw r19,  AXFX_REVHI_DELAYLINE.inPoint    + 0x14(r29) // C[1]
	stw r18,  AXFX_REVHI_DELAYLINE.outPoint   + 0x14(r29) // C[1]
	stw r17,  AXFX_REVHI_DELAYLINE.inPoint    + 0x28(r29) // C[2]
	stw r16,  AXFX_REVHI_DELAYLINE.outPoint   + 0x28(r29) // C[2]
	stfs f16, AXFX_REVHI_DELAYLINE.lastOutput + 0x00(r29) // C[0]
	stfs f17, AXFX_REVHI_DELAYLINE.lastOutput + 0x14(r29) // C[1]
	stfs f18, AXFX_REVHI_DELAYLINE.lastOutput + 0x28(r29) // C[2]
	stw r12,  AXFX_REVHI_DELAYLINE.inPoint    + 0x00(r27) // AP[0]
	stw r11,  AXFX_REVHI_DELAYLINE.outPoint   + 0x00(r27) // AP[0]
	stw r10,  AXFX_REVHI_DELAYLINE.inPoint    + 0x14(r27) // AP[1]
	stw r9,   AXFX_REVHI_DELAYLINE.outPoint   + 0x14(r27) // AP[1]
	stw r8,   AXFX_REVHI_DELAYLINE.inPoint    + 0x28(r27) // AP[2]
	stw r7,   AXFX_REVHI_DELAYLINE.outPoint   + 0x28(r27) // AP[2]
	stfs f19, AXFX_REVHI_DELAYLINE.lastOutput + 0x00(r27) // AP[0]
	stfs f20, AXFX_REVHI_DELAYLINE.lastOutput + 0x14(r27) // AP[1]
	stfs f21, AXFX_REVHI_DELAYLINE.lastOutput + 0x28(r27) // AP[2]
	slwi r31, k, 2
	add r31, r31, rv
	stfs f25, AXFX_REVHI_WORK_DPL2.lpLastout(r31)
	lfd f14, 0x60(r1)
	lfd f15, 0x68(r1)
	lfd f16, 0x70(r1)
	lfd f17, 0x78(r1)
	lfd f18, 0x80(r1)
	lfd f19, 0x88(r1)
	lfd f20, 0x90(r1)
	lfd f21, 0x98(r1)
	lfd f22, 0xa0(r1)
	lfd f23, 0xa8(r1)
	lfd f24, 0xb0(r1)
	lfd f25, 0xb8(r1)
	lmw r14, 0x8(r1)
	addi r1, r1, 0xc0
	blr
}

int AXFXReverbHiInitDpl2(AXFX_REVERBHI_DPL2* reverb) {
    int ret;
    BOOL old;

    old = OSDisableInterrupts();
    reverb->tempDisableFX = 0;
    ret = ReverbHICreateDpl2(&reverb->rv, reverb->coloration, reverb->time, reverb->mix, reverb->damping, reverb->preDelay);
    OSRestoreInterrupts(old);
    return ret;
}

int AXFXReverbHiShutdownDpl2(AXFX_REVERBHI_DPL2* reverb) {
    BOOL old;

    old = OSDisableInterrupts();
    
    // Free all delay line inputs directly (24 delay lines total: 12 AP + 12 C)
    __AXFXFree(reverb->rv.AP[0].inputs);
    __AXFXFree(reverb->rv.AP[1].inputs);
    __AXFXFree(reverb->rv.AP[2].inputs);
    __AXFXFree(reverb->rv.AP[3].inputs);
    __AXFXFree(reverb->rv.AP[4].inputs);
    __AXFXFree(reverb->rv.AP[5].inputs);
    __AXFXFree(reverb->rv.AP[6].inputs);
    __AXFXFree(reverb->rv.AP[7].inputs);
    __AXFXFree(reverb->rv.AP[8].inputs);
    __AXFXFree(reverb->rv.AP[9].inputs);
    __AXFXFree(reverb->rv.AP[10].inputs);
    __AXFXFree(reverb->rv.AP[11].inputs);
    __AXFXFree(reverb->rv.C[0].inputs);
    __AXFXFree(reverb->rv.C[1].inputs);
    __AXFXFree(reverb->rv.C[2].inputs);
    __AXFXFree(reverb->rv.C[3].inputs);
    __AXFXFree(reverb->rv.C[4].inputs);
    __AXFXFree(reverb->rv.C[5].inputs);
    __AXFXFree(reverb->rv.C[6].inputs);
    __AXFXFree(reverb->rv.C[7].inputs);
    __AXFXFree(reverb->rv.C[8].inputs);
    __AXFXFree(reverb->rv.C[9].inputs);
    __AXFXFree(reverb->rv.C[10].inputs);
    __AXFXFree(reverb->rv.C[11].inputs);
    
    // Free pre-delay lines if they exist
    if (reverb->rv.preDelayTime != 0) {
        __AXFXFree(reverb->rv.preDelayLine[0]);
        __AXFXFree(reverb->rv.preDelayLine[1]);
        __AXFXFree(reverb->rv.preDelayLine[2]);
        __AXFXFree(reverb->rv.preDelayLine[3]);
    }
    
    OSRestoreInterrupts(old);
    return 1;
}

int AXFXReverbHiSettingsDpl2(AXFX_REVERBHI_DPL2* rev) {
    BOOL old;

    old = OSDisableInterrupts();
    rev->tempDisableFX = 1;
    ReverbHIModifyDpl2(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay);
    rev->tempDisableFX = 0;
    OSRestoreInterrupts(old);
    return 1;
}

void AXFXReverbHiCallbackDpl2(AXFX_BUFFERUPDATE_DPL2* bufferUpdate, AXFX_REVERBHI_DPL2* reverb) {
    ASSERTMSGLINE(1399, AXGetMode() == 2, "AX mode isn't AX_MODE_DPL2. AX mode must be AX_MODE_DPL2 for using AXFXReverbHiCallbackDpl2");

    if (reverb->tempDisableFX == 0) {
        HandleReverbDpl2(bufferUpdate->L, &reverb->rv, 0);
        HandleReverbDpl2(bufferUpdate->R, &reverb->rv, 1);
        HandleReverbDpl2(bufferUpdate->Ls, &reverb->rv, 2);
        HandleReverbDpl2(bufferUpdate->Rs, &reverb->rv, 3);
    }
}
