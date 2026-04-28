#include "ffcc/pppSRandFV.h"
#include "ffcc/partMng.h"
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

void pppSRandFV(void* basePtr, PppSRandFVParam2* in, _pppCtrlTable* ctrl)
{
    f32* randVec;
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 currentIndex = *(s32*)((u8*)basePtr + 0xC);
    if (currentIndex == 0) {
        randVec = (f32*)((u8*)basePtr + *ctrl->m_serializedDataOffsets + 0x80);
        {
            u8 flag = in->field18;
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
            u8 flag = in->field18;
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
            u8 flag = in->field18;
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
        if (in->field0 != currentIndex) {
            return;
        }
        randVec = (f32*)((u8*)basePtr + *ctrl->m_serializedDataOffsets + 0x80);
    }

    f32* target = (in->field4 == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)((u8*)basePtr + in->field4 + 0x80);

    {
        f32 value = in->field8 * randVec[0] - in->field8;
        target[0] = target[0] + value;
    }
    {
        f32 value = in->fieldC * randVec[1] - in->fieldC;
        target[1] = target[1] + value;
    }
    {
        f32 value = in->field10 * randVec[2] - in->field10;
        target[2] = target[2] + value;
    }
}
