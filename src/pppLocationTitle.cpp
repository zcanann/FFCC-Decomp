#include "ffcc/pppLocationTitle.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char, unsigned char,
                                                                       unsigned char);
extern void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" int rand(void);
extern float FLOAT_80330ee0;
extern float FLOAT_80330EE4;
extern double DOUBLE_80330EE8;
extern char s_pppLocationTitle_cpp_801DB510[];

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

struct LocationTitleColorBlock {
    u8 m_pad[8];
    GXColor m_color;
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
    int serializedOffset;
    int colorOffset;
    s32* serializedOffsets;
    LocationTitleWork* work;
    LocationTitleColorBlock* colorData;
    int graphFrame;
    long* shapeTable;
    LocationTitleParticle* particles;

    if (gPppCalcDisabled != 0) {
        return;
    }

    serializedOffsets = param_3->m_serializedDataOffsets;
    serializedOffset = serializedOffsets[0];
    colorOffset = serializedOffsets[1];
    work = (LocationTitleWork*)((u8*)pppLocationTitle + 0x80 + serializedOffset);
    colorData = (LocationTitleColorBlock*)((u8*)pppLocationTitle + 0x80 + colorOffset);
    rand();

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    shapeTable = **(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + (param_2->m_dataValIndex * 4));
    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (param_2->m_graphId == pppLocationTitle->m_graphId) {
        work->m_cur += param_2->m_arg3;
        work->m_vel += param_2->m_payload0;
        work->m_acc += param_2->m_payload1;
    }

    if (work->m_particles == NULL) {
        LocationTitleParticle* particle;
        float zero;

        work->m_particles = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            param_2->m_maxCount * sizeof(LocationTitleParticle), pppEnvStPtr->m_stagePtr,
            (char*)s_pppLocationTitle_cpp_801DB510, 0x6d);
        zero = FLOAT_80330ee0;
        particle = (LocationTitleParticle*)work->m_particles;

        for (int i = 0; i < param_2->m_maxCount; i++) {
            int randomValue;
            s16 shapeCount;
            s16 shape;

            particle->m_pos.x = zero;
            particle->m_pos.y = zero;
            particle->m_pos.z = zero;
            memcpy(&particle->m_color, &colorData->m_color, 4);
            particle->m_shapeUnk = 0;
            particle->m_frame = work->m_cur;
            randomValue = rand();
            shapeCount = *(s16*)((u8*)shapeTable + 6);
            shape = randomValue - (randomValue / shapeCount) * shapeCount;
            particle->m_shapeB = shape;
            particle->m_shapeA = shape;

            particle++;
        }
    }

    particles = (LocationTitleParticle*)work->m_particles;

    if (work->m_count + 1 < param_2->m_maxCount) {
        graphFrame = (pppLocationTitle->m_graphId >> 0xc)
                   + ((pppLocationTitle->m_graphId < 0)
                   && (((u32)pppLocationTitle->m_graphId & 0xfff) != 0));
        if (graphFrame >= (int)param_2->m_spawnFrame) {
            pppFMATRIX resultMatrix;

            pppMulMatrix(resultMatrix, pppMngStPtr->m_matrix, pppLocationTitle->m_localMatrix);

            particles[work->m_count].m_pos.x = resultMatrix.value[0][3];
            particles[work->m_count].m_pos.y = resultMatrix.value[1][3];
            particles[work->m_count].m_pos.z = resultMatrix.value[2][3];

            if (work->m_count >= 1) {
                particles[work->m_count - 1].m_frame = work->m_cur;
                memcpy(&particles[work->m_count - 1].m_color, &colorData->m_color, 4);
            } else {
                particles[work->m_count].m_frame = work->m_cur;
                memcpy(&particles[work->m_count].m_color, &colorData->m_color, 4);
            }

            work->m_count++;

            if (work->m_count > 1) {
                Vec subVec;
                Vec interp[50];
                u8 stepCount;
                int startIndex;
                int inserted;
                float stepScale;
                Vec* startPos;
                Vec* interpIt;

                stepCount = param_2->m_stepCount;
                startIndex = (int)work->m_count - 2;
                inserted = 0;
                startPos = &particles[startIndex].m_pos;
                stepScale = FLOAT_80330EE4 / (float)(stepCount + 1);
                interpIt = interp;
                PSVECSubtract(&particles[startIndex + 1].m_pos, startPos, &subVec);

                for (int i = 0; i < stepCount; i++) {
                    Vec scaled;
                    float t;

                    t = stepScale * (float)(i + 1);
                    PSVECScale(&subVec, &scaled, t);
                    PSVECAdd(startPos, &scaled, interpIt);
                    inserted++;
                    work->m_count++;

                    if (param_2->m_maxCount <= (u16)(work->m_count + 1)) {
                        break;
                    }

                    interpIt++;
                }

                pppCopyVector(particles[startIndex + inserted + 1].m_pos,
                              particles[startIndex + 1].m_pos);

                interpIt = interp;
                for (int i = 0; i < inserted; i++) {
                    LocationTitleParticle* dst = &particles[startIndex + i + 1];

                    pppCopyVector(dst->m_pos, *interpIt);
                    memcpy(&dst->m_color, &colorData->m_color, 4);
                    dst->m_frame = work->m_cur;
                    interpIt++;
                }
            }
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
    int serializedOffset;
    u32 graphId;
    LocationTitleWork* work;
    int graphFrame;
    int fadeDivisor;
    LocationTitleParticle* particle;
    LocationTitleParticle* particles;
    long** shapeTable;

    serializedOffset = *param_3->m_serializedDataOffsets;
    work = (LocationTitleWork*)((u8*)pppLocationTitle + 0x80 + serializedOffset);

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    graphId = pppLocationTitle->m_graphId;
    graphFrame = ((int)graphId >> 0xc) + ((int)graphId < 0 && (graphId & 0xfff) != 0);
    fadeDivisor = -1;
    particles = (LocationTitleParticle*)work->m_particles;
    shapeTable =
        *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + (param_2->m_dataValIndex * 4));

    if ((int)param_2->m_fadeStartFrame <= graphFrame) {
        fadeDivisor = (int)param_2->m_fadeLength + (graphFrame - (int)param_2->m_fadeStartFrame);
    }

    particle = particles;

    for (int i = 0; i < work->m_count; i++) {
        Mtx model;
        Vec worldPos;

        PSMTXIdentity(model);
        model[0][0] = pppMngStPtr->m_scale.x * particle->m_frame;
        model[1][1] = pppMngStPtr->m_scale.y * particle->m_frame;
        model[2][2] = pppMngStPtr->m_scale.z * particle->m_frame;

        PSMTXMultVec(ppvCameraMatrix02, &particle->m_pos, &worldPos);
        model[0][3] = worldPos.x;
        model[1][3] = worldPos.y;
        model[2][3] = worldPos.z;

        pppSetDrawEnv((pppCVECTOR*)&particle->m_color, (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 0, 1, 0);

        if (fadeDivisor >= 0) {
            u8 alpha;
            int fadeStep;

            alpha = ((u8*)&particle->m_color)[3];
            fadeStep = alpha / fadeDivisor;
            ((u8*)&particle->m_color)[3] = (u8)(alpha - fadeStep);
        }

        GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&particle->m_color);
        GXLoadPosMtxImm(model, 0);
        pppSetBlendMode(param_2->m_blendMode);
        pppDrawShp(*shapeTable, particle->m_shapeB, pppEnvStPtr->m_materialSetPtr, param_2->m_blendMode);
        particle++;
    }
}
