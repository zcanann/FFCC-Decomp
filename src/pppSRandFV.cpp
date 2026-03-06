#include "ffcc/pppSRandFV.h"
#include "ffcc/math.h"

extern CMath Math;
extern int gPppCalcDisabled;
extern float lbl_80330098;
extern float gPppDefaultValueBuffer[];
extern "C" float RandF__5CMathFv(CMath*);

void randfloat(float, float);
void randf(unsigned char);

/*
 * --INFO--
 * PAL Address: 0x80063c7c
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct PppSRandFVParam2 {
    int field0;
    int field4;
    float field8;
    float fieldC;
    float field10;
    unsigned char _pad14[0x18 - 0x14];
    unsigned char field18;
};

struct PppSRandFVParam3 {
    unsigned char _pad0[0xC];
    int* fieldC;
};

void pppSRandFV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    unsigned char* base = (unsigned char*)param1;
    PppSRandFVParam2* in = (PppSRandFVParam2*)param2;
    float* valuePtr;

    int state = *(int*)(base + 0xC);
    if (state == 0) {
        valuePtr = (float*)(base + ((PppSRandFVParam3*)param3)->fieldC[0] + 0x80);

        {
            unsigned char flag = in->field18;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330098;
            }
            valuePtr[0] = value;
        }

        {
            unsigned char flag = in->field18;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330098;
            }
            valuePtr[1] = value;
        }

        {
            unsigned char flag = in->field18;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330098;
            }
            valuePtr[2] = value;
        }
    } else {
        if (in->field0 != state) {
            return;
        }
        valuePtr = (float*)(base + ((PppSRandFVParam3*)param3)->fieldC[0] + 0x80);
    }

    float* target = (in->field4 == -1) ? &gPppDefaultValueBuffer[0] : (float*)(base + in->field4 + 0x80);

    {
        float value = in->field8 * valuePtr[0] - in->field8;
        target[0] = target[0] + value;
    }
    {
        float value = in->fieldC * valuePtr[1] - in->fieldC;
        target[1] = target[1] + value;
    }
    {
        float value = in->field10 * valuePtr[2] - in->field10;
        target[2] = target[2] + value;
    }
}
