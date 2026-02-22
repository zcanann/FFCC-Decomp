#include "ffcc/pppRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_8032FF98;
extern double lbl_8032FFA0;
extern s16 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct RandHCVParams {
    int index;
    int colorOffset;
    s16 delta[4];
    u8 flag;
    u8 pad[3];
} RandHCVParams;

typedef struct RandHCVCtx {
    u8 pad[0xC];
    int* outputOffset;
} RandHCVCtx;

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randshort(short value, float factor) {
    float converted = (float)value;
    float scaled = converted * factor;
    (void)scaled;
}

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

void pppRandHCV(void* p1, void* p2, void* p3) {
    u8* base = (u8*)p1;
    RandHCVParams* params = (RandHCVParams*)p2;
    RandHCVCtx* ctx = (RandHCVCtx*)p3;
    int outputOffset;
    float* randomValue;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->index == *(int*)(base + 0xC)) {
        float value = RandF__5CMathFv(math);
        if (params->flag != 0) {
            value += RandF__5CMathFv(math);
        } else {
            value *= lbl_8032FF98;
        }

        outputOffset = *ctx->outputOffset;
        randomValue = (float*)(base + outputOffset + 0x80);
        *randomValue = value;
    } else if (params->index != *(int*)(base + 0xC)) {
        return;
    }

    outputOffset = *ctx->outputOffset;
    randomValue = (float*)(base + outputOffset + 0x80);

    s16* target;
    if (params->colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)(base + params->colorOffset + 0x80);
    }

    float scale = *randomValue;

    {
        s16 delta = params->delta[0];
        s16 current = target[0];
        target[0] = (s16)(current + (int)((float)delta * scale - (float)delta));
    }

    {
        s16 delta = params->delta[1];
        s16 current = target[1];
        target[1] = (s16)(current + (int)((float)delta * scale - (float)delta));
    }

    {
        s16 delta = params->delta[2];
        s16 current = target[2];
        target[2] = (s16)(current + (int)((float)delta * scale - (float)delta));
    }

    {
        s16 delta = params->delta[3];
        s16 current = target[3];
        target[3] = (s16)(current + (int)((float)delta * scale - (float)delta));
    }
}

}
