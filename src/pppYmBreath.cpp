#include "ffcc/pppYmBreath.h"
#include "dolphin/mtx.h"

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern int DAT_8032ed70;

struct UnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct pppYmBreath {
    unsigned char _pad[8];
};

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
 * Address:	TODO
 * Size:	TODO
 */
void BirthParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*, PARTICLE_DATA*, PARTICLE_WMAT*, PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateParticle(VYmBreath*, PYmBreath*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateAllParticle(_pppPObject* pppObject, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor)
{
    int spawnCount;
    int particleIndex;
    int groupIndex;
    int slotIndex;
    unsigned char* ymBreathWork = (unsigned char*)vYmBreath;
    unsigned char* particleData = (unsigned char*)*(void**)(ymBreathWork + 0x30);
    unsigned char* particleWmat = (unsigned char*)*(void**)(ymBreathWork + 0x34);
    unsigned char* particleColor = (unsigned char*)*(void**)(ymBreathWork + 0x38);
    int* groupTable = *(int**)(ymBreathWork + 0x3C);
    int maxParticleCount = *(int*)(ymBreathWork + 0x40);
    unsigned short emitInterval = *(unsigned short*)((unsigned char*)pYmBreath + 0x1E);
    unsigned short emitMaxPerFrame = *(unsigned short*)((unsigned char*)pYmBreath + 0x1C);
    unsigned short particlesPerGroup = *(unsigned short*)((unsigned char*)pYmBreath + 0x10);
    unsigned short groupTableCount = *(unsigned short*)((unsigned char*)pYmBreath + 0x12);

    if ((DAT_8032ed70 != 0) || (*(short*)((unsigned char*)pYmBreath + 0xC) == -1)) {
        return;
    }

    spawnCount = 0;
    *(short*)(ymBreathWork + 0x44) = *(short*)(ymBreathWork + 0x44) + 1;

    for (particleIndex = 0; particleIndex < maxParticleCount; particleIndex++) {
        if (*(short*)(particleData + 0x50) < 1) {
            short foundSlot = -1;
            short foundGroup = -1;

            SearchIndex(pYmBreath, vYmBreath, foundSlot, foundGroup, (short)particleIndex);
            if (foundGroup != -1) {
                int* group = groupTable + (int)foundGroup * 0x17;
                *(unsigned char*)(group[1] + foundSlot) = 0xFF;
                IsDeadGroupBreath(pYmBreath, vYmBreath, foundGroup);
            }

            if ((emitInterval <= *(unsigned short*)(ymBreathWork + 0x44)) && (spawnCount < (int)emitMaxPerFrame)) {
                BirthParticle(pppObject, vYmBreath, pYmBreath, vColor, (PARTICLE_DATA*)particleData,
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
            UpdateParticle(vYmBreath, pYmBreath, (PARTICLE_DATA*)particleData, vColor, (PARTICLE_COLOR*)particleColor);
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
        *(short*)(ymBreathWork + 0x44) = 0;
    }

    for (groupIndex = 0; groupIndex < (int)groupTableCount; groupIndex++) {
        int* group = groupTable + groupIndex * 0x17;
        if ((group[0] != 1) && (*(signed char*)group[1] != -1) && (*(signed char*)group[2] == 1)) {
            float* position = (float*)(group + 3);
            float* velocity = (float*)(group + 6);
            group[9] = *(int*)((unsigned char*)pYmBreath + 0x14);
            position[0] = 0.0f;
            position[1] = 0.0f;
            position[2] = 0.0f;
            velocity[0] = 0.0f;
            velocity[1] = 0.0f;
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
 * Address:	TODO
 * Size:	TODO
 */
void SetParticleMatrix(_pppPObject*, VYmBreath*, PARTICLE_DATA*, PARTICLE_WMAT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	800c04f8
 * Size:	1264
 */
extern "C" void pppFrameYmBreath(void)
{
}

/*
 * --INFO--
 * Address:	800bffec
 * Size:	1292
 */
extern "C" void pppRenderYmBreath(void)
{
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
extern "C" void pppConstructYmBreath(pppYmBreath* ymBreath, UnkC* dataOffsets)
{
    Mtx* work = (Mtx*)((unsigned char*)ymBreath + 0x80 + *dataOffsets->m_serializedDataOffsets);
    unsigned char* state = (unsigned char*)work;

    PSMTXIdentity(*work);

    work[1][2][0] = 0.0f;
    work[1][1][3] = 0.0f;
    work[1][1][2] = 0.0f;
    work[1][0][0] = 0.0f;
    work[1][0][1] = 0.0f;
    work[1][0][2] = 0.0f;
    work[1][0][3] = 0.0f;
    work[1][1][0] = 0.0f;

    *(short*)(state + 0x46) = 10000;
    *(short*)(state + 0x4A) = 0;
    *(short*)(state + 0x4E) = 0;
    *(unsigned char*)(state + 0x50) = 0;
}

/*
 * --INFO--
 * Address:	800bff70
 * Size:	4
 */
void pppConstruct2YmBreath(void)
{
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
extern "C" void pppDestructYmBreath(pppYmBreath* ymBreath, UnkC* dataOffsets)
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

    for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x10); i++) {
        if ((*(signed char*)(groupData[1] + i) != -1) || (*(signed char*)(groupData[2] + i) != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x10); i++) {
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

    for (g = 0; g < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); g++) {
        for (s = 0; s < *(unsigned short*)((unsigned char*)pYmBreath + 0x10); s++) {
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
