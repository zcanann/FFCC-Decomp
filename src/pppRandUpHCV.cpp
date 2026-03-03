#include "ffcc/pppRandUpHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
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
    u8* base = (u8*)p1;
    if (lbl_8032ED70 != 0) {
        return;
    }

    RandUpHCVParams* params = (RandUpHCVParams*)p2;
    if (params->index == *(int*)(base + 0xC)) {
        f32 randValue = RandF__5CMathFv(&math);
        if (params->flag != 0) {
            randValue = (randValue + RandF__5CMathFv(&math)) * lbl_80330008;
        }

        s32 outputOffset = **(s32**)((u8*)p3 + 0xC) + 0x80;
        *(f32*)(base + outputOffset) = randValue;
    } else if (params->index != *(int*)(base + 0xC)) {
        return;
    }

    s32 outputOffset = **(s32**)((u8*)p3 + 0xC) + 0x80;
    s32 color_offset = params->colorOffset;
    s16* target;

    if (color_offset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)(base + color_offset + 0x80);
    }

    f32 scale = *(f32*)(base + outputOffset);

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
