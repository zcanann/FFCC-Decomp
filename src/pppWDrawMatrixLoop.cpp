#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800c4dd8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixLoop(_pppPObject* object, void*, _pppCtrlTable*)
{
    PSMTXConcat(ppvCameraMatrix, object->m_localMatrix.value, object->m_drawMatrix.value);

    PSVECScale((Vec*)object->m_drawMatrix.value[0], (Vec*)object->m_drawMatrix.value[0], ppvMng->m_scale.x);
    PSVECScale((Vec*)object->m_drawMatrix.value[1], (Vec*)object->m_drawMatrix.value[1], ppvMng->m_scale.y);
    PSVECScale((Vec*)object->m_drawMatrix.value[2], (Vec*)object->m_drawMatrix.value[2], ppvMng->m_scale.z);
}
