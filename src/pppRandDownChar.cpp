#include "ffcc/pppRandDownChar.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF18;
extern f64 lbl_8032FF20;
extern u8 lbl_801EADC8[];

extern "C" {
f32 RandF__5CMathFv(CMath*);
}

struct PppRandDownCharParam2 {
    s32 field0;
    s32 field4;
    u8 field8;
    u8 field9;
};

struct PppRandDownCharParam3 {
    u8 unk0[0xC];
    s32* fieldC;
};

/*
 * --INFO--
 * PAL Address: 80061258
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownChar(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    u8* base = (u8*)param1;
    PppRandDownCharParam2* in = (PppRandDownCharParam2*)param2;
    PppRandDownCharParam3* out = (PppRandDownCharParam3*)param3;
    f32* valuePtr;

    s32 baseState = *(s32*)(base + 0xC);
    if (baseState == 0) {
        f32 value = -RandF__5CMathFv(math);
        if (in->field9 != 0) {
            value = lbl_8032FF18 * (value - RandF__5CMathFv(math));
        }

        valuePtr = (f32*)(base + *out->fieldC + 0x80);
        *valuePtr = value;
    } else {
        if (in->field0 != baseState) {
            return;
        }
        valuePtr = (f32*)(base + *out->fieldC + 0x80);
    }

    u8* target;
    if (in->field4 == -1) {
        target = lbl_801EADC8;
    } else {
        target = (u8*)(base + in->field4 + 0x80);
    }

    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } parts;
    } cvt;
    u8 scale = in->field8;
    cvt.parts.hi = 0x43300000;
    cvt.parts.lo = scale;

    s32 delta = (s32)((float)(cvt.d - lbl_8032FF20) * *valuePtr);
    *target = (u8)(*target + delta);
}
