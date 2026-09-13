#include "ffcc/pppDrawMatrixLoc.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8016c9e8
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixLoc(_pppPObject* object, pppNoStep*, _pppCtrlTable*)
{
    Vec drawPos;
    Vec worldPos;
    Vec localPos;

    worldPos.z = 0.0f;
    worldPos.y = 0.0f;
    worldPos.x = 0.0f;
    PSMTXCopy(object->m_localMatrix.value, object->m_drawMatrix.value);
    PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);
    localPos.x = object->m_drawMatrix.value[0][3];
    localPos.y = object->m_drawMatrix.value[1][3];
    localPos.z = object->m_drawMatrix.value[2][3];
    PSVECAdd(&localPos, &worldPos, &drawPos);
    object->m_drawMatrix.value[0][3] = drawPos.x;
    object->m_drawMatrix.value[1][3] = drawPos.y;
    object->m_drawMatrix.value[2][3] = drawPos.z;
}
