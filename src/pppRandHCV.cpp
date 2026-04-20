#include "ffcc/pppRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandHCVSingleSampleScale = 2.0f;
typedef struct RandHCVParams {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
} RandHCVParams;

typedef struct RandHCVCtx {
    u8 field0[0xC];
    s32* fieldC;
} RandHCVCtx;

/*
 * --INFO--
 * PAL Address: 80061f88
 * PAL Size: 524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

extern "C" {

void pppRandHCV(void* p1, void* p2, void* p3)
{
    u8* base = (u8*)p1;
    RandHCVParams* params = (RandHCVParams*)p2;
    RandHCVCtx* ctx = (RandHCVCtx*)p3;
    s16* target;
    f32* randomValue;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (params->field0 == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (params->field10 != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandHCVSingleSampleScale;
        }

        randomValue = (f32*)(base + *ctx->fieldC + 0x80);
        *randomValue = value;
    } else if (params->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        randomValue = (f32*)(base + *ctx->fieldC + 0x80);
    }

    target = (params->field4 == -1) ? (s16*)gPppDefaultValueBuffer : (s16*)(base + params->field4 + 0x80);

    {
        f32 scale = *randomValue;
        target[0] += (s16)((f32)params->field8 * scale - (f32)params->field8);
        target[1] += (s16)((f32)params->fieldA * scale - (f32)params->fieldA);
        target[2] += (s16)((f32)params->fieldC * scale - (f32)params->fieldC);
        target[3] += (s16)((f32)params->fieldE * scale - (f32)params->fieldE);
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
static short randshort(short value, float scale)
{
    return (short)(((f32)value * scale) - (f32)value);
}
