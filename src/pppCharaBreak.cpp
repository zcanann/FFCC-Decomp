#include "ffcc/pppCharaBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <string.h>
#include "ffcc/ppp_linkage.h"

class CMaterialMan;
extern const char s_pppCharaBreak_cpp_801dd690[] = "pppCharaBreak.cpp";
extern float FLOAT_80332048;
extern float FLOAT_8033204c;
extern float FLOAT_80332050;
extern float FLOAT_80332058;
extern float FLOAT_8033205c;
extern float FLOAT_80332060;
extern float FLOAT_80332064;
extern float FLOAT_80332078;
extern double DOUBLE_80332068;
extern double DOUBLE_80332070;
extern const char sPppCharaBreakObjMeshName[4];
extern int DAT_801dd684;
extern int DAT_801dd688;
extern int DAT_801dd68c;
extern Vec kPppCharaBreakUpVector;
static const float kPppCharaBreakDrawScale = 0.0f;
extern "C" void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void* materialMan, void* materialSet,
                                                                            unsigned int materialIdx, int, int);
static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

static inline Mtx& CameraMatrix()
{
    return CameraPcs.m_cameraMatrix;
}

void pppInitBlendMode(void);

extern "C" {
int rand(void);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(void*, long, float&, float&, float&, float, float&, float&);
void* pppMemFree__FPv(unsigned long, CMemory::CStage*, char*, int);
void CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(CUtil*, Vec*, Vec*, S16Vec*, unsigned long, unsigned long);
void ReWriteDisplayList__5CUtilFPvUlUl(CUtil*, void*, unsigned long, unsigned long);
int GetNumPolygonFromDL__5CUtilFPvUl(CUtil*, void*, unsigned long);
int IsHasDrawFmtDL__5CUtilFUc(CUtil*, unsigned char);
void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(void*);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);

void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
void ConvI2FVector__5CUtilFR3Vec6S16Vecl(CUtil*, Vec*, S16Vec, unsigned long);
void ConvF2IVector__5CUtilFR6S16Vec3Vecl(CUtil*, S16Vec*, Vec, unsigned long);
}

struct POLYGON_DATA {
    u8 m_enabled;
    u8 m_alpha;
    u16 _pad2;
    S16Vec m_normalA;
    S16Vec m_normalB;
    S16Vec m_pos0;
    S16Vec m_pos1;
    S16Vec m_pos2;
    u16 m_posIndices[3];
    u16 m_nrmIndices[3];
    u16 m_texIndices[3];
};

typedef CharaBreakUnkB CharaBreakStep;

STATIC_ASSERT(sizeof(CharaBreakStep) == 0x44);

struct CharaBreakWork {
    u32 _pad0;
    f32 m_value0;
    f32 m_value1;
    f32 m_value2;
    f32 m_value3;
    f32 m_value4;
    f32 m_value5;
    void* m_meshBuffers;
    Vec m_bboxMin;
    u8 _pad2C[0x4];
    Vec m_bboxMax;
    f32 m_miscValue;
    CChara::CModel* m_model;
    u32 m_enabled;
};

struct CharaBreakDisplayListPair {
    void* m_rewrittenDisplayList;
    u32 m_displayListSize;
    u16 m_polygonCount;
    u16 _padA;
    POLYGON_DATA* m_polygonData;
};

struct CharaBreakDisplayList {
    u32 m_size;
    void* m_data;
    u16 m_material;
    u16 _padA;
};

struct CharaBreakMeshData {
    char m_name[0x10];
    u8 m_flags;
    u8 _pad11[3];
    u32 m_vertexCount;
    S16Vec* m_vertices;
    u32 m_normalCount;
    S16Vec* m_normals;
    u32 m_colorCount;
    void* m_colors;
    u32 m_uvCount;
    void* m_uvs;
    u32 m_oneWeightCountOrSize;
    void* m_oneWeightData;
    u32 m_twoWeightCountOrSize;
    void* m_twoWeightData;
    u32 m_threeWeightCountOrSize;
    void* m_threeWeightData;
    s32 m_displayListCount;
    CharaBreakDisplayList* m_displayLists;
    u32 m_skinCount;
    void* m_skins;
    s32 m_nodeIndex;
};

struct CharaBreakMeshRef {
    u8 _pad0[8];
    CharaBreakMeshData* m_data;
    S16Vec* m_workPositions;
    S16Vec* m_workNormals;
};

struct CharaBreakModelData {
    u8 _pad0[0xC];
    u32 m_meshCount;
    u8 _pad10[0x14];
    void* m_materialSet;
    u8 _pad28[0xC];
    u32 m_posQuant;
    u32 m_normQuant;
};

struct CharaBreakModelView {
    u8 _pad0[0xA4];
    CharaBreakModelData* m_data;
    void* m_nodes;
    CharaBreakMeshRef* m_meshes;
};

STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_data) == 0x8);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workNormals) == 0x10);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_data) == 0xA4);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_nodes) == 0xA8);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_meshes) == 0xAC);
STATIC_ASSERT(offsetof(CharaBreakModelData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(CharaBreakModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CharaBreakModelData, m_posQuant) == 0x34);
STATIC_ASSERT(offsetof(CharaBreakModelData, m_normQuant) == 0x38);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_skinCount) == 0x54);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_nodeIndex) == 0x5C);

static inline MtxPtr ModelDrawMtx(CChara::CModel* model)
{
    return reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(model) + 0x8);
}

static inline CharaBreakModelData* ModelData(CChara::CModel* model)
{
    return *reinterpret_cast<CharaBreakModelData**>(reinterpret_cast<u8*>(model) + 0xA4);
}

static inline void* ModelNodes(CChara::CModel* model)
{
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(model) + 0xA8);
}

static inline CharaBreakMeshRef* ModelMeshes(CChara::CModel* model)
{
    return *reinterpret_cast<CharaBreakMeshRef**>(reinterpret_cast<u8*>(model) + 0xAC);
}

extern "C" void CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f(void*, void*, void*, s32, Mtx);
extern "C" void CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f(void);
extern "C" void CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi(void);
extern "C" u32 CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(u32, void*, void*);

/*
 * --INFO--
 * PAL Address: 0x8013F9D0
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkB*, CharaBreakUnkC* data)
{
    int colorOffset = data->m_serializedDataOffsets[0];
    CharaBreakWork* work = (CharaBreakWork*)(charaBreak->m_workArea + data->m_serializedDataOffsets[2]);
    u8* colorWork = charaBreak->m_workArea + colorOffset;

    if (work->m_enabled != 0) {
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        pppInitBlendMode();
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            colorWork + 8,
            (u8*)charaBreak + 0x40,
            kPppCharaBreakDrawScale,
            0,
            0,
            0,
            0,
            1,
            1,
            0);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 2, 2, 3);
        ((u8*)work)[0] = 0xFF;
        ((u8*)work)[1] = 0xFF;
        ((u8*)work)[2] = 0xFF;
        ((u8*)work)[3] = colorWork[0xB];
    }
}
/*
 * --INFO--
 * PAL Address: 0x8013FAA0
 * PAL Size: 1140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkB* step, CharaBreakUnkC* data)
{
    CharaBreakStep* stepData;
    CharaBreakWork* work;
    CChara::CModel* model;
    void* handle;
    u8* mesh;
    u32 i;

    stepData = (CharaBreakStep*)step;
    if (gPppCalcDisabled != 0) {
        return;
    }

    handle = pppMngStPtr->m_owner;
    work = (CharaBreakWork*)(charaBreak->m_workArea + data->m_serializedDataOffsets[2]);
    if (work->m_enabled == 0) {
        return;
    }

    handle = GetCharaHandlePtr__FP8CGObjectl(handle, 0);
    model = (CChara::CModel*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    work->m_model = model;

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(charaBreak,
                                                 stepData->m_graphId,
                                                 work->m_value0,
                                                 work->m_value1,
                                                 work->m_value2,
                                                 stepData->m_dataValIndex,
                                                 stepData->m_graphInit,
                                                 stepData->m_graphStep);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(charaBreak,
                                                 stepData->m_graphId,
                                                 work->m_value3,
                                                 work->m_value4,
                                                 work->m_value5,
                                                 stepData->m_payloadGraphInit,
                                                 stepData->m_payloadGraphStep,
                                                 stepData->m_payloadGraphStepStep);

    model->m_callbackContext = work;
    model->m_callbackParam = stepData;
    model->m_beforeMeshLockEnvCallback = (void (*)(CChara::CModel*, void*, void*, int))
        CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
    model->m_drawMeshDLCallback = (void (*)(CChara::CModel*, void*, void*, int, int, float (*)[4]))
        CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    model->m_afterDrawMeshCallback = (void (*)(CChara::CModel*, void*, void*, int, float (*)[4]))
        CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    *(u32*)((u8*)model + 0xEC) = (u32)CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv;

    if (stepData->m_graphId == charaBreak->m_graphId) {
        f32 zero = FLOAT_80332048;
        if (zero == stepData->m_direction.x && zero == stepData->m_direction.y &&
            zero == stepData->m_direction.z) {
            stepData->m_direction.x = FLOAT_8033204c;
            stepData->m_direction.y = zero;
            stepData->m_direction.z = zero;
        } else {
            PSVECNormalize(&stepData->m_direction, &stepData->m_direction);
        }
    }

    mesh = reinterpret_cast<u8*>(ModelMeshes(model));

    if (work->m_meshBuffers == NULL) {
        work->m_miscValue = FLOAT_80332050;
        work->m_meshBuffers =
            pppMemFree__FPv(ModelData(model)->m_meshCount << 2,
                            pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x3D0);
        if (work->m_meshBuffers == NULL) {
            goto fail;
        }

        for (i = 0; i < ModelData(model)->m_meshCount; i++) {
            ((u32*)work->m_meshBuffers)[i] = 0;
        }

        for (i = 0; i < ModelData(model)->m_meshCount; i++) {
            {
                CharaBreakMeshData* meshData = reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_data;

                if (strcmp(meshData->m_name, sPppCharaBreakObjMeshName) == 0) {
                    CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(
                        &gUtil,
                        &work->m_bboxMin,
                        &work->m_bboxMax,
                        reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_workPositions,
                        meshData->m_vertexCount,
                        ModelData(model)->m_posQuant);
                }
            }

            ((u32*)work->m_meshBuffers)[i] = (u32)pppMemFree__FPv(
                reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_data->m_displayListCount << 2, pppEnvStPtr->m_stagePtr,
                const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x3E9);
            u32 meshBuffer = ((u32*)work->m_meshBuffers)[i];
            if (meshBuffer == 0) {
                goto fail;
            }

            {
                int displayListCount = reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_data->m_displayListCount;
                int* dlEntries = (int*)meshBuffer;
                for (int dl = displayListCount - 1; dl >= 0; dl--) {
                    dlEntries[dl] = 0;
                }
            }

            {
                int displayListCount = reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_data->m_displayListCount;
                CharaBreakDisplayList* displayList = reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_data->m_displayLists;
                int dl = displayListCount - 1;
                CharaBreakDisplayListPair** dlEntries =
                    (CharaBreakDisplayListPair**)(meshBuffer + (dl << 2));
                for (; dl >= 0; dl--, displayList++) {
                    *dlEntries = (CharaBreakDisplayListPair*)pppMemFree__FPv(
                        0x10, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x3FC);
                    if (*dlEntries == NULL) {
                        goto fail;
                    }

                    (*dlEntries)->m_rewrittenDisplayList = NULL;
                    (*dlEntries)->m_displayListSize = 0;
                    (*dlEntries)->m_polygonData = 0;
                    (*dlEntries)->m_displayListSize = displayList->m_size;
                    (*dlEntries)->m_rewrittenDisplayList = pppMemFree__FPv(
                        displayList->m_size, pppEnvStPtr->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x40B);
                    if ((*dlEntries)->m_rewrittenDisplayList == NULL) {
                        goto fail;
                    }

                    memcpy((*dlEntries)->m_rewrittenDisplayList, displayList->m_data, displayList->m_size);
                    ReWriteDisplayList__5CUtilFPvUlUl(&gUtil, (*dlEntries)->m_rewrittenDisplayList,
                                                      displayList->m_size, 1);

                    u32 polygonCount =
                        GetNumPolygonFromDL__5CUtilFPvUl(&gUtil, (*dlEntries)->m_rewrittenDisplayList,
                                                         displayList->m_size);
                    (*dlEntries)->m_polygonData = (POLYGON_DATA*)pppMemFree__FPv(
                        polygonCount * 0x34, pppEnvStPtr->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x423);
                    if ((*dlEntries)->m_polygonData == NULL) {
                        goto fail;
                    }
                    (*dlEntries)->m_polygonCount = (u16)polygonCount;

                    CreatePolygon((*dlEntries)->m_polygonData, displayList->m_data, displayList->m_size,
                                  model, (CChara::CMesh*)mesh);
                    InitPolygonParameter((PCharaBreak*)stepData, (VCharaBreak*)work, (*dlEntries)->m_polygonData,
                                         (*dlEntries)->m_polygonCount, model, (CChara::CMesh*)mesh);

                    dlEntries--;
                }
            }

            mesh += 0x14;
        }
    }

    if (gPppInConstructor == 0) {
        UpdatePolygonData((PCharaBreak*)stepData, (VCharaBreak*)work, model);
    }
    return;

fail:
    work->m_enabled = 0;
    model->m_callbackContext = 0;
    model->m_callbackParam = 0;
    model->m_beforeMeshLockEnvCallback = 0;
    model->m_drawMeshDLCallback = 0;
    model->m_afterDrawMeshCallback = 0;
    *(u32*)((u8*)model + 0xEC) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013FF14
 * PAL Size: 364b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    _WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x319);

    CharaBreakWork* work = (CharaBreakWork*)(charaBreak->m_workArea + data->m_serializedDataOffsets[2]);
    CChara::CModel* model = work->m_model;

    model->m_callbackContext = 0;
    model->m_callbackParam = 0;
    model->m_beforeMeshLockEnvCallback = 0;
    model->m_drawMeshDLCallback = 0;
    model->m_afterDrawMeshCallback = 0;
    *(u32*)((u8*)model + 0xEC) = 0;

    void** perMeshBuffers = (void**)work->m_meshBuffers;
    u8* mesh = reinterpret_cast<u8*>(ModelMeshes(model));
    void** meshBufferSlot = perMeshBuffers;

    if (perMeshBuffers != NULL) {
        for (u32 meshIndex = 0; meshIndex < ModelData(model)->m_meshCount; meshIndex++) {
            u32 dlEntryBase = (u32)*meshBufferSlot;
            int meshData = *(int*)(mesh + 8);
            if (dlEntryBase != 0) {
                int* dlEntries = (int*)dlEntryBase;
                for (u32 dlIndex = 0; dlIndex < *(u32*)(meshData + 0x4C); dlIndex++) {
                    if ((void*)*dlEntries != NULL) {
                        if (*(void**)*dlEntries != NULL) {
                            pppHeapUseRate__FPQ27CMemory6CStage(*(void**)*dlEntries);
                            *(u32*)*dlEntries = 0;
                        }
                        if (*(void**)(*dlEntries + 0xC) != NULL) {
                            pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(*dlEntries + 0xC));
                            *(u32*)(*dlEntries + 0xC) = 0;
                        }
                    }
                    if ((void*)*dlEntries != NULL) {
                        pppHeapUseRate__FPQ27CMemory6CStage((void*)*dlEntries);
                        *dlEntries = 0;
                    }
                    dlEntries++;
                }
            }

            if (*meshBufferSlot != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(*meshBufferSlot);
                *meshBufferSlot = NULL;
            }
            meshBufferSlot++;
            mesh += 0x14;
        }
    }

    if (perMeshBuffers != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(perMeshBuffers);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80140080
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2CharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    float fVar1 = FLOAT_80332048;
    int dataOffset = data->m_serializedDataOffsets[2];
    CharaBreakWork* work = (CharaBreakWork*)(charaBreak->m_workArea + dataOffset);

    work->m_value2 = FLOAT_80332048;
    work->m_value1 = fVar1;
    work->m_value0 = fVar1;
    work->m_value5 = fVar1;
    work->m_value4 = fVar1;
    work->m_value3 = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x801400B0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCharaBreak(pppCharaBreak* charaBreak, CharaBreakUnkC* data)
{
    float fVar1 = FLOAT_80332048;
    int dataOffset = data->m_serializedDataOffsets[2];
    CharaBreakWork* work = (CharaBreakWork*)(charaBreak->m_workArea + dataOffset);

    work->m_meshBuffers = 0;
    work->m_value2 = fVar1;
    work->m_value1 = fVar1;
    work->m_value0 = fVar1;
    work->m_value5 = fVar1;
    work->m_value4 = fVar1;
    work->m_value3 = fVar1;
    work->m_enabled = 1;
}

/*
 * --INFO--
 * PAL Address: 0x801400f0
 * PAL Size: 2220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdatePolygonData(PCharaBreak* step, VCharaBreak* work, CChara::CModel* model)
{
    CharaBreakStep* stepData = (CharaBreakStep*)step;
    CharaBreakWork* workData = (CharaBreakWork*)work;
    CharaBreakModelData* modelData = ModelData(model);
    CChara::CMesh* mesh = reinterpret_cast<CChara::CMesh*>(ModelMeshes(model));
    u32 meshIndex;
    s32 threshold;

    threshold = (s32)((workData->m_value0 * (workData->m_bboxMax.y - workData->m_bboxMin.y)) *
                      (float)((double)(1 << modelData->m_posQuant)));

    for (meshIndex = 0; meshIndex < modelData->m_meshCount; meshIndex++) {
        bool needsMtxUpdate = false;
        Mtx meshToWorld;
        CharaBreakMeshRef* meshRef = reinterpret_cast<CharaBreakMeshRef*>(mesh);
        CharaBreakMeshData* meshData = meshRef->m_data;
        S16Vec* workPositions = meshRef->m_workPositions;

        if (meshData->m_skinCount == 0 && stepData->m_worldSpaceMode == 1) {
            needsMtxUpdate = true;
            PSMTXConcat(ModelDrawMtx(model), *(Mtx*)((u8*)ModelNodes(model) + (meshData->m_nodeIndex * 0xC0) + 0x6C),
                        meshToWorld);
        }

        for (int dl = meshData->m_displayListCount - 1; dl >= 0; dl--) {
            int meshBuffers = *(int*)((int)workData->m_meshBuffers + (meshIndex * 4));
            u8* polygon = *(u8**)(*(int*)(meshBuffers + (dl * 4)) + 0xC);
            u16 polygonCount = *(u16*)(*(int*)(meshBuffers + (dl * 4)) + 8);

            for (u32 polyIndex = 0; polyIndex < polygonCount; polyIndex++) {
                S16Vec transformed[3];

                if (polygon[0] == 0) {
                    int flags[3];
                    flags[0] = DAT_801dd684;
                    flags[1] = DAT_801dd688;
                    flags[2] = DAT_801dd68c;

                    for (int i = 0; i < 3; i++) {
                        S16Vec* dst = &transformed[i];
                        S16Vec* srcPos = workPositions + *(u16*)(polygon + 0x22 + (i * 2));

                        if (needsMtxUpdate) {
                            S16Vec worldPos;
                            Vec transformedPos;
                            worldPos.x = srcPos->x;
                            worldPos.y = srcPos->y;
                            worldPos.z = srcPos->z;
                            ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &transformedPos, worldPos,
                                                                 modelData->m_posQuant);
                            PSMTXMultVec(meshToWorld, &transformedPos, &transformedPos);
                            ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, dst, transformedPos,
                                                                 modelData->m_posQuant);
                        } else {
                            *dst = *srcPos;
                        }

                        if (stepData->m_clipMode == 0) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (dst->y < threshold) {
                                    flags[i] = 1;
                                }
                            } else if (*(short*)(polygon + 0x12 + (i * 6)) < threshold) {
                                flags[i] = 1;
                            }
                        } else if (stepData->m_clipMode == 1) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (threshold < dst->y) {
                                    flags[i] = 1;
                                }
                            } else if (threshold < *(short*)(polygon + 0x12 + (i * 6))) {
                                flags[i] = 1;
                            }
                        }
                    }

                    if (flags[0] == 0) {
                        polygon[0] = 0;
                    } else {
                        polygon[0] = 1;
                        if (flags[1] == 0) {
                            polygon[0] = 0;
                        } else {
                            polygon[0] = 1;
                            if (flags[2] == 0) {
                                polygon[0] = 0;
                            } else {
                                polygon[0] = 1;
                            }
                        }
                    }

                    if (stepData->m_worldSpaceMode == 1 && polygon[0] != 0) {
                        *(S16Vec*)(polygon + 0x10) = transformed[0];
                        *(S16Vec*)(polygon + 0x16) = transformed[1];
                        *(S16Vec*)(polygon + 0x1C) = transformed[2];
                    }
                }

                if (polygon[0] == 0) {
                    if (stepData->m_worldSpaceMode == 1) {
                        *(S16Vec*)(polygon + 0x10) = transformed[0];
                        *(S16Vec*)(polygon + 0x16) = transformed[1];
                        *(S16Vec*)(polygon + 0x1C) = transformed[2];
                    }
                } else {
                    int sumX = (int)*(short*)(polygon + 0x10) + (int)*(short*)(polygon + 0x16) + (int)*(short*)(polygon + 0x1C);
                    int sumY = (int)*(short*)(polygon + 0x12) + (int)*(short*)(polygon + 0x18) + (int)*(short*)(polygon + 0x1E);
                    int sumZ = (int)*(short*)(polygon + 0x14) + (int)*(short*)(polygon + 0x1A) + (int)*(short*)(polygon + 0x20);
                    short avgX = (short)(sumX / 3);
                    short avgY = (short)(sumY / 3);
                    short avgZ = (short)(sumZ / 3);

                    if (avgX >= -0x7530 && avgX <= 0x7530 && avgY >= -0x7530 && avgY <= 0x7530 && avgZ >= -0x7530 &&
                        avgZ <= 0x7530) {
                        Vec center;
                        Vec verts[3];
                        S16Vec normalA;
                        S16Vec normalB;
                        Vec axis;
                        Vec velocity;
                        Quaternion rotQuat;
                        Mtx rotMtx;
                        float sinValue = FLOAT_80332048;
                        float cosValue = FLOAT_80332048;

                        center.x = FLOAT_80332048;
                        center.y = FLOAT_80332048;
                        center.z = FLOAT_80332048;

                        for (int i = 0; i < 3; i++) {
                            S16Vec pos;
                            pos.x = *(short*)(polygon + 0x10 + (i * 6));
                            pos.y = *(short*)(polygon + 0x12 + (i * 6));
                            pos.z = *(short*)(polygon + 0x14 + (i * 6));
                            ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &verts[i], pos, modelData->m_posQuant);
                            PSVECAdd(&center, &verts[i], &center);
                        }

                        PSVECScale(&center, &center, FLOAT_80332058);

                        normalB.x = *(short*)(polygon + 0xA);
                        normalB.y = *(short*)(polygon + 0xC);
                        normalB.z = *(short*)(polygon + 0xE);
                        ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &axis, normalB, modelData->m_normQuant);

                        normalA.x = *(short*)(polygon + 4);
                        normalA.y = *(short*)(polygon + 6);
                        normalA.z = *(short*)(polygon + 8);
                        ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &velocity, normalA, modelData->m_normQuant);
                        PSVECScale(&velocity, &velocity, stepData->m_velocityBase + Math.RandF(stepData->m_velocityRange));

                        C_QUATRotAxisRad(&rotQuat, &axis, FLOAT_8033205c * (float)polygon[1]);
                        PSMTXQuat(rotMtx, &rotQuat);

                        if (stepData->m_spinMode == 1) {
                            int rand10 = (rand() % 10) + 10;
                            short* angleState = (short*)(polygon + 4);
                            if (*(short*)(polygon + 6) == 0) {
                                *angleState += (short)rand10;
                            } else {
                                *angleState -= (short)rand10;
                            }

                            if (*angleState > 0x168) {
                                *angleState = (short)(*angleState - 0x168);
                            }
                            if (*angleState < 0) {
                                *angleState = (short)(*angleState + 0x168);
                            }

                            s32 sinIndex = (s32)(((float)((int)(*angleState << 15))) / FLOAT_80332060);
                            sinValue = *(float*)((u8*)gPppTrigTable + (sinIndex & 0xFFFC));
                            cosValue = *(float*)((u8*)gPppTrigTable + ((sinIndex + 0x4000) & 0xFFFC));
                        }

                        for (int i = 0; i < 3; i++) {
                            Vec translated;
                            float wobbleScale;

                            PSVECSubtract(&verts[i], &center, &translated);
                            PSMTXMultVec(rotMtx, &translated, &translated);
                            PSVECAdd(&translated, &center, &verts[i]);

                            if (stepData->m_spinMode == 0) {
                                verts[i].x += velocity.x;
                                verts[i].y += velocity.y - stepData->m_gravity * (float)*(u16*)(polygon + 2);
                                verts[i].z += velocity.z;
                            } else if (stepData->m_spinMode == 1) {
                                wobbleScale = FLOAT_8033204c + Math.RandF(FLOAT_80332064);
                                verts[i].x += cosValue * wobbleScale;
                                verts[i].y += velocity.y - stepData->m_gravity * (float)*(u16*)(polygon + 2);
                                wobbleScale = FLOAT_8033204c + Math.RandF(FLOAT_80332064);
                                verts[i].z += sinValue * wobbleScale;
                            }

                            verts[i].x += stepData->m_direction.x * workData->m_value3;
                            verts[i].y += stepData->m_direction.y * workData->m_value3;
                            verts[i].z += stepData->m_direction.z * workData->m_value3;

                            ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, (S16Vec*)(polygon + 0x10 + (i * 6)), verts[i],
                                                                 modelData->m_posQuant);
                        }
                        *(short*)(polygon + 2) = *(short*)(polygon + 2) + 1;
                    }
                }

                polygon += 0x34;
            }
        }

        mesh = (CChara::CMesh*)((u8*)mesh + 0x14);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8014099C
 * PAL Size: 812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitPolygonParameter(PCharaBreak* charaBreak, VCharaBreak*, POLYGON_DATA* polygonData, unsigned long polygonCount,
                          CChara::CModel* model, CChara::CMesh* mesh)
{
    CharaBreakStep* stepData = (CharaBreakStep*)charaBreak;
    CharaBreakMeshRef* meshRef = reinterpret_cast<CharaBreakMeshRef*>(mesh);
    S16Vec* workNormals = meshRef->m_workNormals;
    u32 count = polygonCount;
    CChara::CModel* modelPtr = model;
    POLYGON_DATA* polygon = polygonData;
    f32 zero = FLOAT_80332048;

    for (u32 i = 0; i < count; i++) {
        Vec normal;
        Vec up = kPppCharaBreakUpVector;
        Vec tangent;

        int alpha = (int)stepData->m_alphaBase + rand() % stepData->m_alphaRange;
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }

        polygon->m_alpha = (u8)alpha;
        polygon->m_enabled = 0;
        polygon->_pad2 = 0;

        if (stepData->m_clipMode == 2) {
            polygon->m_enabled = 1;
        }

        if (meshRef->m_data->m_skinCount == 0) {
            normal.x = Math.RandF(FLOAT_8033204c);
            normal.y = Math.RandF(FLOAT_8033204c);
            normal.z = Math.RandF(FLOAT_8033204c);
            normal.x *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            normal.y *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            normal.z *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            PSVECNormalize(&normal, &normal);
            ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, &polygon->m_normalA, normal, ModelData(modelPtr)->m_normQuant);
        } else {
            polygon->m_normalA = workNormals[polygon->m_nrmIndices[0]];
            ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &normal, workNormals[polygon->m_nrmIndices[0]],
                                                ModelData(modelPtr)->m_normQuant);
        }

        PSVECCrossProduct(&up, &normal, &tangent);
        float tangentMag = PSVECMag(&tangent);
        if (zero == tangentMag) {
            tangent.x = zero;
            tangent.y = zero;
            tangent.z = zero;
        } else {
            PSVECScale(&tangent, &tangent, FLOAT_8033204c / tangentMag);
        }

        if (zero == tangent.x && zero == tangent.y && zero == tangent.z) {
            tangent.x = FLOAT_8033204c;
            tangent.y = zero;
            tangent.z = zero;
        }

        if (stepData->m_spinMode != 0 && stepData->m_spinMode == 1) {
            polygon->m_normalA.z = 0;
            polygon->m_normalA.y = 0;
            polygon->m_normalA.x = 0;
            polygon->m_normalA.y = rand() % 2;
        }

        ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, &polygon->m_normalB, tangent, ModelData(modelPtr)->m_normQuant);
        polygon++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80140CC8
 * PAL Size: 592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CreatePolygon(POLYGON_DATA* polygonData, void* displayList, unsigned long, CChara::CModel* model, CChara::CMesh* mesh)
{
    u8* polygonBytes = (u8*)polygonData;
    CharaBreakMeshRef* meshRef = reinterpret_cast<CharaBreakMeshRef*>(mesh);
    CharaBreakMeshData* meshData = meshRef->m_data;
    s32 isRigid = 0;
    S16Vec* workPositions;
    BOOL transformPositions = FALSE;
    Mtx meshMtx;

    if (meshData->m_skinCount == 0) {
        isRigid = 1;
        PSMTXConcat(ModelDrawMtx(model), *(Mtx*)((u8*)ModelNodes(model) + (meshData->m_nodeIndex * 0xC0) + 0x6C),
                    meshMtx);
    }
    workPositions = meshRef->m_workPositions;
    u16* stream = (u16*)displayList;

    s32 keepReading = 1;
    while (keepReading != 0) {
        u8 drawCmd = *(u8*)stream;
        u16 drawCount = *(u16*)((u8*)stream + 1);
        u8 drawMode = drawCmd & 7;
        u8 primitive = drawCmd & 0xF8;
        s16 triCount;
        s32 keepTri;
        s32 outVertex;
        u16* stripRestart;

        stream = (u16*)((u8*)stream + 3);
        if (IsHasDrawFmtDL__5CUtilFUc(&gUtil, drawCmd) == 0) {
            keepReading = 0;
        } else {
            triCount = (s16)(drawCount - 2);
            keepTri = 1;
            outVertex = 0;
            stripRestart = 0;

            if (primitive == 0x90) {
                triCount = (s16)((s32)drawCount / 3);
            }

            while (keepTri != 0) {
                u16* previousRestart = stripRestart;
                u16 posIndex = stream[0];
                u16 nrmIndex = stream[1];
                u16 texIndex = stream[3];

                stream += 4;
                if (drawMode == 2) {
                    stream++;
                }

                if (isRigid != 0) {
                    S16Vec* sourcePos = workPositions + posIndex;
                    S16Vec posQuantized = *sourcePos;
                    Vec posFloat;

                    ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &posFloat, posQuantized, ModelData(model)->m_posQuant);
                    PSMTXMultVec(meshMtx, &posFloat, &posFloat);
                    ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, (S16Vec*)(polygonBytes + (outVertex * 6) + 0x10), posFloat,
                                                        ModelData(model)->m_posQuant);
                } else {
                    S16Vec* sourcePos = workPositions + posIndex;
                    s32 positionOffset = outVertex * 6;
                    *(s16*)(polygonBytes + positionOffset + 0x10) = sourcePos->x;
                    *(s16*)(polygonBytes + positionOffset + 0x12) = sourcePos->y;
                    *(s16*)(polygonBytes + positionOffset + 0x14) = sourcePos->z;
                }

                *(u16*)(polygonBytes + (outVertex * 2) + 0x22) = posIndex;
                *(u16*)(polygonBytes + (outVertex * 2) + 0x2E) = texIndex;
                *(u16*)(polygonBytes + (outVertex * 2) + 0x28) = nrmIndex;
                outVertex++;
                stripRestart = previousRestart;

                if (primitive == 0x90) {
                    if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        outVertex = 0;
                        polygonBytes += 0x34;
                    }
                } else if (primitive == 0x98) {
                    if (outVertex == 1) {
                        stripRestart = stream;
                    } else if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        if (triCount != 1) {
                            stream = previousRestart;
                        }
                        outVertex = 0;
                        polygonBytes += 0x34;
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80140F18
 * PAL Size: 708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f(void* model, void* modelData, void*,
                                                                                 s32 meshIndex, Mtx meshMtx)
{
    Mtx cameraMtx;
    Mtx drawMtx;

    CharaBreakWork* workData = reinterpret_cast<CharaBreakWork*>(modelData);
    CChara::CModel* modelPtr = reinterpret_cast<CChara::CModel*>(model);
    CharaBreakMeshRef* meshArray = ModelMeshes(modelPtr);

    if (workData->m_enabled != 0) {
        CharaBreakMeshRef* meshRef = &meshArray[meshIndex];
        CharaBreakMeshData* meshData = meshRef->m_data;
        CharaBreakDisplayList* materialData = meshData->m_displayLists;
        PSMTXCopy(CameraMatrix(), cameraMtx);

        s32 materialIndex = meshData->m_displayListCount - 1;
        s32 materialOffset = materialIndex * 4;

        for (; materialIndex >= 0; materialIndex--, materialData++) {
            CharaBreakDisplayListPair** meshTable =
                reinterpret_cast<CharaBreakDisplayListPair**>(workData->m_meshBuffers) + meshIndex;
            CharaBreakDisplayListPair** displayListEntry =
                reinterpret_cast<CharaBreakDisplayListPair**>(reinterpret_cast<u8*>(*meshTable) + materialOffset);
            POLYGON_DATA* vertexData = (*displayListEntry)->m_polygonData;

            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                &MaterialMan, ModelData(modelPtr)->m_materialSet, materialData->m_material, 0, 0);

            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXSetCullMode(GX_CULL_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc((GXAttr)9, GX_DIRECT);
            GXSetVtxDesc((GXAttr)10, GX_INDEX16);
            GXSetVtxDesc((GXAttr)11, GX_INDEX16);
            GXSetVtxDesc((GXAttr)13, GX_INDEX16);
            GXSetVtxDesc((GXAttr)14, GX_INDEX16);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, GX_POS_XYZ, GX_S16, ModelData(modelPtr)->m_posQuant & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, GX_NRM_XYZ, GX_S16, ModelData(modelPtr)->m_normQuant & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, GX_TEX_ST, GX_S16, 0xC);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)14, GX_TEX_ST, GX_S16, 0xC);

            if (meshRef->m_data->m_skinCount == 0) {
                GXLoadPosMtxImm(cameraMtx, 0);
            } else {
                PSMTXConcat(cameraMtx, meshMtx, drawMtx);
                GXLoadPosMtxImm(drawMtx, 0);
            }

            GXBegin((GXPrimitive)0x90, (GXVtxFmt)7, (*displayListEntry)->m_polygonCount * 3);
            POLYGON_DATA* polygon = vertexData;
            s32 faceIndex = 0;
            u16 zero = 0;
            while (faceIndex < (s32)(u32)(*displayListEntry)->m_polygonCount) {
                s16 posZ = polygon->m_pos0.z;
                s16 posY = polygon->m_pos0.y;
                faceIndex++;
                s16 posX = polygon->m_pos0.x;
                GXWGFifo.u16 = posX;
                GXWGFifo.u16 = posY;
                GXWGFifo.u16 = posZ;
                GXWGFifo.u16 = polygon->m_nrmIndices[0];
                GXWGFifo.u16 = zero;
                GXWGFifo.u16 = polygon->m_texIndices[0];
                GXWGFifo.u16 = polygon->m_texIndices[0];
                posZ = polygon->m_pos1.z;
                posY = polygon->m_pos1.y;
                posX = polygon->m_pos1.x;
                GXWGFifo.u16 = posX;
                GXWGFifo.u16 = posY;
                GXWGFifo.u16 = posZ;
                GXWGFifo.u16 = polygon->m_nrmIndices[1];
                GXWGFifo.u16 = zero;
                GXWGFifo.u16 = polygon->m_texIndices[1];
                GXWGFifo.u16 = polygon->m_texIndices[1];
                posZ = polygon->m_pos2.z;
                posY = polygon->m_pos2.y;
                posX = polygon->m_pos2.x;
                GXWGFifo.u16 = posX;
                GXWGFifo.u16 = posY;
                GXWGFifo.u16 = posZ;
                GXWGFifo.u16 = polygon->m_nrmIndices[2];
                GXWGFifo.u16 = zero;
                GXWGFifo.u16 = polygon->m_texIndices[2];
                polygon++;
                GXWGFifo.u16 = polygon[-1].m_texIndices[2];
            }

            materialOffset -= 4;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801411DC
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi(void)
{
}

/*
 * --INFO--
 * PAL Address: 0x801411E4
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" u32 CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv(u32 value, void* modelData, void* meshData)
{
    if (*(u32*)((u8*)modelData + 0x44) == 0) {
        return value;
    }

    return (u32)__cntlzw(1 - (u32)*((u8*)meshData + 0x42)) >> 5;
}
