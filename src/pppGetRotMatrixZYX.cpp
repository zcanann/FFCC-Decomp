#include "ffcc/pppGetRotMatrixZYX.h"

#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x8005fa88
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixZYX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mX;
    pppFMATRIX mY;
    pppFMATRIX yx;
    pppFMATRIX mZ;

    pppGetRotMatrixX(mX, angle->x);
    pppGetRotMatrixY(mY, angle->y);
    PSMTXConcat(mY.value, mX.value, yx.value);
    pppGetRotMatrixZ(mZ, angle->z);
    PSMTXConcat(mZ.value, yx.value, out.value);
}
