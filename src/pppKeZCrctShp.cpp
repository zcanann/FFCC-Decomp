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

    pppGetRowVector(pObject->m_localMatrix, rowX, rowY, rowZ, rowPos);

    pppScaleVector(scaledX, rowX, pppMngStPtr->m_scale.x);
    pppScaleVector(scaledY, rowY, pppMngStPtr->m_scale.y);
    pppScaleVector(scaledZ, rowZ, pppMngStPtr->m_scale.z);

    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    pppCopyVector(transformedPos, rowPos);

    float scaledPosX = transformedPos.x * *(float*)(param2 + 0x18);
    float scaledPosY = transformedPos.y * *(float*)(param2 + 0x1c);
    float scaledPosZ = transformedPos.z * *(float*)(param2 + 0x20);

    u8 mode = *(u8*)(param2 + 0x28);
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
        float offsetPosX = scaledPosX + *(float*)(param2 + 8);
        float offsetPosY = scaledPosY + *(float*)(param2 + 0xc);
        float offsetPosZ = scaledPosZ + *(float*)(param2 + 0x10);

        worldMatrixB = *(pppFMATRIX*)&ppvWorldMatrix;
        transformedPos.x = offsetPosX;
        transformedPos.y = offsetPosY;
        transformedPos.z = offsetPosZ;
        pppApplyMatrix(transformedPos, worldMatrixB, transformedPos);
    } else if (mode < 3) {
        managerMatrix = pppMngStPtr->m_matrix;
        pppApplyMatrix(zeroVec, managerMatrix, transformedPos);

        float cameraPosX = *(float*)(param2 + 8) * pppMngStPtr->m_scale.x + zeroVec.x;
        float cameraPosY = *(float*)(param2 + 0xc) * pppMngStPtr->m_scale.y + zeroVec.y;
        float cameraPosZ = *(float*)(param2 + 0x10) * pppMngStPtr->m_scale.z + zeroVec.z;

        cameraMatrix = *(pppFMATRIX*)&ppvCameraMatrix0;
        zeroVec.x = cameraPosX;
        zeroVec.y = cameraPosY;
        zeroVec.z = cameraPosZ;
        pppApplyMatrix(zeroVec, cameraMatrix, zeroVec);
    }
}
