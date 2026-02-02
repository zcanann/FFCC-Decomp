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
    PSMTXConcat(*(Mtx*)((char*)src + 0x80), *(Mtx*)((char*)mtx + 0x10), *(Mtx*)((char*)src + *(u32*)((char*)data + 0xc)));
}