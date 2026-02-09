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
    return;
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
    if (lbl_8032ED70 != 0) {
        return;
    }

    RandUpHCVParams* params = (RandUpHCVParams*)p2;
    if (params->index == *(int*)((char*)p1 + 0xC)) {
        float rand_value = RandF__5CMathFv(&math);
        if (params->flag != 0) {
            rand_value = (rand_value + RandF__5CMathFv(&math)) * lbl_80330008;
        }

        int data_offset = **(int**)((char*)p3 + 0xC);
        *(float*)((char*)p1 + data_offset + 0x80) = rand_value;
    } else if (params->index != *(int*)((char*)p1 + 0xC)) {
        return;
    }

    int data_offset = **(int**)((char*)p3 + 0xC);
    float* random_value = (float*)((char*)p1 + data_offset + 0x80);
    int color_offset = params->colorOffset;
    s16* target;

    if (color_offset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)((char*)p1 + color_offset + 0x80);
    }

    float scale = random_value[0];

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
