#include "ffcc/pppKeShpTail2X.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppKeShpTail2XZero = 0.0f;
extern const float kPppKeShpTail2XAlphaScale = 16384.0f;
extern const float kPppKeShpTail2XHalf = 0.5f;
extern const double kPppKeShpTail2XSignedIntBias = 4503601774854144.0;
extern const double kPppKeShpTail2XUnsignedIntBias = 4503599627370496.0;
}
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>

STATIC_ASSERT(offsetof(struct pppKeShpTail2X, m_object.m_workArea) == 0x80);

struct KeShpTail2XWork {
    u8 m_count;
    u8 m_head;
    u16 m_frameAcc;
    u16 m_shapeFrame;
    u16 m_shapePrevFrame;
    Vec m_posHistory[31];
};

struct KeShpTail2XAlphaWork {
    u8 _pad0[6];
    s16 m_alpha;
};
STATIC_ASSERT(offsetof(KeShpTail2XAlphaWork, m_alpha) == 6);

STATIC_ASSERT(sizeof(KeShpTail2XDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(KeShpTail2XDataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(KeShpTail2XDataOffsets, m_alphaWorkOffset) == 0x4);

static inline KeShpTail2XDataOffsets* GetKeShpTail2XDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail2XDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline KeShpTail2XWork* GetKeShpTail2XWork(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail2XWork*>(obj->m_workArea + GetKeShpTail2XDataOffsets(ctrl)->m_workOffset);
}

static inline KeShpTail2XAlphaWork* GetKeShpTail2XAlphaWork(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<KeShpTail2XAlphaWork*>(
        obj->m_workArea + GetKeShpTail2XDataOffsets(ctrl)->m_alphaWorkOffset);
}

/*
 * --INFO--
 * PAL Address: 0x80088698
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDes(_pppPObject* obj, _pppCtrlTable* param_2)
{
    KeShpTail2XWork* work = GetKeShpTail2XWork(obj, param_2);

    work->m_frameAcc = 0;
    work->m_shapeFrame = 0;
    work->m_shapePrevFrame = 0;
    work->m_head = 0;
    work->m_count = 0x1f;
    memset(work->m_posHistory, 0, sizeof(work->m_posHistory));
}

/*
 * --INFO--
 * PAL Address: 0x800886f0
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XCon(_pppPObject* obj, _pppCtrlTable* param_2)
{
    KeShpTail2XWork* work = GetKeShpTail2XWork(obj, param_2);

    work->m_frameAcc = 0;
    work->m_shapeFrame = 0;
    work->m_shapePrevFrame = 0;
    work->m_head = 0;
    work->m_count = 0x1f;
    memset(work->m_posHistory, 0, sizeof(work->m_posHistory));
}

/*
 * --INFO--
 * PAL Address: 0x80088748
 * PAL Size: 1796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDraw(struct pppKeShpTail2X* obj, pppKeShpTail2XStep* step, _pppCtrlTable* param_3)
{
    KeShpTail2XWork* work;
    pppShapeSt* shape;
    tagOAN3_SHAPE* shapeEntry;
    s32 count;
    float alphaMul;
    float zero;
    float colorR;
    float colorG;
    float colorB;
    float colorA;
    float colorStepR;
    float colorStepG;
    float colorStepB;
    float colorStepA;
    float invCountMinusOne;
    pppFVECTOR4 colorStart;
    pppFVECTOR4 colorEnd;
    pppFVECTOR4 colorStep;
    pppFMATRIX localBase;
    pppFMATRIX drawMtx;
    Vec zeroVec ATTRIBUTE_ALIGN(8);
    Vec pos ATTRIBUTE_ALIGN(8);
    Vec seg ATTRIBUTE_ALIGN(8);
    Vec initialSeg ATTRIBUTE_ALIGN(8);
    float trailLen;
    float segLen;
    float segCursor;
    float segRemain;
    float segDx;
    float segDy;
    float segDz;
    float segBaseX;
    float segBaseY;
    float segBaseZ;
    float nextBaseX;
    float nextBaseY;
    float nextBaseZ;
    float drawScale;
    float trailStep;
    float scaleStepDelta;
    s32 curIndex;
    s32 nextIndex;
    s32 lastIndex;
    u8 zEnable;
    u32 dataValIndex;

    zero = kPppKeShpTail2XZero;
    dataValIndex = step->m_dataValIndex;
    if (dataValIndex == 0xffff) {
        return;
    }

    count = step->m_drawCount;
    invCountMinusOne = (float)(count - 1);
    alphaMul = (float)GetKeShpTail2XAlphaWork(&obj->m_object, param_3)->m_alpha / kPppKeShpTail2XAlphaScale;
    colorStart.w = step->m_colorStartA;
    colorEnd.w = step->m_colorEndA;
    colorStart.x = step->m_colorStartR;
    colorStart.y = step->m_colorStartG;
    colorStart.z = step->m_colorStartB;
    colorEnd.x = step->m_colorEndR;
    colorEnd.y = step->m_colorEndG;
    colorEnd.z = step->m_colorEndB;
    colorStart.w *= alphaMul;
    colorEnd.w *= alphaMul;
    colorA = colorStart.w;
    colorR = colorStart.x;
    colorG = colorStart.y;
    colorB = colorStart.z;
    if (invCountMinusOne != zero) {
        colorStep.x = (colorStart.x - colorEnd.x) / invCountMinusOne;
        colorStep.y = (colorStart.y - colorEnd.y) / invCountMinusOne;
        colorStep.z = (colorStart.z - colorEnd.z) / invCountMinusOne;
        colorStep.w = (colorStart.w - colorEnd.w) / invCountMinusOne;
    } else {
        colorStep.x = colorStep.y = colorStep.z = colorStep.w = kPppKeShpTail2XHalf;
    }
    colorStepR = colorStep.x;
    colorStepG = colorStep.y;
    colorStepB = colorStep.z;
    colorStepA = colorStep.w;

    work = GetKeShpTail2XWork(&obj->m_object, param_3);
    shape = ppvEnv->m_resourceTables.m_shapeTablePtr[dataValIndex];
    pppShapeAnimData* shapeAnim = static_cast<pppShapeAnimData*>(shape->m_animData);
    shapeEntry = pppShapeFrame(shapeAnim, work->m_shapePrevFrame);

    pppCopyMatrix(localBase, obj->m_object.m_localMatrix);
    pppUnitMatrix(drawMtx);

    drawScale = step->m_scaleStart;
    scaleStepDelta = (step->m_scaleStart - step->m_scaleEnd) / invCountMinusOne;
    trailStep = step->m_stepDistance * ppvMng->m_scale.x;

    curIndex = work->m_head;
    nextIndex = curIndex + 1;
    lastIndex = work->m_count - 1;
    segBaseX = work->m_posHistory[curIndex].x;
    segBaseY = work->m_posHistory[curIndex].y;
    segBaseZ = work->m_posHistory[curIndex].z;
    if (nextIndex == work->m_count) {
        nextIndex = 0;
    }
    nextBaseX = work->m_posHistory[nextIndex].x;
    nextBaseY = work->m_posHistory[nextIndex].y;
    nextBaseZ = work->m_posHistory[nextIndex].z;
    segDx = nextBaseX - segBaseX;
    segDy = nextBaseY - segBaseY;
    segDz = nextBaseZ - segBaseZ;
    initialSeg.x = segDx;
    initialSeg.y = segDy;
    initialSeg.z = segDz;
    zeroVec.x = zero;
    zeroVec.y = zero;
    zeroVec.z = zero;
    segLen = PSVECDistance(&zeroVec, &initialSeg);
    segRemain = segLen;
    segCursor = zero;

    if (step->m_drawFirst == 0) {
        goto update_step;
    }

draw_loop:
    pos.x = segBaseX;
    pos.y = segBaseY;
    pos.z = segBaseZ;

    if (step->m_worldSpaceMode == 0) {
        PSMTXScaleApply(obj->m_object.m_localMatrix.value, obj->m_object.m_drawMatrix.value,
                        localBase.value[0][0] * (drawScale * ppvMng->m_scale.x),
                        localBase.value[1][1] * (drawScale * ppvMng->m_scale.y),
                        localBase.value[2][2] * (drawScale * ppvMng->m_scale.z));
        PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
        PSMTXCopy(obj->m_object.m_drawMatrix.value, drawMtx.value);
    } else if (step->m_worldSpaceMode == 1) {
        pppUnitMatrix(drawMtx);
        drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * ppvMng->m_scale.x);
        drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * ppvMng->m_scale.y);
        drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * ppvMng->m_scale.z);
        PSMTXMultVec(ppvCameraMatrix, &pos, &pos);
    }

    drawMtx.value[0][3] = pos.x;
    drawMtx.value[1][3] = pos.y;
    drawMtx.value[2][3] = pos.z;

    zEnable = (u32)__cntlzw((u32)step->m_zDisable) >> 5;
    pppSetDrawEnv(0, &drawMtx, (step->m_useEnvDepth != 0) ? step->m_envDepth : kPppKeShpTail2XZero, 0,
                  step->m_drawA, step->m_blendMode, 0, zEnable, 1, 0);

    {
        GXColor amb;
        amb.r = (u8)colorR;
        amb.g = (u8)colorG;
        amb.b = (u8)colorB;
        amb.a = (u8)colorA;
        GXSetChanAmbColor(GX_COLOR0A0, amb);
    }

    pppSetBlendMode(step->m_blendMode);
    pppDrawShp(shapeEntry, ppvEnv->m_materialSetPtr, step->m_blendMode);

update_step:
    count--;
    if (count == 0) {
        return;
    }

    colorR -= colorStepR;
    colorG -= colorStepG;
    colorB -= colorStepB;
    colorA -= colorStepA;
    drawScale -= scaleStepDelta;
    if (trailStep <= zero) {
        return;
    }

advance_segment:
    if (segRemain >= trailStep) {
        pos.x = (segDx * segCursor) / segLen + segBaseX;
        pos.y = (segDy * segCursor) / segLen + segBaseY;
        pos.z = (segDz * segCursor) / segLen + segBaseZ;
        segCursor += trailStep;
        segRemain -= trailStep;
        segBaseX = pos.x;
        segBaseY = pos.y;
        segBaseZ = pos.z;
        goto draw_loop;
    }

    nextIndex++;
    if (nextIndex > lastIndex) {
        nextIndex = 0;
    }
    if (nextIndex == curIndex) {
        return;
    }

move_next_segment:
    trailLen = segCursor - segLen;
    segBaseX = nextBaseX;
    segBaseY = nextBaseY;
    segBaseZ = nextBaseZ;
    nextBaseX = work->m_posHistory[nextIndex].x;
    nextBaseY = work->m_posHistory[nextIndex].y;
    nextBaseZ = work->m_posHistory[nextIndex].z;
    segDx = nextBaseX - segBaseX;
    segDy = nextBaseY - segBaseY;
    segDz = nextBaseZ - segBaseZ;
    seg.x = segDx;
    seg.y = segDy;
    seg.z = segDz;
    zeroVec.x = zero;
    zeroVec.y = zero;
    zeroVec.z = zero;
    segLen = PSVECDistance(&zeroVec, &seg);
    segCursor = trailLen;
    segRemain += segLen;
    goto advance_segment;
}

/*
 * --INFO--
 * PAL Address: 0x80088e4c
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2X(struct pppKeShpTail2X* obj, pppKeShpTail2XStep* step, _pppCtrlTable* param_3)
{
    KeShpTail2XWork* work;
    pppFMATRIX outMatrix;
    Vec historyPos ATTRIBUTE_ALIGN(8);
    Vec initPos ATTRIBUTE_ALIGN(8);
    Vec pos ATTRIBUTE_ALIGN(8);

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetKeShpTail2XWork(&obj->m_object, param_3);

    if (obj->m_object.m_graphId == 0) {
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
        s32 count = work->m_count;
        for (; count > 0; count--) {
            pppCopyVector(*history, historyPos);
            history++;
        }
    }

    if (work->m_head == 0) {
        work->m_head = work->m_count;
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

    {
        pppShapeAnimData* shape =
            static_cast<pppShapeAnimData*>(ppvEnv->m_resourceTables.m_shapeTablePtr[step->m_dataValIndex]->m_animData);
        u16 shapeFrame;
        pppShapeAnimFrame* frameEntry;

        shapeFrame = work->m_shapeFrame;
        work->m_shapePrevFrame = shapeFrame;

        work->m_frameAcc += step->m_frameStep;
        frameEntry = &shape->m_frames[shapeFrame];
        if (work->m_frameAcc >= frameEntry->m_duration) {
            work->m_frameAcc -= frameEntry->m_duration;
            work->m_shapeFrame++;
            if (work->m_shapeFrame >= shape->m_frameCount) {
                if ((frameEntry->m_flags & 0x80) != 0) {
                    work->m_shapeFrame = 0;
                    work->m_frameAcc = 0;
                } else {
                    work->m_frameAcc = 0;
                    work->m_shapeFrame--;
                }
            }
        }
    }
}
