#include "ffcc/pppRandDownChar.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
extern CMath Math;
extern int gPppCalcDisabled;
extern u8 gPppDefaultValueBuffer[];

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandDownCharParam2 {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 field9;
};

struct PppRandDownCharParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 80061258
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownChar(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandDownCharParam2* in = (PppRandDownCharParam2*)param2;
    PppRandDownCharParam3* out = (PppRandDownCharParam3*)param3;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -RandF__5CMathFv(&Math);
        if (in->field9 != 0) {
            f32 mixed = value - RandF__5CMathFv(&Math);
            value = mixed * kPppRandDownCharDualSampleScale;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    u8* target = (in->field4 == -1) ? gPppDefaultValueBuffer : (u8*)(base + in->field4 + 0x80);

    f32 factor = (f32)in->field8;
    f32 scaled = factor * *valuePtr;
    s32 delta = (s32)scaled;
    *target = (u8)(*target + delta);
}
