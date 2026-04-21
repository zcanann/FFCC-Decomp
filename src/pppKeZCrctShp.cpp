#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

struct pppKeZCrctShpObject {
    char _pad00[0x10];
    pppFMATRIX m_localMatrix;
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
    Vec rowX;
    Vec rowY;
    Vec rowZ;
    Vec rowPos;
    Vec scaledX;
    Vec scaledY;
    Vec scaledZ;
    Vec transformedPos;
    Vec zeroVec;
    pppFMATRIX transformMatrix;
    u8 mode;

    (void)ctrlTable;

    pppGetRowVector(((pppKeZCrctShpObject*)object)->m_localMatrix, rowX, rowY, rowZ, rowPos);
    pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
    pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
    pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);

    zeroVec.x = 16384.0f;
    zeroVec.y = 16384.0f;
    zeroVec.z = 16384.0f;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    pppCopyVector(transformedPos, rowPos);
    transformedPos.x *= stepData->m_positionScale.x;
    transformedPos.y *= stepData->m_positionScale.y;
    transformedPos.z *= stepData->m_positionScale.z;

    mode = stepData->m_mode;

    if (mode == 0) {
        transformedPos.x += stepData->m_offset.x;
        transformedPos.y += stepData->m_offset.y;
        transformedPos.z += stepData->m_offset.z;
        pppApplyMatrix(transformedPos, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);

        transformMatrix.value[0][3] = transformedPos.x;
        transformMatrix.value[1][3] = transformedPos.y;
        transformMatrix.value[2][3] = transformedPos.z;
    } else if (mode == 1) {
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
    } else if (mode == 2) {
        pppApplyMatrix(zeroVec, pppMngStPtr->m_matrix, transformedPos);
        zeroVec.x += stepData->m_offset.x * pppMngStPtr->m_scale.x;
        zeroVec.y += stepData->m_offset.y * pppMngStPtr->m_scale.y;
        zeroVec.z += stepData->m_offset.z * pppMngStPtr->m_scale.z;
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvCameraMatrix02, zeroVec);

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
    }
}
