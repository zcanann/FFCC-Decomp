#include "ffcc/pppCrystal.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/pppPart.h"
#include "ffcc/textureman.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include "PowerPC_EABI_Support/Runtime/runtime.h"
#include "ffcc/ppp_linkage.h"

extern const float FLOAT_80330FD4;
extern const float FLOAT_80330FD0;
extern const float FLOAT_80330FD8;
extern const double DOUBLE_80330FE0;
extern const double DOUBLE_80330FE8;
extern const double DOUBLE_80330FF0;
extern const float FLOAT_80330FF8;
extern const double DOUBLE_80331000;
extern const float FLOAT_80331008;
extern const float FLOAT_8033100C;
extern const float FLOAT_80331010;

#define CRYSTAL_REFRACTION_SIZE 32.0f
#define CRYSTAL_HALF_NEGATIVE -0.5f
#define CRYSTAL_SCREEN_WIDTH 640.0f
#define CRYSTAL_SCREEN_HEIGHT 448.0f
#define CRYSTAL_SCENE_FOVY 33.3f
#define CRYSTAL_ASPECT 1.3333334f
#define CRYSTAL_HALF 0.5f

struct CrystalIndTexMtx {
    float value[2][3];
};

struct CrystalTexMtx {
    float value[3][4];
};

struct pppCrystalColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

union CrystalFloatBits {
    float value;
    u32 bits;
};

extern const CrystalTexMtx s_crystalTexMtxBase = {
    {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, -0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}};

extern const CrystalIndTexMtx s_crystalIndTexMtxBase = {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

extern const char s_pppCrystalCpp[] = "pppCrystal.cpp";

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
    double guess = __frsqrte((double)value);

    guess = DOUBLE_80330FE0 * guess * (DOUBLE_80330FE8 - guess * guess * value);
    guess = DOUBLE_80330FE0 * guess * (DOUBLE_80330FE8 - guess * guess * value);
    guess = DOUBLE_80330FE0 * guess * (DOUBLE_80330FE8 - guess * guess * value);

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
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkB* param_2, struct _pppCtrlTable* param_3)
{
	float texW;
	float texH;
	int* serializedDataOffsets = param_3->m_serializedDataOffsets;
	s32 dataValIndex = param_2->m_dataValIndex;
	CrystalWork* work = reinterpret_cast<CrystalWork*>(pppCrystal->m_object.m_workArea + serializedDataOffsets[2]);
	pppCrystalColorBlock* colorBlock =
		reinterpret_cast<pppCrystalColorBlock*>(pppCrystal->m_object.m_workArea + serializedDataOffsets[1]);

	if (dataValIndex == 0xFFFF) {
		return;
	}

	pppModelSt* model = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[dataValIndex];
	CTexture* indirectTex = 0;
	int texSlot = 0;
	CTexture* baseTex = static_cast<CTexture*>(((CMapMesh*)model)->GetTexture(pppEnvStPtr->m_materialSetPtr, texSlot));
	if (param_2->m_payload[0] == 0) {
		if (param_2->m_initWOrk == 0xFFFF) {
			return;
		}
		indirectTex =
			static_cast<CTexture*>(pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk]->GetTexture(pppEnvStPtr->m_materialSetPtr, texSlot));
	}

	int x = 0;
	int y = 0;
	int w = 0x280;
	int h = 0x1C0;
	_GXTexObj* backBufferTex = Graphic.GetBackBufferRect(x, y, w, h, 0);
	if (backBufferTex == 0) {
		return;
	}

	pppSetBlendMode(param_2->m_payload[1]);
	pppSetDrawEnv(
		&colorBlock->m_color, &pppCrystal->m_object.m_drawMatrix, param_2->m_arg3,
		param_2->m_payload[5], param_2->m_payload[4], param_2->m_payload[1], param_2->m_payload[2], 1, 1, param_2->m_payload[3]);

	Mtx lightMtx;
	CrystalTexMtx texMtx = s_crystalTexMtxBase;

	if (param_2->m_payload[0] == 1) {
		texW = CRYSTAL_REFRACTION_SIZE;
		texH = CRYSTAL_REFRACTION_SIZE;
	}
	else {
		texW = (float)indirectTex->m_width;
		texH = (float)indirectTex->m_height;
	}

	CrystalIndTexMtx indMtx = s_crystalIndTexMtxBase;
	indMtx.value[0][0] = ((CRYSTAL_HALF_NEGATIVE * texW) / CRYSTAL_SCREEN_WIDTH) * param_2->m_stepValue;
	indMtx.value[1][1] = ((CRYSTAL_HALF_NEGATIVE * texH) / CRYSTAL_SCREEN_HEIGHT) * param_2->m_stepValue;

	_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXSetNumTexGens(3);
	GXSetNumTevStages(3);

	if ((int)Game.m_currentSceneId == 7) {
		C_MTXLightPerspective(
			lightMtx, CRYSTAL_SCENE_FOVY, CRYSTAL_ASPECT, CRYSTAL_HALF, CRYSTAL_HALF_NEGATIVE, CRYSTAL_HALF, CRYSTAL_HALF);
	} else {
		C_MTXLightPerspective(
			lightMtx, CameraPcs.m_fov, CRYSTAL_ASPECT, CRYSTAL_HALF, CRYSTAL_HALF_NEGATIVE, CRYSTAL_HALF, CRYSTAL_HALF);
	}

	GXLoadTexMtxImm(texMtx.value, 0x40, GX_MTX3x4);
	GXLoadTexMtxImm(lightMtx, 0x43, GX_MTX3x4);
	GXSetTexCoordGen2((GXTexCoordID)0, GX_TG_MTX3x4, GX_TG_NRM, 0x3C, GX_TRUE, 0x40);
	GXSetTexCoordGen2((GXTexCoordID)1, GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0, GX_FALSE, 0x43);
	GXLoadTexObj(backBufferTex, GX_TEXMAP0);
	_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR_NULL);
	_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
	_GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXLoadTexObj(&baseTex->m_texObj, GX_TEXMAP2);
	GXSetTexCoordGen2((GXTexCoordID)2, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
	_GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
	_GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
	_GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
	_GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
	_GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_CPREV, GX_CC_RASC, GX_CC_RASA, GX_CC_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
	_GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	if (param_2->m_payload[0] == 1) {
		GXLoadTexObj(work->m_refractionTexObj, GX_TEXMAP1);
	} else {
		GXLoadTexObj(&indirectTex->m_texObj, GX_TEXMAP1);
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
	pppDrawMesh(model, pppCrystal->m_object.m_drawMatrixPtr, 0);
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
void pppFrameCrystal(struct pppCrystal* pppCrystal, struct pppCrystalUnkB* param_2, struct _pppCtrlTable* param_3)
{
	u32 x;
	u32 y;
	u32 yTile;
	CrystalWork* work;
	CrystalRefractionMap* textureInfo;
	u32 textureSize;
	float magnitude;
	float stepX;
	float stepY;
	float yCoord;
	float xCoord;
	float ySq;
	float coordOffset;
	float coordScale;
	float modulationScale;
	float maxMagnitude;
	CMapMesh* mapMesh;
	int textureIndex;

	if (gPppCalcDisabled != 0) {
		return;
	}

	work = reinterpret_cast<CrystalWork*>(pppCrystal->m_object.m_workArea + param_3->m_serializedDataOffsets[2]);
	s32 dataValIndex = param_2->m_dataValIndex;
	if (dataValIndex == 0xFFFF) {
		return;
	}

	mapMesh = pppEnvStPtr->m_mapMeshPtr[dataValIndex];
	textureIndex = 0;
	mapMesh->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex);

	if (param_2->m_payload[0] == 0) {
		if (param_2->m_initWOrk == 0xFFFF) {
			return;
		}

		mapMesh = pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk];
		mapMesh->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex);
	}

	if ((param_2->m_payload[0] == 1) && (work->m_refractionMap == 0)) {
		work->m_refractionMap = (CrystalRefractionMap*)pppMemAlloc(
			sizeof(CrystalRefractionMap), pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xA7);

		textureInfo = work->m_refractionMap;
		textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
		textureInfo->m_imageData = (u8*)pppMemAlloc(
			textureSize, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xAC);
		textureInfo->m_format = GX_TF_IA8;
		textureInfo->m_width = 0x20;
		textureInfo->m_height = 0x20;
		textureInfo->m_imageCount = 0x100;
		textureInfo->m_bufferSize = textureSize;

		stepX = FLOAT_80330FD0 / (float)(textureInfo->m_width - 1U);
		stepY = FLOAT_80330FD0 / (float)(textureInfo->m_height - 1U);
		yCoord = FLOAT_80330FD4;
		maxMagnitude = FLOAT_80330FF8;
		coordOffset = FLOAT_8033100C;
		modulationScale = FLOAT_80331008;
		coordScale = FLOAT_80331010;

		for (y = 0; y < (u32)textureInfo->m_height; y++) {
			yTile = y >> 2;
			u32 yFine = (y & 3) * 4;
			ySq = yCoord * yCoord;
			xCoord = FLOAT_80330FD4;

			for (x = 0; x < (u32)textureInfo->m_width; x++) {
				u32 xFine = x & 3;
				magnitude = xCoord * xCoord + ySq;
				if (magnitude > FLOAT_80330FD8) {
					magnitude = CrystalSqrtPositive(magnitude);
				} else if ((double)magnitude < DOUBLE_80330FF0) {
					magnitude = NAN;
				} else if (CrystalFpClassify(magnitude) == 1) {
					magnitude = NAN;
				}

				if (magnitude > maxMagnitude) {
					magnitude = maxMagnitude;
				}

				double modulation = fmod(magnitude, DOUBLE_80331000);
				magnitude = modulationScale * (magnitude * (float)modulation);
				u8 nx = (u8)__cvt_fp2unsigned((double)(xCoord * magnitude * coordScale + coordOffset));
				u8* pixel = textureInfo->m_imageData +
					yTile * ((textureInfo->m_width & 0x1FFFFFFCU) << 3) +
					(x & 0x1FFFFFFC) * 8 +
					(xFine + yFine) * 2;
				pixel[0] = nx;
				u8 ny = (u8)__cvt_fp2unsigned((double)(yCoord * magnitude * coordScale + coordOffset));
				xCoord += stepX;
				pixel[1] = ny;
			}

			yCoord += stepY;
		}

		DCFlushRange(textureInfo->m_imageData, textureInfo->m_bufferSize);
		work->m_refractionTexObj = (GXTexObj*)pppMemAlloc(
			0x20, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xB4);
		GXInitTexObj(work->m_refractionTexObj, textureInfo->m_imageData,
			(u16)textureInfo->m_width, (u16)textureInfo->m_height, GX_TF_IA8, GX_CLAMP, GX_CLAMP,
			GX_FALSE);
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
void pppDestructCrystal(struct pppCrystal* pppCrystal, struct _pppCtrlTable* param_2)
{
	int* serializedDataOffsets = param_2->m_serializedDataOffsets;
	CrystalWork* work = reinterpret_cast<CrystalWork*>(pppCrystal->m_object.m_workArea + serializedDataOffsets[2]);
	CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(work->m_refractionMap);

	if ((stage != 0) && (*(CMemory::CStage**)stage != 0)) {
		pppHeapUseRate(*(CMemory::CStage**)stage);
		*(u32*)stage = 0;
	}
	if (stage != 0) {
		pppHeapUseRate(stage);
	}
	if (work->m_refractionTexObj != 0) {
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_refractionTexObj));
		work->m_refractionTexObj = 0;
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
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct _pppCtrlTable* param_2)
{
	int* serializedDataOffsets = param_2->m_serializedDataOffsets;
	CrystalWork* work = reinterpret_cast<CrystalWork*>(pppCrystal->m_object.m_workArea + serializedDataOffsets[2]);

	work->m_refractionMap = 0;
	work->m_refractionTexObj = 0;
}
