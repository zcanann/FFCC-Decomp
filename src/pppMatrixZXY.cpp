#include "ffcc/pppMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065898
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixZXY(_pppPObject* target, void* unused, _pppCtrlTable* param)
{
    (void)unused;
    int* offsets = param->m_serializedDataOffsets;
    u32 translationOffset = offsets[0];
    u32 scaleOffset = offsets[2];
    u32 angleOffset = offsets[1];
    f32* translation = (f32*)(target->m_workArea + translationOffset);
    f32* scale = (f32*)(target->m_workArea + scaleOffset);
    pppIVECTOR4* angle = (pppIVECTOR4*)(target->m_workArea + angleOffset);
    Vec temp1;
    Vec temp2;
    Vec temp3;

    pppGetRotMatrixZXY(target->m_localMatrix, angle);

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
