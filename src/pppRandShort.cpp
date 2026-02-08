#include "ffcc/pppRandShort.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FFC8;
extern s16 lbl_801EADC8;

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandShortParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    u8 fieldA;
};

struct PppRandShortParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x8006249c
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandShort(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandShortParam2* in = (PppRandShortParam2*)param2;
    PppRandShortParam3* out = (PppRandShortParam3*)param3;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&math);
        if (in->fieldA != 0) {
            value += RandF__5CMathFv(&math);
        } else {
            value *= lbl_8032FFC8;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    s16* target;
    if (in->field4 == -1) {
        target = &lbl_801EADC8;
    } else {
        target = (s16*)(base + in->field4 + 0x80);
    }

    f32 delta = ((f32)in->field8 * *valuePtr) - (f32)in->field8;
    *target = (s16)(*target + (s16)delta);
}
