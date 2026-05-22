#include "ffcc/pppYmDeformationScreen.h"
#include "ffcc/graphic.h"
#include "ffcc/render_buffers.h"
#include "ffcc/mapmesh.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include "ffcc/math.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

struct pppYmDeformationScreen;
struct YmDeformationScreenOffsetData {
	int unk0;
	int unk1;
	int offset;
};

struct YmDeformationScreenParam {
	char pad[0xc];
	YmDeformationScreenOffsetData* offsetData;
};

struct Vec4d {
	float x;
	float y;
	float z;
	float w;
};

struct VYmDeformationScreen {
	float m_depth;
	s16 m_angle;
	u8 m_direction;
	u8 m_pad;
	float m_scale;
	float m_values[5];
};

struct YmDeformationScreenData {
	char pad[0xc];
	int* m_serializedDataOffsets;
};

struct YmDeformationScreenStep {
	int m_graphId;
	int m_dataValIndex;
	float m_initWOrk;
	float m_stepValue;
	float m_arg3;
	float m_payload0;
	float m_payload1;
	float m_payload2;
	short m_payload3;
	char m_payloadBytes[0x1a];
};

struct _pppEnvStYmDeformationScreen {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

extern const float FLOAT_80330670;
extern const float FLOAT_80330674;
extern const float FLOAT_80330678;
extern const float FLOAT_8033067C;
extern const float FLOAT_80330680;
extern const float FLOAT_80330684;
extern const float FLOAT_80330688;
extern const float FLOAT_8033068C;
extern const float FLOAT_80330690;

void pppSetFpMatrix(_pppMngSt*);

extern "C" {
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
    void*, int, float*, float*, float*, float, float*, float*);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void*, Mtx44, Vec4d*, Vec4d*);

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
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	YmDeformationScreenStep* step = (YmDeformationScreenStep*)param2;
	VYmDeformationScreen* work =
		(VYmDeformationScreen*)((char*)param1 + 0x80 + ((YmDeformationScreenData*)param3)->m_serializedDataOffsets[2]);
	int textureIndex = 0;
	GXTexObj backTexObj;
	Mtx identity;
	float indMtx[2][3];
	Mtx44 screenMtx;
	float depth;
	float texU;
	float texV;
	pppCVECTOR color;
	int textureBase;

	if (step->m_dataValIndex == 0xFFFF) {
		return;
	}

	textureBase = reinterpret_cast<int>(
		((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex]->GetTexture(pppEnvStPtr->m_materialSetPtr, textureIndex));

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_AND);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	color.rgba[0] = 0x40;
	color.rgba[1] = 0x40;
	color.rgba[2] = 0x40;
	color.rgba[3] = 0x40;
	pppSetBlendMode(0);
	pppSetDrawEnv(&color, (pppFMATRIX*)0, FLOAT_80330670, (u8)0, (u8)0, (u8)0, (u8)0, (u8)1, (u8)1, (u8)0);
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
		orthoMtx[2][2] = FLOAT_8033067C;
		orthoMtx[0][0] = FLOAT_80330674;
		orthoMtx[1][1] = FLOAT_80330678;
		orthoMtx[0][3] = FLOAT_80330680;
		orthoMtx[1][3] = FLOAT_8033067C;
		orthoMtx[2][3] = FLOAT_80330670;
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

		PSMTXRotRad(rot, 'z', FLOAT_80330684 * (float)work->m_angle);
		indMtx[0][0] = rot[0][0] * work->m_scale;
		indMtx[0][1] = rot[0][1] * work->m_scale;
		indMtx[0][2] = 0.0f;
		indMtx[1][0] = rot[1][0] * work->m_scale;
		indMtx[1][1] = rot[1][1] * work->m_scale;
		indMtx[1][2] = 0.0f;
		GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
	}

	texU = (float)(0x280 / *(unsigned int*)(textureBase + 100));
	texV = (float)(0x1C0 / *(unsigned int*)(textureBase + 0x68));

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 0, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(FLOAT_80330670, FLOAT_80330670, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_80330670, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_80330670);
	GXTexCoord2f32(texU, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_8033067C);
	GXTexCoord2f32(texU, texV);
	GXPosition3f32(FLOAT_80330670, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_8033067C);
	GXTexCoord2f32(FLOAT_80330670, texV);

	Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backTexObj, 0, 224, 640, 224, 0, GX_LINEAR, GX_TF_RGBA8, 0);
	GXLoadTexObj(&backTexObj, GX_TEXMAP0);
	depth = work->m_depth;
	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	GXPosition3f32(FLOAT_80330670, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_8033068C, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_80330670);
	GXTexCoord2f32(texU, FLOAT_80330670);
	GXPosition3f32(FLOAT_80330688, FLOAT_80330690, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_8033067C, FLOAT_8033067C);
	GXTexCoord2f32(texU, texV);
	GXPosition3f32(FLOAT_80330670, FLOAT_80330690, depth);
	GXColor1u32(*(u32*)color.rgba);
	GXTexCoord2f32(FLOAT_80330670, FLOAT_8033067C);
	GXTexCoord2f32(FLOAT_80330670, texV);

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
void pppFrameYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	Vec4d outVec;
	Vec4d inVec;
	Mtx44 screenMtx;
	VYmDeformationScreen* work;
	int* serializedDataOffsets;
	float cameraX;
	float cameraY;
	float cameraZ;
	YmDeformationScreenStep* step;

	if (gPppCalcDisabled == 0) {
		step = (YmDeformationScreenStep*)param2;
		serializedDataOffsets = ((YmDeformationScreenData*)param3)->m_serializedDataOffsets;
		work = (VYmDeformationScreen*)((char*)param1 + 0x80 + serializedDataOffsets[2]);

		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param1, step->m_graphId, &work->m_scale, &work->m_values[0], &work->m_values[1], step->m_initWOrk,
			&step->m_stepValue, &step->m_arg3);
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
			param1, step->m_graphId, &work->m_values[2], &work->m_values[3], &work->m_values[4], step->m_payload0,
			&step->m_payload1, &step->m_payload2);

		if (gPppInConstructor == 0) {
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

			if (*(s32*)((u8*)param1 + 0xC) == 0) {
				PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
				inVec.x = FLOAT_80330670;
				inVec.y = FLOAT_80330670;
				inVec.z = -*(float*)&step->m_payloadBytes[2];
				inVec.w = FLOAT_8033067C;
				MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, screenMtx, &inVec, &outVec);
				{
					float outW = outVec.w;
					if (outW != FLOAT_80330670) {
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
				cameraX = CameraPcs._212_4_;
				cameraY = CameraPcs._216_4_;
				cameraZ = CameraPcs._220_4_;
			}
			pppMngStPtr->m_matrix.value[0][3] = cameraX;
			pppMngStPtr->m_matrix.value[1][3] = cameraY;
			pppMngStPtr->m_matrix.value[2][3] = cameraZ;
			pppSetFpMatrix(pppMngStPtr);
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
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, void*)
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
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	float zero = FLOAT_80330670;
	VYmDeformationScreen* work =
		(VYmDeformationScreen*)((char*)obj + ((YmDeformationScreenParam*)param2)->offsetData->offset + 0x80);

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
void pppConstructYmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	YmDeformationScreenOffsetData* offsetData = ((YmDeformationScreenParam*)param2)->offsetData;
	short angle = 0;
	char direction = 1;
	float zero = FLOAT_80330670;
	VYmDeformationScreen* work = (VYmDeformationScreen*)((char*)obj + offsetData->offset + 0x80);

	work->m_angle = angle;
	work->m_direction = direction;
	work->m_values[1] = zero;
	work->m_values[0] = zero;
	work->m_scale = zero;
	work->m_values[4] = zero;
	work->m_values[3] = zero;
	work->m_values[2] = zero;
}
