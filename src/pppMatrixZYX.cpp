#include "ffcc/pppMatrixZYX.h"

#include "ffcc/pppGetRotMatrixZYX.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800659D8
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixZYX(f32* target, void* unused, void* param){
    (void)unused;
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    u32 translationOffset = offsets[0];
    u32 scaleOffset = offsets[2];
    u32 angleOffset = offsets[1];
    f32* translation = (f32*)((u8*)target + translationOffset + 0x80);
    f32* scale = (f32*)((u8*)target + scaleOffset + 0x80);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)target + angleOffset + 0x80);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixZYX(*(pppFMATRIX*)(target + 4), angle);

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
