#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath Math;
extern int gPppCalcDisabled;
extern float lbl_80330060;
extern u8 gPppDefaultValueBuffer[];
extern "C" float RandF__5CMathFv(CMath* instance);

struct PppSRandCVParam2 {
    s32 field0;
    s32 field4;
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 fieldC;
};

struct PppSRandCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppSRandCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppSRandCVParam2* in = (PppSRandCVParam2*)param2;
    PppSRandCVParam3* out = (PppSRandCVParam3*)param3;
    u8* targetColor;

    if (gPppCalcDisabled != 0) {
        return;
    }

    float* target;

    if (in->field0 == *(s32*)(base + 0xC)) {
        target = (float*)(base + *out->fieldC + 0x80);

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330060;
            }
            target[0] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330060;
            }
            target[1] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330060;
            }
            target[2] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                value = value + RandF__5CMathFv(&Math);
            } else {
                value = value * lbl_80330060;
            }
            target[3] = value;
        }
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        target = (float*)(base + *out->fieldC + 0x80);
    }

    s32 colorOffset = in->field4;
    u8* colorPtr;
    if (colorOffset == -1) {
        colorPtr = gPppDefaultValueBuffer;
    } else {
        colorPtr = (u8*)(base + colorOffset + 0x80);
    }
    targetColor = colorPtr;

    s8 baseValue = in->field8;
    targetColor[0] = (u8)(targetColor[0] + (s8)((float)baseValue * target[0] - (float)baseValue));

    baseValue = in->field9;
    targetColor[1] = (u8)(targetColor[1] + (s8)((float)baseValue * target[1] - (float)baseValue));

    baseValue = in->fieldA;
    targetColor[2] = (u8)(targetColor[2] + (s8)((float)baseValue * target[2] - (float)baseValue));

    baseValue = in->fieldB;
    targetColor[3] = (u8)(targetColor[3] + (s8)((float)baseValue * target[3] - (float)baseValue));
}
