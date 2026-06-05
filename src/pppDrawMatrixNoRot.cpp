#include "ffcc/pppDrawMatrixNoRot.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x8008ac30
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixNoRot(struct _pppPObject* object, pppNoStep*, struct _pppCtrlTable*)
{
    PSMTXScaleApply(
        object->m_localMatrix.value,
        object->m_drawMatrix.value,
        (((_pppMngSt*)ppvMng)->m_scale).x,
        (((_pppMngSt*)ppvMng)->m_scale).y,
        (((_pppMngSt*)ppvMng)->m_scale).z
    );
    object->m_drawMatrix.value[0][3] =
        object->m_localMatrix.value[0][3] * (((_pppMngSt*)ppvMng)->m_scale).x +
        ppvWorldMatrix[0][3];
    object->m_drawMatrix.value[1][3] =
        object->m_localMatrix.value[1][3] * (((_pppMngSt*)ppvMng)->m_scale).y + ppvWorldMatrix[1][3];
    object->m_drawMatrix.value[2][3] =
        object->m_localMatrix.value[2][3] * (((_pppMngSt*)ppvMng)->m_scale).z + ppvWorldMatrix[2][3];
}
