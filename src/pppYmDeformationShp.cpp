#include "ffcc/pppYmDeformationShp.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
extern "C" {
extern const float FLOAT_803305f0;
extern const float kPppYmDeformationShpZero;
extern const float FLOAT_803305f8;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

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

struct pppCVECTOR {
	u8 rgba[4];
};

struct YmDeformationShpColorInfo {
	u32 m_unk0;
	u32 m_unk4;
	pppCVECTOR m_color;
};

struct VYmDeformationShp {
	GXTexObj* m_backBuffer;
	int m_pad0;
	int m_pad1;
	s16 m_angle;
	u8 m_direction;
	u8 m_pad2;
	float m_scale;
	float m_values[5];
};

struct pppYmDeformationShpLayout {
	u8 m_pad0[0x40];
	pppFMATRIX m_modelMatrix;
	u8 m_pad70[0x10];
};

struct _pppEnvStYmDeformationShp {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

void pppSetBlendMode(unsigned char);
void pppSetDrawEnv(pppCVECTOR*, pppFMATRIX*, float, unsigned char, unsigned char, unsigned char, unsigned char,
                   unsigned char, unsigned char, unsigned char);

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);

GXTexObj* GetBackBufferRect__8CGraphicFRiRiRiRii(CGraphic* graphic, int& left, int& top, int& width, int& height, int copy);
void DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(int stage, int indStage);
void MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(void* math, Mtx44 mtx, Vec4d* src, Vec4d* dst);
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
	VYmDeformationShp* work =
		(VYmDeformationShp*)((u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[2]);
	int textureIndex = 0;
	Vec2d uvs[4];
	float indMtx[2][3];
	Mtx rotMtx;
	Vec vertices[4];
	Mtx drawMtx;

	if (param_2->m_dataValIndex != 0xFFFF) {
		YmDeformationShpColorInfo* colorInfo =
			(YmDeformationShpColorInfo*)((u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[1]);
		_pppEnvStYmDeformationShp* env = (_pppEnvStYmDeformationShp*)pppEnvStPtr;
		int textureBase = GetTexture__8CMapMeshFP12CMaterialSetRi(
			env->m_mapMeshPtr[param_2->m_dataValIndex], env->m_materialSetPtr, textureIndex);

		PSMTXIdentity(rotMtx);
		pppSetBlendMode(1);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		pppSetDrawEnv(
			&colorInfo->m_color, &((pppYmDeformationShpLayout*)pppYmDeformationShp_)->m_modelMatrix, param_2->m_drawZ,
			param_2->m_alpha, 0, 0, 0, 1, 1, 0);

		GXSetNumTevStages(1);
		GXSetNumTexGens(2);
		GXSetNumChans(1);
		_GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		gUtil.SetVtxFmt_POS_TEX0_TEX1();
		GXLoadTexObj((GXTexObj*)(textureBase + 0x28), GX_TEXMAP1);
		GXSetNumIndStages(1);
		GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
		GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);

		if ((work->m_angle == 0) || (work->m_angle == 0x168)) {
			work->m_angle = 1;
		}

		PSMTXRotRad(drawMtx, 'z', FLOAT_803305f0 * (float)work->m_angle);
		float scale = work->m_scale;
		indMtx[0][0] = drawMtx[0][0] * scale;
		indMtx[0][1] = drawMtx[0][1] * scale;
		indMtx[0][2] = kPppYmDeformationShpZero;
		indMtx[1][0] = drawMtx[1][0] * scale;
		indMtx[1][1] = drawMtx[1][1] * scale;
		indMtx[1][2] = kPppYmDeformationShpZero;
		GXSetIndTexMtx(GX_ITM_0, indMtx, 1);

		if (param_2->m_splitMode == 0) {
			u8 size = param_2->m_size;
			float quadSize = (float)size;
			if (((s8)param_2->m_orientation) == 0) {
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
			} else if (((s8)param_2->m_orientation) == 1) {
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
			}

			uvs[0].x = kPppYmDeformationShpZero;
			uvs[0].y = kPppYmDeformationShpZero;
			uvs[1].x = FLOAT_803305f8;
			uvs[1].y = kPppYmDeformationShpZero;
			uvs[2].x = FLOAT_803305f8;
			uvs[2].y = FLOAT_803305f8;
			uvs[3].x = kPppYmDeformationShpZero;
			uvs[3].y = FLOAT_803305f8;
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, work, vertices, uvs);
		} else {
			short size = param_2->m_size;
			short split = param_2->m_splitSize;
			float uvSplit = (FLOAT_803305f8 / (float)(size + size)) * (float)(size - split);
			float uvRemainder;

			if (((s8)param_2->m_orientation) == 0) {
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
			} else if (((s8)param_2->m_orientation) == 1) {
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
			}

			uvRemainder = FLOAT_803305f8 - uvSplit;
			uvs[0].x = kPppYmDeformationShpZero;
			uvs[0].y = kPppYmDeformationShpZero;
			uvs[1].x = uvSplit;
			uvs[1].y = kPppYmDeformationShpZero;
			uvs[2].x = uvSplit;
			uvs[2].y = uvRemainder;
			uvs[3].x = kPppYmDeformationShpZero;
			uvs[3].y = uvRemainder;
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, work, vertices, uvs);

			if (((s8)param_2->m_orientation) == 0) {
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
			} else if (((s8)param_2->m_orientation) == 1) {
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
			RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, work, vertices, uvs);

			if (param_2->m_splitMode == 1) {
				if (((s8)param_2->m_orientation) == 0) {
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
				} else if (((s8)param_2->m_orientation) == 1) {
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
				RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, work, vertices, uvs);

				if (((s8)param_2->m_orientation) == 0) {
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
				} else if (((s8)param_2->m_orientation) == 1) {
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
				RenderDeformationShape((_pppPObject*)pppYmDeformationShp_, work, vertices, uvs);
			}
		}

		DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1, 0);
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
int RenderDeformationShape(_pppPObject* obj, VYmDeformationShp* work, Vec* vertices, Vec2d* uvs)
{
	pppYmDeformationShpLayout* layout = (pppYmDeformationShpLayout*)obj;
	Vec4d projected[4];
	float minY;
	float maxY;
	float minX;
	float maxX;
	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;
	Mtx texMtx;
	Mtx tempMtx;
	Vec cameraPos;
	Vec projectedObj[4];
	Vec* projectedObjPtrs[4];
	int minXIndex;
	int minYIndex;
	float texScaleX;
	float texScaleY;
	float projectedOffsetX;
	float projectedOffsetY;
	float offsetX;
	float offsetY;
	float one = FLOAT_803305f8;
	float screenCenterX = 320.0f;
	float screenScaleX = 0.003125f;
	float screenCenterY = 224.0f;
	float screenScaleY = 0.004464f;
	int i;

	for (i = 0; i < 4; i++) {
		Vec localVertex = vertices[i];
		Vec4d clipPos;
		Vec worldPos;
		PSMTXMultVec(layout->m_modelMatrix.value, &localVertex, &worldPos);
		clipPos.x = worldPos.x;
		clipPos.y = worldPos.y;
		clipPos.z = worldPos.z;
		clipPos.w = one;
		MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math, ppvScreenMatrix, &clipPos, &projected[i]);
		projected[i].x = projected[i].x / projected[i].w;
		projected[i].y = projected[i].y / projected[i].w;
		projected[i].z = projected[i].z / projected[i].w;
		projected[i].x = screenCenterX + projected[i].x / screenScaleX;
		projected[i].y = screenCenterY - projected[i].y / screenScaleY;
	}

	minY = 1000.0f;
	maxY = -1000.0f;
	minX = minY;
	maxX = maxY;
	for (i = 0; i < 4; i++) {
		if (projected[i].x > maxX) {
			maxX = projected[i].x;
		}
		if (projected[i].y > maxY) {
			maxY = projected[i].y;
		}
		if (projected[i].x < minX) {
			minX = projected[i].x;
		}
		if (projected[i].y < minY) {
			minY = projected[i].y;
		}
	}

	if (((int)minX % 2) != 0) {
		minX = minX - FLOAT_803305f8;
	}
	if (((int)minY % 2) != 0) {
		minY = minY - FLOAT_803305f8;
	}
	if (((int)maxX % 2) != 0) {
		maxX = maxX + FLOAT_803305f8;
	}
	if (((int)maxY % 2) != 0) {
		maxY = maxY + FLOAT_803305f8;
	}

	left = (int)minX;
	top = (int)minY;
	width = (int)maxX - left;
	height = (int)maxY - top;

	pppSetBlendMode(3);
	work->m_backBuffer = GetBackBufferRect__8CGraphicFRiRiRiRii(&Graphic, left, top, width, height, 0);
	if (work->m_backBuffer == 0) {
		return 0;
	}

	PSMTXIdentity(texMtx);
	texMtx[0][0] = ppvScreenMatrix[0][0];
	texMtx[0][1] = ppvScreenMatrix[0][1];
	texMtx[0][2] = ppvScreenMatrix[0][2];
	texMtx[1][0] = ppvScreenMatrix[1][0];
	texMtx[1][1] = ppvScreenMatrix[1][1];
	texMtx[1][2] = ppvScreenMatrix[1][2];
	texMtx[2][0] = ppvScreenMatrix[2][0];
	texMtx[2][1] = ppvScreenMatrix[2][1];
	texMtx[2][2] = ppvScreenMatrix[2][2];
	texMtx[0][0] = ppvScreenMatrix[0][0] * (320.0f / (float)width);
	texMtx[1][1] = ppvScreenMatrix[1][1] * -(224.0f / (float)height);
	texMtx[1][0] = ppvScreenMatrix[1][0];
	texMtx[2][0] = ppvScreenMatrix[2][0];
	texMtx[0][1] = ppvScreenMatrix[0][1];
	texMtx[2][1] = ppvScreenMatrix[2][1];
	texMtx[0][2] = -0.5f;
	texMtx[1][2] = -0.5f;
	texMtx[2][2] = -1.0f;

	PSMTXConcat(texMtx, layout->m_modelMatrix.value, tempMtx);
	cameraPos.z = kPppYmDeformationShpZero;
	cameraPos.y = kPppYmDeformationShpZero;
	cameraPos.x = kPppYmDeformationShpZero;
	PSMTXMultVec(tempMtx, &cameraPos, &cameraPos);
	cameraPos.x = cameraPos.x / cameraPos.z;
	cameraPos.y = cameraPos.y / cameraPos.z;
	texMtx[0][2] = -1.0f + cameraPos.x;
	texMtx[1][2] = -1.0f + cameraPos.y;
	PSMTXConcat(texMtx, layout->m_modelMatrix.value, tempMtx);

	for (i = 0; i < 4; i++) {
		Vec* projectedObjPtr = &projectedObj[i];
		projectedObjPtrs[i] = projectedObjPtr;
		PSMTXMultVec(tempMtx, &vertices[i], projectedObjPtrs[i]);
		projectedObjPtr->x = projectedObjPtr->x / projectedObjPtr->z;
		projectedObjPtr->y = projectedObjPtr->y / projectedObjPtr->z;
	}

	minXIndex = 0;
	minYIndex = 0;
	for (i = 1; i < 4; i++) {
		if (projected[minXIndex].x > projected[i].x) {
			minXIndex = i;
		}
		if (projected[minYIndex].y > projected[i].y) {
			minYIndex = i;
		}
	}

	texScaleX = one / (float)width;
	texScaleY = one / (float)height;
	projectedOffsetX = texScaleX * (projected[minXIndex].x - (float)left);
	offsetX = projectedObj[minXIndex].x - projectedOffsetX;
	projectedOffsetY = texScaleY * (projected[minYIndex].y - (float)top);
	offsetY = projectedObj[minYIndex].y - projectedOffsetY;

	if (left < 0) {
		if (640 < (left + width)) {
			texMtx[0][2] = texMtx[0][2] + (0.5f - cameraPos.x);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[maxIndex].x < projected[i].x) {
					maxIndex = i;
				}
			}
			projectedOffsetX = texScaleX * (((float)left + (float)width) - projected[maxIndex].x);
			texMtx[0][2] = texMtx[0][2] + (projectedObj[maxIndex].x + projectedOffsetX - FLOAT_803305f8);
		}
	} else if ((left + width) <= 640) {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	} else {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	}

	if (top < 0) {
		if (448 < (top + height)) {
			texMtx[1][2] = texMtx[1][2] + (0.5f - cameraPos.y);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[maxIndex].y < projected[i].y) {
					maxIndex = i;
				}
			}
			projectedOffsetY = texScaleY * (((float)top + (float)height) - projected[maxIndex].y);
			texMtx[1][2] = texMtx[1][2] + (projectedObj[maxIndex].y + projectedOffsetY - FLOAT_803305f8);
		}
	} else {
		texMtx[1][2] = texMtx[1][2] + offsetY;
	}

	PSMTXConcat(texMtx, layout->m_modelMatrix.value, texMtx);
	GXLoadTexMtxImm(texMtx, 0x1e, GX_MTX3x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
	GXLoadTexObj(work->m_backBuffer, GX_TEXMAP0);

	GXBegin(GX_QUADS, GX_VTXFMT7, 4);
	for (i = 0; i < 4; i++) {
		GXPosition3f32(vertices[i].x, vertices[i].y, vertices[i].z);
		GXTexCoord2f32(uvs[i].x, uvs[i].y);
		GXTexCoord2f32(uvs[i].x, uvs[i].y);
	}

	return 1;
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
	VYmDeformationShp* state;

	if (gPppCalcDisabled != 0) {
		return;
	}

	state = (VYmDeformationShp*)((u8*)pppYmDeformationShp_ + 0x80 + param_3->m_serializedDataOffsets[2]);

	CalcGraphValue(
		(_pppPObject*)pppYmDeformationShp_, param_2->m_graphId, state->m_scale, state->m_values[0], state->m_values[1],
		param_2->m_payload[0], param_2->m_payload[1], param_2->m_payload[2]);
	CalcGraphValue(
		(_pppPObject*)pppYmDeformationShp_, param_2->m_graphId, state->m_values[2], state->m_values[3], state->m_values[4],
		param_2->m_payload[3], param_2->m_payload[4], param_2->m_payload[5]);

	if (gPppInConstructor != 0) {
		return;
	}

	if (state->m_direction != 0) {
		int step = (int)state->m_values[2];

		state->m_angle = state->m_angle + step;
		if (state->m_angle > param_2->m_payload3) {
			state->m_direction = 0;
		}
	} else {
		int step = (int)state->m_values[2];

		state->m_angle = state->m_angle - step;
		if ((int)state->m_angle < -(int)param_2->m_payload3) {
			state->m_direction = 1;
		}
	}
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
 * PAL Address: 0x80090560
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkC* param_2)
{
	const float& value = kPppYmDeformationShpZero;
	VYmDeformationShp* state =
		(VYmDeformationShp*)((u8*)pppYmDeformationShp_ + 0x80 + param_2->m_serializedDataOffsets[2]);

	state->m_values[1] = value;
	state->m_values[0] = value;
	state->m_scale = value;
	state->m_values[4] = value;
	state->m_values[3] = value;
	state->m_values[2] = value;
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
	const float& value = kPppYmDeformationShpZero;
	VYmDeformationShp* state =
		(VYmDeformationShp*)((u8*)pppYmDeformationShp_ + 0x80 + param_2->m_serializedDataOffsets[2]);

	state->m_backBuffer = 0;
	state->m_pad0 = 0;
	state->m_pad1 = 0;
	state->m_angle = 0;
	state->m_direction = 1;
	state->m_values[1] = value;
	state->m_values[0] = value;
	state->m_scale = value;
	state->m_values[4] = value;
	state->m_values[3] = value;
	state->m_values[2] = value;
}
