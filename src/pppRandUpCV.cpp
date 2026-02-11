#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math;
extern s32 lbl_8032ED70;
extern f32 lbl_8032FF08;
extern u8 lbl_801EADC8[32];
extern "C" f32 RandF__5CMathFv(CMath* instance);

/*
 * --INFO--
 * PAL Address: 0x80062708
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(int*)param2 == *((int*)param1 + 3)) {
        f32 value = RandF__5CMathFv(&math);
        if (*((u8*)param2 + 0xC) != 0) {
            value = (value + RandF__5CMathFv(&math)) * lbl_8032FF08;
        }
        int valueOffset = **(int**)((char*)param3 + 0xC);
        *(f32*)((char*)param1 + valueOffset + 0x80) = value;
    }

    if (*(int*)param2 != *((int*)param1 + 3)) {
        return;
    }

    int valueOffset = **(int**)((char*)param3 + 0xC);
    f32* randomValue = (f32*)((char*)param1 + valueOffset + 0x80);
    f32 scale = randomValue[0];

    int colorOffset = *((int*)param2 + 1);
    u8* target;
    if (colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (u8*)((char*)param1 + colorOffset + 0x80);
    }

    {
        s8 value = *(s8*)((char*)param2 + 0x8);
        target[0] = (u8)(target[0] + (int)((f32)value * scale));
    }

    {
        s8 value = *(s8*)((char*)param2 + 0x9);
        target[1] = (u8)(target[1] + (int)((f32)value * scale));
    }

    {
        s8 value = *(s8*)((char*)param2 + 0xA);
        target[2] = (u8)(target[2] + (int)((f32)value * scale));
    }

    {
        s8 value = *(s8*)((char*)param2 + 0xB);
        target[3] = (u8)(target[3] + (int)((f32)value * scale));
    }
}

/*
 * --INFO--
 * Address: TODO  
 * Size: TODO
 */
void randchar(char, float)
{
    // TODO - appears to be unused based on objdiff
}
