#include "ffcc/pppSpMatrix.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800d3818
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSpMatrix(void* mtx, void* src, void* data)
{
    u32 offset = **((u32**)((char*)data + 0xc));
    Mtx* mtxSrc = (Mtx*)((char*)mtx + offset + 0x80);
    Mtx* mtxOut = (Mtx*)((char*)mtx + 0x10);

    (void)src;
    PSMTXConcat(*mtxSrc, *mtxOut, *mtxOut);
}
