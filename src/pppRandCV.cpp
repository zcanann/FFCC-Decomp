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
    RandCVParams* in = (RandCVParams*)param2;
    RandCVCtx* out = (RandCVCtx*)param3;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->index == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->flag != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandCVSingleSampleScale;
        }

        valuePtr = (f32*)(base + *out->outputOffset + 0x80);
        *valuePtr = value;
    } else if (in->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *out->outputOffset + 0x80);
    }

    target = (in->colorOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + in->colorOffset + 0x80);

    f32 scale = *valuePtr;
    {
        s8 baseValue = in->delta[0];
        target[0] = (u8)(target[0] + (s32)((f32)baseValue * scale - (f32)baseValue));
    }
    {
        s8 baseValue = in->delta[1];
        target[1] = (u8)(target[1] + (s32)((f32)baseValue * scale - (f32)baseValue));
    }
    {
        s8 baseValue = in->delta[2];
        target[2] = (u8)(target[2] + (s32)((f32)baseValue * scale - (f32)baseValue));
    }
    {
        s8 baseValue = in->delta[3];
        target[3] = (u8)(target[3] + (s32)((f32)baseValue * scale - (f32)baseValue));
    }
}
