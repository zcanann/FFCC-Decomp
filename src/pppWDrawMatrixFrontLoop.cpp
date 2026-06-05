#include "ffcc/pppWDrawMatrixFrontLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800c4f50
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixFrontLoop(struct _pppPObject* object, pppNoStep*, struct _pppCtrlTable*)
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

    PSMTXMultVec(ppvCameraMatrix, &localPos, &localPos);

    object->m_drawMatrix.value[0][3] = localPos.x;
    object->m_drawMatrix.value[1][3] = localPos.y;
    object->m_drawMatrix.value[2][3] = localPos.z;
}
