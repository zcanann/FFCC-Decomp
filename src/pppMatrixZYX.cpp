#include "ffcc/pppMatrixZYX.h"

#include "ffcc/pppsintbl.h"
#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 800659d8
 * PAL Size: 320b
 */
void pppMatrixZYX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mZ;
    pppFMATRIX mY;
    pppFMATRIX zy;
    pppFMATRIX mX;

    pppGetRotMatrixZ(mZ, angle->z);
    pppGetRotMatrixY(mY, angle->y);
    PSMTXConcat(mZ.value, mY.value, zy.value);
    pppGetRotMatrixX(mX, angle->x);
    PSMTXConcat(zy.value, mX.value, out.value);
}