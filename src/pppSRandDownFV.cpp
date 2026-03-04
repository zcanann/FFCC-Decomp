#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_80330080;
extern f32 lbl_801EADC8[];

extern "C" f32 RandF__5CMathFv(CMath*);

struct PppSRandDownFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

struct PppSRandDownFVParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80063840
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownFV(void* param1, void* param2, void* param3)
{
    u8* self = (u8*)param1;
    PppSRandDownFVParam2* cfg = (PppSRandDownFVParam2*)param2;
    PppSRandDownFVParam3* info = (PppSRandDownFVParam3*)param3;
    f32* randVec;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 currentIndex = *(s32*)(self + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)(self + *info->fieldC + 0x80);

        {
            u8 flag = cfg->field18;
            f32 value = -RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value - RandF__5CMathFv(math)) * lbl_80330080;
            }
            randVec[0] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = -RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value - RandF__5CMathFv(math)) * lbl_80330080;
            }
            randVec[1] = value;
        }

        {
            u8 flag = cfg->field18;
            f32 value = -RandF__5CMathFv(math);
            if (flag != 0) {
                value = (value - RandF__5CMathFv(math)) * lbl_80330080;
            }
            randVec[2] = value;
        }
    } else {
        if (cfg->field0 != currentIndex) {
            return;
        }
        randVec = (f32*)(self + *info->fieldC + 0x80);
    }

    f32* target = (cfg->field4 == -1) ? lbl_801EADC8 : (f32*)(self + cfg->field4 + 0x80);

    {
        f32 value = randVec[0] * cfg->field8;
        target[0] = target[0] + value;
    }
    {
        f32 value = randVec[1] * cfg->fieldC;
        target[1] = target[1] + value;
    }
    {
        f32 value = randVec[2] * cfg->field10;
        target[2] = target[2] + value;
    }
}
