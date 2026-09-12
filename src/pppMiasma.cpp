#include "ffcc/pppMiasma.h"
#include "ffcc/graphic.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/mapmesh.h"
#include "ffcc/gxfunc.h"
#include "ffcc/util.h"

#include <string.h>

static const float kPppMiasmaMinRadius = -1000.0f;
static const float kPppMiasmaDefaultRadius = 1200.0f;
static const float kPppMiasmaCameraInsidePadding = 10.0f;
static const float kPppMiasmaZero = 0.0f;
static const float kPppMiasmaOne = 1.0f;

union PackedMiasmaColor {
    GXColor color;
    u32 raw;
    u8 bytes[4];
};

struct MiasmaFrameWork {
    s16 m_position[4];
    s16 m_velocity[4];
    s16 m_accel[4];
};

struct MiasmaRadiusWork {
    float m_scale;
};

STATIC_ASSERT(offsetof(MiasmaFrameWork, m_position) == 0x00);
STATIC_ASSERT(offsetof(MiasmaFrameWork, m_velocity) == 0x08);
STATIC_ASSERT(offsetof(MiasmaFrameWork, m_accel) == 0x10);
STATIC_ASSERT(sizeof(MiasmaFrameWork) == 0x18);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x08);
STATIC_ASSERT(sizeof(MiasmaRadiusWork) == 0x04);

STATIC_ASSERT(sizeof(MiasmaDataOffsets) == 0x10);
STATIC_ASSERT(offsetof(MiasmaDataOffsets, m_colorWorkOffset) == 0x4);
STATIC_ASSERT(offsetof(MiasmaDataOffsets, m_frameWorkOffset) == 0x8);
STATIC_ASSERT(offsetof(MiasmaDataOffsets, m_radiusWorkOffset) == 0xC);

static inline MiasmaDataOffsets* GetMiasmaDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<MiasmaDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline MiasmaFrameWork* GetMiasmaFrameWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<MiasmaFrameWork*>(miasma->m_workArea + GetMiasmaDataOffsets(ctrl)->m_frameWorkOffset);
}

static inline VColor* GetMiasmaColorWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(miasma->m_workArea + GetMiasmaDataOffsets(ctrl)->m_colorWorkOffset);
}

static inline MiasmaRadiusWork* GetMiasmaRadiusWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<MiasmaRadiusWork*>(miasma->m_workArea + GetMiasmaDataOffsets(ctrl)->m_radiusWorkOffset);
}

static inline void _GXSetTevOrder(int stage, int texCoord, int texMap, int colorChannel)
{
    _GXSetTevOrder((_GXTevStageID)stage, (_GXTexCoordID)texCoord, (_GXTexMapID)texMap, (_GXChannelID)colorChannel);
}

static inline void _GXSetTevSwapMode(int stage, int rasSel, int texSel)
{
    _GXSetTevSwapMode((_GXTevStageID)stage, (_GXTevSwapSel)rasSel, (_GXTevSwapSel)texSel);
}

static inline void _GXSetTevSwapModeTable(int tevSwapSel, int red, int green, int blue, int alpha)
{
    _GXSetTevSwapModeTable((_GXTevSwapSel)tevSwapSel, (_GXTevColorChan)red, (_GXTevColorChan)green,
                           (_GXTevColorChan)blue, (_GXTevColorChan)alpha);
}

static inline void _GXSetTevColorIn(int stage, int a, int b, int c, int d)
{
    _GXSetTevColorIn((_GXTevStageID)stage, (_GXTevColorArg)a, (_GXTevColorArg)b, (_GXTevColorArg)c,
                     (_GXTevColorArg)d);
}

static inline void _GXSetTevColorOp(int stage, int op, int bias, int scale, int clamp, int reg)
{
    _GXSetTevColorOp((_GXTevStageID)stage, (_GXTevOp)op, (_GXTevBias)bias, (_GXTevScale)scale,
                     (unsigned char)clamp, (_GXTevRegID)reg);
}

static inline void _GXSetTevAlphaIn(int stage, int a, int b, int c, int d)
{
    _GXSetTevAlphaIn((_GXTevStageID)stage, (_GXTevAlphaArg)a, (_GXTevAlphaArg)b, (_GXTevAlphaArg)c,
                     (_GXTevAlphaArg)d);
}

static inline void _GXSetTevAlphaOp(int stage, int op, int bias, int scale, int clamp, int reg)
{
    _GXSetTevAlphaOp((_GXTevStageID)stage, (_GXTevOp)op, (_GXTevBias)bias, (_GXTevScale)scale,
                     (unsigned char)clamp, (_GXTevRegID)reg);
}

static inline float CalcSphereRadius(Vec* vertices, u16 count)
{
    const float& minRadius = kPppMiasmaMinRadius;
    float radius = minRadius;

    for (u16 i = 0; i < count; i++) {
        if (radius < vertices[i].x) {
            radius = vertices[i].x;
        }
    }

    return radius;
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
void pppFrameMiasma(pppMiasma* pppMiasma, pppMiasmaFrameStep* step, _pppCtrlTable* ctrl)
{
    MiasmaFrameWork* work;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetMiasmaFrameWork(pppMiasma, ctrl);
    work->m_velocity[0] = work->m_velocity[0] + work->m_accel[0];
    work->m_position[0] = work->m_position[0] + work->m_velocity[0];
    work->m_velocity[1] = work->m_velocity[1] + work->m_accel[1];
    work->m_position[1] = work->m_position[1] + work->m_velocity[1];
    work->m_velocity[2] = work->m_velocity[2] + work->m_accel[2];
    work->m_position[2] = work->m_position[2] + work->m_velocity[2];
    work->m_velocity[3] = work->m_velocity[3] + work->m_accel[3];
    work->m_position[3] = work->m_position[3] + work->m_velocity[3];

    if (pppMiasma->m_graphId != step->m_graphId) {
        return;
    }

    work->m_position[0] = work->m_position[0] + step->m_addPosX;
    work->m_position[1] = work->m_position[1] + step->m_addPosY;
    work->m_position[2] = work->m_position[2] + step->m_addPosZ;
    work->m_position[3] = work->m_position[3] + step->m_addPosW;
    work->m_velocity[0] = work->m_velocity[0] + step->m_addVelX;
    work->m_velocity[1] = work->m_velocity[1] + step->m_addVelY;
    work->m_velocity[2] = work->m_velocity[2] + step->m_addVelZ;
    work->m_velocity[3] = work->m_velocity[3] + step->m_addVelW;
    work->m_accel[0] = work->m_accel[0] + step->m_addAccX;
    work->m_accel[1] = work->m_accel[1] + step->m_addAccY;
    work->m_accel[2] = work->m_accel[2] + step->m_addAccZ;
    work->m_accel[3] = work->m_accel[3] + step->m_addAccW;
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
void pppDestructMiasma(pppMiasma*, _pppCtrlTable*)
{
    return;
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
void pppConstruct2Miasma(pppMiasma* pppMiasma, _pppCtrlTable* ctrl)
{
    MiasmaFrameWork* work;

    work = GetMiasmaFrameWork(pppMiasma, ctrl);
    memset(work->m_position, 0, sizeof(work->m_position));
    memset(work->m_velocity, 0, sizeof(work->m_velocity));
    memset(work->m_accel, 0, sizeof(work->m_accel));
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
void pppConstructMiasma(pppMiasma* pppMiasma, _pppCtrlTable* ctrl)
{
    MiasmaFrameWork* work;

    work = GetMiasmaFrameWork(pppMiasma, ctrl);
    memset(work->m_position, 0, sizeof(work->m_position));
    memset(work->m_velocity, 0, sizeof(work->m_velocity));
    memset(work->m_accel, 0, sizeof(work->m_accel));
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
void pppRenderMiasma(pppMiasma* pppMiasma, pppMiasmaRenderStep* step, _pppCtrlTable* ctrl)
{
    pppModelSt* model;
    MiasmaFrameWork* work;
    VColor* colorWork;
    MiasmaRadiusWork* radiusWork;
    pppCVECTOR drawColor;
    PackedMiasmaColor packedWork;
    int textureIndex;
    PackedMiasmaColor packedColor;
    Vec quadA;
    Vec quadB;
    Vec cameraPos;
    Vec managerPos;
    float secondaryScale;
    float maxRadius;
    float scaledRadius;
    int texWidth;
    int texHeight;
    u32 scissorWidth;
    u32 scissorHeight;
    int sceneTexSize;
    int maskTexSize;
    int yOffset;
    float yPos;
    int slice;
    int tevSwapChannel;
    int tevAlphaScale;
    int tevStageCount;
    int texGenCount;
    int isCameraInside;
    CGraphic* graphicPtr;
    GXTexObj backSceneTex;
    GXTexObj miasmaMaskTex;
    GXTexObj secondaryMaskTex;
    Mtx44 screenMtx;
    Mtx firstLocalMtx;
    Mtx firstScaleMtx;
    Mtx secondLocalMtx;
    Mtx secondScaleMtx;
    GXColor stepColor;

    Graphic.SetDrawDoneDebugData(0x31);

    work = GetMiasmaFrameWork(pppMiasma, ctrl);
    colorWork = GetMiasmaColorWork(pppMiasma, ctrl);
    radiusWork = GetMiasmaRadiusWork(pppMiasma, ctrl);

    textureIndex = 0;
    slice = 0;
    model = (pppModelSt*)ppvEnv->m_mapMeshPtr[step->m_dataValIndex];
    model->GetTexture(ppvEnv->m_materialSetPtr, textureIndex);

    if (step->m_miasma.m_alphaScale == 0xFF) {
        step->m_miasma.m_alphaScale = 0xFE;
    }

    packedColor.color.r = colorWork->m_color.rgba[0];
    packedColor.color.g = colorWork->m_color.rgba[1];
    packedColor.color.b = colorWork->m_color.rgba[2];
    packedColor.color.a = colorWork->m_color.rgba[3];
    packedWork.bytes[0] = (u8)(work->m_position[0] >> 7);
    packedWork.bytes[1] = (u8)(work->m_position[1] >> 7);
    packedWork.bytes[2] = (u8)(work->m_position[2] >> 7);
    packedWork.bytes[3] = (u8)(work->m_position[3] >> 7);

    sceneTexSize = GXGetTexBufferSize(640, 224, GX_TF_RGBA8, GX_FALSE, 0);
    maskTexSize = GXGetTexBufferSize(640, 224, GX_CTF_R8, GX_FALSE, 0);

    managerPos.x = ppvMng->m_matrix.value[0][3];
    managerPos.y = ppvMng->m_matrix.value[1][3];
    managerPos.z = ppvMng->m_matrix.value[2][3];

    isCameraInside = 0;
    if ((s32)Game.m_currentSceneId == 7) {
        cameraPos.x = ppvCameraMatrix[0][3];
        cameraPos.y = ppvCameraMatrix[1][3];
        cameraPos.z = ppvCameraMatrix[2][3];
        maxRadius = CalcSphereRadius(model->m_vertices, model->m_vertexCount);
    } else {
        cameraPos.x = CameraPcs.m_positionX;
        cameraPos.y = CameraPcs.m_positionY;
        cameraPos.z = CameraPcs.m_positionZ;
        const float& defaultRadius = kPppMiasmaDefaultRadius;
        maxRadius = defaultRadius;
    }

    scaledRadius = maxRadius * radiusWork->m_scale;
    if ((s32)Game.m_currentSceneId != 7) {
        Game.unkFloat_0xca10 = scaledRadius;
    }

    const float& cameraInsidePadding = kPppMiasmaCameraInsidePadding;
    if ((cameraInsidePadding + scaledRadius) > PSVECDistance(&cameraPos, &managerPos)) {
        isCameraInside = 1;
    }

    texHeight = 224;
    texWidth = 640;
    scissorHeight = 224;
    scissorWidth = 640;
    const float yStep = 224.0f;
    graphicPtr = &Graphic;
    do {
        yPos = (float)slice * yStep;
        yOffset = (int)yPos;

        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backSceneTex, 0, yOffset, texWidth, texHeight, 0, GX_LINEAR,
                                   GX_TF_RGBA8, 0);
        GXSetScissor(0, (u32)yPos, scissorWidth, scissorHeight);

        if (isCameraInside) {
            drawColor.rgba[0] = 0xFF;
            drawColor.rgba[1] = 0xFF;
            drawColor.rgba[2] = 0xFF;
            drawColor.rgba[3] = 0xFF;
        } else {
            drawColor.rgba[0] = 0;
            drawColor.rgba[1] = 0;
            drawColor.rgba[2] = 0;
            drawColor.rgba[3] = 0xFF;
        }
        gUtil.RenderColorQuad(kPppMiasmaZero, yPos, 640.0f,
                              224.0f, *(GXColor*)drawColor.rgba);

        pppSetDrawEnv(
            &drawColor, &pppMiasma->m_drawMatrix, kPppMiasmaZero, 0, 0, 1, 0, 1, 1, 1);

        _GXSetTevOrder(0, 0xFF, 0xFF, 4);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);

        model->m_colors->r = 0xFF;
        model->m_colors->g = 0xFF;
        model->m_colors->b = 0xFF;
        model->m_colors->a = 0xFF;
        GXSetChanAmbColor(GX_COLOR0A0, *model->m_colors);
        GXSetChanMatColor(GX_COLOR0A0, *model->m_colors);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

        GXLoadPosMtxImm(pppMiasma->m_drawMatrix.value, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(0);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        GXSetProjection(screenMtx, GX_PERSPECTIVE);
        PSMTXScale(firstScaleMtx, kPppMiasmaOne, kPppMiasmaOne, kPppMiasmaOne);
        PSMTXConcat(firstScaleMtx, pppMiasma->m_localMatrix.value, firstLocalMtx);
        PSMTXConcat(ppvWorldMatrix, firstLocalMtx, pppMiasma->m_drawMatrix.value);
        GXLoadPosMtxImm(pppMiasma->m_drawMatrix.value, 0);

        GXSetTevDirect(GX_TEVSTAGE0);
        pppInitBlendMode();
        pppSetBlendMode(1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        _GXSetTevColorIn(
            0, 0xF, 0xF, 0xF, 0xC);
        _GXSetTevColorOp(0, 0, 0, 2, 1, 0);
        _GXSetTevAlphaIn(
            0, 7, 7, 7, 6);
        _GXSetTevAlphaOp(0, 0, 0, 2, 1, 0);

        if (!isCameraInside) {
            Graphic.SetDrawDoneDebugData(0x32);
            pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
            Graphic.SetDrawDoneDebugData(0x33);
        }

        pppInitBlendMode();
        pppSetBlendMode(2);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        _GXSetTevColorIn(
            0, 0xF, 0xF, 0xF, 0xC);
        _GXSetTevColorOp(0, 0, 0, 2, 1, 0);
        _GXSetTevAlphaIn(
            0, 7, 7, 7, 6);
        _GXSetTevAlphaOp(0, 0, 0, 2, 1, 0);

        Graphic.SetDrawDoneDebugData(0x34);
        pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
        graphicPtr->SetDrawDoneDebugData(0x35);

        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &miasmaMaskTex, 0, yOffset, texWidth, texHeight, sceneTexSize,
                                   GX_LINEAR, GX_CTF_R8, 0);
        if (step->m_miasma.m_useSecondaryMask != 0) {
            if (isCameraInside) {
                drawColor.rgba[0] = 0xFF;
                drawColor.rgba[1] = 0xFF;
                drawColor.rgba[2] = 0xFF;
                drawColor.rgba[3] = 0xFF;
            } else {
                drawColor.rgba[0] = 0;
                drawColor.rgba[1] = 0;
                drawColor.rgba[2] = 0;
                drawColor.rgba[3] = 0xFF;
            }
            gUtil.RenderColorQuad(kPppMiasmaZero, yPos, 640.0f,
                                  224.0f, *(GXColor*)drawColor.rgba);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
            GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
            GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
            GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);

            model->m_colors->r = 0xFF;
            model->m_colors->g = 0xFF;
            model->m_colors->b = 0xFF;
            model->m_colors->a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, *model->m_colors);
            GXSetChanMatColor(GX_COLOR0A0, *model->m_colors);
            GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            GXLoadPosMtxImm(pppMiasma->m_drawMatrix.value, 0);
            GXSetNumTevStages(1);
            GXSetNumTexGens(0);
            GXSetTevDirect(GX_TEVSTAGE0);
            pppInitBlendMode();
            pppSetBlendMode(1);
            GXSetCullMode(GX_CULL_FRONT);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

            secondaryScale = kPppMiasmaOne - step->m_stepValue;
            PSMTXScale(secondScaleMtx, secondaryScale, secondaryScale, secondaryScale);
            PSMTXConcat(secondScaleMtx, pppMiasma->m_localMatrix.value, secondLocalMtx);
            PSMTXConcat(ppvWorldMatrix, secondLocalMtx, pppMiasma->m_drawMatrix.value);
            GXLoadPosMtxImm(pppMiasma->m_drawMatrix.value, 0);

            _GXSetTevColorIn(
                0, 0xF, 0xF, 0xF, 0xC);
            _GXSetTevColorOp(0, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(
                0, 7, 7, 7, 6);
            _GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);

            if (!isCameraInside) {
                Graphic.SetDrawDoneDebugData(0x36);
                pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
                Graphic.SetDrawDoneDebugData(0x37);
            }

            GXSetTevDirect(GX_TEVSTAGE0);
            pppInitBlendMode();
            pppSetBlendMode(2);
            GXSetCullMode(GX_CULL_BACK);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            _GXSetTevColorIn(
                0, 0xF, 0xF, 0xF, 0xC);
            _GXSetTevColorOp(0, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(
                0, 7, 7, 7, 6);
            _GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);

            Graphic.SetDrawDoneDebugData(0x38);
            pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
            Graphic.SetDrawDoneDebugData(0x39);

            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &secondaryMaskTex, 0, yOffset, texWidth, texHeight,
                                       sceneTexSize + maskTexSize, GX_LINEAR, GX_CTF_R8, 0);
        }

        Graphic.SetViewport();
        gUtil.RenderTextureQuad(kPppMiasmaZero, yPos, 640.0f,
                                224.0f, &backSceneTex, 0, 0,
                                0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        gUtil.BeginQuadEnv();
        gUtil.SetVtxFmt_POS_CLR_TEX0_TEX1();

        if (step->m_initWOrk == 0) {
            tevSwapChannel = 0;
        } else if (step->m_initWOrk == 1) {
            tevSwapChannel = 1;
        } else {
            tevSwapChannel = 2;
        }

        if (step->m_arg3 != 2) {
            tevAlphaScale = step->m_miasma.m_alphaScale;
            stepColor.r = tevAlphaScale;
            stepColor.g = tevAlphaScale;
            stepColor.b = tevAlphaScale;
            stepColor.a = tevAlphaScale;
            GXSetTevKColor(GX_KCOLOR0, stepColor);
            pppSetBlendMode(0);
            GXSetChanMatColor(GX_COLOR0A0, packedColor.color);
            GXSetNumTexGens(2);
            _GXSetTevSwapModeTable(
                1, tevSwapChannel, tevSwapChannel, tevSwapChannel, tevSwapChannel);

            GXSetTevDirect(GX_TEVSTAGE0);
            GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(0, 0, 0, 4);
            _GXSetTevSwapMode(0, 0, 1);
            _GXSetTevColorIn(0, 0xF, 8, 0xC, 0xC);
            _GXSetTevColorOp(0, 1, 0, 0, 1, 1);
            _GXSetTevAlphaIn(0, 7, 4, 6, 6);
            _GXSetTevAlphaOp(0, 1, 0, 0, 1, 1);

            GXSetTevDirect(GX_TEVSTAGE1);
            GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(1, 0, 0, 4);
            _GXSetTevSwapMode(1, 0, 1);
            _GXSetTevColorIn(1, 2, 0xE, 0xE, 0xF);
            _GXSetTevColorOp(1, 8, 0, 0, 1, 0);
            _GXSetTevAlphaIn(1, 1, 6, 6, 7);
            _GXSetTevAlphaOp(1, 8, 0, 0, 1, 0);

            GXSetTevDirect(GX_TEVSTAGE2);
            GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_K0_A);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(2, 0, 0, 4);
            _GXSetTevSwapMode(2, 0, 1);
            _GXSetTevColorIn(2, 0xE, 2, 2, 0);
            _GXSetTevColorOp(2, 8, 0, 0, 1, 0);
            _GXSetTevAlphaIn(2, 6, 1, 1, 0);
            _GXSetTevAlphaOp(2, 8, 0, 0, 1, 0);

            GXSetTevDirect(GX_TEVSTAGE3);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(3, 0, 0, 4);
            _GXSetTevSwapMode(3, 0, 1);
            _GXSetTevColorIn(3, 0xF, 0, 10, 0xF);
            _GXSetTevColorOp(3, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(3, 7, 0, 5, 7);
            _GXSetTevAlphaOp(3, 0, 0, 0, 1, 0);

            GXSetTevDirect(GX_TEVSTAGE4);
            GXLoadTexObj(&backSceneTex, GX_TEXMAP1);
            _GXSetTevSwapMode(4, 0, 1);
            _GXSetTevOrder(4, 1, 1, 4);
            _GXSetTevColorIn(4, 0xF, 0xF, 0xF, 0);
            _GXSetTevColorOp(4, 0, 0, 0, 1, 0);
            _GXSetTevAlphaIn(4, 7, 4, 0, 7);
            _GXSetTevAlphaOp(4, 0, 0, 0, 1, 0);
            GXSetNumTevStages(5);

            quadA.x = kPppMiasmaZero;
            quadA.y = yPos;
            quadA.z = kPppMiasmaZero;
            quadB.x = 640.0f;
            quadB.y = yPos + 224.0f;
            quadB.z = kPppMiasmaZero;

            pppInitBlendMode();
            pppSetBlendMode(0);
            if (step->m_arg3 != 2) {
                gUtil.RenderQuadTex2(quadA, quadB, packedColor.color, 0, 0);
            }
        }

        gUtil.InitConstantRegister();
        gUtil.BeginQuadEnv();
        gUtil.SetVtxFmt_POS_CLR_TEX();
        if (step->m_arg3 != 1) {
            GXSetTevDirect(GX_TEVSTAGE0);
            GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            _GXSetTevOrder(0, 0, 0, 4);
            _GXSetTevSwapModeTable(
                2, tevSwapChannel, tevSwapChannel, tevSwapChannel, tevSwapChannel);
            _GXSetTevSwapMode(0, 0, 2);

            pppInitBlendMode();
            pppSetBlendMode(1);
            drawColor.rgba[0] = 0xFF;
            drawColor.rgba[1] = 0xFF;
            drawColor.rgba[2] = 0xFF;
            drawColor.rgba[3] = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, *(GXColor*)drawColor.rgba);
            GXSetChanMatColor(GX_COLOR0A0, packedWork.color);
            GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            GXSetNumChans(1);

            if (step->m_miasma.m_useSecondaryMask != 0) {
                GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
                GXLoadTexObj(&secondaryMaskTex, GX_TEXMAP1);

                GXSetTevDirect(GX_TEVSTAGE0);
                _GXSetTevOrder(0, 0, 0, 4);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevSwapMode(0, 0, 0);
                _GXSetTevColorIn(0, 0xF, 10, 8, 0xF);
                _GXSetTevColorOp(0, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(0, 7, 5, 4, 7);
                _GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
                texGenCount = 1;

                GXSetTevDirect(GX_TEVSTAGE1);
                _GXSetTevOrder(1, 0, 1, 4);
                _GXSetTevColorIn(1, 0xF, 8, 0xC, 0);
                _GXSetTevColorOp(1, 1, 0, 0, 1, 0);
                _GXSetTevAlphaIn(1, 7, 4, 6, 0);
                _GXSetTevAlphaOp(1, 1, 0, 2, 1, 0);

                GXSetTevDirect(GX_TEVSTAGE2);
                _GXSetTevOrder(2, 0, 1, 4);
                _GXSetTevColorIn(2, 0xF, 0xB, 0, 0xF);
                _GXSetTevColorOp(2, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(2, 7, 0, 5, 7);
                tevAlphaScale = 0;
                if (step->m_miasma.m_alphaOpScale == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_miasma.m_alphaOpScale == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp(2, 0, 0, tevAlphaScale, 1, 0);
                tevStageCount = 3;
            } else {
                GXSetTevDirect(GX_TEVSTAGE0);
                GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
                _GXSetTevOrder(0, 0, 0, 4);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevSwapMode(0, 0, 0);
                _GXSetTevColorIn(0, 0xF, 0xF, 0xF, 10);
                _GXSetTevColorOp(0, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(0, 7, 6, 4, 6);
                _GXSetTevAlphaOp(0, 1, 0, 0, 1, 0);

                GXSetTevDirect(GX_TEVSTAGE1);
                _GXSetTevOrder(1, 0, 0, 4);
                _GXSetTevSwapMode(1, 0, 0);
                _GXSetTevColorIn(1, 0xF, 0xF, 0xF, 0);
                _GXSetTevColorOp(1, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(1, 7, 0, 4, 7);
                _GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
                texGenCount = 1;

                GXSetTevDirect(GX_TEVSTAGE2);
                _GXSetTevSwapMode(2, 0, 0);
                GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                _GXSetTevOrder(2, 1, 1, 4);
                _GXSetTevColorIn(2, 0xF, 0xB, 0, 0xF);
                _GXSetTevColorOp(2, 0, 0, 0, 1, 0);
                _GXSetTevAlphaIn(2, 7, 0, 5, 7);

                tevAlphaScale = 0;
                if (step->m_miasma.m_alphaOpScale == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_miasma.m_alphaOpScale == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp(2, 0, 0, tevAlphaScale, 1, 0);
                tevStageCount = 3;
            }

            GXSetNumTevStages(tevStageCount);
            GXSetNumTexGens(texGenCount);
            quadA.x = kPppMiasmaZero;
            quadA.y = yPos;
            quadA.z = kPppMiasmaZero;
            quadB.x = 640.0f;
            quadB.y = yPos + 224.0f;
            quadB.z = kPppMiasmaZero;
            gUtil.RenderQuad(quadA, quadB, packedWork.color, 0, 0);
        }

        gUtil.InitConstantRegister();
        slice++;
    } while (slice < 2);

    gUtil.EndQuadEnv();
    pppInitBlendMode();
    _GXSetTevSwapMode(0, 0, 0);
    Graphic.SetViewport();
    gUtil.InitConstantRegister();
}
