#include "ffcc/pppEmission.h"

#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h"
#include "ffcc/ppp_linkage.h"

extern const char s_pppEmissionShapeObj2;
extern const float FLOAT_803311e0;
extern const float FLOAT_803311e4;
extern const float FLOAT_803311f8;
extern const float FLOAT_8033111C = 15.0f;
extern const float FLOAT_80331120 = 7.0f;
extern const double DOUBLE_80331128 = 4503599627370496.0;
extern const float FLOAT_80331130 = 10000000.0f;
extern "C" const char s_pppEmission_cpp[] = "pppEmission.cpp";

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }
static inline MtxPtr CameraMatrix() { return CameraPcs.m_cameraMatrix; }

typedef CChara::CMesh::CDisplayList EmissionDisplayList;
typedef CChara::CMesh::CRefData EmissionMeshData;
typedef CChara::CMesh EmissionMeshRef;

struct EmissionState;
struct EmissionParticle;

struct EmissionState {
    EmissionParticle* m_particles;
    int m_texture;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    u8 m_colorA;
    float m_scale0;
    float m_scale1;
    float m_scale2;
    float m_scale3;
    u8 m_field1C;
};

struct EmissionParticle {
    float m_scale;
    s16 m_alpha;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    u8 m_colorA;
    s16 m_fieldA;
    s16 m_fieldC;
    u8 m_fieldE;
    u8 m_padF;
};

STATIC_ASSERT(offsetof(EmissionMeshData, m_colors) == 0x28);
STATIC_ASSERT(offsetof(EmissionMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(EmissionMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(CCharaModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(EmissionState, m_scale0) == 0xC);
STATIC_ASSERT(offsetof(EmissionState, m_field1C) == 0x1C);
STATIC_ASSERT(sizeof(EmissionState) == 0x20);
STATIC_ASSERT(sizeof(EmissionParticle) == 0x10);

static inline EmissionState* GetEmissionState(pppEmission* emission, pppEmissionUnkC* ctrl)
{
    return reinterpret_cast<EmissionState*>(
        emission->m_object.m_workArea + ctrl->m_serializedDataOffsets[2]);
}

static inline EmissionMeshData* EmissionMeshAt(CChara::CModel* model, int meshIndex)
{
    return model->m_meshes[meshIndex].m_data;
}

static inline void SetEmissionModelCallbacks(CChara::CModel* model, EmissionState* state, pppEmissionUnkB* step)
{
    model->SetCallbackContext(state, step);
    model->SetDrawMeshDLCallback(Emission_DrawMeshDLCallback);
    model->SetAfterDrawMeshCallback(Emission_AfterDrawMeshCallback);
}

static inline void ClearEmissionModelCallbacks(CChara::CModel* model)
{
    model->SetCallbackContext(0, 0);
    model->SetDrawMeshDLCallback(0);
    model->SetAfterDrawMeshCallback(0);
}

/*
 * --INFO--
 * PAL Address: 0x800E6060
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderEmission(pppEmission*, pppEmissionUnkB*, pppEmissionUnkC*) {
    pppInitBlendMode();
}
/*
 * --INFO--
 * PAL Address: 0x800E6080
 * PAL Size: 1040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameEmission(pppEmission* pppEmission_, pppEmissionUnkB* param_2, pppEmissionUnkC* param_3) {
    if (gPppCalcDisabled != 0) {
        return;
    }

    s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
    EmissionState* state = GetEmissionState(pppEmission_, param_3);
    u8* dataSet = pppEmission_->m_object.m_workArea + serializedDataOffsets[1];

    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    SetEmissionModelCallbacks(model, state, param_2);

    float alphaScale = (float)dataSet[0xB] / FLOAT_803311e0;
    state->m_colorR = dataSet[8];
    state->m_colorG = dataSet[9];
    state->m_colorB = dataSet[0xA];
    state->m_colorA = dataSet[0xB];

    CalcGraphValue(
        &pppEmission_->m_object, param_2->m_graphId,
        state->m_scale0, state->m_scale1, state->m_scale2,
        param_2->m_stepValue, param_2->m_arg3, *(float*)param_2->m_payload);

    if (gPppInConstructor != 0) {
        return;
    }

    int textureIndex = 0;
    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    state->m_texture =
        reinterpret_cast<int>(ppvEnv->m_mapMeshPtr[param_2->m_dataValIndex]->GetTexture(ppvEnv->m_materialSetPtr, textureIndex));

    u8* payload = param_2->m_payload;
    if (payload[9] != 0) {
        if (state->m_particles == 0) {
            state->m_field1C = payload[0xB] / payload[0xC];
            state->m_particles = static_cast<EmissionParticle*>(pppMemAlloc(
                (unsigned long)param_2->m_initWOrk << 4,
                ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppEmission_cpp),
                0x16F));

            EmissionParticle* particle = state->m_particles;
            for (int i = 0; i < param_2->m_initWOrk; i++) {
                Math.RandF(FLOAT_803311e4);

                s16 lifeJitter = (s16)(rand() % payload[0xD]);
                s16 safeJitter = (lifeJitter >= 1) ? lifeJitter : 1;

                particle->m_fieldC = payload[0xF] + safeJitter;
                s16 fade = (u16)payload[0xC] + safeJitter;
                particle->m_fieldA = particle->m_fieldC + safeJitter + fade;
                particle->m_scale = ((float)i * Math.RandF(*(float*)(payload + 4))) + FLOAT_803311e4;
                particle->m_alpha = 0;
                particle->m_fieldE = (u8)((int)payload[0xB] / (int)fade);
                particle++;
            }
        }

        EmissionParticle* particle = state->m_particles;
        for (int i = 0; i < param_2->m_initWOrk; i++) {
            particle->m_scale = particle->m_scale + (state->m_scale0 + Math.RandF(*(float*)(payload + 4)));

            int delay = particle->m_fieldC;
            if (delay > 0) {
                particle->m_fieldC = delay - 1;
                particle->m_alpha = particle->m_alpha + (payload[0xB] / payload[0xF]);
            } else {
                if (payload[0xC] <= particle->m_fieldA) {
                    particle->m_alpha = payload[0xB];
                } else {
                    particle->m_alpha = particle->m_alpha - particle->m_fieldE;
                }
            }

            s16 life = particle->m_fieldA;
            int alpha = (int)((float)particle->m_alpha * alphaScale);
            life--;
            particle->m_fieldA = life;

            if (particle->m_fieldA <= 0) {
                int jitter = 0;
                if (payload[0xD] != 0) {
                    jitter = rand() % payload[0xD];
                }

                particle->m_fieldC = payload[0xF];
                particle->m_fieldA = payload[0xF] + payload[0xE] + jitter + payload[0xC];
                particle->m_scale = FLOAT_803311e4 + Math.RandF(*(float*)(payload + 4));
                particle->m_alpha = 0;
                particle->m_fieldE = payload[0xB] / payload[0xC];
            }

            particle->m_colorR = dataSet[8];
            particle->m_colorG = dataSet[9];
            particle->m_colorB = dataSet[0xA];
            particle->m_colorA = (u8)alpha;
            particle++;
        }

        DCFlushRange(&state->m_colorR, 4);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800E6490
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructEmission(pppEmission* pppEmission_, pppEmissionUnkC* param_2) {
    float baseScale;
    EmissionState* state = GetEmissionState(pppEmission_, param_2);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);

    ClearEmissionModelCallbacks(model);

    Graphic._WaitDrawDone(const_cast<char*>(s_pppEmission_cpp), 0x118);
    CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(state->m_particles);
    if (stage != (CMemory::CStage*)0) {
        pppHeapUseRate(stage);
        state->m_particles = 0;
    }

    baseScale = FLOAT_803311f8;
    state->m_scale2 = FLOAT_803311f8;
    state->m_scale1 = baseScale;
    state->m_scale0 = baseScale;
}

/*
 * --INFO--
 * PAL Address: 0x800E6530
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2Emission(pppEmission* pppEmission_, pppEmissionUnkC* param_2) {
    float baseScale = FLOAT_803311f8;
    EmissionState* state = GetEmissionState(pppEmission_, param_2);
    state->m_scale2 = baseScale;
    state->m_scale1 = baseScale;
    state->m_scale0 = baseScale;
}

/*
 * --INFO--
 * PAL Address: 0x800E6554
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructEmission(pppEmission* pppEmission_, pppEmissionUnkC* param_2) {
    float baseScale = FLOAT_803311f8;
    EmissionState* state = GetEmissionState(pppEmission_, param_2);

    state->m_texture = 0;
    state->m_colorR = 0x80;
    state->m_colorG = 0x80;
    state->m_colorB = 0x80;
    state->m_colorA = 0x80;
    state->m_scale2 = baseScale;
    state->m_scale1 = baseScale;
    state->m_scale0 = baseScale;

    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    model->SetDrawMeshDLCallback(Emission_DrawMeshDLCallback);
    model->SetAfterDrawMeshCallback(Emission_AfterDrawMeshCallback);
    state->m_particles = 0;
    state->m_scale3 = model->m_lightAlpha;
    state->m_field1C = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800E65F4
 * PAL Size: 1216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Emission_AfterDrawMeshCallback(CChara::CModel* model, void* param_2, void* param_3, int meshIndex, float (*param_5)[4]) {
    Graphic.SetDrawDoneDebugData(0x66);

    EmissionState* state = (EmissionState*)param_2;
    pppEmissionUnkB* step = (pppEmissionUnkB*)param_3;
    EmissionMeshData* meshData = EmissionMeshAt(model, meshIndex);
    if ((strcmp((const char*)meshData, &s_pppEmissionShapeObj2) == 0) && (state->m_colorA != 0)) {
        int texture = state->m_texture;
        u32 drawTevBits = 0xACE0F;

        pppInitBlendMode();
        pppSetBlendMode(step->m_payload[8]);
        *(int*)(MaterialManRaw() + 0xD0) = texture + 0x28;

        Mtx viewMtx0;
        Mtx objMtx0;
        Mtx viewMtx1;
        Mtx objMtx1;
        Mtx texMtx0;
        Mtx texMtx1;

        if (step->m_payload[9] == 0) {
            EmissionDisplayList* displayList;
            for (int i = 0; i < step->m_initWOrk; i++) {
                float scale = FLOAT_803311e4;
                scale += (float)i * state->m_scale0;
                PSMTXScale(objMtx0, scale, scale, scale);
                PSMTXConcat(param_5, objMtx0, objMtx0);
                PSMTXCopy(CameraMatrix(), viewMtx0);
                MaterialMan.SetObjMatrix(viewMtx0, objMtx0);

                displayList = meshData->m_displayLists;
                int remaining = meshData->m_displayListCount - 1;
                while (remaining >= 0) {
                    *(int*)(MaterialManRaw() + 0x44) = -1;
                    *(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x48) = drawTevBits;
                    *(int*)(MaterialManRaw() + 0x11C) = 0;
                    *(int*)(MaterialManRaw() + 0x120) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x124) = 0;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(u8*)(MaterialManRaw() + 0x205) = 0xFF;
                    *(u8*)(MaterialManRaw() + 0x206) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x58) = 0;
                    *(int*)(MaterialManRaw() + 0x5C) = 0;
                    *(u8*)(MaterialManRaw() + 0x208) = 0;
                    *(u32*)(MaterialManRaw() + 0x48) |= 0x40000;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(u32*)(MaterialManRaw() + 0x40) = *(u32*)(MaterialManRaw() + 0x48);
                    MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

                    if (step->m_payload[10] == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        PSMTXCopy((float(*)[4])(MaterialManRaw() + 0xE8), texMtx0);
                        GXLoadTexMtxImm(texMtx0, 0x1E, GX_MTX3x4);
                        if (step->m_payload[10] == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (step->m_payload[10] == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, &state->m_colorR, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(displayList->m_data, displayList->m_size);
                    remaining--;
                    displayList++;
                }
            }
        } else if (step->m_payload[9] == 1) {
            EmissionParticle* particle = state->m_particles;
            for (int i = 0; i < step->m_initWOrk; i++) {
                float scale = particle->m_scale;
                PSMTXScale(objMtx1, scale, scale, scale);
                PSMTXConcat(param_5, objMtx1, objMtx1);
                PSMTXCopy(CameraMatrix(), viewMtx1);
                PSMTXConcat(viewMtx1, objMtx1, objMtx1);
                GXLoadPosMtxImm(objMtx1, 0);

                int remaining = meshData->m_displayListCount - 1;
                EmissionDisplayList* displayList = meshData->m_displayLists;
                while (remaining >= 0) {
                    *(int*)(MaterialManRaw() + 0x44) = -1;
                    *(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x48) = drawTevBits;
                    *(int*)(MaterialManRaw() + 0x11C) = 0;
                    *(int*)(MaterialManRaw() + 0x120) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x124) = 0;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(u8*)(MaterialManRaw() + 0x205) = 0xFF;
                    *(u8*)(MaterialManRaw() + 0x206) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x58) = 0;
                    *(int*)(MaterialManRaw() + 0x5C) = 0;
                    *(u8*)(MaterialManRaw() + 0x208) = 0;
                    *(u32*)(MaterialManRaw() + 0x48) |= 0x40000;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(u32*)(MaterialManRaw() + 0x40) = *(u32*)(MaterialManRaw() + 0x48);
                    MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

                    if (step->m_payload[10] == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        PSMTXCopy((float(*)[4])(MaterialManRaw() + 0xE8), texMtx1);
                        GXLoadTexMtxImm(texMtx1, 0x1E, GX_MTX3x4);
                        if (step->m_payload[10] == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (step->m_payload[10] == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, &particle->m_colorR, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(displayList->m_data, displayList->m_size);
                    remaining--;
                    displayList++;
                }
                particle++;
            }
        }

        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        Graphic.SetDrawDoneDebugData(0x67);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800E6AB4
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Emission_DrawMeshDLCallback(CChara::CModel* model, void*, void*, int meshIndex, int displayListIndex, float (*)[4]) {
    Graphic.SetDrawDoneDebugData(0x64);

    EmissionMeshData* meshData = model->m_meshes[meshIndex].m_data;
    EmissionDisplayList* displayList = meshData->m_displayLists;
    displayList += displayListIndex;

    if (strcmp((const char*)meshData, &s_pppEmissionShapeObj2) == 0) {
        meshData->m_colors[0] = 0;
        meshData->m_colors[1] = 0;
        meshData->m_colors[2] = 0;
        meshData->m_colors[3] = 0;
    } else {
        MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
        GXCallDisplayList(displayList->m_data, displayList->m_size);
        Graphic.SetDrawDoneDebugData(0x65);
    }
}
