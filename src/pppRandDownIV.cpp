#include "ffcc/pppRandDownIV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF68;
extern f64 lbl_8032FF70;
extern s32 lbl_801EADC8;

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

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
    u8* base = (u8*)param1;
    PppRandDownIVParam2* in = (PppRandDownIVParam2*)param2;
    PppRandDownIVParam3* out = (PppRandDownIVParam3*)param3;
    f32* valuePtr;
    s32* target;
    f32 value;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = -RandF__5CMathFv(&math);
        if (in->field18 != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_8032FF68;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    }

    if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    }

    valuePtr = (f32*)(base + *out->fieldC + 0x80);
    if (in->field4 == -1) {
        target = &lbl_801EADC8;
    } else {
        target = (s32*)(base + in->field4 + 0x80);
    }

    {
        f32 randValue = *valuePtr;
        target[0] += (s32)((f64)in->field8 * (f64)randValue);
        target[1] += (s32)((f64)in->fieldC * (f64)randValue);
        target[2] += (s32)((f64)in->field10 * (f64)randValue);
    }
}
