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

static inline MiasmaFrameWork* GetMiasmaFrameWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<MiasmaFrameWork*>(miasma->m_workArea + ctrl->m_serializedDataOffsets[2]);
}

static inline VColor* GetMiasmaColorWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(miasma->m_workArea + ctrl->m_serializedDataOffsets[1]);
}

static inline MiasmaRadiusWork* GetMiasmaRadiusWork(pppMiasma* miasma, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<MiasmaRadiusWork*>(miasma->m_workArea + ctrl->m_serializedDataOffsets[3]);
}

static inline float CalcSphereRadius(Vec* vertices, u16 count)
{
    float radius = -1000.0f;

    for (u16 i = 0; i < count; i++) {
        if (radius < vertices[i].x) {
            radius = vertices[i].x;
        }
    }

    return radius;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 104b
 * EN Address: UNUSED
 * EN Size: 120b
 * JP Address: UNUSED
 * JP Size: TODO
 */
static inline void CreateScaleMatrix(_pppPObject* pObject, float scale)
{
    Mtx scaleMtx;
    Mtx localMtx;

    PSMTXScale(scaleMtx, scale, scale, scale);
    PSMTXConcat(scaleMtx, pObject->m_localMatrix.value, localMtx);
    PSMTXConcat(ppvWorldMatrix, localMtx, pObject->m_drawMatrix.value);
    GXLoadPosMtxImm(pObject->m_drawMatrix.value, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80109930
 * PAL Size: 368b
 * EN Address: 0x80108D40
 * EN Size: 368b
 * JP Address: 0x80105A5C
 * JP Size: 368b
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
 * EN Address: 0x80108EB0
 * EN Size: 4b
 * JP Address: 0x80105BCC
 * JP Size: 4b
 */
void pppDestructMiasma(pppMiasma*, _pppCtrlTable*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80109aa4
 * PAL Size: 100b
 * EN Address: 0x80108EB4
 * EN Size: 100b
 * JP Address: 0x80105BD0
 * JP Size: 100b
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
 * EN Address: 0x80108F18
 * EN Size: 100b
 * JP Address: 0x80105C34
 * JP Size: 100b
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
 * EN Address: 0x80108F7C
 * EN Size: 5452b
 * JP Address: 0x80105C98
 * JP Size: 5424b
 */
void pppRenderMiasma(pppMiasma* pppMiasma, pppMiasmaRenderStep* step, _pppCtrlTable* ctrl)
{
    pppCVECTOR drawColor;
    int texHeight;
    int texWidth;
    Vec quadA;
    MiasmaRadiusWork* radiusWork;
    float width;
    PackedMiasmaColor packedWork;
    Mtx44 screenMtx;
    Vec quadB;
    float yPos;
    u32 scissorWidth;
    CGraphic* graphicPtr;
    int maskOffset;
    int secondaryOffset;
    int textureIndex;
    pppModelSt* model;
    Vec cameraPos;
    PackedMiasmaColor packedColor;
    float height;
    float scaledRadius;
    float maxRadius;
    GXTexObj backSceneTex;
    VColor* colorWork;
    u32 maskTexSize;
    int tevAlphaScale;
    int tevStage;
    Vec managerPos;
    int isCameraInside;
    int slice;
    int tevSwapChannel;
    int tevStageCount;
    u32 sceneTexSize;
    GXTexObj miasmaMaskTex;
    float secondaryScale;
    GXTexObj secondaryMaskTex;
    GXColor stepColor;
    u32 scissorHeight;
    MiasmaFrameWork* work;
    int texGenCount;
    int yOffset;

#if defined(VERSION_GCCP01)
    Graphic.SetDrawDoneDebugData(0x31);
#endif

    work = GetMiasmaFrameWork(pppMiasma, ctrl);
    colorWork = GetMiasmaColorWork(pppMiasma, ctrl);
    radiusWork = GetMiasmaRadiusWork(pppMiasma, ctrl);
    tevStage = 0;
    textureIndex = 0;
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

    width = 640.0f;
    height = 224.0f;
    sceneTexSize = GXGetTexBufferSize(width, height, GX_TF_RGBA8, GX_FALSE, 0);
    maskTexSize = GXGetTexBufferSize(width, height, GX_CTF_R8, GX_FALSE, 0);

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
        CameraPcs.GetPosition(&cameraPos);
        maxRadius = 1200.0f;
    }

    scaledRadius = maxRadius * radiusWork->m_scale;
    if ((s32)Game.m_currentSceneId != 7) {
        Game.unkFloat_0xca10 = scaledRadius;
    }

    if ((10.0f + scaledRadius) > PSVECDistance(&cameraPos, &managerPos)) {
        isCameraInside = 1;
    }

    graphicPtr = &Graphic;
    texHeight = height;
    texWidth = width;
    scissorHeight = height;
    scissorWidth = width;
    secondaryOffset = sceneTexSize + maskTexSize;
    slice = 0;
    maskOffset = sceneTexSize;
    do {
        graphicPtr->GetBackBufferRect2(graphicPtr->m_scratchTextureBuffer, &backSceneTex, 0, yOffset = (int)(yPos = (float)slice * height), texWidth, texHeight, 0, GX_LINEAR,
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
        Util.RenderColorQuad(0.0f, yPos, width,
                              height, *(GXColor*)drawColor.rgba);

        pppSetDrawEnv(
            &drawColor, &pppMiasma->m_drawMatrix, 0.0f, 0, 0, 1, 0, 1, 1, 1);

        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
        GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
        GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY);

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
        CameraPcs.GetProjectionMatrix(screenMtx);
        GXSetProjection(screenMtx, GX_PERSPECTIVE);
        CreateScaleMatrix(pppMiasma, 1.0f);

        GXSetTevDirect((GXTevStageID)tevStage);
        pppInitBlendMode();
        pppSetBlendMode(1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        _GXSetTevColorIn(
            GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(
            GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);

        if (!isCameraInside) {
#if defined(VERSION_GCCP01)
            Graphic.SetDrawDoneDebugData(0x32);
#endif
            pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
#if defined(VERSION_GCCP01)
            Graphic.SetDrawDoneDebugData(0x33);
#endif
        }

        pppInitBlendMode();
        pppSetBlendMode(2);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        tevStage = 0;
        _GXSetTevColorIn(
            GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(
            GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);

#if defined(VERSION_GCCP01)
        Graphic.SetDrawDoneDebugData(0x34);
#endif
        pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
#if defined(VERSION_GCCP01)
        Graphic.SetDrawDoneDebugData(0x35);
#endif

        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &miasmaMaskTex, 0, yOffset, texWidth, texHeight, maskOffset,
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
            Util.RenderColorQuad(0.0f, yPos, width,
                                  height, *(GXColor*)drawColor.rgba);
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

            secondaryScale = 1.0f - step->m_stepValue;
            CreateScaleMatrix(pppMiasma, secondaryScale);

            _GXSetTevColorIn(
                GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(
                GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            if (!isCameraInside) {
#if defined(VERSION_GCCP01)
                Graphic.SetDrawDoneDebugData(0x36);
#endif
                pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
#if defined(VERSION_GCCP01)
                Graphic.SetDrawDoneDebugData(0x37);
#endif
            }
            tevStage = 0;

            GXSetTevDirect(GX_TEVSTAGE0);
            pppInitBlendMode();
            pppSetBlendMode(2);
            GXSetCullMode(GX_CULL_BACK);
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
            _GXSetTevColorIn(
                GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(
                GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

#if defined(VERSION_GCCP01)
            Graphic.SetDrawDoneDebugData(0x38);
#endif
            pppDrawMesh(model, pppMiasma->m_drawMatrixPtr, 0);
#if defined(VERSION_GCCP01)
            Graphic.SetDrawDoneDebugData(0x39);
#endif

            Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &secondaryMaskTex, 0, yOffset, texWidth, texHeight,
                                       secondaryOffset, GX_LINEAR, GX_CTF_R8, 0);
        }

        Graphic.SetViewport();
        Util.RenderTextureQuad(0.0f, yPos, width,
                                height, &backSceneTex, 0, 0,
                                0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        Util.BeginQuadEnv();
        Util.SetVtxFmt_POS_CLR_TEX0_TEX1();

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
                GX_TEV_SWAP1, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel);

            GXSetTevDirect(GX_TEVSTAGE0);
            GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
            _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_ONE);
            _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_KONST);
            _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);

            GXSetTevDirect(GX_TEVSTAGE1);
            GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_K0_A);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP1);
            _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_KONST, GX_CC_KONST, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_A0, GX_CA_KONST, GX_CA_KONST, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            GXSetTevDirect(GX_TEVSTAGE2);
            GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K0);
            GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_K0_A);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP1);
            _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_KONST, GX_CC_C0, GX_CC_C0, GX_CC_CPREV);
            _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_KONST, GX_CA_A0, GX_CA_A0, GX_CA_APREV);
            _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            GXSetTevDirect(GX_TEVSTAGE3);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP1);
            _GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            _GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

            GXSetTevDirect(GX_TEVSTAGE4);
            GXLoadTexObj(&backSceneTex, GX_TEXMAP1);
            _GXSetTevSwapMode(GX_TEVSTAGE4, GX_TEV_SWAP0, GX_TEV_SWAP1);
            _GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            _GXSetTevColorIn(GX_TEVSTAGE4, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            _GXSetTevColorOp(GX_TEVSTAGE4, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            _GXSetTevAlphaIn(GX_TEVSTAGE4, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            _GXSetTevAlphaOp(GX_TEVSTAGE4, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetNumTevStages(5);

            quadA.x = 0.0f;
            quadA.y = yPos;
            quadA.z = 0.0f;
            quadB.x = width;
            quadB.y = yPos + height;
            quadB.z = 0.0f;

            pppInitBlendMode();
            pppSetBlendMode(0);
            if (step->m_arg3 != 2) {
                Util.RenderQuadTex2(quadA, quadB, packedColor.color, 0, 0);
            }
        }

        Util.InitConstantRegister();
        Util.BeginQuadEnv();
        Util.SetVtxFmt_POS_CLR_TEX();
        if (step->m_arg3 != 1) {
            GXSetTevDirect(GX_TEVSTAGE0);
            GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
            GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevSwapModeTable(
                GX_TEV_SWAP2, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel, (_GXTevColorChan)tevSwapChannel);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP2);

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
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
                _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
                _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                texGenCount = 1;

                GXSetTevDirect(GX_TEVSTAGE1);
                _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
                _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_CPREV);
                _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_KONST, GX_CA_APREV);
                _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_4, GX_TRUE, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE2);
                _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
                _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_RASA, GX_CC_CPREV, GX_CC_ZERO);
                _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
                tevAlphaScale = 0;
                if (step->m_miasma.m_alphaOpScale == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_miasma.m_alphaOpScale == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, (_GXTevScale)tevAlphaScale, GX_TRUE, GX_TEVPREV);
                tevStageCount = 3;
            } else {
                GXSetTevDirect(GX_TEVSTAGE0);
                GXLoadTexObj(&miasmaMaskTex, GX_TEXMAP0);
                _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
                _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
                _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
                _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_KONST);
                _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

                GXSetTevDirect(GX_TEVSTAGE1);
                _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
                _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
                _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
                _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
                _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                texGenCount = 1;

                GXSetTevDirect(GX_TEVSTAGE2);
                _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
                GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
                _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
                _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_RASA, GX_CC_CPREV, GX_CC_ZERO);
                _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);

                tevAlphaScale = 0;
                if (step->m_miasma.m_alphaOpScale == 1) {
                    tevAlphaScale = 1;
                } else if (step->m_miasma.m_alphaOpScale == 2) {
                    tevAlphaScale = 2;
                }
                _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, (_GXTevScale)tevAlphaScale, GX_TRUE, GX_TEVPREV);
                tevStageCount = 3;
            }

            GXSetNumTevStages(tevStageCount);
            GXSetNumTexGens(texGenCount);
            quadA.x = 0.0f;
            quadA.y = yPos;
            quadA.z = 0.0f;
            quadB.x = width;
            quadB.y = yPos + height;
            quadB.z = 0.0f;
            Util.RenderQuad(quadA, quadB, packedWork.color, 0, 0);
        }

        Util.InitConstantRegister();
        slice++;
    } while (slice < 2);

    Util.EndQuadEnv();
    pppInitBlendMode();
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    Graphic.SetViewport();
    Util.InitConstantRegister();
}
