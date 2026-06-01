#include "ffcc/pppDrawMatrixWood.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"


/*
 * --INFO--
 * PAL Address: 0x8008abc0
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixWood(_pppPObject* object, void*, _pppCtrlTable*) {
    PSMTXScaleApply(
        object->m_localMatrix.value,
        object->m_drawMatrix.value,
        ppvMng->m_scale.x,
        ppvMng->m_scale.y,
        ppvMng->m_scale.z
    );

    object->m_drawMatrix.value[0][3] = object->m_localMatrix.value[0][3];
    object->m_drawMatrix.value[1][3] = object->m_localMatrix.value[1][3];
    object->m_drawMatrix.value[2][3] = object->m_localMatrix.value[2][3];

    PSMTXConcat(ppvWorldMatrixWood, object->m_drawMatrix.value, object->m_drawMatrix.value);
}

