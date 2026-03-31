#include "ffcc/pppCrystal.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

static const float DAT_801db5b8 = 0.5f;
static const float DAT_801db5bc = 0.0f;
static const float DAT_801db5c0 = 0.0f;
static const float DAT_801db5c4 = 0.5f;
static const float DAT_801db5c8 = 0.0f;
static const float DAT_801db5cc = -0.5f;
static const float DAT_801db5d0 = 0.0f;
static const float DAT_801db5d4 = 0.5f;
static const float DAT_801db5d8 = 0.0f;
static const float DAT_801db5dc = 0.0f;
static const float DAT_801db5e0 = 0.0f;
static const float DAT_801db5e4 = 1.0f;
static const float DAT_801db5ec = 0.0f;
static const float DAT_801db5f0 = 0.0f;
static const float DAT_801db5f4 = 0.0f;
static const float DAT_801db5fc = 0.0f;
static const float FLOAT_80330fa8 = 32.0f;
static const float FLOAT_80330fac = -0.5f;
static const float FLOAT_80330fb0 = 640.0f;
static const float FLOAT_80330fb4 = 448.0f;
static const float FLOAT_80330fb8 = 33.3f;
static const float FLOAT_80330fbc = 1.3333334f;
static const float FLOAT_80330fc0 = 0.5f;
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt*, Vec*, int);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int, int, int);
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic*, int&, int&, int&, int&, int);
}

static char s_pppCrystalCpp[] = "pppCrystal.cpp";

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
 * Address:	800dd404
 * Size:	32b
 */
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkC* param_2)
{
	s32* serializedDataOffsets = *(s32**)((u8*)param_2 + 0xC);
	u32* data = (u32*)((char*)pppCrystal + serializedDataOffsets[2] + 0x80);

	data[0] = 0;
	data[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800dd37c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkC* param_2)
{
	s32* serializedDataOffsets = *(s32**)((u8*)param_2 + 0xC);
	u32* puVar1 = (u32*)((char*)pppCrystal + 0x80 + serializedDataOffsets[2]);
	CMemory::CStage* stage = (CMemory::CStage*)puVar1[0];

	if ((stage != 0) && (*(CMemory::CStage**)stage != 0)) {
		pppHeapUseRate(*(CMemory::CStage**)stage);
		*(u32*)stage = 0;
	}
	if (stage != 0) {
		pppHeapUseRate(stage);
	}
	if ((CMemory::CStage*)puVar1[1] != 0) {
		pppHeapUseRate((CMemory::CStage*)puVar1[1]);
		puVar1[1] = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800dcf44
 * PAL Size: 1080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkB* param_2, struct pppCrystalUnkC* param_3)
{
	if (gPppCalcDisabled == 0) {
		CrystalWork* work = (CrystalWork*)((u8*)pppCrystal + param_3->m_serializedDataOffsets[2] + 0x80);

		if (param_2->m_dataValIndex != 0xFFFF) {
			CMapMesh** mapMeshTable = (CMapMesh**)pppEnvStPtr->m_mapMeshPtr;
			int textureIndex = 0;

			GetTexture__8CMapMeshFP12CMaterialSetRi(
				mapMeshTable[param_2->m_dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);

			if (param_2->m_payload[0] == 0) {
				if (param_2->m_initWOrk == 0xFFFF) {
					return;
				}

				GetTexture__8CMapMeshFP12CMaterialSetRi(
					mapMeshTable[param_2->m_initWOrk], pppEnvStPtr->m_materialSetPtr, textureIndex);
			}

			if ((param_2->m_payload[0] == 1) && (work->m_refractionMap == 0)) {
				u32 y;
				u32 x;

				work->m_refractionMap = (CrystalRefractionMap*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
					sizeof(CrystalRefractionMap), pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xA7);

				CrystalRefractionMap* textureInfo = work->m_refractionMap;
				u32 textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
				textureInfo->m_imageData = pppMemAlloc__FUlPQ27CMemory6CStagePci(
					textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xAC);
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

						magnitude = 4.0f * (magnitude * (float)fmod(magnitude, 1.0));
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
					0x20, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xB4);
				GXInitTexObj(work->m_refractionTexObj, textureInfo->m_imageData,
					(u16)textureInfo->m_width, (u16)textureInfo->m_height, GX_TF_IA8, GX_CLAMP, GX_CLAMP,
					GX_FALSE);
			}
		}
	}
}

/*
 * --INFO--
 * Address:	800dc9a0
 * Size:	1444b
 */
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkB* param_2, struct pppCrystalUnkC* param_3)
{
	float texW;
	float texH;
	s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
	u8* workDataBase = (u8*)pppCrystal + serializedDataOffsets[2] + 0x80;
	u8* colorDataBase = (u8*)pppCrystal + serializedDataOffsets[1] + 0x80;

	if (param_2->m_dataValIndex == 0xFFFF) {
		return;
	}

	pppModelSt* model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_dataValIndex];
	int indirectTex = 0;
	int texSlot = 0;
	int baseTex = GetTexture__8CMapMeshFP12CMaterialSetRi((CMapMesh*)model, pppEnvStPtr->m_materialSetPtr, texSlot);
	if (param_2->m_payload[0] == 0) {
		if (param_2->m_initWOrk == 0xFFFF) {
			return;
		}
		indirectTex = GetTexture__8CMapMeshFP12CMaterialSetRi(
			((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param_2->m_initWOrk], pppEnvStPtr->m_materialSetPtr, texSlot);
	}

	int x = 0;
	int y = 0;
	int w = 0x280;
	int h = 0x1C0;
	int backBufferTex = GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, x, y, w, h, 0);
	if (backBufferTex == 0) {
		return;
	}

	pppSetBlendMode(param_2->m_payload[1]);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		colorDataBase + 8, (u8*)pppCrystal + 0x40, param_2->m_arg3,
		param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1, param_2->m_payload[3]);

	Mtx texMtx = {
		{ DAT_801db5b8, DAT_801db5bc, DAT_801db5c0, DAT_801db5c4 },
		{ DAT_801db5c8, DAT_801db5cc, DAT_801db5d0, DAT_801db5d4 },
		{ DAT_801db5d8, DAT_801db5dc, DAT_801db5e0, DAT_801db5e4 },
	};

	if (param_2->m_payload[0] == 1) {
		texW = FLOAT_80330fa8;
		texH = FLOAT_80330fa8;
	}
	else {
		texW = (float)*(u32*)(indirectTex + 0x64);
		texH = (float)*(u32*)(indirectTex + 0x68);
	}

	float indMtx[2][3] = {};
	indMtx[0][0] = ((FLOAT_80330fac * texW) / FLOAT_80330fb0) * param_2->m_stepValue;
	indMtx[1][1] = ((FLOAT_80330fac * texH) / FLOAT_80330fb4) * param_2->m_stepValue;

	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	GXSetNumTexGens(3);
	GXSetNumTevStages(3);

	Mtx lightMtx;
	if ((int)Game.m_currentSceneId == 7) {
		C_MTXLightPerspective(
			lightMtx, FLOAT_80330fb8, FLOAT_80330fbc, FLOAT_80330fc0, FLOAT_80330fac, FLOAT_80330fc0, FLOAT_80330fc0);
	} else {
		C_MTXLightPerspective(
			lightMtx, CameraPcs._252_4_, FLOAT_80330fbc, FLOAT_80330fc0, FLOAT_80330fac, FLOAT_80330fc0, FLOAT_80330fc0);
	}

	GXLoadTexMtxImm(texMtx, 0x40, GX_MTX3x4);
	GXLoadTexMtxImm(lightMtx, 0x43, GX_MTX3x4);
	GXSetTexCoordGen2((GXTexCoordID)0, GX_TG_MTX3x4, GX_TG_NRM, 0x3C, GX_TRUE, 0x40);
	GXSetTexCoordGen2((GXTexCoordID)1, GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0, GX_FALSE, 0x43);
	GXLoadTexObj((_GXTexObj*)backBufferTex, GX_TEXMAP0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 1, 0, 0xFF);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
	GXLoadTexObj((_GXTexObj*)(baseTex + 0x28), GX_TEXMAP2);
	GXSetTexCoordGen2((GXTexCoordID)2, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 2, 2, 4);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0, 8, 0xB, 0xF);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 7, 7, 0);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);
	_GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0, 0xA, 0xB, 0xF);
	_GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
	_GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 7, 7, 0);
	_GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
	if (param_2->m_payload[0] == 1) {
		GXLoadTexObj((_GXTexObj*)(*(u32*)(workDataBase + 4)), GX_TEXMAP1);
	} else {
		GXLoadTexObj((_GXTexObj*)(indirectTex + 0x28), GX_TEXMAP1);
	}
	GXSetNumIndStages(1);
	GXSetIndTexOrder((GXIndTexStageID)0, (GXTexCoordID)0, (GXTexMapID)1);
	GXSetIndTexCoordScale((GXIndTexStageID)0, GX_ITS_1, GX_ITS_1);
	GXSetIndTexMtx((GXIndTexMtxID)1, indMtx, 1);
	GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, GX_ITF_8, GX_ITB_ST, GX_ITM_0, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE,
		GX_ITBA_OFF);
	GXClearVtxDesc();
	GXSetVtxDesc((GXAttr)9, GX_INDEX16);
	GXSetVtxDesc((GXAttr)10, GX_INDEX16);
	GXSetVtxDesc((GXAttr)0xB, GX_INDEX16);
	GXSetVtxDesc((GXAttr)0xD, GX_INDEX16);
	pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)pppCrystal + 0x70), 0);
	GXSetNumIndStages(0);
	GXSetTevDirect((GXTevStageID)0);
	memset(indMtx, 0, sizeof(indMtx));
	GXSetIndTexMtx((GXIndTexMtxID)1, indMtx, 1);
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
