#include <dolphin.h>
#include <dolphin/mtx.h>
#include <math.h>

/*
 * TODO: Remove this note block once linkage has been resolved.
 *
 * Current blocker in this unit:
 * - after trimming GCCP01 down to the PAL-linked subset, mtx44.c now reports
 *   100% code/data in objdiff and promotes all the way to a plain final
 *   main.dol checksum miss, but it still does not link cleanly as Matching
 *
 * Most useful result so far:
 * - PAL map audit was the real fix for the bogus object-extent mismatch:
 *   GCCP01 only links `C_MTXPerspective`, `C_MTXOrtho`, `PSMTX44Identity`,
 *   `PSMTX44Copy`, `PSMTX44Concat`, and `C_MTX44Inverse`
 * - removing the PAL-unused helpers from this file drops rebuilt `mtx44.o`
 *   to that exact six-function `.text` slice and removes the old fake local
 *   `mtxUnit` `.data` blob from source output
 * - after that trim, `main/mtx/mtx44` is 100% in the report, but promoting
 *   just this unit still fails only at the final checksum
 * - that means the remaining blocker is no longer extra code/data in mtx44.c
 *   itself; it is the same shared hidden-link seam still affecting the mtx
 *   cluster after the linked subset has been recovered
 */

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 angle;
    f32 cot;
    f32 tmp;

    ASSERTMSGLINE(179, m, "MTXPerspective():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(180, (fovY > 0.0) && (fovY < 180.0), "MTXPerspective():  'fovY' out of range ");
    ASSERTMSGLINE(181, 0.0f != aspect, "MTXPerspective():  'aspect' is 0 ");

    angle = (0.5f * fovY);
    angle = MTXDegToRad(angle);
    cot = 1 / tanf(angle);
    m[0][0] = (cot / aspect);
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (cot);
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    ASSERTMSGLINE(254, m, "MTXOrtho():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(255, t != b, "MTXOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(256, l != r, "MTXOrtho():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(257, n != f, "MTXOrtho():  'n' and 'f' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = 2 * tmp;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = (tmp * -(r + l));
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = 2 * tmp;
    m[1][2] = 0;
    m[1][3] = (tmp * -(t + b));
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-1 * tmp);
    m[2][3] = (-f * tmp);
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}

void PSMTX44Identity(register Mtx44 m) {
    register f32 c1 = 1.0f;
    register f32 c0 = 0.0f;

    asm {
        stfs c1, 0x0(m)
        psq_st c0, 0x4(m), 0, 0
        psq_st c0, 0xc(m), 0, 0
        stfs c1, 0x14(m)
        psq_st c0, 0x18(m), 0, 0
        psq_st c0, 0x20(m), 0, 0
        stfs c1, 0x28(m)
        psq_st c0, 0x2c(m), 0, 0
        psq_st c0, 0x34(m), 0, 0
        stfs c1, 0x3c(m)
    }
}

asm void PSMTX44Copy(const register Mtx44 src, register Mtx44 dst) {
    nofralloc
    psq_l f1, 0x0(src), 0, 0
    psq_st f1, 0x0(dst), 0, 0
    psq_l f1, 0x8(src), 0, 0
    psq_st f1, 0x8(dst), 0, 0
    psq_l f1, 0x10(src), 0, 0
    psq_st f1, 0x10(dst), 0, 0
    psq_l f1, 0x18(src), 0, 0
    psq_st f1, 0x18(dst), 0, 0
    psq_l f1, 0x20(src), 0, 0
    psq_st f1, 0x20(dst), 0, 0
    psq_l f1, 0x28(src), 0, 0
    psq_st f1, 0x28(dst), 0, 0
    psq_l f1, 0x30(src), 0, 0
    psq_st f1, 0x30(dst), 0, 0
    psq_l f1, 0x38(src), 0, 0
    psq_st f1, 0x38(dst), 0, 0
    blr
}

asm void PSMTX44Concat(const register Mtx44 a, const register Mtx44 b, register Mtx44 ab) {
    nofralloc
    psq_l f0, 0x0(a), 0, 0
    psq_l f2, 0x0(b), 0, 0
    ps_muls0 f6, f2, f0
    psq_l f3, 0x10(b), 0, 0
    psq_l f4, 0x20(b), 0, 0
    ps_madds1 f6, f3, f0, f6
    psq_l f1, 0x8(a), 0, 0
    psq_l f5, 0x30(b), 0, 0
    ps_madds0 f6, f4, f1, f6
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f6, f5, f1, f6
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f8, f2, f0
    ps_madds1 f8, f3, f0, f8
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f8, f4, f1, f8
    ps_madds1 f8, f5, f1, f8
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f10, f2, f0
    ps_madds1 f10, f3, f0, f10
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f10, f4, f1, f10
    ps_madds1 f10, f5, f1, f10
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f12, f2, f0
    psq_l f2, 0x8(b), 0, 0
    ps_madds1 f12, f3, f0, f12
    psq_l f0, 0x0(a), 0, 0
    ps_madds0 f12, f4, f1, f12
    psq_l f3, 0x18(b), 0, 0
    ps_madds1 f12, f5, f1, f12
    psq_l f1, 0x8(a), 0, 0
    ps_muls0 f7, f2, f0
    psq_l f4, 0x28(b), 0, 0
    ps_madds1 f7, f3, f0, f7
    psq_l f5, 0x38(b), 0, 0
    ps_madds0 f7, f4, f1, f7
    psq_l f0, 0x10(a), 0, 0
    ps_madds1 f7, f5, f1, f7
    psq_l f1, 0x18(a), 0, 0
    ps_muls0 f9, f2, f0
    psq_st f6, 0x0(ab), 0, 0
    ps_madds1 f9, f3, f0, f9
    psq_l f0, 0x20(a), 0, 0
    ps_madds0 f9, f4, f1, f9
    psq_st f8, 0x10(ab), 0, 0
    ps_madds1 f9, f5, f1, f9
    psq_l f1, 0x28(a), 0, 0
    ps_muls0 f11, f2, f0
    psq_st f10, 0x20(ab), 0, 0
    ps_madds1 f11, f3, f0, f11
    psq_l f0, 0x30(a), 0, 0
    ps_madds0 f11, f4, f1, f11
    psq_st f12, 0x30(ab), 0, 0
    ps_madds1 f11, f5, f1, f11
    psq_l f1, 0x38(a), 0, 0
    ps_muls0 f13, f2, f0
    psq_st f7, 0x8(ab), 0, 0
    ps_madds1 f13, f3, f0, f13
    psq_st f9, 0x18(ab), 0, 0
    ps_madds0 f13, f4, f1, f13
    psq_st f11, 0x28(ab), 0, 0
    ps_madds1 f13, f5, f1, f13
    psq_st f13, 0x38(ab), 0, 0
    blr
}

#define SWAP(a, b) \
    {              \
        f32 tmp;   \
        tmp = a;   \
        a = b;     \
        b = tmp;   \
    }

/*
 * --INFO--
 * PAL Address: 0x8018680c
 * PAL Size: 1008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
u32 C_MTX44Inverse(const Mtx44 src, Mtx44 inv) {
    Mtx44 gjm;
    s32 i;
    s32 j;
    s32 k;
    f32 w;
    f32 max;
    s32 swp;
    f32 ftmp;

    ASSERTMSGLINE(734, src, "MTX44Inverse():  NULL Mtx44Ptr 'src' ");
    ASSERTMSGLINE(735, inv, "MTX44Inverse():  NULL Mtx44Ptr 'inv' ");

    MTX44Copy(src, gjm);
    MTX44Identity(inv);

    for (i = 0; i < 4; i++) {
        max = 0.0f;
        swp = i;

        for (k = i; k < 4; k++) {
            ftmp = __fabsf(gjm[k][i]);
            if (ftmp > max) {
                max = ftmp;
                swp = k;
            }
        }

        if (max == 0.0f) {
            return 0;
        }

        if (swp != i) {
            for (k = 0; k < 4; k++) {
                SWAP(gjm[i][k], gjm[swp][k]);
                SWAP(inv[i][k], inv[swp][k]);
            }
        }

        w = 1.0f / gjm[i][i];
        for (j = 0; j < 4; j++) {
            gjm[i][j] *= w;
            inv[i][j] *= w;
        }

        for (k = 0; k < 4; k++) {
            if (k != i) {
                w = gjm[k][i];
                for (j = 0; j < 4; j++) {
                    gjm[k][j] -= gjm[i][j] * w;
                    inv[k][j] -= inv[i][j] * w;
                }
            }
        }
    }

    return 1;
}
