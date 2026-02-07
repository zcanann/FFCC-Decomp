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
    void** p3 = (void**)param2;
    int* p2 = (int*)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (p1[3] == 0) {
        float randVal1, randVal2;

        math.RandF();
        randVal1 = 1.0f;

        unsigned char* p2_bytes = (unsigned char*)p2;
        if (p2_bytes[0x18] != 0) {
            math.RandF();
            randVal2 = 1.0f;
            randVal1 = randVal1 + randVal2;
        } else {
            randVal1 = randVal1 * lbl_8032FF90;
        }

        void** basePtr = (void**)((char*)p3 + 0xC);
        int* indexPtr = (int*)*basePtr;
        float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));
        *destAddr = randVal1;

    } else {
        if (p2[0] == p1[3]) {
            void** basePtr = (void**)((char*)p3 + 0xC);
            int* indexPtr = (int*)*basePtr;
            float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));

            float* srcAddr;
            if (p2[1] == -1) {
                srcAddr = &lbl_801EADC8;
            } else {
                srcAddr = (float*)((char*)p1 + (p2[1] + 0x80));
            }

            float destVal = *destAddr;

            float multiplier1 = *(float*)((char*)p2 + 8);
            float srcVal1 = *srcAddr;
            float result1 = srcVal1 + (multiplier1 * destVal - multiplier1);
            *srcAddr = result1;

            float multiplier2 = *(float*)((char*)p2 + 12);
            float srcVal2 = *(float*)((char*)srcAddr + 4);
            float result2 = srcVal2 + (multiplier2 * destVal - multiplier2);
            *(float*)((char*)srcAddr + 4) = result2;

            float multiplier3 = *(float*)((char*)p2 + 16);
            float srcVal3 = *(float*)((char*)srcAddr + 8);
            float result3 = srcVal3 + (multiplier3 * destVal - multiplier3);
            *(float*)((char*)srcAddr + 8) = result3;
        }
    }
}
