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
    u8 m_skipFirst;
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

struct KeShpTail2XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
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

/*
 * --INFO--
 * PAL Address: 0x80088698
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDes(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
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
void pppKeShpTail2XCon(void* obj, void* param_2)
{
	u32 serializedOffset = **(u32**)((u8*)param_2 + 0xc);
	u8* tail = (u8*)obj + serializedOffset + 0x80;

	*(u16*)(tail + 2) = 0;
	*(u16*)(tail + 4) = 0;
	*(u16*)(tail + 6) = 0;
	tail[1] = 0;
	tail[0] = 0x1f;
	memset(tail + 8, 0, 0x174);
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
void pppKeShpTail2XDraw(struct pppKeShpTail2X* obj, pppKeShpTail2XUnkB* param_2, pppKeShpTail2XUnkC* param_3)
{
    KeShpTail2XStep* step = (KeShpTail2XStep*)param_2;
    KeShpTail2XOffsets* offsets = (KeShpTail2XOffsets*)param_3;
    KeShpTail2XWork* work;
    long** shapeTable;
    long* shapeEntry;
    s32 count;
    float alphaMul;
    float colorR;
    float colorG;
    float colorB;
    float colorA;
    float colorEndA;
    float zero;
    float colorStepR;
    float colorStepG;
    float colorStepB;
    float colorStepA;
    float invCountMinusOne;
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
    u32 zEnable;
    s32 dataValIndex;

    zero = kPppKeShpTail2XZero;
    dataValIndex = step->m_dataValIndex;
    if (dataValIndex == 0xffff) {
        return;
    }

    count = step->m_drawCount;
    invCountMinusOne = (float)(count - 1);
    alphaMul = (float)*(s16*)((u8*)obj + 0x86 + offsets->m_serializedDataOffsets[1]) / kPppKeShpTail2XAlphaScale;
    colorR = (float)step->m_colorStartR;
    colorG = (float)step->m_colorStartG;
    colorB = (float)step->m_colorStartB;
    colorA = (float)step->m_colorStartA * alphaMul;
    colorEndA = (float)step->m_colorEndA * alphaMul;
    if (invCountMinusOne != zero) {
        colorStepR = (colorR - (float)step->m_colorEndR) / invCountMinusOne;
        colorStepG = (colorG - (float)step->m_colorEndG) / invCountMinusOne;
        colorStepB = (colorB - (float)step->m_colorEndB) / invCountMinusOne;
        colorStepA = (colorA - colorEndA) / invCountMinusOne;
    } else {
        colorStepR = FLOAT_80330508;
        colorStepG = FLOAT_80330508;
        colorStepB = FLOAT_80330508;
        colorStepA = FLOAT_80330508;
    }

    work = (KeShpTail2XWork*)((u8*)obj + 0x80 + offsets->m_serializedDataOffsets[0]);
    shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
    shapeEntry = (long*)((u8*)*shapeTable + *(s16*)((u8*)*shapeTable + ((u16)work->m_shapePrevFrame << 3) + 0x10));

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

    if (step->m_skipFirst != 0) {
        goto move_next_segment;
    }

draw_loop:
    pos.x = segBaseX;
    pos.y = segBaseY;
    pos.z = segBaseZ;

    if (step->m_worldSpaceMode == 0) {
        PSMTXScaleApply(localBase.value, obj->field_0x40.value, drawScale * pppMngStPtr->m_scale.x,
                        drawScale * pppMngStPtr->m_scale.y,
                        drawScale * pppMngStPtr->m_scale.z);
        PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
        PSMTXCopy(obj->field_0x40.value, drawMtx.value);
    } else if (step->m_worldSpaceMode == 1) {
        pppUnitMatrix(drawMtx);
        drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * pppMngStPtr->m_scale.x);
        drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * pppMngStPtr->m_scale.y);
        drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * pppMngStPtr->m_scale.z);
        PSMTXMultVec(ppvCameraMatrix02, &pos, &pos);
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

    if (segRemain < trailStep) {
        goto advance_segment;
    }

    pos.x = segDx * (segCursor / segLen) + segBaseX;
    pos.y = segDy * (segCursor / segLen) + segBaseY;
    pos.z = segDz * (segCursor / segLen) + segBaseZ;
    segCursor += trailStep;
    segRemain -= trailStep;
    segBaseX = pos.x;
    segBaseY = pos.y;
    segBaseZ = pos.z;
    goto draw_loop;

advance_segment:
    nextIndex++;
    if (nextIndex == work->m_count) {
        nextIndex = 0;
    }
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
void pppKeShpTail2X(struct pppKeShpTail2X* obj, pppKeShpTail2XUnkB* param_2, pppKeShpTail2XUnkC* param_3)
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
    work = (KeShpTail2XWork*)((u8*)obj + ((KeShpTail2XOffsets*)param_3)->m_serializedDataOffsets[0] + 0x80);

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
