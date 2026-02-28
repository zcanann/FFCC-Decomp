#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "dolphin/mtx.h"
#include <string.h>

class CMath;
extern CMath Math;
extern "C" float RandF__5CMathFv(CMath*);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern int rand();
extern float FLOAT_803305a4;
extern pppFMATRIX MatUnit3;
extern _pppEnvSt* pppEnvStPtr;
extern _pppMngSt* pppMngStPtr;
extern s32 DAT_8032ed70;

static char s_pppYmMegaBirthShpTail3_cpp[] = "pppYmMegaBirthShpTail3.cpp";

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
void S4ToF32(pppFVECTOR4*, short*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8008ebbc
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, UnkC* param_2)
{
    pppFMATRIX* work = (pppFMATRIX*)((u8*)pppYmMegaBirthShpTail3_ + 8 + param_2->m_serializedDataOffsets[2]);
    float initVal;

    pppUnitMatrix__FR10pppFMATRIX(work);
    initVal = FLOAT_803305a4;
    work[1].value[0][2] = FLOAT_803305a4;
    work[1].value[0][1] = initVal;
    work[1].value[0][0] = initVal;
    work[1].value[0][3] = 0.0f;
    work[1].value[1][0] = 0.0f;
    work[1].value[1][1] = 0.0f;
    work[1].value[1][2] = 0.0f;
    *(u16*)(work[1].value[1] + 3) = 0;
    *(u16*)((u8*)work[1].value[1] + 0xe) = 0;
    *(u16*)(work[1].value[1] + 3) = 10000;
    *(u16*)work[2].value[2] = (u16)rand();
    pppUnitMatrix__FR10pppFMATRIX(&MatUnit3);
    memset(work[1].value + 2, 0, 8);
    memset(work[1].value[2] + 2, 0, 8);
    memset(work + 2, 0, 8);
    memset(work[2].value[0] + 2, 0, 8);
    memset(work[2].value + 1, 0, 8);
    memset(work[2].value[1] + 2, 0, 8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, UnkC* param_2)
{
    int offset = param_2->m_serializedDataOffsets[2];
    void** ptrBc = (void**)((u8*)&pppYmMegaBirthShpTail3_->field_0xbc + offset);
    void** ptrC0 = (void**)((u8*)&pppYmMegaBirthShpTail3_->field_0xc0 + offset);
    void** ptrC4 = (void**)((u8*)&pppYmMegaBirthShpTail3_->field_0xc4 + offset);

    if (*ptrBc != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrBc);
        *ptrBc = 0;
    }
    if (*ptrC0 != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrC0);
        *ptrC0 = 0;
    }
    if (*ptrC4 != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*ptrC4);
        *ptrC4 = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008dcc8
 * PAL Size: 3704b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3, 
                      PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, VColor* vColor, 
                      _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, 
                      _PARTICLE_COLOR* particleColor)
{
    u8* paramBytes = (u8*)pYmMegaBirthShpTail3;
    u8* particleBytes = (u8*)particleData;
    u8 mode = paramBytes[0x12];
    float speedRandRange = *(float*)(paramBytes + 0x5c);
    float speedRandHalf = 0.5f * speedRandRange;

    memset(particleData, 0, 0x1f8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, 0x30);
    }
    if (particleColor != 0) {
        memset(particleColor, 0, 0x20);
    }

    if (mode < 8) {
        Vec baseDir = *(Vec*)(paramBytes + 0x20);
        pppIVECTOR4 angles;
        pppFMATRIX rot;
        Vec tempVec;
        float spread = (float)paramBytes[0x19];
        float spreadRange = spread * 2.0f;

        angles.x = (s16)(spreadRange * RandF__5CMathFv(&Math) - spread);
        angles.y = (s16)(spreadRange * RandF__5CMathFv(&Math) - spread);
        angles.z = (s16)(spreadRange * RandF__5CMathFv(&Math) - spread);
        angles.w = 0;
        if ((mode == 2) || (mode == 3)) {
            angles.x = 0;
            angles.y = 0;
            angles.z = 0;
            angles.w = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, &baseDir, &particleData->m_velocity);
        particleData->m_velocity.x *= *(float*)(paramBytes + 0x58);
        particleData->m_velocity.y *= pYmMegaBirthShpTail3->m_velocity.x;
        particleData->m_velocity.z *= pYmMegaBirthShpTail3->m_velocity.y;
        tempVec = particleData->m_velocity;
        pppNormalize(particleData->m_velocity, tempVec);
    }

    if ((mode < 6) && (speedRandRange != 0.0f)) {
        u8 randType = paramBytes[0x6a];

        if (randType <= 1) {
            if (randType == 1) {
                RandF__5CMathFv(&Math);
            }
            particleData->m_matrix[0][0] = speedRandRange * RandF__5CMathFv(&Math) - speedRandHalf;
            particleData->m_matrix[0][1] = speedRandRange * RandF__5CMathFv(&Math) - speedRandHalf;
            particleData->m_matrix[0][2] = speedRandRange * RandF__5CMathFv(&Math) - speedRandHalf;
        } else if (randType == 3) {
            particleData->m_matrix[0][0] =
                -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) -
                speedRandHalf;
            particleData->m_matrix[0][1] =
                -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) -
                speedRandHalf;
            particleData->m_matrix[0][2] =
                -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) -
                speedRandHalf;
        } else if (randType == 5) {
            particleData->m_matrix[0][0] = -(0.5f * (RandF__5CMathFv(&Math) *
                                                     (speedRandRange * RandF__5CMathFv(&Math) *
                                                      RandF__5CMathFv(&Math))) -
                                             speedRandRange) -
                                            speedRandHalf;
            particleData->m_matrix[0][1] = -(0.5f * (RandF__5CMathFv(&Math) *
                                                     (speedRandRange * RandF__5CMathFv(&Math) *
                                                      RandF__5CMathFv(&Math))) -
                                             speedRandRange) -
                                            speedRandHalf;
            particleData->m_matrix[0][2] = -(0.5f * (RandF__5CMathFv(&Math) *
                                                     (speedRandRange * RandF__5CMathFv(&Math) *
                                                      RandF__5CMathFv(&Math))) -
                                             speedRandRange) -
                                            speedRandHalf;
        } else {
            particleData->m_matrix[0][0] =
                RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
            particleData->m_matrix[0][1] =
                RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
            particleData->m_matrix[0][2] =
                RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
        }

        particleData->m_matrix[0][0] *= *(float*)(paramBytes + 0x58);
        particleData->m_matrix[0][1] *= pYmMegaBirthShpTail3->m_velocity.x;
        particleData->m_matrix[0][2] *= pYmMegaBirthShpTail3->m_velocity.y;
    } else if ((mode >= 10) && (speedRandRange != 0.0f)) {
        u8 randType = paramBytes[0x6a];
        float scale = speedRandRange;

        if (randType == 3) {
            scale = -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange);
        } else if (randType == 1) {
            RandF__5CMathFv(&Math);
            scale = speedRandRange * RandF__5CMathFv(&Math);
        } else if (randType == 2) {
            scale = RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math));
        } else if (randType == 4) {
            scale = RandF__5CMathFv(&Math) * (RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)));
        } else if (randType == 5) {
            scale = -(0.5f * (RandF__5CMathFv(&Math) *
                              (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math))) -
                      speedRandRange);
        }

        Vec velocity = particleData->m_velocity;
        pppScaleVectorXYZ(particleData->m_velocity, velocity, scale);
    }

    if (paramBytes[0x16] != 0) {
        particleData->m_directionTail.x = (float)vColor->m_alpha;
        *(((u8*)&particleData->m_directionTail.y) + 1) = paramBytes[0x16];
    }
    if (paramBytes[0x17] != 0) {
        *(((u8*)&particleData->m_directionTail.y) + 2) = paramBytes[0x17];
    }

    particleData->m_matrix[2][2] = pYmMegaBirthShpTail3->m_colorDeltaAdd[1];
    particleData->m_matrix[2][3] = pYmMegaBirthShpTail3->m_sizeStart;
    if (pYmMegaBirthShpTail3->m_colorDeltaAdd[3] != 0.0f) {
        particleData->m_matrix[2][2] +=
            (2.0f * pYmMegaBirthShpTail3->m_colorDeltaAdd[3]) * RandF__5CMathFv(&Math) -
            pYmMegaBirthShpTail3->m_colorDeltaAdd[3];
    }

    if (*(s16*)(paramBytes + 0x11) == 0) {
        *(u16*)(particleBytes + 0x22) = 0xFFFF;
    } else {
        *(s16*)(particleBytes + 0x22) = *(s16*)(paramBytes + 0x11);
    }
    *((u8*)&particleData->m_directionTail.y) = 0;

    if (particleWMat != 0) {
        memcpy(particleWMat, &vYmMegaBirthShpTail3->m_emitterMatrix, 0x30);
    }

    particleData->m_colorDeltaAdd[0] = 0.0f;
    particleData->m_colorDeltaAdd[1] = 0.0f;
    particleData->m_colorDeltaAdd[2] = 0.0f;
    particleData->m_colorDeltaAdd[3] = 0.0f;
    *(((u8*)&particleData->m_directionTail.z) + 2) = 0;
    *((u8*)&particleData->m_directionTail.z) = 0;
    *(((u8*)&particleData->m_directionTail.y) + 3) = 0x1f;
    *((u8*)&particleData->m_directionTail.z) = *(((u8*)&particleData->m_directionTail.y) + 3) - 1;
}

/*
 * --INFO--
 * PAL Address: 8008d9f8
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3, 
                     PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, _PARTICLE_DATA* particleData, 
                     VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    unsigned int uVar4 = (unsigned int)vColor->m_alpha;
    
    // Update particle color if present
    if (particleColor != nullptr) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        
        uVar4 = (unsigned int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (uVar4 > 0xff) {
            uVar4 = 0xff;
        }
    }
    
    particleData->m_matrix[2][2] = particleData->m_matrix[2][2] + pYmMegaBirthShpTail3->m_colorDeltaAdd[2];
    particleData->m_matrix[2][3] = particleData->m_matrix[2][3] + pYmMegaBirthShpTail3->m_sizeVal;
    
    // Age particle and update lifetime
    *(char*)&(particleData->m_directionTail).y = *(char*)&(particleData->m_directionTail).y + 1;
    
    // Alpha fade logic with timing
    unsigned int fadeTime = (unsigned int)*(unsigned char*)((int)&(particleData->m_directionTail).y + 1);
    if (fadeTime != 0 && *(unsigned char*)&(particleData->m_directionTail).y <= fadeTime) {
        particleData->m_directionTail.x = particleData->m_directionTail.x - 
            (float)(uVar4) / (float)(fadeTime);
        if (particleData->m_directionTail.x < 0.0f) {
            particleData->m_directionTail.x = 0.0f;
        }
    }
    
    // Second fade phase logic
    unsigned short fadeTime2 = (unsigned short)*(unsigned char*)((int)&(particleData->m_directionTail).y + 2);
    if (fadeTime2 != 0 && *(unsigned short*)((int)particleData->m_matrix[2] + 2) <= fadeTime2) {
        unsigned char fadeInFrames = *((unsigned char*)&pYmMegaBirthShpTail3->m_matrix[1] + 7);
        if (fadeInFrames != 0) {
            particleData->m_directionTail.x = particleData->m_directionTail.x + 
                (float)(uVar4) / (float)(fadeInFrames);
            if (particleData->m_directionTail.x > 1.0f) {
                particleData->m_directionTail.x = 1.0f;
            }
        }
    }
    
    // Timer initialization
    if (*(char*)&(particleData->m_directionTail).z == 0) {
        *(char*)&(particleData->m_directionTail).z = *(char*)((int)&(particleData->m_directionTail).y + 3);
    }
    *(char*)&(particleData->m_directionTail).z = *(char*)&(particleData->m_directionTail).z - 1;
    
    // Transform particle position using local matrix
    PSMTXMultVec(pppPObject->m_localMatrix.value, (Vec*)particleData,
                 (Vec*)(particleData->m_colorDeltaAdd + 
                       (unsigned int)*(unsigned char*)&(particleData->m_directionTail).z * 3 + 0x11));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8008d3a4
 * PAL Size: 1620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, PYmMegaBirthShpTail3* param, UnkC* offsets)
{
    bool hasRequiredMemory;
    int spawnCount = 0;
    int colorOffset;
    u8* paramPayload;
    u8* particleData;
    u32 i;
    _PARTICLE_WMAT* worldMat;
    _PARTICLE_COLOR* particleColor;
    VYmMegaBirthShpTail3* work;

    colorOffset = offsets->m_serializedDataOffsets[1];
    work = (VYmMegaBirthShpTail3*)((u8*)object + 8 + offsets->m_serializedDataOffsets[2]);
    paramPayload = (u8*)&param->m_matrix;

    if (work->m_particles == 0) {
        work->m_maxParticles = *(u16*)(paramPayload + 0xe);
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_maxParticles * 0x1f8, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail3_cpp, 0x2db);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * 0x1f8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_maxParticles * 0x30, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail3_cpp, 0x2e3);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * 0x30);
        }

        work->m_tailScaleDirection = param->m_directionTail;
        PSVECNormalize(&work->m_tailScaleDirection, &work->m_tailScaleDirection);
    }

    hasRequiredMemory = (work->m_particles != 0) && (work->m_wmats != 0);
    if (!hasRequiredMemory) {
        return;
    }

    *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(work[1].m_emitterMatrix.value[1] + 2);
    *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)work[1].m_emitterMatrix.value[1];

    *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2);

    *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 3);
    *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 1);

    *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6);

    *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(work[1].m_emitterMatrix.value[2] + 2);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 8) += *(s16*)work[1].m_emitterMatrix.value[2];

    *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2);

    *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(work[1].m_emitterMatrix.value[2] + 3);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xc) += *(s16*)(work[1].m_emitterMatrix.value[2] + 1);

    *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe);
    *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6);

    if ((float)object->field0_0x0.m_graphId == *(float*)paramPayload) {
        *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)(paramPayload + 0x88);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x8a);
        *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(paramPayload + 0x8c);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)(paramPayload + 0x8e);

        *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(paramPayload + 0x88);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x8a);
        *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(paramPayload + 0x8c);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)(paramPayload + 0x8e);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x90);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa) += *(s16*)(paramPayload + 0x92);
        *(s16*)(work[1].m_emitterMatrix.value[1] + 3) += *(s16*)(paramPayload + 0x94);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe) += *(s16*)(paramPayload + 0x96);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x84);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)(paramPayload + 0x86);
        *(s16*)(work[1].m_emitterMatrix.value[0] + 3) += *(s16*)(paramPayload + 0x88);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)(paramPayload + 0x8a);

        *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(paramPayload + 0x98);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0x9a);
        *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(paramPayload + 0x9c);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)(paramPayload + 0x9e);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0xa0);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa) += *(s16*)(paramPayload + 0xa2);
        *(s16*)(work[1].m_emitterMatrix.value[2] + 3) += *(s16*)(paramPayload + 0xa4);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe) += *(s16*)(paramPayload + 0xa6);
    }

    switch (*(paramPayload + 0x12)) {
    default:
        PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_emitterMatrix.value);
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        PSMTXIdentity(work->m_emitterMatrix.value);
        work->m_emitterMatrix.value[0][0] = pppMngStPtr->m_scale.x;
        work->m_emitterMatrix.value[1][1] = pppMngStPtr->m_scale.x;
        work->m_emitterMatrix.value[2][2] = pppMngStPtr->m_scale.x;
        work->m_emitterMatrix.value[0][3] = pppMngStPtr->m_position.x;
        work->m_emitterMatrix.value[1][3] = pppMngStPtr->m_position.y;
        work->m_emitterMatrix.value[2][3] = pppMngStPtr->m_position.z;
        break;
    }

    worldMat = work->m_wmats;
    particleColor = work->m_colors;
    particleData = (u8*)work->m_particles;

    if ((DAT_8032ed70 != 0) || (*(float*)(paramPayload + 4) == 9.18341e-41f)) {
        return;
    }

    work->m_lifeLimit = work->m_lifeLimit + 1;
    for (i = 0; i < work->m_maxParticles; i++) {
        if (*(s16*)(particleData + 0x22) == 0) {
            if ((*(u16*)(paramPayload + 0x12) <= work->m_lifeLimit) && (spawnCount < *(u16*)(paramPayload + 0x10))) {
                birth(&object->field0_0x0, work, param, (VColor*)((u8*)object + 8 + colorOffset),
                      (_PARTICLE_DATA*)particleData, worldMat, particleColor);
                spawnCount = spawnCount + 1;
            }
        } else {
            calc(&object->field0_0x0, work, param, (_PARTICLE_DATA*)particleData,
                 (VColor*)((u8*)object + 8 + colorOffset), particleColor);
        }

        if (worldMat != 0) {
            worldMat = worldMat + 1;
        }
        if (particleColor != 0) {
            particleColor = particleColor + 1;
        }
        particleData = particleData + 0x1f8;
    }

    if (spawnCount > 0) {
        work->m_lifeLimit = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, UnkB*, UnkC*)
{
	// TODO
}
