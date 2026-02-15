#include "ffcc/pppRandUpFV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
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
void pppRandUpFV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandUpFVParam3* out = (PppRandUpFVParam3*)param3;
    PppRandUpFVParam2* in = (PppRandUpFVParam2*)param2;
    f32* valuePtr;

    s32 state = *(s32*)(base + 0xC);
    if (state == 0) {
        f32 value = RandF__5CMathFv(math);
        if (in->field18 != 0) {
            value = lbl_80330000 * (value + RandF__5CMathFv(math));
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != state) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    f32* target = (in->field4 == -1) ? lbl_801EADC8 : (f32*)(base + in->field4 + 0x80);
    f32 scale = *valuePtr;
    f32 value = in->field8 * scale;
    target[0] = target[0] + value;
    value = in->fieldC * scale;
    target[1] = target[1] + value;
    value = in->field10 * scale;
    target[2] = target[2] + value;
}
