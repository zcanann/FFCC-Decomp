#include "ffcc/pppBreathModel.h"
#include "dolphin/mtx.h"
#include "ffcc/math.h"
#include <string.h>

extern CMath math;
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);

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
void UpdateParticle(VBreathModel*, PBreathModel*, PARTICLE_DATA*, VColor*, PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateAllParticle(_pppPObject*, VBreathModel*, PBreathModel*, VColor*)
{
	// TODO
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
    Mtx* work = (Mtx*)((unsigned char*)pppBreathModel + 0x80 + *param_2->m_serializedDataOffsets);
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
    *(state + 0x50) = 0;
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
void IsDeadGroupBreath(PBreathModel*, VBreathModel*, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SearchIndex(PBreathModel*, VBreathModel*, short&, short&, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void IsExistGroupParticle(PBreathModel*, VBreathModel*, short)
{
	// TODO
}
