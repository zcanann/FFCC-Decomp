#include "ffcc/pppParHitSphMat.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern unsigned char* lbl_8032ED50;
extern float lbl_80330700;
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
void pppParHitSphMat(void* param1, void* param2, void* param3)
{
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    Mtx local_48;
    Mtx MStack_78;
    _GXColor local_a8;
    u8* data = (u8*)param1;
    u8* step = (u8*)param2;
    _pppMngSt* pppMngSt = (_pppMngSt*)lbl_8032ED50;
    f32 radius;

    local_88.z = lbl_80330700;
    local_88.y = lbl_80330700;
    local_88.x = lbl_80330700;

    if (step[0xC] != 0) {
        s32* offsets = *(s32**)((u8*)param3 + 0xC);
        Vec* src = (Vec*)(data + offsets[1] + 0x80);

        PSMTXMultVec(pppMngSt->m_matrix.value, src, &local_94);
    } else {
        local_94.x = pppMngSt->m_matrix.value[0][3];
        local_94.y = pppMngSt->m_matrix.value[1][3];
        local_94.z = pppMngSt->m_matrix.value[2][3];
        s32* offsets = *(s32**)((u8*)param3 + 0xC);
        Vec* src = (Vec*)(data + offsets[1] + 0x80);

        local_94.x = local_94.x + src->x;
        local_94.y = local_94.y + src->y;
        local_94.z = local_94.z + src->z;
    }

    if (*(f32*)(step + 4) != lbl_80330700) {
        PSVECSubtract((Vec*)((u8*)pppMngSt + 8), (Vec*)((u8*)pppMngSt + 0x48), &local_88);
    }

    radius = *(f32*)((u8*)pppMngSt + 0x64) * *(f32*)(step + 8);
    pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(f32*)(step + 4));

    if ((*(u32*)(CFlat + 0x129c) & 0x200000) != 0) {
        local_a8.r = 0xFF;
        local_a8.g = 0xFF;
        local_a8.b = 0xFF;
        local_a8.a = 0xFF;
        PSMTXIdentity(MStack_78);
        PSMTXIdentity(local_48);
        local_48[0][0] = radius;
        local_48[1][1] = radius;
        local_48[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix02, MStack_78, MStack_78);
        PSMTXMultVec(MStack_78, &local_94, &local_a0);
        local_48[0][3] = local_a0.x;
        local_48[1][3] = local_a0.y;
        local_48[2][3] = local_a0.z;
        Graphic.DrawSphere(local_48, local_a8);
    }
}
