#include "ffcc/maplight.h"

/*
 * --INFO--
 * PAL Address: 0x8004b1d0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapLightHolder::GetLightHolder(_GXColor* color, Vec* vec)
{
    if (color != nullptr) {
        // Copy color bytes individually (matching Ghidra decomp)
        ((unsigned char*)color)[0] = ((unsigned char*)this)[0];
        ((unsigned char*)color)[1] = ((unsigned char*)this)[1];
        ((unsigned char*)color)[2] = ((unsigned char*)this)[2];
        ((unsigned char*)color)[3] = ((unsigned char*)this)[3];
    }
    if (vec != nullptr) {
        // Copy Vec as 3 float values (matching Ghidra decomp)  
        ((float*)vec)[0] = *(float*)((char*)this + 4);
        ((float*)vec)[1] = *(float*)((char*)this + 8);
        ((float*)vec)[2] = *(float*)((char*)this + 0xc);
    }
}
