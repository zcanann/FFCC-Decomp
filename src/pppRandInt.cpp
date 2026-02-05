#include "ffcc/pppRandInt.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x80062194
 * PAL Size: 320b
 */

// Forward declarations from CMath
extern "C" {
    float RandF__5CMathFv();
}

void pppRandInt(void* basePtr, void* dataPtr, void* outputPtr)
{
    extern u32 lbl_8032ED70;

    struct Param2 {
        s32 field0;   // offset 0x0
        s32 field4;   // offset 0x4
        s32 field8;   // offset 0x8
        u8  fieldC;   // offset 0xC
    };

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (((s32*)basePtr)[3] == 0) {
        float randomFloat = RandF__5CMathFv();
        if (((Param2*)dataPtr)->fieldC != 0) {
            randomFloat += RandF__5CMathFv();
        } else {
            randomFloat *= 2.0f;
        }

        u32 offset = *(u32*)outputPtr;
        *(float*)((u8*)basePtr + offset + 0x80) = randomFloat;
        return;
    }

    if (((Param2*)dataPtr)->field0 != ((s32*)basePtr)[3]) {
        return;
    }

    u32 offset = *(u32*)outputPtr;
    float* sourcePtr = (float*)((u8*)basePtr + offset + 0x80);

    s32* targetPtr;
    if (((Param2*)dataPtr)->field4 == -1) {
        extern s32 lbl_801EADC8[];
        targetPtr = lbl_801EADC8;
    } else {
        targetPtr = (s32*)((u8*)basePtr + ((Param2*)dataPtr)->field4 + 0x80);
    }

    float scale = (float)((Param2*)dataPtr)->field8;
    s32 delta = (s32)(*sourcePtr * scale);
    *targetPtr += delta;
}
