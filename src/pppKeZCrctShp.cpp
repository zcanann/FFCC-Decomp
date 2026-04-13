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
    float offsetScaledX;
    float offsetScaledY;
    float offsetScaledZ;
    float rotatedOffsetX;
    float rotatedOffsetY;
    float rotatedOffsetZ;
    float scaledPosX;
    float scaledPosY;
    float scaledPosZ;
    float scaledRowZ_X;
    float scaledRowZ_Y;
    float scaledRowZ_Z;
    Vec rowPosCopy;
    float scaledRowY_X;
    float scaledRowY_Y;
    float scaledRowY_Z;
    float scaledRowX_X;
    float scaledRowX_Y;
    float scaledRowX_Z;
    Vec rotatedPos;
    Vec scaledRowZ;
    Vec scaledRowY;
    Vec scaledRowX;
    Vec rowPos;
    Vec rowZ;
    Vec rowY;
    Vec rowX;
    Vec transformedPos;
    pppFMATRIX cameraMatrix;
    pppFMATRIX mngMatrix;
    pppFMATRIX worldMatrix;
    pppFMATRIX worldMatrixWithOffset;
    pppFMATRIX transformMatrix;
    u8 mode;

    (void)ctrlTable;

    pppGetRowVector(((pppKeZCrctShpObject*)object)->m_localMatrix, rowX, rowY, rowZ, rowPos);

    scaledRowX_X = rowX.x;
    scaledRowX_Y = rowX.y;
    scaledRowX_Z = rowX.z;
    pppScaleVector(scaledRowX, rowX, pppMngStPtr->m_scale.x);

    scaledRowY_X = rowY.x;
    scaledRowY_Y = rowY.y;
    scaledRowY_Z = rowY.z;
    pppScaleVector(scaledRowY, rowY, pppMngStPtr->m_scale.y);

    scaledRowZ_X = rowZ.x;
    scaledRowZ_Y = rowZ.y;
    scaledRowZ_Z = rowZ.z;
    pppScaleVector(scaledRowZ, rowZ, pppMngStPtr->m_scale.z);

    rotatedPos.z = 0.0f;
    rotatedPos.y = 0.0f;
    rotatedPos.x = 0.0f;
    pppSetRowVector(transformMatrix, scaledRowX, scaledRowY, scaledRowZ, rotatedPos);

    rowPosCopy.x = rowPos.x;
    rowPosCopy.y = rowPos.y;
    rowPosCopy.z = rowPos.z;
    pppCopyVector(transformedPos, rowPosCopy);

    scaledPosX = transformedPos.x * stepData->m_positionScale.x;
    scaledPosY = transformedPos.y * stepData->m_positionScale.y;
    scaledPosZ = transformedPos.z * stepData->m_positionScale.z;

    mode = stepData->m_mode;
    transformedPos.x = scaledPosX;
    transformedPos.y = scaledPosY;
    transformedPos.z = scaledPosZ;

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

        rotatedOffsetX = scaledPosX;
        rotatedOffsetY = scaledPosY;
        rotatedOffsetZ = scaledPosZ;
        pppApplyMatrix(rotatedPos, worldMatrix, transformedPos);
        transformMatrix.value[0][3] = rotatedPos.x + stepData->m_offset.x;
        transformMatrix.value[1][3] = rotatedPos.y + stepData->m_offset.y;
        transformMatrix.value[2][3] = rotatedPos.z + stepData->m_offset.z;
    } else if (mode == 0) {
        offsetScaledX = scaledPosX + stepData->m_offset.x;
        offsetScaledY = scaledPosY + stepData->m_offset.y;
        offsetScaledZ = scaledPosZ + stepData->m_offset.z;

        worldMatrixWithOffset.value[0][0] = ppvWorldMatrix[0][0];
        worldMatrixWithOffset.value[0][1] = ppvWorldMatrix[0][1];
        worldMatrixWithOffset.value[0][2] = ppvWorldMatrix[0][2];
        worldMatrixWithOffset.value[0][3] = ppvWorldMatrix[0][3];
        worldMatrixWithOffset.value[1][0] = ppvWorldMatrix[1][0];
        worldMatrixWithOffset.value[1][1] = ppvWorldMatrix[1][1];
        worldMatrixWithOffset.value[1][2] = ppvWorldMatrix[1][2];
        worldMatrixWithOffset.value[1][3] = ppvWorldMatrix[1][3];
        worldMatrixWithOffset.value[2][0] = ppvWorldMatrix[2][0];
        worldMatrixWithOffset.value[2][1] = ppvWorldMatrix[2][1];
        worldMatrixWithOffset.value[2][2] = ppvWorldMatrix[2][2];
        worldMatrixWithOffset.value[2][3] = ppvWorldMatrix[2][3];

        transformedPos.x = offsetScaledX;
        transformedPos.y = offsetScaledY;
        transformedPos.z = offsetScaledZ;
        pppApplyMatrix(transformedPos, worldMatrixWithOffset, transformedPos);
        transformMatrix.value[0][3] = transformedPos.x;
        transformMatrix.value[1][3] = transformedPos.y;
        transformMatrix.value[2][3] = transformedPos.z;
    } else if (mode < 3) {
        mngMatrix.value[0][0] = pppMngStPtr->m_matrix.value[0][0];
        mngMatrix.value[0][1] = pppMngStPtr->m_matrix.value[0][1];
        mngMatrix.value[0][2] = pppMngStPtr->m_matrix.value[0][2];
        mngMatrix.value[0][3] = pppMngStPtr->m_matrix.value[0][3];
        mngMatrix.value[1][0] = pppMngStPtr->m_matrix.value[1][0];
        mngMatrix.value[1][1] = pppMngStPtr->m_matrix.value[1][1];
        mngMatrix.value[1][2] = pppMngStPtr->m_matrix.value[1][2];
        mngMatrix.value[1][3] = pppMngStPtr->m_matrix.value[1][3];
        mngMatrix.value[2][0] = pppMngStPtr->m_matrix.value[2][0];
        mngMatrix.value[2][1] = pppMngStPtr->m_matrix.value[2][1];
        mngMatrix.value[2][2] = pppMngStPtr->m_matrix.value[2][2];
        mngMatrix.value[2][3] = pppMngStPtr->m_matrix.value[2][3];

        pppApplyMatrix(rotatedPos, mngMatrix, transformedPos);

        offsetScaledX = stepData->m_offset.x * pppMngStPtr->m_scale.x + rotatedPos.x;
        offsetScaledY = stepData->m_offset.y * pppMngStPtr->m_scale.y + rotatedPos.y;
        offsetScaledZ = stepData->m_offset.z * pppMngStPtr->m_scale.z + rotatedPos.z;

        cameraMatrix.value[0][0] = ppvCameraMatrix02[0][0];
        cameraMatrix.value[0][1] = ppvCameraMatrix02[0][1];
        cameraMatrix.value[0][2] = ppvCameraMatrix02[0][2];
        cameraMatrix.value[0][3] = ppvCameraMatrix02[0][3];
        cameraMatrix.value[1][0] = ppvCameraMatrix02[1][0];
        cameraMatrix.value[1][1] = ppvCameraMatrix02[1][1];
        cameraMatrix.value[1][2] = ppvCameraMatrix02[1][2];
        cameraMatrix.value[1][3] = ppvCameraMatrix02[1][3];
        cameraMatrix.value[2][0] = ppvCameraMatrix02[2][0];
        cameraMatrix.value[2][1] = ppvCameraMatrix02[2][1];
        cameraMatrix.value[2][2] = ppvCameraMatrix02[2][2];
        cameraMatrix.value[2][3] = ppvCameraMatrix02[2][3];

        rotatedPos.x = offsetScaledX;
        rotatedPos.y = offsetScaledY;
        rotatedPos.z = offsetScaledZ;
        pppApplyMatrix(rotatedPos, cameraMatrix, rotatedPos);
        transformMatrix.value[0][3] = rotatedPos.x;
        transformMatrix.value[1][3] = rotatedPos.y;
        transformMatrix.value[2][3] = rotatedPos.z;
    }
}
