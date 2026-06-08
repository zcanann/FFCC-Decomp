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
extern const float kMana2Zero = 0.0f;
extern const float kMana2NegativeOne = -1.0f;
extern const float kMana2One = 1.0f;
extern const float kMana2Half = 0.5f;
extern const float kMana2MeshUvStep = 0.0625f;
extern const double kMana2SignedIntBias = 4503601774854144.0;
extern const float kMana2Two = 2.0f;
extern const float kMana2Quarter = 0.25f;
extern const float kMana2ThreeQuarter = 0.75f;
extern const float kMana2ParaboloidCenterYOffset = 5.0f;
extern const float kMana2ParaboloidTexSize = 128.0f;
extern const float kMana2ParaboloidFov = 90.0f;
extern const float kMana2ParaboloidFar = 10000.0f;
static const char s_manaShapeObj5[] = "obj5";
static const char s_manaShapeObj3[] = "obj3";
static const char s_manaShapeObj1[] = "obj1";
static const char s_manaShapeObj4[] = "obj4";
static const char s_manaShapeObj2[] = "obj2";
extern const float kMana2StepSlopeLimit = 0.99999f;
static const char s_manaShapeObj[] = "obj";
extern const float kMana2WaterRotZRad = -1.5707964f;
extern const float kPppConformBgNormalZero = 0.0f;
extern const float kPppConformBgNormalOne = 1.0f;

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

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline void ClearMana2ModelCallbacks(CChara::CModel* model)
{
    model->SetCallbackContext(0, 0);
    model->m_afterMeshDrawCallback = 0;
    model->SetDrawMeshDLCallback(0);
}

static inline void SetMana2ModelCallbacks(CChara::CModel* model, void* work, pppMana2Step* step)
{
    model->SetCallbackContext(work, step);
    model->m_afterMeshDrawCallback = (CChara::CModel::AfterMeshDrawCallback)Mana2_BeforeDrawCallback;
    model->SetDrawMeshDLCallback(Mana2_DrawMeshDLCallback);
}

static int CreateWaterMesh(Vec* param_1, Vec* param_2, Vec2d* param_3, unsigned short* param_4, float param_5);
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
    unsigned char* colorBytes;
    float* texCoordFloat;
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

    transformedCameraPos.x = LoadFloat(kMana2Zero);
    transformedCameraPos.y = LoadFloat(kMana2Zero);
    transformedCameraPos.z = LoadFloat(kMana2Zero);

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, LoadFloat(kMana2NegativeOne));
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    zero = LoadFloat(kMana2Zero);
    positionIt = positions;
    half = LoadFloat(kMana2Half);
    reflectionIt = reflectionVec;
    normalIt = normals;
    colorBytes = (unsigned char*)color;
    texCoordFloat = (float*)texCoord;

    i = 0;
    while (i < count) {
        PSVECSubtract(positionIt, &transformedCameraPos, &reflected);
        C_VECReflect(&reflected, normalIt, reflectionIt);
        PSMTXMultVec(matrixNoTranslate, reflectionIt, reflectionIt);
        PSVECNormalize(reflectionIt, reflectionIt);

        if (reflectionIt->z >= zero) {
            float denomBase;

            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            denomBase = LoadFloat(kMana2One);
            *texCoordFloat = -reflectionIt->x / (denomBase + reflectionIt->z);
            texCoordFloat[1] = -reflectionIt->y / (denomBase + reflectionIt->z);
        } else {
            float denomBase;

            colorBytes[0] = 0x80;
            colorBytes[1] = 0xff;
            colorBytes[2] = 0x80;
            colorBytes[3] = 0x7f;
            denomBase = LoadFloat(kMana2One);
            *texCoordFloat = -reflectionIt->x / (denomBase - reflectionIt->z);
            texCoordFloat[1] = -reflectionIt->y / (denomBase - reflectionIt->z);
        }

        positionIt++;
        reflectionIt++;
        normalIt++;
        colorBytes += 4;
        i++;
        *texCoordFloat = *texCoordFloat * half;
        *texCoordFloat = *texCoordFloat + half;
        texCoordFloat[1] = texCoordFloat[1] * half;
        texCoordFloat[1] = texCoordFloat[1] + half;
        texCoordFloat += 2;
    }

    DCFlushRange(reflectionVec, count * sizeof(Vec));
    DCFlushRange(texCoord, count << 3);
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
    for (i = 0; i < 0x121; i++) {
        normals[i].z = zero;
        normals[i].y = zero;
        normals[i].x = zero;
    }

    i = 0;
    s32 indicesOffset = i;
    for (; i < 0x200; i++) {
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

    for (i = 0; i < 0x121; i++) {
        PSVECNormalize(&normals[i], &normals[i]);
    }

    DCFlushRange(normals, 0xD8C);
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
    void* positions = mana2->m_positions;
    void* normals = mana2->m_normals;
    void* texCoord0 = mana2->m_texCoord0;
    void* texCoord1 = mana2->m_texCoord1;
    u16* indices = mana2->m_indices;
    void* colors = mana2->m_colors;
    GXTexObj* texObj0 = mana2->m_generatedTexObj0;
    CTexture* texObj2;
    _GXColor blendColor;
    _GXColor modulateColor;

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_INDEX16);
    GXSetVtxDesc((GXAttr)10, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xB, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xD, GX_INDEX16);
    GXSetVtxDesc((GXAttr)0xE, GX_INDEX16);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)10, (GXCompCnt)0, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xB, (GXCompCnt)1, (GXCompType)5, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)7, (GXAttr)0xE, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetNumTexGens(2);
    GXSetCullMode((GXCullMode)0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl((GXChannelID)4, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetNumChans(1);
    blendColor.r = 0xFF;
    blendColor.g = 0xFF;
    blendColor.b = 0xFF;
    blendColor.a = 0xFF;
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetArray((GXAttr)9, positions, 0xC);
    GXSetArray((GXAttr)10, normals, 0xC);
    GXSetArray((GXAttr)0xB, colors, 4);
    GXSetArray((GXAttr)0xD, texCoord0, 8);
    GXSetArray((GXAttr)0xE, texCoord1, 8);
    texObj2 = mana2->m_envTexture1;
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3C, GX_FALSE, 0x7D);
    u8 alpha = mana2->m_waterAlpha;
    blendColor.r = 0x80;
    blendColor.g = 0x80;
    blendColor.b = 0x80;
    blendColor.a = 0x80;
    modulateColor.r = alpha;
    modulateColor.g = alpha;
    modulateColor.b = alpha;
    modulateColor.a = alpha;

    GXSetTevDirect((GXTevStageID)0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXLoadTexObj(&texObj2->m_texObj, GX_TEXMAP0);
    GXSetTevKColor((GXTevKColorID)1, modulateColor);
    GXSetTevKColorSel((GXTevStageID)0, (GXTevKColorSel)0xD);
    GXSetTevKAlphaSel((GXTevStageID)0, (GXTevKAlphaSel)0x1D);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetTevDirect((GXTevStageID)1);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXLoadTexObj(mana2->m_generatedTexObj0, GX_TEXMAP1);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_RASA, GX_CC_KONST, GX_CC_TEXC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);

    GXSetTevDirect((GXTevStageID)2);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR0A0);
    GXLoadTexObj(mana2->m_generatedTexObj1, GX_TEXMAP2);
    GXSetTevKColor((GXTevKColorID)0, blendColor);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xC);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1C);
    _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_KONST, GX_CC_RASA, GX_CC_TEXC, GX_CC_CPREV);
    _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    GXSetNumTevStages(3);
    GXBegin((GXPrimitive)0x90, GX_VTXFMT7, 0x600);
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
    GXLoadTexObj((GXTexObj*)texObj0, GX_TEXMAP0);
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
    float* waterHeightA;
    float* waterHeightB;
    Vec* positions;
    Vec origin;
    float currentScale;
    float neighborScale;

    waterHeightA = mana2->m_waterHeightA;
    positions = mana2->m_positions;
    waterHeightB = mana2->m_waterHeightB;
    if (waterHeightA == NULL) {
        return 0;
    }

    int row = 1;
    int rowBase = 0x11;
    do {
        currentScale = kMana2Zero;
        neighborScale = kMana2Half;
        int index = rowBase + 1;
        for (int col = 1; col < 0x10; col += 5, index += 5) {
            int above0 = index - 0x11;
            int below0 = index + 0x11;

            waterHeightB[index] = currentScale * waterHeightA[index] +
                                  neighborScale * (waterHeightA[above0] + waterHeightA[below0] +
                                                   waterHeightA[index - 1] + waterHeightA[index + 1]) -
                                  waterHeightB[index];

            int index1 = index + 1;
            int above1 = index1 - 0x11;
            int below1 = index1 + 0x11;
            waterHeightB[index1] = currentScale * waterHeightA[index1] +
                                   neighborScale * (waterHeightA[above1] + waterHeightA[below1] +
                                                    waterHeightA[index1 - 1] + waterHeightA[index1 + 1]) -
                                   waterHeightB[index1];

            int index2 = index + 2;
            int above2 = index2 - 0x11;
            int below2 = index2 + 0x11;
            waterHeightB[index2] = currentScale * waterHeightA[index2] +
                                   neighborScale * (waterHeightA[above2] + waterHeightA[below2] +
                                                    waterHeightA[index2 - 1] + waterHeightA[index2 + 1]) -
                                   waterHeightB[index2];

            int index3 = index + 3;
            int above3 = index3 - 0x11;
            int below3 = index3 + 0x11;
            waterHeightB[index3] = currentScale * waterHeightA[index3] +
                                   neighborScale * (waterHeightA[above3] + waterHeightA[below3] +
                                                    waterHeightA[index3 - 1] + waterHeightA[index3 + 1]) -
                                   waterHeightB[index3];

            int index4 = index + 4;
            int above4 = index4 - 0x11;
            int below4 = index4 + 0x11;
            waterHeightB[index4] = currentScale * waterHeightA[index4] +
                                   neighborScale * (waterHeightA[above4] + waterHeightA[below4] +
                                                    waterHeightA[index4 - 1] + waterHeightA[index4 + 1]) -
                                   waterHeightB[index4];
        }
        row++;
        rowBase += 0x11;
    } while (row < 0x10);

    for (int i = 0; i < 0x121; i++) {
        float tmp = waterHeightA[i];
        waterHeightA[i] = waterHeightB[i];
        waterHeightB[i] = tmp;
        positions[i].y = waterHeightA[i];
    }

    DCFlushRange(positions, 0xD8C);
    CalculateNormal(mana2);

    origin.x = mana2->m_waterMtx[0][3];
    origin.y = mana2->m_waterMtx[1][3];
    origin.z = mana2->m_waterMtx[2][3];
    CalcWaterReflectionVector(mana2->m_reflectionVec, mana2->m_positions, mana2->m_normals, 0x121, origin,
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
static int CreateWaterMesh(Vec* param_1, Vec* param_2, Vec2d* param_3, unsigned short* param_4, float param_5)
{
    float zero;
    float normalY;
    float radius;
    float uvStep;
    float x;
    float z;
    int indexOffset;
    int quadIndex;
    int rowBase;
    float* positions;
    int rowCount;
    float* normals;
    float* uvs;
    int colCount;
    int pairCount;

    normalY = LoadFloat(kMana2One);
    zero = LoadFloat(kMana2Zero);
    rowCount = 0;
    uvStep = LoadFloat(kMana2MeshUvStep);
    radius = param_5 * LoadFloat(kMana2Half);
    for (z = radius; -radius <= z; z -= param_5 * uvStep) {
        colCount = 0;
        positions = reinterpret_cast<float*>(param_1);
        normals = reinterpret_cast<float*>(param_2);
        uvs = reinterpret_cast<float*>(param_3);
        for (x = -radius; x <= radius; x += param_5 * uvStep) {
            *positions = x;
            param_1 = reinterpret_cast<Vec*>(positions + 3);
            positions[1] = zero;
            param_2 = reinterpret_cast<Vec*>(normals + 3);
            param_3 = reinterpret_cast<Vec2d*>(uvs + 2);
            positions[2] = z;
            positions = positions + 3;
            *normals = zero;
            normals[1] = normalY;
            normals[2] = zero;
            normals = normals + 3;
            *uvs = static_cast<float>(colCount) * uvStep;
            uvs[1] = static_cast<float>(rowCount) * uvStep;
            uvs = uvs + 2;
            colCount = colCount + 1;
        }
        rowCount = rowCount + 1;
    }
    indexOffset = 0;
    rowCount = 0;
    rowBase = 0;
    do {
        quadIndex = rowBase;
        for (pairCount = 0; pairCount < 8; pairCount++) {
            int nextIndex = quadIndex + 1;
            int lowerIndex = quadIndex + 0x11;
            int lowerNextIndex = quadIndex + 0x12;

            param_4[indexOffset++] = quadIndex;
            param_4[indexOffset++] = nextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerIndex;
            param_4[indexOffset++] = quadIndex++;
            nextIndex = quadIndex + 1;
            lowerIndex = quadIndex + 0x11;
            lowerNextIndex = quadIndex + 0x12;

            param_4[indexOffset++] = quadIndex;
            param_4[indexOffset++] = nextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerIndex;
            param_4[indexOffset++] = quadIndex++;
        }
        rowCount = rowCount + 1;
        rowBase = rowBase + 0x11;
    } while (rowCount < 0x10);
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
void CalcReflectionVector2(
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
    Mtx nodeMtx;
    Mtx nodeRotMtx;
    Mtx cameraMtx;
    Mtx cameraModelMtx;
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
    nodeRotMtx[0][3] = LoadFloat(kMana2Zero);
    nodeRotMtx[1][3] = LoadFloat(kMana2Zero);
    nodeRotMtx[2][3] = LoadFloat(kMana2Zero);

    PSMTXCopy(CameraMatrix(), cameraMtx);
    PSMTXConcat(cameraMtx, matrix, cameraModelMtx);

    const float half = LoadFloat(kMana2Half);

    dlEnd = (u16*)((u8*)displayList + displayListSize);
    while (dl < dlEnd) {
        u8 drawFmt = *(u8*)dl;
        u16 itemCount = *(u16*)((u8*)dl + 1);
        int i;

        if (gUtil.IsHasDrawFmtDL(drawFmt) == 0) {
            break;
        }

        dl = (u16*)((u8*)dl + 3);
        for (i = 0; i < itemCount; i++) {
            u16 posIndex = dl[0];
            u16 normalIndex = dl[1];
            int axis = 0;
            float maxAxis;
            float invAxis;
            Vec* outVec;
            u8* clr;

            dl += 4;
            if ((drawFmt & 7) == 2) {
                dl++;
            }

            gUtil.ConvI2FVector(objSpacePos, positions[posIndex], posScale);
            gUtil.ConvI2FVector(objSpaceNormal, normals[normalIndex], normalScale);
            PSMTXMultVec(matrix, &objSpacePos, &objSpacePos);
            PSMTXMultVec(nodeRotMtx, &objSpaceNormal, &objSpaceNormal);

            PSVECSubtract(&objSpacePos, &cameraPos, &cameraVector);
            PSVECNormalize(&cameraVector, &cameraVector);
            outVec = &reflectionVec[posIndex];
            C_VECReflect(&cameraVector, &objSpaceNormal, outVec);

            float absY = fabsf(outVec->y);
            float absX = fabsf(outVec->x);
            float absZ = fabsf(outVec->z);

            maxAxis = absX;
            if (absY > maxAxis) {
                axis = 1;
                maxAxis = absY;
            }
            if (maxAxis < absZ) {
                axis = 2;
            }
            CVector reflected(outVec->x, outVec->y, outVec->z);

            clr = (u8*)&color[posIndex];
            clr[0] = 0x80;
            clr[1] = 0x80;
            clr[2] = 0x80;
            clr[3] = 0xFF;

            uv.x = (float)half;
            uv.y = (float)half;

            switch (axis) {
            case 0:
                invAxis = LoadFloat(kMana2Two) * reflected.x;
                if (outVec->x >= LoadFloat(kMana2Zero)) {
                    clr[0] = (u8)(clr[0] + 0x7F);
                    uv.x = half - reflected.z / invAxis;
                    uv.y = half - reflected.y / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.x = uv.x + LoadFloat(kMana2Quarter);
                    uv.y = uv.y + LoadFloat(kMana2Quarter);
                } else {
                    clr[0] = (u8)(clr[0] - 0x7F);
                    uv.x = half - reflected.z / invAxis;
                    uv.y = half + reflected.y / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.x = uv.x + LoadFloat(kMana2ThreeQuarter);
                    uv.y = uv.y + LoadFloat(kMana2Quarter);
                }
                break;
            case 1:
                invAxis = LoadFloat(kMana2Two) * reflected.y;
                if (outVec->y >= LoadFloat(kMana2Zero)) {
                    clr[1] = (u8)(clr[1] + 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half + reflected.z / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.x = uv.x + half;
                } else {
                    clr[1] = (u8)(clr[1] - 0x7F);
                    uv.x = half - reflected.x / invAxis;
                    uv.y = half + reflected.z / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.x = uv.x + LoadFloat(kMana2Quarter);
                    uv.y = uv.y + half;
                }
                break;
            case 2:
                invAxis = LoadFloat(kMana2Two) * reflected.z;
                if (outVec->z >= LoadFloat(kMana2Zero)) {
                    clr[2] = (u8)(clr[2] + 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half - reflected.y / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.y = uv.y + LoadFloat(kMana2Quarter);
                } else {
                    clr[2] = (u8)(clr[2] - 0x7F);
                    uv.x = half + reflected.x / invAxis;
                    uv.y = half + reflected.y / invAxis;
                    uv.x = uv.x * LoadFloat(kMana2Quarter);
                    uv.y = uv.y * LoadFloat(kMana2Quarter);
                    uv.x = uv.x + half;
                    uv.y = uv.y + LoadFloat(kMana2Quarter);
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
void Mana2_BeforeDrawCallback(CChara::CModel*, void* param_2, void* param_3, float (*) [4], int)
{
    VMana2* work;
    CChara::CModel* model;
    CCharaPcs::CHandle* handle;
    CGObject* gObject;
    Mtx identityMtx;
    Mtx savedCameraMtx;
    Mtx lookAtMtx;
    Mtx44 projectionMtx;
    Mtx44 savedScreenMtx;
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
    GXTexObj* sourceTexObjs;
    GXTexObj* envTexObj0;
    s32 i;

    work = static_cast<VMana2*>(param_2);
    pppMana2Step* step = static_cast<pppMana2Step*>(param_3);
    baseParaboloidTexObjs = work->m_baseParaboloidTexObjs;
    if (step->m_type == 0) {
        return;
    }

    PSMTXIdentity(identityMtx);
    PSMTXCopy(CameraMatrix(), savedCameraMtx);
    PSMTX44Copy(CameraScreenMatrix(), savedScreenMtx);
    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &sceneTexObj, 0, 0, 0x80, 0x80, 0, GX_NEAR, GX_TF_RGBA8, 0);

    gObject = work->m_object;
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(reinterpret_cast<CCharaPcs::CHandle*>(handle));
    model->m_afterMeshDrawCallback = 0;
    model->SetDrawMeshDLCallback(0);

    if ((int)Game.m_currentSceneId == 7) {
        centerPos.z = LoadFloat(kMana2Zero);
        centerPos.y = LoadFloat(kMana2Zero);
        centerPos.x = LoadFloat(kMana2Zero);
    } else {
        centerPos.x = gObject->m_worldPosition.x;
        centerPos.y = gObject->m_worldPosition.y;
        centerPos.z = gObject->m_worldPosition.z;
    }
    centerPos.y = LoadFloat(kMana2ParaboloidCenterYOffset) + centerPos.y;

    depthTexSize = GXGetTexBufferSize(0x80, 0x80, (_GXTexFmt)6, GX_FALSE, 0);
    GXGetTexBufferSize(0x80, 0x80, (_GXTexFmt)4, GX_FALSE, 0);
    sourceTexObjs = work->m_sourceTexObjs;

    if (step->m_rippleLevel != 0) {
        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &depthTexObj, 0, 0, 0x80, 0x80, depthTexSize, GX_LINEAR,
                                   (_GXTexFmt)0x16, 1);
        GXSetViewport(LoadFloat(kMana2Zero), LoadFloat(kMana2Zero), LoadFloat(kMana2ParaboloidTexSize),
                      LoadFloat(kMana2ParaboloidTexSize), LoadFloat(kMana2Zero), LoadFloat(kMana2One));
        C_MTXPerspective(projectionMtx, LoadFloat(kMana2ParaboloidFov), LoadFloat(kMana2One),
                         LoadFloat(kMana2One), LoadFloat(kMana2ParaboloidFar));
        GXSetProjection(projectionMtx, (_GXProjectionType)0);

        for (i = 0; i < 6; i++) {
            cameraPos.x = centerPos.x;
            cameraPos.y = centerPos.y;
            cameraPos.z = centerPos.z;
            cameraUp.x = LoadFloat(kMana2Zero);
            cameraUp.y = LoadFloat(kMana2One);
            cameraUp.z = LoadFloat(kMana2Zero);

            switch (i) {
            case 0:
                cameraPos.x = centerPos.x + LoadFloat(kMana2One);
                break;
            case 1:
                cameraPos.x = centerPos.x - LoadFloat(kMana2One);
                break;
            case 2:
                cameraPos.y = centerPos.y + LoadFloat(kMana2One);
                cameraUp.x = LoadFloat(kMana2Zero);
                cameraUp.y = LoadFloat(kMana2Zero);
                cameraUp.z = LoadFloat(kMana2NegativeOne);
                break;
            case 3:
                cameraPos.y = centerPos.y - LoadFloat(kMana2One);
                cameraUp.x = LoadFloat(kMana2Zero);
                cameraUp.y = LoadFloat(kMana2Zero);
                cameraUp.z = LoadFloat(kMana2One);
                break;
            case 4:
                cameraPos.z = centerPos.z + LoadFloat(kMana2One);
                break;
            case 5:
                cameraPos.z = centerPos.z - LoadFloat(kMana2One);
                break;
            }

            C_MTXLookAt(lookAtMtx, (Point3d*)&centerPos, &cameraUp, (Point3d*)&cameraPos);
            Graphic.SetViewport();
            GXSetScissor(0, 0, 0x280, 0x1C0);
            gUtil.RenderTextureQuad(LoadFloat(kMana2Zero), LoadFloat(kMana2Zero), LoadFloat(kMana2ParaboloidTexSize),
                                    LoadFloat(kMana2ParaboloidTexSize), baseParaboloidTexObjs, 0, 0, 0,
                                    (_GXBlendFactor)4, (_GXBlendFactor)5);
            baseParaboloidTexObjs++;
        }

        PSMTXCopy(savedCameraMtx, CameraMatrix());
        Graphic.SetViewport();
        GXSetScissor(0, 0, 0x280, 0x1C0);
        GXSetZTexture((GXZTexOp)2, (_GXTexFmt)0x16, 0);
        GXSetColorUpdate(GX_FALSE);
        gUtil.BeginQuadEnv();
        GXSetZMode(GX_TRUE, (_GXCompare)7, GX_TRUE);
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

        quadMin.x = LoadFloat(kMana2Zero);
        quadMin.y = LoadFloat(kMana2Zero);
        quadMin.z = LoadFloat(kMana2Zero);
        quadMax.x = LoadFloat(kMana2ParaboloidTexSize);
        quadMax.y = LoadFloat(kMana2ParaboloidTexSize);
        quadMax.z = LoadFloat(kMana2Zero);
        quadColor.r = 0xFF;
        quadColor.g = 0xFF;
        quadColor.b = 0xFF;
        quadColor.a = 0;
        gUtil.RenderQuad(quadMin, quadMax, quadColor, 0, 0);
        gUtil.EndQuadEnv();
        GXSetZTexture((GXZTexOp)0, (_GXTexFmt)0x11, 0);
        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_TRUE);
        GXSetZCompLoc(GX_TRUE);
        gUtil.RenderTextureQuad(LoadFloat(kMana2Zero), LoadFloat(kMana2Zero), LoadFloat(kMana2ParaboloidTexSize),
                                LoadFloat(kMana2ParaboloidTexSize), &sceneTexObj, 0, 0, 0, (_GXBlendFactor)4,
                                (_GXBlendFactor)5);
        work->m_paraboloidReady = 1;
    }

    envTexObj0 = &work->m_envTexture0->m_texObj;
    if (step->m_rippleLevel == 0) {
        if (work->m_paraboloidReady == 0) {
            GXInitTexObj(work->m_generatedTexObj0, work->m_generatedTexture0, 0x80, 0x80, (_GXTexFmt)4, (_GXTexWrapMode)1,
                         (_GXTexWrapMode)1, GX_FALSE);
            GXInitTexObj(work->m_generatedTexObj1, work->m_generatedTexture1, 0x80, 0x80, (_GXTexFmt)4, (_GXTexWrapMode)1,
                         (_GXTexWrapMode)1, GX_FALSE);
            drawParaboloidMap(work->m_baseParaboloidTexObjs, work->m_generatedTexObj1, work->m_paraboloidMap,
                              work->m_paraboloidMapSize, envTexObj0, 1);
            drawParaboloidMap(work->m_baseParaboloidTexObjs, work->m_generatedTexObj0, work->m_paraboloidMap,
                              work->m_paraboloidMapSize, envTexObj0, 0);
            work->m_paraboloidReady = 1;
        }
    } else {
        GXInitTexObj(work->m_generatedTexObj0, work->m_generatedTexture0, 0x80, 0x80, (_GXTexFmt)4, (_GXTexWrapMode)0,
                     (_GXTexWrapMode)0, GX_FALSE);
        GXInitTexObj(work->m_generatedTexObj1, work->m_generatedTexture1, 0x80, 0x80, (_GXTexFmt)4, (_GXTexWrapMode)0,
                     (_GXTexWrapMode)0, GX_FALSE);
        drawParaboloidMap(sourceTexObjs, work->m_generatedTexObj1, work->m_paraboloidMap, work->m_paraboloidMapSize,
                          envTexObj0, 1);
        drawParaboloidMap(sourceTexObjs, work->m_generatedTexObj0, work->m_paraboloidMap, work->m_paraboloidMapSize,
                          envTexObj0, 0);
        Graphic.SetViewport();
        GXSetProjection(savedScreenMtx, (_GXProjectionType)0);
        PSMTXCopy(savedCameraMtx, CameraMatrix());
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(reinterpret_cast<CCharaPcs::CHandle*>(handle));
    model->m_afterMeshDrawCallback = (CChara::CModel::AfterMeshDrawCallback)Mana2_BeforeDrawCallback;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameMana2(pppMana2* pppMana2, pppMana2Step* param_2, _pppCtrlTable* param_3)
{
    u32 texBufferSize;
    VMana2* mana2Work;
    void* dstBuffer;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CGObject* gObject;
    s32 i;
    CChara::CMesh* mesh;
    CChara::CMesh::CRefData* meshData;
    u32 meshIndex;
    u32 vertexIndex;

    if (ppvUserStopPartF != 0) {
        return;
    }

    gObject = (CGObject*)ppvMng->m_lookTarget;
    mana2Work = GetMana2Work(pppMana2, param_3);
    Mana2SetupBlock* setupBlock = GetMana2SetupBlock(pppMana2, param_3);
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    param_2->m_rippleLevel = 0;
    mana2Work->m_step = param_2;
    if (Game.m_currentMapId == 0x21) {
        param_2->m_rippleLevel = 0;
    }

    SetMana2ModelCallbacks(model, mana2Work, param_2);

    MaterialMan.SetManaAlpha(setupBlock->m_color.rgba[3]);
    mana2Work->m_waterAlpha = MaterialMan.GetManaAlpha();

    if (reinterpret_cast<_pppPObject*>(pppMana2)->m_graphId == 0) {
    mana2Work->m_object = gObject;
    SetMana2ModelCallbacks(model, mana2Work, param_2);
    mana2Work->m_sourceTextures[0] = GetTextureFromRSD(param_2->m_sourceTextureIds[0], ppvEnv);
    mana2Work->m_sourceTextures[1] = GetTextureFromRSD(param_2->m_sourceTextureIds[1], ppvEnv);
    mana2Work->m_sourceTextures[2] = GetTextureFromRSD(param_2->m_sourceTextureIds[2], ppvEnv);
    mana2Work->m_sourceTextures[3] = GetTextureFromRSD(param_2->m_sourceTextureIds[3], ppvEnv);
    mana2Work->m_sourceTextures[4] = GetTextureFromRSD(param_2->m_sourceTextureIds[4], ppvEnv);
    mana2Work->m_sourceTextures[5] = GetTextureFromRSD(param_2->m_sourceTextureIds[5], ppvEnv);
    mana2Work->m_envTexture0 = GetTextureFromRSD(param_2->m_envTextureId0, ppvEnv);
    mana2Work->m_envTexture1 = GetTextureFromRSD(param_2->m_envTextureId1, ppvEnv);

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
    dstBuffer = mana2Work->m_baseParaboloidTexObjs;
    for (i = 0; i < 6; i++) {
        memcpy(dstBuffer, &mana2Work->m_sourceTextures[i]->m_texObj, sizeof(GXTexObj));
        dstBuffer = (void*)((char*)dstBuffer + 0x20);
    }

    mana2Work->m_envTexture0->m_format = 0;
    mana2Work->m_envTexture0->InitTexObj();
    mana2Work->m_envTexture1->m_format = 0;
    mana2Work->m_envTexture1->InitTexObj();

    if (mana2Work->m_paraboloidMap == 0) {
        mana2Work->m_paraboloidMap =
            pppMemAlloc(0xA5E8, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x211);
        genParaboloidMap(mana2Work->m_paraboloidMap, &mana2Work->m_paraboloidMapSize, 0x1E, GX_VTXFMT7);
    }

    mesh = model->m_meshes;
    if (mana2Work->m_positions == 0 && mana2Work->m_normals == 0 && mana2Work->m_waterHeightA == 0) {
        for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++) {
            meshData = mesh->m_data;
            u8 type = param_2->m_type;

            if (((type == 1) && strcmp(meshData->m_name, s_manaShapeObj5) == 0) ||
                ((type == 2) && strcmp(meshData->m_name, s_manaShapeObj3) == 0) ||
                ((type == 3) && strcmp(meshData->m_name, s_manaShapeObj1) == 0)) {
                if (mana2Work->m_meshReflectionVec == 0) {
                    mana2Work->m_meshReflectionVec =
                        static_cast<Vec*>(pppMemAlloc(meshData->m_vertexCount * sizeof(Vec), ppvEnv->m_stagePtr,
                                                      const_cast<char*>(s_pppMana2_cpp), 0x232));
                    Vec* reflectionVec = mana2Work->m_meshReflectionVec;
                    float zero = kMana2Zero;
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
                    u8* color = reinterpret_cast<u8*>(mana2Work->m_meshColors);
                    for (vertexIndex = 0; vertexIndex < meshData->m_vertexCount; vertexIndex++) {
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        color += 4;
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
                    copiedDisplayList = reinterpret_cast<void*>((reinterpret_cast<u32>(copiedDisplayList) + 0x1F) & 0xFFFFFFE0);
                    mana2Work->m_displayListCopies[dlIndex] = copiedDisplayList;
                    mana2Work->m_displayListSize = displayList->m_size;
                    memcpy(copiedDisplayList, displayList->m_data, displayList->m_size);
                    DCFlushRange(copiedDisplayList, displayList->m_size);
                    gUtil.ReWriteDisplayList(copiedDisplayList, displayList->m_size, 1);
                    displayList++;
                }
            }

            if (((type == 1) && strcmp(meshData->m_name, s_manaShapeObj4) == 0) ||
                ((type == 2) && strcmp(meshData->m_name, s_manaShapeObj2) == 0)) {
                mana2Work->m_positions = static_cast<Vec*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26A));
                mana2Work->m_normals = static_cast<Vec*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26B));
                mana2Work->m_colors = static_cast<GXColor*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26C));
                mana2Work->m_texCoord0 = static_cast<Vec2d*>(pppMemAlloc(0x908, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26D));
                mana2Work->m_texCoord1 = static_cast<Vec2d*>(pppMemAlloc(0x908, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26E));
                mana2Work->m_waterHeightA = static_cast<float*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x26F));
                mana2Work->m_waterHeightB = static_cast<float*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x270));
                mana2Work->m_indices = static_cast<u16*>(pppMemAlloc(0xC00, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x271));
                mana2Work->m_reflectionVec = static_cast<Vec*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppMana2_cpp), 0x272));

                float* waterHeightA = mana2Work->m_waterHeightA;
                float* waterHeightB = mana2Work->m_waterHeightB;
                float zero = kMana2Zero;
                for (vertexIndex = 0; vertexIndex < 0x121; vertexIndex++) {
                    waterHeightA[vertexIndex] = zero;
                    waterHeightB[vertexIndex] = zero;
                }

                CreateWaterMesh(mana2Work->m_positions, mana2Work->m_normals, mana2Work->m_texCoord0,
                                mana2Work->m_indices, param_2->m_waterScale);
            }

            mesh++;
        }
    }

    if ((param_2->m_type == 1 || param_2->m_type == 2) && mana2Work->m_waterHeightA != 0) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(mana2Work->m_waterHeightA) + 0x240) = param_2->m_rippleLevel;
    }
    }

    if (param_2->m_type != 0) {
        if (param_2->m_type == 1 || param_2->m_type == 2) {
            UpdateWaterMesh(mana2Work);
        }

        mesh = model->m_meshes;
        for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++) {
            meshData = mesh->m_data;
            u8 type = param_2->m_type;

            if (((type == 1) && strcmp(meshData->m_name, s_manaShapeObj5) == 0) ||
                ((type == 2) && strcmp(meshData->m_name, s_manaShapeObj3) == 0) ||
                ((type == 3) && strcmp(meshData->m_name, s_manaShapeObj1) == 0)) {
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
void pppDestructMana2(pppMana2* pppMana2, _pppCtrlTable* param_2)
{
    VMana2* work;
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CChara::CMesh* mesh;
    pppMana2Step* step;
    u32 i;
    u32 j;

    work = GetMana2Work(pppMana2, param_2);
    MaterialMan.ClearManaParaboloidTexObjs();

    if (work->m_generatedTexObj0 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexObj0);
        work->m_generatedTexObj0 = 0;
    }
    if (work->m_generatedTexObj1 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexObj1);
        work->m_generatedTexObj1 = 0;
    }
    if (work->m_generatedTexture0 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexture0);
        work->m_generatedTexture0 = 0;
    }
    if (work->m_generatedTexture1 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexture1);
        work->m_generatedTexture1 = 0;
    }
    if (work->m_baseParaboloidTexObjs != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_baseParaboloidTexObjs);
        work->m_baseParaboloidTexObjs = 0;
    }
    if (work->m_positions != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_positions);
        work->m_positions = 0;
    }
    if (work->m_normals != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_normals);
        work->m_normals = 0;
    }
    if (work->m_waterHeightA != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_waterHeightA);
        work->m_waterHeightA = 0;
    }
    if (work->m_waterHeightB != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_waterHeightB);
        work->m_waterHeightB = 0;
    }
    if (work->m_indices != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_indices);
        work->m_indices = 0;
    }
    if (work->m_texCoord0 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_texCoord0);
        work->m_texCoord0 = 0;
    }
    if (work->m_texCoord1 != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_texCoord1);
        work->m_texCoord1 = 0;
    }
    if (work->m_sourceTexObjs != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_sourceTexObjs);
        work->m_sourceTexObjs = 0;
    }
    if (work->m_paraboloidMap != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_paraboloidMap);
        work->m_paraboloidMap = 0;
    }
    if (work->m_colors != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_colors);
        work->m_colors = 0;
    }
    if (work->m_reflectionVec != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_reflectionVec);
        work->m_reflectionVec = 0;
    }
    if (work->m_meshReflectionVec != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshReflectionVec);
        work->m_meshReflectionVec = 0;
    }
    if (work->m_meshColors != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshColors);
        work->m_meshColors = 0;
    }
    if (work->m_meshTexCoords != NULL) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshTexCoords);
        work->m_meshTexCoords = 0;
    }
    gObject = (CGObject*)ppvMng->m_lookTarget;
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    model->m_afterMeshDrawCallback = 0;
    model->SetDrawMeshDLCallback(0);
    mesh = model->m_meshes;
    step = work->m_step;
    for (i = 0; i < model->m_data->m_meshCount; i++, mesh++) {
        u8 stepType = step->m_type;
        CChara::CMesh::CRefData* meshData = mesh->m_data;

        if (stepType == 1) {
            if (strcmp(meshData->m_name, s_manaShapeObj5) == 0) {
                for (j = 0; j < meshData->m_displayListCount; j++) {
                    if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                        pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != NULL) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 2) {
            if (strcmp(meshData->m_name, s_manaShapeObj3) == 0) {
                for (j = 0; j < meshData->m_displayListCount; j++) {
                    if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                        pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != NULL) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 3 && strcmp(meshData->m_name, s_manaShapeObj1) == 0) {
            for (j = 0; j < meshData->m_displayListCount; j++) {
                if (work->m_displayListCopies != NULL && work->m_displayListCopies[j] != NULL) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                    work->m_displayListCopies[j] = 0;
                }
            }
            if (work->m_displayListCopies != NULL) {
                pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
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
void pppConstructMana2(pppMana2* pppMana2, _pppCtrlTable* param_2)
{
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    VMana2* work;

    work = GetMana2Work(pppMana2, param_2);
    gObject = (CGObject*)ppvMng->m_lookTarget;
    gObject->m_stepSlopeLimit = LoadFloat(kMana2StepSlopeLimit);

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
void Mana2_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    VMana2* mana2 = (VMana2*)work;
    pppMana2Step* stepData = static_cast<pppMana2Step*>(step);
    int type = stepData->m_type;
    CChara::CMesh::CRefData* meshData = model->m_meshes[partIndex].m_data;
    const char* shape = meshData->m_name;
    CChara::CMesh::CDisplayList* displayList = &meshData->m_displayLists[dlIndex];
    bool draw = false;

    switch (type) {
    case 0:
        if (strcmp(shape, s_manaShapeObj) == 0) {
            draw = true;
        }
        break;
    case 1:
        if (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj5) == 0) {
            draw = true;
        }
        break;
    case 2:
        if (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj3) == 0) {
            draw = true;
        }
        break;
    case 3:
        if (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj1) == 0) {
            draw = true;
        }
        break;
    }

    int waterCmp = strcmp(shape, s_manaShapeObj4);
    if ((waterCmp == 0 && stepData->m_type == 1) || (strcmp(shape, s_manaShapeObj2) == 0 && stepData->m_type == 2)) {
        Mtx cameraMtx;
        Mtx rotMtx;
        Mtx posMtx;
        Vec offset;

        PSMTXCopy(CameraMatrix(), cameraMtx);
        PSMTXRotRad(rotMtx, 'z', LoadFloat(kMana2WaterRotZRad));
        float x = mtx[0][3];
        float y = mtx[1][3];
        float z = mtx[2][3];
        mtx[0][3] = LoadFloat(kMana2Zero);
        mtx[1][3] = LoadFloat(kMana2Zero);
        mtx[2][3] = LoadFloat(kMana2Zero);
        PSMTXConcat(mtx, rotMtx, mtx);

        offset.z = LoadFloat(kMana2Zero);
        offset.x = LoadFloat(kMana2Zero);
        offset.y = stepData->m_waterScale;
        PSMTXMultVec(mtx, &offset, &offset);

        mtx[0][3] = x;
        mtx[1][3] = y - offset.y;
        mtx[2][3] = z;

        PSMTXConcat(cameraMtx, mtx, posMtx);
        GXLoadPosMtxImm(posMtx, 0);
        PSMTXCopy(mtx, mana2->m_waterMtx);
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        RenderWaterMesh(mana2);
        GXSetCullMode((GXCullMode)1);
    }

    if (draw) {
        if (strcmp(shape, s_manaShapeObj) != 0) {
            PSMTXCopy(mtx, mana2->m_reflectionMtx);
            if (mana2->m_paraboloidReady != 0) {
                mana2->m_runtimeColor.r = meshData->m_colors[0];
                mana2->m_runtimeColor.g = meshData->m_colors[1];
                mana2->m_runtimeColor.b = meshData->m_colors[2];
                mana2->m_runtimeColor.a = 0x80;
                DCFlushRange(&mana2->m_runtimeColor, 4);
                GXSetArray((GXAttr)0xB, mana2->m_meshColors, 4);
                GXSetArray((GXAttr)0xD, mana2->m_meshTexCoords, 4);
                MaterialMan.SetManaReflectionEnv(mana2->m_meshReflectionVec, mana2->m_baseParaboloidTexObjs, 0x2ACE0F);
                GXSetCullMode((GXCullMode)1);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
                GXCallDisplayList(mana2->m_displayListCopies[dlIndex], displayList->m_size);
            }
        } else {
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
            MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
            GXCallDisplayList(displayList->m_data, displayList->m_size);
        }
    }
}
