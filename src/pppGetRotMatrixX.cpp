#include "ffcc/pppGetRotMatrixX.h"

#include "ffcc/pppsintbl.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixX(pppFMATRIX& mtx, long angle)
{
    float zero = 0.0f; // FLOAT_8032feb4
    float one = 1.0f; // FLOAT_8032feb0
    float sinValue = pppSinFromTable(angle);
    float cosValue = pppCosFromTable(angle);

    mtx.value[0][0] = one;
    mtx.value[0][1] = zero;
    mtx.value[0][2] = zero;
    mtx.value[0][3] = zero;

    mtx.value[1][0] = zero;
    mtx.value[1][1] = cosValue;
    mtx.value[1][2] = -sinValue;
    mtx.value[1][3] = zero;
	
    mtx.value[2][0] = zero;
    mtx.value[2][1] = sinValue;
    mtx.value[2][2] = cosValue;
    mtx.value[2][3] = zero;
}
