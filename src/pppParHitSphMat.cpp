#include "ffcc/pppParHitSphMat.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern unsigned char* lbl_8032ED50;
extern float lbl_80332080;
extern unsigned char CFlat[];
extern Mtx ppvCameraMatrix02;

/*
 * --INFO--
 * PAL Address: 0x8014139c
 * PAL Size: 436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSphMat(struct _pppPObject* param_1, int param_2, int param_3)
{
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    Mtx sphereMtx;
    Mtx cameraMtx;
    _GXColor local_a8;
    _pppMngSt* pppMngSt = (_pppMngSt*)lbl_8032ED50;
    float radius;

    local_88.z = lbl_80332080;
    local_88.y = lbl_80332080;
    local_88.x = lbl_80332080;

    if (*(u8*)(param_2 + 0xC) != 0) {
        s32* offsets = *(s32**)(param_3 + 0xC);
        Vec* src = (Vec*)((u8*)param_1 + offsets[1] + 0x80);
        PSMTXMultVec(pppMngSt->m_matrix.value, src, &local_94);
    } else {
        local_94.x = *(float*)(lbl_8032ED50 + 0x84);
        local_94.y = *(float*)(lbl_8032ED50 + 0x94);
        local_94.z = *(float*)(lbl_8032ED50 + 0xA4);
        s32* offsets = *(s32**)(param_3 + 0xC);
        Vec* src = (Vec*)((u8*)param_1 + offsets[1] + 0x80);
        local_94.x += src->x;
        local_94.y += src->y;
        local_94.z += src->z;
    }

    if (*(float*)(param_2 + 4) != lbl_80332080) {
        PSVECSubtract((Vec*)((u8*)pppMngSt + 8), (Vec*)((u8*)pppMngSt + 0x48), &local_88);
    }

    radius = *(float*)((u8*)pppMngSt + 0x64) * *(float*)(param_2 + 8);
    pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(float*)(param_2 + 4));

    if ((*(u32*)(CFlat + 0x129c) & 0x200000) != 0) {
        local_a8.r = 0xFF;
        local_a8.g = 0xFF;
        local_a8.b = 0xFF;
        local_a8.a = 0xFF;
        register MtxPtr sphereMtxPtr = sphereMtx;
        PSMTXIdentity(cameraMtx);
        PSMTXIdentity(sphereMtxPtr);
        sphereMtxPtr[0][0] = radius;
        sphereMtxPtr[1][1] = radius;
        sphereMtxPtr[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix02, cameraMtx, cameraMtx);
        PSMTXMultVec(cameraMtx, &local_94, &local_a0);
        sphereMtxPtr[0][3] = local_a0.x;
        sphereMtxPtr[1][3] = local_a0.y;
        sphereMtxPtr[2][3] = local_a0.z;
        Graphic.DrawSphere(sphereMtxPtr, local_a8);
    }
}
