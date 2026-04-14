#include "dolphin/mtx.h"

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - mtx.c reports 100% code/data in objdiff, but promoting it to Matching on
 *   the latest main-based SDK branch still fails the final main.dol checksum
 *
 * Most useful result so far:
 * - the same one-at-a-time Matching probe was repeated for mtx.c, mtx44.c,
 *   vec.c, and quat.c, and all four failed in the exact same way: configure
 *   succeeds, link completes, and only the final checksum check fails
 * - promoting all four mtx units together on the latest main-based SDK branch
 *   still fails only at the final checksum, so the hidden-link seam is not
 *   resolved by treating the cluster as a single promote-together island
 * - that makes this look like a shared hidden-link / metadata seam in the mtx
 *   library cluster rather than a remaining visible source mismatch in this
 *   file's body
 * - a fresh object-extent audit explains that seam more concretely: rebuilt
 *   source `mtx.o` is `0x1CA4` bytes of `.text`, while the extracted target
 *   `mtx.o` is only `0x0A3C`; source still emits the full SDK object plus
 *   local `Unit01` / `.sdata2` constants, while the target slice on GCCP01 is
 *   only the linked subset that imports those constants from outside
 * - that means `mtx.c -> Matching` is not blocked by its visible matched
 *   functions anymore; it is blocked because this repo still models the full
 *   library source file where GCCP01's final linked object only keeps the
 *   subset through `C_MTXLightOrtho`
 * - a PAL-map-backed GCCP01 trim is keepable here: removing every function the
 *   map marks `UNUSED` shrinks rebuilt source `mtx.o` down to the exact target
 *   `.text` extent `0x0A3C` while preserving the still-linked subset through
 *   `C_MTXLightOrtho`
 * - reclaiming the adjacent `Unit01` `.sdata` window and the `0x1C` `.sdata2`
 *   constant run back into `mtx/mtx.c`, plus removing the stray source-side
 *   `Unit01` blob from `si/SIBios.c`, also makes the extracted target
 *   `mtx.o` finally carry `.sdata 0x8` and `.sdata2 0x1C` instead of a
 *   text-only slice
 * - after those fixes, promoting `mtx.c` no longer hangs or exposes a broad
 *   section mismatch; it now gets all the way to a plain final checksum miss
 * - that cluster-level result still holds after later PAL-backed trims in
 *   `mtx44.c`, `vec.c`, and `quat.c`: promoting all four mtx units together
 *   still fails only at the final checksum, so the remaining seam is no
 *   longer the obvious linked-subset recovery in those files
 * - a follow-up probe making `Unit01` non-static in source did not change the
 *   rebuilt object binding at all, so the remaining blocker is not just that
 *   one declaration spelling
 */

static f32 Unit01[] = { 0.0f, 1.0f };

extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 tanf(f32);

#ifdef GEKKO
void PSMTXIdentity(register Mtx m)
{
    register f32 zero_c = 0.0f;
    register f32 one_c = 1.0f;
    register f32 c_01;
    register f32 c_10;
    // clang-format off
  asm {
    psq_st zero_c, 8(m), 0, 0
    ps_merge01 c_01, zero_c, one_c
    psq_st zero_c, 24(m), 0, 0
    ps_merge10 c_10, one_c, zero_c
    psq_st zero_c, 32(m), 0, 0
    psq_st c_01, 16(m), 0, 0
    psq_st c_10, 0(m), 0, 0
    psq_st c_10, 40(m), 0, 0
  }
    // clang-format on
}
#endif

#ifdef GEKKO
asm void PSMTXCopy(const register Mtx src, register Mtx dst)
{
    // clang-format off
  nofralloc

  psq_l fp0, 0(src), 0, 0
  psq_st fp0, 0(dst), 0, 0
  psq_l fp1, 8(src), 0, 0
  psq_st fp1, 8(dst), 0, 0
  psq_l fp2, 16(src), 0, 0
  psq_st fp2, 16(dst), 0, 0
  psq_l fp3, 24(src), 0, 0
  psq_st fp3, 24(dst), 0, 0
  psq_l fp4, 32(src), 0, 0
  psq_st fp4, 32(dst), 0, 0
  psq_l fp5, 40(src), 0, 0
  psq_st fp5, 40(dst), 0, 0

  blr
    // clang-format on
}
#endif

#ifdef GEKKO
asm void PSMTXConcat(const register Mtx mA, const register Mtx mB, register Mtx mAB)
{
    // clang-format off
  nofralloc

#define FP0 fp0
#define FP1 fp1
#define FP2 fp2
#define FP3 fp3
#define FP4 fp4
#define FP5 fp5
#define FP6 fp6
#define FP7 fp7
#define FP8 fp8
#define FP9 fp9
#define FP10 fp10
#define FP11 fp11
#define FP12 fp12
#define FP13 fp13
#define FP14 fp14
#define FP15 fp15
#define FP31 fp31
    stwu    r1, -64(r1);
    psq_l   FP0, 0(mA), 0, 0;
    stfd    fp14, 8(r1);
    psq_l   FP6, 0(mB), 0, 0;
    addis   r6, 0, Unit01@ha;
    psq_l   FP7, 8(mB), 0, 0;
    stfd    fp15, 16(r1)
    addi    r6, r6, Unit01@l;
    stfd    fp31, 40(r1)
    psq_l   FP8, 16(mB), 0, 0
    ps_muls0 FP12, FP6, FP0
    psq_l   FP2, 16(mA), 0, 0
    ps_muls0 FP13, FP7, FP0
    psq_l   FP31, 0(r6), 0, 0
    ps_muls0 FP14, FP6, FP2
    psq_l   FP9, 24(mB), 0, 0
    ps_muls0 FP15, FP7, FP2
    psq_l   FP1, 8(mA), 0, 0
    ps_madds1 FP12, FP8, FP0, FP12
    psq_l   FP3, 24(mA), 0, 0
    ps_madds1 FP14, FP8, FP2, FP14
    psq_l   FP10, 32(mB), 0, 0
    ps_madds1 FP13, FP9, FP0, FP13
    psq_l   FP11, 40(mB), 0, 0
    ps_madds1 FP15, FP9, FP2, FP15
    psq_l   FP4, 32(mA), 0, 0
    psq_l   FP5, 40(mA), 0, 0
    ps_madds0 FP12, FP10, FP1, FP12
    ps_madds0 FP13, FP11, FP1, FP13
    ps_madds0 FP14, FP10, FP3, FP14
    ps_madds0 FP15, FP11, FP3, FP15
    psq_st  FP12, 0(mAB), 0, 0

    ps_muls0 FP2, FP6, FP4
    ps_madds1 FP13, FP31, FP1, FP13
    ps_muls0 FP0, FP7, FP4
    psq_st  FP14, 16(mAB), 0, 0
    ps_madds1 FP15, FP31, FP3, FP15

    psq_st  FP13, 8(mAB), 0, 0

    ps_madds1 FP2, FP8, FP4, FP2
    ps_madds1 FP0, FP9, FP4, FP0
    ps_madds0 FP2, FP10, FP5, FP2
    lfd    fp14, 8(r1)
    psq_st  FP15, 24(mAB), 0, 0
    ps_madds0 FP0, FP11, FP5, FP0
    psq_st  FP2, 32(mAB), 0, 0
    ps_madds1 FP0, FP31, FP5, FP0
    lfd    fp15, 16(r1)
    psq_st  FP0, 40(mAB), 0, 0

    lfd    fp31, 40(r1)
    addi   r1, r1, 64

    blr
    // clang-format on

#undef FP0
#undef FP1
#undef FP2
#undef FP3
#undef FP4
#undef FP5
#undef FP6
#undef FP7
#undef FP8
#undef FP9
#undef FP10
#undef FP11
#undef FP12
#undef FP13
#undef FP14
#undef FP15
#undef FP31
}
#endif

#ifdef GEKKO
void PSMTXTranspose(const register Mtx src, register Mtx xPose)
{
    register f32 c_zero = 0.0F;
    register f32 row0a, row1a, row0b, row1b;
    register f32 trns0, trns1, trns2;
    // clang-format off
  asm
  {
    psq_l       row0a, 0(src),  0, 0
    stfs        c_zero, 44(xPose) 
    psq_l       row1a, 16(src), 0, 0
    ps_merge00  trns0, row0a, row1a 
    psq_l       row0b, 8(src),  1, 0
    ps_merge11  trns1, row0a, row1a 
    psq_l       row1b, 24(src), 1, 0
    psq_st      trns0, 0(xPose),  0, 0
    psq_l       row0a, 32(src), 0, 0
    ps_merge00  trns2, row0b, row1b 
    psq_st      trns1, 16(xPose), 0, 0 
    ps_merge00  trns0, row0a, c_zero 
    psq_st      trns2, 32(xPose), 0, 0
    ps_merge10  trns1, row0a, c_zero 
    psq_st      trns0, 8(xPose),  0, 0 
    lfs         row0b, 40(src) 
    psq_st      trns1, 24(xPose), 0, 0
    stfs        row0b, 40(xPose) 
  }
    // clang-format on
}
#endif

#ifdef GEKKO
asm u32 PSMTXInverse(const register Mtx src, register Mtx inv) {
    // clang-format off
  nofralloc

  psq_l       fp0, 0(src), 1, 0
  psq_l       fp1, 4(src), 0, 0
  psq_l       fp2, 16(src), 1, 0
  ps_merge10  fp6, fp1, fp0
  psq_l       fp3, 20(src), 0, 0
  psq_l       fp4, 32(src), 1, 0
  ps_merge10  fp7, fp3, fp2
  psq_l       fp5, 36(src), 0, 0
  ps_mul      fp11, fp3, fp6
  ps_mul      fp13, fp5, fp7
  ps_merge10  fp8, fp5, fp4
  ps_msub     fp11, fp1, fp7, fp11
  ps_mul      fp12, fp1, fp8
  ps_msub     fp13, fp3, fp8, fp13
  ps_mul      fp10, fp3, fp4
  ps_msub     fp12, fp5, fp6, fp12
  ps_mul      fp9,  fp0, fp5
  ps_mul      fp8,  fp1, fp2
  ps_sub      fp6, fp6, fp6
  ps_msub     fp10, fp2, fp5, fp10
  ps_mul      fp7, fp0, fp13
  ps_msub     fp9,  fp1, fp4, fp9
  ps_madd     fp7, fp2, fp12, fp7
  ps_msub     fp8,  fp0, fp3, fp8
  ps_madd     fp7, fp4, fp11, fp7
  ps_cmpo0    cr0, fp7, fp6
  bne         _regular
  addi        r3, 0, 0
  blr

_regular:
  fres        fp0, fp7
  ps_add      fp6, fp0, fp0
  ps_mul      fp5, fp0, fp0
  ps_nmsub    fp0, fp7, fp5, fp6
  lfs         fp1, 12(src)
  ps_muls0    fp13, fp13, fp0
  lfs         fp2, 28(src)
  ps_muls0    fp12, fp12, fp0
  lfs         fp3, 44(src)
  ps_muls0    fp11, fp11, fp0
  ps_merge00  fp5, fp13, fp12
  ps_muls0    fp10, fp10, fp0
  ps_merge11  fp4, fp13, fp12
  ps_muls0    fp9,  fp9,  fp0
  psq_st      fp5,  0(inv), 0, 0
  ps_mul      fp6, fp13, fp1
  psq_st      fp4,  16(inv), 0, 0
  ps_muls0    fp8,  fp8,  fp0
  ps_madd     fp6, fp12, fp2, fp6
  psq_st      fp10, 32(inv), 1, 0
  ps_nmadd    fp6, fp11, fp3, fp6
  psq_st      fp9,  36(inv), 1, 0
  ps_mul      fp7, fp10, fp1
  ps_merge00  fp5, fp11, fp6
  psq_st      fp8,  40(inv), 1, 0
  ps_merge11  fp4, fp11, fp6
  psq_st      fp5,  8(inv), 0, 0
  ps_madd     fp7, fp9,  fp2, fp7
  psq_st      fp4,  24(inv), 0, 0
  ps_nmadd    fp7, fp8,  fp3, fp7
  addi        r3, 0, 1
  psq_st      fp7,  44(inv), 1, 0
  blr
    // clang-format on
}
#endif

#ifdef GEKKO
void PSMTXRotRad(Mtx m, char axis, f32 rad)
{
    f32 sinA, cosA;

    sinA = sinf(rad);
    cosA = cosf(rad);

    PSMTXRotTrig(m, axis, sinA, cosA);
}
#endif

#ifdef GEKKO
/*
 * --INFO--
 * PAL Address: 0x80185c9c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void PSMTXRotTrig(register Mtx m, register char axis, register f32 sinA, register f32 cosA)
{
    register f32 fc0, fc1, nsinA;
    register f32 fw0, fw1, fw2, fw3;
    register f32 cosB, sinB;
    // clang-format off

  asm {
    frsp sinB, sinA
    frsp cosB, cosA
  }
  fc0 = 0.0F;
  fc1 = 1.0F;
  asm
  {
    ori         axis, axis, 0x20
    ps_neg      nsinA, sinB
    cmplwi      axis, 'x'
    beq         _case_x
    cmplwi      axis, 'y'
    beq         _case_y
    cmplwi      axis, 'z'
    beq         _case_z
    b           _end

_case_x:
    psq_st      fc1,  0(m), 1, 0
    psq_st      fc0,  4(m), 0, 0
    ps_merge00  fw0, sinB, cosB
    psq_st      fc0, 12(m), 0, 0
    ps_merge00  fw1, cosB, nsinA
    psq_st      fc0, 28(m), 0, 0
    psq_st      fc0, 44(m), 1, 0
    psq_st      fw0, 36(m), 0, 0
    psq_st      fw1, 20(m), 0, 0
    b           _end;

_case_y:
    ps_merge00  fw0, cosB, fc0
    ps_merge00  fw1, fc0, fc1
    psq_st      fc0, 24(m), 0, 0
    psq_st      fw0,  0(m), 0, 0
    ps_merge00  fw2, nsinA, fc0
    ps_merge00  fw3, sinB, fc0
    psq_st      fw0, 40(m), 0, 0;
    psq_st      fw1, 16(m), 0, 0;
    psq_st      fw3,  8(m), 0, 0;
    psq_st      fw2, 32(m), 0, 0;
    b           _end;

_case_z:
    psq_st      fc0,  8(m), 0, 0
    ps_merge00  fw0, sinB, cosB
    ps_merge00  fw2, cosB, nsinA
    psq_st      fc0, 24(m), 0, 0
    psq_st      fc0, 32(m), 0, 0
    ps_merge00  fw1, fc1, fc0
    psq_st      fw0, 16(m), 0, 0
    psq_st      fw2,  0(m), 0, 0
    psq_st      fw1, 40(m), 0, 0

_end:
  }
    // clang-format on
}

#endif

#ifdef GEKKO
#define qr0 0

/*
 * --INFO--
 * PAL Address: 0x80185d4c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void __PSMTXRotAxisRadInternal(register f32 sT, register f32 cT, register Mtx m, register const Vec *axis)
{
    register f32 tT;
    register f32 fc0;
    register f32 tmp0;
    register f32 tmp1;
    register f32 tmp2;
    register f32 tmp3;
    register f32 tmp4;
    register f32 tmp5;
    register f32 tmp6;
    register f32 tmp7;
    register f32 tmp8;
    register f32 tmp9;

    tmp9 = 0.5f;
    tmp8 = 3.0f;

#ifdef __MWERKS__ // clang-format off
    asm {
        frsp cT, cT
        psq_l tmp0, 0x0(axis), 0, 0
        frsp sT, sT
        lfs tmp1, 0x8(axis)
        ps_mul tmp2, tmp0, tmp0
        fadds tmp7, tmp9, tmp9
        ps_madd tmp3, tmp1, tmp1, tmp2
        fsubs fc0, tmp9, tmp9
        ps_sum0 tmp4, tmp3, tmp1, tmp2
        fsubs tT, tmp7, cT
        frsqrte tmp5, tmp4
        fmuls tmp2, tmp5, tmp5
        fmuls tmp3, tmp5, tmp9
        fnmsubs tmp2, tmp2, tmp4, tmp8
        fmuls tmp5, tmp2, tmp3
        ps_merge00 cT, cT, cT
        ps_muls0 tmp0, tmp0, tmp5
        ps_muls0 tmp1, tmp1, tmp5
        ps_muls0 tmp4, tmp0, tT
        ps_muls0 tmp9, tmp0, sT
        ps_muls0 tmp5, tmp1, tT
        ps_muls1 tmp3, tmp4, tmp0
        ps_muls0 tmp2, tmp4, tmp0
        ps_muls0 tmp4, tmp4, tmp1
        fnmsubs tmp6, tmp1, sT, tmp3
        fmadds tmp7, tmp1, sT, tmp3
        ps_neg tmp0, tmp9
        ps_sum0 tmp8, tmp4, fc0, tmp9
        ps_sum0 tmp2, tmp2, tmp6, cT
        ps_sum1 tmp3, cT, tmp7, tmp3
        ps_sum0 tmp6, tmp0, fc0, tmp4
        psq_st tmp8, 0x8(m), 0, qr0
        ps_sum0 tmp0, tmp4, tmp4, tmp0
        psq_st tmp2, 0x0(m), 0, qr0
        ps_muls0 tmp5, tmp5, tmp1
        psq_st tmp3, 0x10(m), 0, qr0
        ps_sum1 tmp4, tmp9, tmp0, tmp4
        psq_st tmp6, 0x18(m), 0, qr0
        ps_sum0 tmp5, tmp5, fc0, cT
        psq_st tmp4, 0x20(m), 0, qr0
        psq_st tmp5, 0x28(m), 0, qr0
  }
#endif // clang-format on
}

/*
 * --INFO--
 * PAL Address: 0x80185dfc
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void PSMTXRotAxisRad(register Mtx m, const Vec *axis, register f32 rad)
{
    register f32 sT;
    register f32 cT;

    sT = sinf(rad);
    cT = cosf(rad);
    __PSMTXRotAxisRadInternal(sT, cT, m, axis);
}

#endif

#ifdef GEKKO
void PSMTXTrans(register Mtx m, register f32 xT, register f32 yT, register f32 zT)
{
    register f32 c0 = 0.0F;
    register f32 c1 = 1.0F;
    // clang-format off
  asm
  {
    stfs        xT,     12(m)
    stfs        yT,     28(m)
    psq_st      c0,      4(m), 0, 0
    psq_st      c0,     32(m), 0, 0
    stfs        c0,     16(m)
    stfs        c1,     20(m)
    stfs        c0,     24(m)
    stfs        c1,     40(m)
    stfs        zT,     44(m)
    stfs        c1,      0(m)
  }
    // clang-format on
}
#endif

#ifdef GEKKO
asm void PSMTXTransApply(const register Mtx src, register Mtx dst, register f32 xT, register f32 yT, register f32 zT)
{
    // clang-format off
  nofralloc;
  psq_l       fp4, 0(src),        0, 0
  frsp        xT, xT
  psq_l       fp5, 8(src),        0, 0
  frsp        yT, yT
  psq_l       fp7, 24(src),       0, 0
  frsp        zT, zT
  psq_l       fp8, 40(src),       0, 0
  psq_st      fp4, 0(dst),        0, 0
  ps_sum1     fp5, xT, fp5, fp5
  psq_l       fp6, 16(src),       0, 0   
  psq_st      fp5, 8(dst),        0, 0
  ps_sum1     fp7, yT, fp7, fp7
  psq_l       fp9, 32(src),       0, 0
  psq_st      fp6, 16(dst),       0, 0
  ps_sum1     fp8, zT, fp8, fp8
  psq_st      fp7, 24(dst),       0, 0
  psq_st      fp9, 32(dst),       0, 0
  psq_st      fp8, 40(dst),       0, 0
  blr
    // clang-format on
}
#endif

#ifdef GEKKO
void PSMTXScale(register Mtx m, register f32 xS, register f32 yS, register f32 zS)
{
    register f32 c0 = 0.0F;
    // clang-format off
  asm
  {
    stfs        xS,      0(m)
    psq_st      c0,      4(m), 0, 0
    psq_st      c0,     12(m), 0, 0
    stfs        yS,     20(m)
    psq_st      c0,     24(m), 0, 0
    psq_st      c0,     32(m), 0, 0
    stfs        zS,     40(m)
    stfs        c0,     44(m)
  }
    // clang-format on
}
#endif

#ifdef GEKKO
asm void PSMTXScaleApply(const register Mtx src, register Mtx dst, register f32 xS, register f32 yS, register f32 zS)
{
    // clang-format off
  nofralloc;
  frsp        xS, xS
  psq_l       fp4, 0(src),        0, 0
  frsp        yS, yS
  psq_l       fp5, 8(src),        0, 0
  frsp        zS, zS
  ps_muls0    fp4, fp4, xS
  psq_l       fp6, 16(src),       0, 0
  ps_muls0    fp5, fp5, xS
  psq_l       fp7, 24(src),       0, 0
  ps_muls0    fp6, fp6, yS
  psq_l       fp8, 32(src),       0, 0
  psq_st      fp4, 0(dst),        0, 0
  ps_muls0    fp7, fp7, yS
  psq_l       fp2, 40(src),       0, 0
  psq_st      fp5, 8(dst),        0, 0
  ps_muls0    fp8, fp8, zS
  psq_st      fp6, 16(dst),       0, 0
  ps_muls0    fp2, fp2, zS
  psq_st      fp7, 24(dst),       0, 0
  psq_st      fp8, 32(dst),       0, 0
  psq_st      fp2, 40(dst),       0, 0
  blr
    // clang-format on
}
#endif

#ifdef GEKKO
void PSMTXQuat(register Mtx m, const register Quaternion *q)
{
    register f32 c_zero, c_one, c_two, scale;
    register f32 tmp0, tmp1, tmp2, tmp3, tmp4;
    register f32 tmp5, tmp6, tmp7, tmp8, tmp9;

    c_one = 1.0F;
    // clang-format off
  asm
  {
    psq_l       tmp0, 0(q), 0, 0
    psq_l       tmp1, 8(q), 0, 0
    fsubs       c_zero, c_one, c_one
    fadds       c_two, c_one, c_one
    ps_mul      tmp2, tmp0, tmp0
    ps_merge10  tmp5, tmp0, tmp0
    ps_madd     tmp4, tmp1, tmp1, tmp2
    ps_mul      tmp3, tmp1, tmp1
    ps_sum0     scale, tmp4, tmp4, tmp4
    ps_muls1    tmp7, tmp5, tmp1
    fres        tmp9, scale
    ps_sum1     tmp4, tmp3, tmp4, tmp2
    ps_nmsub    scale, scale, tmp9, c_two
    ps_muls1    tmp6, tmp1, tmp1
    ps_mul      scale, tmp9, scale
    ps_sum0     tmp2, tmp2, tmp2, tmp2
    fmuls       scale, scale, c_two
    ps_madd     tmp8, tmp0, tmp5, tmp6
    ps_msub     tmp6, tmp0, tmp5, tmp6
    psq_st      c_zero, 12(m), 1, 0
    ps_nmsub    tmp2, tmp2, scale, c_one
    ps_nmsub    tmp4, tmp4, scale, c_one
    psq_st      c_zero, 44(m), 1, 0
    ps_mul      tmp8, tmp8, scale
    ps_mul      tmp6, tmp6, scale
    psq_st      tmp2, 40(m), 1, 0
    ps_madds0   tmp5, tmp0, tmp1, tmp7
    ps_merge00  tmp1, tmp8, tmp4
    ps_nmsub    tmp7, tmp7, c_two, tmp5
    ps_merge10  tmp0, tmp4, tmp6
    psq_st      tmp1, 16(m), 0, 0
    ps_mul      tmp5, tmp5, scale
    ps_mul      tmp7, tmp7, scale
    psq_st      tmp0,  0(m), 0, 0
    psq_st      tmp5,  8(m), 1, 0
    ps_merge10  tmp3, tmp7, c_zero
    ps_merge01  tmp9, tmp7, tmp5
    psq_st      tmp3, 24(m), 0, 0
    psq_st      tmp9, 32(m), 0, 0
  }
    // clang-format on
}
#endif

#ifdef GEKKO
void PSMTXReflect(register Mtx m, const register Vec *p, const register Vec *n)
{
    register f32 c_one = 1.0F;
    register f32 vn_xy, vn_z1, n2vn_xy, n2vn_z1, pdotn;
    register f32 tmp0, tmp1, tmp2, tmp3;
    register f32 tmp4, tmp5, tmp6, tmp7;
    // clang-format off
  asm
  {
    psq_l       vn_z1, 8(n), 1, 0
    psq_l       vn_xy, 0(n), 0, 0
    psq_l       tmp0,  0(p), 0, 0
    ps_nmadd    n2vn_z1, vn_z1, c_one, vn_z1
    psq_l       tmp1,  8(p), 1, 0
    ps_nmadd    n2vn_xy, vn_xy, c_one, vn_xy
    ps_muls0    tmp4, vn_xy, n2vn_z1
    ps_mul      pdotn, n2vn_xy, tmp0
    ps_muls0    tmp2, vn_xy, n2vn_xy
    ps_sum0     pdotn, pdotn, pdotn, pdotn
    ps_muls1    tmp3, vn_xy, n2vn_xy
    psq_st      tmp4, 32(m), 0, 0
    ps_sum0     tmp2, tmp2, tmp2, c_one
    ps_nmadd    pdotn, n2vn_z1, tmp1, pdotn
    ps_sum1     tmp3, c_one, tmp3, tmp3
    psq_st      tmp2,  0(m), 0, 0
    ps_muls0    tmp5, vn_xy, pdotn
    ps_merge00  tmp6, n2vn_z1, pdotn
    psq_st      tmp3, 16(m), 0, 0
    ps_merge00  tmp7, tmp4, tmp5
    ps_muls0    tmp6, tmp6, vn_z1
    ps_merge11  tmp5, tmp4, tmp5
    psq_st      tmp7,  8(m), 0, 0
    ps_sum0     tmp6, tmp6, tmp6, c_one
    psq_st      tmp5, 24(m), 0, 0
    psq_st      tmp6, 40(m), 0, 0
  }
    // clang-format on
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80186080
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void C_MTXLookAt(Mtx m, const Point3d* camPos, const Vec* camUp, const Point3d* target)
{
    Vec vLook, vRight, vUp;

    vLook.x = camPos->x - target->x;
    vLook.y = camPos->y - target->y;
    vLook.z = camPos->z - target->z;
    VECNormalize(&vLook, &vLook);
    VECCrossProduct(camUp, &vLook, &vRight);
    VECNormalize(&vRight, &vRight);
    VECCrossProduct(&vLook, &vRight, &vUp);

    m[0][0] = vRight.x;
    m[0][1] = vRight.y;
    m[0][2] = vRight.z;
    m[0][3] = -(camPos->x * vRight.x + camPos->y * vRight.y + camPos->z * vRight.z);

    m[1][0] = vUp.x;
    m[1][1] = vUp.y;
    m[1][2] = vUp.z;
    m[1][3] = -(camPos->x * vUp.x + camPos->y * vUp.y + camPos->z * vUp.z);

    m[2][0] = vLook.x;
    m[2][1] = vLook.y;
    m[2][2] = vLook.z;
    m[2][3] = -(camPos->x * vLook.x + camPos->y * vLook.y + camPos->z * vLook.z);
}

void C_MTXLightFrustum(Mtx m, float t, float b, float l, float r, float n, float scaleS, float scaleT, float transS, float transT)
{
    f32 tmp;
    f32 proj;

    tmp = 1.0f / (r - l);
    m[0][0] = ((2 * n) * tmp) * scaleS;
    m[0][1] = 0.0f;
    proj = (tmp * (r + l)) * scaleS;
    m[0][2] = proj - transS;
    m[0][3] = 0.0f;

    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = ((2 * n) * tmp) * scaleT;
    proj = (tmp * (t + b)) * scaleT;
    m[1][2] = proj - transT;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f;
    m[2][3] = 0.0f;
}

void C_MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, float scaleS, float scaleT, float transS, float transT)
{
    f32 angle;
    f32 cot;

    angle = fovY * 0.5f;
    angle = MTXDegToRad(angle);

    cot = 1.0f / tanf(angle);

    m[0][0] = (cot / aspect) * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = -transS;
    m[0][3] = 0.0f;

    m[1][0] = 0.0f;
    m[1][1] = cot * scaleT;
    m[1][2] = -transT;
    m[1][3] = 0.0f;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = -1.0f;
    m[2][3] = 0.0f;
}

void C_MTXLightOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, float scaleS, float scaleT, float transS, float transT)
{
    f32 tmp;
    f32 add;
    f32 negAdd;
    f32 proj;

    tmp = 1.0f / (r - l);
    m[0][0] = (2.0f * tmp) * scaleS;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    add = r + l;
    negAdd = -add;
    proj = (tmp * negAdd) * scaleS;
    m[0][3] = transS + proj;

    tmp = 1.0f / (t - b);
    m[1][0] = 0.0f;
    m[1][1] = (2.0f * tmp) * scaleT;
    m[1][2] = 0.0f;
    add = t + b;
    negAdd = -add;
    proj = (tmp * negAdd) * scaleT;
    m[1][3] = transT + proj;

    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 0.0f;
    m[2][3] = 1.0f;
}
