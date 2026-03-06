#include "ffcc/pppCallBackDistance.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>

extern u8 PartMng[];

extern "C" {
void ParticleFrameCallback__5CGameFiiiiiP3Vec(CGame*, int, int, int, int, int, Vec*);
}

/*
 * --INFO--
 * PAL Address: 0x80141204
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCallBackDistance(pppCallBackDistance* param1, pppCallBackDistanceUnkB* param2, pppCallBackDistanceUnkC* param3)
{
    u8* pppMngSt = (u8*)pppMngStPtr;
    s32 distanceOffset = *param3->m_serializedDataOffsets + 0x80;
    f32 distance;
    Vec local_1c;
    Vec local_28;

    local_1c.x = *(f32*)(pppMngSt + 0x84);
    local_1c.y = *(f32*)(pppMngSt + 0x94);
    local_1c.z = *(f32*)(pppMngSt + 0xA4);
    distance = PSVECDistance(&local_1c, (Vec*)(pppMngSt + 0x68));

    if ((distance <= param2->m_dataValIndex) ||
        (*(f32*)((u8*)param1 + distanceOffset) <= distance)) {
        s32 partIndex;
        s32 graphFrame;
        s32 m_kind;
        s32 m_nodeIndex;
        s32 initWork;

        pppMngSt = (u8*)pppMngStPtr;
        local_28.x = *(f32*)(pppMngSt + 0x84);
        local_28.y = *(f32*)(pppMngSt + 0x94);
        local_28.z = *(f32*)(pppMngSt + 0xA4);
        PSMTXMultVec(ppvWorldMatrix, &local_28, &local_28);

        partIndex = ((s32)(pppMngSt - (PartMng + 0x2A18))) / 0x158;
        graphFrame = (s32)(*(u32*)((u8*)param1 + 0xC)) / 0x1000;
        m_kind = (s32)*(s16*)(pppMngSt + 0x74);
        m_nodeIndex = (s32)*(s16*)(pppMngSt + 0x76);
        initWork = (s32)*(s16*)&param2->m_initWOrk;

        ParticleFrameCallback__5CGameFiiiiiP3Vec(
            (CGame*)&Game, partIndex, m_kind, m_nodeIndex, initWork, graphFrame, &local_28);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80141314
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCallBackDistance(pppCallBackDistance*, pppCallBackDistanceUnkC*)
{
}

/*
 * --INFO--
 * PAL Address: 0x80141318
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCallBackDistance(pppCallBackDistance* param1, pppCallBackDistanceUnkC* param2)
{
    u8* pppMngSt;
    u8* objPosBase;
    Vec local_1c;
    Vec local_28;
    s32 dataOffset;
    f32* distancePtr;

    pppMngSt = (u8*)pppMngStPtr;
    dataOffset = *param2->m_serializedDataOffsets;
    distancePtr = (f32*)((u8*)param1 + dataOffset + 0x80);
    objPosBase = *(u8**)(pppMngSt + 0xDC);
    local_28.x = *(f32*)(objPosBase + 0x15C);
    local_28.y = *(f32*)(objPosBase + 0x160);
    local_28.z = *(f32*)(objPosBase + 0x164);
    local_1c.x = *(f32*)(pppMngSt + 0x68);
    local_1c.y = *(f32*)(pppMngSt + 0x6C);
    local_1c.z = *(f32*)(pppMngSt + 0x70);
    *distancePtr = PSVECDistance(&local_28, &local_1c);
}


