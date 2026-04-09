#include "ffcc/pppRandDownIV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandDownIVDualSampleScale = 0.5f;
struct PppRandDownIVParam2 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    u8 field14[4];
    u8 field18;
};

struct PppRandDownIVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownIV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandDownIVParam2* in = (PppRandDownIVParam2*)param2;
    PppRandDownIVParam3* out = (PppRandDownIVParam3*)param3;
    f32 value;
    f32* valuePtr;

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = -Math.RandF();
        if (in->field18 != 0) {
            f32 randValue = value - Math.RandF();
            f32 scale = kPppRandDownIVDualSampleScale;
            value = randValue * scale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);
    f32 scale = *valuePtr;

    target[0] += (s32)(scale * (f32)in->field8);
    target[1] += (s32)(scale * (f32)in->fieldC);
    target[2] += (s32)(scale * (f32)in->field10);
}
