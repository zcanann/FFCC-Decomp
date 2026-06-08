#include "ffcc/pppYmMana.h"
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

#include <string.h>
#include <dolphin/os/OSCache.h>
#include "ffcc/ppp_linkage.h"



extern const float kPppYmMoveParabolaNegHalfPi = -1.5707964f;
extern const float kPppYmMoveParabolaZero = 0.0f;
extern const char s_ymManaRuin2Name[] = "ruin_2";
extern const float kYmManaOne = 1.0f;
static const float kYmManaReflectionDenomBias = 1.0f;
extern const float kYmManaHalf = 0.5f;

extern const float kYmManaReflectionUvWarp = 2.0f;
extern const float kYmManaReflectionUvWarpScale = 0.015625f;
extern const float kYmManaNegOne = -1.0f;
extern const float kYmManaWaterUvStep = 0.0625f;
extern const double kYmManaS32FloatBias = 4503601774854144.0;
extern const float kYmManaCaptureHeightOffset = 5.0f;
extern const float kYmManaCaptureFovY = 90.0f;
extern const float kYmManaCaptureFarClip = 100000.0f;
extern const float kYmManaCaptureTextureSize = 128.0f;
static const char s_ymManaShapeObj5[] = "obj5";
static const char s_ymManaShapeObj3[] = "obj3";
static const char s_ymManaShapeObj1[] = "obj1";
static const char s_ymManaShapeObj4[] = "obj4";
static const char s_ymManaShapeObj2[] = "obj2";
extern const double kYmManaU32FloatBias = 4503599627370496.0;
extern const float kYmManaSlopeLimit = 0.99999f;
static const char s_ymManaShapeObj[] = "obj";
extern const float kYmManaLookAtAlphaScale[2] = {255.0f, 0.0f};

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

static const char s_pppYmMana_cpp[] = "pppYmMana.cpp";

STATIC_ASSERT(sizeof(YmManaDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(YmManaDataOffsets, m_setupOffset) == 0x4);
STATIC_ASSERT(offsetof(YmManaDataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(offsetof(VYmMana, m_runtimeColor) == 0x38);
STATIC_ASSERT(offsetof(VYmMana, m_displayListCopies) == 0x60);
STATIC_ASSERT(offsetof(VYmMana, m_meshReflectionVec) == 0x64);
STATIC_ASSERT(offsetof(VYmMana, m_meshColors) == 0x68);
STATIC_ASSERT(offsetof(VYmMana, m_meshTexCoords0) == 0x6C);
STATIC_ASSERT(offsetof(VYmMana, m_meshTexCoords1) == 0x70);
STATIC_ASSERT(offsetof(VYmMana, m_step) == 0x74);
STATIC_ASSERT(offsetof(VYmMana, m_captureTexObjs) == 0x78);
STATIC_ASSERT(offsetof(VYmMana, m_envTexture1) == 0x80);
STATIC_ASSERT(offsetof(VYmMana, m_waterMtx) == 0x88);
STATIC_ASSERT(offsetof(VYmMana, m_reflectionMtx) == 0xB8);
STATIC_ASSERT(offsetof(VYmMana, m_manaAlpha) == 0xE8);
STATIC_ASSERT(offsetof(VYmMana, m_paraboloidReady) == 0xF4);
STATIC_ASSERT(offsetof(VYmMana, m_attachedObject) == 0xF8);
STATIC_ASSERT(offsetof(VYmMana, m_shadowColor) == 0xFC);
STATIC_ASSERT(offsetof(VYmMana, m_baseColor) == 0x100);
STATIC_ASSERT(offsetof(pppYmManaStep, m_sourceTextureId2) == 0x04);
STATIC_ASSERT(offsetof(pppYmManaStep, m_type) == 0x1C);
STATIC_ASSERT(offsetof(pppYmManaStep, m_envTextureId0) == 0x24);
STATIC_ASSERT(offsetof(pppYmManaStep, m_envTextureId1) == 0x28);
STATIC_ASSERT(offsetof(pppYmManaStep, m_waterScale) == 0x2C);
STATIC_ASSERT(offsetof(pppYmManaStep, m_waterOffset) == 0x30);
STATIC_ASSERT(offsetof(pppYmManaStep, m_rippleLevel) == 0x34);
STATIC_ASSERT(offsetof(pppYmManaStep, m_map21Flag) == 0x38);
STATIC_ASSERT(offsetof(pppYmManaStep, m_baseColor) == 0x3C);

static inline YmManaDataOffsets* GetYmManaDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<YmManaDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline void ClearManaModelCallbacks(CChara::CModel* model)
{
    model->SetCallbackContext(0, 0);
    model->m_afterMeshDrawCallback = 0;
    model->SetDrawMeshDLCallback(0);
}

static inline void SetManaModelCallbacks(CChara::CModel* model, void* work, pppYmManaStep* step)
{
    model->SetCallbackContext(work, step);
    model->m_afterMeshDrawCallback = (CChara::CModel::AfterMeshDrawCallback)Mana_BeforeDrawCallback;
    model->SetDrawMeshDLCallback(Mana_DrawMeshDLCallback);
}

static int CreateWaterMesh(Vec* positionsInOut, Vec* normalsOut, Vec2d* uvOut, unsigned short* indicesOut, float size);
static int UpdateWaterMesh(VYmMana* mana);
static int RenderWaterMesh(VYmMana* mana);
static void CalculateNormal(VYmMana* mana);
static void CalcWaterReflectionVector(
    Vec* reflectionVec, Vec* positions, Vec* normals, long count, Vec waterOrigin, float (*matrix)[4], _GXColor* color,
    Vec2d* texCoord);

/*
 * --INFO--
 * PAL Address: 0x800d7ff8
 * PAL Size: 1816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetEnvMap(PYmMana*, VYmMana* vYmMana)
{
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)4, (GXBool)0, (GXColorSrc)0, (GXColorSrc)1, 0, (GXDiffuseFn)0, (GXAttnFn)2);
    GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)0xf);

    GXTexObj* texObjA = vYmMana->m_generatedTexObj1;
    GXTexObj* texObjB = vYmMana->m_generatedTexObj0;
    GXTexObj* texObjC = &vYmMana->m_envTexture1->m_texObj;
    unsigned char alpha = vYmMana->m_manaAlpha;

    _GXColor white = {0xff, 0xff, 0xff, 0xff};
    _GXColor alphaOnly = {0x00, 0x00, 0x00, alpha};
    _GXColor whiteAlpha = {0xff, 0xff, 0xff, alpha};
    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevSwapModeTable((GXTevSwapSel)1, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3, (GXTevColorChan)3);

    GXSetTevDirect((GXTevStageID)0);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)0, (GXTexCoordID)0, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)0, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)0, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)1);

    GXSetTevDirect((GXTevStageID)1);
    GXLoadTexObj(texObjC, (GXTexMapID)0);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)1, (GXTexCoordID)1, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)1, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)1, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xc);
    GXSetTevColorOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)1, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)4);
    GXSetTevAlphaOp((GXTevStageID)1, (GXTevOp)0, (GXTevBias)0, (GXTevScale)2, (GXBool)1, (GXTevRegID)2);

    GXSetTevDirect((GXTevStageID)2);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)2, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)2, (GXTexCoordID)2, (GXTexMapID)1, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)2, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)0, alphaOnly);
    GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xc);
    GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)2, (GXTevColorArg)10, (GXTevColorArg)0xe, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)2, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)2, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)2, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)3);
    GXLoadTexObj(texObjA, (GXTexMapID)1);
    GXSetTexCoordGen2((GXTexCoordID)3, (GXTexGenType)1, (GXTexGenSrc)4, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)3, (GXTexCoordID)3, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)3, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)3, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)3);
    GXSetTevAlphaIn((GXTevStageID)3, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)1);
    GXSetTevAlphaOp((GXTevStageID)3, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)4);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)4, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)4, (GXTexCoordID)4, (GXTexMapID)2, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)4, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKColor((GXTevKColorID)1, whiteAlpha);
    GXSetTevKColorSel((GXTevStageID)4, (GXTevKColorSel)0xd);
    GXSetTevKAlphaSel((GXTevStageID)4, (GXTevKAlphaSel)0x1d);
    GXSetTevColorIn((GXTevStageID)4, (GXTevColorArg)0xe, (GXTevColorArg)0xb, (GXTevColorArg)8, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)4, (GXTevOp)8, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)4, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)4, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)5);
    GXLoadTexObj(texObjB, (GXTexMapID)2);
    GXSetTexCoordGen2((GXTexCoordID)5, (GXTexGenType)1, (GXTexGenSrc)5, 0x3c, (GXBool)0, 0x7d);
    GXSetTevOrder((GXTevStageID)5, (GXTexCoordID)5, (GXTexMapID)0, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)5, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)5, (GXTevColorArg)0xf, (GXTevColorArg)0, (GXTevColorArg)9, (GXTevColorArg)0xf);
    GXSetTevColorOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)5, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)5, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)6);
    GXSetTevOrder((GXTevStageID)6, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)6, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorIn((GXTevStageID)6, (GXTevColorArg)0xf, (GXTevColorArg)6, (GXTevColorArg)0xc, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)6, (GXTevAlphaArg)7, (GXTevAlphaArg)1, (GXTevAlphaArg)6, (GXTevAlphaArg)2);
    GXSetTevAlphaOp((GXTevStageID)6, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetTevDirect((GXTevStageID)7);
    GXSetTevOrder((GXTevStageID)7, (GXTexCoordID)0xff, (GXTexMapID)0xff, (GXChannelID)4);
    GXSetTevSwapMode((GXTevStageID)7, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevKAlphaSel((GXTevStageID)7, (GXTevKAlphaSel)0x1c);
    GXSetTevColorIn((GXTevStageID)7, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0);
    GXSetTevColorOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)7, (GXTevAlphaArg)7, (GXTevAlphaArg)0, (GXTevAlphaArg)6, (GXTevAlphaArg)7);
    GXSetTevAlphaOp((GXTevStageID)7, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, (GXBool)1, (GXTevRegID)0);

    GXSetNumTevStages(8);
    GXSetNumTexGens(6);
}

/*
 * --INFO--
 * PAL Address: 0x800d7fcc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel*, void*, void*, int)
{
	GXSetZMode((GXBool)0, (GXCompare)3, (GXBool)0);
}

/*
 * --INFO--
 * PAL Address: 0x800d7ef4
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Chara_DrawShadowMeshDLCallback(CChara::CModel* model, void* work, void* vYmMana, int meshIndex, int dlIndex, float (*) [4])
{
    VYmMana* mana = static_cast<VYmMana*>(work);
    VYmMana* sourceMana = static_cast<VYmMana*>(vYmMana);
    CChara::CMesh* meshes = model->m_meshes;
    u8 alpha = sourceMana->m_runtimeColor.a;
    if (alpha != 0) {
        mana->m_shadowColor.r = 0xFF;
        mana->m_shadowColor.g = 0xFF;
        mana->m_shadowColor.b = 0xFF;
        mana->m_shadowColor.a = sourceMana->m_runtimeColor.a;
    } else if (alpha == 0) {
        mana->m_shadowColor.r = 0xFF;
        mana->m_shadowColor.g = 0xFF;
        mana->m_shadowColor.b = 0xFF;
        mana->m_shadowColor.a = 0xFF;
    }

    DCFlushRange(&mana->m_shadowColor, 4);
    GXSetArray((GXAttr)0xB, &mana->m_shadowColor, 4);

    meshes += meshIndex;
    CChara::CMesh::CRefData* meshData = meshes->m_data;
    CChara::CMesh::CDisplayList* displayList = meshData->m_displayLists;
    displayList += dlIndex;
    MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
    GXCallDisplayList(displayList->m_data, displayList->m_size);
}

/*
 * --INFO--
 * PAL Address: 0x800d79f4
 * PAL Size: 1280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_DrawMeshDLCallback(CChara::CModel* model, void* work, void* step, int partIndex, int dlIndex, float (*mtx)[4])
{
    CChara::CMesh::CRefData* mesh = model->m_meshes[partIndex].m_data;
    CChara::CMesh::CDisplayList* displayList = &mesh->m_displayLists[dlIndex];
    VYmMana* mana = static_cast<VYmMana*>(work);
    pppYmManaStep* stepData = static_cast<pppYmManaStep*>(step);
    int type = stepData->m_type;
    CGObject* object = mana->m_object;
    int draw = 0;

    switch (type) {
    case 0:
        if (strcmp(mesh->m_name, s_ymManaShapeObj) == 0) {
            draw = 1;
        }
        break;
    case 1:
        if (strcmp(mesh->m_name, s_ymManaShapeObj) == 0 || strcmp(mesh->m_name, s_ymManaShapeObj5) == 0) {
            draw = 1;
        }
        break;
    case 2:
        if (strcmp(mesh->m_name, s_ymManaShapeObj) == 0 || strcmp(mesh->m_name, s_ymManaShapeObj3) == 0) {
            draw = 1;
        }
        break;
    case 3:
        if (strcmp(mesh->m_name, s_ymManaShapeObj) == 0 || strcmp(mesh->m_name, s_ymManaShapeObj1) == 0) {
            draw = 1;
        }
        break;
    }

    int waterCmp = strcmp(mesh->m_name, s_ymManaShapeObj4);
    if ((waterCmp == 0 && stepData->m_type == 1) || (strcmp(mesh->m_name, s_ymManaShapeObj2) == 0 && stepData->m_type == 2)) {
        Mtx cameraMtx;
        Mtx rotXMtx;
        Mtx rotZMtx;
        Mtx offsetMtx;
        Mtx worldMtx;

        PSMTXCopy(CameraMatrix(), cameraMtx);
        PSMTXCopy(mtx, mana->m_waterMtx);
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
        GXSetCullMode(GX_CULL_NONE);
        PSMTXRotRad(rotXMtx, 'x', kPppYmMoveParabolaNegHalfPi);
        PSMTXRotRad(rotZMtx, 'z', kPppYmMoveParabolaNegHalfPi);
        PSMTXIdentity(offsetMtx);
        offsetMtx[1][3] = -stepData->m_waterOffset;
        PSMTXConcat(rotZMtx, offsetMtx, offsetMtx);
        PSMTXConcat(rotXMtx, offsetMtx, offsetMtx);
        PSMTXConcat(mtx, offsetMtx, offsetMtx);
        PSMTXConcat(cameraMtx, offsetMtx, worldMtx);
        GXLoadPosMtxImm(worldMtx, 0);
        RenderWaterMesh(mana);
    }

    if (!draw) {
        return;
    }

    if (strcmp(mesh->m_name, s_ymManaShapeObj) != 0) {
        PSMTXCopy(mtx, mana->m_reflectionMtx);
        if (mana->m_paraboloidReady != 0) {
            mana->m_runtimeColor.r = mesh->m_colors[0];
            mana->m_runtimeColor.g = mesh->m_colors[1];
            mana->m_runtimeColor.b = mesh->m_colors[2];
            mana->m_runtimeColor.a = 0x80;
            DCFlushRange(&mana->m_runtimeColor, 4);
            GXSetArray((GXAttr)0xB, mana->m_meshColors, 4);
            GXSetArray((GXAttr)0xD, mana->m_meshTexCoords0, 4);
            GXSetArray((GXAttr)0xE, mana->m_meshTexCoords1, 4);
            MaterialMan.SetManaReflectionEnv(mana->m_meshReflectionVec, mana->m_generatedTexObj0, mana->m_generatedTexObj1, 0xAEE0F);
            GXSetCullMode((GXCullMode)1);
            GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
            MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
            SetEnvMap((PYmMana*)stepData, mana);
            GXCallDisplayList(mana->m_displayListCopies[dlIndex], displayList->m_size);
            for (int i = 0; i < 16; i++) {
                GXSetTevKColorSel((GXTevStageID)i, (GXTevKColorSel)6);
                GXSetTevKAlphaSel((GXTevStageID)i, (GXTevKAlphaSel)0);
            }
        }
        return;
    }

    if (Game.m_currentMapId == 0x21) {
        float alphaScale = kYmManaLookAtAlphaScale[0] * object->m_lookAtTimer;
        int alpha = (int)alphaScale;
        mana->m_baseColor.r = 0xFF;
        mana->m_baseColor.g = 0xFF;
        mana->m_baseColor.b = 0xFF;
        mana->m_baseColor.a = (u8)alpha;
    } else {
        mana->m_baseColor.r = stepData->m_baseColor.r;
        mana->m_baseColor.g = stepData->m_baseColor.g;
        mana->m_baseColor.b = stepData->m_baseColor.b;
        mana->m_baseColor.a = 0xFF;
        if (stepData->m_baseColor.r == 0) {
            mana->m_baseColor.r = 0xFF;
        }
        if (stepData->m_baseColor.g == 0) {
            mana->m_baseColor.g = 0xFF;
        }
        if (stepData->m_baseColor.b == 0) {
            mana->m_baseColor.b = 0xFF;
        }
    }

    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    DCFlushRange(&mana->m_baseColor, 4);
    GXSetArray((GXAttr)0xB, &mana->m_baseColor, 4);
    MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);
    _GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
    GXCallDisplayList(displayList->m_data, displayList->m_size);
}

/*
 * --INFO--
 * PAL Address: 0x800d7864
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMana(PYmMana* ymMana, _pppCtrlTable* param_2)
{
    YmManaDataOffsets* offsets = GetYmManaDataOffsets(param_2);
    s32 workOffset = offsets->m_workOffset;
    VYmMana* work = reinterpret_cast<VYmMana*>(reinterpret_cast<_pppPObject*>(ymMana)->m_workArea + workOffset);
    CGObject* gObject = ppvMng->m_owner;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    if ((s32)Game.m_currentSceneId == 7) {
        gObject->m_lookAtTimer = kYmManaOne;
    }

    if (Game.m_currentMapId != 0x21) {
        gObject->m_stepSlopeLimit = LoadFloat(kYmManaSlopeLimit);
    }

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
    work->m_captureTexObjs = 0;
    work->m_step = 0;
    work->m_envTexture0 = 0;
    work->m_envTexture1 = 0;
    work->m_meshReflectionVec = 0;
    work->m_meshColors = 0;
    work->m_meshTexCoords0 = 0;
    work->m_meshTexCoords1 = 0;
    work->m_generatedTexObj0 = 0;
    work->m_generatedTexObj1 = 0;
    work->m_generatedTexture0 = 0;
    work->m_generatedTexture1 = 0;
    work->m_manaAlpha = 0xFF;
    PSMTXIdentity(work->m_waterMtx);
    PSMTXIdentity(work->m_reflectionMtx);
    work->m_runtimeColor.r = 0xFF;
    work->m_runtimeColor.g = 0xFF;
    work->m_runtimeColor.b = 0xFF;
    work->m_runtimeColor.a = 0xFF;
    work->m_shadowColor.r = 0xFF;
    work->m_shadowColor.g = 0xFF;
    work->m_shadowColor.b = 0xFF;
    work->m_shadowColor.a = 0xFF;
    work->m_baseColor.r = 0xFF;
    work->m_baseColor.g = 0xFF;
    work->m_baseColor.b = 0xFF;
    work->m_baseColor.a = 0xFF;
    work->m_sourceTextures[0] = 0;
    work->m_sourceTextures[1] = 0;
    work->m_sourceTextures[2] = 0;
    work->m_sourceTextures[3] = 0;
    work->m_sourceTextures[4] = 0;
    work->m_sourceTextures[5] = 0;
    work->m_paraboloidMapSize = 0;
    work->m_displayListSize = 0;
    work->m_paraboloidReady = 0;
    work->m_attachedObject = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800d7440
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMana(PYmMana* ymMana, _pppCtrlTable* param_2)
{
    VYmMana* work =
        reinterpret_cast<VYmMana*>(reinterpret_cast<_pppPObject*>(ymMana)->m_workArea + GetYmManaDataOffsets(param_2)->m_workOffset);
    CGObject* gObject = work->m_object;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CChara::CMesh* mesh;
    pppYmManaStep* step;
    u32 i;
    u32 j;

    gObject->DispCharaParts(1);
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    ClearManaModelCallbacks(model);
    Graphic._WaitDrawDone(const_cast<char*>(s_pppYmMana_cpp), 0x2CE);
    MaterialMan.ClearManaParaboloidTexObjs();

    if (work->m_generatedTexObj0 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexObj0);
        work->m_generatedTexObj0 = 0;
    }
    if (work->m_generatedTexObj1 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexObj1);
        work->m_generatedTexObj1 = 0;
    }
    if (work->m_generatedTexture0 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexture0);
        work->m_generatedTexture0 = 0;
    }
    if (work->m_generatedTexture1 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_generatedTexture1);
        work->m_generatedTexture1 = 0;
    }
    if (work->m_baseParaboloidTexObjs != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_baseParaboloidTexObjs);
        work->m_baseParaboloidTexObjs = 0;
    }
    if (work->m_positions != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_positions);
        work->m_positions = 0;
    }
    if (work->m_normals != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_normals);
        work->m_normals = 0;
    }
    if (work->m_waterHeightA != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_waterHeightA);
        work->m_waterHeightA = 0;
    }
    if (work->m_waterHeightB != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_waterHeightB);
        work->m_waterHeightB = 0;
    }
    if (work->m_indices != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_indices);
        work->m_indices = 0;
    }
    if (work->m_texCoord0 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_texCoord0);
        work->m_texCoord0 = 0;
    }
    if (work->m_texCoord1 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_texCoord1);
        work->m_texCoord1 = 0;
    }
    if (work->m_captureTexObjs != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_captureTexObjs);
        work->m_captureTexObjs = 0;
    }
    if (work->m_paraboloidMap != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_paraboloidMap);
        work->m_paraboloidMap = 0;
    }
    if (work->m_colors != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_colors);
        work->m_colors = 0;
    }
    if (work->m_reflectionVec != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_reflectionVec);
        work->m_reflectionVec = 0;
    }
    if (work->m_meshReflectionVec != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshReflectionVec);
        work->m_meshReflectionVec = 0;
    }
    if (work->m_meshColors != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshColors);
        work->m_meshColors = 0;
    }
    if (work->m_meshTexCoords0 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshTexCoords0);
        work->m_meshTexCoords0 = 0;
    }
    if (work->m_meshTexCoords1 != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_meshTexCoords1);
        work->m_meshTexCoords1 = 0;
    }

    mesh = model->m_meshes;
    step = work->m_step;
    for (i = 0; i < model->m_data->m_meshCount; i++, mesh++) {
        u8 stepType = step->m_type;
        CChara::CMesh::CRefData* shape = mesh->m_data;

        if (stepType == 1) {
            if (strcmp(shape->m_name, s_ymManaShapeObj5) == 0) {
                for (j = 0; j < shape->m_displayListCount; j++) {
                    if (work->m_displayListCopies != 0 && work->m_displayListCopies[j] != NULL) {
                        pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != 0) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 2) {
            if (strcmp(shape->m_name, s_ymManaShapeObj3) == 0) {
                for (j = 0; j < shape->m_displayListCount; j++) {
                    if (work->m_displayListCopies != 0 && work->m_displayListCopies[j] != NULL) {
                        pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                        work->m_displayListCopies[j] = 0;
                    }
                }
                if (work->m_displayListCopies != 0) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
                    work->m_displayListCopies = 0;
                }
            }
        } else if (stepType == 3 && strcmp(shape->m_name, s_ymManaShapeObj1) == 0) {
            for (j = 0; j < shape->m_displayListCount; j++) {
                if (work->m_displayListCopies != 0 && work->m_displayListCopies[j] != NULL) {
                    pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies[j]);
                    work->m_displayListCopies[j] = 0;
                }
            }
            if (work->m_displayListCopies != 0) {
                pppHeapUseRate((CMemory::CStage*)work->m_displayListCopies);
                work->m_displayListCopies = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d694c
 * PAL Size: 2804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMana(PYmMana* pppYmMana, pppYmManaStep* param_2, _pppCtrlTable* param_3)
{
    u32 texBufferSize;
    VYmMana* mana;
    GXTexObj* dstTexObj;
    CChara::CMesh* mesh;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    CGObject* gObject;
    s32 i;
    u32 meshIndex;
    u32 vertexIndex;
    s32 setupOffset;
    u8* workArea;

    if (ppvUserStopPartF != 0) {
        return;
    }

    gObject = ppvMng->m_owner;
    YmManaDataOffsets* serializedOffsets = GetYmManaDataOffsets(param_3);
    setupOffset = serializedOffsets->m_setupOffset;
    workArea = reinterpret_cast<_pppPObject*>(pppYmMana)->m_workArea;
    mana = reinterpret_cast<VYmMana*>(workArea + serializedOffsets->m_workOffset);
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    mana->m_step = param_2;
    if (Game.m_currentMapId == 0x21) {
        param_2->m_map21Flag = 0;
    }

    if (gObject->m_weaponNodeFlagBits.m_attached != 0) {
        mana->m_attachedObject = gObject->m_attachOwner;
    }

    SetManaModelCallbacks(model, mana, param_2);

    MaterialMan.SetManaAlpha((u8)((float)*(workArea + setupOffset + 0xB) * gObject->m_lookAtTimer));
    if (Game.m_currentMapId == 0x21) {
        MaterialMan.SetManaAlpha((u8)(gObject->m_lookAtTimer * (float)*(workArea + setupOffset + 0xB)));
    }
    mana->m_manaAlpha = MaterialMan.GetManaAlpha();

    if (*(s32*)pppYmMana != 0) {
        return;
    }

    mana->m_object = gObject;
    SetManaModelCallbacks(model, mana, param_2);
    mana->m_sourceTextures[0] = GetTextureFromRSD(param_2->m_sourceTextureId0, ppvEnv);
    mana->m_sourceTextures[1] = GetTextureFromRSD(param_2->m_sourceTextureId1, ppvEnv);
    mana->m_sourceTextures[2] = GetTextureFromRSD(param_2->m_sourceTextureId2, ppvEnv);
    mana->m_sourceTextures[3] = GetTextureFromRSD(param_2->m_sourceTextureId3, ppvEnv);
    mana->m_sourceTextures[4] = GetTextureFromRSD(param_2->m_sourceTextureId4, ppvEnv);
    mana->m_sourceTextures[5] = GetTextureFromRSD(param_2->m_sourceTextureId5, ppvEnv);
    mana->m_envTexture0 = GetTextureFromRSD(param_2->m_envTextureId0, ppvEnv);
    mana->m_envTexture1 = GetTextureFromRSD(param_2->m_envTextureId1, ppvEnv);

    mana->m_envTexture0->m_format = 0;
    mana->m_envTexture0->InitTexObj();
    mana->m_envTexture1->m_format = 0;
    mana->m_envTexture1->InitTexObj();

    if (mana->m_captureTexObjs == 0) {
        mana->m_captureTexObjs =
            static_cast<GXTexObj*>(pppMemAlloc(0xC0, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x38F));
    }
    if (mana->m_generatedTexObj0 == 0) {
        mana->m_generatedTexObj0 =
            static_cast<GXTexObj*>(pppMemAlloc(0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x395));
    }
    if (mana->m_generatedTexObj1 == 0) {
        mana->m_generatedTexObj1 =
            static_cast<GXTexObj*>(pppMemAlloc(0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x399));
    }

    texBufferSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB565, GX_FALSE, 0);
    if (mana->m_generatedTexture0 == 0) {
        mana->m_generatedTexture0 =
            pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3A1);
    }
    if (mana->m_generatedTexture1 == 0) {
        mana->m_generatedTexture1 =
            pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3A3);
    }

    GXInitTexObj(mana->m_generatedTexObj0, mana->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, (GXTexWrapMode)1,
                 (GXTexWrapMode)1, GX_FALSE);
    GXInitTexObj(mana->m_generatedTexObj1, mana->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, (GXTexWrapMode)1,
                 (GXTexWrapMode)1, GX_FALSE);

    if (mana->m_baseParaboloidTexObjs == 0) {
        mana->m_baseParaboloidTexObjs =
            static_cast<GXTexObj*>(pppMemAlloc(0xC0, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3B0));
    }
    dstTexObj = mana->m_baseParaboloidTexObjs;
    for (i = 0; i < 6; i++) {
        mana->m_sourceTextures[i]->m_format = 0;
        mana->m_sourceTextures[i]->InitTexObj();
        memcpy(dstTexObj, &mana->m_sourceTextures[i]->m_texObj, sizeof(GXTexObj));
        dstTexObj++;
    }

    mana->m_envTexture0->m_format = 0;
    mana->m_envTexture0->InitTexObj();
    mana->m_envTexture1->m_format = 0;
    mana->m_envTexture1->InitTexObj();

    if (mana->m_paraboloidMap == 0) {
        mana->m_paraboloidMap = pppMemAlloc(0xA5E8, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3CB);
        genParaboloidMap(mana->m_paraboloidMap, &mana->m_paraboloidMapSize, 0x1E, GX_VTXFMT7);
    }

    mesh = model->m_meshes;
    if (mana->m_positions == 0 && mana->m_normals == 0 && mana->m_waterHeightA == 0) {
        for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++, mesh++) {
            CChara::CMesh::CRefData* meshShape = mesh->m_data;
            u8 type = param_2->m_type;

            if (((type == 1) && strcmp(meshShape->m_name, s_ymManaShapeObj5) == 0) ||
                ((type == 2) && strcmp(meshShape->m_name, s_ymManaShapeObj3) == 0) ||
                ((type == 3) && strcmp(meshShape->m_name, s_ymManaShapeObj1) == 0)) {
                if (mana->m_meshReflectionVec == 0) {
                    mana->m_meshReflectionVec = static_cast<Vec*>(
                        pppMemAlloc(meshShape->m_vertexCount * sizeof(Vec), ppvEnv->m_stagePtr,
                                    const_cast<char*>(s_pppYmMana_cpp), 1000));
                    Vec* reflectionVec = mana->m_meshReflectionVec;
                    float zero = kPppYmMoveParabolaZero;
                    for (vertexIndex = 0; vertexIndex < meshShape->m_vertexCount; vertexIndex++) {
                        reflectionVec->z = zero;
                        reflectionVec->y = zero;
                        reflectionVec->x = zero;
                        reflectionVec++;
                    }
                }
                if (mana->m_meshColors == 0) {
                    mana->m_meshColors = static_cast<GXColor*>(
                        pppMemAlloc(meshShape->m_vertexCount * sizeof(GXColor), ppvEnv->m_stagePtr,
                                    const_cast<char*>(s_pppYmMana_cpp), 0x3F1));
                    u8* color = reinterpret_cast<u8*>(mana->m_meshColors);
                    for (vertexIndex = 0; vertexIndex < meshShape->m_vertexCount; vertexIndex++) {
                        color[0] = 0xFF;
                        color[1] = 0xFF;
                        color[2] = 0xFF;
                        color[3] = 0xFF;
                        color += 4;
                    }
                }
                if (mana->m_meshTexCoords0 == 0) {
                    s32 texCoordSize = meshShape->m_vertexCount * 6;
                    mana->m_meshTexCoords0 = static_cast<S16Vec2d*>(
                        pppMemAlloc(texCoordSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3FA));
                    mana->m_meshTexCoords1 = static_cast<S16Vec2d*>(
                        pppMemAlloc(texCoordSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x3FB));
                    u16* texCoordA = reinterpret_cast<u16*>(mana->m_meshTexCoords0);
                    u16* texCoordB = reinterpret_cast<u16*>(mana->m_meshTexCoords1);
                    for (vertexIndex = 0; vertexIndex < meshShape->m_vertexCount; vertexIndex++) {
                        texCoordA[1] = 0;
                        texCoordA[0] = 0;
                        texCoordA += 3;
                        texCoordB[1] = 0;
                        texCoordB[0] = 0;
                        texCoordB += 3;
                    }
                }

                mana->m_displayListCopies = static_cast<void**>(
                    pppMemAlloc(meshShape->m_displayListCount * sizeof(void*), ppvEnv->m_stagePtr,
                                const_cast<char*>(s_pppYmMana_cpp), 0x407));
                CChara::CMesh::CDisplayList* displayList = meshShape->m_displayLists;
                for (s32 dlIndex = meshShape->m_displayListCount - 1; dlIndex >= 0; dlIndex--) {
                    void* copiedDisplayList =
                        pppMemAlloc(displayList->m_size, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x411);
                    copiedDisplayList =
                        reinterpret_cast<void*>((reinterpret_cast<u32>(copiedDisplayList) + 0x1F) & 0xFFFFFFE0);
                    mana->m_displayListCopies[dlIndex] = copiedDisplayList;
                    mana->m_displayListSize = displayList->m_size;
                    memcpy(copiedDisplayList, displayList->m_data, displayList->m_size);
                    DCFlushRange(copiedDisplayList, displayList->m_size);
                    gUtil.ReWriteDisplayList(copiedDisplayList, displayList->m_size, 3);
                    displayList++;
                }
            }

            if (((type == 1) && strcmp(meshShape->m_name, s_ymManaShapeObj4) == 0) ||
                ((type == 2) && strcmp(meshShape->m_name, s_ymManaShapeObj2) == 0)) {
                mana->m_positions =
                    static_cast<Vec*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x427));
                mana->m_normals =
                    static_cast<Vec*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x428));
                mana->m_reflectionVec =
                    static_cast<Vec*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x429));
                mana->m_texCoord0 =
                    static_cast<Vec2d*>(pppMemAlloc(0x908, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42A));
                mana->m_texCoord1 =
                    static_cast<Vec2d*>(pppMemAlloc(0x908, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42B));
                mana->m_waterHeightA =
                    static_cast<float*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42C));
                mana->m_waterHeightB =
                    static_cast<float*>(pppMemAlloc(0x484, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42D));
                mana->m_indices =
                    static_cast<u16*>(pppMemAlloc(0xC00, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42E));
                mana->m_colors =
                    static_cast<GXColor*>(pppMemAlloc(0xD8C, ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMana_cpp), 0x42F));
                float* waterHeightA = mana->m_waterHeightA;
                float* waterHeightB = mana->m_waterHeightB;
                float zero = kPppYmMoveParabolaZero;
                for (vertexIndex = 0; vertexIndex < 0x121; vertexIndex++) {
                    waterHeightA[vertexIndex] = zero;
                    waterHeightB[vertexIndex] = zero;
                }
                CreateWaterMesh(mana->m_positions, mana->m_normals, mana->m_texCoord0, mana->m_indices,
                                param_2->m_waterScale);
            }
        }
    }

    if ((param_2->m_type == 1 || param_2->m_type == 2) && mana->m_waterHeightA != 0) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(mana->m_waterHeightA) + 0x240) = param_2->m_rippleLevel;
    }

    if (param_2->m_type != 0) {
        if (param_2->m_type == 1 || param_2->m_type == 2) {
            UpdateWaterMesh(mana);
        }

        mesh = model->m_meshes;
        for (meshIndex = 0; meshIndex < model->m_data->m_meshCount; meshIndex++, mesh++) {
            CChara::CMesh::CRefData* meshShape = mesh->m_data;
            u8 type = param_2->m_type;

            if (((type == 1) && strcmp(meshShape->m_name, s_ymManaShapeObj5) == 0) ||
                ((type == 2) && strcmp(meshShape->m_name, s_ymManaShapeObj3) == 0) ||
                ((type == 3) && strcmp(meshShape->m_name, s_ymManaShapeObj1) == 0)) {
                for (s32 dlIndex = meshShape->m_displayListCount - 1; dlIndex >= 0; dlIndex--) {
                    CalcReflectionVector2(
                        mana->m_meshReflectionVec, meshShape->m_vertices, meshShape->m_normals, meshShape->m_vertexCount,
                        model->m_data->m_posQuant, model->m_data->m_normQuant, model->m_matrix,
                        mana->m_displayListCopies[dlIndex], mana->m_displayListSize, mana->m_meshColors,
                        mana->m_meshTexCoords0, mana->m_meshTexCoords1,
                        &model->m_nodes[meshShape->m_nodeIndex], pppYmMana, mana);
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d6908
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMana(PYmMana*, pppYmManaStep*, _pppCtrlTable*)
{
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    Graphic.SetViewport();
    pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x800d6110
 * PAL Size: 2040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void Mana_BeforeDrawCallback(CChara::CModel*, void* workPtr, void* step, float (*)[4], int pass)
{
    VYmMana* mana = static_cast<VYmMana*>(workPtr);
    pppYmManaStep* stepData = static_cast<pppYmManaStep*>(step);
    Mtx identityMtx;
    Mtx savedCameraMtx;
    Mtx lookAtMtx;
    Mtx44 savedScreenMtx;
    Mtx44 projectionMtx;
    _GXTexObj sceneTexObj;
    Vec centerPos;
    Vec cameraPos;
    Vec cameraUp;
    CCharaPcs::CHandle* handle;
    CGObject* gObject;
    CChara::CModel* model;
    u32 depthTexSize;
    u32 texBufferStride;
    GXTexObj* sourceTexObjs;
    GXTexObj* captureTexObjs;
    GXTexObj* targetTexObj;
    s32 i;
    f32 savedViewport[6];

    if (pass != 0) {
        return;
    }

    sourceTexObjs = mana->m_baseParaboloidTexObjs;
    if (stepData->m_type == 0) {
        return;
    }

    if (Game.m_currentMapId == 0x21) {
        GXGetViewportv(savedViewport);
    }

    Graphic.SetViewport();
    PSMTXIdentity(identityMtx);
    PSMTXCopy(CameraMatrix(), savedCameraMtx);
    PSMTX44Copy(CameraScreenMatrix(), savedScreenMtx);
    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &sceneTexObj, (int)LoadFloat(kPppYmMoveParabolaZero),
                               (int)LoadFloat(kPppYmMoveParabolaZero), 0x80, 0x80, 0, GX_NEAR, GX_TF_RGBA8, 0);

    gObject = mana->m_object;
    if (gObject == NULL) {
        return;
    }

    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);

    if ((int)Game.m_currentSceneId == 7) {
        centerPos.x = kPppYmMoveParabolaZero;
        centerPos.y = kPppYmMoveParabolaZero;
        centerPos.z = kPppYmMoveParabolaZero;
    } else {
        centerPos = gObject->m_worldPosition;
    }
    centerPos.y += kYmManaCaptureHeightOffset;

    depthTexSize = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGBA8, GX_FALSE, 0);
    texBufferStride = GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB565, GX_FALSE, 0);
    captureTexObjs = mana->m_captureTexObjs;

    if (stepData->m_map21Flag != 0) {
        char* compareName = Game.m_currentScriptName;
        C_MTXPerspective(projectionMtx, kYmManaCaptureFovY, kYmManaOne, kYmManaOne, kYmManaCaptureFarClip);
        GXSetProjection(projectionMtx, (_GXProjectionType)0);

        for (i = 0; i < 6; i++) {
            cameraPos = centerPos;
            cameraUp.x = kPppYmMoveParabolaZero;
            cameraUp.y = kYmManaOne;
            cameraUp.z = kPppYmMoveParabolaZero;

            s32 nameCompare = strcmp(s_ymManaRuin2Name, compareName);
            if (nameCompare == 0) {
                if (i == 0) {
                    cameraPos.z -= kYmManaOne;
                } else if (i == 1) {
                    cameraPos.x += kYmManaOne;
                } else if (i == 2) {
                    cameraPos.z += kYmManaOne;
                } else if (i == 3) {
                    cameraPos.x -= kYmManaOne;
                }
            }

            if (nameCompare != 0 || i == 4 || i == 5) {
                if (i == 3) {
                    cameraPos.z -= kYmManaOne;
                } else if (i < 3) {
                    if (i == 1) {
                        cameraPos.z += kYmManaOne;
                    } else if (i >= 2) {
                        cameraPos.x -= kYmManaOne;
                    } else if (i >= 0) {
                        cameraPos.x += kYmManaOne;
                    }
                } else if (i == 5) {
                    cameraPos.y -= kYmManaOne;
                    cameraUp.y = kPppYmMoveParabolaZero;
                    cameraUp.z = kPppYmMoveParabolaZero;
                } else if (i < 5) {
                    cameraPos.y += kYmManaOne;
                    cameraUp.y = kPppYmMoveParabolaZero;
                    cameraUp.z = kYmManaNegOne;
                }
            }

            C_MTXLookAt(lookAtMtx, (Point3d*)&centerPos, &cameraUp, (Point3d*)&cameraPos);
            Graphic.SetViewport();
            GXSetScissor((u32)LoadFloat(kPppYmMoveParabolaZero), (u32)LoadFloat(kPppYmMoveParabolaZero), 0x80, 0x80);
            gUtil.RenderTextureQuad(kPppYmMoveParabolaZero, kPppYmMoveParabolaZero, kYmManaCaptureTextureSize, kYmManaCaptureTextureSize,
                                    sourceTexObjs, 0, 0, 0, (_GXBlendFactor)4, (_GXBlendFactor)5);

            GXSetViewport(kPppYmMoveParabolaZero, kPppYmMoveParabolaZero, kYmManaCaptureTextureSize, kYmManaCaptureTextureSize, kPppYmMoveParabolaZero, kYmManaOne);
            GXSetScissor((u32)LoadFloat(kPppYmMoveParabolaZero), (u32)LoadFloat(kPppYmMoveParabolaZero), 0x80, 0x80);
            PSMTXCopy(lookAtMtx, CameraMatrix());
            GXSetProjection(projectionMtx, (_GXProjectionType)0);

            if (((gObject->m_weaponNodeFlags & 1) != 0 || gObject->m_attachOwner != NULL) &&
                gObject->m_attachOwner->m_charaModelHandle != NULL) {
                CCharaPcs::CHandle* owner = gObject->m_attachOwner->m_charaModelHandle;
                CChara::CModel* ownerModel = owner->m_model;

                ownerModel->SetCallbackContext(mana, step);
                owner->m_model->m_beforeDrawShadowLockEnvCallback = Mana_BeforeDrawShadowLockEnvCallback;
                owner->m_model->m_drawShadowMeshDLCallback = Chara_DrawShadowMeshDLCallback;
                owner->Draw(1);
                ownerModel = owner->m_model;
                ownerModel->SetCallbackContext(0, 0);
                owner->m_model->m_beforeDrawShadowLockEnvCallback = 0;
                owner->m_model->m_drawShadowMeshDLCallback = 0;
            }

            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, captureTexObjs, 0, 0, 0x80, 0x80,
                                       depthTexSize, GX_LINEAR, GX_TF_RGB565, 0);
            depthTexSize += texBufferStride;
            sourceTexObjs++;
            captureTexObjs++;
        }

        PSMTXCopy(savedCameraMtx, CameraMatrix());
        Graphic.SetViewport();
        GXSetScissor(0, 0, 0x280, 0x1C0);
        for (i = 0; i < 0x10; i++) {
            GXSetTevKColorSel((GXTevStageID)i, (GXTevKColorSel)6);
            GXSetTevKAlphaSel((GXTevStageID)i, (GXTevKAlphaSel)0);
            _GXSetTevSwapMode((GXTevStageID)i, GX_TEV_SWAP0, GX_TEV_SWAP0);
        }
        mana->m_paraboloidReady = 1;
    }

    targetTexObj = &mana->m_envTexture0->m_texObj;
    if (stepData->m_map21Flag != 0) {
        GXInitTexObj(mana->m_generatedTexObj0, mana->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(mana->m_generatedTexObj0, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXInitTexObj(mana->m_generatedTexObj1, mana->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(mana->m_generatedTexObj1, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        drawParaboloidMap(mana->m_captureTexObjs, mana->m_generatedTexObj1, mana->m_paraboloidMap, mana->m_paraboloidMapSize,
                          targetTexObj, 1);
        drawParaboloidMap(mana->m_captureTexObjs, mana->m_generatedTexObj0, mana->m_paraboloidMap, mana->m_paraboloidMapSize,
                          targetTexObj, 0);
        Graphic.SetViewport();
        GXSetProjection(savedScreenMtx, (_GXProjectionType)0);
        PSMTXCopy(savedCameraMtx, CameraMatrix());
        gUtil.RenderTextureQuad(kPppYmMoveParabolaZero, kPppYmMoveParabolaZero, kYmManaCaptureTextureSize, kYmManaCaptureTextureSize, &sceneTexObj,
                                0, 0, 0, (_GXBlendFactor)4, (_GXBlendFactor)5);
    } else {
        if (mana->m_paraboloidReady == 0) {
            GXInitTexObj(mana->m_generatedTexObj0, mana->m_generatedTexture0, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObj(mana->m_generatedTexObj1, mana->m_generatedTexture1, 0x80, 0x80, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
            drawParaboloidMap(mana->m_baseParaboloidTexObjs, mana->m_generatedTexObj1, mana->m_paraboloidMap,
                              mana->m_paraboloidMapSize, targetTexObj, 1);
            drawParaboloidMap(mana->m_baseParaboloidTexObjs, mana->m_generatedTexObj0, mana->m_paraboloidMap,
                              mana->m_paraboloidMapSize, targetTexObj, 0);
            gUtil.RenderTextureQuad(kPppYmMoveParabolaZero, kPppYmMoveParabolaZero, kYmManaCaptureTextureSize, kYmManaCaptureTextureSize, &sceneTexObj,
                                    0, 0, 0, (_GXBlendFactor)4, (_GXBlendFactor)5);
            mana->m_paraboloidReady = 1;
        }
    }

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    handle = GetCharaHandlePtr(gObject, 0);
    model = GetCharaModelPtr(handle);
    model->m_afterMeshDrawCallback = (CChara::CModel::AfterMeshDrawCallback)Mana_BeforeDrawCallback;
    model->SetDrawMeshDLCallback(Mana_DrawMeshDLCallback);

    if (Game.m_currentMapId == 0x21) {
        GXSetViewport(savedViewport[0], savedViewport[1], savedViewport[2], savedViewport[3], savedViewport[4],
                      savedViewport[5]);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d5f7c
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int CreateWaterMesh(Vec* positionsInOut, Vec* normalsOut, Vec2d* uvOut, unsigned short* indicesOut, float size)
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

    normalY = LoadFloat(kYmManaOne);
    zero = LoadFloat(kPppYmMoveParabolaZero);
    rowCount = 0;
    uvStep = LoadFloat(kYmManaWaterUvStep);
    radius = size * LoadFloat(kYmManaHalf);
    for (z = radius; -radius <= z; z -= size * uvStep) {
        colCount = 0;
        positions = reinterpret_cast<float*>(positionsInOut);
        normals = reinterpret_cast<float*>(normalsOut);
        uvs = reinterpret_cast<float*>(uvOut);
        for (x = -radius; x <= radius; x += size * uvStep) {
            *positions = x;
            positionsInOut = reinterpret_cast<Vec*>(positions + 3);
            positions[1] = zero;
            normalsOut = reinterpret_cast<Vec*>(normals + 3);
            uvOut = reinterpret_cast<Vec2d*>(uvs + 2);
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

            indicesOut[indexOffset++] = quadIndex;
            indicesOut[indexOffset++] = nextIndex;
            indicesOut[indexOffset++] = lowerNextIndex;
            indicesOut[indexOffset++] = lowerNextIndex;
            indicesOut[indexOffset++] = lowerIndex;
            indicesOut[indexOffset++] = quadIndex;

            quadIndex++;
            nextIndex = quadIndex + 1;
            lowerIndex = quadIndex + 0x11;
            lowerNextIndex = quadIndex + 0x12;

            indicesOut[indexOffset++] = quadIndex;
            indicesOut[indexOffset++] = nextIndex;
            indicesOut[indexOffset++] = lowerNextIndex;
            indicesOut[indexOffset++] = lowerNextIndex;
            indicesOut[indexOffset++] = lowerIndex;
            indicesOut[indexOffset++] = quadIndex;
            quadIndex++;
        }
        rowCount = rowCount + 1;
        rowBase = rowBase + 0x11;
    } while (rowCount < 0x10);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800d5bb4
 * PAL Size: 968b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int UpdateWaterMesh(VYmMana* mana)
{
    float* waterHeightA;
    float* waterHeightB;
    Vec* positions;
    Vec origin;
    float currentScale;
    float neighborScale;

    waterHeightA = mana->m_waterHeightA;
    positions = mana->m_positions;
    waterHeightB = mana->m_waterHeightB;
    if (waterHeightA == NULL) {
        return 0;
    }

    int row = 1;
    int rowBase = 0x11;
    do {
        currentScale = kPppYmMoveParabolaZero;
        neighborScale = kYmManaHalf;
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
    CalculateNormal(mana);

    origin.x = mana->m_waterMtx[0][3];
    origin.y = mana->m_waterMtx[1][3];
    origin.z = mana->m_waterMtx[2][3];
    CalcWaterReflectionVector(mana->m_reflectionVec, mana->m_positions, mana->m_normals, 0x121, origin,
                              mana->m_waterMtx, mana->m_colors, mana->m_texCoord1);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800d55f4
 * PAL Size: 1472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int RenderWaterMesh(VYmMana* mana)
{
    void* positions = mana->m_positions;
    void* normals = mana->m_normals;
    void* texCoord0 = mana->m_texCoord0;
    void* texCoord1 = mana->m_texCoord1;
    u16* indices = mana->m_indices;
    void* colors = mana->m_colors;
    GXTexObj* texObj0 = mana->m_generatedTexObj0;
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
    texObj2 = mana->m_envTexture1;
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)1, (GXTexGenSrc)5, 0x3C, GX_FALSE, 0x7D);
    u8 alpha = mana->m_manaAlpha;
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
    GXLoadTexObj(mana->m_generatedTexObj0, GX_TEXMAP1);
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
    GXLoadTexObj(mana->m_generatedTexObj1, GX_TEXMAP2);
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
    GXLoadTexObj(texObj0, GX_TEXMAP0);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800d5398
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void CalculateNormal(VYmMana* mana)
{
    Vec* positions;
    Vec* normals;
    u16* indices;
    Vec edgeA;
    Vec edgeB;
    Vec faceNormal;
    s32 i;

    positions = mana->m_positions;
    normals = mana->m_normals;
    indices = mana->m_indices;

    float zero = kPppYmMoveParabolaZero;
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
 * PAL Address: 0x800d50dc
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void CalcWaterReflectionVector(
    Vec* reflectionVec, Vec* positions, Vec* normals, long count, Vec waterOrigin, float (*matrix)[4], _GXColor* color, Vec2d* texCoord)
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

    transformedCameraPos.x = LoadFloat(kPppYmMoveParabolaZero);
    transformedCameraPos.y = LoadFloat(kPppYmMoveParabolaZero);
    transformedCameraPos.z = LoadFloat(kPppYmMoveParabolaZero);

    PSMTXCopy(matrix, matrixNoTranslate);
    objPos.x = matrixNoTranslate[0][3];
    objPos.y = matrixNoTranslate[1][3];
    objPos.z = matrixNoTranslate[2][3];
    matrixNoTranslate[0][3] = transformedCameraPos.x;
    matrixNoTranslate[1][3] = transformedCameraPos.y;
    matrixNoTranslate[2][3] = transformedCameraPos.z;
    PSMTXInverse(matrixNoTranslate, inverseMtx);

    PSVECSubtract(&objPos, &cameraPos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, LoadFloat(kYmManaNegOne));
    PSMTXMultVec(inverseMtx, &cameraPos, &transformedCameraPos);

    colorBytes = (unsigned char*)color;
    texCoordFloat = (float*)texCoord;
    reflectionIt = reflectionVec;
    normalIt = normals;
    zero = LoadFloat(kPppYmMoveParabolaZero);
    half = LoadFloat(kYmManaHalf);

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
            denomBase = LoadFloat(kYmManaOne);
            *texCoordFloat = -reflectionIt->x / (denomBase + reflectionIt->z);
            texCoordFloat[1] = -reflectionIt->y / (denomBase + reflectionIt->z);
        } else {
            float denomBase;

            colorBytes[0] = 0x80;
            colorBytes[1] = 0xff;
            colorBytes[2] = 0x80;
            colorBytes[3] = 0x7f;
            denomBase = LoadFloat(kYmManaOne);
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
 * PAL Address: 0x800d4c7c
 * PAL Size: 1120b
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
    S16Vec2d* texCoordA,
    S16Vec2d* texCoordB,
    CChara::CNode* node,
    PYmMana*,
    VYmMana*)
{
    Vec cameraPos;
    Vec nodePos;
    Vec matrixPos;
    Vec worldPos;
    Vec position;
    Vec normal;
    Vec eyeToPos;
    Vec2d uv;
    Mtx matrixCopy;
    Mtx nodeOffsetMtx;
    Mtx nodeRotMtx;
    Mtx workMtx;
    Mtx normalMtx;
    Mtx rotateMtx;
    u16* dl = (u16*)displayList;
    const float zero = kPppYmMoveParabolaZero;
    const float denomBias = kYmManaReflectionDenomBias;
    const float half = kYmManaHalf;
    const float warp = kYmManaReflectionUvWarp;
    const float scale = kYmManaReflectionUvWarpScale;

    cameraPos.x = CameraWorldX();
    cameraPos.y = CameraWorldY();
    cameraPos.z = CameraWorldZ();

    PSMTXCopy(matrix, matrixCopy);
    PSMTXCopy(node->m_localRuntimeMtx, nodeOffsetMtx);
    PSMTXCopy(node->m_mtx, workMtx);

    nodePos.x = workMtx[0][3];
    nodePos.y = workMtx[1][3];
    nodePos.z = workMtx[2][3];

    matrixPos.x = matrixCopy[0][3];
    matrixPos.y = matrixCopy[1][3];
    matrixPos.z = matrixCopy[2][3];
    PSVECAdd(&nodePos, &matrixPos, &worldPos);

    PSMTXCopy(workMtx, nodeRotMtx);
    PSMTXRotRad(rotateMtx, 'y', kPppYmMoveParabolaNegHalfPi);
    nodeRotMtx[0][3] = worldPos.x;
    nodeRotMtx[1][3] = worldPos.y;
    nodeRotMtx[2][3] = worldPos.z;

    PSMTXCopy(nodeRotMtx, normalMtx);
    normalMtx[0][3] = kPppYmMoveParabolaZero;
    normalMtx[1][3] = kPppYmMoveParabolaZero;
    normalMtx[2][3] = kPppYmMoveParabolaZero;

    u16* dlEnd = (u16*)((u8*)displayList + displayListSize);
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
            float denom;
            u8* colorBytes = (u8*)&color[posIndex];

            dl += 4;
            if ((drawFmt & 7) == 2) {
                dl++;
            }

            gUtil.ConvI2FVector(position, positions[posIndex], posScale);
            gUtil.ConvI2FVector(normal, normals[normalIndex], normalScale);
            PSMTXMultVec(nodeRotMtx, &position, &position);
            PSMTXMultVec(normalMtx, &normal, &normal);

            PSVECSubtract(&position, &cameraPos, &eyeToPos);
            C_VECReflect(&eyeToPos, &normal, &reflectionVec[posIndex]);

            if (strcmp(s_ymManaRuin2Name, Game.m_currentScriptName) == 0) {
                PSMTXMultVec(rotateMtx, &reflectionVec[posIndex], &reflectionVec[posIndex]);
            }

            if (reflectionVec[posIndex].z < zero) {
                colorBytes[0] = 0;
                colorBytes[1] = 0;
                colorBytes[2] = 0;
                colorBytes[3] = 0;
            } else {
                colorBytes[0] = 0xFF;
                colorBytes[1] = 0xFF;
                colorBytes[2] = 0xFF;
                colorBytes[3] = 0xFF;
            }

            denom = denomBias + reflectionVec[posIndex].z;
            uv.x = -reflectionVec[posIndex].x / denom;
            uv.y = -reflectionVec[posIndex].y / denom;
            uv.x *= half;
            uv.y *= half;
            uv.x += half;
            uv.y += half;
            uv.x = -(scale * (warp * (uv.x - half)) - uv.x);
            uv.y = -(scale * (warp * (uv.y - half)) - uv.y);
            gUtil.ConvF2IVector2d(texCoordA[posIndex], uv, 12);

            denom = denomBias - reflectionVec[posIndex].z;
            uv.x = -reflectionVec[posIndex].x / denom;
            uv.y = -reflectionVec[posIndex].y / denom;
            uv.x *= half;
            uv.y *= half;
            uv.x += half;
            uv.y += half;
            uv.x = -(scale * (warp * (uv.x - half)) - uv.x);
            uv.y = -(scale * (warp * (uv.y - half)) - uv.y);
            gUtil.ConvF2IVector2d(texCoordB[posIndex], uv, 12);
        }
    }

    DCFlushRange(texCoordA, count << 2);
    DCFlushRange(texCoordB, count << 2);
    DCFlushRange(color, count << 2);
    DCFlushRange(reflectionVec, count * 0xC);
}
