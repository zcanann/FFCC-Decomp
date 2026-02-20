#include "ffcc/pppEmission.h"

#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

struct _pppMngStEmission {
    u8 _pad0[8];
    void* m_charaObj;
};

struct _pppEnvStEmission {
    CMemory::CStage* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};

struct CameraPcsForEmission {
    Mtx m_cameraMatrix;
};

extern "C" int rand(void);
extern "C" int strcmp(const char*, const char*);

extern CGraphic Graphic;
extern CMath Math;
extern CameraPcsForEmission CameraPcs;
extern char MaterialMan[];
extern _pppMngStEmission* pppMngStPtr;
extern _pppEnvStEmission* pppEnvStPtr;
extern int DAT_8032ed70;
extern u8 DAT_8032ed78;
extern char DAT_803311fc[];
extern float FLOAT_803311e0;
extern float FLOAT_803311e4;
extern float FLOAT_803311f8;
extern double DOUBLE_803311e8;
extern double DOUBLE_803311f0;

extern "C" {
void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);
void pppInitBlendMode__Fv(void);
void pppSetBlendMode__FUc(unsigned char mode);
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void*, void*, unsigned int, int, int);
void SetObjMatrix__12CMaterialManFPA4_fPA4_f(void*, float (*)[4], float (*)[4]);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
float RandF__5CMathFf(float, CMath*);
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

    char* meshData = *(char**)((char*)model + 0xAC + (meshIndex * 0x14) + 8);
    char* displayList = *(char**)(meshData + 0x50) + (displayListIndex * 0xC);

    if (strcmp(meshData, DAT_803311fc) == 0) {
        *(u8*)(meshData + 0x18) = 0;
        *(u8*)(meshData + 0x19) = 0;
        *(u8*)(meshData + 0x1A) = 0;
        *(u8*)(meshData + 0x1B) = 0;
    } else {
        void* modelData = *(void**)((char*)model + 0xA4);
        void* materialSet = *(void**)((char*)modelData + 0x24);
        SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
            MaterialMan, materialSet, *(u16*)(displayList + 8), 0, 0);
        GXCallDisplayList(*(void**)displayList, *(u32*)(displayList + 4));
        Graphic.SetDrawDoneDebugData(0x65);
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
    Graphic.SetDrawDoneDebugData(0x66);

    char* meshData = *(char**)((char*)model + 0xAC + (meshIndex * 0x14) + 8);
    if ((strcmp(meshData, DAT_803311fc) == 0) && (*(u8*)((u8*)param_2 + 0xB) != 0)) {
        int textureInfo = *(int*)((u8*)param_2 + 4);
        pppInitBlendMode__Fv();
        pppSetBlendMode__FUc(*(u8*)((u8*)param_3 + 0x1C));
        *(int*)(MaterialMan + 0xD0) = textureInfo + 0x28;

        u8 mode = *(u8*)((u8*)param_3 + 0x1D);
        if (mode == 0) {
            for (u32 i = 0; i < *(u8*)((u8*)param_3 + 8); i++) {
                float scale = ((float)i * *(float*)((u8*)param_2 + 0xC)) + FLOAT_803311e4;
                Mtx objMtx;
                Mtx viewMtx;
                PSMTXScale(objMtx, scale, scale, scale);
                PSMTXConcat(param_5, objMtx, objMtx);
                PSMTXCopy(CameraPcs.m_cameraMatrix, viewMtx);
                SetObjMatrix__12CMaterialManFPA4_fPA4_f(MaterialMan, viewMtx, objMtx);

                int remaining = *(int*)(meshData + 0x4C);
                char* displayList = *(char**)(meshData + 0x50);
                while (--remaining >= 0) {
                    *(int*)(MaterialMan + 0x44) = -1;
                    *(u8*)(MaterialMan + 0x4C) = 0xFF;
                    *(int*)(MaterialMan + 0x11C) = 0;
                    *(int*)(MaterialMan + 0x120) = 0x1E;
                    *(int*)(MaterialMan + 0x124) = 0;
                    *(u8*)(MaterialMan + 0x205) = 0xFF;
                    *(u8*)(MaterialMan + 0x206) = 0xFF;
                    *(int*)(MaterialMan + 0x58) = 0;
                    *(int*)(MaterialMan + 0x5C) = 0;
                    *(u8*)(MaterialMan + 0x208) = 0;
                    *(int*)(MaterialMan + 0x48) = 0xECE0F;
                    *(int*)(MaterialMan + 0x128) = 0;
                    *(int*)(MaterialMan + 0x12C) = 0x1E;
                    *(int*)(MaterialMan + 0x130) = 0;
                    *(int*)(MaterialMan + 0x40) = 0xECE0F;
                    void* modelData = *(void**)((char*)model + 0xA4);
                    void* materialSet = *(void**)((char*)modelData + 0x24);
                    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                        MaterialMan, materialSet, *(u16*)(displayList + 8), 0, 0);

                    u8 texMode = *(u8*)((u8*)param_3 + 0x1E);
                    if (texMode == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        Mtx texMtx;
                        PSMTXCopy((float(*)[4])(MaterialMan + 0xE8), texMtx);
                        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
                        if (texMode == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (texMode == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, (u8*)param_2 + 8, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(*(void**)displayList, *(u32*)(displayList + 4));
                    displayList += 0xC;
                }
            }
        } else if (mode == 1) {
            float* particle = *(float**)param_2;
            for (int i = 0; i < (int)(u32)*(u8*)((u8*)param_3 + 8); i++) {
                float scale = particle[0];
                Mtx objMtx;
                Mtx viewMtx;
                PSMTXScale(objMtx, scale, scale, scale);
                PSMTXConcat(param_5, objMtx, objMtx);
                PSMTXCopy(CameraPcs.m_cameraMatrix, viewMtx);
                PSMTXConcat(viewMtx, objMtx, objMtx);
                GXLoadPosMtxImm(objMtx, 0);

                int remaining = *(int*)(meshData + 0x4C);
                char* displayList = *(char**)(meshData + 0x50);
                while (--remaining >= 0) {
                    *(int*)(MaterialMan + 0x44) = -1;
                    *(u8*)(MaterialMan + 0x4C) = 0xFF;
                    *(int*)(MaterialMan + 0x11C) = 0;
                    *(int*)(MaterialMan + 0x120) = 0x1E;
                    *(int*)(MaterialMan + 0x124) = 0;
                    *(u8*)(MaterialMan + 0x205) = 0xFF;
                    *(u8*)(MaterialMan + 0x206) = 0xFF;
                    *(int*)(MaterialMan + 0x58) = 0;
                    *(int*)(MaterialMan + 0x5C) = 0;
                    *(u8*)(MaterialMan + 0x208) = 0;
                    *(int*)(MaterialMan + 0x48) = 0xECE0F;
                    *(int*)(MaterialMan + 0x128) = 0;
                    *(int*)(MaterialMan + 0x12C) = 0x1E;
                    *(int*)(MaterialMan + 0x130) = 0;
                    *(int*)(MaterialMan + 0x40) = 0xECE0F;
                    void* modelData = *(void**)((char*)model + 0xA4);
                    void* materialSet = *(void**)((char*)modelData + 0x24);
                    SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                        MaterialMan, materialSet, *(u16*)(displayList + 8), 0, 0);

                    u8 texMode = *(u8*)((u8*)param_3 + 0x1E);
                    if (texMode == 0) {
                        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
                    } else {
                        Mtx texMtx;
                        PSMTXCopy((float(*)[4])(MaterialMan + 0xE8), texMtx);
                        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
                        if (texMode == 1) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
                        } else if (texMode == 2) {
                            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x1E, GX_FALSE, 0x7D);
                        }
                    }

                    GXSetArray((GXAttr)0xB, (u8*)particle + 6, 4);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXCallDisplayList(*(void**)displayList, *(u32*)(displayList + 4));
                    displayList += 0xC;
                }
                particle += 4;
            }
        }

        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        Graphic.SetDrawDoneDebugData(0x67);
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
void pppConstructEmission(pppEmission* pppEmission_, UnkC* param_2) {
    float baseScale = FLOAT_803311f8;
    int offset = param_2->m_serializedDataOffsets[2];
    int* state = (int*)((u8*)pppEmission_ + 0x80 + offset);

    state[1] = 0;
    *(u8*)(state + 2) = 0x80;
    *((u8*)state + 9) = 0x80;
    *((u8*)state + 10) = 0x80;
    *((u8*)state + 11) = 0x80;
    *(float*)(state + 5) = baseScale;
    *(float*)(state + 4) = baseScale;
    *(float*)(state + 3) = baseScale;

    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(u32*)(model + 0xFC) = (u32)Emission_DrawMeshDLCallback;
    *(u32*)(model + 0x104) = (u32)Emission_AfterDrawMeshCallback;
    state[0] = 0;
    state[6] = *(int*)(model + 0x9C);
    *(u8*)(state + 7) = 0;
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
void pppConstruct2Emission(pppEmission* pppEmission_, UnkC* param_2) {
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
void pppDestructEmission(pppEmission* pppEmission_, UnkC* param_2) {
    int* state = (int*)((u8*)pppEmission_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xFC) = 0;
    *(u32*)(model + 0x104) = 0;

    _WaitDrawDone__8CGraphicFPci(&Graphic, (char*)"pppEmission.cpp", 0x118);
    if (state[0] != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)state[0]);
        state[0] = 0;
    }

    *(float*)(state + 3) = FLOAT_803311f8;
    *(float*)(state + 4) = FLOAT_803311f8;
    *(float*)(state + 5) = FLOAT_803311f8;
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
void pppFrameEmission(pppEmission* pppEmission_, UnkB* param_2, UnkC* param_3) {
    if (DAT_8032ed70 != 0) {
        return;
    }

    int dataSet = param_3->m_serializedDataOffsets[1];
    int* state = (int*)((u8*)pppEmission_ + 0x80 + param_3->m_serializedDataOffsets[2]);

    void* handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(int**)(model + 0xE4) = state;
    *(UnkB**)(model + 0xE8) = param_2;
    *(u32*)(model + 0xFC) = (u32)Emission_DrawMeshDLCallback;
    *(u32*)(model + 0x104) = (u32)Emission_AfterDrawMeshCallback;

    u8 baseAlpha = *((u8*)pppEmission_ + 0x8B + dataSet);
    *(u8*)(state + 2) = *((u8*)pppEmission_ + 0x88 + dataSet);
    *((u8*)state + 9) = *((u8*)pppEmission_ + 0x89 + dataSet);
    *((u8*)state + 10) = *((u8*)pppEmission_ + 0x8A + dataSet);
    *((u8*)state + 11) = baseAlpha;

    double alphaScale = (double)((float)baseAlpha / FLOAT_803311e0);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
        param_2->m_stepValue, pppEmission_, param_2->m_graphId,
        (float*)(state + 3), (float*)(state + 4), (float*)(state + 5),
        &param_2->m_arg3, (float*)param_2->m_payload);

    if (DAT_8032ed78 != 0) {
        return;
    }

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    int textureIndex = 0;
    state[1] = GetTexture__8CMapMeshFP12CMaterialSetRi(
        pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],
        pppEnvStPtr->m_materialSetPtr,
        textureIndex);

    u8* payload = param_2->m_payload;
    u8 particleCount = (u8)param_2->m_initWOrk;

    if (payload[9] != 0) {
        if (state[0] == 0) {
            *((u8*)(state + 7)) = payload[0xB] / payload[0xC];
            state[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)particleCount << 4,
                pppEnvStPtr->m_stagePtr,
                (char*)"pppEmission.cpp",
                0x16F);

            float* particle = (float*)state[0];
            for (u32 i = 0; i < particleCount; i++) {
                RandF__5CMathFf(FLOAT_803311e4, &Math);

                int r = rand();
                s16 lifeJitter = (s16)(r % payload[0xD]);
                s16 safeJitter = (lifeJitter > 0) ? lifeJitter : 1;

                *(u16*)(particle + 3) = (u16)payload[0xF] + safeJitter;
                s16 fade = (u16)payload[0xC] + safeJitter;
                *(s16*)((u8*)particle + 10) = *(s16*)(particle + 3) + safeJitter + fade;

                float randOffset = RandF__5CMathFf(*(float*)(payload + 4), &Math);
                particle[0] = ((float)i * randOffset) + FLOAT_803311e4;
                *(u16*)(particle + 1) = 0;
                *((u8*)particle + 0xE) = (u8)((int)payload[0xB] / (int)fade);
                particle += 4;
            }
        }

        float* particle = (float*)state[0];
        for (int i = 0; i < particleCount; i++) {
            float randOffset = RandF__5CMathFf(*(float*)(payload + 4), &Math);
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
            int alpha = (int)((double)(float)*(s16*)(particle + 1) * alphaScale);

            if (*(s16*)((u8*)particle + 10) < 1) {
                s16 jitter = 0;
                if (payload[0xD] != 0) {
                    jitter = (s16)(rand() % payload[0xD]);
                }

                *(u16*)(particle + 3) = payload[0xF];
                *(u16*)((u8*)particle + 10) = (u16)(payload[0xF] + payload[0xE] + jitter + payload[0xC]);
                particle[0] = FLOAT_803311e4 + RandF__5CMathFf(*(float*)(payload + 4), &Math);
                *(u16*)(particle + 1) = 0;
                *((u8*)particle + 0xE) = payload[0xB] / payload[0xC];
            }

            *((u8*)particle + 6) = *((u8*)pppEmission_ + 0x88 + dataSet);
            *((u8*)particle + 7) = *((u8*)pppEmission_ + 0x89 + dataSet);
            *((u8*)particle + 8) = *((u8*)pppEmission_ + 0x8A + dataSet);
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
void pppRenderEmission(pppEmission*, UnkB*, UnkC*) {
    pppInitBlendMode__Fv();
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
