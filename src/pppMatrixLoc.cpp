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
void pppMatrixLoc(void* target, void* arg1, void* param)
{
    u32 dataOffset = **(u32**)((char*)param + 0xc);
    f32* pos = (f32*)((char*)target + dataOffset + 0x80);

    PSMTXIdentity((MtxPtr)((char*)target + 0x10));

    *(f32*)((char*)target + 0x1c) = pos[0];
    *(f32*)((char*)target + 0x2c) = pos[1];
    *(f32*)((char*)target + 0x3c) = pos[2];
}
