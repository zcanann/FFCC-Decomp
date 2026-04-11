#include "ffcc/pppBreathModel.h"
#include "ffcc/linkage.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "ffcc/math.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/pppPart.h"
#include <string.h>

const float FLOAT_80330F80 = -1.0f;

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

static char s_pppBreathModel_cpp[] = "pppBreathModel.cpp";

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
    Mtx matrix;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_rand()
{
	// TODO
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
void BirthParticle(_pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, 
                   VColor* vColor, _PARTICLE_DATA* particleData, Mtx* particleWmat, 
                   _PARTICLE_COLOR* particleColor)
{
    unsigned char* breath = (unsigned char*)pBreathModel;
    unsigned char* particle = (unsigned char*)particleData;
    unsigned char flags;
    float f0;
    float f1;
    float f2;
    Mtx workMtx;
    Vec jitter;
    Vec pos;
    Vec* dir;

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

    if (*(char*)(breath + 0x22) != '\0') {
        *(float*)(particle + 0x88) = (float)(unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
        *(unsigned char*)(particle + 0x54) = *(unsigned char*)(breath + 0x22);
    }
    if (*(char*)(breath + 0x23) != '\0') {
        *(unsigned char*)(particle + 0x55) = *(unsigned char*)(breath + 0x23);
    }

    *(float*)(particle + 0x58) = *(float*)(breath + 0x90);
    *(float*)(particle + 0x5C) = *(float*)(breath + 0x94);
    if (*(unsigned char*)(breath + 0xC1) != 0) {
        *(float*)(particle + 0x60) = *(float*)(breath + 0x9C) * Math.RandF();
        flags = *(unsigned char*)(breath + 0xC1);
        if ((flags & 1) && (flags & 2)) {
            if (Math.RandF() > 0.5f) {
                *(float*)(particle + 0x60) *= FLOAT_80330F80;
            }
        } else if (flags & 2) {
            *(float*)(particle + 0x60) *= FLOAT_80330F80;
        }
    }

    flags = *(unsigned char*)(breath + 0xC1);
    if (flags & 4) {
        *(float*)(particle + 0x58) += *(float*)(particle + 0x60);
    }
    if (flags & 8) {
        *(float*)(particle + 0x5C) += *(float*)(particle + 0x60);
    }

    while (*(float*)(particle + 0x58) >= 6.2831855f) {
        *(float*)(particle + 0x58) -= 6.2831855f;
    }
    while (*(float*)(particle + 0x58) < 0.0f) {
        *(float*)(particle + 0x58) += 6.2831855f;
    }

    *(float*)(particle + 0x64) = *(float*)(breath + 0x50);
    *(float*)(particle + 0x68) = *(float*)(breath + 0x54);
    *(float*)(particle + 0x6C) = *(float*)(breath + 0x58);
    *(float*)(particle + 0x70) = *(float*)(breath + 0x60);
    *(float*)(particle + 0x74) = *(float*)(breath + 0x64);
    *(float*)(particle + 0x78) = *(float*)(breath + 0x68);

    flags = *(unsigned char*)(breath + 0xC0);
    if (flags != 0) {
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
            f0 = *(float*)(breath + 0x80) * Math.RandF();
            *(float*)(particle + 0x7C) = f0;
            *(float*)(particle + 0x80) = f0;
            *(float*)(particle + 0x84) = f0;
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

    if (flags & 4) {
        *(float*)(particle + 0x64) += *(float*)(particle + 0x7C);
        *(float*)(particle + 0x68) += *(float*)(particle + 0x80);
        *(float*)(particle + 0x6C) += *(float*)(particle + 0x84);
    }
    if (flags & 8) {
        *(float*)(particle + 0x70) += *(float*)(particle + 0x7C);
        *(float*)(particle + 0x74) += *(float*)(particle + 0x80);
        *(float*)(particle + 0x78) += *(float*)(particle + 0x84);
    }

    *(float*)(particle + 0x8C) = *(float*)(breath + 0x14);
    if (*(float*)(breath + 0xA8) != kPppBreathModelZero) {
        *(float*)(particle + 0x8C) += (2.0f * *(float*)(breath + 0xA8)) * Math.RandF() - *(float*)(breath + 0xA8);
    }

    if (*(short*)(breath + 0x20) == 0) {
        *(short*)(particle + 0x30) = -1;
    } else {
        *(short*)(particle + 0x30) = *(short*)(breath + 0x20);
    }
    *(unsigned char*)(particle + 0x90) = 0;

    if (particleWmat != NULL) {
        PSMTXCopy(*(Mtx*)vBreathModel, *(Mtx*)particleWmat);
    }
    if (particleColor != NULL) {
        *(u32*)((unsigned char*)particleColor + 0x10) = *(u32*)(breath + 0x28);
        *(u32*)((unsigned char*)particleColor + 0x14) = *(u32*)(breath + 0x2C);
        *(u32*)((unsigned char*)particleColor + 0x18) = *(u32*)(breath + 0x30);
        *(u32*)((unsigned char*)particleColor + 0x1C) = *(u32*)(breath + 0x34);
    }

    if (particleWmat == NULL) {
        return;
    }

    PSMTXCopy(*(Mtx*)particleWmat, workMtx);
    workMtx[0][3] = kPppBreathModelZero;
    workMtx[1][3] = kPppBreathModelZero;
    workMtx[2][3] = kPppBreathModelZero;

    *(float*)(particle + 0x3C) = kPppBreathModelZero;
    *(float*)(particle + 0x40) = kPppBreathModelZero;
    *(float*)(particle + 0x44) = FLOAT_80330F80;
    dir = (Vec*)(particle + 0x3C);
    PSMTXMultVec(workMtx, dir, dir);
    PSVECNormalize(dir, dir);

    f0 = *(float*)(breath + 0xB0);
    f1 = *(float*)(breath + 0xB4);
    f2 = *(float*)(breath + 0xB8);
    jitter.x = -(f0 * 0.5f - Math.RandF(f0));
    jitter.y = -(f1 * 0.5f - Math.RandF(f1));
    jitter.z = -(f2 * 0.5f - Math.RandF(f2));

    pos.x = (*(Mtx*)particleWmat)[0][3];
    pos.y = (*(Mtx*)particleWmat)[1][3];
    pos.z = (*(Mtx*)particleWmat)[2][3];
    PSVECAdd(&jitter, &pos, &pos);
    (*(Mtx*)particleWmat)[0][3] = pos.x;
    (*(Mtx*)particleWmat)[1][3] = pos.y;
    (*(Mtx*)particleWmat)[2][3] = pos.z;

    PSMTXConcat(*(Mtx*)particleWmat, *(Mtx*)((unsigned char*)pppObject + 4), *(Mtx*)particleData);
    PSMTXConcat(ppvCameraMatrix0, *(Mtx*)particleData, workMtx);

    *(float*)(particle + 0x3C) = kPppBreathModelZero;
    *(float*)(particle + 0x40) = kPppBreathModelZero;
    *(float*)(particle + 0x44) = FLOAT_80330F80;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetParticleMatrix(_pppPObject*, VBreathModel*, _PARTICLE_DATA*, Mtx*, _pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern "C" void UpdateParticle__FP12VBreathModelP12PBreathModelP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR(
    VBreathModel*, PBreathModel* pBreathModel, _PARTICLE_DATA* particleData, VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    unsigned char* breath = (unsigned char*)pBreathModel;
    unsigned char* particle = (unsigned char*)particleData;
    unsigned int alpha = (unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
    Vec step;

    if (particleColor != NULL) {
        float* color = (float*)particleColor;
        color[0] += color[4];
        color[1] += color[5];
        color[2] += color[6];
        color[3] += color[7];
        color[4] += *(float*)(breath + 0x38);
        color[5] += *(float*)(breath + 0x3C);
        color[6] += *(float*)(breath + 0x40);
        color[7] += *(float*)(breath + 0x44);
        alpha += (unsigned int)(int)color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    *(float*)(particle + 0x58) += *(float*)(particle + 0x5C);
    if ((*(unsigned char*)(breath + 0xC1) & 0x10) == 0) {
        *(float*)(particle + 0x5C) += *(float*)(breath + 0x98);
    } else {
        *(float*)(particle + 0x5C) += *(float*)(breath + 0x98) + *(float*)(particle + 0x60);
    }

    while (*(float*)(particle + 0x58) >= 6.2831855f) {
        *(float*)(particle + 0x58) -= 6.2831855f;
    }
    while (*(float*)(particle + 0x58) < 0.0f) {
        *(float*)(particle + 0x58) += 6.2831855f;
    }

    *(float*)(particle + 0x64) += *(float*)(particle + 0x70);
    *(float*)(particle + 0x68) += *(float*)(particle + 0x74);
    *(float*)(particle + 0x6C) += *(float*)(particle + 0x78);

    if ((*(unsigned char*)(breath + 0xC0) & 0x10) == 0) {
        *(float*)(particle + 0x70) += *(float*)(breath + 0x70);
        *(float*)(particle + 0x74) += *(float*)(breath + 0x74);
        *(float*)(particle + 0x78) += *(float*)(breath + 0x78);
    } else {
        *(float*)(particle + 0x70) += *(float*)(breath + 0x70) + *(float*)(particle + 0x7C);
        *(float*)(particle + 0x74) += *(float*)(breath + 0x74) + *(float*)(particle + 0x80);
        *(float*)(particle + 0x78) += *(float*)(breath + 0x78) + *(float*)(particle + 0x84);
    }

    *(float*)(particle + 0x8C) += *(float*)(breath + 0xA4);
    if (*(char*)(breath + 0xC8) == '\0') {
        float start = *(float*)(breath + 0xA0);
        float delta = *(float*)(breath + 0xA4);
        if ((start > 0.0f) && (delta < 0.0f)) {
            if (*(float*)(particle + 0x8C) < 0.0f) {
                *(float*)(particle + 0x8C) = 0.0f;
            }
        } else if ((start < 0.0f) && (delta > 0.0f) && (0.0f < *(float*)(particle + 0x8C))) {
            *(float*)(particle + 0x8C) = 0.0f;
        }
    }

    PSVECScale((Vec*)(particle + 0x3C), &step, *(float*)(particle + 0x8C));
    PSVECAdd(&step, (Vec*)(particle + 0x30), (Vec*)(particle + 0x30));

    if (*(short*)(breath + 0x20) != 0) {
        *(short*)(particle + 0x50) -= 1;
    }
    *(unsigned char*)(particle + 0x90) += 1;

    if ((*(char*)(particle + 0x54) != '\0') &&
        ((int)(unsigned int)*(unsigned char*)(particle + 0x90) <= (int)*(char*)(particle + 0x54))) {
        *(float*)(particle + 0x88) -= (float)alpha / (float)(unsigned int)*(unsigned char*)(particle + 0x54);
    }

    if ((*(char*)(particle + 0x55) != '\0') &&
        ((int)*(short*)(particle + 0x50) <= (int)*(char*)(particle + 0x55))) {
        unsigned int fadeFrames = (unsigned int)*(unsigned char*)(breath + 0x23);
        if (fadeFrames != 0) {
            *(float*)(particle + 0x88) += (float)alpha / (float)fadeFrames;
        }
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

    spawnCount = 0;
    particleData = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x30);
    particleWmat = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x34);
    particleColor = (unsigned char*)*(void**)((unsigned char*)vBreathModel + 0x38);
    groupTable = *(BreathParticleGroup**)((unsigned char*)vBreathModel + 0x3C);
    maxParticleCount = *(int*)((unsigned char*)vBreathModel + 0x40);

    if ((gPppCalcDisabled == 0) && (*(int*)((unsigned char*)pBreathModel + 0xC) != 0xFFFF)) {
        *(short*)((unsigned char*)vBreathModel + 0x44) = *(short*)((unsigned char*)vBreathModel + 0x44) + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (*(short*)(particleData + 0x50) >= 1) {
                UpdateParticle__FP12VBreathModelP12PBreathModelP14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR(
                    vBreathModel, pBreathModel, (_PARTICLE_DATA*)particleData, vColor, (_PARTICLE_COLOR*)particleColor);
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

                if ((*(unsigned short*)((unsigned char*)pBreathModel + 0x1E) <=
                     *(unsigned short*)((unsigned char*)vBreathModel + 0x44)) &&
                    (spawnCount < (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x1C))) {
                    BirthParticle(pppObject, vBreathModel, pBreathModel, vColor, (_PARTICLE_DATA*)particleData,
                                  (Mtx*)particleWmat, (_PARTICLE_COLOR*)particleColor);
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
            *(short*)((unsigned char*)vBreathModel + 0x44) = 0;
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
 * PAL Address: 0x800db6e0
 * PAL Size: 1264b
 */
extern "C" void pppFrameBreathModel(pppBreathModel* breathModel, PBreathModel* pBreathModel, pppBreathModelUnkC* offsets)
{
    int colorOffset;
    int* dataOffsets;
    unsigned char* work;
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
    colorOffset = dataOffsets[1];
    work = reinterpret_cast<unsigned char*>(breathModel) + 0x80 + dataOffsets[0];
    color = (VColor*)(reinterpret_cast<unsigned char*>(breathModel) + 0x80 + colorOffset);

    if (*(void**)(work + 0x30) == NULL) {
        int maxParticleCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x1A);
        int particleGroups = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
        int particlePerGroup = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
        int* groupTable;

        *(int*)(work + 0x40) = maxParticleCount;
        *(short*)(work + 0x54) = *(short*)((unsigned char*)pBreathModel + 0x12);
        *(short*)(work + 0x56) = *(short*)((unsigned char*)pBreathModel + 0x10);

        *(void**)(work + 0x30) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x98), pppEnvStPtr->m_stagePtr,
                                                  s_pppBreathModel_cpp, 0x257);
        if (*(void**)(work + 0x30) != NULL) {
            memset(*(void**)(work + 0x30), 0, (unsigned long)(maxParticleCount * 0x98));
        }

        *(void**)(work + 0x34) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x30), pppEnvStPtr->m_stagePtr,
                                                  s_pppBreathModel_cpp, 0x25d);
        if (*(void**)(work + 0x34) != NULL) {
            memset(*(void**)(work + 0x34), 0, (unsigned long)(maxParticleCount * 0x30));
        }

        *(void**)(work + 0x38) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x20), pppEnvStPtr->m_stagePtr,
                                                  s_pppBreathModel_cpp, 0x263);
        if (*(void**)(work + 0x38) != NULL) {
            memset(*(void**)(work + 0x38), 0, (unsigned long)(maxParticleCount * 0x20));
        }

        *(void**)(work + 0x3C) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(particleGroups * 0x5C), pppEnvStPtr->m_stagePtr,
                                                  s_pppBreathModel_cpp, 0x269);
        if (*(void**)(work + 0x3C) != NULL) {
            memset(*(void**)(work + 0x3C), 0, (unsigned long)(particleGroups * 0x5C));

            groupTable = (int*)*(void**)(work + 0x3C);
            for (i = 0; i < particleGroups; i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, pppEnvStPtr->m_stagePtr, s_pppBreathModel_cpp, 0x274);
                memset((void*)groupTable[1], 0xFF, (unsigned long)particlePerGroup);

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, pppEnvStPtr->m_stagePtr, s_pppBreathModel_cpp, 0x277);
                memset((void*)groupTable[2], 0xFF, (unsigned long)particlePerGroup);
                groupTable[0] = 0;
                groupTable += 0x17;
            }
        }

        *(float*)(work + 0x48) = kPppBreathModelZero;
        *(float*)(work + 0x4C) = kPppBreathModelZero;
        *(float*)(work + 0x50) = FLOAT_80330F80;
        PSVECNormalize((Vec*)(work + 0x48), (Vec*)(work + 0x48));
    }

    PSMTXCopy(pppMngStPtr->m_matrix.value, *(Mtx*)work);
    UpdateAllParticle(reinterpret_cast<_pppPObject*>(breathModel), (VBreathModel*)work, pBreathModel, color);

    particleWMat = *(Mtx**)(work + 0x34);
    groupData = *(int**)(work + 0x3C);
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
            scaledOwner = pppMngStPtr->m_ownerScale * *(float*)((unsigned char*)pBreathModel + 8);
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
            pppHitCylinderSendSystem(pppMngStPtr, &origin, &hitVector, scaledOwner,
                                     *(float*)((unsigned char*)pBreathModel + 4));
        }

        groupData += 0x17;
    }
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
    int i;
    int dataOffset;
    int colorOffset;
    int maxParticleCount;
    int graphId;
    int groupCount;
    int slotCount;
    unsigned char* base;
    unsigned char* work;
    unsigned char* particleData;
    unsigned char* particleWMat;
    unsigned char* groupPtr;
    float* particleColor;
    pppModelSt* model;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char colorA;
    Mtx worldMtx;

    dataOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    object = (_pppPObject*)breathModel;
    base = (unsigned char*)breathModel + 0x80;
    work = base + dataOffset;
    particleData = *(unsigned char**)(work + 0x30);
    particleWMat = *(unsigned char**)(work + 0x34);
    particleColor = *(float**)(work + 0x38);
    maxParticleCount = *(int*)(work + 0x40);
    graphId = *(int*)((unsigned char*)pBreathModel + 0x00);

    if (graphId == -1) {
        return;
    }

    model = (pppModelSt*)(*(void***)(pppEnvStPtr + 8))[graphId];
    pppInitBlendMode();
    pppSetBlendMode(*(unsigned char*)((unsigned char*)pBreathModel + 4));
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(base + colorOffset, NULL, 0.0f, 0xFF, 0xFF,
                                                               *(unsigned char*)((unsigned char*)pBreathModel + 4), 0xFF, 0xFF,
                                                               1, 0xFF);

    colorR = *(unsigned char*)(base + colorOffset + 0);
    colorG = *(unsigned char*)(base + colorOffset + 1);
    colorB = *(unsigned char*)(base + colorOffset + 2);
    colorA = *(unsigned char*)(base + colorOffset + 3);

    for (i = 0; i < maxParticleCount; i++) {
        if (*(short*)(particleData + 0x50) > 0) {
            GXColor drawColor;
            Mtx scaledMtx;
            Mtx drawMtx;
            Vec pos;
            int r;
            int g;
            int b;
            int a;

            PSMTXScale(scaledMtx,
                       *(float*)(pppMngStPtr + 0x28) * *(float*)(particleData + 0x64),
                       *(float*)(pppMngStPtr + 0x2C) * *(float*)(particleData + 0x68),
                       *(float*)(pppMngStPtr + 0x30) * *(float*)(particleData + 0x6C));
            PSMTXConcat(*(Mtx*)particleData, scaledMtx, drawMtx);
            PSMTXConcat(ppvCameraMatrix0, drawMtx, drawMtx);
            PSMTXConcat(ppvCameraMatrix0, *(Mtx*)particleData, worldMtx);
            PSMTXMultVec(worldMtx, (Vec*)(particleData + 0x30), &pos);
            drawMtx[0][3] = pos.x;
            drawMtx[1][3] = pos.y;
            drawMtx[2][3] = pos.z;
            GXLoadPosMtxImm(drawMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((double)(int)colorA - *(float*)(particleData + 0x88));

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

        if (particleWMat != NULL) {
            particleWMat += 0x30;
        }
        if (particleColor != NULL) {
            particleColor += 8;
        }
        particleData += 0x98;
    }

    if ((CFlatFlags & 0x200000) != 0) {
        groupCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
        slotCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
        groupPtr = *(unsigned char**)(work + 0x3C);

        for (i = 0; i < groupCount; i++) {
            if (*(int*)groupPtr == 1) {
                GXColor debugColor;
                int firstParticle;
                int j;
                float groupScale;
                Mtx sphereMtx;
                Vec pos;

                if ((i == 0) || (i == 2)) {
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                } else if (i == 1) {
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0xFF;
                    debugColor.a = 0xFF;
                } else if (i == 3) {
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
                for (j = 0; j < slotCount; j++) {
                    if (*(signed char*)(*(int*)(groupPtr + 8) + j) != -1) {
                        firstParticle = (int)*(signed char*)(*(int*)(groupPtr + 4) + j);
                        break;
                    }
                }

                PSMTXIdentity(sphereMtx);
                groupScale = *(float*)(groupPtr + 0x28);
                sphereMtx[0][0] = groupScale;
                sphereMtx[1][1] = groupScale;
                sphereMtx[2][2] = groupScale;
                PSMTXConcat(*(Mtx*)(particleWMat + firstParticle * 0x30), object->m_localMatrix.value, worldMtx);
                PSMTXConcat(ppvCameraMatrix0, worldMtx, worldMtx);
                PSMTXMultVec(worldMtx, (Vec*)(groupPtr + 0x0C), &pos);
                sphereMtx[0][3] = pos.x;
                sphereMtx[1][3] = pos.y;
                sphereMtx[2][3] = pos.z;

                pppSetBlendMode(1);
                DrawSphere__8CGraphicFPA4_f8_GXColor(&Graphic, sphereMtx, debugColor);
            }
            groupPtr += 0x5C;
        }

        pppInitBlendMode();
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 2);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800db18c
 * PAL Size: 120b
 */
extern "C" void pppConstructBreathModel(pppBreathModel* pppBreathModel, pppBreathModelUnkC* param_2)
{
    unsigned char* state = (unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets;
    float fVar1;

    PSMTXIdentity(*(Mtx*)state);
    fVar1 = kPppBreathModelZero;

    *(float*)(state + 0x50) = kPppBreathModelZero;
    *(float*)(state + 0x4C) = fVar1;
    *(float*)(state + 0x48) = fVar1;

    *(int*)(state + 0x30) = 0;
    *(int*)(state + 0x34) = 0;
    *(int*)(state + 0x38) = 0;
    *(int*)(state + 0x3C) = 0;
    *(int*)(state + 0x40) = 0;

    *(short*)(state + 0x44) = 10000;
    *(short*)(state + 0x54) = 0;
    *(short*)(state + 0x56) = 0;
    *(unsigned char*)(state + 0x58) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800db094
 * PAL Size: 248b
 */
extern "C" void pppDestructBreathModel(pppBreathModel* pppBreathModel, pppBreathModelUnkC* param_2)
{
    unsigned char* work = (unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets;
    void** particleData = (void**)(work + 0x30);

    if (particleData[0] != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[0]);
        particleData[0] = NULL;
    }

    if (particleData[1] != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[1]);
        particleData[1] = NULL;
    }

    if (particleData[2] != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[2]);
        particleData[2] = NULL;
    }

    if (particleData[3] != NULL) {
        int i;
        unsigned char* group = (unsigned char*)particleData[3];

        for (i = 0; i < *(short*)(work + 0x54); i++) {
            void** groupData = (void**)(group + 4);

            if (groupData[0] != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(groupData[0]);
                groupData[0] = NULL;
            }

            if (groupData[1] != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(groupData[1]);
                groupData[1] = NULL;
            }

            group += 0x5C;
        }

        pppHeapUseRate__FPQ27CMemory6CStage(particleData[3]);
        particleData[3] = NULL;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
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

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
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
