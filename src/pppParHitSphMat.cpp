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
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    Mtx sphereMtx;
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor local_a8;
    _pppMngSt* pppMngSt = (_pppMngSt*)ppvMng;
    float radius;

    local_88.z = 0.0f;
    local_88.y = 0.0f;
    local_88.x = 0.0f;

    if (step->m_useWorkPosition != 0) {
        ParHitSphMatDataOffsets* offsets = GetParHitSphMatDataOffsets(ctrlTable);
        Vec* src = (Vec*)(pObject->m_workArea + offsets->m_positionOffset);
        PSMTXMultVec(pppMngSt->m_matrix.value, src, &local_94);
    } else {
        local_94.x = ppvMng->m_matrix.value[0][3];
        local_94.y = ppvMng->m_matrix.value[1][3];
        local_94.z = ppvMng->m_matrix.value[2][3];
        ParHitSphMatDataOffsets* offsets = GetParHitSphMatDataOffsets(ctrlTable);
        Vec* src = (Vec*)(pObject->m_workArea + offsets->m_positionOffset);
        local_94.x += src->x;
        local_94.y += src->y;
        local_94.z += src->z;
    }

    if (step->m_height != 0.0f) {
        PSVECSubtract(&pppMngSt->m_position, ParHitSphMatPreviousPosition(pppMngSt), &local_88);
    }

    radius = pppMngSt->m_hitScale * step->m_radiusScale;
    pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, step->m_height);

    if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
        local_a8.r = 0xFF;
        local_a8.g = 0xFF;
        local_a8.b = 0xFF;
        local_a8.a = 0xFF;
        PSMTXIdentity(cameraMtx);
        PSMTXIdentity(sphereMtx);
        sphereMtx[0][0] = radius;
        sphereMtx[1][1] = radius;
        sphereMtx[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix, cameraMtx, cameraMtx);
        PSMTXMultVec(cameraMtx, &local_94, &local_a0);
        sphereMtx[0][3] = local_a0.x;
        sphereMtx[1][3] = local_a0.y;
        sphereMtx[2][3] = local_a0.z;
        Graphic.DrawSphere(sphereMtx, local_a8);
    }
}
