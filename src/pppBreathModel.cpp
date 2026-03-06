#include "ffcc/pppBreathModel.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include "ffcc/math.h"
#include "ffcc/symbols_shared.h"
#include <string.h>

extern CMath math;
extern float FLOAT_80330F80;
extern int gPppCalcDisabled;
extern u32 CFlatFlags;
extern Mtx ppvCameraMatrix0;
extern unsigned char* pppMngStPtr;
extern unsigned char* pppEnvStPtr;

struct pppFMATRIX {
    Mtx value;
};

struct pppModelSt;

extern "C" {
void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
void pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(void*, Vec*, Vec*, float, float);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppSetBlendMode__FUc(u8);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void pppInitBlendMode__Fv(void);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
}

static char s_pppBreathModel_cpp[] = "pppBreathModel.cpp";

struct pppBreathModelUnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct pppBreathModel {
    unsigned char _pad[8];
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
                   VColor* vColor, PARTICLE_DATA* particleData, PARTICLE_WMAT* particleWmat, 
                   PARTICLE_COLOR* particleColor)
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

    math.RandF();
    math.RandF();
    math.RandF();

    if (*(char*)(breath + 0x22) != '\0') {
        *(float*)(particle + 0x68) = (float)(unsigned int)*(unsigned char*)((unsigned char*)vColor + 0x0B);
        *(unsigned char*)(particle + 0x39) = *(unsigned char*)(breath + 0x22);
    }
    if (*(char*)(breath + 0x23) != '\0') {
        *(unsigned char*)(particle + 0x3D) = *(unsigned char*)(breath + 0x23);
    }

    *(float*)(particle + 0x68) = *(float*)(breath + 0x90);
    *(float*)(particle + 0x6C) = *(float*)(breath + 0x94);
    if (*(unsigned char*)(breath + 0xC1) != 0) {
        *(float*)(particle + 0x60) = *(float*)(breath + 0x9C) * math.RandF();
        flags = *(unsigned char*)(breath + 0xC1);
        if ((flags & 1) && (flags & 2)) {
            if (math.RandF() > 0.5f) {
                *(float*)(particle + 0x60) *= FLOAT_80330F80;
            }
        } else if (flags & 2) {
            *(float*)(particle + 0x60) *= FLOAT_80330F80;
        }
    }

    flags = *(unsigned char*)(breath + 0xC1);
    if (flags & 4) {
        *(float*)(particle + 0x68) += *(float*)(particle + 0x60);
    }
    if (flags & 8) {
        *(float*)(particle + 0x6C) += *(float*)(particle + 0x60);
    }

    while (*(float*)(particle + 0x68) >= 6.2831855f) {
        *(float*)(particle + 0x68) -= 6.2831855f;
    }
    while (*(float*)(particle + 0x68) < 0.0f) {
        *(float*)(particle + 0x68) += 6.2831855f;
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
            *(float*)(particle + 0x7C) = *(float*)(breath + 0x80) * math.RandF();
            *(float*)(particle + 0x80) = *(float*)(breath + 0x84) * math.RandF();
            *(float*)(particle + 0x84) = *(float*)(breath + 0x88) * math.RandF();
            if ((flags & 1) && (flags & 2)) {
                if (math.RandF() > 0.5f) {
                    *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                }
                if (math.RandF() > 0.5f) {
                    *(float*)(particle + 0x80) *= FLOAT_80330F80;
                }
                if (math.RandF() > 0.5f) {
                    *(float*)(particle + 0x84) *= FLOAT_80330F80;
                }
            } else if (flags & 2) {
                *(float*)(particle + 0x7C) *= FLOAT_80330F80;
                *(float*)(particle + 0x80) *= FLOAT_80330F80;
                *(float*)(particle + 0x84) *= FLOAT_80330F80;
            }
        } else {
            f0 = *(float*)(breath + 0x80) * math.RandF();
            *(float*)(particle + 0x7C) = f0;
            *(float*)(particle + 0x80) = f0;
            *(float*)(particle + 0x84) = f0;
            if ((flags & 1) && (flags & 2)) {
                if (math.RandF() > 0.5f) {
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
        *(float*)(particle + 0x8C) += (2.0f * *(float*)(breath + 0xA8)) * math.RandF() - *(float*)(breath + 0xA8);
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

    *(float*)(particle + 0x0C) = kPppBreathModelZero;
    *(float*)(particle + 0x10) = kPppBreathModelZero;
    *(float*)(particle + 0x14) = 1.0f;
    dir = (Vec*)(particle + 0x0C);
    PSMTXMultVec(workMtx, dir, dir);
    PSVECNormalize(dir, dir);

    f0 = *(float*)(breath + 0xB0);
    f1 = *(float*)(breath + 0xB4);
    f2 = *(float*)(breath + 0xB8);
    jitter.x = -(f0 * 0.5f - math.RandF(f0));
    jitter.y = -(f1 * 0.5f - math.RandF(f1));
    jitter.z = -(f2 * 0.5f - math.RandF(f2));

    pos.x = (*(Mtx*)particleWmat)[0][3];
    pos.y = (*(Mtx*)particleWmat)[1][3];
    pos.z = (*(Mtx*)particleWmat)[2][3];
    PSVECAdd(&jitter, &pos, &pos);
    (*(Mtx*)particleWmat)[0][3] = pos.x;
    (*(Mtx*)particleWmat)[1][3] = pos.y;
    (*(Mtx*)particleWmat)[2][3] = pos.z;

    PSMTXConcat(*(Mtx*)particleWmat, *(Mtx*)((unsigned char*)pppObject + 4), *(Mtx*)particleData);
    PSMTXConcat(ppvCameraMatrix0, *(Mtx*)particleData, workMtx);

    *(float*)(particle + 0x0C) = kPppBreathModelZero;
    *(float*)(particle + 0x10) = kPppBreathModelZero;
    *(float*)(particle + 0x14) = 1.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetParticleMatrix(_pppPObject*, VBreathModel*, PARTICLE_DATA*, PARTICLE_WMAT*, _pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateParticle(VBreathModel*, PBreathModel* pBreathModel, PARTICLE_DATA* particleData, VColor* vColor, PARTICLE_COLOR* particleColor)
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
    int spawnCount;
    int i;
    int groupIndex;
    int slotIndex;
    unsigned char* work = (unsigned char*)vBreathModel;
    unsigned char* particleData = (unsigned char*)*(void**)(work + 0x30);
    unsigned char* particleWmat = (unsigned char*)*(void**)(work + 0x34);
    unsigned char* particleColor = (unsigned char*)*(void**)(work + 0x38);
    int* groupTable = *(int**)(work + 0x3C);
    int maxParticleCount = *(int*)(work + 0x40);
    unsigned short groups = *(unsigned short*)((unsigned char*)pBreathModel + 0x12);
    unsigned short slots = *(unsigned short*)((unsigned char*)pBreathModel + 0x10);

    if (gPppCalcDisabled != 0 || *(short*)((unsigned char*)pBreathModel + 0xC) == -1) {
        return;
    }

    spawnCount = 0;
    *(short*)(work + 0x44) = *(short*)(work + 0x44) + 1;

    for (i = 0; i < maxParticleCount; i++) {
        if (*(short*)(particleData + 0x50) < 1) {
            short foundSlot = -1;
            short foundGroup = -1;
            int groupPtr = *(int*)(work + 0x3C);
            bool found = false;

            for (foundGroup = 0; foundGroup < (short)groups; foundGroup++) {
                for (foundSlot = 0; foundSlot < (short)slots; foundSlot++) {
                    if ((short)i == (short)*(signed char*)(*(int*)(groupPtr + 4) + foundSlot)) {
                        found = true;
                        goto found_search_index;
                    }
                }
                groupPtr += 0x5C;
            }
            foundSlot = -1;
            foundGroup = -1;

found_search_index:
            if (foundGroup != -1) {
                int* group = groupTable + (int)foundGroup * 0x17;
                *(unsigned char*)(group[1] + foundSlot) = 0xFF;
                IsDeadGroupBreath(pBreathModel, vBreathModel, foundGroup);
            }

            if (*(unsigned short*)((unsigned char*)pBreathModel + 0x1E) <= *(unsigned short*)(work + 0x44) &&
                spawnCount < (int)*(unsigned short*)((unsigned char*)pBreathModel + 0x1C)) {
                BirthParticle(pppObject, vBreathModel, pBreathModel, vColor, (PARTICLE_DATA*)particleData,
                              (PARTICLE_WMAT*)particleWmat, (PARTICLE_COLOR*)particleColor);
                spawnCount++;

                found = false;
                for (groupIndex = 0; groupIndex < (int)groups; groupIndex++) {
                    int* group = groupTable + groupIndex * 0x17;
                    for (slotIndex = 0; slotIndex < (int)slots; slotIndex++) {
                        if ((*(signed char*)(group[1] + slotIndex) == -1) &&
                            (*(signed char*)(group[2] + slotIndex) == -1)) {
                            *(signed char*)(group[1] + slotIndex) = (signed char)i;
                            *(unsigned char*)(group[2] + slotIndex) = 1;
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
            }
        } else {
            UpdateParticle(vBreathModel, pBreathModel, (PARTICLE_DATA*)particleData, vColor, (PARTICLE_COLOR*)particleColor);
        }

        particleData += 0x98;
        if (particleWmat != NULL) {
            particleWmat += 0x30;
        }
        if (particleColor != NULL) {
            particleColor += 0x20;
        }
    }

    if (spawnCount > 0) {
        *(short*)(work + 0x44) = 0;
    }

    for (groupIndex = 0; groupIndex < (int)groups; groupIndex++) {
        int* group = groupTable + groupIndex * 0x17;
        if ((group[0] != 1) && (*(signed char*)group[1] != -1) && (*(signed char*)group[2] == 1)) {
            Vec unitVelocity;
            unitVelocity.x = kPppBreathModelZero;
            unitVelocity.y = kPppBreathModelZero;
            unitVelocity.z = 1.0f;
            group[9] = *(int*)((unsigned char*)pBreathModel + 0x14);
            *(float*)(group + 3) = kPppBreathModelZero;
            *((float*)(group + 3) + 1) = kPppBreathModelZero;
            *((float*)(group + 3) + 2) = kPppBreathModelZero;
            *(Vec*)(group + 6) = unitVelocity;
            PSMTXCopy(*(Mtx*)pppMngStPtr, *(Mtx*)(group + 0xB));
            group[0] = 1;
        }
    }

    for (groupIndex = 0; groupIndex < (int)groups; groupIndex++) {
        int* group = groupTable + groupIndex * 0x17;
        if (group[0] != 0) {
            Vec stepVelocity;
            PSVECScale((Vec*)(group + 6), &stepVelocity, (float)group[9]);
            PSVECAdd(&stepVelocity, (Vec*)(group + 3), (Vec*)(group + 3));
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
    int i;
    int j;
    int firstParticle;
    int slotCount;
    int groupCount;
    int* dataOffsets;
    unsigned char* base;
    unsigned char* work;
    unsigned char* groupPtr;
    unsigned char* particleWMat;
    bool ready;
    float scaleValue;
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
    base = (unsigned char*)breathModel + 8;
    work = base + dataOffsets[0];

    if (*(void**)(work + 0x30) == NULL) {
        int maxParticleCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x1A);
        int particleGroups = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
        int particlePerGroup = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
        int* groupTable;

        *(int*)(work + 0x40) = maxParticleCount;
        *(short*)(work + 0x54) = *(short*)((unsigned char*)pBreathModel + 0x10);
        *(short*)(work + 0x56) = *(short*)((unsigned char*)pBreathModel + 0x12);

        *(void**)(work + 0x30) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x98), *(void**)pppEnvStPtr,
                                                  s_pppBreathModel_cpp, 0x257);
        if (*(void**)(work + 0x30) != NULL) {
            memset(*(void**)(work + 0x30), 0, (unsigned long)(maxParticleCount * 0x98));
        }

        *(void**)(work + 0x34) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x30), *(void**)pppEnvStPtr,
                                                  s_pppBreathModel_cpp, 0x25d);
        if (*(void**)(work + 0x34) != NULL) {
            memset(*(void**)(work + 0x34), 0, (unsigned long)(maxParticleCount * 0x30));
        }

        *(void**)(work + 0x38) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(maxParticleCount * 0x20), *(void**)pppEnvStPtr,
                                                  s_pppBreathModel_cpp, 0x263);
        if (*(void**)(work + 0x38) != NULL) {
            memset(*(void**)(work + 0x38), 0, (unsigned long)(maxParticleCount * 0x20));
        }

        *(void**)(work + 0x3C) =
            pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(particleGroups * 0x5C), *(void**)pppEnvStPtr,
                                                  s_pppBreathModel_cpp, 0x269);
        if (*(void**)(work + 0x3C) != NULL) {
            memset(*(void**)(work + 0x3C), 0, (unsigned long)(particleGroups * 0x5C));

            groupTable = (int*)*(void**)(work + 0x3C);
            for (i = 0; i < particleGroups; i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, *(void**)pppEnvStPtr, s_pppBreathModel_cpp, 0x274);
                memset((void*)groupTable[1], 0xFF, (unsigned long)particlePerGroup);

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)particlePerGroup, *(void**)pppEnvStPtr, s_pppBreathModel_cpp, 0x277);
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

    PSMTXCopy(*(Mtx*)pppMngStPtr, *(Mtx*)work);
    UpdateAllParticle((_pppPObject*)breathModel, (VBreathModel*)work, pBreathModel, (VColor*)(base + dataOffsets[1]));

    groupCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x12);
    slotCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pBreathModel + 0x10);
    particleWMat = *(unsigned char**)(work + 0x34);
    groupPtr = *(unsigned char**)(work + 0x3C);
    scaleValue = *(float*)((unsigned char*)pBreathModel + 8);

    for (i = 0; i < groupCount; i++) {
        ready = true;
        for (j = 0; j < slotCount; j++) {
            if ((*(signed char*)(*(int*)(groupPtr + 4) + j) == -1) || (*(signed char*)(*(int*)(groupPtr + 8) + j) != 1)) {
                ready = false;
                break;
            }
        }

        if (ready) {
            firstParticle = -1;
            for (j = 0; j < slotCount; j++) {
                if (*(signed char*)(*(int*)(groupPtr + 8) + j) != -1) {
                    firstParticle = (int)*(signed char*)(*(int*)(groupPtr + 4) + j);
                    break;
                }
            }

            if (firstParticle >= 0) {
                Mtx* particleMtx = (Mtx*)(particleWMat + firstParticle * 0x30);

                PSMTXIdentity(scaleMtx);
                scaleMtx[0][0] = scaleValue;
                scaleMtx[1][1] = scaleValue;
                scaleMtx[2][2] = scaleValue;

                PSMTXConcat(*particleMtx, *(Mtx*)((unsigned char*)breathModel + 4), worldMtx);
                PSMTXMultVec(worldMtx, (Vec*)(groupPtr + 0xC), &origin);

                PSMTXCopy(*particleMtx, rotMtx.value);
                rotMtx.value[0][3] = kPppBreathModelZero;
                rotMtx.value[1][3] = kPppBreathModelZero;
                rotMtx.value[2][3] = kPppBreathModelZero;

                dir = *(Vec*)(groupPtr + 0x18);
                PSMTXMultVec(rotMtx.value, &dir, &dir);
                if ((dir.x != 0.0f) || (dir.y != 0.0f) || (dir.z != 0.0f)) {
                    PSVECNormalize(&dir, &dirNorm);
                } else {
                    dirNorm.x = 0.0f;
                    dirNorm.y = 0.0f;
                    dirNorm.z = 0.0f;
                }
                PSVECScale(&dirNorm, &target, *(float*)(groupPtr + 0x24));
                PSVECAdd(&origin, &target, &target);
                PSVECSubtract(&target, &origin, &hitVector);

                pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(pppMngStPtr, &origin, &hitVector, scaleValue,
                                                                    *(float*)((unsigned char*)pBreathModel + 4));
            }
        }

        groupPtr += 0x5C;
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
    int i;
    int dataOffset;
    int colorOffset;
    int maxParticleCount;
    int graphId;
    unsigned char* base;
    unsigned char* work;
    unsigned char* particleData;
    unsigned char* particleWMat;
    float* particleColor;
    pppModelSt* model;
    GXColor baseColor;
    GXColor drawColor;
    Mtx scaledMtx;
    Mtx drawMtx;
    Mtx worldMtx;
    Vec pos;

    dataOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    base = (unsigned char*)breathModel + 8;
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
    pppInitBlendMode__Fv();
    pppSetBlendMode__FUc(*(unsigned char*)((unsigned char*)pBreathModel + 4));
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(base + colorOffset, NULL, 0.0f, 0xFF, 0xFF,
                                                               *(unsigned char*)((unsigned char*)pBreathModel + 4), 0xFF, 0xFF,
                                                               1, 0xFF);

    baseColor.r = *(unsigned char*)(base + colorOffset + 0);
    baseColor.g = *(unsigned char*)(base + colorOffset + 1);
    baseColor.b = *(unsigned char*)(base + colorOffset + 2);
    baseColor.a = *(unsigned char*)(base + colorOffset + 3);

    for (i = 0; i < maxParticleCount; i++) {
        if (*(short*)(particleData + 0x50) > 0) {
            drawColor = baseColor;
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

            if (particleColor != NULL) {
                int r = (int)baseColor.r + (int)particleColor[0];
                int g = (int)baseColor.g + (int)particleColor[1];
                int b = (int)baseColor.b + (int)particleColor[2];
                int a = (int)baseColor.a + (int)particleColor[3];

                if (r < 0) r = 0;
                if (r > 255) r = 255;
                if (g < 0) g = 0;
                if (g > 255) g = 255;
                if (b < 0) b = 0;
                if (b > 255) b = 255;
                if (a < 0) a = 0;
                if (a > 127) a = 127;

                drawColor.r = (u8)r;
                drawColor.g = (u8)g;
                drawColor.b = (u8)b;
                drawColor.a = (u8)a;
            }

            GXLoadPosMtxImm(drawMtx, 0);
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
        pppInitBlendMode__Fv();
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
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
    int groupTable = *(int*)((unsigned char*)vBreathModel + 0x3C) + (int)groupIndex * 0x5C;
    bool isDead = true;
    float zero = kPppBreathModelZero;
    int* groupData = (int*)groupTable;

    for (i = 0; i < *(unsigned short*)((unsigned char*)pBreathModel + 0x10); i++) {
        if ((*(signed char*)(groupData[1] + i) != -1) || (*(signed char*)(groupData[2] + i) != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < *(unsigned short*)((unsigned char*)pBreathModel + 0x10); i++) {
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
    int* groupArray;

    SearchIndex(pBreathModel, vBreathModel, slotIndex, groupIndex, particleIndex);
    if (groupIndex != -1) {
        groupArray = *(int**)((unsigned char*)vBreathModel + 0x3C);
        *(unsigned char*)(groupArray[groupIndex * 0x17 + 1] + slotIndex) = 0xFF;
    }
}



