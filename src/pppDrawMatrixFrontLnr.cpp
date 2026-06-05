#include "ffcc/pppDrawMatrixFrontLnr.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800d1968
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixFrontLnr(_pppPObject* object, pppNoStep*, _pppCtrlTable*)
{
    Vec local_18;
    _pppMngSt* mng = (_pppMngSt*)ppvMng;
    
    PSMTXScaleApply(
        object->m_localMatrix.value,
        object->m_drawMatrix.value,
        mng->m_scale.x,
        mng->m_scale.y,
        mng->m_scale.z
    );
    
    local_18.x = object->m_localMatrix.value[0][3];
    local_18.y = object->m_localMatrix.value[1][3];
    local_18.z = object->m_localMatrix.value[2][3];
    
    PSMTXMultVec(ppvCameraMatrix, &local_18, &local_18);
    
    object->m_drawMatrix.value[0][3] = local_18.x;
    object->m_drawMatrix.value[1][3] = local_18.y;
    object->m_drawMatrix.value[2][3] = local_18.z;
}

