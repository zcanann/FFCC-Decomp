#include "ffcc/pppGetRotMatrixXZY.h"

#include "ffcc/pppsintbl.h"
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
	pppFMATRIX mY;
	pppFMATRIX mZ;
	pppFMATRIX zy;
	pppFMATRIX mX;

	pppGetRotMatrixY(mY, angle->y);
	pppGetRotMatrixZ(mZ, angle->z);
	PSMTXConcat(mZ.value, mY.value, zy.value);
	pppGetRotMatrixX(mX, angle->x);
	PSMTXConcat(mX.value, zy.value, out.value);
}
