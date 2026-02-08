#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330080;
extern unsigned char lbl_801EADC8[];

extern "C" float RandF__5CMathFv(CMath*);

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
    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(int*)((char*)param1 + 0xC) == 0) {
        int dataOffset = **(int**)((char*)param3 + 0xC);
        float* randomVec = (float*)((char*)param1 + dataOffset + 0x80);
        unsigned char blendTwice = *(unsigned char*)((char*)param2 + 0x18);
        float randVal;

        randVal = -RandF__5CMathFv();
        if (blendTwice != 0) {
            randVal = (randVal - RandF__5CMathFv()) * lbl_80330080;
        }
        randomVec[0] = randVal;

        randVal = -RandF__5CMathFv();
        if (blendTwice != 0) {
            randVal = (randVal - RandF__5CMathFv()) * lbl_80330080;
        }
        randomVec[1] = randVal;

        randVal = -RandF__5CMathFv();
        if (blendTwice != 0) {
            randVal = (randVal - RandF__5CMathFv()) * lbl_80330080;
        }
        randomVec[2] = randVal;
        return;
    }

    if (*(int*)param2 != *(int*)((char*)param1 + 0xC)) {
        return;
    }

    {
        int dataOffset = **(int**)((char*)param3 + 0xC);
        float* randomVec = (float*)((char*)param1 + dataOffset + 0x80);
        int targetOffset = *(int*)((char*)param2 + 4);
        unsigned char* target;

        if (targetOffset == -1) {
            target = lbl_801EADC8;
        } else {
            target = (unsigned char*)((char*)param1 + targetOffset + 0x80);
        }

        target[0] = (unsigned char)(target[0] + (int)(*(float*)((char*)param2 + 8) * randomVec[0]));
        target[1] = (unsigned char)(target[1] + (int)(*(float*)((char*)param2 + 0xC) * randomVec[1]));
        target[2] = (unsigned char)(target[2] + (int)(*(float*)((char*)param2 + 0x10) * randomVec[2]));
    }
}
