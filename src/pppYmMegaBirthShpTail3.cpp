#include "global.h"
#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"

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
    unsigned short m_emitTimer;
    unsigned short m_pathIndex;
    s16 m_colorStart[4];
    s16 m_colorEnd[4];
    s16 m_colorStartStep[4];
    s16 m_colorStartAcceleration[4];
    s16 m_colorEndStep[4];
    s16 m_colorEndAcceleration[4];
    u16 m_randomSeed;
    u8 m_pad82[2];
};

static pppFMATRIX g_matUnit;

static const char s_pppYmMegaBirthShpTail3_cpp[] = "pppYmMegaBirthShpTail3.cpp";

STATIC_ASSERT(sizeof(PYmMegaBirthShpTail3) == 0xBC);
STATIC_ASSERT(sizeof(VYmMegaBirthShpTail3) == 0x84);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_shapeIndex) == 0x4);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_maxParticles) == 0xe);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_life) == 0x14);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_spawnMode) == 0x18);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_baseDirection) == 0x20);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_tailDirection) == 0x30);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_speed) == 0x40);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_spawnScale) == 0x58);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_randType) == 0x68);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_pathIndex) == 0x6a);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_colorStart) == 0x78);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_colorEndAcceleration) == 0xa0);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_drawCount) == 0xb0);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_depth) == 0xb4);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail3, m_matrixMode) == 0xb9);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorStart) == 0x50);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorEnd) == 0x58);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorStartStep) == 0x60);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorStartAcceleration) == 0x68);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorEndStep) == 0x70);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_colorEndAcceleration) == 0x78);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail3, m_randomSeed) == 0x80);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail3DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail3DataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(sizeof(YmMegaBirthShpTail3DataOffsets) == 0xC);

static inline YmMegaBirthShpTail3DataOffsets* GetYmMegaBirthShpTail3DataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmMegaBirthShpTail3DataOffsets*>(ctrl->m_serializedDataOffsets);
}

void birth(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
void calc(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);


/*
 * --INFO--
 * PAL Address: 8008ca98
 * PAL Size: 2316b
 * EN Address: 0x8008C434
 * EN Size: 2316b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, PYmMegaBirthShpTail3* step, _pppCtrlTable* offsets)
{
    s32 startIndex;
    VYmMegaBirthShpTail3* work;
    VColor* colorWork;
    u8* particle;
    _PARTICLE_WMAT* wmats;
    _PARTICLE_COLOR* colors;
    tagOAN3_SHAPE* shape;
    pppShapeAnimData* shapeAnim;
    u32 i;
    float colorStepR;
    float segDz;
    float nextY;
    s32 count;
    float nextZ;
    s32 nextIndex;
    s32 lastIndex;
    float diffG;
    float segLen;
    u8 zEnable;
    _PARTICLE_DATA* particlesBase;
    _PARTICLE_WMAT* wmatsBase;
    float colorStepG;
    u32 particleShapeFrame;
    float baseX;
    float baseY;
    float diffR;
    float colorStepB;
    float alphaMul;
    float baseZ;
    float segCursor;
    float segRemain;
    float drawScale;
    float nextX;
    Vec* history;
    float diffA;
    float segDx;
    u32 workRand;
    u32 shapeFrameStep;
    float segDy;
    float colorStepA;
    float curX;
    float diffB;
    u32 shapeFrameCount;
    s8 hasRequiredMemory;
    float curY;
    float curZ;
    float scaleStep;
    float countMinusOne;
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

    work = (VYmMegaBirthShpTail3*)(object->m_workArea + GetYmMegaBirthShpTail3DataOffsets(offsets)->m_workOffset);
    colorWork = (VColor*)(object->m_workArea + GetYmMegaBirthShpTail3DataOffsets(offsets)->m_colorOffset);
    particlesBase = work->m_particles;
    colors = work->m_colors;
    wmatsBase = work->m_wmats;
    particle = (u8*)particlesBase;
    wmats = wmatsBase;

    if (particlesBase == 0) {
        hasRequiredMemory = false;
    } else if (wmatsBase == 0) {
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
            count = step->m_drawCount;
            countMinusOne = (float)(count - 1);
            alphaMul = (float)colorWork->m_alpha / 16384.0f;
            lastIndex = *(u8*)(particle + 0x37) - 1;
            colorStart.x = (float)(work->m_colorStart[0] >> 7);
            colorStart.y = (float)(work->m_colorStart[1] >> 7);
            colorStart.z = (float)(work->m_colorStart[2] >> 7);
            colorStart.w = (float)(work->m_colorStart[3] >> 7);
            colorEnd.x = (float)(work->m_colorEnd[0] >> 7);
            colorEnd.y = (float)(work->m_colorEnd[1] >> 7);
            colorEnd.z = (float)(work->m_colorEnd[2] >> 7);
            colorEnd.w = (float)(work->m_colorEnd[3] >> 7);
            colorStart.w *= alphaMul;
            colorEnd.w *= alphaMul;
            diffA = colorStart.w - colorEnd.w;
            startIndex = *(u8*)(particle + 0x38);
            segCursor = step->m_segmentLength;
            diffR = colorStart.x - colorEnd.x;
            diffG = colorStart.y - colorEnd.y;
            diffB = colorStart.z - colorEnd.z;
            if (countMinusOne != 0.0f) {
                colorStepR = diffR / countMinusOne;
                colorStepG = diffG / countMinusOne;
                colorStepB = diffB / countMinusOne;
                colorStepA = diffA / countMinusOne;
            }

            drawScale = step->m_drawScaleStart;
            history = (Vec*)(particle + 0x80);
            curX = history[startIndex].x;
            curY = history[startIndex].y;
            curZ = history[startIndex].z;
            nextIndex = startIndex + 1;
            scaleStep = (drawScale - step->m_drawScaleEnd) / countMinusOne;
            baseX = curX;
            baseY = curY;
            baseZ = curZ;
            if (startIndex == lastIndex) {
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

            particleShapeFrame = *(u16*)(particle + 0x1C);
            workRand = work->m_randomSeed;
            shapeFrameStep = shapeAnim->m_frames[0].m_duration;
            shapeFrameCount = shapeAnim->m_frameCount;

            for (count = step->m_drawCount; count > 0; count--) {
                if ((0.0f != ((Vec*)(particle + 0x80))[nextIndex].x) ||
                    (0.0f != ((Vec*)(particle + 0x80))[nextIndex].y) ||
                    (0.0f != ((Vec*)(particle + 0x80))[nextIndex].z)) {
                    workRand = (workRand * 0x80d + 7) & 0xFFFF;
                    shape = pppShapeFrame(shapeAnim, ((particleShapeFrame + workRand) / shapeFrameStep) % shapeFrameCount);

                    pppUnitMatrix(drawMtx);
                    drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                    drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                    drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;

                    if (step->m_rotationEnabled != 0) {
                        pppFMATRIX rotMtx;
                        PSMTXRotRad(rotMtx.value, 'z', 0.017453292f * (float)*(u16*)(particle + count * sizeof(u16) + 0x40));
                        pppMulMatrix(drawMtx, rotMtx, drawMtx);
                    }

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
                    if (amb.a > 0x7F) {
                        amb.a = 0x7F;
                    }
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
                        float t = segCursor / segLen;
                        curX = segDx * t;
                        curY = segDy * t;
                        curZ = segDz * t;
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
        *(u16*)(particle + 0x1C) += step->m_frameStep;
        particle += 0x1F8;
    }
}

/*
 * --INFO--
 * PAL Address: 8008d3a4
 * PAL Size: 1620b
 * EN Address: 0x8008CD40
 * EN Size: 1620b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, PYmMegaBirthShpTail3* param, _pppCtrlTable* offsets)
{
    s8 hasRequiredMemory;
    u32 i;
    int colorOffset;
    int spawnCount;
    _PARTICLE_COLOR* particleColor;
    _PARTICLE_WMAT* worldMat;
    u8* particleData;

    YmMegaBirthShpTail3DataOffsets* serializedOffsets = GetYmMegaBirthShpTail3DataOffsets(offsets);
    colorOffset = serializedOffsets->m_colorOffset;
    VYmMegaBirthShpTail3* const work =
        (VYmMegaBirthShpTail3*)(object->m_workArea + serializedOffsets->m_workOffset);
    VColor* const colorWork = (VColor*)(object->m_workArea + colorOffset);

    if (work->m_particles == 0) {
        work->m_maxParticles = param->m_maxParticles;
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

        work->m_tailScaleDirection = param->m_tailDirection;
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
        work->m_colorStartStep[0] += work->m_colorStartAcceleration[0];
        work->m_colorStart[0] += work->m_colorStartStep[0];

        work->m_colorStartStep[1] += work->m_colorStartAcceleration[1];
        work->m_colorStart[1] += work->m_colorStartStep[1];

        work->m_colorStartStep[2] += work->m_colorStartAcceleration[2];
        work->m_colorStart[2] += work->m_colorStartStep[2];

        work->m_colorStartStep[3] += work->m_colorStartAcceleration[3];
        work->m_colorStart[3] += work->m_colorStartStep[3];

        work->m_colorEndStep[0] += work->m_colorEndAcceleration[0];
        work->m_colorEnd[0] += work->m_colorEndStep[0];

        work->m_colorEndStep[1] += work->m_colorEndAcceleration[1];
        work->m_colorEnd[1] += work->m_colorEndStep[1];

        work->m_colorEndStep[2] += work->m_colorEndAcceleration[2];
        work->m_colorEnd[2] += work->m_colorEndStep[2];

        work->m_colorEndStep[3] += work->m_colorEndAcceleration[3];
        work->m_colorEnd[3] += work->m_colorEndStep[3];

        if (object->m_graphId == param->m_graphId) {
            work->m_colorStart[0] += param->m_colorStart[0];
            work->m_colorStart[1] += param->m_colorStart[1];
            work->m_colorStart[2] += param->m_colorStart[2];
            work->m_colorStart[3] += param->m_colorStart[3];

            work->m_colorStartStep[0] += param->m_colorStartStep[0];
            work->m_colorStartStep[1] += param->m_colorStartStep[1];
            work->m_colorStartStep[2] += param->m_colorStartStep[2];
            work->m_colorStartStep[3] += param->m_colorStartStep[3];

            work->m_colorStartAcceleration[0] += param->m_colorStartAcceleration[0];
            work->m_colorStartAcceleration[1] += param->m_colorStartAcceleration[1];
            work->m_colorStartAcceleration[2] += param->m_colorStartAcceleration[2];
            work->m_colorStartAcceleration[3] += param->m_colorStartAcceleration[3];

            work->m_colorEnd[0] += param->m_colorEnd[0];
            work->m_colorEnd[1] += param->m_colorEnd[1];
            work->m_colorEnd[2] += param->m_colorEnd[2];
            work->m_colorEnd[3] += param->m_colorEnd[3];

            work->m_colorEndStep[0] += param->m_colorEndStep[0];
            work->m_colorEndStep[1] += param->m_colorEndStep[1];
            work->m_colorEndStep[2] += param->m_colorEndStep[2];
            work->m_colorEndStep[3] += param->m_colorEndStep[3];

            work->m_colorEndAcceleration[0] += param->m_colorEndAcceleration[0];
            work->m_colorEndAcceleration[1] += param->m_colorEndAcceleration[1];
            work->m_colorEndAcceleration[2] += param->m_colorEndAcceleration[2];
            work->m_colorEndAcceleration[3] += param->m_colorEndAcceleration[3];
        }

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

        if ((ppvUserStopPartF == 0) && (param->m_shapeIndex != 0xffff)) {
            work->m_emitTimer = work->m_emitTimer + 1;
            for (; i < work->m_maxParticles; i++) {
                if (*(u16*)(particleData + 0x22) != 0) {
                    calc((_pppPObject*)object, work, param, (_PARTICLE_DATA*)particleData, colorWork, particleColor);
                } else {
                    if ((param->m_emitInterval <= work->m_emitTimer) && (spawnCount < param->m_emitCount)) {
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
                work->m_emitTimer = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 8008d9f8
 * PAL Size: 720b
 * EN Address: 0x8008D394
 * EN Size: 720b
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
          PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    int alpha = vColor->m_color.rgba[3];
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

        alpha = vColor->m_color.rgba[3] + (int)particleColor->m_color[3];
        if (alpha > 0xff) {
            alpha = 0xff;
        }
    }

    *velocityScale = *velocityScale + pYmMegaBirthShpTail3->m_speedStep;
    *tailScale = *tailScale + pYmMegaBirthShpTail3->m_tailSpeedStep;

    Vec scaled;
    pppScaleVectorXYZ(scaled, *(Vec*)(particleBytes + 0x10), *velocityScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail3->m_tailScaleDirection, *tailScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    if (pYmMegaBirthShpTail3->m_life != 0) {
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
        unsigned char fadeInFrames = pYmMegaBirthShpTail3->m_fadeOutFrames;
        *blend = *blend +
            (float)alpha / (float)fadeInFrames;
        if (*blend > 127.0f) {
            *blend = 127.0f;
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
 * EN Address: 0x8008D664
 * EN Size: 3704b
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
           PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat,
           _PARTICLE_COLOR* particleColor)
{
    u8* particleBytes = (u8*)particleData;
    float spread = (float)pYmMegaBirthShpTail3->m_spread;
    float spreadRange = 2.0f * spread;

    memset(particleData, 0, 0x1f8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    switch (pYmMegaBirthShpTail3->m_spawnMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        Vec baseDir;
        pppIVECTOR4 angles;
        pppFMATRIX rot;

        baseDir.x = pYmMegaBirthShpTail3->m_baseDirection.x;
        baseDir.y = pYmMegaBirthShpTail3->m_baseDirection.y;
        baseDir.z = pYmMegaBirthShpTail3->m_baseDirection.z;
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / 180.0f);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / 180.0f);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / 180.0f);
        if ((pYmMegaBirthShpTail3->m_spawnMode == 2) || (pYmMegaBirthShpTail3->m_spawnMode == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, &baseDir, reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->x *= pYmMegaBirthShpTail3->m_spawnScale.x;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->y *= pYmMegaBirthShpTail3->m_spawnScale.y;
        reinterpret_cast<Vec*>(particleData->m_matrix[1])->z *= pYmMegaBirthShpTail3->m_spawnScale.z;
        pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]),
                     *reinterpret_cast<Vec*>(particleData->m_matrix[1]));
        break;
    }
    }

    switch (pYmMegaBirthShpTail3->m_spawnMode) {
    default:
    {
        if (0.0f != pYmMegaBirthShpTail3->m_spawnRange) {
            float scale = pYmMegaBirthShpTail3->m_spawnRange;

            switch (pYmMegaBirthShpTail3->m_randType) {
            case 1:
                Math.RandF();
                scale = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
                break;
            case 2:
            {
                float rand1 = Math.RandF();
                scale = (pYmMegaBirthShpTail3->m_spawnRange * Math.RandF()) * rand1;
                break;
            }
            case 3:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                scale = pYmMegaBirthShpTail3->m_spawnRange - 0.7f * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1);
                break;
            }
            case 4:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
                break;
            }
            case 5:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = pYmMegaBirthShpTail3->m_spawnRange - 0.5f * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
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
        if (0.0f == pYmMegaBirthShpTail3->m_spawnRange) {
            break;
        }
        float speedRandHalf = 0.5f * pYmMegaBirthShpTail3->m_spawnRange;

        {
        float rand1;
        float rand2;
        float rand3;
        switch (pYmMegaBirthShpTail3->m_randType) {
        default:
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][0] -= speedRandHalf;
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][1] -= speedRandHalf;
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_spawnRange * Math.RandF();
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 2:
            rand1 = Math.RandF();
            particleData->m_matrix[0][0] = (pYmMegaBirthShpTail3->m_spawnRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            particleData->m_matrix[0][1] = (pYmMegaBirthShpTail3->m_spawnRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            particleData->m_matrix[0][2] = (pYmMegaBirthShpTail3->m_spawnRange * Math.RandF()) * rand1;
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 3:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_spawnRange - 0.7f * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1);
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_spawnRange - 0.7f * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1);
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_spawnRange - 0.7f * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1);
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 4:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][0] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][1] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][2] = Math.RandF() * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        case 5:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][0] = pYmMegaBirthShpTail3->m_spawnRange - 0.5f * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][0] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][1] = pYmMegaBirthShpTail3->m_spawnRange - 0.5f * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][1] -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            particleData->m_matrix[0][2] = pYmMegaBirthShpTail3->m_spawnRange - 0.5f * (rand3 * ((pYmMegaBirthShpTail3->m_spawnRange * rand2) * rand1));
            particleData->m_matrix[0][2] -= speedRandHalf;
            break;
        }
        }

        particleData->m_matrix[0][0] *= pYmMegaBirthShpTail3->m_spawnScale.x;
        particleData->m_matrix[0][1] *= pYmMegaBirthShpTail3->m_spawnScale.y;
        particleData->m_matrix[0][2] *= pYmMegaBirthShpTail3->m_spawnScale.z;
        break;
    }

    case 6:
    case 7:
    case 8:
    case 9:
    {
        Vec* pathBase = pppPObject->m_drawMatrixPtr;

        if (pYmMegaBirthShpTail3->m_pathIndex >= 0) {
            pppShapeGroupRaw* pathInfo = &ppvEnv->m_shapeGroupPtr[pYmMegaBirthShpTail3->m_pathIndex];

            if (pathBase == 0) {
                pathBase = ppvEnv->m_mapMeshPtr[pathInfo->m_meshIndex]->m_vertices;
            }

            {
                float vx;
                float vy;
                float vz;
                float sampleT;

                switch (pYmMegaBirthShpTail3->m_randType) {
                default:
                {
                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (s16)pathInfo->m_vertexCount) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    u16 sampleIndex = vYmMegaBirthShpTail3->m_pathIndex;
                    u16* indices = pathInfo->m_vertexIndices;
                    vYmMegaBirthShpTail3->m_pathIndex = sampleIndex + 1;

                    Vec* pathVec = &pathBase[indices[sampleIndex]];
                    vx = pathVec->x;
                    vy = pathVec->y;
                    vz = pathVec->z;
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

                {
                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (s16)pathInfo->m_vertexCount) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    int sampleIndex = (int)(sampleT * (float)pathInfo->m_vertexCount);
                    Vec* pathVec = &pathBase[pathInfo->m_vertexIndices[sampleIndex]];
                    vx = pathVec->x;
                    vy = pathVec->y;
                    vz = pathVec->z;
                }
                path_store:

                particleData->m_matrix[0][0] = vx * pYmMegaBirthShpTail3->m_spawnScale.x;
                particleData->m_matrix[0][1] = vy * pYmMegaBirthShpTail3->m_spawnScale.y;
                particleData->m_matrix[0][2] = vz * pYmMegaBirthShpTail3->m_spawnScale.z;

                if ((pYmMegaBirthShpTail3->m_spawnMode == 8) || (pYmMegaBirthShpTail3->m_spawnMode == 9)) {
                    Vec velocity = *reinterpret_cast<Vec*>(particleData->m_matrix[0]);
                    pppNormalize(*reinterpret_cast<Vec*>(particleData->m_matrix[1]), velocity);
                }
            }
        }
        break;
    }

    }


    if (pYmMegaBirthShpTail3->m_fadeInFrames != 0) {
        *(float*)(particleBytes + 0x30) = (float)vColor->m_color.rgba[3];
        particleBytes[0x35] = pYmMegaBirthShpTail3->m_fadeInFrames;
    }
    if (pYmMegaBirthShpTail3->m_fadeOutFrames != 0) {
        particleBytes[0x36] = pYmMegaBirthShpTail3->m_fadeOutFrames;
    }

    particleData->m_matrix[2][2] = pYmMegaBirthShpTail3->m_speed;
    particleData->m_matrix[2][3] = pYmMegaBirthShpTail3->m_tailSpeed;
    if (pYmMegaBirthShpTail3->m_speedRandom != 0.0f) {
        float rand1 = Math.RandF();
        particleData->m_matrix[2][2] +=
            (2.0f * pYmMegaBirthShpTail3->m_speedRandom) * rand1 -
            pYmMegaBirthShpTail3->m_speedRandom;
    }

    if (pYmMegaBirthShpTail3->m_life == 0) {
        *(u16*)((u8*)particleData + 0x22) = 0xFFFF;
    } else {
        *(s16*)((u8*)particleData + 0x22) = pYmMegaBirthShpTail3->m_life;
    }
    particleBytes[0x34] = 0;

    switch (pYmMegaBirthShpTail3->m_matrixMode) {
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
 * EN Address: 0x8008E4DC
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, _pppCtrlTable* ctrlTable)
{
    int workOffset = GetYmMegaBirthShpTail3DataOffsets(ctrlTable)->m_workOffset;
    VYmMegaBirthShpTail3* work = reinterpret_cast<VYmMegaBirthShpTail3*>(object->m_workArea + workOffset);

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
 * EN Address: 0x8008E558
 * EN Size: 228b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, _pppCtrlTable* ctrlTable)
{
    VYmMegaBirthShpTail3* work = reinterpret_cast<VYmMegaBirthShpTail3*>(
        object->m_workArea + GetYmMegaBirthShpTail3DataOffsets(ctrlTable)->m_workOffset);

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
    work->m_randomSeed = rand();
    pppUnitMatrix(g_matUnit);
    memset(work->m_colorStart, 0, sizeof(work->m_colorStart));
    memset(work->m_colorEnd, 0, sizeof(work->m_colorEnd));
    memset(work->m_colorStartStep, 0, sizeof(work->m_colorStartStep));
    memset(work->m_colorStartAcceleration, 0, sizeof(work->m_colorStartAcceleration));
    memset(work->m_colorEndStep, 0, sizeof(work->m_colorEndStep));
    memset(work->m_colorEndAcceleration, 0, sizeof(work->m_colorEndAcceleration));
}
