#include "ffcc/pppGetRotMatrixYZX.h"

#include "ffcc/pppGetRotMatrixX.h"
#include "ffcc/pppGetRotMatrixY.h"
#include "ffcc/pppGetRotMatrixZ.h"

/*
 * --INFO--
 * PAL Address: 0x8005f93c
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetRotMatrixYZX(pppFMATRIX& out, pppIVECTOR4* angle)
{
    s32* angle32 = (s32*)angle;
    pppFMATRIX mX;
    pppFMATRIX mZ;
    pppFMATRIX zx;
    pppFMATRIX mY;

    pppGetRotMatrixX(mX, angle32[0]);
    pppGetRotMatrixZ(mZ, angle32[2]);
    PSMTXConcat(mZ.value, mX.value, zx.value);
    pppGetRotMatrixY(mY, angle32[1]);
    PSMTXConcat(mY.value, zx.value, out.value);
}
