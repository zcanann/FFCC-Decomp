#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern _pppMngSt* pppMngStPtr;
extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
void pppNormalize__FR3Vec3Vec(float*, Vec*);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
}

/*
 * --INFO--
 * PAL Address: 0x800d4558
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkC* dataPtr)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    f32* work = (f32*)((u8*)basePtr + *dataPtr->m_serializedDataOffsets + 0x80);
    f32 fVar2 = gPppYmMoveParabolaZero;

    work[2] = gPppYmMoveParabolaZero;
    work[1] = fVar2;
    work[0] = fVar2;
    *(u16*)(work + 3) = 1;

    if (Game.game.m_currentSceneId == 7) {
        Vec basePos = pppMngSt->m_savedPosition;
        Vec worldOffset;
        Vec outPos;

        pppCopyVector__FR3Vec3Vec((Vec*)(work + 4), &basePos);

        worldOffset.x = pppMngStPtr->m_matrix.value[0][3];
        worldOffset.y = pppMngStPtr->m_matrix.value[1][3];
        worldOffset.z = pppMngStPtr->m_matrix.value[2][3];

        outPos.x = work[4];
        outPos.y = work[5];
        outPos.z = work[6];
        pppAddVector__FR3Vec3Vec3Vec((Vec*)(work + 4), &outPos, &worldOffset);

        outPos.x = work[4];
        outPos.y = work[5];
        outPos.z = work[6];
        pppCopyVector__FR3Vec3Vec(&pppMngSt->m_paramVec0, &outPos);
        pppMngSt->m_paramVec0.x = pppMngSt->m_paramVec0.x + gPppYmMoveParabolaYOffsetStep;
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
extern "C" void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, struct pppYmMoveParabolaUnkC* offsetData)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    f32* work;
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
    double frameCount;
    u32 sinIndex;

    if (gPppCalcDisabled == 0) {
        work = (f32*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);
        work[1] = work[1] + work[2];
        work[0] = work[0] + work[1];
        if (stepData->m_graphId == basePtr->m_graphId) {
            work[0] = work[0] + stepData->m_stepValue;
            work[1] = work[1] + stepData->m_arg3;
            work[2] = work[2] + stepData->m_payload;
        }
        frameCount = (double)*(u16*)(work + 3);
        if (Game.game.m_currentSceneId == 7) {
            local_44.y = gPppYmMoveParabolaZero;
            local_44.x = gPppYmMoveParabolaYOffsetStep;
            local_44.z = gPppYmMoveParabolaZero;
        } else {
            PSVECSubtract(&pppMngSt->m_paramVec0, &pppMngSt->m_savedPosition, &local_44);
        }
        local_50 = local_44.x;
        local_4c = local_44.y;
        local_48 = local_44.z;
        pppNormalize__FR3Vec3Vec((float*)&local_44, (Vec*)&local_50);
        sinIndex = (u32)((gPppYmMoveParabolaAngleScale * stepData->m_dataValIndex) / gPppYmMoveParabolaAngleDivisor);
        local_30 = (f32)(frameCount * (double)(work[0] * *(f32*)((u8*)gPppTrigTable + ((sinIndex + 0x4000) & 0xFFFC))));
        local_38 = local_44.x * local_30;
        local_30 = local_44.z * local_30;
        local_34 = (f32)(
            frameCount * (double)(work[0] * *(f32*)((u8*)gPppTrigTable + (sinIndex & 0xFFFC))) -
            (double)(f32)(frameCount * (double)(f32)((double)(gPppYmMoveParabolaGravityScale * stepData->m_initWOrk) * frameCount)));
        if (Game.game.m_currentSceneId == 7) {
            local_68 = work[4];
            local_64 = work[5];
            local_60 = work[6];
            local_5c = local_38;
            local_58 = local_34;
            local_54 = local_30;
            pppAddVector__FR3Vec3Vec3Vec((Vec*)&local_38, (Vec*)&local_5c, (Vec*)&local_68);
        } else {
            local_80 = pppMngSt->m_savedPosition.x;
            local_7c = pppMngSt->m_savedPosition.y;
            local_78 = pppMngSt->m_savedPosition.z;
            local_74 = local_38;
            local_70 = local_34;
            local_6c = local_30;
            pppAddVector__FR3Vec3Vec3Vec((Vec*)&local_38, (Vec*)&local_74, (Vec*)&local_80);
        }
        local_8c.x = pppMngSt->m_position.x;
        local_8c.y = pppMngSt->m_position.y;
        local_8c.z = pppMngSt->m_position.z;
        pppCopyVector__FR3Vec3Vec(&pppMngSt->m_previousPosition, &local_8c);
        local_98.x = local_38;
        local_98.y = local_34;
        local_98.z = local_30;
        pppCopyVector__FR3Vec3Vec(&pppMngSt->m_position, &local_98);
        pppMngStPtr->m_matrix.value[0][3] = local_38;
        pppMngStPtr->m_matrix.value[1][3] = local_34;
        pppMngStPtr->m_matrix.value[2][3] = local_30;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        *(u16*)(work + 3) = *(u16*)(work + 3) + 1;
    }
}
