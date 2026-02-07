#include "ffcc/pppSRandFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330098;
extern float lbl_801EADC8;
extern "C" float RandF__5CMathFv(CMath*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randfloat(float, float)
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

/*
 * --INFO--
 * PAL Address: 0x80063c7c
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandFV(void* param1, void* param2, void* param3)
{
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (p1[3] == 0) {
        int* indexPtr = *(int**)((char*)p3 + 0xC);
        float* outVec = (float*)((char*)p1 + *indexPtr + 0x80);
        unsigned char blendTwice = ((unsigned char*)p2)[0x18];
        float randVal;

        randVal = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            randVal = randVal + RandF__5CMathFv(&math);
        } else {
            randVal = randVal * lbl_80330098;
        }
        outVec[0] = randVal;

        randVal = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            randVal = randVal + RandF__5CMathFv(&math);
        } else {
            randVal = randVal * lbl_80330098;
        }
        outVec[1] = randVal;

        randVal = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            randVal = randVal + RandF__5CMathFv(&math);
        } else {
            randVal = randVal * lbl_80330098;
        }
        outVec[2] = randVal;
        return;
    }

    if (p2[0] != p1[3]) {
        return;
    }

    int* indexPtr = *(int**)((char*)p3 + 0xC);
    float* randomVec = (float*)((char*)p1 + *indexPtr + 0x80);
    float* targetVec;

    if (p2[1] == -1) {
        targetVec = &lbl_801EADC8;
    } else {
        targetVec = (float*)((char*)p1 + p2[1] + 0x80);
    }

    targetVec[0] = targetVec[0] + (*(float*)((char*)p2 + 8) * randomVec[0] - *(float*)((char*)p2 + 8));
    targetVec[1] = targetVec[1] + (*(float*)((char*)p2 + 0xC) * randomVec[1] - *(float*)((char*)p2 + 0xC));
    targetVec[2] = targetVec[2] + (*(float*)((char*)p2 + 0x10) * randomVec[2] - *(float*)((char*)p2 + 0x10));
}
