#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

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
 * PAL Address: 0x80066194
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
    f32* randomValue;
    u8* targetColor;

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
        randomValue = (f32*)(base + *ctx->outputOffset + 0x80);
        *randomValue = value;
    } else if (params->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        randomValue = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s32 colorOffset = params->colorOffset;
    if (colorOffset == -1) {
        targetColor = &gPppDefaultValueBuffer[0];
    } else {
        targetColor = base + colorOffset + 0x80;
    }

    f32 scale = *randomValue;
    targetColor[0] = (u8)(targetColor[0] + (s8)((f32)params->delta[0] * scale - (f32)params->delta[0]));
    targetColor[1] = (u8)(targetColor[1] + (s8)((f32)params->delta[1] * scale - (f32)params->delta[1]));
    targetColor[2] = (u8)(targetColor[2] + (s8)((f32)params->delta[2] * scale - (f32)params->delta[2]));
    targetColor[3] = (u8)(targetColor[3] + (s8)((f32)params->delta[3] * scale - (f32)params->delta[3]));
}
