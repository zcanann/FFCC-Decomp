#include "ffcc/pppLocationTitle.h"
#include "ffcc/linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(LocationTitleWork) == 0x14);
STATIC_ASSERT(offsetof(LocationTitleWork, m_particles) == 0x00);
STATIC_ASSERT(offsetof(LocationTitleWork, m_count) == 0x04);
STATIC_ASSERT(offsetof(LocationTitleWork, m_cur) == 0x08);
STATIC_ASSERT(offsetof(LocationTitleWork, m_vel) == 0x0C);
STATIC_ASSERT(offsetof(LocationTitleWork, m_acc) == 0x10);
STATIC_ASSERT(sizeof(LocationTitleParticle) == 0x1C);
STATIC_ASSERT(offsetof(LocationTitleParticle, m_color) == 0x0C);
STATIC_ASSERT(offsetof(LocationTitleParticle, m_frame) == 0x10);
STATIC_ASSERT(offsetof(LocationTitleParticle, m_shapeB) == 0x18);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x08);
STATIC_ASSERT(sizeof(LocationTitleDataOffsets) == 0x8);
STATIC_ASSERT(offsetof(LocationTitleDataOffsets, m_workOffset) == 0x00);
STATIC_ASSERT(offsetof(LocationTitleDataOffsets, m_colorOffset) == 0x04);

static const char s_pppLocationTitle_cpp[] = "pppLocationTitle.cpp";

static inline LocationTitleDataOffsets* GetLocationTitleDataOffsets(pppLocationTitleOffsets* offsets)
{
    return reinterpret_cast<LocationTitleDataOffsets*>(offsets->m_serializedDataOffsets);
}

static inline LocationTitleWork* GetLocationTitleWork(pppLocationTitle* locationTitle, pppLocationTitleOffsets* offsets)
{
    return reinterpret_cast<LocationTitleWork*>(
        locationTitle->m_workArea + GetLocationTitleDataOffsets(offsets)->m_workOffset);
}

static inline VColor* GetLocationTitleColorBlock(
    pppLocationTitle* locationTitle, pppLocationTitleOffsets* offsets)
{
    return reinterpret_cast<VColor*>(
        locationTitle->m_workArea + GetLocationTitleDataOffsets(offsets)->m_colorOffset);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 196b
 * EN Address: UNUSED
 * EN Size: 260b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void copyPolygonData(LocationTitleParticle* dst, LocationTitleParticle* src)
{
    pppCopyVector(dst->m_pos, src->m_pos);
    memcpy(&dst->m_color, &src->m_color, sizeof(GXColor));
    dst->m_frame = src->m_frame;
    dst->m_shapeUnk = src->m_shapeUnk;
    dst->m_shapeA = src->m_shapeA;
    dst->m_shapeB = src->m_shapeB;
    dst->m_pad = src->m_pad;
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
void pppRenderLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleStep* param_2, pppLocationTitleOffsets* param_3)
{
    int dataValIndex;
    LocationTitleWork* work;
    int graphFrame;
    LocationTitleParticle* particle;
    LocationTitleParticle* particles;
    pppShapeSt* shape;
    int fadeDivisor;

    dataValIndex = param_2->m_dataValIndex;
    work = GetLocationTitleWork(pppLocationTitle, param_3);

    if (dataValIndex == 0xFFFF) {
        return;
    }

    fadeDivisor = -1;
    particles = work->m_particles;
    shape = ppvEnv->m_shapeTablePtr[dataValIndex];
    graphFrame = pppLocationTitle->m_graphId / 0x1000;

    if ((int)param_2->m_fadeStartFrame <= graphFrame) {
        fadeDivisor = (int)param_2->m_fadeLength + (graphFrame - (int)param_2->m_fadeStartFrame);
    }

    particle = particles;

    for (int i = 0; i < work->m_count; i++) {
        Mtx model;
        Vec worldPos;

        PSMTXIdentity(model);
        model[0][0] = ppvMng->m_scale.x * particle->m_frame;
        model[1][1] = ppvMng->m_scale.y * particle->m_frame;
        model[2][2] = ppvMng->m_scale.z * particle->m_frame;

        PSMTXMultVec(ppvCameraMatrix, &particle->m_pos, &worldPos);
        model[0][3] = worldPos.x;
        model[1][3] = worldPos.y;
        model[2][3] = worldPos.z;

        pppSetDrawEnv((pppCVECTOR*)&particle->m_color, (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 0, 1, 0);

        if (fadeDivisor >= 0) {
            u8 alpha;
            int fadeStep;

            alpha = particle->m_color.a;
            fadeStep = alpha / fadeDivisor;
            particle->m_color.a = static_cast<u8>(alpha - fadeStep);
        }

        GXSetChanMatColor(GX_COLOR0A0, particle->m_color);
        GXLoadPosMtxImm(model, 0);
        pppSetBlendMode(param_2->m_blendMode);
        pppDrawShp(static_cast<long*>(shape->m_animData), particle->m_shapeB, ppvEnv->m_materialSetPtr,
                   param_2->m_blendMode);
        particle++;
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
void pppFrameLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleStep* param_2, pppLocationTitleOffsets* param_3)
{
    pppFMATRIX resultMatrix;
    Vec subVec;
    Vec interp[50];
    Vec scaled;
    Vec* startPos;
    Vec* interpWrite;
    Vec* interpRead;
    int startIndex;
    LocationTitleParticle* dst;
    LocationTitleWork* work;
    VColor* colorData;
    int graphFrame;
    pppShapeAnimData* shapeAnim;
    LocationTitleParticle* particles;
    LocationTitleParticle* particle;
    float zero;
    int randomValue;
    s16 shapeCount;
    s16 shape;
    int inserted;
    float stepScale;
    float t;
    int nextCount;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetLocationTitleWork(pppLocationTitle, param_3);
    colorData = GetLocationTitleColorBlock(pppLocationTitle, param_3);
    rand();

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    shapeAnim = static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[param_2->m_dataValIndex]->m_animData);
    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (param_2->m_graphId == pppLocationTitle->m_graphId) {
        work->m_cur += param_2->m_arg3;
        work->m_vel += param_2->m_payload0;
        work->m_acc += param_2->m_payload1;
    }

    if (work->m_particles == NULL) {
        work->m_particles = static_cast<LocationTitleParticle*>(pppMemAlloc(
            param_2->m_maxCount * sizeof(LocationTitleParticle), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppLocationTitle_cpp), 0x6d));
        zero = 0.0f;
        particle = work->m_particles;

        for (int i = 0; i < param_2->m_maxCount; i++) {
            particle->m_pos.x = zero;
            particle->m_pos.y = zero;
            particle->m_pos.z = zero;
            memcpy(&particle->m_color, &colorData->m_color, 4);
            particle->m_shapeUnk = 0;
            particle->m_frame = work->m_cur;
            randomValue = rand();
            shapeCount = shapeAnim->m_frameCount;
            shape = randomValue % shapeCount;
            particle->m_shapeB = shape;
            particle->m_shapeA = shape;

            particle++;
        }
    }

    particles = work->m_particles;

    if (work->m_count + 1 < param_2->m_maxCount) {
        graphFrame = pppLocationTitle->m_graphId / 0x1000;
        if (graphFrame >= (int)param_2->m_spawnFrame) {
            pppMulMatrix(resultMatrix, ppvMng->m_matrix, pppLocationTitle->m_localMatrix);

            particles[work->m_count].m_pos.x = resultMatrix.value[0][3];
            particles[work->m_count].m_pos.y = resultMatrix.value[1][3];
            particles[work->m_count].m_pos.z = resultMatrix.value[2][3];

            if ((int)(work->m_count - 1) >= 0) {
                particles[work->m_count - 1].m_frame = work->m_cur;
                memcpy(&particles[work->m_count - 1].m_color, &colorData->m_color, 4);
            } else {
                particles[work->m_count].m_frame = work->m_cur;
                memcpy(&particles[work->m_count].m_color, &colorData->m_color, 4);
            }

            work->m_count++;

            if (work->m_count > 1) {
                startIndex = (int)work->m_count - 2;
                inserted = 0;
                startPos = &particles[startIndex].m_pos;
                stepScale = 1.0f / (float)(param_2->m_stepCount + 1);
                PSVECSubtract(&particles[startIndex + 1].m_pos, startPos, &subVec);
                interpRead = interp;
                interpWrite = interpRead;

                for (int i = 0; i < param_2->m_stepCount; i++) {
                    t = stepScale * (float)(i + 1);
                    PSVECScale(&subVec, &scaled, t);
                    PSVECAdd(startPos, &scaled, interpWrite);
                    inserted++;
                    work->m_count++;

                    {
                        nextCount = work->m_count + 1;

                        if (nextCount >= param_2->m_maxCount) {
                            break;
                        }
                    }

                    interpWrite++;
                }

                pppCopyVector(particles[startIndex + 1 + inserted].m_pos,
                              particles[startIndex + 1].m_pos);

                for (int i = 0; i < inserted; i++) {
                    dst = &particles[startIndex + (i + 1)];

                    pppCopyVector(dst->m_pos, *interpRead);
                    memcpy(&dst->m_color, &colorData->m_color, 4);
                    dst->m_frame = work->m_cur;
                    interpRead++;
                }
            }
        }
    }
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
void pppDestructLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleOffsets* param_2)
{
    LocationTitleWork* work = GetLocationTitleWork(pppLocationTitle, param_2);

    if (work->m_particles != NULL) {
        pppMemFree(work->m_particles);
        work->m_particles = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d92cc
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLocationTitle(pppLocationTitle* pppLocationTitle, pppLocationTitleOffsets* param_2)
{
    LocationTitleWork* work;
    f32 value;

    value = 0.0f;
    work = GetLocationTitleWork(pppLocationTitle, param_2);
    work->m_particles = 0;
    work->m_count = 0;
    work->m_acc = value;
    work->m_vel = value;
    work->m_cur = value;
}
