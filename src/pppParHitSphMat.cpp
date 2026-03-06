#include "ffcc/pppParHitSphMat.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/symbols_shared.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
extern unsigned char CFlat[];
extern unsigned char Graphic[];
extern Mtx ppvCameraMatrix02;
extern "C" void DrawSphere__8CGraphicFPA4_f8_GXColor(void* graphic, MtxPtr mtx, _GXColor color);

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
    Mtx cameraMtx ATTRIBUTE_ALIGN(8);
    _GXColor local_a8;
    _pppMngSt* pppMngSt = (_pppMngSt*)pppMngStPtr;
    float radius;

    local_88.z = kPppParHitSphMatZero;
    local_88.y = kPppParHitSphMatZero;
    local_88.x = kPppParHitSphMatZero;

    if (*(u8*)(param_2 + 0xC) != 0) {
        s32* offsets = *(s32**)(param_3 + 0xC);
        Vec* src = (Vec*)((u8*)param_1 + offsets[1] + 0x80);
        PSMTXMultVec(pppMngSt->m_matrix.value, src, &local_94);
    } else {
        local_94.x = *(float*)((u8*)pppMngStPtr + 0x84);
        local_94.y = *(float*)((u8*)pppMngStPtr + 0x94);
        local_94.z = *(float*)((u8*)pppMngStPtr + 0xA4);
        s32* offsets = *(s32**)(param_3 + 0xC);
        Vec* src = (Vec*)((u8*)param_1 + offsets[1] + 0x80);
        local_94.x += src->x;
        local_94.y += src->y;
        local_94.z += src->z;
    }

    if (*(float*)(param_2 + 4) != kPppParHitSphMatZero) {
        PSVECSubtract((Vec*)((u8*)pppMngSt + 8), (Vec*)((u8*)pppMngSt + 0x48), &local_88);
    }

    radius = *(float*)((u8*)pppMngSt + 0x64) * *(float*)(param_2 + 8);
    pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(float*)(param_2 + 4));

    if ((*(u32*)(CFlat + 0x129c) & 0x200000) != 0) {
        local_a8.r = 0xFF;
        local_a8.g = 0xFF;
        local_a8.b = 0xFF;
        local_a8.a = 0xFF;
        PSMTXIdentity(cameraMtx);
        PSMTXIdentity(sphereMtx);
        sphereMtx[0][0] = radius;
        sphereMtx[1][1] = radius;
        sphereMtx[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix02, cameraMtx, cameraMtx);
        PSMTXMultVec(cameraMtx, &local_94, &local_a0);
        sphereMtx[0][3] = local_a0.x;
        sphereMtx[1][3] = local_a0.y;
        sphereMtx[2][3] = local_a0.z;
        DrawSphere__8CGraphicFPA4_f8_GXColor(Graphic, sphereMtx, local_a8);
    }
}

