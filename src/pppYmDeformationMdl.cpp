#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppYmEnv.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

static const float FLOAT_80330d98 = 2.0f;
static const float FLOAT_80330d9c = 2.0f;
static const float FLOAT_80330da0 = 0.0f;
static const float FLOAT_80330da4 = 1.0f;
static const float FLOAT_80330da8 = 0.017453292f;
static const float kPppYmDeformationMdlZero = 0.0f;
static const double DOUBLE_80330db0 = 4503601774854144.0;

struct pppCVECTOR {
    u8 rgba[4];
};

struct pppFMATRIX {
    Mtx value;
};

struct pppModelSt;
struct _pppPObject;

struct YmDeformationMdlColorInfo {
    u32 m_unk0;
    u32 m_unk4;
    pppCVECTOR m_color;
};

struct YmDeformationMdlState {
    s16 m_angle;
    u8 m_direction;
    u8 m_pad;
    float m_scale;
    float m_values[5];
};

struct pppYmDeformationMdlLayout {
    u8 m_pad0[0x40];
    pppFMATRIX m_modelMatrix;
    Vec* m_drawMatrixPtr;
    u8 m_pad74[0xC];
};

struct _pppEnvStYmDeformationMdl {
    void* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};
extern _pppEnvStYmDeformationMdl* pppEnvStPtr;

static inline Mtx& CameraMatrix()
{
    return *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(&CameraPcs) + 0x4);
}

static inline Mtx44& CameraScreenMatrix()
{
    return *reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x94);
}

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);

void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(int, int,
                                                                                                                      int, int,
                                                                                                                      int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic*, int&, int&, int&, int&, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
int __cntlzw(unsigned int);
}

/*
 * --INFO--
 * PAL Address: 0x800d20c0
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, struct pppYmDeformationMdlUnkC* param_2)
{
    u8 direction = 1;
    u16* puVar2 = (u16*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    float fVar1 = kPppYmDeformationMdlZero;

    *puVar2 = 0;
    *(u8*)(puVar2 + 1) = direction;
    *(float*)(puVar2 + 6) = fVar1;
    *(float*)(puVar2 + 4) = fVar1;
    *(float*)(puVar2 + 2) = fVar1;
    *(float*)(puVar2 + 0xc) = fVar1;
    *(float*)(puVar2 + 10) = fVar1;
    *(float*)(puVar2 + 8) = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x800d2090
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, pppYmDeformationMdlUnkC* param_2)
{
    extern float FLOAT_80330dac;
    float value = FLOAT_80330dac;
    float* state = (float*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);

    state[3] = FLOAT_80330dac;
    state[2] = value;
    state[1] = value;
    state[6] = value;
    state[5] = value;
    state[4] = value;
}

/*
 * --INFO--
 * PAL Address: 0x800d208c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationMdl(pppYmDeformationMdl*, pppYmDeformationMdlUnkC*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800d1f58
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3)
{
    s16* psVar1;

    if ((gPppCalcDisabled == 0) &&
        ((psVar1 = (s16*)((u8*)pppYmDeformationMdl + 0x80 + param_3->m_serializedDataOffsets[2])),
         (param_2->m_dataValIndex != 0xFFFF))) {
        CalcGraphValue(
            (_pppPObject*)pppYmDeformationMdl, param_2->m_graphId, *(float*)(psVar1 + 2), *(float*)(psVar1 + 4),
            *(float*)(psVar1 + 6), param_2->m_initWOrk, param_2->m_stepValue, param_2->m_arg3);
        CalcGraphValue(
            (_pppPObject*)pppYmDeformationMdl, param_2->m_graphId, *(float*)(psVar1 + 8), *(float*)(psVar1 + 10),
            *(float*)(psVar1 + 0xC), param_2->m_payload0, param_2->m_payload1, param_2->m_payload2);

        if (gPppInConstructor == 0) {
            if (*(u8*)(psVar1 + 1) != 0) {
                *psVar1 = *psVar1 + (int)*(float*)(psVar1 + 8);
                if (*psVar1 > param_2->m_payload3) {
                    *(u8*)(psVar1 + 1) = 0;
                }
            } else {
                *psVar1 = *psVar1 - (int)*(float*)(psVar1 + 8);
                if ((int)*psVar1 < -(int)param_2->m_payload3) {
                    *(u8*)(psVar1 + 1) = 1;
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d19f0
 * PAL Size: 1384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl, pppYmDeformationMdlUnkB* param_2, pppYmDeformationMdlUnkC* param_3)
{
    extern float FLOAT_80330dac;
    pppYmDeformationMdlLayout* modelObject = (pppYmDeformationMdlLayout*)pppYmDeformationMdl;
    YmDeformationMdlState* state = (YmDeformationMdlState*)((u8*)pppYmDeformationMdl + param_3->m_serializedDataOffsets[2] + 0x80);
    YmDeformationMdlColorInfo* colorInfo;
    pppModelSt* model;
    Mtx indWarpMtx;
    Mtx44 screenMtx;
    Mtx cameraMtx;
    Mtx texMtx;
    Mtx rotMtx;
    Mtx resetRotMtx;
    float indMtx[2][3];
    float resetIndMtx[2][3];
    int textureIndex = 0;
    int left;
    int top;
    int width;
    int height;
    int backTexture;
    int textureBase;

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    model = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
    colorInfo = (YmDeformationMdlColorInfo*)((u8*)pppYmDeformationMdl + param_3->m_serializedDataOffsets[1] + 0x80);
    textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);

    PSMTXIdentity(indWarpMtx);
    pppSetBlendMode(0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        &colorInfo->m_color, &modelObject->m_modelMatrix, param_2->m_payload4, param_2->m_payloadByte2B, param_2->m_payloadByte2A,
        param_2->m_payloadByte28, param_2->m_payloadByte29, (u8)((u32)__cntlzw((u8)param_2->m_payloadByte2C) >> 5), 1, 0);

    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(1, 0, 1, 2, 0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 9, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7, 7, 4);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);

    pppSetBlendMode(param_2->m_payloadByte28);
    if (param_2->m_payloadByte28 == 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 1, 5, 1);
    }
    if (param_2->m_payloadByte28 == 3) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 1, 5, 1);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
    }

    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(1, 3);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_INDEX16);
    GXSetVtxDesc((GXAttr)10, GX_INDEX16);
    GXSetVtxDesc((GXAttr)11, GX_INDEX16);
    GXSetVtxDesc((GXAttr)13, GX_INDEX16);

    left = 0;
    top = 0;
    width = 0x280;
    height = 0x1c0;
    backTexture = GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, left, top, width, height, 0);
    if (backTexture != 0) {
        PSMTXIdentity(texMtx);
        PSMTX44Copy(CameraScreenMatrix(), screenMtx);
        PSMTXCopy(CameraMatrix(), cameraMtx);

        texMtx[0][0] = screenMtx[0][0] * (FLOAT_80330d98 / (float)width);
        texMtx[1][1] = screenMtx[1][1] * -(FLOAT_80330d9c / (float)height);
        texMtx[1][0] = screenMtx[1][0];
        texMtx[2][0] = screenMtx[2][0];
        texMtx[0][1] = screenMtx[0][1];
        texMtx[2][1] = screenMtx[2][1];
        texMtx[0][2] = FLOAT_80330da0;
        texMtx[1][2] = FLOAT_80330da0;
        texMtx[2][2] = FLOAT_80330da4;
        PSMTXConcat(texMtx, modelObject->m_modelMatrix.value, texMtx);
        GXLoadTexMtxImm(texMtx, 0x1E, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, 0x1E, GX_FALSE, GX_PTIDENTITY);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
        GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

        if ((state->m_angle == 0) || (state->m_angle == 0x168)) {
            state->m_angle = 1;
        }

        PSMTXRotRad(rotMtx, 'z', FLOAT_80330da8 * (float)state->m_angle);
        indMtx[0][0] = rotMtx[0][0] * state->m_scale;
        indMtx[0][1] = rotMtx[0][1] * state->m_scale;
        indMtx[0][2] = kPppYmDeformationMdlZero;
        indMtx[1][0] = rotMtx[1][0] * state->m_scale;
        indMtx[1][1] = rotMtx[1][1] * state->m_scale;
        indMtx[1][2] = kPppYmDeformationMdlZero;
        GXSetIndTexMtx(GX_ITM_0, indMtx, 1);

        GXLoadTexObj((_GXTexObj*)backTexture, GX_TEXMAP0);
        GXLoadTexObj((_GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
        pppDrawMesh__FP10pppModelStP3Veci(model, modelObject->m_drawMatrixPtr, 0);

        GXSetTevDirect((GXTevStageID)1);
        GXSetNumIndStages(0);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

        PSMTXRotRad(resetRotMtx, 'z', FLOAT_80330dac);
        resetIndMtx[0][0] = FLOAT_80330dac;
        resetIndMtx[0][1] = FLOAT_80330dac;
        resetIndMtx[0][2] = FLOAT_80330dac;
        resetIndMtx[1][0] = FLOAT_80330dac;
        resetIndMtx[1][1] = FLOAT_80330dac;
        resetIndMtx[1][2] = FLOAT_80330dac;
        GXSetIndTexMtx(GX_ITM_0, resetIndMtx, 1);

        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
        pppInitBlendMode();
    }
}
