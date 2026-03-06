#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
extern CMath Math;
extern int gPppCalcDisabled;
extern s16 gPppDefaultValueBuffer[];
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandUpShortParam {
    s32 targetId;
    s32 sourceOffset;
    u16 scale;
    u8 randomTwice;
};

struct RandUpShortCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpShort(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandUpShortParam* in = (RandUpShortParam*)param2;
    RandUpShortCtx* ctx = (RandUpShortCtx*)param3;
    s16* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = RandF__5CMathFv(&Math);
        if (in->randomTwice != 0) {
            f32 mixed = value + RandF__5CMathFv(&Math);
            value = mixed * kPppRandUpShortDualSampleScale;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (in->targetId != state) {
            return;
        }
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    target = (in->sourceOffset == -1) ? &gPppDefaultValueBuffer[0] : (s16*)(base + in->sourceOffset + 0x80);

    u16 scale = in->scale;
    f32 scaled = (f32)scale * *valuePtr;
    s32 delta = (s32)scaled;
    *target = (s16)(*target + delta);
}
