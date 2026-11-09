#include "global.h"
#include "ffcc/pppKeDMat.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x8008ed4c
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject, pppNoStep*, _pppCtrlTable* ctrlTable)
{
    pppFMATRIX* targetMatrix = (pppFMATRIX*)(
        pObject->m_workArea + ctrlTable->m_serializedDataOffsets[1]);

    pppMulMatrix(pObject->m_drawMatrix, *(pppFMATRIX*)&ppvWorldMatrix, pObject->m_localMatrix);
    pppCopyMatrix(*targetMatrix, pObject->m_drawMatrix);
}
