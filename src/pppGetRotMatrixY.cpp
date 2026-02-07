#include "ffcc/pppGetRotMatrixY.h"

extern float ppvSinTbl[];

/*
 * --INFO--
 * PAL Address: 0x8005f868
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixY(pppFMATRIX& mtx, long angle)
{
    float one = 1.0f;
    float zero = 0.0f;
    float sinValue = *(float*)((unsigned char*)ppvSinTbl + (angle & 0xFFFC));
    float cosValue = *(float*)((unsigned char*)ppvSinTbl + ((angle + 0x4000) & 0xFFFC));

    mtx.value[0][0] = cosValue;
    mtx.value[0][1] = zero;
    mtx.value[0][2] = sinValue;
    mtx.value[0][3] = zero;

    mtx.value[1][0] = zero;
    mtx.value[1][1] = one;
    mtx.value[1][2] = zero;
    mtx.value[1][3] = zero;

    mtx.value[2][0] = -sinValue;
    mtx.value[2][1] = zero;
    mtx.value[2][2] = cosValue;
    mtx.value[2][3] = zero;
}
