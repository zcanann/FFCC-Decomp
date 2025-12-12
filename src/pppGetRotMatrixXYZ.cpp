#include "ffcc/pppGetRotMatrixXYZ.h"

#include "ffcc/partMngTrig.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
