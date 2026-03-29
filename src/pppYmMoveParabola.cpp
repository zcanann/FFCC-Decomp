#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
}

struct pppYmMoveParabolaWork {
    f32 m_distance;
    f32 m_velocity;
    f32 m_acceleration;
    u16 m_frame;
    u16 _pad0x0E;
    Vec m_basePosition;
};

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

    pppYmMoveParabolaWork* work =
        (pppYmMoveParabolaWork*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);
    _pppMngSt* pppMngSt = pppMngStPtr;

    work->m_velocity = work->m_velocity + work->m_acceleration;
    work->m_distance = work->m_distance + work->m_velocity;
    if (stepData->m_graphId == basePtr->m_graphId) {
        work->m_distance = work->m_distance + stepData->m_stepValue;
        work->m_velocity = work->m_velocity + stepData->m_arg3;
        work->m_acceleration = work->m_acceleration + stepData->m_payload;
    }

    double frameCount = (double)work->m_frame;
    Vec direction;
    if ((s32)Game.m_currentSceneId == 7) {
        direction.y = gPppYmMoveParabolaZero;
        direction.x = gPppYmMoveParabolaYOffsetStep;
        direction.z = gPppYmMoveParabolaZero;
    } else {
        PSVECSubtract(&pppMngSt->m_paramVec0, &pppMngSt->m_savedPosition, &direction);
    }

    Vec normalizedSource = direction;
    pppNormalize(direction, normalizedSource);

    s32 sinIndex;
    {
        f32 tableAngle = (gPppYmMoveParabolaAngleScale * stepData->m_dataValIndex) / gPppYmMoveParabolaAngleDivisor;
        sinIndex = (s32)tableAngle;
    }
    f32 parabolaScale = (f32)(frameCount * (double)(work->m_distance * *(f32*)((u8*)gPppTrigTable + ((sinIndex + 0x4000) & 0xFFFC))));
    f32 posX = direction.x * parabolaScale;
    f32 posZ = direction.z * parabolaScale;
    f32 posY = (f32)(
        frameCount * (double)(work->m_distance * *(f32*)((u8*)gPppTrigTable + (sinIndex & 0xFFFC))) -
        (double)(f32)(frameCount * (double)(f32)((double)(gPppYmMoveParabolaGravityScale * stepData->m_initWOrk) * frameCount)));

    Vec newPosition;
    newPosition.x = posX;
    newPosition.y = posY;
    newPosition.z = posZ;
    if ((s32)Game.m_currentSceneId == 7) {
        Vec basePosition = work->m_basePosition;
        pppAddVector(newPosition, newPosition, basePosition);
    } else {
        Vec basePosition = pppMngSt->m_savedPosition;
        pppAddVector(newPosition, newPosition, basePosition);
    }

    Vec oldPosition = pppMngSt->m_position;
    pppCopyVector(pppMngSt->m_previousPosition, oldPosition);
    pppCopyVector(pppMngSt->m_position, newPosition);

    pppMngStPtr->m_matrix.value[0][3] = newPosition.x;
    pppMngStPtr->m_matrix.value[1][3] = newPosition.y;
    pppMngStPtr->m_matrix.value[2][3] = newPosition.z;
    pppSetFpMatrix(pppMngSt);
    work->m_frame = work->m_frame + 1;
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
    pppYmMoveParabolaWork* work =
        (pppYmMoveParabolaWork*)((u8*)basePtr + *dataPtr->m_serializedDataOffsets + 0x80);
    f32 zero = gPppYmMoveParabolaZero;

    work->m_acceleration = zero;
    work->m_velocity = zero;
    work->m_distance = zero;
    work->m_frame = 1;

    if ((s32)Game.m_currentSceneId == 7) {
        Vec savedPosition = pppMngSt->m_savedPosition;
        Vec matrixOffset;
        Vec basePosition;
        Vec paramPosition;

        pppCopyVector__FR3Vec3Vec(&work->m_basePosition, &savedPosition);

        matrixOffset.x = pppMngStPtr->m_matrix.value[0][3];
        matrixOffset.y = pppMngStPtr->m_matrix.value[1][3];
        matrixOffset.z = pppMngStPtr->m_matrix.value[2][3];

        basePosition = work->m_basePosition;
        pppAddVector__FR3Vec3Vec3Vec(&work->m_basePosition, &basePosition, &matrixOffset);

        paramPosition = work->m_basePosition;
        pppCopyVector__FR3Vec3Vec(&pppMngSt->m_paramVec0, &paramPosition);
        pppMngSt->m_paramVec0.x = pppMngSt->m_paramVec0.x + gPppYmMoveParabolaYOffsetStep;
    }
}
