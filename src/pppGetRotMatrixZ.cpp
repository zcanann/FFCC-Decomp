#include "ffcc/pppGetRotMatrixZ.h"

#include "ffcc/partMngTrig.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixZ(pppFMATRIX& mtx, long angle)
{    
	float zero = 0.0f; // FLOAT_8032fec4
	float one = 1.0f; // FLOAT_8032fec0
	float sinValue = pppSinFromTable(angle);
	float cosValue = pppCosFromTable(angle);

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
