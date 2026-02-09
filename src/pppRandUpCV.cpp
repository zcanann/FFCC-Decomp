#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF08;
extern f64 lbl_8032FF10;
extern u8 lbl_801EADC8[32];
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandUpCVParams {
    s32 index;
    s32 colorOffset;
    s8 delta[4];
    u8 randomTwice;
    u8 pad[3];
};

struct RandUpCVCtx {
    u8 _pad[0xC];
    s32* valueOffset;
};

union RandUpCVConv {
    f64 d;
    struct {
        u32 hi;
        u32 lo;
    } parts;
};

/*
 * --INFO--
 * PAL Address: 0x80062708
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandUpCVParams* in = (RandUpCVParams*)param2;
    RandUpCVCtx* ctx = (RandUpCVCtx*)param3;
    s32 state = *(s32*)(base + 0xC);

    if (in->index == state) {
        f32 value = RandF__5CMathFv(&math);
        if (in->randomTwice != 0) {
            value = (value + RandF__5CMathFv(&math)) * lbl_8032FF08;
        }
        *(f32*)(base + *ctx->valueOffset + 0x80) = value;
    } else if (in->index != state) {
        return;
    }

    f32 scale = *(f32*)(base + *ctx->valueOffset + 0x80);

    u8* target;
    if (in->colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = base + in->colorOffset + 0x80;
    }

    RandUpCVConv cvt;
    cvt.parts.hi = 0x43300000;

    cvt.parts.lo = (u32)((s32)in->delta[0] ^ 0x8000);
    target[0] = (u8)(target[0] + (s32)((cvt.d - lbl_8032FF10) * scale));

    cvt.parts.lo = (u32)((s32)in->delta[1] ^ 0x8000);
    target[1] = (u8)(target[1] + (s32)((cvt.d - lbl_8032FF10) * scale));

    cvt.parts.lo = (u32)((s32)in->delta[2] ^ 0x8000);
    target[2] = (u8)(target[2] + (s32)((cvt.d - lbl_8032FF10) * scale));

    cvt.parts.lo = (u32)((s32)in->delta[3] ^ 0x8000);
    target[3] = (u8)(target[3] + (s32)((cvt.d - lbl_8032FF10) * scale));
}

/*
 * --INFO--
 * Address: TODO  
 * Size: TODO
 */
void randchar(char, float)
{
    // TODO - appears to be unused based on objdiff
}
