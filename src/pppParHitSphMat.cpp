#include "ffcc/pppParHitSphMat.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <dolphin/mtx.h>

extern unsigned char* lbl_8032ED50;
extern unsigned char CFlat[];

/*
 * --INFO--
 * PAL Address: 0x8014139c
 * PAL Size: 436b
 */
void pppParHitSphMat(void* param1, void* param2, void* param3)
{
    Vec local_88;
    Vec local_94;
    Vec local_a0;
    _GXColor local_7c;
    Mtx MStack_78;
    Mtx local_48;
    u8* pppMngSt = lbl_8032ED50;
    u8* data = (u8*)param1;
    u8* step = (u8*)param2;
    f32 hitLength;
    f32 radius;

    local_88.x = 0.0f;
    local_88.y = 0.0f;
    local_88.z = 0.0f;

    if (step[0xC] != 0) {
        s32* offsets = *(s32**)((u8*)param3 + 0xC);
        Vec* src = (Vec*)(data + offsets[1] + 0x80);

        PSMTXMultVec((MtxPtr)(pppMngSt + 0x78), src, &local_94);
    } else {
        s32* offsets = *(s32**)((u8*)param3 + 0xC);
        Vec* src = (Vec*)(data + offsets[1] + 0x80);

        local_94.x = *(f32*)(pppMngSt + 0x84);
        local_94.y = *(f32*)(pppMngSt + 0x94);
        local_94.z = *(f32*)(pppMngSt + 0xA4);
        local_94.x = local_94.x + src->x;
        local_94.y = local_94.y + src->y;
        local_94.z = local_94.z + src->z;
    }

    hitLength = *(f32*)(step + 4);
    if (hitLength != 0.0f) {
        PSVECSubtract((Vec*)(pppMngSt + 8), (Vec*)(pppMngSt + 0x48), &local_88);
    }

    radius = *(f32*)(pppMngSt + 0x64) * *(f32*)(step + 8);
    pppHitCylinderSendSystem((_pppMngSt*)pppMngSt, &local_94, &local_88, radius, hitLength);

    if ((*(u32*)(CFlat + 0x129c) & 0x200000) != 0) {
        local_7c.r = 0xFF;
        local_7c.g = 0xFF;
        local_7c.b = 0xFF;
        local_7c.a = 0xFF;
        PSMTXIdentity(MStack_78);
        PSMTXIdentity(local_48);
        local_48[0][0] = radius;
        local_48[1][1] = radius;
        local_48[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix0, MStack_78, MStack_78);
        PSMTXMultVec(MStack_78, &local_94, &local_a0);
        local_48[0][3] = local_a0.x;
        local_48[1][3] = local_a0.y;
        local_48[2][3] = local_a0.z;
        Graphic.DrawSphere(local_48, local_7c);
    }
}
