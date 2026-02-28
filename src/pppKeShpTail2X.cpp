#include "ffcc/pppKeShpTail2X.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <string.h>

extern int lbl_8032ED70;
extern float lbl_80330500;
extern float lbl_80330504;
extern _pppMngSt* pppMngStPtr;
extern _pppEnvSt* lbl_8032ED54;
extern _pppEnvSt* pppEnvStPtr;
extern Mtx ppvWorldMatrix;
extern Mtx ppvCameraMatrix02;

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
int __cntlzw(unsigned int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char);
void pppSetBlendMode__FUc(unsigned char);
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
    u8 m_zDisable;
    u8 m_blendMode;
    u8 _pad2B[2];
    float m_envDepth;
};

struct KeShpTail2XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

struct KeShpTail2XWork {
    u8 m_count;
    u8 m_head;
    u16 m_frameAcc;
    u16 m_shapeFrame;
    u16 m_shapePrevFrame;
    Vec m_posHistory[31];
};

struct KeShpTail2XObject {
    u8 _pad0[0xc];
    _pppPObject m_obj;
};

/*
 * --INFO--
 * PAL Address: 0x80088e4c
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2X(_pppPObject* obj, UnkB* param_2, UnkC* param_3)
{
    KeShpTail2XStep* step;
    KeShpTail2XWork* work;
    KeShpTail2XObject* tailObj;
    Vec pos;

    if (lbl_8032ED70 != 0) {
        return;
    }

    step = (KeShpTail2XStep*)param_2;
    tailObj = (KeShpTail2XObject*)obj;
    work = (KeShpTail2XWork*)((u8*)obj + 0x80 + ((KeShpTail2XOffsets*)param_3)->m_serializedDataOffsets[0]);

    if (tailObj->m_obj.m_graphId == 0) {
        if (step->m_worldSpaceMode == 0) {
            pos.x = tailObj->m_obj.m_localMatrix.value[0][3];
            pos.y = tailObj->m_obj.m_localMatrix.value[1][3];
            pos.z = tailObj->m_obj.m_localMatrix.value[2][3];
        } else if (step->m_worldSpaceMode == 1) {
            pppFMATRIX ownerMatrix;
            pppFMATRIX partMatrix;
            pppFMATRIX outMatrix;

            partMatrix = tailObj->m_obj.m_localMatrix;
            ownerMatrix = pppMngStPtr->m_matrix;
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        u8 count = work->m_count;
        Vec* history = work->m_posHistory;
        if (count != 0) {
            do {
                pppCopyVector__FR3Vec3Vec(history, &pos);
                history++;
                count--;
            } while (count != 0);
        }
    }

    if (work->m_head == 0) {
        work->m_head = work->m_count;
    }
    work->m_head--;

    if (step->m_worldSpaceMode == 0) {
        pos.x = tailObj->m_obj.m_localMatrix.value[0][3];
        pos.y = tailObj->m_obj.m_localMatrix.value[1][3];
        pos.z = tailObj->m_obj.m_localMatrix.value[2][3];
    } else if (step->m_worldSpaceMode == 1) {
        pppFMATRIX ownerMatrix;
        pppFMATRIX partMatrix;
        pppFMATRIX outMatrix;

        partMatrix = tailObj->m_obj.m_localMatrix;
        ownerMatrix = pppMngStPtr->m_matrix;
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector__FR3Vec3Vec((Vec*)((u8*)work + (u32)work->m_head * 0xc + 8), &pos);

    {
        long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
        u8* frameEntry;
        s16 frameDuration;

        work->m_shapePrevFrame = work->m_shapeFrame;
        frameEntry = (u8*)shape + ((u32)work->m_shapeFrame << 3) + 0x10;

        work->m_frameAcc += step->m_frameStep;
        frameDuration = *(s16*)(frameEntry + 2);
        if (work->m_frameAcc >= frameDuration) {
            work->m_frameAcc -= frameDuration;
            work->m_shapeFrame++;
            if (work->m_shapeFrame >= (u16)*(s16*)((u8*)shape + 6)) {
                if ((frameEntry[4] & 0x80) != 0) {
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

/*
 * --INFO--
 * PAL Address: 0x80088748
 * PAL Size: 1796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail2XDraw(_pppPObject* obj, UnkB* param_2, UnkC* param_3)
{
    KeShpTail2XStep* step = (KeShpTail2XStep*)param_2;
    KeShpTail2XOffsets* offsets = (KeShpTail2XOffsets*)param_3;
    KeShpTail2XObject* tailObj = (KeShpTail2XObject*)obj;
    KeShpTail2XWork* work;
    long* shapeTable;
    long* shapeEntry;
    u16 count;
    float alphaMul;
    float colorR;
    float colorG;
    float colorB;
    float colorA;
    float colorStepR;
    float colorStepG;
    float colorStepB;
    float colorStepA;
    float invCountMinusOne;
    pppFMATRIX localBase;
    pppFMATRIX drawMtx;
    Vec zeroVec;
    Vec pos;
    Vec nextPos;
    Vec seg;
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
    float drawScale;
    float drawScaleStep;
    float scaleStepDelta;
    u8 curIndex;
    u8 nextIndex;
    u8 lastIndex;
    u8 zEnable;
    _pppMngSt* mng;

    if (step->m_dataValIndex == -1) {
        return;
    }

    count = step->m_drawCount;
    if (count == 0) {
        return;
    }

    invCountMinusOne = (float)(step->m_drawCount - 1);
    alphaMul = (float)*(s16*)((u8*)obj + 0x86 + offsets->m_serializedDataOffsets[1]) / lbl_80330504;
    if (invCountMinusOne != lbl_80330500) {
        colorStepR = ((float)step->m_colorStartR - (float)step->m_colorEndR) / invCountMinusOne;
        colorStepG = ((float)step->m_colorStartG - (float)step->m_colorEndG) / invCountMinusOne;
        colorStepB = ((float)step->m_colorStartB - (float)step->m_colorEndB) / invCountMinusOne;
        colorStepA = (((float)step->m_colorStartA * alphaMul) - ((float)step->m_colorEndA * alphaMul)) / invCountMinusOne;
    } else {
        colorStepR = lbl_80330500;
        colorStepG = lbl_80330500;
        colorStepB = lbl_80330500;
        colorStepA = lbl_80330500;
    }

    work = (KeShpTail2XWork*)((u8*)obj + 0x80 + offsets->m_serializedDataOffsets[0]);
    mng = (_pppMngSt*)lbl_8032ED50;
    shapeTable = *(long**)(*(u32*)&lbl_8032ED54->m_particleColors[0] + step->m_dataValIndex * 4);
    shapeEntry = (long*)((u8*)shapeTable + *(s16*)((u8*)shapeTable + ((u16)work->m_shapePrevFrame << 3) + 0x10));

    colorR = (float)step->m_colorStartR;
    colorG = (float)step->m_colorStartG;
    colorB = (float)step->m_colorStartB;
    colorA = (float)step->m_colorStartA * alphaMul;

    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&localBase, &tailObj->m_obj.m_localMatrix);
    pppUnitMatrix__FR10pppFMATRIX(&drawMtx);

    drawScale = step->m_scaleStart;
    scaleStepDelta = (step->m_scaleStart - step->m_scaleEnd) / invCountMinusOne;
    drawScaleStep = step->m_stepDistance * mng->m_scale.x;
    if (drawScaleStep <= lbl_80330500) {
        return;
    }

    curIndex = work->m_head;
    nextIndex = curIndex + 1;
    lastIndex = work->m_count - 1;
    if (curIndex == lastIndex) {
        nextIndex = 0;
    }

    pos = work->m_posHistory[curIndex];
    nextPos = work->m_posHistory[nextIndex];
    segDx = nextPos.x - pos.x;
    segDy = nextPos.y - pos.y;
    segDz = nextPos.z - pos.z;
    seg.x = segDx;
    seg.y = segDy;
    seg.z = segDz;
    zeroVec.x = lbl_80330500;
    zeroVec.y = lbl_80330500;
    zeroVec.z = lbl_80330500;
    segLen = PSVECDistance(&zeroVec, &seg);
    segRemain = segLen;
    segCursor = lbl_80330500;
    segBaseX = pos.x;
    segBaseY = pos.y;
    segBaseZ = pos.z;

    if (step->m_skipFirst != 0) {
        goto move_next_segment;
    }

draw_loop:
    pos.x = segBaseX;
    pos.y = segBaseY;
    pos.z = segBaseZ;

    if (step->m_worldSpaceMode == 0) {
        PSMTXScaleApply(localBase.value, *(Mtx*)((u8*)&tailObj->m_obj + 0x40), drawScale * mng->m_scale.x,
                        drawScale * mng->m_scale.y,
                        drawScale * mng->m_scale.z);
        PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
        PSMTXCopy(*(Mtx*)((u8*)&tailObj->m_obj + 0x40), drawMtx.value);
    } else if (step->m_worldSpaceMode == 1) {
        pppUnitMatrix__FR10pppFMATRIX(&drawMtx);
        drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * mng->m_scale.x);
        drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * mng->m_scale.y);
        drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * mng->m_scale.z);
        PSMTXMultVec(ppvCameraMatrix02, &pos, &pos);
    }

    drawMtx.value[0][3] = pos.x;
    drawMtx.value[1][3] = pos.y;
    drawMtx.value[2][3] = pos.z;

    zEnable = (u8)((u32)__cntlzw((u32)step->m_zDisable) >> 5);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((void*)0, &drawMtx,
                                                               (step->m_useEnvDepth != 0) ? step->m_envDepth : lbl_80330500, 0,
                                                               step->m_drawA, step->m_blendMode, 0, zEnable, 1, 0);

    {
        GXColor amb;
        amb.r = (u8)colorR;
        amb.g = (u8)colorG;
        amb.b = (u8)colorB;
        amb.a = (u8)colorA;
        GXSetChanAmbColor(GX_COLOR0A0, amb);
    }

    pppSetBlendMode__FUc(step->m_blendMode);
    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(shapeEntry, lbl_8032ED54->m_materialSetPtr, step->m_blendMode);

    count--;
    if (count == 0) {
        return;
    }

    colorR -= colorStepR;
    colorG -= colorStepG;
    colorB -= colorStepB;
    colorA -= colorStepA;
    drawScale -= scaleStepDelta;
    drawScaleStep -= scaleStepDelta;
    if (drawScaleStep <= lbl_80330500) {
        return;
    }

    if (segRemain < drawScaleStep) {
        goto advance_segment;
    }

    pos.x = segDx * (segCursor / segLen) + segBaseX;
    pos.y = segDy * (segCursor / segLen) + segBaseY;
    pos.z = segDz * (segCursor / segLen) + segBaseZ;
    segCursor += drawScaleStep;
    segRemain -= drawScaleStep;
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
    pos = nextPos;
    trailLen = segCursor - segLen;
    nextPos = work->m_posHistory[nextIndex];
    segDx = nextPos.x - pos.x;
    segDy = nextPos.y - pos.y;
    segDz = nextPos.z - pos.z;
    seg.x = segDx;
    seg.y = segDy;
    seg.z = segDz;
    segLen = PSVECDistance(&zeroVec, &seg);
    segCursor = trailLen;
    segRemain += segLen;
    segBaseX = pos.x;
    segBaseY = pos.y;
    segBaseZ = pos.z;
    goto draw_loop;
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}
