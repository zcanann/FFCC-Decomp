#include "ffcc/pppSRandFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330098;
extern float lbl_801EADC8[];
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
    SelectInfo* sel = reinterpret_cast<SelectInfo*>(param3);
    float* randVec;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*reinterpret_cast<int*>(self + 0xC) == 0) {
        randVec = reinterpret_cast<float*>(self + *sel->offsetPtr + 0x80);
        unsigned char blendTwice = cfg->blendTwice;
        float value;

        value = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * lbl_80330098;
        }
        randVec[0] = value;

        value = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * lbl_80330098;
        }
        randVec[1] = value;

        value = RandF__5CMathFv(&math);
        if (blendTwice != 0) {
            value = value + RandF__5CMathFv(&math);
        } else {
            value = value * lbl_80330098;
        }
        randVec[2] = value;
        return;
    }

    if (cfg->index != *reinterpret_cast<int*>(self + 0xC)) {
        return;
    }

    randVec = reinterpret_cast<float*>(self + *sel->offsetPtr + 0x80);
    float* targetVec;

    if (cfg->offset == -1) {
        targetVec = lbl_801EADC8;
    } else {
        targetVec = reinterpret_cast<float*>(self + cfg->offset + 0x80);
    }

    targetVec[0] += cfg->x * randVec[0] - cfg->x;
    targetVec[1] += cfg->y * randVec[1] - cfg->y;
    targetVec[2] += cfg->z * randVec[2] - cfg->z;
}
