#include "ffcc/pppKeDMat.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x80095854
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject, void*, _pppCtrlTable* ctrlTable)
{
    int targetOffset = ctrlTable->m_serializedDataOffsets[1];
    pppFMATRIX* targetMatrix = (pppFMATRIX*)(pObject->m_workArea + targetOffset);

    pppMulMatrix(pObject->m_drawMatrix, *(pppFMATRIX*)&ppvWorldMatrix, pObject->m_localMatrix);
    pppCopyMatrix(*targetMatrix, pObject->m_drawMatrix);
}
