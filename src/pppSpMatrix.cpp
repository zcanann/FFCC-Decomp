#include "global.h"
#include "ffcc/pppSpMatrix.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

struct SpMatrixDataOffsets
{
    s32 m_matrixOffset;
};

STATIC_ASSERT(offsetof(SpMatrixDataOffsets, m_matrixOffset) == 0x0);

static inline SpMatrixDataOffsets* GetSpMatrixDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<SpMatrixDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800d3818
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSpMatrix(_pppPObject* mtx, pppNoStep* stepData, _pppCtrlTable* data)
{
    int offset = GetSpMatrixDataOffsets(data)->m_matrixOffset;
    Mtx* mtxSrc = (Mtx*)(mtx->m_workArea + offset);
    Mtx* mtxOut = &mtx->m_localMatrix.value;

    (void)stepData;
    PSMTXConcat(*mtxSrc, *mtxOut, *mtxOut);
}
