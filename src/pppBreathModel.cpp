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
    unsigned char _pad[8];
};

struct BreathParticleGroup {
    int active;
    signed char* particleIndices;
    unsigned char* particleStates;
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

struct BreathModelRenderStep {
    int m_graphId;
    int m_dataValIndex;
    int m_initWork;
    int m_stepValue;
    union {
        int m_arg3;
        struct {
            u16 m_slotCount;
            u16 m_groupCount;
        } m_groupInfo;
    };
    unsigned char m_payload[1];
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
    float zero;

    PSMTXIdentity(state->m_matrix);
    zero = 0.0f;

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
    _pppPObject* object;
    BreathModelRenderStep* step;
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

    object = reinterpret_cast<_pppPObject*>(breathModel);
    step = (BreathModelRenderStep*)pBreathModel;
    workOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    work = reinterpret_cast<VBreathModel*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + workOffset);
    color = reinterpret_cast<VColor*>(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);
    particleData = reinterpret_cast<float*>(work->m_particleData);
    matrixList = work->m_particleWmats;
    particleColor = reinterpret_cast<float*>(work->m_particleColors);
    groupData = reinterpret_cast<int*>(work->m_groups);
    groupCount = work->m_particleCount;

    if (step->m_stepValue == 0xFFFF) {
        return;
    }

    model = (pppModelSt*)(*(void***)((u8*)pppEnvStPtr + 8))[step->m_stepValue];
    pppInitBlendMode();
    pppSetBlendMode(step->m_payload[4]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(NULL, NULL, *(float*)(step->m_payload + 0xB0), step->m_payload[0xB6],
                                                               step->m_payload[0xB5], step->m_payload[4], step->m_payload[0xB7],
                                                               step->m_payload[0xB8], 1, step->m_payload[0xB9]);

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
            pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((unsigned char*)breathModel + 0x70), 1);
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
        for (i = 0; i < (int)step->m_groupInfo.m_groupCount; i++) {
            if (groupData[0] == 1) {
                _GXColor debugColor;
                int firstParticle;
                int j;
                float groupScale;
                Mtx sphereMtx;
                Mtx tempMtx;
                Vec pos;

                if (i != 2) {
                    if (i >= 2) {
                        if (i >= 4) {
                            debugColor.r = 0x00;
                            debugColor.g = 0x60;
                            debugColor.b = 0x80;
                            debugColor.a = 0xFF;
                        } else {
                            debugColor.r = 0x80;
                            debugColor.g = 0x80;
                            debugColor.b = 0x80;
                            debugColor.a = 0xFF;
                        }
                    } else if (i == 0) {
                        debugColor.r = 0x80;
                        debugColor.g = 0x00;
                        debugColor.b = 0x00;
                        debugColor.a = 0xFF;
                    } else if (i >= 0) {
                        debugColor.r = 0x80;
                        debugColor.g = 0x80;
                        debugColor.b = 0xFF;
                        debugColor.a = 0xFF;
                    } else {
                        debugColor.r = 0x00;
                        debugColor.g = 0x60;
                        debugColor.b = 0x80;
                        debugColor.a = 0xFF;
                    }
                } else {
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                }

                firstParticle = -1;
                groupScale = *(float*)(groupData + 10);
                for (j = 0; j < (int)step->m_groupInfo.m_slotCount; j++) {
                    if (*(signed char*)(groupData[2] + j) != -1) {
                        firstParticle = (int)*(signed char*)(groupData[1] + j);
                        break;
                    }
                }

                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = groupScale;
                sphereMtx[1][1] = groupScale;
                sphereMtx[2][2] = groupScale;
                PSMTXConcat(work->m_particleWmats[firstParticle], object->m_localMatrix.value, tempMtx);
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

        work->m_particleCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x1A);
        work->m_slotCount = *(unsigned short*)((unsigned char*)pBreathModel + 0x10);
        work->m_groupCount = *(unsigned short*)((unsigned char*)pBreathModel + 0x12);

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
                (unsigned long)((int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12) * 0x5C),
                pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x269);
        if (work->m_groups != NULL) {
            memset(work->m_groups, 0,
                   (unsigned long)((int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12) * 0x5C));

            groupTable = (int*)work->m_groups;
            for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12); i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10),
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x274);
                void* particleIndices = (void*)groupTable[1];
                memset(particleIndices, -1,
                       (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10));

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10),
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBreathModel_cpp_801DB5A0), 0x277);
                void* particleStates = (void*)groupTable[2];
                memset(particleStates, -1,
                       (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10));
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
    for (groupIndex = 0; groupIndex < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
        groupIndex++) {
        slotCount = (unsigned int)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
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
            scaledOwner = mngSt->m_previousPositionFields.m_paramD * *(float*)((unsigned char*)pBreathModel + 8);
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
            PSMTXConcat(*particleMtx, reinterpret_cast<_pppPObject*>(breathModel)->m_localMatrix.value, worldMtx);
            PSMTXMultVec(worldMtx, (Vec*)(groupTable + 0xC), &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = kPppBreathModelZero;
            rotMtx.value[1][3] = kPppBreathModelZero;
            rotMtx.value[2][3] = kPppBreathModelZero;
            *(float*)(groupTable + 0x28) = scaledOwner;
            pppCopyVector(dir, *(Vec*)(groupTable + 0x18));
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppNormalize__FR3Vec3Vec(reinterpret_cast<float*>(&dir), &dirNorm);
            PSVECScale(&dirNorm, &target, *(float*)(groupTable + 0x24));
            pppAddVector(target, origin, target);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(mngSt, &origin, &hitVector, scaledOwner,
                                     *(float*)((unsigned char*)pBreathModel + 4));
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
    bool found;
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
    particleData = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x30);
    particleWmat = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x34);
    particleColor = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x38);
    groupTable = *(BreathParticleGroup**)((unsigned char*)vBreathModel + 0x3C);
    maxParticleCount = *(int*)((unsigned char*)vBreathModel + 0x40);
    emitFrameCounter = (unsigned short*)((unsigned char*)vBreathModel + 0x44);

    if ((gPppCalcDisabled == 0) && (*(int*)((unsigned char*)pBreathModel + 0xC) != 0xFFFF)) {
        *emitFrameCounter = *emitFrameCounter + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (*(short*)(particleData + 0x50) >= 1) {
                UpdateParticle__FP12VBreathModelP12PBreathModelP13PARTICLE_DATAP6VColorP14PARTICLE_COLOR(
                    vBreathModel, pBreathModel, (PARTICLE_DATA*)particleData, vColor, (PARTICLE_COLOR*)particleColor);
            } else {
                float zero = kPppBreathModelZero;

                groupTableWork = *(int*)((unsigned char*)vBreathModel + 0x3C);
                for (foundGroup = 0;
                     foundGroup < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
                     foundGroup++) {
                    for (foundSlot = 0;
                         foundSlot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
                         foundSlot++) {
                        if ((int)(short)i == (int)*(signed char*)(*(int*)(groupTableWork + 4) + (int)foundSlot)) {
                            found = true;
                            goto found_index;
                        }
                    }
                    groupTableWork += 0x5C;
                }
                found = false;
                foundSlot = -1;
                foundGroup = -1;

            found_index:
                if (found) {
                    groupTable[(int)foundGroup].particleIndices[(int)foundSlot] = -1;
                }

                if ((int)foundGroup != -1) {
                    int slot;
                    unsigned int slotCount;

                    slot = 0;
                    group = *(int*)((unsigned char*)vBreathModel + 0x3C) + (int)foundGroup * 0x5C;
                    slotCount = *(unsigned short*)((unsigned char*)pBreathModel + 0x10);
                    while (slotCount != 0) {
                        if ((*(signed char*)(*(int*)(group + 4) + slot) != -1) ||
                            (*(signed char*)(*(int*)(group + 8) + slot) != 1)) {
                            found = false;
                            goto group_checked;
                        }
                        slot++;
                        slotCount--;
                    }
                    found = true;

                group_checked:
                    if (found) {
                        groupData = &groupTable[(int)foundGroup];
                        for (slot = 0; slot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10); slot++) {
                            groupData->particleStates[slot] = 0xFF;
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

                if ((*(unsigned short*)((unsigned char*)pBreathModel + 0x1E) <= *emitFrameCounter) &&
                    (spawnCount < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x1C))) {
                    BirthParticle__FP11_pppPObjectP12VBreathModelP12PBreathModelP6VColorP13PARTICLE_DATAP13PARTICLE_WMATP14PARTICLE_COLOR(
                        pppObject, vBreathModel, pBreathModel, vColor, (PARTICLE_DATA*)particleData,
                        (PARTICLE_WMAT*)particleWmat, (PARTICLE_COLOR*)particleColor);
                    found = true;
                    spawnCount += 1;
                    groupData = groupTable;
                    for (j = 0; j < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12); j++) {
                        for (k = 0; k < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10); k++) {
                            if ((groupData->particleIndices[k] == -1) && (groupData->particleStates[k] == 0xFF)) {
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
        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12); i++) {
            if ((groupData->active != 1) && (*groupData->particleIndices != -1) && (*groupData->particleStates == 1)) {
                unitVelocity.x = kPppBreathModelZero;
                unitVelocity.y = kPppBreathModelZero;
                unitVelocity.z = FLOAT_80330F80;
                groupData->speed = *(float*)((unsigned char*)pBreathModel + 0x14);
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.x = 0.0f;
                groupData->position.y = 0.0f;
                groupData->position.z = 0.0f;
                PSMTXCopy(*(Mtx*)pppMngStPtr, groupData->matrix);
                groupData->active = 1;
            }
            groupData += 1;
        }

        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12); i++) {
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
    unsigned char* breath = (unsigned char*)pBreathModel;
    Vec* particle = reinterpret_cast<Vec*>(particleData);
    int alpha = vColor->m_alpha;
    char frameCount;
    Vec step;

    if (particleColor != NULL) {
        particleColor->m_color[0] += particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] += particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] += particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] += particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] += *(float*)(breath + 0x38);
        particleColor->m_colorFrameDeltas[1] += *(float*)(breath + 0x3C);
        particleColor->m_colorFrameDeltas[2] += *(float*)(breath + 0x40);
        particleColor->m_colorFrameDeltas[3] += *(float*)(breath + 0x44);
        alpha = (int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    particle[7].y += particle[7].z;
    if (*(unsigned char*)(breath + 0xC1) & 0x10) {
        particle[7].z = *(float*)(breath + 0x98) + particle[8].x + particle[7].z;
    } else {
        particle[7].z += *(float*)(breath + 0x98);
    }

    while (FLOAT_80330F88 <= particle[7].y) {
        particle[7].y -= FLOAT_80330F84;
    }
    while (particle[7].y < FLOAT_80330F8C) {
        particle[7].y += FLOAT_80330F84;
    }

    particle[8].y += particle[9].y;
    particle[8].z += particle[9].z;
    particle[9].x += particle[10].x;

    if (*(unsigned char*)(breath + 0xC0) & 0x10) {
        particle[9].y = *(float*)(breath + 0x70) + particle[10].y + particle[9].y;
        particle[9].z = *(float*)(breath + 0x74) + particle[10].z + particle[9].z;
        particle[10].x = *(float*)(breath + 0x78) + particle[11].x + particle[10].x;
    } else {
        particle[9].y += *(float*)(breath + 0x70);
        particle[9].z += *(float*)(breath + 0x74);
        particle[10].x += *(float*)(breath + 0x78);
    }

    particle[11].z += *(float*)(breath + 0xA4);
    unsigned char clampScale = *(unsigned char*)(breath + 0xC8);
    if (clampScale == 0) {
        float zero = kPppBreathModelZero;
        float start = *(float*)(breath + 0xA0);
        if (zero < start) {
            if (*(float*)(breath + 0xA4) < zero) {
                if (particle[11].z < zero) {
                    particle[11].z = zero;
                }
            }
        } else if (start < zero) {
            if ((zero < *(float*)(breath + 0xA4)) && (zero < particle[11].z)) {
                particle[11].z = zero;
            }
        }
    }

    PSVECScale(&particle[5], &step, particle[11].z);
    PSVECAdd(&step, &particle[4], &particle[4]);

    unsigned short life = *(unsigned short*)(breath + 0x20);
    if (life != 0) {
        *(short*)&particle[6].z = *(short*)&particle[6].z - 1;
    }
    *(char*)&particle[12].x = *(char*)&particle[12].x + 1;

    frameCount = *(char*)&particle[7].x;
    if ((frameCount != '\0') && ((int)(unsigned int)*(unsigned char*)&particle[12].x <= (int)frameCount)) {
        *(float*)&particle[11].y -= (float)alpha / (float)(int)frameCount;
    }

    frameCount = *(char*)((unsigned char*)&particle[7].x + 1);
    if ((frameCount != '\0') && ((int)*(short*)&particle[6].z <= (int)frameCount)) {
        *(float*)&particle[11].y += (float)alpha / (float)(unsigned int)*(unsigned char*)(breath + 0x23);
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
    unsigned char* breath = (unsigned char*)pBreathModel;
    unsigned char* particle = (unsigned char*)particleData;
    Mtx workMtx;
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

    if (*(unsigned char*)(breath + 0x22) != 0) {
        *(float*)(particle + 0x88) = (float)(unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
        *(unsigned char*)(particle + 0x54) = *(unsigned char*)(breath + 0x22);
    }
    if (*(unsigned char*)(breath + 0x23) != 0) {
        *(unsigned char*)(particle + 0x55) = *(unsigned char*)(breath + 0x23);
    }

    *(float*)(particle + 0x58) = *(float*)(breath + 0x90);
    *(float*)(particle + 0x5C) = *(float*)(breath + 0x94);
    if (*(unsigned char*)(breath + 0xC1) != 0) {
        unsigned char flags = *(unsigned char*)(breath + 0xC1);

        *(float*)(particle + 0x60) = *(float*)(breath + 0x9C) * Math.RandF();
        if ((flags & 1) && (flags & 2)) {
            if (Math.RandF() > 0.5f) {
                *(float*)(particle + 0x60) *= FLOAT_80330F80;
            }
        } else if (flags & 2) {
            *(float*)(particle + 0x60) *= FLOAT_80330F80;
        }
    }

    if ((*(unsigned char*)(breath + 0xC1) & 4) != 0) {
        *(float*)(particle + 0x58) += *(float*)(particle + 0x60);
    }
    if ((*(unsigned char*)(breath + 0xC1) & 8) != 0) {
        *(float*)(particle + 0x5C) += *(float*)(particle + 0x60);
    }

    while (*(float*)(particle + 0x58) >= FLOAT_80330F88) {
        *(float*)(particle + 0x58) -= FLOAT_80330F84;
    }
    while (*(float*)(particle + 0x58) < FLOAT_80330F8C) {
        *(float*)(particle + 0x58) += FLOAT_80330F84;
    }

    *(float*)(particle + 0x64) = *(float*)(breath + 0x50);
    *(float*)(particle + 0x68) = *(float*)(breath + 0x54);
    *(float*)(particle + 0x6C) = *(float*)(breath + 0x58);
    *(float*)(particle + 0x70) = *(float*)(breath + 0x60);
    *(float*)(particle + 0x74) = *(float*)(breath + 0x64);
    *(float*)(particle + 0x78) = *(float*)(breath + 0x68);

    if (*(unsigned char*)(breath + 0xC0) != 0) {
        unsigned char flags = *(unsigned char*)(breath + 0xC0);

        if ((flags & 0x20) == 0) {
            *(float*)(particle + 0x7C) = *(float*)(breath + 0x80) * Math.RandF();
            *(float*)(particle + 0x80) = *(float*)(breath + 0x84) * Math.RandF();
            *(float*)(particle + 0x84) = *(float*)(breath + 0x88) * Math.RandF();
            if ((flags & 1) && (flags & 2)) {
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                }
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x80) *= FLOAT_80330F80;
                }
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x84) *= FLOAT_80330F80;
                }
            } else if (flags & 2) {
                *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                *(float*)(particle + 0x80) *= FLOAT_80330F80;
                *(float*)(particle + 0x84) *= FLOAT_80330F80;
            }
        } else {
            float value = *(float*)(breath + 0x80) * Math.RandF();

            *(float*)(particle + 0x7C) = value;
            *(float*)(particle + 0x80) = value;
            *(float*)(particle + 0x84) = value;
            if ((flags & 1) && (flags & 2)) {
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                    *(float*)(particle + 0x80) *= FLOAT_80330F80;
                    *(float*)(particle + 0x84) *= FLOAT_80330F80;
                }
            } else if (flags & 2) {
                *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                *(float*)(particle + 0x80) *= FLOAT_80330F80;
                *(float*)(particle + 0x84) *= FLOAT_80330F80;
            }
        }
    }

    if ((*(unsigned char*)(breath + 0xC0) & 4) != 0) {
        *(float*)(particle + 0x64) += *(float*)(particle + 0x7C);
        *(float*)(particle + 0x68) += *(float*)(particle + 0x80);
        *(float*)(particle + 0x6C) += *(float*)(particle + 0x84);
    }
    if ((*(unsigned char*)(breath + 0xC0) & 8) != 0) {
        *(float*)(particle + 0x70) += *(float*)(particle + 0x7C);
        *(float*)(particle + 0x74) += *(float*)(particle + 0x80);
        *(float*)(particle + 0x78) += *(float*)(particle + 0x84);
    }

    *(float*)(particle + 0x8C) = *(float*)(breath + 0x14);
    if (*(float*)(breath + 0xA8) != kPppBreathModelZero) {
        *(float*)(particle + 0x8C) += (2.0f * *(float*)(breath + 0xA8)) * Math.RandF() - *(float*)(breath + 0xA8);
    }

    if (*(short*)(breath + 0x20) == 0) {
        *(short*)(particle + 0x50) = -1;
    } else {
        *(short*)(particle + 0x50) = *(short*)(breath + 0x20);
    }
    *(unsigned char*)(particle + 0x90) = 0;

    PSMTXCopy(*(Mtx*)vBreathModel, *(Mtx*)particleWmat);
    if (particleColor != NULL) {
        *(u32*)((unsigned char*)particleColor + 0x10) = *(u32*)(breath + 0x28);
        *(u32*)((unsigned char*)particleColor + 0x14) = *(u32*)(breath + 0x2C);
        *(u32*)((unsigned char*)particleColor + 0x18) = *(u32*)(breath + 0x30);
        *(u32*)((unsigned char*)particleColor + 0x1C) = *(u32*)(breath + 0x34);
    }

    PSMTXCopy(*(Mtx*)particleWmat, workMtx);
    workMtx[0][3] = kPppBreathModelZero;
    workMtx[1][3] = kPppBreathModelZero;
    workMtx[2][3] = kPppBreathModelZero;

    *(float*)(particle + 0x3C) = kPppBreathModelZero;
    *(float*)(particle + 0x40) = kPppBreathModelZero;
    *(float*)(particle + 0x44) = FLOAT_80330F80;
    PSMTXMultVec(workMtx, (Vec*)(particle + 0x3C), (Vec*)(particle + 0x3C));
    PSVECNormalize((Vec*)(particle + 0x3C), (Vec*)(particle + 0x3C));

    jitter.x = -(*(float*)(breath + 0xB0) * 0.5f - Math.RandF(*(float*)(breath + 0xB0)));
    jitter.y = -(*(float*)(breath + 0xB4) * 0.5f - Math.RandF(*(float*)(breath + 0xB4)));
    jitter.z = -(*(float*)(breath + 0xB8) * 0.5f - Math.RandF(*(float*)(breath + 0xB8)));

    pos.x = (*(Mtx*)particleWmat)[0][3];
    pos.y = (*(Mtx*)particleWmat)[1][3];
    pos.z = (*(Mtx*)particleWmat)[2][3];
    PSVECAdd(&jitter, &pos, &pos);
    (*(Mtx*)particleWmat)[0][3] = pos.x;
    (*(Mtx*)particleWmat)[1][3] = pos.y;
    (*(Mtx*)particleWmat)[2][3] = pos.z;

    PSMTXConcat(*(Mtx*)particleWmat, *(Mtx*)((unsigned char*)pppObject + 4), *(Mtx*)particleData);
    PSMTXConcat(ppvCameraMatrix02, *(Mtx*)particleData, workMtx);

    *(float*)(particle + 0x3C) = kPppBreathModelZero;
    *(float*)(particle + 0x40) = kPppBreathModelZero;
    *(float*)(particle + 0x44) = FLOAT_80330F80;
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

    for (i = 0; i < *(unsigned short*)((unsigned char*)pBreathModel + 0x10); i++) {
        if ((groupData->particleIndices[i] != -1) || (groupData->particleStates[i] != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < *(unsigned short*)((unsigned char*)pBreathModel + 0x10); i++) {
            groupData->particleStates[i] = 0xFF;
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

    for (g = 0; g < *(unsigned short*)((unsigned char*)pBreathModel + 0x12); g++) {
        for (s = 0; s < *(unsigned short*)((unsigned char*)pBreathModel + 0x10); s++) {
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
