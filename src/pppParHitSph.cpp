#include "ffcc/pppParHitSph.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

static const float kPppParHitSphZero = 0.0f;

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
void pppParHitSph(_pppPObject* pObject, ParHitSphParams* params)
{
    Vec hitVector;
    Vec origin;
    Vec debugPos;
    Mtx sphereMtx;
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor debugColor;
    _pppMngSt* pppMngSt = (_pppMngSt*)ppvMng;
    float radius;

    PSVECSubtract(&ppvMng->m_position, ParHitSphPreviousPosition(ppvMng), &hitVector);
    origin.x = ppvMng->m_matrix.value[0][3];
    origin.y = ppvMng->m_matrix.value[1][3];
    origin.z = ppvMng->m_matrix.value[2][3];
    radius = pppMngSt->m_hitScale * params->m_radiusScale;

    if (((kPppParHitSphZero == hitVector.x) && (kPppParHitSphZero == hitVector.y)) &&
        (kPppParHitSphZero == hitVector.z)) {
        pppHitCylinderSendSystem(pppMngSt, &origin, &hitVector, radius, kPppParHitSphZero);
    } else {
        pppHitCylinderSendSystem(pppMngSt, &origin, &hitVector, radius, params->m_cylinderScale);
    }

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
