#include "ffcc/pppMatrixLoc.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800652ac
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixLoc(void* target, void* param)
{
    // Initialize matrix to identity (matrix is at offset 0x10)
    PSMTXIdentity((MtxPtr)((char*)target + 0x10));
    
    // Get position data pointer from param+0xc, then add target+0x80  
    int dataOffset = *(int*)((char*)param + 0xc);
    f32* posData = (f32*)((char*)target + dataOffset + 0x80);
    
    // Store position values in matrix translation column
    *(f32*)((char*)target + 0x1c) = posData[0];  // X translation  
    *(f32*)((char*)target + 0x2c) = posData[1];  // Y translation
    *(f32*)((char*)target + 0x3c) = posData[2];  // Z translation
}