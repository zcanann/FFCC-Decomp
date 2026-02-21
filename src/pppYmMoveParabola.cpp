#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern f32 FLOAT_80330e18;
extern f32 FLOAT_80330e1c;
extern f32 FLOAT_80330e20;
extern f32 FLOAT_80330e24;
extern f32 FLOAT_80330e28;
extern s32 DAT_8032ed70;
extern u8* lbl_8032ED50;
extern f32 lbl_801EC9F0[];

/*
 * --INFO--
 * PAL Address: 0x800d4558
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmMoveParabola(pppYmMoveParabola* basePtr, UnkC* offsetData)
{
    _pppMngSt* pppMngSt;
    f32 value;
    f32* work;
    Vec local_48;
    Vec local_24;
    f32 local_3c;
    f32 local_38;
    f32 local_34;
    f32 local_30;
    f32 local_2c;
    f32 local_28;
    f32 local_18;
    f32 local_14;
    f32 local_10;

    value = FLOAT_80330e1c;
    pppMngSt = (_pppMngSt*)lbl_8032ED50;
    work = (f32*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);

    work[2] = FLOAT_80330e1c;
    work[1] = value;
    work[0] = value;
    *(u16*)(work + 3) = 1;

    if (Game.game.m_currentSceneId == 7) {
        local_24.x = *(f32*)((u8*)pppMngSt + 0x58);
        local_24.y = *(f32*)((u8*)pppMngSt + 0x5C);
        local_24.z = *(f32*)((u8*)pppMngSt + 0x60);
        pppCopyVector(*(Vec*)(work + 4), local_24);

        local_3c = pppMngStPtr->m_matrix.value[0][3];
        local_38 = pppMngStPtr->m_matrix.value[1][3];
        local_34 = pppMngStPtr->m_matrix.value[2][3];

        local_30 = work[4];
        local_2c = work[5];
        local_28 = work[6];

        local_18 = local_3c;
        local_14 = local_38;
        local_10 = local_34;

        pppAddVector(*(Vec*)(work + 4), *(Vec*)&local_30, *(Vec*)&local_3c);

        local_48.x = work[4];
        local_48.y = work[5];
        local_48.z = work[6];
        pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x68), local_48);
        *(f32*)((u8*)pppMngSt + 0x68) += FLOAT_80330e18;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d4278
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmMoveParabola(pppYmMoveParabola* basePtr, UnkB* stepData, UnkC* offsetData)
{
    u32 tableIndex;
    _pppMngSt* pppMngSt;
    f32* work;
    double frameCount;
    Vec local_98;
    Vec local_8c;
    f32 local_80;
    f32 local_7c;
    f32 local_78;
    f32 local_74;
    f32 local_70;
    f32 local_6c;
    f32 local_68;
    f32 local_64;
    f32 local_60;
    f32 local_5c;
    f32 local_58;
    f32 local_54;
    f32 local_50;
    f32 local_4c;
    f32 local_48;
    Vec local_44;
    f32 local_38;
    f32 local_34;
    f32 local_30;

    pppMngSt = (_pppMngSt*)lbl_8032ED50;

    if (DAT_8032ed70 == 0) {
        work = (f32*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);

        work[1] += work[2];
        work[0] += work[1];

        if (stepData->m_graphId == basePtr->m_graphId) {
            work[0] += stepData->m_stepValue;
            work[1] += (f32)stepData->m_arg3;
            work[2] += *(f32*)stepData->m_payload;
        }

        frameCount = (double)(f32)(*(u16*)(work + 3));

        if (Game.game.m_currentSceneId == 7) {
            local_44.y = FLOAT_80330e1c;
            local_44.x = FLOAT_80330e18;
            local_44.z = FLOAT_80330e1c;
        } else {
            PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &local_44);
        }

        local_50 = local_44.x;
        local_4c = local_44.y;
        local_48 = local_44.z;
        pppNormalize(local_44, *(Vec*)&local_50);

        tableIndex = (u32)((FLOAT_80330e20 * (f32)stepData->m_dataValIndex) / FLOAT_80330e24);

        local_30 = (f32)(frameCount * (double)(work[0] * *(f32*)((u8*)lbl_801EC9F0 + ((tableIndex + 0x4000) & 0xFFFC))));
        local_38 = local_44.x * local_30;
        local_30 = local_44.z * local_30;

        local_34 = (f32)(frameCount * (double)(work[0] * *(f32*)((u8*)lbl_801EC9F0 + (tableIndex & 0xFFFC))) -
                         (double)(f32)(frameCount * (double)(f32)((double)(FLOAT_80330e28 * (f32)stepData->m_initWOrk) * frameCount)));

        if (Game.game.m_currentSceneId == 7) {
            local_68 = work[4];
            local_64 = work[5];
            local_60 = work[6];

            local_5c = local_38;
            local_58 = local_34;
            local_54 = local_30;

            pppAddVector(*(Vec*)&local_38, *(Vec*)&local_5c, *(Vec*)&local_68);
        } else {
            local_80 = *(f32*)((u8*)pppMngSt + 0x58);
            local_7c = *(f32*)((u8*)pppMngSt + 0x5C);
            local_78 = *(f32*)((u8*)pppMngSt + 0x60);

            local_74 = local_38;
            local_70 = local_34;
            local_6c = local_30;

            pppAddVector(*(Vec*)&local_38, *(Vec*)&local_74, *(Vec*)&local_80);
        }

        local_8c.x = *(f32*)((u8*)pppMngSt + 0x08);
        local_8c.y = *(f32*)((u8*)pppMngSt + 0x0C);
        local_8c.z = *(f32*)((u8*)pppMngSt + 0x10);
        pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x48), local_8c);

        local_98.x = local_38;
        local_98.y = local_34;
        local_98.z = local_30;
        pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x08), local_98);

        pppMngStPtr->m_matrix.value[0][3] = local_38;
        pppMngStPtr->m_matrix.value[1][3] = local_34;
        pppMngStPtr->m_matrix.value[2][3] = local_30;
        pppSetFpMatrix(pppMngSt);

        *(u16*)(work + 3) = *(u16*)(work + 3) + 1;
    }
}
