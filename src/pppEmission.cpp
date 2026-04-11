#include "ffcc/pppEmission.h"

#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include "ffcc/ppp_linkage.h"

struct _pppMngStEmission {
    u8 _pad0[0xD8];
    void* m_charaObj;
};

struct _pppEnvStEmission {
    CMemory::CStage* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};
extern _pppMngStEmission* pppMngStPtr;
extern _pppEnvStEmission* pppEnvStPtr;

extern "C" int rand(void);
extern const char DAT_803311fc;
extern float FLOAT_803311e0;
extern float FLOAT_803311e4;
extern float FLOAT_803311f8;
extern double DOUBLE_803311e8;
extern double DOUBLE_803311f0;
char s_pppEmission_cpp_801db7e8[] = "pppEmission.cpp";

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }
static inline MtxPtr CameraMatrix() { return reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4); }

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
void SetDrawDoneDebugData__8CGraphicFSc(void*, signed char);
void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);

void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void SetObjMatrix__12CMaterialManFPA4_fPA4_f(void*, float (*)[4], float (*)[4]);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
}

/*
 * --INFO--
 * PAL Address: 0x800E6B98
 * PAL Size: 2b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetTexGenMode(pppEmission*) {
    // TODO
}

struct EmissionDisplayList {
    u32 m_size;
    void* m_data;
    u16 m_material;
};

struct EmissionMeshData {
    u8 _pad0[0x28];
    u8* m_colors;
    u8 _pad1[0x20];
    u32 m_displayListCount;
    EmissionDisplayList* m_displayLists;
};

struct EmissionMeshRef {
    u8 _pad0[8];
    EmissionMeshData* m_data;
    u8 _pad1[8];
};

struct EmissionModelData {
    u8 _pad0[0x24];
    void* m_materialSet;
};

struct EmissionModelView {
    u8 _pad0[0xA4];
    EmissionModelData* m_data;
    u8 _padA8[0x4];
    EmissionMeshRef* m_meshes;
};

struct EmissionState {
    void* m_particles;
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
    u16 m_alpha;
    u8 m_colorR;
    u8 m_colorG;
    u8 m_colorB;
    u8 m_colorA;
    s16 m_fieldA;
    u16 m_fieldC;
    u8 m_fieldE;
    u8 m_padF;
};

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
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x64);

    EmissionMeshRef* meshList = *(EmissionMeshRef**)((u8*)model + 0xAC);
    EmissionMeshData* meshData = meshList[meshIndex].m_data;
    EmissionDisplayList* displayList = meshData->m_displayLists;
    displayList += displayListIndex;

    if (strcmp((const char*)meshData, &DAT_803311fc) == 0) {
        meshData->m_colors[0] = 0;
        meshData->m_colors[1] = 0;
        meshData->m_colors[2] = 0;
        meshData->m_colors[3] = 0;
    } else {
        EmissionModelData* modelData = *(EmissionModelData**)((u8*)model + 0xA4);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
            &MaterialMan, modelData->m_materialSet, displayList->m_material, 0, 0);
        GXCallDisplayList(displayList->m_data, displayList->m_size);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x65);
    }
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
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x66);

    EmissionModelView* modelView = (EmissionModelView*)model;
    EmissionState* state = (EmissionState*)param_2;
    pppEmissionUnkB* step = (pppEmissionUnkB*)param_3;
    EmissionMeshData* meshData = modelView->m_meshes[meshIndex].m_data;
    if ((strcmp((const char*)meshData, &DAT_803311fc) == 0) && (state->m_colorA != 0)) {
        int textureInfo = state->m_texture;
        pppInitBlendMode();
        pppSetBlendMode(step->m_payload[8]);
        *(int*)(MaterialManRaw() + 0xD0) = textureInfo + 0x28;

        u8 mode = step->m_payload[9];
        if (mode == 0) {
            for (u32 i = 0; i < (u8)step->m_initWOrk; i++) {
                float scale = ((float)i * state->m_scale0) + FLOAT_803311e4;
                Mtx objMtx;
                Mtx viewMtx;
                PSMTXScale(objMtx, scale, scale, scale);
                PSMTXConcat(param_5, objMtx, objMtx);
                PSMTXCopy(CameraMatrix(), viewMtx);
                SetObjMatrix__12CMaterialManFPA4_fPA4_f(&MaterialMan, viewMtx, objMtx);

                int remaining = meshData->m_displayListCount;
                EmissionDisplayList* displayList = meshData->m_displayLists;
                while (--remaining >= 0) {
                    *(int*)(MaterialManRaw() + 0x44) = -1;
                    *(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x11C) = 0;
                    *(int*)(MaterialManRaw() + 0x120) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x124) = 0;
                    *(u8*)(MaterialManRaw() + 0x205) = 0xFF;
                    *(u8*)(MaterialManRaw() + 0x206) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x58) = 0;
                    *(int*)(MaterialManRaw() + 0x5C) = 0;
                    *(u8*)(MaterialManRaw() + 0x208) = 0;
                    *(int*)(MaterialManRaw() + 0x48) = 0xECE0F;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(int*)(MaterialManRaw() + 0x40) = 0xECE0F;
                    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                        &MaterialMan, modelView->m_data->m_materialSet, displayList->m_material, 0, 0);

                    u8 texMode = step->m_payload[10];
                    if (texMode == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        Mtx texMtx;
                        PSMTXCopy((float(*)[4])(MaterialManRaw() + 0xE8), texMtx);
                        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
                        if (texMode == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (texMode == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, &state->m_colorR, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(displayList->m_data, displayList->m_size);
                    displayList++;
                }
            }
        } else if (mode == 1) {
            EmissionParticle* particle = (EmissionParticle*)state->m_particles;
            for (int i = 0; i < (int)(u8)step->m_initWOrk; i++) {
                float scale = particle->m_scale;
                Mtx objMtx;
                Mtx viewMtx;
                PSMTXScale(objMtx, scale, scale, scale);
                PSMTXConcat(param_5, objMtx, objMtx);
                PSMTXCopy(CameraMatrix(), viewMtx);
                PSMTXConcat(viewMtx, objMtx, objMtx);
                GXLoadPosMtxImm(objMtx, 0);

                int remaining = meshData->m_displayListCount;
                EmissionDisplayList* displayList = meshData->m_displayLists;
                while (--remaining >= 0) {
                    *(int*)(MaterialManRaw() + 0x44) = -1;
                    *(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x11C) = 0;
                    *(int*)(MaterialManRaw() + 0x120) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x124) = 0;
                    *(u8*)(MaterialManRaw() + 0x205) = 0xFF;
                    *(u8*)(MaterialManRaw() + 0x206) = 0xFF;
                    *(int*)(MaterialManRaw() + 0x58) = 0;
                    *(int*)(MaterialManRaw() + 0x5C) = 0;
                    *(u8*)(MaterialManRaw() + 0x208) = 0;
                    *(int*)(MaterialManRaw() + 0x48) = 0xECE0F;
                    *(int*)(MaterialManRaw() + 0x128) = 0;
                    *(int*)(MaterialManRaw() + 0x12C) = 0x1E;
                    *(int*)(MaterialManRaw() + 0x130) = 0;
                    *(int*)(MaterialManRaw() + 0x40) = 0xECE0F;
                    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                        &MaterialMan, modelView->m_data->m_materialSet, displayList->m_material, 0, 0);

                    u8 texMode = step->m_payload[10];
                    if (texMode == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        Mtx texMtx;
                        PSMTXCopy((float(*)[4])(MaterialManRaw() + 0xE8), texMtx);
                        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
                        if (texMode == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (texMode == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, &particle->m_colorR, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(displayList->m_data, displayList->m_size);
                    displayList++;
                }
                particle++;
            }
        }

        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x67);
    }
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
    struct EmissionState {
        int field0;
        int field4;
        u8 field8;
        u8 field9;
        u8 fieldA;
        u8 fieldB;
        float fieldC;
        float field10;
        float field14;
        float field18;
        u8 field1C;
    };

    s32* serializedDataOffsets = param_2->m_serializedDataOffsets;
    int offset = serializedDataOffsets[2];
    EmissionState* state = (EmissionState*)((u8*)pppEmission_ + 0x80 + offset);

    state->field4 = 0;
    state->field8 = 0x80;
    state->field9 = 0x80;
    state->fieldA = 0x80;
    state->fieldB = 0x80;
    state->field14 = 0.0f;
    state->field10 = 0.0f;
    state->fieldC = 0.0f;

    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(u32*)(model + 0xFC) = (u32)Emission_DrawMeshDLCallback;
    *(u32*)(model + 0x104) = (u32)Emission_AfterDrawMeshCallback;
    state->field0 = 0;
    state->field18 = *(float*)(model + 0x9C);
    state->field1C = 0;
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
    int offset = param_2->m_serializedDataOffsets[2];
    float* state = (float*)((u8*)pppEmission_ + 0x80 + offset);
    state[5] = baseScale;
    state[4] = baseScale;
    state[3] = baseScale;
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
    int* state = (int*)((u8*)pppEmission_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xFC) = 0;
    *(u32*)(model + 0x104) = 0;

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_pppEmission_cpp_801db7e8, 0x118);
    CMemory::CStage* stage = (CMemory::CStage*)state[0];
    if (stage != (CMemory::CStage*)0) {
        pppHeapUseRate__FPQ27CMemory6CStage(stage);
        state[0] = 0;
    }

    baseScale = FLOAT_803311f8;
    *(float*)(state + 5) = FLOAT_803311f8;
    *(float*)(state + 4) = baseScale;
    *(float*)(state + 3) = baseScale;
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
    int* state = (int*)((u8*)pppEmission_ + 0x80 + serializedDataOffsets[2]);
    u8* dataSet = (u8*)pppEmission_ + 0x80 + serializedDataOffsets[1];

    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(int**)(model + 0xE4) = state;
    *(pppEmissionUnkB**)(model + 0xE8) = param_2;
    *(u32*)(model + 0xFC) = (u32)Emission_DrawMeshDLCallback;
    *(u32*)(model + 0x104) = (u32)Emission_AfterDrawMeshCallback;

    u8 baseAlpha = dataSet[0xB];
    *(u8*)(state + 2) = dataSet[8];
    double alphaScale = (double)baseAlpha / FLOAT_803311e0;
    *((u8*)state + 9) = dataSet[9];
    *((u8*)state + 10) = dataSet[0xA];
    *((u8*)state + 11) = baseAlpha;

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
        param_2->m_stepValue, pppEmission_, param_2->m_graphId,
        (float*)(state + 3), (float*)(state + 4), (float*)(state + 5),
        &param_2->m_arg3, (float*)param_2->m_payload);

    if (gPppInConstructor != 0) {
        return;
    }

    int textureIndex = 0;
    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    state[1] = GetTexture__8CMapMeshFP12CMaterialSetRi(
        pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],
        pppEnvStPtr->m_materialSetPtr,
        textureIndex);

    u8* payload = param_2->m_payload;
    u8 particleCount = *(u8*)&param_2->m_initWOrk;

    if (payload[9] != 0) {
        if (state[0] == 0) {
            *((u8*)(state + 7)) = payload[0xB] / payload[0xC];
            state[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)particleCount << 4,
                pppEnvStPtr->m_stagePtr,
                s_pppEmission_cpp_801db7e8,
                0x16F);

            float* particle = (float*)state[0];
            for (u32 i = 0; i < particleCount; i++) {
                Math.RandF(FLOAT_803311e4);

                int r = rand();
                s16 lifeJitter = (s16)(r % payload[0xD]);
                s16 safeJitter = (lifeJitter > 0) ? lifeJitter : 1;

                *(u16*)(particle + 3) = (u16)payload[0xF] + safeJitter;
                s16 fade = (u16)payload[0xC] + safeJitter;
                *(s16*)((u8*)particle + 10) = *(s16*)(particle + 3) + safeJitter + fade;

                float randOffset = Math.RandF(*(float*)(payload + 4));
                particle[0] = ((float)i * randOffset) + FLOAT_803311e4;
                *(u16*)(particle + 1) = 0;
                *((u8*)particle + 0xE) = (u8)((int)payload[0xB] / (int)fade);
                particle += 4;
            }
        }

        float* particle = (float*)state[0];
        for (int i = 0; i < particleCount; i++) {
            float randOffset = Math.RandF(*(float*)(payload + 4));
            particle[0] = particle[0] + *(float*)(state + 3) + randOffset;

            if (*(s16*)(particle + 3) < 1) {
                if (*(s16*)((u8*)particle + 10) < (s16)(u16)payload[0xC]) {
                    *(u16*)(particle + 1) = (u16)(*(s16*)(particle + 1) - *((u8*)particle + 0xE));
                } else {
                    *(u16*)(particle + 1) = (u16)payload[0xB];
                }
            } else {
                *(s16*)(particle + 3) = *(s16*)(particle + 3) - 1;
                *(u16*)(particle + 1) = (u16)(*(s16*)(particle + 1) + (payload[0xB] / payload[0xF]));
            }

            *(s16*)((u8*)particle + 10) = *(s16*)((u8*)particle + 10) - 1;
            int alpha = (int)((double)*(s16*)(particle + 1) * alphaScale);

            if (*(s16*)((u8*)particle + 10) < 1) {
                s16 jitter = 0;
                if (payload[0xD] != 0) {
                    jitter = (s16)(rand() % payload[0xD]);
                }

                *(u16*)(particle + 3) = payload[0xF];
                *(u16*)((u8*)particle + 10) = (u16)(payload[0xF] + payload[0xE] + jitter + payload[0xC]);
                particle[0] = FLOAT_803311e4 + Math.RandF(*(float*)(payload + 4));
                *(u16*)(particle + 1) = 0;
                *((u8*)particle + 0xE) = payload[0xB] / payload[0xC];
            }

            *((u8*)particle + 6) = dataSet[8];
            *((u8*)particle + 7) = dataSet[9];
            *((u8*)particle + 8) = dataSet[0xA];
            *((u8*)particle + 9) = (u8)alpha;
            particle += 4;
        }

        DCFlushRange(state + 2, 4);
    }
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
 * PAL Address: 0x801A1970
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GXSetTexCoordGen(void) {
    // TODO
}
