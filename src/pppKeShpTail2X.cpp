#include "ffcc/pppKeShpTail2X.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppKeShpTail2XZero;
extern const float kPppKeShpTail2XAlphaScale;
extern const float FLOAT_80330508;
extern int gPppCalcDisabled;
}
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>

extern "C" {
int __cntlzw(unsigned int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char);

void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);
}

struct KeShpTail2XStep {
    u8 _pad0[4];
    s32 m_dataValIndex;
    s32 m_frameStep;
    float m_scaleStart;
    float m_scaleEnd;
    u8 m_colorStartR;
    u8 m_colorStartG;
    u8 m_colorStartB;
    u8 m_colorStartA;
    u8 m_colorEndR;
    u8 m_colorEndG;
    u8 m_colorEndB;
    u8 m_colorEndA;
    float m_stepDistance;
    u16 m_drawCount;
    u8 m_drawFirst;
    u8 m_drawA;
    u8 m_drawB;
    u8 m_useEnvDepth;
    u8 m_worldSpaceMode;
    u8 _pad27;
    u8 m_zDisable;
    u8 m_blendMode;
    u8 _pad2A[2];
    float m_envDepth;
};

struct KeShpTail2XShapeFrame {
    s16 m_shapeOffset;
    s16 m_duration;
    u8 m_flags;
    u8 _pad5[3];
};

struct KeShpTail2XWork {
    u8 m_count;
    u8 m_head;
    u16 m_frameAcc;
    u16 m_shapeFrame;
    u16 m_shapePrevFrame;
    Vec m_posHistory[31];
};

inline void U8ToF32(pppFVECTOR4* dest, u8* src)
{
    dest->x = src[0];
    dest->y = src[1];
    dest->z = src[2];
    dest->w = src[3];
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
void pppKeShpTail2XDes(void* obj, _pppCtrlTable* param_2)
{
    KeShpTail2XWork* work = (KeShpTail2XWork*)((u8*)obj + param_2->m_serializedDataOffsets[0] + 0x80);

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
void pppKeShpTail2XCon(void* obj, _pppCtrlTable* param_2)
{
    KeShpTail2XWork* work = (KeShpTail2XWork*)((u8*)obj + param_2->m_serializedDataOffsets[0] + 0x80);

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
void pppKeShpTail2XDraw(struct pppKeShpTail2X* obj, pppKeShpTail2XUnkB* param_2, _pppCtrlTable* param_3)
{
    KeShpTail2XStep* step = (KeShpTail2XStep*)param_2;
    KeShpTail2XWork* work;
    long** shapeTable;
    long* shapeEntry;
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
    s32 dataValIndex;

    zero = kPppKeShpTail2XZero;
    dataValIndex = step->m_dataValIndex;
    if (dataValIndex == 0xffff) {
        return;
    }

    count = step->m_drawCount;
    invCountMinusOne = (float)(count - 1);
    alphaMul = (float)*(s16*)((u8*)obj + 0x86 + param_3->m_serializedDataOffsets[1]) / kPppKeShpTail2XAlphaScale;
    U8ToF32(&colorStart, &step->m_colorStartR);
    U8ToF32(&colorEnd, &step->m_colorEndR);
    colorStart.w *= alphaMul;
    colorEnd.w *= alphaMul;
    colorR = colorStart.x;
    colorG = colorStart.y;
    colorB = colorStart.z;
    colorA = colorStart.w;
    if (invCountMinusOne != zero) {
        colorStep.x = (colorStart.x - colorEnd.x) / invCountMinusOne;
        colorStep.y = (colorStart.y - colorEnd.y) / invCountMinusOne;
        colorStep.z = (colorStart.z - colorEnd.z) / invCountMinusOne;
        colorStep.w = (colorStart.w - colorEnd.w) / invCountMinusOne;
    } else {
        colorStep.x = FLOAT_80330508;
        colorStep.y = FLOAT_80330508;
        colorStep.z = FLOAT_80330508;
        colorStep.w = FLOAT_80330508;
    }
    colorStepR = colorStep.x;
    colorStepG = colorStep.y;
    colorStepB = colorStep.z;
    colorStepA = colorStep.w;

    work = (KeShpTail2XWork*)((u8*)obj + 0x80 + param_3->m_serializedDataOffsets[0]);
    shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
    shapeEntry = (long*)((u8*)*shapeTable + *(s16*)((u8*)*shapeTable + (work->m_shapePrevFrame << 3) + 0x10));

    pppCopyMatrix(localBase, obj->pppPObject.m_localMatrix);
    pppUnitMatrix(drawMtx);

    drawScale = step->m_scaleStart;
    scaleStepDelta = (step->m_scaleStart - step->m_scaleEnd) / invCountMinusOne;
    trailStep = step->m_stepDistance * pppMngStPtr->m_scale.x;

    curIndex = work->m_head;
    nextIndex = curIndex + 1;
    lastIndex = work->m_count - 1;
    segBaseX = work->m_posHistory[curIndex].x;
    segBaseY = work->m_posHistory[curIndex].y;
    segBaseZ = work->m_posHistory[curIndex].z;
    if (curIndex == lastIndex) {
        nextIndex = 0;
    }
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
        PSMTXScaleApply(obj->pppPObject.m_localMatrix.value, obj->field_0x40.value,
                        localBase.value[0][0] * (drawScale * pppMngStPtr->m_scale.x),
                        localBase.value[1][1] * (drawScale * pppMngStPtr->m_scale.y),
                        localBase.value[2][2] * (drawScale * pppMngStPtr->m_scale.z));
        PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
        PSMTXCopy(obj->field_0x40.value, drawMtx.value);
    } else if (step->m_worldSpaceMode == 1) {
        pppUnitMatrix(drawMtx);
        drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * pppMngStPtr->m_scale.x);
        drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * pppMngStPtr->m_scale.y);
        drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * pppMngStPtr->m_scale.z);
        PSMTXMultVec(ppvCameraMatrix, &pos, &pos);
    }

    drawMtx.value[0][3] = pos.x;
    drawMtx.value[1][3] = pos.y;
    drawMtx.value[2][3] = pos.z;

    zEnable = (u32)__cntlzw((u32)step->m_zDisable) >> 5;
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((void*)0, &drawMtx,
                                                               (step->m_useEnvDepth != 0) ? step->m_envDepth : kPppKeShpTail2XZero, 0,
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
    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(shapeEntry, pppEnvStPtr->m_materialSetPtr, step->m_blendMode);

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

advance_segment:
    if (nextIndex == lastIndex) {
        nextIndex = 0;
        goto wrapped_segment;
    }
    nextIndex++;
wrapped_segment:
    if (nextIndex == work->m_head) {
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
    segLen = PSVECDistance(&zeroVec, &seg);
    segCursor = trailLen;
    segRemain += segLen;
    goto draw_loop;
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
void pppKeShpTail2X(struct pppKeShpTail2X* obj, pppKeShpTail2XUnkB* param_2, _pppCtrlTable* param_3)
{
    KeShpTail2XStep* step;
    KeShpTail2XWork* work;
    pppFMATRIX outMatrix;
    Vec historyPos ATTRIBUTE_ALIGN(8);
    Vec initPos ATTRIBUTE_ALIGN(8);
    Vec pos ATTRIBUTE_ALIGN(8);

    if (gPppCalcDisabled != 0) {
        return;
    }

    step = (KeShpTail2XStep*)param_2;
    work = (KeShpTail2XWork*)((u8*)obj + param_3->m_serializedDataOffsets[0] + 0x80);

    if (obj->pppPObject.m_graphId == 0) {
        if (step->m_worldSpaceMode == 0) {
            initPos.x = obj->pppPObject.m_localMatrix.value[0][3];
            initPos.y = obj->pppPObject.m_localMatrix.value[1][3];
            initPos.z = obj->pppPObject.m_localMatrix.value[2][3];
        } else if (step->m_worldSpaceMode == 1) {
            pppMulMatrix(outMatrix, pppMngStPtr->m_matrix, obj->pppPObject.m_localMatrix);
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
        pos.x = obj->pppPObject.m_localMatrix.value[0][3];
        pos.y = obj->pppPObject.m_localMatrix.value[1][3];
        pos.z = obj->pppPObject.m_localMatrix.value[2][3];
    } else if (step->m_worldSpaceMode == 1) {
        pppMulMatrix(outMatrix, pppMngStPtr->m_matrix, obj->pppPObject.m_localMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector(work->m_posHistory[work->m_head], pos);

    {
        long** shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
        u8* shape = (u8*)*shapeTable;
        u16 shapeFrame;
        KeShpTail2XShapeFrame* frameEntry;

        shapeFrame = work->m_shapeFrame;
        work->m_shapePrevFrame = shapeFrame;

        work->m_frameAcc += step->m_frameStep;
        frameEntry = reinterpret_cast<KeShpTail2XShapeFrame*>(shape + ((u32)shapeFrame << 3) + 0x10);
        if (work->m_frameAcc >= frameEntry->m_duration) {
            work->m_frameAcc -= frameEntry->m_duration;
            work->m_shapeFrame++;
            if (work->m_shapeFrame >= *(s16*)(shape + 6)) {
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
