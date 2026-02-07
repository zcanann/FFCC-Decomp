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

// Forward declarations from CMath
extern "C" {
    float RandF__5CMathFv(CMath*);
}

extern CMath math;

void pppRandInt(void* basePtr, void* dataPtr, void* outputPtr)
{
    extern u32 lbl_8032ED70;
    u8* base = (u8*)basePtr;
    u32* data = (u32*)dataPtr;
    u32* out = (u32*)outputPtr;
    float* source;
    s32 baseValue;

    if (lbl_8032ED70 != 0) {
        return;
    }

    baseValue = *(s32*)(base + 0xC);
    if (baseValue == 0) {
        float value = RandF__5CMathFv(&math);

        if (((u8*)dataPtr)[0xC] != 0) {
            value += RandF__5CMathFv(&math);
        } else {
            value *= 2.0f;
        }

        source = (float*)(base + *(u32*)out[3] + 0x80);
        *source = value;
    } else {
        if ((s32)data[0] != baseValue) {
            return;
        }

        source = (float*)(base + *(u32*)out[3] + 0x80);
    }

    s32* targetPtr;
    if ((s32)data[1] == -1) {
        extern s32 lbl_801EADC8[];
        targetPtr = lbl_801EADC8;
    } else {
        targetPtr = (s32*)(base + data[1] + 0x80);
    }

    {
        u32 value = data[2];
        float result = ((float)value * *source) - (float)value;
        *targetPtr = (s32)result + *targetPtr;
    }
}
