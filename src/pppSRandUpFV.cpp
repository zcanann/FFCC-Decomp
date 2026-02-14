#include "ffcc/pppSRandUpFV.h"
#include "ffcc/math.h"

extern CMath math[];
extern int lbl_8032ED70;
extern float lbl_803300C0;
extern float lbl_801EADC8[];
extern "C" float RandF__5CMathFv(CMath*);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randfloat(float f1, float f2)
{
    // Basic random float implementation
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char param)
{
    // Basic random function with byte parameter
}

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppSRandUpFV(void* param1, void* param2, void* param3)
{
    struct Param {
        int index;
        int offset;
        float x;
        float y;
        float z;
        unsigned char _pad[4];
        unsigned char blendTwice;
    };
    struct SelectInfo {
        int _pad0;
        int _pad1;
        int _pad2;
        int* offsetPtr;
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(param1);
    Param* cfg = reinterpret_cast<Param*>(param2);
    float* randVec;
    int currentIndex;

    if (lbl_8032ED70 != 0) {
        return;
    }

    currentIndex = *reinterpret_cast<int*>(self + 0xC);
    if (currentIndex == 0) {
        int offset = *reinterpret_cast<SelectInfo*>(param3)->offsetPtr;
        unsigned char blendTwice = cfg->blendTwice;
        randVec = reinterpret_cast<float*>(self + offset + 0x80);

        float value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
        }
        randVec[0] = value;

        value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
        }
        randVec[1] = value;

        value = RandF__5CMathFv(math);
        if (blendTwice != 0) {
            value = (value + RandF__5CMathFv(math)) * lbl_803300C0;
        }
        randVec[2] = value;
    } else {
        if (cfg->index != currentIndex) {
            return;
        }
        randVec = reinterpret_cast<float*>(self + *reinterpret_cast<SelectInfo*>(param3)->offsetPtr + 0x80);
    }

    float* target;
    if (cfg->offset == -1) {
        target = lbl_801EADC8;
    } else {
        target = reinterpret_cast<float*>(self + cfg->offset + 0x80);
    }

    {
        float value = cfg->x * randVec[0];
        target[0] = target[0] + value;
    }
    {
        float value = cfg->y * randVec[1];
        target[1] = target[1] + value;
    }
    {
        float value = cfg->z * randVec[2];
        target[2] = target[2] + value;
    }
}
