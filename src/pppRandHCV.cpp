#include "ffcc/pppRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_8032FF98;
extern s16 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

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
    f32* randomValue;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->field0 == *(s32*)(base + 0xC)) {
        f32 value = RandF__5CMathFv(&math[0]);
        if (params->field10 != 0) {
            value += RandF__5CMathFv(&math[0]);
        } else {
            value *= lbl_8032FF98;
        }

        randomValue = (f32*)(base + *ctx->fieldC + 0x80);
        *randomValue = value;
    } else {
        if (params->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        randomValue = (f32*)(base + *ctx->fieldC + 0x80);
    }

    s16* target = (params->field4 == -1) ? lbl_801EADC8 : (s16*)(base + params->field4 + 0x80);

    {
        s32 delta;

        delta = (s32)((f32)params->field8 * *randomValue - (f32)params->field8);
        target[0] = (s16)(target[0] + delta);

        delta = (s32)((f32)params->fieldA * *randomValue - (f32)params->fieldA);
        target[1] = (s16)(target[1] + delta);

        delta = (s32)((f32)params->fieldC * *randomValue - (f32)params->fieldC);
        target[2] = (s16)(target[2] + delta);

        delta = (s32)((f32)params->fieldE * *randomValue - (f32)params->fieldE);
        target[3] = (s16)(target[3] + delta);
    }
}

}
