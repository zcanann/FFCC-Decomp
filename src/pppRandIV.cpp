#include "ffcc/pppRandIV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandIVSingleSampleScale = 2.0f;
extern s32 gPppDefaultValueBuffer[];


struct PppRandIVParam2 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    u8 field14[4];
    u8 field18;
};

struct PppRandIVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x800622d4
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandIV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandIVParam2* in = (PppRandIVParam2*)param2;
    PppRandIVParam3* out = (PppRandIVParam3*)param3;
    s32* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->field18 != 0) {
            value += Math.RandF();
        } else {
            value *= kPppRandIVSingleSampleScale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }
    
    target = (in->field4 == -1) ? &gPppDefaultValueBuffer[0] : (s32*)(base + in->field4 + 0x80);

    {
        f32 randValue = *valuePtr;
        target[0] += (s32)((f32)in->field8 * randValue - (f32)in->field8);
        target[1] += (s32)((f32)in->fieldC * randValue - (f32)in->fieldC);
        target[2] += (s32)((f32)in->field10 * randValue - (f32)in->field10);
    }
}
