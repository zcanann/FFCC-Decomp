#include "ffcc/pppYmBreath.h"
#include "dolphin/mtx.h"

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);

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
void UpdateAllParticle(_pppPObject*, VYmBreath*, PYmBreath*, VColor*)
{
	// TODO
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
void IsDeadGroupBreath(PYmBreath*, VYmBreath*, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SearchIndex(PYmBreath*, VYmBreath*, short&, short&, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void IsExistGroupParticle(PYmBreath*, VYmBreath*, short)
{
	// TODO
}
