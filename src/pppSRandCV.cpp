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
    float* target;
    u8* targetColor;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (float*)(base + *ctx->outputOffset + 0x80);

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
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
    } else if (in->targetId != *(s32*)(base + 0xC)) {
        return;
    } else {
        target = (float*)(base + *ctx->outputOffset + 0x80);
    }

    s32 colorOffset = in->sourceOffset;
    if (colorOffset == -1) {
        targetColor = gPppDefaultValueBuffer;
    } else {
        targetColor = base + colorOffset + 0x80;
    }

    targetColor[0] = (u8)(targetColor[0] + (s8)((float)in->delta[0] * target[0] - (float)in->delta[0]));
    targetColor[1] = (u8)(targetColor[1] + (s8)((float)in->delta[1] * target[1] - (float)in->delta[1]));
    targetColor[2] = (u8)(targetColor[2] + (s8)((float)in->delta[2] * target[2] - (float)in->delta[2]));
    targetColor[3] = (u8)(targetColor[3] + (s8)((float)in->delta[3] * target[3] - (float)in->delta[3]));
}
