#include "ffcc/pppYmDeformationShp.h"
#include "global.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/math.h"
#include "ffcc/mapmesh.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppVec.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/textureman.h"
static const float kPppYmDeformationShpDegToRad = 0.017453292f;
static const float kPppYmDeformationShpZero = 0.0f;
static const float kPppYmDeformationShpOne = 1.0f;
static const double kPppYmDeformationShpIntToDoubleBias = 4503601774854144.0;
static const double kPppYmDeformationShpUnsignedToDoubleBias = 4503599627370496.0;
static const float kPppYmDeformationShpScreenCenterX = 320.0f;
static const float kPppYmDeformationShpInvScreenCenterX = 0.003125f;
static const float kPppYmDeformationShpScreenCenterY = 224.0f;
static const float kPppYmDeformationShpInvScreenCenterY = 0.004464f;
static const float kPppYmDeformationShpMaxBound = 1000.0f;
static const float kPppYmDeformationShpMinBound = -1000.0f;
static const float kPppYmDeformationShpTexCenter = -0.5f;
static const float kPppYmDeformationShpNegOne = -1.0f;
static const float kPppYmDeformationShpHalf = 0.5f;
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct YmDeformationShpColorInfo {
	u32 m_unk0;
	u32 m_unk4;
	pppCVECTOR m_color;
};

int RenderDeformationShape(_pppPObject*, VYmDeformationShp*, Vec*, Vec2d*);

STATIC_ASSERT(offsetof(YmDeformationShpDataOffsets, m_colorInfoOffset) == 0x4);
STATIC_ASSERT(offsetof(YmDeformationShpDataOffsets, m_stateOffset) == 0x8);
STATIC_ASSERT(sizeof(YmDeformationShpDataOffsets) == 0xC);

static inline YmDeformationShpDataOffsets* DeformationShpDataOffsets(_pppCtrlTable* ctrl)
{
	return reinterpret_cast<YmDeformationShpDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline VYmDeformationShp* DeformationShpState(pppYmDeformationShp* object, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<VYmDeformationShp*>(
		object->m_workArea + DeformationShpDataOffsets(ctrl)->m_stateOffset);
}

static inline YmDeformationShpColorInfo* DeformationShpColorInfo(pppYmDeformationShp* object, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<YmDeformationShpColorInfo*>(
		object->m_workArea + DeformationShpDataOffsets(ctrl)->m_colorInfoOffset);
}

inline void oddToEven(float& value)
{
	if (((int)value % 2) != 0) {
		value += kPppYmDeformationShpOne;
	}
}

inline void oddToEven(int& value)
{
	if ((value % 2) != 0) {
		value++;
	}
}

inline void calcScreenPos(Vec4d& out, Vec pos, Mtx drawMtx, Mtx44 screenMtx)
{
	Vec worldPos;
	Vec4d clipPos;

	PSMTXMultVec(drawMtx, &pos, &worldPos);
	clipPos.x = worldPos.x;
	clipPos.y = worldPos.y;
	clipPos.z = worldPos.z;
	clipPos.w = kPppYmDeformationShpOne;
	Math.MTX44MultVec4(screenMtx, &clipPos, &out);
	out.x = out.x / out.w;
	out.y = out.y / out.w;
	out.z = out.z / out.w;
	out.x = kPppYmDeformationShpScreenCenterX + out.x / kPppYmDeformationShpInvScreenCenterX;
	out.y = kPppYmDeformationShpScreenCenterY - out.y / kPppYmDeformationShpInvScreenCenterY;
}

inline void calcBoundaryBox(Vec& boundsMin, Vec& boundsMax, Vec4d* projected)
{
	boundsMin.y = kPppYmDeformationShpMaxBound;
	boundsMax.y = kPppYmDeformationShpMinBound;
	boundsMin.x = boundsMin.y;
	boundsMax.x = boundsMax.y;

	for (int i = 0; i < 4; i++) {
		if (projected[i].x > boundsMax.x) {
			boundsMax.x = projected[i].x;
		}
		if (projected[i].y > boundsMax.y) {
			boundsMax.y = projected[i].y;
		}
		if (projected[i].x < boundsMin.x) {
			boundsMin.x = projected[i].x;
		}
		if (projected[i].y < boundsMin.y) {
			boundsMin.y = projected[i].y;
		}
	}

	if (((int)boundsMin.x % 2) != 0) {
		boundsMin.x -= kPppYmDeformationShpOne;
	}
	if (((int)boundsMin.y % 2) != 0) {
		boundsMin.y -= kPppYmDeformationShpOne;
	}
	if (((int)boundsMax.x % 2) != 0) {
		boundsMax.x += kPppYmDeformationShpOne;
	}
	if (((int)boundsMax.y % 2) != 0) {
		boundsMax.y += kPppYmDeformationShpOne;
	}
}

inline void setVertexUV(Vec2d* uvs, float left, float top, float right, float bottom)
{
	uvs[0].x = left;
	uvs[0].y = top;
	uvs[1].x = right;
	uvs[1].y = top;
	uvs[2].x = right;
	uvs[2].y = bottom;
	uvs[3].x = left;
	uvs[3].y = bottom;
}

inline void setVertexPos(Vec* vertices, s8 orientation, float left, float top, float right, float bottom)
{
	if (orientation == 0) {
		vertices[0].x = left;
		vertices[0].y = top;
		vertices[0].z = kPppYmDeformationShpZero;
		vertices[1].x = right;
		vertices[1].y = top;
		vertices[1].z = kPppYmDeformationShpZero;
		vertices[2].x = right;
		vertices[2].y = bottom;
		vertices[2].z = kPppYmDeformationShpZero;
		vertices[3].x = left;
		vertices[3].y = bottom;
		vertices[3].z = kPppYmDeformationShpZero;
	} else if (orientation == 1) {
		vertices[0].x = left;
		vertices[0].y = kPppYmDeformationShpZero;
		vertices[0].z = top;
		vertices[1].x = right;
		vertices[1].y = kPppYmDeformationShpZero;
		vertices[1].z = top;
		vertices[2].x = right;
		vertices[2].y = kPppYmDeformationShpZero;
		vertices[2].z = bottom;
		vertices[3].x = left;
		vertices[3].y = kPppYmDeformationShpZero;
		vertices[3].z = bottom;
	}
}

inline void setVertexPos(Vec& v0, Vec& v1, Vec& v2, Vec& v3, float halfSize, s8 orientation)
{
	if (orientation == 0) {
		v0.x = -halfSize;
		v0.y = halfSize;
		v0.z = kPppYmDeformationShpZero;
		v1.x = halfSize;
		v1.y = halfSize;
		v1.z = kPppYmDeformationShpZero;
		v2.x = halfSize;
		v2.y = -halfSize;
		v2.z = kPppYmDeformationShpZero;
		v3.x = -halfSize;
		v3.y = -halfSize;
		v3.z = kPppYmDeformationShpZero;
	} else if (orientation == 1) {
		v0.x = -halfSize;
		v0.y = kPppYmDeformationShpZero;
		v0.z = halfSize;
		v1.x = halfSize;
		v1.y = kPppYmDeformationShpZero;
		v1.z = halfSize;
		v2.x = halfSize;
		v2.y = kPppYmDeformationShpZero;
		v2.z = -halfSize;
		v3.x = -halfSize;
		v3.y = kPppYmDeformationShpZero;
		v3.z = -halfSize;
	}
}

inline void setVertexPos(Vec& v0, Vec& v1, Vec& v2, Vec& v3, float halfX, float halfY, s8 orientation)
{
	if (orientation == 0) {
		v0.x = -halfX;
		v0.y = halfY;
		v0.z = kPppYmDeformationShpZero;
		v1.x = halfX;
		v1.y = halfY;
		v1.z = kPppYmDeformationShpZero;
		v2.x = halfX;
		v2.y = -halfY;
		v2.z = kPppYmDeformationShpZero;
		v3.x = -halfX;
		v3.y = -halfY;
		v3.z = kPppYmDeformationShpZero;
	} else if (orientation == 1) {
		v0.x = -halfX;
		v0.y = kPppYmDeformationShpZero;
		v0.z = halfY;
		v1.x = halfX;
		v1.y = kPppYmDeformationShpZero;
		v1.z = halfY;
		v2.x = halfX;
		v2.y = kPppYmDeformationShpZero;
		v2.z = -halfY;
		v3.x = -halfX;
		v3.y = kPppYmDeformationShpZero;
		v3.z = -halfY;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void SetUpIndWarp(VYmDeformationShp* work)
{
	float indMtx[2][3];
	Mtx drawMtx;

	GXSetNumIndStages(1);
	GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
	GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);

	if ((work->m_angle == 0) || (work->m_angle == 0x168)) {
		work->m_angle = 1;
	}

	PSMTXRotRad(drawMtx, 'z', kPppYmDeformationShpDegToRad * (float)work->m_angle);
	float scale = work->m_scale;
	indMtx[0][0] = drawMtx[0][0] * scale;
	indMtx[0][1] = drawMtx[0][1] * scale;
	indMtx[0][2] = kPppYmDeformationShpZero;
	indMtx[1][0] = drawMtx[1][0] * scale;
	indMtx[1][1] = drawMtx[1][1] * scale;
	indMtx[1][2] = kPppYmDeformationShpZero;
	GXSetIndTexMtx(GX_ITM_0, indMtx, 1);
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
void pppRenderYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpStep* param_2, _pppCtrlTable* param_3)
{
	_pppPObject* object = pppYmDeformationShp_;
	VYmDeformationShp* work = DeformationShpState(pppYmDeformationShp_, param_3);
	int textureIndex = 0;
	Vec2d uvs[4];
	Mtx rotMtx;
	Vec vertices[4];

	if (param_2->m_dataValIndex != 0xFFFF) {
		YmDeformationShpColorInfo* colorInfo = DeformationShpColorInfo(pppYmDeformationShp_, param_3);
		_pppEnvSt* env = ppvEnv;
		CTexture* texture =
			env->m_mapMeshPtr[param_2->m_dataValIndex]->GetTexture(env->m_materialSetPtr, textureIndex);

		PSMTXIdentity(rotMtx);
		pppSetBlendMode(1);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		pppSetDrawEnv(
			&colorInfo->m_color, &object->m_drawMatrix, param_2->m_drawZ,
			param_2->m_alpha, 0, 0, 0, 1, 1, 0);

		GXSetNumTevStages(1);
		GXSetNumTexGens(2);
		GXSetNumChans(1);
		_GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		gUtil.SetVtxFmt_POS_TEX0_TEX1();
		GXLoadTexObj(&texture->m_texObj, GX_TEXMAP1);
		SetUpIndWarp(work);

		if (param_2->m_splitMode == 0) {
			u8 size = param_2->m_size;
			s8 orientation = param_2->m_orientation;
			float quadSize = (float)size;
			setVertexPos(vertices[0], vertices[1], vertices[2], vertices[3], quadSize, orientation);
			setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, kPppYmDeformationShpOne, kPppYmDeformationShpOne);
			RenderDeformationShape(object, work, vertices, uvs);
		} else {
			short size = param_2->m_size;
			short split = param_2->m_splitSize;
			float uvSplit = (kPppYmDeformationShpOne / (float)((u8)param_2->m_size + (u8)param_2->m_size)) * (float)(size - split);
			float uvRemainder;

			setVertexPos(vertices, (s8)param_2->m_orientation, -size, -split, -split, split);
			uvRemainder = kPppYmDeformationShpOne - uvSplit;
			setVertexUV(uvs, kPppYmDeformationShpZero, uvSplit, uvSplit, uvRemainder);
			RenderDeformationShape(object, work, vertices, uvs);

			setVertexPos(vertices, (s8)param_2->m_orientation, size, -split, split, split);
			setVertexUV(uvs, kPppYmDeformationShpOne, uvSplit, uvRemainder, uvRemainder);
			RenderDeformationShape(object, work, vertices, uvs);

			if (param_2->m_splitMode == 1) {
				setVertexPos(vertices, (s8)param_2->m_orientation, -size, -size, size, -split);
				setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, kPppYmDeformationShpOne, uvSplit);
				RenderDeformationShape(object, work, vertices, uvs);

				setVertexPos(vertices, (s8)param_2->m_orientation, -size, split, size, size);
				setVertexUV(uvs, kPppYmDeformationShpZero, uvRemainder, kPppYmDeformationShpOne, kPppYmDeformationShpOne);
				RenderDeformationShape(object, work, vertices, uvs);
			}
		}

		DisableIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE0);
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
	Vec4d projected[4];
	Vec boundsMin;
	Vec boundsMax;
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
	float one = kPppYmDeformationShpOne;
	int i;

	for (i = 0; i < 4; i++) {
		calcScreenPos(projected[i], vertices[i], obj->m_drawMatrix.value, ppvScreenMatrix);
	}

	calcBoundaryBox(boundsMin, boundsMax, projected);

	left = (int)boundsMin.x;
	top = (int)boundsMin.y;
	width = (int)boundsMax.x - left;
	height = (int)boundsMax.y - top;

	pppSetBlendMode(3);
	work->m_backBuffer = Graphic.GetBackBufferRect(left, top, width, height, 0);
	if (work->m_backBuffer == 0) {
		return 0;
	}

	PSMTXIdentity(texMtx);
	texMtx[0][0] = ppvScreenMatrix[0][0];
	texMtx[0][2] = ppvScreenMatrix[0][2];
	texMtx[1][2] = ppvScreenMatrix[1][2];
	texMtx[1][1] = ppvScreenMatrix[1][1];
	texMtx[2][2] = ppvScreenMatrix[2][2];
	texMtx[1][0] = ppvScreenMatrix[1][0];
	texMtx[2][0] = ppvScreenMatrix[2][0];
	texMtx[0][1] = ppvScreenMatrix[0][1];
	texMtx[2][1] = ppvScreenMatrix[2][1];
	texMtx[0][0] = ppvScreenMatrix[0][0] * (kPppYmDeformationShpScreenCenterX / (float)width);
	texMtx[1][1] = ppvScreenMatrix[1][1] * -(kPppYmDeformationShpScreenCenterY / (float)height);
	texMtx[0][2] = kPppYmDeformationShpTexCenter;
	texMtx[1][2] = kPppYmDeformationShpTexCenter;
	texMtx[2][2] = kPppYmDeformationShpNegOne;

	PSMTXConcat(texMtx, obj->m_drawMatrix.value, tempMtx);
	cameraPos.z = kPppYmDeformationShpZero;
	cameraPos.y = kPppYmDeformationShpZero;
	cameraPos.x = kPppYmDeformationShpZero;
	PSMTXMultVec(tempMtx, &cameraPos, &cameraPos);
	cameraPos.x = cameraPos.x / cameraPos.z;
	cameraPos.y = cameraPos.y / cameraPos.z;
	texMtx[0][2] = kPppYmDeformationShpNegOne + cameraPos.x;
	texMtx[1][2] = kPppYmDeformationShpNegOne + cameraPos.y;
	PSMTXConcat(texMtx, obj->m_drawMatrix.value, tempMtx);

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
			texMtx[0][2] = texMtx[0][2] + (kPppYmDeformationShpHalf - cameraPos.x);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[maxIndex].x < projected[i].x) {
					maxIndex = i;
				}
			}
			projectedOffsetX = texScaleX * (((float)left + (float)width) - projected[maxIndex].x);
			texMtx[0][2] = texMtx[0][2] + (projectedObj[maxIndex].x + projectedOffsetX - kPppYmDeformationShpOne);
		}
	} else if (640 < (left + width)) {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	} else {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	}

	if (top < 0) {
		if (448 < (top + height)) {
			texMtx[1][2] = texMtx[1][2] + (kPppYmDeformationShpHalf - cameraPos.y);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (projected[maxIndex].y < projected[i].y) {
					maxIndex = i;
				}
			}
			projectedOffsetY = texScaleY * (((float)top + (float)height) - projected[maxIndex].y);
			texMtx[1][2] = texMtx[1][2] + (projectedObj[maxIndex].y + projectedOffsetY - kPppYmDeformationShpOne);
		}
	} else {
		texMtx[1][2] = texMtx[1][2] + offsetY;
	}

	PSMTXConcat(texMtx, obj->m_drawMatrix.value, texMtx);
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
void pppFrameYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpStep* param_2, _pppCtrlTable* param_3)
{
	VYmDeformationShp* state;

	if (ppvUserStopPartF != 0) {
		return;
	}

	state = DeformationShpState(pppYmDeformationShp_, param_3);

	CalcGraphValue(
		pppYmDeformationShp_, param_2->m_graphId, state->m_scale, state->m_values[0], state->m_values[1],
		param_2->m_deformation.m_scale.m_valueAdd, param_2->m_deformation.m_scale.m_velocityAdd,
		param_2->m_deformation.m_scale.m_accelerationAdd);
	CalcGraphValue(
		pppYmDeformationShp_, param_2->m_graphId, state->m_values[2], state->m_values[3], state->m_values[4],
		param_2->m_deformation.m_angle.m_valueAdd, param_2->m_deformation.m_angle.m_velocityAdd,
		param_2->m_deformation.m_angle.m_accelerationAdd);

	if (ppvIsLoopCalc != 0) {
		return;
	}

	if (state->m_direction != 0) {
		int step = (int)state->m_values[2];

		state->m_angle = state->m_angle + step;
		if (state->m_angle > param_2->m_angleLimit) {
			state->m_direction = 0;
		}
	} else {
		int step = (int)state->m_values[2];

		state->m_angle = state->m_angle - step;
		if ((int)state->m_angle < -(int)param_2->m_angleLimit) {
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
void pppDestructYmDeformationShp(pppYmDeformationShp*, _pppCtrlTable*)
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
void pppConstruct2YmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, _pppCtrlTable* param_2)
{
	float value = kPppYmDeformationShpZero;
	VYmDeformationShp* state = DeformationShpState(pppYmDeformationShp_, param_2);

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
void pppConstructYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, _pppCtrlTable* param_2)
{
	float value = kPppYmDeformationShpZero;
	VYmDeformationShp* state = DeformationShpState(pppYmDeformationShp_, param_2);

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
