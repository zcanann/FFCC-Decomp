#include "ffcc/pppCrystal2.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/pppPart.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "PowerPC_EABI_Support/Runtime/runtime.h"
#include "ffcc/ppp_linkage.h"

#include <math.h>

extern const double DOUBLE_80331FC0 = 2.4;
extern const float kPppScreenQuakeZero[2] = {0.0f, 0.0f};

struct Crystal2IndTexMtx {
    f32 value[2][3];
};

struct Crystal2TexMtx {
    f32 value[3][4];
};

struct pppCrystal2ColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

union Crystal2FloatBits {
    float value;
    u32 bits;
};

extern const Crystal2IndTexMtx s_crystal2IndTexMtxBase = {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

extern const Crystal2TexMtx s_crystal2TexMtxBase = {
    {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, -0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}};

extern const char s_pppCrystal2Cpp[] = "pppCrystal2.cpp";

static inline int Crystal2FpClassify(float value)
{
    Crystal2FloatBits bits;

    bits.value = value;
    switch (bits.bits & 0x7F800000) {
    case 0x7F800000:
        if ((bits.bits & 0x007FFFFF) != 0) {
            return 1;
        }
        return 2;

    case 0:
        if ((bits.bits & 0x007FFFFF) != 0) {
            return 5;
        }
        return 3;
    }

    return 4;
}

static inline float Crystal2SqrtPositive(float value)
{
    double guess = __frsqrte((double)value);

    guess = 0.5 * guess * (3.0 - guess * guess * value);
    guess = 0.5 * guess * (3.0 - guess * guess * value);
    guess = 0.5 * guess * (3.0 - guess * guess * value);

    return (float)(value * guess);
}

/*
 * --INFO--
 * PAL Address: 0x8013e694
 * PAL Size: 1212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkB* param_2, _pppCtrlTable* param_3)
{
    int* serializedDataOffsets = param_3->m_serializedDataOffsets;
    s32 dataValIndex = param_2->m_dataValIndex;
    Crystal2Work* work =
        reinterpret_cast<Crystal2Work*>(pppCrystal2->m_object.m_workArea + serializedDataOffsets[2]);
    pppCrystal2ColorBlock* colorBlock =
        reinterpret_cast<pppCrystal2ColorBlock*>(pppCrystal2->m_object.m_workArea + serializedDataOffsets[1]);
    pppModelSt* model;
    CTexture* sourceTex;
    _GXTexObj backTexObj;
    int textureIndex;
    Crystal2IndTexMtx indTexMtx;
    Mtx normalMtx;
    Mtx cameraMtx;
    Mtx tmpMtx;
    Mtx drawMtx;
    Mtx lightMtx;
    Crystal2TexMtx texMtx;

    if (dataValIndex != 0xFFFF) {
        sourceTex = 0;
        model = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[dataValIndex];
        textureIndex = 0;
        ((CMapMesh*)model)->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (param_2->m_payload[0] == 0) {
            if (param_2->m_initWOrk == 0xFFFF) {
                return;
            }
            sourceTex =
                static_cast<CTexture*>(pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk]->GetTexture(
                    pppEnvStPtr->m_materialSetPtr, textureIndex));
        }

        pppSetBlendMode(0);
        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 0x280, 0x1C0, 0, GX_LINEAR,
                                   (_GXTexFmt)4, 0);
        pppSetDrawEnv(
            &colorBlock->m_color, &pppCrystal2->m_object.m_drawMatrix, param_2->m_arg3,
            param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1,
            param_2->m_payload[3]);
        GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);

        indTexMtx = s_crystal2IndTexMtxBase;
        indTexMtx.value[0][0] = -0.5f * param_2->m_stepValue;
        indTexMtx.value[1][1] = indTexMtx.value[0][0];
        texMtx = s_crystal2TexMtxBase;

        PSMTXIdentity(drawMtx);
        PSMTXConcat(pppMngStPtr->m_matrix.value, pppCrystal2->m_object.m_localMatrix.value, cameraMtx);
        if ((int)Game.m_currentSceneId == 7) {
            f32 perspectiveScale = param_2->m_perspectiveScale;
            C_MTXLightPerspective(lightMtx, 25.0f, 1.3333334f, perspectiveScale, -perspectiveScale, 0.5f, 0.5f);
            PSMTXConcat(ppvCameraMatrix, cameraMtx, tmpMtx);
        } else {
            f32 perspectiveScale = param_2->m_perspectiveScale;
            C_MTXLightPerspective(lightMtx, CameraPcs._252_4_, 1.3333334f, perspectiveScale, -perspectiveScale, 0.5f,
                                  0.5f);
            PSMTXConcat(CameraPcs.m_cameraMatrix, cameraMtx, tmpMtx);
        }
        PSMTXConcat(lightMtx, tmpMtx, drawMtx);
        PSMTXInverse(tmpMtx, normalMtx);
        PSMTXTranspose(normalMtx, normalMtx);

        if (param_2->m_payload[0] == 0) {
            GXLoadTexObj(&sourceTex->m_texObj, GX_TEXMAP1);
        } else {
            GXLoadTexObj(work->m_refractionTexObj, GX_TEXMAP1);
        }

        GXSetNumIndStages(1);
        GXSetIndTexOrder((GXIndTexStageID)0, GX_TEXCOORD0, GX_TEXMAP1);
        GXSetIndTexCoordScale((GXIndTexStageID)0, GX_ITS_1, GX_ITS_1);
        GXSetIndTexMtx((GXIndTexMtxID)1, indTexMtx.value, 1);
        GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, (GXIndTexFormat)0, (GXIndTexBiasSel)3,
                         (GXIndTexMtxID)1, (GXIndTexWrap)0, (GXIndTexWrap)0, GX_FALSE, GX_FALSE,
                         (GXIndTexAlphaSel)0);

        GXLoadTexMtxImm(texMtx.value, 0x40, GX_MTX3x4);
        GXLoadTexMtxImm(normalMtx, 0x21, GX_MTX3x4);
        GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)0, (GXTexGenSrc)1, 0x21, GX_TRUE, 0x40);
        GXLoadTexObj(&backTexObj, GX_TEXMAP0);
        GXLoadTexMtxImm(drawMtx, 0x1E, GX_MTX3x4);
        GXSetTexCoordGen2((GXTexCoordID)1, (GXTexGenType)0, (GXTexGenSrc)0, 0x1E, GX_FALSE, 0x7D);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR0A0);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ONE, GX_CC_RASC);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ONE);
        _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumTevStages(1);
        GXSetNumTexGens(2);
        GXClearVtxDesc();
        GXSetVtxDesc((GXAttr)9, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)10, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)0xB, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)0xD, (GXAttrType)3);
        pppDrawMesh(model, 0, 0);
        gUtil.DisableIndMtx();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013eb50
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkB* param_2, _pppCtrlTable* param_3)
{
    u32 x;
    u32 y;
    u32 yTile;
    Crystal2Work* work;
    Crystal2RefractionMap* textureInfo;
    u32 textureSize;
    float magnitude;
    float stepX;
    float stepY;
    float yCoord;
    float xCoord;
    float ySq;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = reinterpret_cast<Crystal2Work*>(pppCrystal2->m_object.m_workArea + param_3->m_serializedDataOffsets[2]);
    if ((param_2->m_payload[0] != 0) && (work->m_refractionMap == 0)) {
        work->m_refractionMap = (Crystal2RefractionMap*)pppMemAlloc(
            sizeof(Crystal2RefractionMap), pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystal2Cpp), 0xA8);

        textureInfo = work->m_refractionMap;
        textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
        textureInfo->m_imageData = (u8*)pppMemAlloc(
            textureSize, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystal2Cpp), 0xAD);
        textureInfo->m_format = GX_TF_IA8;
        textureInfo->m_width = 0x20;
        textureInfo->m_height = 0x20;
        textureInfo->m_imageCount = 0x100;
        textureInfo->m_bufferSize = textureSize;

        stepX = 2.0f / (float)(textureInfo->m_width - 1);
        stepY = 2.0f / (float)(textureInfo->m_height - 1);
        yCoord = -1.0f;

        for (y = 0; y < (u32)textureInfo->m_height; y++) {
            yTile = y >> 2;
            u32 yFine = (y & 3) * 4;
            ySq = yCoord * yCoord;
            xCoord = -1.0f;

            for (x = 0; x < (u32)textureInfo->m_width; x++) {
                magnitude = xCoord * xCoord + ySq;

                if (magnitude > 0.0f) {
                    magnitude = Crystal2SqrtPositive(magnitude);
                } else if ((double)magnitude < 0.0) {
                    magnitude = NAN;
                } else if (Crystal2FpClassify(magnitude) == 1) {
                    magnitude = NAN;
                }

                u32 xFine = x & 3;
                if (magnitude > 1.0f) {
                    magnitude = 1.0f;
                }

                u8 nx = (u8)__cvt_fp2unsigned((double)(xCoord * magnitude * 127.0f + 128.0f));
                u8* pixel = textureInfo->m_imageData +
                    yTile * ((textureInfo->m_width & 0x1FFFFFFCU) << 3) +
                    (x & 0x1FFFFFFC) * 8 +
                    (xFine + yFine) * 2;

                pixel[0] = nx;
                u8 ny = (u8)__cvt_fp2unsigned((double)(yCoord * magnitude * 127.0f + 128.0f));
                xCoord += stepX;
                pixel[1] = ny;
            }

            yCoord += stepY;
        }

        DCFlushRange(textureInfo->m_imageData, textureInfo->m_bufferSize);
        work->m_refractionTexObj = (GXTexObj*)pppMemAlloc(
            0x20, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystal2Cpp), 0xB5);
        GXInitTexObj(work->m_refractionTexObj, textureInfo->m_imageData, (u16)textureInfo->m_width,
                     (u16)textureInfo->m_height, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013eeec
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal2(pppCrystal2* pppCrystal2, _pppCtrlTable* param_2)
{
    Crystal2Work* work = reinterpret_cast<Crystal2Work*>(
        pppCrystal2->m_object.m_workArea + param_2->m_serializedDataOffsets[2]);
    CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(work->m_refractionMap);

    if (work->m_refractionTexObj != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_refractionTexObj));
        work->m_refractionTexObj = 0;
    }

    if ((stage != 0) && (*(CMemory::CStage**)stage != 0)) {
        pppHeapUseRate(*(CMemory::CStage**)stage);
        *(u32*)stage = 0;
    }

    if (stage != 0) {
        pppHeapUseRate(stage);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8013ef74
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCrystal2(pppCrystal2* pppCrystal2, _pppCtrlTable* param_2)
{
    Crystal2Work* work = reinterpret_cast<Crystal2Work*>(
        pppCrystal2->m_object.m_workArea + param_2->m_serializedDataOffsets[2]);

    work->m_refractionMap = 0;
    work->m_refractionTexObj = 0;
}
