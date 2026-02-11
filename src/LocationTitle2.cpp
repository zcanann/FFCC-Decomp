#include "ffcc/LocationTitle2.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/p_game.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

// External function declarations
extern "C" int rand(void);

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
    int iVar1;
    int iVar2;
    int* piVar12;
    
    if (DAT_8032ed70 == 0) {
        iVar2 = unkC->m_serializedDataOffsets[1];
        piVar12 = (int*)((char*)locationTitle + 8 + *unkC->m_serializedDataOffsets);
        
        // Random function call
        rand();
        
        if (unkB->m_dataValIndex != 0xffff) {
            // Basic frame processing logic based on decomp
            piVar12[3] = (int)((float)piVar12[3] + (float)piVar12[4]);
            piVar12[2] = (int)((float)piVar12[2] + (float)piVar12[3]);
            
            if (unkB->m_initWOrk == locationTitle->pad[0]) { // field0_0x0.m_graphId
                piVar12[2] = (int)((float)piVar12[2] + (float)unkB->m_arg3);
                piVar12[3] = (int)((float)piVar12[3] + *(float*)unkB->m_payload);
                piVar12[4] = (int)((float)piVar12[4] + *(float*)((u8*)unkB->m_payload + 4));
            }
            
            // Memory allocation logic if needed
            if (*piVar12 == 0) {
                // Complex memory allocation and setup logic would go here
            }
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

    if (unkB->m_dataValIndex != 0xFFFF) {
        u32 graphId = *(u32*)locationTitle;
        int graphFrame = GetGraphFrameFromId(graphId);
        LocationTitle2Work* work = (LocationTitle2Work*)((u8*)locationTitle + 8 + serializedOffset);
        LocationTitle2Particle* particle = (LocationTitle2Particle*)work->m_particles;
        long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + unkB->m_dataValIndex * 4);
        u8 blendMode = *((u8*)&unkB->m_stepValue + 1);

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

                if (((u8*)unkB->m_payload)[0xE] != 0) {
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
