#include "ffcc/pppBlurChara.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/gxfunc.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct Vec2d {
    float x;
    float y;
};

struct Vec4d {
    float x;
    float y;
    float z;
    float w;
};

struct pppBlurCharaWork {
    void* m_captureBuffer;
    void* m_ownerObj;
    _GXTexObj* m_smallTexObj;
    float m_savedModelField;
};

struct BlurCharaModelRaw {
    u8 _pad0[0x9C];
    float m_savedField; // 0x9C
    u8 _padA0[0xE4 - 0xA0];
    pppBlurCharaWork* m_work;        // 0xE4
    pppBlurCharaUnkB* m_renderData;  // 0xE8
    u8 _padEC[0xF4 - 0xEC];
    void (*m_beforeMeshLockCallback)(CChara::CModel*, void*, void*, int); // 0xF4
    u8 _padF8[0x108 - 0xF8];
    void (*m_afterDrawModelCallback)(CChara::CModel*, void*, void*); // 0x108
};
STATIC_ASSERT(offsetof(BlurCharaModelRaw, m_work) == 0xE4);
STATIC_ASSERT(offsetof(BlurCharaModelRaw, m_beforeMeshLockCallback) == 0xF4);
STATIC_ASSERT(offsetof(BlurCharaModelRaw, m_afterDrawModelCallback) == 0x108);

struct pppMngStBlurCharaRaw {
    char _padding0[0xDC];
    void* m_charaObj;
};

extern const f32 FLOAT_80331030;
extern const f32 FLOAT_80331034;
extern const f32 FLOAT_80331038;
extern const f32 FLOAT_8033103c;
extern const f32 FLOAT_80331040;
extern const f32 FLOAT_80331044;
extern const f32 FLOAT_80331048;
extern const f32 FLOAT_8033104c;
extern const f32 FLOAT_80331050;
extern const f32 FLOAT_80331054;
extern const double DOUBLE_80330FE8 = 3.0;
extern const double DOUBLE_80331058 = 4503599627370496.0;

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

static inline float CameraLookAtX()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs));
}

static inline float CameraLookAtZ()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0x8);
}

static inline float CameraWorldX()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0xC);
}

static inline float CameraWorldZ()
{
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(&CameraPcs) + 0x14);
}

static inline Mtx& CameraMatrix()
{
    return *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(&CameraPcs) + 0x18);
}

static inline Mtx44& CameraScreenMatrix()
{
    return *reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48);
}

extern const char s_pppBlurChara_cpp[] = "pppBlurChara.cpp";

static inline pppBlurCharaWork* GetBlurWork(pppBlurChara* blurChara, const pppBlurCharaUnkC* data) {
    return (pppBlurCharaWork*)((char*)blurChara + 0x80 + data->m_serializedDataOffsets[2]);
}

static inline BlurCharaModelRaw* GetBlurCharaModelRaw(CChara::CModel* model)
{
    return reinterpret_cast<BlurCharaModelRaw*>(model);
}

struct BlurCharaColorData {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

struct BlurCharaTexData {
    u8 _pad0[4];
    int m_objPosBase;
    _GXTexObj* m_texObj;
};

/*
 * --INFO--
 * PAL Address: 0x800ddaf8
 * PAL Size: 1460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderBlurChara(pppBlurChara* blurChara, pppBlurCharaUnkB* param_2, pppBlurCharaUnkC* param_3)
{
    int texDataOffset = param_3->m_serializedDataOffsets[2];
    int colorDataOffset = param_3->m_serializedDataOffsets[1];
    BlurCharaTexData* texData = reinterpret_cast<BlurCharaTexData*>((u8*)blurChara + 0x80 + texDataOffset);
    BlurCharaColorData* colorData = reinterpret_cast<BlurCharaColorData*>((u8*)blurChara + 0x80 + colorDataOffset);
    int textureBase = 0;
    int objPosBase;
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
        textureBase = reinterpret_cast<int>(
            ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_initWOrk]->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex));
    } else {
        Graphic.CreateSmallBackTexture(Graphic.m_scratchTextureBuffer, &smallBackTex, 0x140 / param_2->m_smallTextureDiv,
                                       0xE0 / param_2->m_smallTextureDiv, GX_LINEAR, GX_TF_RGBA8, 0);
    }

    pppInitBlendMode();
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(&colorData->m_color, (pppFMATRIX*)0, FLOAT_80331030, param_2->m_alpha, 0, 0, 0, 1, 1, 0);
    objPosBase = texData->m_objPosBase;

    PSMTXIdentity(identityMtx);

    cameraPos.x = CameraPcs.m_positionX;
    cameraPos.y = CameraPcs.m_positionY;
    cameraPos.z = CameraPcs.m_positionZ;
    cameraTarget.x = CameraPcs.m_targetX;
    cameraTarget.y = CameraPcs.m_targetY;
    cameraTarget.z = CameraPcs.m_targetZ;
    cameraPos.y = FLOAT_80331030;
    cameraTarget.y = FLOAT_80331030;
    PSVECSubtract(&cameraTarget, &cameraPos, &cameraDir);
    cameraDir.y = FLOAT_80331030;

    GXGetProjectionv(gxProjection);
    GXGetViewportv(viewport);
    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
    PSMTXIdentity(identityMtx);

    objPos.x = *(float*)(objPosBase + 0x15C);
    objPos.y = *(float*)(objPosBase + 0x160);
    objPos.z = *(float*)(objPosBase + 0x164);

    GXProject(cameraPos.x + objPos.x, FLOAT_80331030, cameraPos.z + objPos.z, cameraMtx, gxProjection, viewport,
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
        GXLoadTexObj((_GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
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
    projection[2][2] = FLOAT_8033103c;
    projection[0][0] = FLOAT_80331034;
    projection[1][1] = FLOAT_80331038;
    projection[0][3] = FLOAT_80331040;
    projection[1][3] = FLOAT_8033103c;
    projection[2][3] = FLOAT_80331030;
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);

    float depth = (float)PSVECDistance(&cameraPos, &objPos);
    depth -= param_2->m_stepValue;

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    inVec.x = FLOAT_80331030;
    inVec.y = FLOAT_80331030;
    inVec.z = -depth;
    inVec.w = FLOAT_8033103c;
    Math.MTX44MultVec4(screenMtx, &inVec, &outVec);

    if (outVec.w != FLOAT_80331030) {
        outVec.z = outVec.z / outVec.w;
    }

    float arg = param_2->m_arg3;
    float quadZ = outVec.z;
    float scaledArg = FLOAT_80331044 * arg;
    quadA.y = -arg;
    quadA.z = quadZ;
    quadA.x = -scaledArg;
    quadB.x = FLOAT_80331048 + scaledArg;
    quadB.y = FLOAT_8033104c + arg;
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
void pppFrameBlurChara(pppBlurChara* blurChara, pppBlurCharaUnkB* param_2, pppBlurCharaUnkC* param_3)
{
    pppBlurCharaWork* work;
    CCharaPcs::CHandle* handle;
    BlurCharaModelRaw* rawModel;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = GetBlurWork(blurChara, param_3);
    handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(((pppMngStBlurCharaRaw*)pppMngStPtr)->m_charaObj), 0);
    rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr(handle));

    rawModel->m_work = work;
    rawModel->m_renderData = param_2;

    if ((unsigned int)work->m_captureBuffer == 0) {
        unsigned int texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

        work->m_captureBuffer = pppMemAlloc(texBufferSize, pppEnvStPtr->m_stagePtr,
                                            const_cast<char*>(s_pppBlurChara_cpp), 0xD5);
        work->m_smallTexObj = reinterpret_cast<_GXTexObj*>(
            pppMemAlloc(0x20, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBlurChara_cpp), 0xD7));

        rawModel->m_work = work;
        rawModel->m_renderData = param_2;
        rawModel->m_beforeMeshLockCallback = BlurChara_SetBeforeMeshLockEnvCallback;
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
void pppDestructBlurChara(pppBlurChara* blurChara, pppBlurCharaUnkC* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(work->m_ownerObj), 0);
    BlurCharaModelRaw* rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr(handle));

    rawModel->m_afterDrawModelCallback = 0;
    rawModel->m_work = 0;
    rawModel->m_renderData = 0;

    if ((CMemory::CStage*)work->m_captureBuffer != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_captureBuffer);
        work->m_captureBuffer = 0;
    }

    if ((CMemory::CStage*)work->m_smallTexObj != 0) {
        pppHeapUseRate((CMemory::CStage*)work->m_smallTexObj);
        work->m_smallTexObj = 0;
    }

    rawModel->m_savedField = work->m_savedModelField;
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
void pppConstructBlurChara(pppBlurChara* blurChara, pppBlurCharaUnkC* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    void* ownerObj = ((pppMngStBlurCharaRaw*)pppMngStPtr)->m_charaObj;
    CCharaPcs::CHandle* handle;
    BlurCharaModelRaw* rawModel;

    work->m_ownerObj = ownerObj;
    handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(ownerObj), 0);
    rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr(handle));

    rawModel->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;
    work->m_captureBuffer = 0;
    work->m_smallTexObj = 0;
    work->m_savedModelField = rawModel->m_savedField;
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
    BlurCharaModelRaw* rawModel = GetBlurCharaModelRaw(model);
    pppBlurCharaWork* work = reinterpret_cast<pppBlurCharaWork*>(param_2);
    pppBlurCharaUnkB* renderData = reinterpret_cast<pppBlurCharaUnkB*>(param_3);
    int width;
    int height;
    CCharaPcs::CHandle* handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(work->m_ownerObj), 0);
    _GXTexObj backTexObj;
    Vec posA;
    Vec posB;
    _GXColor white;

    GXGetTexBufferSize(0x140, 0xE0, GX_TF_RGBA8, GX_FALSE, GX_FALSE);
    width = (int)FLOAT_80331050;
    height = (int)FLOAT_80331054;

    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_RGBA8, 0);

    gUtil.SetVtxFmt_POS_CLR();
    white.r = 0;
    white.g = 0;
    white.b = 0;
    white.a = 0xFF;

    posA.x = FLOAT_80331030;
    posA.y = FLOAT_80331030;
    posA.z = FLOAT_80331030;
    posB.x = (float)width;
    posB.y = (float)height;
    posB.z = FLOAT_80331030;

    gUtil.BeginQuadEnv();
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    gUtil.RenderQuadNoTex(posA, posB, white);
    gUtil.EndQuadEnv();

    GXSetViewport(FLOAT_80331030, FLOAT_80331030, FLOAT_80331050, FLOAT_80331054, FLOAT_80331030, FLOAT_8033103c);
    GXSetScissor(0, 0, (unsigned int)FLOAT_80331050, (unsigned int)FLOAT_80331054);

    rawModel->m_beforeMeshLockCallback = BlurChara_SetBeforeMeshLockEnvCallback;
    rawModel->m_afterDrawModelCallback = 0;
    handle->Draw(0);
    rawModel->m_beforeMeshLockCallback = 0;
    rawModel->m_afterDrawModelCallback = BlurChara_AfterDrawModelCallback;

    Graphic.SetViewport();
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);

    if (renderData->m_afterDrawPass == 1) {
        float scaledOffsetY;
        {
            float offsetY = renderData->m_afterDrawOffsetY;
            scaledOffsetY = FLOAT_80331044 * offsetY;

            gUtil.RenderTextureQuad(-scaledOffsetY, -offsetY, FLOAT_80331050 + scaledOffsetY,
                                    FLOAT_80331054 + offsetY,
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
        posA.z = FLOAT_80331030;
        posB.x = FLOAT_80331050 - scaledOffsetY;
        posB.y = FLOAT_80331054 - offsetY;
        posB.z = FLOAT_80331030;

        _GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_OR);
        gUtil.RenderQuad(posA, posB, white, 0, 0);
        gUtil.EndQuadEnv();

        Graphic.GetBackBufferRect2(work->m_captureBuffer, work->m_smallTexObj, 0, 0, width, height, 0, GX_LINEAR, GX_TF_I8, 0);
    }

    gUtil.RenderTextureQuad(FLOAT_80331030, FLOAT_80331030, FLOAT_80331050, FLOAT_80331054, &backTexObj, 0, 0, 0,
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
    *(unsigned int*)(MaterialManRaw() + 0x48) |= 0x10000;
}
