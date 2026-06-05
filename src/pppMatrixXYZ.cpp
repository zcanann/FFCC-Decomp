#include "ffcc/pppMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065398
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppMatrixXYZ(_pppPObject* target, pppNoStep* stepData, _pppCtrlTable* param)
{
    (void)stepData;
    int* offsets = param->m_serializedDataOffsets;
    pppIVECTOR4* angle = (pppIVECTOR4*)(target->m_workArea + offsets[1]);
    f32* translation = (f32*)(target->m_workArea + offsets[0]);
    f32* scale = (f32*)(target->m_workArea + offsets[2]);
    Vec tempVec1;
    Vec tempVec2;
    Vec tempVec3;

    pppGetRotMatrixXYZ(target->m_localMatrix, angle);

    tempVec1.x = target->m_localMatrix.value[0][0];
    tempVec1.y = target->m_localMatrix.value[1][0];
    tempVec1.z = target->m_localMatrix.value[2][0];
    PSVECScale(&tempVec1, &tempVec1, scale[0]);
    target->m_localMatrix.value[0][0] = tempVec1.x;
    target->m_localMatrix.value[1][0] = tempVec1.y;
    target->m_localMatrix.value[2][0] = tempVec1.z;

    tempVec2.x = target->m_localMatrix.value[0][1];
    tempVec2.y = target->m_localMatrix.value[1][1];
    tempVec2.z = target->m_localMatrix.value[2][1];
    PSVECScale(&tempVec2, &tempVec2, scale[1]);
    target->m_localMatrix.value[0][1] = tempVec2.x;
    target->m_localMatrix.value[1][1] = tempVec2.y;
    target->m_localMatrix.value[2][1] = tempVec2.z;

    tempVec3.x = target->m_localMatrix.value[0][2];
    tempVec3.y = target->m_localMatrix.value[1][2];
    tempVec3.z = target->m_localMatrix.value[2][2];
    PSVECScale(&tempVec3, &tempVec3, scale[2]);
    target->m_localMatrix.value[0][2] = tempVec3.x;
    target->m_localMatrix.value[1][2] = tempVec3.y;
    target->m_localMatrix.value[2][2] = tempVec3.z;

    target->m_localMatrix.value[0][3] = translation[0];
    target->m_localMatrix.value[1][3] = translation[1];
    target->m_localMatrix.value[2][3] = translation[2];
}
