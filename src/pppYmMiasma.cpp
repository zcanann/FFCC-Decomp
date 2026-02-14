#include "ffcc/pppYmMiasma.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <string.h>

extern int rand();
extern float ppvSinTbl[];
extern float FLOAT_80330640;
extern float FLOAT_80330644;
extern float FLOAT_80330650;
extern float FLOAT_80330654;
extern float FLOAT_8033065c;
extern float FLOAT_80330660;
extern float FLOAT_80330664;
extern u32 DAT_80330658;
extern int DAT_8032ed70;
extern double DOUBLE_80330648;
extern double RandF__5CMathFf(double, void*);
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern char Math;
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
extern "C" void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" void pppSetBlendMode__FUc(unsigned char);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);

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
    u32 value;
    float fVar1 = FLOAT_80330644;
    u32* work = (u32*)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]);

    value = DAT_80330658;
    work[0] = 0;
    ((float*)work)[7] = fVar1;
    ((float*)work)[8] = fVar1;
    ((float*)work)[9] = fVar1;
    *((u8*)(work + 2)) = 0;
    work[4] = value;
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

    *(float*)((u8*)pppYmMiasma_ + 0x9c + offset) = FLOAT_80330644;
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
    if (*(void**)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]));
    }
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
{
    static char sPppYmMiasmaCpp[] = "pppYmMiasma.cpp";
    int* step = (int*)param_2;
    int* work;
    int i;
    int particle;
    int count;
    Vec matrixPos;
    Vec oldPos;
    Vec delta;

    if (DAT_8032ed70 != 0) {
        return;
    }

    work = (int*)((u8*)pppYmMiasma_ + 8 + param_3->m_serializedDataOffsets[2]);

    if (step[0] == *(int*)pppYmMiasma_) {
        work[7] = (int)((float)work[7] + (float)step[0x16]);
        work[8] = (int)((float)work[8] + (float)step[0x17]);
        work[9] = (int)((float)work[9] + (float)step[0x18]);
    }

    count = (int)(u32) * (u16*)(step + 3);
    if (work[0] == 0) {
        work[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)count * 0x50, pppEnvStPtr->m_stagePtr, sPppYmMiasmaCpp, 0x18d);
        particle = work[0];
        for (i = 0; i < count; i++) {
            InitParticleData((VYmMiasma*)work, (_pppPObject*)pppYmMiasma_, (PYmMiasma*)step, (_PARTICLE_DATA*)particle);
            particle += 0x50;
        }
    }

    *((u8*)(work + 2)) = (u8)(*((u8*)(work + 2)) + 1);
    work[1] = (int)((float)work[1] - (float)step[0x1b]);
    if ((float)work[1] < FLOAT_80330644) {
        work[1] = (int)FLOAT_80330644;
    }

    if (*((u8*)(step + 0x19)) < *((u8*)(work + 2))) {
        int r;
        s16 angleDelta;
        u32 signBit;
        u32 angleIdx;

        *((u8*)(work + 2)) = 0;
        work[1] = step[6];

        r = rand();
        angleDelta = (s16)r - (s16)(r / (int)*(s16*)(step + 0x1a)) * *(s16*)(step + 0x1a);
        signBit = (u32)(int)angleDelta >> 31;
        if ((((int)angleDelta & 1U) ^ signBit) == signBit) {
            angleDelta = -angleDelta;
        }

        angleIdx = (u32)((FLOAT_80330650 * FLOAT_80330640 * (float)(s16)(angleDelta + *(s16*)((u8*)step + 0x66))) /
                         FLOAT_80330654);
        work[4] = *(int*)((u8*)ppvSinTbl + ((angleIdx + 0x4000) & 0xfffc));
        work[5] = (int)FLOAT_80330644;
        work[6] = *(int*)((u8*)ppvSinTbl + (angleIdx & 0xfffc));
    }

    work[8] = (int)((float)work[8] + (float)work[9]);
    work[7] = (int)((float)work[7] + (float)work[8]);

    particle = work[0];
    for (i = 0; i < count; i++) {
        UpdateParticleData((_pppPObject*)pppYmMiasma_, (_pppCtrlTable*)param_3, (PYmMiasma*)step, (_PARTICLE_DATA*)particle);
        particle += 0x50;
    }

    matrixPos.x = pppMngStPtr->m_matrix.value[0][3];
    matrixPos.y = pppMngStPtr->m_matrix.value[1][3];
    matrixPos.z = pppMngStPtr->m_matrix.value[2][3];
    oldPos.x = *(float*)(work + 10);
    oldPos.y = *(float*)(work + 0xb);
    oldPos.z = *(float*)(work + 0xc);

    pppSubVector__FR3Vec3Vec3Vec(&delta, &matrixPos, &oldPos);
    if ((double)PSVECDistance(&matrixPos, (Vec*)(work + 10)) == (double)FLOAT_80330644) {
        *((u8*)(work + 0xd)) = 0;
    } else {
        *((u8*)(work + 0xd)) = 0xff;
    }

    pppCopyVector__FR3Vec3Vec((Vec*)(work + 10), &matrixPos);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
{
    float* particle = (float*)((u8*)pppYmMiasma_ + 8 + param_3->m_serializedDataOffsets[2]);
    u8* step = (u8*)param_2;
    u16 count = *(u16*)(step + 0x10);

    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);

    for (int i = 0; i < (int)count; i++) {
        u16 dataValIndex = *(u16*)(step + 4);
        if (dataValIndex != 0xffff) {
            long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
            pppFMATRIX model;
            pppFMATRIX scaleMatrix;
            pppFMATRIX rotMatrix;
            Mtx rotMtx;
            Vec pos;
            GXColor amb;
            u8 blend = step[0x18 + 0x1e];

            pppUnitMatrix__FR10pppFMATRIX(&model);
            model.value[2][2] = particle[0x10];
            model.value[0][0] = pppMngStPtr->m_scale.x * model.value[2][2];
            model.value[1][1] = pppMngStPtr->m_scale.y * model.value[2][2];
            model.value[2][2] = pppMngStPtr->m_scale.z * model.value[2][2];

            PSMTXRotRad(rotMtx, 'z', FLOAT_80330640 * (float)*(s16*)((u8*)particle + 0x38));
            scaleMatrix = model;
            memcpy(rotMatrix.value, rotMtx, sizeof(Mtx));
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&model, &rotMatrix, &scaleMatrix);

            pos.x = particle[0];
            pos.y = particle[1];
            pos.z = particle[2];
            if (Game.game.m_currentSceneId == 7) {
                PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
            } else {
                PSMTXMultVec(ppvCameraMatrix0, &pos, &pos);
            }

            model.value[0][3] = pos.x;
            model.value[1][3] = pos.y;
            model.value[2][3] = pos.z;

            pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                0, &model, FLOAT_80330644, step[0x18 + 0x61], step[0x18 + 0x60], blend, 0, 1, 1, 0);

            amb.r = *(u8*)((u8*)particle + 0x20);
            amb.g = *(u8*)((u8*)particle + 0x22);
            amb.b = *(u8*)((u8*)particle + 0x24);
            amb.a = *(u8*)((u8*)particle + 0x26);
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppSetBlendMode__FUc(blend);
            pppDrawShp__FPlsP12CMaterialSetUc(
                shapeTable, *(s16*)((u8*)particle + 0x4e), pppEnvStPtr->m_materialSetPtr, blend);
        }

        particle += 0x14;
    }
}
