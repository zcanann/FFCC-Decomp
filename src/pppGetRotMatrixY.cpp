#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppsintbl.h"

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
    const float kZero = 0.0f;
    const float kOne = 1.0f;
    unsigned int tableAngle = angle;
    float sinValue = pppSinFromTable(tableAngle);
    float cosValue = pppCosFromTable(tableAngle);

    mtx.value[0][0] = cosValue;
    mtx.value[0][1] = kZero;
    mtx.value[0][2] = sinValue;
    mtx.value[0][3] = kZero;

    mtx.value[1][0] = kZero;
    mtx.value[1][1] = kOne;
    mtx.value[1][2] = kZero;
    mtx.value[1][3] = kZero;

    mtx.value[2][0] = -sinValue;
    mtx.value[2][1] = kZero;
    mtx.value[2][2] = cosValue;
    mtx.value[2][3] = kZero;
}
