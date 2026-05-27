#include "ffcc/pppParHitSph.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
extern "C" {
extern const float kPppParHitSphZero;
extern const char s_pppParHitSphWin[] = "win";
}
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 80093d04
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSph(struct _pppPObject* param_1, int param_2)
{
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    Mtx sphereMtx;
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor local_a8;
    _pppMngSt* pppMngSt = (_pppMngSt*)ppvMng;
    float radius;

    PSVECSubtract((Vec*)((u8*)ppvMng + 0x8), (Vec*)((u8*)ppvMng + 0x48), &local_88);
    local_94.x = ppvMng->m_matrix.value[0][3];
    local_94.y = ppvMng->m_matrix.value[1][3];
    local_94.z = ppvMng->m_matrix.value[2][3];
    radius = pppMngSt->m_previousPosition.z * *(float*)(param_2 + 8);

    if (((kPppParHitSphZero == local_88.x) && (kPppParHitSphZero == local_88.y)) &&
        (kPppParHitSphZero == local_88.z)) {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, kPppParHitSphZero);
    } else {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(float*)(param_2 + 4));
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
