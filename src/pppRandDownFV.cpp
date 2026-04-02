#include "ffcc/pppRandDownFV.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

const float kPppRandDownFVDualSampleScale = 0.5f;
struct PppRandDownFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

struct PppRandDownFVParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80061664
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownFV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandDownFVParam3* out = (PppRandDownFVParam3*)param3;
    PppRandDownFVParam2* in = (PppRandDownFVParam2*)param2;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->field18 != 0) {
            f32 randomValue = value - Math.RandF();
            f32 scale = kPppRandDownFVDualSampleScale;
            value = randomValue * scale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32 sourceOffset = in->field4;
    f32* target = (sourceOffset == -1) ? (f32*)gPppDefaultValueBuffer : (f32*)(base + sourceOffset + 0x80);

    f32 base0 = target[0];
    f32 value = in->field8;
    f32 scale = *valuePtr;
    f32 delta0 = value * scale;
    target[0] = base0 + delta0;

    value = in->fieldC * scale;
    target[1] = target[1] + value;
    value = in->field10 * scale;
    target[2] = target[2] + value;
}
