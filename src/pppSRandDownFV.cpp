#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330080;
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
 * PAL Address: 0x80063840
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownFV(void* param1, void* param2, void* param3)
{
    int* indexPtr;
    float* randomVec;
    float* targetVec;
    int state;

    if (lbl_8032ED70 != 0) {
        return;
    }

    state = *(int*)((char*)param1 + 0xC);
    if (state == 0) {
        indexPtr = *(int**)((char*)param3 + 0xC);
        randomVec = (float*)((char*)param1 + *indexPtr + 0x80);

        float randVal = -RandF__5CMathFv(&math);
        if (*((unsigned char*)param2 + 0x18) != 0) {
            randVal = (randVal - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randomVec[0] = randVal;

        randVal = -RandF__5CMathFv(&math);
        if (*((unsigned char*)param2 + 0x18) != 0) {
            randVal = (randVal - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randomVec[1] = randVal;

        randVal = -RandF__5CMathFv(&math);
        if (*((unsigned char*)param2 + 0x18) != 0) {
            randVal = (randVal - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randomVec[2] = randVal;
    } else {
        if (*(int*)param2 != state) {
            return;
        }

        indexPtr = *(int**)((char*)param3 + 0xC);
        randomVec = (float*)((char*)param1 + *indexPtr + 0x80);
    }

    if (*((int*)param2 + 1) == -1) {
        targetVec = &lbl_801EADC8;
    } else {
        targetVec = (float*)((char*)param1 + *((int*)param2 + 1) + 0x80);
    }

    targetVec[0] = targetVec[0] + (*((float*)param2 + 2) * randomVec[0]);
    targetVec[1] = targetVec[1] + (*((float*)param2 + 3) * randomVec[1]);
    targetVec[2] = targetVec[2] + (*((float*)param2 + 4) * randomVec[2]);
}
