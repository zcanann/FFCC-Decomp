#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "types.h"

extern CMath math[];
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

    if (*(s32*)param2 != *(s32*)((u8*)param1 + 0xC)) {
        return;
    }

    f32 value = RandF__5CMathFv(math);
    if (*((u8*)param2 + 0xC) != 0) {
        value = lbl_8032FF08 * (value + RandF__5CMathFv(math));
    }

    s32 offset = **(s32**)((u8*)param3 + 0xC);
    *(f32*)((u8*)param1 + offset + 0x80) = value;

    s32 colorOffset = *(s32*)((u8*)param2 + 0x4);
    u8* target;
    if (colorOffset == -1) {
        target = lbl_801EADC8;
    } else {
        target = (u8*)param1 + colorOffset + 0x80;
    }

    f32 scale = *(f32*)((u8*)param1 + offset + 0x80);

    {
        target[0] = (u8)(target[0] + (s32)(scale * (f32)*(s8*)((u8*)param2 + 0x8)));
    }

    {
        target[1] = (u8)(target[1] + (s32)(scale * (f32)*(s8*)((u8*)param2 + 0x9)));
    }

    {
        target[2] = (u8)(target[2] + (s32)(scale * (f32)*(s8*)((u8*)param2 + 0xA)));
    }

    {
        target[3] = (u8)(target[3] + (s32)(scale * (f32)*(s8*)((u8*)param2 + 0xB)));
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
