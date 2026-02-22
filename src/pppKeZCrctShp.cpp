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
    float scaledPosX;
    float scaledPosY;
    float scaledPosZ;
    u8 mode;

    pppGetRowVector(*(pppFMATRIX*)((char*)pObject + 0x10), rowX, rowY, rowZ, rowPos);
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
        Vec modePos;
        modePos.x = scaledPosX;
        modePos.y = scaledPosY;
        modePos.z = scaledPosZ;
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvWorldMatrix, modePos);
    } else if (mode == 0) {
        float offsetPosX;
        float offsetPosY;
        float offsetPosZ;
        Vec offsetPos;

        offsetPosX = scaledPosX + *(float*)(param2 + 8);
        offsetPosY = scaledPosY + *(float*)(param2 + 0xc);
        offsetPosZ = scaledPosZ + *(float*)(param2 + 0x10);

        transformedPos.x = offsetPosX;
        transformedPos.y = offsetPosY;
        transformedPos.z = offsetPosZ;
        offsetPos.x = offsetPosX;
        offsetPos.y = offsetPosY;
        offsetPos.z = offsetPosZ;
        pppApplyMatrix(transformedPos, *(pppFMATRIX*)&ppvWorldMatrix, offsetPos);
    } else if (mode < 3) {
        Vec modePos;
        float cameraPosX;
        float cameraPosY;
        float cameraPosZ;

        modePos.x = scaledPosX;
        modePos.y = scaledPosY;
        modePos.z = scaledPosZ;
        pppApplyMatrix(zeroVec, pppMngStPtr->m_matrix, modePos);
        cameraPosX = *(float*)(param2 + 8) * pppMngStPtr->m_scale.x + zeroVec.x;
        cameraPosY = *(float*)(param2 + 0xc) * pppMngStPtr->m_scale.y + zeroVec.y;
        cameraPosZ = *(float*)(param2 + 0x10) * pppMngStPtr->m_scale.z + zeroVec.z;

        zeroVec.x = cameraPosX;
        zeroVec.y = cameraPosY;
        zeroVec.z = cameraPosZ;
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvCameraMatrix0, zeroVec);
    }
}
