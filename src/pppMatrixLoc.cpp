#include "ffcc/pppMatrixLoc.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800652ac
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixLoc(_pppPObject* target, void* unused, _pppCtrlTable* param)
{
    (void)unused;

    int* offsetPtr = param->m_serializedDataOffsets;
    f32* posData = (f32*)(target->m_workArea + *offsetPtr);

    PSMTXIdentity(target->m_localMatrix.value);
    target->m_localMatrix.value[0][3] = posData[0];
    target->m_localMatrix.value[1][3] = posData[1];
    target->m_localMatrix.value[2][3] = posData[2];
}
