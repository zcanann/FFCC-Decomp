#include "ffcc/pppCharaBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include <string.h>
#include "ffcc/ppp_linkage.h"

struct _pppMngStCharaBreak {
    u8 _pad0[0xD8];
    void* m_charaObj;
};
extern _pppMngStCharaBreak* pppMngStPtr;

extern struct _pppEnvSt {
    CMemory::CStage* m_stagePtr;
} *pppEnvStPtr;
class CMaterialMan;
static const char s_pppCharaBreak_cpp_801dd690[] = "pppCharaBreak.cpp";
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
extern int DAT_801dd684;
extern int DAT_801dd688;
extern int DAT_801dd68c;
extern Vec kPppCharaBreakUpVector;
extern int ppvSinTbl;
extern void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void* materialMan, void* materialSet,
                                                                        unsigned int materialIdx, int, int);
static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

static inline Mtx& CameraMatrix()
{
    return *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(&CameraPcs) + 0x1C);
}

void pppInitBlendMode(void);

extern "C" {
int rand(void);
void* GetCharaHandlePtr__FP8CGObjectl(void*, long);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
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

struct CharaBreakStep {
    s32 m_graphId;
    f32 m_dataValIndex;
    f32 m_graphInit;
    f32 m_graphStep;
    f32 m_gravity;
    f32 _pad14;
    Vec m_direction;
    u8 _pad24[0x4];
    f32 m_payloadGraphInit;
    f32 m_payloadGraphStep;
    f32 m_payloadGraphStepStep;
    u8 m_alphaBase;
    u8 m_alphaRange;
    u8 _pad36[0x2];
    f32 m_velocityBase;
    f32 m_velocityRange;
    u8 m_spinMode;
    u8 m_clipMode;
    u8 m_worldSpaceMode;
    u8 _pad43;
};

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
    u8* m_model;
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
    u8 _pad0[0x12];
    u16 m_meshCount;
    u8 _padC[0x14];
    void* m_materialSet;
    u8 _pad24[0x8];
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
STATIC_ASSERT(offsetof(CharaBreakModelData, m_meshCount) == 0x12);
STATIC_ASSERT(offsetof(CharaBreakModelData, m_materialSet) == 0x28);
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
    Mtx drawMtx;
    Mtx cameraMtx;

    if (*(s32*)((u8*)modelData + 0x44) != 0) {
        s32 meshArrayBase = *(s32*)((u8*)model + 0xAC) + meshIndex * 0x14;
        s32 meshData = *(s32*)((u8*)meshArrayBase + 8);
        s32 materialData = *(s32*)((u8*)meshData + 0x50);
        s32 materialIndex;
        s32 materialOffset;

        PSMTXCopy(CameraMatrix(), cameraMtx);

        materialIndex = *(s32*)((u8*)meshData + 0x4C) - 1;
        materialOffset = materialIndex * 4;

        for (; materialIndex >= 0; materialIndex--) {
            s32 meshTable = *(s32*)((u8*)*(s32*)((u8*)modelData + 0x1C) + meshIndex * 4);
            s32 displayList = *(s32*)((u8*)meshTable + materialOffset);
            s32 vertexData = *(s32*)((u8*)displayList + 0xC);
            s32 faceIndex = 0;

            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                &MaterialMan, *(void**)((u8*)*(s32*)((u8*)model + 0xA4) + 0x24), *(u16*)((u8*)materialData + 8), 0, 0);

            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXSetCullMode(GX_CULL_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc((GXAttr)9, GX_DIRECT);
            GXSetVtxDesc((GXAttr)10, GX_INDEX16);
            GXSetVtxDesc((GXAttr)11, GX_INDEX16);
            GXSetVtxDesc((GXAttr)13, GX_INDEX16);
            GXSetVtxDesc((GXAttr)14, GX_INDEX16);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, GX_POS_XYZ, GX_S16, *(u32*)((u8*)*(s32*)((u8*)model + 0xA4) + 0x34) & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, GX_CLR_RGB, GX_RGBA8, *(u32*)((u8*)*(s32*)((u8*)model + 0xA4) + 0x38) & 0xFF);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)11, GX_NRM_XYZ, GX_S16, 0);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)13, GX_TEX_ST, GX_S16, 0xC);
            GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)14, GX_TEX_ST, GX_S16, 0xC);

            if (*(s32*)((u8*)*(s32*)((u8*)meshArrayBase + 8) + 0x54) == 0) {
                GXLoadPosMtxImm(cameraMtx, 0);
            } else {
                PSMTXConcat(cameraMtx, meshMtx, drawMtx);
                GXLoadPosMtxImm(drawMtx, 0);
            }

            GXBegin((GXPrimitive)0x90, (GXVtxFmt)7, *(u16*)((u8*)displayList + 8) * 3);
            while (faceIndex < (s32)(u32)*(u16*)((u8*)displayList + 8)) {
                faceIndex++;
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x10);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x12);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x14);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x28);
                GXWGFifo.u16 = 0;
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2E);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2E);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x16);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x18);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1A);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2A);
                GXWGFifo.u16 = 0;
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x30);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x30);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1C);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x1E);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x20);
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x2C);
                GXWGFifo.u16 = 0;
                GXWGFifo.u16 = *(u16*)((u8*)vertexData + 0x32);
                vertexData += 0x34;
                GXWGFifo.u16 = *(u16*)((u8*)vertexData - 2);
            }

            materialOffset -= 4;
            materialData += 0xC;
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
    CharaBreakMeshRef* meshRef = reinterpret_cast<CharaBreakMeshRef*>(mesh);
    CharaBreakMeshData* meshData = meshRef->m_data;
    s32 isRigid = 0;
    S16Vec* workPositions;
    u16* stream = (u16*)displayList;
    u8* polygonBytes = (u8*)polygonData;
    BOOL transformPositions = FALSE;
    Mtx meshMtx;

    if (meshData->m_skinCount == 0) {
        isRigid = 1;
        PSMTXConcat(ModelDrawMtx(model), *(Mtx*)((u8*)ModelNodes(model) + (meshData->m_nodeIndex * 0xC0) + 0x6C),
                    meshMtx);
    }
    workPositions = meshRef->m_workPositions;

    s32 keepReading = 1;
    while (keepReading != 0) {
        u8 drawCmd = *(u8*)stream;
        u16 drawCount = *(u16*)((u8*)stream + 1);
        u8 primitive = drawCmd & 0xF8;
        s16 triCount;
        s32 outVertex;
        u16* stripRestart;

        stream = (u16*)((u8*)stream + 3);
        if (IsHasDrawFmtDL__5CUtilFUc(&gUtil, drawCmd) == 0) {
            keepReading = 0;
        } else {
            triCount = (s16)(drawCount - 2);
            outVertex = 0;
            stripRestart = 0;
            s32 keepTri = 1;

            if (primitive == 0x90) {
                triCount = (s16)((s32)drawCount / 3);
            }

            while (keepTri != 0) {
                u16* previousRestart = stripRestart;
                u16 posIndex = stream[0];
                u16 nrmIndex = stream[1];
                u16 texIndex = stream[3];

                stripRestart = stream + 4;
                if ((drawCmd & 7) == 2) {
                    stripRestart = stream + 5;
                }
                stream = stripRestart;

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
                        if (triCount < 1) {
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
                        if (triCount < 1) {
                            keepTri = 0;
                        }
                        if ((triCount & 1) == 0) {
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
    u32 normQuant = ModelData(model)->m_normQuant;

    for (u32 i = 0; i < polygonCount; i++) {
        Vec normal;
        Vec tangent;
        Vec up = kPppCharaBreakUpVector;

        int alpha = (int)stepData->m_alphaBase + rand() % stepData->m_alphaRange;
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }

        polygonData->m_alpha = (u8)alpha;
        polygonData->m_enabled = 0;
        polygonData->_pad2 = 0;

        if (stepData->m_clipMode == 2) {
            polygonData->m_enabled = 1;
        }

        if (meshRef->m_data->m_skinCount == 0) {
            normal.x = Math.RandF(FLOAT_8033204c);
            normal.y = Math.RandF(FLOAT_8033204c);
            normal.z = Math.RandF(FLOAT_8033204c);
            normal.x *= (rand() % 2) ? FLOAT_80332078 : FLOAT_8033204c;
            normal.y *= (rand() % 2) ? FLOAT_80332078 : FLOAT_8033204c;
            normal.z *= (rand() % 2) ? FLOAT_80332078 : FLOAT_8033204c;
            PSVECNormalize(&normal, &normal);
            ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, &polygonData->m_normalA, normal, normQuant);
        } else {
            polygonData->m_normalA = workNormals[polygonData->m_nrmIndices[0]];
            ConvI2FVector__5CUtilFR3Vec6S16Vecl(&gUtil, &normal, polygonData->m_normalA, normQuant);
        }

        PSVECCrossProduct(&up, &normal, &tangent);
        float tangentMag = PSVECMag(&tangent);
        if (tangentMag == FLOAT_80332048) {
            tangent.x = FLOAT_80332048;
            tangent.y = FLOAT_80332048;
            tangent.z = FLOAT_80332048;
        } else {
            PSVECScale(&tangent, &tangent, FLOAT_8033204c / tangentMag);
        }

        if (tangent.x == FLOAT_80332048 && tangent.y == FLOAT_80332048 && tangent.z == FLOAT_80332048) {
            tangent.x = FLOAT_8033204c;
            tangent.y = FLOAT_80332048;
            tangent.z = FLOAT_80332048;
        }

        if (stepData->m_spinMode == 1) {
            polygonData->m_normalA.x = 0;
            polygonData->m_normalA.z = 0;
            polygonData->m_normalA.y = rand() % 2;
        }

        ConvF2IVector__5CUtilFR6S16Vec3Vecl(&gUtil, &polygonData->m_normalB, tangent, normQuant);
        polygonData++;
    }
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

                            u32 sinIndex = (u32)(((float)((int)(*angleState << 15))) / FLOAT_80332060);
                            sinValue = *(float*)((int)ppvSinTbl + (sinIndex & 0xFFFC));
                            cosValue = *(float*)((int)ppvSinTbl + ((sinIndex + 0x4000) & 0xFFFC));
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
    u8* work = (u8*)charaBreak + 0x80 + dataOffset;

    *(u32*)(work + 0x1C) = 0;
    *(float*)(work + 0xC) = fVar1;
    *(float*)(work + 8) = fVar1;
    *(float*)(work + 4) = fVar1;
    *(float*)(work + 0x18) = fVar1;
    *(float*)(work + 0x14) = fVar1;
    *(float*)(work + 0x10) = fVar1;
    *(u32*)(work + 0x44) = 1;
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
    u8* work = (u8*)charaBreak + 0x80 + dataOffset;

    *(float*)(work + 0xC) = FLOAT_80332048;
    *(float*)(work + 8) = fVar1;
    *(float*)(work + 4) = fVar1;
    *(float*)(work + 0x18) = fVar1;
    *(float*)(work + 0x14) = fVar1;
    *(float*)(work + 0x10) = fVar1;
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

    CharaBreakWork* work = (CharaBreakWork*)((u8*)charaBreak + 0x80 + data->m_serializedDataOffsets[2]);
    u8* model = work->m_model;

    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xF4) = 0;
    *(u32*)(model + 0xFC) = 0;
    *(u32*)(model + 0x104) = 0;
    *(u32*)(model + 0xEC) = 0;

    void** perMeshBuffers = (void**)work->m_meshBuffers;
    u8* mesh = *(u8**)(model + 0xAC);
    void** meshBufferSlot = perMeshBuffers;

    if (perMeshBuffers != NULL) {
        for (u32 meshIndex = 0; meshIndex < *(u32*)(*(u8**)(model + 0xA4) + 0xC); meshIndex++) {
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
    u8* model;
    void* handle;
    u8* mesh;
    u32 meshCount;
    u32 i;

    if (gPppCalcDisabled != 0) {
        return;
    }

    stepData = (CharaBreakStep*)step;
    work = (CharaBreakWork*)((u8*)charaBreak + 0x80 + data->m_serializedDataOffsets[2]);
    if (work->m_enabled == 0) {
        return;
    }

    handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_charaObj, 0);
    model = (u8*)GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    work->m_model = model;

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf((float)stepData->m_dataValIndex,
                                                 charaBreak,
                                                 stepData->m_graphId,
                                                 &work->m_value0,
                                                 &work->m_value1,
                                                 &work->m_value2,
                                                 &stepData->m_graphInit,
                                                 &stepData->m_graphStep);

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(stepData->m_payloadGraphInit,
                                                 charaBreak,
                                                 stepData->m_graphId,
                                                 &work->m_value3,
                                                 &work->m_value4,
                                                 &work->m_value5,
                                                 &stepData->m_payloadGraphStep,
                                                 &stepData->m_payloadGraphStepStep);

    *(u32*)(model + 0xE4) = (u32)work;
    *(u32*)(model + 0xE8) = (u32)stepData;
    *(u32*)(model + 0xF4) = (u32)CharaBreak_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
    *(u32*)(model + 0xFC) = (u32)CharaBreak_DrawMeshDLCallback__FPQ26CChara6CModelPvPviiPA4_f;
    *(u32*)(model + 0x104) = (u32)CharaBreak_AfterDrawMeshCallback__FPQ26CChara6CModelPvPviPA4_f;
    *(u32*)(model + 0xEC) = (u32)CharaBreak_BeforeCalcMatrixCallback__FPQ26CChara6CModelPvPv;

    if (stepData->m_graphId == *(s32*)charaBreak) {
        f32 zero = FLOAT_80332048;
        if (stepData->m_direction.x == zero && stepData->m_direction.y == zero &&
            stepData->m_direction.z == zero) {
            stepData->m_direction.x = FLOAT_8033204c;
            stepData->m_direction.y = zero;
            stepData->m_direction.z = zero;
        } else {
            PSVECNormalize(&stepData->m_direction, &stepData->m_direction);
        }
    }

    mesh = reinterpret_cast<u8*>(ModelMeshes(reinterpret_cast<CChara::CModel*>(model)));
    meshCount = ModelData(reinterpret_cast<CChara::CModel*>(model))->m_meshCount;

    if (work->m_meshBuffers == NULL) {
        work->m_miscValue = FLOAT_80332050;
        work->m_meshBuffers = pppMemAlloc__FUlPQ27CMemory6CStagePci(meshCount << 2, pppEnvStPtr->m_stagePtr,
                                                                     const_cast<char*>(s_pppCharaBreak_cpp_801dd690),
                                                                     0x3D0);
        if (work->m_meshBuffers == NULL) {
            goto fail;
        }

        for (i = 0; i < ModelData(reinterpret_cast<CChara::CModel*>(model))->m_meshCount; i++) {
            ((u32*)work->m_meshBuffers)[i] = 0;
        }

        for (i = 0; i < meshCount; i++) {
            CharaBreakMeshData* meshData = *(CharaBreakMeshData**)(mesh + 8);

            if (strcmp(meshData->m_name, "") == 0) {
                CalcBoundaryBoxQuantized__5CUtilFP3VecP3VecP6S16VecUlUl(
                    &gUtil,
                    &work->m_bboxMin,
                    &work->m_bboxMax,
                    reinterpret_cast<CharaBreakMeshRef*>(mesh)->m_workPositions,
                    meshData->m_vertexCount,
                    ModelData(reinterpret_cast<CChara::CModel*>(model))->m_posQuant);
            }

            ((u32*)work->m_meshBuffers)[i] = (u32)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                meshData->m_displayListCount << 2, pppEnvStPtr->m_stagePtr,
                const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x3E9);
            if (((u32*)work->m_meshBuffers)[i] == 0) {
                goto fail;
            }

            {
                int displayListCount = meshData->m_displayListCount;
                int* dlEntries = (int*)((u32*)work->m_meshBuffers)[i];
                for (int dl = displayListCount - 1; dl >= 0; dl--) {
                    dlEntries[dl] = 0;
                }
            }

            {
                int displayListCount = meshData->m_displayListCount;
                CharaBreakDisplayList* displayList = meshData->m_displayLists;
                CharaBreakDisplayListPair** dlEntries =
                    (CharaBreakDisplayListPair**)(((u32*)work->m_meshBuffers)[i] + ((displayListCount - 1) << 2));
                for (int dl = displayListCount - 1; dl >= 0; dl--) {
                    *dlEntries = (CharaBreakDisplayListPair*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                        0x10, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x3FC);
                    CharaBreakDisplayListPair* dlPair = *dlEntries;
                    if (dlPair == NULL) {
                        goto fail;
                    }

                    dlPair->m_rewrittenDisplayList = NULL;
                    dlPair->m_displayListSize = 0;
                    dlPair->m_polygonData = 0;
                    dlPair->m_displayListSize = displayList->m_size;
                    dlPair->m_rewrittenDisplayList = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                        dlPair->m_displayListSize, pppEnvStPtr->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x40B);
                    if (dlPair->m_rewrittenDisplayList == NULL) {
                        goto fail;
                    }

                    memcpy(dlPair->m_rewrittenDisplayList, displayList->m_data, dlPair->m_displayListSize);
                    ReWriteDisplayList__5CUtilFPvUlUl(&gUtil, dlPair->m_rewrittenDisplayList, dlPair->m_displayListSize, 1);

                    u32 polygonCount =
                        GetNumPolygonFromDL__5CUtilFPvUl(&gUtil, dlPair->m_rewrittenDisplayList, dlPair->m_displayListSize);
                    dlPair->m_polygonData = (POLYGON_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                        polygonCount * 0x34, pppEnvStPtr->m_stagePtr,
                        const_cast<char*>(s_pppCharaBreak_cpp_801dd690), 0x423);
                    if (dlPair->m_polygonData == NULL) {
                        goto fail;
                    }
                    dlPair->m_polygonCount = (u16)polygonCount;

                    CreatePolygon(dlPair->m_polygonData, displayList->m_data, displayList->m_size, (CChara::CModel*)model,
                                  (CChara::CMesh*)mesh);
                    InitPolygonParameter((PCharaBreak*)stepData, (VCharaBreak*)work, dlPair->m_polygonData, dlPair->m_polygonCount,
                                         (CChara::CModel*)model, (CChara::CMesh*)mesh);

                    dlEntries--;
                    displayList++;
                }
            }

            mesh += 0x14;
        }
    }

    if (gPppInConstructor == 0) {
        UpdatePolygonData((PCharaBreak*)stepData, (VCharaBreak*)work, (CChara::CModel*)model);
    }
    return;

fail:
    work->m_enabled = 0;
    *(u32*)(model + 0xE4) = 0;
    *(u32*)(model + 0xE8) = 0;
    *(u32*)(model + 0xF4) = 0;
    *(u32*)(model + 0xFC) = 0;
    *(u32*)(model + 0x104) = 0;
    *(u32*)(model + 0xEC) = 0;
}

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
    u8* work = (u8*)charaBreak + 0x80 + data->m_serializedDataOffsets[2];
    u8* colorWork = (u8*)charaBreak + 0x80 + colorOffset;

    if (*(u32*)(work + 0x44) != 0) {
        void* envColor = colorWork + 8;
        void* envMtx = (u8*)charaBreak + 0x40;

        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        pppInitBlendMode();
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            envColor,
            envMtx,
            FLOAT_80332048,
            0,
            0,
            0,
            0,
            1,
            1,
            0);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 2, 2, 3);
        work[0] = 0xFF;
        work[1] = 0xFF;
        work[2] = 0xFF;
        work[3] = colorWork[0xB];
    }
}
