#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

extern const float FLOAT_803304F8;
extern const float kPppKeShpTail2XAlphaScale = 16384.0f;

struct pppKeZCrctShpObject {
    u8 _pad0[0xc];
    _pppPObject m_object;
};

/*
 * --INFO--
 * PAL Address: 0x8008821c
 * PAL Size: 1148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeZCrctShpDraw(_pppPObject* object, pppKeZCrctShpStep* stepData, _pppCtrlTable* ctrlTable)
{
    Vec transformedPos ATTRIBUTE_ALIGN(8);
    Vec rowX ATTRIBUTE_ALIGN(8);
    Vec rowY ATTRIBUTE_ALIGN(8);
    Vec rowZ ATTRIBUTE_ALIGN(8);
    Vec rowPos ATTRIBUTE_ALIGN(8);
    Vec scaledX ATTRIBUTE_ALIGN(8);
    Vec scaledY ATTRIBUTE_ALIGN(8);
    Vec scaledZ ATTRIBUTE_ALIGN(8);
    Vec zeroVec ATTRIBUTE_ALIGN(8);
    pppFMATRIX transformMatrix;
    u8 mode;

    (void)ctrlTable;

    pppGetRowVector(((pppKeZCrctShpObject*)object)->m_object.m_localMatrix, rowX, rowY, rowZ, rowPos);
    pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
    pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
    pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);

    zeroVec.z = FLOAT_803304F8;
    zeroVec.y = FLOAT_803304F8;
    zeroVec.x = FLOAT_803304F8;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    pppCopyVector(transformedPos, rowPos);
    transformedPos.x *= stepData->m_positionScale.x;
    transformedPos.y *= stepData->m_positionScale.y;
    transformedPos.z *= stepData->m_positionScale.z;

    mode = stepData->m_mode;

    switch (mode) {
    case 0:
        transformedPos.x += stepData->m_offset.x;
        transformedPos.y += stepData->m_offset.y;
        transformedPos.z += stepData->m_offset.z;
        pppApplyMatrix(transformedPos, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);

        transformMatrix.value[0][3] = transformedPos.x;
        transformMatrix.value[1][3] = transformedPos.y;
        transformMatrix.value[2][3] = transformedPos.z;
        break;
    case 1:
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);
        zeroVec.x += stepData->m_offset.x;
        zeroVec.y += stepData->m_offset.y;
        zeroVec.z += stepData->m_offset.z;

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
        break;
    case 2:
        pppApplyMatrix(zeroVec, pppMngStPtr->m_matrix, transformedPos);
        zeroVec.x += stepData->m_offset.x * pppMngStPtr->m_scale.x;
        zeroVec.y += stepData->m_offset.y * pppMngStPtr->m_scale.y;
        zeroVec.z += stepData->m_offset.z * pppMngStPtr->m_scale.z;
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvCameraMatrix02, zeroVec);

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
        break;
    }
}
