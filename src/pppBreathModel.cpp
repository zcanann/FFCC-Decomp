#define PPP_BREATHMODEL_CUSTOM_PARTICLE_TYPES
#include "ffcc/pppBreathModel.h"
#include "ffcc/linkage.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "ffcc/math.h"
extern "C" {
extern int gPppCalcDisabled;
}
#include "ffcc/pppPart.h"
#include <string.h>

struct pppModelSt;

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" const char s_pppBreathModel_cpp[] = "pppBreathModel.cpp";

struct pppBreathModelUnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct pppBreathModel;

struct BreathParticleGroup {
    int active;
    signed char* particleIndices;
    signed char* particleStates;
    Vec position;
    Vec direction;
    float speed;
    float scale;
    Mtx matrix;
};

struct VBreathModel {
    Mtx m_matrix;
    PARTICLE_DATA* m_particleData;
    PARTICLE_WMAT* m_particleWmats;
    PARTICLE_COLOR* m_particleColors;
    BreathParticleGroup* m_groups;
    int m_particleCount;
    u16 m_emitFrameCounter;
    u16 _pad46;
    Vec m_direction;
    s16 m_groupCount;
    s16 m_slotCount;
    u8 m_flags;
    u8 _pad59[3];
};

struct PBreathModel {
    int m_graphId;
    float m_groupRadius;
    float m_groupOwnerScale;
    int m_stepValue;
    u16 m_slotCount;
    u16 m_groupCount;
    float m_groupSpeed;
    u8 m_blendMode;
    u8 _pad19;
    u16 m_particleCount;
    u16 m_emitCount;
    u16 m_emitInterval;
    u16 m_particleLifetime;
    u8 m_fadeOutFrames;
    u8 m_fadeInFrames;
    unsigned char _pad24[0x04];
    float m_colorFrameDelta0;
    float m_colorFrameDelta1;
    float m_colorFrameDelta2;
    float m_colorFrameDelta3;
    float m_colorFrameAccel0;
    float m_colorFrameAccel1;
    float m_colorFrameAccel2;
    float m_colorFrameAccel3;
    unsigned char _pad48[0x08];
    float m_rotationStartX;
    float m_rotationStartY;
    float m_rotationStartZ;
    unsigned char _pad5C[0x04];
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    float m_rotationVelocityZ;
    unsigned char _pad6C[0x04];
    float m_rotationAccelX;
    float m_rotationAccelY;
    float m_rotationAccelZ;
    unsigned char _pad7C[0x04];
    float m_rotationRandomX;
    float m_rotationRandomY;
    float m_rotationRandomZ;
    unsigned char _pad8C[0x04];
    float m_angleStart;
    float m_angleStep;
    float m_angleAccel;
    float m_angleRandomRange;
    float m_scaleClampStart;
    float m_scaleAccel;
    float m_scaleRandomRange;
    unsigned char _padAC[0x04];
    float m_spawnJitterX;
    float m_spawnJitterY;
    float m_spawnJitterZ;
    unsigned char _padBC[0x04];
    u8 m_rotationFlags;
    u8 m_angleFlags;
    unsigned char _padC2[0x02];
    float m_drawEnvScale;
    u8 m_disableScaleClamp;
    u8 m_drawEnvColor0;
    u8 m_drawEnvColor1;
    u8 m_drawEnvColor2;
    u8 m_drawEnvColor3;
    u8 m_drawEnvColor4;
};

struct BreathParticleData {
    Mtx m_modelMtx;
    Vec m_position;
    Vec m_direction;
    u8 _pad48[0x08];
    s16 m_life;
    u8 _pad52[0x02];
    char m_fadeOutFrames;
    char m_fadeInFrames;
    float m_angle;
    float m_angleVelocity;
    float m_angleRandom;
    float m_rotationX;
    float m_rotationY;
    float m_rotationZ;
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    float m_rotationVelocityZ;
    float m_rotationAccelX;
    float m_rotationAccelY;
    float m_rotationAccelZ;
    float m_alpha;
    float m_scale;
    u8 m_age;
    u8 _pad91[0x07];
};

struct PARTICLE_DATA {
    u8 _pad[0x98];
};

struct PARTICLE_WMAT {
    Mtx m_matrix;
};

struct PARTICLE_COLOR {
    float m_color[4];
    float m_colorFrameDeltas[4];
};

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void get_rand()
{
	// TODO
}
#endif

void UpdateAllParticle(_pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, VColor* vColor);

/*
 * --INFO--
 * PAL Address: 0x800db094
 * PAL Size: 248b
 */
extern "C" void pppDestructBreathModel(pppBreathModel* pppBreathModel, pppBreathModelUnkC* param_2)
{
    BreathParticleGroup* group;
    VBreathModel* state = (VBreathModel*)((unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets);

    if (state->m_particleData != NULL) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(state->m_particleData));
        state->m_particleData = 0;
    }

    if (state->m_particleWmats != NULL) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(state->m_particleWmats));
        state->m_particleWmats = 0;
    }

    if (state->m_particleColors != NULL) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(state->m_particleColors));
        state->m_particleColors = 0;
    }

    group = state->m_groups;
    if (group != NULL) {
        int i;

        for (i = 0; i < state->m_groupCount; i++) {
            if (group->particleIndices != NULL) {
                pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(group->particleIndices));
                group->particleIndices = 0;
            }

            if (group->particleStates != NULL) {
                pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(group->particleStates));
                group->particleStates = 0;
            }

            group = (BreathParticleGroup*)((unsigned char*)group + 0x5C);
        }

        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(state->m_groups));
        state->m_groups = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800db18c
 * PAL Size: 120b
 */
extern "C" void pppConstructBreathModel(pppBreathModel* pppBreathModel, pppBreathModelUnkC* param_2)
{
    VBreathModel* state = (VBreathModel*)((unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets);
    PSMTXIdentity(state->m_matrix);
    float zero = 0.0f;

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
 * PAL Address: 0x800db204
 * PAL Size: 1244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderBreathModel(pppBreathModel* breathModel, PBreathModel* pBreathModel, pppBreathModelUnkC* offsets)
{
    BreathParticleData* particleData;
    PARTICLE_WMAT* matrixList;
    PARTICLE_COLOR* particleColor;
    BreathParticleGroup* groupData;
    int groupCount;
    _pppPObject* object;
    int workOffset;
    int colorOffset;
    VBreathModel* work;
    VColor* color;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char colorA;
    int i;
    pppModelSt* model;
    _GXColor drawColor;
    _GXColor debugColor;
    Vec debugPos;
    Vec pos;
    Mtx debugMtx;
    Mtx sphereMtx;
    Mtx cameraMtx;
    Mtx drawMtx;
    Mtx tempMtx;

    object = reinterpret_cast<_pppPObject*>(breathModel);
    workOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    work = reinterpret_cast<VBreathModel*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + workOffset);
    color = reinterpret_cast<VColor*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);
    particleData = reinterpret_cast<BreathParticleData*>(work->m_particleData);
    matrixList = work->m_particleWmats;
    particleColor = work->m_particleColors;
    groupData = work->m_groups;
    groupCount = work->m_particleCount;

    if (pBreathModel->m_stepValue == 0xFFFF) {
        return;
    }

    model = reinterpret_cast<pppModelSt*>(pppEnvStPtr->m_mapMeshPtr[pBreathModel->m_stepValue]);
    pppInitBlendMode();
    pppSetBlendMode(pBreathModel->m_blendMode);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(
        static_cast<pppCVECTOR*>(NULL), static_cast<pppFMATRIX*>(NULL), pBreathModel->m_drawEnvScale,
        pBreathModel->m_drawEnvColor1, pBreathModel->m_drawEnvColor0, pBreathModel->m_blendMode,
        pBreathModel->m_drawEnvColor2, pBreathModel->m_drawEnvColor3, static_cast<u8>(1), pBreathModel->m_drawEnvColor4);

    colorR = color->m_red;
    colorG = color->m_green;
    colorB = color->m_blue;
    colorA = color->m_alpha;

    for (i = 0; i < groupCount; i++) {
        if (0 < particleData->m_life) {
            int r;
            int g;
            int b;
            int a;

            PSMTXScale(drawMtx, pppMngStPtr->m_scale.x * particleData->m_rotationX,
                       pppMngStPtr->m_scale.y * particleData->m_rotationY,
                       pppMngStPtr->m_scale.z * particleData->m_rotationZ);
            PSMTXConcat(particleData->m_modelMtx, drawMtx, tempMtx);
            PSMTXConcat(ppvCameraMatrix, tempMtx, tempMtx);
            PSMTXConcat(ppvCameraMatrix, particleData->m_modelMtx, cameraMtx);
            PSMTXMultVec(cameraMtx, &particleData->m_position, &pos);
            tempMtx[0][3] = pos.x;
            tempMtx[1][3] = pos.y;
            tempMtx[2][3] = pos.z;
            GXLoadPosMtxImm(tempMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((float)(int)colorA - particleData->m_alpha);

            if (particleColor != NULL) {
                r += (int)particleColor->m_color[0];
                g += (int)particleColor->m_color[1];
                b += (int)particleColor->m_color[2];
                a += (int)particleColor->m_color[3];
            }

            if (r < 0) {
                r = 0;
            } else if (r > 255) {
                r = 255;
            }
            if (g < 0) {
                g = 0;
            } else if (g > 255) {
                g = 255;
            }
            if (b < 0) {
                b = 0;
            } else if (b > 255) {
                b = 255;
            }
            if (a < 0) {
                a = 0;
            } else if (a > 127) {
                a = 127;
            }

            drawColor.r = (u8)r;
            drawColor.g = (u8)g;
            drawColor.b = (u8)b;
            drawColor.a = (u8)a;
            GXSetChanAmbColor(GX_COLOR0A0, drawColor);
            pppDrawMesh(model, object->m_drawMatrixPtr, 1);
        }

        if (matrixList != NULL) {
            matrixList++;
        }
        if (particleColor != NULL) {
            particleColor++;
        }
        particleData++;
    }

    if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
        BreathParticleGroup* debugGroupData = groupData;
        for (i = 0; i < (int)pBreathModel->m_groupCount; i++, debugGroupData++) {
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
                for (j = 0; j < (int)pBreathModel->m_slotCount; j++) {
                    if (debugGroupData->particleStates[j] != -1) {
                        firstParticle = debugGroupData->particleIndices[j];
                        break;
                    }
                }

                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = groupScale;
                sphereMtx[1][1] = groupScale;
                sphereMtx[2][2] = groupScale;
                PSMTXConcat(work->m_particleWmats[firstParticle].m_matrix, object->m_localMatrix.value, debugMtx);
                PSMTXConcat(ppvCameraMatrix, debugMtx, debugMtx);
                PSMTXMultVec(debugMtx, &debugGroupData->position, &debugPos);
                sphereMtx[0][3] = debugPos.x;
                sphereMtx[1][3] = debugPos.y;
                sphereMtx[2][3] = debugPos.z;

                pppSetBlendMode(1);
                Graphic.DrawSphere(sphereMtx, debugColor);
            }
        }

        pppInitBlendMode();
        _GXSetTevOp(GX_TEVSTAGE0, GX_BLEND);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800db6e0
 * PAL Size: 1264b
 */
extern "C" void pppFrameBreathModel(pppBreathModel* breathModel, PBreathModel* pBreathModel, pppBreathModelUnkC* offsets)
{
    BreathParticleGroup* groupData;
    _pppMngSt* mngSt;
    int colorOffset;
    int* dataOffsets;
    VColor* color;
    VBreathModel* work;
    Mtx* particleWMat;
    Mtx* particleMtx;
    int groupIndex;
    int firstParticle;
    short slotIndex;
    int particleSlot;
    int slotCount;
    int ready;
    float scaledOwner;
    BreathParticleGroup* groupCheck;
    Mtx scaleMtx;
    Mtx worldMtx;
    pppFMATRIX rotMtx;
    Vec hitVector;
    Vec dir;
    Vec origin;
    Vec target;

    if (gPppCalcDisabled != 0) {
        return;
    }

    _pppPObject* object = reinterpret_cast<_pppPObject*>(breathModel);

    dataOffsets = offsets->m_serializedDataOffsets;
    mngSt = pppMngStPtr;
    colorOffset = dataOffsets[1];
    work = reinterpret_cast<VBreathModel*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + dataOffsets[0]);
    color = (VColor*)(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);

    if (work->m_particleData == NULL) {
        BreathParticleGroup* groupTable;
        int i;

        work->m_particleCount = pBreathModel->m_particleCount;
        work->m_slotCount = pBreathModel->m_slotCount;
        work->m_groupCount = pBreathModel->m_groupCount;

        work->m_particleData =
            (PARTICLE_DATA*)pppMemAlloc((unsigned long)(work->m_particleCount * 0x98), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp), 0x257);
        if (work->m_particleData != NULL) {
            memset(work->m_particleData, 0, (unsigned long)(work->m_particleCount * 0x98));
        }

        work->m_particleWmats =
            (PARTICLE_WMAT*)pppMemAlloc((unsigned long)(work->m_particleCount * 0x30), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp), 0x25d);
        if (work->m_particleWmats != NULL) {
            memset(work->m_particleWmats, 0, (unsigned long)(work->m_particleCount * 0x30));
        }

        work->m_particleColors =
            (PARTICLE_COLOR*)pppMemAlloc((unsigned long)(work->m_particleCount << 5), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp), 0x263);
        if (work->m_particleColors != NULL) {
            memset(work->m_particleColors, 0, (unsigned long)(work->m_particleCount << 5));
        }

        work->m_groups =
            (BreathParticleGroup*)pppMemAlloc(
                (unsigned long)((int)pBreathModel->m_groupCount * 0x5C),
                pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp), 0x269);
        if (work->m_groups != NULL) {
            memset(work->m_groups, 0, (unsigned long)((int)pBreathModel->m_groupCount * 0x5C));

            groupTable = work->m_groups;
            for (i = 0; i < (int)pBreathModel->m_groupCount; i++) {
                groupTable->particleIndices = (signed char*)pppMemAlloc(
                    (unsigned long)pBreathModel->m_slotCount,
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp), 0x274);
                memset(groupTable->particleIndices, -1, (unsigned long)pBreathModel->m_slotCount);

                groupTable->particleStates = (signed char*)pppMemAlloc(
                    (unsigned long)pBreathModel->m_slotCount,
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp), 0x277);
                memset(groupTable->particleStates, -1, (unsigned long)pBreathModel->m_slotCount);
                groupTable->active = 0;
                groupTable++;
            }
        }

        work->m_direction.x = 0.0f;
        work->m_direction.y = 0.0f;
        work->m_direction.z = -1.0f;
        PSVECNormalize(&work->m_direction, &work->m_direction);
    }

    PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_matrix);
    UpdateAllParticle(reinterpret_cast<_pppPObject*>(breathModel), work, pBreathModel, color);

    particleWMat = reinterpret_cast<Mtx*>(work->m_particleWmats);
    groupData = work->m_groups;
    for (groupIndex = 0; groupIndex < (int)pBreathModel->m_groupCount; groupIndex++) {
        groupCheck = &work->m_groups[(short)groupIndex];
        slotCount = pBreathModel->m_slotCount;
        for (slotIndex = 0; slotIndex < (int)slotCount; slotIndex++) {
            if ((groupCheck->particleIndices[slotIndex] == -1) || (groupCheck->particleStates[slotIndex] != 1)) {
                ready = 0;
                goto group_ready;
            }
        }
        ready = 1;
group_ready:
        if (ready) {
            firstParticle = -1;
            scaledOwner = mngSt->m_previousPosition.z * pBreathModel->m_groupOwnerScale;
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
            particleMtx = (Mtx*)((unsigned char*)particleWMat + firstParticle * 0x30);
            PSMTXConcat(*particleMtx, object->m_localMatrix.value, worldMtx);
            PSMTXMultVec(worldMtx, &groupData->position, &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = 0.0f;
            rotMtx.value[1][3] = 0.0f;
            rotMtx.value[2][3] = 0.0f;
            groupData->scale = scaledOwner;
            pppCopyVector(dir, groupData->direction);
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppNormalize(dir, dir);
            PSVECScale(&dir, &dir, groupData->speed);
            pppAddVector(target, origin, dir);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(mngSt, &origin, &hitVector, scaledOwner, pBreathModel->m_groupRadius);
        }
        groupData++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateAllParticle(_pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, VColor* vColor)
{
    PBreathModel* params = reinterpret_cast<PBreathModel*>(pBreathModel);
    BreathParticleData* particleData;
    PARTICLE_WMAT* particleWmat;
    PARTICLE_COLOR* particleColor;
    BreathParticleGroup* groupTable;
    int maxParticleCount;
    unsigned short* emitFrameCounter;
    int found;
    int spawnCount;
    int i;
    int k;
    int j;
    BreathParticleGroup* checkGroup;
    BreathParticleGroup* groupCursor;
    BreathParticleGroup* groupData;
    short groupIndex;
    short slotIndex;
    short foundSlot;
    short foundGroup;
    Vec unitVelocity;
    Vec stepVelocity;

    particleData = reinterpret_cast<BreathParticleData*>(vBreathModel->m_particleData);
    particleWmat = vBreathModel->m_particleWmats;
    particleColor = vBreathModel->m_particleColors;
    groupTable = vBreathModel->m_groups;
    maxParticleCount = vBreathModel->m_particleCount;
    spawnCount = 0;
    emitFrameCounter = &vBreathModel->m_emitFrameCounter;

    if ((gPppCalcDisabled == 0) && (params->m_stepValue != 0xFFFF)) {
        *emitFrameCounter = *emitFrameCounter + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (particleData->m_life > 0) {
                UpdateParticle(
                    vBreathModel, pBreathModel, (PARTICLE_DATA*)particleData, vColor, particleColor);
            } else {
                float zero = 0.0f;

                groupCursor = vBreathModel->m_groups;
                foundGroup = -1;
                foundSlot = -1;
                for (groupIndex = 0; groupIndex < (int)params->m_groupCount; groupIndex++, groupCursor++) {
                    for (slotIndex = 0; slotIndex < (int)params->m_slotCount; slotIndex++) {
                        signed char* particleIndices = groupCursor->particleIndices;
                        if ((short)i == particleIndices[(short)slotIndex]) {
                            foundGroup = groupIndex;
                            foundSlot = slotIndex;
                            found = true;
                            goto found_index;
                        }
                    }
                }
                found = false;

            found_index:
                if (found) {
                    groupTable[(int)foundGroup].particleIndices[(int)foundSlot] = -1;
                }

                if ((int)foundGroup != -1) {
                    int slot;

                    slot = 0;
                    checkGroup = &vBreathModel->m_groups[(int)foundGroup];
                    for (slot = 0; slot < (int)params->m_slotCount; slot++) {
                        if ((checkGroup->particleIndices[slot] != -1) ||
                            (checkGroup->particleStates[slot] != 1)) {
                            found = false;
                            goto group_checked;
                        }
                    }
                    found = true;

                group_checked:
                    if (found == 1) {
                        groupData = &groupTable[(int)foundGroup];
                        for (slot = 0; slot < (int)params->m_slotCount; slot++) {
                            groupData->particleStates[slot] = -1;
                            groupData->position.z = zero;
                            groupData->position.y = zero;
                            groupData->position.x = zero;
                            groupData->direction.z = zero;
                            groupData->direction.y = zero;
                            groupData->direction.x = zero;
                            groupData->speed = zero;
                        }
                        groupData->active = 0;
                    }
                }

                if ((params->m_emitInterval <= *emitFrameCounter) && (spawnCount < (int)params->m_emitCount)) {
                    bool placing;

                    BirthParticle(
                        pppObject, vBreathModel, pBreathModel, vColor, (PARTICLE_DATA*)particleData,
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
                unitVelocity.x = 0.0f;
                unitVelocity.y = 0.0f;
                unitVelocity.z = -1.0f;
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.z = 0.0f;
                groupData->position.y = 0.0f;
                groupData->position.x = 0.0f;
                PSMTXCopy(pppMngStPtr->m_matrix.value, groupData->matrix);
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
 * PAL Address: 0x800DBFD4
 * PAL Size: 940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateParticle(
    VBreathModel*, PBreathModel* pBreathModel, PARTICLE_DATA* particleData, VColor* vColor, PARTICLE_COLOR* particleColor)
{
    PBreathModel* params = reinterpret_cast<PBreathModel*>(pBreathModel);
    BreathParticleData* particle = reinterpret_cast<BreathParticleData*>(particleData);
    int alpha = vColor->m_alpha;
    Vec step;

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

    while (180.0f <= particle->m_angle) {
        particle->m_angle -= 360.0f;
    }
    while (particle->m_angle < -180.0f) {
        particle->m_angle += 360.0f;
    }

    particle->m_rotationX += particle->m_rotationVelocityX;
    particle->m_rotationY += particle->m_rotationVelocityY;
    particle->m_rotationZ += particle->m_rotationVelocityZ;

    if (params->m_rotationFlags & 0x10) {
        particle->m_rotationVelocityX = params->m_rotationAccelX + particle->m_rotationAccelX + particle->m_rotationVelocityX;
        particle->m_rotationVelocityY = params->m_rotationAccelY + particle->m_rotationAccelY + particle->m_rotationVelocityY;
        particle->m_rotationVelocityZ = params->m_rotationAccelZ + particle->m_rotationAccelZ + particle->m_rotationVelocityZ;
    } else {
        particle->m_rotationVelocityX += params->m_rotationAccelX;
        particle->m_rotationVelocityY += params->m_rotationAccelY;
        particle->m_rotationVelocityZ += params->m_rotationAccelZ;
    }

    particle->m_scale += params->m_scaleAccel;
    if (params->m_disableScaleClamp == 0) {
        float zero = 0.0f;
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
 * PAL Address: 0x800dc380
 * PAL Size: 1568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BirthParticle(
    _pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, VColor* vColor,
    PARTICLE_DATA* particleData, PARTICLE_WMAT* particleWmat, PARTICLE_COLOR* particleColor)
{
    PBreathModel* params = reinterpret_cast<PBreathModel*>(pBreathModel);
    BreathParticleData* particle = reinterpret_cast<BreathParticleData*>(particleData);
    Mtx workMtx;
    Mtx cameraMtx;
    Vec jitter;
    Vec pos;

    memset(particleData, 0, 0x98);
    if (particleWmat != NULL) {
        memset(particleWmat, 0, 0x30);
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, 0x20);
    }

    Math.RandF();
    Math.RandF();
    Math.RandF();

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
        if ((params->m_angleFlags & 1) && (params->m_angleFlags & 2)) {
            if (0.5 < Math.RandF()) {
                particle->m_angleRandom *= -1.0f;
            }
        } else if (params->m_angleFlags & 2) {
            particle->m_angleRandom *= -1.0f;
        }
    }

    if ((params->m_angleFlags & 4) != 0) {
        particle->m_angle += particle->m_angleRandom;
    }
    if ((params->m_angleFlags & 8) != 0) {
        particle->m_angleVelocity += particle->m_angleRandom;
    }

    while (180.0f <= particle->m_angle) {
        particle->m_angle -= 360.0f;
    }
    while (particle->m_angle < -180.0f) {
        particle->m_angle += 360.0f;
    }

    particle->m_rotationX = params->m_rotationStartX;
    particle->m_rotationY = params->m_rotationStartY;
    particle->m_rotationZ = params->m_rotationStartZ;
    particle->m_rotationVelocityX = params->m_rotationVelocityX;
    particle->m_rotationVelocityY = params->m_rotationVelocityY;
    particle->m_rotationVelocityZ = params->m_rotationVelocityZ;

    if (params->m_rotationFlags != 0) {
        if (params->m_rotationFlags & 0x20) {
            float rotationAccel = params->m_rotationRandomX * Math.RandF();
            particle->m_rotationAccelZ = rotationAccel;
            particle->m_rotationAccelY = rotationAccel;
            particle->m_rotationAccelX = rotationAccel;
            if ((params->m_rotationFlags & 1) && (params->m_rotationFlags & 2)) {
                if (0.5 < Math.RandF()) {
                    particle->m_rotationAccelX *= -1.0f;
                    particle->m_rotationAccelY *= -1.0f;
                    particle->m_rotationAccelZ *= -1.0f;
                }
            } else if (params->m_rotationFlags & 2) {
                particle->m_rotationAccelX *= -1.0f;
                particle->m_rotationAccelY *= -1.0f;
                particle->m_rotationAccelZ *= -1.0f;
            }
        } else {
            particle->m_rotationAccelX = params->m_rotationRandomX * Math.RandF();
            particle->m_rotationAccelY = params->m_rotationRandomY * Math.RandF();
            particle->m_rotationAccelZ = params->m_rotationRandomZ * Math.RandF();
            if ((params->m_rotationFlags & 1) && (params->m_rotationFlags & 2)) {
                if (0.5 < Math.RandF()) {
                    particle->m_rotationAccelX *= -1.0f;
                }
                if (0.5 < Math.RandF()) {
                    particle->m_rotationAccelY *= -1.0f;
                }
                if (0.5 < Math.RandF()) {
                    particle->m_rotationAccelZ *= -1.0f;
                }
            } else if (params->m_rotationFlags & 2) {
                particle->m_rotationAccelX *= -1.0f;
                particle->m_rotationAccelY *= -1.0f;
                particle->m_rotationAccelZ *= -1.0f;
            }
        }
    }

    if ((params->m_rotationFlags & 4) != 0) {
        particle->m_rotationX += particle->m_rotationAccelX;
        particle->m_rotationY += particle->m_rotationAccelY;
        particle->m_rotationZ += particle->m_rotationAccelZ;
    }
    if ((params->m_rotationFlags & 8) != 0) {
        particle->m_rotationVelocityX += particle->m_rotationAccelX;
        particle->m_rotationVelocityY += particle->m_rotationAccelY;
        particle->m_rotationVelocityZ += particle->m_rotationAccelZ;
    }

    particle->m_scale = params->m_groupSpeed;
    if (params->m_scaleRandomRange != 0.0f) {
        float rand = Math.RandF();
        float scaledRange = 2.0f * params->m_scaleRandomRange;
        particle->m_scale += scaledRange * rand - params->m_scaleRandomRange;
    }

    if (params->m_particleLifetime == 0) {
        particle->m_life = -1;
    } else {
        particle->m_life = params->m_particleLifetime;
    }
    particle->m_age = 0;

    PSMTXCopy(*(Mtx*)vBreathModel, *(Mtx*)particleWmat);
    if (particleColor != NULL) {
        particleColor->m_colorFrameDeltas[0] = params->m_colorFrameDelta0;
        particleColor->m_colorFrameDeltas[1] = params->m_colorFrameDelta1;
        particleColor->m_colorFrameDeltas[2] = params->m_colorFrameDelta2;
        particleColor->m_colorFrameDeltas[3] = params->m_colorFrameDelta3;
    }

    PSMTXCopy(*(Mtx*)particleWmat, workMtx);
    workMtx[0][3] = 0.0f;
    workMtx[1][3] = 0.0f;
    workMtx[2][3] = 0.0f;

    particle->m_direction.x = 0.0f;
    particle->m_direction.y = 0.0f;
    particle->m_direction.z = -1.0f;
    PSMTXMultVec(workMtx, &particle->m_direction, &particle->m_direction);
    PSVECNormalize(&particle->m_direction, &particle->m_direction);

    float half = 0.5f;
    jitter.x = Math.RandF(params->m_spawnJitterX) - params->m_spawnJitterX * half;
    jitter.y = Math.RandF(params->m_spawnJitterY) - params->m_spawnJitterY * half;
    jitter.z = Math.RandF(params->m_spawnJitterZ) - params->m_spawnJitterZ * half;

    pos.x = (*(Mtx*)particleWmat)[0][3];
    pos.y = (*(Mtx*)particleWmat)[1][3];
    pos.z = (*(Mtx*)particleWmat)[2][3];
    PSVECAdd(&jitter, &pos, &pos);
    (*(Mtx*)particleWmat)[0][3] = pos.x;
    (*(Mtx*)particleWmat)[1][3] = pos.y;
    (*(Mtx*)particleWmat)[2][3] = pos.z;

    PSMTXConcat(*(Mtx*)particleWmat, pppObject->m_localMatrix.value, *(Mtx*)particleData);
    PSMTXConcat(ppvCameraMatrix, *(Mtx*)particleData, cameraMtx);

    particle->m_direction.x = 0.0f;
    particle->m_direction.y = 0.0f;
    particle->m_direction.z = -1.0f;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void SetParticleMatrix(_pppPObject*, VBreathModel*, PARTICLE_DATA*, PARTICLE_WMAT*, _pppMngSt*)
{
	// TODO
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void IsDeadGroupBreath(PBreathModel* pBreathModel, VBreathModel* vBreathModel, short groupIndex)
{
    int i;
    bool isDead = true;
    float zero = 0.0f;
    BreathParticleGroup* groupData =
        &(*(BreathParticleGroup**)((unsigned char*)vBreathModel + 0x3C))[(int)groupIndex];

    for (i = 0; i < pBreathModel->m_slotCount; i++) {
        if ((groupData->particleIndices[i] != -1) || (groupData->particleStates[i] != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < pBreathModel->m_slotCount; i++) {
            groupData->particleStates[i] = -1;
            groupData->position.x = zero;
            groupData->position.y = zero;
            groupData->position.z = zero;
            groupData->direction.x = zero;
            groupData->direction.y = zero;
            groupData->direction.z = zero;
            groupData->speed = zero;
        }
        groupData->active = 0;
    }
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void SearchIndex(PBreathModel* pBreathModel, VBreathModel* vBreathModel, short& slotIndex, short& groupIndex, short particleIndex)
{
    int groupTable = *(int*)((unsigned char*)vBreathModel + 0x3C);
    short g;
    short s;

    for (g = 0; g < pBreathModel->m_groupCount; g++) {
        for (s = 0; s < pBreathModel->m_slotCount; s++) {
            if ((int)particleIndex == (int)*(signed char*)(*(int*)(groupTable + 4) + s)) {
                slotIndex = s;
                groupIndex = g;
                return;
            }
        }
        groupTable += 0x5C;
    }

    slotIndex = -1;
    groupIndex = -1;
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void IsExistGroupParticle(PBreathModel* pBreathModel, VBreathModel* vBreathModel, short particleIndex)
{
    short slotIndex;
    short groupIndex;
    BreathParticleGroup* groupArray;

    SearchIndex(pBreathModel, vBreathModel, slotIndex, groupIndex, particleIndex);
    if (groupIndex != -1) {
        groupArray = *(BreathParticleGroup**)((unsigned char*)vBreathModel + 0x3C);
        groupArray[groupIndex].particleIndices[slotIndex] = -1;
    }
}
#endif
