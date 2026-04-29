#include "ffcc/pppBreathModel.h"
#include "ffcc/linkage.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "ffcc/math.h"
extern "C" {
extern const float kPppBreathModelZero = 0.0f;
extern int gPppCalcDisabled;
}
#include "ffcc/pppPart.h"
#include <string.h>

extern const double DOUBLE_80330F78 = 4503601774854144.0;
extern const float FLOAT_80330F80 = -1.0f;
extern const float FLOAT_80330F84 = 360.0f;
extern const float FLOAT_80330F88 = 180.0f;
extern const float FLOAT_80330F8C = -180.0f;
extern const double DOUBLE_80330F90 = 4503599627370496.0;
extern const double DOUBLE_80330F98 = 0.5;
extern const float FLOAT_80330FA0 = 2.0f;
extern const float FLOAT_80330FA4 = 0.5f;

struct pppModelSt;

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);

void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void pppNormalize__FR3Vec3Vec(float*, Vec*);

void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void DrawSphere__8CGraphicFPA4_f8_GXColor(void*, Mtx, _GXColor);
}

extern "C" const char s_pppBreathModel_cpp_801DB5A0[] = "pppBreathModel.cpp";

struct pppBreathModelUnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct pppBreathModel {
    unsigned char _pad00[0x10];
    Mtx m_localMatrix;
    unsigned char _pad40[0x30];
    Vec* m_modelVertices;
    unsigned char _pad74[0x0C];
    unsigned char m_workArea[1];
};

struct pppBreathModelPObject {
    unsigned char _pad00[0x10];
    Mtx m_localMatrix;
};

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
    unsigned char _pad18[0x02];
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
    unsigned char _padC2[0x06];
    u8 m_disableScaleClamp;
};

struct BreathParticleData {
    Mtx m_modelMtx;
    Vec m_position;
    Vec m_direction;
    u8 _pad48[0x08];
    s16 m_life;
    u8 _pad52[0x02];
    u8 m_fadeOutFrames;
    u8 m_fadeInFrames;
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

extern "C" void BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR(
    _pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, VColor* vColor,
    PARTICLE_DATA* particleData, PARTICLE_WMAT* particleWmat, PARTICLE_COLOR* particleColor);
extern "C" void UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR(
    VBreathModel*, PBreathModel* pBreathModel, PARTICLE_DATA* particleData, VColor* vColor, PARTICLE_COLOR* particleColor);
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
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleData);
        state->m_particleData = 0;
    }

    if (state->m_particleWmats != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleWmats);
        state->m_particleWmats = 0;
    }

    if (state->m_particleColors != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleColors);
        state->m_particleColors = 0;
    }

    group = state->m_groups;
    if (group != NULL) {
        int i;

        for (i = 0; i < state->m_groupCount; i++) {
            if (group->particleIndices != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(group->particleIndices);
                group->particleIndices = 0;
            }

            if (group->particleStates != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(group->particleStates);
                group->particleStates = 0;
            }

            group = (BreathParticleGroup*)((unsigned char*)group + 0x5C);
        }

        pppHeapUseRate__FPQ27CMemory6CStage(state->m_groups);
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
    const float& zero = kPppBreathModelZero;

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
    int workOffset;
    int colorOffset;
    VBreathModel* work;
    VColor* color;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char colorA;
    int i;
    float* particleData;
    Mtx* matrixList;
    float* particleColor;
    int* groupData;
    int groupCount;
    pppModelSt* model;

    workOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    work = reinterpret_cast<VBreathModel*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + workOffset);
    color = reinterpret_cast<VColor*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);
    particleData = reinterpret_cast<float*>(work->m_particleData);
    matrixList = work->m_particleWmats;
    particleColor = reinterpret_cast<float*>(work->m_particleColors);
    groupData = reinterpret_cast<int*>(work->m_groups);
    groupCount = work->m_particleCount;

    if (pBreathModel->m_stepValue == 0xFFFF) {
        return;
    }

    model = (pppModelSt*)(*(void***)((u8*)pppEnvStPtr + 8))[pBreathModel->m_stepValue];
    pppInitBlendMode();
    pppSetBlendMode(*(reinterpret_cast<u8*>(pBreathModel) + 0x18));
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        NULL, NULL, *reinterpret_cast<float*>(reinterpret_cast<u8*>(pBreathModel) + 0xC4),
        *(reinterpret_cast<u8*>(pBreathModel) + 0xCA), *(reinterpret_cast<u8*>(pBreathModel) + 0xC9),
        *(reinterpret_cast<u8*>(pBreathModel) + 0x18), *(reinterpret_cast<u8*>(pBreathModel) + 0xCB),
        *(reinterpret_cast<u8*>(pBreathModel) + 0xCC), 1, *(reinterpret_cast<u8*>(pBreathModel) + 0xCD));

    colorR = color->m_red;
    colorG = color->m_green;
    colorB = color->m_blue;
    colorA = color->m_alpha;

    for (i = 0; i < groupCount; i++) {
        if (0 < *(short*)((unsigned char*)particleData + 0x50)) {
            _GXColor drawColor;
            Mtx drawMtx;
            Mtx tempMtx;
            Vec pos;
            int r;
            int g;
            int b;
            int a;

            PSMTXScale(drawMtx, *(float*)((u8*)pppMngStPtr + 0x28) * particleData[0x19],
                       *(float*)((u8*)pppMngStPtr + 0x2C) * particleData[0x1A],
                       *(float*)((u8*)pppMngStPtr + 0x30) * particleData[0x1B]);
            PSMTXConcat(*(Mtx*)particleData, drawMtx, tempMtx);
            PSMTXConcat(ppvCameraMatrix02, tempMtx, tempMtx);
            PSMTXConcat(ppvCameraMatrix02, *(Mtx*)particleData, drawMtx);
            PSMTXMultVec(drawMtx, (Vec*)(particleData + 0xC), &pos);
            tempMtx[0][3] = pos.x;
            tempMtx[1][3] = pos.y;
            tempMtx[2][3] = pos.z;
            GXLoadPosMtxImm(tempMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((float)(int)colorA - particleData[0x22]);

            if (particleColor != NULL) {
                r += (int)particleColor[0];
                g += (int)particleColor[1];
                b += (int)particleColor[2];
                a += (int)particleColor[3];
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
            pppDrawMesh__FP10pppModelStP3Veci(model, breathModel->m_modelVertices, 1);
        }

        if (matrixList != NULL) {
            matrixList++;
        }
        if (particleColor != NULL) {
            particleColor += 8;
        }
        particleData += 0x26;
    }

    if ((*(u32*)(CFlat + 0x129C) & 0x200000) != 0) {
        for (i = 0; i < (int)pBreathModel->m_groupCount; i++) {
            if (groupData[0] == 1) {
                _GXColor debugColor;
                int firstParticle;
                int j;
                float groupScale;
                Mtx sphereMtx;
                Mtx tempMtx;
                Vec pos;

                if (i == 2) {
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                } else if (i < 2) {
                    if (i == 0) {
                        debugColor.r = 0x80;
                        debugColor.g = 0x00;
                        debugColor.b = 0x00;
                        debugColor.a = 0xFF;
                    } else if (i < 0) {
                        debugColor.r = 0x00;
                        debugColor.g = 0x60;
                        debugColor.b = 0x80;
                        debugColor.a = 0xFF;
                    } else {
                        debugColor.r = 0x80;
                        debugColor.g = 0x80;
                        debugColor.b = 0xFF;
                        debugColor.a = 0xFF;
                    }
                } else if (i < 4) {
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                } else {
                    debugColor.r = 0x00;
                    debugColor.g = 0x60;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                }

                firstParticle = -1;
                groupScale = *(float*)(groupData + 10);
                for (j = 0; j < (int)pBreathModel->m_slotCount; j++) {
                    if (*(signed char*)(groupData[2] + j) != -1) {
                        firstParticle = (int)*(signed char*)(groupData[1] + j);
                        break;
                    }
                }

                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = groupScale;
                sphereMtx[1][1] = groupScale;
                sphereMtx[2][2] = groupScale;
                PSMTXConcat(work->m_particleWmats[firstParticle], breathModel->m_localMatrix, tempMtx);
                PSMTXConcat(ppvCameraMatrix02, tempMtx, tempMtx);
                PSMTXMultVec(tempMtx, (Vec*)(groupData + 3), &pos);
                sphereMtx[0][3] = pos.x;
                sphereMtx[1][3] = pos.y;
                sphereMtx[2][3] = pos.z;

                pppSetBlendMode(1);
                DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic, sphereMtx, debugColor);
            }
            groupData += 0x17;
        }

        pppInitBlendMode();
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 2);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800db6e0
 * PAL Size: 1264b
 */
extern "C" void pppFrameBreathModel(pppBreathModel* breathModel, PBreathModel* pBreathModel, pppBreathModelUnkC* offsets)
{
    int colorOffset;
    int* dataOffsets;
    VBreathModel* work;
    VColor* color;
    int* groupData;
    Mtx* particleWMat;
    Mtx* particleMtx;
    int i;
    int groupIndex;
    int firstParticle;
    int groupTable;
    int slotIndex;
    unsigned int slotCount;
    bool ready;
    float scaledOwner;
    Mtx scaleMtx;
    Mtx worldMtx;
    pppFMATRIX rotMtx;
    Vec origin;
    Vec dir;
    Vec dirNorm;
    Vec target;
    Vec hitVector;

    if (gPppCalcDisabled != 0) {
        return;
    }

    dataOffsets = offsets->m_serializedDataOffsets;
    _pppMngSt* mngSt = pppMngStPtr;
    colorOffset = dataOffsets[1];
    work = reinterpret_cast<VBreathModel*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + dataOffsets[0]);
    color = (VColor*)(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);

    if (work->m_particleData == NULL) {
        int* groupTable;

        work->m_particleCount = pBreathModel->m_particleCount;
        work->m_slotCount = pBreathModel->m_slotCount;
        work->m_groupCount = pBreathModel->m_groupCount;

        work->m_particleData =
            (PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount * 0x98), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x257);
        if (work->m_particleData != NULL) {
            memset(work->m_particleData, 0, (unsigned long)(work->m_particleCount * 0x98));
        }

        work->m_particleWmats =
            (PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount * 0x30), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x25d);
        if (work->m_particleWmats != NULL) {
            memset(work->m_particleWmats, 0, (unsigned long)(work->m_particleCount * 0x30));
        }

        work->m_particleColors =
            (PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount << 5), pppEnvStPtr->m_stagePtr,
                                                  const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x263);
        if (work->m_particleColors != NULL) {
            memset(work->m_particleColors, 0, (unsigned long)(work->m_particleCount << 5));
        }

        work->m_groups =
            (BreathParticleGroup*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)((int)pBreathModel->m_groupCount * 0x5C),
                pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x269);
        if (work->m_groups != NULL) {
            memset(work->m_groups, 0, (unsigned long)((int)pBreathModel->m_groupCount * 0x5C));

            groupTable = (int*)work->m_groups;
            for (i = 0; i < (int)pBreathModel->m_groupCount; i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)pBreathModel->m_slotCount,
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x274);
                void* particleIndices = (void*)groupTable[1];
                memset(particleIndices, -1, (unsigned long)pBreathModel->m_slotCount);

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)pBreathModel->m_slotCount,
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x277);
                void* particleStates = (void*)groupTable[2];
                memset(particleStates, -1, (unsigned long)pBreathModel->m_slotCount);
                groupTable[0] = 0;
                groupTable += 0x17;
            }
        }

        work->m_direction.x = kPppBreathModelZero;
        work->m_direction.y = kPppBreathModelZero;
        work->m_direction.z = FLOAT_80330F80;
        PSVECNormalize(&work->m_direction, &work->m_direction);
    }

    PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_matrix);
    UpdateAllParticle(reinterpret_cast<_pppPObject*>(breathModel), work, pBreathModel, color);

    particleWMat = work->m_particleWmats;
    groupData = (int*)work->m_groups;
    for (groupIndex = 0; groupIndex < (int)pBreathModel->m_groupCount; groupIndex++) {
        slotCount = pBreathModel->m_slotCount;
        groupTable = (int)groupData;
        for (slotIndex = 0; slotIndex < (int)slotCount; slotIndex++) {
            if ((*(signed char*)(*(int*)(groupTable + 4) + slotIndex) == -1) ||
                (*(signed char*)(*(int*)(groupTable + 8) + slotIndex) != 1)) {
                ready = false;
                goto group_ready;
            }
        }
        ready = true;
group_ready:
        if (ready) {
            firstParticle = -1;
            scaledOwner = mngSt->m_previousPosition.z * pBreathModel->m_groupOwnerScale;
            for (slotIndex = 0; slotCount != 0; slotCount--) {
                if (*(signed char*)(*(int*)(groupTable + 8) + slotIndex) != -1) {
                    firstParticle = (int)*(signed char*)(*(int*)(groupTable + 4) + slotIndex);
                    break;
                }
                slotIndex++;
            }

            PSMTXIdentity(scaleMtx);
            scaleMtx[0][0] = scaledOwner;
            scaleMtx[1][1] = scaledOwner;
            scaleMtx[2][2] = scaledOwner;
            particleMtx = (Mtx*)((unsigned char*)particleWMat + firstParticle * 0x30);
            PSMTXConcat(*particleMtx, breathModel->m_localMatrix, worldMtx);
            PSMTXMultVec(worldMtx, (Vec*)(groupTable + 0xC), &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = kPppBreathModelZero;
            rotMtx.value[1][3] = kPppBreathModelZero;
            rotMtx.value[2][3] = kPppBreathModelZero;
            *(float*)(groupTable + 0x28) = scaledOwner;
            pppCopyVector(dir, *(Vec*)(groupTable + 0x18));
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppCopyVector(dirNorm, dir);
            pppNormalize__FR3Vec3Vec(reinterpret_cast<float*>(&dir), &dirNorm);
            PSVECScale(&dir, &target, *(float*)(groupTable + 0x24));
            pppAddVector(target, origin, target);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(mngSt, &origin, &hitVector, scaledOwner, pBreathModel->m_groupRadius);
        }

        groupData += 0x17;
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
    int found;
    int spawnCount;
    int i;
    int j;
    int k;
    int group;
    int groupTableWork;
    BreathParticleGroup* groupTable;
    BreathParticleGroup* groupData;
    unsigned char* particleData;
    unsigned char* particleWmat;
    unsigned char* particleColor;
    int maxParticleCount;
    short foundSlot;
    short foundGroup;
    Vec stepVelocity;
    Vec unitVelocity;
    unsigned short* emitFrameCounter;

    spawnCount = 0;
    particleData = (unsigned char*)vBreathModel->m_particleData;
    particleWmat = (unsigned char*)vBreathModel->m_particleWmats;
    particleColor = (unsigned char*)vBreathModel->m_particleColors;
    groupTable = vBreathModel->m_groups;
    maxParticleCount = vBreathModel->m_particleCount;
    emitFrameCounter = &vBreathModel->m_emitFrameCounter;

    if ((gPppCalcDisabled == 0) && (params->m_stepValue != 0xFFFF)) {
        *emitFrameCounter = *emitFrameCounter + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (*(short*)(particleData + 0x50) > 0) {
                UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR(
                    vBreathModel, pBreathModel, (PARTICLE_DATA*)particleData, vColor, (PARTICLE_COLOR*)particleColor);
            } else {
                float zero = kPppBreathModelZero;

                groupTableWork = (int)vBreathModel->m_groups;
                foundGroup = -1;
                foundSlot = -1;
                for (short groupIndex = 0; groupIndex < (int)params->m_groupCount; groupIndex++) {
                    for (short slotIndex = 0; slotIndex < (int)params->m_slotCount; slotIndex++) {
                        if ((int)(short)i == (int)*(signed char*)(*(int*)(groupTableWork + 4) + (int)slotIndex)) {
                            foundGroup = groupIndex;
                            foundSlot = slotIndex;
                            found = true;
                            goto found_index;
                        }
                    }
                    groupTableWork += 0x5C;
                }
                found = false;

            found_index:
                if (found) {
                    groupTable[(int)foundGroup].particleIndices[(int)foundSlot] = -1;
                }

                if ((int)foundGroup != -1) {
                    int slot;

                    slot = 0;
                    group = (int)vBreathModel->m_groups + (int)foundGroup * 0x5C;
                    for (slot = 0; slot < (int)params->m_slotCount; slot++) {
                        if ((*(signed char*)(*(int*)(group + 4) + slot) != -1) ||
                            (*(signed char*)(*(int*)(group + 8) + slot) != 1)) {
                            found = false;
                            goto group_checked;
                        }
                    }
                    found = true;

                group_checked:
                    if (found) {
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
                    BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR(
                        pppObject, vBreathModel, pBreathModel, vColor, (PARTICLE_DATA*)particleData,
                        (PARTICLE_WMAT*)particleWmat, (PARTICLE_COLOR*)particleColor);
                    found = true;
                    spawnCount += 1;
                    groupData = groupTable;
                    for (j = 0; j < (int)params->m_groupCount; j++) {
                        for (k = 0; k < (int)params->m_slotCount; k++) {
                            if ((groupData->particleIndices[k] == -1) && (groupData->particleStates[k] == -1)) {
                                groupData->particleIndices[k] = (signed char)i;
                                found = false;
                                groupData->particleStates[k] = 1;
                            }
                            if (!found) {
                                break;
                            }
                        }
                        if (!found) {
                            break;
                        }
                        groupData += 1;
                    }
                }
            }

            if (particleWmat != NULL) {
                particleWmat += 0x30;
            }
            if (particleColor != NULL) {
                particleColor += 0x20;
            }
            particleData += 0x98;
        }

        if (spawnCount > 0) {
            *emitFrameCounter = 0;
        }

        groupData = groupTable;
        for (i = 0; i < (int)params->m_groupCount; i++) {
            if ((groupData->active != 1) && (*groupData->particleIndices != -1) && (*groupData->particleStates == 1)) {
                unitVelocity.x = kPppBreathModelZero;
                unitVelocity.y = kPppBreathModelZero;
                unitVelocity.z = FLOAT_80330F80;
                groupData->speed = params->m_groupSpeed;
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.z = kPppBreathModelZero;
                groupData->position.y = kPppBreathModelZero;
                groupData->position.x = kPppBreathModelZero;
                PSMTXCopy(*(Mtx*)pppMngStPtr, groupData->matrix);
                groupData->active = 1;
            }
            groupData += 1;
        }

        for (i = 0; i < (int)params->m_groupCount; i++) {
            if (groupTable->active != 0) {
                PSVECScale(&groupTable->direction, &stepVelocity, groupTable->speed);
                PSVECAdd(&stepVelocity, &groupTable->position, &groupTable->position);
            }
            groupTable += 1;
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
extern "C" void UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR(
    VBreathModel*, PBreathModel* pBreathModel, PARTICLE_DATA* particleData, VColor* vColor, PARTICLE_COLOR* particleColor)
{
    PBreathModel* params = reinterpret_cast<PBreathModel*>(pBreathModel);
    BreathParticleData* particle = reinterpret_cast<BreathParticleData*>(particleData);
    int alpha = vColor->m_alpha;
    char frameCount;
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

    while (FLOAT_80330F88 <= particle->m_angle) {
        particle->m_angle -= FLOAT_80330F84;
    }
    while (particle->m_angle < FLOAT_80330F8C) {
        particle->m_angle += FLOAT_80330F84;
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
    unsigned char clampScale = params->m_disableScaleClamp;
    if (clampScale == 0) {
        float zero = kPppBreathModelZero;
        if (zero < params->m_scaleClampStart) {
            if (params->m_scaleAccel < zero) {
                if (particle->m_scale < zero) {
                    particle->m_scale = zero;
                }
            }
        } else if (params->m_scaleClampStart < zero) {
            if ((zero < params->m_scaleAccel) && (zero < particle->m_scale)) {
                particle->m_scale = zero;
            }
        }
    }

    PSVECScale(&particle->m_direction, &step, particle->m_scale);
    PSVECAdd(&step, &particle->m_position, &particle->m_position);

    unsigned short life = params->m_particleLifetime;
    if (life != 0) {
        particle->m_life = particle->m_life - 1;
    }
    particle->m_age = particle->m_age + 1;

    frameCount = particle->m_fadeOutFrames;
    if ((frameCount != '\0') && ((int)(unsigned int)particle->m_age <= (int)frameCount)) {
        particle->m_alpha -= (float)alpha / (float)(int)frameCount;
    }

    frameCount = particle->m_fadeInFrames;
    if ((frameCount != '\0') && ((int)particle->m_life <= (int)frameCount)) {
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
extern "C" void BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR(
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
            if (DOUBLE_80330F98 < Math.RandF()) {
                particle->m_angleRandom *= FLOAT_80330F80;
            }
        } else if (params->m_angleFlags & 2) {
            particle->m_angleRandom *= FLOAT_80330F80;
        }
    }

    if ((params->m_angleFlags & 4) != 0) {
        particle->m_angle += particle->m_angleRandom;
    }
    if ((params->m_angleFlags & 8) != 0) {
        particle->m_angleVelocity += particle->m_angleRandom;
    }

    while (FLOAT_80330F88 <= particle->m_angle) {
        particle->m_angle -= FLOAT_80330F84;
    }
    while (particle->m_angle < FLOAT_80330F8C) {
        particle->m_angle += FLOAT_80330F84;
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
                if (DOUBLE_80330F98 < Math.RandF()) {
                    particle->m_rotationAccelX *= FLOAT_80330F80;
                    particle->m_rotationAccelY *= FLOAT_80330F80;
                    particle->m_rotationAccelZ *= FLOAT_80330F80;
                }
            } else if (params->m_rotationFlags & 2) {
                particle->m_rotationAccelX *= FLOAT_80330F80;
                particle->m_rotationAccelY *= FLOAT_80330F80;
                particle->m_rotationAccelZ *= FLOAT_80330F80;
            }
        } else {
            particle->m_rotationAccelX = params->m_rotationRandomX * Math.RandF();
            particle->m_rotationAccelY = params->m_rotationRandomY * Math.RandF();
            particle->m_rotationAccelZ = params->m_rotationRandomZ * Math.RandF();
            if ((params->m_rotationFlags & 1) && (params->m_rotationFlags & 2)) {
                if (DOUBLE_80330F98 < Math.RandF()) {
                    particle->m_rotationAccelX *= FLOAT_80330F80;
                }
                if (DOUBLE_80330F98 < Math.RandF()) {
                    particle->m_rotationAccelY *= FLOAT_80330F80;
                }
                if (DOUBLE_80330F98 < Math.RandF()) {
                    particle->m_rotationAccelZ *= FLOAT_80330F80;
                }
            } else if (params->m_rotationFlags & 2) {
                particle->m_rotationAccelX *= FLOAT_80330F80;
                particle->m_rotationAccelY *= FLOAT_80330F80;
                particle->m_rotationAccelZ *= FLOAT_80330F80;
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
    if (params->m_scaleRandomRange != kPppBreathModelZero) {
        float rand = Math.RandF();
        float scaledRange = FLOAT_80330FA0 * params->m_scaleRandomRange;
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
    workMtx[0][3] = kPppBreathModelZero;
    workMtx[1][3] = kPppBreathModelZero;
    workMtx[2][3] = kPppBreathModelZero;

    particle->m_direction.x = kPppBreathModelZero;
    particle->m_direction.y = kPppBreathModelZero;
    particle->m_direction.z = FLOAT_80330F80;
    PSMTXMultVec(workMtx, &particle->m_direction, &particle->m_direction);
    PSVECNormalize(&particle->m_direction, &particle->m_direction);

    const float& half = FLOAT_80330FA4;
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

    PSMTXConcat(*(Mtx*)particleWmat, reinterpret_cast<pppBreathModelPObject*>(pppObject)->m_localMatrix,
                *(Mtx*)particleData);
    PSMTXConcat(ppvCameraMatrix02, *(Mtx*)particleData, cameraMtx);

    particle->m_direction.x = kPppBreathModelZero;
    particle->m_direction.y = kPppBreathModelZero;
    particle->m_direction.z = FLOAT_80330F80;
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
    float zero = kPppBreathModelZero;
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
