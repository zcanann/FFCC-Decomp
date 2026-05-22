#include "ffcc/pppYmDeformationMdl.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/pppTypes.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

struct pppCVECTOR {
    u8 rgba[4];
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
extern const float kYmDeformationMdlBackTextureWidth;
extern const float kYmDeformationMdlBackTextureHeight;
extern const float kYmDeformationMdlTexMtxOffset;
extern const float kYmDeformationMdlTexMtxDepth;
extern const float kYmDeformationMdlDegToRad;
extern const float kYmDeformationMdlZero = 0.0f;

static inline Mtx& CameraMatrix()
{
    return *reinterpret_cast<Mtx*>(reinterpret_cast<u8*>(&CameraPcs) + 0x4);
}

static inline Mtx44& CameraScreenMatrix()
{
    return *reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x94);
}

static inline float DeformationMdlZero()
{
    return *reinterpret_cast<const float*>(&kYmDeformationMdlZero);
}

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);
void pppSetDrawEnv(pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char,
                   unsigned char, unsigned char, unsigned char);
void pppDrawMesh(pppModelSt*, Vec*, int);

extern "C" {
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic*, int&, int&, int&, int&, int);
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
    textureBase = reinterpret_cast<int>(reinterpret_cast<CMapMesh*>(model)->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex));

    PSMTXIdentity(indWarpMtx);
    pppSetBlendMode(0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    int zEnable = (param_2->m_payloadByte2C == 0) ? 1 : 0;
    pppSetDrawEnv(
        &colorInfo->m_color, &modelObject->m_modelMatrix, param_2->m_payload4, param_2->m_payloadByte2B, param_2->m_payloadByte2A,
        param_2->m_payloadByte28, param_2->m_payloadByte29, static_cast<unsigned char>(zEnable), 1, 0);

    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    pppSetBlendMode(param_2->m_payloadByte28);
    if (param_2->m_payloadByte28 == 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_AND);
    }
    if (param_2->m_payloadByte28 == 3) {
        _GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_AND);
        _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    }

    _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
    _GXSetTevOp(GX_TEVSTAGE1, GX_REPLACE);
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

        texMtx[1][0] = screenMtx[1][0];
        texMtx[2][0] = screenMtx[2][0];
        texMtx[0][1] = screenMtx[0][1];
        texMtx[2][1] = screenMtx[2][1];
        texMtx[0][0] = screenMtx[0][0];
        texMtx[1][1] = screenMtx[1][1];
        texMtx[0][2] = screenMtx[0][2];
        texMtx[1][2] = screenMtx[1][2];
        texMtx[2][2] = screenMtx[2][2];
        texMtx[0][0] = texMtx[0][0] * (kYmDeformationMdlBackTextureWidth / (float)width);
        texMtx[1][1] = texMtx[1][1] * -(kYmDeformationMdlBackTextureHeight / (float)height);
        texMtx[0][2] = kYmDeformationMdlTexMtxOffset;
        texMtx[1][2] = kYmDeformationMdlTexMtxOffset;
        texMtx[2][2] = kYmDeformationMdlTexMtxDepth;
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

        PSMTXRotRad(rotMtx, 'z', kYmDeformationMdlDegToRad * (float)state->m_angle);
        indMtx[0][0] = rotMtx[0][0] * state->m_scale;
        indMtx[0][1] = rotMtx[0][1] * state->m_scale;
        indMtx[0][2] = DeformationMdlZero();
        indMtx[1][0] = rotMtx[1][0] * state->m_scale;
        indMtx[1][1] = rotMtx[1][1] * state->m_scale;
        indMtx[1][2] = DeformationMdlZero();
        GXSetIndTexMtx(GX_ITM_0, indMtx, 1);

        GXLoadTexObj((_GXTexObj*)backTexture, GX_TEXMAP0);
        GXLoadTexObj((_GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
        pppDrawMesh(model, modelObject->m_drawMatrixPtr, 0);

        GXSetTevDirect((GXTevStageID)1);
        GXSetNumIndStages(0);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

        PSMTXRotRad(resetRotMtx, 'z', DeformationMdlZero());
        resetIndMtx[0][0] = DeformationMdlZero();
        resetIndMtx[0][1] = DeformationMdlZero();
        resetIndMtx[0][2] = DeformationMdlZero();
        resetIndMtx[1][0] = DeformationMdlZero();
        resetIndMtx[1][1] = DeformationMdlZero();
        resetIndMtx[1][2] = DeformationMdlZero();
        GXSetIndTexMtx(GX_ITM_0, resetIndMtx, 1);

        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        pppInitBlendMode();
    }
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
    YmDeformationMdlState* state;

    if ((gPppCalcDisabled == 0) &&
        ((state = (YmDeformationMdlState*)((u8*)pppYmDeformationMdl + 0x80 + param_3->m_serializedDataOffsets[2])),
         (param_2->m_dataValIndex != 0xFFFF))) {
        CalcGraphValue(
            (_pppPObject*)pppYmDeformationMdl, param_2->m_graphId, state->m_scale, state->m_values[0],
            state->m_values[1], param_2->m_initWOrk, param_2->m_stepValue, param_2->m_arg3);
        CalcGraphValue(
            (_pppPObject*)pppYmDeformationMdl, param_2->m_graphId, state->m_values[2], state->m_values[3],
            state->m_values[4], param_2->m_payload0, param_2->m_payload1, param_2->m_payload2);

        if (gPppInConstructor == 0) {
            if (state->m_direction != 0) {
                state->m_angle = state->m_angle + (int)state->m_values[2];
                if (state->m_angle > param_2->m_payload3) {
                    state->m_direction = 0;
                }
            } else {
                state->m_angle = state->m_angle - (int)state->m_values[2];
                if ((int)state->m_angle < -(int)param_2->m_payload3) {
                    state->m_direction = 1;
                }
            }
        }
    }
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
 * PAL Address: 0x800d2090
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationMdl(pppYmDeformationMdl* pppYmDeformationMdl_, pppYmDeformationMdlUnkC* param_2)
{
    const float& value = kYmDeformationMdlZero;
    YmDeformationMdlState* state = (YmDeformationMdlState*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);

    state->m_values[1] = value;
    state->m_values[0] = value;
    state->m_scale = value;
    state->m_values[4] = value;
    state->m_values[3] = value;
    state->m_values[2] = value;
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
    const float& zero = kYmDeformationMdlZero;
    YmDeformationMdlState* state = (YmDeformationMdlState*)((u8*)pppYmDeformationMdl_ + 0x80 + param_2->m_serializedDataOffsets[2]);

    state->m_angle = 0;
    state->m_direction = 1;
    state->m_values[1] = zero;
    state->m_values[0] = zero;
    state->m_scale = zero;
    state->m_values[4] = zero;
    state->m_values[3] = zero;
    state->m_values[2] = zero;
}

extern const double kPppYmSharedDoubleBias = 4503601774854144.0;
