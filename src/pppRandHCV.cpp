#include "ffcc/pppRandHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
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
    RandHCVParams* params = (RandHCVParams*)p2;
    int id = *(int*)((char*)p1 + 0xc);
    int* baseIndex;
    int baseOffset;
    float* scalePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (params->index == id) {
        float randValue = RandF__5CMathFv(&math);
        if (params->flag != 0) {
            randValue = randValue + RandF__5CMathFv(&math);
        } else {
            randValue = randValue * lbl_8032FF98;
        }

        baseIndex = *(int**)((char*)p3 + 0xc);
        baseOffset = *baseIndex;
        scalePtr = (float*)((char*)p1 + baseOffset + 0x80);
        *scalePtr = randValue;
    }

    if (params->index != id) {
        return;
    }

    baseIndex = *(int**)((char*)p3 + 0xc);
    baseOffset = *baseIndex;
    scalePtr = (float*)((char*)p1 + baseOffset + 0x80);

    s16* target;
    if (params->colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (s16*)((char*)p1 + params->colorOffset + 0x80);
    }

    float scale = *scalePtr;

    {
        s16 current = target[0];
        s16 base = params->delta[0];
        target[0] = (s16)(current + (int)((float)base * scale - (float)current));
    }

    {
        s16 current = target[1];
        s16 base = params->delta[1];
        target[1] = (s16)(current + (int)((float)base * scale - (float)current));
    }

    {
        s16 current = target[2];
        s16 base = params->delta[2];
        target[2] = (s16)(current + (int)((float)base * scale - (float)current));
    }

    {
        s16 current = target[3];
        s16 base = params->delta[3];
        target[3] = (s16)(current + (int)((float)base * scale - (float)current));
    }
}

}
