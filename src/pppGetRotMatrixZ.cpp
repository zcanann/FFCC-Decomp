#include "ffcc/ppp_constants.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x8005F9B4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixZ(pppFMATRIX& mtx, long angle)
{
    unsigned int tableAngle = angle;
    float one = 1.0f;
    float zero = 0.0f;
    float sinValue = *(float*)((unsigned char*)gPppTrigTable + (tableAngle & 0xFFFC));
    float cosValue = *(float*)((unsigned char*)gPppTrigTable + ((tableAngle + 0x4000) & 0xFFFC));

    mtx.value[0][0] = cosValue;
    mtx.value[0][1] = -sinValue;
    mtx.value[0][2] = zero;
    mtx.value[0][3] = zero;

    mtx.value[1][0] = sinValue;
    mtx.value[1][1] = cosValue;
    mtx.value[1][2] = zero;
    mtx.value[1][3] = zero;

    mtx.value[2][0] = zero;
    mtx.value[2][1] = zero;
    mtx.value[2][2] = one;
    mtx.value[2][3] = zero;
}
