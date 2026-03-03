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
void pppMatrixXYZ(void* target, void* unused, void* param)
{
    (void)unused;

    f32* matrix = (f32*)target;
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)target + offsets[1] + 0x80);
    f32* translation = (f32*)((u8*)target + offsets[0] + 0x80);
    f32* scale = (f32*)((u8*)target + offsets[2] + 0x80);
    Vec tempVec1;
    Vec tempVec2;
    Vec tempVec3;

    pppGetRotMatrixXYZ(*(pppFMATRIX*)(matrix + 4), angle);

    tempVec1.x = matrix[4];
    tempVec1.y = matrix[8];
    tempVec1.z = matrix[12];
    PSVECScale(&tempVec1, &tempVec1, scale[0]);
    matrix[4] = tempVec1.x;
    matrix[8] = tempVec1.y;
    matrix[12] = tempVec1.z;

    tempVec2.x = matrix[5];
    tempVec2.y = matrix[9];
    tempVec2.z = matrix[13];
    PSVECScale(&tempVec2, &tempVec2, scale[1]);
    matrix[5] = tempVec2.x;
    matrix[9] = tempVec2.y;
    matrix[13] = tempVec2.z;

    tempVec3.x = matrix[6];
    tempVec3.y = matrix[10];
    tempVec3.z = matrix[14];
    PSVECScale(&tempVec3, &tempVec3, scale[2]);
    matrix[6] = tempVec3.x;
    matrix[10] = tempVec3.y;
    matrix[14] = tempVec3.z;

    matrix[7] = translation[0];
    matrix[11] = translation[1];
    matrix[15] = translation[2];
}
