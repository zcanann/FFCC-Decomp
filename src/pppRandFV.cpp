#include "ffcc/pppRandFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF90;
extern float lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80061e54
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFV(void* param1, void* param2, void* param3)
{
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (p1[3] == 0) {
        float randVal = 1.0f;

        math.RandF();

        if (((unsigned char*)p3)[0x18] != 0) {
            math.RandF();
            randVal = randVal + 1.0f;
        } else {
            randVal = randVal * lbl_8032FF90;
        }

        int* indexPtr = *(int**)((char*)p2 + 0xC);
        *(float*)((char*)p1 + *indexPtr + 0x80) = randVal;
        return;
    }

    if (p3[0] != p1[3]) {
        return;
    }

    int* indexPtr = *(int**)((char*)p2 + 0xC);
    float* destAddr = (float*)((char*)p1 + *indexPtr + 0x80);
    float* srcAddr;
    float destVal = *destAddr;

    if (p3[1] == -1) {
        srcAddr = &lbl_801EADC8;
    } else {
        srcAddr = (float*)((char*)p1 + p3[1] + 0x80);
    }

    srcAddr[0] = srcAddr[0] + (*(float*)((char*)p3 + 8) * destVal - *(float*)((char*)p3 + 8));
    srcAddr[1] = srcAddr[1] + (*(float*)((char*)p3 + 12) * destVal - *(float*)((char*)p3 + 12));
    srcAddr[2] = srcAddr[2] + (*(float*)((char*)p3 + 16) * destVal - *(float*)((char*)p3 + 16));
}
