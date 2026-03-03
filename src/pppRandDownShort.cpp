#include "ffcc/pppRandDownShort.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern "C" f32 RandF__5CMathFv(CMath*);

extern s32 lbl_8032ED70;
extern f32 lbl_8032FF78;
extern f64 lbl_8032FF80;
extern s16 lbl_801EADC8[];

struct RandDownShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 randomTwice;
};

struct RandDownShortCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80061c1c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownShort(void* r3, void* r4, void* r5)
{
    u8* base = (u8*)r3;
    RandDownShortParam* in = (RandDownShortParam*)r4;
    RandDownShortCtx* ctx = (RandDownShortCtx*)r5;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -RandF__5CMathFv(&math[0]);

        if (in->randomTwice != 0) {
            value = (value - RandF__5CMathFv(&math[0])) * lbl_8032FF78;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s16* target;
    if (in->sourceOffset == -1) {
        target = &lbl_801EADC8[0];
    } else {
        target = (s16*)(base + in->sourceOffset + 0x80);
    }

    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } bits;
    } cvt;

    cvt.bits.hi = 0x43300000;
    cvt.bits.lo = in->scale;

    s32 delta = (s32)((cvt.d - lbl_8032FF80) * *valuePtr);
    *target = (s16)(*target + delta);
}
