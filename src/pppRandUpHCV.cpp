#include "ffcc/pppRandUpHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandUpHCVDualSampleScale = 0.5f;
extern s16 gPppDefaultValueBuffer[];
static f64 const sPppRandUpHCVConvertBias = 4503601774854144.0;

typedef struct RandUpHCVParams {
    int index;
    int colorOffset;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 flag;
    u8 pad[3];
} RandUpHCVParams;

typedef struct RandUpHCVCtx {
    u8 _pad0[0xC];
    s32* outputOffset;
} RandUpHCVCtx;

/*
 * --INFO--
 * PAL Address: 80062B18
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpHCV(void* p1, void* p2, void* p3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)p1;
    RandUpHCVParams* params = (RandUpHCVParams*)p2;
    RandUpHCVCtx* ctx = (RandUpHCVCtx*)p3;
    f32* valuePtr;
    if (params->index == *(int*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (params->flag != 0) {
            f32 random = Math.RandF();
            f32 blend = value + random;
            f32 scale = kPppRandUpHCVDualSampleScale;
            value = blend * scale;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else if (params->index != *(int*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s16* target = (params->colorOffset == -1) ? &gPppDefaultValueBuffer[0] : (s16*)(base + params->colorOffset + 0x80);

    s32 delta = (s32)((f32)params->field8 * *valuePtr);
    target[0] = (s16)(target[0] + delta);

    delta = (s32)((f32)params->fieldA * *valuePtr);
    target[1] = (s16)(target[1] + delta);

    delta = (s32)((f32)params->fieldC * *valuePtr);
    target[2] = (s16)(target[2] + delta);

    delta = (s32)((f32)params->fieldE * *valuePtr);
    target[3] = (s16)(target[3] + delta);
}
