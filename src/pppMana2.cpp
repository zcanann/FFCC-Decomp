#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/gobject.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "ffcc/vector.h"

#include <string.h>
#include <math.h>
#include <dolphin/os/OSCache.h>
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(offsetof(VMana2, m_runtimeColor) == 0x38);
STATIC_ASSERT(offsetof(VMana2, m_positions) == 0x3C);
STATIC_ASSERT(offsetof(VMana2, m_indices) == 0x50);
STATIC_ASSERT(offsetof(VMana2, m_displayListCopies) == 0x60);
STATIC_ASSERT(offsetof(VMana2, m_step) == 0x70);
STATIC_ASSERT(offsetof(VMana2, m_waterMtx) == 0x80);
STATIC_ASSERT(offsetof(VMana2, m_reflectionMtx) == 0xB0);
STATIC_ASSERT(offsetof(VMana2, m_waterAlpha) == 0xE0);
STATIC_ASSERT(offsetof(VMana2, m_paraboloidReady) == 0xEC);
STATIC_ASSERT(offsetof(pppMana2Step, m_sourceTextureIds) == 0x04);
STATIC_ASSERT(offsetof(pppMana2Step, m_type) == 0x1C);
STATIC_ASSERT(offsetof(pppMana2Step, m_envTextureId0) == 0x24);
STATIC_ASSERT(offsetof(pppMana2Step, m_envTextureId1) == 0x28);
STATIC_ASSERT(offsetof(pppMana2Step, m_waterScale) == 0x30);
STATIC_ASSERT(offsetof(pppMana2Step, m_rippleLevel) == 0x38);

// The mana water surface is a 17 x 17 vertex grid: 289 vertices, 16 x 16 quads = 512 triangles.
enum {
    kWaterGridStride = 0x11,
    kWaterGridQuads = 0x10,
    kWaterVertexCount = 0x121,
    kWaterTriangleCount = 0x200,
};

static const char sRenderMana2Message[] = "Render Mana2!!";
static const char s_pppMana2_cpp[] = "pppMana2.cpp";

struct Mana2SetupBlock
{
    u8 m_pad0[8];
    pppCVECTOR m_color;
};

STATIC_ASSERT(sizeof(Mana2DataOffsets) == 0xC);
STATIC_ASSERT(offsetof(Mana2DataOffsets, m_setupOffset) == 0x4);
STATIC_ASSERT(offsetof(Mana2DataOffsets, m_workOffset) == 0x8);

static void Mana2_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
static void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);

static inline float CameraWorldX()
{
    return CameraPcs.m_positionX;
}

static inline float CameraWorldY()
{
    return CameraPcs.m_positionY;
}

static inline float CameraWorldZ()
{
    return CameraPcs.m_positionZ;
}

static inline Mtx& CameraMatrix()
{
    return CameraPcs.m_cameraMatrix;
}

static inline Mtx44& CameraScreenMatrix()
{
    return CameraPcs.m_screenMatrix;
}

static inline Mana2DataOffsets* GetMana2DataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<Mana2DataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline VMana2* GetMana2Work(pppMana2* mana, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VMana2*>(
        reinterpret_cast<_pppPObject*>(mana)->m_workArea + GetMana2DataOffsets(ctrl)->m_workOffset);
}

static inline Mana2SetupBlock* GetMana2SetupBlock(pppMana2* mana, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<Mana2SetupBlock*>(
        reinterpret_cast<_pppPObject*>(mana)->m_workArea + GetMana2DataOffsets(ctrl)->m_setupOffset);
}

static inline void ClearMana2ModelCallbacks(CChara::CModel* model)
{
    model->SetCallbackContext(0, 0);
    model->m_beforeDrawModelCallback = 0;
    model->SetDrawMeshDLCallback(0);
}

static inline void SetMana2ModelCallbacks(CChara::CModel* model, void* work, pppMana2Step* step)
{
    model->SetCallbackContext(work, step);
    model->m_beforeDrawModelCallback = Mana2_BeforeDrawCallback;
    model->SetDrawMeshDLCallback(Mana2_DrawMeshDLCallback);
}

static int CreateWaterMesh(Vec* positions, Vec* normals, Vec2d* texCoords, unsigned short* indices, float waterScale);
static int UpdateWaterMesh(VMana2* mana2);
static int RenderWaterMesh(VMana2* mana2);
static void CalculateNormal(VMana2* mana2);
static void CalcWaterReflectionVector(
    Vec* reflectionVec, Vec* positions, Vec* normals, long count, Vec waterOrigin, float (*matrix)[4], _GXColor* color,
    Vec2d* texCoord);

/*
 * --INFO--
 * PAL Address: 0x8010617c
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void CalcWaterReflectionVector(
    Vec* reflectionVec,
    Vec* positions,
    Vec* normals,
    long count,
    Vec waterOrigin,
    float (*matrix)[4],
    _GXColor* color,
    Vec2d* texCoord)
{
    Vec cameraPos;
    Vec transformedCameraPos;
    Vec objPos;
    Vec reflected;
    Mtx matrixNoTranslate;
    Mtx inverseMtx;
    Vec* positionIt;
    Vec* reflectionIt;
    Vec* normalIt;
    _GXColor* colorIt;
    Vec2d* texCoordIt;
    float zero;
    float half;
    long i;

    (void)waterOrigin;

    if ((int)Game.m_currentSceneId == 7) {
        cameraPos.x = ppvCameraMatrix[0][3];
        cameraPos.y = ppvCameraMatrix[1][3];
        cameraPos.z = ppvCameraMatrix[2][3];
    } else {
        cameraPos.x = CameraWorldX();
        cameraPos.y = CameraWorldY();
        cameraPos.z = CameraWorldZ();
    }

    transformedCameraPos.x = 0.0f;
    transformedCameraPos.y = 0.0f;
    transformedCameraPos.z = 0.0f;

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, -1.0f);
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    zero = 0.0f;
    positionIt = positions;
    half = 0.5f;
    reflectionIt = reflectionVec;
    normalIt = normals;
    colorIt = color;
    texCoordIt = texCoord;

    i = 0;
    while (i < count) {
        PSVECSubtract(positionIt, &transformedCameraPos, &reflected);
        C_VECReflect(&reflected, normalIt, reflectionIt);
        PSMTXMultVec(matrixNoTranslate, reflectionIt, reflectionIt);
        PSVECNormalize(reflectionIt, reflectionIt);

        if (reflectionIt->z >= zero) {
            float denomBase;

            colorIt->r = 0x80;
            colorIt->g = 0x80;
            colorIt->b = 0xff;
            colorIt->a = 0xbc;
            denomBase = 1.0f;
            texCoordIt->x = -reflectionIt->x / (denomBase + reflectionIt->z);
            texCoordIt->y = -reflectionIt->y / (denomBase + reflectionIt->z);
        } else {
            float denomBase;

            colorIt->r = 0x80;
            colorIt->g = 0xff;
            colorIt->b = 0x80;
            colorIt->a = 0x7f;
            denomBase = 1.0f;
            texCoordIt->x = -reflectionIt->x / (denomBase - reflectionIt->z);
            texCoordIt->y = -reflectionIt->y / (denomBase - reflectionIt->z);
        }

        positionIt++;
        reflectionIt++;
        normalIt++;
        colorIt++;
        i++;
        texCoordIt->x = texCoordIt->x * half;
        texCoordIt->x = texCoordIt->x + half;
        texCoordIt->y = texCoordIt->y * half;
        texCoordIt->y = texCoordIt->y + half;
        texCoordIt++;
    }

    DCFlushRange(reflectionVec, count * sizeof(Vec));
    DCFlushRange(texCoord, count * sizeof(Vec2d));
}
/*
 * --INFO--
 * PAL Address: 0x80106438
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void CalculateNormal(VMana2* mana2)
{
    Vec* positions;
    Vec* normals;
    u16* indices;
    Vec edgeA;
    Vec edgeB;
    Vec faceNormal;
    s32 i;

    positions = mana2->m_positions;
    normals = mana2->m_normals;
    indices = mana2->m_indices;

    float zero = 0.0f;
    for (i = 0; i < kWaterVertexCount; i++) {
        normals[i].z = zero;
        normals[i].y = zero;
        normals[i].x = zero;
    }

    i = 0;
    s32 indicesOffset = i;
    for (; i < kWaterTriangleCount; i++) {
        u16 i0 = indices[indicesOffset++];
        u16 i1 = indices[indicesOffset++];
        u16 i2 = indices[indicesOffset++];

        edgeA.x = positions[i1].x - positions[i0].x;
        edgeA.y = positions[i1].y - positions[i0].y;
        edgeA.z = positions[i1].z - positions[i0].z;

        edgeB.x = positions[i2].x - positions[i0].x;
        edgeB.y = positions[i2].y - positions[i0].y;
        edgeB.z = positions[i2].z - positions[i0].z;

        PSVECCrossProduct(&edgeA, &edgeB, &faceNormal);
        PSVECNormalize(&faceNormal, &faceNormal);

        PSVECAdd(&normals[i0], &faceNormal, &normals[i0]);
        PSVECAdd(&normals[i1], &faceNormal, &normals[i1]);
        PSVECAdd(&normals[i2], &faceNormal, &normals[i2]);
    }

    for (i = 0; i < kWaterVertexCount; i++) {
        PSVECNormalize(&normals[i], &normals[i]);
    }

    DCFlushRange(normals, kWaterVertexCount * sizeof(Vec));
}

/*
 * --INFO--
 * PAL Address: 0x80106694
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int RenderWaterMesh(VMana2* mana2)
{
    Vec* positions = mana2->m_positions;
    Vec* normals = mana2->m_normals;
    Vec2d* texCoord0 = mana2->m_texCoord0;
    Vec2d* texCoord1 = mana2->m_texCoord1;
    u16* indices = mana2->m_indices;
    GXColor* colors = mana2->m_colors;
    GXTexObj* generatedTexObj0 = mana2->m_generatedTexObj0;
    CTexture* envTexture1;
    _GXColor blendColor;
    _GXColor modulateColor;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxDesc(GX_VA_TEX1, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GXSetNumTexGens(2);
    GXSetCullMode(GX_CULL_NONE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetNumChans(1);
    blendColor.r = 0xFF;
    blendColor.g = 0xFF;
    blendColor.b = 0xFF;
    blendColor.a = 0xFF;
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetArray(GX_VA_POS, positions, sizeof(Vec));
    GXSetArray(GX_VA_NRM, normals, sizeof(Vec));
    GXSetArray(GX_VA_CLR0, colors, sizeof(GXColor));
    GXSetArray(GX_VA_TEX0, texCoord0, sizeof(Vec2d));
    GXSetArray(GX_VA_TEX1, texCoord1, sizeof(Vec2d));
    envTexture1 = mana2->m_envTexture1;
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    u8 alpha = mana2->m_waterAlpha;
    blendColor.r = 0x80;
    blendColor.g = 0x80;
    blendColor.b = 0x80;
    blendColor.a = 0x80;
    modulateColor.r = alpha;
    modulateColor.g = alpha;
    modulateColor.b = alpha;
    modulateColor.a = alpha;

    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXLoadTexObj(&envTexture1->m_texObj, GX_TEXMAP0);
    GXSetTevKColor(GX_KCOLOR1, modulateColor);
    GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K1);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_K1_A);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetTevDirect(GX_TEVSTAGE1);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXLoadTexObj(mana2->m_generatedTexObj0, GX_TEXMAP1);
    GXSetTevKColor(GX_KCOLOR0, blendColor);
    GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);
    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_RASA, GX_CC_KONST, GX_CC_TEXC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);

    GXSetTevDirect(GX_TEVSTAGE2);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR0A0);
    GXLoadTexObj(mana2->m_generatedTexObj1, GX_TEXMAP2);
    GXSetTevKColor(GX_KCOLOR0, blendColor);
    GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K0);
    GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_K0_A);
    _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_KONST, GX_CC_RASA, GX_CC_TEXC, GX_CC_CPREV);
    _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetNumTevStages(3);
    GXBegin(GX_TRIANGLES, GX_VTXFMT7, 0x600);
    u16* indexIt = indices;
    for (int i = 0; i < 0x180; i++) {
        GXPosition1x16(indexIt[0]);
        GXNormal1x16(indexIt[0]);
        GXColor1x16(indexIt[0]);
        GXTexCoord1x16(indexIt[0]);
        GXTexCoord1x16(indexIt[0]);
        GXPosition1x16(indexIt[1]);
        GXNormal1x16(indexIt[1]);
        GXColor1x16(indexIt[1]);
        GXTexCoord1x16(indexIt[1]);
        GXTexCoord1x16(indexIt[1]);
        GXPosition1x16(indexIt[2]);
        GXNormal1x16(indexIt[2]);
        GXColor1x16(indexIt[2]);
        GXTexCoord1x16(indexIt[2]);
        GXTexCoord1x16(indexIt[2]);
        GXPosition1x16(indexIt[3]);
        GXNormal1x16(indexIt[3]);
        GXColor1x16(indexIt[3]);
        GXTexCoord1x16(indexIt[3]);
        GXTexCoord1x16(indexIt[3]);
        indexIt += 4;
    }

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetNumTevStages(1);
    GXLoadTexObj(generatedTexObj0, GX_TEXMAP0);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80106c54
 * PAL Size: 968b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int UpdateWaterMesh(VMana2* mana2)
{
    float neighborScale;
    float currentScale;
    Vec origin;
    Vec* positions;
    float* waterHeightB;
    float* waterHeightA;

    waterHeightA = mana2->m_waterHeightA;
    positions = mana2->m_positions;
    waterHeightB = mana2->m_waterHeightB;
    if (waterHeightA == NULL) {
        return 0;
    }

    for (int row = 1; row < kWaterGridQuads; row++) {
        currentScale = 0.0f;
        neighborScale = 0.5f;
        for (int col = 1; col < kWaterGridQuads; col++) {
            int index = row * kWaterGridStride + col;
            float* center = &waterHeightA[index];
            waterHeightB[index] = currentScale * center[0] +
                                  neighborScale * (waterHeightA[index - kWaterGridStride] + waterHeightA[index + kWaterGridStride] +
                                                   center[-1] + center[1]) -
                                  waterHeightB[index];
        }
    }

    for (int i = 0; i < kWaterVertexCount; i++) {
        float tmp = waterHeightA[i];
        waterHeightA[i] = waterHeightB[i];
        waterHeightB[i] = tmp;
        positions[i].y = waterHeightA[i];
    }

    DCFlushRange(positions, kWaterVertexCount * sizeof(Vec));
    CalculateNormal(mana2);

    origin.x = mana2->m_waterMtx[0][3];
    origin.y = mana2->m_waterMtx[1][3];
    origin.z = mana2->m_waterMtx[2][3];
    CalcWaterReflectionVector(mana2->m_reflectionVec, mana2->m_positions, mana2->m_normals, kWaterVertexCount, origin,
                              mana2->m_waterMtx, mana2->m_colors, mana2->m_texCoord1);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8010701c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int CreateWaterMesh(Vec* positions, Vec* normals, Vec2d* texCoords, unsigned short* indices, float waterScale)
{
    float zero;
    float normalY;
    float x;
    float z;
    float step;
    float radius;
    float uvStep;
    int indexOffset;
    int quadIndex;
    int rowBase;
    int rowCount;
    int colCount;

    normalY = 1.0f;
    zero = 0.0f;
    rowCount = 0;
    uvStep = 0.0625f;
    radius = waterScale * 0.5f;
    step = waterScale * uvStep;
    for (z = radius; z >= -radius; z -= step) {
        colCount = 0;
        for (x = -radius; x <= radius; x += step) {
            positions->x = x;
            positions->y = zero;
            positions->z = z;
            positions++;
            normals->x = zero;
            normals->y = normalY;
            normals->z = zero;
            normals++;
            texCoords->x = static_cast<float>(colCount) * uvStep;
            texCoords->y = static_cast<float>(rowCount) * uvStep;
            texCoords++;
            colCount = colCount + 1;
        }
        rowCount = rowCount + 1;
    }
    indexOffset = 0;
    rowCount = 0;
    rowBase = 0;
    do {
        quadIndex = rowBase;
        for (int col = 0; col < kWaterGridQuads; col++, quadIndex++) {
            indices[indexOffset++] = quadIndex;
            indices[indexOffset++] = quadIndex + 1;
            indices[indexOffset++] = quadIndex + kWaterGridStride + 1;
            indices[indexOffset++] = quadIndex + kWaterGridStride + 1;
            indices[indexOffset++] = quadIndex + kWaterGridStride;
            indices[indexOffset++] = quadIndex;
        }
        rowCount = rowCount + 1;
        rowBase = rowBase + kWaterGridStride;
    } while (rowCount < kWaterGridQuads);
    return 1;
}

#ifndef VERSION_GCCP01
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeWave(Vec*, unsigned short*, float*, Vec, float, float)
{
	// TODO
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801071b0
 * PAL Size: 1428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void CalcReflectionVector2(
    Vec* reflectionVec,
    S16Vec* positions,
    S16Vec* normals,
    long count,
    unsigned long posScale,
    unsigned long normalScale,
    float (*matrix)[4],
    void* displayList,
    unsigned long displayListSize,
    _GXColor* color,
    S16Vec2d* texCoord,
    CChara::CNode* node)
{
    Vec cameraPos;
    Vec nodeOffset;
    Vec matrixPos;
    Vec worldPos;
    Vec cameraVector;
    Vec objSpacePos;
    Vec objSpaceNormal;
    Vec2d uv;
    Mtx cameraModelMtx;
    Mtx cameraMtx;
    Mtx nodeRotMtx;
    Mtx nodeMtx;
    float (*nodeMatrix)[4];
    u16* dl = (u16*)displayList;
    u16* dlEnd;

    cameraPos.x = CameraWorldX();
    cameraPos.y = CameraWorldY();
    cameraPos.z = CameraWorldZ();

    PSMTXCopy(matrix, nodeMtx);
    nodeMatrix = node->m_mtx;
    nodeOffset.x = nodeMatrix[0][3];
    nodeOffset.y = nodeMatrix[1][3];
    nodeOffset.z = nodeMatrix[2][3];

    matrixPos.x = nodeMtx[0][3];
    matrixPos.y = nodeMtx[1][3];
    matrixPos.z = nodeMtx[2][3];
    PSVECAdd(&nodeOffset, &matrixPos, &worldPos);

    PSMTXCopy(nodeMatrix, matrix);
    matrix[0][3] = worldPos.x;
    matrix[1][3] = worldPos.y;
    matrix[2][3] = worldPos.z;

    PSMTXCopy(matrix, nodeRotMtx);
    nodeRotMtx[0][3] = 0.0f;
    nodeRotMtx[1][3] = 0.0f;
    nodeRotMtx[2][3] = 0.0f;

    PSMTXCopy(CameraMatrix(), cameraMtx);
    PSMTXConcat(cameraMtx, matrix, cameraModelMtx);

    const float half = 0.5f;

    dlEnd = (u16*)((u8*)displayList + displayListSize);
    while (dl < dlEnd) {
        u8 drawFmt = *(u8*)dl;
        u16 itemCount = *(u16*)((u8*)dl + 1);
        int i;
        u32 fmt = drawFmt & 7;

        dl = (u16*)((u8*)dl + 3);
        if (gUtil.IsHasDrawFmtDL(drawFmt) == 0) {
            break;
        }
        for (i = 0; i < itemCount; i++) {
            Vec* vtxReflection;
            u16 posIndex = dl[0];
            u16 normalIndex = dl[1];
            int axis = 0;
            float maxAxis;
            float invAxis;
            _GXColor* vtxColor;

            dl += 4;
            if (fmt == 2) {
                dl++;
            }

            gUtil.ConvI2FVector(objSpacePos, positions[posIndex], posScale);
            gUtil.ConvI2FVector(objSpaceNormal, normals[normalIndex], normalScale);
            PSMTXMultVec(matrix, &objSpacePos, &objSpacePos);
            PSMTXMultVec(nodeRotMtx, &objSpaceNormal, &objSpaceNormal);

            PSVECSubtract(&objSpacePos, &cameraPos, &cameraVector);
            PSVECNormalize(&cameraVector, &cameraVector);
            vtxReflection = &reflectionVec[posIndex];
            C_VECReflect(&cameraVector, &objSpaceNormal, vtxReflection);

            float absAxis[3];
            float* absAxisPtr = absAxis;
            absAxisPtr[1] = fabsf(vtxReflection->y);
            absAxisPtr[0] = fabsf(vtxReflection->x);
            absAxisPtr[2] = fabsf(vtxReflection->z);

            axis = 0;
            if (absAxisPtr[1] > absAxisPtr[0]) {
                axis = 1;
                maxAxis = absAxisPtr[1];
            } else {
                maxAxis = absAxisPtr[0];
            }
            if (absAxisPtr[2] > maxAxis) {
                axis = 2;
            }
            CVector reflected(vtxReflection->x, vtxReflection->y, vtxReflection->z);

            vtxColor = &color[posIndex];
            vtxColor->r = 0x80;
            vtxColor->g = 0x80;
            vtxColor->b = 0x80;

            uv.y = half;
            uv.x = half;
            vtxColor->a = 0xFF;

            switch (axis) {
            case 0:
                {
                    float two = 2.0f;
                    invAxis = two * reflected.x;
                }
                if (vtxReflection->x >= 0.0f) {
                    vtxColor->r = (u8)(vtxColor->r + 0x7F);
                    uv.x = half - reflected.z / invAxis;
                    uv.y = half - reflected.y / invAxis;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x + 0.25f;
                    uv.y = uv.y + 0.25f;
                } else {
                    vtxColor->r = (u8)(vtxColor->r - 0x7F);
                    uv.x = half - reflected.z / invAxis;
                    uv.y = half + reflected.y / invAxis;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x + 0.75f;
                    uv.y = uv.y + 0.25f;
                }
                break;
            case 1:
                {
                    float two = 2.0f;
                    invAxis = two * reflected.y;
                }
                if (vtxReflection->y >= 0.0f) {
                    vtxColor->g = (u8)(vtxColor->g + 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half + reflected.z / invAxis;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x + half;
                } else {
                    vtxColor->g = (u8)(vtxColor->g - 0x7F);
                    uv.x = half - reflected.x / invAxis;
                    uv.y = half + reflected.z / invAxis;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x + 0.25f;
                    uv.y = uv.y + half;
                }
                break;
            case 2:
                {
                    float two = 2.0f;
                    invAxis = two * reflected.z;
                }
                if (vtxReflection->z >= 0.0f) {
                    vtxColor->b = (u8)(vtxColor->b + 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half - reflected.y / invAxis;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y + 0.25f;
                } else {
                    vtxColor->b = (u8)(vtxColor->b - 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half + reflected.y / invAxis;
                    uv.x = uv.x * 0.25f;
                    uv.y = uv.y * 0.25f;
                    uv.x = uv.x + half;
                    uv.y = uv.y + 0.25f;
                }
                break;
            }

            gUtil.ConvF2IVector2d(texCoord[normalIndex], uv, 12);
        }
    }

    DCFlushRange(reflectionVec, count * sizeof(Vec));
    DCFlushRange(texCoord, count << 3);
}

/*
 * --INFO--
 * PAL Address: 0x80107744
 * PAL Size: 1796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void Mana2_BeforeDrawCallback(CChara::CModel*, void* work, void* step, float (*) [4], int)
{
    VMana2* mana2;
    CChara::CModel* model;
    CCharaPcs::CHandle* handle;
    Mtx44 savedScreenMtx;
    Mtx savedCameraMtx;
    Mtx identityMtx;
    Mtx lookAtMtx;
    Mtx44 projectionMtx;
    _GXTexObj sceneTexObj;
    _GXTexObj depthTexObj;
    Vec centerPos;
    Vec cameraPos;
    Vec cameraUp;
    Vec quadMin;
    Vec quadMax;
    GXColor quadColor;
    u32 depthTexSize;
    GXTexObj* baseParaboloidTexObjs;
    CGObject* gObject;
    GXTexObj* sourceTexObjs;
    CTexture* envTexture0;
    s32 i;

    mana2 = static_cast<VMana2*>(work);
    pppMana2Step* stepData = static_cast<pppMana2Step*>(step);
    baseParaboloidTexObjs = mana2->m_baseParaboloidTexObjs;
    if (stepData->m_type == 0) {
        return;
    }

    PSMTXIdentity(identityMtx);
    PSMTXCopy(CameraMatrix(), savedCameraMtx);
    PSMTX44Copy(CameraScreenMatrix(), savedScreenMtx);
    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &sceneTexObj, 0, 0, 0x80, 0x80, 0, GX_LINEAR, GX_TF_RGBA8, 0);

    gObject = mana2->m_object;
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(reinterpret_cast<CCharaPcs::CHandle*>(handle));
    model->m_beforeDrawModelCallback = 0;
    model->SetDrawMeshDLCallback(0);

    if ((int)Game.m_currentSceneId == 7) {
        centerPos.z = 0.0f;
        centerPos.y = 0.0f;
        centerPos.x = 0.0f;
    } else {
        centerPos.x = gObject->m_worldPosition.x;
        centerPos.y = gObject->m_worldPosition.y;
        centerPos.z = gObject->m_worldPosition.z;
    }
    centerPos.y = 5.0f + centerPos.y;
    centerPos.x = centerPos.x;
    centerPos.z = centerPos.z;

    depthTexSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
    GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB565, GX_FALSE, 0);
    sourceTexObjs = mana2->m_sourceTexObjs;

    if (stepData->m_rippleLevel != 0) {
        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &depthTexObj, 0, 0, 0x80, 0x80, depthTexSize, GX_NEAR,
                                   GX_TF_Z24X8, 1);
        GXSetViewport(0.0f, 0.0f, 128.0f,
                      128.0f, 0.0f, 1.0f);
        float fov = 90.0f;
        C_MTXPerspective(projectionMtx, fov, 1.0f,
                         1.0f, 10000.0f);
        GXSetProjection(projectionMtx, GX_PERSPECTIVE);
        float one = 1.0f;
        float zero = 0.0f;

        for (i = 0; i < 6; i++) {
            cameraPos.x = centerPos.x;
            cameraPos.y = centerPos.y;
            cameraPos.z = centerPos.z;
            cameraUp.x = zero;
            cameraUp.y = one;
            cameraUp.z = zero;

            switch (i) {
            case 0:
                cameraPos.x = centerPos.x + one;
                break;
            case 4:
                cameraPos.z = centerPos.z + one;
                break;
            case 1:
                cameraPos.x = centerPos.x - one;
                break;
            case 5:
                cameraPos.z = centerPos.z - one;
                break;
            case 2:
                cameraPos.y = centerPos.y + one;
                cameraUp.x = zero;
                cameraUp.y = zero;
                cameraUp.z = -1.0f;
                break;
            case 3:
                cameraPos.y = centerPos.y - one;
                cameraUp.x = zero;
                cameraUp.y = zero;
                cameraUp.z = one;
                break;
            }

            C_MTXLookAt(lookAtMtx, (Point3d*)&centerPos, &cameraUp, (Point3d*)&cameraPos);
            Graphic.SetViewport();
            GXSetScissor(0, 0, 0x280, 0x1C0);
            float texQuadZero = 0.0f;
            float texQuadSize = 128.0f;
            gUtil.RenderTextureQuad(texQuadZero, texQuadZero, texQuadSize,
                                    texQuadSize, baseParaboloidTexObjs, 0, 0, 0,
                                    GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
            baseParaboloidTexObjs++;
        }

        PSMTXCopy(savedCameraMtx, CameraMatrix());
        Graphic.SetViewport();
        GXSetScissor(0, 0, 0x280, 0x1C0);
        GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
        GXSetColorUpdate(GX_FALSE);
        gUtil.BeginQuadEnv();
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
        GXSetZCompLoc(GX_FALSE);
        gUtil.SetVtxFmt_POS_CLR_TEX();
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXLoadTexObj(&depthTexObj, GX_TEXMAP0);

        quadMin.x = 0.0f;
        quadMin.y = 0.0f;
        quadMin.z = 0.0f;
        quadMax.x = 128.0f;
        quadMax.y = 128.0f;
        quadMax.z = 0.0f;
        quadColor.r = 0xFF;
        quadColor.g = 0xFF;
        quadColor.b = 0xFF;
        quadColor.a = 0;
        gUtil.RenderQuad(quadMin, quadMax, quadColor, 0, 0);
        gUtil.EndQuadEnv();
        GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_TRUE);
        GXSetZCompLoc(GX_TRUE);
        quadMin.x = 0.0f;
        quadMin.y = 0.0f;
        quadMin.z = 0.0f;
        gUtil.RenderTextureQuad(0.0f, 0.0f, 128.0f,
                                128.0f, &sceneTexObj, 0, 0, 0, GX_BL_SRCALPHA,
                                GX_BL_INVSRCALPHA);
        mana2->m_paraboloidReady = 1;
    }

    envTexture0 = mana2->m_envTexture0;
    if (stepData->m_rippleLevel != 0) {
        GXInitTexObj(mana2->m_generatedTexObj0, mana2->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP,
                     GX_CLAMP, GX_FALSE);
        GXInitTexObj(mana2->m_generatedTexObj1, mana2->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP,
                     GX_CLAMP, GX_FALSE);
        drawParaboloidMap(sourceTexObjs, mana2->m_generatedTexObj1, mana2->m_paraboloidMap, mana2->m_paraboloidMapSize,
                          &envTexture0->m_texObj, 1);
        drawParaboloidMap(sourceTexObjs, mana2->m_generatedTexObj0, mana2->m_paraboloidMap, mana2->m_paraboloidMapSize,
                          &envTexture0->m_texObj, 0);
        Graphic.SetViewport();
        GXSetProjection(savedScreenMtx, GX_PERSPECTIVE);
        PSMTXCopy(savedCameraMtx, CameraMatrix());
    } else {
        if (mana2->m_paraboloidReady == 0) {
            GXInitTexObj(mana2->m_generatedTexObj0, mana2->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, GX_REPEAT,
                         GX_REPEAT, GX_FALSE);
            GXInitTexObj(mana2->m_generatedTexObj1, mana2->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, GX_REPEAT,
                         GX_REPEAT, GX_FALSE);
            drawParaboloidMap(mana2->m_baseParaboloidTexObjs, mana2->m_generatedTexObj1, mana2->m_paraboloidMap,
                              mana2->m_paraboloidMapSize, &envTexture0->m_texObj, 1);
            drawParaboloidMap(mana2->m_baseParaboloidTexObjs, mana2->m_generatedTexObj0, mana2->m_paraboloidMap,
                              mana2->m_paraboloidMapSize, &envTexture0->m_texObj, 0);
            mana2->m_paraboloidReady = 1;
        }
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(reinterpret_cast<CCharaPcs::CHandle*>(handle));
    model->m_beforeDrawModelCallback = Mana2_BeforeDrawCallback;
    model->SetDrawMeshDLCallback(Mana2_DrawMeshDLCallback);
}

/*
 * --INFO--
 * PAL Address: 0x80107e48
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMana2(pppMana2*, pppMana2Step*, _pppCtrlTable*)
{
    Graphic.Printf(const_cast<char*>(sRenderMana2Message));
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x80107ea4
 * PAL Size: 2556b
 * EN Address: 0x801072B4
 * EN Size: 2556b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameMana2(pppMana2* pppMana2, pppMana2Step* step, _pppCtrlTable* ctrl)
{
    u32 texBufferSize;
    CGObject* gObject;
    VMana2* mana2Work;
    GXTexObj* dstTexObj;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    s32 i;
    CChara::CMesh* mesh;
    CChara::CMesh::CRefData* meshData;
    u32 meshIndex;
    u32 vertexIndex;

    if (ppvUserStopPartF != 0) {
        return;
    }

    gObject = (CGObject*)ppvMng->m_lookTarget;
    mana2Work = GetMana2Work(pppMana2, ctrl);
    Mana2SetupBlock* setupBlock = GetMana2SetupBlock(pppMana2, ctrl);
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    step->m_rippleLevel = 0;
    mana2Work->m_step = step;
    if (Game.m_currentMapId == 0x21) {
        step->m_rippleLevel = 0;
    }

    SetMana2ModelCallbacks(model, mana2Work, step);

    unsigned char reflectionAlpha = setupBlock->m_color.rgba[3];
    MaterialMan.SetReflectionAlpha(reflectionAlpha);
    mana2Work->m_waterAlpha = reflectionAlpha;

    if (reinterpret_cast<_pppPObject*>(pppMana2)->m_graphId == 0) {
        mana2Work->m_object = gObject;
        SetMana2ModelCallbacks(model, mana2Work, step);
        mana2Work->m_sourceTextures[0] = GetTextureFromRSD(step->m_sourceTextureIds[0], ppvEnv);
        mana2Work->m_sourceTextures[1] = GetTextureFromRSD(step->m_sourceTextureIds[1], ppvEnv);
        mana2Work->m_sourceTextures[2] = GetTextureFromRSD(step->m_sourceTextureIds[2], ppvEnv);
        mana2Work->m_sourceTextures[3] = GetTextureFromRSD(step->m_sourceTextureIds[3], ppvEnv);
        mana2Work->m_sourceTextures[4] = GetTextureFromRSD(step->m_sourceTextureIds[4], ppvEnv);
        mana2Work->m_sourceTextures[5] = GetTextureFromRSD(step->m_sourceTextureIds[5], ppvEnv);
        mana2Work->m_envTexture0 = GetTextureFromRSD(step->m_envTextureId0, ppvEnv);
        mana2Work->m_envTexture1 = GetTextureFromRSD(step->m_envTextureId1, ppvEnv);

        if (mana2Work->m_sourceTexObjs == 0) {
            mana2Work->m_sourceTexObjs =
                static_cast<GXTexObj*>(pppMemAlloc(0xC0, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1D7));
        }
        if (mana2Work->m_generatedTexObj0 == 0) {
            mana2Work->m_generatedTexObj0 =
                static_cast<GXTexObj*>(pppMemAlloc(0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1DD));
        }
        if (mana2Work->m_generatedTexObj1 == 0) {
            mana2Work->m_generatedTexObj1 =
                static_cast<GXTexObj*>(pppMemAlloc(0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1E1));
        }

        texBufferSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB565, GX_FALSE, 0);
        if (mana2Work->m_generatedTexture0 == 0) {
            mana2Work->m_generatedTexture0 =
                pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1E9);
        }
        if (mana2Work->m_generatedTexture1 == 0) {
            mana2Work->m_generatedTexture1 =
                pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1EB);
        }

        GXInitTexObj(mana2Work->m_generatedTexObj0, mana2Work->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, GX_REPEAT, GX_REPEAT, GX_FALSE);
        GXInitTexObj(mana2Work->m_generatedTexObj1, mana2Work->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, GX_REPEAT, GX_REPEAT, GX_FALSE);

        if (mana2Work->m_baseParaboloidTexObjs == 0) {
            mana2Work->m_baseParaboloidTexObjs =
                static_cast<GXTexObj*>(pppMemAlloc(0xC0, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x1F6));
        }
        dstTexObj = mana2Work->m_baseParaboloidTexObjs;
        for (i = 0; i < 6; i++) {
            memcpy(dstTexObj, &mana2Work->m_sourceTextures[i]->m_texObj, sizeof(GXTexObj));
            dstTexObj++;
        }

        CTexture* envTexture0 = mana2Work->m_envTexture0;
        CTexture* envTexture1 = mana2Work->m_envTexture1;
        envTexture0->m_wrapMode = 0;
        envTexture0->InitTexObj();
        envTexture1->m_wrapMode = 0;
        envTexture1->InitTexObj();

        if (mana2Work->m_paraboloidMap == 0) {
            mana2Work->m_paraboloidMap =
                pppMemAlloc(0xA5E8, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x211);
            genParaboloidMap(mana2Work->m_paraboloidMap, &mana2Work->m_paraboloidMapSize, 0x1E, GX_VTXFMT7);
        }

        mesh = model->m_meshes;
        if (mana2Work->m_positions == 0 && mana2Work->m_normals == 0 && mana2Work->m_waterHeightA == 0) {
            for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++) {
                meshData = mesh->m_data;

                if (((step->m_type == 1) && strcmp(meshData->m_name, "obj5") == 0) ||
                    ((step->m_type == 2) && strcmp(meshData->m_name, "obj3") == 0) ||
                    ((step->m_type == 3) && strcmp(meshData->m_name, "obj1") == 0)) {
                    if (mana2Work->m_meshReflectionVec == 0) {
                        mana2Work->m_meshReflectionVec =
                            static_cast<Vec*>(pppMemAlloc(meshData->m_vertexCount * sizeof(Vec), ppvEnv->m_stagePtr,
                                                          const_cast<char*>(s_pppMana2_cpp), 0x232));
                        Vec* reflectionVec = mana2Work->m_meshReflectionVec;
                        float zero = 0.0f;
                        for (vertexIndex = 0; vertexIndex < meshData->m_vertexCount; vertexIndex++) {
                            reflectionVec->z = zero;
                            reflectionVec->y = zero;
                            reflectionVec->x = zero;
                            reflectionVec++;
                        }
                    }

                    if (mana2Work->m_meshColors == 0) {
                        mana2Work->m_meshColors =
                            static_cast<GXColor*>(pppMemAlloc(meshData->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
                                                              const_cast<char*>(s_pppMana2_cpp), 0x23B));
                        GXColor* color = mana2Work->m_meshColors;
                        for (vertexIndex = 0; vertexIndex < meshData->m_vertexCount; vertexIndex++) {
                            color->r = 0xFF;
                            color->g = 0xFF;
                            color->b = 0xFF;
                            color->a = 0xFF;
                            color++;
                        }
                    }

                    if (mana2Work->m_meshTexCoords == 0) {
                        mana2Work->m_meshTexCoords =
                            static_cast<S16Vec2d*>(pppMemAlloc(meshData->m_vertexCount * 6, ppvEnv->m_stagePtr,
                                                               const_cast<char*>(s_pppMana2_cpp), 0x244));
                        u16* texCoord = reinterpret_cast<u16*>(mana2Work->m_meshTexCoords);
                        for (vertexIndex = 0; vertexIndex < meshData->m_vertexCount; vertexIndex++) {
                            texCoord[1] = 0;
                            texCoord[0] = 0;
                            texCoord += 3;
                        }
                    }

                    mana2Work->m_displayListCopies =
                        static_cast<void**>(pppMemAlloc(meshData->m_displayListCount * sizeof(void*), ppvEnv->m_stagePtr,
                                                        const_cast<char*>(s_pppMana2_cpp), 0x24B));
                    CChara::CMesh::CDisplayList* displayList = meshData->m_displayLists;
                    for (s32 dlIndex = meshData->m_displayListCount - 1; dlIndex >= 0; dlIndex--) {
                        void* copiedDisplayList =
                            pppMemAlloc(displayList->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x255);
                        mana2Work->m_displayListCopies[dlIndex] = copiedDisplayList;
                        mana2Work->m_displayListCopies[dlIndex] = reinterpret_cast<void*>(
                            (reinterpret_cast<u32>(mana2Work->m_displayListCopies[dlIndex]) + 0x1F) & 0xFFFFFFE0);
                        mana2Work->m_displayListSize = displayList->m_size;
                        memcpy(mana2Work->m_displayListCopies[dlIndex], displayList->m_data, displayList->m_size);
                        DCFlushRange(mana2Work->m_displayListCopies[dlIndex], displayList->m_size);
                        gUtil.ReWriteDisplayList(mana2Work->m_displayListCopies[dlIndex], displayList->m_size, 1);
                        displayList++;
                    }
                }

                if (((step->m_type == 1) && strcmp(meshData->m_name, "obj4") == 0) ||
                    ((step->m_type == 2) && strcmp(meshData->m_name, "obj2") == 0)) {
                    mana2Work->m_positions = static_cast<Vec*>(pppMemAlloc(kWaterVertexCount * sizeof(Vec), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26A));
                    mana2Work->m_normals = static_cast<Vec*>(pppMemAlloc(kWaterVertexCount * sizeof(Vec), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26B));
                    mana2Work->m_colors = static_cast<GXColor*>(pppMemAlloc(kWaterVertexCount * sizeof(GXColor), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26C));
                    mana2Work->m_texCoord0 = static_cast<Vec2d*>(pppMemAlloc(kWaterVertexCount * sizeof(Vec2d), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26D));
                    mana2Work->m_texCoord1 = static_cast<Vec2d*>(pppMemAlloc(kWaterVertexCount * sizeof(Vec2d), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26E));
                    mana2Work->m_waterHeightA = static_cast<float*>(pppMemAlloc(kWaterVertexCount * sizeof(float), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26F));
                    mana2Work->m_waterHeightB = static_cast<float*>(pppMemAlloc(kWaterVertexCount * sizeof(float), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x270));
                    mana2Work->m_indices = static_cast<u16*>(pppMemAlloc(kWaterTriangleCount * 3 * sizeof(u16), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x271));
                    mana2Work->m_reflectionVec = static_cast<Vec*>(pppMemAlloc(kWaterVertexCount * sizeof(Vec), ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x272));

                    float* waterHeightA = mana2Work->m_waterHeightA;
                    float* waterHeightB = mana2Work->m_waterHeightB;
                    float zero = 0.0f;
                    for (vertexIndex = 0; vertexIndex < kWaterVertexCount; vertexIndex++) {
                        waterHeightA[vertexIndex] = zero;
                        waterHeightB[vertexIndex] = zero;
                    }

                    CreateWaterMesh(mana2Work->m_positions, mana2Work->m_normals, mana2Work->m_texCoord0,
                                    mana2Work->m_indices, step->m_waterScale);
                }

                mesh++;
            }
        }

        if (step->m_type == 1 || step->m_type == 2) {
            float* waterHeightA = mana2Work->m_waterHeightA;
            float rippleHeight = step->m_rippleHeight;
            if (waterHeightA != 0) {
                waterHeightA[0x90] = rippleHeight;
            }
        }
    }

    if (step->m_type != 0) {
        if (step->m_type == 1 || step->m_type == 2) {
            UpdateWaterMesh(mana2Work);
        }

        mesh = model->m_meshes;
        for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++) {
            meshData = mesh->m_data;

            if (((step->m_type == 1) && strcmp(meshData->m_name, "obj5") == 0) ||
                ((step->m_type == 2) && strcmp(meshData->m_name, "obj3") == 0) ||
                ((step->m_type == 3) && strcmp(meshData->m_name, "obj1") == 0)) {
                for (s32 dlIndex = meshData->m_displayListCount - 1; dlIndex >= 0; dlIndex--) {
                    CalcReflectionVector2(
                        mana2Work->m_meshReflectionVec, meshData->m_vertices, meshData->m_normals,
                        meshData->m_vertexCount, model->m_data->m_posQuant,
                        model->m_data->m_normQuant, model->m_matrix,
                        mana2Work->m_displayListCopies[dlIndex], mana2Work->m_displayListSize,
                        mana2Work->m_meshColors, mana2Work->m_meshTexCoords,
                        &model->m_nodes[meshData->m_nodeIndex]);
                }
            }

            mesh++;
        }
    }
}
/*
 * --INFO--
 * PAL Address: 0x801088a0
 * PAL Size: 992b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructMana2(pppMana2* pppMana2, _pppCtrlTable* ctrl)
{
    VMana2* work;
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CChara::CMesh* mesh;
    pppMana2Step* step;
    u32 i;
    u32 j;

    work = GetMana2Work(pppMana2, ctrl);
    MaterialMan.ClearManaParaboloidTexObjs();

    if (work->m_generatedTexObj0 != NULL) {
        pppMemFree(work->m_generatedTexObj0);
        work->m_generatedTexObj0 = 0;
    }
    if (work->m_generatedTexObj1 != NULL) {
        pppMemFree(work->m_generatedTexObj1);
        work->m_generatedTexObj1 = 0;
    }
    if (work->m_generatedTexture0 != NULL) {
        pppMemFree(work->m_generatedTexture0);
        work->m_generatedTexture0 = 0;
    }
    if (work->m_generatedTexture1 != NULL) {
        pppMemFree(work->m_generatedTexture1);
        work->m_generatedTexture1 = 0;
    }
    if (work->m_baseParaboloidTexObjs != NULL) {
        pppMemFree(work->m_baseParaboloidTexObjs);
        work->m_baseParaboloidTexObjs = 0;
    }
    if (work->m_positions != NULL) {
        pppMemFree(work->m_positions);
        work->m_positions = 0;
    }
    if (work->m_normals != NULL) {
        pppMemFree(work->m_normals);
        work->m_normals = 0;
    }
    if (work->m_waterHeightA != NULL) {
        pppMemFree(work->m_waterHeightA);
        work->m_waterHeightA = 0;
    }
    if (work->m_waterHeightB != NULL) {
        pppMemFree(work->m_waterHeightB);
        work->m_waterHeightB = 0;
    }
    if (work->m_indices != NULL) {
        pppMemFree(work->m_indices);
        work->m_indices = 0;
    }
    if (work->m_texCoord0 != NULL) {
        pppMemFree(work->m_texCoord0);
        work->m_texCoord0 = 0;
    }
    if (work->m_texCoord1 != NULL) {
        pppMemFree(work->m_texCoord1);
        work->m_texCoord1 = 0;
    }
    if (work->m_sourceTexObjs != NULL) {
        pppMemFree(work->m_sourceTexObjs);
        work->m_sourceTexObjs = 0;
    }
    if (work->m_paraboloidMap != NULL) {
        pppMemFree(work->m_paraboloidMap);
        work->m_paraboloidMap = 0;
    }
    if (work->m_colors != NULL) {
        pppMemFree(work->m_colors);
        work->m_colors = 0;
    }
    if (work->m_reflectionVec != NULL) {
        pppMemFree(work->m_reflectionVec);
        work->m_reflectionVec = 0;
    }
    if (work->m_meshReflectionVec != NULL) {
        pppMemFree(work->m_meshReflectionVec);
        work->m_meshReflectionVec = 0;
    }
    if (work->m_meshColors != NULL) {
        pppMemFree(work->m_meshColors);
        work->m_meshColors = 0;
    }
    if (work->m_meshTexCoords != NULL) {
        pppMemFree(work->m_meshTexCoords);
        work->m_meshTexCoords = 0;
    }
    gObject = (CGObject*)ppvMng->m_lookTarget;
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    model->m_beforeDrawModelCallback = 0;
    model->SetDrawMeshDLCallback(0);
    mesh = model->m_meshes;
    step = work->m_step;
    for (i = 0; i < model->m_data->m_meshCount; i++, mesh++) {
        u8 stepType = step->m_type;
        CChara::CMesh::CRefData* meshData = mesh->m_data;

        if (stepType == 1) {
            if (strcmp(meshData->m_name, "obj5") == 0) {
                for (j = 0; j < meshData->m_displayListCount; j++) {
                    if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                        pppMemFree(work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != NULL) {
                    pppMemFree(work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 2) {
            if (strcmp(meshData->m_name, "obj3") == 0) {
                for (j = 0; j < meshData->m_displayListCount; j++) {
                    if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                        pppMemFree(work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != NULL) {
                    pppMemFree(work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 3 && strcmp(meshData->m_name, "obj1") == 0) {
            for (j = 0; j < meshData->m_displayListCount; j++) {
                if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                    pppMemFree(work->m_displayListCopies[j]);
                    work->m_displayListCopies[j] = 0;
                }
            }
            if (work->m_displayListCopies != NULL) {
                pppMemFree(work->m_displayListCopies);
                work->m_displayListCopies = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80108c80
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructMana2(pppMana2* pppMana2, _pppCtrlTable* ctrl)
{
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    VMana2* work;

    work = GetMana2Work(pppMana2, ctrl);
    gObject = (CGObject*)ppvMng->m_lookTarget;
    gObject->m_alphaTarget = 0.99999f;

    handle = GetCharaHandlePtr(gObject, 0);
    GetCharaModelPtr(handle);
    model = handle->m_model;
    model->m_meshVisibleMask = 0x3F;
    work->m_manager = ppvMng;

    work->m_object = 0;
    work->m_manager = 0;
    work->m_paraboloidMap = 0;
    work->m_baseParaboloidTexObjs = 0;
    work->m_positions = 0;
    work->m_normals = 0;
    work->m_waterHeightA = 0;
    work->m_waterHeightB = 0;
    work->m_indices = 0;
    work->m_texCoord0 = 0;
    work->m_texCoord1 = 0;
    work->m_displayListCopies = 0;
    work->m_reflectionVec = 0;
    work->m_colors = 0;
    work->m_sourceTexObjs = 0;
    work->m_step = 0;
    work->m_envTexture0 = 0;
    work->m_envTexture1 = 0;
    work->m_meshReflectionVec = 0;
    work->m_meshColors = 0;
    work->m_meshTexCoords = 0;
    work->m_generatedTexObj0 = 0;
    work->m_generatedTexObj1 = 0;
    work->m_generatedTexture0 = 0;
    work->m_generatedTexture1 = 0;
    work->m_waterAlpha = 0xFF;
    PSMTXIdentity(work->m_waterMtx);
    PSMTXIdentity(work->m_reflectionMtx);
    work->m_runtimeColor.r = 0xFF;
    work->m_runtimeColor.g = 0xFF;
    work->m_runtimeColor.b = 0xFF;
    work->m_runtimeColor.a = 0xFF;
    work->m_sourceTextures[0] = 0;
    work->m_sourceTextures[1] = 0;
    work->m_sourceTextures[2] = 0;
    work->m_sourceTextures[3] = 0;
    work->m_sourceTextures[4] = 0;
    work->m_sourceTextures[5] = 0;
    work->m_paraboloidMapSize = 0;
    work->m_displayListSize = 0;
    work->m_paraboloidReady = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80108db0
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void Mana2_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    CChara::CMesh::CRefData* meshData = model->m_meshes[partIndex].m_data;
    VMana2* mana2 = (VMana2*)work;
    CChara::CMesh::CDisplayList* displayList = &meshData->m_displayLists[dlIndex];
    unsigned int draw = 0;
    pppMana2Step* stepData = static_cast<pppMana2Step*>(step);
    int type = stepData->m_type;

    switch (type) {
    case 0:
        if (strcmp(meshData->m_name, "obj") == 0) {
            draw = 1;
        }
        break;
    case 1:
        if (strcmp(meshData->m_name, "obj") == 0 || strcmp(meshData->m_name, "obj5") == 0) {
            draw = 1;
        }
        break;
    case 2:
        if (strcmp(meshData->m_name, "obj") == 0 || strcmp(meshData->m_name, "obj3") == 0) {
            draw = 1;
        }
        break;
    case 3:
        if (strcmp(meshData->m_name, "obj") == 0 || strcmp(meshData->m_name, "obj1") == 0) {
            draw = 1;
        }
        break;
    }

    int waterCmp = strcmp(meshData->m_name, "obj4");
    if ((waterCmp == 0 && stepData->m_type == 1) || (strcmp(meshData->m_name, "obj2") == 0 && stepData->m_type == 2)) {
        Mtx cameraMtx;
        Mtx posMtx;
        Mtx rotMtx;
        Vec offset;

        PSMTXCopy(CameraMatrix(), cameraMtx);
        PSMTXRotRad(rotMtx, 'z', -1.5707964f);
        float x = mtx[0][3];
        float y = mtx[1][3];
        float z = mtx[2][3];
        mtx[0][3] = 0.0f;
        mtx[1][3] = 0.0f;
        mtx[2][3] = 0.0f;
        PSMTXConcat(mtx, rotMtx, mtx);

        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        offset.y = stepData->m_waterScale;
        PSMTXMultVec(mtx, &offset, &offset);

        y = y - offset.y;
        mtx[0][3] = x;
        mtx[1][3] = y;
        mtx[2][3] = z;

        PSMTXConcat(cameraMtx, mtx, posMtx);
        GXLoadPosMtxImm(posMtx, 0);
        PSMTXCopy(mtx, mana2->m_waterMtx);
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        RenderWaterMesh(mana2);
        GXSetCullMode(GX_CULL_FRONT);
    }

    if (draw) {
        if (draw == 1 && strcmp(meshData->m_name, "obj") != 0) {
            PSMTXCopy(mtx, mana2->m_reflectionMtx);
            if (mana2->m_paraboloidReady != 0) {
                mana2->m_runtimeColor.r = meshData->m_colors[0].r;
                mana2->m_runtimeColor.g = meshData->m_colors[0].g;
                mana2->m_runtimeColor.b = meshData->m_colors[0].b;
                mana2->m_runtimeColor.a = 0x80;
                DCFlushRange(&mana2->m_runtimeColor, 4);
                GXSetArray(GX_VA_CLR0, mana2->m_meshColors, 4);
                GXSetArray(GX_VA_TEX0, mana2->m_meshTexCoords, 4);
                MaterialMan.SetManaReflectionVec(mana2->m_meshReflectionVec);
                MaterialMan.InitEnv();
                MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x200000));
                MaterialMan.LockEnv();
                MaterialMan.SetEnvTexObj(mana2->m_baseParaboloidTexObjs);
                GXSetCullMode(GX_CULL_FRONT);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);
                GXCallDisplayList(mana2->m_displayListCopies[dlIndex], displayList->m_size);
            }
        } else {
            if (strcmp(meshData->m_name, "obj") == 0) {
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
                MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, GX_CS_SCALE_1);
                GXCallDisplayList(displayList->m_data, displayList->m_size);
            }
        }
    }
}
