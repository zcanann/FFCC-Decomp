#include "ffcc/pppSRandUpCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
extern u8 gPppDefaultValueBuffer[];
extern "C" float RandF__5CMathFv(CMath* instance);

struct SRandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
};

struct SRandUpCVCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 0x80064114
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpCV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    SRandUpCVParam* in = (SRandUpCVParam*)param2;
    SRandUpCVCtx* ctx = (SRandUpCVCtx*)param3;
    f32* target;

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (f32*)(base + *ctx->outputOffset + 0x80);

        {
            u8 flag = in->randomTwice;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpCVDualSampleScale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->randomTwice;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpCVDualSampleScale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->randomTwice;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpCVDualSampleScale;
            }
            target[2] = value;
        }

        {
            u8 flag = in->randomTwice;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpCVDualSampleScale;
            }
            target[3] = value;
        }
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        target = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s32 color_offset = in->sourceOffset;
    u8* target_colors = (color_offset == -1) ? gPppDefaultValueBuffer : (base + color_offset + 0x80);

    {
        s8 deltaBase = in->delta[0];
        s32 delta = (s32)((f32)deltaBase * target[0]);
        target_colors[0] = (u8)(target_colors[0] + delta);
    }

    {
        s8 deltaBase = in->delta[1];
        s32 delta = (s32)((f32)deltaBase * target[1]);
        target_colors[1] = (u8)(target_colors[1] + delta);
    }

    {
        s8 deltaBase = in->delta[2];
        s32 delta = (s32)((f32)deltaBase * target[2]);
        target_colors[2] = (u8)(target_colors[2] + delta);
    }

    {
        s8 deltaBase = in->delta[3];
        s32 delta = (s32)((f32)deltaBase * target[3]);
        target_colors[3] = (u8)(target_colors[3] + delta);
    }
}
