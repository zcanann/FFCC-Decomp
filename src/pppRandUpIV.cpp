#include "ffcc/pppRandUpIV.h"
#include "ffcc/math.h"
#include "types.h"

extern s32 lbl_8032ED70;
extern f32 lbl_80330028;
extern CMath math[];
extern s32 lbl_801EADC8[];

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandUpIVParam2 {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    u8 field14[4];
    u8 field18;
};

struct PppRandUpIVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80062e0c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpIV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandUpIVParam2* in = (PppRandUpIVParam2*)param2;
    PppRandUpIVParam3* out = (PppRandUpIVParam3*)param3;
    f32 value;
    s32 outputOffset = *out->fieldC + 0x80;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = RandF__5CMathFv(&math[0]);
        if (in->field18 != 0) {
            f32 randValue = value + RandF__5CMathFv(&math[0]);
            value = randValue * lbl_80330028;
        }

        *(f32*)(base + outputOffset) = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    }
    if (in->field4 == -1) {
        target = &lbl_801EADC8[0];
    } else {
        if (in->field0 != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? &lbl_801EADC8[0] : (s32*)(base + in->field4 + 0x80);
    f32 scale = *valuePtr;

    target[0] += (s32)((f32)in->field8 * scale);
    target[1] += (s32)((f32)in->fieldC * scale);
    target[2] += (s32)((f32)in->field10 * scale);
}
