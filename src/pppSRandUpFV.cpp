#include "ffcc/pppSRandUpFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
extern f32 gPppDefaultValueBuffer[];
extern "C" f32 RandF__5CMathFv(CMath*);

struct PppSRandUpFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

struct PppSRandUpFVParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpFV(void* param1, void* param2, void* param3)
{
    u8* self = (u8*)param1;
    PppSRandUpFVParam2* cfg = (PppSRandUpFVParam2*)param2;
    PppSRandUpFVParam3* info = (PppSRandUpFVParam3*)param3;
    f32* randVec;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 currentIndex = *(s32*)(self + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)(self + *info->fieldC + 0x80);

        {
            u8 flag = cfg->field18;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpFVDualSampleScale;
            }
            randVec[0] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpFVDualSampleScale;
            }
            randVec[1] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = RandF__5CMathFv(&Math);
            if (flag != 0) {
                f32 randomPair = value + RandF__5CMathFv(&Math);
                value = randomPair * kPppSRandUpFVDualSampleScale;
            }
            randVec[2] = value;
        }
    } else {
        if (cfg->field0 != currentIndex) {
            return;
        }
        randVec = (f32*)(self + *info->fieldC + 0x80);
    }

    f32* target = (cfg->field4 == -1) ? gPppDefaultValueBuffer : (f32*)(self + cfg->field4 + 0x80);

    {
        f32 value = cfg->field8 * randVec[0];
        target[0] = target[0] + value;
    }
    {
        f32 value = cfg->fieldC * randVec[1];
        target[1] = target[1] + value;
    }
    {
        f32 value = cfg->field10 * randVec[2];
        target[2] = target[2] + value;
    }
}
