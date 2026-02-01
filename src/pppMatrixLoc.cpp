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
void pppMatrixLoc(void* mtxObj, void* locData)
{
    // Calculate location pointer first (matches original order)
    u32 locPtr = *(u32*)((char*)locData + 0xc);
    u32 locBase = *(u32*)locPtr;
    f32* loc = (f32*)((u32)mtxObj + locBase + 0x80);
    
    // Matrix is at offset 0x10 within the object
    MtxPtr mtx = (MtxPtr)((char*)mtxObj + 0x10);
    PSMTXIdentity(mtx);
    
    // Set translation components - offsets 0x1c, 0x2c, 0x3c from mtxObj
    *(f32*)((char*)mtxObj + 0x1c) = loc[0];  // X translation
    *(f32*)((char*)mtxObj + 0x2c) = loc[1];  // Y translation 
    *(f32*)((char*)mtxObj + 0x3c) = loc[2];  // Z translation
}