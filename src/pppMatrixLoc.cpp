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
void pppMatrixLoc(void* target, void* unused, void* param)
{
    (void)unused;

    int* offsetPtr = *(int**)((char*)param + 0xC);
    f32* posData = (f32*)((char*)target + *offsetPtr + 0x80);

    PSMTXIdentity((MtxPtr)((char*)target + 0x10));
    *(f32*)((char*)target + 0x1C) = posData[0];
    *(f32*)((char*)target + 0x2C) = posData[1];
    *(f32*)((char*)target + 0x3C) = posData[2];
}
