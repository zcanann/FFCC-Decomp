#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "types.h"
#include "dolphin/mtx.h"
#include "dolphin/math.h"

struct pppYmMoveCircleWork {
    f32 m_angle;
    f32 m_angleStep;
    f32 m_angleStepStep;
    f32 m_angleStepStepStep;
    f32 m_radius;
    f32 m_radiusStep;
    f32 m_radiusStepStep;
    f32 m_unk1C;
    Vec m_center;
    u8 m_hasInit;
};

static const f32 kPppYmMoveCircleTurnSpan = 360.0f;
static const f32 kPppYmMoveCircleZero = 0.0f;
static const f32 kPppYmMoveCircleAngleScale = 32768.0f;
static const f32 kPppYmMoveCircleAngleToTableScale = 0.017453292f;
static const f32 kPppYmMoveCircleTableDivisor = 3.1415927f;
static const f32 kPppYmMoveCircleOne = 1.0f;
static const f32 kPppYmMoveCircleRadToAngleScale = 57.29578f;


/*
 * --INFO--
 * PAL Address: 0x800d160c
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmMoveCircle(pppYmMoveCircle* basePtr, pppYmMoveCircleStep* stepData, pppYmMoveCircleOffsets* offsetData)
{
    pppYmMoveCircleWork* work;
    _pppMngSt* pppMngSt;
    Vec nextPos;
    s32 tableIndex;
    f32 sinAngle;
    f32 cosAngle;
    f32 tableAngle;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (pppYmMoveCircleWork*)((u8*)basePtr + offsetData->m_serializedDataOffsets[0] + 0x80);
    pppMngSt = pppMngStPtr;

    work->m_radiusStep += work->m_radiusStepStep;
    work->m_radius += work->m_radiusStep;
    work->m_angleStepStep += work->m_angleStepStepStep;
    work->m_angleStep += work->m_angleStepStep;

    if (stepData->m_graphId == basePtr->m_graphId) {
        work->m_radius += stepData->m_radius;
        work->m_radiusStep += stepData->m_radiusStep;
        work->m_radiusStepStep += stepData->m_radiusStepStep;
        work->m_angleStep += stepData->m_angleStep;
        work->m_angleStepStep += stepData->m_angleStepStep;
        work->m_angleStepStepStep += stepData->m_angleStepStepStep;
    }
    work->m_angle += work->m_angleStep;
    turnSpan = kPppYmMoveCircleTurnSpan;

    if (work->m_angle > gPppYmMoveCircleTurnSpan) {
        work->m_angle -= gPppYmMoveCircleTurnSpan;
    }
    if (work->m_angle < kPppYmMoveCircleZero) {
        work->m_angle += kPppYmMoveCircleTurnSpan;
    }

    nextPos.y = kPppYmMoveCircleZero;
    {
        f32 tableAngle =
            (kPppYmMoveCircleAngleScale * (kPppYmMoveCircleAngleToTableScale * work->m_angle)) /
            kPppYmMoveCircleTableDivisor;
        tableIndex = (s32)tableAngle;
    }
    sinAngle = *(f32*)((u8*)gPppTrigTable + (tableIndex & 0xFFFC));
    cosAngle = *(f32*)((u8*)gPppTrigTable + ((tableIndex + 0x4000) & 0xFFFC));
    nextPos.x = work->m_radius * cosAngle;
    nextPos.z = work->m_radius * -sinAngle;
    nextPos.x += work->m_center.x;
    nextPos.y = pppMngSt->m_position.y;
    nextPos.z += work->m_center.z;

    pppCopyVector(*(Vec*)&pppMngSt->m_userFloat0, pppMngSt->m_position);
    pppCopyVector(pppMngSt->m_position, nextPos);

    pppMngStPtr->m_matrix.value[0][3] = nextPos.x;
    pppMngStPtr->m_matrix.value[1][3] = nextPos.y;
    pppMngStPtr->m_matrix.value[2][3] = nextPos.z;
    pppSetFpMatrix(pppMngSt);
}

/*
 * --INFO--
 * PAL Address: 0x800d183c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmMoveCircle(pppYmMoveCircle* basePtr, pppYmMoveCircleOffsets* offsetData)
{
    Vec tempUp;
    Vec temp1;
    _pppMngSt* pppMngSt;
    s32 offset;
    pppYmMoveCircleWork* work;

    pppMngSt = pppMngStPtr;
    offset = offsetData->m_serializedDataOffsets[0];
    work = (pppYmMoveCircleWork*)((u8*)basePtr + offset + 0x80);

    tempUp.x = kPppYmMoveCircleOne;
    tempUp.y = kPppYmMoveCircleZero;
    tempUp.z = kPppYmMoveCircleZero;

    PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &temp1);
    PSVECNormalize(&temp1, &temp1);

    work->m_angle = kPppYmMoveCircleRadToAngleScale * (f32)acos(PSVECDotProduct(&tempUp, &temp1));

    if ((temp1.x <= kPppYmMoveCircleZero && temp1.z >= kPppYmMoveCircleZero) ||
        (temp1.x >= kPppYmMoveCircleZero && temp1.z >= kPppYmMoveCircleZero)) {
        work->m_angle = kPppYmMoveCircleTurnSpan - work->m_angle;
    }

    work->m_radiusStepStep = kPppYmMoveCircleZero;
    work->m_radiusStep = kPppYmMoveCircleZero;
    work->m_radius = kPppYmMoveCircleZero;
    work->m_angleStepStepStep = kPppYmMoveCircleZero;
    work->m_angleStepStep = kPppYmMoveCircleZero;
    work->m_angleStep = kPppYmMoveCircleZero;
    pppCopyVector(work->m_center, *(Vec*)((u8*)pppMngSt + 0x58));
    work->m_hasInit = 0;
}
