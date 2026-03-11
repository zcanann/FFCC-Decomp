#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

static int GetGraphFrameFromId(u32 graphId)
{
    int frame = (int)graphId >> 12;
    if (((int)graphId < 0) && ((graphId & 0xFFF) != 0)) {
        frame++;
    }
    return frame;
}

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern "C" void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
extern float FLOAT_80330ee0;
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
    s16 m_shapeUnk;
    s16 m_shapeA;
    s16 m_shapeB;
    s16 m_pad;
};

static char s_pppLocationTitle_cpp[] = "pppLocationTitle.cpp";

/*
 * --INFO--
 * PAL Address: 0x800d92cc
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleUnkC* param_2)
{
    LocationTitleWork* work;
    f32 value;

    value = FLOAT_80330ee0;
    work = (LocationTitleWork*)((u8*)pppLocationTitle + 0x80 + *param_2->m_serializedDataOffsets);
    work->m_particles = 0;
    work->m_count = 0;
    work->m_acc = value;
    work->m_vel = value;
    work->m_cur = value;
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
void pppDestructLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleUnkC* param_2)
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
void pppFrameLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3)
{
    int colorOffset;
    LocationTitleWork* work;
    u16 maxCount;
    u32 graphId;
    u32 dataValIndex;
    int graphFrame;

    if (gPppCalcDisabled != 0) {
        return;
    }

    colorOffset = param_3->m_serializedDataOffsets[1];
    work = (LocationTitleWork*)((u8*)pppLocationTitle + 0x80 + *param_3->m_serializedDataOffsets);
    rand();

    dataValIndex = param_2->m_dataValIndex;
    if ((u16)dataValIndex == 0xFFFF) {
        return;
    }

    long* shapeTable = **(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + ((u16)dataValIndex * 4));
    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (param_2->m_graphId == pppLocationTitle->m_graphId) {
        work->m_cur += param_2->m_arg3;
        work->m_vel += param_2->m_payload0;
        work->m_acc += param_2->m_payload1;
    }

    maxCount = param_2->m_maxCount;
    if (work->m_particles == NULL) {
        LocationTitleParticle* particle;

        work->m_particles =
            pppMemAlloc__FUlPQ27CMemory6CStagePci(maxCount * sizeof(LocationTitleParticle),
                                                  pppEnvStPtr->m_stagePtr, s_pppLocationTitle_cpp, 0x6d);
        particle = (LocationTitleParticle*)work->m_particles;

        for (u16 i = 0; i < maxCount; i++) {
            int randomValue;
            s16 shapeCount;
            s16 shape;

            particle->m_pos.x = 0.0f;
            particle->m_pos.y = 0.0f;
            particle->m_pos.z = 0.0f;
            memcpy(&particle->m_color, (u8*)pppLocationTitle + 0x88 + colorOffset, 4);
            particle->m_shapeUnk = 0;
            particle->m_frame = work->m_cur;
            randomValue = rand();
            shapeCount = *(s16*)((u8*)shapeTable + 6);
            shape = (s16)randomValue - (s16)(randomValue / (int)shapeCount) * shapeCount;
            particle->m_shapeA = shape;
            particle->m_shapeB = shape;

            particle++;
        }
    }

    if (work->m_count + 1 >= maxCount) {
        return;
    }

    graphId = pppLocationTitle->m_graphId;
    graphFrame = GetGraphFrameFromId(graphId);
    if (graphFrame < (int)param_2->m_spawnFrame) {
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
        pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&resultMatrix, &managerMatrix, &localMatrix);

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

        {
            Vec tailPos = particles[startIndex + 1].m_pos;
            pppCopyVector(particles[startIndex + inserted + 1].m_pos, tailPos);
        }

        for (int i = 0; i < inserted; i++) {
            LocationTitleParticle* dst = &particles[startIndex + i + 1];
            Vec interpPos = interp[i];
            pppCopyVector(dst->m_pos, interpPos);
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
void pppRenderLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3)
{
    int serializedOffset = *param_3->m_serializedDataOffsets;
    LocationTitleWork* work = (LocationTitleWork*)((u8*)pppLocationTitle + 0x80 + serializedOffset);
    u32 dataValIndex = param_2->m_dataValIndex;

    if ((u16)dataValIndex == 0xFFFF) {
        return;
    }

    u32 graphId = pppLocationTitle->m_graphId;
    int fadeDivisor = -1;
    int graphFrame = GetGraphFrameFromId(graphId);
    LocationTitleParticle* particle = (LocationTitleParticle*)work->m_particles;
    long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + ((u16)dataValIndex * 4));

    if ((int)param_2->m_fadeStartFrame <= graphFrame) {
        fadeDivisor = (int)param_2->m_fadeLength + (graphFrame - (int)param_2->m_fadeStartFrame);
    }

    for (int i = 0; i < work->m_count; i++, particle++) {
        Mtx model;
        Vec worldPos;

        PSMTXIdentity(model);
        model[2][2] = particle->m_frame;
        model[0][0] = pppMngStPtr->m_scale.x * model[2][2];
        model[1][1] = pppMngStPtr->m_scale.y * model[2][2];
        model[2][2] = pppMngStPtr->m_scale.z * model[2][2];

        PSMTXMultVec(ppvCameraMatrix0, &particle->m_pos, &worldPos);
        model[0][3] = worldPos.x;
        model[1][3] = worldPos.y;
        model[2][3] = worldPos.z;

        pppSetDrawEnv((pppCVECTOR*)&particle->m_color, (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 0, 1, 0);

        if (fadeDivisor >= 0) {
            u8 alpha = ((u8*)&particle->m_color)[3];
            ((u8*)&particle->m_color)[3] = (u8)(alpha - (u8)(alpha / fadeDivisor));
        }

        GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&particle->m_color);
        GXLoadPosMtxImm(model, 0);

        pppSetBlendMode(*(((u8*)&param_2->m_stepValue) + 1));
        pppDrawShp(*shapeTable, particle->m_shapeB, pppEnvStPtr->m_materialSetPtr,
                   *(((u8*)&param_2->m_stepValue) + 1));
    }
}
