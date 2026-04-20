#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "types.h"
#include "dolphin/mtx.h"
#include "math.h"

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
    int* serializedDataOffsets;
    u8* pppMngSt;
    Vec nextPos;
    s32 tableIndex;
    f32 sinAngle;
    f32 cosAngle;
    f32 radiusX;
    f32 radiusZ;
    f32 turnSpan;

    if (gPppCalcDisabled != 0) {
        return;
    }

    serializedDataOffsets = offsetData->m_serializedDataOffsets;
    work = (pppYmMoveCircleWork*)((u8*)basePtr + serializedDataOffsets[0] + 0x80);
    pppMngSt = (u8*)pppMngStPtr;

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
    turnSpan = gPppYmMoveCircleTurnSpan;

    if (work->m_angle > turnSpan) {
        work->m_angle -= turnSpan;
    }
    if (work->m_angle < gPppYmMoveCircleZero) {
        work->m_angle += gPppYmMoveCircleTurnSpan;
    }

    nextPos.y = gPppYmMoveCircleZero;
    {
        f32 tableAngle =
            (gPppYmMoveCircleAngleScale * (gPppYmMoveCircleAngleToTableScale * work->m_angle)) /
            gPppYmMoveCircleTableDivisor;
        tableIndex = (s32)tableAngle;
    }
    sinAngle = *(f32*)((u8*)gPppTrigTable + (tableIndex & 0xFFFC));
    cosAngle = *(f32*)((u8*)gPppTrigTable + ((tableIndex + 0x4000) & 0xFFFC));
    radiusX = work->m_radius * cosAngle;
    radiusZ = work->m_radius * -sinAngle;
    nextPos.x = radiusX;
    nextPos.z = radiusZ;
    nextPos.x += work->m_center.x;
    nextPos.y = *(f32*)(pppMngSt + 0xC);
    nextPos.z += work->m_center.z;

    pppCopyVector(*(Vec*)(pppMngSt + 0x48), *(Vec*)(pppMngSt + 0x8));
    pppCopyVector(*(Vec*)(pppMngSt + 0x8), nextPos);

    *(f32*)((u8*)pppMngStPtr + 0x84) = nextPos.x;
    *(f32*)((u8*)pppMngStPtr + 0x94) = nextPos.y;
    *(f32*)((u8*)pppMngStPtr + 0xA4) = nextPos.z;
    pppSetFpMatrix((_pppMngSt*)pppMngSt);
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
    const f32 kZero = 0.0f;
    const f32 kOne = 1.0f;
    Vec tempUp;
    Vec temp1;
    _pppMngSt* pppMngSt;
    s32 offset;
    pppYmMoveCircleWork* work;

    pppMngSt = pppMngStPtr;
    offset = offsetData->m_serializedDataOffsets[0];
    work = (pppYmMoveCircleWork*)((u8*)basePtr + offset + 0x80);

    tempUp.x = kOne;
    tempUp.y = kZero;
    tempUp.z = kZero;

    PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &temp1);
    PSVECNormalize(&temp1, &temp1);

    work->m_angle = gPppYmMoveCircleRadToAngleScale * (f32)acos(PSVECDotProduct(&tempUp, &temp1));

    if ((temp1.x <= kZero && temp1.z >= kZero) || (temp1.x >= kZero && temp1.z >= kZero)) {
        work->m_angle = gPppYmMoveCircleTurnSpan - work->m_angle;
    }

    work->m_radiusStepStep = kZero;
    work->m_radiusStep = kZero;
    work->m_radius = kZero;
    work->m_angleStepStepStep = kZero;
    work->m_angleStepStep = kZero;
    work->m_angleStep = kZero;
    pppCopyVector(work->m_center, *(Vec*)((u8*)pppMngSt + 0x58));
    work->m_hasInit = 0;
}
