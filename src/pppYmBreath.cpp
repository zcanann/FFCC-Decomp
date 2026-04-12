#include "ffcc/pppYmBreath.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "dolphin/mtx.h"

#include <string.h>
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern "C" void pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(void* outMatrix, void* angle);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSetBlendMode(unsigned char);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern float FLOAT_80330c80;
extern float FLOAT_80330c84;
extern float FLOAT_80330c90;
extern double DOUBLE_80330c88;
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);

struct pppYmBreathUnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct YmBreathRenderStep {
    int m_graphId;
    int m_dataValIndex;
    unsigned short m_initWork;
    unsigned short m_stepValue;
    int m_arg3;
    unsigned char* m_payload;
};

struct YmBreathParticleGroup {
    int active;
    signed char* particleIndices;
    unsigned char* particleStates;
    Vec position;
    Vec direction;
    float speed;
    Mtx matrix;
};

static char s_pppYmBreath_cpp[] = "pppYmBreath.cpp";

/*
 * --INFO--
 * Address:	800bfe74
 * Size:	4
 */
void get_rand()
{
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
void BirthParticle(_pppPObject*, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor, _PARTICLE_DATA* particleData,
                   Mtx* particleWmat, _PARTICLE_COLOR* particleColor)
{
    unsigned char* breath = (unsigned char*)pYmBreath;
    unsigned char* particle = (unsigned char*)particleData;
    pppIVECTOR4 angle;
    pppFMATRIX rotMtx;
    Vec baseDir;
    Vec normDir;
    float spread;
    unsigned char flags;

    memset(particle + 0x30, 0, 0x60);
    if (particleWmat != NULL) {
        memset(particleWmat, 0, 0x30);
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, 0x20);
    }

    spread = (float)(unsigned int)*(unsigned char*)(breath + 0x28);
    baseDir.x = 0.0f;
    baseDir.y = 0.0f;
    baseDir.z = -1.0f;

    angle.x = (short)((spread + spread) * Math.RandF() - spread);
    angle.y = (short)((spread + spread) * Math.RandF() - spread);
    angle.z = (short)((spread + spread) * Math.RandF() - spread);
    angle.w = 0;

    pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&rotMtx, &angle);
    PSMTXMultVecSR(rotMtx.value, &baseDir, (Vec*)(particle + 0x3C));

    *(float*)(particle + 0x3C) *= *(float*)(breath + 0xB0);
    *(float*)(particle + 0x40) *= *(float*)(breath + 0xB4);
    *(float*)(particle + 0x44) *= *(float*)(breath + 0xB8);

    normDir.x = *(float*)(particle + 0x3C);
    normDir.y = *(float*)(particle + 0x40);
    normDir.z = *(float*)(particle + 0x44);
    pppNormalize__FR3Vec3Vec((float*)(particle + 0x3C), &normDir);

    if (*(float*)(breath + 0xAC) != 0.0f) {
        PSVECScale((Vec*)(particle + 0x3C), (Vec*)(particle + 0x30), *(float*)(breath + 0xAC));
    }

    if (*(char*)(breath + 0x26) != 0) {
        *(float*)(particle + 0x7C) = (float)(unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
        *(char*)(particle + 0x54) = *(char*)(breath + 0x26);
    }
    if (*(char*)(breath + 0x27) != 0) {
        *(char*)(particle + 0x55) = *(char*)(breath + 0x27);
    }

    *(float*)(particle + 0x58) = *(float*)(breath + 0x90);
    *(float*)(particle + 0x5C) = *(float*)(breath + 0x94);

    if (*(char*)(breath + 0xC2) != 0) {
        *(float*)(particle + 0x60) = *(float*)(breath + 0x9C) * Math.RandF();
        flags = *(unsigned char*)(breath + 0xC2);

        if (((flags & 1) != 0) && ((flags & 2) != 0)) {
            if (Math.RandF() > 0.5f) {
                *(float*)(particle + 0x60) = -*(float*)(particle + 0x60);
            }
        } else if ((flags & 2) != 0) {
            *(float*)(particle + 0x60) = -*(float*)(particle + 0x60);
        }
    }

    if ((*(unsigned char*)(breath + 0xC2) & 4) != 0) {
        *(float*)(particle + 0x58) += *(float*)(particle + 0x60);
    }
    if ((*(unsigned char*)(breath + 0xC2) & 8) != 0) {
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
    *(float*)(particle + 0x6C) = *(float*)(breath + 0x60);
    *(float*)(particle + 0x70) = *(float*)(breath + 0x64);

    if (*(unsigned char*)(breath + 0xC1) != 0) {
        flags = *(unsigned char*)(breath + 0xC1);
        if ((flags & 0x20) == 0) {
            *(float*)(particle + 0x74) = *(float*)(breath + 0x80) * Math.RandF();
            *(float*)(particle + 0x78) = *(float*)(breath + 0x84) * Math.RandF();

            if (((flags & 1) != 0) && ((flags & 2) != 0)) {
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x74) = -*(float*)(particle + 0x74);
                }
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x78) = -*(float*)(particle + 0x78);
                }
            } else if ((flags & 2) != 0) {
                *(float*)(particle + 0x74) = -*(float*)(particle + 0x74);
                *(float*)(particle + 0x78) = -*(float*)(particle + 0x78);
            }
        } else {
            *(float*)(particle + 0x74) = *(float*)(breath + 0x80) * Math.RandF();
            *(float*)(particle + 0x78) = *(float*)(particle + 0x74);

            if (((flags & 1) != 0) && ((flags & 2) != 0)) {
                if (Math.RandF() > 0.5f) {
                    *(float*)(particle + 0x74) = -*(float*)(particle + 0x74);
                    *(float*)(particle + 0x78) = -*(float*)(particle + 0x78);
                }
            } else if ((flags & 2) != 0) {
                *(float*)(particle + 0x74) = -*(float*)(particle + 0x74);
                *(float*)(particle + 0x78) = -*(float*)(particle + 0x78);
            }
        }
    }

    if ((*(unsigned char*)(breath + 0xC1) & 4) != 0) {
        *(float*)(particle + 0x64) += *(float*)(particle + 0x74);
        *(float*)(particle + 0x68) += *(float*)(particle + 0x78);
    }
    if ((*(unsigned char*)(breath + 0xC1) & 8) != 0) {
        *(float*)(particle + 0x6C) += *(float*)(particle + 0x74);
        *(float*)(particle + 0x70) += *(float*)(particle + 0x78);
    }

    *(float*)(particle + 0x80) = *(float*)(breath + 0x18);
    if (*(float*)(breath + 0xA8) != 0.0f) {
        spread = *(float*)(breath + 0xA8);
        *(float*)(particle + 0x80) += (spread + spread) * Math.RandF() - spread;
    }

    if (*(short*)(breath + 0x24) == 0) {
        *(short*)(particle + 0x50) = -1;
    } else {
        *(short*)(particle + 0x50) = *(short*)(breath + 0x24);
    }
    *(unsigned char*)(particle + 0x84) = 0;

    if (particleWmat != NULL) {
        PSMTXCopy(*(Mtx*)vYmBreath, *(Mtx*)particleWmat);
    }
    if (particleColor != NULL) {
        *(float*)((unsigned char*)particleColor + 0x10) = *(float*)(breath + 0x2C);
        *(float*)((unsigned char*)particleColor + 0x14) = *(float*)(breath + 0x30);
        *(float*)((unsigned char*)particleColor + 0x18) = *(float*)(breath + 0x34);
        *(float*)((unsigned char*)particleColor + 0x1C) = *(float*)(breath + 0x38);
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
void UpdateParticle(VYmBreath* vYmBreath, PYmBreath* pYmBreath, _PARTICLE_DATA* particleData, VColor* vColor,
                    _PARTICLE_COLOR* particleColor)
{
    unsigned char* breath = (unsigned char*)pYmBreath;
    unsigned char* particle = (unsigned char*)particleData;
    unsigned char* color = (unsigned char*)particleColor;
    unsigned int alpha = (unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
    Vec step;

    (void)vYmBreath;

    if (color != NULL) {
        *(float*)(color + 0x00) += *(float*)(color + 0x10);
        *(float*)(color + 0x04) += *(float*)(color + 0x14);
        *(float*)(color + 0x08) += *(float*)(color + 0x18);
        *(float*)(color + 0x0C) += *(float*)(color + 0x1C);
        *(float*)(color + 0x10) += *(float*)(breath + 0x3C);
        *(float*)(color + 0x14) += *(float*)(breath + 0x40);
        *(float*)(color + 0x18) += *(float*)(breath + 0x44);
        *(float*)(color + 0x1C) += *(float*)(breath + 0x48);
        alpha += (unsigned int)(int)*(float*)(color + 0x0C);
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    *(float*)(particle + 0x58) += *(float*)(particle + 0x5C);
    if ((*(unsigned char*)(breath + 0xC2) & 0x10) == 0) {
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

    *(float*)(particle + 0x64) += *(float*)(particle + 0x6C);
    *(float*)(particle + 0x68) += *(float*)(particle + 0x70);
    if ((*(unsigned char*)(breath + 0xC1) & 0x10) == 0) {
        *(float*)(particle + 0x6C) += *(float*)(breath + 0x70);
        *(float*)(particle + 0x70) += *(float*)(breath + 0x74);
    } else {
        *(float*)(particle + 0x6C) += *(float*)(breath + 0x70) + *(float*)(particle + 0x74);
        *(float*)(particle + 0x70) += *(float*)(breath + 0x74) + *(float*)(particle + 0x78);
    }

    *(float*)(particle + 0x80) += *(float*)(breath + 0xA4);
    if (*(char*)(breath + 0xC8) == '\0') {
        float start = *(float*)(breath + 0xA0);
        float delta = *(float*)(breath + 0xA4);
        if ((start > 0.0f) && (delta < 0.0f)) {
            if (*(float*)(particle + 0x80) < 0.0f) {
                *(float*)(particle + 0x80) = 0.0f;
            }
        } else if ((start < 0.0f) && (delta > 0.0f) && (0.0f < *(float*)(particle + 0x80))) {
            *(float*)(particle + 0x80) = 0.0f;
        }
    }

    PSVECScale((Vec*)(particle + 0x3C), &step, *(float*)(particle + 0x80));
    PSVECAdd(&step, (Vec*)(particle + 0x30), (Vec*)(particle + 0x30));

    if (*(short*)(breath + 0x24) != 0) {
        *(short*)(particle + 0x50) -= 1;
    }
    *(unsigned char*)(particle + 0x84) += 1;

    if ((*(char*)(particle + 0x54) != '\0') &&
        ((int)(unsigned int)*(unsigned char*)(particle + 0x84) <= (int)*(char*)(particle + 0x54))) {
        *(float*)(particle + 0x7C) -= (float)alpha / (float)(unsigned int)*(unsigned char*)(particle + 0x54);
    }

    if ((*(char*)(particle + 0x55) != '\0') && ((int)*(short*)(particle + 0x50) <= (int)*(char*)(particle + 0x55))) {
        *(float*)(particle + 0x7C) += (float)alpha / (float)(unsigned int)*(unsigned char*)(breath + 0x27);
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
    bool found;
    int spawnCount;
    int i;
    int j;
    int k;
    int group;
    int groupTableWork;
    YmBreathParticleGroup* groupTable;
    YmBreathParticleGroup* groupData;
    unsigned char* particleData;
    unsigned char* particleWmat;
    unsigned char* particleColor;
    int maxParticleCount;
    short foundSlot;
    short foundGroup;
    Vec stepVelocity;
    Vec unitVelocity;

    spawnCount = 0;
    particleData = (unsigned char*)*(void**)((unsigned char*)vYmBreath + 0x30);
    particleWmat = (unsigned char*)*(void**)((unsigned char*)vYmBreath + 0x34);
    particleColor = (unsigned char*)*(void**)((unsigned char*)vYmBreath + 0x38);
    groupTable = *(YmBreathParticleGroup**)((unsigned char*)vYmBreath + 0x3C);
    maxParticleCount = *(int*)((unsigned char*)vYmBreath + 0x40);

    if ((gPppCalcDisabled == 0) && (*(int*)((unsigned char*)pYmBreath + 0xC) != 0xFFFF)) {
        *(short*)((unsigned char*)vYmBreath + 0x44) = *(short*)((unsigned char*)vYmBreath + 0x44) + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (*(short*)(particleData + 0x50) >= 1) {
                UpdateParticle(vYmBreath, pYmBreath, (_PARTICLE_DATA*)particleData, vColor,
                               (_PARTICLE_COLOR*)particleColor);
                pppCalcFrameShape(*(long**)(*(int*)(pppEnvStPtr + 0xC) + *(int*)((unsigned char*)pYmBreath + 0xC) * 4),
                                  *(short*)(particleData + 0x58), *(short*)(particleData + 0x5A),
                                  *(short*)(particleData + 0x56), *(short*)((unsigned char*)pYmBreath + 0x10));
            } else {
                float zero = FLOAT_80330c80;

                groupTableWork = *(int*)((unsigned char*)vYmBreath + 0x3C);
                for (foundGroup = 0;
                     foundGroup < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14);
                     foundGroup++) {
                    for (foundSlot = 0;
                         foundSlot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
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
                    group = *(int*)((unsigned char*)vYmBreath + 0x3C) + (int)foundGroup * 0x5C;
                    slotCount = *(unsigned short*)((unsigned char*)pYmBreath + 0x12);
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
                        for (slot = 0; slot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                             slot++) {
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

                if ((*(unsigned short*)((unsigned char*)pYmBreath + 0x22) <=
                     *(unsigned short*)((unsigned char*)vYmBreath + 0x44)) &&
                    (spawnCount < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x20))) {
                    BirthParticle(pppObject, vYmBreath, pYmBreath, vColor, (_PARTICLE_DATA*)particleData,
                                  (Mtx*)particleWmat, (_PARTICLE_COLOR*)particleColor);
                    found = true;
                    spawnCount += 1;
                    groupData = groupTable;
                    for (j = 0; j < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); j++) {
                        for (k = 0; k < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                             k++) {
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
            *(short*)((unsigned char*)vYmBreath + 0x44) = 0;
        }

        groupData = groupTable;
        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); i++) {
            if ((groupData->active != 1) && (*groupData->particleIndices != -1) && (*groupData->particleStates == 1)) {
                unitVelocity.x = FLOAT_80330c80;
                unitVelocity.y = FLOAT_80330c80;
                unitVelocity.z = FLOAT_80330c90;
                groupData->speed = *(float*)((unsigned char*)pYmBreath + 0x18);
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.x = 0.0f;
                groupData->position.y = 0.0f;
                groupData->position.z = 0.0f;
                PSMTXCopy(*(Mtx*)pppMngStPtr, groupData->matrix);
                groupData->active = 1;
            }
            groupData += 1;
        }

        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); i++) {
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
 * Address:	TODO
 * Size:	TODO
 */
void SetParticleMatrix(_pppPObject*, VYmBreath*, _PARTICLE_DATA*, Mtx*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	800c04f8
 * Size:	1264
 */
extern "C" void pppFrameYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, pppYmBreathUnkC* offsets)
{
    int colorOffset;
    int* dataOffsets;
    unsigned char* work;
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
    work = reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + dataOffsets[0];

    if (*(void**)(work + 0x30) == NULL) {
        int maxParticleCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x1E);
        int particleGroups = (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14);
        int particlePerGroup = (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
        int* groupTable;

        *(int*)(work + 0x40) = maxParticleCount;
        *(short*)(work + 0x54) = *(short*)((unsigned char*)pYmBreath + 0x14);
        *(short*)(work + 0x56) = *(short*)((unsigned char*)pYmBreath + 0x12);

        *(void**)(work + 0x30) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x98), pppEnvStPtr->m_stagePtr,
                                                  s_pppYmBreath_cpp, 0x243);
        if (*(void**)(work + 0x30) != NULL) {
            memset(*(void**)(work + 0x30), 0, (unsigned long)(maxParticleCount * 0x98));
        }

        *(void**)(work + 0x34) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x30), pppEnvStPtr->m_stagePtr,
                                                  s_pppYmBreath_cpp, 0x249);
        if (*(void**)(work + 0x34) != NULL) {
            memset(*(void**)(work + 0x34), 0, (unsigned long)(maxParticleCount * 0x30));
        }

        *(void**)(work + 0x38) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x20), pppEnvStPtr->m_stagePtr,
                                                  s_pppYmBreath_cpp, 0x24F);
        if (*(void**)(work + 0x38) != NULL) {
            memset(*(void**)(work + 0x38), 0, (unsigned long)(maxParticleCount * 0x20));
        }

        *(void**)(work + 0x3C) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(particleGroups * 0x5C), pppEnvStPtr->m_stagePtr,
                                                  s_pppYmBreath_cpp, 0x255);
        if (*(void**)(work + 0x3C) != NULL) {
            memset(*(void**)(work + 0x3C), 0, (unsigned long)(particleGroups * 0x5C));

            groupTable = (int*)*(void**)(work + 0x3C);
            for (i = 0; i < particleGroups; i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, pppEnvStPtr->m_stagePtr, s_pppYmBreath_cpp, 0x260);
                memset((void*)groupTable[1], 0xFF, (unsigned long)particlePerGroup);

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, pppEnvStPtr->m_stagePtr, s_pppYmBreath_cpp, 0x263);
                memset((void*)groupTable[2], 0xFF, (unsigned long)particlePerGroup);
                groupTable[0] = 0;
                groupTable += 0x17;
            }
        }

        *(float*)(work + 0x48) = 0.0f;
        *(float*)(work + 0x4C) = 0.0f;
        *(float*)(work + 0x50) = 1.0f;
        PSVECNormalize((Vec*)(work + 0x48), (Vec*)(work + 0x48));
    }

    PSMTXCopy(pppMngStPtr->m_matrix.value, *(Mtx*)work);
    UpdateAllParticle(reinterpret_cast<_pppPObject*>(ymBreath), (VYmBreath*)work, pYmBreath,
                      (VColor*)(reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + colorOffset));

    particleWMat = *(Mtx**)(work + 0x34);
    groupData = *(int**)(work + 0x3C);
    for (groupIndex = 0; groupIndex < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14);
         groupIndex++) {
        slotCount = (unsigned int)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
        groupTable = *(int*)(work + 0x3C) + groupIndex * 0x5C;
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
            scaledOwner = pppMngStPtr->m_ownerScale * *(float*)((unsigned char*)pYmBreath + 8);
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
            PSMTXConcat(*particleMtx, reinterpret_cast<_pppPObject*>(ymBreath)->m_localMatrix.value, worldMtx);
            PSMTXMultVec(worldMtx, (Vec*)(groupTable + 0xC), &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = FLOAT_80330c80;
            rotMtx.value[1][3] = FLOAT_80330c80;
            rotMtx.value[2][3] = FLOAT_80330c80;
            *(float*)(groupTable + 0x28) = scaledOwner;
            pppCopyVector(dir, *(Vec*)(groupTable + 0x18));
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppNormalize__FR3Vec3Vec(reinterpret_cast<float*>(&dir), &dirNorm);
            PSVECScale(&dirNorm, &target, *(float*)(groupTable + 0x24));
            pppAddVector(target, origin, target);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(pppMngStPtr, &origin, &hitVector, scaledOwner,
                                                                *(float*)((unsigned char*)pYmBreath + 4));
        }

        groupData += 0x17;
    }
}

/*
 * --INFO--
 * Address:	800bffec
 * Size:	1292
 */
extern "C" void pppRenderYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, pppYmBreathUnkC* offsets)
{
    _pppPObject* object;
    YmBreathRenderStep* step;
    int workOffset;
    int colorOffset;
    Vec* source;
    Mtx* matrixList;
    float* colorDelta;
    int* groupData;
    int groupCount;
    long* shape;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char colorA;
    int i;

    object = reinterpret_cast<_pppPObject*>(ymBreath);
    step = (YmBreathRenderStep*)pYmBreath;
    workOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    source = *(Vec**)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x30);
    matrixList = *(Mtx**)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x34);
    colorDelta = *(float**)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x38);
    groupData = *(int**)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x3C);
    groupCount = *(int*)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x40);

    if (step->m_stepValue == 0) {
        return;
    }

    shape = *(long**)(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pppEnvStPtr) + 0xC) + step->m_stepValue * 4);
    pppSetBlendMode(step->m_payload[8]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        step->m_payload + 0xB0, 0, 0.0f, step->m_payload[0xB6], step->m_payload[0xB5], step->m_payload[8], 0, 1, 1, 0);

    colorR = *(reinterpret_cast<unsigned char*>(ymBreath) + 8 + colorOffset + 0);
    colorG = *(reinterpret_cast<unsigned char*>(ymBreath) + 8 + colorOffset + 1);
    colorB = *(reinterpret_cast<unsigned char*>(ymBreath) + 8 + colorOffset + 2);
    colorA = *(reinterpret_cast<unsigned char*>(ymBreath) + 8 + colorOffset + 3);

    for (i = 0; i < groupCount; i++) {
        if (*(short*)&source[2].z > 0) {
            _GXColor amb;
            Mtx drawMtx;
            Mtx rotMtx;
            Vec pos;
            pppFMATRIX viewMtx;
            int r;
            int g;
            int b;
            int a;

            PSMTXIdentity(drawMtx);
            drawMtx[0][0] = source[4].y * pppMngStPtr->m_scale.x;
            drawMtx[1][1] = source[4].z * pppMngStPtr->m_scale.y;
            drawMtx[2][2] = drawMtx[0][0];
            if (FLOAT_80330c80 != source[3].y) {
                PSMTXRotRad(rotMtx, 'z', FLOAT_80330c84 * source[3].y);
                PSMTXConcat(drawMtx, rotMtx, drawMtx);
            }

            pppUnitMatrix(viewMtx);
            PSMTXConcat(*matrixList, object->m_localMatrix.value, viewMtx.value);
            PSMTXConcat(ppvCameraMatrix0, viewMtx.value, viewMtx.value);
            PSMTXMultVec(viewMtx.value, source, &pos);
            drawMtx[0][3] = pos.x;
            drawMtx[1][3] = pos.y;
            drawMtx[2][3] = pos.z;
            GXLoadPosMtxImm(drawMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((double)(int)colorA - DOUBLE_80330c88 - source[6].y);
            if (colorDelta != 0) {
                r += (int)colorDelta[0];
                g += (int)colorDelta[1];
                b += (int)colorDelta[2];
                a += (int)colorDelta[3];
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

            amb.r = (unsigned char)r;
            amb.g = (unsigned char)g;
            amb.b = (unsigned char)b;
            amb.a = (unsigned char)a;
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppDrawShp__FPlsP12CMaterialSetUc(shape, *(short*)((unsigned char*)&source[7].y + 2),
                                              pppEnvStPtr->m_materialSetPtr,
                                              step->m_payload[8]);
        }

        if (matrixList != 0) {
            matrixList++;
        }
        if (colorDelta != 0) {
            colorDelta += 8;
        }
        source += 8;
    }

    if ((CFlatFlags & 0x200000) != 0) {
        for (i = 0; i < (int)*(unsigned short*)step->m_payload; i++) {
            if (groupData[0] == 1) {
                _GXColor debugColor;
                int firstParticle;
                int j;
                float scale;
                Mtx sphereMtx;
                Mtx tempMtx;
                Vec debugPos;

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
                for (j = 0; j < (int)*(unsigned short*)((unsigned char*)&step->m_arg3 + 2); j++) {
                    if (*(signed char*)(groupData[2] + j) != -1) {
                        firstParticle = (int)*(signed char*)(groupData[1] + j);
                        break;
                    }
                }

                scale = (float)groupData[10];
                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = scale;
                sphereMtx[1][1] = scale;
                sphereMtx[2][2] = scale;

                PSMTXConcat(*(Mtx*)(*(int*)(reinterpret_cast<unsigned char*>(ymBreath) + 8 + workOffset + 0x34) +
                                    firstParticle * 0x30),
                            object->m_localMatrix.value, tempMtx);
                PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
                PSMTXMultVec(tempMtx, (Vec*)(groupData + 3), &debugPos);
                sphereMtx[0][3] = debugPos.x;
                sphereMtx[1][3] = debugPos.y;
                sphereMtx[2][3] = debugPos.z;
                Graphic.DrawSphere(sphereMtx, debugColor);
            }
            groupData += 0x17;
        }

        pppSetBlendMode(1);
        pppSetBlendMode(0);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 2);
    }
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
extern "C" void pppConstructYmBreath(pppYmBreath* ymBreath, pppYmBreathUnkC* dataOffsets)
{
    unsigned char* state = (unsigned char*)ymBreath + 0x80 + *dataOffsets->m_serializedDataOffsets;
    float zero;

    PSMTXIdentity(*(Mtx*)state);
    zero = FLOAT_80330c80;

    *(float*)(state + 0x50) = FLOAT_80330c80;
    *(float*)(state + 0x4C) = zero;
    *(float*)(state + 0x48) = zero;

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
 * Address:	800bff70
 * Size:	4
 */
void pppConstruct2YmBreath(_pppPObject* obj)
{
    (void)obj;
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
extern "C" void pppDestructYmBreath(pppYmBreath* ymBreath, pppYmBreathUnkC* dataOffsets)
{
    unsigned char* work = (unsigned char*)ymBreath + 0x80 + *dataOffsets->m_serializedDataOffsets;
    void** particleData = (void**)(work + 0x30);

    if (particleData[0] != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[0]);
        particleData[0] = 0;
    }

    if (particleData[1] != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[1]);
        particleData[1] = 0;
    }

    if (particleData[2] != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(particleData[2]);
        particleData[2] = 0;
    }

    if (particleData[3] != 0) {
        int i;
        unsigned char* group = (unsigned char*)particleData[3];

        for (i = 0; i < *(short*)(work + 0x54); i++) {
            void** groupData = (void**)(group + 4);

            if (groupData[0] != 0) {
                pppHeapUseRate__FPQ27CMemory6CStage(groupData[0]);
                groupData[0] = 0;
            }

            if (groupData[1] != 0) {
                pppHeapUseRate__FPQ27CMemory6CStage(groupData[1]);
                groupData[1] = 0;
            }

            group += 0x5C;
        }

        pppHeapUseRate__FPQ27CMemory6CStage(particleData[3]);
        particleData[3] = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void IsDeadGroupBreath(PYmBreath* pYmBreath, VYmBreath* vBreathModel, short groupIndex)
{
    int i;
    int groupTable = *(int*)((unsigned char*)vBreathModel + 0x3C) + (int)groupIndex * 0x5C;
    bool isDead = true;
    float zero = 0.0f;
    int* groupData = (int*)groupTable;

    for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); i++) {
        if ((*(signed char*)(groupData[1] + i) != -1) || (*(signed char*)(groupData[2] + i) != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); i++) {
            *(unsigned char*)(groupData[2] + i) = 0xFF;
            groupData[3] = (int)zero;
            groupData[4] = (int)zero;
            groupData[5] = (int)zero;
            groupData[6] = (int)zero;
            groupData[7] = (int)zero;
            groupData[8] = (int)zero;
            groupData[9] = (int)zero;
        }
        groupData[0] = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SearchIndex(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short& slotIndex, short& groupIndex, short particleIndex)
{
    int groupTable = *(int*)((unsigned char*)vYmBreath + 0x3C);
    short g;
    short s;

    for (g = 0; g < *(unsigned short*)((unsigned char*)pYmBreath + 0x14); g++) {
        for (s = 0; s < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); s++) {
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
void IsExistGroupParticle(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short particleIndex)
{
    short slotIndex;
    short groupIndex;
    int* groupArray;

    SearchIndex(pYmBreath, vYmBreath, slotIndex, groupIndex, particleIndex);
    if (groupIndex != -1) {
        groupArray = *(int**)((unsigned char*)vYmBreath + 0x3C);
        *(unsigned char*)(groupArray[groupIndex * 0x17 + 1] + slotIndex) = 0xFF;
    }
}
