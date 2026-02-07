#include "ffcc/pppRandFV.h"
#include "ffcc/math.h"
#include "types.h"

// Forward declarations from CMath
extern "C" {
    float RandF__5CMathFv(CMath*);
}

extern CMath math;
extern u32 lbl_8032ED70;
extern float lbl_8032FF90;
extern float lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80061e54
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFV(void* basePtr, void* dataPtr, void* outputPtr)
{
    u8* base = (u8*)basePtr;
    s32* data = (s32*)dataPtr;
    s32* out = (s32*)outputPtr;
    float* source;
    float value;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(s32*)(base + 0xC) == 0) {
        value = RandF__5CMathFv(&math);

        if (((u8*)outputPtr)[0x18] != 0) {
            value += RandF__5CMathFv(&math);
        } else {
            value *= lbl_8032FF90;
        }

        source = (float*)(base + *(u32*)data[3] + 0x80);
        *source = value;
    } else {
        if (out[0] != *(s32*)(base + 0xC)) {
            return;
        }

        source = (float*)(base + *(u32*)data[3] + 0x80);
    }

    float* dest;
    if (out[1] == -1) {
        dest = &lbl_801EADC8;
    } else {
        dest = (float*)(base + out[1] + 0x80);
    }

    float factor = *source;

    {
        float mul = *(float*)(out + 2);
        float cur = dest[0];
        dest[0] = cur + (mul * factor - mul);
    }

    {
        float mul = *(float*)(out + 3);
        float cur = dest[1];
        dest[1] = cur + (mul * factor - mul);
    }

    {
        float mul = *(float*)(out + 4);
        float cur = dest[2];
        dest[2] = cur + (mul * factor - mul);
    }
}
