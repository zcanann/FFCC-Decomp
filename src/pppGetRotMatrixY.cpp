#include "ffcc/ppp_constants.h"
#include "ffcc/pppGetRotMatrixY.h"

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
    unsigned int tableAngle = angle;
    float sinValue = *(float*)((unsigned char*)gPppTrigTable + (angle & 0xFFFC));
    float cosValue = *(float*)((unsigned char*)gPppTrigTable + ((tableAngle + 0x4000) & 0xFFFC));

    mtx.value[0][0] = cosValue;
    mtx.value[0][1] = kPppGetRotMatrixYZero;
    mtx.value[0][2] = sinValue;
    mtx.value[0][3] = kPppGetRotMatrixYZero;

    mtx.value[1][0] = kPppGetRotMatrixYZero;
    mtx.value[1][1] = kPppGetRotMatrixYOne;
    mtx.value[1][2] = kPppGetRotMatrixYZero;
    mtx.value[1][3] = kPppGetRotMatrixYZero;

    mtx.value[2][0] = -sinValue;
    mtx.value[2][1] = kPppGetRotMatrixYZero;
    mtx.value[2][2] = cosValue;
    mtx.value[2][3] = kPppGetRotMatrixYZero;
}
