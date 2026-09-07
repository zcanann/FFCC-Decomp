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

static const char s_pppBlurChara_cpp[] = "pppBlurChara.cpp";

extern const float kPppBlurZero;
extern const float kPppBlurProjScaleX;
extern const float kPppBlurProjScaleY;
extern const float kPppBlurOne;
extern const float kPppBlurNegOne;
extern const float kPppScreenAspect;
extern const float kPppScreenWidth;
extern const float kPppScreenHeight;
extern const float kPppHalfScreenWidth;
extern const float kPppHalfScreenHeight;

struct pppBlurCharaWork {
    void* m_captureBuffer;
    CGObject* m_ownerObj;
    GXTexObj* m_smallTexObj;
    float m_savedModelField;
};

struct BlurCharaColorData {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

struct BlurCharaTexData {
    u8 _pad0[4];
    CGObject* m_objPosBase;
    GXTexObj* m_texObj;
};

STATIC_ASSERT(sizeof(pppBlurCharaWork) == 0x10);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_captureBuffer) == 0x00);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_ownerObj) == 0x04);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_smallTexObj) == 0x08);
STATIC_ASSERT(offsetof(pppBlurCharaWork, m_savedModelField) == 0x0C);
STATIC_ASSERT(offsetof(BlurCharaColorData, m_color) == 0x08);
STATIC_ASSERT(offsetof(BlurCharaTexData, m_objPosBase) == 0x04);
STATIC_ASSERT(offsetof(BlurCharaTexData, m_texObj) == 0x08);
STATIC_ASSERT(sizeof(BlurCharaDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(BlurCharaDataOffsets, m_colorDataOffset) == 0x4);
STATIC_ASSERT(offsetof(BlurCharaDataOffsets, m_texDataOffset) == 0x8);

static inline BlurCharaDataOffsets* GetBlurCharaDataOffsets(const _pppCtrlTable* data)
{
    return reinterpret_cast<BlurCharaDataOffsets*>(data->m_serializedDataOffsets);
}

static inline pppBlurCharaWork* GetBlurWork(pppBlurChara* blurChara, const _pppCtrlTable* data) {
    return (pppBlurCharaWork*)(blurChara->m_workArea + GetBlurCharaDataOffsets(data)->m_texDataOffset);
}

static inline BlurCharaTexData* GetBlurTexData(pppBlurChara* blurChara, const _pppCtrlTable* data)
{
    return reinterpret_cast<BlurCharaTexData*>(
        blurChara->m_workArea + GetBlurCharaDataOffsets(data)->m_texDataOffset);
}

static inline BlurCharaColorData* GetBlurColorData(pppBlurChara* blurChara, const _pppCtrlTable* data)
{
    return reinterpret_cast<BlurCharaColorData*>(
        blurChara->m_workArea + GetBlurCharaDataOffsets(data)->m_colorDataOffset);
}

void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);
void BlurChara_AfterDrawModelCallback(CChara::CModel*, void*, void*);

/*
 * --INFO--
 * PAL Address: 0x800ddaf8
 * PAL Size: 1460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderBlurChara(pppBlurChara* blurChara, pppBlurCharaStep* param_2, _pppCtrlTable* param_3)
{
    BlurCharaTexData* texData = GetBlurTexData(blurChara, param_3);
    BlurCharaColorData* colorData = GetBlurColorData(blurChara, param_3);
    CTexture* texture = 0;
    CGObject* objPosBase;
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

    if (param_2->m_textureMode == 1) {
        textureIndex = 0;
        if (param_2->m_initWOrk == 0xFFFF) {
            return;
        }
        texture = ((CMapMesh**)ppvEnv->m_mapMeshPtr)[param_2->m_initWOrk]->GetTexture(
            ppvEnv->m_materialSetPtr, textureIndex);
    } else {
        Graphic.CreateSmallBackTexture(Graphic.m_scratchTextureBuffer, &smallBackTex, 0x140 / param_2->m_smallTextureDiv,
                                       0xE0 / param_2->m_smallTextureDiv, GX_LINEAR, GX_TF_RGBA8, 0);
    }

    pppInitBlendMode();
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(&colorData->m_color, (pppFMATRIX*)0, kPppBlurZero, param_2->m_alpha, 0, 0, 0, 1, 1, 0);
    objPosBase = texData->m_objPosBase;

    PSMTXIdentity(identityMtx);

    cameraPos.x = CameraPcs.m_positionX;
    cameraPos.y = CameraPcs.m_positionY;
    cameraPos.z = CameraPcs.m_positionZ;
    cameraTarget.x = CameraPcs.m_targetX;
    cameraTarget.y = CameraPcs.m_targetY;
    cameraTarget.z = CameraPcs.m_targetZ;
    cameraTarget.y = cameraPos.y = kPppBlurZero;
    PSVECSubtract(&cameraTarget, &cameraPos, &cameraDir);
    cameraDir.y = kPppBlurZero;

    GXGetProjectionv(gxProjection);
    GXGetViewportv(viewport);
    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXIdentity(identityMtx);

    objPos = objPosBase->m_worldPosition;

    GXProject(cameraPos.x + objPos.x, kPppBlurZero, cameraPos.z + objPos.z, cameraMtx, gxProjection, viewport,
              &projX, &projY, &projZ);

    gUtil.BeginQuadEnv();
    GXSetNumTevStages(2);
    GXSetNumTexGens(2);
    gUtil.SetVtxFmt_POS_CLR_TEX();
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
    GXLoadTexObj(texData->m_texObj, GX_TEXMAP0);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);

    if (param_2->m_textureMode == 1) {
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
    projection[0][0] = kPppBlurProjScaleX;
    projection[1][1] = kPppBlurProjScaleY;
    projection[2][2] = kPppBlurOne;
    projection[0][3] = kPppBlurNegOne;
    projection[1][3] = projection[2][2];
    projection[2][3] = kPppBlurZero;
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    float depth = (float)PSVECDistance(&cameraPos, &objPos);
    depth -= param_2->m_stepValue;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    inVec.x = kPppBlurZero;
    inVec.y = kPppBlurZero;
    inVec.z = -depth;
    inVec.w = kPppBlurOne;
    Math.MTX44MultVec4(screenMtx, &inVec, &outVec);

    if (outVec.w != kPppBlurZero) {
        outVec.z = outVec.z / outVec.w;
    }

    float arg = param_2->m_arg3;
    float quadZ = outVec.z;
    float scaledArg = kPppScreenAspect * arg;
    quadA.y = -arg;
    quadA.z = quadZ;
    quadA.x = -scaledArg;
    quadB.x = kPppScreenWidth + scaledArg;
    quadB.y = kPppScreenHeight + arg;
    quadB.z = quadZ;

    gUtil.RenderQuad(quadA, quadB, drawColor, 0, 0);

    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x800de0ac
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameBlurChara(pppBlurChara* blurChara, pppBlurCharaStep* param_2, _pppCtrlTable* param_3)
{
    pppBlurCharaWork* work;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetBlurWork(blurChara, param_3);
    handle = GetCharaHandlePtr(ppvMng->m_lookTarget, 0);
    model = GetCharaModelPtr(handle);

    model->m_callbackContext = work;
    model->m_callbackParam = param_2;

    if ((unsigned int)work->m_captureBuffer == 0) {
        unsigned int texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

        work->m_captureBuffer = pppMemAlloc(texBufferSize, ppvEnv->m_stagePtr,
                                            const_cast<char*>(s_pppBlurChara_cpp), 0xD5);
        work->m_smallTexObj = reinterpret_cast<_GXTexObj*>(
            pppMemAlloc(0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppBlurChara_cpp), 0xD7));

        model->m_callbackContext = work;
        model->m_callbackParam = param_2;
        model->SetBeforeMeshLockEnvCallback(BlurChara_SetBeforeMeshLockEnvCallback);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800de194
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructBlurChara(pppBlurChara* blurChara, _pppCtrlTable* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(work->m_ownerObj, 0);
    CChara::CModel* model = GetCharaModelPtr(handle);

    model->m_afterDrawModelCallback = 0;
    model->m_callbackContext = 0;
    model->m_callbackParam = 0;

    if ((CMemory::CStage*)work->m_captureBuffer != 0) {
        pppMemFree(work->m_captureBuffer);
        work->m_captureBuffer = 0;
    }

    if ((CMemory::CStage*)work->m_smallTexObj != 0) {
        pppMemFree(work->m_smallTexObj);
        work->m_smallTexObj = 0;
    }

    model->m_lightAlpha = work->m_savedModelField;
}

/*
 * --INFO--
 * PAL Address: 0x800de22c
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructBlurChara(pppBlurChara* blurChara, _pppCtrlTable* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    CGObject* ownerObj = ppvMng->m_lookTarget;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    work->m_ownerObj = ownerObj;
    handle = GetCharaHandlePtr(ownerObj, 0);
    model = GetCharaModelPtr(handle);

    model->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;
    work->m_captureBuffer = 0;
    work->m_smallTexObj = 0;
    work->m_savedModelField = model->m_lightAlpha;
}

/*
 * --INFO--
 * PAL Address: 0x800de29c
 * PAL Size: 1084b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BlurChara_AfterDrawModelCallback(CChara::CModel* model, void* param_2, void* param_3)
{
    pppBlurCharaWork* work = reinterpret_cast<pppBlurCharaWork*>(param_2);
    pppBlurCharaStep* renderData = reinterpret_cast<pppBlurCharaStep*>(param_3);
    int width;
    int height;
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(work->m_ownerObj, 0);
    _GXTexObj backTexObj;
    Vec posA;
    Vec posB;
    _GXColor white;

    GXGetTexBufferSize(0x140, 0xE0, GX_TF_RGBA8, GX_FALSE, GX_FALSE);
    width = (int)kPppHalfScreenWidth;
    height = (int)kPppHalfScreenHeight;

    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_RGBA8, 0);

    gUtil.SetVtxFmt_POS_CLR();
    white.r = 0;
    white.g = 0;
    white.b = 0;
    white.a = 0xFF;

    posA.x = kPppBlurZero;
    posA.y = kPppBlurZero;
    posA.z = kPppBlurZero;
    posB.x = (float)width;
    posB.y = (float)height;
    posB.z = kPppBlurZero;

    gUtil.BeginQuadEnv();
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    gUtil.RenderQuadNoTex(posA, posB, white);
    gUtil.EndQuadEnv();

    GXSetViewport(kPppBlurZero, kPppBlurZero, kPppHalfScreenWidth, kPppHalfScreenHeight, kPppBlurZero, kPppBlurOne);
    GXSetScissor(0, 0, (unsigned int)kPppHalfScreenWidth, (unsigned int)kPppHalfScreenHeight);

    model->SetBeforeMeshLockEnvCallback(BlurChara_SetBeforeMeshLockEnvCallback);
    model->m_afterDrawModelCallback = 0;
    handle->Draw(0);
    model->SetBeforeMeshLockEnvCallback(0);
    model->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;

    Graphic.SetViewport();
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);

    if (renderData->m_afterDrawPass == 1) {
        float scaledOffsetY;
        {
            float offsetY = renderData->m_afterDrawOffsetY;
            scaledOffsetY = kPppScreenAspect * offsetY;

            gUtil.RenderTextureQuad(-scaledOffsetY, -offsetY, kPppHalfScreenWidth + scaledOffsetY,
                                    kPppHalfScreenHeight + offsetY,
                                    work->m_smallTexObj, 0, 0, 0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        }

        gUtil.BeginQuadEnv();
        gUtil.SetVtxFmt_POS_CLR_TEX();
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
        GXLoadTexObj(work->m_smallTexObj, GX_TEXMAP0);

        white.r = 0xFF;
        white.g = 0xFF;
        white.b = 0xFF;
        white.a = 0xFF;

        float offsetY = renderData->m_afterDrawOffsetY;
        posA.x = scaledOffsetY;
        posA.y = offsetY;
        posA.z = kPppBlurZero;
        posB.x = kPppHalfScreenWidth - scaledOffsetY;
        posB.y = kPppHalfScreenHeight - offsetY;
        posB.z = kPppBlurZero;

        _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_OR);
        gUtil.RenderQuad(posA, posB, white, 0, 0);
        gUtil.EndQuadEnv();

        Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);
    }

    gUtil.RenderTextureQuad(kPppBlurZero, kPppBlurZero, kPppHalfScreenWidth, kPppHalfScreenHeight, &backTexObj, 0, 0, 0,
                            GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}

/*
 * --INFO--
 * PAL Address: 0x800de6d8
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BlurChara_SetBeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int)
{
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    MaterialMan.OrCurrentEnvTevBit(0x10000);
}

extern const float kPppBlurZero = 0.0f;
extern const float kPppBlurProjScaleX = 0.003125f;
extern const float kPppBlurProjScaleY = -0.004464f;
extern const float kPppBlurOne = 1.0f;
extern const float kPppBlurNegOne = -1.0f;
extern const float kPppScreenAspect = 1.3333334f;
extern const float kPppScreenWidth = 640.0f;
extern const float kPppScreenHeight = 448.0f;
extern const float kPppHalfScreenWidth = 320.0f;
extern const float kPppHalfScreenHeight = 224.0f;
