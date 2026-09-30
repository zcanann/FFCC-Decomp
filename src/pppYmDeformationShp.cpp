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

static inline VColor* DeformationShpColorInfo(pppYmDeformationShp* object, _pppCtrlTable* ctrl)
{
	return reinterpret_cast<VColor*>(
		object->m_workArea + DeformationShpDataOffsets(ctrl)->m_colorInfoOffset);
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

inline void calcBoundaryBox(Vec& boundsMin, Vec& boundsMax, Vec4d* screenPos)
{
	boundsMin.y = kPppYmDeformationShpMaxBound;
	boundsMax.y = kPppYmDeformationShpMinBound;
	boundsMin.x = boundsMin.y;
	boundsMax.x = boundsMax.y;

	for (int i = 0; i < 4; i++) {
		if (screenPos[i].x > boundsMax.x) {
			boundsMax.x = screenPos[i].x;
		}
		if (screenPos[i].y > boundsMax.y) {
			boundsMax.y = screenPos[i].y;
		}
		if (screenPos[i].x < boundsMin.x) {
			boundsMin.x = screenPos[i].x;
		}
		if (screenPos[i].y < boundsMin.y) {
			boundsMin.y = screenPos[i].y;
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
		v0.z = -halfSize;
		v1.x = halfSize;
		v1.y = kPppYmDeformationShpZero;
		v1.z = -halfSize;
		v2.x = halfSize;
		v2.y = kPppYmDeformationShpZero;
		v2.z = halfSize;
		v3.x = -halfSize;
		v3.y = kPppYmDeformationShpZero;
		v3.z = halfSize;
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
inline void SetUpIndWarp(VYmDeformationShp* state)
{
	float indMtx[2][3];
	Mtx drawMtx;

	GXSetNumIndStages(1);
	GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
	GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);

	if ((state->m_angle == 0) || (state->m_angle == 0x168)) {
		state->m_angle = 1;
	}

	PSMTXRotRad(drawMtx, 'z', kPppYmDeformationShpDegToRad * (float)state->m_angle);
	indMtx[0][0] = drawMtx[0][0] * state->m_scale;
	indMtx[0][1] = drawMtx[0][1] * state->m_scale;
	indMtx[0][2] = kPppYmDeformationShpZero;
	indMtx[1][0] = drawMtx[1][0] * state->m_scale;
	indMtx[1][1] = drawMtx[1][1] * state->m_scale;
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
void pppRenderYmDeformationShp(pppYmDeformationShp* object, pppYmDeformationShpStep* step, _pppCtrlTable* ctrl)
{
	VYmDeformationShp* state = DeformationShpState(object, ctrl);
	int textureIndex = 0;
	Vec2d uvs[4];
	Mtx identityMtx;
	Vec vertices[4];

	if (step->m_dataValIndex != 0xFFFF) {
		VColor* colorInfo = DeformationShpColorInfo(object, ctrl);
		_pppEnvSt* env = ppvEnv;
		CTexture* texture =
			env->m_mapMeshPtr[step->m_dataValIndex]->GetTexture(env->m_materialSetPtr, textureIndex);

		PSMTXIdentity(identityMtx);
		pppSetBlendMode(1);
		_GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
		pppSetDrawEnv(
			&colorInfo->m_color, &object->m_drawMatrix, step->m_drawZ,
			step->m_alpha, 0, 0, 0, 1, 1, 0);

		GXSetNumTevStages(1);
		GXSetNumTexGens(2);
		GXSetNumChans(1);
		_GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		gUtil.SetVtxFmt_POS_TEX0_TEX1();
		GXLoadTexObj(&texture->m_texObj, GX_TEXMAP1);
		SetUpIndWarp(state);

		if (step->m_splitMode == 0) {
			s8 orientation = step->m_orientation;
			setVertexPos(vertices[0], vertices[1], vertices[2], vertices[3], (float)(u8)step->m_size, orientation);
			setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, kPppYmDeformationShpOne, kPppYmDeformationShpOne);
			RenderDeformationShape(object, state, vertices, uvs);
		} else {
			short size = step->m_size;
			short split = step->m_splitSize;
			float uvRemainder;
			float uvSplit = (kPppYmDeformationShpOne / (float)((u8)step->m_size << 1)) * (float)(size - split);

			setVertexPos(vertices, (s8)step->m_orientation, -size, -split, -split, split);
			setVertexUV(uvs, kPppYmDeformationShpZero, uvSplit, uvSplit, kPppYmDeformationShpOne - uvSplit);
			RenderDeformationShape(object, state, vertices, uvs);

			uvRemainder = kPppYmDeformationShpOne - uvSplit;
			setVertexPos(vertices, (s8)step->m_orientation, size, -split, split, split);
			setVertexUV(uvs, kPppYmDeformationShpOne, uvSplit, uvRemainder, uvRemainder);
			RenderDeformationShape(object, state, vertices, uvs);

			if (step->m_splitMode == 1) {
				setVertexPos(vertices, (s8)step->m_orientation, -size, -size, size, -split);
				setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, kPppYmDeformationShpOne, uvSplit);
				RenderDeformationShape(object, state, vertices, uvs);

				setVertexPos(vertices, (s8)step->m_orientation, -size, split, size, size);
				setVertexUV(uvs, kPppYmDeformationShpZero, uvRemainder, kPppYmDeformationShpOne, kPppYmDeformationShpOne);
				RenderDeformationShape(object, state, vertices, uvs);
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
int RenderDeformationShape(_pppPObject* object, VYmDeformationShp* state, Vec* vertices, Vec2d* uvs)
{
	Vec4d screenPos[4];
	Vec boundsMin;
	Vec boundsMax;
	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;
	Mtx texMtx;
	Mtx tempMtx;
	Vec projectedOrigin;
	Vec texPos[4];
	Vec* texPosPtrs[4];
	int minXIndex;
	int minYIndex;
	float texScaleX;
	float texScaleY;
	float texOffsetX;
	float texOffsetY;
	float offsetX;
	float offsetY;
	int i;

	for (i = 0; i < 4; i++) {
		calcScreenPos(screenPos[i], vertices[i], object->m_drawMatrix.value, ppvScreenMatrix);
	}

	calcBoundaryBox(boundsMin, boundsMax, screenPos);

	left = (int)boundsMin.x;
	top = (int)boundsMin.y;
	width = (int)boundsMax.x - left;
	height = (int)boundsMax.y - top;

	pppSetBlendMode(3);
	state->m_backBuffer = Graphic.GetBackBufferRect(left, top, width, height, 0);
	if (state->m_backBuffer == 0) {
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

	PSMTXConcat(texMtx, object->m_drawMatrix.value, tempMtx);
	projectedOrigin.z = kPppYmDeformationShpZero;
	projectedOrigin.y = kPppYmDeformationShpZero;
	projectedOrigin.x = kPppYmDeformationShpZero;
	PSMTXMultVec(tempMtx, &projectedOrigin, &projectedOrigin);
	projectedOrigin.x = projectedOrigin.x / projectedOrigin.z;
	projectedOrigin.y = projectedOrigin.y / projectedOrigin.z;
	texMtx[0][2] = kPppYmDeformationShpNegOne + projectedOrigin.x;
	texMtx[1][2] = kPppYmDeformationShpNegOne + projectedOrigin.y;
	PSMTXConcat(texMtx, object->m_drawMatrix.value, tempMtx);

	for (i = 0; i < 4; i++) {
		Vec* texPosPtr = &texPos[i];
		texPosPtrs[i] = texPosPtr;
		PSMTXMultVec(tempMtx, &vertices[i], texPosPtrs[i]);
		texPosPtr->x = texPosPtr->x / texPosPtr->z;
		texPosPtr->y = texPosPtr->y / texPosPtr->z;
	}

	minXIndex = 0;
	minYIndex = 0;
	for (i = 1; i < 4; i++) {
		if (screenPos[minXIndex].x > screenPos[i].x) {
			minXIndex = i;
		}
		if (screenPos[minYIndex].y > screenPos[i].y) {
			minYIndex = i;
		}
	}

	texScaleX = kPppYmDeformationShpOne / (float)width;
	texScaleY = kPppYmDeformationShpOne / (float)height;
	texOffsetX = texScaleX * (screenPos[minXIndex].x - (float)left);
	offsetX = texPos[minXIndex].x - texOffsetX;
	texOffsetY = texScaleY * (screenPos[minYIndex].y - (float)top);
	offsetY = texPos[minYIndex].y - texOffsetY;

	if (left < 0) {
		if (640 < (left + width)) {
			texMtx[0][2] = texMtx[0][2] + (kPppYmDeformationShpHalf - projectedOrigin.x);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (screenPos[maxIndex].x < screenPos[i].x) {
					maxIndex = i;
				}
			}
			texOffsetX = texScaleX * (((float)left + (float)width) - screenPos[maxIndex].x);
			texMtx[0][2] = texMtx[0][2] + (texPos[maxIndex].x + texOffsetX - kPppYmDeformationShpOne);
		}
	} else if (640 < (left + width)) {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	} else {
		texMtx[0][2] = texMtx[0][2] + offsetX;
	}

	if (top < 0) {
		if (448 < (top + height)) {
			texMtx[1][2] = texMtx[1][2] + (kPppYmDeformationShpHalf - projectedOrigin.y);
		} else {
			int maxIndex = 0;
			for (i = 1; i < 4; i++) {
				if (screenPos[maxIndex].y < screenPos[i].y) {
					maxIndex = i;
				}
			}
			texOffsetY = texScaleY * (((float)top + (float)height) - screenPos[maxIndex].y);
			texMtx[1][2] = texMtx[1][2] + (texPos[maxIndex].y + texOffsetY - kPppYmDeformationShpOne);
		}
	} else {
		texMtx[1][2] = texMtx[1][2] + offsetY;
	}

	PSMTXConcat(texMtx, object->m_drawMatrix.value, texMtx);
	GXLoadTexMtxImm(texMtx, 0x1e, GX_MTX3x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
	GXLoadTexObj(state->m_backBuffer, GX_TEXMAP0);

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
void pppFrameYmDeformationShp(pppYmDeformationShp* object, pppYmDeformationShpStep* step, _pppCtrlTable* ctrl)
{
	VYmDeformationShp* state;

	if (ppvUserStopPartF != 0) {
		return;
	}

	state = DeformationShpState(object, ctrl);

	CalcGraphValue(
		object, step->m_graphId, state->m_scale, state->m_values[0], state->m_values[1],
		step->m_deformation.m_scale.m_valueAdd, step->m_deformation.m_scale.m_velocityAdd,
		step->m_deformation.m_scale.m_accelerationAdd);
	CalcGraphValue(
		object, step->m_graphId, state->m_values[2], state->m_values[3], state->m_values[4],
		step->m_deformation.m_angle.m_valueAdd, step->m_deformation.m_angle.m_velocityAdd,
		step->m_deformation.m_angle.m_accelerationAdd);

	if (ppvIsLoopCalc != 0) {
		return;
	}

	if (state->m_direction != 0) {
		int angleStep = (int)state->m_values[2];

		state->m_angle = state->m_angle + angleStep;
		if (state->m_angle > step->m_angleLimit) {
			state->m_direction = 0;
		}
	} else {
		int angleStep = (int)state->m_values[2];

		state->m_angle = state->m_angle - angleStep;
		if ((int)state->m_angle < -(int)step->m_angleLimit) {
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
void pppConstruct2YmDeformationShp(pppYmDeformationShp* object, _pppCtrlTable* ctrl)
{
	float zero = kPppYmDeformationShpZero;
	VYmDeformationShp* state = DeformationShpState(object, ctrl);

	state->m_values[1] = zero;
	state->m_values[0] = zero;
	state->m_scale = zero;
	state->m_values[4] = zero;
	state->m_values[3] = zero;
	state->m_values[2] = zero;
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
void pppConstructYmDeformationShp(pppYmDeformationShp* object, _pppCtrlTable* ctrl)
{
	float zero = kPppYmDeformationShpZero;
	VYmDeformationShp* state = DeformationShpState(object, ctrl);

	state->m_backBuffer = 0;
	state->m_pad0 = 0;
	state->m_pad1 = 0;
	state->m_angle = 0;
	state->m_direction = 1;
	state->m_values[1] = zero;
	state->m_values[0] = zero;
	state->m_scale = zero;
	state->m_values[4] = zero;
	state->m_values[3] = zero;
	state->m_values[2] = zero;
}
