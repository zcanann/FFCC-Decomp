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
void pppMatrixXZY(f32* target, void* unused, void* param){
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)target + offsets[1] + 0x80);
    f32* translation = (f32*)((u8*)target + offsets[0] + 0x80);
    f32* scale = (f32*)((u8*)target + offsets[2] + 0x80);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixXZY(*(pppFMATRIX*)((u8*)target + 0x10), angle);

    temp1.x = target[4];
    temp1.y = target[8];
    temp1.z = target[12];
    PSVECScale(&temp1, &temp1, scale[0]);
    target[4] = temp1.x;
    target[8] = temp1.y;
    target[12] = temp1.z;

    temp2.x = target[5];
    temp2.y = target[9];
    temp2.z = target[13];
    PSVECScale(&temp2, &temp2, scale[1]);
    target[5] = temp2.x;
    target[9] = temp2.y;
    target[13] = temp2.z;

    temp3.x = target[6];
    temp3.y = target[10];
    temp3.z = target[14];
    PSVECScale(&temp3, &temp3, scale[2]);
    target[6] = temp3.x;
    target[10] = temp3.y;
    target[14] = temp3.z;

    target[7] = translation[0];
    target[11] = translation[1];
    target[15] = translation[2];
}
