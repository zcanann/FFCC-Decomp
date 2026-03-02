#include "ffcc/pppRandUpInt.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern s32 lbl_8032ED70;
extern f32 lbl_80330018;
extern f64 lbl_80330020;
extern s32 lbl_801EADC8;
extern "C" {
f32 RandF__5CMathFv(CMath*);
}

/*
 * --INFO--
 * PAL Address: 0x80062ce0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpInt(void* r3, void* r4, void* r5)
{
    u8* param1 = (u8*)r3;
    u8* param2 = (u8*)r4;
    u8* param3 = (u8*)r5;
    f32* valuePtr;

    if (lbl_8032ED70 != 0) {
        return;
    }

    s32 baseState = *(s32*)(param1 + 0xC);
    if (baseState == 0) {
        f32 value = RandF__5CMathFv(&math[0]);
        if (*(u8*)(param2 + 0xC) != 0) {
            value = (value + RandF__5CMathFv(&math[0])) * lbl_80330018;
        }

        valuePtr = (f32*)(param1 + **(s32**)(param3 + 0xC) + 0x80);
        *valuePtr = value;
    } else {
        if (*(s32*)(param2 + 0) != baseState) {
            return;
        }
        valuePtr = (f32*)(param1 + **(s32**)(param3 + 0xC) + 0x80);
    }

    s32* target;
    if (*(s32*)(param2 + 4) == -1) {
        target = &lbl_801EADC8;
    } else {
        target = (s32*)(param1 + *(s32*)(param2 + 4) + 0x80);
    }

    union {
        f64 d;
        struct {
            u32 hi;
            u32 lo;
        } parts;
    } cvt;
    cvt.parts.hi = 0x43300000;
    cvt.parts.lo = *(u32*)(param2 + 8);

    s32 delta = (s32)((cvt.d - lbl_80330020) * *valuePtr);
    *target += delta;
}
