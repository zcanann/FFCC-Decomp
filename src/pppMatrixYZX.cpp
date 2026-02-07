#include "ffcc/pppMatrixYZX.h"
#include "ffcc/pppGetRotMatrixYZX.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065758
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixYZX(void* target, void* unused, void* param)
{
    (void)unused;

    f32* matrix = (f32*)target;
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)target + offsets[1] + 0x80);
    f32* scale = (f32*)((u8*)target + offsets[2] + 0x80);
    f32* translation = (f32*)((u8*)target + offsets[0] + 0x80);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixYZX(*(pppFMATRIX*)(matrix + 4), angle);

    temp1.x = matrix[4];
    temp1.y = matrix[8];
    temp1.z = matrix[12];
    PSVECScale(&temp1, &temp1, scale[0]);
    matrix[4] = temp1.x;
    matrix[8] = temp1.y;
    matrix[12] = temp1.z;

    temp2.x = matrix[5];
    temp2.y = matrix[9];
    temp2.z = matrix[13];
    PSVECScale(&temp2, &temp2, scale[1]);
    matrix[5] = temp2.x;
    matrix[9] = temp2.y;
    matrix[13] = temp2.z;

    temp3.x = matrix[6];
    temp3.y = matrix[10];
    temp3.z = matrix[14];
    PSVECScale(&temp3, &temp3, scale[2]);
    matrix[6] = temp3.x;
    matrix[10] = temp3.y;
    matrix[14] = temp3.z;

    matrix[7] = translation[0];
    matrix[11] = translation[1];
    matrix[15] = translation[2];
}
