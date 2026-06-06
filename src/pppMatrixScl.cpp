#include "ffcc/pppMatrixScl.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

STATIC_ASSERT(sizeof(MatrixSclDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(MatrixSclDataOffsets, m_translationOffset) == 0x0);
STATIC_ASSERT(offsetof(MatrixSclDataOffsets, m_scaleOffset) == 0x4);

static inline MatrixSclDataOffsets* GetMatrixSclDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<MatrixSclDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x8006530c
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixScl(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param)
{
    (void)stepData;

    MatrixSclDataOffsets* dataPtr = GetMatrixSclDataOffsets(param);
    u32 index1 = dataPtr->m_translationOffset;
    u32 index2 = dataPtr->m_scaleOffset;

    f32* scale1 = (f32*)(target->m_workArea + index1);
    f32* scale2 = (f32*)(target->m_workArea + index2);

    PSMTXIdentity(target->m_localMatrix.value);

    target->m_localMatrix.value[0][0] = scale2[0];
    target->m_localMatrix.value[1][1] = scale2[1];
    target->m_localMatrix.value[2][2] = scale2[2];
    target->m_localMatrix.value[0][3] = scale1[0];
    target->m_localMatrix.value[1][3] = scale1[1];
    target->m_localMatrix.value[2][3] = scale1[2];
}
