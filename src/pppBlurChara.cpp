#include "ffcc/pppBlurChara.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
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

extern float FLOAT_80331030;
extern float FLOAT_80331034;
extern float FLOAT_80331038;
extern float FLOAT_8033103c;
extern float FLOAT_80331040;
extern float FLOAT_80331044;
extern float FLOAT_80331048;
extern float FLOAT_8033104c;
extern float FLOAT_80331050;
extern float FLOAT_80331054;

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

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
int pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);
void Draw__Q29CCharaPcs7CHandleFi(void* handle, int drawType);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(pppCVECTOR*, pppFMATRIX*, float, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int stage, int mode);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int tevSwapSel, int red, int green, int blue, int alpha);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap,
                                                                                 int colorChannel);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int stage, int a, int b, int c, int d);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int stage, int op, int bias,
                                                                                           int scale, int clamp,
                                                                                           int reg);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int type, int src, int dst,
                                                                                    int op);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(CMath* math, Mtx44 mtx, Vec4d* src, Vec4d* dst);
}

static const char s_pppBlurChara_cpp_801DB620[] = "pppBlurChara.cpp";

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
    Vec cameraTarget;
    Vec cameraPos;
    Vec objPos;
    Vec cameraDir;
    Vec4d inVec;
    Vec4d outVec;
    float gxProjection[7];
    float viewport[6];
    float projX;
    float projY;
    float projZ;
    Vec quadA;
    Vec quadB;

    if (param_2->m_textureMode == 1) {
        textureIndex = 0;
        if (param_2->m_initWOrk == 0xFFFF) {
            return;
        }
        textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
            ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_initWOrk], pppEnvStPtr->m_materialSetPtr, textureIndex);
    } else {
        Graphic.CreateSmallBackTexture(Graphic.m_scratchTextureBuffer, &smallBackTex, 0x140 / param_2->m_smallTextureDiv,
                                       0xE0 / param_2->m_smallTextureDiv, GX_LINEAR, GX_TF_RGBA8, 0);
    }

    pppInitBlendMode();
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(&colorData->m_color, (pppFMATRIX*)0, FLOAT_80331030,
                                                               param_2->m_alpha, 0, 0, 0, 1, 1, 0);
    objPosBase = texData->m_objPosBase;

    PSMTXIdentity(identityMtx);

    cameraPos.x = CameraPcs._224_4_;
    cameraPos.y = FLOAT_80331030;
    cameraPos.z = CameraPcs._232_4_;
    cameraTarget.x = CameraPcs._212_4_;
    cameraTarget.y = FLOAT_80331030;
    cameraTarget.z = CameraPcs._220_4_;
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
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        1, 0, 0, 0, 0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 7);

    GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<_GXColor*>(&colorData->m_color));
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    drawColor.r = colorData->m_color.rgba[0];
    drawColor.g = colorData->m_color.rgba[1];
    drawColor.b = colorData->m_color.rgba[2];
    drawColor.a = colorData->m_color.rgba[3];

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    GXLoadTexObj(texData->m_texObj, GX_TEXMAP0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 10, 8,
                                                                                                          0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 5, 4,
                                                                                                          7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);

    if (param_2->m_textureMode == 1) {
        GXLoadTexObj((_GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
    } else {
        GXLoadTexObj(&smallBackTex, GX_TEXMAP1);
    }

    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8, 1,
                                                                                                          0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 5, 0,
                                                                                                          7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);

    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, 0);
    GXSetCurrentMtx(0);

    PSMTX44Identity(projection);
    projection[0][0] = FLOAT_80331034;
    projection[1][1] = FLOAT_80331038;
    projection[2][2] = FLOAT_8033103c;
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
    MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, screenMtx, &inVec, &outVec);

    if (outVec.w != FLOAT_80331030) {
        outVec.z = outVec.z / outVec.w;
    }

    quadB.x = -param_2->m_arg3;
    quadA.x = -(FLOAT_80331044 * param_2->m_arg3);
    quadA.y = FLOAT_80331048 + (FLOAT_80331044 * param_2->m_arg3);
    quadA.z = outVec.z;
    quadB.y = FLOAT_8033104c + param_2->m_arg3;
    quadB.z = outVec.z;

    gUtil.RenderQuad(quadA, quadB, drawColor, 0, 0);

    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
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
    void* handle;
    BlurCharaModelRaw* rawModel;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = GetBlurWork(blurChara, param_3);
    handle = GetCharaHandlePtr__FP8CGObjectl(((pppMngStBlurCharaRaw*)pppMngStPtr)->m_charaObj, 0);
    rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle));

    rawModel->m_work = work;
    rawModel->m_renderData = param_2;

    if ((unsigned int)work->m_captureBuffer == 0) {
        unsigned int texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

        work->m_captureBuffer = reinterpret_cast<void*>(
            pppMemAlloc__FUlPQ27CMemory6CStagePci(texBufferSize, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBlurChara_cpp_801DB620), 0xD5));
        work->m_smallTexObj = reinterpret_cast<_GXTexObj*>(
            pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppBlurChara_cpp_801DB620), 0xD7));

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
    void* handle = GetCharaHandlePtr__FP8CGObjectl(work->m_ownerObj, 0);
    BlurCharaModelRaw* rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle));

    rawModel->m_afterDrawModelCallback = 0;
    rawModel->m_work = 0;
    rawModel->m_renderData = 0;

    if ((CMemory::CStage*)work->m_captureBuffer != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)work->m_captureBuffer);
        work->m_captureBuffer = 0;
    }

    if ((CMemory::CStage*)work->m_smallTexObj != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)work->m_smallTexObj);
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
    void* handle;
    BlurCharaModelRaw* rawModel;

    work->m_ownerObj = ownerObj;
    handle = GetCharaHandlePtr__FP8CGObjectl(ownerObj, 0);
    rawModel = reinterpret_cast<BlurCharaModelRaw*>(GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle));

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
    void* handle = GetCharaHandlePtr__FP8CGObjectl(work->m_ownerObj, 0);
    _GXTexObj backTexObj;
    Vec posA;
    Vec posB;
    _GXColor white;

    GXGetTexBufferSize(0x140, 0xE0, GX_TF_RGBA8, GX_FALSE, GX_FALSE);
    width = (int)FLOAT_80331050;
    height = (int)FLOAT_80331054;

    Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &backTexObj, 0, 0, width, height, 0, GX_NEAR, GX_TF_RGBA8, 0);

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
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(GX_TEVSTAGE0, GX_PASSCLR);
    gUtil.RenderQuadNoTex(posA, posB, white);
    gUtil.EndQuadEnv();

    GXSetViewport(FLOAT_80331030, FLOAT_80331030, FLOAT_80331050, FLOAT_80331054, FLOAT_80331030, FLOAT_8033103c);
    GXSetScissor(0, 0, (unsigned int)FLOAT_80331050, (unsigned int)FLOAT_80331054);

    rawModel->m_beforeMeshLockCallback = BlurChara_SetBeforeMeshLockEnvCallback;
    rawModel->m_afterDrawModelCallback = 0;
    Draw__Q29CCharaPcs7CHandleFi(handle, 0);
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
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(GX_TEVSTAGE0, GX_REPLACE);
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

        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3, 1, 1, 7);
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
