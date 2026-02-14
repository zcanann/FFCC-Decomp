#include "ffcc/pppSRandCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern u8 lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath* instance);

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    float* target;

    if (*(int*)param2 == *((int*)param1 + 3)) {
        int** base_ptr = (int**)((char*)param3 + 0xc);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);

        u8 flag = *((u8*)param2 + 0xc);
        float value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * 2.0f;
        }
        target[0] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * 2.0f;
        }
        target[1] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * 2.0f;
        }
        target[2] = value;

        value = RandF__5CMathFv(&math);
        if (flag != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * 2.0f;
        }
        target[3] = value;
    } else if (*(int*)param2 != *((int*)param1 + 3)) {
        int** base_ptr = (int**)((char*)param3 + 0xc);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);
    }

    int color_offset = *((int*)param2 + 1);
    u8* target_color;
    if (color_offset == -1) {
        target_color = lbl_801EADC8;
    } else {
        target_color = (u8*)((char*)param1 + color_offset + 0x80);
    }

    {
        u8 current = target_color[0];
        s8 base = *(s8*)((char*)param2 + 8);
        int delta = (int)((float)base * target[0] - (float)current);
        target_color[0] = (u8)(current + delta);
    }

    {
        u8 current = target_color[1];
        s8 base = *(s8*)((char*)param2 + 9);
        int delta = (int)((float)base * target[1] - (float)current);
        target_color[1] = (u8)(current + delta);
    }

    {
        u8 current = target_color[2];
        s8 base = *(s8*)((char*)param2 + 0xa);
        int delta = (int)((float)base * target[2] - (float)current);
        target_color[2] = (u8)(current + delta);
    }

    {
        u8 current = target_color[3];
        s8 base = *(s8*)((char*)param2 + 0xb);
        int delta = (int)((float)base * target[3] - (float)current);
        target_color[3] = (u8)(current + delta);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randchar(char, float)
{
    // TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char)
{
    // TODO
}

#ifdef __cplusplus
}
#endif
