#include "global.h"
#include "ffcc/pppKeDMat.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"

struct KeDMatDataOffsets {
    s32 _unused0;
    s32 m_targetMatrixOffset;
};

STATIC_ASSERT(offsetof(KeDMatDataOffsets, m_targetMatrixOffset) == 0x4);

static inline KeDMatDataOffsets* GetKeDMatDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<KeDMatDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline pppFMATRIX* GetKeDMatTargetMatrix(_pppPObject* pObject, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<pppFMATRIX*>(
        pObject->m_workArea + GetKeDMatDataOffsets(ctrlTable)->m_targetMatrixOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80095854
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeDMatDraw(_pppPObject* pObject, pppNoStep*, _pppCtrlTable* ctrlTable)
{
    pppFMATRIX* targetMatrix = GetKeDMatTargetMatrix(pObject, ctrlTable);

    pppMulMatrix(pObject->m_drawMatrix, *(pppFMATRIX*)&ppvWorldMatrix, pObject->m_localMatrix);
    pppCopyMatrix(*targetMatrix, pObject->m_drawMatrix);
}
