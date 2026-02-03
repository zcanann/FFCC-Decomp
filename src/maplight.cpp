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
        *color = mColor;
    }
    if (vec != nullptr) {
        *vec = mVec;
    }
}
