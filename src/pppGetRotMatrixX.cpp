#include "ffcc/pppGetRotMatrixX.h"

#include "ffcc/partMngTrig.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixX(pppFMATRIX& mtx, unsigned long angle)
{
    float zero = 0.0f; // FLOAT_8032feb4
    float one = 1.0f; // FLOAT_8032feb0
    float sinValue = pppSinFromTable(angle);
    float cosValue = pppCosFromTable(angle);

    mtx[0][0] = one;
    mtx[0][1] = zero;
    mtx[0][2] = zero;
    mtx[0][3] = zero;

    mtx[1][0] = zero;
    mtx[1][1] = cosValue;
    mtx[1][2] = -sinValue;
    mtx[1][3] = zero;
	
    mtx[2][0] = zero;
    mtx[2][1] = sinValue;
    mtx[2][2] = cosValue;
    mtx[2][3] = zero;
}
