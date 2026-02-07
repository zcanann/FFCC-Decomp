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
    float* target;

    if (lbl_8032ED70 != 0) {
        return;
    }

    {
        int** basePtr = (int**)((char*)param3 + 0xc);
        int offset = **basePtr;
        target = (float*)((char*)param1 + offset + 0x80);
    }

    if (*(int*)param2 == *((int*)param1 + 3)) {
        u8 flag = *((u8*)param2 + 0xc);
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
    }

    {
        int colorOffset = *((int*)param2 + 1);
        u8* colors;

        if (colorOffset == -1) {
            colors = lbl_801EADC8;
        } else {
            colors = (u8*)((char*)param1 + colorOffset + 0x80);
        }

        {
            s8 base = *((s8*)param2 + 8);
            int delta = (int)(base * target[0]);
            colors[0] = (u8)(colors[0] + delta);
        }

        {
            s8 base = *((s8*)param2 + 9);
            int delta = (int)(base * target[1]);
            colors[1] = (u8)(colors[1] + delta);
        }

        {
            s8 base = *((s8*)param2 + 10);
            int delta = (int)(base * target[2]);
            colors[2] = (u8)(colors[2] + delta);
        }

        {
            s8 base = *((s8*)param2 + 11);
            int delta = (int)(base * target[3]);
            colors[3] = (u8)(colors[3] + delta);
        }
    }
}
