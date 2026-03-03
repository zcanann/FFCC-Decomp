#include "ffcc/pppRandDownHCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern s16 lbl_801EADC8[];
extern f32 lbl_8032FF48;

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandDownHCVParam2 {
    s32 field0;
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
    u8 field10;
};

struct PppRandDownHCVParam3 {
    u8 field0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void randshort(short value, float multiplier)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownHCV(void* param1, void* param2, void* param3)
{
    u8* base = (u8*)param1;
    PppRandDownHCVParam2* in = (PppRandDownHCVParam2*)param2;
    PppRandDownHCVParam3* out = (PppRandDownHCVParam3*)param3;
    f32* valuePtr;
    s16* target;
    f32 value;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (in->field0 == *(s32*)(base + 0xC)) {
        value = -RandF__5CMathFv(&math[0]);
        if (in->field10 != 0) {
            value = (value - RandF__5CMathFv(&math[0])) * lbl_8032FF48;
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    }

    if (in->field0 != *(s32*)(base + 0xC)) {
        return;
    }

    valuePtr = (f32*)(base + *out->fieldC + 0x80);
    if (in->field4 == -1) {
        target = &lbl_801EADC8[0];
    } else {
        target = (s16*)(base + in->field4 + 0x80);
    }

    {
        f32 randValue = *valuePtr;

        target[0] = (s16)(target[0] + (s32)((f32)in->field8 * randValue));
        target[1] = (s16)(target[1] + (s32)((f32)in->fieldA * randValue));
        target[2] = (s16)(target[2] + (s32)((f32)in->fieldC * randValue));
        target[3] = (s16)(target[3] + (s32)((f32)in->fieldE * randValue));
    }
}
