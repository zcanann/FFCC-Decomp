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
 * PAL Address: 0x800d4278
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, struct pppYmMoveParabolaUnkC* offsetData)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    _pppMngSt* pppMngSt = pppMngStPtr;
    f32* work = (f32*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);

    work[1] = work[1] + work[2];
    work[0] = work[0] + work[1];
    if (stepData->m_graphId == basePtr->m_graphId) {
        work[0] = work[0] + stepData->m_stepValue;
        work[1] = work[1] + stepData->m_arg3;
        work[2] = work[2] + stepData->m_payload;
    }

    double frameCount = (double)*(u16*)(work + 3);
    Vec direction;
    if (Game.game.m_currentSceneId == 7) {
        direction.y = gPppYmMoveParabolaZero;
        direction.x = gPppYmMoveParabolaYOffsetStep;
        direction.z = gPppYmMoveParabolaZero;
    } else {
        PSVECSubtract(&pppMngSt->m_paramVec0, &pppMngSt->m_savedPosition, &direction);
    }

    Vec normalizedSource = direction;
    pppNormalize__FR3Vec3Vec((float*)&direction, &normalizedSource);

    u32 sinIndex = (u32)((gPppYmMoveParabolaAngleScale * stepData->m_dataValIndex) / gPppYmMoveParabolaAngleDivisor);
    f32 parabolaScale = (f32)(frameCount * (double)(work[0] * *(f32*)((u8*)gPppTrigTable + ((sinIndex + 0x4000) & 0xFFFC))));
    f32 posX = direction.x * parabolaScale;
    f32 posZ = direction.z * parabolaScale;
    f32 posY = (f32)(
        frameCount * (double)(work[0] * *(f32*)((u8*)gPppTrigTable + (sinIndex & 0xFFFC))) -
        (double)(f32)(frameCount * (double)(f32)((double)(gPppYmMoveParabolaGravityScale * stepData->m_initWOrk) * frameCount)));

    Vec newPosition;
    if (Game.game.m_currentSceneId == 7) {
        Vec offset;
        Vec basePosition;

        basePosition.x = work[4];
        basePosition.y = work[5];
        basePosition.z = work[6];
        offset.x = posX;
        offset.y = posY;
        offset.z = posZ;
        pppAddVector__FR3Vec3Vec3Vec(&newPosition, &offset, &basePosition);
    } else {
        Vec offset;
        Vec basePosition = pppMngSt->m_savedPosition;

        offset.x = posX;
        offset.y = posY;
        offset.z = posZ;
        pppAddVector__FR3Vec3Vec3Vec(&newPosition, &offset, &basePosition);
    }

    Vec oldPosition = pppMngSt->m_position;
    pppCopyVector__FR3Vec3Vec(&pppMngSt->m_previousPosition, &oldPosition);
    pppCopyVector__FR3Vec3Vec(&pppMngSt->m_position, &newPosition);

    pppMngStPtr->m_matrix.value[0][3] = newPosition.x;
    pppMngStPtr->m_matrix.value[1][3] = newPosition.y;
    pppMngStPtr->m_matrix.value[2][3] = newPosition.z;
    pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    *(u16*)(work + 3) = *(u16*)(work + 3) + 1;
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
    f32 zero = gPppYmMoveParabolaZero;

    work[2] = zero;
    work[1] = zero;
    work[0] = zero;
    *(u16*)(work + 3) = 1;

    if (Game.game.m_currentSceneId == 7) {
        Vec basePos = pppMngSt->m_savedPosition;
        Vec worldOffset;
        Vec addPos;
        Vec paramPos;

        pppCopyVector__FR3Vec3Vec((Vec*)(work + 4), &basePos);

        worldOffset.x = pppMngStPtr->m_matrix.value[0][3];
        worldOffset.y = pppMngStPtr->m_matrix.value[1][3];
        worldOffset.z = pppMngStPtr->m_matrix.value[2][3];

        addPos.x = work[4];
        addPos.y = work[5];
        addPos.z = work[6];
        pppAddVector__FR3Vec3Vec3Vec((Vec*)(work + 4), &addPos, &worldOffset);

        paramPos.x = work[4];
        paramPos.y = work[5];
        paramPos.z = work[6];
        pppCopyVector__FR3Vec3Vec(&pppMngSt->m_paramVec0, &paramPos);
        pppMngSt->m_paramVec0.x = pppMngSt->m_paramVec0.x + gPppYmMoveParabolaYOffsetStep;
    }
}
