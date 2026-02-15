#include "ffcc/pppCallBackDistance.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>

extern u8 PartMng[];
extern u8* lbl_8032ED50;

/*
 * --INFO--
 * PAL Address: 0x80141318
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCallBackDistance(pppCallBackDistance* param1, UnkC* param2)
{
    u8* pppMngSt;
    u8* objPosBase;
    Vec local_1c;
    Vec local_28;
    s32 dataOffset;
    f32* distancePtr;

    pppMngSt = lbl_8032ED50;
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

/*
 * --INFO--
 * PAL Address: 0x80141314
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCallBackDistance(void)
{
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
void pppFrameCallBackDistance(pppCallBackDistance* param1, UnkB* param2, UnkC* param3)
{
    u8* pppMngSt = lbl_8032ED50;
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

        pppMngSt = lbl_8032ED50;
        local_28.x = *(f32*)(pppMngSt + 0x84);
        local_28.y = *(f32*)(pppMngSt + 0x94);
        local_28.z = *(f32*)(pppMngSt + 0xA4);
        PSMTXMultVec(ppvWorldMatrix, &local_28, &local_28);

        partIndex = ((s32)(pppMngSt - (PartMng + 0x2A18))) / 0x158;
        graphFrame = (s32)(*(u32*)((u8*)param1 + 0xC)) / 0x1000;
        Game.game.ParticleFrameCallback(partIndex, (s32)*(s16*)(pppMngSt + 0x74),
                                        (s32)*(s16*)(pppMngSt + 0x76),
                                        (s32)*(s16*)&param2->m_initWOrk, graphFrame, &local_28);
    }
}
