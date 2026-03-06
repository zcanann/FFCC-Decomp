#include "ffcc/pppRandInt.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/ppp_constants.h"
/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

extern CMath Math;
extern int gPppCalcDisabled;
extern s32 gPppDefaultValueBuffer[];

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
};

struct PppRandIntParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

void pppRandInt(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandIntParam2* in = (PppRandIntParam2*)param2;
    PppRandIntParam3* out = (PppRandIntParam3*)param3;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&Math);
        if (in->fieldC != 0) {
            value += RandF__5CMathFv(&Math);
        } else {
            value *= kPppRandIntSingleSampleScale;
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
    *target += (s32)((f32)in->field8 * *valuePtr - (f32)in->field8);
}
