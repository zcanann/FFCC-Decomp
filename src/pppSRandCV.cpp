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
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        target = (float*)(base + *out->fieldC + 0x80);
    }

    s32 colorOffset = in->field4;
    u8* target_colors = (colorOffset == -1) ? gPppDefaultValueBuffer : (u8*)(base + colorOffset + 0x80);

    {
        s8 deltaBase = in->field8;
        s32 delta = (s32)((f32)deltaBase * target[0] - (f32)deltaBase);
        target_colors[0] = (u8)(target_colors[0] + delta);
    }

    {
        s8 deltaBase = in->field9;
        s32 delta = (s32)((f32)deltaBase * target[1] - (f32)deltaBase);
        target_colors[1] = (u8)(target_colors[1] + delta);
    }

    {
        s8 deltaBase = in->fieldA;
        s32 delta = (s32)((f32)deltaBase * target[2] - (f32)deltaBase);
        target_colors[2] = (u8)(target_colors[2] + delta);
    }

    {
        s8 deltaBase = in->fieldB;
        s32 delta = (s32)((f32)deltaBase * target[3] - (f32)deltaBase);
        target_colors[3] = (u8)(target_colors[3] + delta);
    }
}
