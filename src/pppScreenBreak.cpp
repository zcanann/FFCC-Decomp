#include "ffcc/pppScreenBreak.h"

#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/color.h"
#include "ffcc/gxfunc.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/linkage.h"
#include "ffcc/p_graphic.h"
#include "ffcc/ptrarray_fwd.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"

#include "dolphin/gx.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

typedef CChara::CMesh::CDisplayList ScreenBreakDisplayList;
typedef CChara::CMesh ScreenBreakMeshRef;
typedef CChara::CMesh::CRefData ScreenBreakMeshData;

struct ScreenBreakPiece {
    Vec m_velocity;
    Vec m_offset;
    Vec m_axis;
    Vec m_translation;
    float m_timer;
    float m_angle;
    u8 m_active;
    u8 m_pad39[3];
};

struct ScreenBreakColorData {
    u8 m_pad0[8];
    GXColor m_color;
};

STATIC_ASSERT(offsetof(ScreenBreakMeshRef, m_data) == 0x8);
STATIC_ASSERT(offsetof(CChara::CNode, m_localRuntimeMtx) == 0x14);
STATIC_ASSERT(offsetof(CChara::CNode, m_flags) == 0xBC);
STATIC_ASSERT(sizeof(ScreenBreakPiece) == 0x3C);
STATIC_ASSERT(offsetof(ScreenBreakPiece, m_offset) == 0x0C);
STATIC_ASSERT(offsetof(ScreenBreakPiece, m_translation) == 0x24);
STATIC_ASSERT(offsetof(ScreenBreakPiece, m_active) == 0x38);
STATIC_ASSERT(offsetof(VScreenBreak, m_pieces) == 0x0C);
STATIC_ASSERT(offsetof(VScreenBreak, m_backBufferTexObj) == 0x10);
STATIC_ASSERT(offsetof(VScreenBreak, m_extent) == 0x18);
STATIC_ASSERT(offsetof(VScreenBreak, m_backBufferReady) == 0x24);
STATIC_ASSERT(offsetof(VScreenBreak, m_color) == 0x28);
STATIC_ASSERT(offsetof(ScreenBreakColorData, m_color) == 0x08);
STATIC_ASSERT(offsetof(PScreenBreak, m_graphPayload) == 0x14);
STATIC_ASSERT(offsetof(PScreenBreak, m_gravityScale) == 0x18);
STATIC_ASSERT(offsetof(PScreenBreak, m_gravityDir) == 0x20);
STATIC_ASSERT(offsetof(PScreenBreak, m_gravityAmount) == 0x30);
STATIC_ASSERT(offsetof(PScreenBreak, m_angleRand) == 0x34);
STATIC_ASSERT(offsetof(PScreenBreak, m_speedBase) == 0x38);
STATIC_ASSERT(offsetof(PScreenBreak, m_speedRand) == 0x3C);
STATIC_ASSERT(sizeof(ScreenBreakDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(ScreenBreakDataOffsets, m_colorDataOffset) == 0x0);
STATIC_ASSERT(offsetof(ScreenBreakDataOffsets, m_valueOffset) == 0x8);

static const float kScreenBreakExtentScale = 2.0f;
static const float kScreenBreakZero = 0.0f;
static const float kScreenBreakTranslationRandLimit = 0.3f;
static const float kScreenBreakMeshCenterScale = -0.5f;
static const float kScreenBreakOne = 1.0f;
static const float kScreenBreakNegativeOne = -1.0f;
static const float kScreenBreakDegToRad = 0.017453292f;
static const double kScreenBreakS32ToDoubleBias = 4503599627370496.0;
static const float kScreenBreakLightOffset = 30.0f;
static const float kScreenBreakLightAttnA2 = 4.0f;
static const float kScreenBreakLightAttnK2 = -3.0f;
static const float kScreenBreakHalf = 0.5f;

static const char sF999Root[] = "f999_root";
static const char s_pppScreenBreak_cpp[] = "pppScreenBreak.cpp";

static inline MtxPtr ScreenBreakModelMtx(CChara::CModel* model) { return model->m_drawMtx; }
static inline CCharaModelData* ScreenBreakModelRef(CChara::CModel* model) { return model->m_data; }
static inline u32 ScreenBreakMeshNodeIndex(ScreenBreakMeshData* meshData) { return meshData->m_nodeIndex; }
static inline ScreenBreakDataOffsets* GetScreenBreakDataOffsets(_pppCtrlTable* ctrl) { return reinterpret_cast<ScreenBreakDataOffsets*>(ctrl->m_serializedDataOffsets); }
static inline u8* GetScreenBreakWork(pppScreenBreak* screenBreak, s32 offset) { return screenBreak->m_workArea + offset; }
static inline VScreenBreak* GetScreenBreakValue(pppScreenBreak* screenBreak, s32 offset) { return reinterpret_cast<VScreenBreak*>(GetScreenBreakWork(screenBreak, offset)); }
static inline ScreenBreakColorData* GetScreenBreakColorData(pppScreenBreak* screenBreak, s32 offset) { return reinterpret_cast<ScreenBreakColorData*>(GetScreenBreakWork(screenBreak, offset)); }

static inline int GraphicScreenBreakBlurEnabled() { return Graphic.m_blurActive; }

int SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*);
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

/*
 * --INFO--
 * PAL Address: 0x8012d458
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBreak(pppScreenBreak* screenBreak, PScreenBreak*, _pppCtrlTable* param_3)
{
    ScreenBreakDataOffsets* offsets = GetScreenBreakDataOffsets(param_3);
    VScreenBreak* value = GetScreenBreakValue(screenBreak, offsets->m_valueOffset);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    model->SearchNode(const_cast<char*>(sF999Root));

    if (value->m_backBufferReady == 0) {
        Graphic.GetBackBufferRect2(
            Graphic.m_savedFrameBuffer, value->m_backBufferTexObj, 0, 0, 0x280, 0x1C0, 0, (_GXTexFilter)1, (_GXTexFmt)4, 0);
        value->m_backBufferReady = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012d500
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameScreenBreak(pppScreenBreak* screenBreak, PScreenBreak* param_2, _pppCtrlTable* param_3)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    if (GraphicScreenBreakBlurEnabled() != 0) {
        GraphicPcs.SetBlurParameter(0, 0, 0, 0, 0, 0, 0);
    }

    ScreenBreakDataOffsets* offsets = GetScreenBreakDataOffsets(param_3);
    VScreenBreak* value = GetScreenBreakValue(screenBreak, offsets->m_valueOffset);
    ScreenBreakColorData* colorSource = GetScreenBreakColorData(screenBreak, offsets->m_colorDataOffset);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    model->SetCallbackContext(value, param_2);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    value->m_color = colorSource->m_color;
    DCFlushRange(&value->m_color, sizeof(value->m_color));

    CalcGraphValue(screenBreak, param_2->m_graphId, value->m_graphValue0, value->m_graphValue1, value->m_graphValue2,
                   param_2->m_stepValue, param_2->m_arg3, param_2->m_graphPayload);

    ScreenBreakPiece* pieceStorage = value->m_pieces;
    if (pieceStorage == 0) {
        pieceStorage = static_cast<ScreenBreakPiece*>(
            pppMemAlloc(ScreenBreakModelRef(model)->m_meshCount * sizeof(ScreenBreakPiece), ppvEnv->m_stagePtr,
                        const_cast<char*>(s_pppScreenBreak_cpp), 0x25E));
        value->m_pieces = pieceStorage;
        value->m_backBufferTexObj = static_cast<GXTexObj*>(pppMemAlloc(0x20, ppvEnv->m_stagePtr,
                                                                      const_cast<char*>(s_pppScreenBreak_cpp), 0x25F));
        InitPieceData(model, param_2, value);
        PSVECNormalize(&param_2->m_gravityDir, &param_2->m_gravityDir);
    }

    const float& two = kScreenBreakExtentScale;
    float sx = two * value->m_extent.x;
    float sy = two * value->m_extent.y;
    ScreenBreakPiece* piece = value->m_pieces;
    for (u32 i = 0; i < ScreenBreakModelRef(model)->m_meshCount; i++) {
        switch (param_2->m_initWOrk) {
        case 0:
            piece->m_active = 1;
            break;
        case 1:
            if (-piece->m_translation.y < (value->m_graphValue0 * sy) - value->m_extent.y) {
                piece->m_active = 1;
            }
            break;
        case 2:
            float pieceY = piece->m_translation.y;
            if (-pieceY > value->m_extent.y - (value->m_graphValue0 * sy)) {
                piece->m_active = 1;
            }
            break;
        case 3:
            if (-piece->m_translation.x < (value->m_graphValue0 * sx) + -value->m_extent.x) {
                piece->m_active = 1;
            }
            break;
        case 4:
            float pieceX = piece->m_translation.x;
            if (-pieceX > value->m_extent.x - (value->m_graphValue0 * sx)) {
                piece->m_active = 1;
            }
            break;
        case 5: {
            sx = value->m_extent.x;
            sy = value->m_extent.y;
            float x = value->m_graphValue0 * sx;
            float y = value->m_graphValue0 * sy;
            float pieceX = piece->m_translation.x;
            if ((x >= pieceX) && (-pieceX <= x) &&
                (y >= piece->m_translation.y) && (-piece->m_translation.y <= y)) {
                piece->m_active = 1;
            }
            break;
        }
        case 6: {
            sx = value->m_extent.x;
            float x = value->m_graphValue0 * sx;
            sy = value->m_extent.y;
            float y = value->m_graphValue0 * sy;
            if ((-piece->m_translation.x >= sx - x) || (-piece->m_translation.x <= -sx + x) ||
                (-piece->m_translation.y >= sy - y) || (-piece->m_translation.y <= -sy + y)) {
                piece->m_active = 1;
            }
            break;
        }
        default:
            break;
        }
        piece++;
    }

    pppSetFpMatrix(ppvMng);
}

/*
 * --INFO--
 * PAL Address: 0x8012d870
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenBreak(pppScreenBreak* screenBreak, _pppCtrlTable* param_2)
{
    ScreenBreakDataOffsets* offsets = GetScreenBreakDataOffsets(param_2);
    VScreenBreak* pppData = GetScreenBreakValue(screenBreak, offsets->m_valueOffset);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    if (model != 0) {
        model->m_afterMeshDrawCallback = 0;
        model->SetDrawMeshDLCallback(0);
        model->SetBeforeMeshLockEnvCallback(0);
        model->SetCallbackContext(0, 0);
        model->SetBeforeCalcMatrixCallback(0);
    }
    if (pppData->m_pieces != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(pppData->m_pieces));
        pppData->m_pieces = 0;
    }
    if (pppData->m_backBufferTexObj != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(pppData->m_backBufferTexObj));
        pppData->m_backBufferTexObj = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012d90c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenBreak(pppScreenBreak* screenBreak, _pppCtrlTable* param_2)
{
    ScreenBreakDataOffsets* offsets = GetScreenBreakDataOffsets(param_2);
    VScreenBreak* value = GetScreenBreakValue(screenBreak, offsets->m_valueOffset);
    const float& f = kScreenBreakZero;
    value->m_graphValue2 = f;
    value->m_graphValue1 = f;
    value->m_graphValue0 = f;
}

/*
 * --INFO--
 * PAL Address: 0x8012d930
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenBreak(pppScreenBreak* screenBreak, _pppCtrlTable* param_2)
{
    ScreenBreakDataOffsets* offsets = GetScreenBreakDataOffsets(param_2);
    VScreenBreak* value = GetScreenBreakValue(screenBreak, offsets->m_valueOffset);
    CGObject* gObject = ppvMng->m_owner;
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(gObject, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);
    gObject->m_displayFlags |= 0x40;
    model->m_afterMeshDrawCallback = (CChara::CModel::AfterMeshDrawCallback)SB_BeforeDrawCallback;
    const float& f = kScreenBreakZero;
    model->SetDrawMeshDLCallback(SB_DrawMeshDLCallback);
    model->SetBeforeMeshLockEnvCallback(SB_BeforeMeshLockEnvCallback);
    model->SetBeforeCalcMatrixCallback(SB_BeforeCalcMatrixCallback);
    value->m_pieces = 0;
    value->m_backBufferTexObj = 0;
    value->m_extent.z = f;
    value->m_extent.y = f;
    value->m_extent.x = f;
    value->m_graphValue2 = f;
    value->m_graphValue1 = f;
    value->m_graphValue0 = f;
    value->m_backBufferReady = 0;
    value->m_color.r = 0xFF;
    value->m_color.g = 0xFF;
    value->m_color.b = 0xFF;
    value->m_color.a = 0xFF;
}

/*
 * --INFO--
 * PAL Address: 0x8012da00
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
    GXSetZMode(GX_TRUE, (GXCompare)7, GX_TRUE);
}

/*
 * --INFO--
 * PAL Address: 0x8012da2c
 * PAL Size: 1020b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitPieceData(CChara::CModel* model, PScreenBreak* step, VScreenBreak* work)
{
    s32 iVar6;
    u32 uVar15;
    PScreenBreak* stepData = step;
    ScreenBreakPiece* piece;
    s32 iVar16;
    float dVar17;
    float dVar19;
    float dVar18;
    float dVar20;
    float dVar21;
    float dVar22;
    float dVar24;
    float dVar25;
    S16Vec globalMax;
    u32 uStack_b4;

    memset(work->m_pieces, 0, ScreenBreakModelRef(model)->m_meshCount * sizeof(ScreenBreakPiece));
    dVar19 = kScreenBreakTranslationRandLimit;
    CChara::CMesh* mesh = model->m_meshes;
    dVar18 = -dVar19;
    piece = work->m_pieces;
    dVar20 = kScreenBreakOne;
    globalMax.x = -0x7FFF;
    globalMax.y = -0x7FFF;
    dVar21 = kScreenBreakNegativeOne;
    globalMax.z = -0x7FFF;
    dVar22 = kScreenBreakZero;
    dVar24 = kScreenBreakExtentScale;
    dVar25 = kScreenBreakDegToRad;

    for (uVar15 = 0; uVar15 < ScreenBreakModelRef(model)->m_meshCount;) {
        ScreenBreakMeshData* meshData = mesh->m_data;
        CChara::CNode* node = &model->m_nodes[ScreenBreakMeshNodeIndex(meshData)];
        node->m_flags &= 0x7F;
        PSMTXIdentity(node->m_localRuntimeMtx);

        u32 vertexCount = meshData->m_vertexCount;
        iVar6 = 0;
        S16Vec meshMax;
        meshMax.x = -0x7FFF;
        meshMax.y = -0x7FFF;
        meshMax.z = -0x7FFF;
        S16Vec meshMin;
        meshMin.x = 0x7FFF;
        meshMin.y = 0x7FFF;
        meshMin.z = 0x7FFF;

        for (u32 j = 0; j < vertexCount; j++) {
            s16 x = *(s16*)((u8*)meshData->m_vertices + iVar6);
            s16 globalX = globalMax.x;
            if (globalX < x) {
                globalX = x;
            }
            globalMax.x = globalX;

            s16 y = *(s16*)((u8*)meshData->m_vertices + iVar6 + 2);
            s16 globalY = globalMax.y;
            if (globalY < y) {
                globalY = y;
            }
            globalMax.y = globalY;

            s16 z = *(s16*)((u8*)meshData->m_vertices + iVar6 + 4);
            s16 globalZ = globalMax.z;
            if (globalZ < z) {
                globalZ = z;
            }
            globalMax.z = globalZ;

            s16* vertex = (s16*)((u8*)meshData->m_vertices + iVar6);

            s16 minCandidateX = vertex[0];
            if (meshMin.x < vertex[0]) {
                minCandidateX = meshMin.x;
            }
            meshMin.x = minCandidateX;

            s16 minCandidateY = vertex[1];
            if (meshMin.y < vertex[1]) {
                minCandidateY = meshMin.y;
            }
            meshMin.y = minCandidateY;

            s16 minCandidateZ = vertex[2];
            if (meshMin.z < vertex[2]) {
                minCandidateZ = meshMin.z;
            }
            meshMin.z = minCandidateZ;

            s16 maxCandidateX = meshMax.x;
            if (maxCandidateX < vertex[0]) {
                maxCandidateX = vertex[0];
            }
            meshMax.x = maxCandidateX;

            s16* vertexY = (s16*)((u8*)meshData->m_vertices + iVar6);
            s16 maxCandidateY = meshMax.y;
            if (maxCandidateY < vertexY[1]) {
                maxCandidateY = vertexY[1];
            }
            meshMax.y = maxCandidateY;

            s16* vertexZ = (s16*)((u8*)meshData->m_vertices + iVar6);
            s16 maxCandidateZ = meshMax.z;
            if (maxCandidateZ < vertexZ[2]) {
                maxCandidateZ = vertexZ[2];
            }
            meshMax.z = maxCandidateZ;

            iVar6 += 6;
        }

        meshMax.x += meshMin.x;
        meshMax.y += meshMin.y;
        meshMax.z += meshMin.z;
        gUtil.ConvI2FVector(piece->m_translation, meshMax, ScreenBreakModelRef(model)->m_posQuant);
        PSVECScale(&piece->m_translation, &piece->m_translation, kScreenBreakMeshCenterScale);

        dVar17 = piece->m_translation.x;
        if (piece->m_translation.x > dVar19) {
            dVar17 = Math.RandF(dVar19);
        }
        if (piece->m_translation.x < dVar18) {
            dVar17 = -Math.RandF(dVar19);
        }

        piece->m_velocity.x = dVar17;
        piece->m_velocity.y = dVar20;
        piece->m_velocity.z = dVar21;
        PSVECNormalize(&piece->m_velocity, &piece->m_velocity);
        Vec up = {0.0f, 1.0f, 0.0f};
        PSVECCrossProduct(&piece->m_velocity, &up, &piece->m_axis);

        dVar17 = Math.RandF(stepData->m_speedRand);
        PSVECScale(&piece->m_velocity, &piece->m_velocity, stepData->m_speedBase + dVar17);

        piece->m_offset.z = dVar22;
        piece->m_offset.y = dVar22;
        piece->m_offset.x = dVar22;
        piece->m_timer = dVar22;

        uStack_b4 = static_cast<u32>(stepData->m_angleRand);
        dVar17 = Math.RandF((float)uStack_b4);
        mesh++;
        uVar15++;
        piece->m_angle = dVar25 * (dVar24 + dVar17);
        piece->m_active = 0;
        piece++;
    }

    gUtil.ConvI2FVector(work->m_extent, globalMax, ScreenBreakModelRef(model)->m_posQuant);
}

/*
 * --INFO--
 * PAL Address: 0x8012de28
 * PAL Size: 776b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void*, int meshIndex, int drawListIndex, float (*) [4])
{
    VScreenBreak* work = static_cast<VScreenBreak*>(param_2);
    ScreenBreakMeshRef* mesh = model->m_meshes;
    mesh += meshIndex;
    ScreenBreakMeshData* meshData = mesh->m_data;
    ScreenBreakDisplayList* displayList = meshData->m_displayLists;

    displayList += drawListIndex;

    if (work->m_backBufferReady != 0) {
        CMaterial* material = model->m_data->m_materialSet->m_materials[displayList->m_material];

        MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 1, (_GXTevScale)0);
        GXSetArray((GXAttr)0xB, &work->m_color, 4);

        if (material->GetTextureCount() == 1) {
            GXSetNumChans(1);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevKColor((GXTevKColorID)0, CColor(0xA0, 0xA0, 0xA0, 0xA0).color);
            GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xC);
            GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1C);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_KONST, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_COMP_BGR24_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevKColor((GXTevKColorID)1, CColor(0x60, 0x60, 0x60, work->m_color.a).color);
            GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xD);
            GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1D);
            _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1D);
            _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ONE, GX_CC_TEXC, GX_CC_CPREV);
            _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            GXSetNumTevStages(3);
            GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
            GXLoadTexObj(work->m_backBufferTexObj, (GXTexMapID)0);
        }

        GXCallDisplayList(displayList->m_data, displayList->m_size);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012e130
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*) [4], int)
{
    Vec lightDir;
    GXLightObj lightObj;
    CCameraPcs* camera = &CameraPcs;
    const float& zero = kScreenBreakZero;

    lightDir.x = camera->m_directionX - (30.0f + camera->m_positionX);
    lightDir.y = camera->m_directionY - (30.0f + camera->m_positionY);
    lightDir.z = camera->m_directionZ - (30.0f + camera->m_positionZ);
    PSVECNormalize(&lightDir, &lightDir);

    GXInitSpecularDirHA(&lightObj, lightDir.x, lightDir.y, lightDir.z, zero, 1.0f, zero);
    GXInitLightAttn(&lightObj, zero, zero, 1.0f, 4.0f, zero, -3.0f);

    GXInitLightColor(&lightObj, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    GXLoadLightObjImm(&lightObj, (GXLightID)1);
    GXSetChanCtrl((GXChannelID)0, 1, (GXColorSrc)0, (GXColorSrc)1, 1, (GXDiffuseFn)2, (GXAttnFn)0);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
}

/*
 * --INFO--
 * PAL Address: 0x8012e258
 * PAL Size: 900b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int SB_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void* param_3)
{
    float zero = kScreenBreakZero;
    VScreenBreak* work = static_cast<VScreenBreak*>(param_2);
    PScreenBreak* step = static_cast<PScreenBreak*>(param_3);
    ScreenBreakPiece* pieceData = work->m_pieces;
    Vec translation;
    Vec cameraForward;
    Vec cameraPos;
    Vec4d clipInput;
    Vec4d clipOutput;
    Vec screenOffset;
    Vec cameraOffset;
    Vec basis = {0.0f, 1.0f, 0.0f};
    Vec gravityAdd;
    Vec axis;
    Quaternion meshQuat;
    Quaternion axisQuat;
    Quaternion resultQuat;
    Vec invTransOffset;
    Mtx cameraMtx;
    Mtx invCameraMtx;
    Mtx44 screenMtx;
    Mtx meshMtx;
    Mtx quatMtx;
    Mtx transMtx;
    Mtx invTransMtx;
    ScreenBreakMeshRef* mesh;

    cameraForward.x = CameraPcs.m_directionX;
    cameraForward.y = CameraPcs.m_directionY;
    cameraForward.z = CameraPcs.m_directionZ;
    cameraPos.x = CameraPcs.m_positionX;
    cameraPos.y = CameraPcs.m_positionY;
    cameraPos.z = CameraPcs.m_positionZ;

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);

    PSVECCrossProduct(&cameraForward, &basis, &cameraOffset);
    PSVECNormalize(&cameraOffset, &cameraOffset);

    screenOffset.x = work->m_extent.x * cameraOffset.x + cameraPos.x;
    screenOffset.y = cameraPos.y;
    screenOffset.z = work->m_extent.x * cameraOffset.z + cameraPos.z;

    PSMTXMultVec(cameraMtx, &screenOffset, (Vec*)&clipInput);
    clipInput.w = 1.0f;
    Math.MTX44MultVec4(screenMtx, &clipInput, &clipOutput);

    translation.x = clipOutput.x * cameraForward.x;
    translation.y = clipOutput.x * cameraForward.y;
    translation.z = clipOutput.x * cameraForward.z;
    PSVECAdd(&cameraPos, &translation, &translation);

    PSMTXInverse(cameraMtx, invCameraMtx);
    PSMTXConcat(invCameraMtx, ScreenBreakModelMtx(model), ScreenBreakModelMtx(model));
    model->m_drawMtx[0][3] = translation.x;
    model->m_drawMtx[1][3] = translation.y;
    model->m_drawMtx[2][3] = translation.z;

    mesh = model->m_meshes;
    if (step->m_gravityAmount != zero) {
        PSVECScale(&step->m_gravityDir, &gravityAdd, step->m_gravityAmount);
    }

    for (u32 i = 0; i < ScreenBreakModelRef(model)->m_meshCount; i++) {
        ScreenBreakMeshData* meshData = mesh->m_data;
        if (pieceData->m_active != 0) {
            MtxPtr nodeMtx = model->m_nodes[ScreenBreakMeshNodeIndex(meshData)].m_localRuntimeMtx;

            nodeMtx[0][3] = zero;
            nodeMtx[1][3] = zero;
            nodeMtx[2][3] = zero;

            PSMTXCopy(nodeMtx, meshMtx);
            PSMTXIdentity(transMtx);
            transMtx[0][3] = pieceData->m_translation.x;
            transMtx[1][3] = pieceData->m_translation.y;
            transMtx[2][3] = pieceData->m_translation.z;
            PSMTXInverse(transMtx, invTransMtx);

            axis.x = pieceData->m_axis.x;
            axis.y = pieceData->m_axis.y;
            axis.z = pieceData->m_axis.z;
            C_QUATRotAxisRad(&axisQuat, &axis, pieceData->m_angle);
            PSMTXQuat(quatMtx, &axisQuat);
            C_QUATMtx(&meshQuat, meshMtx);
            PSQUATMultiply(&axisQuat, &meshQuat, &resultQuat);
            PSMTXQuat(quatMtx, &resultQuat);
            PSMTXConcat(quatMtx, transMtx, nodeMtx);

            pieceData->m_offset.x -= pieceData->m_velocity.x;
            float gravityTerm = 0.5f * step->m_gravityScale * pieceData->m_timer;
            pieceData->m_offset.y = pieceData->m_velocity.y * pieceData->m_timer - gravityTerm * pieceData->m_timer;
            pieceData->m_offset.z -= pieceData->m_velocity.z;

            if (step->m_gravityAmount != zero) {
                pieceData->m_offset.x += gravityAdd.x;
                pieceData->m_offset.z += gravityAdd.z;
            }

            pieceData->m_timer += 1.0f;

            invTransOffset.x = invTransMtx[0][3];
            invTransOffset.y = invTransMtx[1][3];
            invTransOffset.z = invTransMtx[2][3];
            PSVECAdd(&pieceData->m_offset, &invTransOffset, &invTransOffset);
            invTransMtx[0][3] = invTransOffset.x;
            invTransMtx[1][3] = invTransOffset.y;
            invTransMtx[2][3] = invTransOffset.z;
            PSMTXConcat(invTransMtx, nodeMtx, nodeMtx);
        }

        mesh++;
        pieceData++;
    }

    return 1;
}
