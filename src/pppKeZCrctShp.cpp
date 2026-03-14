#include "ffcc/pppKeZCrctShp.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

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
    Vec zeroVec;
    Vec transformedPos;
    pppFMATRIX transformMatrix;
    pppFMATRIX worldMatrix;
    pppFMATRIX worldMatrix2;
    pppFMATRIX ownerMatrix;
    pppFMATRIX cameraMatrix;
    Vec rowXCopy;
    Vec rowYCopy;
    Vec rowZCopy;
    Vec posCopy;
    Vec transformedPosCopy;
    f32 posX;
    f32 posY;
    f32 posZ;
    s32 mode;

    (void)ctrlTable;

    pppGetRowVector(*(pppFMATRIX*)((char*)object + 0x10), rowX, rowY, rowZ, rowPos);
    rowXCopy = rowX;
    pppScaleVector(scaledX, rowXCopy, pppMngStPtr->m_scale.x);
    rowYCopy = rowY;
    pppScaleVector(scaledY, rowYCopy, pppMngStPtr->m_scale.y);
    rowZCopy = rowZ;
    pppScaleVector(scaledZ, rowZCopy, pppMngStPtr->m_scale.z);

    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    posCopy = rowPos;
    pppCopyVector(transformedPos, posCopy);
    posX = transformedPos.x * stepData->m_positionScale.x;
    posY = transformedPos.y * stepData->m_positionScale.y;
    posZ = transformedPos.z * stepData->m_positionScale.z;
    transformedPos.x = posX;
    transformedPos.y = posY;
    transformedPos.z = posZ;

    mode = stepData->m_mode;
    if (mode == 1) {
        worldMatrix.value[0][0] = ppvWorldMatrix[0][0];
        worldMatrix.value[0][1] = ppvWorldMatrix[0][1];
        worldMatrix.value[0][2] = ppvWorldMatrix[0][2];
        worldMatrix.value[0][3] = ppvWorldMatrix[0][3];
        worldMatrix.value[1][0] = ppvWorldMatrix[1][0];
        worldMatrix.value[1][1] = ppvWorldMatrix[1][1];
        worldMatrix.value[1][2] = ppvWorldMatrix[1][2];
        worldMatrix.value[1][3] = ppvWorldMatrix[1][3];
        worldMatrix.value[2][0] = ppvWorldMatrix[2][0];
        worldMatrix.value[2][1] = ppvWorldMatrix[2][1];
        worldMatrix.value[2][2] = ppvWorldMatrix[2][2];
        worldMatrix.value[2][3] = ppvWorldMatrix[2][3];
        transformedPosCopy.x = posX;
        transformedPosCopy.y = posY;
        transformedPosCopy.z = posZ;
        pppApplyMatrix(zeroVec, worldMatrix, transformedPosCopy);
    } else if (mode == 0) {
        posX = posX + stepData->m_offset.x;
        posY = posY + stepData->m_offset.y;
        posZ = posZ + stepData->m_offset.z;
        worldMatrix2.value[0][0] = ppvWorldMatrix[0][0];
        worldMatrix2.value[0][1] = ppvWorldMatrix[0][1];
        worldMatrix2.value[0][2] = ppvWorldMatrix[0][2];
        worldMatrix2.value[0][3] = ppvWorldMatrix[0][3];
        worldMatrix2.value[1][0] = ppvWorldMatrix[1][0];
        worldMatrix2.value[1][1] = ppvWorldMatrix[1][1];
        worldMatrix2.value[1][2] = ppvWorldMatrix[1][2];
        worldMatrix2.value[1][3] = ppvWorldMatrix[1][3];
        worldMatrix2.value[2][0] = ppvWorldMatrix[2][0];
        worldMatrix2.value[2][1] = ppvWorldMatrix[2][1];
        worldMatrix2.value[2][2] = ppvWorldMatrix[2][2];
        worldMatrix2.value[2][3] = ppvWorldMatrix[2][3];
        transformedPos.x = posX;
        transformedPos.y = posY;
        transformedPos.z = posZ;
        transformedPosCopy = transformedPos;
        pppApplyMatrix(transformedPos, worldMatrix2, transformedPosCopy);
    } else if (mode < 3) {
        ownerMatrix.value[0][0] = pppMngStPtr->m_matrix.value[0][0];
        ownerMatrix.value[0][1] = pppMngStPtr->m_matrix.value[0][1];
        ownerMatrix.value[0][2] = pppMngStPtr->m_matrix.value[0][2];
        ownerMatrix.value[0][3] = pppMngStPtr->m_matrix.value[0][3];
        ownerMatrix.value[1][0] = pppMngStPtr->m_matrix.value[1][0];
        ownerMatrix.value[1][1] = pppMngStPtr->m_matrix.value[1][1];
        ownerMatrix.value[1][2] = pppMngStPtr->m_matrix.value[1][2];
        ownerMatrix.value[1][3] = pppMngStPtr->m_matrix.value[1][3];
        ownerMatrix.value[2][0] = pppMngStPtr->m_matrix.value[2][0];
        ownerMatrix.value[2][1] = pppMngStPtr->m_matrix.value[2][1];
        ownerMatrix.value[2][2] = pppMngStPtr->m_matrix.value[2][2];
        ownerMatrix.value[2][3] = pppMngStPtr->m_matrix.value[2][3];
        transformedPosCopy.x = posX;
        transformedPosCopy.y = posY;
        transformedPosCopy.z = posZ;
        pppApplyMatrix(zeroVec, ownerMatrix, transformedPosCopy);

        posX = stepData->m_offset.x * pppMngStPtr->m_scale.x + zeroVec.x;
        posY = stepData->m_offset.y * pppMngStPtr->m_scale.y + zeroVec.y;
        posZ = stepData->m_offset.z * pppMngStPtr->m_scale.z + zeroVec.z;
        cameraMatrix.value[0][0] = ppvCameraMatrix0[0][0];
        cameraMatrix.value[0][1] = ppvCameraMatrix0[0][1];
        cameraMatrix.value[0][2] = ppvCameraMatrix0[0][2];
        cameraMatrix.value[0][3] = ppvCameraMatrix0[0][3];
        cameraMatrix.value[1][0] = ppvCameraMatrix0[1][0];
        cameraMatrix.value[1][1] = ppvCameraMatrix0[1][1];
        cameraMatrix.value[1][2] = ppvCameraMatrix0[1][2];
        cameraMatrix.value[1][3] = ppvCameraMatrix0[1][3];
        cameraMatrix.value[2][0] = ppvCameraMatrix0[2][0];
        cameraMatrix.value[2][1] = ppvCameraMatrix0[2][1];
        cameraMatrix.value[2][2] = ppvCameraMatrix0[2][2];
        cameraMatrix.value[2][3] = ppvCameraMatrix0[2][3];
        zeroVec.x = posX;
        zeroVec.y = posY;
        zeroVec.z = posZ;
        transformedPosCopy = zeroVec;
        pppApplyMatrix(zeroVec, cameraMatrix, transformedPosCopy);
    }
}
