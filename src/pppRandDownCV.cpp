#include "ffcc/pppRandDownCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern f32 lbl_8032FF28;
extern "C" f32 RandF__5CMathFv(CMath*);

struct PppRandDownCVParam2 {
    s32 field0;
    s32 field4;
    s8 field8;
    s8 field9;
    s8 fieldA;
    s8 fieldB;
    u8 fieldC;
};

struct PppRandDownCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

extern "C" {

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void randchar(char value, float multiplier)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 80061384
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandDownCVParam2* in = (PppRandDownCVParam2*)param2;
    PppRandDownCVParam3* out = (PppRandDownCVParam3*)param3;
    u8* target;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        f32 value = -RandF__5CMathFv(&math[0]);
        if (in->fieldC != 0) {
            value = (value - RandF__5CMathFv(&math[0])) * lbl_8032FF28;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    target = (in->field4 == -1) ? &lbl_801EADC8[0] : (u8*)(base + in->field4 + 0x80);

    {
        f32 scale = *valuePtr;
        target[0] = (u8)(target[0] + (s32)((f32)in->field8 * scale));
        target[1] = (u8)(target[1] + (s32)((f32)in->field9 * scale));
        target[2] = (u8)(target[2] + (s32)((f32)in->fieldA * scale));
        target[3] = (u8)(target[3] + (s32)((f32)in->fieldB * scale));
    }
}

}
