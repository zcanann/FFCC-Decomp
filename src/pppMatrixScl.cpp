#include "ffcc/pppMatrixScl.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x8006530c
 * PAL Size: 140b
 */
void pppMatrixScl(void* mtx, void* data)
{
    f32* matrix = (f32*)mtx;
    Mtx* mtxPtr = (Mtx*)((u8*)matrix + 16);
    
    void* dataPtr = ((void**)data)[3];
    u32 index1 = ((u32*)dataPtr)[0];
    u32 index2 = ((u32*)dataPtr)[1];
    
    f32* scale1 = (f32*)((u8*)matrix + index1 + 0x80);
    f32* scale2 = (f32*)((u8*)matrix + index2 + 0x80);
    
    PSMTXIdentity(*mtxPtr);
    
    matrix[4] = scale2[0];   // 0x10 offset
    matrix[9] = scale2[1];   // 0x24 offset
    matrix[14] = scale2[2];  // 0x38 offset
    matrix[7] = scale1[0];   // 0x1c offset
    matrix[11] = scale1[1];  // 0x2c offset
    matrix[15] = scale1[2];  // 0x3c offset
}