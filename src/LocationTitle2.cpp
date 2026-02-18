#include "ffcc/LocationTitle2.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_game.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

// External function declarations
extern "C" int rand(void);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

// External data references
extern int DAT_8032ed70;

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
} CameraPcs;

static int GetGraphFrameFromId(u32 graphId)
{
    return ((int)graphId >> 12) + (int)((graphId & 0x80000000) != 0 && (graphId & 0xFFF) != 0);
}

struct LocationTitle2Work {
    void* m_particles;
    u16 m_count;
    u16 m_pad;
    float m_cur;
    float m_vel;
    float m_acc;
};

struct LocationTitle2Particle {
    Vec m_pos;
    u32 m_color;
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    s16 m_frame;
    s16 m_pad0;
    s16 m_shape;
    s16 m_pad1;
};

/*
 * --INFO--
 * PAL Address: 0x800da90c
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLocationTitle2(struct pppLocationTitle2* locationTitle, struct UnkC* unkC)
{
    struct LocationTitle2Work {
        void* data;
        u16 count;
        u16 pad;
        float scaleX;
        float scaleY;
        float scaleZ;
    };
    float value;
    LocationTitle2Work* work;

    value = 0.0f;
    work = (LocationTitle2Work*)((char*)locationTitle + 8 + *unkC->m_serializedDataOffsets);
    work->data = 0;
    work->count = 0;
    work->scaleZ = value;
    work->scaleY = value;
    work->scaleX = value;
}

/*
 * --INFO--
 * PAL Address: 0x800da8b8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructLocationTitle2(struct pppLocationTitle2* locationTitle, struct UnkC* unkC) 
{
    int serializedOffset;
    CMemory::CStage** stagePtr;

    serializedOffset = *unkC->m_serializedDataOffsets;
    stagePtr = (CMemory::CStage**)((char*)locationTitle + 8 + serializedOffset);

    if (*stagePtr != 0) {
        pppHeapUseRate(*stagePtr);
        *stagePtr = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800da3f8
 * PAL Size: 1216b  
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameLocationTitle2(struct pppLocationTitle2* locationTitle, struct UnkB* unkB, struct UnkC* unkC)
{
    int colorOffset;
    LocationTitle2Work* work;
    u16 maxCount;
    long* shapeTable;
    int graphFrame;
    u32 graphId;
    pppFMATRIX* localMatrix;
    const float kInterpScale = 1.0f;

    if (DAT_8032ed70 != 0) {
        return;
    }

    colorOffset = unkC->m_serializedDataOffsets[1];
    graphId = *(u32*)locationTitle;
    localMatrix = (pppFMATRIX*)((u8*)locationTitle + 4);
    work = (LocationTitle2Work*)((u8*)locationTitle + 8 + *unkC->m_serializedDataOffsets);
    rand();

    if (unkB->m_dataValIndex == 0xFFFF) {
        return;
    }

    shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (*(u32*)((u8*)unkB + 8) == graphId) {
        work->m_cur += unkB->m_arg3;
        work->m_vel += *(float*)unkB->m_payload;
        work->m_acc += *(float*)((u8*)unkB->m_payload + 4);
    }

    maxCount = *(u16*)((u8*)&unkB->m_initWOrk + 2);
    if (work->m_particles == 0) {
        LocationTitle2Particle* particles;

        work->m_particles = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            maxCount * sizeof(LocationTitle2Particle), pppEnvStPtr->m_stagePtr, (char*)"LocationTitle2.cpp",
            0x70);
        memset(work->m_particles, 0, maxCount * sizeof(LocationTitle2Particle));

        particles = (LocationTitle2Particle*)work->m_particles;
        for (u16 i = 0; i < maxCount; i++) {
            memcpy(&particles[i].m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
            particles[i].m_scaleX = localMatrix->value[0][0];
            particles[i].m_scaleY = localMatrix->value[1][1];
            particles[i].m_scaleZ = localMatrix->value[2][2];

            if (*(s16*)((u8*)shapeTable + 6) != 0) {
                particles[i].m_shape = (s16)(rand() % *(s16*)((u8*)shapeTable + 6));
            } else {
                particles[i].m_shape = 0;
            }
        }
    }

    if (work->m_count + 1 >= maxCount) {
        return;
    }

    graphFrame = GetGraphFrameFromId(graphId);
    {
        LocationTitle2Particle* particles = (LocationTitle2Particle*)work->m_particles;
        u16 count = work->m_count;
        pppFMATRIX resultMatrix;

        pppMulMatrix(resultMatrix, pppMngStPtr->m_matrix, *localMatrix);

        particles[count].m_pos.x = resultMatrix.value[0][3];
        particles[count].m_pos.y = resultMatrix.value[1][3];
        particles[count].m_pos.z = resultMatrix.value[2][3] + kInterpScale;
        particles[count].m_frame = (s16)graphFrame;

        if ((s16)count - 1 < 0) {
            memcpy(&particles[count].m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
        } else {
            memcpy(&particles[count - 1].m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
        }

        work->m_count = count + 1;
    }

    if (work->m_count > 1) {
        LocationTitle2Particle* particles = (LocationTitle2Particle*)work->m_particles;
        Vec subVec;
        Vec interp[50];
        u16 count = work->m_count;
        u8 stepCount = *(u8*)&unkB->m_stepValue;
        int startIndex = count - 2;
        int inserted = 0;
        float inv = kInterpScale / (float)(stepCount + 1);

        PSVECSubtract(&particles[count - 1].m_pos, &particles[startIndex].m_pos, &subVec);

        for (u8 i = 0; i < stepCount; i++) {
            float t = (float)(i + 1) * inv;
            Vec scaled;

            PSVECScale(&subVec, &scaled, t);
            PSVECAdd(&particles[startIndex].m_pos, &scaled, &interp[i]);
            inserted++;
            work->m_count++;

            if (maxCount <= work->m_count + 1) {
                break;
            }
        }

        particles[startIndex + inserted + 1].m_pos = particles[startIndex + 1].m_pos;

        for (int i = 0; i < inserted; i++) {
            LocationTitle2Particle* dst = &particles[startIndex + i + 1];

            interp[i].z += kInterpScale;
            dst->m_pos = interp[i];
            memcpy(&dst->m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
            dst->m_scaleX = localMatrix->value[0][0];
            dst->m_scaleY = localMatrix->value[1][1];
            dst->m_scaleZ = localMatrix->value[2][2];
            dst->m_frame = (s16)graphFrame;
            dst->m_pad0 = 0;
            dst->m_shape = 0;
            dst->m_pad1 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800da0b4
 * PAL Size: 836b
 * EN Address: TODO  
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderLocationTitle2(struct pppLocationTitle2* locationTitle, struct UnkB* unkB, struct UnkC* unkC)
{
    int serializedOffset = *unkC->m_serializedDataOffsets;
    u32 dataValIndex = *(u32*)((u8*)unkB + 4);

    if (dataValIndex != 0xFFFF) {
        u32 graphId = *(u32*)locationTitle;
        int graphFrame = GetGraphFrameFromId(graphId);
        LocationTitle2Work* work = (LocationTitle2Work*)((u8*)locationTitle + 8 + serializedOffset);
        LocationTitle2Particle* particle = (LocationTitle2Particle*)work->m_particles;
        long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
        u8 blendMode = *((u8*)unkB + 0xD);

        pppSetBlendMode(blendMode);

        if (Game.game.m_currentSceneId != 7) {
            Vec matrixPos;
            Vec cameraPos;
            Vec look;
            Vec side;
            Vec up;

            matrixPos.x = pppMngStPtr->m_matrix.value[0][3];
            matrixPos.y = pppMngStPtr->m_matrix.value[1][3];
            matrixPos.z = pppMngStPtr->m_matrix.value[2][3];

            cameraPos.x = CameraPcs._224_4_;
            cameraPos.y = CameraPcs._228_4_;
            cameraPos.z = CameraPcs._232_4_;

            PSVECSubtract(&cameraPos, &matrixPos, &look);
            if ((look.x == 0.0f) && (look.y == 0.0f) && (look.z == 0.0f)) {
                return;
            }

            PSVECNormalize(&look, &look);
            side.x = look.z;
            side.y = 0.0f;
            side.z = -look.x;

            if ((look.z == 0.0f) && (side.z == 0.0f)) {
                side.x = 1.0f;
                side.z = 0.0f;
                up.x = 0.0f;
                up.y = 0.0f;
                up.z = 1.0f;
            } else {
                PSVECNormalize(&side, &side);
                PSVECCrossProduct(&look, &side, &up);
                PSVECNormalize(&up, &up);
            }

            pppMngStPtr->m_matrix.value[0][0] = side.x;
            pppMngStPtr->m_matrix.value[1][0] = side.y;
            pppMngStPtr->m_matrix.value[2][0] = side.z;
            pppMngStPtr->m_matrix.value[0][1] = up.x;
            pppMngStPtr->m_matrix.value[1][1] = up.y;
            pppMngStPtr->m_matrix.value[2][1] = up.z;
            pppMngStPtr->m_matrix.value[0][2] = look.x;
            pppMngStPtr->m_matrix.value[1][2] = look.y;
            pppMngStPtr->m_matrix.value[2][2] = look.z;
        }

        for (u16 i = 0; i < work->m_count; i++) {
            Mtx model;
            Vec transformedPos;
            GXColor color;

            if (graphFrame <= particle->m_frame) {
                PSMTXIdentity(model);
                model[0][0] = pppMngStPtr->m_scale.x * particle->m_scaleX;
                model[1][1] = pppMngStPtr->m_scale.y * particle->m_scaleY;
                model[2][2] = pppMngStPtr->m_scale.z * particle->m_scaleZ;

                PSMTXMultVec(pppMngStPtr->m_matrix.value, &particle->m_pos, &transformedPos);
                PSMTXMultVec(ppvCameraMatrix0, &transformedPos, &transformedPos);

                model[0][3] = transformedPos.x;
                model[1][3] = transformedPos.y;
                model[2][3] = transformedPos.z;

                pppSetDrawEnv((pppCVECTOR*)&particle->m_color, (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 1, 1, 1);
                GXSetCullMode(GX_CULL_NONE);
                GXSetColorUpdate(GX_FALSE);
                GXLoadPosMtxImm(model, 0);

                if (*((u8*)unkB + 0x22) != 0) {
                    GXSetColorUpdate(GX_TRUE);
                }

                *(u32*)&color = particle->m_color;
                GXSetChanMatColor(GX_COLOR0A0, color);
                pppDrawShp(shapeTable, particle->m_shape, pppEnvStPtr->m_materialSetPtr, blendMode);
            }

            particle++;
        }

        GXSetColorUpdate(GX_TRUE);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
}
