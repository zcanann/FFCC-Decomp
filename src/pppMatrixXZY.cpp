#include "ffcc/pppMatrixXZY.h"

#include "ffcc/pppGetRotMatrixXZY.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80060380
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixXZY(pppFMATRIX& mtx, void* param)
{
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)&mtx + offsets[1] + 0x80);
    f32* scale = (f32*)((u8*)&mtx + offsets[2] + 0x80);
    f32* translation = (f32*)((u8*)&mtx + offsets[0] + 0x80);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixXZY(mtx, angle);

    temp1.x = mtx.value[0][0];
    temp1.y = mtx.value[1][0];
    temp1.z = mtx.value[2][0];
    PSVECScale(&temp1, &temp1, scale[0]);
    mtx.value[0][0] = temp1.x;
    mtx.value[1][0] = temp1.y;
    mtx.value[2][0] = temp1.z;

    temp2.x = mtx.value[0][1];
    temp2.y = mtx.value[1][1];
    temp2.z = mtx.value[2][1];
    PSVECScale(&temp2, &temp2, scale[1]);
    mtx.value[0][1] = temp2.x;
    mtx.value[1][1] = temp2.y;
    mtx.value[2][1] = temp2.z;

    temp3.x = mtx.value[0][2];
    temp3.y = mtx.value[1][2];
    temp3.z = mtx.value[2][2];
    PSVECScale(&temp3, &temp3, scale[2]);
    mtx.value[0][2] = temp3.x;
    mtx.value[1][2] = temp3.y;
    mtx.value[2][2] = temp3.z;

    mtx.value[0][3] = translation[0];
    mtx.value[1][3] = translation[1];
    mtx.value[2][3] = translation[2];
}
