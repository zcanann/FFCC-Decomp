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

extern int gPppCalcDisabled;

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

    tempUp.y = 1.0f;
    tempUp.x = 0.0f;
    tempUp.z = 0.0f;

    PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &temp1);
    PSVECNormalize(&temp1, &temp1);

    work->m_angle = gPppYmMoveCircleRadToAngleScale * acosf(PSVECDotProduct(&tempUp, &temp1));

    if ((temp1.x <= 0.0f && temp1.z >= 0.0f) || (temp1.x >= 0.0f && temp1.z >= 0.0f)) {
        work->m_angle = gPppYmMoveCircleTurnSpan - work->m_angle;
    }

    work->m_radiusStepStep = 0.0f;
    work->m_radiusStep = 0.0f;
    work->m_radius = 0.0f;
    work->m_angleStepStepStep = 0.0f;
    work->m_angleStepStep = 0.0f;
    work->m_angleStep = 0.0f;
    pppCopyVector(work->m_center, *(Vec*)((u8*)pppMngSt + 0x58));
    work->m_hasInit = 0;
}

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

    if (work->m_angle > gPppYmMoveCircleTurnSpan) {
        work->m_angle -= gPppYmMoveCircleTurnSpan;
    }
    if (work->m_angle < gPppYmMoveCircleZero) {
        work->m_angle += gPppYmMoveCircleTurnSpan;
    }

    tableIndex = (s32)((gPppYmMoveCircleAngleScale * (gPppYmMoveCircleAngleToTableScale * work->m_angle)) / gPppYmMoveCircleTableDivisor);
    sinAngle = *(f32*)((u8*)gPppTrigTable + (tableIndex & 0xFFFC));
    cosAngle = *(f32*)((u8*)gPppTrigTable + ((tableIndex + 0x4000) & 0xFFFC));
    radiusX = work->m_radius * cosAngle;
    radiusZ = work->m_radius * -sinAngle;
    nextPos.x = radiusX + work->m_center.x;
    nextPos.y = gPppYmMoveCircleZero;
    nextPos.y = *(f32*)(pppMngSt + 0xC);
    nextPos.z = radiusZ + work->m_center.z;

    pppCopyVector(*(Vec*)(pppMngSt + 0x48), *(Vec*)(pppMngSt + 0x8));
    pppCopyVector(*(Vec*)(pppMngSt + 0x8), nextPos);

    *(f32*)((u8*)pppMngStPtr + 0x84) = nextPos.x;
    *(f32*)((u8*)pppMngStPtr + 0x94) = nextPos.y;
    *(f32*)((u8*)pppMngStPtr + 0xA4) = nextPos.z;
    pppSetFpMatrix((_pppMngSt*)pppMngSt);
}


