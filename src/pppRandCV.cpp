#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandCVSingleSampleScale = 2.0f;

typedef struct RandCVParams {
    s32 field0;
    s32 field4;
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 fieldC;
    u8 pad[3];
} RandCVParams;

typedef struct RandCVCtx {
    u8 field0[0xC];
    s32* fieldC;
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
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (params->field0 == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (params->fieldC != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandCVSingleSampleScale;
        }

        valuePtr = (f32*)(base + *ctx->fieldC + 0x80);
        *valuePtr = value;
    } else if (params->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *ctx->fieldC + 0x80);
    }

    target = (params->field4 == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + params->field4 + 0x80);

    f32 scale = *valuePtr;
    {
        u8 color = target[0];
        target[0] = color + (s8)((f32)params->field8 * scale - (f32)params->field8);
    }
    {
        u8 color = target[1];
        target[1] = color + (s8)((f32)params->field9 * scale - (f32)params->field9);
    }
    {
        u8 color = target[2];
        target[2] = color + (s8)((f32)params->fieldA * scale - (f32)params->fieldA);
    }
    {
        u8 color = target[3];
        target[3] = color + (s8)((f32)params->fieldB * scale - (f32)params->fieldB);
    }
}
