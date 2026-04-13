#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppSRandDownFVDualSampleScale = 0.5f;
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
    u8* base = (u8*)param1;
    PppSRandDownFVParam2* in = (PppSRandDownFVParam2*)param2;
    PppSRandDownFVParam3* out = (PppSRandDownFVParam3*)param3;

    if (gPppCalcDisabled != 0) {
        return;
    }

    f32* target;
    if (*(s32*)(base + 0xC) == 0) {
        target = (f32*)(base + *out->fieldC + 0x80);

        {
            u8 flag = in->field18;
            f32 value = -Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value - random;
                f32 scale = kPppSRandDownFVDualSampleScale;
                value = blend * scale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->field18;
            f32 value = -Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value - random;
                f32 scale = kPppSRandDownFVDualSampleScale;
                value = blend * scale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->field18;
            f32 value = -Math.RandF();
            if (flag != 0) {
                f32 random = Math.RandF();
                f32 blend = value - random;
                f32 scale = kPppSRandDownFVDualSampleScale;
                value = blend * scale;
            }
            target[2] = value;
        }
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        target = (f32*)(base + *out->fieldC + 0x80);
    }

    s32 valueOffset = in->field4;
    f32* valueBuffer = (valueOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + valueOffset + 0x80);

    {
        f32 value = in->field8 * target[0];
        valueBuffer[0] = valueBuffer[0] + value;
    }
    {
        f32 value = in->fieldC * target[1];
        valueBuffer[1] = valueBuffer[1] + value;
    }
    {
        f32 value = in->field10 * target[2];
        valueBuffer[2] = valueBuffer[2] + value;
    }
}
