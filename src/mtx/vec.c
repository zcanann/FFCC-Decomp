#include <math.h>
#include "dolphin/mtx.h"

#define R_RET fp1
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

void C_VECAdd(const Vec* a, const Vec* b, Vec* ab)
{
    ASSERTMSGLINE(87, a, "VECAdd():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(88, b, "VECAdd():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(89, ab, "VECAdd():  NULL VecPtr 'ab' ");

    ab->x = a->x + b->x;
    ab->y = a->y + b->y;
    ab->z = a->z + b->z;
}

asm void PSVECAdd(const register Vec *vec1, const register Vec *vec2, register Vec *ret)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc;
	psq_l     FP2,  0(vec1), 0, 0;
	psq_l     FP4,  0(vec2), 0, 0;
	ps_add    FP6, FP2, FP4;
	psq_st    FP6,  0(ret), 0, 0;
	psq_l     FP3,   8(vec1), 1, 0;
	psq_l     FP5,   8(vec2), 1, 0;
	ps_add    FP7, FP3, FP5;
	psq_st    FP7,   8(ret), 1, 0;
	blr
#endif // clang-format on
}

void C_VECSubtract(const Vec* a, const Vec* b, Vec* a_b)
{
    ASSERTMSGLINE(156, a, "VECSubtract():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(157, b, "VECSubtract():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(158, a_b, "VECSubtract():  NULL VecPtr 'a_b' ");

    a_b->x = a->x - b->x;
    a_b->y = a->y - b->y;
    a_b->z = a->z - b->z;
}

asm void PSVECSubtract(const register Vec *vec1, const register Vec *vec2, register Vec *ret)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc;
	psq_l     FP2,  0(vec1), 0, 0;
	psq_l     FP4,  0(vec2), 0, 0;
	ps_sub    FP6, FP2, FP4;
	psq_st    FP6, 0(ret), 0, 0;
	psq_l     FP3,   8(vec1), 1, 0;
	psq_l     FP5,   8(vec2), 1, 0;
	ps_sub    FP7, FP3, FP5;
	psq_st    FP7,  8(ret), 1, 0;
	blr
#endif // clang-format on
}

void C_VECScale(const Vec* src, Vec* dst, f32 scale)
{
    ASSERTMSGLINE(226, src, "VECScale():  NULL VecPtr 'src' ");
    ASSERTMSGLINE(227, dst, "VECScale():  NULL VecPtr 'dst' ");

    dst->x = src->x * scale;
    dst->y = src->y * scale;
    dst->z = src->z * scale;
}

asm void PSVECScale(register const Vec *src, register Vec *dst, register f32 scale)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
	psq_l        f0, 0(src), 0, 0
    psq_l        f2, 8(src), 1, 0
    ps_muls0     f0, f0, f1
    psq_st       f0, 0(dst), 0, 0
    ps_muls0     f0, f2, f1
    psq_st       f0, 8(dst), 1, 0
    blr 
#endif // clang-format on
}

void C_VECNormalize(const Vec* src, Vec* unit)
{
    f32 mag;

    ASSERTMSGLINE(295, src, "VECNormalize():  NULL VecPtr 'src' ");
    ASSERTMSGLINE(296, unit, "VECNormalize():  NULL VecPtr 'unit' ");

    mag = (src->x * src->x) + (src->y * src->y) + (src->z * src->z);
    ASSERTMSGLINE(301, 0.0f != mag, "VECNormalize():  zero magnitude vector ");

    mag     = 1.0f / sqrtf(mag);
    unit->x = src->x * mag;
    unit->y = src->y * mag;
    unit->z = src->z * mag;
}

void PSVECNormalize(const register Vec *vec1, register Vec *ret)
{
#ifdef __MWERKS__ // clang-format off
	register f32 half  = 0.5f;
	register f32 three = 3.0f;
	register f32 xx_zz, xx_yy;
	register f32 square_sum;
	register f32 ret_sqrt;
	register f32 n_0, n_1;
	asm {
		psq_l       FP2, 0(vec1), 0, 0;
		ps_mul      xx_yy, FP2, FP2;
		psq_l       FP3, 8(vec1), 1, 0;
		ps_madd     xx_zz, FP3, FP3, xx_yy;
		ps_sum0     square_sum, xx_zz, FP3, xx_yy;
		frsqrte     ret_sqrt, square_sum;
		fmuls       n_0, ret_sqrt, ret_sqrt;
		fmuls       n_1, ret_sqrt, half;
		fnmsubs     n_0, n_0, square_sum, three;
		fmuls       ret_sqrt, n_0, n_1;
		ps_muls0    FP2, FP2, ret_sqrt;
		psq_st      FP2, 0(ret), 0, 0;
		ps_muls0    FP3, FP3, ret_sqrt;
		psq_st      FP3, 8(ret), 1, 0;
	}
#endif // clang-format on
}

f32 C_VECSquareMag(const Vec* v)
{
    f32 sqmag;

    ASSERTMSGLINE(386, v, "VECMag():  NULL VecPtr 'v' ");

    sqmag = (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
    return sqmag;
}

asm f32 PSVECSquareMag(register const Vec *v) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
    psq_l      f0, 0(v), 0, 0
    ps_mul     f0, f0, f0
    lfs        f1, 8(v)
    ps_madd    f1, f1, f1, f0
    ps_sum0    f1, f1, f0, f0
    blr 
#endif // clang-format on
}

f32 C_VECMag(const Vec* v)
{
    return sqrtf(C_VECSquareMag(v));
}

f32 PSVECMag(const register Vec *v)
{
#ifdef __MWERKS__ // clang-format off
    register f32 vxy, vzz;
    register f32 sqmag, rmag;
    register f32 nwork0, nwork1;
    register f32 c_three, c_half, c_zero;

    c_half = 0.5f;

    asm {
        psq_l vxy, 0(v), 0, 0
        ps_mul vxy, vxy, vxy
        lfs vzz, 8(v)
        fsubs c_zero, c_half, c_half
        ps_madd sqmag, vzz, vzz, vxy
        ps_sum0 sqmag, sqmag, vxy, vxy
        fcmpu cr0, sqmag, c_zero
        beq lbl_PSVECMag_ret
        frsqrte rmag, sqmag
    }

    c_three = 3.0f;

    asm {
        fmuls nwork0, rmag, rmag
        fmuls nwork1, rmag, c_half
        fnmsubs nwork0, nwork0, sqmag, c_three
        fmuls rmag, nwork0, nwork1
        fmuls sqmag, sqmag, rmag
    lbl_PSVECMag_ret:
    }

    return sqmag;
#endif // clang-format on
}

f32 C_VECDotProduct(const Vec* a, const Vec* b)
{
    f32 dot;

    ASSERTMSGLINE(465, a, "VECDotProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(466, b, "VECDotProduct():  NULL VecPtr 'b' ");

    dot = (a->z * b->z) + ((a->x * b->x) + (a->y * b->y));
    return dot;
}

asm f32 PSVECDotProduct(const register Vec *vec1, const register Vec *vec2)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc;
    psq_l      f2, 4(r3), 0, 0 /* qr0 */
    psq_l      f3, 4(r4), 0, 0 /* qr0 */
    ps_mul     f2, f2, f3
    psq_l      f5, 0(r3), 0, 0 /* qr0 */
    psq_l      f4, 0(r4), 0, 0 /* qr0 */
    ps_madd    f3, f5, f4, f2
    ps_sum0    f1, f3, f2, f2
    blr 
#endif // clang-format on
}

void C_VECCrossProduct(const Vec* a, const Vec* b, Vec* axb)
{
    Vec tmp;

    ASSERTMSGLINE(527, a, "VECCrossProduct():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(528, b, "VECCrossProduct():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(529, axb, "VECCrossProduct():  NULL VecPtr 'axb' ");

    tmp.x  = (a->y * b->z) - (a->z * b->y);
    tmp.y  = (a->z * b->x) - (a->x * b->z);
    tmp.z  = (a->x * b->y) - (a->y * b->x);
    axb->x = tmp.x;
    axb->y = tmp.y;
    axb->z = tmp.z;
}

asm void PSVECCrossProduct(register const Vec *a, register const Vec *b, register Vec *axb)
{
#ifdef __MWERKS__ // clang-format off
	nofralloc
    psq_l          f1, 0(b), 0, 0
    lfs            f2, 8(a)
    psq_l          f0, 0(a), 0, 0
    ps_merge10     f6, f1, f1
    lfs            f3, 8(b)
    ps_mul         f4, f1, f2
    ps_muls0       f7, f1, f0
    ps_msub        f5, f0, f3, f4
    ps_msub        f8, f0, f6, f7
    ps_merge11     f9, f5, f5
    ps_merge01     f10, f5, f8
    psq_st         f9, 0(axb), 1, 0
    ps_neg         f10, f10
    psq_st         f10, 4(axb), 0, 0
    blr 
#endif // clang-format on
}

void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half)
{
    Vec aTmp;
    Vec bTmp;
    Vec hTmp;

    ASSERTMSGLINE(639, a, "VECHalfAngle():  NULL VecPtr 'a' ");
    ASSERTMSGLINE(640, b, "VECHalfAngle():  NULL VecPtr 'b' ");
    ASSERTMSGLINE(641, half, "VECHalfAngle():  NULL VecPtr 'half' ");

    aTmp.x = -a->x;
    aTmp.y = -a->y;
    aTmp.z = -a->z;
    bTmp.x = -b->x;
    bTmp.y = -b->y;
    bTmp.z = -b->z;
    C_VECNormalize(&aTmp, &aTmp);
    C_VECNormalize(&bTmp, &bTmp);
    C_VECAdd(&aTmp, &bTmp, &hTmp);
    if (C_VECDotProduct(&hTmp, &hTmp) > 0.0f) {
        C_VECNormalize(&hTmp, half);
        return;
    }
    *half = hTmp;
}

void C_VECReflect(const Vec *src, const Vec *normal, Vec *dst)
{
    Vec a0;
    Vec b0;
    f32 dot;
    f32 scaledDot;

    a0.x = -src->x;
    a0.y = -src->y;
    a0.z = -src->z;

    VECNormalize(&a0, &a0);
    VECNormalize(normal, &b0);

    dot = VECDotProduct(&a0, &b0);
    scaledDot = b0.x * 2.0f * dot;
    dst->x = scaledDot - a0.x;
    scaledDot = b0.y * 2.0f * dot;
    dst->y = scaledDot - a0.y;
    scaledDot = b0.z * 2.0f * dot;
    dst->z = scaledDot - a0.z;

    VECNormalize(dst, dst);
}

f32 C_VECSquareDistance(const Vec* a, const Vec* b)
{
    Vec diff;

    diff.x = a->x - b->x;
    diff.y = a->y - b->y;
    diff.z = a->z - b->z;
    return (diff.z * diff.z) + ((diff.x * diff.x) + (diff.y * diff.y));
}

asm f32 PSVECSquareDistance(register const Vec *a, register const Vec *b) {
#ifdef __MWERKS__ // clang-format off
	nofralloc
    psq_l      f0, 4(a), 0, 0
    psq_l      f1, 4(b), 0, 0
    ps_sub     f2, f0, f1
    psq_l      f0, 0(a), 0, 0
    psq_l      f1, 0(b), 0, 0
    ps_mul     f2, f2, f2
    ps_sub     f0, f0, f1
    ps_madd    f1, f0, f0, f2
    ps_sum0    f1, f1, f2, f2
    blr 
#endif // clang-format on
}

f32 C_VECDistance(const Vec* a, const Vec* b)
{
    return sqrtf(C_VECSquareDistance(a, b));
}

f32 PSVECDistance(register const Vec *a, register const Vec *b)
{
#ifdef __MWERKS__ // clang-format off
    register f32 v0yz, v1yz, v0xy, v1xy, dyz, dxy;
    register f32 sqdist, rdist;
    register f32 nwork0, nwork1;
    register f32 c_half, c_three, c_zero;

    asm {
        psq_l v0yz, 4(a), 0, 0
        psq_l v1yz, 4(b), 0, 0
        ps_sub dyz, v0yz, v1yz
        psq_l v0xy, 0(a), 0, 0
        psq_l v1xy, 0(b), 0, 0
        ps_mul dyz, dyz, dyz
        ps_sub dxy, v0xy, v1xy
    }

    c_half = 0.5f;

    asm {
        ps_madd sqdist, dxy, dxy, dyz
        fsubs c_zero, c_half, c_half
        ps_sum0 sqdist, sqdist, dyz, dyz
        fcmpu cr0, c_zero, sqdist
        beq lbl_PSVECDistance_ret
    }

    c_three = 3.0f;

    asm {
        frsqrte rdist, sqdist
        fmuls nwork0, rdist, rdist
        fmuls nwork1, rdist, c_half
        fnmsubs nwork0, nwork0, sqdist, c_three
        fmuls rdist, nwork0, nwork1
        fmuls sqdist, sqdist, rdist
    lbl_PSVECDistance_ret:
    }

    return sqdist;
#endif // clang-format on
}
