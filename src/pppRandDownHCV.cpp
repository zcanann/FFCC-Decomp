#include "ffcc/pppRandDownHCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern s16 lbl_801EADC8[];
extern float lbl_8032FF48;
extern "C" float RandF__5CMathFv(CMath* instance);

extern "C" {

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void randshort(short value, float multiplier)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownHCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(int*)param2 == *((int*)param1 + 3)) {
        float rand_value = -RandF__5CMathFv(&math);
        if (*((u8*)param2 + 0x10) != 0) {
            rand_value = (rand_value - RandF__5CMathFv(&math)) * lbl_8032FF48;
        }

        int data_offset = **(int**)((char*)param3 + 0xc);
        *(float*)((char*)param1 + data_offset + 0x80) = rand_value;
    } else if (*(int*)param2 != *((int*)param1 + 3)) {
        int data_offset = **(int**)((char*)param3 + 0xc);
        float* random_value = (float*)((char*)param1 + data_offset + 0x80);
        int color_offset = *((int*)param2 + 1);
        s16* target;

        if (color_offset == -1) {
            target = lbl_801EADC8;
        } else {
            target = (s16*)((char*)param1 + color_offset + 0x80);
        }

        float scale = random_value[0];

        {
            s16 base = *(s16*)((char*)param2 + 0x8);
            target[0] = (s16)(target[0] + (int)((float)base * scale));
        }

        {
            s16 base = *(s16*)((char*)param2 + 0xa);
            target[1] = (s16)(target[1] + (int)((float)base * scale));
        }

        {
            s16 base = *(s16*)((char*)param2 + 0xc);
            target[2] = (s16)(target[2] + (int)((float)base * scale));
        }

        {
            s16 base = *(s16*)((char*)param2 + 0xe);
            target[3] = (s16)(target[3] + (int)((float)base * scale));
        }
    }
}

}
