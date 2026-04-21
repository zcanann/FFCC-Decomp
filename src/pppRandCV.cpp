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
    f32* valuePtr;

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

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else if (params->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    u8* targetColor;
    s32 colorOffset = params->colorOffset;
    if (colorOffset == -1) {
        targetColor = gPppDefaultValueBuffer;
    } else {
        targetColor = base + colorOffset + 0x80;
    }

    {
        f32 scale = *valuePtr;

        {
            u8 color = targetColor[0];
            targetColor[0] = color + (s8)((f32)params->delta[0] * scale - (f32)params->delta[0]);
        }
        {
            u8 color = targetColor[1];
            targetColor[1] = color + (s8)((f32)params->delta[1] * scale - (f32)params->delta[1]);
        }
        {
            u8 color = targetColor[2];
            targetColor[2] = color + (s8)((f32)params->delta[2] * scale - (f32)params->delta[2]);
        }
        {
            u8 color = targetColor[3];
            targetColor[3] = color + (s8)((f32)params->delta[3] * scale - (f32)params->delta[3]);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static char randchar(char value, float scale)
{
    return (char)(((f32)value * scale) - (f32)value);
}
