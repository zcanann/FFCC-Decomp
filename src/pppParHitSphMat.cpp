#include "global.h"
#include "ffcc/pppParHitSphMat.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

STATIC_ASSERT(sizeof(ParHitSphMatDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(ParHitSphMatDataOffsets, m_positionOffset) == 0x4);

static inline ParHitSphMatDataOffsets* GetParHitSphMatDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<ParHitSphMatDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline Vec* ParHitSphMatPreviousPosition(_pppMngSt* mng)
{
    return &mng->UserPosition();
}

/*
 * --INFO--
 * PAL Address: 0x8014139c
 * PAL Size: 436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSphMat(_pppPObject* pObject, pppParHitSphMatStep* step, _pppCtrlTable* ctrlTable)
{
    Vec hitVector;
    Vec origin;
    Vec debugPos;
    Mtx sphereMtx;
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor debugColor;
    _pppMngSt* pppMngSt = (_pppMngSt*)ppvMng;
    float radius;

    hitVector.z = 0.0f;
    hitVector.y = 0.0f;
    hitVector.x = 0.0f;

    if (step->m_useWorkPosition != 0) {
        ParHitSphMatDataOffsets* offsets = GetParHitSphMatDataOffsets(ctrlTable);
        Vec* workPos = (Vec*)(pObject->m_workArea + offsets->m_positionOffset);
        PSMTXMultVec(pppMngSt->m_matrix.value, workPos, &origin);
    } else {
        origin.x = ppvMng->m_matrix.value[0][3];
        origin.y = ppvMng->m_matrix.value[1][3];
        origin.z = ppvMng->m_matrix.value[2][3];
        ParHitSphMatDataOffsets* offsets = GetParHitSphMatDataOffsets(ctrlTable);
        Vec* workPos = (Vec*)(pObject->m_workArea + offsets->m_positionOffset);
        origin.x += workPos->x;
        origin.y += workPos->y;
        origin.z += workPos->z;
    }

    if (step->m_height != 0.0f) {
        PSVECSubtract(&pppMngSt->m_position, ParHitSphMatPreviousPosition(pppMngSt), &hitVector);
    }

    radius = pppMngSt->m_hitScale * step->m_radiusScale;
    pppHitCylinderSendSystem(pppMngSt, &origin, &hitVector, radius, step->m_height);

    if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
        debugColor.r = 0xFF;
        debugColor.g = 0xFF;
        debugColor.b = 0xFF;
        debugColor.a = 0xFF;
        PSMTXIdentity(cameraMtx);
        PSMTXIdentity(sphereMtx);
        sphereMtx[0][0] = radius;
        sphereMtx[1][1] = radius;
        sphereMtx[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix, cameraMtx, cameraMtx);
        PSMTXMultVec(cameraMtx, &origin, &debugPos);
        sphereMtx[0][3] = debugPos.x;
        sphereMtx[1][3] = debugPos.y;
        sphereMtx[2][3] = debugPos.z;
        Graphic.DrawSphere(sphereMtx, debugColor);
    }
}
