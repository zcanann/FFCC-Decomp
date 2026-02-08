#include "ffcc/pppRandDownShort.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
extern "C" f32 RandF__5CMathFv(CMath*);

extern s32 lbl_8032ED70;
extern f32 lbl_8032FF78;
extern f64 lbl_8032FF80;
extern s16 lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80061c1c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownShort(void* r3, void* r4, void* r5)
{
    u8* param1 = (u8*)r3;
    u8* param2 = (u8*)r4;
    u8* param3 = (u8*)r5;
    f32* valuePtr;

    if (lbl_8032ED70 == 0) {
        s32 baseState = *(s32*)(param1 + 0xC);
        if (baseState == 0) {
            f32 value = -RandF__5CMathFv(&math[0]);

            if (*(u8*)(param2 + 0xA) != 0) {
                value = (value - RandF__5CMathFv(&math[0])) * lbl_8032FF78;
            }

            valuePtr = (f32*)(param1 + **(s32**)(param3 + 0xC) + 0x80);
            *valuePtr = value;
        } else {
            if (*(s32*)(param2 + 0) != baseState) {
                return;
            }

            valuePtr = (f32*)(param1 + **(s32**)(param3 + 0xC) + 0x80);
        }

        s16* target;
        if (*(s32*)(param2 + 4) == -1) {
            target = &lbl_801EADC8;
        } else {
            target = (s16*)(param1 + *(s32*)(param2 + 4) + 0x80);
        }

        union {
            f64 d;
            struct {
                u32 hi;
                u32 lo;
            } bits;
        } cvt;

        cvt.bits.hi = 0x43300000;
        cvt.bits.lo = *(u16*)(param2 + 8);

        *target = (s16)(*target + (s32)((f32)(cvt.d - lbl_8032FF80) * *valuePtr));
    }
}
