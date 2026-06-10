#include "ffcc/pppKeShpTail3X.h"
#include "global.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppShape.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

static const float kPppKeShpTail3XZero = 0.0f;
static const float kPppKeShpTail3XAlphaScale = 16384.0f;
static const float kPppKeShpTail3XHalf = 0.5f;
static const float kPppKeShpTail3XRandomMax = 65535.0f;
static const float kPppKeShpTail3XOne = 1.0f;
static const float kPppKeShpTail3XDegToRad = 0.017453292f;

static inline float LoadFloat(const float& value)
{
    return value;
}

STATIC_ASSERT(offsetof(struct pppKeShpTail3X, m_object.m_workArea) == 0x80);

struct KeShpTail3XWork {
    s16 m_values[24];
    Vec m_posHistory[28];
    u16 m_angles[28];
    u32 m_shapeData;
    u16 m_shapeFrame;
    u16 m_unk1be;
    u16 m_rand;
    u8 m_head;
    u8 m_initialized;
};
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_posHistory) == 0x30);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_angles) == 0x180);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_shapeData) == 0x1b8);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_shapeFrame) == 0x1bc);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_rand) == 0x1c0);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_head) == 0x1c2);
STATIC_ASSERT(offsetof(KeShpTail3XWork, m_initialized) == 0x1c3);
STATIC_ASSERT(sizeof(KeShpTail3XWork) == 0x1c4);

struct KeShpTail3XAlphaWork {
    u8 _pad0[6];
    s16 m_alpha;
};
STATIC_ASSERT(offsetof(KeShpTail3XAlphaWork, m_alpha) == 6);

STATIC_ASSERT(sizeof(KeShpTail3XDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(KeShpTail3XDataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(KeShpTail3XDataOffsets, m_alphaWorkOffset) == 0x4);

static inline KeShpTail3XDataOffsets* GetKeShpTail3XDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail3XDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline KeShpTail3XWork* GetKeShpTail3XWork(struct pppKeShpTail3X* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail3XWork*>(
        obj->m_object.m_workArea + GetKeShpTail3XDataOffsets(ctrl)->m_workOffset);
}

static inline KeShpTail3XAlphaWork* GetKeShpTail3XAlphaWork(struct pppKeShpTail3X* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail3XAlphaWork*>(
        obj->m_object.m_workArea + GetKeShpTail3XDataOffsets(ctrl)->m_alphaWorkOffset);
}

inline void S4ToF32(pppFVECTOR4* dest, s16* src)
{
    dest->x = src[0] >> 7;
    dest->y = src[1] >> 7;
    dest->z = src[2] >> 7;
    dest->w = src[3] >> 7;
}

/*
 * --INFO--
 * PAL Address: 0x8008922c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDes(_pppPObjLink* obj, _pppCtrlTable* ctrlTable)
{
    (void)obj;
    (void)ctrlTable;
}

/*
 * --INFO--
 * PAL Address: 0x80089230
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XCon(struct pppKeShpTail3X* obj, _pppCtrlTable* param_2)
{
    KeShpTail3XWork* work;
    KeShpTail3XDataOffsets* offsets;
    int i;
    float scale;

    offsets = GetKeShpTail3XDataOffsets(param_2);
    work = reinterpret_cast<KeShpTail3XWork*>(obj->m_object.m_workArea + offsets->m_workOffset);
    work->m_initialized = 0;
    work->m_head = 0;
    work->m_shapeFrame = 0;
    work->m_shapeData = 0;
    work->m_rand = (u16)rand();
    memset(work->m_values, 0, 8);
    memset(&work->m_values[4], 0, 8);
    memset(&work->m_values[8], 0, 8);
    memset(&work->m_values[12], 0, 8);
    memset(&work->m_values[16], 0, 8);
    memset(&work->m_values[20], 0, 8);

    scale = kPppKeShpTail3XZero;
    i = 0;
    do {
        s32 rnd = rand();
        work->m_angles[i] = (s16)(rnd - (rnd / 0x168) * 0x168);
        work->m_posHistory[i].z = scale;
        work->m_posHistory[i].y = scale;
        work->m_posHistory[i].x = scale;
        i++;
    } while (i < 0x1c);
}

/*
 * --INFO--
 * PAL Address: 0x80089360
 * PAL Size: 2624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma optimization_level 3
void pppKeShpTail3XDraw(struct pppKeShpTail3X* obj, struct pppKeShpTail3XStep* step, _pppCtrlTable* param_3)
{
    KeShpTail3XWork* work;
    s32 currentIndex;
    Vec* history;
    pppShapeAnimData* shapeAnim;
    int count;
    s32 nextIndex;
    u16 rng;
    s32 shapeFrameCount;
    tagOAN3_SHAPE* shapeEntry;
    float alphaMul;
    float invCountMinusOne;
    float xDiff;
    float yDiff;
    float zDiff;
    float wDiff;
    pppFVECTOR4 colorStart;
    pppFVECTOR4 colorEnd;
    float colorStepX;
    float colorStepY;
    float colorStepZ;
    float colorStepW;
    pppFMATRIX localBase;
    pppFMATRIX unitScratch;
    pppFMATRIX drawMtx;
    pppFMATRIX rotMtxA;
    pppFMATRIX rotMtxB;
    Vec zeroVecA;
    Vec initialSeg;
    Vec pos;
    Vec zeroVecB;
    Vec seg;
    float drawScale;
    float segDx;
    float segDy;
    float segDz;
    int life;
    s32 shapeFrameDuration;
    float shapeScale;
    float shapeScaleStep;
    float trailStep;
    float trailStepDelta;
    float segLen;
    float segRemain;
    float posX;
    float posY;
    float posZ;
    float startX;
    float startY;
    float startZ;
    float nextBaseX;
    float nextBaseY;
    float nextBaseZ;
    u8 zEnable;
    float segCursor = kPppKeShpTail3XZero;
    s32 dataValIndex;

    work = GetKeShpTail3XWork(obj, param_3);
    dataValIndex = step->m_dataValIndex;
    if (dataValIndex == 0xffff) {
        return;
    }

    count = step->m_drawCount;

    invCountMinusOne = (float)(count - 1);
    alphaMul = (float)GetKeShpTail3XAlphaWork(obj, param_3)->m_alpha /
               kPppKeShpTail3XAlphaScale;
    S4ToF32(&colorStart, &work->m_values[0]);
    S4ToF32(&colorEnd, &work->m_values[4]);
    colorStart.w *= alphaMul;
    colorEnd.w *= alphaMul;
    wDiff = colorStart.w - colorEnd.w;
    xDiff = colorStart.x - colorEnd.x;
    yDiff = colorStart.y - colorEnd.y;
    zDiff = colorStart.z - colorEnd.z;
    if (invCountMinusOne != kPppKeShpTail3XZero) {
        colorStepY = yDiff / invCountMinusOne;
        colorStepZ = zDiff / invCountMinusOne;
        colorStepW = wDiff / invCountMinusOne;
        colorStepX = xDiff / invCountMinusOne;
    } else {
        colorStepX = kPppKeShpTail3XHalf;
        colorStepY = colorStepX;
        colorStepZ = colorStepX;
        colorStepW = colorStepX;
    }

    shapeAnim = static_cast<pppShapeAnimData*>(ppvEnv->m_resourceTables.m_shapeTablePtr[dataValIndex]->m_animData);

    pppCopyMatrix(localBase, obj->m_object.m_localMatrix);
    pppUnitMatrix(unitScratch);

    shapeScale = (float)step->m_stepValue;
    shapeScaleStep = (shapeScale - (float)step->m_arg3) / invCountMinusOne;
    trailStep = step->m_stepDistance * ppvMng->m_scale.x;
    trailStepDelta = trailStep * (shapeScaleStep / shapeScale);
    if (trailStep == kPppKeShpTail3XZero) {
        count = 0;
    }

    history = work->m_posHistory;
    currentIndex = work->m_head;
    posX = history[currentIndex].x;
    posZ = history[currentIndex].z;
    posY = history[currentIndex].y;
    startZ = posZ;
    startX = posX;
    startY = posY;
    nextIndex = currentIndex + 1;
    if (currentIndex == 0x1b) {
        nextIndex = 0;
    }
    nextBaseX = history[nextIndex].x;
    nextBaseZ = history[nextIndex].z;
    segDx = nextBaseX - posX;
    nextBaseY = history[nextIndex].y;
    segDz = nextBaseZ - posZ;
    segDy = nextBaseY - posY;
    initialSeg.x = segDx;
    initialSeg.y = segDy;
    initialSeg.z = segDz;
    zeroVecA.z = kPppKeShpTail3XZero;
    zeroVecA.y = kPppKeShpTail3XZero;
    zeroVecA.x = kPppKeShpTail3XZero;
    segLen = PSVECDistance(&zeroVecA, &initialSeg);
    segRemain = segLen;
    life = work->m_shapeData;
    shapeFrameDuration = shapeAnim->m_frames[0].m_duration;
    rng = work->m_rand;
    shapeFrameCount = shapeAnim->m_frameCount;

    if (step->m_drawFirst == 0) {
        goto update_step;
    }

draw_loop:
    drawScale = shapeScale;

    {
        u32 lcg = (u32)rng * 0x80du + 7u;
        rng = (u16)lcg;
        drawScale *= -(((float)rng / kPppKeShpTail3XRandomMax) * step->m_randomScale - kPppKeShpTail3XOne);
        {
            u32 shapeIdx = (u32)(life + rng) / shapeFrameDuration;
            pppShapeAnimFrame* frame = &shapeAnim->m_frames[shapeIdx % (u32)shapeFrameCount];
            shapeEntry = reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) + frame->m_shapeOffset);
        }
    }

    pos.x = posX;
    pos.z = posZ;
    pos.y = posY;

    if (step->m_worldSpaceMode == 0) {
        PSMTXScaleApply(obj->m_object.m_localMatrix.value, obj->m_object.m_drawMatrix.value,
                        localBase.value[0][0] * (drawScale * ppvMng->m_scale.x),
                        localBase.value[1][1] * (drawScale * ppvMng->m_scale.y),
                        localBase.value[2][2] * (drawScale * ppvMng->m_scale.z));
        if ((step->m_rotateEnabled != 0) && (count != 0)) {
            PSMTXRotRad(rotMtxA.value, 'z', kPppKeShpTail3XDegToRad * (float)work->m_angles[count]);
            pppMulMatrix(obj->m_object.m_drawMatrix, rotMtxA, obj->m_object.m_drawMatrix);
        }
        PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
        PSMTXCopy(obj->m_object.m_drawMatrix.value, drawMtx.value);
    } else if (step->m_worldSpaceMode == 1) {
        pppUnitMatrix(drawMtx);
        drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * ppvMng->m_scale.x);
        drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * ppvMng->m_scale.y);
        drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * ppvMng->m_scale.z);
        if ((step->m_rotateEnabled != 0) && (count != 0)) {
            PSMTXRotRad(rotMtxB.value, 'z', kPppKeShpTail3XDegToRad * (float)work->m_angles[count]);
            pppMulMatrix(drawMtx, rotMtxB, drawMtx);
        }
        PSMTXMultVec(ppvCameraMatrix, &pos, &pos);
    }

    drawMtx.value[0][3] = pos.x;
    drawMtx.value[1][3] = pos.y;
    drawMtx.value[2][3] = pos.z;

    zEnable = (u8)((u32)__cntlzw((u32)step->m_zDisable) >> 5);
    pppSetDrawEnv(
        0, &drawMtx, (step->m_useEnvDepth != 0) ? step->m_envDepth : kPppKeShpTail3XZero, 0, step->m_drawA,
        step->m_blendMode, 0, zEnable, 1, 0);
    GXLoadPosMtxImm(drawMtx.value, 0);

    {
        GXColor amb;

        amb.r = (u8)colorStart.x;
        amb.g = (u8)colorStart.y;
        amb.b = (u8)colorStart.z;
        amb.a = (u8)colorStart.w;
        GXSetChanAmbColor(GX_COLOR0A0, amb);
    }

    pppSetBlendMode(step->m_blendMode);
    pppDrawShp(shapeEntry, ppvEnv->m_materialSetPtr, step->m_blendMode);

update_step:
    count--;
    if (count == 0) {
        return;
    }

    colorStart.x -= colorStepX;
    colorStart.y -= colorStepY;
    colorStart.z -= colorStepZ;
    colorStart.w -= colorStepW;
    shapeScale -= shapeScaleStep;
    trailStep -= trailStepDelta;
    if (trailStep <= kPppKeShpTail3XZero) {
        return;
    }

advance_segment:
    if (segRemain >= trailStep) {
        float ratio = segCursor / segLen;
        posX = segDx * ratio + startX;
        posZ = segDz * ratio + startZ;
        segCursor += trailStep;
        posY = segDy * ratio + startY;
        segRemain -= trailStep;
        goto draw_loop;
    }

    if (nextIndex++ == 0x1b) {
        nextIndex = 0;
    }
    if (nextIndex == currentIndex) {
        return;
    }

    startX = nextBaseX;
    startY = nextBaseY;
    startZ = nextBaseZ;
    segCursor -= segLen;
    nextBaseY = history[nextIndex].y;
    nextBaseZ = history[nextIndex].z;
    nextBaseX = history[nextIndex].x;
    segDy = nextBaseY - startY;
    segDz = nextBaseZ - startZ;
    segDx = nextBaseX - startX;
    seg.y = segDy;
    seg.z = segDz;
    seg.x = segDx;
    zeroVecB.z = kPppKeShpTail3XZero;
    zeroVecB.y = kPppKeShpTail3XZero;
    zeroVecB.x = kPppKeShpTail3XZero;
    segLen = PSVECDistance(&zeroVecB, &seg);
    segRemain += segLen;
    goto advance_segment;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x80089da0
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3X(struct pppKeShpTail3X* obj, struct pppKeShpTail3XStep* step, _pppCtrlTable* param_3)
{
    KeShpTail3XWork* work;
    pppFMATRIX outMatrix;
    Vec historyPos ATTRIBUTE_ALIGN(8);
    Vec initPos ATTRIBUTE_ALIGN(8);
    Vec pos ATTRIBUTE_ALIGN(8);

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetKeShpTail3XWork(obj, param_3);

    if ((obj->m_object.m_graphId == 0) && (obj->m_object.m_field7D != 0)) {
        work->m_initialized = 1;

        if (step->m_worldSpaceMode == 0) {
            initPos.x = obj->m_object.m_localMatrix.value[0][3];
            initPos.y = obj->m_object.m_localMatrix.value[1][3];
            initPos.z = obj->m_object.m_localMatrix.value[2][3];
        } else if (step->m_worldSpaceMode == 1) {
            pppMulMatrix(outMatrix, ppvMng->m_matrix, obj->m_object.m_localMatrix);
            initPos.x = outMatrix.value[0][3];
            initPos.y = outMatrix.value[1][3];
            initPos.z = outMatrix.value[2][3];
        }

        pppCopyVector(historyPos, initPos);
        Vec* history = work->m_posHistory;
        s32 i = 0x1c;
        do {
            pppCopyVector(*history, historyPos);
            history++;
            i--;
        } while (i > 0);
    }

    if (work->m_head == 0) {
        work->m_head = 0x1c;
    }
    work->m_head--;

    if (step->m_worldSpaceMode == 0) {
        pos.x = obj->m_object.m_localMatrix.value[0][3];
        pos.y = obj->m_object.m_localMatrix.value[1][3];
        pos.z = obj->m_object.m_localMatrix.value[2][3];
    } else if (step->m_worldSpaceMode == 1) {
        pppMulMatrix(outMatrix, ppvMng->m_matrix, obj->m_object.m_localMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector(work->m_posHistory[work->m_head], pos);

    work->m_values[8] += work->m_values[0xc];
    work->m_values[0] += work->m_values[8];
    work->m_values[9] += work->m_values[0xd];
    work->m_values[1] += work->m_values[9];
    work->m_values[10] += work->m_values[0xe];
    work->m_values[2] += work->m_values[10];
    work->m_values[0xb] += work->m_values[0xf];
    work->m_values[3] += work->m_values[0xb];
    work->m_values[0x10] += work->m_values[0x14];
    work->m_values[4] += work->m_values[0x10];
    work->m_values[0x11] += work->m_values[0x15];
    work->m_values[5] += work->m_values[0x11];
    work->m_values[0x12] += work->m_values[0x16];
    work->m_values[6] += work->m_values[0x12];
    work->m_values[0x13] += work->m_values[0x17];
    work->m_values[7] += work->m_values[0x13];

    if (obj->m_object.m_graphId == step->m_graphId) {
        work->m_values[0] += step->m_valueSteps[0];
        work->m_values[1] += step->m_valueSteps[1];
        work->m_values[2] += step->m_valueSteps[2];
        work->m_values[3] += step->m_valueSteps[3];
        work->m_values[8] += step->m_valueSteps[8];
        work->m_values[9] += step->m_valueSteps[9];
        work->m_values[10] += step->m_valueSteps[10];
        work->m_values[0xb] += step->m_valueSteps[11];
        work->m_values[0xc] += step->m_valueSteps[12];
        work->m_values[0xd] += step->m_valueSteps[13];
        work->m_values[0xe] += step->m_valueSteps[14];
        work->m_values[0xf] += step->m_valueSteps[15];
        work->m_values[4] += step->m_valueSteps[4];
        work->m_values[5] += step->m_valueSteps[5];
        work->m_values[6] += step->m_valueSteps[6];
        work->m_values[7] += step->m_valueSteps[7];
        work->m_values[0x10] += step->m_valueSteps[16];
        work->m_values[0x11] += step->m_valueSteps[17];
        work->m_values[0x12] += step->m_valueSteps[18];
        work->m_values[0x13] += step->m_valueSteps[19];
        work->m_values[0x14] += step->m_valueSteps[20];
        work->m_values[0x15] += step->m_valueSteps[21];
        work->m_values[0x16] += step->m_valueSteps[22];
        work->m_values[0x17] += step->m_valueSteps[23];
    }

    work->m_shapeData += step->m_initWork;
}
