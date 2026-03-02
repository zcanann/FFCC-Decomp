#include "ffcc/pppGetRotMatrixZXY.h"

#include "ffcc/pppsintbl.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixZXY(pppFMATRIX& out, pppIVECTOR4* angle)
{
    s32* angle32 = (s32*)angle;
    pppFMATRIX mY;
    pppFMATRIX mX;
    pppFMATRIX xy;
    pppFMATRIX mZ;
	
    pppGetRotMatrixY(mY, angle32[1]);
    pppGetRotMatrixX(mX, angle32[0]);
    PSMTXConcat(mX.value, mY.value, xy.value);
    pppGetRotMatrixZ(mZ, angle32[2]);
    PSMTXConcat(mZ.value, xy.value, out.value);
}
