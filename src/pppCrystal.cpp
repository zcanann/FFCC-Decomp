#include "ffcc/pppCrystal.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_game.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>

extern int DAT_8032ed70;
extern float DAT_801db5b8;
extern float DAT_801db5bc;
extern float DAT_801db5c0;
extern float DAT_801db5c4;
extern float DAT_801db5c8;
extern float DAT_801db5cc;
extern float DAT_801db5d0;
extern float DAT_801db5d4;
extern float DAT_801db5d8;
extern float DAT_801db5dc;
extern float DAT_801db5e0;
extern float DAT_801db5e4;
extern float DAT_801db5ec;
extern float DAT_801db5f0;
extern float DAT_801db5f4;
extern float DAT_801db5fc;
extern float FLOAT_80330fa8;
extern float FLOAT_80330fac;
extern float FLOAT_80330fb0;
extern float FLOAT_80330fb4;
extern float FLOAT_80330fb8;
extern float FLOAT_80330fbc;
extern float FLOAT_80330fc0;
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
} CameraPcs;

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void pppSetBlendMode__FUc(unsigned char);
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
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	s32 iVar1 = param_2->m_serializedDataOffsets[2];
	u32* data = (u32*)((char*)pppCrystal + iVar1 + 8);

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
void pppDestructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	u32* puVar1 = (u32*)((char*)pppCrystal + 0x80 + param_2->m_serializedDataOffsets[2]);
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
 * Address:	800dcf44
 * Size:	1080b
 */
void pppFrameCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	int* refractionData;
	int* textureInfo;
	u16 dataValIndex;
	u16 initWork;
	u8* payload;
	int textureIndex;
	int textureBase;
	int textureSize;
	u32 y;
	u32 x;

	if (DAT_8032ed70 != 0) {
		return;
	}

	refractionData = (int*)((u8*)pppCrystal + param_3->m_serializedDataOffsets[2] + 8);
	dataValIndex = *(u16*)((u8*)param_2 + 4);
	if (dataValIndex == 0xFFFF) {
		return;
	}

	payload = (u8*)param_2 + 0x14;
	textureIndex = 0;
	textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
		&pppEnvStPtr->m_mapMeshPtr[dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);
	(void)textureBase;

	if (payload[0] == 0) {
		initWork = *(u16*)((u8*)param_2 + 8);
		if (initWork == 0xFFFF) {
			return;
		}
		GetTexture__8CMapMeshFP12CMaterialSetRi(
			&pppEnvStPtr->m_mapMeshPtr[initWork], pppEnvStPtr->m_materialSetPtr, textureIndex);
	}

	if ((payload[0] != 1) || (refractionData[0] != 0)) {
		return;
	}

	refractionData[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		0x18, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xA7);
	if (refractionData[0] == 0) {
		return;
	}

	textureInfo = (int*)refractionData[0];
	textureSize = (int)GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
	textureInfo[0] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xAC);
	textureInfo[1] = GX_TF_IA8;
	textureInfo[2] = 0x20;
	textureInfo[3] = 0x20;
	textureInfo[4] = 0x100;
	textureInfo[5] = textureSize;

	if (textureInfo[0] == 0) {
		return;
	}

	{
		const float start = -1.0f;
		const float step = 2.0f / (float)(textureInfo[2] - 1);
		float yy = start;

		for (y = 0; y < (u32)textureInfo[3]; ++y) {
			float xx = start;
			const float y2 = yy * yy;

			for (x = 0; x < (u32)textureInfo[2]; ++x) {
				float magnitude = xx * xx + y2;
				float normal = 0.0f;

				if (magnitude > 1.0f) {
					normal = 1.0f / sqrtf(magnitude);
				} else if (magnitude > 0.0f) {
					normal = sqrtf(magnitude);
				}

				if (normal > 0.8f) {
					normal = 0.8f;
				}

				{
					const u8 nx =
						(u8)__cvt_fp2unsigned((double)(xx * normal * 127.0f + 128.0f));
					const u8 ny =
						(u8)__cvt_fp2unsigned((double)(yy * normal * 127.0f + 128.0f));
					u8* pixel = (u8*)(textureInfo[0] +
						(y >> 2) * (textureInfo[2] & 0x1FFFFFFCU) * 8 +
						(x & 0x1FFFFFFC) * 8 +
						((x & 3) + (y & 3) * 4) * 2);

					pixel[0] = nx;
					pixel[1] = ny;
				}
				xx += step;
			}
			yy += step;
		}
	}

	DCFlushRange((void*)textureInfo[0], textureInfo[5]);
	refractionData[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
		0x20, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xB4);
	if (refractionData[1] != 0) {
		GXInitTexObj((GXTexObj*)refractionData[1], (void*)textureInfo[0], (u16)textureInfo[2],
			(u16)textureInfo[3], GX_TF_IA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
	}
}

/*
 * --INFO--
 * Address:	800dc9a0
 * Size:	1444b
 */
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	float texW;
	float texH;
	int offsetWork = param_3->m_serializedDataOffsets[2];
	int offsetColor = param_3->m_serializedDataOffsets[1];

	if ((u16)param_2->m_dataValIndex == 0xFFFF) {
		return;
	}

	pppModelSt* model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[(u16)param_2->m_dataValIndex];
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

	pppSetBlendMode__FUc(param_2->m_payload[1]);
	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		(u8*)pppCrystal + 0x88 + offsetColor, (u8*)pppCrystal + 0x40, (float)param_2->m_arg3,
		param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1, param_2->m_payload[3]);

	Mtx texMtx;
	texMtx[0][0] = DAT_801db5b8;
	texMtx[0][1] = DAT_801db5bc;
	texMtx[0][2] = DAT_801db5c0;
	texMtx[0][3] = DAT_801db5c4;
	texMtx[1][0] = DAT_801db5c8;
	texMtx[1][1] = DAT_801db5cc;
	texMtx[1][2] = DAT_801db5d0;
	texMtx[1][3] = DAT_801db5d4;
	texMtx[2][0] = DAT_801db5d8;
	texMtx[2][1] = DAT_801db5dc;
	texMtx[2][2] = DAT_801db5e0;
	texMtx[2][3] = DAT_801db5e4;

	texW = FLOAT_80330fa8;
	texH = FLOAT_80330fa8;
	if (param_2->m_payload[0] != 1) {
		texW = (float)*(u32*)(indirectTex + 0x64);
		texH = (float)*(u32*)(indirectTex + 0x68);
	}

	float indMtx[2][3];
	indMtx[0][0] = ((FLOAT_80330fac * texW) / FLOAT_80330fb0) * param_2->m_stepValue;
	indMtx[0][1] = DAT_801db5ec;
	indMtx[0][2] = DAT_801db5f0;
	indMtx[1][0] = DAT_801db5f4;
	indMtx[1][1] = ((FLOAT_80330fac * texH) / FLOAT_80330fb4) * param_2->m_stepValue;
	indMtx[1][2] = DAT_801db5fc;

	Mtx lightMtx;
	if (Game.game.m_currentSceneId == 7) {
		C_MTXLightPerspective(
			lightMtx, FLOAT_80330fb8, FLOAT_80330fbc, FLOAT_80330fc0, FLOAT_80330fac, FLOAT_80330fc0, FLOAT_80330fc0);
	} else {
		C_MTXLightPerspective(
			lightMtx, CameraPcs._252_4_, FLOAT_80330fbc, FLOAT_80330fc0, FLOAT_80330fac, FLOAT_80330fc0, FLOAT_80330fc0);
	}

	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	GXSetNumTexGens(3);
	GXSetNumTevStages(3);
	GXLoadTexMtxImm(texMtx, 0x40, GX_MTX3x4);
	GXLoadTexMtxImm(lightMtx, 0x43, GX_MTX3x4);
	GXSetTexCoordGen2((GXTexCoordID)0, GX_TG_MTX3x4, GX_TG_POS, 0x3C, GX_TRUE, 0x40);
	GXSetTexCoordGen2((GXTexCoordID)1, GX_TG_MTX3x4, GX_TG_NRM, GX_IDENTITY, GX_FALSE, 0x43);
	GXLoadTexObj((_GXTexObj*)backBufferTex, GX_TEXMAP0);
	_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 1, 0, 0xFF);
	_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
	GXLoadTexObj((_GXTexObj*)(baseTex + 0x28), GX_TEXMAP2);
	GXSetTexCoordGen2((GXTexCoordID)2, GX_TG_MTX2x4, GX_TG_TEX1, 0x3C, GX_FALSE, 0x7D);
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
		GXLoadTexObj((_GXTexObj*)(*(u32*)((u8*)pppCrystal + 0x84 + offsetWork)), GX_TEXMAP1);
	} else {
		GXLoadTexObj((_GXTexObj*)(indirectTex + 0x28), GX_TEXMAP1);
	}
	GXSetNumIndStages(1);
	GXSetIndTexOrder((GXIndTexStageID)0, (GXTexCoordID)0, (GXTexMapID)1);
	GXSetIndTexCoordScale((GXIndTexStageID)0, GX_ITS_1, GX_ITS_1);
	GXSetIndTexMtx((GXIndTexMtxID)1, indMtx, 1);
	GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, GX_ITF_8, GX_ITB_NONE, GX_ITM_1, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE,
		GX_ITBA_OFF);
	GXClearVtxDesc();
	GXSetVtxDesc((GXAttr)9, GX_DIRECT);
	GXSetVtxDesc((GXAttr)10, GX_DIRECT);
	GXSetVtxDesc((GXAttr)0xB, GX_DIRECT);
	GXSetVtxDesc((GXAttr)0xD, GX_DIRECT);
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
