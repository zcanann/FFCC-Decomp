#include "ffcc/pppParHitSph.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
static const float kPppParHitSphZero = 0.0f;
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static inline Vec* ParHitSphPreviousPosition(_pppMngSt* mng)
{
    return &mng->UserPosition();
}

/*
 * --INFO--
 * PAL Address: 80093d04
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSph(_pppPObject* param_1, ParHitSphParams* params)
{
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    Mtx sphereMtx;
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor local_a8;
    _pppMngSt* pppMngSt = (_pppMngSt*)ppvMng;
    float radius;

    PSVECSubtract(&ppvMng->m_position, ParHitSphPreviousPosition(ppvMng), &local_88);
    local_94.x = ppvMng->m_matrix.value[0][3];
    local_94.y = ppvMng->m_matrix.value[1][3];
    local_94.z = ppvMng->m_matrix.value[2][3];
    radius = pppMngSt->m_previousPosition.z * params->m_radiusScale;

    if (((kPppParHitSphZero == local_88.x) && (kPppParHitSphZero == local_88.y)) &&
        (kPppParHitSphZero == local_88.z)) {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, kPppParHitSphZero);
    } else {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, params->m_cylinderScale);
    }

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
