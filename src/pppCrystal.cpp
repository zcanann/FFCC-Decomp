#include "global.h"
#include "ffcc/pppCrystal.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/hsd_image.h"
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

struct CrystalWork {
    HSD_ImageBuffer* m_refractionMap;
    GXTexObj* m_refractionTexObj;
};

STATIC_ASSERT(sizeof(HSD_ImageBuffer) == 0x18);
STATIC_ASSERT(sizeof(CrystalDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(CrystalDataOffsets, m_colorBlockOffset) == 0x4);
STATIC_ASSERT(offsetof(CrystalDataOffsets, m_workOffset) == 0x8);

inline void ImageBufferSetPixel_IA8(HSD_ImageBuffer* imageBuffer, u32 x, u32 y, u32 intensity, u32 alpha, u32, u32);

static inline CrystalDataOffsets* GetCrystalDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<CrystalDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline CrystalWork* GetCrystalWork(pppCrystal* crystal, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<CrystalWork*>(crystal->m_workArea + GetCrystalDataOffsets(ctrl)->m_workOffset);
}

static inline VColor* GetCrystalColorBlock(pppCrystal* crystal, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(crystal->m_workArea + GetCrystalDataOffsets(ctrl)->m_colorBlockOffset);
}

union CrystalFloatBits {
    float value;
    u32 bits;
};

extern const CrystalTexMtx s_crystalTexMtxBase = {
    {{0.5f, 0.0f, 0.0f, 0.5f}, {0.0f, -0.5f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.0f, 1.0f}}};

extern const CrystalIndTexMtx s_crystalIndTexMtxBase = {{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

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
    double guess = __frsqrte((double)value);

    guess = 0.5 * guess * (3.0 - guess * guess * value);
    guess = 0.5 * guess * (3.0 - guess * guess * value);
    guess = 0.5 * guess * (3.0 - guess * guess * value);

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
void pppRenderCrystal(pppCrystal* pppCrystal, pppCrystalStep* param_2, _pppCtrlTable* param_3)
{
	float texW;
	float texH;
	s32 dataValIndex = param_2->m_dataValIndex;
	CrystalWork* work = GetCrystalWork(pppCrystal, param_3);
	VColor* colorBlock = GetCrystalColorBlock(pppCrystal, param_3);

	if (dataValIndex == 0xFFFF) {
		return;
	}

	pppModelSt* model = (pppModelSt*)ppvEnv->m_mapMeshPtr[dataValIndex];
	CTexture* indirectTex = 0;
	int texSlot = 0;
	CTexture* baseTex = static_cast<CTexture*>(((CMapMesh*)model)->GetTexture(ppvEnv->m_materialSetPtr, texSlot));
	if (param_2->m_crystal.m_refractionMode == 0) {
		if (param_2->m_initWOrk == 0xFFFF) {
			return;
		}
		indirectTex =
			static_cast<CTexture*>(ppvEnv->m_mapMeshPtr[param_2->m_initWOrk]->GetTexture(ppvEnv->m_materialSetPtr, texSlot));
	}

	int x = 0;
	int y = 0;
	int w = 0x280;
	int h = 0x1C0;
	_GXTexObj* backBufferTex = Graphic.GetBackBufferRect(x, y, w, h, 0);
	if (backBufferTex == 0) {
		return;
	}

	pppSetBlendMode(param_2->m_crystal.m_blendMode);
	pppSetDrawEnv(
		&colorBlock->m_color, &pppCrystal->m_drawMatrix, param_2->m_arg3,
		param_2->m_crystal.m_drawEnvColor1, param_2->m_crystal.m_drawEnvColor0, param_2->m_crystal.m_blendMode, param_2->m_crystal.m_drawFlag, 1, 1, param_2->m_crystal.m_zMode);

	Mtx lightMtx;
	CrystalTexMtx texMtx = s_crystalTexMtxBase;

	if (param_2->m_crystal.m_refractionMode == 1) {
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
	if (param_2->m_crystal.m_refractionMode == 1) {
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
	pppDrawMesh(model, pppCrystal->m_drawMatrixPtr, 0);
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
void pppFrameCrystal(pppCrystal* pppCrystal, pppCrystalStep* param_2, _pppCtrlTable* param_3)
{
	u32 y;
	CrystalWork* work;
	u32 yTile;
	u32 x;
	HSD_ImageBuffer* textureInfo;
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

	if (ppvUserStopPartF != 0) {
		return;
	}

	work = GetCrystalWork(pppCrystal, param_3);
	s32 dataValIndex = param_2->m_dataValIndex;
	if (dataValIndex == 0xFFFF) {
		return;
	}

	mapMesh = ppvEnv->m_mapMeshPtr[dataValIndex];
	textureIndex = 0;
	mapMesh->GetTexture(ppvEnv->m_materialSetPtr, textureIndex);

	if (param_2->m_crystal.m_refractionMode == 0) {
		if (param_2->m_initWOrk == 0xFFFF) {
			return;
		}

		mapMesh = ppvEnv->m_mapMeshPtr[param_2->m_initWOrk];
		mapMesh->GetTexture(ppvEnv->m_materialSetPtr, textureIndex);
	}

	if ((param_2->m_crystal.m_refractionMode == 1) && (work->m_refractionMap == 0)) {
		work->m_refractionMap = (HSD_ImageBuffer*)pppMemAlloc(
			sizeof(HSD_ImageBuffer), ppvEnv->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xA7);

		textureInfo = work->m_refractionMap;
		textureSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);
		textureInfo->m_imageData = (u8*)pppMemAlloc(
			textureSize, ppvEnv->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xAC);
		textureInfo->m_format = GX_TF_IA8;
		textureInfo->m_width = 0x20;
		textureInfo->m_height = 0x20;
		textureInfo->m_imageCount = 0x100;
		textureInfo->m_bufferSize = textureSize;

		stepX = 2.0f / (float)(textureInfo->m_width - 1U);
		stepY = 2.0f / (float)(textureInfo->m_height - 1U);
		yCoord = -1.0f;
		coordOffset = 128.0f;
		maxMagnitude = 1.0f;
		modulationScale = 5.0f;
		coordScale = 127.0f;

		for (y = 0; y < (u32)textureInfo->m_height; y++) {
			yTile = y >> 2;
			u32 yFine = (y & 3) * 4;
			ySq = yCoord * yCoord;
			xCoord = -1.0f;

			for (x = 0; x < (u32)textureInfo->m_width; x++) {
				magnitude = xCoord * xCoord + ySq;
				if (magnitude > 0.0f) {
					magnitude = CrystalSqrtPositive(magnitude);
				} else if ((double)magnitude < 0.0) {
					magnitude = NAN;
				} else if (CrystalFpClassify(magnitude) == 1) {
					magnitude = NAN;
				}

				u32 xFine = x & 3;
				if (magnitude > maxMagnitude) {
					magnitude = maxMagnitude;
				}

				double modulation = fmod(magnitude, 0.2f);
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
			0x20, ppvEnv->m_stagePtr, const_cast<char*>(s_pppCrystalCpp), 0xB4);
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
void pppDestructCrystal(pppCrystal* pppCrystal, _pppCtrlTable* param_2)
{
	CrystalWork* work = GetCrystalWork(pppCrystal, param_2);
	HSD_ImageBuffer* textureInfo = work->m_refractionMap;

	if ((textureInfo != 0) && (textureInfo->m_imageData != 0)) {
		pppMemFree(textureInfo->m_imageData);
		textureInfo->m_imageData = 0;
	}
	if (textureInfo != 0) {
		pppMemFree(textureInfo);
	}
	if (work->m_refractionTexObj != 0) {
		pppMemFree(work->m_refractionTexObj);
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
void pppConstructCrystal(pppCrystal* pppCrystal, _pppCtrlTable* param_2)
{
	CrystalWork* work = GetCrystalWork(pppCrystal, param_2);

	work->m_refractionMap = 0;
	work->m_refractionTexObj = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void MakeRefractionMap(HSD_ImageBuffer* imageBuffer)
{
    u32 y;
    u32 x;
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

    imageBuffer->m_format = GX_TF_IA8;
    imageBuffer->m_width = 0x20;
    imageBuffer->m_height = 0x20;
    imageBuffer->m_imageCount = 0x100;
    imageBuffer->m_bufferSize = GXGetTexBufferSize(0x20, 0x20, GX_TF_IA8, GX_FALSE, 0);

    stepX = 2.0f / (float)(imageBuffer->m_width - 1U);
    stepY = 2.0f / (float)(imageBuffer->m_height - 1U);
    yCoord = -1.0f;
    maxMagnitude = 1.0f;
    coordOffset = 128.0f;
    modulationScale = 5.0f;
    coordScale = 127.0f;

    for (y = 0; y < imageBuffer->m_height; y++) {
        ySq = yCoord * yCoord;
        xCoord = -1.0f;

        for (x = 0; x < imageBuffer->m_width; x++) {
            magnitude = xCoord * xCoord + ySq;
            if (magnitude > 0.0f) {
                magnitude = CrystalSqrtPositive(magnitude);
            } else if ((double)magnitude < 0.0) {
                magnitude = NAN;
            } else if (CrystalFpClassify(magnitude) == 1) {
                magnitude = NAN;
            }

            if (magnitude > maxMagnitude) {
                magnitude = maxMagnitude;
            }

            double modulation = fmod(magnitude, 0.2f);
            magnitude = modulationScale * (magnitude * (float)modulation);
            ImageBufferSetPixel_IA8(
                imageBuffer, x, y,
                __cvt_fp2unsigned((double)(xCoord * magnitude * coordScale + coordOffset)),
                __cvt_fp2unsigned((double)(yCoord * magnitude * coordScale + coordOffset)), 0, 0);
            xCoord += stepX;
        }

        yCoord += stepY;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void ImageBufferSetPixel_IA8(HSD_ImageBuffer* imageBuffer, u32 x, u32 y, u32 intensity, u32 alpha, u32, u32)
{
    u32 yTile = y >> 2;
    u32 yFine = (y & 3) * 4;
    u32 xFine = x & 3;
    u8* pixel = imageBuffer->m_imageData +
        yTile * ((imageBuffer->m_width & 0x1FFFFFFCU) << 3) +
        (x & 0x1FFFFFFC) * 8 +
        (xFine + yFine) * 2;

    pixel[0] = (u8)intensity;
    pixel[1] = (u8)alpha;
}
