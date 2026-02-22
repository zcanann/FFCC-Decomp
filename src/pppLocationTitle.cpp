#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

static int GetGraphFrameFromId(u32 graphId)
{
    return ((int)graphId >> 12) + (int)((graphId & 0x80000000) != 0 && (graphId & 0xFFF) != 0);
}

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern int DAT_8032ed70;
extern "C" int rand(void);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

struct LocationTitleWork {
    void* m_particles;
    u16 m_count;
    u16 m_pad;
    float m_cur;
    float m_vel;
    float m_acc;
};

struct LocationTitleParticle {
    Vec m_pos;
    u32 m_color;
    float m_frame;
    s16 m_shapeA;
    s16 m_shapeB;
};

/*
 * --INFO--
 * PAL Address: 0x800d92cc
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLocationTitle(pppLocationTitle* pppLocationTitle, UnkC* param_2)
{
    s32* serializedOffsets = *(s32**)((u8*)param_2 + 0xC);
    u8* base = (u8*)pppLocationTitle + *serializedOffsets + 0x80;
    float value = 0.0f;

    *(u32*)(base + 0x0) = 0;
    *(u16*)(base + 0x4) = 0;
    *(float*)(base + 0x10) = value;
    *(float*)(base + 0xC) = value;
    *(float*)(base + 0x8) = value;
}

/*
 * --INFO--
 * PAL Address: 0x800d9278
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructLocationTitle(pppLocationTitle* pppLocationTitle, UnkC* param_2)
{
    int serializedOffset;
    CMemory::CStage** stagePtr;
    s32* serializedOffsets;

    serializedOffsets = *(s32**)((u8*)param_2 + 0xC);
    serializedOffset = *serializedOffsets;
    stagePtr = (CMemory::CStage**)((u8*)pppLocationTitle + serializedOffset + 0x80);

    if (*stagePtr != NULL) {
        pppHeapUseRate(*stagePtr);
        *stagePtr = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d8dac
 * PAL Size: 1228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLocationTitle(pppLocationTitle* pppLocationTitle, UnkB* param_2, UnkC* param_3)
{
    int colorOffset;
    LocationTitleWork* work;
    u16 maxCount;
    u32 graphId;
    int graphFrame;

    if (DAT_8032ed70 != 0) {
        return;
    }

    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (LocationTitleWork*)((u8*)pppLocationTitle + 8 + *param_3->m_serializedDataOffsets);
    rand();

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);
    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (param_2->m_graphId == *(u32*)pppLocationTitle) {
        work->m_cur += param_2->m_arg3;
        work->m_vel += *(float*)param_2->m_payload;
        work->m_acc += *(float*)((u8*)param_2->m_payload + 4);
    }

    maxCount = *(u16*)((u8*)&param_2->m_initWOrk + 2);
    if (work->m_particles == NULL) {
        LocationTitleParticle* particle;

        work->m_particles =
            pppMemAlloc__FUlPQ27CMemory6CStagePci(maxCount * sizeof(LocationTitleParticle),
                                                  pppEnvStPtr->m_stagePtr, (char*)"pppLocationTitle.cpp", 0x6d);
        particle = (LocationTitleParticle*)work->m_particles;

        for (u16 i = 0; i < maxCount; i++) {
            particle->m_pos.x = 0.0f;
            particle->m_pos.y = 0.0f;
            particle->m_pos.z = 0.0f;
            memcpy(&particle->m_color, (u8*)pppLocationTitle + 0x88 + colorOffset, 4);
            particle->m_frame = work->m_cur;

            s16 shape = (s16)(rand() % *(s16*)((u8*)shapeTable + 6));
            particle->m_shapeA = shape;
            particle->m_shapeB = shape;

            particle++;
        }
    }

    if (work->m_count + 1 >= maxCount) {
        return;
    }

    graphId = *(u32*)pppLocationTitle;
    graphFrame = GetGraphFrameFromId(graphId);
    if (graphFrame < *(u16*)((u8*)param_2->m_payload + 8)) {
        return;
    }

    {
        LocationTitleParticle* particles = (LocationTitleParticle*)work->m_particles;
        u16 count = work->m_count;
        pppFMATRIX localMatrix;
        pppFMATRIX managerMatrix;
        pppFMATRIX resultMatrix;

        localMatrix = *(pppFMATRIX*)((u8*)pppLocationTitle + 4);
        managerMatrix = pppMngStPtr->m_matrix;
        pppMulMatrix(resultMatrix, managerMatrix, localMatrix);

        particles[count].m_pos.x = resultMatrix.value[0][3];
        particles[count].m_pos.y = resultMatrix.value[1][3];
        particles[count].m_pos.z = resultMatrix.value[2][3];

        if ((s16)count - 1 < 0) {
            particles[count].m_frame = work->m_cur;
            memcpy(&particles[count].m_color, (u8*)pppLocationTitle + 0x88 + colorOffset, 4);
        } else {
            particles[count - 1].m_frame = work->m_cur;
            memcpy(&particles[count - 1].m_color, (u8*)pppLocationTitle + 0x88 + colorOffset, 4);
        }

        work->m_count = count + 1;
    }

    if (work->m_count > 1) {
        LocationTitleParticle* particles = (LocationTitleParticle*)work->m_particles;
        Vec subVec;
        Vec interp[50];
        LocationTitleParticle* startParticle;
        u8 stepCount = *(u8*)&param_2->m_stepValue;
        int startIndex = (int)work->m_count - 2;
        int inserted = 0;
        double stepScale = (double)(1.0f / (float)(stepCount + 1));

        startParticle = &particles[startIndex];
        PSVECSubtract(&particles[work->m_count - 1].m_pos, &startParticle->m_pos, &subVec);

        for (int i = 0; i < stepCount; i++) {
            Vec scaled;
            float t = (float)(stepScale * (double)(i + 1));

            PSVECScale(&subVec, &scaled, t);
            PSVECAdd(&startParticle->m_pos, &scaled, &interp[i]);
            inserted++;
            work->m_count++;

            if (maxCount <= (u16)(work->m_count + 1)) {
                break;
            }
        }

        pppCopyVector(particles[startIndex + inserted + 1].m_pos, particles[startIndex + 1].m_pos);

        for (int i = 0; i < inserted; i++) {
            LocationTitleParticle* dst = &particles[startIndex + i + 1];
            pppCopyVector(dst->m_pos, interp[i]);
            memcpy(&dst->m_color, (u8*)pppLocationTitle + 0x88 + colorOffset, 4);
            dst->m_frame = work->m_cur;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d8c1c
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderLocationTitle(pppLocationTitle* pppLocationTitle, UnkB* param_2, UnkC* param_3)
{
    int serializedOffset = *param_3->m_serializedDataOffsets;

    if (param_2->m_dataValIndex != 0xFFFF) {
        u32 graphId = *(u32*)pppLocationTitle;
        int fadeDivisor = -1;
        int graphFrame = GetGraphFrameFromId(graphId);
        Vec* particle = *(Vec**)((u8*)pppLocationTitle + 8 + serializedOffset);
        long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + param_2->m_dataValIndex * 4);

        u16* payload = (u16*)param_2->m_payload;
        if ((int)payload[5] <= graphFrame) {
            fadeDivisor = payload[6] + (graphFrame - (int)payload[5]);
        }

        u16 count = *(u16*)((u8*)pppLocationTitle + 12 + serializedOffset);
        for (int i = 0; i < (int)count; i++) {
            Mtx model;
            Vec worldPos;
            u32 colorWord;
            GXColor color;

            PSMTXIdentity(model);
            model[2][2] = particle[1].y;
            model[0][0] = pppMngStPtr->m_scale.x * model[2][2];
            model[1][1] = pppMngStPtr->m_scale.y * model[2][2];
            model[2][2] = pppMngStPtr->m_scale.z * model[2][2];

            PSMTXMultVec(ppvCameraMatrix0, particle, &worldPos);
            model[0][3] = worldPos.x;
            model[1][3] = worldPos.y;
            model[2][3] = worldPos.z;

            pppSetDrawEnv((pppCVECTOR*)(particle + 1), (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 0, 1, 0);

            if (fadeDivisor >= 0) {
                u8* alpha = (u8*)&particle[1].x + 3;
                *alpha = (u8)(*alpha - (*alpha / fadeDivisor));
            }

            colorWord = *(u32*)&particle[1].x;
            *(u32*)&color = colorWord;
            GXSetChanMatColor(GX_COLOR0A0, color);
            GXLoadPosMtxImm(model, 0);

            pppSetBlendMode(((u8*)&param_2->m_stepValue)[1]);
            pppDrawShp(shapeTable, *(short*)&particle[2].x, pppEnvStPtr->m_materialSetPtr,
                       ((u8*)&param_2->m_stepValue)[1]);

            particle = (Vec*)&particle[2].y;
        }
    }
}
