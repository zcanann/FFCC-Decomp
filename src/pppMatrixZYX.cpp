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
extern "C" void pppMatrixZYX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mZ, mY, mX, zy;

    pppGetRotMatrixZ(mZ, angle->z);
    pppGetRotMatrixY(mY, angle->y);
    pppGetRotMatrixX(mX, angle->x);
    
    PSMTXConcat(mZ.value, mY.value, zy.value);
    PSMTXConcat(zy.value, mX.value, out.value);
}