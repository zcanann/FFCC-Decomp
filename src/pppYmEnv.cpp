#include "ffcc/pppYmEnv.h"
#include "ffcc/gobject.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"

#include <math.h>

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int tevSwapSel, int red, int green, int blue, int alpha);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap,
                                                                                 int colorChannel);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
}

struct _pppEnvStYmEnv {
    void* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};

struct CTextureLite {
    char pad_0x0[0x28];
    GXTexObj m_texObj;
    GXTlutObj m_tlutObj0;
    GXTlutObj m_tlutObj1;
};

/*
 * --INFO--
 * PAL Address: 0x800e602c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel* GetModelPtr(CGObject* gObject)
{
    if (gObject == 0) {
        return 0;
    }

    CCharaPcs::CHandle* handle = gObject->m_charaModelHandle;
    if (handle == 0) {
        return 0;
    }

    return handle->m_model;
}
/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GetCharaNodeFrameMatrix(_pppMngSt*, float, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800e58c0
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CalcGraphValue(_pppPObject* object, long graphId, float& value, float& velocity, float& acceleration, float addValue,
                    float& velocityAdd, float& accelerationAdd)
{
    velocity += acceleration;
    value += velocity;

    if (graphId == object->m_graphId) {
        value += addValue;
        velocity += velocityAdd;
        acceleration += accelerationAdd;
    }
}
/*
 * --INFO--
 * PAL Address: 0x800e5870
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GetTextureFromRSD(int mapMeshIndex, _pppEnvSt* env)
{
    int textureIndex;

    if (mapMeshIndex == 0xFFFF) {
        return;
    }

    textureIndex = 0;
    GetTexture__8CMapMeshFP12CMaterialSetRi(((_pppEnvStYmEnv*)env)->m_mapMeshPtr[mapMeshIndex],
                                            ((_pppEnvStYmEnv*)env)->m_materialSetPtr, textureIndex);
}

/*
 * --INFO--
 * PAL Address: 0x800e5858
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CChara::CModel* GetCharaModelPtr(CCharaPcs::CHandle* handle)
{
    if (handle == 0) {
        return 0;
    }

    return handle->m_model;
}

/*
 * --INFO--
 * PAL Address: 0x800e57f0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCharaPcs::CHandle* GetCharaHandlePtr(CGObject* gObject, long modelType)
{
    if (gObject == 0) {
        return 0;
    }

    if (modelType == 1) {
        if (gObject->m_weaponModelHandle != 0) {
            return gObject->m_weaponModelHandle;
        }
    } else if (modelType < 1) {
        if (modelType >= 0 && gObject->m_charaModelHandle != 0) {
            return gObject->m_charaModelHandle;
        }
    } else if (modelType < 3 && gObject->m_shieldModelHandle != 0) {
        return gObject->m_shieldModelHandle;
    }

    return 0;
}
/*
 * --INFO--
 * PAL Address: 0x800e5780
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void DisableIndWarp(_GXTevStageID tevStage, _GXIndTexStageID indStage)
{
    float indMtx[2][3];

    GXSetTevDirect((GXTevStageID)tevStage);
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale((GXIndTexStageID)indStage, GX_ITS_1, GX_ITS_1);

    indMtx[0][0] = 0.0f;
    indMtx[0][1] = 0.0f;
    indMtx[0][2] = 0.0f;
    indMtx[1][0] = 0.0f;
    indMtx[1][1] = 0.0f;
    indMtx[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
}

/*
 * --INFO--
 * PAL Address: 0x800e54dc
 * PAL Size: 676b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SetUpPaletteEnv(CTexture* texture)
{
    GXColorS10 tevColor2;
    GXColorS10 tevColor3;
    CTextureLite* textureLite;

    GXSetNumTevStages(3);
    GXSetNumTexGens(1);

    tevColor2.r = -1;
    tevColor2.g = 0;
    tevColor2.b = 0;
    tevColor2.a = -1;
    GXSetTevColorS10((GXTevRegID)2, tevColor2);

    tevColor3.r = 0;
    tevColor3.g = 0;
    tevColor3.b = 0;
    tevColor3.a = -1;
    GXSetTevColorS10((GXTevRegID)3, tevColor3);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(1, 0, 3,
                                                                                                                     3, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(2, 2, 2,
                                                                                                                     2, 3);

    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 4,
                                                                                                          0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);

    GXSetTevDirect(GX_TEVSTAGE1);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8, 6,
                                                                                                          0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 6, 4,
                                                                                                          7);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 2);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);

    GXSetTevDirect(GX_TEVSTAGE2);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0, 10,
                                                                                                          0xF);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 5,
                                                                                                          7);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 1, 1, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 2, 1, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);

    textureLite = (CTextureLite*)texture;
    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT0);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP0);
    GXInitTexObjTlut(&textureLite->m_texObj, GX_TLUT1);
    GXLoadTexObj(&textureLite->m_texObj, GX_TEXMAP1);
    GXLoadTlut(&textureLite->m_tlutObj0, GX_TLUT0);
    GXLoadTlut(&textureLite->m_tlutObj1, GX_TLUT1);
}

/*
 * --INFO--
 * PAL Address: 0x800e4fb8
 * PAL Size: 1316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void genParaboloidMap(void* displayListBuffer, unsigned long* outDisplayListSize, unsigned short detail, _GXVtxFmt vtxFmt)
{
    static const char s_pppYmEnv_cpp[] = "pppYmEnv.cpp";
    static const char s_exiting[] = "Exiting";
    static const char s_display_list_alloc_error[] = "Error allocating display list. Need %u bytes\n";
    const float kZero = 0.0f;
    const float kOne = 1.0f;
    const float kPi = 3.1415927f;
    const float kHalfPi = 1.5707964f;
    const float kNormalScale = 0.5f;

    const unsigned int rings = detail;
    const int ringVertexCount = rings + 1;
    const unsigned int displayListSize = ((ringVertexCount + (rings - 2) * ringVertexCount * 2) * 0x18 + 0x1F) & ~0x1F;

    DCInvalidateRange(displayListBuffer, displayListSize);
    GXBeginDisplayList(displayListBuffer, displayListSize);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    const float latStep = kHalfPi / (float)rings;
    const float firstLat = latStep;
    const float firstRingSin = (float)sin(firstLat);
    const float firstRingCos = (float)cos(firstLat);

    GXBegin(GX_TRIANGLEFAN, (GXVtxFmt)vtxFmt, rings + 2);
    GXPosition3f32(kZero, kZero, kOne);
    GXNormal3f32(kZero, kZero, kOne);

    for (unsigned int i = 0; i <= rings; i++) {
        const float lon = (2.0f * kPi * (float)i) / (float)rings;
        const float lonSin = (float)sin(lon);
        const float lonCos = (float)cos(lon);

        const float x = firstRingSin * lonCos;
        const float y = firstRingSin * lonSin;
        const float z = firstRingCos;

        GXPosition3f32(x, y, z);
        GXNormal3f32(kNormalScale * x * z, kNormalScale * y * z, z * z);
    }

    for (unsigned int ring = 2; ring < rings; ring++) {
        const float upperLat = (kHalfPi * (float)(ring - 1)) / (float)rings;
        const float lowerLat = (kHalfPi * (float)ring) / (float)rings;

        const float upperSin = (float)sin(upperLat);
        const float upperCos = (float)cos(upperLat);
        const float lowerSin = (float)sin(lowerLat);
        const float lowerCos = (float)cos(lowerLat);

        if ((float)fabs(upperCos) < 1.0e-6f || (float)fabs(lowerCos) < 1.0e-6f) {
            break;
        }

        GXBegin(GX_TRIANGLESTRIP, (GXVtxFmt)vtxFmt, ringVertexCount * 2);
        for (unsigned int i = 0; i <= rings; i++) {
            const float lon = (2.0f * kPi * (float)i) / (float)rings;
            const float lonSin = (float)sin(lon);
            const float lonCos = (float)cos(lon);

            const float lx = lowerSin * lonCos;
            const float ly = lowerSin * lonSin;
            GXPosition3f32(lx, ly, lowerCos);
            GXNormal3f32(kNormalScale * lx * lowerCos, kNormalScale * ly * lowerCos, lowerCos * lowerCos);

            const float ux = upperSin * lonCos;
            const float uy = upperSin * lonSin;
            GXPosition3f32(ux, uy, upperCos);
            GXNormal3f32(kNormalScale * ux * upperCos, kNormalScale * uy * upperCos, upperCos * upperCos);
        }
    }

    *outDisplayListSize = GXEndDisplayList();
    if (displayListSize < *outDisplayListSize) {
        OSReport(s_display_list_alloc_error, displayListSize);
        OSPanic(s_pppYmEnv_cpp, 0x19f, s_exiting);
    }

    DCFlushRange(displayListBuffer, *outDisplayListSize);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void drawParaboloidMap(_GXTexObj*, _GXTexObj*, void*, unsigned long, _GXTexObj*, unsigned char)
{
	// TODO
}
