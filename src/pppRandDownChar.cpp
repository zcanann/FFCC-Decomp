#include "ffcc/pppRandDownChar.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF18;
extern f64 lbl_8032FF20;
extern u8 lbl_801EADC8;
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandDownCharParam {
    s32 targetId;
    s32 sourceOffset;
    u8 scale;
    u8 randomTwice;
};

struct RandDownCharCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 80061258
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownChar(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    RandDownCharParam* in = (RandDownCharParam*)param2;
    RandDownCharCtx* ctx = (RandDownCharCtx*)param3;
    f32* valuePtr;

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = -RandF__5CMathFv(&math);
        if (in->randomTwice != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_8032FF18;
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
        target = &lbl_801EADC8;
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
    cvt.parts.hi = 0x43300000;
    cvt.parts.lo = in->scale;

    s32 delta = (s32)((cvt.d - lbl_8032FF20) * *valuePtr);
    *target = (u8)(*target + delta);
}
