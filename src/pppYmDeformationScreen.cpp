#include "ffcc/pppYmDeformationScreen.h"
#include "global.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(YmDeformationScreenDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(YmDeformationScreenDataOffsets, m_workOffset) == 0x8);

static const float kYmDeformationScreenZero = 0.0f;
static const float kYmDeformationScreenOrthoScaleX = 0.003125f;
static const float kYmDeformationScreenOrthoScaleY = -0.004464f;
static const float kYmDeformationScreenOne = 1.0f;
static const float kYmDeformationScreenOrthoOffsetX = -1.0f;
static const float kYmDeformationScreenAngleToRad = 0.017453292f;
static const float kYmDeformationScreenQuadRight = 640.0f;
static const float kYmDeformationScreenQuadMiddleY = 224.0f;
static const float kYmDeformationScreenQuadBottom = 448.0f;

static inline YmDeformationScreenDataOffsets* GetYmDeformationScreenDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<YmDeformationScreenDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline VYmDeformationScreen* GetYmDeformationScreenWork(pppYmDeformationScreen* obj, s32 offset)
{
	return reinterpret_cast<VYmDeformationScreen*>(obj->m_workArea + offset);
}

/*
 * --INFO--
 * PAL Address: 0x800981a8
 * PAL Size: 1716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, YmDeformationScreenStep* step, _pppCtrlTable* param3)
{
	VYmDeformationScreen* work = GetYmDeformationScreenWork(
		param1, GetYmDeformationScreenDataOffsets(param3)->m_workOffset);
	int textureIndex = 0;
	GXTexObj backTexObj;
	Mtx identity;
	float indMtx[2][3];
	Mtx44 screenMtx;
	float depth;
	float texU;
	float texV;
	float quadMiddleY;
	float one;
	float quadRight;
	float zero;
	pppCVECTOR color;
	CTexture* texture;

	if (step->m_dataValIndex == 0xFFFF) {
		return;
	}

	texture = ((CMapMesh**)ppvEnv->m_mapMeshPtr)[step->m_dataValIndex]->GetTexture(
		ppvEnv->m_materialSetPtr, textureIndex);

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	color.rgba[0] = 0x40;
	color.rgba[1] = 0x40;
	color.rgba[2] = 0x40;
	color.rgba[3] = 0x40;
	pppSetBlendMode(0);
	pppSetDrawEnv(&color, (pppFMATRIX*)0, kYmDeformationScreenZero, (u8)0, (u8)0, (u8)0, (u8)0, (u8)1, (u8)1, (u8)0);
	_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	_GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_RED);
	_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
	_GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
	_GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
	_GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	_GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
	_GXSetTevOp(GX_TEVSTAGE1, GX_MODULATE);

	gUtil.BeginQuadEnv();
	gUtil.SetVtxFmt_POS_CLR_TEX0_TEX1();
	GXSetNumTevStages(1);
	GXSetNumTexGens(2);
	GXSetNumChans(1);
	{
		Mtx44 orthoMtx;
		Mtx rot;

		PSMTXIdentity(identity);
		GXLoadPosMtxImm(identity, 0);
		GXSetCurrentMtx(0);

		PSMTX44Identity(orthoMtx);
		orthoMtx[0][0] = kYmDeformationScreenOrthoScaleX;
		orthoMtx[1][1] = kYmDeformationScreenOrthoScaleY;
		orthoMtx[2][2] = kYmDeformationScreenOne;
		orthoMtx[0][3] = kYmDeformationScreenOrthoOffsetX;
		orthoMtx[1][3] = orthoMtx[2][2];
		orthoMtx[2][3] = kYmDeformationScreenZero;
		GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);

		GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

		depth = work->m_depth;
		GXSetNumIndStages(1);
		GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
		GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
		GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);

		if ((work->m_angle == 0) || (work->m_angle == 0x168)) {
			work->m_angle = 1;
		}

		PSMTXRotRad(rot, 'z', kYmDeformationScreenAngleToRad * (float)work->m_angle);
		indMtx[0][0] = rot[0][0] * work->m_scale;
		indMtx[0][1] = rot[0][1] * work->m_scale;
		indMtx[0][2] = 0.0f;
		indMtx[1][0] = rot[1][0] * work->m_scale;
		indMtx[1][1] = rot[1][1] * work->m_scale;
		indMtx[1][2] = 0.0f;
		GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
	}

	texU = (float)(0x280 / texture->m_width);
	texV = (float)(0x1C0 / texture->m_height);

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	GXLoadTexObj(&texture->m_texObj, GX_TEXMAP1);
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	zero = kYmDeformationScreenZero;
	quadRight = kYmDeformationScreenQuadRight;
	one = kYmDeformationScreenOne;
	quadMiddleY = kYmDeformationScreenQuadMiddleY;
	GXPosition3f32(zero, zero, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(zero, zero);
	GXTexCoord2f32(zero, zero);
	GXPosition3f32(quadRight, zero, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(one, zero);
	GXTexCoord2f32(texU, zero);
	GXPosition3f32(quadRight, quadMiddleY, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(one, one);
	GXTexCoord2f32(texU, texV);
	GXPosition3f32(zero, quadMiddleY, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(zero, one);
	GXTexCoord2f32(zero, texV);

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 224, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	depth = work->m_depth;
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	{
		float bottomQuadBottom = kYmDeformationScreenQuadBottom;
		float bottomOne = kYmDeformationScreenOne;
		float bottomRight = kYmDeformationScreenQuadRight;
		float bottomMiddleY = kYmDeformationScreenQuadMiddleY;
		float bottomZero = kYmDeformationScreenZero;

		GXPosition3f32(bottomZero, bottomMiddleY, depth);
		GXColor1u32(*(u32*)color.rgba);
		GXTexCoord2f32(bottomZero, bottomZero);
		GXTexCoord2f32(bottomZero, bottomZero);
		GXPosition3f32(bottomRight, bottomMiddleY, depth);
		GXColor1u32(*(u32*)color.rgba);
		GXTexCoord2f32(bottomOne, bottomZero);
		GXTexCoord2f32(texU, bottomZero);
		GXPosition3f32(bottomRight, bottomQuadBottom, depth);
		GXColor1u32(*(u32*)color.rgba);
		GXTexCoord2f32(bottomOne, bottomOne);
		GXTexCoord2f32(texU, texV);
		GXPosition3f32(bottomZero, bottomQuadBottom, depth);
		GXColor1u32(*(u32*)color.rgba);
		GXTexCoord2f32(bottomZero, bottomOne);
		GXTexCoord2f32(bottomZero, texV);
	}

	gUtil.EndQuadEnv();
	DisableIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE0);
	GXSetProjection(screenMtx, GX_PERSPECTIVE);
	pppInitBlendMode();
}

/*
 * --INFO--
 * PAL Address: 0x8009885c
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationScreen(pppYmDeformationScreen* param1, YmDeformationScreenStep* step, _pppCtrlTable* param3)
{
	Vec4d outVec;
	Vec4d inVec;
	Mtx44 screenMtx;
	VYmDeformationScreen* work;
	YmDeformationScreenDataOffsets* serializedDataOffsets;
	float cameraX;
	float cameraY;
	float cameraZ;

	if (ppvUserStopPartF == 0) {
		serializedDataOffsets = GetYmDeformationScreenDataOffsets(param3);
		work = GetYmDeformationScreenWork(param1, serializedDataOffsets->m_workOffset);

		CalcGraphValue(
			param1, step->m_graphId, work->m_scale, work->m_values[0],
			work->m_values[1], step->m_initWOrk, step->m_stepValue, step->m_arg3);
		CalcGraphValue(
			param1, step->m_graphId, work->m_values[2], work->m_values[3], work->m_values[4],
			step->m_payload0, step->m_payload1, step->m_payload2);

		if (ppvIsLoopCalc == 0) {
			if (work->m_direction != 0) {
				work->m_angle += (int)work->m_values[2];
				if (work->m_angle > step->m_payload3) {
					work->m_direction = 0;
				}
			} else {
				work->m_angle -= (int)work->m_values[2];
				if (work->m_angle < -step->m_payload3) {
					work->m_direction = 1;
				}
			}

			if (param1->m_graphId == 0) {
				PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
				inVec.x = kYmDeformationScreenZero;
				inVec.y = kYmDeformationScreenZero;
				inVec.z = -*(float*)&step->m_payloadBytes[2];
				inVec.w = kYmDeformationScreenOne;
				Math.MTX44MultVec4(screenMtx, &inVec, &outVec);
				{
					float zero = kYmDeformationScreenZero;
					float outW = outVec.w;
					if (outW != zero) {
						outVec.z /= outW;
					}
				}
				work->m_depth = outVec.z;
			}

			if ((s32)Game.m_currentSceneId == 7) {
				cameraX = ppvCameraMatrix[0][3];
				cameraY = ppvCameraMatrix[1][3];
				cameraZ = ppvCameraMatrix[2][3];
			} else {
				cameraX = CameraPcs.m_targetX;
				cameraY = CameraPcs.m_targetY;
				cameraZ = CameraPcs.m_targetZ;
			}
			ppvMng->m_matrix.value[0][3] = cameraX;
			ppvMng->m_matrix.value[1][3] = cameraY;
			ppvMng->m_matrix.value[2][3] = cameraZ;
			pppSetFpMatrix(ppvMng);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80098a60
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, _pppCtrlTable*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80098a64
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen* obj, _pppCtrlTable* param2)
{
	float zero = kYmDeformationScreenZero;
	VYmDeformationScreen* work = GetYmDeformationScreenWork(
		obj, GetYmDeformationScreenDataOffsets(param2)->m_workOffset);

	work->m_values[1] = zero;
	work->m_values[0] = zero;
	work->m_scale = zero;
	work->m_values[4] = zero;
	work->m_values[3] = zero;
	work->m_values[2] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a94
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationScreen(pppYmDeformationScreen* obj, _pppCtrlTable* param2)
{
	short angle = 0;
	char direction = 1;
	float zero = kYmDeformationScreenZero;
	VYmDeformationScreen* work = GetYmDeformationScreenWork(
		obj, GetYmDeformationScreenDataOffsets(param2)->m_workOffset);

	work->m_angle = angle;
	work->m_direction = direction;
	work->m_values[1] = zero;
	work->m_values[0] = zero;
	work->m_scale = zero;
	work->m_values[4] = zero;
	work->m_values[3] = zero;
	work->m_values[2] = zero;
}
