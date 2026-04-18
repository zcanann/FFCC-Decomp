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
    Vec branchPos;
    Vec zeroVec;
    pppFMATRIX cameraMatrix;
    pppFMATRIX managerMatrix;
    pppFMATRIX worldMatrixMode1;
    pppFMATRIX worldMatrixMode0;
    pppFMATRIX transformMatrix;
    const f32 zero = 0.0f;

    (void)ctrlTable;

    pppGetRowVector(((pppKeZCrctShpObject*)object)->m_localMatrix, rowX, rowY, rowZ, rowPos);
    pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
    pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
    pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);

    zeroVec.x = zero;
    zeroVec.y = zero;
    zeroVec.z = zero;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    pppCopyVector(transformedPos, rowPos);
    transformedPos.x *= stepData->m_positionScale.x;
    transformedPos.y *= stepData->m_positionScale.y;
    transformedPos.z *= stepData->m_positionScale.z;

    if (stepData->m_mode == 0) {
        branchPos.x = transformedPos.x + stepData->m_offset.x;
        branchPos.y = transformedPos.y + stepData->m_offset.y;
        branchPos.z = transformedPos.z + stepData->m_offset.z;
        worldMatrixMode0 = *(pppFMATRIX*)&ppvWorldMatrix;
        pppApplyMatrix(transformedPos, worldMatrixMode0, branchPos);

        transformMatrix.value[0][3] = transformedPos.x;
        transformMatrix.value[1][3] = transformedPos.y;
        transformMatrix.value[2][3] = transformedPos.z;
    } else if (stepData->m_mode == 1) {
        worldMatrixMode1 = *(pppFMATRIX*)&ppvWorldMatrix;
        pppApplyMatrix(zeroVec, worldMatrixMode1, transformedPos);

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
    } else if (stepData->m_mode == 2) {
        managerMatrix = pppMngStPtr->m_matrix;
        pppApplyMatrix(zeroVec, managerMatrix, transformedPos);
        branchPos.x = stepData->m_offset.x * pppMngStPtr->m_scale.x + zeroVec.x;
        branchPos.y = stepData->m_offset.y * pppMngStPtr->m_scale.y + zeroVec.y;
        branchPos.z = stepData->m_offset.z * pppMngStPtr->m_scale.z + zeroVec.z;
        cameraMatrix = *(pppFMATRIX*)&ppvCameraMatrix02;
        pppApplyMatrix(zeroVec, cameraMatrix, branchPos);

        transformMatrix.value[0][3] = zeroVec.x;
        transformMatrix.value[1][3] = zeroVec.y;
        transformMatrix.value[2][3] = zeroVec.z;
    }
}
