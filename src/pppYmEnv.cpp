#include "ffcc/pppYmEnv.h"
#include "ffcc/gobject.h"
#include "ffcc/mapmesh.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/partMng.h"
#include "ffcc/graphic.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppGetRotMatrixXZY.h"
#include "ffcc/pppGetRotMatrixYXZ.h"
#include "ffcc/pppGetRotMatrixYZX.h"
#include "ffcc/pppGetRotMatrixZXY.h"
#include "ffcc/pppGetRotMatrixZYX.h"
#include "ffcc/util.h"

#include <math.h>

extern const float FLOAT_80331180;
extern const float FLOAT_80331184;
extern const float FLOAT_80331188;
extern const float FLOAT_8033118C;
extern const float FLOAT_80331190;
extern const float FLOAT_80331194;
extern const float FLOAT_80331198;
extern const float FLOAT_8033119C;
extern const float FLOAT_803311A0;
extern const float FLOAT_803311B0;
extern const float FLOAT_803311B4;
extern const float FLOAT_803311B8;
extern const double DOUBLE_803311C0;
extern const float FLOAT_803311C8;
extern const char s_Exiting_803311CC[8];

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

struct GraphValueState {
    float value;
    float velocity;
    float acceleration;
    s32 graphId;
};

struct Vec2d {
    float x;
    float y;
};

struct PartMngEditRaw {
    u8 m_pad00[0x1C8];
    void* m_recvBuff;
};

struct CAnimRaw {
    u8 m_pad00[0x10];
    u16 m_frameCount;
};

struct CModelRaw {
    u8 m_pad00[0xA8];
    u8* m_nodes;
    u8 m_padAC[0x8];
    float m_time;
    u8 m_padB8[0x18];
    CAnimRaw* m_anim;
};

extern const float FLOAT_803310C0 = 320.0f;
extern const float FLOAT_803310C4 = 224.0f;
extern const float FLOAT_803310C8 = 0.0f;
extern const float FLOAT_803310CC = 1.0f;
extern const double DOUBLE_803310D0 = 4503599627370496.0;
extern const char s_YmEnvMapLabel_803310D8[] = "MAP";
extern const char s_YmEnvMonsterLabel_803310DC[] = "MON";
extern const char s_YmEnvScoreLabel_803310E0[] = "SCO";
extern const char s_YmEnvTreeLabel_803310E4[] = "TRE";
extern const char s_YmEnvSeparator_803310E8[] = "|\n";
extern const double DOUBLE_803310F0 = 57.295780181884766;
extern const float FLOAT_803310F8 = 1.5f;
extern const double DOUBLE_80331100 = 4503601774854144.0;
extern const float FLOAT_80331108 = 0.25f;
extern const float FLOAT_8033110C = 0.0f;
extern const float FLOAT_80331110 = 10.0f;
extern const char sMogFurTextureName[] = "n915m_2";

/*
 * --INFO--
 * PAL Address: 0x800e46dc
 * PAL Size: 2268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void drawParaboloidMap(_GXTexObj* texObjs, _GXTexObj* targetTexObj, void* displayList, unsigned long displayListSize,
                       _GXTexObj* blendTexObj, unsigned char mode)
{
    const unsigned char s_texObjIndices[] = {5, 2, 1, 0, 4, 5, 0, 0, 0, 0};
    const unsigned char s_xAxisRotIndices[] = {0, 0, 0, 0, 1, 1, 0, 0, 2, 0};
    const unsigned char s_yAxisRotIndices[] = {1, 3, 4, 2, 1, 0, 4, 3, 0, 0};
    const float s_xAxisAngles[] = {90.0f, 180.0f, 270.0f, 180.0f, -90.0f, 90.0f};
    const unsigned char s_xAxisIds[] = {'y', 'y', 'y', 'y', 'x', 'x'};
    const float s_yAxisAngles[] = {0.0f, 180.0f};

    const unsigned int texWidth = GXGetTexObjWidth(targetTexObj);
    const unsigned int texHeight = GXGetTexObjHeight(targetTexObj);

    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    const unsigned int modeOffset = mode * 5;

    _GXColor color;
    GXLightObj lightObj;
    Mtx44 orthoMtx;
    Mtx cameraMtx;
    Mtx objectMtx;
    Mtx lightFrustumMtx;
    Mtx tempMtx;

    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0xFF;
    const Vec s_cameraPos = {0.0f, 0.0f, 6.0f};
    const Vec s_cameraUp = {0.0f, 1.0f, 0.0f};
    const Vec s_cameraLook = {0.0f, 0.0f, 0.0f};

    gUtil.RenderColorQuad(0.0f, 0.0f, texWidth, texHeight, color);

    const unsigned short rtWidth = GXGetTexObjWidth(targetTexObj);
    const unsigned short rtHeight = GXGetTexObjHeight(targetTexObj);
    const GXTexFmt targetFmt = GXGetTexObjFmt(targetTexObj);
    void* targetData = GXGetTexObjData(targetTexObj);

    C_MTXOrtho(orthoMtx, FLOAT_80331184, FLOAT_80331188, FLOAT_80331188, FLOAT_80331184, FLOAT_80331184,
               FLOAT_8033118C);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

    C_MTXLookAt(cameraMtx, &s_cameraPos, &s_cameraUp, &s_cameraLook);
    GXLoadPosMtxImm(cameraMtx, 0);

    GXSetCullMode(GX_CULL_BACK);
    GXSetViewport(0.0f, 0.0f, rtWidth, rtHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, rtWidth, rtHeight);
    GXSetTexCopySrc(0, 0, rtWidth, rtHeight);
    GXSetTexCopyDst(rtWidth, rtHeight, targetFmt, GX_FALSE);

    GXSetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_NONE, GX_AF_SPEC);

    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = 0xFF;
    GXInitLightColor(&lightObj, color);
    GXSetChanMatColor(GX_COLOR0A0, color);
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 0;
    GXSetChanAmbColor(GX_COLOR0A0, color);
    GXInitLightAttnA(&lightObj, FLOAT_80331180, FLOAT_80331190, FLOAT_80331180);
    GXInitLightAttnK(&lightObj, FLOAT_80331180, FLOAT_80331184, FLOAT_80331180);
    GXInitLightPos(&lightObj, FLOAT_80331180, FLOAT_80331180, FLOAT_80331188);
    GXInitLightDir(&lightObj, FLOAT_80331180, FLOAT_80331180, FLOAT_80331188);
    GXLoadLightObjImm(&lightObj, GX_LIGHT0);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_NRM, 0x1E, GX_FALSE, GX_PTIDENTITY);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);

    C_MTXLightFrustum(lightFrustumMtx, FLOAT_80331194, FLOAT_80331198, FLOAT_80331194, FLOAT_80331198,
                      FLOAT_80331184, FLOAT_8033119C, FLOAT_8033119C, FLOAT_8033119C, FLOAT_8033119C);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);

    if (blendTexObj != 0) {
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_APREV, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV);
        _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevDirect(GX_TEVSTAGE1);
        GXSetNumTevStages(2);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_NRM, 0x1E, GX_FALSE, GX_PTIDENTITY);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;
        color.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, color);
        GXLoadTexObj(blendTexObj, GX_TEXMAP0);
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT7, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    const float kDegToRad = FLOAT_803311A0;
    const float kZero = FLOAT_80331180;
    for (int i = 0; i < 5; i++) {
        const unsigned char texObjIdx = s_texObjIndices[modeOffset + i];
        const unsigned char xRotIdx = s_xAxisRotIndices[modeOffset + i];
        const unsigned char yRotIdx = s_yAxisRotIndices[modeOffset + i];

        if (blendTexObj != 0) {
            GXLoadTexObj(&texObjs[texObjIdx], GX_TEXMAP1);
        } else {
            GXLoadTexObj(&texObjs[texObjIdx], GX_TEXMAP0);
        }

        PSMTXIdentity(objectMtx);

        const float yAxisAngle = s_yAxisAngles[yRotIdx];
        if (yAxisAngle != kZero) {
            PSMTXRotRad(tempMtx, 'y', FLOAT_803311A0 * yAxisAngle);
            PSMTXConcat(objectMtx, tempMtx, objectMtx);
        }

        PSMTXRotRad(tempMtx, s_xAxisIds[xRotIdx], kDegToRad * s_xAxisAngles[xRotIdx]);
        PSMTXConcat(objectMtx, tempMtx, objectMtx);
        PSMTXConcat(lightFrustumMtx, objectMtx, objectMtx);

        GXLoadTexMtxImm(objectMtx, 0x1E, GX_MTX3x4);
        GXLoadNrmMtxImm(objectMtx, 0);
        GXCallDisplayList(displayList, displayListSize);
    }

    Graphic.GetBackBufferRect2(targetData, targetTexObj, 0, 0, rtWidth, rtHeight, 0, GX_LINEAR, GX_TF_RGB565, 0);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.SetViewport();

    if (mode != 0) {
        Vec2d uvMin;
        Vec2d uvMax;

        uvMin.x = 1.0f;
        uvMin.y = 0.0f;
        uvMax.x = 0.0f;
        uvMax.y = 1.0f;

        gUtil.RenderTextureQuad(0.0f, 0.0f, rtWidth, rtHeight, targetTexObj, &uvMin, &uvMax, 0, (GXBlendFactor)4,
                                (GXBlendFactor)5);
        Graphic.GetBackBufferRect2(targetData, targetTexObj, 0, 0, texWidth, texHeight, 0, GX_LINEAR, GX_TF_RGB565, 0);
    }
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
    static const char s_display_list_alloc_error[] = "Error allocating display list (%d, %d)\n";
    static const char s_pppYmEnv_cpp[] = "pppYmEnv.cpp";
    const int ringVertexCount = detail + 1;
    unsigned long displayListSize =
        ((ringVertexCount + (detail - 2) * ringVertexCount * 2) * 6 * sizeof(float) + 0x1F) & ~0x1F;

    DCInvalidateRange(displayListBuffer, displayListSize);
    GXBeginDisplayList(displayListBuffer, displayListSize);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt((GXVtxFmt)vtxFmt, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);

    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT7, detail + 2);

    const float latStep = FLOAT_803311B0 / (float)detail;
    const float firstLat = latStep;
    const float firstRingSin = FLOAT_80331184 * (float)sin(firstLat);
    const float firstRingCos = FLOAT_80331184 * (float)cos(firstLat);
    const float firstNormalZ = FLOAT_80331190 * firstRingCos * firstRingCos;

    GXPosition3f32(FLOAT_80331180, FLOAT_80331180, FLOAT_80331184);
    GXNormal3f32(FLOAT_80331180, FLOAT_80331180, FLOAT_80331190);

    int i = 0;
    float lon = FLOAT_80331180;
    while (i <= (int)detail) {
        const float x = firstRingSin * (float)cos(lon);
        const float y = firstRingSin * (float)sin(lon);
        const float z = firstRingCos;

        GXPosition3f32(x, y, z);
        GXNormal3f32(FLOAT_803311B4 * x * z, FLOAT_803311B4 * y * z, firstNormalZ);

        i++;
        lon = (FLOAT_803311B8 * (float)i) / (float)detail;
    }

    for (int ring = 2; ring < (int)detail; ring++) {
        const float lowerLat = (FLOAT_803311B0 * (float)ring) / (float)detail;
        const float upperLat = (FLOAT_803311B0 * (float)(ring - 1)) / (float)detail;

        const float upperSin = FLOAT_80331184 * (float)sin(upperLat);
        const float upperCos = FLOAT_80331184 * (float)cos(upperLat);
        const float lowerSin = FLOAT_80331184 * (float)sin(lowerLat);
        const float lowerCos = FLOAT_80331184 * (float)cos(lowerLat);
        const float upperNormalZ = FLOAT_80331190 * upperCos * upperCos;
        const float lowerNormalZ = FLOAT_80331190 * lowerCos * lowerCos;

        if (fabs(upperCos) < DOUBLE_803311C0 || fabs(lowerCos) < DOUBLE_803311C0) {
            break;
        }

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, ringVertexCount * 2);
        i = 0;
        lon = FLOAT_80331180;
        while (i <= (int)detail) {
            const float lx = lowerSin * (float)cos(lon);
            const float ly = lowerSin * (float)sin(lon);
            GXPosition3f32(lx, ly, lowerCos);
            GXNormal3f32(FLOAT_803311B4 * lx * lowerCos, FLOAT_803311B4 * ly * lowerCos, lowerNormalZ);

            const float ux = upperSin * (float)cos(lon);
            const float uy = upperSin * (float)sin(lon);
            GXPosition3f32(ux, uy, upperCos);
            GXNormal3f32(FLOAT_803311B4 * ux * upperCos, FLOAT_803311B4 * uy * upperCos, upperNormalZ);

            i++;
            lon = (FLOAT_803311C8 * (float)i) / (float)detail;
        }
    }

    *outDisplayListSize = GXEndDisplayList();
    if (*outDisplayListSize > displayListSize) {
        OSReport(s_display_list_alloc_error, displayListSize, *outDisplayListSize);
        OSPanic(s_pppYmEnv_cpp, 0x19f, s_Exiting_803311CC);
    }

    DCFlushRange(displayListBuffer, *outDisplayListSize);
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
    GXColor tevColor3;
    GXColor tevColor2;
    CTextureLite* textureLite;

    GXSetNumTevStages(3);
    GXSetNumTexGens(1);

    tevColor2.r = 0xFF;
    tevColor2.g = 0xFF;
    tevColor2.b = 0;
    tevColor2.a = 0;

    tevColor3.r = 0;
    tevColor3.g = 0;
    tevColor3.b = 0xFF;
    tevColor3.a = 0xFF;

    GXSetTevColor((GXTevRegID)2, tevColor2);
    GXSetTevColor((GXTevRegID)3, tevColor3);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

    GXSetTevDirect(GX_TEVSTAGE1);
    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);

    GXSetTevDirect(GX_TEVSTAGE2);
    _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);
    _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);

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

    indMtx[0][0] = FLOAT_80331180;
    indMtx[0][1] = FLOAT_80331180;
    indMtx[0][2] = FLOAT_80331180;
    indMtx[1][0] = FLOAT_80331180;
    indMtx[1][1] = FLOAT_80331180;
    indMtx[1][2] = FLOAT_80331180;
    GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
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

    switch (modelType) {
    case 0:
        if (gObject->m_charaModelHandle != 0) {
            return gObject->m_charaModelHandle;
        }
        break;
    case 1:
        if (gObject->m_weaponModelHandle != 0) {
            return gObject->m_weaponModelHandle;
        }
        break;
    case 2:
        if (gObject->m_shieldModelHandle != 0) {
            return gObject->m_shieldModelHandle;
        }
        break;
    }

    return 0;
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
    if (handle != 0) {
        return handle->m_model;
    }

    return 0;
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
int GetTextureFromRSD(int mapMeshIndex, _pppEnvSt* env)
{
    _pppEnvStYmEnv* ymEnv = (_pppEnvStYmEnv*)env;
    int textureIndex;
    CMapMesh* mapMesh;
    CMapMesh** mapMeshArray;

    if (mapMeshIndex == 0xFFFF) {
        return 0;
    }

    mapMeshArray = ymEnv->m_mapMeshPtr;
    mapMesh = mapMeshArray[mapMeshIndex];
    textureIndex = 0;
    return reinterpret_cast<int>(mapMesh->GetTexture(ymEnv->m_materialSetPtr, textureIndex));
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
    GraphValueState* state = (GraphValueState*)object;

    velocity += acceleration;
    value += velocity;

    if (graphId == state->graphId) {
        value += addValue;
        velocity += velocityAdd;
        acceleration += accelerationAdd;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800e591c
 * PAL Size: 1808b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int GetCharaNodeFrameMatrix(_pppMngSt* mngSt, float frameAdd, float (*outMatrix)[4])
{
    void* nodeNameBase;
    CGObject* owner;
    CModelRaw* modelRaw;
    CChara::CModel* model;
    CChara::CNode* node;
    int skNodeIndex;
    int animFrameMax;
    u32 animFrameCount;
    int frameInt;
    float frame;
    float modelTime;
    Vec local88;
    Vec local94;
    Vec localA0;
    Vec localAC;
    Vec localB8;
    Vec localC4;
    Vec localD0;
    Vec localDC;
    Vec localE8;
    Vec localF4;
    Vec local100;
    Vec local10C;
    Vec local118;
    pppFMATRIX localMatrix ATTRIBUTE_ALIGN(8);

    owner = (CGObject*)mngSt->m_owner;
    if ((s32)Game.m_currentSceneId == 7) {
        nodeNameBase = (u8*)(reinterpret_cast<PartMngEditRaw*>(&PartMng)->m_recvBuff) + mngSt->m_nodeIndex * 0x60;
    } else {
        nodeNameBase = (u8*)(*(u32*)mngSt->m_pppResSet) + mngSt->m_nodeIndex * 0x60 + 0x20;
    }

    if (owner == 0) {
        return 0;
    }

    CCharaPcs::CHandle* handle = owner->m_charaModelHandle;
    if (handle == 0) {
        return 0;
    }

    model = handle->m_model;
    if (model == 0) {
        return 0;
    }

    skNodeIndex = model->SearchNodeSk((char*)nodeNameBase + 0x50);
    if (skNodeIndex == -1) {
        return 0;
    }

    modelRaw = (CModelRaw*)model;
    node = (CChara::CNode*)(modelRaw->m_nodes + skNodeIndex * 0xC0);
    modelTime = modelRaw->m_time;
    if (modelRaw->m_anim != 0) {
        animFrameCount = modelRaw->m_anim->m_frameCount;
    } else {
        animFrameCount = 0;
    }

    frameInt = (int)modelTime;
    animFrameMax = (int)(float)animFrameCount;
    int frameDiv = frameInt / animFrameMax;
    frame = (float)(frameInt - frameDiv * animFrameMax);
    if (frame < FLOAT_80331190) {
        return 0;
    }

    if (frame != FLOAT_80331180) {
        frame -= FLOAT_80331184;
    }

    model->CalcFrameMatrix(frame + frameAdd, node, outMatrix);

    switch (mngSt->m_rotationOrder) {
    case 0:
        pppGetRotMatrixXYZ(localMatrix, &mngSt->m_rotation);
        break;
    case 1:
        pppGetRotMatrixXZY(localMatrix, &mngSt->m_rotation);
        break;
    case 2:
        pppGetRotMatrixYXZ(localMatrix, &mngSt->m_rotation);
        break;
    case 3:
        pppGetRotMatrixYZX(localMatrix, &mngSt->m_rotation);
        break;
    case 4:
        pppGetRotMatrixZXY(localMatrix, &mngSt->m_rotation);
        break;
    case 5:
        pppGetRotMatrixZYX(localMatrix, &mngSt->m_rotation);
        break;
    }

    switch (mngSt->m_matrixMode) {
    case 3:
        if (mngSt->m_bindNode != 0) {
            PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &local88);
            outMatrix[0][3] += local88.x;
            outMatrix[1][3] += local88.y;
            outMatrix[2][3] += local88.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            local94.x = localMatrix.value[0][0];
            local94.y = localMatrix.value[1][0];
            local94.z = localMatrix.value[2][0];
            PSVECScale(&local94, &local94, mngSt->m_scale.x);
            localMatrix.value[0][0] = local94.x;
            localMatrix.value[1][0] = local94.y;
            localMatrix.value[2][0] = local94.z;

            localA0.x = localMatrix.value[0][1];
            localA0.y = localMatrix.value[1][1];
            localA0.z = localMatrix.value[2][1];
            PSVECScale(&localA0, &localA0, mngSt->m_scale.y);
            localMatrix.value[0][1] = localA0.x;
            localMatrix.value[1][1] = localA0.y;
            localMatrix.value[2][1] = localA0.z;

            localAC.x = localMatrix.value[0][2];
            localAC.y = localMatrix.value[1][2];
            localAC.z = localMatrix.value[2][2];
            PSVECScale(&localAC, &localAC, mngSt->m_scale.z);
            localMatrix.value[0][2] = localAC.x;
            localMatrix.value[1][2] = localAC.y;
            localMatrix.value[2][2] = localAC.z;
            goto copy_out;
        }
        break;
    case 5:
        if (mngSt->m_bindNode != 0) {
            outMatrix[0][3] += pppMngStPtr->m_position.x;
            outMatrix[1][3] += pppMngStPtr->m_position.y;
            outMatrix[2][3] += pppMngStPtr->m_position.z;
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            if (FLOAT_80331184 != mngSt->m_scale.x) {
                localB8.x = localMatrix.value[0][0];
                localB8.y = localMatrix.value[1][0];
                localB8.z = localMatrix.value[2][0];
                PSVECScale(&localB8, &localB8, mngSt->m_scale.x);
                localMatrix.value[0][0] = localB8.x;
                localMatrix.value[1][0] = localB8.y;
                localMatrix.value[2][0] = localB8.z;
            }
            if (FLOAT_80331184 != mngSt->m_scale.y) {
                localC4.x = localMatrix.value[0][1];
                localC4.y = localMatrix.value[1][1];
                localC4.z = localMatrix.value[2][1];
                PSVECScale(&localC4, &localC4, mngSt->m_scale.y);
                localMatrix.value[0][1] = localC4.x;
                localMatrix.value[1][1] = localC4.y;
                localMatrix.value[2][1] = localC4.z;
            }
            if (FLOAT_80331184 != mngSt->m_scale.z) {
                localD0.x = localMatrix.value[0][2];
                localD0.y = localMatrix.value[1][2];
                localD0.z = localMatrix.value[2][2];
                PSVECScale(&localD0, &localD0, mngSt->m_scale.z);
                localMatrix.value[0][2] = localD0.x;
                localMatrix.value[1][2] = localD0.y;
                localMatrix.value[2][2] = localD0.z;
            }
            goto copy_out;
        }
        break;
    case 6:
        if (mngSt->m_bindNode != 0) {
            PSVECNormalize((Vec*)outMatrix, (Vec*)outMatrix);
            PSVECNormalize((Vec*)&outMatrix[1][0], (Vec*)&outMatrix[1][0]);
            PSVECNormalize((Vec*)&outMatrix[2][0], (Vec*)&outMatrix[2][0]);
            PSMTXMultVecSR(outMatrix, &pppMngStPtr->m_position, &local88);
            PSMTXConcat(outMatrix, localMatrix.value, localMatrix.value);

            if (FLOAT_80331184 != mngSt->m_scale.x) {
                localDC.x = localMatrix.value[0][0];
                localDC.y = localMatrix.value[1][0];
                localDC.z = localMatrix.value[2][0];
                PSVECScale(&localDC, &localDC, mngSt->m_scale.x);
                localMatrix.value[0][0] = localDC.x;
                localMatrix.value[1][0] = localDC.y;
                localMatrix.value[2][0] = localDC.z;
            }
            if (FLOAT_80331184 != mngSt->m_scale.y) {
                localE8.x = localMatrix.value[0][1];
                localE8.y = localMatrix.value[1][1];
                localE8.z = localMatrix.value[2][1];
                PSVECScale(&localE8, &localE8, mngSt->m_scale.y);
                localMatrix.value[0][1] = localE8.x;
                localMatrix.value[1][1] = localE8.y;
                localMatrix.value[2][1] = localE8.z;
            }
            if (FLOAT_80331184 != mngSt->m_scale.z) {
                localF4.x = localMatrix.value[0][2];
                localF4.y = localMatrix.value[1][2];
                localF4.z = localMatrix.value[2][2];
                PSVECScale(&localF4, &localF4, mngSt->m_scale.z);
                localMatrix.value[0][2] = localF4.x;
                localMatrix.value[1][2] = localF4.y;
                localMatrix.value[2][2] = localF4.z;
            }

            goto copy_out;
        }
        break;
    }

    if (FLOAT_80331184 != mngSt->m_scale.x) {
        local100.x = localMatrix.value[0][0];
        local100.y = localMatrix.value[1][0];
        local100.z = localMatrix.value[2][0];
        PSVECScale(&local100, &local100, mngSt->m_scale.x);
        localMatrix.value[0][0] = local100.x;
        localMatrix.value[1][0] = local100.y;
        localMatrix.value[2][0] = local100.z;
    }
    if (FLOAT_80331184 != mngSt->m_scale.y) {
        local10C.x = localMatrix.value[0][1];
        local10C.y = localMatrix.value[1][1];
        local10C.z = localMatrix.value[2][1];
        PSVECScale(&local10C, &local10C, mngSt->m_scale.y);
        localMatrix.value[0][1] = local10C.x;
        localMatrix.value[1][1] = local10C.y;
        localMatrix.value[2][1] = local10C.z;
    }
    if (FLOAT_80331184 != mngSt->m_scale.z) {
        local118.x = localMatrix.value[0][2];
        local118.y = localMatrix.value[1][2];
        local118.z = localMatrix.value[2][2];
        PSVECScale(&local118, &local118, mngSt->m_scale.z);
        localMatrix.value[0][2] = local118.x;
        localMatrix.value[1][2] = local118.y;
        localMatrix.value[2][2] = local118.z;
    }

    localMatrix.value[0][3] = mngSt->m_position.x;
    localMatrix.value[1][3] = mngSt->m_position.y;
    localMatrix.value[2][3] = mngSt->m_position.z;

copy_out:
    PSMTXCopy(localMatrix.value, outMatrix);
    return 1;
}

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

    CChara::CModel* model = handle->m_model;
    if (handle != 0) {
        return model;
    }

    return 0;
}
