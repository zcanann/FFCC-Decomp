#include "ffcc/pppRandDownIV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
extern s32 gPppDefaultValueBuffer[];


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
            value = randValue * kPppRandDownIVDualSampleScale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? &gPppDefaultValueBuffer[0] : (s32*)(base + in->field4 + 0x80);

    {
        f32 factor = (f32)in->field8;
        f32 scaled = factor * *valuePtr;
        s32 delta = (s32)scaled;
        target[0] += delta;
    }

    {
        f32 factor = (f32)in->fieldC;
        f32 scaled = factor * *valuePtr;
        s32 delta = (s32)scaled;
        target[1] += delta;
    }

    {
        f32 factor = (f32)in->field10;
        f32 scaled = factor * *valuePtr;
        s32 delta = (s32)scaled;
        target[2] += delta;
    }
}
