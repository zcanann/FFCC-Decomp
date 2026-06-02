#include "ffcc/pppMana2.h"
#include "ffcc/graphic.h"
#include "ffcc/render_buffers.h"
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

struct Vec2d {
    float x;
    float y;
};

struct VMana2 {
    CGObject* m_object;
    void* m_manager;
    CTexture* m_sourceTextures[6];
    GXTexObj* m_baseParaboloidTexObjs;
    void* m_paraboloidMap;
    GXTexObj* m_generatedTexObj0;
    GXTexObj* m_generatedTexObj1;
    void* m_generatedTexture0;
    void* m_generatedTexture1;
    GXColor m_runtimeColor;
    Vec* m_positions;
    Vec* m_normals;
    Vec* m_reflectionVec;
    float* m_waterHeightA;
    float* m_waterHeightB;
    u16* m_indices;
    Vec2d* m_texCoord0;
    Vec2d* m_texCoord1;
    GXColor* m_colors;
    void** m_displayListCopies;
    Vec* m_meshReflectionVec;
    GXColor* m_meshColors;
    S16Vec2d* m_meshTexCoords;
    pppMana2UnkB* m_step;
    GXTexObj* m_sourceTexObjs;
    CTexture* m_envTexture0;
    CTexture* m_envTexture1;
    Mtx m_waterMtx;
    Mtx m_reflectionMtx;
    u8 m_waterAlpha;
    u8 _padE1[3];
    u32 m_paraboloidMapSize;
    u32 m_displayListSize;
    u8 m_paraboloidReady;
};

struct pppMana2UnkB {
    u8 _pad00[0x4];
    s32 m_sourceTextureIds[6];
    u8 m_type;
    u8 _pad1D[0x7];
    s32 m_envTextureId0;
    s32 m_envTextureId1;
    u8 _pad2C[0x4];
    float m_waterScale;
    u8 _pad34[0x4];
    u8 m_rippleLevel;
};

STATIC_ASSERT(offsetof(VMana2, m_runtimeColor) == 0x38);
STATIC_ASSERT(offsetof(VMana2, m_positions) == 0x3C);
STATIC_ASSERT(offsetof(VMana2, m_indices) == 0x50);
STATIC_ASSERT(offsetof(VMana2, m_displayListCopies) == 0x60);
STATIC_ASSERT(offsetof(VMana2, m_step) == 0x70);
STATIC_ASSERT(offsetof(VMana2, m_waterMtx) == 0x80);
STATIC_ASSERT(offsetof(VMana2, m_reflectionMtx) == 0xB0);
STATIC_ASSERT(offsetof(VMana2, m_waterAlpha) == 0xE0);
STATIC_ASSERT(offsetof(VMana2, m_paraboloidReady) == 0xEC);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_sourceTextureIds) == 0x04);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_type) == 0x1C);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_envTextureId0) == 0x24);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_envTextureId1) == 0x28);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_waterScale) == 0x30);
STATIC_ASSERT(offsetof(pppMana2UnkB, m_rippleLevel) == 0x38);

extern "C" const char s_Render_Mana2___801dc4d0[] = "Render Mana2!!";
extern "C" const char s_pppMana2_cpp[] = "pppMana2.cpp";
extern const float FLOAT_80331898 = 0.0f;
extern const float FLOAT_8033189c = -1.0f;
extern const float FLOAT_803318a0 = 1.0f;
extern const float FLOAT_803318a4 = 0.5f;
extern const float FLOAT_803318A8 = 0.0625f;
extern const double DOUBLE_803318B0 = 4503601774854144.0;
extern const float FLOAT_803318b8 = 2.0f;
extern const float FLOAT_803318bc = 0.25f;
extern const float FLOAT_803318c0 = 0.75f;
extern const float FLOAT_803318c4 = 5.0f;
extern const float FLOAT_803318c8 = 128.0f;
extern const float FLOAT_803318cc = 90.0f;
extern const float FLOAT_803318d0 = 10000.0f;
extern const char s_manaShapeObj5[] = "obj5";
extern const char s_manaShapeObj3[] = "obj3";
extern const char s_manaShapeObj1[] = "obj1";
extern const char s_manaShapeObj4[] = "obj4";
extern const char s_manaShapeObj2[] = "obj2";
extern const float FLOAT_803318fc = 0.99999f;
extern const char s_manaShapeObj[] = "obj";
extern const float FLOAT_80331904 = -1.5707964f;
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

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

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

static inline void SetMana2ModelCallbacks(CChara::CModel* model, void* work, pppMana2UnkB* step)
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

    transformedCameraPos.x = LoadFloat(FLOAT_80331898);
    transformedCameraPos.y = LoadFloat(FLOAT_80331898);
    transformedCameraPos.z = LoadFloat(FLOAT_80331898);

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, LoadFloat(FLOAT_8033189c));
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    colorBytes = (unsigned char*)color;
    texCoordFloat = (float*)texCoord;
    reflectionIt = reflectionVec;
    normalIt = normals;
    zero = LoadFloat(FLOAT_80331898);
    half = LoadFloat(FLOAT_803318a4);

    for (i = 0; i < count; i++) {
        PSVECSubtract(positions, &transformedCameraPos, &reflected);
        C_VECReflect(&reflected, normalIt, reflectionIt);
        PSMTXMultVec(matrixNoTranslate, reflectionIt, reflectionIt);
        PSVECNormalize(reflectionIt, reflectionIt);

        if (reflectionIt->z >= zero) {
            float denomBase;

            colorBytes[0] = 0x80;
            colorBytes[1] = 0x80;
            colorBytes[2] = 0xff;
            colorBytes[3] = 0xbc;
            denomBase = LoadFloat(FLOAT_803318a0);
            *texCoordFloat = -reflectionIt->x / (denomBase + reflectionIt->z);
            texCoordFloat[1] = -reflectionIt->y / (denomBase + reflectionIt->z);
        } else {
            float denomBase;

            colorBytes[0] = 0x80;
            colorBytes[1] = 0xff;
            colorBytes[2] = 0x80;
            colorBytes[3] = 0x7f;
            denomBase = LoadFloat(FLOAT_803318a0);
            *texCoordFloat = -reflectionIt->x / (denomBase - reflectionIt->z);
            texCoordFloat[1] = -reflectionIt->y / (denomBase - reflectionIt->z);
        }

        positions++;
        reflectionIt++;
        normalIt++;
        colorBytes += 4;
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

    positions = mana2->m_positions;
    normals = mana2->m_normals;
    indices = mana2->m_indices;

    float zero = FLOAT_80331898;
    for (s32 i = 0; i < 0x121; i++) {
        normals[i].z = zero;
        normals[i].y = zero;
        normals[i].x = zero;
    }

    s32 i = 0;
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
    currentScale = FLOAT_80331898;
    neighborScale = FLOAT_803318a4;
    do {
        int col = 1;
        int batch = 3;
        do {
            int index = rowBase + col;
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
            col += 5;
            batch--;
        } while (batch != 0);
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

    normalY = LoadFloat(FLOAT_803318a0);
    zero = LoadFloat(FLOAT_80331898);
    rowCount = 0;
    uvStep = LoadFloat(FLOAT_803318A8);
    radius = param_5 * LoadFloat(FLOAT_803318a4);
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
            int nextNextIndex = quadIndex + 2;
            int lowerNextNextIndex = quadIndex + 0x13;

            param_4[indexOffset++] = quadIndex;
            param_4[indexOffset++] = nextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = lowerIndex;
            param_4[indexOffset++] = quadIndex;
            param_4[indexOffset++] = nextIndex;
            param_4[indexOffset++] = nextNextIndex;
            param_4[indexOffset++] = lowerNextNextIndex;
            param_4[indexOffset++] = lowerNextNextIndex;
            param_4[indexOffset++] = lowerNextIndex;
            param_4[indexOffset++] = nextIndex;
            quadIndex = quadIndex + 2;
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
    u16* dl = (u16*)displayList;
    u16* dlEnd;

    cameraPos.x = CameraWorldX();
    cameraPos.y = CameraWorldY();
    cameraPos.z = CameraWorldZ();

    PSMTXCopy(matrix, nodeMtx);
    nodeOffset.x = node->m_mtx[0][3];
    nodeOffset.y = node->m_mtx[1][3];
    nodeOffset.z = node->m_mtx[2][3];

    matrixPos.x = nodeMtx[0][3];
    matrixPos.y = nodeMtx[1][3];
    matrixPos.z = nodeMtx[2][3];
    PSVECAdd(&nodeOffset, &matrixPos, &worldPos);

    PSMTXCopy(node->m_mtx, matrix);
    matrix[0][3] = worldPos.x;
    matrix[1][3] = worldPos.y;
    matrix[2][3] = worldPos.z;

    PSMTXCopy(matrix, nodeRotMtx);
    nodeRotMtx[0][3] = LoadFloat(FLOAT_80331898);
    nodeRotMtx[1][3] = LoadFloat(FLOAT_80331898);
    nodeRotMtx[2][3] = LoadFloat(FLOAT_80331898);

    PSMTXCopy(CameraMatrix(), cameraMtx);
    PSMTXConcat(cameraMtx, matrix, cameraModelMtx);

    const double half = (double)LoadFloat(FLOAT_803318a4);

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
                invAxis = LoadFloat(FLOAT_803318b8) * reflected.x;
                if (outVec->x >= LoadFloat(FLOAT_80331898)) {
                    clr[0] = (u8)(clr[0] + 0x7F);
                    uv.x = (float)((half - (double)(reflected.z / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
                    uv.y = (float)((half - (double)(reflected.y / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
                } else {
                    clr[0] = (u8)(clr[0] - 0x7F);
                    uv.x = (float)((half - (double)(reflected.z / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318c0));
                    uv.y = (float)((half + (double)(reflected.y / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
                }
                break;
            case 1:
                invAxis = LoadFloat(FLOAT_803318b8) * reflected.y;
                if (outVec->y >= LoadFloat(FLOAT_80331898)) {
                    clr[1] = (u8)(clr[1] + 0x7F);
                    uv.y = (float)((half + (double)(reflected.z / invAxis)) * (double)LoadFloat(FLOAT_803318bc));
                    uv.x =
                        (float)((double)((float)(half + (double)(reflected.x / invAxis)) * LoadFloat(FLOAT_803318bc)) + half);
                } else {
                    clr[1] = (u8)(clr[1] - 0x7F);
                    uv.x = (float)((half - (double)(reflected.x / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
                    uv.y =
                        (float)((double)((float)(half + (double)(reflected.z / invAxis)) * LoadFloat(FLOAT_803318bc)) + half);
                }
                break;
            case 2:
                invAxis = LoadFloat(FLOAT_803318b8) * reflected.z;
                if (outVec->z >= LoadFloat(FLOAT_80331898)) {
                    clr[2] = (u8)(clr[2] + 0x7F);
                    uv.x = (float)((half + (double)(reflected.x / invAxis)) * (double)LoadFloat(FLOAT_803318bc));
                    uv.y = (float)((half - (double)(reflected.y / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
                } else {
                    clr[2] = (u8)(clr[2] - 0x7F);
                    uv.x =
                        (float)((double)((float)(half + (double)(reflected.x / invAxis)) * LoadFloat(FLOAT_803318bc)) + half);
                    uv.y = (float)((half + (double)(reflected.y / invAxis)) * (double)LoadFloat(FLOAT_803318bc) +
                                   (double)LoadFloat(FLOAT_803318bc));
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
    baseParaboloidTexObjs = work->m_baseParaboloidTexObjs;
    if (*(u8*)((char*)param_3 + 0x1C) == 0) {
        return;
    }

    PSMTXIdentity(identityMtx);
    PSMTXCopy(CameraMatrix(), savedCameraMtx);
    PSMTX44Copy(CameraScreenMatrix(), savedScreenMtx);
    Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &sceneTexObj, 0, 0, 0x80, 0x80, 0, GX_NEAR, GX_TF_RGBA8, 0);

    gObject = work->m_object;
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(reinterpret_cast<CCharaPcs::CHandle*>(handle));
    model->m_afterMeshDrawCallback = 0;
    model->SetDrawMeshDLCallback(0);

    if ((int)Game.m_currentSceneId == 7) {
        centerPos.x = LoadFloat(FLOAT_80331898);
        centerPos.y = LoadFloat(FLOAT_80331898);
        centerPos.z = LoadFloat(FLOAT_80331898);
    } else {
        centerPos.x = gObject->m_worldPosition.x;
        centerPos.y = gObject->m_worldPosition.y;
        centerPos.z = gObject->m_worldPosition.z;
    }
    centerPos.y += LoadFloat(FLOAT_803318c4);

    depthTexSize = GXGetTexBufferSize(0x80, 0x80, (_GXTexFmt)6, GX_FALSE, 0);
    GXGetTexBufferSize(0x80, 0x80, (_GXTexFmt)4, GX_FALSE, 0);
    sourceTexObjs = work->m_sourceTexObjs;

    if (*(u8*)((char*)param_3 + 0x38) != 0) {
        Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &depthTexObj, 0, 0, 0x80, 0x80, depthTexSize, GX_LINEAR,
                                   (_GXTexFmt)0x16, 1);
        GXSetViewport(LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_803318c8),
                      LoadFloat(FLOAT_803318c8), LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_803318a0));
        C_MTXPerspective(projectionMtx, LoadFloat(FLOAT_803318cc), LoadFloat(FLOAT_803318a0),
                         LoadFloat(FLOAT_803318a0), LoadFloat(FLOAT_803318d0));
        GXSetProjection(projectionMtx, (_GXProjectionType)0);

        for (i = 0; i < 6; i++) {
            cameraPos.x = centerPos.x;
            cameraPos.y = centerPos.y;
            cameraPos.z = centerPos.z;
            cameraUp.y = LoadFloat(FLOAT_803318a0);
            cameraUp.z = LoadFloat(FLOAT_80331898);

            if (i == 3) {
                cameraPos.y = centerPos.y - LoadFloat(FLOAT_803318a0);
                cameraUp.y = LoadFloat(FLOAT_80331898);
                cameraUp.z = LoadFloat(FLOAT_803318a0);
            } else if (i < 3) {
                if (i == 1) {
                    cameraPos.x = centerPos.x - LoadFloat(FLOAT_803318a0);
                } else if (i < 1) {
                    cameraPos.x = centerPos.x + LoadFloat(FLOAT_803318a0);
                } else {
                    cameraPos.y = centerPos.y + LoadFloat(FLOAT_803318a0);
                    cameraUp.y = LoadFloat(FLOAT_80331898);
                    cameraUp.z = LoadFloat(FLOAT_8033189c);
                }
            } else if (i == 5) {
                cameraPos.z = centerPos.z - LoadFloat(FLOAT_803318a0);
            } else {
                cameraPos.z = centerPos.z + LoadFloat(FLOAT_803318a0);
            }

            cameraUp.x = LoadFloat(FLOAT_80331898);
            C_MTXLookAt(lookAtMtx, (Point3d*)&centerPos, &cameraUp, (Point3d*)&cameraPos);
            Graphic.SetViewport();
            GXSetScissor(0, 0, 0x280, 0x1C0);
            gUtil.RenderTextureQuad(LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_803318c8),
                                    LoadFloat(FLOAT_803318c8), baseParaboloidTexObjs, 0, 0, 0,
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

        quadMin.x = LoadFloat(FLOAT_80331898);
        quadMin.y = LoadFloat(FLOAT_80331898);
        quadMin.z = LoadFloat(FLOAT_80331898);
        quadMax.x = LoadFloat(FLOAT_803318c8);
        quadMax.y = LoadFloat(FLOAT_803318c8);
        quadMax.z = LoadFloat(FLOAT_80331898);
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
        gUtil.RenderTextureQuad(LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_80331898), LoadFloat(FLOAT_803318c8),
                                LoadFloat(FLOAT_803318c8), &sceneTexObj, 0, 0, 0, (_GXBlendFactor)4,
                                (_GXBlendFactor)5);
        work->m_paraboloidReady = 1;
    }

    envTexObj0 = &work->m_envTexture0->m_texObj;
    if (*(u8*)((char*)param_3 + 0x38) == 0) {
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
void pppRenderMana2(pppMana2*, pppMana2UnkB*, pppMana2UnkC*)
{
    Graphic.Printf(const_cast<char*>(s_Render_Mana2___801dc4d0));
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
void pppFrameMana2(pppMana2* pppMana2, pppMana2UnkB* param_2, pppMana2UnkC* param_3)
{
    u32 texBufferSize;
    VMana2* mana2Work;
    void* dstBuffer;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CGObject* gObject;
    s32 i;
    s32 setupOffset;
    u8* setup;
    CChara::CMesh* mesh;
    CChara::CMesh::CRefData* meshData;
    u32 meshIndex;
    u32 vertexIndex;

    if (gPppCalcDisabled != 0) {
        return;
    }

    gObject = (CGObject*)ppvMng->m_lookTarget;
    mana2Work = reinterpret_cast<VMana2*>((char*)pppMana2 + 0x80 + param_3->m_serializedDataOffsets[2]);
    setupOffset = param_3->m_serializedDataOffsets[1];
    setup = (u8*)pppMana2 + 0x80 + setupOffset;
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

    mana2Work->m_waterAlpha = setup[0xB];

    if (*(s32*)pppMana2 != 0) {
        return;
    }

    mana2Work->m_object = gObject;
    SetMana2ModelCallbacks(model, mana2Work, param_2);
    mana2Work->m_sourceTextures[0] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[0], ppvEnv));
    mana2Work->m_sourceTextures[1] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[1], ppvEnv));
    mana2Work->m_sourceTextures[2] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[2], ppvEnv));
    mana2Work->m_sourceTextures[3] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[3], ppvEnv));
    mana2Work->m_sourceTextures[4] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[4], ppvEnv));
    mana2Work->m_sourceTextures[5] = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_sourceTextureIds[5], ppvEnv));
    mana2Work->m_envTexture0 = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_envTextureId0, ppvEnv));
    mana2Work->m_envTexture1 = reinterpret_cast<CTexture*>(GetTextureFromRSD(param_2->m_envTextureId1, ppvEnv));

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
                    float zero = FLOAT_80331898;
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
                float zero = FLOAT_80331898;
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
void pppDestructMana2(pppMana2* pppMana2, pppMana2UnkC* param_2)
{
    VMana2* work;
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CChara::CMesh* mesh;
    pppMana2UnkB* step;
    u32 i;
    u32 j;

    work = reinterpret_cast<VMana2*>((char*)pppMana2 + 0x80 + param_2->m_serializedDataOffsets[2]);
    *(u32*)(MaterialManRaw() + 0xD0) = 0;
    *(u32*)(MaterialManRaw() + 0xDC) = 0;

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
void pppConstructMana2(pppMana2* pppMana2, pppMana2UnkC* param_2)
{
    CGObject* gObject;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    VMana2* work;
    s32 workOffset;

    workOffset = param_2->m_serializedDataOffsets[2];
    work = reinterpret_cast<VMana2*>((char*)pppMana2 + 0x80 + workOffset);
    gObject = (CGObject*)ppvMng->m_lookTarget;
    gObject->m_stepSlopeLimit = LoadFloat(FLOAT_803318fc);

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
    int type = *(u8*)((char*)step + 0x1C);
    CChara::CMesh::CRefData* meshData = model->m_meshes[partIndex].m_data;
    const char* shape = meshData->m_name;
    u32* dlEntry = (u32*)(meshData->m_displayLists + dlIndex);
    int draw = 0;

    if (type == 2) {
        if (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj3) == 0) {
            draw = 1;
        }
    } else if (type < 2) {
        if (type == 0) {
            if (strcmp(shape, s_manaShapeObj) == 0) {
                draw = 1;
            }
        } else if (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj5) == 0) {
            draw = 1;
        }
    } else if (type < 4 && (strcmp(shape, s_manaShapeObj) == 0 || strcmp(shape, s_manaShapeObj1) == 0)) {
        draw = 1;
    }

    int waterCmp = strcmp(shape, s_manaShapeObj4);
    if ((waterCmp == 0 && *(u8*)((char*)step + 0x1C) == 1) ||
        (strcmp(shape, s_manaShapeObj2) == 0 && *(u8*)((char*)step + 0x1C) == 2)) {
        Mtx cameraMtx;
        Mtx rotMtx;
        Mtx posMtx;
        Vec offset;
        float x = mtx[0][3];
        float y = mtx[1][3];
        float z = mtx[2][3];

        PSMTXCopy(CameraMatrix(), cameraMtx);
        PSMTXRotRad(rotMtx, 'z', LoadFloat(FLOAT_80331904));
        mtx[0][3] = LoadFloat(FLOAT_80331898);
        mtx[1][3] = LoadFloat(FLOAT_80331898);
        mtx[2][3] = LoadFloat(FLOAT_80331898);
        PSMTXConcat(mtx, rotMtx, mtx);

        offset.x = LoadFloat(FLOAT_80331898);
        offset.y = *(float*)((char*)step + 0x30);
        offset.z = LoadFloat(FLOAT_80331898);
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
                *(u32*)(MaterialManRaw() + 0x08) = (u32)mana2->m_meshReflectionVec;
                *(u32*)(MaterialManRaw() + 0x44) = 0xFFFFFFFF;
                *(u8*)(MaterialManRaw() + 0x4C) = 0xFF;
                *(u32*)(MaterialManRaw() + 0x11C) = 0;
                *(u32*)(MaterialManRaw() + 0x120) = 0x1E;
                *(u32*)(MaterialManRaw() + 0x124) = 0;
                *(u8*)(MaterialManRaw() + 0x205) = 0xFF;
                *(u8*)(MaterialManRaw() + 0x206) = 0xFF;
                *(u32*)(MaterialManRaw() + 0x58) = 0;
                *(u32*)(MaterialManRaw() + 0x5C) = 0;
                *(u8*)(MaterialManRaw() + 0x208) = 0;
                *(u32*)(MaterialManRaw() + 0x48) = 0x2ACE0F;
                *(u32*)(MaterialManRaw() + 0x128) = 0;
                *(u32*)(MaterialManRaw() + 0x12C) = 0x1E;
                *(u32*)(MaterialManRaw() + 0x130) = 0;
                *(u32*)(MaterialManRaw() + 0x40) = 0x2ACE0F;
                *(u32*)(MaterialManRaw() + 0xD0) = (u32)mana2->m_baseParaboloidTexObjs;
                GXSetCullMode((GXCullMode)1);
                GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
                MaterialMan.SetMaterial(model->m_data->m_materialSet, *(u16*)((char*)dlEntry + 8), 0, (_GXTevScale)0);
                GXCallDisplayList(mana2->m_displayListCopies[dlIndex], *dlEntry);
            }
        } else {
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
            MaterialMan.SetMaterial(model->m_data->m_materialSet, *(u16*)((char*)dlEntry + 8), 0, (_GXTevScale)0);
            GXCallDisplayList((void*)dlEntry[1], dlEntry[0]);
        }
    }
}
