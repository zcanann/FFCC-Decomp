#include "ffcc/pppSRandDownFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330080;
extern float lbl_801EADC8[];

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
    struct Param {
        int index;
        int offset;
        float x;
        float y;
        float z;
        unsigned char _pad[8];
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

        float value = -RandF__5CMathFv(&math);
        if (cfg->blendTwice != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randVec[0] = value;

        value = -RandF__5CMathFv(&math);
        if (cfg->blendTwice != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randVec[1] = value;

        value = -RandF__5CMathFv(&math);
        if (cfg->blendTwice != 0) {
            value = (value - RandF__5CMathFv(&math)) * lbl_80330080;
        }
        randVec[2] = value;
    } else {
        if (cfg->index != *reinterpret_cast<int*>(self + 0xC)) {
            return;
        }
        randVec = reinterpret_cast<float*>(self + *sel->offsetPtr + 0x80);
    }

    float* target;
    if (cfg->offset == -1) {
        target = lbl_801EADC8;
    } else {
        target = reinterpret_cast<float*>(self + cfg->offset + 0x80);
    }

    target[0] += cfg->x * randVec[0];
    target[1] += cfg->y * randVec[1];
    target[2] += cfg->z * randVec[2];
}
