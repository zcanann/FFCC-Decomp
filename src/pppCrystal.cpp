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

extern const float FLOAT_80330fa8 = 32.0f;
extern const float FLOAT_80330fac = -0.5f;
extern const float FLOAT_80330fb0 = 640.0f;
extern const float FLOAT_80330fb4 = 448.0f;
extern const float FLOAT_80330fb8 = 33.3f;
extern const float FLOAT_80330fbc = 1.3333334f;
extern const float FLOAT_80330fc0 = 0.5f;
extern const double DOUBLE_80330FC8 = 4503599627370496.0;
extern const float FLOAT_80330FD0 = 2.0f;

#define CRYSTAL_REFRACTION_SIZE 32.0f
#define CRYSTAL_HALF_NEGATIVE -0.5f
#define CRYSTAL_SCREEN_WIDTH 640.0f
#define CRYSTAL_SCREEN_HEIGHT 448.0f
#define CRYSTAL_SCENE_FOVY 33.3f
#define CRYSTAL_ASPECT 1.3333334f
#define CRYSTAL_HALF 0.5f
#define CRYSTAL_COORD_RANGE 2.0f
#define CRYSTAL_COORD_MIN -1.0f
#define CRYSTAL_MAGNITUDE_UNIT 1.0f
#define CRYSTAL_MAGNITUDE_CAP 0.8f
#define CRYSTAL_FMOD_PERIOD 1.0
#define CRYSTAL_MODULATION_SCALE 4.0f
#define CRYSTAL_NORMAL_OFFSET 128.0f
#define CRYSTAL_NORMAL_SCALE 127.0f
extern "C" unsigned int __cvt_fp2unsigned(double);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, const char*, int);

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

struct CrystalIndTexMtx {
    float value[2][3];
};

struct CrystalTexMtx {
    float value[3][4];
};

struct pppCrystalRenderObject {
    u8 _pad0[0x10];
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_drawMatrix;
    Vec* m_drawMatrixPtr;
    u8 _pad74[0xC];
    CrystalWork m_work;
};

struct pppCrystalColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

union CrystalFloatBits {
    float value;
    u32 bits;
};

static const CrystalTexMtx s_crystalTexMtxBase = {
    {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, -0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}};

static const CrystalIndTexMtx s_crystalIndTexMtxBase = {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

static const char s_pppCrystalCpp[] = "pppCrystal.cpp";

static inline int CrystalFpClassify(float value)
{
    CrystalFloatBits bits;

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

static inline float CrystalSqrtPositive(float value)
{
    const double half = 0.5;
    const double three = 3.0;
    double guess = __frsqrte((double)value);

    guess = half * guess * (three - guess * guess * value);
    guess = half * guess * (three - guess * guess * value);
    guess = half * guess * (three - guess * guess * value);

    return (float)(value * guess);
}

/*
 * --INFO--
 * PAL Address: 0x800dc9a0
 * PAL Size: 1444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkB* param_2, struct pppCrystalUnkC* param_3)
{
	float texW;
	float texH;
	s32* serializedDataOffsets = param_3->m_serializedDataOffsets;
	s32 dataValIndex = param_2->m_dataValIndex;
	CrystalWork* work = (CrystalWork*)((u8*)pppCrystal + serializedDataOffsets[2] + 0x80);
	pppCrystalColorBlock* colorBlock = (pppCrystalColorBlock*)((u8*)pppCrystal + serializedDataOffsets[1] + 0x80);
	pppCrystalRenderObject* object;

	if (dataValIndex == 0xFFFF) {
		return;
	}

	pppModelSt* model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[dataValIndex];
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
		&colorBlock->m_color, (pppFMATRIX*)((u8*)pppCrystal + 0x40), param_2->m_arg3,
		param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1, param_2->m_payload[3]);

	Mtx lightMtx;
	CrystalTexMtx texMtx = s_crystalTexMtxBase;

	if (param_2->m_payload[0] == 1) {
		texW = CRYSTAL_REFRACTION_SIZE;
		texH = CRYSTAL_REFRACTION_SIZE;
	}
	else {
		texW = (float)*(u32*)(indirectTex + 0x64);
		texH = (float)*(u32*)(indirectTex + 0x68);
	}

	CrystalIndTexMtx indMtx = s_crystalIndTexMtxBase;
	indMtx.value[0][0] = ((CRYSTAL_HALF_NEGATIVE * texW) / CRYSTAL_SCREEN_WIDTH) * param_2->m_stepValue;
	indMtx.value[1][1] = ((CRYSTAL_HALF_NEGATIVE * texH) / CRYSTAL_SCREEN_HEIGHT) * param_2->m_stepValue;

	_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
	GXSetNumTexGens(3);
	GXSetNumTevStages(3);

	if ((int)Game.m_currentSceneId == 7) {
		C_MTXLightPerspective(
			lightMtx, CRYSTAL_SCENE_FOVY, CRYSTAL_ASPECT, CRYSTAL_HALF, CRYSTAL_HALF_NEGATIVE, CRYSTAL_HALF, CRYSTAL_HALF);
	} else {
		C_MTXLightPerspective(
			lightMtx, CameraPcs._252_4_, CRYSTAL_ASPECT, CRYSTAL_HALF, CRYSTAL_HALF_NEGATIVE, CRYSTAL_HALF, CRYSTAL_HALF);
	}

	GXLoadTexMtxImm(texMtx.value, 0x40, GX_MTX3x4);
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
		GXLoadTexObj(work->m_refractionTexObj, GX_TEXMAP1);
	} else {
		GXLoadTexObj((_GXTexObj*)(indirectTex + 0x28), GX_TEXMAP1);
	}
	GXSetNumIndStages(1);
	GXSetIndTexOrder((GXIndTexStageID)0, (GXTexCoordID)0, (GXTexMapID)1);
	GXSetIndTexCoordScale((GXIndTexStageID)0, GX_ITS_1, GX_ITS_1);
	GXSetIndTexMtx((GXIndTexMtxID)1, indMtx.value, 1);
	GXSetTevIndirect((GXTevStageID)0, (GXIndTexStageID)0, GX_ITF_8, GX_ITB_ST, GX_ITM_0, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE,
		GX_ITBA_OFF);
	GXClearVtxDesc();
	GXSetVtxDesc((GXAttr)9, GX_INDEX16);
	GXSetVtxDesc((GXAttr)10, GX_INDEX16);
	GXSetVtxDesc((GXAttr)0xB, GX_INDEX16);
	GXSetVtxDesc((GXAttr)0xD, GX_INDEX16);
	object = (pppCrystalRenderObject*)pppCrystal;
	pppDrawMesh__FP10pppModelStP3Veci(model, object->m_drawMatrixPtr, 0);
	GXSetNumIndStages(0);
	GXSetTevDirect((GXTevStageID)0);
	memset(&indMtx, 0, sizeof(indMtx));
	GXSetIndTexMtx((GXIndTexMtxID)1, indMtx.value, 1);
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
				CrystalRefractionMap* textureInfo;
				u32 textureSize;
				float stepX;
				float stepY;
				float yCoord;
				u32 y;
				u32 x;

				work->m_refractionMap = (CrystalRefractionMap*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
					sizeof(CrystalRefractionMap), pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xA7);

				textureInfo = work->m_refractionMap;
				textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
				textureInfo->m_imageData = (u8*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
					textureSize, pppEnvStPtr->m_stagePtr, s_pppCrystalCpp, 0xAC);
				textureInfo->m_format = GX_TF_IA8;
				textureInfo->m_width = 0x20;
				textureInfo->m_height = 0x20;
				textureInfo->m_imageCount = 0x100;
				textureInfo->m_bufferSize = textureSize;

				stepX = CRYSTAL_COORD_RANGE / (float)(textureInfo->m_width - 1);
				stepY = CRYSTAL_COORD_RANGE / (float)(textureInfo->m_height - 1);
				yCoord = CRYSTAL_COORD_MIN;

				for (y = 0; y < (u32)textureInfo->m_height; y++) {
					u32 yTile = y >> 2;
					u32 yFine = (y & 3) * 4;
					float ySq = yCoord * yCoord;
					float xCoord = CRYSTAL_COORD_MIN;

					for (x = 0; x < (u32)textureInfo->m_width; x++) {
						float magnitude = xCoord * xCoord + ySq;
						if (magnitude > CRYSTAL_MAGNITUDE_UNIT) {
							magnitude = CrystalSqrtPositive(magnitude);
						} else if ((double)magnitude < 0.0) {
							magnitude = NAN;
						} else if (CrystalFpClassify(magnitude) == 1) {
							magnitude = NAN;
						}

						if (magnitude > CRYSTAL_MAGNITUDE_CAP) {
							magnitude = CRYSTAL_MAGNITUDE_CAP;
						}

						double modulation = fmod(magnitude, CRYSTAL_FMOD_PERIOD);
						magnitude = CRYSTAL_MODULATION_SCALE * (magnitude * (float)modulation);
						u32 xFine = x & 3;
						u8 nx = (u8)__cvt_fp2unsigned((double)(xCoord * magnitude * CRYSTAL_NORMAL_SCALE + CRYSTAL_NORMAL_OFFSET));
						u8* pixel = textureInfo->m_imageData +
							yTile * ((textureInfo->m_width & 0x1FFFFFFCU) << 3) +
							(x & 0x1FFFFFFC) * 8 +
							(xFine + yFine) * 2;
						pixel[0] = nx;
						u8 ny = (u8)__cvt_fp2unsigned((double)(yCoord * magnitude * CRYSTAL_NORMAL_SCALE + CRYSTAL_NORMAL_OFFSET));
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
 * PAL Address: 0x800dd404
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkC* param_2)
{
	s32* serializedDataOffsets = *(s32**)((u8*)param_2 + 0xC);
	u32* data = (u32*)((char*)pppCrystal + serializedDataOffsets[2] + 0x80);

	data[0] = 0;
	data[1] = 0;
}
