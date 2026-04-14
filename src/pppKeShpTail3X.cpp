#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppShape.h"
#include "ffcc/symbols_shared.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

extern "C" int rand(void);

extern "C" {
int __cntlzw(unsigned int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char,
                                                               unsigned char, unsigned char, unsigned char,
                                                               unsigned char, unsigned char);
void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);
}

struct KeShpTail3XStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWork;
    float m_stepValue;
    float m_arg3;
    float m_randomScale;
    float m_stepDistance;
    u8 m_drawCount;
    u8 m_useRandomShape;
    s16 m_rotateEnabled;
    s16 m_valueSteps[24];
    u8 m_drawA;
    u8 _pad51;
    u8 m_useEnvDepth;
    u8 m_worldSpaceMode;
    u8 _pad54;
    u8 m_zDisable;
    u8 m_blendMode;
    u8 _pad57;
    float m_envDepth;
};

struct KeShpTail3XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

struct KeShpTail3XWork {
    s16 m_values[24];
    Vec m_posHistory[28];
    s16 m_angles[28];
    u32 m_shapeData;
    u16 m_shapeFrame;
    u16 m_unk1be;
    u16 m_rand;
    u8 m_head;
    u8 m_initialized;
};

struct KeShpTail3XObject {
    u8 _pad0[0xc];
    _pppPObject m_obj;
};

/*
 * --INFO--
 * PAL Address: 0x80089da0
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3X(struct pppKeShpTail3X* obj, struct pppKeShpTail3XUnkB* param_2, struct pppKeShpTail3XUnkC* param_3)
{
    KeShpTail3XStep* step;
    KeShpTail3XWork* work;
    Vec pos;
    Vec historyPos ATTRIBUTE_ALIGN(8);

    if (gPppCalcDisabled != 0) {
        return;
    }

    step = (KeShpTail3XStep*)param_2;
    work = (KeShpTail3XWork*)((u8*)obj + 0x80 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[0]);

    if ((obj->pppPObject.m_graphId == 0) && (obj->field_0x7d != 0)) {
        work->m_initialized = 1;

        if (step->m_worldSpaceMode == 0) {
            pos.x = obj->pppPObject.m_localMatrix.value[0][3];
            pos.y = obj->pppPObject.m_localMatrix.value[1][3];
            pos.z = obj->pppPObject.m_localMatrix.value[2][3];
        } else if (step->m_worldSpaceMode == 1) {
            pppFMATRIX outMatrix;

            pppMulMatrix(outMatrix, pppMngStPtr->m_matrix, obj->pppPObject.m_localMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        pppCopyVector(historyPos, pos);
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
        pos.x = obj->pppPObject.m_localMatrix.value[0][3];
        pos.y = obj->pppPObject.m_localMatrix.value[1][3];
        pos.z = obj->pppPObject.m_localMatrix.value[2][3];
    } else if (step->m_worldSpaceMode == 1) {
        pppFMATRIX outMatrix;

        pppMulMatrix(outMatrix, pppMngStPtr->m_matrix, obj->pppPObject.m_localMatrix);
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

    if (obj->pppPObject.m_graphId == step->m_graphId) {
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

/*
 * --INFO--
 * PAL Address: 0x80089360
 * PAL Size: 2624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDraw(struct pppKeShpTail3X* obj, struct pppKeShpTail3XUnkB* param_2, struct pppKeShpTail3XUnkC* param_3)
{
    KeShpTail3XStep* step = (KeShpTail3XStep*)param_2;
    KeShpTail3XOffsets* offsets = (KeShpTail3XOffsets*)param_3;
    KeShpTail3XObject* tailObj = (KeShpTail3XObject*)obj;
    KeShpTail3XWork* work;
    long** shapeTable;
    long* shapeEntry;
    u8* shapeData;
    u8 count;
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
    pppFMATRIX rotMtx;
    pppFMATRIX tmpMtx;
    Vec zeroVec;
    Vec pos;
    Vec nextPos;
    Vec seg;
    _pppMngSt* mng;
    float envDepth;
    float drawScale;
    float segDx;
    float segDy;
    float segDz;
    u16 rng;
    int life;
    u16 shapeSetCount;
    s16 shapeCount;
    float shapeScale;
    float shapeScaleStep;
    float trailStep;
    float trailStepDelta;
    float segLen;
    float trailLen;
    float segCursor;
    float segRemain;
    float segBaseX;
    float segBaseY;
    float segBaseZ;
    u8 currentIndex;
    u8 nextIndex;
    u8 zEnable;

    if (step->m_dataValIndex == -1) {
        return;
    }

    count = step->m_drawCount;
    if (count == 0) {
        return;
    }

    work = (KeShpTail3XWork*)((u8*)obj + 0x80 + offsets->m_serializedDataOffsets[0]);
    invCountMinusOne = (float)(count - 1);
    alphaMul = (float)*(s16*)((u8*)obj + 0x86 + offsets->m_serializedDataOffsets[1]) / kPppKeShpTail2XAlphaScale;
    colorR = (float)(work->m_values[0] >> 7);
    colorG = (float)(work->m_values[1] >> 7);
    colorB = (float)(work->m_values[2] >> 7);
    colorA = (float)(work->m_values[3] >> 7) * alphaMul;

    if (invCountMinusOne != kPppKeShpTail2XZero) {
        colorStepR = (colorR - (float)(work->m_values[4] >> 7)) / invCountMinusOne;
        colorStepG = (colorG - (float)(work->m_values[5] >> 7)) / invCountMinusOne;
        colorStepB = (colorB - (float)(work->m_values[6] >> 7)) / invCountMinusOne;
        colorStepA = (colorA - ((float)(work->m_values[7] >> 7) * alphaMul)) / invCountMinusOne;
    } else {
        colorStepR = kPppKeShpTail2XZero;
        colorStepG = kPppKeShpTail2XZero;
        colorStepB = kPppKeShpTail2XZero;
        colorStepA = kPppKeShpTail2XZero;
    }

    mng = (_pppMngSt*)pppMngStPtr;
    shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
    shapeData = (u8*)*shapeTable;

    pppCopyMatrix(localBase, tailObj->m_obj.m_localMatrix);
    pppUnitMatrix(drawMtx);

    shapeScale = (float)step->m_stepValue;
    shapeScaleStep = ((float)step->m_stepValue - (float)step->m_arg3) / invCountMinusOne;
    trailStep = step->m_stepDistance * mng->m_scale.x;
    trailStepDelta = trailStep * (shapeScaleStep / (float)step->m_stepValue);
    if (trailStep == kPppKeShpTail2XZero) {
        return;
    }

    currentIndex = work->m_head;
    nextIndex = currentIndex + 1;
    if (currentIndex == 0x1b) {
        nextIndex = 0;
    }

    pos = work->m_posHistory[currentIndex];
    nextPos = work->m_posHistory[nextIndex];
    segDx = nextPos.x - pos.x;
    segDy = nextPos.y - pos.y;
    segDz = nextPos.z - pos.z;
    seg.x = segDx;
    seg.y = segDy;
    seg.z = segDz;
    zeroVec.x = kPppKeShpTail2XZero;
    zeroVec.y = kPppKeShpTail2XZero;
    zeroVec.z = kPppKeShpTail2XZero;
    segLen = PSVECDistance(&zeroVec, &seg);
    segRemain = segLen;
    segCursor = kPppKeShpTail2XZero;
    segBaseX = pos.x;
    segBaseY = pos.y;
    segBaseZ = pos.z;

    life = work->m_shapeData;
    shapeSetCount = *(u16*)(shapeData + 0x12);
    rng = work->m_rand;
    shapeCount = *(s16*)(shapeData + 6);

draw_loop:
    while (count != 0) {
        envDepth = kPppKeShpTail2XZero;
        drawScale = shapeScale;

        if (step->m_useRandomShape != 0) {
            u32 lcg = (u32)rng * 0x80du + 7u;
            rng = (u16)lcg;
            drawScale *= -((((float)rng / 65535.0f) * step->m_randomScale) - 1.0f);
            {
                u32 shapeIdx = (u32)(life + rng) / shapeSetCount;
                shapeEntry = (long*)(shapeData + *(s16*)(shapeData + (shapeIdx % (u32)shapeCount) * 8 + 0x10));
            }
        } else {
            shapeEntry = (long*)shapeData;
        }

        pos.x = segBaseX;
        pos.y = segBaseY;
        pos.z = segBaseZ;

        if (step->m_worldSpaceMode == 0) {
            PSMTXScaleApply(localBase.value, obj->field_0x40.value, drawScale * mng->m_scale.x, drawScale * mng->m_scale.y,
                            drawScale * mng->m_scale.z);
            if ((step->m_rotateEnabled != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)work->m_angles[count]);
                pppCopyMatrix(tmpMtx, obj->field_0x40);
                pppMulMatrix(obj->field_0x40, rotMtx, tmpMtx);
            }
            PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
            PSMTXCopy(obj->field_0x40.value, drawMtx.value);
        } else if (step->m_worldSpaceMode == 1) {
            pppUnitMatrix(drawMtx);
            drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * mng->m_scale.x);
            drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * mng->m_scale.y);
            drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * mng->m_scale.z);
            if ((step->m_rotateEnabled != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)work->m_angles[count]);
                pppCopyMatrix(tmpMtx, drawMtx);
                pppMulMatrix(drawMtx, rotMtx, tmpMtx);
            }
            PSMTXMultVec(ppvCameraMatrix02, &pos, &pos);
        }

        drawMtx.value[0][3] = pos.x;
        drawMtx.value[1][3] = pos.y;
        drawMtx.value[2][3] = pos.z;

        if (step->m_useEnvDepth != 0) {
            envDepth = step->m_envDepth;
        }
        zEnable = (u8)((u32)__cntlzw((u32)step->m_zDisable) >> 5);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((void*)0, &drawMtx, envDepth, 0, step->m_drawA,
                                                                  step->m_blendMode, 0, zEnable, 1, 0);
        GXLoadPosMtxImm(drawMtx.value, 0);

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
            break;
        }

        trailLen = trailStep - trailStepDelta;
        colorR -= colorStepR;
        colorG -= colorStepG;
        colorB -= colorStepB;
        colorA -= colorStepA;
        shapeScale -= shapeScaleStep;
        trailStep = trailLen;
        if (trailLen <= 0.0f) {
            return;
        }

        if (segRemain < trailLen) {
            goto advance_segment;
        }

        pos.x = segDx * (segCursor / segLen) + segBaseX;
        pos.y = segDy * (segCursor / segLen) + segBaseY;
        pos.z = segDz * (segCursor / segLen) + segBaseZ;
        segCursor += trailLen;
        segRemain -= trailLen;
        segBaseX = pos.x;
        segBaseY = pos.y;
        segBaseZ = pos.z;
        goto draw_loop;

advance_segment:
        nextIndex++;
        if (nextIndex == 0x1c) {
            nextIndex = 0;
        }
        if (nextIndex == currentIndex) {
            return;
        }

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

    pppSetBlendMode(3);
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
void pppKeShpTail3XCon(struct pppKeShpTail3X* obj, struct pppKeShpTail3XUnkC* param_2)
{
    unsigned char* anglePtr;
    unsigned char* work;
    int i;
    float one;

    work = (unsigned char*)((u8*)obj + 0x80 + ((KeShpTail3XOffsets*)param_2)->m_serializedDataOffsets[0]);
    work[0x1c3] = 0;
    work[0x1c2] = 0;
    *(u16*)(work + 0x1bc) = 0;
    *(u32*)(work + 0x1b8) = 0;
    *(u16*)(work + 0x1c0) = (u16)rand();
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
    memset(work + 0x18, 0, 8);
    memset(work + 0x20, 0, 8);
    memset(work + 0x28, 0, 8);

    one = kPppKeShpTail3XOne;
    i = 0;
    anglePtr = work;
    do {
        s32 rnd = rand();
        *(s16*)(anglePtr + 0x180) = (s16)(rnd - (rnd / 0x168) * 0x168);
        anglePtr += 2;
        *(float*)(work + 0x38) = one;
        *(float*)(work + 0x34) = one;
        *(float*)(work + 0x30) = one;
        work += 0xc;
        i++;
    } while (i < 0x1c);
}

/*
 * --INFO--
 * PAL Address: 0x8008922c
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDes(_pppPObjLink* obj, _pppCtrlTable* ctrlTable)
{
	(void)obj;
	(void)ctrlTable;
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void S4ToF32(pppFVECTOR4*, short*)
{
	// TODO
}
