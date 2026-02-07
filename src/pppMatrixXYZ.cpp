#include "ffcc/pppMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065398
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppMatrixXYZ(pppFMATRIX& matrix, PPPCREATEPARAM* param)
{
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)&matrix + offsets[1] + 0x80);
    f32* scale = (f32*)((u8*)&matrix + offsets[2] + 0x80);
    f32* translation = (f32*)((u8*)&matrix + offsets[0] + 0x80);
    Vec tempVec1;
    Vec tempVec2;
    Vec tempVec3;

    pppGetRotMatrixXYZ(matrix, angle);

    tempVec1.x = matrix.value[0][0];
    tempVec1.y = matrix.value[1][0];
    tempVec1.z = matrix.value[2][0];
    PSVECScale(&tempVec1, &tempVec1, scale[0]);
    matrix.value[0][0] = tempVec1.x;
    matrix.value[1][0] = tempVec1.y;
    matrix.value[2][0] = tempVec1.z;

    tempVec2.x = matrix.value[0][1];
    tempVec2.y = matrix.value[1][1];
    tempVec2.z = matrix.value[2][1];
    PSVECScale(&tempVec2, &tempVec2, scale[1]);
    matrix.value[0][1] = tempVec2.x;
    matrix.value[1][1] = tempVec2.y;
    matrix.value[2][1] = tempVec2.z;

    tempVec3.x = matrix.value[0][2];
    tempVec3.y = matrix.value[1][2];
    tempVec3.z = matrix.value[2][2];
    PSVECScale(&tempVec3, &tempVec3, scale[2]);
    matrix.value[0][2] = tempVec3.x;
    matrix.value[1][2] = tempVec3.y;
    matrix.value[2][2] = tempVec3.z;

    matrix.value[0][3] = translation[0];
    matrix.value[1][3] = translation[1];
    matrix.value[2][3] = translation[2];
}
