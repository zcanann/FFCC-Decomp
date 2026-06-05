#include "ffcc/pppMatrixLoc.h"
#include "global.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

struct MatrixLocDataOffsets {
    s32 m_translationOffset;
};

STATIC_ASSERT(offsetof(MatrixLocDataOffsets, m_translationOffset) == 0x0);

static inline MatrixLocDataOffsets* GetMatrixLocDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<MatrixLocDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800652ac
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixLoc(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param)
{
    (void)stepData;

    MatrixLocDataOffsets* offsetPtr = GetMatrixLocDataOffsets(param);
    f32* posData = (f32*)(target->m_workArea + offsetPtr->m_translationOffset);

    PSMTXIdentity(target->m_localMatrix.value);
    target->m_localMatrix.value[0][3] = posData[0];
    target->m_localMatrix.value[1][3] = posData[1];
    target->m_localMatrix.value[2][3] = posData[2];
}
