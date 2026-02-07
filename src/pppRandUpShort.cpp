#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330038; 
extern double lbl_80330040;
extern short lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 */
void pppRandUpShort(void* param1, void* param2, void* param3)
{
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int*** p3 = (int***)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (p1[3] == 0) {
        math.RandF();

        float randVal = 1.0f;
        if (*(u8*)((char*)p2 + 0xA) != 0) {
            math.RandF();
            randVal += 1.0f;
        }

        randVal *= lbl_80330038;
        *(float*)((char*)p1 + (***p3 + 0x80)) = randVal;
        return;
    }

    if (p2[0] != p1[3]) {
        return;
    }

    float* src = (float*)((char*)p1 + ***p3);
    short* dst;
    if (p2[1] == -1) {
        dst = &lbl_801EADC8;
    } else {
        dst = (short*)((char*)p1 + p2[1] + 0x80);
    }

    int add = (int)(((double)*(short*)((char*)p2 + 8) - lbl_80330040) * *(float*)((char*)src + 0x80));
    *dst = *dst + add;
}
