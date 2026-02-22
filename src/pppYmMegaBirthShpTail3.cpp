#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/pppPart.h"
#include "dolphin/mtx.h"
#include <string.h>

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
    // Complex particle initialization based on Ghidra decomp
    // Initialize matrix data
    if (particleData != nullptr) {
        // Basic matrix initialization
        PSMTXIdentity(particleData->m_matrix);
    }
    
    // Initialize color data if provided
    if (particleColor != nullptr) {
        particleColor->m_color[0] = 0.0f;
        particleColor->m_color[1] = 0.0f;
        particleColor->m_color[2] = 0.0f;
        particleColor->m_color[3] = 0.0f;
    }
    
    // Basic randomization setup
    if (pYmMegaBirthShpTail3 != nullptr) {
        // Initialize matrix
        PSMTXIdentity(pYmMegaBirthShpTail3->m_matrix);
    }
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
    
    // Update matrix values - placeholder implementation
    particleData->m_matrix[2][2] = particleData->m_matrix[2][2] + 0.1f; // placeholder
    particleData->m_matrix[2][3] = particleData->m_matrix[2][3] + 0.1f; // placeholder
    
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
        particleData->m_directionTail.x = particleData->m_directionTail.x + 
            (float)(uVar4) / (float)(fadeTime2);
        if (particleData->m_directionTail.x > 1.0f) {
            particleData->m_directionTail.x = 1.0f;
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
        work->m_emitterMatrix.value[1][1] = pppMngStPtr->m_scale.y;
        work->m_emitterMatrix.value[2][2] = pppMngStPtr->m_scale.z;
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
