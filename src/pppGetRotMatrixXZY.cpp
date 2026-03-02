#include "ffcc/pppGetRotMatrixXZY.h"

#include "ffcc/pppsintbl.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x80064948
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixXZY(pppFMATRIX& out, pppIVECTOR4* angle)
{
	s32* angle32 = (s32*)angle;
	pppFMATRIX mY;
	pppFMATRIX mZ;
	pppFMATRIX zy;
	pppFMATRIX mX;

	pppGetRotMatrixY(mY, angle32[1]);
	pppGetRotMatrixZ(mZ, angle32[2]);
	PSMTXConcat(mZ.value, mY.value, zy.value);
	pppGetRotMatrixX(mX, angle32[0]);
	PSMTXConcat(mX.value, zy.value, out.value);
}
