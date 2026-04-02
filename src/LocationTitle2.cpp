#include "ffcc/LocationTitle2.h"
#include "ffcc/chara.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_game.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

// External function declarations
extern "C" int rand(void);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, const char*, int);
extern "C" int SearchNode__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" void CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(void*, CChara::CModel*);
extern "C" void SetFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);

// External data references
extern float FLOAT_80330f48;
extern float FLOAT_80330f4c;
extern double DOUBLE_80330f58;
extern char DAT_80330f50[];

static int GetGraphFrameFromId(u32 graphId)
{
    return (int)graphId / 0x1000;
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
    u16 m_frame;
    s16 m_pad0;
    s16 m_pad1;
    s16 m_shape;
};

static const char s_LocationTitle2_cpp[] = "LocationTitle2.cpp";

/*
 * --INFO--
 * PAL Address: 0x800da90c
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructLocationTitle2(struct pppLocationTitle2* locationTitle, struct pppLocationTitle2UnkC* unkC)
{
    LocationTitle2Work* work;
    f32 value;

    value = FLOAT_80330f48;
    work = (LocationTitle2Work*)((char*)locationTitle + 0x80 + *unkC->m_serializedDataOffsets);
    work->m_particles = 0;
    work->m_count = 0;
    work->m_acc = value;
    work->m_vel = value;
    work->m_cur = value;
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
extern "C" void pppDestructLocationTitle2(struct pppLocationTitle2* locationTitle, struct pppLocationTitle2UnkC* unkC) 
{
    int serializedOffset;
    CMemory::CStage** stagePtr;

    serializedOffset = *unkC->m_serializedDataOffsets;
    stagePtr = (CMemory::CStage**)((char*)locationTitle + 0x80 + serializedOffset);

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
extern "C" void pppFrameLocationTitle2(struct pppLocationTitle2* locationTitle, struct pppLocationTitle2UnkB* unkB, struct pppLocationTitle2UnkC* unkC)
{
    int serializedOffset;
    int colorOffset;
    s32* serializedOffsets;
    LocationTitle2Work* work;
    u8* colorSrc;

    if (gPppCalcDisabled != 0) {
        return;
    }

    serializedOffsets = unkC->m_serializedDataOffsets;
    serializedOffset = serializedOffsets[0];
    colorOffset = serializedOffsets[1];
    work = (LocationTitle2Work*)((u8*)locationTitle + 0x80 + serializedOffset);
    colorSrc = (u8*)locationTitle + 0x88 + colorOffset;
    rand();

    if (unkB->m_dataValIndex == 0xFFFF) {
        return;
    }

    work->m_vel += work->m_acc;
    work->m_cur += work->m_vel;

    if (unkB->m_graphId == locationTitle->m_graphId) {
        work->m_cur += unkB->m_arg3;
        work->m_vel += unkB->m_payload0;
        work->m_acc += unkB->m_payload1;
    }

    if (work->m_particles == 0) {
        LocationTitle2Particle* particles;
        int ownerData;
        CChara::CModel* model;
        int nodeIndex;
        u8* modelAnim;
        u8* modelNodes;
        double zOffset;

        work->m_particles = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            unkB->m_maxCount * sizeof(LocationTitle2Particle), pppEnvStPtr->m_stagePtr, s_LocationTitle2_cpp,
            0x70);
        memset(work->m_particles, 0, unkB->m_maxCount * sizeof(LocationTitle2Particle));
        particles = (LocationTitle2Particle*)work->m_particles;

        ownerData = *(int*)((u8*)pppMngStPtr->m_owner + 0xF8);
        model = 0;
        if (ownerData != 0 && *(CChara::CModel**)(ownerData + 0x168) != 0) {
            model = *(CChara::CModel**)(ownerData + 0x168);
        }

        nodeIndex = SearchNode__Q26CChara6CModelFPc(model, DAT_80330f50);
        modelAnim = *(u8**)((u8*)model + 0xA4);
        modelNodes = *(u8**)((u8*)model + 0xA8);
        zOffset = (double)FLOAT_80330f4c;

        for (u32 frameIndex = 0; frameIndex < *(u16*)(modelAnim + 0x10); frameIndex++) {
            Mtx nodeMtx;
            LocationTitle2Particle* particle;

            CalcBind__Q26CChara5CNodeFPQ26CChara6CModel(modelNodes + nodeIndex * 0xC0, model);
            SetFrame__Q26CChara6CModelFf((float)frameIndex, model);
            CalcMatrix__Q26CChara6CModelFv(model);
            PSMTXCopy((float(*)[4])(modelNodes + nodeIndex * 0xC0 + 0xC), nodeMtx);

            particle = &particles[work->m_count];
            particle->m_pos.x = nodeMtx[0][3];
            particle->m_pos.y = nodeMtx[1][3];
            particle->m_pos.z = (float)((double)nodeMtx[2][3] + zOffset);
            memcpy(&particle->m_color, colorSrc, 4);
            particle->m_pad0 = 0;
            particle->m_pad1 = 0;
            particle->m_shape = 0;
            particle->m_frame = (s16)frameIndex;
            particle->m_scaleX = locationTitle->m_localMatrix.value[0][0];
            particle->m_scaleY = locationTitle->m_localMatrix.value[1][1];
            particle->m_scaleZ = locationTitle->m_localMatrix.value[2][2];
            work->m_count++;

            if (unkB->m_maxCount <= (u16)(work->m_count + 1U)) {
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
                Vec* interpIt;

                stepCount = unkB->m_stepCount;
                startIndex = (int)work->m_count - 2;
                inserted = 0;
                startParticle = &particles[startIndex];
                stepScale = (double)(FLOAT_80330f4c / (float)(stepCount + 1));
                interpIt = interp;
                PSVECSubtract(&particles[work->m_count - 1].m_pos, &startParticle->m_pos, &stepDir);

                for (int i = 0; i < stepCount; i++) {
                    Vec scaled;
                    float t;

                    t = (float)(stepScale * (double)(i + 1));
                    PSVECScale(&stepDir, &scaled, t);
                    PSVECAdd(&startParticle->m_pos, &scaled, interpIt);
                    inserted++;
                    work->m_count++;

                    if (unkB->m_maxCount <= (u16)(work->m_count + 1U)) {
                        break;
                    }

                    interpIt++;
                }

                pppCopyVector(particles[startIndex + inserted + 1].m_pos,
                              particles[startIndex + 1].m_pos);

                interpIt = interp;
                for (int i = 0; i < inserted; i++) {
                    LocationTitle2Particle* dst;

                    dst = &particles[startIndex + i + 1];
                    interpIt->z = (float)((double)interpIt->z + zOffset);
                    pppCopyVector(dst->m_pos, *interpIt);
                    memcpy(&dst->m_color, colorSrc, 4);
                    dst->m_pad0 = 0;
                    dst->m_pad1 = 0;
                    dst->m_shape = 0;
                    dst->m_scaleX = locationTitle->m_localMatrix.value[0][0];
                    dst->m_scaleY = locationTitle->m_localMatrix.value[1][1];
                    dst->m_scaleZ = locationTitle->m_localMatrix.value[2][2];
                    dst->m_frame = (s16)frameIndex;
                    interpIt++;
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
extern "C" void pppRenderLocationTitle2(struct pppLocationTitle2* locationTitle, struct pppLocationTitle2UnkB* unkB, struct pppLocationTitle2UnkC* unkC)
{
    int serializedOffset;
    LocationTitle2Work* work;
    LocationTitle2Particle* particle;
    long** shapeTable;
    int graphFrame;

    serializedOffset = *unkC->m_serializedDataOffsets;
    work = (LocationTitle2Work*)((u8*)locationTitle + 0x80 + serializedOffset);

    if (unkB->m_dataValIndex == 0xFFFF) {
        return;
    }

    particle = (LocationTitle2Particle*)work->m_particles;
    shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
    graphFrame = GetGraphFrameFromId(locationTitle->m_graphId);

    pppSetBlendMode(unkB->m_blendMode);

    if ((int)Game.m_currentSceneId != 7) {
        Vec cameraPos;
        Vec look;
        Vec side;
        Vec up;
        Vec lookNorm;
        Vec matrixPos;

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

        PSVECNormalize(&look, &lookNorm);
        side.x = lookNorm.z;
        side.y = 0.0f;
        side.z = -lookNorm.x;

        if ((lookNorm.z == 0.0f) && (side.z == 0.0f)) {
            side.x = 1.0f;
            side.z = 0.0f;
            up.x = 0.0f;
            up.y = 0.0f;
            up.z = 1.0f;
        } else {
            PSVECNormalize(&side, &side);
            PSVECCrossProduct(&lookNorm, &side, &up);
            PSVECNormalize(&up, &up);
        }

        pppMngStPtr->m_matrix.value[0][0] = side.x;
        pppMngStPtr->m_matrix.value[1][0] = side.y;
        pppMngStPtr->m_matrix.value[2][0] = side.z;
        pppMngStPtr->m_matrix.value[0][1] = up.x;
        pppMngStPtr->m_matrix.value[1][1] = up.y;
        pppMngStPtr->m_matrix.value[2][1] = up.z;
        pppMngStPtr->m_matrix.value[0][2] = lookNorm.x;
        pppMngStPtr->m_matrix.value[1][2] = lookNorm.y;
        pppMngStPtr->m_matrix.value[2][2] = lookNorm.z;
    }

    for (int i = 0; i < work->m_count; i++) {
        Mtx model;
        Vec transformedPos;

        if ((int)particle->m_frame >= graphFrame) {
            transformedPos.x = 0.0f;
            transformedPos.y = 0.0f;
            transformedPos.z = 0.0f;
            PSMTXIdentity(model);
            model[0][0] = pppMngStPtr->m_scale.x * locationTitle->m_localMatrix.value[0][0];
            model[1][1] = pppMngStPtr->m_scale.y * locationTitle->m_localMatrix.value[1][1];
            model[2][2] = pppMngStPtr->m_scale.z * locationTitle->m_localMatrix.value[2][2];

            PSMTXMultVec(pppMngStPtr->m_matrix.value, &particle->m_pos, &transformedPos);
            PSMTXMultVec(ppvCameraMatrix02, &transformedPos, &transformedPos);

            model[0][3] = transformedPos.x;
            model[1][3] = transformedPos.y;
            model[2][3] = transformedPos.z;

            pppSetDrawEnv((pppCVECTOR*)&particle->m_color, (pppFMATRIX*)0, 0.0f, 0, 0, 0, 0, 1, 1, 1);
            GXSetCullMode(GX_CULL_NONE);
            GXSetColorUpdate(GX_FALSE);
            GXLoadPosMtxImm(model, 0);

            if (unkB->m_enableColorUpdate != 0) {
                GXSetColorUpdate(GX_TRUE);
            }

            GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&particle->m_color);
            pppDrawShp(*shapeTable, particle->m_shape, pppEnvStPtr->m_materialSetPtr, unkB->m_blendMode);
        }

        particle++;
    }

    GXSetColorUpdate(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
}
