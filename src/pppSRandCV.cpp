#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct SRandCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
    u8 _pad[3];
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

    f32* target;

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (f32*)(base + *ctx->outputOffset + 0x80);

        {
            u8 flag = in->randomTwice;
            f32 value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[2] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[3] = value;
        }
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        target = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    u8* target_colors =
        (in->sourceOffset == -1) ? gPppDefaultValueBuffer : (u8*)(base + in->sourceOffset + 0x80);

    target_colors[0] += (s8)((f32)in->delta[0] * target[0] - (f32)in->delta[0]);
    target_colors[1] += (s8)((f32)in->delta[1] * target[1] - (f32)in->delta[1]);
    target_colors[2] += (s8)((f32)in->delta[2] * target[2] - (f32)in->delta[2]);
    target_colors[3] += (s8)((f32)in->delta[3] * target[3] - (f32)in->delta[3]);
}
