#include "ffcc/pppGetRotMatrixYXZ.h"

#include "ffcc/pppsintbl.h"
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
    s32* angle32 = (s32*)angle;
    pppFMATRIX mZ;
    pppFMATRIX mX;
    pppFMATRIX xz;
    pppFMATRIX mY;

    pppGetRotMatrixZ(mZ, angle32[2]);
    pppGetRotMatrixX(mX, angle32[0]);
    PSMTXConcat(mX.value, mZ.value, xz.value);
    pppGetRotMatrixY(mY, angle32[1]);
    PSMTXConcat(mY.value, xz.value, out.value);
}
