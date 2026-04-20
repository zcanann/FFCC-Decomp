#include "ffcc/pppSRandFV.h"
#include "ffcc/math.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "dolphin/types.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppSRandFVSingleSampleScale = 2.0f;
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
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 _pad14[0x18 - 0x14];
    u8 field18;
};

struct PppSRandFVParam3 {
    u8 _pad0[0xC];
    s32* fieldC;
};

void pppSRandFV(void* param1, void* param2, void* param3)
{
    PppSRandFVParam2* cfg = (PppSRandFVParam2*)param1;
    u8* self = (u8*)param2;
    PppSRandFVParam3* info = (PppSRandFVParam3*)param3;
    f32* randVec;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 currentIndex = *(s32*)(self + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)(self + *info->fieldC + 0x80);
        {
            u8 flag = cfg->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                f32 scale = kPppSRandFVSingleSampleScale;
                value = value * scale;
            }
            randVec[0] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                f32 scale = kPppSRandFVSingleSampleScale;
                value = value * scale;
            }
            randVec[1] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                f32 scale = kPppSRandFVSingleSampleScale;
                value = value * scale;
            }
            randVec[2] = value;
        }
    } else {
        if (cfg->field0 != currentIndex) {
            return;
        }
        randVec = (f32*)(self + *info->fieldC + 0x80);
    }

    f32* target = (cfg->field4 == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(self + cfg->field4 + 0x80);

    {
        f32 value = cfg->field8 * randVec[0] - cfg->field8;
        target[0] = target[0] + value;
    }
    {
        f32 value = cfg->fieldC * randVec[1] - cfg->fieldC;
        target[1] = target[1] + value;
    }
    {
        f32 value = cfg->field10 * randVec[2] - cfg->field10;
        target[2] = target[2] + value;
    }
}
