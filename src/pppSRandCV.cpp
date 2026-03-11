#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"
extern "C" float RandF__5CMathFv(CMath* instance);

struct SRandCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
};

struct SRandCVCtx {
    u8 _pad[0xC];
    s32* outputOffset;
};

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    SRandCVParam* in = (SRandCVParam*)param2;
    SRandCVCtx* ctx = (SRandCVCtx*)param3;
    if (gPppCalcDisabled != 0) {
        return;
    }

    float* target;

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (float*)(base + *ctx->outputOffset + 0x80);

        {
            u8 flag = in->randomTwice;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[2] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[3] = value;
        }
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        target = (float*)(base + *ctx->outputOffset + 0x80);
    }

    s32 color_offset = in->sourceOffset;
    u8* target_colors = (color_offset == -1) ? gPppDefaultValueBuffer : (base + color_offset + 0x80);

    {
        s8 deltaBase = in->delta[0];
        s32 delta = (s32)((f32)deltaBase * target[0] - (f32)deltaBase);
        target_colors[0] = (u8)(target_colors[0] + delta);
    }

    {
        s8 deltaBase = in->delta[1];
        s32 delta = (s32)((f32)deltaBase * target[1] - (f32)deltaBase);
        target_colors[1] = (u8)(target_colors[1] + delta);
    }

    {
        s8 deltaBase = in->delta[2];
        s32 delta = (s32)((f32)deltaBase * target[2] - (f32)deltaBase);
        target_colors[2] = (u8)(target_colors[2] + delta);
    }

    {
        s8 deltaBase = in->delta[3];
        s32 delta = (s32)((f32)deltaBase * target[3] - (f32)deltaBase);
        target_colors[3] = (u8)(target_colors[3] + delta);
    }
}
