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
    Vec rowXCopy;
    Vec rowYCopy;
    Vec rowZCopy;
    Vec rowPosCopy;
    Vec scaledX;
    Vec scaledY;
    Vec scaledZ;
    Vec zeroVec;
    Vec transformedPos;
    pppFMATRIX transformMatrix;
    pppFMATRIX cameraMatrix;
    pppFMATRIX managerMatrix;
    pppFMATRIX worldMatrix;
    u8 mode;
    float transformedX;
    float transformedY;
    float transformedZ;
    float offsetX;
    float offsetY;
    float offsetZ;

    (void)ctrlTable;

    pppGetRowVector(((pppKeZCrctShpObject*)object)->m_localMatrix, rowX, rowY, rowZ, rowPos);
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

    rowPosCopy = rowPos;
    pppCopyVector(transformedPos, rowPosCopy);
    transformedX = transformedPos.x * stepData->m_positionScale.x;
    transformedY = transformedPos.y * stepData->m_positionScale.y;
    transformedZ = transformedPos.z * stepData->m_positionScale.z;
    transformedPos.x = transformedX;
    transformedPos.y = transformedY;
    transformedPos.z = transformedZ;

    mode = stepData->m_mode;

    if (mode == 1) {
        pppCopyMatrix(worldMatrix, *(pppFMATRIX*)&ppvWorldMatrix);
        pppApplyMatrix(zeroVec, worldMatrix, transformedPos);
    } else if (mode == 0) {
        offsetX = transformedX + stepData->m_offset.x;
        offsetY = transformedY + stepData->m_offset.y;
        offsetZ = transformedZ + stepData->m_offset.z;
        transformedPos.x = offsetX;
        transformedPos.y = offsetY;
        transformedPos.z = offsetZ;
        pppCopyMatrix(worldMatrix, *(pppFMATRIX*)&ppvWorldMatrix);
        pppApplyMatrix(transformedPos, worldMatrix, transformedPos);
    } else if (mode < 3) {
        pppCopyMatrix(managerMatrix, pppMngStPtr->m_matrix);
        pppApplyMatrix(zeroVec, managerMatrix, transformedPos);

        offsetX = stepData->m_offset.x * pppMngStPtr->m_scale.x + zeroVec.x;
        offsetY = stepData->m_offset.y * pppMngStPtr->m_scale.y + zeroVec.y;
        offsetZ = stepData->m_offset.z * pppMngStPtr->m_scale.z + zeroVec.z;

        pppCopyMatrix(cameraMatrix, *(pppFMATRIX*)&ppvCameraMatrix02);
        zeroVec.x = offsetX;
        zeroVec.y = offsetY;
        zeroVec.z = offsetZ;
        pppApplyMatrix(zeroVec, cameraMatrix, zeroVec);
    }
}
