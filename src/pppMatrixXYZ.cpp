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
void pppMatrixXYZ(f32* target, void* unused, void* param){
    (void)unused;
    u32* offsets = (u32*)*(void**)((u8*)param + 0xC);
    pppIVECTOR4* angle = (pppIVECTOR4*)((u8*)target + offsets[1] + 0x80);
    f32* translation = (f32*)((u8*)target + offsets[0] + 0x80);
    f32* scale = (f32*)((u8*)target + offsets[2] + 0x80);
    Vec tempVec1;
    Vec tempVec2;
    Vec tempVec3;

    pppGetRotMatrixXYZ(*(pppFMATRIX*)(target + 4), angle);

    tempVec1.x = target[4];
    tempVec1.y = target[8];
    tempVec1.z = target[12];
    PSVECScale(&tempVec1, &tempVec1, scale[0]);
    target[4] = tempVec1.x;
    target[8] = tempVec1.y;
    target[12] = tempVec1.z;

    tempVec2.x = target[5];
    tempVec2.y = target[9];
    tempVec2.z = target[13];
    PSVECScale(&tempVec2, &tempVec2, scale[1]);
    target[5] = tempVec2.x;
    target[9] = tempVec2.y;
    target[13] = tempVec2.z;

    tempVec3.x = target[6];
    tempVec3.y = target[10];
    tempVec3.z = target[14];
    PSVECScale(&tempVec3, &tempVec3, scale[2]);
    target[6] = tempVec3.x;
    target[10] = tempVec3.y;
    target[14] = tempVec3.z;

    target[7] = translation[0];
    target[11] = translation[1];
    target[15] = translation[2];
}
