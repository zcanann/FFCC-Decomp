#include "ffcc/pppRandInt.h"
#include "ffcc/math.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FFA8;
extern f64 lbl_8032FFB0;
extern s32 lbl_801EADC8[];

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

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&math[0]);
        if (in->fieldC != 0) {
            value += RandF__5CMathFv(&math[0]);
        } else {
            value *= lbl_8032FFA8;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s32* target = (in->field4 == -1) ? lbl_801EADC8 : (s32*)(base + in->field4 + 0x80);
    *target += (s32)((f32)in->field8 * *valuePtr - (f32)in->field8);
}
