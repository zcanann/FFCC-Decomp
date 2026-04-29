#include "ffcc/pppSRandUpFV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct PppSRandUpFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

static inline float randf(unsigned char flag)
{
    float value = Math.RandF();
    if (flag != 0) {
        float random = Math.RandF();
        float blend = value + random;
        float scale = 0.5f;
        value = blend * scale;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpFV(_pppPObject* basePtr, PppSRandUpFVParam2* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 currentIndex = *(s32*)((u8*)basePtr + 0xC);
    f32* randVec;
    if (currentIndex == 0) {
        randVec = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);

        {
            u8 flag = in->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value + random;
                f32 scale = 0.5f;
                value = blend * scale;
            }
            randVec[0] = value;
        }

        {
            u8 flag = in->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value + random;
                f32 scale = 0.5f;
                value = blend * scale;
            }
            randVec[1] = value;
        }

        {
            u8 flag = in->field18;
            f32 value = Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value + random;
                f32 scale = 0.5f;
                value = blend * scale;
            }
            randVec[2] = value;
        }
    } else {
        if (in->field0 != currentIndex) {
            return;
        }
        randVec = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    f32* target = (in->field4 == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)((u8*)basePtr + in->field4 + 0x80);

    {
        f32 value = in->field8 * randVec[0];
        target[0] = target[0] + value;
    }
    {
        f32 value = in->fieldC * randVec[1];
        target[1] = target[1] + value;
    }
    {
        f32 value = in->field10 * randVec[2];
        target[2] = target[2] + value;
    }
}
