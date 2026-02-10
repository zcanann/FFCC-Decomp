#include "ffcc/pppRandDownCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern char lbl_801EAC40[];
extern float lbl_8032FF28;
extern "C" float RandF__5CMathFv(CMath*);

extern "C" {

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void randchar(char value, float multiplier)
{
    // Simple random char generation function
}

/*
 * --INFO--
 * PAL Address: 80061384
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownCV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(int*)param2 == *((int*)param1 + 3)) {
        float rand_value = -RandF__5CMathFv(&math);
        if (*((u8*)param2 + 0xc) != 0) {
            rand_value = (rand_value - RandF__5CMathFv(&math)) * lbl_8032FF28;
        }

        int data_offset = **(int**)((char*)param3 + 0xc);
        *(float*)((char*)param1 + data_offset + 0x80) = rand_value;
    }

    if (*(int*)param2 != *((int*)param1 + 3)) {
        return;
    }

    int data_offset = **(int**)((char*)param3 + 0xc);
    float* random_value = (float*)((char*)param1 + data_offset + 0x80);
    int color_offset = *((int*)param2 + 1);
    char* target;

    if (color_offset == -1) {
        target = lbl_801EAC40;
    } else {
        target = (char*)((char*)param1 + color_offset + 0x80);
    }

    float scale = random_value[0];

    {
        char base = *(char*)((char*)param2 + 0x8);
        target[0] = (char)(target[0] + (int)((float)base * scale));
    }

    {
        char base = *(char*)((char*)param2 + 0x9);
        target[1] = (char)(target[1] + (int)((float)base * scale));
    }

    {
        char base = *(char*)((char*)param2 + 0xa);
        target[2] = (char)(target[2] + (int)((float)base * scale));
    }

    {
        char base = *(char*)((char*)param2 + 0xb);
        target[3] = (char)(target[3] + (int)((float)base * scale));
    }
}

}
