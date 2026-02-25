#include "ffcc/pppMiasma.h"
#include "ffcc/graphic.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/util.h"

#include <string.h>

extern int lbl_8032ED70;
extern float FLOAT_80331928;
extern float FLOAT_8033192c;
extern float FLOAT_80331930;
extern float FLOAT_80331934;
extern float FLOAT_80331938;
extern float FLOAT_8033193c;
extern float FLOAT_80331940;
extern void* DAT_80238030;
extern CUtil DAT_8032ec70;

extern struct {
    float _212_4_, _216_4_, _220_4_;
    float _224_4_, _228_4_, _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
} CameraPcs;

extern "C" {
void GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
void pppInitBlendMode__Fv(void);
void pppSetBlendMode__FUc(u8);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, s32);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int, int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
}

struct PppMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_pad;
    float m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CalcSphereRadius(Vec*, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CreateScaleMatrix(_pppPObject*, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80109b6c
 * PAL Size: 5604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderMiasma(pppMiasma* pppMiasma, void* param_2, pppMiasmaCtrl* param_3)
{
    PppMiasmaRenderStep* step;
    pppModelSt* model;
    s16* work;
    u8 packedWork[4];
    u32 packedColor;
    Vec managerPos;
    Vec cameraPos;
    float radius;
    float maxRadius;
    float radiusScale;
    int texWidth;
    int texHeight;
    int i4TexSize;
    int rgba8TexSize;
    int colorOffset;
    int textureIndex;
    int yOffset;
    u32 colorRaw;
    u16 i;
    u32 slice;
    u8 tevSwapChannel;
    u8 tevAlphaScale;
    bool inFarZone;
    GXTexObj backI4Tex;
    GXTexObj backRgba8Tex;
    GXTexObj backRgba8Tex2;
    Mtx scaleMtx;
    Mtx localMtx;
    Mtx44 screenMtx;
    GXColor drawColor;
    GXColor workColor;
    GXColor stepColor;
    u8* meshColor;
    Vec quadA;
    Vec quadB;

    Graphic.SetDrawDoneDebugData(0x31);

    step = (PppMiasmaRenderStep*)param_2;
    work = (s16*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[2]);
    colorOffset = param_3->m_serializedDataOffsets[1];
    radiusScale = *(float*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[3]);

    textureIndex = 0;
    model = (pppModelSt*)(((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex]);
    GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);

    if (step->m_payload[0x1e] == 0xFF) {
        step->m_payload[0x1e] = 0xFE;
    }

    packedColor = *(u32*)((u8*)pppMiasma + 0x88 + colorOffset);
    packedWork[0] = (u8)(work[0] >> 7);
    packedWork[1] = (u8)(work[1] >> 7);
    packedWork[2] = (u8)(work[2] >> 7);
    packedWork[3] = (u8)(work[3] >> 7);

    texWidth = (int)FLOAT_80331928;
    texHeight = (int)FLOAT_8033192c;
    i4TexSize = GXGetTexBufferSize(texWidth, texHeight, (GXTexFmt)6, GX_FALSE, 0);
    rgba8TexSize = GXGetTexBufferSize(texWidth, texHeight, (GXTexFmt)0x28, GX_FALSE, 0);

    managerPos.x = pppMngStPtr->m_matrix.value[0][3];
    managerPos.y = pppMngStPtr->m_matrix.value[1][3];
    managerPos.z = pppMngStPtr->m_matrix.value[2][3];

    if (Game.game.m_currentSceneId == 7) {
        float* radiusArray;
        u16 meshCount;

        cameraPos.x = ppvCameraMatrix0[0][3];
        cameraPos.y = ppvCameraMatrix0[1][3];
        cameraPos.z = ppvCameraMatrix0[2][3];
        maxRadius = FLOAT_80331930;

        meshCount = *(u16*)((u8*)&model->m_mapMesh + 0x0);
        radiusArray = *(float**)((u8*)&model->m_mapMesh + 0x2c);
        for (i = 0; i < meshCount; i++) {
            radius = radiusArray[i * 3];
            if (maxRadius < radius) {
                maxRadius = radius;
            }
        }
    } else {
        cameraPos.x = CameraPcs._224_4_;
        cameraPos.y = CameraPcs._228_4_;
        cameraPos.z = CameraPcs._232_4_;
        maxRadius = FLOAT_80331934;
    }

    maxRadius = maxRadius * radiusScale;
    if (Game.game.m_currentSceneId != 7) {
        Game.game.unkFloat_0xca10 = maxRadius;
    }

    inFarZone = (FLOAT_80331938 + maxRadius) <= PSVECDistance(&cameraPos, &managerPos);

    drawColor.r = inFarZone ? 0 : 0xFF;
    drawColor.g = drawColor.r;
    drawColor.b = drawColor.r;
    drawColor.a = 0xFF;

    for (slice = 0; slice < 2; slice++) {
        yOffset = (int)((float)slice * FLOAT_8033192c);

        Graphic.GetBackBufferRect2(DAT_80238030, &backI4Tex, 0, yOffset, texWidth, texHeight, 0, GX_LINEAR, GX_TF_I4, 0);
        GXSetScissor(0, yOffset, (u32)FLOAT_80331928, (u32)FLOAT_8033192c);

        DAT_8032ec70.RenderColorQuad(FLOAT_8033193c, (float)yOffset, FLOAT_80331928, FLOAT_8033192c, drawColor);

        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            &drawColor, (u8*)pppMiasma + 0x40, FLOAT_8033193c, 0, 0, 1, 0, 1, 1, 1);

        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

        GXClearVtxDesc();
        GXSetVtxDesc((GXAttr)9, GX_INDEX8);
        GXSetVtxDesc((GXAttr)10, GX_INDEX8);
        GXSetVtxDesc((GXAttr)0xB, GX_INDEX8);
        GXSetVtxDesc((GXAttr)0xD, GX_INDEX8);

        meshColor = *(u8**)((u8*)&model->m_mapMesh + 0x3C);
        meshColor[0] = 0xFF;
        meshColor[1] = 0xFF;
        meshColor[2] = 0xFF;
        meshColor[3] = 0xFF;
        colorRaw = *(u32*)meshColor;
        GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*)&colorRaw);
        GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&colorRaw);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXLoadPosMtxImm(*(Mtx*)((u8*)pppMiasma + 0x40), 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(0);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        GXSetProjection(screenMtx, GX_ORTHOGRAPHIC);
        PSMTXScale(scaleMtx, FLOAT_80331940, FLOAT_80331940, FLOAT_80331940);
        PSMTXConcat(scaleMtx, *(Mtx*)((u8*)pppMiasma + 4), localMtx);
        PSMTXConcat(ppvWorldMatrix, localMtx, *(Mtx*)((u8*)pppMiasma + 0x40));
        GXLoadPosMtxImm(*(Mtx*)((u8*)pppMiasma + 0x40), 0);

        GXSetTevDirect(GX_TEVSTAGE0);
        pppInitBlendMode__Fv();
        pppSetBlendMode__FUc(1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
            0, 0xF, 0xF, 0xF, 0xC);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 2, 1, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
            0, 7, 7, 7, 6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 2, 1, 0);

        if (inFarZone) {
            Graphic.SetDrawDoneDebugData(0x32);
            pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)pppMiasma + 0x70), 0);
            Graphic.SetDrawDoneDebugData(0x33);
        }

        pppInitBlendMode__Fv();
        pppSetBlendMode__FUc(2);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
            0, 0xF, 0xF, 0xF, 0xC);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 2, 1, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
            0, 7, 7, 7, 6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 2, 1, 0);

        Graphic.SetDrawDoneDebugData(0x34);
        pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)pppMiasma + 0x70), 0);
        Graphic.SetDrawDoneDebugData(0x35);

        Graphic.GetBackBufferRect2(DAT_80238030, &backRgba8Tex, 0, yOffset, texWidth, texHeight, i4TexSize, GX_LINEAR,
                                   GX_TF_RGBA8, 0);
        if (step->m_payload[0x1D] != 0) {
            DAT_8032ec70.RenderColorQuad(FLOAT_8033193c, (float)yOffset, FLOAT_80331928, FLOAT_8033192c, drawColor);
            Graphic.GetBackBufferRect2(DAT_80238030, &backRgba8Tex2, 0, yOffset, texWidth, texHeight, i4TexSize + rgba8TexSize,
                                       GX_LINEAR, GX_TF_RGBA8, 0);
        }

        Graphic.SetViewport();
        DAT_8032ec70.RenderTextureQuad(FLOAT_8033193c, (float)yOffset, FLOAT_80331928, FLOAT_8033192c, &backI4Tex, 0, 0,
                                       0, (GXBlendFactor)4, (GXBlendFactor)5);
        DAT_8032ec70.BeginQuadEnv();
        DAT_8032ec70.SetVtxFmt_POS_CLR_TEX0_TEX1();

        if ((u8)step->m_initWOrk == 0) {
            tevSwapChannel = 0;
        } else if ((u8)step->m_initWOrk == 1) {
            tevSwapChannel = 1;
        } else {
            tevSwapChannel = 2;
        }

        if ((u8)step->m_arg3 != 2) {
            tevAlphaScale = step->m_payload[0x1e];
            stepColor.r = tevAlphaScale;
            stepColor.g = tevAlphaScale;
            stepColor.b = tevAlphaScale;
            stepColor.a = tevAlphaScale;
            GXSetTevKColor((GXTevKColorID)0, stepColor);
            pppSetBlendMode__FUc(0);
            GXSetChanMatColor(GX_COLOR0A0, *(GXColor*)&packedColor);
            GXSetNumTexGens(2);
            _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
                1, tevSwapChannel, tevSwapChannel, tevSwapChannel, tevSwapChannel);

            GXSetTevDirect((GXTevStageID)0);
            GXLoadTexObj(&backRgba8Tex, GX_TEXMAP0);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 0xC, 0xC);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 1, 0, 0, 1, 1);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 4, 6, 6);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 1, 0, 0, 1, 1);

            GXSetTevDirect((GXTevStageID)1);
            GXSetTevKColorSel((GXTevStageID)1, (GXTevKColorSel)0xC);
            GXSetTevKAlphaSel((GXTevStageID)1, (GXTevKAlphaSel)0x1C);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 0, 4);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 1);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 2, 0xE, 0xE, 0xF);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 8, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 1, 6, 6, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 8, 0, 0, 1, 0);

            GXSetTevDirect((GXTevStageID)2);
            GXSetTevKColorSel((GXTevStageID)2, (GXTevKColorSel)0xC);
            GXSetTevKAlphaSel((GXTevStageID)2, (GXTevKAlphaSel)0x1C);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0, 0, 4);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 1);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xE, 2, 2, 0);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 8, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 6, 1, 1, 0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 8, 0, 0, 1, 0);

            GXSetTevDirect((GXTevStageID)3);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(3, 0, 0, 4);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3, 0, 1);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(3, 0xF, 0, 10, 0xF);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(3, 7, 0, 5, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(3, 0, 0, 0, 1, 0);

            GXSetTevDirect((GXTevStageID)4);
            GXLoadTexObj(&backI4Tex, GX_TEXMAP1);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(4, 0, 1);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(4, 1, 1, 4);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(4, 0xF, 0xF, 0xF, 0);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(4, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(4, 7, 4, 0, 7);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(4, 0, 0, 0, 1, 0);
            GXSetNumTevStages(5);

            quadA.x = FLOAT_8033193c;
            quadA.y = (float)yOffset;
            quadA.z = FLOAT_8033193c;
            quadB.x = FLOAT_80331928;
            quadB.y = (float)yOffset + FLOAT_8033192c;
            quadB.z = FLOAT_8033193c;

            pppInitBlendMode__Fv();
            pppSetBlendMode__FUc(0);
            if ((u8)step->m_arg3 != 2) {
                DAT_8032ec70.RenderQuadTex2(quadA, quadB, *(GXColor*)&packedColor, 0, 0);
            }
        }

        DAT_8032ec70.InitConstantRegister();
        DAT_8032ec70.BeginQuadEnv();
        DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
        if ((u8)step->m_arg3 != 1) {
            GXSetTevDirect((GXTevStageID)0);
            GXLoadTexObj(&backRgba8Tex, GX_TEXMAP0);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
            _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
                2, tevSwapChannel, tevSwapChannel, tevSwapChannel, tevSwapChannel);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 2);

            pppInitBlendMode__Fv();
            pppSetBlendMode__FUc(1);
            drawColor.r = 0xFF;
            drawColor.g = 0xFF;
            drawColor.b = 0xFF;
            drawColor.a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*)&drawColor);
            workColor = *(GXColor*)packedWork;
            GXSetChanMatColor(GX_COLOR0A0, workColor);
            GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            GXSetNumChans(1);

            if (step->m_payload[0x1D] == 0) {
                GXSetTevDirect((GXTevStageID)0);
                GXLoadTexObj(&backRgba8Tex, GX_TEXMAP0);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 0xF, 0xF, 10);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 6, 4, 6);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 1, 0, 0, 1, 0);

                GXSetTevDirect((GXTevStageID)1);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 0, 4);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 0xF, 0xF, 0);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 0, 4, 7);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);

                GXSetTevDirect((GXTevStageID)2);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 1, 1, 4);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0xB, 0, 0xF);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 5, 7);

                tevAlphaScale = 0;
                if (step->m_payload[0x1C] == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_payload[0x1C] == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, tevAlphaScale, 1, 0);
            } else {
                GXLoadTexObj(&backRgba8Tex, GX_TEXMAP0);
                GXLoadTexObj(&backRgba8Tex2, GX_TEXMAP1);

                GXSetTevDirect((GXTevStageID)0);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 10, 8, 0xF);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 5, 4, 7);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

                GXSetTevDirect((GXTevStageID)1);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 4);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8, 0xC, 0);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 1, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 4, 6, 0);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 1, 0, 2, 1, 0);

                GXSetTevDirect((GXTevStageID)2);
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0, 1, 4);
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0xB, 0, 0xF);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0, 5, 7);
                tevAlphaScale = 0;
                if (step->m_payload[0x1C] == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_payload[0x1C] == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, tevAlphaScale, 1, 0);
            }

            GXSetNumTevStages(3);
            GXSetNumTexGens(1);
            quadA.x = FLOAT_8033193c;
            quadA.y = (float)yOffset;
            quadA.z = FLOAT_8033193c;
            quadB.x = FLOAT_80331928;
            quadB.y = (float)yOffset + FLOAT_8033192c;
            quadB.z = FLOAT_8033193c;
            DAT_8032ec70.RenderQuad(quadA, quadB, *(GXColor*)packedWork, 0, 0);
        }

        DAT_8032ec70.InitConstantRegister();
    }

    DAT_8032ec70.EndQuadEnv();
    pppInitBlendMode__Fv();
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    Graphic.SetViewport();
    DAT_8032ec70.InitConstantRegister();
}

/*
 * --INFO--
 * PAL Address: 0x80109b08
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructMiasma(pppMiasma* pppMiasma, pppMiasmaCtrl* param_2)
{
    u8* work;

    work = (u8*)pppMiasma + 0x80 + param_2->m_serializedDataOffsets[2];
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
}

/*
 * --INFO--
 * PAL Address: 0x80109aa4
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2Miasma(pppMiasma* pppMiasma, pppMiasmaCtrl* param_2)
{
    u8* work;

    work = (u8*)pppMiasma + 0x80 + param_2->m_serializedDataOffsets[2];
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
}

/*
 * --INFO--
 * PAL Address: 0x80109aa0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructMiasma(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80109930
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameMiasma(pppMiasma* pppMiasma, pppMiasmaFrameStep* param_2, pppMiasmaCtrl* param_3)
{
    s16* work;

    if (lbl_8032ED70 != 0) {
        return;
    }

    work = (s16*)((u8*)pppMiasma + 0x80 + param_3->m_serializedDataOffsets[2]);
    work[4] = work[4] + work[8];
    work[0] = work[0] + work[4];
    work[5] = work[5] + work[9];
    work[1] = work[1] + work[5];
    work[6] = work[6] + work[10];
    work[2] = work[2] + work[6];
    work[7] = work[7] + work[11];
    work[3] = work[3] + work[7];

    if (pppMiasma->m_graphId != param_2->m_graphId) {
        return;
    }

    work[0] = work[0] + param_2->m_addPosX;
    work[1] = work[1] + param_2->m_addPosY;
    work[2] = work[2] + param_2->m_addPosZ;
    work[3] = work[3] + param_2->m_addPosW;
    work[4] = work[4] + param_2->m_addVelX;
    work[5] = work[5] + param_2->m_addVelY;
    work[6] = work[6] + param_2->m_addVelZ;
    work[7] = work[7] + param_2->m_addVelW;
    work[8] = work[8] + param_2->m_addAccX;
    work[9] = work[9] + param_2->m_addAccY;
    work[10] = work[10] + param_2->m_addAccZ;
    work[11] = work[11] + param_2->m_addAccW;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}
