#include "ffcc/pppGetRotMatrixXZY.h"

#include "ffcc/partMngTrig.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixXZY(pppFMATRIX& out, pppIVECTOR4* angle)
{
	pppFMATRIX mZ;
	pppFMATRIX mY;
	Mtx yz;
	pppFMATRIX mX;

	pppGetRotMatrixZ(mZ, angle->z);
	pppGetRotMatrixY(mY, angle->y);
	PSMTXConcat(mY, mZ, yz);
	pppGetRotMatrixX(mX, angle->x);
	PSMTXConcat(mX, yz, out);
}
