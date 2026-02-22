#include "ffcc/pppRyjMegaBirthModel.h"
#include <string.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern float FLOAT_80330498;
extern float FLOAT_8033049c;

static char s_pppRyjMegaBirthModel_cpp_801d9c18[] = "pppRyjMegaBirthModel.cpp";

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
 * Address:	TODO
 * Size:	TODO
 */
void get_noise(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VRyjMegaBirthModel*, PRyjMegaBirthModel*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80087ce8
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModel(_pppPObject* pObject, PRyjMegaBirthModel* params, PRyjMegaBirthModelOffsets* offsets)
{
    bool hasRequiredMemory;
    s32 colorOffset = offsets->m_serializedDataOffsets[1];
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];
    u8* payload = (u8*)params;

    if (*(void**)(work + 0xC) == 0) {
        *(u32*)(work + 0x18) = *(u16*)(payload + 0x20);
        *(void**)(work + 0xC) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            *(u32*)(work + 0x18) * 0xA0, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0x8D);
        if (*(void**)(work + 0xC) != 0) {
            memset(*(void**)(work + 0xC), 0, *(u32*)(work + 0x18) * 0xA0);
        }

        if (*(u8*)(payload + 0x136) != 0) {
            *(void**)(work + 0x10) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                *(u32*)(work + 0x18) * 0x30, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0x97);
            if (*(void**)(work + 0x10) != 0) {
                memset(*(void**)(work + 0x10), 0, *(u32*)(work + 0x18) * 0x30);
            }
        }

        if (*(u8*)(payload + 0x131) != 0) {
            *(void**)(work + 0x14) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                *(u32*)(work + 0x18) << 5, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0xA2);
            if (*(void**)(work + 0x14) != 0) {
                memset(*(void**)(work + 0x14), 0, *(u32*)(work + 0x18) << 5);
            }
        }

        *(float*)(work + 0x0) = *(float*)(payload + 0xF8);
        *(float*)(work + 0x4) = *(float*)(payload + 0xFC);
        *(float*)(work + 0x8) = *(float*)(payload + 0x100);
        PSVECNormalize((Vec*)(work + 0x0), (Vec*)(work + 0x0));

        *(float*)(work + 0x20) = pObject->m_localMatrix.value[0][3];
        *(float*)(work + 0x24) = pObject->m_localMatrix.value[1][3];
        *(float*)(work + 0x28) = pObject->m_localMatrix.value[2][3];
        *(float*)(work + 0x2C) = pObject->m_localMatrix.value[0][3];
        *(float*)(work + 0x30) = pObject->m_localMatrix.value[1][3];
        *(float*)(work + 0x34) = pObject->m_localMatrix.value[2][3];
    }

    if (*(void**)(work + 0xC) == 0) {
        hasRequiredMemory = false;
    } else if ((*(u8*)(payload + 0x136) != 0) && (*(void**)(work + 0x10) == 0)) {
        hasRequiredMemory = false;
    } else if ((*(u8*)(payload + 0x131) == 0) || (*(void**)(work + 0x14) != 0)) {
        hasRequiredMemory = true;
    } else {
        hasRequiredMemory = false;
    }

    if (hasRequiredMemory) {
        calc_particle(pObject, (VRyjMegaBirthModel*)work, params, (VColor*)((u8*)pObject + 0x80 + colorOffset));
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80085a38
 * PAL Size: 1432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VRyjMegaBirthModel* vRyjMegaBirthModel, 
          PRyjMegaBirthModel* pRyjMegaBirthModel, _PARTICLE_DATA* particleData, 
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    // Basic particle color updates
    if (particleColor != nullptr) {
        // Update color values
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        
        // Update color frame deltas
        particleColor->m_colorFrameDeltas[0] = particleColor->m_colorFrameDeltas[0] + pRyjMegaBirthModel->m_colorDeltaAdd[0];
        particleColor->m_colorFrameDeltas[1] = particleColor->m_colorFrameDeltas[1] + pRyjMegaBirthModel->m_colorDeltaAdd[1];
        particleColor->m_colorFrameDeltas[2] = particleColor->m_colorFrameDeltas[2] + pRyjMegaBirthModel->m_colorDeltaAdd[2];
        particleColor->m_colorFrameDeltas[3] = particleColor->m_colorFrameDeltas[3] + pRyjMegaBirthModel->m_colorDeltaAdd[3];
    }
    
    // Basic particle data updates
    particleData->m_colorDeltaAdd[0] = particleData->m_colorDeltaAdd[0] + particleData->m_colorDeltaAdd[3];
    particleData->m_colorDeltaAdd[1] = particleData->m_colorDeltaAdd[1] + particleData->m_sizeStart;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRyjDrawMegaBirthModel(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirthModel*, VRyjMegaBirthModel*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void set_matrix(_pppPObject*, pppFMATRIX, pppFMATRIX, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80084260
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModelCon(_pppPObject* pObject, PRyjMegaBirthModelOffsets* offsets)
{
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];
    float value0 = FLOAT_80330498;
    float value1 = FLOAT_8033049c;

    memset(work, 0, 0xC);
    *(void**)(work + 0xC) = 0;
    *(void**)(work + 0x10) = 0;
    *(void**)(work + 0x14) = 0;
    *(void**)(work + 0x18) = 0;
    *(u16*)(work + 0x1C) = 10000;
    *(u16*)(work + 0x1E) = 0;
    *(float*)(work + 0x20) = value0;
    *(float*)(work + 0x24) = value1;
    *(float*)(work + 0x28) = value0;
    *(float*)(work + 0x2C) = value0;
    *(float*)(work + 0x30) = value1;
    *(float*)(work + 0x34) = value0;
}

/*
 * --INFO--
 * PAL Address: 0x800841e4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModelDes(_pppPObject* pObject, PRyjMegaBirthModelOffsets* offsets)
{
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];

    if (*(void**)(work + 0xC) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0xC));
        *(void**)(work + 0xC) = 0;
    }

    if (*(void**)(work + 0x10) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x10));
        *(void**)(work + 0x10) = 0;
    }

    if (*(void**)(work + 0x14) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x14));
        *(void**)(work + 0x14) = 0;
    }
}
