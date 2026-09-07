#include "global.h"
#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppYmMegaBirthShpTail3AlphaDivisor = 16384.0f;
extern const float kPppYmMegaBirthShpTail3Zero = 0.0f;
extern const float kPppYmMegaBirthShpTail3DegToRad = 0.017453292f;
extern const float kPppYmMegaBirthShpTail3DepthAlphaScale = 0.00787f;
extern const float kPppYmMegaBirthShpTail3ColorComponentMax = 127.0f;
extern const double kPppYmMegaBirthShpTail3U32ToDoubleBias = 4503601774854144.0;
extern const double kPppYmMegaBirthShpTail3S32ToDoubleBias = 4503599627370496.0;
extern const float kPppYmMegaBirthShpTail3Double = 2.0f;
extern const float kPppYmMegaBirthShpTail3HalfTurnDegrees = 180.0f;
extern const float kPppYmMegaBirthShpTail3RandomSpeedScale = 0.7f;
extern const float kPppYmMegaBirthShpTail3Half = 0.5f;
extern const double kPppYmMegaBirthShpTail3OneDouble = 1.0;
}
#include "dolphin/mtx.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

struct VYmMegaBirthShpTail3
{
    pppFMATRIX m_emitterMatrix;
    Vec m_tailScaleDirection;
    _PARTICLE_DATA* m_particles;
    _PARTICLE_WMAT* m_wmats;
    _PARTICLE_COLOR* m_colors;
    unsigned int m_maxParticles;
    unsigned short m_lifeLimit;
    unsigned short m_pathIndex;
};

static pppFMATRIX g_matUnit;

static const char s_pppYmMegaBirthShpTail3_cpp[] = "pppYmMegaBirthShpTail3.cpp";

STATIC_ASSERT(offsetof(YmMegaBirthShpTail3DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail3DataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(sizeof(YmMegaBirthShpTail3DataOffsets) == 0xC);
STATIC_ASSERT(offsetof(pppYmMegaBirthShpTail3Offsets, m_serializedDataOffsets) == 0xC);

void birth(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);

static inline float LoadFloat(const float& value)
{
    return value;
}

/*
 * --INFO--
 * PAL Address: 8008ca98
 * PAL Size: 2316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, pppYmMegaBirthShpTail3RenderStep* stepData, pppYmMegaBirthShpTail3Offsets* offsets)
{
    u8* step = (u8*)stepData;
    u8* payload = step + 0x14;
    YmMegaBirthShpTail3DataOffsets* serializedOffsets = offsets->m_serializedDataOffsets;
    const s32 colorOffset = serializedOffsets->m_colorOffset;
    const s32 particleDataOffset = serializedOffsets->m_workOffset;
    s32 trailReadIndex;
    u8* workBytes = object->m_workArea + particleDataOffset;
    VColor* colorWork = (VColor*)(object->m_workArea + colorOffset);
    u8* particle = *(u8**)(workBytes + 0x3c);
    _PARTICLE_WMAT* wmats;
    _PARTICLE_COLOR* colors = *(_PARTICLE_COLOR**)(workBytes + 0x44);
    s8 hasRequiredMemory;

    wmats = *(_PARTICLE_WMAT**)(workBytes + 0x40);

    if (particle == 0) {
        hasRequiredMemory = false;
    } else if (wmats == 0) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }
    if (!hasRequiredMemory) {
        return;
    }
    if (*(s32*)(step + 4) == 0xFFFF) {
        return;
    }
    const u32 dataValIndex = *(u32*)(step + 4);

    pppShapeAnimData* shapeAnim =
        static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[dataValIndex]->m_animData);
    pppSetDrawEnv(
        0, &object->m_drawMatrix, *(float*)(payload + 0xA0), payload[0xA4], step[0x0C],
        payload[0x58], 0, (u8)(((u32)__cntlzw((u32)payload[0x55])) >> 5), 1, 0);
    pppSetBlendMode(payload[0x58]);

    for (u32 i = 0; i < *(u32*)(workBytes + 0x48); i++) {
        if (*(u16*)(particle + 0x22) != 0) {
            const u32 frameCountRaw = *(u16*)(payload + 0x9C);
                u32 frameCount = frameCountRaw;
                pppFMATRIX drawMtx;
                Vec zeroVec;
                Vec segVec;
                union { Vec cameraPos; double _cameraPosAlign; };
                union { Vec trailPos; double _trailPosAlign; };
                union { Vec managerPos; double _managerPosAlign; };
                GXColor amb;
                u8* curHist;
                tagOAN3_SHAPE* shape;
                u32 particleShapeFrame;
                u32 shapeFrameStep;
                const float alphaScale = (float)*(s16*)((u8*)colorWork + 6) / LoadFloat(kPppYmMegaBirthShpTail3AlphaDivisor);
                const float stepDivisor = (float)(s32)(frameCountRaw - 1);
                s32 trailNextIndex;
                const s32 trailMaxIndex = *(u8*)(particle + 0x37) - 1;
                float drawScale;
                float fadeR = (float)(*(s16*)(workBytes + 0x50) >> 7);
                float fadeG = (float)(*(s16*)(workBytes + 0x52) >> 7);
                float fadeB = (float)(*(s16*)(workBytes + 0x54) >> 7);
                float fadeA = (float)(*(s16*)(workBytes + 0x56) >> 7) * alphaScale;
                const float fadeAEnd = (float)(*(s16*)(workBytes + 0x5e) >> 7) * alphaScale;
                const float fadeANum = fadeA - fadeAEnd;
                trailReadIndex = *(u8*)(particle + 0x38);
                const float fadeRNum = fadeR - (float)(*(s16*)(workBytes + 0x58) >> 7);
                const float fadeGNum = fadeG - (float)(*(s16*)(workBytes + 0x5a) >> 7);
                const float fadeBNum = fadeB - (float)(*(s16*)(workBytes + 0x5c) >> 7);
                float fadeRStep;
                float fadeGStep;
                float fadeBStep;
                float fadeAStep;
                if (stepDivisor != LoadFloat(kPppYmMegaBirthShpTail3Zero)) {
                    fadeRStep = fadeRNum / stepDivisor;
                    fadeGStep = fadeGNum / stepDivisor;
                    fadeBStep = fadeBNum / stepDivisor;
                    fadeAStep = fadeANum / stepDivisor;
                }
                drawScale = *(float*)(payload + 0x5C);
                trailNextIndex = trailReadIndex + 1;
                const float drawScaleStep =
                    (drawScale - *(float*)(payload + 0x60)) / stepDivisor;
                Vec* history = (Vec*)(particle + 0x80);
                u32 workRand;
                u32 shapeFrameCount;
                float trailX, trailY, trailZ;
                float camX;
                float segX, segY, segZ;
                float camY, camZ;
                float segLen;
                float startX, startY, startZ;
                float spacingAccum;
                float segProgress;

                spacingAccum = *(float*)(payload + 0x98);
                {
                    Vec* p = &history[trailReadIndex];
                    trailX = p->x;
                    trailY = p->y;
                    trailZ = p->z;
                }
                if (trailReadIndex == trailMaxIndex) {
                    trailNextIndex = 0;
                }
                {
                    Vec* p = &history[trailNextIndex];
                    camX = p->x;
                    camY = p->y;
                    camZ = p->z;
                }
                segX = camX - trailX;
                segY = camY - trailY;
                segZ = camZ - trailZ;
                zeroVec.z = kPppYmMegaBirthShpTail3Zero;
                zeroVec.y = kPppYmMegaBirthShpTail3Zero;
                zeroVec.x = kPppYmMegaBirthShpTail3Zero;
                segVec.x = segX;
                segVec.y = segY;
                segVec.z = segZ;
                startZ = trailZ;
                startY = trailY;
                startX = trailX;
                segLen = PSVECDistance(&zeroVec, &segVec);
                segProgress = segLen;

                if (payload[0x9E] == 0) {
                    goto fade_dec;
                }
                particleShapeFrame = *(u16*)(particle + 0x1C);
                workRand = *(u16*)(workBytes + 0x80);
                shapeFrameStep = (u32)shapeAnim->m_frames[0].m_duration;
                shapeFrameCount = (u32)shapeAnim->m_frameCount;

                for (frameCount = *(u16*)(payload + 0x9C); 0 < (s32)frameCount; frameCount--) {
                    curHist = particle + trailNextIndex * 0xc;
                    if ((kPppYmMegaBirthShpTail3Zero != *(float*)(curHist + 0x80)) ||
                        (kPppYmMegaBirthShpTail3Zero != *(float*)(curHist + 0x84)) ||
                        (kPppYmMegaBirthShpTail3Zero != *(float*)(curHist + 0x88))) {
                        {
                            workRand = (workRand * 0x80d + 7) & 0xFFFF;
                            const u32 shapeFrame = (particleShapeFrame + workRand) / shapeFrameStep;
                            shape = reinterpret_cast<tagOAN3_SHAPE*>(
                                (u8*)shapeAnim +
                                *(s16*)((u8*)shapeAnim + (shapeFrame % shapeFrameCount) * 8 + 0x10));

                            pppUnitMatrix(drawMtx);
                            drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                            drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                            drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;

                            if (*(u16*)(payload + 0x94) != 0) {
                                pppFMATRIX rotMtx;
                                PSMTXRotRad(rotMtx.value, 'z',
                                            kPppYmMegaBirthShpTail3DegToRad *
                                                (float)*(u16*)(particle + frameCount * sizeof(u16) + 0x40));
                                pppMulMatrix(drawMtx, rotMtx, drawMtx);
                            }

                            trailPos.x = trailX;
                            trailPos.y = trailY;
                            trailPos.z = trailZ;
                            if (payload[0xA5] == 0) {
                                PSMTXMultVec(ppvWorldMatrix, &trailPos, &cameraPos);
                            } else if (payload[0xA5] == 1) {
                                managerPos.x = ppvMng->m_matrix.value[0][3];
                                managerPos.y = ppvMng->m_matrix.value[1][3];
                                managerPos.z = ppvMng->m_matrix.value[2][3];
                                PSVECAdd(&managerPos, &trailPos, &trailPos);
                                PSMTXMultVec(ppvCameraMatrix, &trailPos, &cameraPos);
                            }

                            drawMtx.value[0][3] = cameraPos.x;
                            drawMtx.value[1][3] = cameraPos.y;
                            drawMtx.value[2][3] = cameraPos.z;
                            GXLoadPosMtxImm(drawMtx.value, 0);

                            amb.r = (s8)fadeR;
                            amb.g = (u8)fadeG;
                            amb.b = (u8)fadeB;
                            amb.a = (u8)(fadeA * (kPppYmMegaBirthShpTail3DepthAlphaScale * (kPppYmMegaBirthShpTail3ColorComponentMax - *(float*)(particle + 0x30))));
                            if (amb.a > 0x7F) {
                                amb.a = 0x7F;
                            }
                            GXSetChanAmbColor(GX_COLOR0A0, amb);
                            pppDrawShp(shape, ppvEnv->m_materialSetPtr, payload[0x58]);
                        }

                    fade_dec:
                        fadeR -= fadeRStep;
                        fadeG -= fadeGStep;
                        fadeB -= fadeBStep;
                        fadeA -= fadeAStep;
                        drawScale -= drawScaleStep;
                        if (*(float*)(payload + 0x98) <= kPppYmMegaBirthShpTail3Zero) {
                            break;
                        }

                        for (;;) {
                            Vec innerZero;
                            Vec innerSeg;
                            const float spacing = *(float*)(payload + 0x98);
                            if (segProgress >= spacing) {
                                const float t = spacingAccum / segLen;
                                float mx = segX * t;
                                float my = segY * t;
                                float mz = segZ * t;
                                trailX = mx + startX;
                                trailY = my + startY;
                                trailZ = mz + startZ;
                                spacingAccum = spacingAccum + spacing;
                                segProgress = segProgress - spacing;
                                break;
                            }

                            {
                                s32 prevNext = trailNextIndex;
                                trailNextIndex++;
                                if (prevNext == trailMaxIndex) {
                                    trailNextIndex = 0;
                                }
                            }
                            if (trailNextIndex == trailReadIndex) {
                                goto next_particle;
                            }

                            startX = camX;
                            startY = camY;
                            startZ = camZ;
                            spacingAccum = spacingAccum - segLen;
                            {
                                Vec* p = &history[trailNextIndex];
                                camY = p->y;
                                camZ = p->z;
                                camX = p->x;
                                segY = camY - startY;
                                segZ = camZ - startZ;
                                segX = camX - startX;
                            }
                            innerZero.z = kPppYmMegaBirthShpTail3Zero;
                            innerZero.y = kPppYmMegaBirthShpTail3Zero;
                            innerZero.x = kPppYmMegaBirthShpTail3Zero;
                            innerSeg.x = segX;
                            innerSeg.y = segY;
                            innerSeg.z = segZ;
                            segLen = PSVECDistance(&innerZero, &innerSeg);
                            segProgress = segProgress + segLen;
                        }
                    }
                }
                next_particle:;
        }

        if (wmats != 0) {
            wmats = wmats + 1;
        }
        if (colors != 0) {
            colors = colors + 1;
        }
        *(u16*)(particle + 0x1C) += *(s32*)(step + 0x8);
        particle += 0x1F8;
    }
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 8008d3a4
 * PAL Size: 1620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, PYmMegaBirthShpTail3* param, pppYmMegaBirthShpTail3Offsets* offsets)
{
    s8 hasRequiredMemory;
    u32 i;
    u8* paramPayload;
    int colorOffset;
    u8* particleData;
    _PARTICLE_COLOR* particleColor;
    _PARTICLE_WMAT* worldMat;
    int spawnCount;

    YmMegaBirthShpTail3DataOffsets* serializedOffsets = offsets->m_serializedDataOffsets;
    colorOffset = serializedOffsets->m_colorOffset;
    VYmMegaBirthShpTail3* const work =
        (VYmMegaBirthShpTail3*)(object->m_workArea + serializedOffsets->m_workOffset);
    VColor* const colorWork = (VColor*)(object->m_workArea + colorOffset);
    paramPayload = (u8*)param;

    if (work->m_particles == 0) {
        work->m_maxParticles = *(u16*)(paramPayload + 0xe);
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_maxParticles * 0x1f8, ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmMegaBirthShpTail3_cpp), 0x2db);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * 0x1f8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc(
            work->m_maxParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmMegaBirthShpTail3_cpp), 0x2e3);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * sizeof(_PARTICLE_WMAT));
        }

        work->m_tailScaleDirection = param->m_directionTail;
        pppNormalize(work->m_tailScaleDirection, work->m_tailScaleDirection);
    }

    if (work->m_particles == 0) {
        hasRequiredMemory = false;
    } else if (work->m_wmats == 0) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }
    if (hasRequiredMemory) {
        *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(work[1].m_emitterMatrix.value[1] + 2);
        *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)work[1].m_emitterMatrix.value[1];

        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2);

        *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 3);
        *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 1);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6);

        *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(work[1].m_emitterMatrix.value[2] + 2);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 8) += *(s16*)work[1].m_emitterMatrix.value[2];

        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2);

        *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(work[1].m_emitterMatrix.value[2] + 3);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xc) += *(s16*)(work[1].m_emitterMatrix.value[2] + 1);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6);

        if (object->m_graphId == *(s32*)paramPayload) {
            *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)(paramPayload + 0x78);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x7a);
            *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(paramPayload + 0x7c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)(paramPayload + 0x7e);

            *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(paramPayload + 0x88);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x8a);
            *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(paramPayload + 0x8c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)(paramPayload + 0x8e);

            *(s16*)(work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x90);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa) += *(s16*)(paramPayload + 0x92);
            *(s16*)(work[1].m_emitterMatrix.value[1] + 3) += *(s16*)(paramPayload + 0x94);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe) += *(s16*)(paramPayload + 0x96);

            *(s16*)(work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x80);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)(paramPayload + 0x82);
            *(s16*)(work[1].m_emitterMatrix.value[0] + 3) += *(s16*)(paramPayload + 0x84);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)(paramPayload + 0x86);

            *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(paramPayload + 0x98);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0x9a);
            *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(paramPayload + 0x9c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)(paramPayload + 0x9e);

            *(s16*)(work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0xa0);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa) += *(s16*)(paramPayload + 0xa2);
            *(s16*)(work[1].m_emitterMatrix.value[2] + 3) += *(s16*)(paramPayload + 0xa4);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe) += *(s16*)(paramPayload + 0xa6);
        }

        switch (*(paramPayload + 0x18)) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        {
            Vec firstCol;
            Vec secondCol;
            Vec thirdCol;

            PSMTXIdentity(work->m_emitterMatrix.value);
            firstCol.x = work->m_emitterMatrix.value[0][0];
            firstCol.y = work->m_emitterMatrix.value[1][0];
            firstCol.z = work->m_emitterMatrix.value[2][0];
            PSVECScale(&firstCol, &firstCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][0] = firstCol.x;
            work->m_emitterMatrix.value[1][0] = firstCol.y;
            work->m_emitterMatrix.value[2][0] = firstCol.z;

            secondCol.x = work->m_emitterMatrix.value[0][1];
            secondCol.y = work->m_emitterMatrix.value[1][1];
            secondCol.z = work->m_emitterMatrix.value[2][1];
            PSVECScale(&secondCol, &secondCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][1] = secondCol.x;
            work->m_emitterMatrix.value[1][1] = secondCol.y;
            work->m_emitterMatrix.value[2][1] = secondCol.z;

            thirdCol.x = work->m_emitterMatrix.value[0][2];
            thirdCol.y = work->m_emitterMatrix.value[1][2];
            thirdCol.z = work->m_emitterMatrix.value[2][2];
            PSVECScale(&thirdCol, &thirdCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][2] = thirdCol.x;
            work->m_emitterMatrix.value[1][2] = thirdCol.y;
            work->m_emitterMatrix.value[2][2] = thirdCol.z;

            work->m_emitterMatrix.value[0][3] = ppvMng->m_position.x;
            work->m_emitterMatrix.value[1][3] = ppvMng->m_position.y;
            work->m_emitterMatrix.value[2][3] = ppvMng->m_position.z;
            break;
        }
        default:
            pppCopyMatrix(work->m_emitterMatrix, ppvMng->m_matrix);
            break;
        }

        i = 0;
        particleData = (u8*)work->m_particles;
        worldMat = work->m_wmats;
        particleColor = work->m_colors;
        spawnCount = i;

        if ((ppvUserStopPartF == 0) && (*(s32*)(paramPayload + 4) != 0xffff)) {
            work->m_lifeLimit = work->m_lifeLimit + 1;
            for (; i < work->m_maxParticles; i++) {
                if (*(u16*)(particleData + 0x22) != 0) {
                    calc((_pppPObject*)object, work, param, (_PARTICLE_DATA*)particleData, colorWork, particleColor);
                } else {
                    if ((*(u16*)(paramPayload + 0x12) <= work->m_lifeLimit) && (spawnCount < *(u16*)(paramPayload + 0x10))) {
                        birth((_pppPObject*)object, work, param, colorWork, (_PARTICLE_DATA*)particleData, worldMat, particleColor);
                        spawnCount = spawnCount + 1;
                    }
                }

                if (worldMat != 0) {
                    worldMat = worldMat + 1;
                }
                if (particleColor != 0) {
                    particleColor = particleColor + 1;
                }
                particleData = particleData + 0x1f8;
            }

            if (spawnCount > 0) {
                work->m_lifeLimit = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 8008d9f8
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
          PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    int alpha = vColor->m_alpha;
    u8* particleBytes = (u8*)particleData;
    float* blend = (float*)(particleBytes + 0x30);
    float* velocityScale = (float*)(particleBytes + 0x28);
    float* tailScale = (float*)(particleBytes + 0x2c);
    u8* frameState = particleBytes + 0x30;

    if (particleColor != nullptr) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];

        alpha = vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xff) {
            alpha = 0xff;
        }
    }

    *velocityScale = *velocityScale + pYmMegaBirthShpTail3->m_colorDeltaAdd[2];
    *tailScale = *tailScale + pYmMegaBirthShpTail3->m_sizeVal;

    Vec scaled;
    pppScaleVectorXYZ(scaled, *(Vec*)(particleBytes + 0x10), *velocityScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail3->m_tailScaleDirection, *tailScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    if (*(u16*)((u8*)&pYmMegaBirthShpTail3->m_matrix[1] + 0x4) != 0) {
        *(u16*)(particleBytes + 0x22) = *(u16*)(particleBytes + 0x22) - 1;
    }

    frameState[4] = frameState[4] + 1;

    unsigned int fadeTime = (unsigned int)frameState[5];
    if (fadeTime != 0 && frameState[4] <= fadeTime) {
        *blend = *blend -
            (float)alpha / (float)fadeTime;
        if (*blend < 0.0f) {
            *blend = 0.0f;
        }
    }

    unsigned int fadeTime2 = frameState[6];
    if (fadeTime2 != 0 && *(u16*)(particleBytes + 0x22) <= static_cast<int>(fadeTime2)) {
        unsigned char fadeInFrames = *((unsigned char*)&pYmMegaBirthShpTail3->m_matrix[1] + 7);
        *blend = *blend +
            (float)alpha / (float)fadeInFrames;
        if (*blend > kPppYmMegaBirthShpTail3ColorComponentMax) {
            *blend = kPppYmMegaBirthShpTail3ColorComponentMax;
        }
    }

    if (frameState[8] == 0) {
        frameState[8] = frameState[7];
    }
    frameState[8] = frameState[8] - 1;

    PSMTXMultVec(pppPObject->m_localMatrix.value, (Vec*)particleData,
                 (Vec*)(particleBytes + (unsigned int)frameState[8] * sizeof(Vec) + 0x80));
}

/*
 * --INFO--
 * PAL Address: 8008dcc8
 * PAL Size: 3704b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
           PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat,
           _PARTICLE_COLOR* particleColor)
{
    u8* paramBytes = (u8*)pYmMegaBirthShpTail3;
    u8* particleBytes = (u8*)particleData;
    float spread = (float)paramBytes[0x19];
    float spreadRange = kPppYmMegaBirthShpTail3Double * spread;

    memset(particleData, 0, 0x1f8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    if ((s32)paramBytes[0x18] < 8 && (s32)paramBytes[0x18] >= 0) {
        Vec baseDir;
        pppIVECTOR4 angles;
        pppFMATRIX rot;

        baseDir.x = pYmMegaBirthShpTail3->m_matrix[2][0];
        baseDir.y = pYmMegaBirthShpTail3->m_matrix[2][1];
        baseDir.z = pYmMegaBirthShpTail3->m_matrix[2][2];
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / kPppYmMegaBirthShpTail3HalfTurnDegrees);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / kPppYmMegaBirthShpTail3HalfTurnDegrees);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / kPppYmMegaBirthShpTail3HalfTurnDegrees);
        if ((paramBytes[0x18] == 2) || (paramBytes[0x18] == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, &baseDir, reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->x *= pYmMegaBirthShpTail3->m_speedScaleX;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->y *= pYmMegaBirthShpTail3->m_speedScaleYZ.x;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->z *= pYmMegaBirthShpTail3->m_speedScaleYZ.y;
        pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]),
                     *reinterpret_cast<Vec*>(particleData->m_matrix[1]));
    }

    if ((s32)paramBytes[0x18] < 6) {
        if ((s32)paramBytes[0x18] >= 4) {
            goto mode_4_5;
        }
        goto scalar;
    }
    if ((s32)paramBytes[0x18] >= 10) {
        goto scalar;
    }
    goto path;

scalar:
    {
        if (kPppYmMegaBirthShpTail3Zero != pYmMegaBirthShpTail3->m_speedRandRange) {
            float scale = pYmMegaBirthShpTail3->m_speedRandRange;

            switch (pYmMegaBirthShpTail3->m_randType) {
            case 1:
                Math.RandF();
                scale = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
                break;
            case 2:
            {
                float rand1 = Math.RandF();
                scale = (pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF()) * rand1;
                break;
            }
            case 3:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                scale = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3RandomSpeedScale * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1);
                break;
            }
            case 4:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
                break;
            }
            case 5:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3Half * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
                break;
            }
            }

            Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[1]);
            pppScaleVectorXYZ(*reinterpret_cast<Vec*>(particleData->m_matrix[0]), velocity, scale);
        }
        goto done;
    }

mode_4_5:
    {
        if (kPppYmMegaBirthShpTail3Zero == pYmMegaBirthShpTail3->m_speedRandRange) {
            goto done;
        }
        float speedRandHalf = kPppYmMegaBirthShpTail3Half * pYmMegaBirthShpTail3->m_speedRandRange;

        {
        float rand1;
        float rand2;
        float rand3;
        switch (pYmMegaBirthShpTail3->m_randType) {
        default:
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 2:
            rand1 = Math.RandF();
            particleData->m_matrix[0][0] = (pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            particleData->m_matrix[0][1] = (pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            particleData->m_matrix[0][2] = (pYmMegaBirthShpTail3->m_speedRandRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 3:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3RandomSpeedScale * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1);
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3RandomSpeedScale * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1);
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3RandomSpeedScale * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1);
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 4:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][0] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][1] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][2] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 5:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3Half * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3Half * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_speedRandRange - kPppYmMegaBirthShpTail3Half * (rand3 * ((pYmMegaBirthShpTail3->m_speedRandRange * rand2) * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        }

        particleData->m_matrix[0][0] *= pYmMegaBirthShpTail3->m_speedScaleX;
        particleData->m_matrix[0][1] *= pYmMegaBirthShpTail3->m_speedScaleYZ.x;
        particleData->m_matrix[0][2] *= pYmMegaBirthShpTail3->m_speedScaleYZ.y;
        goto done;
    }

path:
    {
        float* pathBase = reinterpret_cast<float*>(pppPObject->m_drawMatrixPtr);

        if (*(s16*)(paramBytes + 0x6a) >= 0) {
            short* pathInfo = reinterpret_cast<short*>(ppvEnv->m_shapeGroupPtr + (*(s16*)(paramBytes + 0x6a)));

            if (pathBase == 0) {
                pathBase = *(float**)((u8*)ppvEnv->m_mapMeshPtr[*pathInfo] + 0x2C);
            }

            {
                float vx;
                float vy;
                float vz;
                float sampleT;

                switch (pYmMegaBirthShpTail3->m_randType) {
                default:
                {
                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (s16)pathInfo[1]) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    u16 sampleIndex = vYmMegaBirthShpTail3->m_pathIndex;
                    u16* indices = (u16*)*(int*)(pathInfo + 2);
                    vYmMegaBirthShpTail3->m_pathIndex = sampleIndex + 1;

                    float* pathVec = (float*)((u8*)pathBase + indices[sampleIndex] * sizeof(Vec));
                    vx = pathVec[0];
                    vy = pathVec[1];
                    vz = pathVec[2];
                    goto path_store;
                }
                case 1:
                    Math.RandF();
                    sampleT = Math.RandF();
                    break;
                case 2:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    sampleT = r2 * (r1 * r0);
                    break;
                }
                case 3:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    sampleT = static_cast<float>(kPppYmMegaBirthShpTail3OneDouble - (r2 * (r1 * r0)));
                    break;
                }
                case 4:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    float r3 = Math.RandF();
                    sampleT = r3 * (r2 * (r1 * r0));
                    break;
                }
                case 5:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    float r3 = Math.RandF();
                    float r4 = Math.RandF();
                    sampleT = static_cast<float>(kPppYmMegaBirthShpTail3OneDouble - (r4 * (r3 * (r2 * (r1 * r0)))));
                    break;
                }
                }

                {
                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (s16)pathInfo[1]) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    int sampleIndex = (int)(sampleT * (float)pathInfo[1]);
                    float* pathVec = (float*)((u8*)pathBase + *(u16*)(*(int*)(pathInfo + 2) + sampleIndex * 2) * sizeof(Vec));
                    vx = pathVec[0];
                    vy = pathVec[1];
                    vz = pathVec[2];
                }
                path_store:

                particleData->m_matrix[0][0] = vx * pYmMegaBirthShpTail3->m_speedScaleX;
                particleData->m_matrix[0][1] = vy * pYmMegaBirthShpTail3->m_speedScaleYZ.x;
                particleData->m_matrix[0][2] = vz * pYmMegaBirthShpTail3->m_speedScaleYZ.y;

                if ((paramBytes[0x18] == 8) || (paramBytes[0x18] == 9)) {
                    Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[0]);
                    pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]), velocity);
                }
            }
        }
        goto done;
    }

done:

    if (paramBytes[0x16] != 0) {
        *(float*)(particleBytes + 0x30) = (float)vColor->m_alpha;
        particleBytes[0x35] = paramBytes[0x16];
    }
    if (paramBytes[0x17] != 0) {
        particleBytes[0x36] = paramBytes[0x17];
    }

    particleData->m_matrix[2][2] = pYmMegaBirthShpTail3->m_colorDeltaAdd[1];
    particleData->m_matrix[2][3] = pYmMegaBirthShpTail3->m_sizeStart;
    if (pYmMegaBirthShpTail3->m_colorDeltaAdd[3] != 0.0f) {
        float rand1 = Math.RandF();
        particleData->m_matrix[2][2] +=
            (kPppYmMegaBirthShpTail3Double * pYmMegaBirthShpTail3->m_colorDeltaAdd[3]) * rand1 -
            pYmMegaBirthShpTail3->m_colorDeltaAdd[3];
    }

    if (*(u16*)(paramBytes + 0x14) == 0) {
        *(u16*)((u8*)particleData + 0x22) = 0xFFFF;
    } else {
        *(s16*)((u8*)particleData + 0x22) = *(u16*)(paramBytes + 0x14);
    }
    particleBytes[0x34] = 0;

    switch (pYmMegaBirthShpTail3->m_wmatCopyMode) {
    case 0:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail3->m_emitterMatrix);
        break;
    case 1:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail3->m_emitterMatrix);
        break;
    }

    *(u16*)(particleBytes + 0x3a) = 0;
    *(u16*)(particleBytes + 0x3c) = 0;
    *(u16*)(particleBytes + 0x3e) = 0;
    particleBytes[0x38] = 0;
    particleBytes[0x37] = 0x1f;

    Vec zeroVec;
    zeroVec.z = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.x = 0.0f;
    s16* angle = (s16*)particleData;
    Vec* history = (Vec*)((u8*)particleData + 0x80);
    for (int i = 0; i < 0x1f; i++) {
        pppCopyVector(*history, zeroVec);
        history++;
        *(s16*)((u8*)angle + 0x40) = (s16)(rand() % 360);
        angle++;
    }

    particleBytes[0x38] = particleBytes[0x37];
    particleBytes[0x38] = particleBytes[0x38] - 1;
    *(u16*)(particleData->m_matrix[1] + 3) = 0;
}

/*
 * --INFO--
 * PAL Address: 8008eb40
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, pppYmMegaBirthShpTail3Offsets* param_2)
{
    int offset = param_2->m_serializedDataOffsets->m_workOffset;
    VYmMegaBirthShpTail3* work = reinterpret_cast<VYmMegaBirthShpTail3*>(pppYmMegaBirthShpTail3_->m_workArea + offset);

    if (work->m_particles != 0) {
        pppMemFree(work->m_particles);
        work->m_particles = 0;
    }
    if (work->m_wmats != 0) {
        pppMemFree(work->m_wmats);
        work->m_wmats = 0;
    }
    if (work->m_colors != 0) {
        pppMemFree(work->m_colors);
        work->m_colors = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008ebbc
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, pppYmMegaBirthShpTail3Offsets* param_2)
{
    pppFMATRIX* work =
        (pppFMATRIX*)(pppYmMegaBirthShpTail3_->m_workArea + param_2->m_serializedDataOffsets->m_workOffset);
    float initVal;

    pppUnitMatrix(*work);
    initVal = LoadFloat(kPppYmMegaBirthShpTail3Zero);
    work[1].value[0][2] = initVal;
    work[1].value[0][1] = initVal;
    work[1].value[0][0] = initVal;
    *reinterpret_cast<u32*>(&work[1].value[0][3]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][0]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][1]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][2]) = 0;
    *(u16*)(work[1].value[1] + 3) = 0;
    *(u16*)((u8*)work[1].value[1] + 0xe) = 0;
    *(u16*)(work[1].value[1] + 3) = 10000;
    *(u16*)work[2].value[2] = (u16)rand();
    pppUnitMatrix(g_matUnit);
    memset(work[1].value + 2, 0, 8);
    memset(work[1].value[2] + 2, 0, 8);
    memset(work + 2, 0, 8);
    memset(work[2].value[0] + 2, 0, 8);
    memset(work[2].value + 1, 0, 8);
    memset(work[2].value[1] + 2, 0, 8);
}
