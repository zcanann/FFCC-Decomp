#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_80330038;
extern f64 lbl_80330040;
extern s16 lbl_801EADC8;

struct PppRandUpShortParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    u8 fieldA;
};

struct PppRandUpShortParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpShort(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    s32* base = (s32*)param1;
    PppRandUpShortParam2* in = (PppRandUpShortParam2*)param2;
    s32*** out = (s32***)param3;
    s32 baseState = base[3];

    if (baseState == 0) {
        math.RandF();
        f32 value = 1.0f;
        if (in->fieldA != 0) {
            math.RandF();
            value += 1.0f;
        }
        value *= lbl_80330038;
        *(f32*)((u8*)base + ***out + 0x80) = value;
        return;
    }

    if (in->field0 != baseState) {
        return;
    }

    s16* target;

    if (in->field4 == -1) {
        target = &lbl_801EADC8;
    } else {
        target = (s16*)((u8*)base + in->field4 + 0x80);
    }

    s32 delta = (s32)(((f64)in->field8 - lbl_80330040) * *(f32*)((u8*)base + ***out + 0x80));
    *target = (s16)(*target + delta);
}
