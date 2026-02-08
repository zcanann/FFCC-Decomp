#include "ffcc/pppCallBackDistance.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>

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
    _pppMngSt* mngSt;
    u8* mngBytes;
    u32 graphId;
    s32 dataOffset;
    s32 frameIndex;
    s32 graphChunk;
    s32 graphAdjust;
    Vec worldPos;
    Vec particlePos;
    f32 distance;

    mngSt = pppMngStPtr;
    mngBytes = (u8*)mngSt;
    particlePos.x = *(f32*)(mngBytes + 0x10);
    dataOffset = *param3->m_serializedDataOffsets;
    particlePos.y = *(f32*)(mngBytes + 0x20);
    particlePos.z = *(f32*)(mngBytes + 0x30);
    distance = PSVECDistance(&particlePos, (Vec*)(mngBytes + 0x64));
    mngSt = pppMngStPtr;
    mngBytes = (u8*)mngSt;

    if ((distance <= param2->m_dataValIndex) || (*(f32*)((u8*)param1 + dataOffset + 8) <= distance)) {
        worldPos.x = *(f32*)(mngBytes + 0x10);
        worldPos.y = *(f32*)(mngBytes + 0x20);
        worldPos.z = *(f32*)(mngBytes + 0x30);
        PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

        frameIndex = (s32)(mngBytes + 0x42E55C58) / 0x158 + ((s32)(mngBytes + 0x42E55C58) >> 0x1f);
        frameIndex = frameIndex - (frameIndex >> 0x1f);

        graphId = *(u32*)&param1->field0_0x0;
        graphChunk = (s32)graphId >> 0xc;
        graphAdjust = 0;
        if (((s32)graphId < 0) && ((graphId & 0xfff) != 0)) {
            graphAdjust = 1;
        }

        Game.game.ParticleFrameCallback(frameIndex, (s32)*(s16*)(mngBytes + 0xb0),
                                        (s32)*(s16*)(mngBytes + 0xb2), (s32)param2->m_initWOrk,
                                        graphChunk + graphAdjust, &worldPos);
    }
}
