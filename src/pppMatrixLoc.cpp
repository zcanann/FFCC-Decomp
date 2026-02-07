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
    f32* posData = (f32*)((char*)target + *(int*)*(int*)((char*)param + 0xc) + 0x80);
    (void)unused;

    PSMTXIdentity((MtxPtr)((char*)target + 0x10));

    *(f32*)((char*)target + 0x1c) = posData[0];
    *(f32*)((char*)target + 0x2c) = posData[1];
    *(f32*)((char*)target + 0x3c) = posData[2];
}
