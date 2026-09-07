#include "global.h"
#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppYmMegaBirthShpTail2Zero = 0.0f;
extern const float kPppYmMegaBirthShpTail2AlphaDivisor = 16384.0f;
extern const float kPppYmMegaBirthShpTail2Half = 0.5f;
extern const float kPppYmMegaBirthShpTail2DepthAlphaScale = 0.00787f;
extern const float kPppYmMegaBirthShpTail2ColorComponentMax = 127.0f;
extern const double kPppYmMegaBirthShpTail2U32ToDoubleBias = 4503601774854144.0;
extern const double kPppYmMegaBirthShpTail2S32ToDoubleBias = 4503599627370496.0;
extern const float kPppYmMegaBirthShpTail2Double = 2.0f;
extern const float kPppYmMegaBirthShpTail2HalfTurnDegrees = 180.0f;
extern const float kPppYmMegaBirthShpTail2RandomSpeedScale = 0.7f;
extern const double kPppYmMegaBirthShpTail2OneDouble = 1.0;
}
#include <dolphin/mtx.h>
#include <string.h>

struct VYmMegaBirthShpTail2
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

static const char s_pppYmMegaBirthShpTail2_cpp[] = "pppYmMegaBirthShpTail2.cpp";

STATIC_ASSERT(sizeof(YmMegaBirthShpTail2DataOffsets) == 0xC);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_workOffset) == 0x8);

static inline YmMegaBirthShpTail2DataOffsets* GetYmMegaBirthShpTail2DataOffsets(_pppCtrlTable* offsets)
{
    return reinterpret_cast<YmMegaBirthShpTail2DataOffsets*>(offsets->m_serializedDataOffsets);
}

void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);

static inline float LoadFloat(const float& value)
{
    return value;
}

/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_common_subs off
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, pppYmMegaBirthShpTail2RenderStep* stepData, _pppCtrlTable* offsets)
{
    u8* step = (u8*)stepData;
    YmMegaBirthShpTail2DataOffsets* serializedOffsets = GetYmMegaBirthShpTail2DataOffsets(offsets);
    const s32 colorOffset = serializedOffsets->m_colorOffset;
    const s32 particleDataOffset = serializedOffsets->m_workOffset;
    VYmMegaBirthShpTail2* work =
        (VYmMegaBirthShpTail2*)(object->m_workArea + particleDataOffset);
    VColor* colorWork = (VColor*)(object->m_workArea + colorOffset);
    _PARTICLE_DATA* const particlesBase = work->m_particles;
    _PARTICLE_WMAT* const wmatsBase = work->m_wmats;
    _PARTICLE_COLOR* const colorsBase = work->m_colors;
    _PARTICLE_DATA* particles = particlesBase;
    _PARTICLE_WMAT* wmats = wmatsBase;
    _PARTICLE_COLOR* colors = colorsBase;
    s8 hasRequiredMemory;

    if (particlesBase == 0) {
        hasRequiredMemory = false;
    } else if (wmatsBase == 0) {
        hasRequiredMemory = false;
    } else if ((step[0x69] != 0) && (colorsBase == 0)) {
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
        0, &object->m_drawMatrix, *(float*)(step + 0x88), step[0x8C], step[0x0C],
        step[0x6E], 0, step[0x6B] == 0, 1, 0);
    pppSetBlendMode(step[0x6E]);

    for (u32 i = 0; i < work->m_maxParticles; i++) {
        u8* particle = (u8*)particles + i * 0x1B8;
        if (*(u16*)(particle + 0x22) != 0) {
            const s32 frameCountRaw = *(s16*)(step + 0x84);
            s32 frameCount = frameCountRaw;
            pppFMATRIX drawMtx;
            Vec zeroVec;
            Vec segVec;
            union { Vec cameraPos; double _camAlign[2]; };
            union { Vec trailPos; double _trailAlign[2]; };
            union { Vec managerPos; double _mgrAlign[2]; };
            GXColor amb;
            const s32 shapeFrameIndex = *(u16*)(particle + 0x20);
            pppShapeAnimFrame* shapeFrame = &shapeAnim->m_frames[shapeFrameIndex];
            tagOAN3_SHAPE* shape =
                reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) + shapeFrame->m_shapeOffset);
            const s32 trailReadIndex = *(u8*)(particle + 0x38);
            const s32 trailMaxIndex = *(u8*)(particle + 0x37) - 1;
            s32 trailNextIndex;
            const float stepDivisor = (float)((s32)frameCountRaw - 1);
            const float alphaScale = (float)*(s16*)((u8*)colorWork + 6) / LoadFloat(kPppYmMegaBirthShpTail2AlphaDivisor);
            float fadeA = (float)step[0x7B] * alphaScale;
            const float fadeANum = fadeA - (float)step[0x7F] * alphaScale;
            float fadeRGB[3];
            fadeRGB[2] = (float)step[0x78];
            fadeRGB[1] = (float)step[0x79];
            fadeRGB[0] = (float)step[0x7A];
            const float fadeRNum = fadeRGB[2] - (float)step[0x7C];
            const float fadeGNum = fadeRGB[1] - (float)step[0x7D];
            const float fadeBNum = fadeRGB[0] - (float)step[0x7E];
            float fadeRStep;
            float fadeGStep;
            float fadeBStep;
            float fadeAStep;
            if (stepDivisor != LoadFloat(kPppYmMegaBirthShpTail2Zero)) {
                fadeGStep = fadeGNum / stepDivisor;
                fadeBStep = fadeBNum / stepDivisor;
                fadeAStep = fadeANum / stepDivisor;
                fadeRStep = fadeRNum / stepDivisor;
            } else {
                fadeRStep = LoadFloat(kPppYmMegaBirthShpTail2Half);
                fadeGStep = LoadFloat(kPppYmMegaBirthShpTail2Half);
                fadeBStep = LoadFloat(kPppYmMegaBirthShpTail2Half);
                fadeAStep = LoadFloat(kPppYmMegaBirthShpTail2Half);
            }
            Vec* history;
            float drawScale;
            float drawScaleStep;
            s32 trailStartIndex;
            float segLen;
            float segProgress = LoadFloat(kPppYmMegaBirthShpTail2Zero);
            float segRemaining;
            float trailX, trailY, trailZ;
            float drawX, drawY, drawZ;
            float camX, camY, camZ;
            float segX, segY, segZ;

            pppUnitMatrix(drawMtx);
            history = (Vec*)(particle + 0x40);
            trailStartIndex = *(u8*)(particle + 0x38);
            drawScale = *(float*)(step + 0x70);
            drawScaleStep = (drawScale - *(float*)(step + 0x74)) / stepDivisor;
            {
                Vec* p = &history[trailReadIndex];
                trailX = p->x;
                trailY = p->y;
                trailZ = p->z;
            }
            drawX = trailX;
            drawY = trailY;
            drawZ = trailZ;
            trailNextIndex = trailReadIndex + 1;
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
            zeroVec.z = LoadFloat(kPppYmMegaBirthShpTail2Zero);
            zeroVec.y = LoadFloat(kPppYmMegaBirthShpTail2Zero);
            zeroVec.x = LoadFloat(kPppYmMegaBirthShpTail2Zero);
            segVec.x = segX;
            segVec.y = segY;
            segVec.z = segZ;
            segLen = PSVECDistance(&zeroVec, &segVec);
            segRemaining = segLen;

            if (step[0x86] == 0) {
                goto step_advance;
            }
            for (frameCount = *(u16*)(step + 0x84); frameCount > 0; frameCount--) {
                Vec* testPos = &((Vec*)(particle + 0x40))[trailNextIndex];
                if ((testPos->x != 0.0f) || (testPos->y != 0.0f) || (testPos->z != 0.0f)) {
                    pppUnitMatrix(drawMtx);
                    drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                    drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                    drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;
                    trailPos.x = trailX;
                    trailPos.y = trailY;
                    trailPos.z = trailZ;

                    if (step[0x8D] == 0) {
                        PSMTXMultVec(ppvWorldMatrix, &trailPos, &cameraPos);
                    } else if (step[0x8D] == 1) {
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

                    amb.r = (u8)fadeRGB[2];
                    amb.g = (u8)fadeRGB[1];
                    amb.b = (u8)fadeRGB[0];
                    amb.a = (u8)(fadeA * (LoadFloat(kPppYmMegaBirthShpTail2DepthAlphaScale) * (LoadFloat(kPppYmMegaBirthShpTail2ColorComponentMax) - *(float*)(particle + 0x30))));
                    GXSetChanAmbColor(GX_COLOR0A0, amb);
                    pppDrawShp(shape, ppvEnv->m_materialSetPtr, step[0x6E]);
                }
            step_advance:
                fadeRGB[2] -= fadeRStep;
                fadeRGB[1] -= fadeGStep;
                fadeRGB[0] -= fadeBStep;
                fadeA -= fadeAStep;
                drawScale -= drawScaleStep;

                if (*(float*)(step + 0x80) <= LoadFloat(kPppYmMegaBirthShpTail2Zero)) {
                    break;
                }

                for (;;) {
                    Vec innerZero;
                    Vec innerSeg;
                    s32 prevNext;

                    if (segRemaining >= *(float*)(step + 0x80)) {
                        trailX = segX * segProgress / segLen + drawX;
                        trailY = segY * segProgress / segLen + drawY;
                        trailZ = segZ * segProgress / segLen + drawZ;
                        segProgress += *(float*)(step + 0x80);
                        segRemaining -= *(float*)(step + 0x80);
                        break;
                    }

                    prevNext = trailNextIndex;
                    trailNextIndex++;
                    if (prevNext == trailMaxIndex) {
                        trailNextIndex = 0;
                    }
                    if (trailNextIndex == trailStartIndex) {
                        goto next_particle;
                    }

                    segProgress -= segLen;
                    drawX = camX;
                    drawY = camY;
                    drawZ = camZ;
                    {
                        Vec* p = &history[trailNextIndex];
                        camY = p->y;
                        camZ = p->z;
                        camX = p->x;
                    }
                    segY = camY - drawY;
                    segZ = camZ - drawZ;
                    segX = camX - drawX;
                    innerZero.z = LoadFloat(kPppYmMegaBirthShpTail2Zero);
                    innerZero.y = LoadFloat(kPppYmMegaBirthShpTail2Zero);
                    innerZero.x = LoadFloat(kPppYmMegaBirthShpTail2Zero);
                    innerSeg.x = segX;
                    innerSeg.y = segY;
                    innerSeg.z = segZ;
                    segLen = PSVECDistance(&innerZero, &innerSeg);
                    segRemaining += segLen;
                }
            }
        }
        next_particle:;
        if (wmats != 0) {
            wmats = wmats + 1;
        }
        if (colors != 0) {
            colors = colors + 1;
        }
    }
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* param, _pppCtrlTable* offsets)
{
    s8 hasRequiredMemory;
    u32 i;
    u8* paramPayload;
    int colorOffset;
    int spawnCount;
    _PARTICLE_COLOR* particleColor;
    _PARTICLE_WMAT* worldMat;
    u8* particleData;

    YmMegaBirthShpTail2DataOffsets* serializedOffsets = GetYmMegaBirthShpTail2DataOffsets(offsets);
    colorOffset = serializedOffsets->m_colorOffset;
    VYmMegaBirthShpTail2* const work =
        (VYmMegaBirthShpTail2*)(object->m_workArea + serializedOffsets->m_workOffset);
    VColor* const colorWork = (VColor*)(object->m_workArea + colorOffset);
    paramPayload = (u8*)param;

    if (work->m_particles == 0) {
        work->m_maxParticles = *(u16*)((u8*)&param->m_matrix + 0xe);
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_maxParticles * 0x1b8, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x30e);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * 0x1b8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc(
            work->m_maxParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x316);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * sizeof(_PARTICLE_WMAT));
        }

        if (paramPayload[0x69] != 0) {
            work->m_colors = (_PARTICLE_COLOR*)pppMemAlloc(
                work->m_maxParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x31e);
            if (work->m_colors != 0) {
                memset(work->m_colors, 0, work->m_maxParticles * sizeof(_PARTICLE_COLOR));
            }
        }

        work->m_tailScaleDirection = param->m_directionTail;
        pppNormalize(work->m_tailScaleDirection, work->m_tailScaleDirection);
    }

    if (work->m_particles == 0) {
        hasRequiredMemory = false;
    } else if (work->m_wmats == 0) {
        hasRequiredMemory = false;
    } else if ((paramPayload[0x69] != 0) && (work->m_colors == 0)) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }

    if (hasRequiredMemory) {
        switch (paramPayload[0x18]) {
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

        spawnCount = 0;
        i = spawnCount;
        particleData = (u8*)work->m_particles;
        worldMat = work->m_wmats;
        particleColor = work->m_colors;

        if ((ppvUserStopPartF == 0) && (*(s32*)((u8*)&param->m_matrix + 4) != 0xFFFF)) {
            work->m_lifeLimit = work->m_lifeLimit + 1;

            for (; i < work->m_maxParticles; i++) {
                if (*(u16*)(particleData + 0x22) != 0) {
                    calc((_pppPObject*)object, work, param, (_PARTICLE_DATA*)particleData, colorWork, particleColor);
                } else {
                    if ((*(u16*)((u8*)&param->m_matrix + 0x12) <= work->m_lifeLimit) &&
                        (spawnCount < *(u16*)((u8*)&param->m_matrix + 0x10))) {
                        birth((_pppPObject*)object, work, param, colorWork, (_PARTICLE_DATA*)particleData, worldMat,
                            particleColor);
                        spawnCount = spawnCount + 1;
                    }
                }

                if (worldMat != 0) {
                    worldMat = worldMat + 1;
                }
                if (particleColor != 0) {
                    particleColor = particleColor + 1;
                }
                particleData = particleData + 0x1b8;
            }

            if (spawnCount > 0) {
                work->m_lifeLimit = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008b824
 * PAL Size: 772b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
          PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    s32 alpha = ((u8*)vColor)[0xb];
    u8* color = (u8*)particleData;
    float* blend = (float*)(color + 0x30);
    float* velocityScale = (float*)(color + 0x28);
    float* tailScale = (float*)(color + 0x2c);
    u8* frameState = color + 0x30;
    u8 frameWindow;
    u8 fadeInFrames;
    u8 historyIndex;
    u16 frameIndex;
    pppShapeAnimData* shapeAnim;
    pppShapeAnimFrame* frameEntry;
    Vec scaled;

    *velocityScale = *velocityScale + pYmMegaBirthShpTail2->m_colorDeltaAdd[2];
    *tailScale = *tailScale + pYmMegaBirthShpTail2->m_sizeVal;

    pppScaleVectorXYZ(scaled, *reinterpret_cast<Vec*>(color + 0x10), *velocityScale);
    pppAddVector(*(Vec*)(color + 0x0), *(Vec*)(color + 0x0), scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail2->m_tailScaleDirection, *tailScale);
    pppAddVector(*(Vec*)(color + 0x0), *(Vec*)(color + 0x0), scaled);

    if (*(u16*)((u8*)&pYmMegaBirthShpTail2->m_matrix[1] + 0x4) != 0) {
        *(u16*)(color + 0x22) = *(u16*)(color + 0x22) - 1;
    }

    frameState[4] = frameState[4] + 1;
    frameWindow = frameState[5];
    if ((frameWindow != 0) && (frameState[4] <= frameWindow)) {
        *blend = *blend - ((float)alpha / (float)frameWindow);
        if (*blend < kPppYmMegaBirthShpTail2Zero) {
            *blend = kPppYmMegaBirthShpTail2Zero;
        }
    }

    if ((frameState[6] != 0) && (*(u16*)(color + 0x22) <= frameState[6])) {
        fadeInFrames = *((u8*)&pYmMegaBirthShpTail2->m_matrix[1] + 7);
        *blend = *blend + ((float)alpha / (float)fadeInFrames);
        if (*blend > kPppYmMegaBirthShpTail2ColorComponentMax) {
            *blend = kPppYmMegaBirthShpTail2ColorComponentMax;
        }
    }

    if (frameState[8] == 0) {
        frameState[8] = frameState[7];
    }
    frameState[8] = frameState[8] - 1;
    historyIndex = frameState[8];

    PSMTXMultVec(pppPObject->m_localMatrix.value, (Vec*)(color + 0x0),
                 (Vec*)(color + historyIndex * sizeof(VColor) + 0x40));

    frameIndex = *(u16*)(color + 0x1e);
    shapeAnim =
        static_cast<pppShapeAnimData*>(
        ppvEnv->m_shapeTablePtr[*reinterpret_cast<s32*>((u8*)pYmMegaBirthShpTail2->m_matrix[0] + 4)]
            ->m_animData);
    *(u16*)(color + 0x20) = frameIndex;

    frameEntry = &shapeAnim->m_frames[frameIndex];
    *(u16*)(color + 0x1c) =
        *(u16*)(color + 0x1c) + *reinterpret_cast<s32*>((u8*)pYmMegaBirthShpTail2->m_matrix[0] + 8);
    int elapsedFrame = *(u16*)(color + 0x1c);
    int frameDuration = frameEntry->m_duration;
    if ((int)elapsedFrame < frameDuration) {
        return;
    }

    *(u16*)(color + 0x1c) = (u16)(elapsedFrame - frameDuration);
    *(u16*)(color + 0x1e) = *(u16*)(color + 0x1e) + 1;
    if ((int)*(u16*)(color + 0x1e) >= shapeAnim->m_frameCount) {
        if ((frameEntry->m_flags & 0x80) != 0) {
            *(u16*)(color + 0x1e) = 0;
            *(u16*)(color + 0x1c) = 0;
        } else {
            *(u16*)(color + 0x1c) = 0;
            *(u16*)(color + 0x1e) = *(u16*)(color + 0x1e) - 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008bb28
 * PAL Size: 3704b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail2* work, PYmMegaBirthShpTail2* param, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    u8* paramBytes = (u8*)param;
    u8* particleBytes = (u8*)particleData;
    float spread = (float)paramBytes[0x19];
    float spreadRange = kPppYmMegaBirthShpTail2Double * spread;

    memset(particleData, 0, 0x1b8);
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

        baseDir.x = param->m_matrix[2][0];
        baseDir.y = param->m_matrix[2][1];
        baseDir.z = param->m_matrix[2][2];
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / kPppYmMegaBirthShpTail2HalfTurnDegrees);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / kPppYmMegaBirthShpTail2HalfTurnDegrees);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / kPppYmMegaBirthShpTail2HalfTurnDegrees);
        if ((paramBytes[0x18] == 2) || (paramBytes[0x18] == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, &baseDir, reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        particleData->m_matrix[1][0] *= *(float*)(paramBytes + 0x58);
        particleData->m_matrix[1][1] *= param->m_speedScale.x;
        particleData->m_matrix[1][2] *= param->m_speedScale.y;
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
        float speedRandRange = param->m_speedRandRange;
        if (speedRandRange != kPppYmMegaBirthShpTail2Zero) {
            float scale = speedRandRange;

            switch (param->m_randType) {
            case 1:
                Math.RandF();
                scale = param->m_speedRandRange * Math.RandF();
                break;
            case 2: {
                float a = Math.RandF();
                scale = a * (param->m_speedRandRange * Math.RandF());
                break;
            }
            case 3: {
                float a = Math.RandF();
                scale = -(kPppYmMegaBirthShpTail2RandomSpeedScale * (a * (param->m_speedRandRange * Math.RandF())) - *(float*)(paramBytes + 0x54));
                break;
            }
            case 4: {
                float a = Math.RandF();
                float b = Math.RandF();
                float c = Math.RandF();
                scale = Math.RandF() * (c * (a * (param->m_speedRandRange * b)));
                break;
            }
            case 5: {
                float a = Math.RandF();
                float b = Math.RandF();
                scale = -(kPppYmMegaBirthShpTail2Half * (Math.RandF() * (a * (param->m_speedRandRange * b))) - *(float*)(paramBytes + 0x54));
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
        if (param->m_speedRandRange == kPppYmMegaBirthShpTail2Zero) {
            goto done;
        }
        float speedRandHalf = kPppYmMegaBirthShpTail2Half * param->m_speedRandRange;

        switch (param->m_randType) {
        default:
            particleData->m_matrix[0][0] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_matrix[0][0] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = param->m_speedRandRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 2: {
            float a0 = Math.RandF();
            particleData->m_matrix[0][0] = a0 * (param->m_speedRandRange * Math.RandF());
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            particleData->m_matrix[0][1] = a1 * (param->m_speedRandRange * Math.RandF());
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            particleData->m_matrix[0][2] = a2 * (param->m_speedRandRange * Math.RandF());
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 3: {
            float a0 = Math.RandF();
            particleData->m_matrix[0][0] = -(kPppYmMegaBirthShpTail2RandomSpeedScale * (a0 * (param->m_speedRandRange * Math.RandF())) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            particleData->m_matrix[0][1] = -(kPppYmMegaBirthShpTail2RandomSpeedScale * (a1 * (param->m_speedRandRange * Math.RandF())) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            particleData->m_matrix[0][2] = -(kPppYmMegaBirthShpTail2RandomSpeedScale * (a2 * (param->m_speedRandRange * Math.RandF())) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 4: {
            float a0 = Math.RandF();
            float b0 = Math.RandF();
            float c0 = Math.RandF();
            particleData->m_matrix[0][0] = Math.RandF() * (c0 * (a0 * (param->m_speedRandRange * b0)));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            float b1 = Math.RandF();
            float c1 = Math.RandF();
            particleData->m_matrix[0][1] = Math.RandF() * (c1 * (a1 * (param->m_speedRandRange * b1)));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            float b2 = Math.RandF();
            float c2 = Math.RandF();
            particleData->m_matrix[0][2] = Math.RandF() * (c2 * (a2 * (param->m_speedRandRange * b2)));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 5: {
            float a0 = Math.RandF();
            float b0 = Math.RandF();
            particleData->m_matrix[0][0] = -(kPppYmMegaBirthShpTail2Half * (Math.RandF() * (a0 * (param->m_speedRandRange * b0))) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            float b1 = Math.RandF();
            particleData->m_matrix[0][1] = -(kPppYmMegaBirthShpTail2Half * (Math.RandF() * (a1 * (param->m_speedRandRange * b1))) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            float b2 = Math.RandF();
            particleData->m_matrix[0][2] = -(kPppYmMegaBirthShpTail2Half * (Math.RandF() * (a2 * (param->m_speedRandRange * b2))) - *(float*)(paramBytes + 0x54));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        }

        particleData->m_matrix[0][0] *= *(float*)(paramBytes + 0x58);
        particleData->m_matrix[0][1] *= param->m_speedScale.x;
        particleData->m_matrix[0][2] *= param->m_speedScale.y;
        goto done;
    }

path:
    {
        float* pathBase = reinterpret_cast<float*>(pppPObject->m_drawMatrixPtr);

        if (param->m_tail2PathIndex >= 0) {
            short* pathInfo = reinterpret_cast<short*>(ppvEnv->m_shapeGroupPtr + (param->m_tail2PathIndex));

            if (pathBase == 0) {
                pathBase = (float*)ppvEnv->m_mapMeshPtr[*pathInfo]->m_vertices;
            }

            {
                float vx;
                float vy;
                float vz;
                float sampleT;

                switch (param->m_randType) {
                default:
                    if ((int)work->m_pathIndex >= pathInfo[1]) {
                        work->m_pathIndex = 0;
                    }

                    if (pathBase != 0) {
                        int sampleIndex = work->m_pathIndex;
                        u16* indices = (u16*)*(int*)(pathInfo + 2);
                        work->m_pathIndex = sampleIndex + 1;

                        float* pathVec = (float*)((u8*)pathBase + indices[(u16)sampleIndex] * sizeof(Vec));
                        vx = pathVec[0];
                        vy = pathVec[1];
                        vz = pathVec[2];
                    }
                    goto path_apply;
                case 1:
                    Math.RandF();
                    sampleT = Math.RandF();
                    break;
                case 2: {
                    float a = Math.RandF();
                    float b = Math.RandF();
                    sampleT = a * b * Math.RandF();
                    break;
                }
                case 3: {
                    float a = Math.RandF();
                    float b = Math.RandF();
                    sampleT = static_cast<float>(kPppYmMegaBirthShpTail2OneDouble - (a * b * Math.RandF()));
                    break;
                }
                case 4: {
                    float a = Math.RandF();
                    float b = Math.RandF();
                    float c = Math.RandF();
                    sampleT = a * (b * (c * Math.RandF()));
                    break;
                }
                case 5: {
                    float a = Math.RandF();
                    float b = Math.RandF();
                    float c = Math.RandF();
                    float d = Math.RandF();
                    sampleT = static_cast<float>(kPppYmMegaBirthShpTail2OneDouble - (a * (b * (c * (d * Math.RandF())))));
                    break;
                }
                }

                if ((int)work->m_pathIndex >= pathInfo[1]) {
                    work->m_pathIndex = 0;
                }

                if (pathBase != 0) {
                    int sampleIndex = (int)(sampleT * (float)pathInfo[1]);
                    float* pathVec = (float*)((u8*)pathBase + *(u16*)(*(int*)(pathInfo + 2) + sampleIndex * 2) * sizeof(Vec));
                    vx = pathVec[0];
                    vy = pathVec[1];
                    vz = pathVec[2];
                }

            path_apply:
                particleData->m_matrix[0][0] = vx * param->field_0x58;
                particleData->m_matrix[0][1] = vy * param->m_speedScale.x;
                particleData->m_matrix[0][2] = vz * param->m_speedScale.y;

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

    particleData->m_matrix[2][2] = param->m_colorDeltaAdd[1];
    particleData->m_matrix[2][3] = param->m_sizeStart;
    if (param->m_colorDeltaAdd[3] != 0.0f) {
        particleData->m_matrix[2][2] +=
            (kPppYmMegaBirthShpTail2Double * param->m_colorDeltaAdd[3]) * Math.RandF() - *(float*)(paramBytes + 0x48);
    }

    if (*(u16*)(paramBytes + 0x14) == 0) {
        *(u16*)(particleBytes + 0x22) = 0xFFFF;
    } else {
        *(u16*)(particleBytes + 0x22) = *(u16*)(paramBytes + 0x14);
    }
    particleBytes[0x34] = 0;

    switch ((s32)paramBytes[0x8d]) {
    case 0:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, work->m_emitterMatrix);
        break;
    case 1:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, work->m_emitterMatrix);
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
    Vec* history = (Vec*)(particleBytes + 0x40);
    for (int i = 0x1e; i >= 0; i--) {
        pppCopyVector(*history, zeroVec);
        history++;
    }

    particleBytes[0x38] = particleBytes[0x37];
    particleBytes[0x38] = particleBytes[0x38] - 1;
}

/*
 * --INFO--
 * PAL Address: 0x8008c9a0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    u8* work = param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset;
    void** ptrBc = (void**)(work + 0x3c);
    void** ptrC0 = (void**)(work + 0x40);
    void** ptrC4 = (void**)(work + 0x44);

    if (*ptrBc != 0) {
        pppMemFree(*ptrBc);
        *ptrBc = 0;
    }
    if (*ptrC0 != 0) {
        pppMemFree(*ptrC0);
        *ptrC0 = 0;
    }
    if (*ptrC4 != 0) {
        pppMemFree(*ptrC4);
        *ptrC4 = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008ca1c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    pppFMATRIX* work = (pppFMATRIX*)(param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);
    float initVal;

    pppUnitMatrix(*work);
    initVal = LoadFloat(kPppYmMegaBirthShpTail2Zero);

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
    pppUnitMatrix(g_matUnit);
}
