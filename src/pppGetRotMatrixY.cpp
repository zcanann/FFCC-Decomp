#include "ffcc/pppGetRotMatrixY.h"

#include "ffcc/partMngTrig.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixY(pppFMATRIX& mtx, unsigned long angle)
{  
	float zero = 0.0f; // FLOAT_8032febc
	float one = 1.0f; // FLOAT_8032feb8
	float sinValue = pppSinFromTable(angle);
	float cosValue = pppCosFromTable(angle);

	mtx[0][0] = cosValue;
	mtx[0][1] = zero;
	mtx[0][2] = sinValue;
	mtx[0][3] = zero;

	mtx[1][0] = zero;
	mtx[1][1] = one;
	mtx[1][2] = zero;
	mtx[1][3] = zero;

	mtx[2][0] = -sinValue;
	mtx[2][1] = zero;
	mtx[2][2] = cosValue;
	mtx[2][3] = zero;
}
