#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

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
    u8* colors;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(int*)param2 == *((int*)param1 + 3)) {
        return;
    }

    if (*(int*)param2 == -1) {
        if (*((u8*)param2 + 0xc) != 0) {
            RandF__5CMathFv(&math);
            RandF__5CMathFv(&math);
        }
        colors = lbl_801EADC8;
    } else {
        colors = (u8*)((char*)param1 + *((int*)param2 + 1) + 0x80);
    }

    {
        int valueOffset = *(int*)param1 + 0x80;
        float scale = *(float*)((char*)*(void**)((char*)param3 + 0xc) + valueOffset);

        {
            s8 delta = *((s8*)param2 + 8);
            int add = (int)((float)delta * scale);
            colors[0] = (u8)(colors[0] + add);
        }

        {
            s8 delta = *((s8*)param2 + 9);
            int add = (int)((float)delta * scale);
            colors[1] = (u8)(colors[1] + add);
        }

        {
            s8 delta = *((s8*)param2 + 10);
            int add = (int)((float)delta * scale);
            colors[2] = (u8)(colors[2] + add);
        }

        {
            s8 delta = *((s8*)param2 + 11);
            int add = (int)((float)delta * scale);
            colors[3] = (u8)(colors[3] + add);
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randchar(char value, float multiplier)
{
    (void)value;
    (void)multiplier;
}
