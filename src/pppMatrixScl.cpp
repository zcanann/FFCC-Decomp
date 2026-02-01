#include "ffcc/pppMatrixScl.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x8006530c
 * PAL Size: 140b
 */
void pppMatrixScl(void* mtx, void* data)
{
    f32* m = (f32*)mtx;
    Mtx* matPtr = (Mtx*)((u8*)m + 16);
    PSMTXIdentity(*matPtr);
    
    void* dataPtr = ((void**)data)[3]; 
    u32* indices = (u32*)dataPtr;
    u32 idx1 = indices[0];
    u32 idx2 = indices[1];
    
    f32* src1 = (f32*)((u8*)mtx + idx1 + 0x80);
    f32* src2 = (f32*)((u8*)mtx + idx2 + 0x80);
    
    m[4] = src2[0];   // 0x10 offset 
    m[9] = src2[1];   // 0x24 offset
    m[14] = src2[2];  // 0x38 offset
    m[7] = src1[0];   // 0x1c offset
    m[11] = src1[1];  // 0x2c offset  
    m[15] = src1[2];  // 0x3c offset
}