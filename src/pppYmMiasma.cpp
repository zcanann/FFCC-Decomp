#include "ffcc/pppYmMiasma.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>

extern int rand();
extern float ppvSinTbl[];
extern float FLOAT_80330644;
extern float FLOAT_8033065c;
extern float FLOAT_80330664;
extern u32 DAT_80330658;
extern double RandF__5CMathFf(double, void*);
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern char Math;

/*
 * --INFO--
 * Address:	80091234
 * Size:	872b
 */
void InitParticleData(VYmMiasma* vYmMiasma, _pppPObject* pppPObject, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    u32 randVal;
    float sinVal, cosVal;
    u16 angleVal;
    s16 lifeTimeVariation;
    float radiusFactor, heightOffset;
    Vec direction, tempPos;
    
    // Random angle generation for particle direction
    randVal = rand();
    angleVal = (u16)(randVal & 0xFFFF);
    sinVal = ppvSinTbl[(angleVal & 0xFFFF) >> 2];
    cosVal = ppvSinTbl[((angleVal + 0x4000) & 0xFFFF) >> 2];
    
    // Calculate random radius factor 
    radiusFactor = (float)randVal * FLOAT_8033065c - FLOAT_80330664;
    
    // Set particle velocity/direction based on random values
    particleData->m_matrix[0][0] = sinVal * radiusFactor;
    particleData->m_matrix[1][0] = sinVal * radiusFactor;
    
    // Random height offset
    heightOffset = RandF__5CMathFf((double)*(float *)((char*)pYmMiasma + 0x40), &Math);
    particleData->m_matrix[0][1] = heightOffset;
    particleData->m_matrix[1][1] = heightOffset;
    
    particleData->m_matrix[0][2] = cosVal * radiusFactor;
    particleData->m_matrix[1][2] = cosVal * radiusFactor;
    
    // Normalize direction vector
    tempPos.x = particleData->m_matrix[1][0];
    tempPos.y = particleData->m_matrix[1][1];  
    tempPos.z = particleData->m_matrix[1][2];
    pppNormalize__FR3Vec3Vec((float*)particleData->m_matrix[1], &tempPos);
    
    // Initialize lifetime with variation
    lifeTimeVariation = (s16)randVal % *(s16*)((char*)pYmMiasma + 0x30);
    particleData->m_lifeTime = *(u8*)((char*)pYmMiasma + 0x24);
    particleData->m_age = 0;
    
    // Color initialization
    particleData->m_colorDeltaAdd[0] = *(float*)((char*)pYmMiasma + 0x34);
    particleData->m_colorDeltaAdd[1] = *(float*)((char*)pYmMiasma + 0x10) + radiusFactor;
}

/*
 * --INFO--
 * Address:	80090e3c
 * Size:	1016b
 */
void UpdateParticleData(_pppPObject* pppPObject, _pppCtrlTable* pppCtrlTable, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    float deltaTime;
    Vec velocity;
    
    if (!particleData || !pYmMiasma) return;
    
    // Age the particle
    particleData->m_age++;
    
    // Early exit if particle is dead
    if (particleData->m_age >= particleData->m_lifeTime) {
        return;
    }
    
    // Apply velocity to position
    deltaTime = 1.0f; // Frame time
    velocity.x = particleData->m_matrix[1][0] * deltaTime;
    velocity.y = particleData->m_matrix[1][1] * deltaTime;
    velocity.z = particleData->m_matrix[1][2] * deltaTime;
    
    // Update position matrix
    particleData->m_matrix[0][3] += velocity.x;
    particleData->m_matrix[1][3] += velocity.y;  
    particleData->m_matrix[2][3] += velocity.z;
    
    // Apply gravity or other forces
    particleData->m_velocity.y -= 0.01f; // Gravity
    
    // Update size over lifetime
    float lifeFactor = (float)particleData->m_age / (float)particleData->m_lifeTime;
    particleData->m_sizeVal = particleData->m_sizeStart * (1.0f - lifeFactor) + particleData->m_sizeEnd * lifeFactor;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderParticle(_pppPObject* pppPObject, PYmMiasma* pYmMiasma, _PARTICLE_DATA* particleData)
{
    // Basic rendering setup
    if (!particleData) return;
}

/*
 * --INFO--
 * PAL Address: 0x80090dec
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
{
    float fVar1 = FLOAT_80330644;
    u32* work = (u32*)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]);

    work[0] = 0;
    ((float*)work)[7] = fVar1;
    ((float*)work)[8] = fVar1;
    ((float*)work)[9] = fVar1;
    *((u8*)(work + 2)) = 0;
    work[4] = DAT_80330658;
    ((float*)work)[5] = fVar1;
    ((float*)work)[6] = fVar1;
    ((float*)work)[0xc] = fVar1;
    ((float*)work)[0xb] = fVar1;
    ((float*)work)[10] = fVar1;
    *((u8*)(work + 0xd)) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80090dc8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
{
    int offset = param_2->m_serializedDataOffsets[2];
    float fVar1 = FLOAT_80330644;

    *(float*)((u8*)pppYmMiasma_ + 0x9c + offset) = fVar1;
    *(float*)((u8*)pppYmMiasma_ + 0xa0 + offset) = fVar1;
    *(float*)((u8*)pppYmMiasma_ + 0xa4 + offset) = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80090d90
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
{
    void* stage = *(void**)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]);

    if (stage != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(stage);
    }
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
{
    (void)pppYmMiasma_;
    (void)param_2;
    (void)param_3;
    // Frame update function - based on Ghidra analysis this manages particle lifecycle
    if (!pppEnvStPtr || !pppMngStPtr) return;
    
    // Basic frame processing
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
{
    (void)pppYmMiasma_;
    (void)param_2;
    (void)param_3;
    // Render function stub
}
