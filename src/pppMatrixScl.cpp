#include "ffcc/pppMatrixScl.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x8006530c
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixScl(f32* target, void* unused, void* param){
    (void)unused;
    Mtx* mtxPtr = (Mtx*)((u8*)target + 0x10);

    void* dataPtr = ((void**)param)[3];
    u32 index1 = ((u32*)dataPtr)[0];
    u32 index2 = ((u32*)dataPtr)[1];

    f32* scale1 = (f32*)((u8*)target + index1 + 0x80);
    f32* scale2 = (f32*)((u8*)target + index2 + 0x80);

    PSMTXIdentity(*mtxPtr);

    target[4] = scale2[0];
    target[9] = scale2[1];
    target[14] = scale2[2];
    target[7] = scale1[0];
    target[11] = scale1[1];
    target[15] = scale1[2];
}
