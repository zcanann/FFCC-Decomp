#include "ffcc/pppGetRotMatrixXYZ.h"

#include "ffcc/pppsintbl.h"
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
    s32* angle32 = (s32*)angle;
	pppFMATRIX mZ;
	pppFMATRIX mY;
	pppFMATRIX yz;
	pppFMATRIX mX;

	pppGetRotMatrixZ(mZ, angle32[2]);
	pppGetRotMatrixY(mY, angle32[1]);
	PSMTXConcat(mY.value, mZ.value, yz.value);
	pppGetRotMatrixX(mX, angle32[0]);
	PSMTXConcat(mX.value, yz.value, out.value);
}
