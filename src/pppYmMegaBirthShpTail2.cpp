#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>
#include <string.h>

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
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
 * Address:	TODO
 * Size:	TODO
 */
void birth(_pppPObject*, VYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*)
{
	// TODO
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
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, UnkB*, UnkC*)
{
	// TODO: Implement rendering
}
