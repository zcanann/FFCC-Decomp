#include "ffcc/pppCrystal2.h"
#include "ffcc/graphic.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

extern float FLOAT_80331fd0;
extern float FLOAT_80331fd4;
extern float FLOAT_80331fd8;
extern float FLOAT_80331fdc;
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int,
                                                                                           int);
}

static char s_pppCrystal2Cpp[] = "pppCrystal2.cpp";

struct Crystal2IndTexMtx {
    f32 value[2][3];
};

struct Crystal2TexMtx {
    f32 value[3][4];
};

struct pppCrystal2RenderObject {
    u8 _pad0[0x10];
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    Vec* m_drawMatrixPtr;
    u8 _pad74[0xC];
    Crystal2Work m_work;
};

struct pppCrystal2ColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

union Crystal2FloatBits {
    float value;
    unsigned long bits;
};

static const Crystal2IndTexMtx s_crystal2IndTexMtxBase = {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

static const Crystal2TexMtx s_crystal2TexMtxBase = {
    {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, -0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}};

static inline bool Crystal2IsNaN(float value)
{
    Crystal2FloatBits bits;

    bits.value = value;
    return (bits.bits & 0x7F800000) == 0x7F800000 && (bits.bits & 0x007FFFFF) != 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeRefractionMap(HSD_ImageBuffer*)
{
	// TODO
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
void pppConstructCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkC* param_2)
{
    s32 iVar1 = param_2->m_serializedDataOffsets[2];
    u32* data = (u32*)((char*)pppCrystal2 + iVar1 + 0x80);

    data[0] = 0;
    data[1] = 0;
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
void pppDestructCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkC* param_2)
{
    u32* puVar1;
    CMemory::CStage* stage;

    puVar1 = (u32*)((u8*)pppCrystal2 + param_2->m_serializedDataOffsets[2] + 0x80);
    stage = (CMemory::CStage*)puVar1[0];
    
    if ((CMemory::CStage*)puVar1[1] != 0) {
        pppHeapUseRate((CMemory::CStage*)puVar1[1]);
        puVar1[1] = 0;
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
 * PAL Address: 0x8013eb50
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkB* param_2, pppCrystal2UnkC* param_3)
{
    if (gPppCalcDisabled == 0) {
        Crystal2Work* work = (Crystal2Work*)((u8*)pppCrystal2 + param_3->m_serializedDataOffsets[2] + 0x80);

        if ((param_2->m_payload[0] != 0) && (work->m_refractionMap == 0)) {
            Crystal2RefractionMap* textureInfo;
            u32 textureSize;
            float stepX;
            float stepY;
            float yCoord;
            u32 y;
            u32 x;

            work->m_refractionMap = (Crystal2RefractionMap*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                sizeof(Crystal2RefractionMap), pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xA8);

            textureInfo = work->m_refractionMap;
            textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
            textureInfo->m_imageData = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xAD);
            textureInfo->m_format = GX_TF_IA8;
            textureInfo->m_width = 0x20;
            textureInfo->m_height = 0x20;
            textureInfo->m_imageCount = 0x100;
            textureInfo->m_bufferSize = textureSize;

            stepX = 2.0f / (float)(textureInfo->m_width - 1);
            stepY = 2.0f / (float)(textureInfo->m_height - 1);
            yCoord = -1.0f;

            for (y = 0; y < (u32)textureInfo->m_height; y++) {
                float ySq = yCoord * yCoord;
                float xCoord = -1.0f;

                for (x = 0; x < (u32)textureInfo->m_width; x++) {
                    float magnitude = xCoord * xCoord + ySq;

                    if (magnitude > 1.0f) {
                        magnitude = sqrtf(magnitude);
                    } else if (magnitude < 0.0f) {
                        magnitude = NAN;
                    } else if (Crystal2IsNaN(magnitude)) {
                        magnitude = NAN;
                    }

                    if (magnitude > 0.8f) {
                        magnitude = 0.8f;
                    }

                    u8 nx = (u8)__cvt_fp2unsigned((double)(xCoord * magnitude * 127.0f + 128.0f));
                    u8* pixel = (u8*)((u32)textureInfo->m_imageData +
                        (y >> 2) * (textureInfo->m_width & 0x1FFFFFFCU) * 8 +
                        (x & 0x1FFFFFFC) * 8 +
                        ((x & 3) + (y & 3) * 4) * 2);

                    pixel[0] = nx;
                    u8 ny = (u8)__cvt_fp2unsigned((double)(yCoord * magnitude * 127.0f + 128.0f));
                    xCoord += stepX;
                    pixel[1] = ny;
                }

                yCoord += stepY;
            }

            DCFlushRange(textureInfo->m_imageData, textureInfo->m_bufferSize);
            work->m_refractionTexObj = (GXTexObj*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                0x20, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xB5);
            GXInitTexObj(work->m_refractionTexObj, textureInfo->m_imageData, (u16)textureInfo->m_width,
                         (u16)textureInfo->m_height, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
        }
    }
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
void pppRenderCrystal2(pppCrystal2* pppCrystal2, pppCrystal2UnkB* param_2, pppCrystal2UnkC* param_3)
{
    s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
    s32 dataValIndex = param_2->m_dataValIndex;
    Crystal2Work* work = (Crystal2Work*)((u8*)pppCrystal2 + serializedDataOffsets[2] + 0x80);
    pppCrystal2ColorBlock* colorBlock = (pppCrystal2ColorBlock*)((u8*)pppCrystal2 + serializedDataOffsets[1] + 0x80);
    pppCrystal2RenderObject* object;
    pppModelSt* model;
    int sourceTex;
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
        model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[dataValIndex];
        textureIndex = 0;
        GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);
        if (param_2->m_payload[0] == 0) {
            if (param_2->m_initWOrk == 0xFFFF) {
                return;
            }
            sourceTex = GetTexture__8CMapMeshFP12CMaterialSetRi(
                ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_initWOrk], pppEnvStPtr->m_materialSetPtr,
                textureIndex);
        }

        pppSetBlendMode(0);
        Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 0x280, 0x1C0, 0, GX_LINEAR,
                                   (_GXTexFmt)4, 0);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            &colorBlock->m_color, (pppFMATRIX*)((u8*)pppCrystal2 + 0x40), param_2->m_arg3,
            param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1,
            param_2->m_payload[3]);
        GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);

        indTexMtx = s_crystal2IndTexMtxBase;
        indTexMtx.value[0][0] = FLOAT_80331fd0 * param_2->m_stepValue;
        indTexMtx.value[1][1] = indTexMtx.value[0][0];
        texMtx = s_crystal2TexMtxBase;

        object = (pppCrystal2RenderObject*)pppCrystal2;
        PSMTXIdentity(drawMtx);
        PSMTXConcat(pppMngStPtr->m_matrix.value, object->m_localMatrix.value, cameraMtx);
        if ((int)Game.m_currentSceneId == 7) {
            f32 perspectiveScale = param_2->m_perspectiveScale;
            C_MTXLightPerspective(lightMtx, FLOAT_80331fd4, FLOAT_80331fd8, perspectiveScale, -perspectiveScale,
                                  FLOAT_80331fdc, FLOAT_80331fdc);
            PSMTXConcat(ppvCameraMatrix02, cameraMtx, tmpMtx);
        } else {
            f32 perspectiveScale = param_2->m_perspectiveScale;
            C_MTXLightPerspective(lightMtx, CameraPcs._252_4_, FLOAT_80331fd8, perspectiveScale, -perspectiveScale,
                                  FLOAT_80331fdc, FLOAT_80331fdc);
            PSMTXConcat(CameraPcs.m_cameraMatrix, cameraMtx, tmpMtx);
        }
        PSMTXConcat(lightMtx, tmpMtx, drawMtx);
        PSMTXInverse(tmpMtx, normalMtx);
        PSMTXTranspose(normalMtx, normalMtx);

        if (param_2->m_payload[0] == 0) {
            GXLoadTexObj((_GXTexObj*)(sourceTex + 0x28), GX_TEXMAP1);
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
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 1, 0, 4);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
            0, 0xF, 8, 0xC, 0xA);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7,
                                                                                                               7, 6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(2);
        GXClearVtxDesc();
        GXSetVtxDesc((GXAttr)9, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)10, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)0xB, (GXAttrType)3);
        GXSetVtxDesc((GXAttr)0xD, (GXAttrType)3);
        pppDrawMesh__FP10pppModelStP3Veci(model, 0, 0);
        gUtil.DisableIndMtx();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}
