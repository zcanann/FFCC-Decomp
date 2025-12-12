#include "ffcc/pppGetRotMatrixZXY.h"

#include "ffcc/partMngTrig.h"
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
    pppFMATRIX mY;
    pppFMATRIX mX;
    Mtx xy;
    pppFMATRIX mZ;
	
    pppGetRotMatrixY(mY, angle->y);
    pppGetRotMatrixX(mX, angle->x);
    PSMTXConcat(mX, mY, xy);
    pppGetRotMatrixZ(mZ, angle->z);
    PSMTXConcat(mZ, xy, out);
}
