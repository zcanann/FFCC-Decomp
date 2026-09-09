#include "global.h"
#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"

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
    unsigned short m_emitTimer;
    unsigned short m_pathIndex;
};

static pppFMATRIX g_matUnit;

static const char s_pppYmMegaBirthShpTail2_cpp[] = "pppYmMegaBirthShpTail2.cpp";

STATIC_ASSERT(sizeof(PYmMegaBirthShpTail2) == 0x90);
STATIC_ASSERT(sizeof(VYmMegaBirthShpTail2) == 0x50);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_particles) == 0x3C);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_wmats) == 0x40);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_colors) == 0x44);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_maxParticles) == 0x48);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_emitTimer) == 0x4C);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_pathIndex) == 0x4E);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_shapeIndex) == 0x4);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_frameStep) == 0x8);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_maxParticles) == 0xe);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_life) == 0x14);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_spawnMode) == 0x18);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_baseDirection) == 0x20);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_tailDirection) == 0x30);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_speed) == 0x40);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_spawnScale) == 0x58);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_randType) == 0x68);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_pathIndex) == 0x6c);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_colorStart) == 0x78);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_segmentLength) == 0x80);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_drawCount) == 0x84);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_depth) == 0x88);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_matrixMode) == 0x8d);

STATIC_ASSERT(sizeof(YmMegaBirthShpTail2DataOffsets) == 0xC);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_workOffset) == 0x8);

static inline YmMegaBirthShpTail2DataOffsets* GetYmMegaBirthShpTail2DataOffsets(_pppCtrlTable* offsets)
{
    return reinterpret_cast<YmMegaBirthShpTail2DataOffsets*>(offsets->m_serializedDataOffsets);
}

void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);


/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 * EN Address: 0x8008A660
 * EN Size: 1840b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* stepData, _pppCtrlTable* offsets)
{
    PYmMegaBirthShpTail2* step = stepData;
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
    } else if ((step->m_enableParticleColor != 0) && (colorsBase == 0)) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }
    if (!hasRequiredMemory) {
        return;
    }
    if (step->m_shapeIndex == 0xFFFF) {
        return;
    }
    const u32 dataValIndex = step->m_shapeIndex;

    pppShapeAnimData* shapeAnim =
        static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[dataValIndex]->m_animData);
    pppSetDrawEnv(
        0, &object->m_drawMatrix, step->m_depth, step->m_lightTarget, step->m_fogIndex,
        step->m_blendMode, 0, step->m_disableDepthTest == 0, 1, 0);
    pppSetBlendMode(step->m_blendMode);

    for (u32 i = 0; i < work->m_maxParticles; i++) {
        u8* particle = (u8*)particles + i * 0x1B8;
        if (*(u16*)(particle + 0x22) != 0) {
            const s32 drawCount = step->m_drawCount;
            s32 frameCount = drawCount;
            pppFMATRIX drawMtx;
            Vec zeroVec;
            Vec segVec;
            Vec cameraPos;
            Vec trailPos;
            Vec managerPos;
            GXColor amb;
            const s32 shapeFrameIndex = *(u16*)(particle + 0x20);
            pppShapeAnimFrame* shapeFrame = &shapeAnim->m_frames[shapeFrameIndex];
            tagOAN3_SHAPE* shape =
                reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) + shapeFrame->m_shapeOffset);
            const s32 trailReadIndex = *(u8*)(particle + 0x38);
            const s32 trailMaxIndex = *(u8*)(particle + 0x37) - 1;
            s32 trailNextIndex;
            const float stepDivisor = (float)((s32)drawCount - 1);
            const float alphaScale = (float)*(s16*)((u8*)colorWork + 6) / 16384.0f;
            float fadeA = (float)step->m_colorStart.a * alphaScale;
            const float fadeANum = fadeA - (float)step->m_colorEnd.a * alphaScale;
            float fadeRGB[3];
            fadeRGB[0] = (float)step->m_colorStart.r;
            fadeRGB[1] = (float)step->m_colorStart.g;
            fadeRGB[2] = (float)step->m_colorStart.b;
            const float fadeRNum = fadeRGB[0] - (float)step->m_colorEnd.r;
            const float fadeGNum = fadeRGB[1] - (float)step->m_colorEnd.g;
            const float fadeBNum = fadeRGB[2] - (float)step->m_colorEnd.b;
            float fadeRStep;
            float fadeGStep;
            float fadeBStep;
            float fadeAStep;
            if (stepDivisor != 0.0f) {
                fadeGStep = fadeGNum / stepDivisor;
                fadeBStep = fadeBNum / stepDivisor;
                fadeAStep = fadeANum / stepDivisor;
                fadeRStep = fadeRNum / stepDivisor;
            } else {
                fadeRStep = 0.5f;
                fadeGStep = 0.5f;
                fadeBStep = 0.5f;
                fadeAStep = 0.5f;
            }
            Vec* history;
            float drawScale;
            float drawScaleStep;
            s32 trailStartIndex;
            float segLen;
            float segProgress = 0.0f;
            float segRemaining;
            float trailX, trailY, trailZ;
            float drawX, drawY, drawZ;
            float camX, camY, camZ;
            float segX, segY, segZ;

            pppUnitMatrix(drawMtx);
            history = (Vec*)(particle + 0x40);
            trailStartIndex = *(u8*)(particle + 0x38);
            drawScale = step->m_drawScaleStart;
            drawScaleStep = (drawScale - step->m_drawScaleEnd) / stepDivisor;
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
            zeroVec.z = 0.0f;
            zeroVec.y = 0.0f;
            zeroVec.x = 0.0f;
            segVec.x = segX;
            segVec.y = segY;
            segVec.z = segZ;
            segLen = PSVECDistance(&zeroVec, &segVec);
            segRemaining = segLen;

            if (step->m_drawHead == 0) {
                goto step_advance;
            }
            for (frameCount = step->m_drawCount; frameCount > 0; frameCount--) {
                Vec* testPos = &((Vec*)(particle + 0x40))[trailNextIndex];
                if ((testPos->x != 0.0f) || (testPos->y != 0.0f) || (testPos->z != 0.0f)) {
                    pppUnitMatrix(drawMtx);
                    drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                    drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                    drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;
                    trailPos.x = trailX;
                    trailPos.y = trailY;
                    trailPos.z = trailZ;

                    if (step->m_matrixMode == 0) {
                        PSMTXMultVec(ppvWorldMatrix, &trailPos, &cameraPos);
                    } else if (step->m_matrixMode == 1) {
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

                    amb.r = (u8)fadeRGB[0];
                    amb.g = (u8)fadeRGB[1];
                    amb.b = (u8)fadeRGB[2];
                    amb.a = (u8)(fadeA * (0.00787f * (127.0f - *(float*)(particle + 0x30))));
                    GXSetChanAmbColor(GX_COLOR0A0, amb);
                    pppDrawShp(shape, ppvEnv->m_materialSetPtr, step->m_blendMode);
                }
            step_advance:
                fadeRGB[0] -= fadeRStep;
                fadeRGB[1] -= fadeGStep;
                fadeRGB[2] -= fadeBStep;
                fadeA -= fadeAStep;
                drawScale -= drawScaleStep;

                if (step->m_segmentLength <= 0.0f) {
                    break;
                }

                for (;;) {
                    Vec innerZero;
                    Vec innerSeg;
                    s32 prevNext;

                    if (segRemaining >= step->m_segmentLength) {
                        trailX = segX * segProgress / segLen + drawX;
                        trailY = segY * segProgress / segLen + drawY;
                        trailZ = segZ * segProgress / segLen + drawZ;
                        segProgress += step->m_segmentLength;
                        segRemaining -= step->m_segmentLength;
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
                    innerZero.z = 0.0f;
                    innerZero.y = 0.0f;
                    innerZero.x = 0.0f;
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

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 * EN Address: 0x8008AD90
 * EN Size: 1072b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* param, _pppCtrlTable* offsets)
{
    s8 hasRequiredMemory;
    u32 i;
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

    if (work->m_particles == 0) {
        work->m_maxParticles = param->m_maxParticles;
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

        if (param->m_enableParticleColor != 0) {
            work->m_colors = (_PARTICLE_COLOR*)pppMemAlloc(
                work->m_maxParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x31e);
            if (work->m_colors != 0) {
                memset(work->m_colors, 0, work->m_maxParticles * sizeof(_PARTICLE_COLOR));
            }
        }

        work->m_tailScaleDirection = param->m_tailDirection;
        pppNormalize(work->m_tailScaleDirection, work->m_tailScaleDirection);
    }

    if (work->m_particles == 0) {
        hasRequiredMemory = false;
    } else if (work->m_wmats == 0) {
        hasRequiredMemory = false;
    } else if ((param->m_enableParticleColor != 0) && (work->m_colors == 0)) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }

    if (hasRequiredMemory) {
        switch (param->m_spawnMode) {
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

        if ((ppvUserStopPartF == 0) && (param->m_shapeIndex != 0xFFFF)) {
            work->m_emitTimer = work->m_emitTimer + 1;

            for (; i < work->m_maxParticles; i++) {
                if (*(u16*)(particleData + 0x22) != 0) {
                    calc((_pppPObject*)object, work, param, (_PARTICLE_DATA*)particleData, colorWork, particleColor);
                } else {
                    if ((param->m_emitInterval <= work->m_emitTimer) &&
                        (spawnCount < param->m_emitCount)) {
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
                work->m_emitTimer = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008b824
 * PAL Size: 772b
 * EN Address: 0x8008B1C0
 * EN Size: 772b
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

    *velocityScale = *velocityScale + pYmMegaBirthShpTail2->m_speedStep;
    *tailScale = *tailScale + pYmMegaBirthShpTail2->m_tailSpeedStep;

    pppScaleVectorXYZ(scaled, *reinterpret_cast<Vec*>(color + 0x10), *velocityScale);
    pppAddVector(*(Vec*)(color + 0x0), *(Vec*)(color + 0x0), scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail2->m_tailScaleDirection, *tailScale);
    pppAddVector(*(Vec*)(color + 0x0), *(Vec*)(color + 0x0), scaled);

    if (pYmMegaBirthShpTail2->m_life != 0) {
        *(u16*)(color + 0x22) = *(u16*)(color + 0x22) - 1;
    }

    frameState[4] = frameState[4] + 1;
    frameWindow = frameState[5];
    if ((frameWindow != 0) && (frameState[4] <= frameWindow)) {
        *blend = *blend - ((float)alpha / (float)frameWindow);
        if (*blend < 0.0f) {
            *blend = 0.0f;
        }
    }

    if ((frameState[6] != 0) && (*(u16*)(color + 0x22) <= frameState[6])) {
        fadeInFrames = pYmMegaBirthShpTail2->m_fadeOutFrames;
        *blend = *blend + ((float)alpha / (float)fadeInFrames);
        if (*blend > 127.0f) {
            *blend = 127.0f;
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
        ppvEnv->m_shapeTablePtr[pYmMegaBirthShpTail2->m_shapeIndex]
            ->m_animData);
    *(u16*)(color + 0x20) = frameIndex;

    frameEntry = &shapeAnim->m_frames[frameIndex];
    *(u16*)(color + 0x1c) =
        *(u16*)(color + 0x1c) + pYmMegaBirthShpTail2->m_frameStep;
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
 * EN Address: 0x8008B4C4
 * EN Size: 3704b
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail2* work, PYmMegaBirthShpTail2* param, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    u8* particleBytes = (u8*)particleData;
    float spread = (float)param->m_spread;
    float spreadRange = 2.0f * spread;

    memset(particleData, 0, 0x1b8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    if ((s32)param->m_spawnMode < 8 && (s32)param->m_spawnMode >= 0) {
        Vec baseDir;
        pppIVECTOR4 angles;
        pppFMATRIX rot;

        baseDir.x = param->m_baseDirection.x;
        baseDir.y = param->m_baseDirection.y;
        baseDir.z = param->m_baseDirection.z;
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / 180.0f);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / 180.0f);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / 180.0f);
        if ((param->m_spawnMode == 2) || (param->m_spawnMode == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, &baseDir, reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        particleData->m_matrix[1][0] *= param->m_spawnScale.x;
        particleData->m_matrix[1][1] *= param->m_spawnScale.y;
        particleData->m_matrix[1][2] *= param->m_spawnScale.z;
        pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]),
                     *reinterpret_cast<Vec*>(particleData->m_matrix[1]));
    }

    if ((s32)param->m_spawnMode < 6) {
        if ((s32)param->m_spawnMode >= 4) {
            goto mode_4_5;
        }
        goto scalar;
    }
    if ((s32)param->m_spawnMode >= 10) {
        goto scalar;
    }
    goto path;

scalar:
    {
        float speedRandRange = param->m_spawnRange;
        if (speedRandRange != 0.0f) {
            float scale = speedRandRange;

            switch (param->m_randType) {
            case 1:
                Math.RandF();
                scale = param->m_spawnRange * Math.RandF();
                break;
            case 2: {
                float a = Math.RandF();
                scale = a * (param->m_spawnRange * Math.RandF());
                break;
            }
            case 3: {
                float a = Math.RandF();
                scale = param->m_spawnRange - 0.7f * (a * (param->m_spawnRange * Math.RandF()));
                break;
            }
            case 4: {
                float a = Math.RandF();
                float b = Math.RandF();
                float c = Math.RandF();
                scale = Math.RandF() * (c * (a * (param->m_spawnRange * b)));
                break;
            }
            case 5: {
                float a = Math.RandF();
                float b = Math.RandF();
                scale = param->m_spawnRange - 0.5f * (Math.RandF() * (a * (param->m_spawnRange * b)));
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
        if (param->m_spawnRange == 0.0f) {
            goto done;
        }
        float speedRandHalf = 0.5f * param->m_spawnRange;

        switch (param->m_randType) {
        default:
            particleData->m_matrix[0][0] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_matrix[0][0] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = param->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 2: {
            float a0 = Math.RandF();
            particleData->m_matrix[0][0] = a0 * (param->m_spawnRange * Math.RandF());
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            particleData->m_matrix[0][1] = a1 * (param->m_spawnRange * Math.RandF());
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            particleData->m_matrix[0][2] = a2 * (param->m_spawnRange * Math.RandF());
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 3: {
            float a0 = Math.RandF();
            particleData->m_matrix[0][0] = param->m_spawnRange - 0.7f * (a0 * (param->m_spawnRange * Math.RandF()));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            particleData->m_matrix[0][1] = param->m_spawnRange - 0.7f * (a1 * (param->m_spawnRange * Math.RandF()));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            particleData->m_matrix[0][2] = param->m_spawnRange - 0.7f * (a2 * (param->m_spawnRange * Math.RandF()));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 4: {
            float a0 = Math.RandF();
            float b0 = Math.RandF();
            float c0 = Math.RandF();
            particleData->m_matrix[0][0] = Math.RandF() * (c0 * (a0 * (param->m_spawnRange * b0)));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            float b1 = Math.RandF();
            float c1 = Math.RandF();
            particleData->m_matrix[0][1] = Math.RandF() * (c1 * (a1 * (param->m_spawnRange * b1)));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            float b2 = Math.RandF();
            float c2 = Math.RandF();
            particleData->m_matrix[0][2] = Math.RandF() * (c2 * (a2 * (param->m_spawnRange * b2)));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        case 5: {
            float a0 = Math.RandF();
            float b0 = Math.RandF();
            particleData->m_matrix[0][0] = param->m_spawnRange - 0.5f * (Math.RandF() * (a0 * (param->m_spawnRange * b0)));
            particleData->m_matrix[0][0] -= speedRandHalf;
            float a1 = Math.RandF();
            float b1 = Math.RandF();
            particleData->m_matrix[0][1] = param->m_spawnRange - 0.5f * (Math.RandF() * (a1 * (param->m_spawnRange * b1)));
            particleData->m_matrix[0][1] -= speedRandHalf;
            float a2 = Math.RandF();
            float b2 = Math.RandF();
            particleData->m_matrix[0][2] = param->m_spawnRange - 0.5f * (Math.RandF() * (a2 * (param->m_spawnRange * b2)));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        }

        particleData->m_matrix[0][0] *= param->m_spawnScale.x;
        particleData->m_matrix[0][1] *= param->m_spawnScale.y;
        particleData->m_matrix[0][2] *= param->m_spawnScale.z;
        goto done;
    }

path:
    {
        float* pathBase = reinterpret_cast<float*>(pppPObject->m_drawMatrixPtr);

        if (param->m_pathIndex >= 0) {
            short* pathInfo = reinterpret_cast<short*>(ppvEnv->m_shapeGroupPtr + (param->m_pathIndex));

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
                    sampleT = static_cast<float>(1.0 - (a * b * Math.RandF()));
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
                    sampleT = static_cast<float>(1.0 - (a * (b * (c * (d * Math.RandF())))));
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
                particleData->m_matrix[0][0] = vx * param->m_spawnScale.x;
                particleData->m_matrix[0][1] = vy * param->m_spawnScale.y;
                particleData->m_matrix[0][2] = vz * param->m_spawnScale.z;

                if ((param->m_spawnMode == 8) || (param->m_spawnMode == 9)) {
                    Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[0]);
                    pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]), velocity);
                }
            }
        }
        goto done;
    }

done:
    if (param->m_fadeInFrames != 0) {
        *(float*)(particleBytes + 0x30) = (float)vColor->m_alpha;
        particleBytes[0x35] = param->m_fadeInFrames;
    }
    if (param->m_fadeOutFrames != 0) {
        particleBytes[0x36] = param->m_fadeOutFrames;
    }

    particleData->m_matrix[2][2] = param->m_speed;
    particleData->m_matrix[2][3] = param->m_tailSpeed;
    if (param->m_speedRandom != 0.0f) {
        particleData->m_matrix[2][2] +=
            (2.0f * param->m_speedRandom) * Math.RandF() - param->m_speedRandom;
    }

    if (param->m_life == 0) {
        *(u16*)(particleBytes + 0x22) = 0xFFFF;
    } else {
        *(u16*)(particleBytes + 0x22) = param->m_life;
    }
    particleBytes[0x34] = 0;

    switch ((s32)param->m_matrixMode) {
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
 * EN Address: 0x8008C33C
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    VYmMegaBirthShpTail2* work = reinterpret_cast<VYmMegaBirthShpTail2*>(
        param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);

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
 * PAL Address: 0x8008ca1c
 * PAL Size: 124b
 * EN Address: 0x8008C3B8
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    VYmMegaBirthShpTail2* work = reinterpret_cast<VYmMegaBirthShpTail2*>(
        param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);

    pppUnitMatrix(work->m_emitterMatrix);
    work->m_tailScaleDirection.z = 0.0f;
    work->m_tailScaleDirection.y = 0.0f;
    work->m_tailScaleDirection.x = 0.0f;
    work->m_particles = 0;
    work->m_wmats = 0;
    work->m_colors = 0;
    work->m_maxParticles = 0;
    work->m_emitTimer = 0;
    work->m_pathIndex = 0;
    work->m_emitTimer = 10000;
    pppUnitMatrix(g_matUnit);
}
