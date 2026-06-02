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
void pppDrawMatrixLoc(_pppPObject* object, void*, _pppCtrlTable*)
{
    Vec local_2c;
    Vec local_38;
    Vec local_20[2];

    local_2c.z = 0.0f;
    local_2c.y = 0.0f;
    local_2c.x = 0.0f;
    PSMTXCopy(object->m_localMatrix.value, object->m_drawMatrix.value);
    PSMTXMultVec(ppvWorldMatrix, &local_2c, &local_2c);
    local_38.x = object->m_drawMatrix.value[0][3];
    local_38.y = object->m_drawMatrix.value[1][3];
    local_38.z = object->m_drawMatrix.value[2][3];
    PSVECAdd(&local_38, &local_2c, local_20);
    object->m_drawMatrix.value[0][3] = local_20[0].x;
    object->m_drawMatrix.value[1][3] = local_20[0].y;
    object->m_drawMatrix.value[2][3] = local_20[0].z;
}
