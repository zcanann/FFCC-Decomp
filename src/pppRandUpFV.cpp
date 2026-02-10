#include "ffcc/pppRandUpFV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_80330000;
extern f32 lbl_801EADC8[];
extern "C" f32 RandF__5CMathFv(CMath*);

struct PppRandUpFVParam2 {
    s32 field0;
    s32 field4;
    f32 field8;
    f32 fieldC;
    f32 field10;
    u8 unk14[0x18 - 0x14];
    u8 field18;
};

struct PppRandUpFVParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x800629e8
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpFV(void* param1, void* param2, void* param3) {
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandUpFVParam2* in = (PppRandUpFVParam2*)param2;
    PppRandUpFVParam3* out = (PppRandUpFVParam3*)param3;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&math);
        if (in->field18 != 0) {
            value = (value + RandF__5CMathFv(&math)) * lbl_80330000;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    f32* target;
    if (in->field4 == -1) {
        target = lbl_801EADC8;
    } else {
        target = (f32*)(base + in->field4 + 0x80);
    }

    f32 scale = *valuePtr;
    target[0] = target[0] + in->field8 * scale;
    target[1] = target[1] + in->fieldC * scale;
    target[2] = target[2] + in->field10 * scale;
}
