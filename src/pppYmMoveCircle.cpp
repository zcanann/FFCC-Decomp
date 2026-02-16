#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppPart.h"
#include "types.h"
#include "dolphin/mtx.h"
#include <math.h>

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

extern s32 DAT_8032ed70;
extern unsigned char* lbl_8032ED50;
extern f32 lbl_801EC9F0[];
extern f32 lbl_80330D78;
extern f32 lbl_80330D7C;
extern f32 lbl_80330D80;
extern f32 lbl_80330D84;
extern f32 lbl_80330D88;
extern f32 lbl_80330D8C;
extern f32 lbl_80330D90;
extern "C" double acos(double);

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
    Vec temp2;
    Vec temp1;
    u8* pppMngSt = lbl_8032ED50;
    pppYmMoveCircleWork* work = (pppYmMoveCircleWork*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);

    PSVECSubtract((Vec*)(pppMngSt + 0x68), (Vec*)(pppMngSt + 0x58), &temp1);
    PSVECNormalize(&temp1, &temp1);

    temp2.x = lbl_80330D7C;
    temp2.y = lbl_80330D8C;
    temp2.z = lbl_80330D7C;
    double angle = acos((double)PSVECDotProduct(&temp2, &temp1));
    work->m_angle = lbl_80330D90 * (f32)angle;

    if ((temp1.x <= lbl_80330D7C && temp1.z >= lbl_80330D7C) ||
        (temp1.x >= lbl_80330D7C && temp1.z >= lbl_80330D7C)) {
        work->m_angle = lbl_80330D78 - work->m_angle;
    }

    work->m_angleStep = lbl_80330D7C;
    work->m_angleStepStep = lbl_80330D7C;
    work->m_angleStepStepStep = lbl_80330D7C;
    work->m_radius = lbl_80330D7C;
    work->m_radiusStep = lbl_80330D7C;
    work->m_radiusStepStep = lbl_80330D7C;
    pppCopyVector(work->m_center, *(Vec*)(pppMngSt + 0x58));
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
    Vec nextPos;
    s32 tableIndex;

    if (DAT_8032ed70 != 0) {
        return;
    }

    work = (pppYmMoveCircleWork*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);

    work->m_radiusStep += work->m_radiusStepStep;
    work->m_radius += work->m_radiusStep;
    work->m_angleStep += work->m_angleStepStep;
    work->m_angle += work->m_angleStep;

    if (stepData->m_graphId == basePtr->m_graphId) {
        work->m_radius += stepData->m_radius;
        work->m_radiusStep += stepData->m_radiusStep;
        work->m_radiusStepStep += stepData->m_radiusStepStep;
        work->m_angle += stepData->m_angle;
        work->m_angleStep += stepData->m_angleStep;
        work->m_angleStepStep += stepData->m_angleStepStep;
    }

    if (work->m_angle > lbl_80330D78) {
        work->m_angle -= lbl_80330D78;
    }
    if (work->m_angle < lbl_80330D7C) {
        work->m_angle += lbl_80330D78;
    }

    tableIndex = (s32)((lbl_80330D80 * (lbl_80330D84 * work->m_angle)) / lbl_80330D88);
    nextPos.x = (work->m_radius * *(f32*)((u8*)lbl_801EC9F0 + ((tableIndex + 0x4000) & 0xFFFC))) + work->m_center.x;
    nextPos.y = *(f32*)((u8*)lbl_8032ED50 + 0xC);
    nextPos.z = (work->m_radius * -(*(f32*)((u8*)lbl_801EC9F0 + (tableIndex & 0xFFFC)))) + work->m_center.z;

    pppCopyVector(*(Vec*)((u8*)lbl_8032ED50 + 0x48), *(Vec*)((u8*)lbl_8032ED50 + 0x8));
    pppCopyVector(*(Vec*)((u8*)lbl_8032ED50 + 0x8), nextPos);

    *(f32*)((u8*)lbl_8032ED50 + 0x84) = nextPos.x;
    *(f32*)((u8*)lbl_8032ED50 + 0x94) = nextPos.y;
    *(f32*)((u8*)lbl_8032ED50 + 0xA4) = nextPos.z;
    pppSetFpMatrix((_pppMngSt*)lbl_8032ED50);
}
