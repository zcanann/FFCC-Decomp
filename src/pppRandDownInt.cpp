#include "ffcc/pppRandDownInt.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"

const float kPppRandDownIntDualSampleScale = 0.5f;
extern s32 gPppDefaultValueBuffer[];


struct PppRandDownIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
};

struct PppRandDownIntParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80066ab4
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownInt(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandDownIntParam2* in = (PppRandDownIntParam2*)param2;
    PppRandDownIntParam3* out = (PppRandDownIntParam3*)param3;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -Math.RandF();
        if (in->fieldC != 0) {
            f32 mixed = value - Math.RandF();
            f32 scale = kPppRandDownIntDualSampleScale;
            value = mixed * scale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? gPppDefaultValueBuffer : (s32*)(base + in->field4 + 0x80);

    f32 factor = (f32)in->field8;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    *target += delta;
}
