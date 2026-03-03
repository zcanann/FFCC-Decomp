#include "ffcc/pppRandUpHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_80330008;
extern s16 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

typedef struct RandUpHCVParams {
    int index;
    int colorOffset;
    s16 delta[4];
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
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)p1;
    RandUpHCVParams* params = (RandUpHCVParams*)p2;
    RandUpHCVCtx* ctx = (RandUpHCVCtx*)p3;
    f32* valuePtr;
    if (params->index == *(int*)(base + 0xC)) {
        f32 value = RandF__5CMathFv(math);
        if (params->flag != 0) {
            value = (value + RandF__5CMathFv(math)) * lbl_80330008;
        }

        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
        *valuePtr = value;
    } else {
        if (params->index != *(int*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(base + *ctx->outputOffset + 0x80);
    }

    s16* target;
    s32 colorOffset = params->colorOffset;
    if (colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)(base + colorOffset + 0x80);
    }

    f32 scale = *valuePtr;

    {
        s16 base = params->delta[0];
        target[0] = (s16)(target[0] + (int)((float)base * scale));
    }
    {
        s16 base = params->delta[1];
        target[1] = (s16)(target[1] + (int)((float)base * scale));
    }
    {
        s16 base = params->delta[2];
        target[2] = (s16)(target[2] + (int)((float)base * scale));
    }
    {
        s16 base = params->delta[3];
        target[3] = (s16)(target[3] + (int)((float)base * scale));
    }
}
