#include "ffcc/pppGetRotMatrixYZX.h"

#include "ffcc/partMngTrig.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetRotMatrixYZX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mX;
    pppFMATRIX mZ;
    Mtx zx;
    pppFMATRIX mY;

    pppGetRotMatrixX(mX, angle->x);
    pppGetRotMatrixZ(mZ, angle->z);
    PSMTXConcat(mZ, mX, zx);
    pppGetRotMatrixY(mY, angle->y);
    PSMTXConcat(mY, zx, out);
}
