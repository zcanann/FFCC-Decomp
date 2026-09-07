#include "ffcc/pppGetRotMatrixXYZ.h"

#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x8005f71c
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixXYZ(pppFMATRIX& out, pppIVECTOR4* angle)
{
	pppFMATRIX mZ;
	pppFMATRIX mY;
	pppFMATRIX yz;
	pppFMATRIX mX;

	pppGetRotMatrixZ(mZ, angle->z);
	pppGetRotMatrixY(mY, angle->y);
	PSMTXConcat(mY.value, mZ.value, yz.value);
	pppGetRotMatrixX(mX, angle->x);
	PSMTXConcat(mX.value, yz.value, out.value);
}
