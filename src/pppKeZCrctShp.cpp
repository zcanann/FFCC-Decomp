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
void pppKeZCrctShpDraw(_pppPObject *pObject, int param2)
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
    pppFMATRIX cameraMatrix;
    pppFMATRIX managerMatrix;
    pppFMATRIX worldMatrixA;
    pppFMATRIX worldMatrixB;
    float scaledPosX;
    float scaledPosY;
    float scaledPosZ;
    u8 mode;

    pppGetRowVector(pObject->m_localMatrix, rowX, rowY, rowZ, rowPos);
    pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
    pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
    pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);

    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);
    pppCopyVector(transformedPos, rowPos);
    scaledPosX = transformedPos.x * *(float*)(param2 + 0x18);
    scaledPosY = transformedPos.y * *(float*)(param2 + 0x1c);
    scaledPosZ = transformedPos.z * *(float*)(param2 + 0x20);
    mode = *(u8*)(param2 + 0x28);
    transformedPos.x = scaledPosX;
    transformedPos.y = scaledPosY;
    transformedPos.z = scaledPosZ;

    if (mode == 1) {
        worldMatrixA = *(pppFMATRIX*)&ppvWorldMatrix;

        Vec modePos;
        modePos.x = scaledPosX;
        modePos.y = scaledPosY;
        modePos.z = scaledPosZ;
        pppApplyMatrix(zeroVec, worldMatrixA, modePos);
    } else if (mode == 0) {
        float offsetPosX;
        float offsetPosY;
        float offsetPosZ;
        Vec offsetPos;

        offsetPosX = scaledPosX + *(float*)(param2 + 8);
        offsetPosY = scaledPosY + *(float*)(param2 + 0xc);
        offsetPosZ = scaledPosZ + *(float*)(param2 + 0x10);

        worldMatrixB = *(pppFMATRIX*)&ppvWorldMatrix;
        transformedPos.x = offsetPosX;
        transformedPos.y = offsetPosY;
        transformedPos.z = offsetPosZ;
        offsetPos.x = offsetPosX;
        offsetPos.y = offsetPosY;
        offsetPos.z = offsetPosZ;
        pppApplyMatrix(transformedPos, worldMatrixB, offsetPos);
    } else if (mode < 3) {
        Vec modePos;
        float cameraPosX;
        float cameraPosY;
        float cameraPosZ;

        managerMatrix = pppMngStPtr->m_matrix;
        modePos.x = scaledPosX;
        modePos.y = scaledPosY;
        modePos.z = scaledPosZ;
        pppApplyMatrix(zeroVec, managerMatrix, modePos);
        cameraPosX = *(float*)(param2 + 8) * pppMngStPtr->m_scale.x + zeroVec.x;
        cameraPosY = *(float*)(param2 + 0xc) * pppMngStPtr->m_scale.y + zeroVec.y;
        cameraPosZ = *(float*)(param2 + 0x10) * pppMngStPtr->m_scale.z + zeroVec.z;

        cameraMatrix = *(pppFMATRIX*)&ppvCameraMatrix0;
        zeroVec.x = cameraPosX;
        zeroVec.y = cameraPosY;
        zeroVec.z = cameraPosZ;
        pppApplyMatrix(zeroVec, cameraMatrix, zeroVec);
    }
}
