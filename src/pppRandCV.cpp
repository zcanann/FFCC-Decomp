#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath Math;
extern int gPppCalcDisabled;
extern f32 lbl_8032FF08;
extern u8 gPppDefaultValueBuffer[];
extern "C" f32 RandF__5CMathFv(CMath* instance);

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

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (params->index == *(s32*)(base + 0xC)) {
        f32 value = RandF__5CMathFv(&Math);
        if (params->flag != 0) {
            value += RandF__5CMathFv(&Math);
        } else {
            value *= lbl_8032FF08;
        }
        randomValue = (f32*)(base + *ctx->outputOffset + 0x80);
        *randomValue = value;
    } else if (params->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        randomValue = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s32 colorOffset = params->colorOffset;
    u8* target = (colorOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + colorOffset + 0x80);
    f32 scale = *randomValue;

    {
        s8 baseValue = params->delta[0];
        s32 delta = (s32)((f32)baseValue * scale - (f32)baseValue);
        target[0] = (u8)(target[0] + delta);
    }

    {
        s8 baseValue = params->delta[1];
        s32 delta = (s32)((f32)baseValue * scale - (f32)baseValue);
        target[1] = (u8)(target[1] + delta);
    }

    {
        s8 baseValue = params->delta[2];
        s32 delta = (s32)((f32)baseValue * scale - (f32)baseValue);
        target[2] = (u8)(target[2] + delta);
    }

    {
        s8 baseValue = params->delta[3];
        s32 delta = (s32)((f32)baseValue * scale - (f32)baseValue);
        target[3] = (u8)(target[3] + delta);
    }
}
