#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern double DOUBLE_80330E30;

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

    f32 frameCount = (f32)work->m_frame;
    Vec direction;
    if ((s32)Game.m_currentSceneId == 7) {
        f32 zero = gPppYmMoveParabolaZero;
        f32 yOffset = gPppYmMoveParabolaYOffsetStep;

        direction.y = zero;
        direction.x = yOffset;
        direction.z = zero;
    } else {
        PSVECSubtract(&pppMngSt->m_paramVec0, (Vec*)((u8*)pppMngSt + 0x58), &direction);
    }

    Vec normalizedSource = direction;
    pppNormalize(direction, normalizedSource);

    u32 sinIndex = (u32)((gPppYmMoveParabolaAngleScale * stepData->m_dataValIndex) / gPppYmMoveParabolaAngleDivisor);
    f32 positionScale =
        (f32)(frameCount * (double)(work->m_distance * *(f32*)((u8*)gPppTrigTable + ((sinIndex + 0x4000) & 0xFFFC))));
    f32 positionX = direction.x * positionScale;
    f32 positionZ = direction.z * positionScale;
    f32 positionY =
        (f32)(frameCount * (double)(work->m_distance * *(f32*)((u8*)gPppTrigTable + (sinIndex & 0xFFFC))) -
              (double)(f32)(frameCount * (double)((gPppYmMoveParabolaGravityScale * stepData->m_initWOrk) * frameCount)));
    Vec newPosition;
    newPosition.x = positionX;
    newPosition.y = positionY;
    newPosition.z = positionZ;
    if ((s32)Game.m_currentSceneId == 7) {
        Vec basePosition = work->m_basePosition;
        pppAddVector(newPosition, newPosition, basePosition);
    } else {
        Vec basePosition = *(Vec*)((u8*)pppMngSt + 0x58);
        pppAddVector(newPosition, newPosition, basePosition);
    }

    Vec oldPosition = pppMngSt->m_position;
    pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x48), oldPosition);
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

    work->m_acceleration = 0.0f;
    work->m_velocity = 0.0f;
    work->m_distance = 0.0f;
    work->m_frame = 1;

    if ((s32)Game.m_currentSceneId == 7) {
        Vec matrixOffset;

        pppCopyVector(work->m_basePosition, *(Vec*)((u8*)pppMngSt + 0x58));

        matrixOffset.x = pppMngStPtr->m_matrix.value[0][3];
        matrixOffset.y = pppMngStPtr->m_matrix.value[1][3];
        matrixOffset.z = pppMngStPtr->m_matrix.value[2][3];

        pppAddVector(work->m_basePosition, work->m_basePosition, matrixOffset);
        pppCopyVector(pppMngSt->m_paramVec0, work->m_basePosition);
        pppMngSt->m_paramVec0.x = pppMngSt->m_paramVec0.x + gPppYmMoveParabolaYOffsetStep;
    }
}
