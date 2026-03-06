#include "ffcc/pppRandUpInt.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath Math;
extern int gPppCalcDisabled;
extern f32 lbl_80330018;
extern const f64 lbl_80330020;
extern s32 gPppDefaultValueBuffer[];
extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandUpIntParam2 {
    s32 field0;
    s32 field4;
    u32 field8;
    u8 fieldC;
};

struct PppRandUpIntParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80062ce0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpInt(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandUpIntParam2* in = (PppRandUpIntParam2*)param2;
    PppRandUpIntParam3* out = (PppRandUpIntParam3*)param3;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&Math);
        if (in->fieldC != 0) {
            f32 mixed = value + RandF__5CMathFv(&Math);
            value = mixed * lbl_80330018;
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

    f32 scaled = (f32)in->field8 * *valuePtr;
    s32 delta = (s32)scaled;
    *target += delta;
}
