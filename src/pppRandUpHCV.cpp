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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randshort(short value, float factor)
{
    float scaled = (float)value * factor;
    (void)scaled;
}

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
    RandUpHCVParams* params = (RandUpHCVParams*)p2;
    int id = *(int*)((char*)p1 + 0xC);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->index == id) {
        float randValue = RandF__5CMathFv(&math);
        if (params->flag != 0) {
            randValue = (randValue + RandF__5CMathFv(&math)) * lbl_80330008;
        }

        int dataOffset = **(int**)((char*)p3 + 0xC);
        *(float*)((char*)p1 + dataOffset + 0x80) = randValue;
    }

    if (params->index != id) {
        return;
    }

    int dataOffset = **(int**)((char*)p3 + 0xC);
    float scale = *(float*)((char*)p1 + dataOffset + 0x80);

    s16* target;
    if (params->colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)((char*)p1 + params->colorOffset + 0x80);
    }

    {
        int add = (int)((double)params->delta[0] * (double)scale);
        target[0] = (s16)(target[0] + add);
    }
    {
        int add = (int)((double)params->delta[1] * (double)scale);
        target[1] = (s16)(target[1] + add);
    }
    {
        int add = (int)((double)params->delta[2] * (double)scale);
        target[2] = (s16)(target[2] + add);
    }
    {
        int add = (int)((double)params->delta[3] * (double)scale);
        target[3] = (s16)(target[3] + add);
    }
}
