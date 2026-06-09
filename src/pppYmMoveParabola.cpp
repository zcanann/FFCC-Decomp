#include "ffcc/pppYmMoveParabola.h"
#include "global.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/game.h"
#include "types.h"
#include "dolphin/mtx.h"

struct pppYmMoveParabolaWork {
    f32 m_distance;
    f32 m_velocity;
    f32 m_acceleration;
    u16 m_frame;
    u16 _pad0x0E;
    Vec m_basePosition;
};

extern const float gPppYmMoveParabolaYOffsetStep = 1.0f;
extern const float gPppYmMoveParabolaZero = 0.0f;
extern const float gPppYmMoveParabolaAngleScale = 32768.0f;
extern const float gPppYmMoveParabolaAngleDivisor = 180.0f;
extern const float gPppYmMoveParabolaGravityScale = 0.5f;

STATIC_ASSERT(sizeof(YmMoveParabolaDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(YmMoveParabolaDataOffsets, m_workOffset) == 0x0);

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline YmMoveParabolaDataOffsets* GetYmMoveParabolaDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmMoveParabolaDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline pppYmMoveParabolaWork* ParabolaWork(pppYmMoveParabola* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppYmMoveParabolaWork*>(object->m_workArea +
                                                   GetYmMoveParabolaDataOffsets(ctrl)->m_workOffset);
}

static inline Vec* ParabolaPreviousPosition(_pppMngSt* mng)
{
    return &mng->UserPosition();
}

static inline Vec* ParabolaBasePosition(_pppMngSt* mng)
{
    return &mng->BasePosition();
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
extern "C" void pppFrameYmMoveParabola(pppYmMoveParabola* basePtr, pppYmMoveParabolaStep* stepData, _pppCtrlTable* offsetData)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    pppYmMoveParabolaWork* work = ParabolaWork(basePtr, offsetData);
    _pppMngSt* pppMngSt = ppvMng;

    work->m_velocity = work->m_velocity + work->m_acceleration;
    work->m_distance = work->m_distance + work->m_velocity;
    if (stepData->m_graphId == basePtr->m_graphId) {
        work->m_distance = work->m_distance + stepData->m_stepValue;
        work->m_velocity = work->m_velocity + stepData->m_arg3;
        work->m_acceleration = work->m_acceleration + stepData->m_payload;
    }

    f32 frameCount = (f32)work->m_frame;
    Vec newPosition;
    Vec direction;
    if ((s32)Game.m_currentSceneId == 7) {
        f32 yOffset = gPppYmMoveParabolaYOffsetStep;
        f32 zero = gPppYmMoveParabolaZero;

        direction.x = yOffset;
        direction.z = direction.y = zero;
    } else {
        PSVECSubtract(&pppMngSt->m_paramVec0, ParabolaBasePosition(pppMngSt), &direction);
    }

    Vec normalizedSource = direction;
    pppNormalize(direction, normalizedSource);

    s32 sinIndex = (s32)((gPppYmMoveParabolaAngleScale * stepData->m_dataValIndex) / gPppYmMoveParabolaAngleDivisor);
    f32 xzScale = frameCount * (work->m_distance * ppvSinTbl[((sinIndex + 0x4000) & 0xFFFC) >> 2]);
    newPosition.x = direction.x * xzScale;
    f32 gravityOffset = gPppYmMoveParabolaGravityScale * stepData->m_initWOrk;
    newPosition.y = (frameCount * (work->m_distance * ppvSinTbl[(sinIndex & 0xFFFC) >> 2])) -
                    (frameCount * (gravityOffset * frameCount));
    newPosition.z = direction.z * xzScale;
    if ((s32)Game.m_currentSceneId == 7) {
        Vec basePosition = work->m_basePosition;
        pppAddVector(newPosition, newPosition, basePosition);
    } else {
        Vec basePosition = *ParabolaBasePosition(pppMngSt);
        pppAddVector(newPosition, newPosition, basePosition);
    }

    Vec oldPosition = pppMngSt->m_position;
    pppCopyVector(*ParabolaPreviousPosition(pppMngSt), oldPosition);
    pppCopyVector(pppMngSt->m_position, newPosition);

    ppvMng->m_matrix.value[0][3] = newPosition.x;
    ppvMng->m_matrix.value[1][3] = newPosition.y;
    ppvMng->m_matrix.value[2][3] = newPosition.z;
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
extern "C" void pppConstructYmMoveParabola(pppYmMoveParabola* basePtr, _pppCtrlTable* dataPtr)
{
    const f32 zero = LoadFloat(gPppYmMoveParabolaZero);
    _pppMngSt* pppMngSt = ppvMng;
    pppYmMoveParabolaWork* work = ParabolaWork(basePtr, dataPtr);

    work->m_acceleration = zero;
    work->m_velocity = zero;
    work->m_distance = zero;
    work->m_frame = 1;

    if ((s32)Game.m_currentSceneId == 7) {
        Vec matrixOffset;

        pppCopyVector(work->m_basePosition, *ParabolaBasePosition(pppMngSt));

        matrixOffset.x = ppvMng->m_matrix.value[0][3];
        matrixOffset.y = ppvMng->m_matrix.value[1][3];
        matrixOffset.z = ppvMng->m_matrix.value[2][3];

        pppAddVector(work->m_basePosition, work->m_basePosition, matrixOffset);
        pppCopyVector(pppMngSt->m_paramVec0, work->m_basePosition);
        pppMngSt->m_paramVec0.x = pppMngSt->m_paramVec0.x + LoadFloat(gPppYmMoveParabolaYOffsetStep);
    }
}
