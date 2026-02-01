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
    char* targetPtr = (char*)target;
    
    // Initialize matrix to identity (matrix is at offset 0x10)
    PSMTXIdentity((MtxPtr)(targetPtr + 0x10));
    
    // Get position data pointer from param+0xc, then add target+0x80
    void** dataPtr = (void**)((char*)param + 0xc);
    char* posData = targetPtr + (int)*dataPtr + 0x80;
    f32* pos = (f32*)posData;
    
    // Store position values in matrix translation column
    *(f32*)(targetPtr + 0x1c) = pos[0];  // X translation  
    *(f32*)(targetPtr + 0x2c) = pos[1];  // Y translation
    *(f32*)(targetPtr + 0x3c) = pos[2];  // Z translation
}