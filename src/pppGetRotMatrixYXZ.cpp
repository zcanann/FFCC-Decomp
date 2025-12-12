#include "ffcc/pppGetRotMatrixYXZ.h"

#include "ffcc/partMngTrig.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixYXZ(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mZ;
    pppFMATRIX mX;
    Mtx xz;
    pppFMATRIX mY;

    pppGetRotMatrixZ(mZ, angle->z);
    pppGetRotMatrixX(mX, angle->x);
    PSMTXConcat(mX, mZ, xz);
    pppGetRotMatrixY(mY, angle->y);
    PSMTXConcat(mY, xz, out);
}
