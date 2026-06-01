#include "ffcc/pppCharaBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include "ffcc/ppp_linkage.h"

extern Vec kPppCharaBreakUpVector;
extern "C" const char s_pppCharaBreak_cpp[24] = "pppCharaBreak.cpp";
extern const float FLOAT_80332048;
extern const float FLOAT_8033204c;
extern const float FLOAT_80332050;
extern const char sPppCharaBreakObjMeshName[4];
extern const float FLOAT_80332058;
extern const float FLOAT_8033205c;
extern const float FLOAT_80332060;
extern const float FLOAT_80332064;
extern const double DOUBLE_80332068;
extern const double DOUBLE_80332070;
extern const float FLOAT_80332078;
extern const int kCharaBreakInitialVertexFlag0;
extern const int kCharaBreakInitialVertexFlag1;
extern const int kCharaBreakInitialVertexFlag2;

static inline Mtx& CameraMatrix()
{
    return CameraPcs.m_cameraMatrix;
}

struct POLYGON_DATA {
    u8 m_enabled;
    u8 m_alpha;
    u16 _pad2;
    S16Vec m_normalA;
    S16Vec m_normalB;
    S16Vec m_pos[3];
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

struct CharaBreakModelView {
    u8 _pad0[0xA4];
    CCharaModelData* m_data;
    void* m_nodes;
    CharaBreakMeshRef* m_meshes;
};

STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_data) == 0x8);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workPositions) == 0xC);
STATIC_ASSERT(offsetof(CharaBreakMeshRef, m_workNormals) == 0x10);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_data) == 0xA4);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_nodes) == 0xA8);
STATIC_ASSERT(offsetof(CharaBreakModelView, m_meshes) == 0xAC);
STATIC_ASSERT(offsetof(CCharaModelData, m_meshCount) == 0xC);
STATIC_ASSERT(offsetof(CCharaModelData, m_materialSet) == 0x24);
STATIC_ASSERT(offsetof(CCharaModelData, m_posQuant) == 0x34);
STATIC_ASSERT(offsetof(CCharaModelData, m_normQuant) == 0x38);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_displayListCount) == 0x4C);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_displayLists) == 0x50);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_skinCount) == 0x54);
STATIC_ASSERT(offsetof(CharaBreakMeshData, m_nodeIndex) == 0x5C);

static inline MtxPtr ModelDrawMtx(CChara::CModel* model)
{
    return reinterpret_cast<MtxPtr>(reinterpret_cast<u8*>(model) + 0x8);
}

static inline CCharaModelData* ModelData(CChara::CModel* model)
{
    return model->m_data;
}

static inline void* ModelNodes(CChara::CModel* model)
{
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(model) + 0xA8);
}

static inline CharaBreakMeshRef* ModelMeshes(CChara::CModel* model)
{
    return *reinterpret_cast<CharaBreakMeshRef**>(reinterpret_cast<u8*>(model) + 0xAC);
}

static inline CharaBreakMeshData* MeshData(CChara::CMesh* mesh)
{
    return reinterpret_cast<CharaBreakMeshData*>(mesh->m_data);
}

static void CharaBreak_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);
static void CharaBreak_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void CharaBreak_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
static int CharaBreak_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);

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
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        pppInitBlendMode();
        pppSetDrawEnv(
            (pppCVECTOR*)(colorWork + 8),
            (pppFMATRIX*)((u8*)charaBreak + 0x40),
            FLOAT_80332048,
            0,
            0,
            0,
            0,
            1,
            1,
            0);
        _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCCLR, GX_BL_SRCCLR, GX_LO_COPY);
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
    CGObject* handle;
    CChara::CMesh* mesh;
    u32 i;

    stepData = (CharaBreakStep*)step;
    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (CharaBreakWork*)(charaBreak->m_workArea + data->m_serializedDataOffsets[2]);
    handle = reinterpret_cast<CGObject*>(ppvMng->m_owner);
    if (work->m_enabled == 0) {
        return;
    }

    CCharaPcs::CHandle* charaHandle = GetCharaHandlePtr(handle, 0);
    model = GetCharaModelPtr(charaHandle);
    work->m_model = model;

    CalcGraphValue(reinterpret_cast<_pppPObject*>(charaBreak),
                                                 stepData->m_graphId,
                                                 work->m_value0,
                                                 work->m_value1,
                                                 work->m_value2,
                                                 stepData->m_dataValIndex,
                                                 stepData->m_graphInit,
                                                 stepData->m_graphStep);

    CalcGraphValue(reinterpret_cast<_pppPObject*>(charaBreak),
                                                 stepData->m_graphId,
                                                 work->m_value3,
                                                 work->m_value4,
                                                 work->m_value5,
                                                 stepData->m_payloadGraphInit,
                                                 stepData->m_payloadGraphStep,
                                                 stepData->m_payloadGraphStepStep);

    model->SetCallbackContext(work, stepData);
    model->SetBeforeMeshLockEnvCallback(CharaBreak_BeforeMeshLockEnvCallback);
    model->SetDrawMeshDLCallback(CharaBreak_DrawMeshDLCallback);
    model->SetAfterDrawMeshCallback(CharaBreak_AfterDrawMeshCallback);
    model->m_beforeCalcMatrixCallback = CharaBreak_BeforeCalcMatrixCallback;

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

    mesh = model->m_meshes;

    if (work->m_meshBuffers == NULL) {
        work->m_miscValue = FLOAT_80332050;
        work->m_meshBuffers =
            pppMemFree__FPv(ModelData(model)->m_meshCount << 2,
                            ppvEnv->m_stagePtr, const_cast<char*>(s_pppCharaBreak_cpp), 0x3D0);
        if (work->m_meshBuffers == NULL) {
            goto fail;
        }

        for (i = 0; i < ModelData(model)->m_meshCount; i++) {
            ((u32*)work->m_meshBuffers)[i] = 0;
        }

        for (i = 0; i < ModelData(model)->m_meshCount; i++) {
            {
                CharaBreakMeshData* meshData = MeshData(mesh);

                if (strcmp(meshData->m_name, sPppCharaBreakObjMeshName) == 0) {
                    gUtil.CalcBoundaryBoxQuantized(&work->m_bboxMin, &work->m_bboxMax,
                        mesh->m_workPositions, meshData->m_vertexCount,
                        ModelData(model)->m_posQuant);
                }
            }

            ((u32*)work->m_meshBuffers)[i] = (u32)pppMemFree__FPv(
                MeshData(mesh)->m_displayListCount << 2, ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppCharaBreak_cpp), 0x3E9);
            u32 meshBuffer = ((u32*)work->m_meshBuffers)[i];
            if (meshBuffer == 0) {
                goto fail;
            }

            {
                int displayListCount = MeshData(mesh)->m_displayListCount;
                int* dlEntries = (int*)meshBuffer;
                for (int dl = displayListCount - 1; dl >= 0; dl--) {
                    dlEntries[dl] = 0;
                }
            }

            {
                int displayListCount = MeshData(mesh)->m_displayListCount;
                CharaBreakDisplayList* displayList = MeshData(mesh)->m_displayLists;
                int dl = displayListCount - 1;
                CharaBreakDisplayListPair** dlEntries =
                    (CharaBreakDisplayListPair**)(meshBuffer + (dl << 2));
                for (; dl >= 0; dl--, displayList++) {
                    *dlEntries = (CharaBreakDisplayListPair*)pppMemFree__FPv(
                        0x10, ppvEnv->m_stagePtr, const_cast<char*>(s_pppCharaBreak_cpp), 0x3FC);
                    if (*dlEntries == NULL) {
                        goto fail;
                    }

                    (*dlEntries)->m_rewrittenDisplayList = NULL;
                    (*dlEntries)->m_displayListSize = 0;
                    (*dlEntries)->m_polygonData = 0;
                    (*dlEntries)->m_displayListSize = displayList->m_size;
                    (*dlEntries)->m_rewrittenDisplayList = pppMemFree__FPv(
                        displayList->m_size, ppvEnv->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp), 0x40B);
                    if ((*dlEntries)->m_rewrittenDisplayList == NULL) {
                        goto fail;
                    }

                    memcpy((*dlEntries)->m_rewrittenDisplayList, displayList->m_data, displayList->m_size);
                    gUtil.ReWriteDisplayList((*dlEntries)->m_rewrittenDisplayList, displayList->m_size, 1);

                    u32 polygonCount = gUtil.GetNumPolygonFromDL((*dlEntries)->m_rewrittenDisplayList, displayList->m_size);
                    (*dlEntries)->m_polygonData = (POLYGON_DATA*)pppMemFree__FPv(
                        polygonCount * 0x34, ppvEnv->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp), 0x423);
                    if ((*dlEntries)->m_polygonData == NULL) {
                        goto fail;
                    }
                    (*dlEntries)->m_polygonCount = (u16)polygonCount;

                    CreatePolygon((*dlEntries)->m_polygonData, displayList->m_data, displayList->m_size,
                                  model, mesh);
                    InitPolygonParameter((PCharaBreak*)stepData, (VCharaBreak*)work, (*dlEntries)->m_polygonData,
                                         (*dlEntries)->m_polygonCount, model, mesh);

                    dlEntries--;
                }
            }

            mesh++;
        }
    }

    if (gPppInConstructor == 0) {
        UpdatePolygonData((PCharaBreak*)stepData, (VCharaBreak*)work, model);
    }
    return;

fail:
    work->m_enabled = 0;
    model->SetCallbackContext(0, 0);
    model->SetBeforeMeshLockEnvCallback(0);
    model->SetDrawMeshDLCallback(0);
    model->SetAfterDrawMeshCallback(0);
    model->m_beforeCalcMatrixCallback = 0;
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
    Graphic._WaitDrawDone(const_cast<char*>(s_pppCharaBreak_cpp), 0x319);

    CharaBreakWork* work = (CharaBreakWork*)(charaBreak->m_workArea + data->m_serializedDataOffsets[2]);
    CChara::CModel* model = work->m_model;

    model->SetCallbackContext(0, 0);
    model->SetBeforeMeshLockEnvCallback(0);
    model->SetDrawMeshDLCallback(0);
    model->SetAfterDrawMeshCallback(0);
    model->m_beforeCalcMatrixCallback = 0;

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
                            pppHeapUseRate((CMemory::CStage*)*(void**)*dlEntries);
                            *(u32*)*dlEntries = 0;
                        }
                        if (*(void**)(*dlEntries + 0xC) != NULL) {
                            pppHeapUseRate((CMemory::CStage*)*(void**)(*dlEntries + 0xC));
                            *(u32*)(*dlEntries + 0xC) = 0;
                        }
                    }
                    if ((void*)*dlEntries != NULL) {
                        pppHeapUseRate((CMemory::CStage*)*dlEntries);
                        *dlEntries = 0;
                    }
                    dlEntries++;
                }
            }

            if (*meshBufferSlot != NULL) {
                pppHeapUseRate((CMemory::CStage*)*meshBufferSlot);
                *meshBufferSlot = NULL;
            }
            mesh += 0x14;
            meshBufferSlot++;
        }
    }

    if (perMeshBuffers != NULL) {
        pppHeapUseRate((CMemory::CStage*)perMeshBuffers);
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
    CChara::CMesh* mesh = model->m_meshes;
    u32 meshIndex;
    s16 threshold;

    threshold = (s32)((workData->m_value0 * (workData->m_bboxMax.y - workData->m_bboxMin.y)) *
                      (float)(1 << ModelData(model)->m_posQuant));

    for (meshIndex = 0; meshIndex < ModelData(model)->m_meshCount; meshIndex++) {
        s32 needsMtxUpdate = 0;
        Mtx meshToWorld;
        CharaBreakMeshData* meshData = MeshData(mesh);
        S16Vec* workPositions = mesh->m_workPositions;

        if (meshData->m_skinCount == 0 && stepData->m_worldSpaceMode == 1) {
            needsMtxUpdate = 1;
            PSMTXConcat(model->m_matrix, model->m_nodes[meshData->m_nodeIndex].m_mtx, meshToWorld);
        }

        for (int dl = meshData->m_displayListCount - 1; dl >= 0; dl--) {
            CharaBreakDisplayListPair** displayListPairs =
                reinterpret_cast<CharaBreakDisplayListPair**>(
                    reinterpret_cast<void**>(workData->m_meshBuffers)[meshIndex]);
            CharaBreakDisplayListPair* displayListPair = displayListPairs[dl];
            POLYGON_DATA* polygon = displayListPair->m_polygonData;

            for (u32 polyIndex = 0; polyIndex < displayListPair->m_polygonCount; polyIndex++) {
                S16Vec transformed[3];

                if (polygon->m_enabled == 0) {
                    int flags[3];
                    flags[0] = kCharaBreakInitialVertexFlag0;
                    flags[1] = kCharaBreakInitialVertexFlag1;
                    flags[2] = kCharaBreakInitialVertexFlag2;

                    for (int i = 0; i < 3; i++) {
                        S16Vec* dst = &transformed[i];
                        S16Vec* srcPos = workPositions + polygon->m_posIndices[i];

                        if (needsMtxUpdate) {
                            S16Vec worldPos;
                            Vec transformedPos;
                            worldPos.x = srcPos->x;
                            worldPos.y = srcPos->y;
                            worldPos.z = srcPos->z;
                            gUtil.ConvI2FVector(transformedPos, worldPos, ModelData(model)->m_posQuant);
                            PSMTXMultVec(meshToWorld, &transformedPos, &transformedPos);
                            gUtil.ConvF2IVector(*dst, transformedPos, ModelData(model)->m_posQuant);
                        } else {
                            *dst = *srcPos;
                        }

                        if (stepData->m_clipMode == 0) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (dst->y < threshold) {
                                    flags[i] = 1;
                                }
                            } else if (polygon->m_pos[i].y < threshold) {
                                flags[i] = 1;
                            }
                        } else if (stepData->m_clipMode == 1) {
                            if (stepData->m_worldSpaceMode == 1) {
                                if (dst->y > threshold) {
                                    flags[i] = 1;
                                }
                            } else if (polygon->m_pos[i].y > threshold) {
                                flags[i] = 1;
                            }
                        }
                    }

                    if (flags[0] == 0) {
                        polygon->m_enabled = 0;
                    } else {
                        polygon->m_enabled = 1;
                        if (flags[1] == 0) {
                            polygon->m_enabled = 0;
                        } else {
                            polygon->m_enabled = 1;
                            if (flags[2] == 0) {
                                polygon->m_enabled = 0;
                            } else {
                                polygon->m_enabled = 1;
                            }
                        }
                    }

                    if (stepData->m_worldSpaceMode == 1 && polygon->m_enabled != 0) {
                        polygon->m_pos[0] = transformed[0];
                        polygon->m_pos[1] = transformed[1];
                        polygon->m_pos[2] = transformed[2];
                    }
                }

                if (polygon->m_enabled == 0) {
                    if (stepData->m_worldSpaceMode == 1) {
                        polygon->m_pos[0] = transformed[0];
                        polygon->m_pos[1] = transformed[1];
                        polygon->m_pos[2] = transformed[2];
                    }
                } else {
                    Vec center;
                    center.z = FLOAT_80332048;
                    center.y = FLOAT_80332048;
                    center.x = FLOAT_80332048;

                    int sumX = (int)polygon->m_pos[0].x + (int)polygon->m_pos[1].x + (int)polygon->m_pos[2].x;
                    int sumY = (int)polygon->m_pos[0].y + (int)polygon->m_pos[1].y + (int)polygon->m_pos[2].y;
                    int sumZ = (int)polygon->m_pos[0].z + (int)polygon->m_pos[1].z + (int)polygon->m_pos[2].z;
                    short avgX = (short)(sumX / 3);
                    short avgY = (short)(sumY / 3);
                    short avgZ = (short)(sumZ / 3);

                    if (avgX >= -0x7530 && avgX <= 0x7530 && avgY >= -0x7530 && avgY <= 0x7530 && avgZ >= -0x7530 &&
                        avgZ <= 0x7530) {
                        Vec verts[3];
                        S16Vec normalA;
                        S16Vec normalB;
                        Vec axis;
                        Vec velocity;
                        Quaternion rotQuat;
                        Mtx rotMtx;
                        float cosValue;
                        float sinValue;

                        for (int i = 0; i < 3; i++) {
                            S16Vec pos = polygon->m_pos[i];
                            gUtil.ConvI2FVector(verts[i], pos, ModelData(model)->m_posQuant);
                            PSVECAdd(&center, &verts[i], &center);
                        }

                        PSVECScale(&center, &center, FLOAT_80332058);

                        normalB = polygon->m_normalB;
                        gUtil.ConvI2FVector(axis, normalB, ModelData(model)->m_normQuant);

                        normalA = polygon->m_normalA;
                        gUtil.ConvI2FVector(velocity, normalA, ModelData(model)->m_normQuant);
                        PSVECScale(&velocity, &velocity, stepData->m_velocityBase + Math.RandF(stepData->m_velocityRange));

                        C_QUATRotAxisRad(&rotQuat, &axis, FLOAT_8033205c * (float)polygon->m_alpha);
                        PSMTXQuat(rotMtx, &rotQuat);
                        cosValue = FLOAT_80332048;
                        sinValue = cosValue;

                        if (stepData->m_spinMode == 1) {
                            short* angleState = &polygon->m_normalA.x;
                            if (polygon->m_normalA.y == 0) {
                                int rand10 = (rand() % 10) + 10;
                                *angleState += rand10;
                            } else {
                                int rand10 = (rand() % 10) + 10;
                                *angleState -= rand10;
                            }

                            s32 angle = *angleState;
                            if (angle > 0x168) {
                                angle -= 0x168;
                                *angleState = angle;
                            }
                            angle = *angleState;
                            if (angle < 0) {
                                angle += 0x168;
                                *angleState = angle;
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
                                verts[i].y += velocity.y - stepData->m_gravity * (float)polygon->_pad2;
                                verts[i].z += velocity.z;
                            } else if (stepData->m_spinMode == 1) {
                                wobbleScale = FLOAT_8033204c + Math.RandF(FLOAT_80332064);
                                verts[i].x += cosValue * wobbleScale;
                                verts[i].y += velocity.y - stepData->m_gravity * (float)polygon->_pad2;
                                wobbleScale = FLOAT_8033204c + Math.RandF(FLOAT_80332064);
                                verts[i].z += sinValue * wobbleScale;
                            }

                            verts[i].x += stepData->m_direction.x * workData->m_value3;
                            verts[i].y += stepData->m_direction.y * workData->m_value3;
                            verts[i].z += stepData->m_direction.z * workData->m_value3;

                            gUtil.ConvF2IVector(polygon->m_pos[i], verts[i], ModelData(model)->m_posQuant);
                        }
                        polygon->_pad2++;
                    }
                }

                polygon++;
            }
        }

        mesh++;
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
    S16Vec* workNormals = mesh->m_workNormals;
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

        if (MeshData(mesh)->m_skinCount == 0) {
            normal.x = Math.RandF(FLOAT_8033204c);
            normal.y = Math.RandF(FLOAT_8033204c);
            normal.z = Math.RandF(FLOAT_8033204c);
            normal.x *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            normal.y *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            normal.z *= (rand() % 2) ? FLOAT_8033204c : FLOAT_80332078;
            PSVECNormalize(&normal, &normal);
            gUtil.ConvF2IVector(polygon->m_normalA, normal, ModelData(modelPtr)->m_normQuant);
        } else {
            polygon->m_normalA = workNormals[polygon->m_nrmIndices[0]];
            gUtil.ConvI2FVector(normal, workNormals[polygon->m_nrmIndices[0]], ModelData(modelPtr)->m_normQuant);
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

        gUtil.ConvF2IVector(polygon->m_normalB, tangent, ModelData(modelPtr)->m_normQuant);
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
    CharaBreakMeshData* meshData = MeshData(mesh);
    S16Vec* workPositions;
    s32 isRigid = 0;
    Mtx meshMtx;

    if (meshData->m_skinCount == 0) {
        isRigid = 1;
        PSMTXConcat(ModelDrawMtx(model), model->m_nodes[meshData->m_nodeIndex].m_mtx, meshMtx);
    }
    workPositions = mesh->m_workPositions;
    u16* stream = (u16*)displayList;

    s32 keepReading = 1;
    while (keepReading != 0) {
        u8 drawCmd = *(u8*)stream;
        u16 drawCount = *(u16*)((u8*)stream + 1);
        u8 drawMode = drawCmd & 7;
        u8 primitive = drawCmd & 0xF8;
        s32 keepTri;
        s32 outVertex;
        u16* stripRestart;
        s16 triCount;

        stream = (u16*)((u8*)stream + 3);
        if (gUtil.IsHasDrawFmtDL(drawCmd) == 0) {
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

                    gUtil.ConvI2FVector(posFloat, posQuantized, ModelData(model)->m_posQuant);
                    PSMTXMultVec(meshMtx, &posFloat, &posFloat);
                    gUtil.ConvF2IVector(polygonData->m_pos[outVertex], posFloat,
                        ModelData(model)->m_posQuant);
                } else {
                    S16Vec* sourcePos = workPositions + posIndex;
                    polygonData->m_pos[outVertex] = *sourcePos;
                }

                polygonData->m_posIndices[outVertex] = posIndex;
                polygonData->m_texIndices[outVertex] = texIndex;
                polygonData->m_nrmIndices[outVertex] = nrmIndex;
                outVertex++;
                stripRestart = previousRestart;

                if (primitive == 0x90) {
                    if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        outVertex = 0;
                        polygonData = reinterpret_cast<POLYGON_DATA*>((u8*)polygonData + 0x34);
                    }
                } else if (primitive == 0x98) {
                    if (outVertex == 1) {
                        stripRestart = stream;
                    } else if (outVertex == 3) {
                        triCount--;
                        if (triCount <= 0) {
                            keepTri = 0;
                        }
                        if ((__rlwnm(1, (u32)__cntlzw((s32)triCount), 31, 31) & 0xFF) == 0) {
                            stream = previousRestart;
                        }
                        outVertex = 0;
                        polygonData = reinterpret_cast<POLYGON_DATA*>((u8*)polygonData + 0x34);
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
static void CharaBreak_AfterDrawMeshCallback(
    CChara::CModel* modelPtr, void* modelData, void*, int meshIndex, float (*meshMtx)[4])
{
    Mtx cameraMtx;
    Mtx drawMtx;

    CharaBreakWork* workData = reinterpret_cast<CharaBreakWork*>(modelData);
    CChara::CMesh* meshArray = modelPtr->m_meshes;

    if (workData->m_enabled != 0) {
        CChara::CMesh* meshRef = &meshArray[meshIndex];
        CharaBreakMeshData* meshData = MeshData(meshRef);
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

            MaterialMan.SetMaterial(
                (CMaterialSet*)ModelData(modelPtr)->m_materialSet, materialData->m_material, 0, GX_CS_SCALE_1);

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

            if (MeshData(meshRef)->m_skinCount == 0) {
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
                s16 posZ = polygon->m_pos[0].z;
                s16 posY = polygon->m_pos[0].y;
                faceIndex++;
                s16 posX = polygon->m_pos[0].x;
                GXWGFifo.u16 = posX;
                GXWGFifo.u16 = posY;
                GXWGFifo.u16 = posZ;
                GXWGFifo.u16 = polygon->m_nrmIndices[0];
                GXWGFifo.u16 = zero;
                GXWGFifo.u16 = polygon->m_texIndices[0];
                GXWGFifo.u16 = polygon->m_texIndices[0];
                posZ = polygon->m_pos[1].z;
                posY = polygon->m_pos[1].y;
                posX = polygon->m_pos[1].x;
                GXWGFifo.u16 = posX;
                GXWGFifo.u16 = posY;
                GXWGFifo.u16 = posZ;
                GXWGFifo.u16 = polygon->m_nrmIndices[1];
                GXWGFifo.u16 = zero;
                GXWGFifo.u16 = polygon->m_texIndices[1];
                GXWGFifo.u16 = polygon->m_texIndices[1];
                posZ = polygon->m_pos[2].z;
                posY = polygon->m_pos[2].y;
                posX = polygon->m_pos[2].x;
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
static void CharaBreak_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4])
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
static void CharaBreak_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
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
static int CharaBreak_BeforeCalcMatrixCallback(CChara::CModel* model, void* modelData, void* meshData)
{
    if (*(u32*)((u8*)modelData + 0x44) == 0) {
        return reinterpret_cast<int>(model);
    }

    return (u32)__cntlzw(1 - (u32)*((u8*)meshData + 0x42)) >> 5;
}
