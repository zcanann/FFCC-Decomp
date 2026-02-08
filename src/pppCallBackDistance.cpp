#include "ffcc/pppCallBackDistance.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>

extern CPartMng PartMng;

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
    Vec local_28;
    Vec local_1c;
    f64 dVar3;
    s32 iVar1;
    f32* pDataVal;

    iVar1 = *param2->m_serializedDataOffsets;
    pDataVal = (f32*)((u8*)param1 + 0x80 + iVar1);
    local_28.x = pppMngStPtr->m_matrix.value[0][3];
    local_28.y = pppMngStPtr->m_matrix.value[1][3];
    local_28.z = pppMngStPtr->m_matrix.value[2][3];
    local_1c.x = *(f32*)((u8*)pppMngStPtr + 0x68);
    local_1c.y = *(f32*)((u8*)pppMngStPtr + 0x6c);
    local_1c.z = *(f32*)((u8*)pppMngStPtr + 0x70);
    dVar3 = (f64)PSVECDistance(&local_28, &local_1c);
    *pDataVal = (f32)dVar3;
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
    _pppMngSt* pppMngSt;
    u32 graphId;
    s32 dataOffset;
    f64 distance;
    Vec worldPos;
    Vec particlePos;

    particlePos.x = pppMngStPtr->m_matrix.value[0][3];
    dataOffset = *param3->m_serializedDataOffsets;
    particlePos.y = pppMngStPtr->m_matrix.value[1][3];
    particlePos.z = pppMngStPtr->m_matrix.value[2][3];
    distance = (f64)PSVECDistance(&particlePos, (Vec*)((u8*)pppMngStPtr + 0x64));
    pppMngSt = pppMngStPtr;

    if ((distance <= (double)(f32)param2->m_dataValIndex) ||
        ((double)*(f32*)((u8*)(&param1->field0_0x0 + 2) + dataOffset) <= distance)) {
        worldPos.x = pppMngStPtr->m_matrix.value[0][3];
        worldPos.y = pppMngStPtr->m_matrix.value[1][3];
        worldPos.z = pppMngStPtr->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

        graphId = *(u32*)&param1->field0_0x0;
        dataOffset = ((s32)((u8*)pppMngSt - ((u8*)&PartMng + 0x2A18))) / 0x158;

        Game.game.ParticleFrameCallback(dataOffset, (s32)pppMngSt->m_kind, (s32)pppMngSt->m_nodeIndex,
                                        (s32)*(s16*)&param2->m_initWOrk,
                                        ((s32)graphId >> 0xC) +
                                            (((s32)graphId < 0) && ((graphId & 0xFFF) != 0)),
                                        &worldPos);
    }
}
