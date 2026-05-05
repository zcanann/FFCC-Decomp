#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include "types.h"
#include "dolphin/mtx.h"

extern "C" double acos(double);

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
extern "C" void pppFrameYmMoveCircle(_pppPObject* basePtr, pppYmMoveCircleStep* stepData, _pppCtrlTable* offsetData)
{
    pppYmMoveCircleWork* work;
    int* serializedDataOffsets;
    _pppMngSt* pppMngSt;
    Vec nextPos;
    s32 tableIndex;
    f32 sinAngle;
    f32 cosAngle;

    if (gPppCalcDisabled != 0) {
        return;
    }

    serializedDataOffsets = offsetData->m_serializedDataOffsets;
    work = (pppYmMoveCircleWork*)(basePtr->m_workArea + serializedDataOffsets[0]);
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

    if (work->m_angle > 360.0f) {
        work->m_angle -= 360.0f;
    }
    if (work->m_angle < 0.0f) {
        work->m_angle += 360.0f;
    }

    {
        f32 tableAngle =
            (32768.0f * (0.017453292f * work->m_angle)) /
            3.1415927f;
        tableIndex = (s32)tableAngle;
    }
    nextPos.y = 0.0f;
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
extern "C" void pppConstructYmMoveCircle(_pppPObject* basePtr, _pppCtrlTable* offsetData)
{
    Vec tempUp;
    Vec temp1;
    _pppMngSt* pppMngSt;
    s32 offset;
    pppYmMoveCircleWork* work;

    pppMngSt = pppMngStPtr;
    offset = offsetData->m_serializedDataOffsets[0];
    work = (pppYmMoveCircleWork*)(basePtr->m_workArea + offset);

    tempUp.x = 1.0f;
    tempUp.y = 0.0f;
    tempUp.z = 0.0f;

    PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &temp1);
    PSVECNormalize(&temp1, &temp1);

    work->m_angle = 57.29578f * (f32)acos(PSVECDotProduct(&tempUp, &temp1));

    if ((temp1.x <= 0.0f && temp1.z >= 0.0f) ||
        (temp1.x >= 0.0f && temp1.z >= 0.0f)) {
        work->m_angle = 360.0f - work->m_angle;
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
