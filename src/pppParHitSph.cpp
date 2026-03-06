#include "ffcc/pppParHitSph.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern float lbl_80330700;
extern unsigned char CFlat[];
extern unsigned char Graphic[];
extern Mtx ppvCameraMatrix02;
extern "C" void DrawSphere__8CGraphicFPA4_f8_GXColor(void* graphic, MtxPtr mtx, _GXColor color);

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
    _pppMngSt* pppMngSt = (_pppMngSt*)pppMngStPtr;
    float radius;

    PSVECSubtract((Vec*)(pppMngStPtr + 0x8), (Vec*)(pppMngStPtr + 0x48), &local_88);
    local_94.x = *(float*)(pppMngStPtr + 0x84);
    local_94.y = *(float*)(pppMngStPtr + 0x94);
    local_94.z = *(float*)(pppMngStPtr + 0xA4);
    radius = *(float*)((u8*)pppMngSt + 0x64) * *(float*)(param_2 + 8);

    if (((lbl_80330700 == local_88.x) && (lbl_80330700 == local_88.y)) &&
        (lbl_80330700 == local_88.z)) {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, lbl_80330700);
    } else {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(float*)(param_2 + 4));
    }

    if ((*(unsigned int*)(CFlat + 0x129c) & 0x200000) != 0) {
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


