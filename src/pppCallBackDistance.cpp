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
    char* owner;
    Vec local_28;
    Vec local_1c;
    f64 dVar3;
    s32 iVar1;

    iVar1 = *param2->m_serializedDataOffsets;
    owner = (char*)pppMngStPtr->m_owner;
    local_28.x = *(float*)(owner + 0x15c);
    local_28.y = *(float*)(owner + 0x160);
    local_28.z = *(float*)(owner + 0x164);
    local_1c.x = pppMngStPtr->m_scale.x;
    local_1c.y = pppMngStPtr->m_scale.y;
    local_1c.z = pppMngStPtr->m_scale.z;
    dVar3 = (f64)PSVECDistance(&local_28, &local_1c);
    *(f32*)((s32)(&param1->field0_0x0 + 2) + iVar1) = (f32)dVar3;
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
    _pppMngSt* p_Var1;
    u32 uVar2;
    s32 iVar3;
    Vec local_28;
    Vec local_1c;
    f64 dVar4;

    local_1c.x = pppMngStPtr->m_matrix.value[0][3];
    iVar3 = *param3->m_serializedDataOffsets;
    local_1c.y = pppMngStPtr->m_matrix.value[1][3];
    local_1c.z = pppMngStPtr->m_matrix.value[2][3];
    dVar4 = (f64)PSVECDistance(&local_1c, &pppMngStPtr->m_scale);
    p_Var1 = pppMngStPtr;

    if ((dVar4 <= (f64)param2->m_dataValIndex) ||
        ((f64)*(f32*)((s32)(&param1->field0_0x0 + 2) + iVar3) <= dVar4)) {
        local_28.x = pppMngStPtr->m_matrix.value[0][3];
        local_28.y = pppMngStPtr->m_matrix.value[1][3];
        local_28.z = pppMngStPtr->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &local_28, &local_28);
        uVar2 = *(u32*)&param1->field0_0x0;
        iVar3 = (s32)&p_Var1[0x5f2411].m_scale / 0x158 + ((s32)&p_Var1[0x5f2411].m_scale >> 0x1f);
        Game.game.ParticleFrameCallback(iVar3 - (iVar3 >> 0x1f), (s32)p_Var1->m_kind,
                                        (s32)p_Var1->m_nodeIndex, (s32)param2->m_initWOrk,
                                        ((s32)uVar2 >> 0xc) +
                                            (u32)((s32)uVar2 < 0 && (uVar2 & 0xfff) != 0),
                                        &local_28);
    }
}
