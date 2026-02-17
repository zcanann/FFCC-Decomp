#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>
#include <string.h>

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern "C" void pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*);
extern float lbl_80330560;
extern pppFMATRIX g_matUnit2;
extern s32 DAT_8032ed70;

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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* obj, PYmMegaBirthShpTail2* param, UnkC* offs)
{
    static char s_pppYmMegaBirthShpTail2_cpp[] = "pppYmMegaBirthShpTail2.cpp";
    VYmMegaBirthShpTail2* work;
    VColor* colorBase;
    u8* paramBytes = (u8*)param;
    u16 spawnCount;
    u16 spawnDelay;
    u8 mode;
    u32 spawnedThisFrame;

    colorBase = (VColor*)((u8*)obj + 0x80 + offs->m_serializedDataOffsets[1]);
    work = (VYmMegaBirthShpTail2*)((u8*)obj + 0x80 + offs->m_serializedDataOffsets[2]);

    if (work->m_particles == (_PARTICLE_DATA*)0) {
        u32 maxCount;
        Vec dirCopy;

        maxCount = *(u16*)((u8*)&param->m_matrix + 0xe);
        work->m_maxParticles = maxCount;

        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            maxCount * 0x1b8, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp, 0x30e);
        if (work->m_particles != (_PARTICLE_DATA*)0) {
            memset(work->m_particles, 0, maxCount * 0x1b8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            maxCount * 0x30, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp, 0x316);
        if (work->m_wmats != (_PARTICLE_WMAT*)0) {
            memset(work->m_wmats, 0, maxCount * 0x30);
        }

        if (paramBytes[0x69] != 0) {
            work->m_colors = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                maxCount << 5, pppEnvStPtr->m_stagePtr, s_pppYmMegaBirthShpTail2_cpp, 0x31e);
            if (work->m_colors != (_PARTICLE_COLOR*)0) {
                memset(work->m_colors, 0, maxCount << 5);
            }
        }

        work->m_tailScaleDirection = param->m_directionTail;
        dirCopy = work->m_tailScaleDirection;
        pppNormalize__FR3Vec3Vec((float*)&work->m_tailScaleDirection, &dirCopy);
    }

    if ((work->m_particles == (_PARTICLE_DATA*)0) ||
        (work->m_wmats == (_PARTICLE_WMAT*)0) ||
        ((paramBytes[0x69] != 0) && (work->m_colors == (_PARTICLE_COLOR*)0))) {
        return;
    }

    mode = paramBytes[0x12];
    switch (mode) {
    default: {
        pppFMATRIX local;
        local = pppMngStPtr->m_matrix;
        pppCopyMatrix__FR10pppFMATRIX10pppFMATRIX((pppFMATRIX*)work, &local);
        break;
    }
    case 1:
    case 3:
    case 5:
    case 7:
    case 9: {
        Vec axis;
        float scale;

        PSMTXIdentity(work->m_emitterMatrix.value);
        scale = pppMngStPtr->m_scale.x;

        axis.x = work->m_emitterMatrix.value[0][0];
        axis.y = work->m_emitterMatrix.value[1][0];
        axis.z = work->m_emitterMatrix.value[2][0];
        PSVECScale(&axis, &axis, scale);
        work->m_emitterMatrix.value[0][0] = axis.x;
        work->m_emitterMatrix.value[1][0] = axis.y;
        work->m_emitterMatrix.value[2][0] = axis.z;

        axis.x = work->m_emitterMatrix.value[0][1];
        axis.y = work->m_emitterMatrix.value[1][1];
        axis.z = work->m_emitterMatrix.value[2][1];
        PSVECScale(&axis, &axis, scale);
        work->m_emitterMatrix.value[0][1] = axis.x;
        work->m_emitterMatrix.value[1][1] = axis.y;
        work->m_emitterMatrix.value[2][1] = axis.z;

        axis.x = work->m_emitterMatrix.value[0][2];
        axis.y = work->m_emitterMatrix.value[1][2];
        axis.z = work->m_emitterMatrix.value[2][2];
        PSVECScale(&axis, &axis, scale);
        work->m_emitterMatrix.value[0][2] = axis.x;
        work->m_emitterMatrix.value[1][2] = axis.y;
        work->m_emitterMatrix.value[2][2] = axis.z;

        work->m_emitterMatrix.value[0][3] = pppMngStPtr->m_position.x;
        work->m_emitterMatrix.value[1][3] = pppMngStPtr->m_position.y;
        work->m_emitterMatrix.value[2][3] = pppMngStPtr->m_position.z;
        break;
    }
    }

    if ((DAT_8032ed70 != 0) || (*(u16*)(paramBytes + 0x0) == 0)) {
        return;
    }

    work->m_lifeLimit++;
    spawnCount = *(u16*)(paramBytes + 0x10);
    spawnDelay = *(u16*)(paramBytes + 0x12);
    spawnedThisFrame = 0;

    {
        u32 i;
        _PARTICLE_DATA* particle = work->m_particles;
        PARTICLE_WMAT* wmat = (PARTICLE_WMAT*)work->m_wmats;
        _PARTICLE_COLOR* color = work->m_colors;

        for (i = 0; i < work->m_maxParticles; i++) {
            if (*(s16*)((u8*)particle->m_matrix[2] + 2) == 0) {
                if ((work->m_lifeLimit >= spawnDelay) && (spawnedThisFrame < spawnCount)) {
                    birth(&obj->field0_0x0, work, param, colorBase, particle, (_PARTICLE_WMAT*)wmat, color);
                    spawnedThisFrame++;
                }
            } else {
                calc__FP11_pppPObjectP20VYmMegaBirthShpTail2P20PYmMegaBirthShpTail2P14_PARTICLE_DATAP6VColorP15_PARTICLE_COLOR(
                    &obj->field0_0x0, work, param, particle, colorBase, color);
            }

            if (wmat != (PARTICLE_WMAT*)0) {
                wmat++;
            }
            if (color != (_PARTICLE_COLOR*)0) {
                color++;
            }
            particle = (_PARTICLE_DATA*)((u8*)particle + 0x1b8);
        }
    }

    if (spawnedThisFrame > 0) {
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
