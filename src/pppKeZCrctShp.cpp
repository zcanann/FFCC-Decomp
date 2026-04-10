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

    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    pppSetRowVector(transformMatrix, scaledX, scaledY, scaledZ, zeroVec);

    pppCopyVector(transformedPos, rowPos);
    transformedPos.x *= stepData->m_positionScale.x;
    transformedPos.y *= stepData->m_positionScale.y;
    transformedPos.z *= stepData->m_positionScale.z;

    mode = stepData->m_mode;

    if (mode == 1) {
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);
    } else if (mode == 0) {
        transformedPos.x += stepData->m_offset.x;
        transformedPos.y += stepData->m_offset.y;
        transformedPos.z += stepData->m_offset.z;
        pppApplyMatrix(transformedPos, *(pppFMATRIX*)&ppvWorldMatrix, transformedPos);
    } else if (mode < 3) {
        pppApplyMatrix(zeroVec, pppMngStPtr->m_matrix, transformedPos);
        zeroVec.x += stepData->m_offset.x * pppMngStPtr->m_scale.x;
        zeroVec.y += stepData->m_offset.y * pppMngStPtr->m_scale.y;
        zeroVec.z += stepData->m_offset.z * pppMngStPtr->m_scale.z;
        pppApplyMatrix(zeroVec, *(pppFMATRIX*)&ppvCameraMatrix02, zeroVec);
    }
}
