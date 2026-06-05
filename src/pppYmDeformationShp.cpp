#include "ffcc/pppYmDeformationShp.h"
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
extern "C" {
const float FLOAT_803305f0 = 0.017453292f;
const float kPppYmDeformationShpZero = 0.0f;
const float FLOAT_803305f8 = 1.0f;
}
#include "ffcc/util.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct pppYmDeformationShpGraphArgs {
    f32 m_valueAdd;
    f32 m_velocityAdd;
    f32 m_accelerationAdd;
};

struct pppYmDeformationShpUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_size;
    u8 m_pad_0x9[3];
    union {
        f32 m_payload[6];
        struct Payload {
            pppYmDeformationShpGraphArgs m_scale;
            pppYmDeformationShpGraphArgs m_angle;
        } m_deformation;
    };
    s16 m_payload3;
    s8 m_splitMode;
    u8 m_splitSize;
    u8 m_orientation;
    u8 m_pad_0x29[3];
    f32 m_drawZ;
    u8 m_pad_0x30;
    u8 m_alpha;
    u8 m_pad_0x32[0xA];
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

int RenderDeformationShape(_pppPObject*, VYmDeformationShp*, Vec*, Vec2d*);

struct _pppEnvStYmDeformationShp {
	void* m_stagePtr;
	CMaterialSet* m_materialSetPtr;
	CMapMesh** m_mapMeshPtr;
};

template <typename T>
static inline T* PppWorkArea(pppYmDeformationShp* object, _pppCtrlTable* ctrl, int index)
{
	return reinterpret_cast<T*>(object->m_workArea + ctrl->m_serializedDataOffsets[index]);
}

static inline void setVertexUV(Vec2d* uvs, float left, float top, float right, float bottom)
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

static inline void setVertexPos(Vec* vertices, s8 orientation, float left, float top, float right, float bottom)
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

/*
 * --INFO--
 * PAL Address: 0x8008eec8
 * PAL Size: 2904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkB* param_2, _pppCtrlTable* param_3)
{
	_pppPObject* object = pppYmDeformationShp_;
	VYmDeformationShp* work = (VYmDeformationShp*)(object->m_workArea + param_3->m_serializedDataOffsets[2]);
	int textureIndex = 0;
	Vec2d uvs[4];
	float indMtx[2][3];
	Mtx rotMtx;
	Vec vertices[4];
	Mtx drawMtx;

	if (param_2->m_dataValIndex != 0xFFFF) {
		YmDeformationShpColorInfo* colorInfo =
			(YmDeformationShpColorInfo*)(object->m_workArea + param_3->m_serializedDataOffsets[1]);
		_pppEnvStYmDeformationShp* env = (_pppEnvStYmDeformationShp*)ppvEnv;
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
			setVertexPos(vertices, (s8)param_2->m_orientation, -quadSize, quadSize, quadSize, -quadSize);
			setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, FLOAT_803305f8, FLOAT_803305f8);
			RenderDeformationShape(object, work, vertices, uvs);
		} else {
			short size = param_2->m_size;
			short split = param_2->m_splitSize;
			float uvSplit = (FLOAT_803305f8 / (float)(size + size)) * (float)(size - split);
			float uvRemainder;

			setVertexPos(vertices, (s8)param_2->m_orientation, -size, -split, -split, split);
			uvRemainder = FLOAT_803305f8 - uvSplit;
			setVertexUV(uvs, kPppYmDeformationShpZero, uvSplit, uvSplit, uvRemainder);
			RenderDeformationShape(object, work, vertices, uvs);

			setVertexPos(vertices, (s8)param_2->m_orientation, size, -split, split, split);
			setVertexUV(uvs, FLOAT_803305f8, uvSplit, uvRemainder, uvRemainder);
			RenderDeformationShape(object, work, vertices, uvs);

			if (param_2->m_splitMode == 1) {
				setVertexPos(vertices, (s8)param_2->m_orientation, -size, -size, size, -split);
				setVertexUV(uvs, kPppYmDeformationShpZero, kPppYmDeformationShpZero, FLOAT_803305f8, uvSplit);
				RenderDeformationShape(object, work, vertices, uvs);

				setVertexPos(vertices, (s8)param_2->m_orientation, -size, split, size, size);
				setVertexUV(uvs, kPppYmDeformationShpZero, uvRemainder, FLOAT_803305f8, FLOAT_803305f8);
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
		PSMTXMultVec(obj->m_drawMatrix.value, &localVertex, &worldPos);
		clipPos.x = worldPos.x;
		clipPos.y = worldPos.y;
		clipPos.z = worldPos.z;
		clipPos.w = one;
		Math.MTX44MultVec4(ppvScreenMatrix, &clipPos, &projected[i]);
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
	texMtx[0][0] = ppvScreenMatrix[0][0] * (320.0f / (float)width);
	texMtx[1][1] = ppvScreenMatrix[1][1] * -(224.0f / (float)height);
	texMtx[0][2] = -0.5f;
	texMtx[1][2] = -0.5f;
	texMtx[2][2] = -1.0f;

	PSMTXConcat(texMtx, obj->m_drawMatrix.value, tempMtx);
	cameraPos.z = kPppYmDeformationShpZero;
	cameraPos.y = kPppYmDeformationShpZero;
	cameraPos.x = kPppYmDeformationShpZero;
	PSMTXMultVec(tempMtx, &cameraPos, &cameraPos);
	cameraPos.x = cameraPos.x / cameraPos.z;
	cameraPos.y = cameraPos.y / cameraPos.z;
	texMtx[0][2] = -1.0f + cameraPos.x;
	texMtx[1][2] = -1.0f + cameraPos.y;
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
	} else if (640 < (left + width)) {
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
void pppFrameYmDeformationShp(pppYmDeformationShp* pppYmDeformationShp_, pppYmDeformationShpUnkB* param_2, _pppCtrlTable* param_3)
{
	VYmDeformationShp* state;

	if (ppvUserStopPartF != 0) {
		return;
	}

	state = PppWorkArea<VYmDeformationShp>(pppYmDeformationShp_, param_3, 2);

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
	const float& value = kPppYmDeformationShpZero;
	VYmDeformationShp* state = PppWorkArea<VYmDeformationShp>(pppYmDeformationShp_, param_2, 2);

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
	const float& value = kPppYmDeformationShpZero;
	VYmDeformationShp* state = PppWorkArea<VYmDeformationShp>(pppYmDeformationShp_, param_2, 2);

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
