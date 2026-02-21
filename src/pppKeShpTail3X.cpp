#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/pppShape.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

extern "C" int rand(void);
extern int DAT_8032ed70;

struct KeShpTail3XStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_initWOrk;
    s32 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

struct KeShpTail3XOffsets {
    u8 _pad0[0xc];
    s32* m_serializedDataOffsets;
};

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
int __cntlzw(unsigned int);
}
extern Mtx ppvWorldMatrix;
extern Mtx ppvCameraMatrix0;
extern _pppEnvSt* pppEnvStPtr;

/*
 * --INFO--
 * PAL Address: 0x80089da0
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3X(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
{
    KeShpTail3XStep* step;
    s16* work;
    Vec pos;
    Vec temp;

    if (DAT_8032ed70 != 0) {
        return;
    }

    step = (KeShpTail3XStep*)param_2;
    work = (s16*)((u8*)&obj->pppPObject + 8 + ((KeShpTail3XOffsets*)param_3)->m_serializedDataOffsets[0]);

    if ((obj->pppPObject.m_graphId == 0) && (obj->field_0x7d != 0)) {
        ((u8*)work)[0x1c3] = 1;

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
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
            pos.x = outMatrix.value[0][3];
            pos.y = outMatrix.value[1][3];
            pos.z = outMatrix.value[2][3];
        }

        pppCopyVector__FR3Vec3Vec(&temp, &pos);
        Vec* history = (Vec*)(work + 0x18);
        s32 i = 0x1c;
        do {
            pppCopyVector__FR3Vec3Vec(&pos, &temp);
            pppCopyVector__FR3Vec3Vec(history, &pos);
            history++;
            i--;
        } while (i > 0);
    }

    if (((u8*)work)[0x1c2] == 0) {
        ((u8*)work)[0x1c2] = 0x1c;
    }
    ((u8*)work)[0x1c2]--;

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
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&outMatrix, &ownerMatrix, &partMatrix);
        pos.x = outMatrix.value[0][3];
        pos.y = outMatrix.value[1][3];
        pos.z = outMatrix.value[2][3];
    }

    pppCopyVector__FR3Vec3Vec((Vec*)(work + ((u8*)work)[0x1c2] * 6 + 0x18), &pos);

    work[8] += work[0xc];
    work[0] += work[8];
    work[9] += work[0xd];
    work[1] += work[9];
    work[10] += work[0xe];
    work[2] += work[10];
    work[0xb] += work[0xf];
    work[3] += work[0xb];
    work[0x10] += work[0x14];
    work[4] += work[0x10];
    work[0x11] += work[0x15];
    work[5] += work[0x11];
    work[0x12] += work[0x16];
    work[6] += work[0x12];
    work[0x13] += work[0x17];
    work[7] += work[0x13];

    if (obj->pppPObject.m_graphId == step->m_graphId) {
        work[0] += *(s16*)(step->m_payload + 0xc);
        work[1] += *(s16*)(step->m_payload + 0xe);
        work[2] += *(s16*)(step->m_payload + 0x10);
        work[3] += *(s16*)(step->m_payload + 0x12);
        work[8] += *(s16*)(step->m_payload + 0x1c);
        work[9] += *(s16*)(step->m_payload + 0x1e);
        work[10] += *(s16*)(step->m_payload + 0x20);
        work[0xb] += *(s16*)(step->m_payload + 0x22);
        work[0xc] += *(s16*)(step->m_payload + 0x24);
        work[0xd] += *(s16*)(step->m_payload + 0x26);
        work[0xe] += *(s16*)(step->m_payload + 0x28);
        work[0xf] += *(s16*)(step->m_payload + 0x2a);
        work[4] += *(s16*)(step->m_payload + 0x14);
        work[5] += *(s16*)(step->m_payload + 0x16);
        work[6] += *(s16*)(step->m_payload + 0x18);
        work[7] += *(s16*)(step->m_payload + 0x1a);
        work[0x10] += *(s16*)(step->m_payload + 0x2c);
        work[0x11] += *(s16*)(step->m_payload + 0x2e);
        work[0x12] += *(s16*)(step->m_payload + 0x30);
        work[0x13] += *(s16*)(step->m_payload + 0x32);
        work[0x14] += *(s16*)(step->m_payload + 0x34);
        work[0x15] += *(s16*)(step->m_payload + 0x36);
        work[0x16] += *(s16*)(step->m_payload + 0x38);
        work[0x17] += *(s16*)(step->m_payload + 0x3a);
    }

    *(u32*)(work + 0xdc) += step->m_initWOrk;
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
void pppKeShpTail3XDraw(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
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

    pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&localBase, &obj->pppPObject.m_localMatrix);
    pppUnitMatrix__FR10pppFMATRIX(&local);

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
            PSMTXScaleApply(localBase.value, *(Mtx*)((u8*)obj + 0x40), drawScale * pppMngStPtr->m_scale.x,
                            drawScale * pppMngStPtr->m_scale.y, drawScale * pppMngStPtr->m_scale.z);
            if ((*(s16*)(step->m_payload + 10) != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)(u16)work[(int)count + 0xc0]);
                pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&tmpMtx, (pppFMATRIX*)((u8*)obj + 0x40));
                pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX((pppFMATRIX*)((u8*)obj + 0x40), &rotMtx, &tmpMtx);
            }
            PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
            PSMTXCopy(*(Mtx*)((u8*)obj + 0x40), drawMtx.value);
        } else if (step->m_payload[0x3f] == 1) {
            pppUnitMatrix__FR10pppFMATRIX(&drawMtx);
            drawMtx.value[0][0] = drawScale * (localBase.value[0][0] * pppMngStPtr->m_scale.x);
            drawMtx.value[1][1] = drawScale * (localBase.value[1][1] * pppMngStPtr->m_scale.y);
            drawMtx.value[2][2] = drawScale * (localBase.value[2][2] * pppMngStPtr->m_scale.z);
            if ((*(s16*)(step->m_payload + 10) != 0) && (count != 0)) {
                PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)(u16)work[(int)count + 0xc0]);
                pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(&tmpMtx, &drawMtx);
                pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&drawMtx, &rotMtx, &tmpMtx);
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
void pppKeShpTail3XCon(struct pppKeShpTail3X* obj, struct UnkC* param_2)
{
    unsigned char* anglePtr;
    unsigned char* work;
    int i;
    float one;

    work = (unsigned char*)((u8*)&obj->pppPObject + 8 + ((KeShpTail3XOffsets*)param_2)->m_serializedDataOffsets[0]);
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

    one = 1.0f;
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
void pppKeShpTail3XDes(void)
{
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
