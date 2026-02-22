#include "ffcc/pppCrystal2.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"
#include "ffcc/util.h"

#include <math.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern void* DAT_80238030;
extern CUtil DAT_8032ec70;
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
extern float ppvScreenMatrix[4][4];
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

extern struct {
    float _224_4_;
    float _228_4_;
    float _232_4_;
    float _236_4_;
    float _240_4_;
    float _244_4_;
    float _252_4_;
    Mtx m_cameraMatrix;
} CameraPcs;

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void pppSetBlendMode__FUc(unsigned char);
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
void pppConstructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
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
void pppDestructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
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
void pppFrameCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    if ((DAT_8032ed70 == 0) && (param_2->m_payload[0] != 0)) {
        int* refractionData = (int*)((char*)pppCrystal2 + param_3->m_serializedDataOffsets[2] + 0x80);
        if (refractionData[0] == 0) {
            u32 y;
            u32 x;
            refractionData[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                0x18, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xA8);

            int* textureInfo = (int*)refractionData[0];
            const int textureSize = (int)GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
            textureInfo[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xAD);
            textureInfo[1] = GX_TF_IA8;
            textureInfo[2] = 0x20;
            textureInfo[3] = 0x20;
            textureInfo[4] = 0x100;
            textureInfo[5] = textureSize;

            const float start = -1.0f;
            const float stepX = 2.0f / (float)(textureInfo[2] - 1);
            const float stepY = 2.0f / (float)(textureInfo[3] - 1);
            float yy = start;

            for (y = 0; y < (u32)textureInfo[3]; ++y) {
                float xx = start;
        const float y2 = yy * yy;

                for (x = 0; x < (u32)textureInfo[2]; ++x) {
                    float magnitude = xx * xx + y2;
                    if (magnitude < 0.0f) {
                        magnitude = 0.0f;
                    }

                    float normal = 0.0f;
                    if (magnitude > 1.0f) {
                        normal = 1.0f / sqrtf(magnitude);
                    } else if (magnitude > 0.0f) {
                        normal = sqrtf(magnitude);
                    }

                    if (normal > 0.8f) {
                        normal = 0.8f;
                    }

                    const u8 nx = (u8)__cvt_fp2unsigned((double)(xx * normal * 127.0f + 128.0f));
                    const u8 ny = (u8)__cvt_fp2unsigned((double)(yy * normal * 127.0f + 128.0f));
                    u8* pixel = (u8*)(textureInfo[0] +
                        (y >> 2) * (textureInfo[2] & 0x1ffffffcU) * 8 +
                        (x & 0x1ffffffc) * 8 +
                        ((x & 3) + (y & 3) * 4) * 2);

                    pixel[0] = nx;
                    pixel[1] = ny;
                    xx += stepX;
                }

                yy += stepY;
            }

            DCFlushRange((void*)textureInfo[0], textureInfo[5]);
            refractionData[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                0x20, pppEnvStPtr->m_stagePtr, s_pppCrystal2Cpp, 0xB5);
            
        GXInitTexObj((GXTexObj*)refractionData[1], (void*)textureInfo[0], (u16)textureInfo[2], (u16)textureInfo[3],
                     GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
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
void pppRenderCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    int workOffset = param_3->m_serializedDataOffsets[2];
    int colorOffset = param_3->m_serializedDataOffsets[1];

    if (param_2->m_dataValIndex == 0xFFFF) {
        return;
    }

    int textureIndex = 0;
    pppModelSt* model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_dataValIndex];
    int sourceTex = GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, textureIndex);
    if (param_2->m_payload[0] == 0) {
        if (param_2->m_initWOrk == 0xFFFF) {
            return;
        }
        sourceTex = GetTexture__8CMapMeshFP12CMaterialSetRi(
            ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_initWOrk], pppEnvStPtr->m_materialSetPtr, textureIndex);
    }

    _GXTexObj backTexObj;
    Mtx drawMtx;
    Mtx texMtx;
    Mtx normalMtx;
    Mtx cameraMtx;
    Mtx tmpMtx;
    float indMtx[2][3];
    float slope = FLOAT_80331fd0 * param_2->m_stepValue;
    float range = *(float*)(param_2->m_payload + 8);

    pppSetBlendMode__FUc(0);
    Graphic.GetBackBufferRect2(DAT_80238030, &backTexObj, 0, 0, 0x280, 0x1C0, 0, GX_LINEAR, GX_TF_RGBA8, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)pppCrystal2 + 0x88 + colorOffset, (u8*)pppCrystal2 + 0x40, (float)param_2->m_arg3, param_2->m_payload[5],
        param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1, param_2->m_payload[3]);

    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);

    indMtx[0][0] = slope;
    indMtx[0][1] = DAT_801dd60c;
    indMtx[0][2] = DAT_801dd610;
    indMtx[1][0] = DAT_801dd614;
    indMtx[1][1] = slope;
    indMtx[1][2] = DAT_801dd61c;

    texMtx[0][0] = DAT_801dd620;
    texMtx[0][1] = DAT_801dd624;
    texMtx[0][2] = DAT_801dd628;
    texMtx[0][3] = DAT_801dd62c;
    texMtx[1][0] = DAT_801dd630;
    texMtx[1][1] = DAT_801dd634;
    texMtx[1][2] = DAT_801dd638;
    texMtx[1][3] = DAT_801dd63c;
    texMtx[2][0] = DAT_801dd640;
    texMtx[2][1] = DAT_801dd644;
    texMtx[2][2] = DAT_801dd648;
    texMtx[2][3] = DAT_801dd64c;

    PSMTXIdentity(drawMtx);
    PSMTXConcat(pppMngStPtr->m_matrix.value, ((_pppPObject*)pppCrystal2)->m_localMatrix.value, cameraMtx);
    if (Game.game.m_currentSceneId == 7) {
        C_MTXLightPerspective(texMtx, FLOAT_80331fd4, FLOAT_80331fd8, range, -range, FLOAT_80331fdc, FLOAT_80331fdc);
        PSMTXConcat(ppvCameraMatrix0, cameraMtx, tmpMtx);
    } else {
        C_MTXLightPerspective(texMtx, CameraPcs._252_4_, FLOAT_80331fd8, range, -range, FLOAT_80331fdc, FLOAT_80331fdc);
        PSMTXConcat(CameraPcs.m_cameraMatrix, cameraMtx, tmpMtx);
    }
    PSMTXConcat(texMtx, tmpMtx, drawMtx);
    PSMTXInverse(tmpMtx, normalMtx);
    PSMTXTranspose(normalMtx, normalMtx);

    if (param_2->m_payload[0] == 0) {
        GXLoadTexObj((_GXTexObj*)(sourceTex + 0x28), GX_TEXMAP1);
    } else {
        GXLoadTexObj((_GXTexObj*)(*(u32*)((u8*)pppCrystal2 + 0x84 + workOffset)), GX_TEXMAP1);
    }

    GXSetNumIndStages(1);
    GXSetIndTexOrder((GXIndTexStageID)0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale((GXIndTexStageID)0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_1, indMtx, 1);
    GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, GX_ITF_8, GX_ITB_NONE, GX_ITM_1, GX_ITW_0, GX_ITW_0,
                     GX_FALSE, GX_FALSE, GX_ITBA_OFF);

    GXLoadTexMtxImm(texMtx, 0x40, GX_MTX3x4);
    GXLoadTexMtxImm(normalMtx, 0x21, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_NRM, 0x21, GX_TRUE, 0x40);
    GXLoadTexObj(&backTexObj, GX_TEXMAP0);
    GXLoadTexMtxImm(drawMtx, 0x1E, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_POS, 0x1E, GX_FALSE, GX_IDENTITY);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 1, 0, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8, 0xC,
                                                                                                           0xA);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(0, 7, 7, 7, 6);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)10, GX_DIRECT);
    GXSetVtxDesc((GXAttr)0xB, GX_DIRECT);
    GXSetVtxDesc((GXAttr)0xD, GX_DIRECT);
    pppDrawMesh__FP10pppModelStP3Veci(model, 0, 0);
    DAT_8032ec70.DisableIndMtx();
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
