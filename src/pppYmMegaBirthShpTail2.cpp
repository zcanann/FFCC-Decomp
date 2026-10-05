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

inline void U8ToF32(pppFVECTOR4* dest, u8* src)
{
    dest->x = src[0];
    dest->y = src[1];
    dest->z = src[2];
    dest->w = src[3];
}

static void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
static void calc(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);


/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 * EN Address: 0x8008A660
 * EN Size: 1840b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* step, _pppCtrlTable* offsets)
{
    VYmMegaBirthShpTail2* work;
    VColor* colorWork;
    u8* particle;
    _PARTICLE_WMAT* wmats;
    _PARTICLE_COLOR* colors;
    tagOAN3_SHAPE* shape;
    pppShapeAnimData* shapeAnim;
    u32 i;
    s32 count;
    s32 startIndex;
    float segLen;
    s32 nextIndex;
    s32 lastIndex;
    float baseX;
    float baseY;
    _PARTICLE_DATA* particlesBase;
    _PARTICLE_WMAT* wmatsBase;
    _PARTICLE_COLOR* colorsBase;
    float colorStepG;
    float baseZ;
    float colorStepB;
    Vec* history;
    float diffR;
    float segCursor;
    float segRemain;
    float drawScale;
    float diffG;
    s8 hasRequiredMemory;
    float nextZ;
    float nextY;
    float curY;
    float curZ;
    float countMinusOne;
    float colorStepR;
    float nextX;
    float colorStepA;
    float segDx;
    float alphaMul;
    u8 zEnable;
    float segDy;
    float diffB;
    float diffA;
    float segDz;
    float curX;
    float scaleStep;
    pppFVECTOR4 colorStart;
    pppFVECTOR4 colorEnd;
    pppFMATRIX drawMtx;
    Vec zeroVec;
    Vec seg;
    pppFVECTOR4 camPos;
    pppFVECTOR4 pos;
    pppFVECTOR4 mngPos;
    Vec zeroVecB;
    Vec segB;
    GXColor amb;

    work = (VYmMegaBirthShpTail2*)(object->m_workArea + GetYmMegaBirthShpTail2DataOffsets(offsets)->m_workOffset);
    colorWork = (VColor*)(object->m_workArea + GetYmMegaBirthShpTail2DataOffsets(offsets)->m_colorOffset);
    particlesBase = work->m_particles;
    wmatsBase = work->m_wmats;
    colorsBase = work->m_colors;
    particle = (u8*)particlesBase;
    wmats = wmatsBase;
    colors = colorsBase;

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

    shapeAnim = static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[step->m_shapeIndex]->m_animData);
    if (step->m_disableDepthTest != 0) {
        zEnable = 0;
    } else {
        zEnable = 1;
    }
    pppSetDrawEnv(0, &object->m_drawMatrix, step->m_depth, step->m_lightTarget, step->m_fogIndex,
                  step->m_blendMode, 0, zEnable, 1, 0);
    pppSetBlendMode(step->m_blendMode);

    for (i = 0; i < work->m_maxParticles; i++) {
        if (*(u16*)(particle + 0x22) != 0) {
            segCursor = 0.0f;
            count = step->m_drawCount;
            countMinusOne = (float)(count - 1);
            alphaMul = (float)colorWork->m_alpha / 16384.0f;
            U8ToF32(&colorStart, (u8*)&step->m_colorStart);
            U8ToF32(&colorEnd, (u8*)&step->m_colorEnd);
            colorStart.w *= alphaMul;
            colorEnd.w *= alphaMul;
            diffA = colorStart.w - colorEnd.w;
            diffR = colorStart.x - colorEnd.x;
            diffG = colorStart.y - colorEnd.y;
            diffB = colorStart.z - colorEnd.z;
            lastIndex = *(u8*)(particle + 0x37) - 1;
            nextIndex = *(u8*)(particle + 0x38);
            shape = reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) +
                                                     shapeAnim->m_frames[*(u16*)(particle + 0x20)].m_shapeOffset);
            if (countMinusOne != segCursor) {
                colorStepR = diffR / countMinusOne;
                colorStepG = diffG / countMinusOne;
                colorStepB = diffB / countMinusOne;
                colorStepA = diffA / countMinusOne;
            } else {
                colorStepR = 0.5f;
                colorStepG = colorStepR;
                colorStepB = colorStepR;
                colorStepA = colorStepR;
            }

            pppUnitMatrix(drawMtx);
            drawScale = step->m_drawScaleStart;
            scaleStep = (drawScale - step->m_drawScaleEnd) / countMinusOne;

            history = (Vec*)(particle + 0x40);
            startIndex = *(u8*)(particle + 0x38);
            curX = history[nextIndex].x;
            curY = history[nextIndex].y;
            curZ = history[nextIndex].z;
            baseX = curX;
            baseY = curY;
            baseZ = curZ;
            if (nextIndex++ == lastIndex) {
                nextIndex = 0;
            }
            nextX = history[nextIndex].x;
            nextY = history[nextIndex].y;
            nextZ = history[nextIndex].z;
            segDx = nextX - curX;
            segDy = nextY - curY;
            segDz = nextZ - curZ;
            zeroVec.z = 0.0f;
            zeroVec.y = 0.0f;
            zeroVec.x = 0.0f;
            seg.x = segDx;
            seg.y = segDy;
            seg.z = segDz;
            segLen = PSVECDistance(&zeroVec, &seg);
            segRemain = segLen;

            if (step->m_drawHead == 0) {
                goto update_step;
            }

            for (count = step->m_drawCount; count > 0; count--) {
                if ((0.0f != ((Vec*)(particle + 0x40))[nextIndex].x) ||
                    (0.0f != ((Vec*)(particle + 0x40))[nextIndex].y) ||
                    (0.0f != ((Vec*)(particle + 0x40))[nextIndex].z)) {
                    pppUnitMatrix(drawMtx);
                    drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                    drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                    drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;
                    pos.x = curX;
                    pos.y = curY;
                    pos.z = curZ;

                    if (step->m_matrixMode == 0) {
                        PSMTXMultVec(ppvWorldMatrix, (Vec*)&pos, (Vec*)&camPos);
                    } else if (step->m_matrixMode == 1) {
                        mngPos.x = ppvMng->m_matrix.value[0][3];
                        mngPos.y = ppvMng->m_matrix.value[1][3];
                        mngPos.z = ppvMng->m_matrix.value[2][3];
                        PSVECAdd((Vec*)&mngPos, (Vec*)&pos, (Vec*)&pos);
                        PSMTXMultVec(ppvCameraMatrix, (Vec*)&pos, (Vec*)&camPos);
                    }

                    drawMtx.value[0][3] = camPos.x;
                    drawMtx.value[1][3] = camPos.y;
                    drawMtx.value[2][3] = camPos.z;
                    GXLoadPosMtxImm(drawMtx.value, 0);

                    amb.r = (u8)colorStart.x;
                    amb.g = (u8)colorStart.y;
                    amb.b = (u8)colorStart.z;
                    amb.a = (u8)(colorStart.w * (0.00787f * (127.0f - *(float*)(particle + 0x30))));
                    GXSetChanAmbColor(GX_COLOR0A0, amb);
                    pppDrawShp(shape, ppvEnv->m_materialSetPtr, step->m_blendMode);

                update_step:
                    colorStart.x -= colorStepR;
                    colorStart.y -= colorStepG;
                    colorStart.z -= colorStepB;
                    colorStart.w -= colorStepA;
                    drawScale -= scaleStep;
                    if (step->m_segmentLength <= 0.0f) {
                        goto next_particle;
                    }

                advance_segment:
                    if (segRemain >= step->m_segmentLength) {
                        curX = (segDx * segCursor) / segLen;
                        curY = (segDy * segCursor) / segLen;
                        curZ = (segDz * segCursor) / segLen;
                        curX += baseX;
                        curY += baseY;
                        curZ += baseZ;
                        segCursor += step->m_segmentLength;
                        segRemain -= step->m_segmentLength;
                        continue;
                    }

                    if (nextIndex++ == lastIndex) {
                        nextIndex = 0;
                    }
                    if (nextIndex == startIndex) {
                        goto next_particle;
                    }

                    baseX = nextX;
                    baseY = nextY;
                    baseZ = nextZ;
                    segCursor -= segLen;
                    segDy = (nextY = history[nextIndex].y) - baseY;
                    segDz = (nextZ = history[nextIndex].z) - baseZ;
                    segDx = (nextX = history[nextIndex].x) - baseX;
                    zeroVecB.z = 0.0f;
                    zeroVecB.y = 0.0f;
                    zeroVecB.x = 0.0f;
                    segB.x = segDx;
                    segB.y = segDy;
                    segB.z = segDz;
                    segLen = PSVECDistance(&zeroVecB, &segB);
                    segRemain += segLen;
                    goto advance_segment;
                }
            }
        }
    next_particle:
        if (wmats != 0) {
            wmats = wmats + 1;
        }
        if (colors != 0) {
            colors = colors + 1;
        }
        particle += 0x1B8;
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
static void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
          PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    s32 alpha = vColor->m_color.rgba[3];
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
                 (Vec*)(color + historyIndex * sizeof(Vec) + 0x40));

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
static void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
           PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat,
           _PARTICLE_COLOR* particleColor)
{
    u8* particleBytes = (u8*)particleData;
    float vx;
    float vy;
    float vz;
    float spread = (float)pYmMegaBirthShpTail2->m_spread;
    float spreadRange = 2.0f * spread;

    memset(particleData, 0, 0x1b8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    switch (pYmMegaBirthShpTail2->m_spawnMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        pppFVECTOR4 baseDir;
        pppIVECTOR4 angles;
        pppFMATRIX rot;

        baseDir.x = pYmMegaBirthShpTail2->m_baseDirection.x;
        baseDir.y = pYmMegaBirthShpTail2->m_baseDirection.y;
        baseDir.z = pYmMegaBirthShpTail2->m_baseDirection.z;
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / 180.0f);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / 180.0f);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / 180.0f);
        if ((pYmMegaBirthShpTail2->m_spawnMode == 2) || (pYmMegaBirthShpTail2->m_spawnMode == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, (Vec*)&baseDir, reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->x *= pYmMegaBirthShpTail2->m_spawnScale.x;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->y *= pYmMegaBirthShpTail2->m_spawnScale.y;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->z *= pYmMegaBirthShpTail2->m_spawnScale.z;
        pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]),
                     *reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        break;
    }
    }

    switch (pYmMegaBirthShpTail2->m_spawnMode) {
    default:
    {
        if (0.0f != pYmMegaBirthShpTail2->m_spawnRange) {
            float scale;

            switch (pYmMegaBirthShpTail2->m_randType) {
            default:
                scale = pYmMegaBirthShpTail2->m_spawnRange;
                break;
            case 1:
                Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
                break;
            case 2:
            {
                scale = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
                break;
            }
            case 3:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (scale * rand1);
                break;
            }
            case 4:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                float rand4 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = rand4 * (rand3 * (scale * rand1));
                break;
            }
            case 5:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (scale * rand1));
                break;
            }
            }

            Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[1]);
            pppScaleVectorXYZ(*reinterpret_cast<Vec*>(particleData->m_matrix[0]), velocity, scale);
        }
        break;
    }

    case 4:
    case 5:
    {
        if (0.0f == pYmMegaBirthShpTail2->m_spawnRange) {
            break;
        }
        float speedRandHalf = 0.5f * pYmMegaBirthShpTail2->m_spawnRange;

        {
        float rand1;
        float rand2;
        float rand3;
        float rand4;
        switch (pYmMegaBirthShpTail2->m_randType) {
        default:
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 2:
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 3:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 4:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][0] = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][1] = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][2] = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 5:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        }

        particleData->m_matrix[0][0] *= pYmMegaBirthShpTail2->m_spawnScale.x;
        particleData->m_matrix[0][1] *= pYmMegaBirthShpTail2->m_spawnScale.y;
        particleData->m_matrix[0][2] *= pYmMegaBirthShpTail2->m_spawnScale.z;
        break;
    }

    case 6:
    case 7:
    case 8:
    case 9:
    {
        Vec* pathBase = pppPObject->m_drawMatrixPtr;

        if (pYmMegaBirthShpTail2->m_pathIndex >= 0) {
            pppShapeGroupRaw* pathInfo = &ppvEnv->m_shapeGroupPtr[pYmMegaBirthShpTail2->m_pathIndex];

            if (pathBase == 0) {
                pathBase = ppvEnv->m_mapMeshPtr[pathInfo->m_meshIndex]->m_vertices;
            }

            {
                float sampleT;

                switch (pYmMegaBirthShpTail2->m_randType) {
                default:
                    if ((int)vYmMegaBirthShpTail2->m_pathIndex >= pathInfo->m_vertexCount) {
                        vYmMegaBirthShpTail2->m_pathIndex = 0;
                    }

                    if (pathBase != 0) {
                        u16 sampleIndex = vYmMegaBirthShpTail2->m_pathIndex;
                        u16* indices = pathInfo->m_vertexIndices;
                        vYmMegaBirthShpTail2->m_pathIndex = sampleIndex + 1;

                        Vec* pathVec = &pathBase[indices[sampleIndex]];
                        vx = pathVec->x;
                        vy = pathVec->y;
                        vz = pathVec->z;
                    }
                    goto path_store;
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
                    sampleT = static_cast<float>(1.0 - (r2 * (r1 * r0)));
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
                    sampleT = static_cast<float>(1.0 - (r4 * (r3 * (r2 * (r1 * r0)))));
                    break;
                }
                }

                if ((int)vYmMegaBirthShpTail2->m_pathIndex >= pathInfo->m_vertexCount) {
                    vYmMegaBirthShpTail2->m_pathIndex = 0;
                }

                if (pathBase != 0) {
                    int sampleIndex = (int)(sampleT * (float)pathInfo->m_vertexCount);
                    Vec* pathVec = &pathBase[pathInfo->m_vertexIndices[sampleIndex]];
                    vx = pathVec->x;
                    vy = pathVec->y;
                    vz = pathVec->z;
                }
                path_store:

                particleData->m_matrix[0][0] = vx * pYmMegaBirthShpTail2->m_spawnScale.x;
                particleData->m_matrix[0][1] = vy * pYmMegaBirthShpTail2->m_spawnScale.y;
                particleData->m_matrix[0][2] = vz * pYmMegaBirthShpTail2->m_spawnScale.z;

                if ((pYmMegaBirthShpTail2->m_spawnMode == 8) || (pYmMegaBirthShpTail2->m_spawnMode == 9)) {
                    Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[0]);
                    pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]), velocity);
                }
            }
        }
        break;
    }

    }


    if (pYmMegaBirthShpTail2->m_fadeInFrames != 0) {
        *(float*)(particleBytes + 0x30) = (float)vColor->m_color.rgba[3];
        particleBytes[0x35] = pYmMegaBirthShpTail2->m_fadeInFrames;
    }
    if (pYmMegaBirthShpTail2->m_fadeOutFrames != 0) {
        particleBytes[0x36] = pYmMegaBirthShpTail2->m_fadeOutFrames;
    }

    particleData->m_matrix[2][2] = pYmMegaBirthShpTail2->m_speed;
    particleData->m_matrix[2][3] = pYmMegaBirthShpTail2->m_tailSpeed;
    if (pYmMegaBirthShpTail2->m_speedRandom != 0.0f) {
        float rand1 = Math.RandF();
        particleData->m_matrix[2][2] +=
            (2.0f * pYmMegaBirthShpTail2->m_speedRandom) * rand1 -
            pYmMegaBirthShpTail2->m_speedRandom;
    }

    if (pYmMegaBirthShpTail2->m_life == 0) {
        *(u16*)((u8*)particleData + 0x22) = 0xFFFF;
    } else {
        *(s16*)((u8*)particleData + 0x22) = pYmMegaBirthShpTail2->m_life;
    }
    particleBytes[0x34] = 0;

    switch (pYmMegaBirthShpTail2->m_matrixMode) {
    case 0:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail2->m_emitterMatrix);
        break;
    case 1:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail2->m_emitterMatrix);
        break;
    }

    *(u16*)(particleBytes + 0x3a) = 0;
    *(u16*)(particleBytes + 0x3c) = 0;
    *(u16*)(particleBytes + 0x3e) = 0;
    particleBytes[0x38] = 0;
    particleBytes[0x37] = 0x1f;

    pppFVECTOR4 zeroVec;
    zeroVec.z = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.x = 0.0f;
    Vec* history = (Vec*)(particleBytes + 0x40);
    for (int i = 0x1e; i >= 0; i--) {
        pppCopyVector(*history, *(Vec*)&zeroVec);
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
 * JP Address: 0x8008BE34
 * JP Size: 124b
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    VYmMegaBirthShpTail2* work = reinterpret_cast<VYmMegaBirthShpTail2*>(
        param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);

    pppUnitMatrix(work->m_emitterMatrix);
    work->m_tailScaleDirection.x = work->m_tailScaleDirection.y = work->m_tailScaleDirection.z = 0.0f;
    work->m_particles = 0;
    work->m_wmats = 0;
    work->m_colors = 0;
    work->m_maxParticles = 0;
    work->m_emitTimer = 0;
    work->m_pathIndex = 0;
    work->m_emitTimer = 10000;
    pppUnitMatrix(g_matUnit);
}
