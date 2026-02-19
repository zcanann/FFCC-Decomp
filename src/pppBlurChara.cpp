#include "ffcc/pppBlurChara.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"

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
    int m_captureBuffer;
    void* m_ownerObj;
    int m_smallTexObj;
    float m_savedModelField;
};

struct pppMngStBlurCharaRaw {
    char _padding0[0xD8];
    void* m_charaObj;
};

extern int DAT_8032ed70;
extern void* DAT_80238030;
extern CUtil DAT_8032ec70;
extern char MaterialMan[];
extern unsigned char* lbl_8032ED50;

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

extern struct {
    float _212_4_;
    float _216_4_;
    float _220_4_;
    float _224_4_;
    float _228_4_;
    float _232_4_;
    Mtx m_cameraMatrix;
    Mtx44 m_screenMatrix;
} CameraPcs;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
int pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppHeapUseRate__FPQ27CMemory6CStage(CMemory::CStage* stage);
void Draw__Q29CCharaPcs7CHandleFi(void* handle, int drawType);
void pppInitBlendMode__Fv(void);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(pppCVECTOR*, pppFMATRIX*, float, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char,
                                                                 unsigned char, unsigned char, unsigned char);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
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
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void* math, Mtx44 mtx, Vec4d* src, Vec4d* dst);
}

static char s_pppBlurCharaCpp[] = "pppBlurChara.cpp";

static inline pppBlurCharaWork* GetBlurWork(pppBlurChara* blurChara, const UnkC* data) {
    return (pppBlurCharaWork*)((char*)blurChara + 0x80 + data->m_serializedDataOffsets[2]);
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
    *(unsigned int*)(MaterialMan + 0x48) |= 0x10000;
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
    void* handle = GetCharaHandlePtr__FP8CGObjectl(((void**)param_2)[1], 0);
    _GXTexObj backTexObj;
    _GXColor white;
    Vec posA;
    Vec posB;
    Vec uvA;
    Vec uvB;

    Graphic.GetBackBufferRect2(DAT_80238030, &backTexObj, 0, 0, (int)FLOAT_80331050, (int)FLOAT_80331054, 0,
                               GX_NEAR, GX_TF_RGBA8, 0);

    DAT_8032ec70.SetVtxFmt_POS_CLR();
    DAT_8032ec70.BeginQuadEnv();
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;

    posA.x = FLOAT_80331030;
    posA.y = FLOAT_80331030;
    posA.z = FLOAT_80331030;
    posB.x = FLOAT_80331050;
    posB.y = FLOAT_80331054;
    posB.z = FLOAT_80331030;
    DAT_8032ec70.RenderQuadNoTex(posA, posB, white);
    DAT_8032ec70.EndQuadEnv();

    GXSetViewport(FLOAT_80331030, FLOAT_80331030, FLOAT_80331050, FLOAT_80331054, FLOAT_80331030, FLOAT_8033103c);
    GXSetScissor(0, 0, (unsigned int)FLOAT_80331050, (unsigned int)FLOAT_80331054);

    *(void**)((char*)model + 0xF4) = (void*)BlurChara_SetBeforeMeshLockEnvCallback;
    *(void**)((char*)model + 0x108) = 0;
    Draw__Q29CCharaPcs7CHandleFi(handle, 0);
    *(void**)((char*)model + 0xF4) = 0;
    *(void**)((char*)model + 0x108) = (void*)BlurChara_AfterDrawModelCallback;

    Graphic.SetViewport();
    GXSetScissor(0, 0, 0x280, 0x1C0);
    Graphic.GetBackBufferRect2(((void**)param_2)[0], (_GXTexObj*)((void**)param_2)[2], 0, 0, (int)FLOAT_80331050,
                               (int)FLOAT_80331054, 0, GX_NEAR, GX_TF_I8, 0);

    if (*((unsigned char*)param_3 + 4) == 1) {
        float blur = *(float*)((char*)param_3 + 0x14);
        float blurX = FLOAT_80331044 * blur;

        DAT_8032ec70.RenderTextureQuad(-blurX, -blur, FLOAT_80331050 + blurX, FLOAT_80331054 + blur,
                                       (_GXTexObj*)((void**)param_2)[2], 0, 0, 0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);

        DAT_8032ec70.BeginQuadEnv();
        DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
        GXLoadTexObj((_GXTexObj*)((void**)param_2)[2], GX_TEXMAP0);

        posA.x = blurX;
        posA.y = blur;
        posA.z = FLOAT_80331030;
        posB.x = FLOAT_80331050 - blurX;
        posB.y = FLOAT_80331054 - blur;
        posB.z = FLOAT_80331030;

        uvA.x = FLOAT_80331030;
        uvA.y = FLOAT_80331030;
        uvB.x = FLOAT_80331030;
        uvB.y = FLOAT_80331030;

        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3, 1, 1, 7);
        DAT_8032ec70.RenderQuad(posA, posB, white, (Vec2d*)&uvA, (Vec2d*)&uvB);
        DAT_8032ec70.EndQuadEnv();

        Graphic.GetBackBufferRect2(((void**)param_2)[0], (_GXTexObj*)((void**)param_2)[2], 0, 0, (int)FLOAT_80331050,
                                   (int)FLOAT_80331054, 0, GX_NEAR, GX_TF_I8, 0);
    }

    DAT_8032ec70.RenderTextureQuad(FLOAT_80331030, FLOAT_80331030, FLOAT_80331050, FLOAT_80331054, &backTexObj, 0, 0,
                                   0, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
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
void pppConstructBlurChara(pppBlurChara* blurChara, UnkC* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    void* ownerObj = *(void**)(lbl_8032ED50 + 0xDC);
    void* handle;
    int model;

    work->m_ownerObj = ownerObj;
    handle = GetCharaHandlePtr__FP8CGObjectl(ownerObj, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    *(void**)(model + 0x108) = (void*)BlurChara_AfterDrawModelCallback;
    work->m_captureBuffer = 0;
    work->m_smallTexObj = 0;
    work->m_savedModelField = *(float*)(model + 0x9C);
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
void pppDestructBlurChara(pppBlurChara* blurChara, UnkC* data)
{
    pppBlurCharaWork* work = GetBlurWork(blurChara, data);
    void* handle = GetCharaHandlePtr__FP8CGObjectl(work->m_ownerObj, 0);
    int model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    *(int*)(model + 0x108) = 0;
    *(int*)(model + 0xE4) = 0;
    *(int*)(model + 0xE8) = 0;

    if ((CMemory::CStage*)work->m_captureBuffer != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)work->m_captureBuffer);
        work->m_captureBuffer = 0;
    }

    if ((CMemory::CStage*)work->m_smallTexObj != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CMemory::CStage*)work->m_smallTexObj);
        work->m_smallTexObj = 0;
    }

    *(float*)(model + 0x9C) = work->m_savedModelField;
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
void pppFrameBlurChara(pppBlurChara* blurChara, UnkB* param_2, UnkC* param_3)
{
    pppBlurCharaWork* work;
    void* handle;
    int model;

    if (DAT_8032ed70 != 0) {
        return;
    }

    work = GetBlurWork(blurChara, param_3);
    handle = GetCharaHandlePtr__FP8CGObjectl(((pppMngStBlurCharaRaw*)pppMngStPtr)->m_charaObj, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

    *(pppBlurCharaWork**)(model + 0xE4) = work;
    *(UnkB**)(model + 0xE8) = param_2;

    if ((unsigned int)work->m_captureBuffer == 0) {
        unsigned int texBufferSize = GXGetTexBufferSize(0x140, 0xE0, GX_TF_I8, GX_FALSE, GX_FALSE);

        work->m_captureBuffer = pppMemAlloc__FUlPQ27CMemory6CStagePci(texBufferSize, pppEnvStPtr->m_stagePtr,
                                                                      s_pppBlurCharaCpp, 0xD5);
        work->m_smallTexObj = pppMemAlloc__FUlPQ27CMemory6CStagePci(0x20, pppEnvStPtr->m_stagePtr,
                                                                    s_pppBlurCharaCpp, 0xD7);

        *(pppBlurCharaWork**)(model + 0xE4) = work;
        *(UnkB**)(model + 0xE8) = param_2;
        *(void**)(model + 0xF4) = (void*)BlurChara_SetBeforeMeshLockEnvCallback;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800ddaf8
 * PAL Size: 1460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderBlurChara(pppBlurChara* blurChara, UnkB* param_2, UnkC* param_3)
{
    int textureBase = 0;
    int textureIndex = 0;
    int colorOffset = param_3->m_serializedDataOffsets[1];
    int texOffset = param_3->m_serializedDataOffsets[2];
    pppBlurCharaWork* work = GetBlurWork(blurChara, param_3);
    _GXTexObj smallBackTex;
    _GXColor drawColor;
    Mtx identityMtx;
    Mtx cameraMtx;
    Mtx44 projection;
    Mtx44 screenMtx;
    Vec cameraPos;
    Vec cameraTarget;
    Vec cameraDir;
    Vec objPos;
    Vec2d uv0;
    Vec2d uv1;
    Vec4d inVec;
    Vec4d outVec;
    float viewport[6];
    float gxProjection[7];
    float projX;
    float projY;
    float projZ;

    if (*((unsigned char*)&param_2->m_dataValIndex + 1) == 1) {
        if (param_2->m_initWOrk == -1) {
            return;
        }
        textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(&pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk],
                                                               pppEnvStPtr->m_materialSetPtr, textureIndex);
    } else {
        unsigned int div = *((unsigned char*)&param_2->m_dataValIndex + 2);
        Graphic.CreateSmallBackTexture(DAT_80238030, &smallBackTex, 0x140 / div, 0xE0 / div, GX_NEAR, GX_TF_I8, 0);
    }

    pppInitBlendMode__Fv();
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((pppCVECTOR*)((char*)blurChara + 0x88 + colorOffset),
                                                               0, FLOAT_80331030, param_2->m_payload[5], 0, 0, 0, 1,
                                                               1, 0);

    drawColor = *(_GXColor*)((char*)blurChara + 0x88 + colorOffset);
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

    objPos.x = *(float*)(*(int*)((char*)blurChara + 0x84 + texOffset) + 0x15C);
    objPos.y = *(float*)(*(int*)((char*)blurChara + 0x84 + texOffset) + 0x160);
    objPos.z = *(float*)(*(int*)((char*)blurChara + 0x84 + texOffset) + 0x164);

    GXProject(cameraPos.x + objPos.x, FLOAT_80331030, cameraPos.z + objPos.z, cameraMtx, gxProjection, viewport,
              &projX, &projY, &projZ);

    DAT_8032ec70.BeginQuadEnv();
    GXSetNumTevStages(2);
    GXSetNumTexGens(2);
    DAT_8032ec70.SetVtxFmt_POS_CLR_TEX();
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, 0x7d);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, 0x7d);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        1, 0, 0, 0, 0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 7);

    GXSetChanMatColor(GX_COLOR0A0, drawColor);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    GXLoadTexObj(*(_GXTexObj**)((char*)blurChara + 0x88 + texOffset), GX_TEXMAP0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 10, 8,
                                                                                                          0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 5, 4,
                                                                                                          7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 1, 1, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);

    if (*((unsigned char*)&param_2->m_dataValIndex + 1) == 1) {
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

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    inVec.x = FLOAT_80331030;
    inVec.y = FLOAT_80331030;
    inVec.z = -(PSVECDistance(&cameraPos, &objPos) - param_2->m_stepValue);
    inVec.w = FLOAT_8033103c;
    MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(0, screenMtx, &inVec, &outVec);

    if (outVec.w != FLOAT_80331030) {
        outVec.z = outVec.z / outVec.w;
    }

    uv0.x = -FLOAT_80331044 * param_2->m_arg3;
    uv0.y = FLOAT_80331048 + FLOAT_80331044 * param_2->m_arg3;
    uv1.x = -param_2->m_arg3;
    uv1.y = FLOAT_8033104c + param_2->m_arg3;

    Vec quadA;
    Vec quadB;
    quadA.x = uv0.x;
    quadA.y = uv0.y;
    quadA.z = outVec.z;
    quadB.x = uv1.x;
    quadB.y = uv1.y;
    quadB.z = outVec.z;

    DAT_8032ec70.RenderQuad(quadA, quadB, drawColor, &uv0, &uv1);

    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    pppInitBlendMode__Fv();
}
