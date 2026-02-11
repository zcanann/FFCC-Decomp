#include "ffcc/pppSRandUpCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

/*
 * --INFO--
 * PAL Address: 0x80064114
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    float* target;

    if (*(int*)param2 == *((int*)param1 + 3)) {
        int** base_ptr = (int**)((char*)param3 + 0xc);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);

        u8 flag = *((u8*)param2 + 0x10);
        float value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = (value + RandF__5CMathFv(&math)) * 0.5f;
        }
        target[0] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = (value + RandF__5CMathFv(&math)) * 0.5f;
        }
        target[1] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = (value + RandF__5CMathFv(&math)) * 0.5f;
        }
        target[2] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = (value + RandF__5CMathFv(&math)) * 0.5f;
        }
        target[3] = value;
    } else if (*(int*)param2 != *((int*)param1 + 3)) {
        int** base_ptr = (int**)((char*)param3 + 0xc);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);
    }

    int color_offset = *((int*)param2 + 1);
    u8* target_colors;
    if (color_offset == -1) {
        target_colors = lbl_801EADC8;
    } else {
        target_colors = (u8*)((char*)param1 + color_offset + 0x80);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0x8);
        int delta = (int)(base * target[0]);
        target_colors[0] = (u8)(target_colors[0] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0x9);
        int delta = (int)(base * target[1]);
        target_colors[1] = (u8)(target_colors[1] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0xA);
        int delta = (int)(base * target[2]);
        target_colors[2] = (u8)(target_colors[2] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0xB);
        int delta = (int)(base * target[3]);
        target_colors[3] = (u8)(target_colors[3] + delta);
    }
}
