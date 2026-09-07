#include "ffcc/pppYmBreath.h"
#include "global.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "dolphin/mtx.h"

#include <string.h>
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppBreathParticle.h"
#include "ffcc/pppShape.h"

static const float kYmBreathZero = 0.0f;
static const float kYmBreathDegToRad = 0.01745329238474369f;
static const float kYmBreathNegativeOne = -1.0f;
static const float kYmBreathFullTurnDegrees = 360.0f;
static const float kYmBreathHalfCircleDegrees = 180.0f;
static const float kYmBreathNegativeHalfCircleDegrees = -180.0f;
static const float kYmBreathSpreadScale = 2.0f;
static const double kYmBreathHalfChance = 0.5;

struct YmBreathParticleGroup {
    int active;
    signed char* particleIndices;
    signed char* particleStates;
    Vec position;
    Vec direction;
    float speed;
    float scale;
    Mtx matrix;
};

struct PARTICLE_DATA;

struct VYmBreath {
    Mtx m_matrix;
    PARTICLE_DATA* m_particleData;
    PARTICLE_WMAT* m_particleWmats;
    PARTICLE_COLOR* m_particleColors;
    YmBreathParticleGroup* m_groups;
    int m_particleCount;
    u16 m_emitFrameCounter;
    u16 _pad46;
    Vec m_direction;
    s16 m_groupCount;
    s16 m_slotCount;
    u8 m_flags;
    unsigned char _pad59[3];
};

struct PARTICLE_DATA {
    Vec m_position;
    Vec m_direction;
    unsigned char _pad18[0x08];
    s16 m_life;
    unsigned char _pad22[0x02];
    char m_fadeOutFrames;
    char m_fadeInFrames;
    unsigned char _pad26[0x02];
    float m_angle;
    float m_angleVelocity;
    float m_angleRandom;
    float m_rotationX;
    float m_rotationY;
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    float m_rotationAccelX;
    float m_rotationAccelY;
    float m_alpha;
    float m_scale;
    u8 m_age;
    u8 _pad55;
    s16 m_shapeFrame0;
    s16 m_shapeFrame1;
    s16 m_shapeFrame2;
    unsigned char _pad5C[0x04];
};

STATIC_ASSERT(sizeof(PARTICLE_DATA) == 0x60);
STATIC_ASSERT(offsetof(PARTICLE_DATA, m_life) == 0x20);
STATIC_ASSERT(offsetof(PARTICLE_DATA, m_shapeFrame0) == 0x56);
STATIC_ASSERT(sizeof(YmBreathParticleGroup) == 0x5C);
STATIC_ASSERT(sizeof(YmBreathDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(YmBreathDataOffsets, m_workOffset) == 0x0);
STATIC_ASSERT(offsetof(YmBreathDataOffsets, m_colorOffset) == 0x4);

void BirthParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*);
void UpdateParticle(VYmBreath*, PYmBreath*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*);
void UpdateAllParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*);

static const char s_pppYmBreath_cpp[] = "pppYmBreath.cpp";

static inline YmBreathDataOffsets* GetYmBreathDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmBreathDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline VYmBreath* GetYmBreathWork(pppYmBreath* ymBreath, s32 offset)
{
    return reinterpret_cast<VYmBreath*>(ymBreath->m_workArea + offset);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int IsDeadGroupBreath(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short groupIndex)
{
    YmBreathParticleGroup* group = &vYmBreath->m_groups[groupIndex];
    for (int slot = 0; slot < pYmBreath->m_slotCount; slot++) {
        if (group->particleIndices[slot] != -1 || group->particleStates[slot] != 1) {
            return false;
        }
    }
    return true;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int SearchIndex(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short& groupIndex, short& slotIndex, short particleIndex)
{
    YmBreathParticleGroup* groupTable = vYmBreath->m_groups;
    short g;
    short s;

    groupIndex = -1;
    slotIndex = -1;

    for (g = 0; g < pYmBreath->m_groupCount; g++) {
        for (s = 0; s < pYmBreath->m_slotCount; s++) {
            if ((int)particleIndex == (int)groupTable->particleIndices[s]) {
                groupIndex = g;
                slotIndex = s;
                return true;
            }
        }
        groupTable++;
    }

    return false;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int IsExistGroupParticle(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short groupIndex)
{
    YmBreathParticleGroup* group = &vYmBreath->m_groups[groupIndex];
    for (short slot = 0; slot < pYmBreath->m_slotCount; slot++) {
        if (group->particleIndices[slot] == -1 || group->particleStates[slot] != 1) {
            return false;
        }
    }
    return true;
}

/*
 * --INFO--
 * PAL Address: 0x800bfe78
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppDestructYmBreath(pppYmBreath* ymBreath, _pppCtrlTable* dataOffsets)
{
    YmBreathParticleGroup* group;
    VYmBreath* state =
        reinterpret_cast<VYmBreath*>(ymBreath->m_workArea + GetYmBreathDataOffsets(dataOffsets)->m_workOffset);

    if (state->m_particleData != NULL) {
        pppHeapUseRate((CMemory::CStage*)state->m_particleData);
        state->m_particleData = 0;
    }

    if (state->m_particleWmats != NULL) {
        pppHeapUseRate((CMemory::CStage*)state->m_particleWmats);
        state->m_particleWmats = 0;
    }

    if (state->m_particleColors != NULL) {
        pppHeapUseRate((CMemory::CStage*)state->m_particleColors);
        state->m_particleColors = 0;
    }

    group = state->m_groups;
    if (group != NULL) {
        int i;

        for (i = 0; i < state->m_groupCount; i++) {
            if (group->particleIndices != NULL) {
                pppHeapUseRate((CMemory::CStage*)group->particleIndices);
                group->particleIndices = 0;
            }

            if (group->particleStates != NULL) {
                pppHeapUseRate((CMemory::CStage*)group->particleStates);
                group->particleStates = 0;
            }

            group++;
        }

        pppHeapUseRate((CMemory::CStage*)state->m_groups);
        state->m_groups = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800bff70
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmBreath(_pppPObject* obj)
{
    (void)obj;
}

/*
 * --INFO--
 * PAL Address: 0x800bff74
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmBreath(pppYmBreath* ymBreath, _pppCtrlTable* dataOffsets)
{
    VYmBreath* state = GetYmBreathWork(ymBreath, GetYmBreathDataOffsets(dataOffsets)->m_workOffset);
    float zero;

    PSMTXIdentity(state->m_matrix);
    zero = kYmBreathZero;

    state->m_direction.z = zero;
    state->m_direction.y = zero;
    state->m_direction.x = zero;

    state->m_particleData = 0;
    state->m_particleWmats = 0;
    state->m_particleColors = 0;
    state->m_groups = 0;
    state->m_particleCount = 0;

    state->m_emitFrameCounter = 10000;
    state->m_groupCount = 0;
    state->m_slotCount = 0;
    state->m_flags = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800bffec
 * PAL Size: 1292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, _pppCtrlTable* offsets)
{
    PYmBreath* params = pYmBreath;
    int workOffset;
    int colorOffset;
    VYmBreath* work;
    VColor* color;
    PARTICLE_DATA* particle;
    PARTICLE_WMAT* matrixList;
    PARTICLE_COLOR* particleColor;
    YmBreathParticleGroup* groupData;
    int i;
    int groupCount;
    pppShapeSt* shape;
    int colorR;
    int colorG;
    int colorB;
    int colorA;
    _GXColor drawColor;
    _GXColor debugColor;
    Vec debugPos;
    Vec pos;
    Mtx tempMtx;
    Mtx sphereMtx;
    Mtx rotMtx;
    pppFMATRIX viewMtx;
    Mtx drawMtx;

    workOffset = GetYmBreathDataOffsets(offsets)->m_workOffset;
    colorOffset = GetYmBreathDataOffsets(offsets)->m_colorOffset;
    work = reinterpret_cast<VYmBreath*>(ymBreath->m_workArea + workOffset);
    color = reinterpret_cast<VColor*>(ymBreath->m_workArea + colorOffset);
    particle = work->m_particleData;
    matrixList = work->m_particleWmats;
    particleColor = work->m_particleColors;
    groupData = work->m_groups;
    groupCount = work->m_particleCount;

    if (params->m_shapeStepValue == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_resourceTables.m_shapeTablePtr[params->m_shapeStepValue];
    pppSetBlendMode(params->m_blendMode);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(
        0, 0, params->m_drawEnvScale, params->m_drawEnvColor1, params->m_drawEnvColor0,
        params->m_blendMode, 0, 1, 1, 0);

    colorR = color->m_red;
    colorG = color->m_green;
    colorB = color->m_blue;
    colorA = color->m_alpha;

    for (i = 0; i < groupCount; i++) {
        if (particle->m_life > 0) {
            int r;
            int g;
            int b;
            int a;

            PSMTXIdentity(drawMtx);
            drawMtx[0][0] = particle->m_rotationX * ppvMng->m_scale.x;
            drawMtx[1][1] = particle->m_rotationY * ppvMng->m_scale.y;
            drawMtx[2][2] = drawMtx[0][0];
            if (kYmBreathZero != particle->m_angle) {
                PSMTXRotRad(rotMtx, 'z', kYmBreathDegToRad * particle->m_angle);
                PSMTXConcat(drawMtx, rotMtx, drawMtx);
            }

            pppUnitMatrix(viewMtx);
            PSMTXConcat(matrixList->m_matrix, ymBreath->m_localMatrix.value, viewMtx.value);
            PSMTXConcat(ppvCameraMatrix, viewMtx.value, viewMtx.value);
            PSMTXMultVec(viewMtx.value, &particle->m_position, &pos);
            drawMtx[0][3] = pos.x;
            drawMtx[1][3] = pos.y;
            drawMtx[2][3] = pos.z;
            GXLoadPosMtxImm(drawMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((float)(int)colorA - particle->m_alpha);
            if (particleColor != 0) {
                r += (int)particleColor->m_color[0];
                g += (int)particleColor->m_color[1];
                b += (int)particleColor->m_color[2];
                a += (int)particleColor->m_color[3];
            }

            if (r < 0) {
                r = 0;
            } else if (r > 0xFF) {
                r = 0xFF;
            }
            if (g < 0) {
                g = 0;
            } else if (g > 0xFF) {
                g = 0xFF;
            }
            if (b < 0) {
                b = 0;
            } else if (b > 0xFF) {
                b = 0xFF;
            }
            if (a < 0) {
                a = 0;
            } else if (a > 0x7F) {
                a = 0x7F;
            }

            drawColor.r = (unsigned char)r;
            drawColor.g = (unsigned char)g;
            drawColor.b = (unsigned char)b;
            drawColor.a = (unsigned char)a;
            GXSetChanAmbColor(GX_COLOR0A0, drawColor);
            pppDrawShp(static_cast<long*>(shape->m_animData), particle->m_shapeFrame2, ppvEnv->m_materialSetPtr,
                       params->m_blendMode);
        }

        if (matrixList != 0) {
            matrixList++;
        }
        if (particleColor != 0) {
            particleColor++;
        }
        particle++;
    }

    if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
        YmBreathParticleGroup* debugGroupData = groupData;
        for (i = 0; i < (int)params->m_groupCount; i++, debugGroupData++) {
            if (debugGroupData->active == 1) {
                int firstParticle;
                int j;
                float groupScale;

                switch (i) {
                case 0:
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                    break;
                case 1:
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0xFF;
                    debugColor.a = 0xFF;
                    break;
                case 2:
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                    break;
                case 3:
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                    break;
                default:
                    debugColor.r = 0x00;
                    debugColor.g = 0x60;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                    break;
                }

                firstParticle = -1;
                groupScale = debugGroupData->scale;
                for (j = 0; j < (int)params->m_slotCount; j++) {
                    if (debugGroupData->particleStates[j] != -1) {
                        firstParticle = debugGroupData->particleIndices[j];
                        break;
                    }
                }

                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = groupScale;
                sphereMtx[1][1] = groupScale;
                sphereMtx[2][2] = groupScale;

                PSMTXConcat(work->m_particleWmats[firstParticle].m_matrix, ymBreath->m_localMatrix.value, tempMtx);
                PSMTXConcat(ppvCameraMatrix, tempMtx, tempMtx);
                PSMTXMultVec(tempMtx, &debugGroupData->position, &debugPos);
                sphereMtx[0][3] = debugPos.x;
                sphereMtx[1][3] = debugPos.y;
                sphereMtx[2][3] = debugPos.z;
                Graphic.DrawSphere(sphereMtx, debugColor);
            }
        }

        pppSetBlendMode(1);
        pppSetBlendMode(0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_BLEND);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c04f8
 * PAL Size: 1264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, _pppCtrlTable* offsets)
{
    PYmBreath* params = pYmBreath;
    YmBreathParticleGroup* groupData;
    _pppMngSt* mngSt;
    YmBreathDataOffsets* dataOffsets;
    VColor* color;
    VYmBreath* work;
    PARTICLE_WMAT* particleWMat;
    PARTICLE_WMAT* particleMtx;
    int i;
    int groupIndex;
    int firstParticle;
    int particleSlot;
    int slotCount;
    float scaledOwner;
    Mtx scaleMtx;
    Mtx worldMtx;
    pppFMATRIX rotMtx;
    Vec hitVector;
    Vec dir;
    Vec origin;
    Vec target;

    if (ppvUserStopPartF != 0) {
        return;
    }

    dataOffsets = GetYmBreathDataOffsets(offsets);
    mngSt = ppvMng;
    int colorOffset = dataOffsets->m_colorOffset;
    work = reinterpret_cast<VYmBreath*>(ymBreath->m_workArea + dataOffsets->m_workOffset);
    color = (VColor*)(ymBreath->m_workArea + colorOffset);

    if (work->m_particleData == NULL) {
        YmBreathParticleGroup* groupTable;

        work->m_particleCount = (int)params->m_particleCount;
        work->m_slotCount = params->m_slotCount;
        work->m_groupCount = params->m_groupCount;

        work->m_particleData =
            (PARTICLE_DATA*)pppMemAlloc((unsigned long)(work->m_particleCount * sizeof(PARTICLE_DATA)),
                                        ppvEnv->m_stagePtr,
                                        const_cast<char*>(s_pppYmBreath_cpp), 0x243);
        if (work->m_particleData != NULL) {
            memset(work->m_particleData, 0, (unsigned long)(work->m_particleCount * sizeof(PARTICLE_DATA)));
        }

        work->m_particleWmats =
            (PARTICLE_WMAT*)pppMemAlloc((unsigned long)(work->m_particleCount * sizeof(PARTICLE_WMAT)),
                                        ppvEnv->m_stagePtr,
                                        const_cast<char*>(s_pppYmBreath_cpp), 0x249);
        if (work->m_particleWmats != NULL) {
            memset(work->m_particleWmats, 0, (unsigned long)(work->m_particleCount * sizeof(PARTICLE_WMAT)));
        }

        work->m_particleColors =
            (PARTICLE_COLOR*)pppMemAlloc((unsigned long)(work->m_particleCount * sizeof(PARTICLE_COLOR)),
                                         ppvEnv->m_stagePtr,
                                         const_cast<char*>(s_pppYmBreath_cpp), 0x24F);
        if (work->m_particleColors != NULL) {
            memset(work->m_particleColors, 0, (unsigned long)(work->m_particleCount * sizeof(PARTICLE_COLOR)));
        }

        work->m_groups =
            (YmBreathParticleGroup*)pppMemAlloc(
                (unsigned long)((int)params->m_groupCount * sizeof(YmBreathParticleGroup)), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppYmBreath_cpp), 0x255);
        if (work->m_groups != NULL) {
            memset(work->m_groups, 0, (unsigned long)((int)params->m_groupCount * sizeof(YmBreathParticleGroup)));

            groupTable = work->m_groups;
            for (i = 0; i < (int)params->m_groupCount; i++) {
                groupTable->particleIndices = (signed char*)pppMemAlloc(
                    (unsigned long)params->m_slotCount, ppvEnv->m_stagePtr,
                    const_cast<char*>(s_pppYmBreath_cpp), 0x260);
                memset(groupTable->particleIndices, -1, (unsigned long)params->m_slotCount);

                groupTable->particleStates = (signed char*)pppMemAlloc(
                    (unsigned long)params->m_slotCount, ppvEnv->m_stagePtr,
                    const_cast<char*>(s_pppYmBreath_cpp), 0x263);
                memset(groupTable->particleStates, -1, (unsigned long)params->m_slotCount);
                groupTable->active = 0;
                groupTable++;
            }
        }

        work->m_direction.x = kYmBreathZero;
        work->m_direction.y = kYmBreathZero;
        work->m_direction.z = kYmBreathNegativeOne;
        PSVECNormalize(&work->m_direction, &work->m_direction);
    }

    PSMTXCopy(ppvMng->m_matrix.value, work->m_matrix);
    UpdateAllParticle(ymBreath, work, pYmBreath, color);

    particleWMat = work->m_particleWmats;
    groupData = work->m_groups;
    for (groupIndex = 0; groupIndex < (int)params->m_groupCount; groupIndex++) {
        slotCount = params->m_slotCount;
        if (IsExistGroupParticle(params, work, (short)groupIndex)) {
            firstParticle = -1;
            scaledOwner = mngSt->m_hitScale * params->m_groupOwnerScale;
            for (particleSlot = 0; particleSlot < slotCount; particleSlot++) {
                if (groupData->particleStates[particleSlot] != -1) {
                    firstParticle = groupData->particleIndices[particleSlot];
                    break;
                }
            }

            PSMTXIdentity(scaleMtx);
            scaleMtx[0][0] = scaledOwner;
            scaleMtx[1][1] = scaledOwner;
            scaleMtx[2][2] = scaledOwner;
            particleMtx = &particleWMat[firstParticle];
            PSMTXConcat(particleMtx->m_matrix, ymBreath->m_localMatrix.value, worldMtx);
            PSMTXMultVec(worldMtx, &groupData->position, &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = kYmBreathZero;
            rotMtx.value[1][3] = kYmBreathZero;
            rotMtx.value[2][3] = kYmBreathZero;
            groupData->scale = scaledOwner;
            pppCopyVector(dir, groupData->direction);
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppNormalize(dir, dir);
            PSVECScale(&dir, &dir, groupData->speed);
            pppAddVector(target, origin, dir);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(mngSt, &origin, &hitVector, scaledOwner, params->m_groupRadius);
        }
        groupData++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c09e8
 * PAL Size: 1072b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateAllParticle(_pppPObject* pppObject, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor)
{
    PYmBreath* params = pYmBreath;
    PARTICLE_DATA* particleData;
    PARTICLE_WMAT* particleWmat;
    PARTICLE_COLOR* particleColor;
    YmBreathParticleGroup* groupTable;
    int maxParticleCount;
    unsigned short* emitFrameCounter;
    int spawnCount;
    int i;
    int k;
    int j;
    YmBreathParticleGroup* groupData;
    short foundSlot;
    short foundGroup;
    Vec unitVelocity;
    Vec stepVelocity;

    particleData = vYmBreath->m_particleData;
    particleWmat = vYmBreath->m_particleWmats;
    particleColor = vYmBreath->m_particleColors;
    groupTable = vYmBreath->m_groups;
    maxParticleCount = vYmBreath->m_particleCount;
    spawnCount = 0;
    emitFrameCounter = &vYmBreath->m_emitFrameCounter;

    if ((ppvUserStopPartF == 0) && (params->m_shapeStepValue != 0xFFFF)) {
        *emitFrameCounter = *emitFrameCounter + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (particleData->m_life > 0) {
                UpdateParticle(vYmBreath, pYmBreath, particleData, vColor, particleColor);
                pppShapeSt* shape = ppvEnv->m_resourceTables.m_shapeTablePtr[params->m_shapeStepValue];
                pppCalcFrameShape(static_cast<long*>(shape->m_animData), particleData->m_shapeFrame1,
                                  particleData->m_shapeFrame2, particleData->m_shapeFrame0,
                                  params->m_shapeFrameArg);
            } else {
                float zero = kYmBreathZero;

                if (SearchIndex(params, vYmBreath, foundGroup, foundSlot, (short)i)) {
                    groupTable[foundGroup].particleIndices[foundSlot] = -1;
                }
                if (foundGroup != -1) {
                    if (IsDeadGroupBreath(params, vYmBreath, foundGroup) == 1) {
                        groupData = &groupTable[foundGroup];
                        for (int slot = 0; slot < params->m_slotCount; slot++) {
                            groupData->particleStates[slot] = -1;
                            groupData->position.x = groupData->position.y = groupData->position.z = zero;
                            groupData->direction.x = groupData->direction.y = groupData->direction.z = zero;
                            groupData->speed = zero;
                        }
                        groupData->active = 0;
                    }
                }

                if ((params->m_emitInterval <= *emitFrameCounter) && (spawnCount < (int)params->m_emitCount)) {
                    bool placing;

                    BirthParticle(pppObject, vYmBreath, pYmBreath, vColor, particleData,
                                  particleWmat, particleColor);
                    placing = true;
                    spawnCount += 1;
                    groupData = groupTable;
                    for (j = 0; j < (int)params->m_groupCount; j++) {
                        for (k = 0; k < (int)params->m_slotCount; k++) {
                            if ((groupData->particleIndices[k] == -1) && (groupData->particleStates[k] == -1)) {
                                groupData->particleIndices[k] = (signed char)i;
                                placing = false;
                                groupData->particleStates[k] = 1;
                            }
                            if (!placing) {
                                break;
                            }
                        }
                        if (!placing) {
                            break;
                        }
                        groupData += 1;
                    }
                }
            }

            if (particleWmat != NULL) {
                particleWmat += 1;
            }
            if (particleColor != NULL) {
                particleColor += 1;
            }
            particleData += 1;
        }

        if (spawnCount > 0) {
            *emitFrameCounter = 0;
        }

        groupData = groupTable;
        for (j = 0; j < (int)params->m_groupCount; j++) {
            if ((groupData->active != 1) && (*groupData->particleIndices != -1) && (*groupData->particleStates == 1)) {
                groupData->speed = params->m_groupSpeed;
                unitVelocity.x = kYmBreathZero;
                unitVelocity.y = kYmBreathZero;
                unitVelocity.z = kYmBreathNegativeOne;
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.z = kYmBreathZero;
                groupData->position.y = kYmBreathZero;
                groupData->position.x = kYmBreathZero;
                PSMTXCopy(ppvMng->m_matrix.value, groupData->matrix);
                groupData->active = 1;
            }
            groupData += 1;
        }

        groupData = groupTable;
        for (j = 0; j < (int)params->m_groupCount; j++) {
            if (groupData->active != 0) {
                PSVECScale(&groupData->direction, &stepVelocity, groupData->speed);
                PSVECAdd(&stepVelocity, &groupData->position, &groupData->position);
            }
            groupData += 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c0e18
 * PAL Size: 884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateParticle(VYmBreath* vYmBreath, PYmBreath* pYmBreath, PARTICLE_DATA* particleData, VColor* vColor,
                    PARTICLE_COLOR* particleColor)
{
    PYmBreath* params = pYmBreath;
    int alpha = vColor->m_alpha;
    PARTICLE_DATA* particle = particleData;
    Vec step;

    (void)vYmBreath;

    if (particleColor != NULL) {
        particleColor->m_color[0] += particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] += particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] += particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] += particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] += params->m_colorFrameAccel0;
        particleColor->m_colorFrameDeltas[1] += params->m_colorFrameAccel1;
        particleColor->m_colorFrameDeltas[2] += params->m_colorFrameAccel2;
        particleColor->m_colorFrameDeltas[3] += params->m_colorFrameAccel3;
        alpha = (int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    particle->m_angle += particle->m_angleVelocity;
    if (params->m_angleFlags & 0x10) {
        particle->m_angleVelocity = params->m_angleAccel + particle->m_angleRandom + particle->m_angleVelocity;
    } else {
        particle->m_angleVelocity += params->m_angleAccel;
    }

    while (kYmBreathHalfCircleDegrees <= particle->m_angle) {
        particle->m_angle -= kYmBreathFullTurnDegrees;
    }
    while (particle->m_angle < kYmBreathNegativeHalfCircleDegrees) {
        particle->m_angle += kYmBreathFullTurnDegrees;
    }

    particle->m_rotationX += particle->m_rotationVelocityX;
    particle->m_rotationY += particle->m_rotationVelocityY;
    if (params->m_rotationFlags & 0x10) {
        particle->m_rotationVelocityX = params->m_rotationAccelX + particle->m_rotationAccelX + particle->m_rotationVelocityX;
        particle->m_rotationVelocityY = params->m_rotationAccelY + particle->m_rotationAccelY + particle->m_rotationVelocityY;
    } else {
        particle->m_rotationVelocityX += params->m_rotationAccelX;
        particle->m_rotationVelocityY += params->m_rotationAccelY;
    }

    particle->m_scale += params->m_scaleAccel;
    if (params->m_disableScaleClamp == 0) {
        float zero = kYmBreathZero;
        if ((zero < params->m_scaleClampStart) && (params->m_scaleAccel < zero)) {
            if (particle->m_scale < zero) {
                particle->m_scale = zero;
            }
        } else if (params->m_scaleClampStart < zero) {
            if ((zero < params->m_scaleAccel) && (zero < particle->m_scale)) {
                particle->m_scale = zero;
            }
        }
    }

    PSVECScale(&particle->m_direction, &step, particle->m_scale);
    PSVECAdd(&step, &particle->m_position, &particle->m_position);

    if (params->m_particleLifetime != 0) {
        particle->m_life = particle->m_life - 1;
    }
    particle->m_age = particle->m_age + 1;

    char fadeOutFrames = particle->m_fadeOutFrames;
    if ((fadeOutFrames != 0) && (particle->m_age <= fadeOutFrames)) {
        particle->m_alpha -= (float)alpha / (float)fadeOutFrames;
    }

    if ((particle->m_fadeInFrames != '\0') && ((int)particle->m_life <= (int)particle->m_fadeInFrames)) {
        particle->m_alpha += (float)alpha / (float)(unsigned int)params->m_fadeInFrames;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c118c
 * PAL Size: 1580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BirthParticle(_pppPObject*, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor, PARTICLE_DATA* particleData,
                   PARTICLE_WMAT* particleWmat, PARTICLE_COLOR* particleColor)
{
    Vec baseDir;
    pppIVECTOR4 angle;
    pppFMATRIX rotMtx;
    float spread;
    float range;
    u8 flags;

    spread = (float)(unsigned int)pYmBreath->m_spread;
    range = spread * kYmBreathSpreadScale;

    memset(particleData, 0, sizeof(PARTICLE_DATA));
    if (particleWmat != NULL) {
        memset(particleWmat, 0, sizeof(PARTICLE_WMAT));
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, sizeof(PARTICLE_COLOR));
    }

    PYmBreath* params = pYmBreath;
    PARTICLE_DATA* particle = particleData;

    baseDir.x = kYmBreathZero;
    baseDir.y = kYmBreathZero;
    baseDir.z = kYmBreathNegativeOne;

    angle.x = (int)(range * Math.RandF() - spread);
    angle.x = (int)((float)(angle.x << 15) / kYmBreathHalfCircleDegrees);
    angle.y = (int)(range * Math.RandF() - spread);
    angle.y = (int)((float)(angle.y << 15) / kYmBreathHalfCircleDegrees);
    angle.z = (int)(range * Math.RandF() - spread);
    angle.z = (int)((float)(angle.z << 15) / kYmBreathHalfCircleDegrees);

    pppGetRotMatrixXYZ(rotMtx, &angle);
    PSMTXMultVecSR(rotMtx.value, &baseDir, &particle->m_direction);

    particle->m_direction.x *= params->m_directionScaleX;
    particle->m_direction.y *= params->m_directionScaleY;
    particle->m_direction.z *= params->m_directionScaleZ;

    Vec directionNorm = particle->m_direction;
    pppNormalize(particle->m_direction, directionNorm);

    if (kYmBreathZero != params->m_spawnOffset) {
        PSVECScale(&particle->m_direction, &particle->m_position, params->m_spawnOffset);
    }

    if (params->m_fadeOutFrames != 0) {
        particle->m_alpha = (float)(unsigned int)vColor->m_alpha;
        particle->m_fadeOutFrames = params->m_fadeOutFrames;
    }
    if (params->m_fadeInFrames != 0) {
        particle->m_fadeInFrames = params->m_fadeInFrames;
    }

    particle->m_angle = params->m_angleStart;
    particle->m_angleVelocity = params->m_angleStep;

    if (params->m_angleFlags != 0) {
        particle->m_angleRandom = params->m_angleRandomRange * Math.RandF();
        flags = params->m_angleFlags;
        if (((flags & 1) != 0) && ((flags & 2) != 0)) {
            if (kYmBreathHalfChance < Math.RandF()) {
                particle->m_angleRandom *= kYmBreathNegativeOne;
            }
        } else if ((flags & 2) != 0) {
            particle->m_angleRandom *= kYmBreathNegativeOne;
        }
    }

    if ((params->m_angleFlags & 4) != 0) {
        particle->m_angle += particle->m_angleRandom;
    }
    if ((params->m_angleFlags & 8) != 0) {
        particle->m_angleVelocity += particle->m_angleRandom;
    }

    while (kYmBreathHalfCircleDegrees <= particle->m_angle) {
        particle->m_angle -= kYmBreathFullTurnDegrees;
    }
    while (particle->m_angle < kYmBreathNegativeHalfCircleDegrees) {
        particle->m_angle += kYmBreathFullTurnDegrees;
    }

    particle->m_rotationX = params->m_rotationStartX;
    particle->m_rotationY = params->m_rotationStartY;
    particle->m_rotationVelocityX = params->m_rotationVelocityX;
    particle->m_rotationVelocityY = params->m_rotationVelocityY;

    if (params->m_rotationFlags != 0) {
        if ((params->m_rotationFlags & 0x20) != 0) {
            float rotationAccel = params->m_rotationRandomX * Math.RandF();
            particle->m_rotationAccelY = rotationAccel;
            particle->m_rotationAccelX = rotationAccel;
            if (((params->m_rotationFlags & 1) != 0) && ((params->m_rotationFlags & 2) != 0)) {
                if (kYmBreathHalfChance < Math.RandF()) {
                    particle->m_rotationAccelX *= kYmBreathNegativeOne;
                    particle->m_rotationAccelY *= kYmBreathNegativeOne;
                }
            } else if ((params->m_rotationFlags & 2) != 0) {
                particle->m_rotationAccelX *= kYmBreathNegativeOne;
                particle->m_rotationAccelY *= kYmBreathNegativeOne;
            }
        } else {
            particle->m_rotationAccelX = params->m_rotationRandomX * Math.RandF();
            particle->m_rotationAccelY = params->m_rotationRandomY * Math.RandF();
            if (((params->m_rotationFlags & 1) != 0) && ((params->m_rotationFlags & 2) != 0)) {
                if (kYmBreathHalfChance < Math.RandF()) {
                    particle->m_rotationAccelX *= kYmBreathNegativeOne;
                }
                if (kYmBreathHalfChance < Math.RandF()) {
                    particle->m_rotationAccelY *= kYmBreathNegativeOne;
                }
            } else if ((params->m_rotationFlags & 2) != 0) {
                particle->m_rotationAccelX *= kYmBreathNegativeOne;
                particle->m_rotationAccelY *= kYmBreathNegativeOne;
            }
        }
    }

    if ((params->m_rotationFlags & 4) != 0) {
        particle->m_rotationX += particle->m_rotationAccelX;
        particle->m_rotationY += particle->m_rotationAccelY;
    }
    if ((params->m_rotationFlags & 8) != 0) {
        particle->m_rotationVelocityX += particle->m_rotationAccelX;
        particle->m_rotationVelocityY += particle->m_rotationAccelY;
    }

    float zero = kYmBreathZero;
    particle->m_scale = params->m_groupSpeed;
    if (zero != params->m_scaleRandomRange) {
        float rand = Math.RandF();
        float scaledRange = params->m_scaleRandomRange * kYmBreathSpreadScale;
        particle->m_scale += scaledRange * rand - params->m_scaleRandomRange;
    }

    if (params->m_particleLifetime == 0) {
        particle->m_life = -1;
    } else {
        particle->m_life = params->m_particleLifetime;
    }
    particle->m_age = 0;

    PSMTXCopy(vYmBreath->m_matrix, particleWmat->m_matrix);
    if (particleColor != NULL) {
        particleColor->m_colorFrameDeltas[0] = params->m_colorFrameDelta0;
        particleColor->m_colorFrameDeltas[1] = params->m_colorFrameDelta1;
        particleColor->m_colorFrameDeltas[2] = params->m_colorFrameDelta2;
        particleColor->m_colorFrameDeltas[3] = params->m_colorFrameDelta3;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void get_rand()
{
    Math.RandF();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void SetParticleMatrix(_pppPObject* pppObject, VYmBreath* vYmBreath, PARTICLE_DATA* particleData,
                              PARTICLE_WMAT* particleWmat)
{
    PARTICLE_DATA* particle = particleData;
    Mtx workMtx;

    PSMTXCopy(vYmBreath->m_matrix, particleWmat->m_matrix);
    PSMTXCopy(particleWmat->m_matrix, workMtx);
    workMtx[0][3] = 0.0f;
    workMtx[1][3] = 0.0f;
    workMtx[2][3] = 0.0f;

    PSMTXMultVec(workMtx, &particle->m_direction, &particle->m_direction);
    PSVECNormalize(&particle->m_direction, &particle->m_direction);
    PSMTXConcat(particleWmat->m_matrix, pppObject->m_localMatrix.value, particleWmat->m_matrix);
}
