#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppShape.h"
#include "ffcc/symbols_shared.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

extern "C" int rand(void);

struct KeShpTail3XStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8 m_payload[0x40];
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

extern "C" {
int __cntlzw(unsigned int);
}

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
    s16* stepWork;
    Vec pos;
    Vec temp;
    Vec historyPos;

    if (gPppCalcDisabled != 0) {
        return;
    }

    step = (KeShpTail3XStep*)param_2;
    work = (KeShpTail3XWork*)((u8*)obj + 0x80 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[0]);
    stepWork = (s16*)&step->m_payload[0xc];

    if ((obj->pppPObject.m_graphId == 0) && (obj->field_0x7d != 0)) {
        work->m_initialized = 1;

        if (step->m_payload[0x3f] == 0) {
            pos.x = obj->pppPObject.m_localMatrix.value[0][3];
            pos.y = obj->pppPObject.m_localMatrix.value[1][3];
            pos.z = obj->pppPObject.m_localMatrix.value[2][3];
        } else if (step->m_payload[0x3f] == 1) {
            pppFMATRIX ownerMatrix;
            pppFMATRIX partMatrix;
            pppFMATRIX outMatrix;

            partMatrix = obj->pppPObject.m_localMatrix;
            ownerMatrix = pppMngStPtr->m_matrix;
            pppMulMatrix(outMatrix, ownerMatrix, partMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        pppCopyVector(historyPos, pos);
        Vec* history = work->m_posHistory;
        s32 i = 0x1c;
        do {
            temp = historyPos;
            pppCopyVector(*history, temp);
            history++;
            i--;
        } while (i > 0);
    }

    if (work->m_head == 0) {
        work->m_head = 0x1c;
    }
    work->m_head--;

    if (step->m_payload[0x3f] == 0) {
        pos.x = obj->pppPObject.m_localMatrix.value[0][3];
        pos.y = obj->pppPObject.m_localMatrix.value[1][3];
        pos.z = obj->pppPObject.m_localMatrix.value[2][3];
    } else if (step->m_payload[0x3f] == 1) {
        pppFMATRIX ownerMatrix;
        pppFMATRIX partMatrix;
        pppFMATRIX outMatrix;

        partMatrix = obj->pppPObject.m_localMatrix;
        ownerMatrix = pppMngStPtr->m_matrix;
        pppMulMatrix(outMatrix, ownerMatrix, partMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    temp = pos;
    pppCopyVector(work->m_posHistory[work->m_head], temp);

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
        work->m_values[0] += stepWork[0];
        work->m_values[1] += stepWork[1];
        work->m_values[2] += stepWork[2];
        work->m_values[3] += stepWork[3];
        work->m_values[8] += stepWork[8];
        work->m_values[9] += stepWork[9];
        work->m_values[10] += stepWork[10];
        work->m_values[0xb] += stepWork[11];
        work->m_values[0xc] += stepWork[12];
        work->m_values[0xd] += stepWork[13];
        work->m_values[0xe] += stepWork[14];
        work->m_values[0xf] += stepWork[15];
        work->m_values[4] += stepWork[4];
        work->m_values[5] += stepWork[5];
        work->m_values[6] += stepWork[6];
        work->m_values[7] += stepWork[7];
        work->m_values[0x10] += stepWork[16];
        work->m_values[0x11] += stepWork[17];
        work->m_values[0x12] += stepWork[18];
        work->m_values[0x13] += stepWork[19];
        work->m_values[0x14] += stepWork[20];
        work->m_values[0x15] += stepWork[21];
        work->m_values[0x16] += stepWork[22];
        work->m_values[0x17] += stepWork[23];
    }

    work->m_shapeData += step->m_initWOrk;
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
    s16* work;
    u8* workBytes;
    long* shapeTable;
    int shapeData;
    u8 count;
    float fadeR;
    float fadeG;
    float fadeB;
    float fadeA;
    float stepR;
    float stepG;
    float stepB;
    float stepA;
    pppFMATRIX local;
    pppFMATRIX localBase;
    pppFMATRIX drawMtx;
    pppFMATRIX rotMtx;
    pppFMATRIX tmpMtx;
    Vec pos;
    Vec nextPos;
    Vec seg;
    Vec zeroVec;
    u16 rng;
    int life;
    u16 shapeSetCount;
    s16 shapeCount;
    float scaleFalloff;
    float baseScale;
    float baseScaleStep;
    float stepScale;
    float lenNow;
    float segLen;
    float segBaseX;
    float segBaseY;
    float segBaseZ;
    float segDirX;
    float segDirY;
    float segDirZ;
    float segCursor;
    float segCursorLen;
    float segWork;
    u8 currentIndex;
    u8 nextIndex;

    if (step->m_dataValIndex == -1) {
        return;
    }
    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;

    work = (s16*)((u8*)&obj->pppPObject + 8 + offsets->m_serializedDataOffsets[0]);
    workBytes = (u8*)work;
    shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
    if (shapeTable == NULL) {
        return;
    }
    shapeData = *(int*)shapeTable;

    count = step->m_payload[8];
    if (count == 0) {
        return;
    }

    fadeR = (float)(work[0] >> 7);
    fadeG = (float)(work[1] >> 7);
    fadeB = (float)(work[2] >> 7);
    fadeA = (float)(work[3] >> 7) * ((float)*(s16*)((u8*)obj + 0x86 + offsets->m_serializedDataOffsets[1]) / 128.0f);
    if (count == 1) {
        stepR = 0.0f;
        stepG = 0.0f;
        stepB = 0.0f;
        stepA = 0.0f;
    } else {
        stepR = (fadeR - (float)(work[4] >> 7)) / (float)(count - 1);
        stepG = (fadeG - (float)(work[5] >> 7)) / (float)(count - 1);
        stepB = (fadeB - (float)(work[6] >> 7)) / (float)(count - 1);
        stepA = (fadeA - ((float)(work[7] >> 7) * ((float)*(s16*)((u8*)obj + 0x86 + offsets->m_serializedDataOffsets[1]) / 128.0f))) /
                (float)(count - 1);
    }

    pppCopyMatrix(localBase, obj->pppPObject.m_localMatrix);
    pppUnitMatrix(local);

    scaleFalloff = ((float)step->m_stepValue - (float)step->m_arg3) / (float)(count - 1);
    baseScale = *(float*)(step->m_payload + 4) * pppMngStPtr->m_scale.x;
    baseScaleStep = baseScale * (scaleFalloff / (float)step->m_stepValue);
    if (baseScale == 0.0f) {
        return;
    }

    rng = (u16)work[0xe0];
    life = *(s32*)(work + 0xdc);
    shapeSetCount = *(u16*)(shapeData + 0x12);
    shapeCount = *(s16*)(shapeData + 6);
    stepScale = (float)step->m_stepValue;

    currentIndex = workBytes[0x1c2];
    nextIndex = currentIndex + 1;
    if (currentIndex == 0x1b) {
        nextIndex = 0;
    }

    pos = ((Vec*)(work + 0x18))[currentIndex];
    nextPos = ((Vec*)(work + 0x18))[nextIndex];
    seg.x = nextPos.x - pos.x;
    seg.y = nextPos.y - pos.y;
    seg.z = nextPos.z - pos.z;
    segLen = PSVECDistance(&zeroVec, &seg);
    segCursorLen = segLen;
    segCursor = 0.0f;
    segBaseX = pos.x;
    segBaseY = pos.y;
    segBaseZ = pos.z;
    segDirX = seg.x;
    segDirY = seg.y;
    segDirZ = seg.z;

    while (count != 0) {
        int shapeEntry;
        GXColor amb;
        u8 zEnable;
        float envDepth = 0.0f;
        u8 blendMode = step->m_payload[0x42];
        float drawScale = stepScale;

        if (step->m_payload[9] != 0) {
            u32 lcg = (u32)rng * 0x80du + 7u;
            rng = (u16)lcg;
            drawScale *= -((((float)rng / 65535.0f) * *(float*)(step->m_payload) - 1.0f));
            {
                u32 shapeIdx = (u32)(life + rng) / shapeSetCount;
                shapeEntry = shapeData + *(s16*)(shapeData + (shapeIdx % (u32)shapeCount) * 8 + 0x10);
            }
        } else {
            shapeEntry = shapeData;
        }

        pos.x = segBaseX;
        pos.y = segBaseY;
        pos.z = segBaseZ;

        if (step->m_payload[0x3f] == 0) {
            PSMTXScaleApply(localBase.value, obj->field_0x40.value, drawScale * pppMngStPtr->m_scale.x,
                            drawScale * pppMngStPtr->m_scale.y, drawScale * pppMngStPtr->m_scale.z);
            if ((*(s16*)(step->m_payload + 10) != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)(u16)work[(int)count + 0xc0]);
                pppCopyMatrix(tmpMtx, obj->field_0x40);
                pppMulMatrix(obj->field_0x40, rotMtx, tmpMtx);
            }
            PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
            PSMTXCopy(obj->field_0x40.value, drawMtx.value);
        } else if (step->m_payload[0x3f] == 1) {
            pppUnitMatrix(drawMtx);
            drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * pppMngStPtr->m_scale.x);
            drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * pppMngStPtr->m_scale.y);
            drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * pppMngStPtr->m_scale.z);
            if ((*(s16*)(step->m_payload + 10) != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)(u16)work[(int)count + 0xc0]);
                pppCopyMatrix(tmpMtx, drawMtx);
                pppMulMatrix(drawMtx, rotMtx, tmpMtx);
            }
            PSMTXMultVec(ppvCameraMatrix0, &pos, &pos);
        }

        drawMtx.value[0][3] = pos.x;
        drawMtx.value[1][3] = pos.y;
        drawMtx.value[2][3] = pos.z;

        zEnable = (u8)((u32)__cntlzw((u32)step->m_payload[0x41]) >> 5);
        if (step->m_payload[0x3e] != 0) {
            envDepth = *(float*)(step->m_payload + 0x44);
        }
        pppSetDrawEnv((pppCVECTOR*)0, &drawMtx, envDepth, 0, step->m_payload[0x3c], blendMode, 0, zEnable, 1, 0);
        GXLoadPosMtxImm(drawMtx.value, 0);

        amb.r = (u8)fadeR;
        amb.g = (u8)fadeG;
        amb.b = (u8)fadeB;
        amb.a = (u8)fadeA;
        GXSetChanAmbColor(GX_COLOR0A0, amb);

        pppSetBlendMode(blendMode);
        pppDrawShp((tagOAN3_SHAPE*)shapeEntry, pppEnvStPtr->m_materialSetPtr, blendMode);

        count--;
        if (count == 0) {
            break;
        }

        lenNow = baseScale - baseScaleStep;
        fadeR -= stepR;
        fadeG -= stepG;
        fadeB -= stepB;
        fadeA -= stepA;
        stepScale -= scaleFalloff;
        baseScale = lenNow;
        if (lenNow <= 0.0f) {
            return;
        }

        for (; segCursorLen < lenNow; segCursorLen += segLen) {
            nextIndex++;
            if (nextIndex == 0x1c) {
                nextIndex = 0;
            }
            if (nextIndex == currentIndex) {
                return;
            }

            {
                Vec* p = &((Vec*)(work + 0x18))[nextIndex];
                segWork = segCursor - segLen;
                segBaseX = nextPos.x;
                segBaseY = nextPos.y;
                segBaseZ = nextPos.z;
                seg.x = p->x - nextPos.x;
                seg.y = p->y - nextPos.y;
                seg.z = p->z - nextPos.z;
                segLen = PSVECDistance(&zeroVec, &seg);
                nextPos = *p;
                segDirX = seg.x;
                segDirY = seg.y;
                segDirZ = seg.z;
                segCursor = segWork;
            }
        }

        {
            float t = segCursor / segLen;
            pos.x = segDirX * t + segBaseX;
            pos.y = segDirY * t + segBaseY;
            pos.z = segDirZ * t + segBaseZ;
            segCursor += lenNow;
            segCursorLen -= lenNow;
            segBaseX = pos.x;
            segBaseY = pos.y;
            segBaseZ = pos.z;
        }
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
