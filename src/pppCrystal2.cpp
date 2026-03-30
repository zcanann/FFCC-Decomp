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

extern float DAT_801dd60c;
extern float DAT_801dd610;
extern float DAT_801dd614;
extern float DAT_801dd61c;
extern float DAT_801dd620;
extern float DAT_801dd624;
extern float DAT_801dd628;
extern float DAT_801dd62c;
extern float DAT_801dd630;
extern float DAT_801dd634;
extern float DAT_801dd638;
extern float DAT_801dd63c;
extern float DAT_801dd640;
extern float DAT_801dd644;
extern float DAT_801dd648;
extern float DAT_801dd64c;
extern float FLOAT_80331fd0;
extern float FLOAT_80331fd4;
extern float FLOAT_80331fd8;
extern float FLOAT_80331fdc;
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

static inline float CameraPerspectiveFov()
{
    return CameraPcs._252_4_;
}

static inline Mtx& CameraMatrix()
{
    return CameraPcs.m_cameraMatrix;
}

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
            u32 y;
            u32 x;

            work->m_refractionMap = (Crystal2RefractionMap*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                sizeof(Crystal2RefractionMap), pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xA8);

            Crystal2RefractionMap* textureInfo = work->m_refractionMap;
            u32 textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
            textureInfo->m_imageData = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xAD);
            textureInfo->m_format = GX_TF_IA8;
            textureInfo->m_width = 0x20;
            textureInfo->m_height = 0x20;
            textureInfo->m_imageCount = 0x100;
            textureInfo->m_bufferSize = textureSize;

            const float start = -1.0f;
            const float stepX = 2.0f / (float)(textureInfo->m_width - 1);
            const float stepY = 2.0f / (float)(textureInfo->m_height - 1);
            float yCoord = start;

            for (y = 0; y < (u32)textureInfo->m_height; y++) {
                float xCoord = start;
                float ySq = yCoord * yCoord;

                for (x = 0; x < (u32)textureInfo->m_width; x++) {
                    float magnitude = xCoord * xCoord + ySq;
                    if (magnitude > 1.0f) {
                        magnitude = sqrtf(magnitude);
                    } else if (magnitude < 0.0f) {
                        magnitude = 0.0f;
                    }

                    if (magnitude > 0.8f) {
                        magnitude = 0.8f;
                    }

                    u8 nx = (u8)__cvt_fp2unsigned((double)(xCoord * magnitude * 127.0f + 128.0f));
                    u8* pixel = (u8*)((u32)textureInfo->m_imageData +
                        (y >> 2) * (textureInfo->m_width & 0x1FFFFFFCU) * 8 +
                        (x & 0x1FFFFFFC) * 8 +
                        ((x & 3) + (y & 3) * 4) * 2);
                    u8 ny = (u8)__cvt_fp2unsigned((double)(yCoord * magnitude * 127.0f + 128.0f));

                    pixel[0] = nx;
                    pixel[1] = ny;
                    xCoord += stepX;
                }

                yCoord += stepY;
            }

            DCFlushRange(textureInfo->m_imageData, textureInfo->m_bufferSize);
            work->m_refractionTexObj = (GXTexObj*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                0x20, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xB5);
            GXInitTexObj(work->m_refractionTexObj, textureInfo->m_imageData, (u16)textureInfo->m_width,
                         (u16)textureInfo->m_height, GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
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
    Crystal2Work* work = (Crystal2Work*)((u8*)&pppCrystal2->m_work + serializedDataOffsets[2]);
    pppCVECTOR* color = (pppCVECTOR*)(pppCrystal2->m_color + serializedDataOffsets[1]);
    int sourceTex;
    pppModelSt* model;
    _GXTexObj backTexObj;
    int textureIndex = 0;
    float indMtx00;
    float indMtx01;
    float indMtx02;
    float indMtx10;
    float indMtx11;
    float indMtx12;
    float texMtx00;
    float texMtx01;
    float texMtx02;
    float texMtx03;
    float texMtx10;
    float texMtx11;
    float texMtx12;
    float texMtx13;
    float texMtx20;
    float texMtx21;
    float texMtx22;
    float texMtx23;
    Mtx lightMtx;
    Mtx drawMtx;
    Mtx tmpMtx;
    Mtx cameraMtx;
    Mtx normalMtx;

    if (param_2->m_dataValIndex != 0xFFFF) {
        model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_dataValIndex];
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
        Graphic.GetBackBufferRect2(gRenderScratchTextureBuffer, &backTexObj, 0, 0, 0x280, 0x1C0, 0, GX_LINEAR, GX_TF_RGBA8, 0);
        pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
            color, (u8*)pppCrystal2 + 0x40, param_2->m_arg3,
            param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1,
            param_2->m_payload[3]);
        GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);

        indMtx00 = FLOAT_80331fd0 * param_2->m_stepValue;
        indMtx01 = DAT_801dd60c;
        indMtx02 = DAT_801dd610;
        indMtx10 = DAT_801dd614;
        indMtx11 = indMtx00;
        indMtx12 = DAT_801dd61c;

        texMtx00 = DAT_801dd620;
        texMtx01 = DAT_801dd624;
        texMtx02 = DAT_801dd628;
        texMtx03 = DAT_801dd62c;
        texMtx10 = DAT_801dd630;
        texMtx11 = DAT_801dd634;
        texMtx12 = DAT_801dd638;
        texMtx13 = DAT_801dd63c;
        texMtx20 = DAT_801dd640;
        texMtx21 = DAT_801dd644;
        texMtx22 = DAT_801dd648;
        texMtx23 = DAT_801dd64c;

        PSMTXIdentity(drawMtx);
        PSMTXConcat(pppMngStPtr->m_matrix.value, ((_pppPObject*)pppCrystal2)->m_localMatrix.value, cameraMtx);
        if (Game.m_currentSceneId == 7) {
            C_MTXLightPerspective(lightMtx, FLOAT_80331fd4, FLOAT_80331fd8, param_2->m_perspectiveScale,
                                  -param_2->m_perspectiveScale,
                                  FLOAT_80331fdc, FLOAT_80331fdc);
            PSMTXConcat(ppvCameraMatrix0, cameraMtx, tmpMtx);
        } else {
            C_MTXLightPerspective(lightMtx, CameraPerspectiveFov(), FLOAT_80331fd8, param_2->m_perspectiveScale,
                                  -param_2->m_perspectiveScale,
                                  FLOAT_80331fdc, FLOAT_80331fdc);
            PSMTXConcat(CameraMatrix(), cameraMtx, tmpMtx);
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
        GXSetIndTexMtx(GX_ITM_1, (const f32(*)[3])&indMtx00, 1);
        GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, GX_ITF_8, GX_ITB_NONE, GX_ITM_1, GX_ITW_0, GX_ITW_0,
                         GX_FALSE, GX_FALSE, GX_ITBA_OFF);

        GXLoadTexMtxImm((const f32(*)[4])&texMtx00, 0x40, GX_MTX3x4);
        GXLoadTexMtxImm(normalMtx, 0x21, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x21, GX_TRUE, 0x40);
        GXLoadTexObj(&backTexObj, GX_TEXMAP0);
        GXLoadTexMtxImm(drawMtx, 0x1E, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, GX_IDENTITY);
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
        GXSetVtxDesc((GXAttr)9, GX_DIRECT);
        GXSetVtxDesc((GXAttr)10, GX_DIRECT);
        GXSetVtxDesc((GXAttr)0xB, GX_DIRECT);
        GXSetVtxDesc((GXAttr)0xD, GX_DIRECT);
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
