#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
extern u8 gPppDefaultValueBuffer[32];
extern "C" f32 RandF__5CMathFv(CMath* instance);

struct RandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
};

struct RandUpCVCtx {
    u8 _pad[0xC];
    s32* outputOffset;
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
    u8* base = (u8*)param1;
    RandUpCVParam* in = (RandUpCVParam*)param2;
    RandUpCVCtx* ctx = (RandUpCVCtx*)param3;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        f32 value = RandF__5CMathFv(&Math);
        if (in->randomTwice != 0) {
            f32 random = RandF__5CMathFv(&Math);
            f32 blend = value + random;
            value = blend * kPppRandUpCVDualSampleScale;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else if (in->targetId != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    target = (in->sourceOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + in->sourceOffset + 0x80);

    {
        f32 scale = *valuePtr;
        {
            s8 baseValue = in->delta[0];
            target[0] = (u8)(target[0] + (s32)((f32)baseValue * scale));
        }
        {
            s8 baseValue = in->delta[1];
            target[1] = (u8)(target[1] + (s32)((f32)baseValue * scale));
        }
        {
            s8 baseValue = in->delta[2];
            target[2] = (u8)(target[2] + (s32)((f32)baseValue * scale));
        }
        {
            s8 baseValue = in->delta[3];
            target[3] = (u8)(target[3] + (s32)((f32)baseValue * scale));
        }
    }
}
