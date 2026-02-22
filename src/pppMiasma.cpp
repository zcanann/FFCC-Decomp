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
    float _224_4_, _228_4_, _232_4_;
} CameraPcs;

extern "C" {
void GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh*, CMaterialSet*, int&);
void pppInitBlendMode__Fv(void);
void pppSetBlendMode__FUc(u8);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, s32);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
}

struct PppMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_payload[0x20];
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
    bool inFarZone;
    GXTexObj backI4Tex;
    GXTexObj backRgba8Tex;
    GXTexObj backRgba8Tex2;
    Mtx scaleMtx;
    Mtx localMtx;
    GXColor drawColor;
    u8* meshColor;

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
            &drawColor, (u8*)pppMiasma + 0x40, FLOAT_8033193c, 0, 1, 0, 1, 1, 1, 0);

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

        GXSetNumTevStages(1);
        GXSetNumTexGens(0);
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
    }

    Graphic.SetViewport();

    (void)work;
    (void)packedWork;
    (void)packedColor;
    (void)textureIndex;
    (void)backI4Tex;
    (void)backRgba8Tex;
    (void)backRgba8Tex2;
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
