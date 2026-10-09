#include "ffcc/pppBlurChara.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/gobject.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/gxfunc.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct pppBlurCharaWork {
    void* m_captureBuffer;
    CGObject* m_ownerObj;
    GXTexObj* m_smallTexObj;
    float m_savedLightAlpha;
};

STATIC_ASSERT(sizeof(pppBlurCharaWork) == 0x10);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_captureBuffer) == 0x00);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_ownerObj) == 0x04);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_smallTexObj) == 0x08);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_savedLightAlpha) == 0x0C);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x08);
STATIC_ASSERT(sizeof(BlurCharaDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(BlurCharaDataOffsets, m_colorDataOffset) == 0x4);
STATIC_ASSERT(offsetof(BlurCharaDataOffsets, m_texDataOffset) == 0x8);

static inline BlurCharaDataOffsets* GetBlurCharaDataOffsets(const _pppCtrlTable* ctrl)
{
    return reinterpret_cast<BlurCharaDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline pppBlurCharaWork* GetBlurWork(pppBlurChara* blurChara, const _pppCtrlTable* ctrl) {
    return (pppBlurCharaWork*)(blurChara->m_workArea + GetBlurCharaDataOffsets(ctrl)->m_texDataOffset);
}

static inline VColor* GetBlurColorData(pppBlurChara* blurChara, const _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(
        blurChara->m_workArea + GetBlurCharaDataOffsets(ctrl)->m_colorDataOffset);
}

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);

/*
 * --INFO--
 * PAL Address: 0x800ddaf8
 * PAL Size: 1460b
 * EN Address: 0x800DD2C4
 * EN Size: 1460b
 * JP Address: 0x800DADD4
 * JP Size: 1460b
 */
void pppRenderBlurChara(pppBlurChara* blurChara, pppBlurCharaStep* step, _pppCtrlTable* ctrl)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, ctrl);
    VColor* colorData = GetBlurColorData(blurChara, ctrl);
    CTexture* texture = 0;
    CGObject* ownerObj;
    _GXTexObj smallBackTex;
    _GXColor drawColor;
    int textureIndex;
    Mtx identityMtx;
    Mtx cameraMtx;
    Mtx44 projection;
    Mtx44 screenMtx;
    Vec quadA;
    Vec quadB;
    Vec cameraPos;
    Vec cameraDir;
    Vec objPos;
    Vec cameraTarget;
    Vec4d outVec;
    Vec4d inVec;
    float gxProjection[7];
    float viewport[6];
    float projX;
    float projY;
    float projZ;

    if (step->m_textureMode == 1) {
        textureIndex = 0;
        if (step->m_initWOrk == 0xFFFF) {
            return;
        }
        texture = ppvEnv->m_mapMeshPtr[step->m_initWOrk]->GetTexture(
            ppvEnv->m_materialSetPtr, textureIndex);
    } else {
        Graphic.CreateSmallBackTexture(Graphic.m_scratchTextureBuffer, &smallBackTex, 0x140 / step->m_smallTextureDiv,
                                       0xE0 / step->m_smallTextureDiv, GX_LINEAR, GX_TF_RGBA8, 0);
    }

    pppInitBlendMode();
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(&colorData->m_color, (pppFMATRIX*)0, 0.0f, step->m_alpha, 0, 0, 0, 1, 1, 0);
    ownerObj = work->m_ownerObj;

    PSMTXIdentity(identityMtx);

    cameraPos.x = CameraPcs.m_positionX;
    cameraPos.y = CameraPcs.m_positionY;
    cameraPos.z = CameraPcs.m_positionZ;
    cameraTarget.x = CameraPcs.m_targetX;
    cameraTarget.y = CameraPcs.m_targetY;
    cameraTarget.z = CameraPcs.m_targetZ;
    cameraTarget.y = cameraPos.y = 0.0f;
    PSVECSubtract(&cameraTarget, &cameraPos, &cameraDir);
    cameraDir.y = 0.0f;

    GXGetProjectionv(gxProjection);
    GXGetViewportv(viewport);
    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXIdentity(identityMtx);

    objPos = ownerObj->m_worldPosition;

    GXProject(cameraPos.x + objPos.x, 0.0f, cameraPos.z + objPos.z, cameraMtx, gxProjection, viewport,
              &projX, &projY, &projZ);

    Util.BeginQuadEnv();
    GXSetNumTevStages(2);
    GXSetNumTexGens(2);
    Util.SetVtxFmt_POS_CLR_TEX();
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_RED);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_OR);

    GXSetChanMatColor(GX_COLOR0A0, drawColor);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    drawColor.r = colorData->m_color.rgba[0];
    drawColor.g = colorData->m_color.rgba[1];
    drawColor.b = colorData->m_color.rgba[2];
    drawColor.a = colorData->m_color.rgba[3];

    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    GXLoadTexObj(work->m_smallTexObj, GX_TEXMAP0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    if (step->m_textureMode == 1) {
        GXLoadTexObj(&texture->m_texObj, GX_TEXMAP1);
    } else {
        GXLoadTexObj(&smallBackTex, GX_TEXMAP1);
    }

    _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_APREV, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_RASA, GX_CA_APREV, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetCurrentMtx(0);

    PSMTX44Identity(projection);
    projection[0][0] = 0.003125f;
    projection[1][1] = -0.004464f;
    projection[2][2] = 1.0f;
    projection[0][3] = -1.0f;
    projection[1][3] = projection[2][2];
    projection[2][3] = 0.0f;
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    float depth = (float)PSVECDistance(&cameraPos, &objPos);
    depth -= step->m_stepValue;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    inVec.x = 0.0f;
    inVec.y = 0.0f;
    inVec.z = -depth;
    inVec.w = 1.0f;
    Math.MTX44MultVec4(screenMtx, &inVec, &outVec);

    if (outVec.w) {
        outVec.z = outVec.z / outVec.w;
    }

    float expandY = step->m_arg3;
    float quadZ = outVec.z;
    float expandX = 1.3333334f * expandY;
    quadA.y = -expandY;
    quadA.z = quadZ;
    quadA.x = -expandX;
    quadB.x = 640.0f + expandX;
    quadB.y = 448.0f + expandY;
    quadB.z = quadZ;

    Util.RenderQuad(quadA, quadB, drawColor, 0, 0);

    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x800de0ac
 * PAL Size: 232b
 * EN Address: 0x800DD878
 * EN Size: 232b
 * JP Address: 0x800DB388
 * JP Size: 232b
 */
void pppFrameBlurChara(pppBlurChara* blurChara, pppBlurCharaStep* step, _pppCtrlTable* ctrl)
{
    pppBlurCharaWork* work;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetBlurWork(blurChara, ctrl);
    handle = GetCharaHandlePtr(ppvMng->m_lookTarget, 0);
    model = GetCharaModelPtr(handle);

    model->m_callbackContext = work;
    model->m_callbackParam = step;

    if (work->m_captureBuffer == 0) {
        unsigned int texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

        work->m_captureBuffer = pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr,
                                            "pppBlurChara.cpp", 0xD5);
        work->m_smallTexObj = static_cast<GXTexObj*>(
            pppMemAlloc(0x20, ppvEnv->m_stagePtr, "pppBlurChara.cpp", 0xD7));

        model->m_callbackContext = work;
        model->m_callbackParam = step;
        model->SetBeforeMeshLockEnvCallback(BlurChara_SetBeforeMeshLockEnvCallback);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800de194
 * PAL Size: 152b
 * EN Address: 0x800DD960
 * EN Size: 152b
 * JP Address: 0x800DB470
 * JP Size: 152b
 */
void pppDestructBlurChara(pppBlurChara* blurChara, _pppCtrlTable* ctrl)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, ctrl);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(work->m_ownerObj, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);

    model->m_afterDrawModelCallback = 0;
    model->m_callbackContext = 0;
    model->m_callbackParam = 0;

    if (work->m_captureBuffer != 0) {
        pppMemFree(work->m_captureBuffer);
        work->m_captureBuffer = 0;
    }

    if (work->m_smallTexObj != 0) {
        pppMemFree(work->m_smallTexObj);
        work->m_smallTexObj = 0;
    }

    model->m_lightAlpha = work->m_savedLightAlpha;
}

/*
 * --INFO--
 * PAL Address: 0x800de22c
 * PAL Size: 112b
 * EN Address: 0x800DD9F8
 * EN Size: 112b
 * JP Address: 0x800DB508
 * JP Size: 112b
 */
void pppConstructBlurChara(pppBlurChara* blurChara, _pppCtrlTable* ctrl)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, ctrl);
    CGObject* ownerObj = ppvMng->m_lookTarget;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    work->m_ownerObj = ownerObj;
    handle = GetCharaHandlePtr(ownerObj, 0);
    model = GetCharaModelPtr(handle);

    model->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;
    work->m_captureBuffer = 0;
    work->m_smallTexObj = 0;
    work->m_savedLightAlpha = model->m_lightAlpha;
}

/*
 * --INFO--
 * PAL Address: 0x800de29c
 * PAL Size: 1084b
 * EN Address: 0x800DDA68
 * EN Size: 1084b
 * JP Address: 0x800DB578
 * JP Size: 1084b
 */
void BlurChara_AfterDrawModelCallback(CChara::CModel* model, void* context, void* param)
{
    pppBlurCharaWork* work = reinterpret_cast<pppBlurCharaWork*>(context);
    pppBlurCharaStep* step = reinterpret_cast<pppBlurCharaStep*>(param);
    float screenWidth = 320.0f;
    float screenHeight = 224.0f;
    int width;
    int height;
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(work->m_ownerObj, 0);
    _GXTexObj backTexObj;
    Vec posA;
    Vec posB;
    _GXColor quadColor;

    GXGetTexBufferSize(0x140, 0xE0, GX_TF_RGBA8, GX_FALSE, GX_FALSE);
    width = (int)screenWidth;
    height = (int)screenHeight;

    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_RGBA8, 0);

    Util.SetVtxFmt_POS_CLR();
    quadColor.r = 0;
    quadColor.g = 0;
    quadColor.b = 0;
    quadColor.a = 0xFF;

    posA.x = 0.0f;
    posA.y = 0.0f;
    posA.z = 0.0f;
    posB.x = (float)width;
    posB.y = (float)height;
    posB.z = 0.0f;

    Util.BeginQuadEnv();
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    Util.RenderQuadNoTex(posA, posB, quadColor);
    Util.EndQuadEnv();

    GXSetViewport(0.0f, 0.0f, screenWidth, screenHeight, 0.0f, 1.0f);
    GXSetScissor(0, 0, (unsigned int)screenWidth, (unsigned int)screenHeight);

    model->SetBeforeMeshLockEnvCallback(BlurChara_SetBeforeMeshLockEnvCallback);
    model->m_afterDrawModelCallback = 0;
    handle->Draw(0);
    model->SetBeforeMeshLockEnvCallback(0);
    model->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;

    Graphic.SetViewport();
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);

    if (step->m_afterDrawPass == 1) {
        float scaledOffsetY;
        {
            float offsetY = step->m_afterDrawOffsetY;
            scaledOffsetY = 1.3333334f * offsetY;

            Util.RenderTextureQuad(-scaledOffsetY, -offsetY, screenWidth + scaledOffsetY,
                                    screenHeight + offsetY,
                                    work->m_smallTexObj, 0, 0, 0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        }

        Util.BeginQuadEnv();
        Util.SetVtxFmt_POS_CLR_TEX();
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
        GXLoadTexObj(work->m_smallTexObj, GX_TEXMAP0);

        quadColor.r = 0xFF;
        quadColor.g = 0xFF;
        quadColor.b = 0xFF;
        quadColor.a = 0xFF;

        float offsetY = step->m_afterDrawOffsetY;
        posA.x = scaledOffsetY;
        posA.y = offsetY;
        posA.z = 0.0f;
        posB.x = screenWidth - scaledOffsetY;
        posB.y = screenHeight - offsetY;
        posB.z = 0.0f;

        _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_OR);
        Util.RenderQuad(posA, posB, quadColor, 0, 0);
        Util.EndQuadEnv();

        Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);
    }

    Util.RenderTextureQuad(0.0f, 0.0f, screenWidth, screenHeight, &backTexObj, 0, 0, 0,
                            GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}

/*
 * --INFO--
 * PAL Address: 0x800de6d8
 * PAL Size: 64b
 * EN Address: 0x800DDEA4
 * EN Size: 64b
 * JP Address: 0x800DB9B4
 * JP Size: 64b
 */
void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    MaterialMan.SetTevBit(static_cast<CMaterialMan::TEV_BIT>(0x10000));
}
