#include "ffcc/pppGetRotMatrixZYX.h"

#include "ffcc/pppsintbl.h"
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
    s32* angle32 = (s32*)angle;
    pppFMATRIX mX;
    pppFMATRIX mY;
    pppFMATRIX yx;
    pppFMATRIX mZ;

    pppGetRotMatrixX(mX, angle32[0]);
    pppGetRotMatrixY(mY, angle32[1]);
    PSMTXConcat(mY.value, mX.value, yx.value);
    pppGetRotMatrixZ(mZ, angle32[2]);
    PSMTXConcat(mZ.value, yx.value, out.value);
}
