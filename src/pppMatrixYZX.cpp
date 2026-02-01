#include "ffcc/pppMatrixYZX.h"

#include "ffcc/pppsintbl.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 320b
 */
void pppMatrixYZX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mY;
    pppFMATRIX mZ;
    pppFMATRIX yz;
    pppFMATRIX mX;

    pppGetRotMatrixY(mY, angle->y);
    pppGetRotMatrixZ(mZ, angle->z);
    PSMTXConcat(mY.value, mZ.value, yz.value);
    pppGetRotMatrixX(mX, angle->x);
    PSMTXConcat(yz.value, mX.value, out.value);
}