#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandCVSingleSampleScale = 2.0f;

typedef struct RandCVParams {
    s32 index;
    s32 colorOffset;
    s8 delta[4];
    u8 flag;
    u8 pad[3];
} RandCVParams;

typedef struct RandCVCtx {
    u8 pad[0xC];
    s32* outputOffset;
} RandCVCtx;

/*
 * --INFO--
 * PAL Address: 0x8006103C
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    RandCVParams* params = (RandCVParams*)param2;
    RandCVCtx* ctx = (RandCVCtx*)param3;
    f32* target;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (params->index == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (params->flag != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandCVSingleSampleScale;
        }

        target = (f32*)(base + *ctx->outputOffset + 0x80);
        target[0] = value;
    } else if (params->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        target = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s32 colorOffset = params->colorOffset;
    u8* targetColor = (colorOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + colorOffset + 0x80);

    {
        f32 scale = target[0];

        {
            s8 baseValue = params->delta[0];
            targetColor[0] = (u8)(targetColor[0] + (s32)((f32)baseValue * scale - (f32)baseValue));
        }
        {
            s8 baseValue = params->delta[1];
            targetColor[1] = (u8)(targetColor[1] + (s32)((f32)baseValue * scale - (f32)baseValue));
        }
        {
            s8 baseValue = params->delta[2];
            targetColor[2] = (u8)(targetColor[2] + (s32)((f32)baseValue * scale - (f32)baseValue));
        }
        {
            s8 baseValue = params->delta[3];
            targetColor[3] = (u8)(targetColor[3] + (s32)((f32)baseValue * scale - (f32)baseValue));
        }
    }
}
