#include "ffcc/pppGetRotMatrixYXZ.h"

#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x8005f8c4
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixYXZ(pppFMATRIX& out, pppIVECTOR4* angle)
{
    pppFMATRIX mZ;
    pppFMATRIX mX;
    pppFMATRIX xz;
    pppFMATRIX mY;

    pppGetRotMatrixZ(mZ, angle->z);
    pppGetRotMatrixX(mX, angle->x);
    PSMTXConcat(mX.value, mZ.value, xz.value);
    pppGetRotMatrixY(mY, angle->y);
    PSMTXConcat(mY.value, xz.value, out.value);
}
