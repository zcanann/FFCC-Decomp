#include "ffcc/pppMatrixZYX.h"
#include "global.h"

#include "ffcc/pppGetRotMatrixZYX.h"
#include <dolphin/mtx.h>

STATIC_ASSERT(sizeof(MatrixZYXDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(MatrixZYXDataOffsets, m_translationOffset) == 0x0);
STATIC_ASSERT(offsetof(MatrixZYXDataOffsets, m_angleOffset) == 0x4);
STATIC_ASSERT(offsetof(MatrixZYXDataOffsets, m_scaleOffset) == 0x8);

static inline MatrixZYXDataOffsets* GetMatrixZYXDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<MatrixZYXDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800659D8
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixZYX(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param)
{
    (void)stepData;
    MatrixZYXDataOffsets* offsets = GetMatrixZYXDataOffsets(param);
    u32 translationOffset = offsets->m_translationOffset;
    u32 scaleOffset = offsets->m_scaleOffset;
    u32 angleOffset = offsets->m_angleOffset;
    f32* translation = (f32*)(target->m_workArea + translationOffset);
    f32* scale = (f32*)(target->m_workArea + scaleOffset);
    pppIVECTOR4* angle = (pppIVECTOR4*)(target->m_workArea + angleOffset);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixZYX(target->m_localMatrix, angle);

    temp1.x = target->m_localMatrix.value[0][0];
    temp1.y = target->m_localMatrix.value[1][0];
    temp1.z = target->m_localMatrix.value[2][0];
    PSVECScale(&temp1, &temp1, scale[0]);
    target->m_localMatrix.value[0][0] = temp1.x;
    target->m_localMatrix.value[1][0] = temp1.y;
    target->m_localMatrix.value[2][0] = temp1.z;

    temp2.x = target->m_localMatrix.value[0][1];
    temp2.y = target->m_localMatrix.value[1][1];
    temp2.z = target->m_localMatrix.value[2][1];
    PSVECScale(&temp2, &temp2, scale[1]);
    target->m_localMatrix.value[0][1] = temp2.x;
    target->m_localMatrix.value[1][1] = temp2.y;
    target->m_localMatrix.value[2][1] = temp2.z;

    temp3.x = target->m_localMatrix.value[0][2];
    temp3.y = target->m_localMatrix.value[1][2];
    temp3.z = target->m_localMatrix.value[2][2];
    PSVECScale(&temp3, &temp3, scale[2]);
    target->m_localMatrix.value[0][2] = temp3.x;
    target->m_localMatrix.value[1][2] = temp3.y;
    target->m_localMatrix.value[2][2] = temp3.z;

    target->m_localMatrix.value[0][3] = translation[0];
    target->m_localMatrix.value[1][3] = translation[1];
    target->m_localMatrix.value[2][3] = translation[2];
}
