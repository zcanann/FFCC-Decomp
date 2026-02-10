#include "ffcc/pppRandChar.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FEF8;
extern f64 lbl_8032FF00;
extern u8 lbl_801EADC8[32];
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 randomTwice;
};

struct RandCharCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80060efc
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandChar(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandCharParam* in = (RandCharParam*)param2;
    RandCharCtx* ctx = (RandCharCtx*)param3;
    f32* valuePtr;

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = RandF__5CMathFv(math);
        if (in->randomTwice != 0) {
            value += RandF__5CMathFv(math);
        } else {
            value *= lbl_8032FEF8;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    u8* target;
    if (in->sourceOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = base + in->sourceOffset + 0x80;
    }

    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } parts;
    } cvt;

    u8 current = *target;
    cvt.parts.hi = 0x43300000;
    cvt.parts.lo = in->scale;
    f64 scaled = cvt.d - lbl_8032FF00;
    cvt.parts.lo = current;

    s32 delta = (s32)(scaled * *valuePtr - (cvt.d - lbl_8032FF00));
    *target = (u8)(current + delta);
}
