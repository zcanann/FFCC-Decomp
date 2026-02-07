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
void pppMatrixLoc(void* target, void* param) {
    char* t = (char*)target;
    char* p = (char*)param;
    f32* pos;

    PSMTXIdentity((MtxPtr)(t + 0x10));
    pos = (f32*)(t + *(int*)(p + 0xC) + 0x80);
    *(f32*)(t + 0x1C) = pos[0];
    *(f32*)(t + 0x2C) = pos[1];
    *(f32*)(t + 0x3C) = pos[2];
}
