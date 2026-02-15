#include "ffcc/pppRyjMegaBirthModel.h"
#include <string.h>

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern float FLOAT_80330498;
extern float FLOAT_8033049c;

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
 * Address:	TODO
 * Size:	TODO
 */
void pppRyjMegaBirthModel(void)
{
	// TODO
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
