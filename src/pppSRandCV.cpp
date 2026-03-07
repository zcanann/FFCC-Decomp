#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

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
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[2] = value;
        }

        {
            u8 flag = in->fieldC;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                value = value * kPppSRandCVSingleSampleScale;
            }
            target[3] = value;
        }
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        target = (float*)(base + *out->fieldC + 0x80);
    }

    s32 colorOffset = in->field4;
    targetColor = (colorOffset == -1) ? &gPppDefaultValueBuffer[0] : (base + colorOffset + 0x80);

    targetColor[0] = (u8)(targetColor[0] + (s8)((float)in->field8 * target[0] - (float)in->field8));
    targetColor[1] = (u8)(targetColor[1] + (s8)((float)in->field9 * target[1] - (float)in->field9));
    targetColor[2] = (u8)(targetColor[2] + (s8)((float)in->fieldA * target[2] - (float)in->fieldA));
    targetColor[3] = (u8)(targetColor[3] + (s8)((float)in->fieldB * target[3] - (float)in->fieldB));
}

