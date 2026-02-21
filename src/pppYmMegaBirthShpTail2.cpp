#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include <dolphin/mtx.h>
#include <string.h>

class CMath;
extern CMath Math;
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" float RandF__5CMathFv(CMath*);
extern "C" int __cntlzw(unsigned int);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" void pppSetBlendMode__FUc(unsigned char);
extern "C" void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);
extern float lbl_80330560;
extern pppFMATRIX g_matUnit2;
extern s32 DAT_8032ed70;

static char s_pppYmMegaBirthShpTail2_cpp_801d9c68[] = "pppYmMegaBirthShpTail2.cpp";

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
void U8ToF32(pppFVECTOR4*, unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VYmMegaBirthShpTail2* vdata, PYmMegaBirthShpTail2* param)
{
	vdata->m_maxParticles = *(unsigned short*)((char*)&param->m_matrix + 0xe);
	// TODO: Proper memory allocation
	vdata->m_particles = (_PARTICLE_DATA*)0;
	vdata->m_wmats = (_PARTICLE_WMAT*)0;
	vdata->m_colors = (_PARTICLE_COLOR*)0;
}

/*
 * --INFO--
 * PAL Address: 0x8008ca1c
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, UnkC* param2)
{
    pppFMATRIX* work = (pppFMATRIX*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    float initVal;

    pppUnitMatrix__FR10pppFMATRIX(work);
    initVal = lbl_80330560;

    work[1].value[0][2] = initVal;
    work[1].value[0][1] = initVal;
    work[1].value[0][0] = initVal;
    work[1].value[0][3] = 0.0f;
    work[1].value[1][0] = 0.0f;
    work[1].value[1][1] = 0.0f;
    work[1].value[1][2] = 0.0f;
    *(u16*)(work[1].value[1] + 3) = 0;
    *(u16*)((u8*)work[1].value[1] + 0xe) = 0;
    *(u16*)(work[1].value[1] + 3) = 10000;
    pppUnitMatrix__FR10pppFMATRIX(&g_matUnit2);
}

/*
 * --INFO--
 * PAL Address: 0x8008c9a0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, UnkC* param2)
{
    u8* work = (u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2];
    void** ptrBc = (void**)(work + 0x3c);
    void** ptrC0 = (void**)(work + 0x40);
    void** ptrC4 = (void**)(work + 0x44);

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
 * PAL Address: 0x8008bb28
 * PAL Size: 3704b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail2* work, PYmMegaBirthShpTail2* param, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    u8* paramBytes = (u8*)param;
    u8* particleBytes = (u8*)particleData;
    u8 mode = paramBytes[0x12];
    float speedRandRange = *(float*)(paramBytes + 0x5c);
    float speedRandHalf = 0.5f * speedRandRange;

    memset(particleData, 0, 0x1b8);
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
        particleData->m_velocity.y *= param->m_velocity.x;
        particleData->m_velocity.z *= param->m_velocity.y;
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
            particleData->m_matrix[0][0] = -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) - speedRandHalf;
            particleData->m_matrix[0][1] = -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) - speedRandHalf;
            particleData->m_matrix[0][2] = -(2.0f * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math)) - speedRandRange) - speedRandHalf;
        } else if (randType == 5) {
            particleData->m_matrix[0][0] =
                -(0.5f * (RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math))) - speedRandRange) - speedRandHalf;
            particleData->m_matrix[0][1] =
                -(0.5f * (RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math))) - speedRandRange) - speedRandHalf;
            particleData->m_matrix[0][2] =
                -(0.5f * (RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math))) - speedRandRange) - speedRandHalf;
        } else {
            particleData->m_matrix[0][0] = RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
            particleData->m_matrix[0][1] = RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
            particleData->m_matrix[0][2] = RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math)) - speedRandHalf;
        }

        particleData->m_matrix[0][0] *= *(float*)(paramBytes + 0x58);
        particleData->m_matrix[0][1] *= param->m_velocity.x;
        particleData->m_matrix[0][2] *= param->m_velocity.y;
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
            scale = -(0.5f * (RandF__5CMathFv(&Math) * (speedRandRange * RandF__5CMathFv(&Math) * RandF__5CMathFv(&Math))) - speedRandRange);
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

    particleData->m_matrix[2][2] = param->m_colorDeltaAdd[1];
    particleData->m_matrix[2][3] = param->m_sizeStart;
    if (param->m_colorDeltaAdd[3] != 0.0f) {
        particleData->m_matrix[2][2] += (2.0f * param->m_colorDeltaAdd[3]) * RandF__5CMathFv(&Math) - param->m_colorDeltaAdd[3];
    }

    if (*(s16*)(paramBytes + 0x11) == 0) {
        *(u16*)(particleBytes + 0x22) = 0xFFFF;
    } else {
        *(s16*)(particleBytes + 0x22) = *(s16*)(paramBytes + 0x11);
    }
    *((u8*)&particleData->m_directionTail.y) = 0;

    if (particleWMat != 0) {
        memcpy(particleWMat, &work->m_emitterMatrix, 0x30);
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
 * PAL Address: 0x8008b824
 * PAL Size: 772b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR(
    _pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
    PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, _PARTICLE_DATA*, VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    u8* color = (u8*)vColor;
    u32 alpha = 0;
    float* blend = (float*)(color + 0x30);
    float* velocityScale = (float*)(color + 0x28);
    float* tailScale = (float*)(color + 0x2c);
    u8* frameState = color + 0x30;
    u8 frameWindow;
    u8 fadeInFrames;
    u8 historyIndex;
    u16 frameIndex;
    int colorTable;
    int frameEntry;
    s16 frameDuration;
    Vec local;
    Vec scaled;

    if (particleColor != 0) {
        alpha = ((u8*)particleColor)[0xb];
    }

    *velocityScale = *velocityScale + pYmMegaBirthShpTail2->m_colorDeltaAdd[2];
    *tailScale = *tailScale + pYmMegaBirthShpTail2->m_sizeVal;

    local.x = *(float*)(color + 0x10);
    local.y = *(float*)(color + 0x14);
    local.z = *(float*)(color + 0x18);
    scaled.x = local.x * *velocityScale;
    scaled.y = local.y * *velocityScale;
    scaled.z = local.z * *velocityScale;
    *(float*)(color + 0x00) = *(float*)(color + 0x00) + scaled.x;
    *(float*)(color + 0x04) = *(float*)(color + 0x04) + scaled.y;
    *(float*)(color + 0x08) = *(float*)(color + 0x08) + scaled.z;

    scaled.x = vYmMegaBirthShpTail2->m_tailScaleDirection.x * *tailScale;
    scaled.y = vYmMegaBirthShpTail2->m_tailScaleDirection.y * *tailScale;
    scaled.z = vYmMegaBirthShpTail2->m_tailScaleDirection.z * *tailScale;
    *(float*)(color + 0x00) = *(float*)(color + 0x00) + scaled.x;
    *(float*)(color + 0x04) = *(float*)(color + 0x04) + scaled.y;
    *(float*)(color + 0x08) = *(float*)(color + 0x08) + scaled.z;

    if (*(s16*)((u8*)&pYmMegaBirthShpTail2->m_matrix[1] + 0x4) != 0) {
        *(s16*)(color + 0x22) = *(s16*)(color + 0x22) - 1;
    }

    frameState[4] = frameState[4] + 1;
    frameWindow = frameState[5];
    if ((frameWindow != 0) && (frameState[4] <= frameWindow)) {
        *blend = *blend - ((float)alpha / (float)frameWindow);
        if (*blend < lbl_80330560) {
            *blend = lbl_80330560;
        }
    }

    if ((frameState[6] != 0) && (*(u16*)(color + 0x22) <= frameState[6])) {
        fadeInFrames = *((u8*)&pYmMegaBirthShpTail2->m_matrix[1] + 7);
        if (fadeInFrames != 0) {
            *blend = *blend + ((float)alpha / (float)fadeInFrames);
            if (*blend > 1.0f) {
                *blend = 1.0f;
            }
        }
    }

    if (frameState[8] == 0) {
        frameState[8] = frameState[7];
    }
    frameState[8] = frameState[8] - 1;
    historyIndex = frameState[8];

    PSMTXMultVec(pppPObject->m_localMatrix.value, (Vec*)(color + 0x0),
                 (Vec*)(color + ((historyIndex + 5) * sizeof(VColor)) + 0x4));

    frameIndex = *(u16*)(color + 0x1e);
    colorTable = **(int**)(*(int*)&pppEnvStPtr->m_particleColors[0] +
                           (int)pYmMegaBirthShpTail2->m_matrix[0][1] * 4);
    *(u16*)(color + 0x20) = frameIndex;

    frameEntry = colorTable + (u32)frameIndex * 8 + 0x10;
    *(s16*)(color + 0x1c) = *(s16*)(color + 0x1c) + *(s16*)((u8*)pYmMegaBirthShpTail2->m_matrix[0] + 8);
    frameDuration = *(s16*)(frameEntry + 2);
    if ((int)frameDuration <= *(u16*)(color + 0x1c)) {
        *(u16*)(color + 0x1c) = *(u16*)(color + 0x1c) - frameDuration;
        *(s16*)(color + 0x1e) = *(s16*)(color + 0x1e) + 1;
        if ((int)*(s16*)(colorTable + 6) <= *(u16*)(color + 0x1e)) {
            if ((*(u8*)(frameEntry + 4) & 0x80) == 0) {
                color[0x1c] = 0;
                color[0x1d] = 0;
                *(s16*)(color + 0x1e) = *(s16*)(color + 0x1e) - 1;
            } else {
                color[0x1e] = 0;
                color[0x1f] = 0;
                color[0x1c] = 0;
                color[0x1d] = 0;
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calc_particle(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* param, UnkC* offsets)
{
    bool hasRequiredMemory;
    int spawnCount = 0;
    u8* paramPayload;
    u8* particleData;
    int colorOffset;
    u32 i;
    _PARTICLE_WMAT* worldMat;
    _PARTICLE_COLOR* particleColor;
    VYmMegaBirthShpTail2* work;

    colorOffset = offsets->m_serializedDataOffsets[1];
    work = (VYmMegaBirthShpTail2*)((u8*)object + 0x80 + offsets->m_serializedDataOffsets[2]);
    paramPayload = (u8*)param;

    if (work->m_particles == 0) {
        work->m_maxParticles = *(u16*)((u8*)&param->m_matrix + 0xe);
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_maxParticles * 0x1b8, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp_801d9c68, 0x30e);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * 0x1b8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_maxParticles * 0x30, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp_801d9c68, 0x316);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * 0x30);
        }

        if (paramPayload[0x69] != 0) {
            work->m_colors = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                work->m_maxParticles << 5, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp_801d9c68, 0x31e);
            if (work->m_colors != 0) {
                memset(work->m_colors, 0, work->m_maxParticles << 5);
            }
        }

        work->m_tailScaleDirection = param->m_directionTail;
        PSVECNormalize(&work->m_tailScaleDirection, &work->m_tailScaleDirection);
    }

    if (work->m_particles == 0) {
        hasRequiredMemory = false;
    } else if (work->m_wmats == 0) {
        hasRequiredMemory = false;
    } else if ((paramPayload[0x69] == 0) || (work->m_colors != 0)) {
        hasRequiredMemory = true;
    } else {
        hasRequiredMemory = false;
    }

    if (!hasRequiredMemory) {
        return;
    }

    switch (paramPayload[0x16]) {
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

    if ((DAT_8032ed70 != 0) || (paramPayload[0x16] == 0)) {
        return;
    }

    worldMat = work->m_wmats;
    particleColor = work->m_colors;
    particleData = (u8*)work->m_particles;
    work->m_lifeLimit = work->m_lifeLimit + 1;

    for (i = 0; i < work->m_maxParticles; i++) {
        if (*(s16*)(particleData + 0x22) == 0) {
            if ((*(u16*)((u8*)&param->m_matrix + 0x12) <= work->m_lifeLimit) &&
                (spawnCount < *(u16*)((u8*)&param->m_matrix + 0x10))) {
                birth(&object->field0_0x0, work, param, (VColor*)((u8*)object + 0x80 + colorOffset),
                    (_PARTICLE_DATA*)particleData, worldMat, particleColor);
                spawnCount = spawnCount + 1;
            }
        } else {
            calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR(
                &object->field0_0x0, work, param, (_PARTICLE_DATA*)particleData, (VColor*)particleData,
                (_PARTICLE_COLOR*)((u8*)object + 0x80 + colorOffset));
        }

        if (worldMat != 0) {
            worldMat = worldMat + 1;
        }
        if (particleColor != 0) {
            particleColor = particleColor + 1;
        }
        particleData = particleData + 0x1b8;
    }

    if (spawnCount > 0) {
        work->m_lifeLimit = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, UnkB* stepData, UnkC* offsets)
{
    u8* step = (u8*)stepData;
    u8* payload = step + 0x14;
    const u16 dataValIndex = *(u16*)step;
    const s32 particleDataOffset = offsets->m_serializedDataOffsets[2];
    _PARTICLE_DATA* particles = *(_PARTICLE_DATA**)((u8*)&object->field_0xbc + particleDataOffset);
    _PARTICLE_WMAT* wmats = *(_PARTICLE_WMAT**)((u8*)&object->field_0xc0 + particleDataOffset);
    _PARTICLE_COLOR* colors = *(_PARTICLE_COLOR**)((u8*)&object->field_0xc4 + particleDataOffset);
    const u32 maxParticles = *(u32*)((u8*)&object->field_0xc8 + particleDataOffset);
    bool hasRequiredMemory = false;

    if (particles != 0 && wmats != 0) {
        hasRequiredMemory = (payload[0x55] == 0) || (colors != 0);
    }
    if (!hasRequiredMemory || dataValIndex == 0xFFFF) {
        return;
    }

    int shapeTable = **(int**)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
    const u8 zEnable = (u8)(((u32)__cntlzw((u32)payload[0x57])) >> 5);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (void*)(payload + 0x74), &object->field_0x40, *(float*)(payload + 0x74), payload[0x78], step[0x10],
        payload[0x5A], 0, zEnable, 1, 0);
    pppSetBlendMode__FUc(payload[0x5A]);

    for (u32 i = 0; i < maxParticles; i++) {
        u8* particle = (u8*)particles + i * 0x1B8;
        if (*(s16*)(particle + 0x22) != 0) {
            const u16 frameCountRaw = *(u16*)(payload + 0x70);
            if (frameCountRaw != 0) {
                pppFMATRIX drawMtx;
                Vec drawPos;
                Vec cameraPos;
                Vec managerPos;
                Vec zeroVec;
                GXColor amb;
                const s16 shapeOffset = *(s16*)(shapeTable + (u16)*(u16*)(particle + 0x20) * 8 + 0x10);
                const u8 trailReadIndex = *(u8*)(particle + 0x38);
                const u8 trailMaxIndex = (u8)(*(u8*)(particle + 0x37) - 1);
                u8 trailNextIndex = (u8)(trailReadIndex + 1);
                float drawScale = (float)payload[0x64];
                const float drawScaleStep =
                    (drawScale - (float)payload[0x68]) / ((frameCountRaw > 1) ? (float)(frameCountRaw - 1) : 1.0f);
                float fadeR = (float)payload[0x64];
                float fadeG = (float)payload[0x65];
                float fadeB = (float)payload[0x66];
                float fadeA = (float)payload[0x67];
                const float fadeRStep =
                    (fadeR - (float)payload[0x68]) / ((frameCountRaw > 1) ? (float)(frameCountRaw - 1) : 1.0f);
                const float fadeGStep =
                    (fadeG - (float)payload[0x69]) / ((frameCountRaw > 1) ? (float)(frameCountRaw - 1) : 1.0f);
                const float fadeBStep =
                    (fadeB - (float)payload[0x6A]) / ((frameCountRaw > 1) ? (float)(frameCountRaw - 1) : 1.0f);
                const float fadeAStep =
                    (fadeA - (float)payload[0x6B]) / ((frameCountRaw > 1) ? (float)(frameCountRaw - 1) : 1.0f);
                const float spacing = *(float*)(payload + 0x6C);
                Vec* history = (Vec*)(particle + 0x40);
                Vec segVec;
                float segLen;
                float segProgress = 0.0f;
                u16 frameCount = frameCountRaw;

                if (trailReadIndex == trailMaxIndex) {
                    trailNextIndex = 0;
                }

                drawPos = history[trailReadIndex];
                cameraPos = history[trailNextIndex];
                segVec.x = cameraPos.x - drawPos.x;
                segVec.y = cameraPos.y - drawPos.y;
                segVec.z = cameraPos.z - drawPos.z;
                zeroVec.x = 0.0f;
                zeroVec.y = 0.0f;
                zeroVec.z = 0.0f;
                segLen = PSVECDistance(&zeroVec, &segVec);

                if (payload[0x72] == 0) {
                    continue;
                }

                while (frameCount != 0) {
                    Vec trailPos = drawPos;
                    bool canDraw = (trailPos.x != 0.0f) || (trailPos.y != 0.0f) || (trailPos.z != 0.0f);
                    if (canDraw) {
                        pppUnitMatrix__FR10pppFMATRIX(&drawMtx);
                        drawMtx.value[0][0] = drawScale * pppMngStPtr->m_scale.x;
                        drawMtx.value[1][1] = drawScale * pppMngStPtr->m_scale.y;
                        drawMtx.value[2][2] = drawScale * pppMngStPtr->m_scale.z;

                        if (payload[0x79] == 0) {
                            PSMTXMultVec(ppvWorldMatrix, &trailPos, &cameraPos);
                        } else if (payload[0x79] == 1) {
                            managerPos.x = pppMngStPtr->m_matrix.value[0][3];
                            managerPos.y = pppMngStPtr->m_matrix.value[1][3];
                            managerPos.z = pppMngStPtr->m_matrix.value[2][3];
                            PSVECAdd(&trailPos, &managerPos, &trailPos);
                            PSMTXMultVec(ppvCameraMatrix0, &trailPos, &cameraPos);
                        } else {
                            cameraPos = trailPos;
                        }

                        drawMtx.value[0][3] = cameraPos.x;
                        drawMtx.value[1][3] = cameraPos.y;
                        drawMtx.value[2][3] = cameraPos.z;
                        GXLoadPosMtxImm(drawMtx.value, 0);

                        amb.r = (u8)fadeR;
                        amb.g = (u8)fadeG;
                        amb.b = (u8)fadeB;
                        amb.a = (u8)(fadeA * (1.0f - *(float*)(particle + 0x30)));
                        GXSetChanAmbColor(GX_COLOR0A0, amb);
                        pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(
                            (void*)(shapeTable + shapeOffset), pppEnvStPtr->m_materialSetPtr, payload[0x5A]);
                    }

                    frameCount--;
                    if (frameCount == 0 || spacing <= 0.0f) {
                        break;
                    }

                    drawScale -= drawScaleStep;
                    fadeR -= fadeRStep;
                    fadeG -= fadeGStep;
                    fadeB -= fadeBStep;
                    fadeA -= fadeAStep;
                    if (drawScale <= 0.0f) {
                        break;
                    }

                    segProgress += spacing;
                    while (segLen > 0.0f && segProgress > segLen) {
                        const float overflow = segProgress - segLen;
                        trailNextIndex++;
                        if (trailNextIndex > trailMaxIndex) {
                            trailNextIndex = 0;
                        }
                        if (trailNextIndex == trailReadIndex) {
                            frameCount = 0;
                            break;
                        }

                        drawPos = history[trailNextIndex];
                        {
                            u8 nextTrail = (u8)(trailNextIndex + 1);
                            if (trailNextIndex == trailMaxIndex) {
                                nextTrail = 0;
                            }
                            cameraPos = history[nextTrail];
                        }
                        segVec.x = cameraPos.x - drawPos.x;
                        segVec.y = cameraPos.y - drawPos.y;
                        segVec.z = cameraPos.z - drawPos.z;
                        segLen = PSVECDistance(&zeroVec, &segVec);
                        segProgress = overflow;
                    }
                    if (frameCount == 0 || segLen <= 0.0f) {
                        break;
                    }

                    {
                        const float t = segProgress / segLen;
                        drawPos.x = history[trailNextIndex].x + segVec.x * t;
                        drawPos.y = history[trailNextIndex].y + segVec.y * t;
                        drawPos.z = history[trailNextIndex].z + segVec.z * t;
                    }
                }
            }
        }
    }
}
