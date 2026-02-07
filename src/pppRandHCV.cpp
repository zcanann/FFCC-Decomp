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

typedef union DoubleConv {
    struct {
        unsigned int hi;
        unsigned int lo;
    } parts;
    double d;
} DoubleConv;

typedef struct RandHCVConv {
    DoubleConv d0;
    DoubleConv c0;
    DoubleConv d1;
    DoubleConv c1;
    DoubleConv d2;
    DoubleConv c2;
    DoubleConv d3;
    DoubleConv c3;
} RandHCVConv;

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
    const double bias = lbl_8032FFA0;
    RandHCVConv conv;

    {
        s16 delta = params->delta[0];
        s16 current = target[0];
        conv.d0.parts.hi = 0x43300000;
        conv.d0.parts.lo = (unsigned int)((int)delta ^ 0x8000);
        conv.c0.parts.hi = 0x43300000;
        conv.c0.parts.lo = (unsigned int)((int)current ^ 0x8000);
        double value = conv.d0.d - bias;
        double baseValue = conv.c0.d - bias;
        double result = value * (double)scale - baseValue;
        int add = (int)result;
        target[0] = (s16)(current + add);
    }

    {
        s16 delta = params->delta[1];
        s16 current = target[1];
        conv.d1.parts.hi = 0x43300000;
        conv.d1.parts.lo = (unsigned int)((int)delta ^ 0x8000);
        conv.c1.parts.hi = 0x43300000;
        conv.c1.parts.lo = (unsigned int)((int)current ^ 0x8000);
        double value = conv.d1.d - bias;
        double baseValue = conv.c1.d - bias;
        double result = value * (double)scale - baseValue;
        int add = (int)result;
        target[1] = (s16)(current + add);
    }

    {
        s16 delta = params->delta[2];
        s16 current = target[2];
        conv.d2.parts.hi = 0x43300000;
        conv.d2.parts.lo = (unsigned int)((int)delta ^ 0x8000);
        conv.c2.parts.hi = 0x43300000;
        conv.c2.parts.lo = (unsigned int)((int)current ^ 0x8000);
        double value = conv.d2.d - bias;
        double baseValue = conv.c2.d - bias;
        double result = value * (double)scale - baseValue;
        int add = (int)result;
        target[2] = (s16)(current + add);
    }

    {
        s16 delta = params->delta[3];
        s16 current = target[3];
        conv.d3.parts.hi = 0x43300000;
        conv.d3.parts.lo = (unsigned int)((int)delta ^ 0x8000);
        conv.c3.parts.hi = 0x43300000;
        conv.c3.parts.lo = (unsigned int)((int)current ^ 0x8000);
        double value = conv.d3.d - bias;
        double baseValue = conv.c3.d - bias;
        double result = value * (double)scale - baseValue;
        int add = (int)result;
        target[3] = (s16)(current + add);
    }
}

}
