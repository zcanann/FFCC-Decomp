#include "ffcc/LocationTitle2.h"
#include "ffcc/chara.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_game.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

// External function declarations
extern "C" int rand(void);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" int SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, CChara::CModel*);
extern "C" void SetFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);

// External data references
extern int DAT_8032ed70;
extern float FLOAT_80330f48;
extern float FLOAT_80330f4c;
extern double DOUBLE_80330f58;
extern char DAT_80330f50[];

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

static char s_LocationTitle2_cpp[] = "LocationTitle2.cpp";

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
    u32 graphId;

    if (DAT_8032ed70 != 0) {
        return;
    }

    colorOffset = unkC->m_serializedDataOffsets[1];
    graphId = *(u32*)locationTitle;
    work = (LocationTitle2Work*)((u8*)locationTitle + 8 + *unkC->m_serializedDataOffsets);
    rand();

    if (unkB->m_dataValIndex == 0xFFFF) {
        return;
    }

    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (*(u32*)((u8*)unkB + 8) == graphId) {
        work->m_cur += unkB->m_arg3;
        work->m_vel += *(float*)unkB->m_payload;
        work->m_acc += *(float*)((u8*)unkB->m_payload + 4);
    }

    if (work->m_particles == 0) {
        u16 maxCount;
        LocationTitle2Particle* particles;
        pppFMATRIX* localMatrix;
        int ownerData;
        CChara::CModel* model;
        int nodeIndex;
        u8* modelBytes;
        u8* modelAnim;
        u8* modelNodes;
        u16 animFrameCount;

        localMatrix = (pppFMATRIX*)((u8*)locationTitle + 4);
        maxCount = *(u16*)((u8*)&unkB->m_initWOrk + 2);
        work->m_particles = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            maxCount * sizeof(LocationTitle2Particle), pppEnvStPtr->m_stagePtr, s_LocationTitle2_cpp,
            0x70);
        memset(work->m_particles, 0, maxCount * sizeof(LocationTitle2Particle));
        particles = (LocationTitle2Particle*)work->m_particles;

        ownerData = 0;
        if (pppMngStPtr->m_owner != 0) {
            ownerData = *(int*)((u8*)pppMngStPtr->m_owner + 0xF8);
        }

        model = 0;
        if (ownerData != 0) {
            model = *(CChara::CModel**)(ownerData + 0x168);
        }

        if (model == 0) {
            return;
        }

        nodeIndex = SearchNode__Q26CChara6CModelFPc(model, DAT_80330f50);
        modelBytes = (u8*)model;
        modelAnim = *(u8**)(modelBytes + 0xA4);
        modelNodes = *(u8**)(modelBytes + 0xA8);
        animFrameCount = *(u16*)(modelAnim + 0x10);

        for (u16 frameIndex = 0; frameIndex < animFrameCount; frameIndex++) {
            Mtx nodeMtx;
            LocationTitle2Particle* particle;
            u16 count;

            CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(modelNodes + nodeIndex * 0xC0, model);
            SetFrame__Q26CChara6CModelFf((float)frameIndex, model);
            CalcMatrix__Q26CChara6CModelFv(model);
            PSMTXCopy((float(*)[4])(modelNodes + nodeIndex * 0xC0 + 0xC), nodeMtx);

            count = work->m_count;
            particle = &particles[count];
            particle->m_pos.x = nodeMtx[0][3];
            particle->m_pos.y = nodeMtx[1][3];
            particle->m_pos.z = nodeMtx[2][3] + FLOAT_80330f4c;
            memcpy(&particle->m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
            particle->m_pad0 = 0;
            particle->m_shape = 0;
            particle->m_pad1 = 0;
            particle->m_frame = (s16)frameIndex;
            particle->m_scaleX = localMatrix->value[0][0];
            particle->m_scaleY = localMatrix->value[1][1];
            particle->m_scaleZ = localMatrix->value[2][2];
            work->m_count = count + 1;

            if (maxCount <= (u16)(work->m_count + 1)) {
                return;
            }

            if (work->m_count > 1) {
                Vec stepDir;
                Vec interp[21];
                u8 stepCount;
                int startIndex;
                int inserted;
                double stepScale;
                LocationTitle2Particle* startParticle;

                stepCount = *(u8*)&unkB->m_stepValue;
                startIndex = (int)work->m_count - 2;
                inserted = 0;
                startParticle = &particles[startIndex];
                stepScale = (double)(FLOAT_80330f4c / (float)(stepCount + 1));
                PSVECSubtract(&particles[work->m_count - 1].m_pos, &startParticle->m_pos, &stepDir);

                for (int i = 0; i < stepCount; i++) {
                    Vec scaled;
                    float t;

                    t = (float)(stepScale * (double)(i + 1));
                    PSVECScale(&stepDir, &scaled, t);
                    PSVECAdd(&startParticle->m_pos, &scaled, &interp[i]);
                    inserted++;
                    work->m_count++;

                    if (maxCount <= (u16)(work->m_count + 1)) {
                        break;
                    }
                }

                pppCopyVector(particles[startIndex + inserted + 1].m_pos,
                              particles[startIndex + 1].m_pos);

                for (int i = 0; i < inserted; i++) {
                    LocationTitle2Particle* dst;

                    dst = &particles[startIndex + i + 1];
                    interp[i].z += FLOAT_80330f4c;
                    pppCopyVector(dst->m_pos, interp[i]);
                    memcpy(&dst->m_color, (u8*)locationTitle + 0x88 + colorOffset, 4);
                    dst->m_pad0 = 0;
                    dst->m_shape = 0;
                    dst->m_pad1 = 0;
                    dst->m_scaleX = localMatrix->value[0][0];
                    dst->m_scaleY = localMatrix->value[1][1];
                    dst->m_scaleZ = localMatrix->value[2][2];
                    dst->m_frame = (s16)frameIndex;
                }
            }
        }

        SetFrame__Q26CChara6CModelFf(FLOAT_80330f48, model);
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
