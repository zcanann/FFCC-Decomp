#include "ffcc/pppYmDeformationShp.h"
#include "ffcc/graphic.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
extern "C" {
extern const float kPppYmDeformationShpZero;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern float FLOAT_803305f0;
extern float FLOAT_803305f8;
extern float FLOAT_80330610;
extern float FLOAT_80330614;
extern float FLOAT_80330618;
extern float FLOAT_8033061c;
extern float FLOAT_80330620;
extern float FLOAT_80330624;
extern float FLOAT_8033062c;
extern float FLOAT_80330630;

struct Vec2d {
	float x;
	float y;
};

struct Vec4d {
	float x;
	float y;
	float z;
	float w;
};

struct _pppEnvStYmDeformationShp {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

void pppSetBlendMode(unsigned char);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
	void* color, void* matrix, float z, unsigned char a3, unsigned char a4, unsigned char a5, unsigned char a6,
	unsigned char a7, unsigned char a8, unsigned char a9);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int stage, int rasSel, int texSel);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int comp0, int ref0, int op, int comp1, int ref1);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int stage, int texCoord, int texMap, int chan);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int stage, int mode);
void SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(void* util);
int GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic* graphic, int& left, int& top, int& width, int& height, int copy);
void DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(int stage, int indStage);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void* math, Mtx44 mtx, Vec4d* src, Vec4d* dst);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationShp*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcBoundaryBox(Vec&, Vec&, Vec4d*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexPos(Vec&, Vec&, Vec&, Vec&, float, char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexPos(Vec*, char, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setVertexUV(Vec2d*, float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcScreenPos(Vec4d&, Vec&, float (*)[4], float (*)[4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void oddToEven(float&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80090590
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkC* param_2)
{
	float value = kPppYmDeformationShpZero;
	u32* state = (u32*)((u8*)pppYmDeformationShp_ + 0x80 + param_2->m_serializedDataOffsets[2]);

	state[0] = 0;
	state[1] = 0;
	state[2] = 0;
	*(u16*)(state + 3) = 0;
	*(u8*)((u8*)state + 0xe) = 1;
	((f32*)state)[6] = value;
	((f32*)state)[5] = value;
	((f32*)state)[4] = value;
	((f32*)state)[9] = value;
	((f32*)state)[8] = value;
	((f32*)state)[7] = value;
}

/*
 * --INFO--
 * PAL Address: 0x80090560
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkC* param_2)
{
	struct WorkState {
		u32 m_data0;
		u32 m_data1;
		u32 m_data2;
		u16 m_angle;
		u8 m_direction;
		u8 m_pad;
		float m_values[6];
	};

	float value = kPppYmDeformationShpZero;
	WorkState* state = (WorkState*)((u8*)pppYmDeformationShp_ + 0x80 + param_2->m_serializedDataOffsets[2]);

	state->m_values[2] = kPppYmDeformationShpZero;
	state->m_values[1] = value;
	state->m_values[0] = value;
	state->m_values[5] = value;
	state->m_values[4] = value;
	state->m_values[3] = value;
}

/*
 * --INFO--
 * PAL Address: 0x8009055c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkC*)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80090438
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkB* param_2, pppYmDeformationShpUnkC* param_3)
{
	struct FrameState {
		u32 m_data0;
		u32 m_data1;
		u32 m_data2;
		s16 m_angle;
		u8 m_direction;
		u8 m_pad;
		float m_values[6];
	};

	FrameState* state;

	if (gPppCalcDisabled != 0) {
		return;
	}

	state = (FrameState*)((u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[2]);

	CalcGraphValue(
		(_pppPObject*)pppYmDeformationShp_, param_2->m_graphId, state->m_values[0], state->m_values[1],
		state->m_values[2], param_2->m_payload[0], param_2->m_payload[1], param_2->m_payload[2]);
	CalcGraphValue(
		(_pppPObject*)pppYmDeformationShp_, param_2->m_graphId, state->m_values[3], state->m_values[4],
		state->m_values[5], param_2->m_payload[3], param_2->m_payload[4], param_2->m_payload[5]);

	if (gPppInConstructor != 0) {
		return;
	}

	if (state->m_direction != 0) {
		int step = (int)state->m_values[3];

		state->m_angle = state->m_angle + step;
		if (state->m_angle > param_2->m_payload3) {
			state->m_direction = 0;
		}
	} else {
		int step = (int)state->m_values[3];

		state->m_angle = state->m_angle - step;
		if ((int)state->m_angle < -(int)param_2->m_payload3) {
			state->m_direction = 1;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8008fa20
 * PAL Size: 2584b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void RenderDeformationShape(_pppPObject* obj, VYmDeformationShp* work, Vec* vertices, Vec2d* uvs)
{
	const f32 (*objMtx)[4] = (const f32(*)[4])((u8*)obj + 4);
	Vec4d projected[4];
	Vec worldPos;
	Vec4d clipPos;
	float maxX;
	float maxY;
	float minX;
	float minY;
	int left;
	int top;
	int width;
	int height;
	Mtx texMtx;
	Mtx tempMtx;
	Vec origin;
	Vec cameraPos;
	Vec projectedObj[4];
	int maxXIndex;
	int maxYIndex;
	float texScaleX;
	float texScaleY;
	float offsetX;
	float offsetY;
	int i;

	for (i = 0; i < 4; i++) {
		PSMTXMultVec(objMtx, &vertices[i], &worldPos);
		clipPos.x = worldPos.x;
		clipPos.y = worldPos.y;
		clipPos.z = worldPos.z;
		clipPos.w = FLOAT_803305f8;
		MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(0, ppvScreenMatrix, &clipPos, &projected[i]);
		projected[i].x = projected[i].x / projected[i].w;
		projected[i].y = projected[i].y / projected[i].w;
		projected[i].z = projected[i].z / projected[i].w;
		projected[i].x = FLOAT_80330610 + projected[i].x / FLOAT_80330614;
		projected[i].y = FLOAT_80330618 - projected[i].y / FLOAT_8033061c;
	}

	maxX = FLOAT_80330624;
	maxY = FLOAT_80330624;
	minX = FLOAT_80330620;
	minY = FLOAT_80330620;
	for (i = 0; i < 4; i++) {
		if (maxX < projected[i].x) {
			maxX = projected[i].x;
		}
		if (maxY < projected[i].y) {
			maxY = projected[i].y;
		}
		if (projected[i].x < minX) {
			minX = projected[i].x;
		}
		if (projected[i].y < minY) {
			minY = projected[i].y;
		}
	}

	if (((int)minX & 1) != 0) {
		minX = minX - FLOAT_803305f8;
	}
	if (((int)minY & 1) != 0) {
		minY = minY - FLOAT_803305f8;
	}
	if (((int)maxX & 1) != 0) {
		maxX = maxX + FLOAT_803305f8;
	}
	if (((int)maxY & 1) != 0) {
		maxY = maxY + FLOAT_803305f8;
	}

	left = (int)minX;
	top = (int)minY;
	width = (int)maxX - left;
	height = (int)maxY - top;

	pppSetBlendMode(3);
	*(int*)work = GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, left, top, width, height, 0);
	if (*(int*)work == 0) {
		return;
	}

	PSMTXIdentity(texMtx);
	texMtx[0][0] = ppvScreenMatrix[0][0] * (FLOAT_80330610 / (float)width);
	texMtx[1][1] = ppvScreenMatrix[1][1] * -(FLOAT_80330618 / (float)height);
	texMtx[1][0] = ppvScreenMatrix[1][0];
	texMtx[2][0] = ppvScreenMatrix[2][0];
	texMtx[0][1] = ppvScreenMatrix[0][1];
	texMtx[2][1] = ppvScreenMatrix[2][1];
	texMtx[0][2] = 0.0f;
	texMtx[1][2] = 0.0f;
	texMtx[2][2] = FLOAT_8033062c;

	PSMTXConcat(texMtx, objMtx, tempMtx);
	origin.x = kPppYmDeformationShpZero;
	origin.y = kPppYmDeformationShpZero;
	origin.z = kPppYmDeformationShpZero;
	PSMTXMultVec(tempMtx, &origin, &cameraPos);
	cameraPos.x = cameraPos.x / cameraPos.z;
	cameraPos.y = cameraPos.y / cameraPos.z;
	texMtx[0][2] = FLOAT_8033062c + cameraPos.x;
	texMtx[1][2] = FLOAT_8033062c + cameraPos.y;
	PSMTXConcat(texMtx, objMtx, tempMtx);

	for (i = 0; i < 4; i++) {
		PSMTXMultVec(tempMtx, &vertices[i], &projectedObj[i]);
		projectedObj[i].x = projectedObj[i].x / projectedObj[i].z;
		projectedObj[i].y = projectedObj[i].y / projectedObj[i].z;
	}

	maxXIndex = 0;
	maxYIndex = 0;
	for (i = 1; i < 4; i++) {
		if (projected[maxXIndex].x < projected[i].x) {
			maxXIndex = i;
		}
		if (projected[maxYIndex].y < projected[i].y) {
			maxYIndex = i;
		}
	}

	texScaleX = FLOAT_803305f8 / (float)width;
	texScaleY = FLOAT_803305f8 / (float)height;
	offsetX = projectedObj[maxXIndex].x - texScaleX * (projected[maxXIndex].x - (float)left);
	offsetY = projectedObj[maxYIndex].y - texScaleY * (projected[maxYIndex].y - (float)top);

	if (left < 0) {
		if ((left + width) < 641) {
			int minIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[i].x < projected[minIndex].x) {
					minIndex = i;
				}
			}
			texMtx[0][2] = texMtx[0][2] + (texScaleX * ((float)(left + width) - projected[minIndex].x) +
			                               projectedObj[minIndex].x - FLOAT_803305f8);
		} else {
			texMtx[0][2] = texMtx[0][2] + (FLOAT_80330630 - cameraPos.x);
		}
	} else {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	}

	if (top < 0) {
		if ((top + height) < 449) {
			int minIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[i].y < projected[minIndex].y) {
					minIndex = i;
				}
			}
			texMtx[1][2] = texMtx[1][2] + (texScaleY * ((float)(top + height) - projected[minIndex].y) +
			                               projectedObj[minIndex].y - FLOAT_803305f8);
		} else {
			texMtx[1][2] = texMtx[1][2] + (FLOAT_80330630 - cameraPos.y);
		}
	} else {
		texMtx[1][2] = texMtx[1][2] + offsetY;
	}

	PSMTXConcat(texMtx, objMtx, texMtx);
	GXLoadTexMtxImm(texMtx, 0x1e, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
	GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
	GXLoadTexObj((GXTexObj*)*(int*)work, GX_TEXMAP0);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	for (i = 0; i < 4; i++) {
		GXPosition3f32(vertices[i].x, vertices[i].y, vertices[i].z);
		GXTexCoord2f32(uvs[i].x, uvs[i].y);
		GXTexCoord2f32(uvs[i].x, uvs[i].y);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8008eec8
 * PAL Size: 2904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkB* param_2, pppYmDeformationShpUnkC* param_3)
{
	struct WorkState {
		int m_backBuffer;
		int m_pad0;
		int m_pad1;
		s16 m_angle;
		u8 m_direction;
		u8 m_pad2;
		float m_scale;
		float m_values[5];
	};

	int textureIndex = 0;
	WorkState* work = (WorkState*)((u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[2]);
	Mtx rotMtx;
	float indMtx[2][3];
	Vec vertices[4];
	Vec2d uvs[4];

	if (param_2->m_dataValIndex != 0xFFFF) {
		_pppEnvStYmDeformationShp* env = (_pppEnvStYmDeformationShp*)pppEnvStPtr;
		int colorOffset = param_3->m_serializedDataOffsets[1];
		int textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
			env->m_mapMeshPtr[param_2->m_dataValIndex], env->m_materialSetPtr, textureIndex);

		PSMTXIdentity(rotMtx);
		pppSetBlendMode(1);
		_GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
		pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
			(u8*)pppYmDeformationShp_ + 0x88 + colorOffset, (u8*)pppYmDeformationShp_ + 0x40, param_2->m_drawZ, param_2->m_alpha, 0, 0, 0, 1,
			1, 0);

		GXSetNumTevStages(1);
		GXSetNumTexGens(2);
		GXSetNumChans(1);
		_GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
		_GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
		_GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 3);
		SetVtxFmt_POS_TEX0_TEX1__5CUtilFv(&gUtil);
		GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
		GXSetNumIndStages(1);
		GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
		GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_ITW_0, GX_ITM_1);

		if ((work->m_angle == 0) || (work->m_angle == 0x168)) {
			work->m_angle = 1;
		}

		PSMTXRotRad(rotMtx, 'z', FLOAT_803305f0 * (float)work->m_angle);
		indMtx[0][0] = rotMtx[0][0] * work->m_scale;
		indMtx[0][1] = rotMtx[0][1] * work->m_scale;
		indMtx[1][0] = rotMtx[1][0] * work->m_scale;
		indMtx[1][1] = rotMtx[1][1] * work->m_scale;
		indMtx[0][2] = kPppYmDeformationShpZero;
		indMtx[1][2] = kPppYmDeformationShpZero;
		GXSetIndTexMtx(GX_ITM_1, indMtx, 1);

		if (param_2->m_splitMode == 0) {
			float quadSize = (float)param_2->m_size;
			if (param_2->m_orientation == 0) {
				vertices[0].x = -quadSize;
				vertices[0].y = quadSize;
				vertices[0].z = kPppYmDeformationShpZero;
				vertices[1].x = quadSize;
				vertices[1].y = quadSize;
				vertices[1].z = kPppYmDeformationShpZero;
				vertices[2].x = quadSize;
				vertices[2].y = -quadSize;
				vertices[2].z = kPppYmDeformationShpZero;
				vertices[3].x = -quadSize;
				vertices[3].y = -quadSize;
				vertices[3].z = kPppYmDeformationShpZero;
			} else if (param_2->m_orientation == 1) {
				vertices[0].x = -quadSize;
				vertices[0].y = kPppYmDeformationShpZero;
				vertices[0].z = -quadSize;
				vertices[1].x = quadSize;
				vertices[1].y = kPppYmDeformationShpZero;
				vertices[1].z = -quadSize;
				vertices[2].x = quadSize;
				vertices[2].y = kPppYmDeformationShpZero;
				vertices[2].z = quadSize;
				vertices[3].x = -quadSize;
				vertices[3].y = kPppYmDeformationShpZero;
				vertices[3].z = quadSize;
			} else {
				DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
				return;
			}

			uvs[0].x = kPppYmDeformationShpZero;
			uvs[0].y = kPppYmDeformationShpZero;
			uvs[1].x = FLOAT_803305f8;
			uvs[1].y = kPppYmDeformationShpZero;
			uvs[2].x = FLOAT_803305f8;
			uvs[2].y = FLOAT_803305f8;
			uvs[3].x = kPppYmDeformationShpZero;
			uvs[3].y = FLOAT_803305f8;
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, vertices, uvs);
		} else {
			float size = (float)param_2->m_size;
			float split = (float)param_2->m_splitSize;
			float uvSplit = (FLOAT_803305f8 / (size + size)) * (size - split);
			float uvRemainder = FLOAT_803305f8 - uvSplit;

			if (param_2->m_orientation == 0) {
				vertices[0].x = -size;
				vertices[0].y = -split;
				vertices[0].z = kPppYmDeformationShpZero;
				vertices[1].x = -split;
				vertices[1].y = -split;
				vertices[1].z = kPppYmDeformationShpZero;
				vertices[2].x = -split;
				vertices[2].y = split;
				vertices[2].z = kPppYmDeformationShpZero;
				vertices[3].x = -size;
				vertices[3].y = split;
				vertices[3].z = kPppYmDeformationShpZero;
			} else if (param_2->m_orientation == 1) {
				vertices[0].x = -size;
				vertices[0].y = kPppYmDeformationShpZero;
				vertices[0].z = -split;
				vertices[1].x = -split;
				vertices[1].y = kPppYmDeformationShpZero;
				vertices[1].z = -split;
				vertices[2].x = -split;
				vertices[2].y = kPppYmDeformationShpZero;
				vertices[2].z = split;
				vertices[3].x = -size;
				vertices[3].y = kPppYmDeformationShpZero;
				vertices[3].z = split;
			} else {
				DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
				return;
			}

			uvs[0].x = kPppYmDeformationShpZero;
			uvs[0].y = kPppYmDeformationShpZero;
			uvs[1].x = uvSplit;
			uvs[1].y = kPppYmDeformationShpZero;
			uvs[2].x = uvSplit;
			uvs[2].y = uvRemainder;
			uvs[3].x = kPppYmDeformationShpZero;
			uvs[3].y = uvRemainder;
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, vertices, uvs);

			if (param_2->m_orientation == 0) {
				vertices[0].x = split;
				vertices[0].y = -split;
				vertices[0].z = kPppYmDeformationShpZero;
				vertices[1].x = size;
				vertices[1].y = -split;
				vertices[1].z = kPppYmDeformationShpZero;
				vertices[2].x = size;
				vertices[2].y = split;
				vertices[2].z = kPppYmDeformationShpZero;
				vertices[3].x = split;
				vertices[3].y = split;
				vertices[3].z = kPppYmDeformationShpZero;
			} else {
				vertices[0].x = split;
				vertices[0].y = kPppYmDeformationShpZero;
				vertices[0].z = -split;
				vertices[1].x = size;
				vertices[1].y = kPppYmDeformationShpZero;
				vertices[1].z = -split;
				vertices[2].x = size;
				vertices[2].y = kPppYmDeformationShpZero;
				vertices[2].z = split;
				vertices[3].x = split;
				vertices[3].y = kPppYmDeformationShpZero;
				vertices[3].z = split;
			}

			uvs[0].x = FLOAT_803305f8;
			uvs[0].y = uvSplit;
			uvs[1].x = uvRemainder;
			uvs[1].y = uvSplit;
			uvs[2].x = uvRemainder;
			uvs[2].y = uvRemainder;
			uvs[3].x = FLOAT_803305f8;
			uvs[3].y = uvRemainder;
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, vertices, uvs);

			if (param_2->m_splitMode == 1) {
				if (param_2->m_orientation == 0) {
					vertices[0].x = -size;
					vertices[0].y = -size;
					vertices[0].z = kPppYmDeformationShpZero;
					vertices[1].x = size;
					vertices[1].y = -size;
					vertices[1].z = kPppYmDeformationShpZero;
					vertices[2].x = size;
					vertices[2].y = -split;
					vertices[2].z = kPppYmDeformationShpZero;
					vertices[3].x = -size;
					vertices[3].y = -split;
					vertices[3].z = kPppYmDeformationShpZero;
				} else if (param_2->m_orientation == 1) {
					vertices[0].x = -size;
					vertices[0].y = kPppYmDeformationShpZero;
					vertices[0].z = -size;
					vertices[1].x = size;
					vertices[1].y = kPppYmDeformationShpZero;
					vertices[1].z = -size;
					vertices[2].x = size;
					vertices[2].y = kPppYmDeformationShpZero;
					vertices[2].z = -split;
					vertices[3].x = -size;
					vertices[3].y = kPppYmDeformationShpZero;
					vertices[3].z = -split;
				}

				uvs[0].x = kPppYmDeformationShpZero;
				uvs[0].y = kPppYmDeformationShpZero;
				uvs[1].x = FLOAT_803305f8;
				uvs[1].y = kPppYmDeformationShpZero;
				uvs[2].x = FLOAT_803305f8;
				uvs[2].y = uvSplit;
				uvs[3].x = kPppYmDeformationShpZero;
				uvs[3].y = uvSplit;
				RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, vertices, uvs);

				if (param_2->m_orientation == 0) {
					vertices[0].x = split;
					vertices[0].y = -size;
					vertices[0].z = kPppYmDeformationShpZero;
					vertices[1].x = size;
					vertices[1].y = -size;
					vertices[1].z = kPppYmDeformationShpZero;
					vertices[2].x = size;
					vertices[2].y = size;
					vertices[2].z = kPppYmDeformationShpZero;
					vertices[3].x = split;
					vertices[3].y = size;
					vertices[3].z = kPppYmDeformationShpZero;
				} else if (param_2->m_orientation == 1) {
					vertices[0].x = split;
					vertices[0].y = kPppYmDeformationShpZero;
					vertices[0].z = -size;
					vertices[1].x = size;
					vertices[1].y = kPppYmDeformationShpZero;
					vertices[1].z = -size;
					vertices[2].x = size;
					vertices[2].y = kPppYmDeformationShpZero;
					vertices[2].z = size;
					vertices[3].x = split;
					vertices[3].y = kPppYmDeformationShpZero;
					vertices[3].z = size;
				}

				uvs[0].x = kPppYmDeformationShpZero;
				uvs[0].y = uvRemainder;
				uvs[1].x = FLOAT_803305f8;
				uvs[1].y = uvRemainder;
				uvs[2].x = FLOAT_803305f8;
				uvs[2].y = FLOAT_803305f8;
				uvs[3].x = kPppYmDeformationShpZero;
				uvs[3].y = FLOAT_803305f8;
				RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, (VYmDeformationShp*)work, vertices, uvs);
			}
		}
	}

	DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
}
