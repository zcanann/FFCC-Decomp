#include "ffcc/pppBreathModel.h"
#include "dolphin/mtx.h"
#include "ffcc/math.h"
#include <string.h>

extern CMath math;
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern float lbl_80330F70;
extern int DAT_8032ed70;

struct UnkC {
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
 */
void BirthParticle(_pppPObject* pppObject, VBreathModel* vBreathModel, PBreathModel* pBreathModel, 
                   VColor* vColor, PARTICLE_DATA* particleData, PARTICLE_WMAT* particleWmat, 
                   PARTICLE_COLOR* particleColor)
{
	// Initialize particle data structure
	memset(particleData, 0, 0x98);
	
	if (particleWmat != NULL) {
		memset(particleWmat, 0, 0x30);
	}
	
	if (particleColor != NULL) {
		memset(particleColor, 0, 0x20);
	}

	// Generate random values for particle initialization
	math.RandF();
	math.RandF();
	math.RandF();

	// Alpha channel setup
	if (*(char*)((int)pBreathModel + 0x22) != 0) {
		*(float*)((int)particleData + 0x68) = *(float*)((char*)vColor + 0x3); // Assume alpha at offset 3
		*(char*)((int)particleData + 0x39) = *(char*)((int)pBreathModel + 0x22);
	}

	// Additional particle properties
	if (*(char*)((int)pBreathModel + 0x23) != 0) {
		*(char*)((int)particleData + 0x3D) = *(char*)((int)pBreathModel + 0x23);
	}

	// Base timing values
	*(float*)((int)particleData + 0x68) = *(float*)((int)pBreathModel + 0x90);
	*(float*)((int)particleData + 0x6C) = *(float*)((int)pBreathModel + 0x94);

	// Random angle adjustment
	if (*(char*)((int)pBreathModel + 0xc1) != 0) {
		math.RandF();
		// Basic randomization logic - simplified for compilation
		*(float*)((int)particleData + 0x60) = *(float*)((int)pBreathModel + 0x9c) * 0.5f;
		
		unsigned char flags = *(unsigned char*)((int)pBreathModel + 0xc1);
		if ((flags & 2) != 0) {
			*(float*)((int)particleData + 0x60) *= -1.0f;
		}
	}

	// Apply angle adjustments to timing
	if ((*(unsigned char*)((int)pBreathModel + 0xc1) & 4) != 0) {
		*(float*)((int)particleData + 0x68) += *(float*)((int)particleData + 0x60);
	}
	
	if ((*(unsigned char*)((int)pBreathModel + 0xc1) & 8) != 0) {
		*(float*)((int)particleData + 0x6C) += *(float*)((int)particleData + 0x60);
	}

	// Angle wrapping (normalize to 0-2π range)
	while (*(float*)((int)particleData + 0x68) >= 6.28318f) {
		*(float*)((int)particleData + 0x68) -= 6.28318f;
	}
	while (*(float*)((int)particleData + 0x68) < 0.0f) {
		*(float*)((int)particleData + 0x68) += 6.28318f;
	}

	// Set base velocity values
	*(float*)((int)particleData + 0x64) = *(float*)((int)pBreathModel + 0x50);
	*(float*)((int)particleData + 0x68) = *(float*)((int)pBreathModel + 0x54);
	*(float*)((int)particleData + 0x6C) = *(float*)((int)pBreathModel + 0x58);

	// Set acceleration values  
	*(float*)((int)particleData + 0x70) = *(float*)((int)pBreathModel + 0x60);
	*(float*)((int)particleData + 0x74) = *(float*)((int)pBreathModel + 0x64);
	*(float*)((int)particleData + 0x78) = *(float*)((int)pBreathModel + 0x68);

	// Random velocity components - simplified for compilation
	unsigned char velocityFlags = *(unsigned char*)((int)pBreathModel + 0xc0);
	if (velocityFlags != 0) {
		math.RandF();
		math.RandF();
		math.RandF();
		
		// Basic velocity setup
		*(float*)((int)particleData + 0x7C) = *(float*)((int)pBreathModel + 0x80) * 0.5f;
		*(float*)((int)particleData + 0x80) = *(float*)((int)pBreathModel + 0x84) * 0.5f;
		*(float*)((int)particleData + 0x84) = *(float*)((int)pBreathModel + 0x88) * 0.5f;

		if ((velocityFlags & 2) != 0) {
			*(float*)((int)particleData + 0x7C) *= -1.0f;
			*(float*)((int)particleData + 0x80) *= -1.0f;
			*(float*)((int)particleData + 0x84) *= -1.0f;
		}
	}

	// Set particle lifetime 
	*(float*)((int)particleData + 0x8C) = *(float*)((int)pBreathModel + 0x14);

	// Random lifetime variation - simplified
	if (*(float*)((int)pBreathModel + 0xa8) != 0.0f) {
		math.RandF();
		// Apply basic lifetime variation
		*(float*)((int)particleData + 0x8C) += *(float*)((int)pBreathModel + 0xa8) * 0.1f;
	}

	// Set particle texture/type
	if (*(short*)((int)pBreathModel + 0x20) == 0) {
		*(short*)((int)particleData + 0x30) = -1;
	} else {
		*(short*)((int)particleData + 0x30) = *(short*)((int)pBreathModel + 0x20);
	}

	// Initialize state flag
	*(unsigned char*)((int)particleData + 0x90) = 0;

	// Copy world matrix
	if (particleWmat != NULL) {
		PSMTXCopy(*(Mtx*)vBreathModel, *(Mtx*)particleWmat);
	}

	// Copy color data
	if (particleColor != NULL) {
		*(unsigned int*)((int)particleColor + 0x10) = *(unsigned int*)((int)pBreathModel + 0x28);
		*(unsigned int*)((int)particleColor + 0x14) = *(unsigned int*)((int)pBreathModel + 0x2c);
		*(unsigned int*)((int)particleColor + 0x18) = *(unsigned int*)((int)pBreathModel + 0x30);
		*(unsigned int*)((int)particleColor + 0x1c) = *(unsigned int*)((int)pBreathModel + 0x34);
	}
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
    int particleIndex;
    int groupIndex;
    int slotIndex;
    unsigned char* breathModelWork = (unsigned char*)vBreathModel;
    unsigned char* particleData = (unsigned char*)*(void**)(breathModelWork + 0x30);
    unsigned char* particleWmat = (unsigned char*)*(void**)(breathModelWork + 0x34);
    unsigned char* particleColor = (unsigned char*)*(void**)(breathModelWork + 0x38);
    int* groupTable = *(int**)(breathModelWork + 0x3C);
    int maxParticleCount = *(int*)(breathModelWork + 0x40);
    unsigned short emitInterval = *(unsigned short*)((unsigned char*)pBreathModel + 0x1E);
    unsigned short emitMaxPerFrame = *(unsigned short*)((unsigned char*)pBreathModel + 0x1C);
    unsigned short particlesPerGroup = *(unsigned short*)((unsigned char*)pBreathModel + 0x10);
    unsigned short groupTableCount = *(unsigned short*)((unsigned char*)pBreathModel + 0x12);

    if ((DAT_8032ed70 != 0) || (*(short*)((unsigned char*)pBreathModel + 0xC) == -1)) {
        return;
    }

    spawnCount = 0;
    *(short*)(breathModelWork + 0x44) = *(short*)(breathModelWork + 0x44) + 1;

    for (particleIndex = 0; particleIndex < maxParticleCount; particleIndex++) {
        if (*(short*)(particleData + 0x50) < 1) {
            short foundSlot = -1;
            short foundGroup = -1;

            SearchIndex(pBreathModel, vBreathModel, foundSlot, foundGroup, (short)particleIndex);
            if (foundGroup != -1) {
                int* group = groupTable + (int)foundGroup * 0x17;
                *(unsigned char*)(group[1] + foundSlot) = 0xFF;
                IsDeadGroupBreath(pBreathModel, vBreathModel, foundGroup);
            }

            if ((emitInterval <= *(unsigned short*)(breathModelWork + 0x44)) &&
                (spawnCount < (int)emitMaxPerFrame)) {
                BirthParticle(pppObject, vBreathModel, pBreathModel, vColor, (PARTICLE_DATA*)particleData,
                              (PARTICLE_WMAT*)particleWmat, (PARTICLE_COLOR*)particleColor);
                spawnCount++;

                for (groupIndex = 0; groupIndex < (int)groupTableCount; groupIndex++) {
                    int* group = groupTable + groupIndex * 0x17;
                    for (slotIndex = 0; slotIndex < (int)particlesPerGroup; slotIndex++) {
                        if ((*(signed char*)(group[1] + slotIndex) == -1) &&
                            (*(signed char*)(group[2] + slotIndex) == -1)) {
                            *(signed char*)(group[1] + slotIndex) = (signed char)particleIndex;
                            *(unsigned char*)(group[2] + slotIndex) = 1;
                            groupIndex = (int)groupTableCount;
                            break;
                        }
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
        *(short*)(breathModelWork + 0x44) = 0;
    }

    for (groupIndex = 0; groupIndex < (int)groupTableCount; groupIndex++) {
        int* group = groupTable + groupIndex * 0x17;
        if ((group[0] != 1) && (*(signed char*)group[1] != -1) && (*(signed char*)group[2] == 1)) {
            float* position = (float*)(group + 3);
            float* velocity = (float*)(group + 6);
            group[9] = *(int*)((unsigned char*)pBreathModel + 0x14);
            position[0] = lbl_80330F70;
            position[1] = lbl_80330F70;
            position[2] = lbl_80330F70;
            velocity[0] = lbl_80330F70;
            velocity[1] = lbl_80330F70;
            velocity[2] = 1.0f;
            group[0] = 1;
        }
    }

    for (groupIndex = 0; groupIndex < (int)groupTableCount; groupIndex++) {
        int* group = groupTable + groupIndex * 0x17;
        if (group[0] != 0) {
            float* position = (float*)(group + 3);
            float* velocity = (float*)(group + 6);
            float step = (float)group[9];
            position[0] += velocity[0] * step;
            position[1] += velocity[1] * step;
            position[2] += velocity[2] * step;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800db6e0
 * PAL Size: 1264b
 */
extern "C" void pppFrameBreathModel(void)
{
	// Basic particle system frame processing
	// TODO: Complete implementation
}

/*
 * --INFO--
 * PAL Address: 0x800db204
 * PAL Size: 1244b
 */
extern "C" void pppRenderBreathModel(void)
{
	// Basic particle system rendering
	// TODO: Complete implementation  
}

/*
 * --INFO--
 * PAL Address: 0x800db18c
 * PAL Size: 120b
 */
extern "C" void pppConstructBreathModel(pppBreathModel* pppBreathModel, UnkC* param_2)
{
    unsigned char* state = (unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets;
    float fVar1;

    PSMTXIdentity(*(Mtx*)state);
    fVar1 = lbl_80330F70;

    *(float*)(state + 0x50) = lbl_80330F70;
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
extern "C" void pppDestructBreathModel(pppBreathModel* pppBreathModel, UnkC* param_2)
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
    float zero = lbl_80330F70;
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
