#include "ffcc/ppp_constants.h"
#include "ffcc/pppGetRotMatrixX.h"

/*
 * --INFO--
 * PAL Address: 0x8005f794
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixX(pppFMATRIX& mtx, long angle)
{
    unsigned int tableAngle = angle;
    float sinValue = *(float*)((unsigned char*)gPppTrigTable + (tableAngle & 0xFFFC));
    float cosValue = *(float*)((unsigned char*)gPppTrigTable + ((tableAngle + 0x4000) & 0xFFFC));

    mtx.value[0][0] = kPppGetRotMatrixXOne;
    mtx.value[0][1] = kPppGetRotMatrixXZero;
    mtx.value[0][2] = kPppGetRotMatrixXZero;
    mtx.value[0][3] = kPppGetRotMatrixXZero;

    mtx.value[1][0] = kPppGetRotMatrixXZero;
    mtx.value[1][1] = cosValue;
    mtx.value[1][2] = -sinValue;
    mtx.value[1][3] = kPppGetRotMatrixXZero;

    mtx.value[2][0] = kPppGetRotMatrixXZero;
    mtx.value[2][1] = sinValue;
    mtx.value[2][2] = cosValue;
    mtx.value[2][3] = kPppGetRotMatrixXZero;
}
