#include "ffcc/pppDrawMatrixFront.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>


/*
 * --INFO--
 * PAL Address: 0x8006a584
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFront(_pppPObject* object, pppNoStep*, _pppCtrlTable*)
{
    Vec localPos;

    PSMTXScaleApply(
        object->m_localMatrix.value,
        object->m_drawMatrix.value,
        ppvMng->m_scale.x,
        ppvMng->m_scale.y,
        ppvMng->m_scale.z
    );

    localPos.x = object->m_localMatrix.value[0][3];
    localPos.y = object->m_localMatrix.value[1][3];
    localPos.z = object->m_localMatrix.value[2][3];

    PSMTXMultVec(ppvWorldMatrix, &localPos, &localPos);

    object->m_drawMatrix.value[0][3] = localPos.x;
    object->m_drawMatrix.value[1][3] = localPos.y;
    object->m_drawMatrix.value[2][3] = localPos.z;
}
