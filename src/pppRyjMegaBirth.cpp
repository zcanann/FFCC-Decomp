#include "global.h"
#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/partMng.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppRyjMegaBirthZero;
}
#include <string.h>

static Mtx g_matUnit;

static const char s_pppRyjMegaBirth_cpp[] = "pppRyjMegaBirth.cpp";

STATIC_ASSERT(sizeof(RyjMegaBirthDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(RyjMegaBirthDataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(RyjMegaBirthDataOffsets, m_workOffset) == 0x8);

static inline RyjMegaBirthDataOffsets* GetRyjMegaBirthDataOffsets(PRyjMegaBirthOffsets* offsets)
{
	return reinterpret_cast<RyjMegaBirthDataOffsets*>(offsets->m_serializedDataOffsets);
}

static inline RyjMegaBirthDataOffsets* GetRyjMegaBirthDataOffsets(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<RyjMegaBirthDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

extern const float kPppRyjMegaBirthDegToRad;
extern const float kPppRyjMegaBirthAngleWrapDegrees = 360.0f;
extern const float kPppRyjMegaBirthHalfTurnDegrees = 180.0f;
extern const float kPppRyjMegaBirthNegativeHalfTurnDegrees = -180.0f;
extern const double kPppRyjMegaBirthS32ToDoubleBias = 4503599627370496.0;
extern const float kPppRyjMegaBirthDouble = 2.0f;
extern const float kPppRyjMegaBirthRandomSpeedScale = 0.7f;
extern const float kPppRyjMegaBirthHalf = 0.5f;
extern const double kPppRyjMegaBirthOneDouble = 1.0;
extern const double kPppRyjMegaBirthHalfDouble = 0.5;
extern const float kPppRyjMegaBirthSignFlipTable[2] = { -1.0f, 0.0f };
extern const float kPppRyjMegaBirthSharedZero = 0.0f;
extern const float kPppRyjMegaBirthModelInitialY = 30.0f;
extern const float kPppRyjMegaBirthPi = 3.1415927f;

static inline float RyjZero()
{
	return *reinterpret_cast<const float*>(&kPppRyjMegaBirthZero);
}

static inline float* f32_at(void* base, s32 off)
{
	return (float*)((u8*)base + off);
}

static inline s16* s16_at(void* base, s32 off)
{
	return (s16*)((u8*)base + off);
}

static inline u16* u16_at(void* base, s32 off)
{
	return (u16*)((u8*)base + off);
}

static inline u8* u8_at(void* base, s32 off)
{
	return (u8*)base + off;
}

static inline unsigned char clamp_u8(float value)
{
	int ivalue = (int)value;
	if (ivalue < 0) {
		return 0;
	}
	if (ivalue > 0xFF) {
		return 0xFF;
	}
	return (unsigned char)ivalue;
}

static inline signed char random_signed_byte_span(u8 span)
{
	return (signed char)((s32)((float)((u8)span * 2) * Math.RandF() - (float)((u8)span / 2)));
}

static inline void apply_signed_randomization_2(u8* particle, s32 offset, u8 flags)
{
	if (((flags & 1) != 0) && ((flags & 2) != 0)) {
		if (kPppRyjMegaBirthHalfDouble < (double)Math.RandF()) {
			float v0 = *f32_at(particle, offset);
			*f32_at(particle, offset) = v0 * kPppRyjMegaBirthSignFlipTable[0];
		}
		if (kPppRyjMegaBirthHalfDouble < (double)Math.RandF()) {
			float v4 = *f32_at(particle, offset + 4);
			*f32_at(particle, offset + 4) = v4 * kPppRyjMegaBirthSignFlipTable[0];
		}
	} else if ((flags & 2) != 0) {
		float v0 = *f32_at(particle, offset);
		*f32_at(particle, offset) = v0 * kPppRyjMegaBirthSignFlipTable[0];
		float v4 = *f32_at(particle, offset + 4);
		*f32_at(particle, offset + 4) = v4 * kPppRyjMegaBirthSignFlipTable[0];
	}
}

/*
 * --INFO--
 * PAL Address: 0x80082278
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthDes(_pppPObject* pObject, PRyjMegaBirthOffsets* offsets)
{
	VRyjMegaBirth* work =
		reinterpret_cast<VRyjMegaBirth*>(pObject->m_workArea + GetRyjMegaBirthDataOffsets(offsets)->m_workOffset);

	if (work->m_particleBlock != 0)
	{
		pppMemFree(work->m_particleBlock);
		work->m_particleBlock = 0;
	}

	if (work->m_worldMatrixBlock != 0)
	{
		pppMemFree(work->m_worldMatrixBlock);
		work->m_worldMatrixBlock = 0;
	}

	if (work->m_colorBlock != 0)
	{
		pppMemFree(work->m_colorBlock);
		work->m_colorBlock = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x800822f4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthCon(_pppPObject* pObject, PRyjMegaBirthOffsets* offsets)
{
	VRyjMegaBirth* work = (VRyjMegaBirth*)(pObject->m_workArea + GetRyjMegaBirthDataOffsets(offsets)->m_workOffset);
	float zero;

	PSMTXIdentity(work->m_worldMatrix);
	zero = kPppRyjMegaBirthZero;
	work->m_accelerationAxis.z = kPppRyjMegaBirthZero;
	work->m_accelerationAxis.y = zero;
	work->m_accelerationAxis.x = zero;
	work->m_particleBlock = 0;
	work->m_worldMatrixBlock = 0;
	work->m_colorBlock = 0;
	work->m_numParticles = 0;
	work->m_emitTimer = 0;
	work->m_meshEmitIndex = 0;
	work->m_emitTimer = 10000;

	PSMTXIdentity(g_matUnit);
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static inline void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirth* params, VRyjMegaBirth* work)
{
	u8 mode = params->m_spawnMode;

	if ((mode == 1) || (mode == 3) || (mode == 5) || (mode == 7) || (mode == 9)) {
		PSMTXIdentity(out.value);
		out.value[0][0] = ppvMng->m_scale.x;
		out.value[1][1] = ppvMng->m_scale.y;
		out.value[2][2] = ppvMng->m_scale.z;
		out.value[0][3] = ppvMng->m_position.x;
		out.value[1][3] = ppvMng->m_position.y;
		out.value[2][3] = ppvMng->m_position.z;
	} else {
		PSMTXCopy(ppvMng->m_matrix.value, out.value);
	}

	if (work != NULL) {
		PSMTXCopy(out.value, work->m_worldMatrix);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static inline void set_matrix(
	_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirth* params, VRyjMegaBirth* work, _PARTICLE_DATA* particle,
	_PARTICLE_WMAT* particleWorldMat)
{
	pppFMATRIX local;
	pppFMATRIX world;
	Mtx scale;

	pppUnitMatrix(local);
	local.value[0][3] = *f32_at(particle, 0x0);
	local.value[1][3] = *f32_at(particle, 0x4);
	local.value[2][3] = *f32_at(particle, 0x8);

	PSMTXScale(scale, particle->m_sizeStart, particle->m_sizeEnd, particle->m_sizeVal);
	PSMTXConcat(local.value, scale, local.value);

	if (particleWorldMat != NULL) {
		PSMTXCopy(*(Mtx*)particleWorldMat, world.value);
	} else {
		init_matrix(pObject, world, params, work);
	}

	PSMTXConcat(world.value, local.value, world.value);
	PSMTXConcat(ppvCameraMatrix0, world.value, out.value);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRyjDrawMegaBirth(_pppPObject* obj, PRyjMegaBirth* stepData, _pppCtrlTable* ctrlTable)
{
	PRyjMegaBirth* params = (PRyjMegaBirth*)stepData;
	u8* payload = (u8*)params;
	RyjMegaBirthDataOffsets* offsets = GetRyjMegaBirthDataOffsets(ctrlTable);
	VRyjMegaBirth* work = (VRyjMegaBirth*)(obj->m_workArea + offsets->m_workOffset);
	tagOAN3_SHAPE* drawShape;
	VColor* baseColor = (VColor*)(obj->m_workArea + offsets->m_colorOffset);
	_PARTICLE_DATA* particleBlock = work->m_particleBlock;
	_PARTICLE_WMAT* particleWorldMatBlock = work->m_worldMatrixBlock;
	_PARTICLE_COLOR* colorBlock = work->m_colorBlock;
	_PARTICLE_DATA* particle = particleBlock;
	_PARTICLE_WMAT* particleWorldMat = particleWorldMatBlock;
	_PARTICLE_COLOR* colorData = colorBlock;
	s32 numParticles = work->m_numParticles;
	s8 hasRequiredMemory;
	pppFMATRIX baseViewMatrix;

	if (particleBlock == NULL) {
		hasRequiredMemory = 0;
	} else if (((params->m_matrixMode == 1) || (params->m_matrixMode == 2)) && (particleWorldMatBlock == NULL)) {
		hasRequiredMemory = 0;
	} else if ((params->m_enableParticleColor != 0) && (colorBlock == NULL)) {
		hasRequiredMemory = 0;
	} else {
		hasRequiredMemory = 1;
	}

	if (!hasRequiredMemory) {
		return;
	}

	if (params->m_shapeIndex == 0xFFFF) {
		return;
	}

	switch (params->m_matrixMode) {
	case 0:
		PSMTXConcat(work->m_worldMatrix, obj->m_localMatrix.value, baseViewMatrix.value);
		PSMTXConcat(ppvCameraMatrix, baseViewMatrix.value, baseViewMatrix.value);
		break;
	case 1:
		break;
	case 2:
		break;
	}

	pppShapeSt* shape = ppvEnv->m_shapeTablePtr[params->m_shapeIndex];
	u8 useTexture;
	if (params->m_textureMode != 0) {
		useTexture = 0;
	} else {
		useTexture = 1;
	}
	float drawScale = params->m_drawDepthEnabled != 0 ? params->m_drawDepth : kPppRyjMegaBirthZero;

	pppSetDrawEnv(
		(pppCVECTOR*)0, (pppFMATRIX*)0, drawScale, params->m_lightTarget, params->m_fogIndex, params->m_blendMode, 0, useTexture, 1,
		0);

	long* animData = static_cast<long*>(shape->m_animData);
	int baseRed = baseColor->m_color.rgba[0];
	int baseGreen = baseColor->m_color.rgba[1];
	int baseBlue = baseColor->m_color.rgba[2];
	int baseAlpha = baseColor->m_color.rgba[3];

	for (int i = 0; i < numParticles; i++) {
		if (*u16_at(particle, 0x22) != 0) {
			Mtx rotMatrix;
			pppFMATRIX viewMatrix;
			Mtx drawMatrix;
			Vec viewPos2;
			Vec viewPos1;
			Vec viewPos0;
			Vec drawPos;
			pppCVECTOR drawColor;
			int red;
			int green;
			int blue;
			int alpha;

			PSMTXIdentity(drawMatrix);
			drawMatrix[0][0] = ((float*)particle)[13] * ppvMng->m_scale.x;
			drawMatrix[1][1] = ((float*)particle)[14] * ppvMng->m_scale.y;
			drawMatrix[2][2] = drawMatrix[0][0];

			if (*f32_at(particle, 0x28) != kPppRyjMegaBirthZero) {
				PSMTXRotRad(rotMatrix, 'Z', kPppRyjMegaBirthDegToRad * *f32_at(particle, 0x28));
				PSMTXConcat(drawMatrix, rotMatrix, drawMatrix);
			}

			{
				drawPos.x = drawMatrix[0][3];
				drawPos.y = drawMatrix[1][3];
				drawPos.z = drawMatrix[2][3];
				PSVECAdd(&drawPos, (Vec*)particle, &drawPos);
				drawMatrix[0][3] = drawPos.x;
				drawMatrix[1][3] = drawPos.y;
				drawMatrix[2][3] = drawPos.z;
			}

			switch (params->m_matrixMode) {
			case 0: {

				viewPos0.x = drawMatrix[0][3];
				viewPos0.y = drawMatrix[1][3];
				viewPos0.z = drawMatrix[2][3];
				PSMTXMultVec(baseViewMatrix.value, &viewPos0, &viewPos0);
				drawMatrix[0][3] = viewPos0.x;
				drawMatrix[1][3] = viewPos0.y;
				drawMatrix[2][3] = viewPos0.z;
				break;
			}
			case 1: {

				PSMTXConcat(*(Mtx*)particleWorldMat, obj->m_localMatrix.value, viewMatrix.value);
				PSMTXConcat(ppvCameraMatrix, viewMatrix.value, viewMatrix.value);
				viewPos1.x = drawMatrix[0][3];
				viewPos1.y = drawMatrix[1][3];
				viewPos1.z = drawMatrix[2][3];
				PSMTXMultVec(viewMatrix.value, &viewPos1, &viewPos1);
				drawMatrix[0][3] = viewPos1.x;
				drawMatrix[1][3] = viewPos1.y;
				drawMatrix[2][3] = viewPos1.z;
				break;
			}
			case 2: {

				PSMTXConcat(work->m_worldMatrix, *(Mtx*)particleWorldMat, viewMatrix.value);
				PSMTXConcat(ppvCameraMatrix, viewMatrix.value, viewMatrix.value);
				viewPos2.x = drawMatrix[0][3];
				viewPos2.y = drawMatrix[1][3];
				viewPos2.z = drawMatrix[2][3];
				PSMTXMultVec(viewMatrix.value, &viewPos2, &viewPos2);
				drawMatrix[0][3] = viewPos2.x;
				drawMatrix[1][3] = viewPos2.y;
				drawMatrix[2][3] = viewPos2.z;
				break;
			}
			default:
				break;
			}

			GXLoadPosMtxImm(drawMatrix, 0);

			u16 frame = *u16_at(particle, 0x20);
			pppShapeAnimData* shapeAnim = reinterpret_cast<pppShapeAnimData*>(animData);
			drawShape = (tagOAN3_SHAPE*)((u8*)shapeAnim + shapeAnim->m_frames[frame].m_shapeOffset);

			red = baseRed + (int)*(s8*)((u8*)particle + 0x24);
			green = baseGreen + (int)*(s8*)((u8*)particle + 0x25);
			blue = baseBlue + (int)*(s8*)((u8*)particle + 0x26);
			alpha = (int)((float)baseAlpha + (float)(int)*(s8*)((u8*)particle + 0x27) - *f32_at(particle, 0x54));

			if (colorData != NULL) {
				red += (int)colorData->m_color[0];
				green += (int)colorData->m_color[1];
				blue += (int)colorData->m_color[2];
				alpha += (int)colorData->m_color[3];
			}

			if (red < 0) {
				red = 0;
			} else if (red > 0xFF) {
				red = 0xFF;
			}
			if (green < 0) {
				green = 0;
			} else if (green > 0xFF) {
				green = 0xFF;
			}
			if (blue < 0) {
				blue = 0;
			} else if (blue > 0xFF) {
				blue = 0xFF;
			}
			if (alpha < 0) {
				alpha = 0;
			} else if (alpha > 0x7F) {
				alpha = 0x7F;
			}
			drawColor.rgba[0] = red;
			drawColor.rgba[1] = green;
			drawColor.rgba[2] = blue;
			drawColor.rgba[3] = alpha;

			GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)drawColor.rgba);
			pppSetBlendMode(params->m_blendMode);
			pppDrawShp(drawShape, ppvEnv->m_materialSetPtr, params->m_blendMode);
		}

		if (particleWorldMat != NULL) {
			particleWorldMat = particleWorldMat + 1;
		}
		if (colorData != NULL) {
			colorData = colorData + 1;
		}
		particle = (_PARTICLE_DATA*)((u8*)particle + 0x60);
	}
}


/*
 * --INFO--
 * PAL Address: 0x80082894
 * PAL Size: 636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirth(_pppPObject* pObject, PRyjMegaBirth* particleData, PRyjMegaBirthOffsets* offsets)
{
	s8 hasRequiredMemory;
	RyjMegaBirthDataOffsets* serializedDataOffsets;
	s32 workOffset;
	s32 colorOffset;
	VRyjMegaBirth* work;
	VColor* color;

	serializedDataOffsets = GetRyjMegaBirthDataOffsets(offsets);
	workOffset = serializedDataOffsets->m_workOffset;
	colorOffset = serializedDataOffsets->m_colorOffset;
	work = reinterpret_cast<VRyjMegaBirth*>(pObject->m_workArea + workOffset);
	color = reinterpret_cast<VColor*>(pObject->m_workArea + colorOffset);

	if (work->m_particleBlock == NULL)
	{
		work->m_numParticles = particleData->m_maxParticles;
		work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc(
			work->m_numParticles * 0x60, ppvEnv->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp), 0x262);
		if (work->m_particleBlock != NULL)
		{
			memset(work->m_particleBlock, 0, work->m_numParticles * 0x60);
		}

		if ((particleData->m_matrixMode == 1) || (particleData->m_matrixMode == 2))
		{
			work->m_worldMatrixBlock = (_PARTICLE_WMAT*)pppMemAlloc(
				work->m_numParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp), 0x269);
			if (work->m_worldMatrixBlock != NULL)
			{
				memset(work->m_worldMatrixBlock, 0, work->m_numParticles * sizeof(_PARTICLE_WMAT));
			}
		}

		if (particleData->m_enableParticleColor != 0)
		{
			work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc(
				work->m_numParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp), 0x271);
			if (work->m_colorBlock != NULL)
			{
				memset(work->m_colorBlock, 0, work->m_numParticles * sizeof(_PARTICLE_COLOR));
			}
		}

		work->m_accelerationAxis.x = particleData->m_accelerationAxis.x;
		work->m_accelerationAxis.y = particleData->m_accelerationAxis.y;
		work->m_accelerationAxis.z = particleData->m_accelerationAxis.z;
		PSVECNormalize(&work->m_accelerationAxis, &work->m_accelerationAxis);
	}

	if (work->m_particleBlock == NULL)
	{
		hasRequiredMemory = 0;
	}
	else if (((particleData->m_matrixMode == 1) || (particleData->m_matrixMode == 2)) &&
	         (work->m_worldMatrixBlock == NULL))
	{
		hasRequiredMemory = 0;
	}
	else if ((particleData->m_enableParticleColor != 0) && (work->m_colorBlock == NULL))
	{
		hasRequiredMemory = 0;
	}
	else
	{
		hasRequiredMemory = 1;
	}

	if (hasRequiredMemory)
	{
		switch (particleData->m_spawnMode)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
			PSMTXIdentity(work->m_worldMatrix);
			work->m_worldMatrix[0][0] = ppvMng->m_scale.x;
			work->m_worldMatrix[1][1] = ppvMng->m_scale.y;
			work->m_worldMatrix[2][2] = ppvMng->m_scale.z;
			work->m_worldMatrix[0][3] = ppvMng->m_position.x;
			work->m_worldMatrix[1][3] = ppvMng->m_position.y;
			work->m_worldMatrix[2][3] = ppvMng->m_position.z;
			break;
		default:
			PSMTXCopy(ppvMng->m_matrix.value, work->m_worldMatrix);
			break;
		}

		calc_particle(pObject, work, particleData, color);
	}
}


/*
 * --INFO--
 * PAL Address: 0x80082b10
 * PAL Size: 440b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc_particle(_pppPObject* pObject, VRyjMegaBirth* work, PRyjMegaBirth* param, VColor* color)
{
	s16 duration;
	u16 frame;
	pppShapeAnimData* shapeAnim;
	pppShapeAnimFrame* frameData;
	_PARTICLE_DATA* particle;
	_PARTICLE_WMAT* worldMats;
	_PARTICLE_COLOR* colorData;
	s32 maxParticles;
	s32 emitCount;
	s32 i;

	emitCount = 0;
	particle = (_PARTICLE_DATA*)work->m_particleBlock;
	worldMats = work->m_worldMatrixBlock;
	colorData = work->m_colorBlock;
	maxParticles = work->m_numParticles;

	if ((ppvUserStopPartF == 0) && (param->m_shapeIndex != 0xFFFF))
	{
		work->m_emitTimer = work->m_emitTimer + 1;

		for (i = 0; i < maxParticles; i = i + 1)
		{
			if (*(u16*)((u8*)particle + 0x22) != 0)
			{
				calc(work, param, particle, color, colorData);

				frame = *(u16*)((u8*)particle + 0x1E);
				shapeAnim =
					static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[param->m_shapeIndex]->m_animData);
				*(u16*)((u8*)particle + 0x20) = frame;
				frameData = &shapeAnim->m_frames[frame];

				*(u16*)((u8*)particle + 0x1C) = *(u16*)((u8*)particle + 0x1C) + param->m_frameStep;
				frame = *(u16*)((u8*)particle + 0x1C);
				duration = frameData->m_duration;

				if ((s32)frame >= (s32)duration)
				{
					*(u16*)((u8*)particle + 0x1C) = frame - duration;
					*(u16*)((u8*)particle + 0x1E) = *(u16*)((u8*)particle + 0x1E) + 1;

					if ((s32)*(u16*)((u8*)particle + 0x1E) >= (s32)shapeAnim->m_frameCount)
					{
						if ((frameData->m_flags & 0x80) != 0)
						{
							*(u16*)((u8*)particle + 0x1E) = 0;
							*(u16*)((u8*)particle + 0x1C) = 0;
						}
						else
						{
							*(u16*)((u8*)particle + 0x1C) = 0;
							*(u16*)((u8*)particle + 0x1E) = *(u16*)((u8*)particle + 0x1E) - 1;
						}
					}
				}
			}
			else if ((param->m_emitInterval <= work->m_emitTimer) &&
			         (emitCount < (s32)param->m_emitCount))
			{
				birth(pObject, work, param, color, particle, worldMats, colorData);
				emitCount = emitCount + 1;
			}

			if (worldMats != 0)
			{
				worldMats = worldMats + 1;
			}

			if (colorData != 0)
			{
				colorData = colorData + 1;
			}

			particle = (_PARTICLE_DATA*)((u8*)particle + 0x60);
		}

		if (emitCount > 0)
		{
			work->m_emitTimer = 0;
		}
	}
}


/*
 * --INFO--
 * PAL Address: 0x80082cc8
 * PAL Size: 936b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(
	VRyjMegaBirth* work, PRyjMegaBirth* param, _PARTICLE_DATA* particle, VColor* vColor,
	_PARTICLE_COLOR* colorData)
{
	int alpha;
	u8* paramPayload;
	u8* particlePayload;
	u32 frameCount;
	Vec step;

	alpha = vColor->m_color.rgba[3];
	paramPayload = (u8*)param;
	particlePayload = (u8*)particle;

	if (colorData != NULL)
	{
		colorData->m_color[0] = colorData->m_color[0] + colorData->m_colorFrameDeltas[0];
		colorData->m_color[1] = colorData->m_color[1] + colorData->m_colorFrameDeltas[1];
		colorData->m_color[2] = colorData->m_color[2] + colorData->m_colorFrameDeltas[2];
		colorData->m_color[3] = colorData->m_color[3] + colorData->m_colorFrameDeltas[3];
		colorData->m_colorFrameDeltas[0] = colorData->m_colorFrameDeltas[0] + *f32_at(paramPayload, 0x3C);
		colorData->m_colorFrameDeltas[1] = colorData->m_colorFrameDeltas[1] + *f32_at(paramPayload, 0x40);
		colorData->m_colorFrameDeltas[2] = colorData->m_colorFrameDeltas[2] + *f32_at(paramPayload, 0x44);
		colorData->m_colorFrameDeltas[3] = colorData->m_colorFrameDeltas[3] + *f32_at(paramPayload, 0x48);
		alpha = (int)vColor->m_color.rgba[3] + (int)colorData->m_color[3];
		if (alpha > 0xFF)
		{
			alpha = 0xFF;
		}
	}

	*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + *f32_at(particlePayload, 0x2C);
	if ((paramPayload[0xEB] & 0x10) != 0)
	{
		*f32_at(particlePayload, 0x2C) =
			*f32_at(particlePayload, 0x2C) + (*f32_at(paramPayload, 0x98) + *f32_at(particlePayload, 0x30));
	}
	else
	{
		*f32_at(particlePayload, 0x2C) = *f32_at(particlePayload, 0x2C) + *f32_at(paramPayload, 0x98);
	}

	{
		const float& angleWrap = kPppRyjMegaBirthAngleWrapDegrees;
		const float& angleMax = kPppRyjMegaBirthHalfTurnDegrees;
		volatile float* angle = f32_at(particlePayload, 0x28);
		while (angleMax <= *angle)
		{
			*angle = *angle - angleWrap;
		}
	}
	{
		const float& angleWrap = kPppRyjMegaBirthAngleWrapDegrees;
		const float& angleMin = kPppRyjMegaBirthNegativeHalfTurnDegrees;
		volatile float* angle = f32_at(particlePayload, 0x28);
		while (*angle < angleMin)
		{
			*angle = *angle + angleWrap;
		}
	}

	*f32_at(particlePayload, 0x34) = *f32_at(particlePayload, 0x34) + *f32_at(particlePayload, 0x3C);
	*f32_at(particlePayload, 0x38) = *f32_at(particlePayload, 0x38) + *f32_at(particlePayload, 0x40);
	if ((paramPayload[0xEA] & 0x10) != 0)
	{
		*f32_at(particlePayload, 0x3C) =
			*f32_at(particlePayload, 0x3C) + (*f32_at(paramPayload, 0x70) + *f32_at(particlePayload, 0x44));
		*f32_at(particlePayload, 0x40) =
			*f32_at(particlePayload, 0x40) + (*f32_at(paramPayload, 0x74) + *f32_at(particlePayload, 0x48));
	}
	else
	{
		*f32_at(particlePayload, 0x3C) = *f32_at(particlePayload, 0x3C) + *f32_at(paramPayload, 0x70);
		*f32_at(particlePayload, 0x40) = *f32_at(particlePayload, 0x40) + *f32_at(paramPayload, 0x74);
	}

	*f32_at(particlePayload, 0x4C) = *f32_at(particlePayload, 0x4C) + *f32_at(paramPayload, 0xC4);
	if (paramPayload[0xEE] == 0)
	{
		if ((kPppRyjMegaBirthZero < *f32_at(paramPayload, 0xC0)) &&
		    (*f32_at(paramPayload, 0xC4) < kPppRyjMegaBirthZero))
		{
			if (*f32_at(particlePayload, 0x4C) < kPppRyjMegaBirthZero)
			{
				*f32_at(particlePayload, 0x4C) = kPppRyjMegaBirthZero;
			}
		}
		else
		{
			float zero = RyjZero();
			if ((*f32_at(paramPayload, 0xC0) < zero) &&
			    (zero < *f32_at(paramPayload, 0xC4)) &&
			    (zero < *f32_at(particlePayload, 0x4C)))
			{
				*f32_at(particlePayload, 0x4C) = zero;
			}
		}
	}

	*f32_at(particlePayload, 0x50) = *f32_at(particlePayload, 0x50) + *f32_at(paramPayload, 0xD0);
	PSVECScale((Vec*)(particlePayload + 0x10), &step, *f32_at(particlePayload, 0x4C));
	PSVECAdd(&step, (Vec*)particlePayload, (Vec*)particlePayload);
	PSVECScale(&work->m_accelerationAxis, &step, *f32_at(particlePayload, 0x50));
	PSVECAdd((Vec*)particlePayload, &step, (Vec*)particlePayload);

	if (*u16_at(paramPayload, 0x26) != 0)
	{
		*u16_at(particlePayload, 0x22) = *u16_at(particlePayload, 0x22) - 1;
	}

	*u8_at(particlePayload, 0x58) = *u8_at(particlePayload, 0x58) + 1;
	frameCount = *u8_at(particlePayload, 0x59);
	if ((frameCount != 0) && ((u32)*u8_at(particlePayload, 0x58) <= frameCount))
	{
		*f32_at(particlePayload, 0x54) = *f32_at(particlePayload, 0x54) - (float)alpha / (float)frameCount;
	}

	frameCount = *u8_at(particlePayload, 0x5A);
	if ((frameCount != 0) && ((int)*u16_at(particlePayload, 0x22) <= (int)frameCount))
	{
		float fadeAlpha = (float)alpha;
		float fadeFrameCount = (float)(unsigned int)paramPayload[0x29];
		float particleAlpha = *f32_at(particlePayload, 0x54);

		*f32_at(particlePayload, 0x54) = particleAlpha + fadeAlpha / fadeFrameCount;
	}
}


/*
 * --INFO--
 * PAL Address: 0x80083070
 * PAL Size: 4468b
 * EN Address: 0x80082A0C
 * EN Size: 4468b
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(
    _pppPObject* pObject, VRyjMegaBirth* work, PRyjMegaBirth* param, VColor* color, _PARTICLE_DATA* particle,
    _PARTICLE_WMAT* worldMat, _PARTICLE_COLOR* colorData)
{
	u8* payload;
	u8* particlePayload;
	u16 life;
	float vx;
	float vy;
	float vz;

	payload = (u8*)param;
	float spread = (float)param->m_spread;
	float spreadRange = kPppRyjMegaBirthDouble * spread;

	memset(particle, 0, 0x60);
	if (worldMat != NULL) {
		memset(worldMat, 0, sizeof(_PARTICLE_WMAT));
	}
	if (colorData != NULL) {
		memset(colorData, 0, sizeof(_PARTICLE_COLOR));
	}
	particlePayload = (u8*)particle;

	switch (param->m_spawnMode) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7: {
		Vec baseDir;
		pppIVECTOR4 angles;
		pppFMATRIX rot;

		baseDir.x = param->m_baseDirection.x;
		baseDir.y = param->m_baseDirection.y;
		baseDir.z = param->m_baseDirection.z;
		angles.x = (s32)(spreadRange * Math.RandF() - spread);
		angles.x = (s32)((float)(angles.x << 15) / kPppRyjMegaBirthHalfTurnDegrees);
		angles.y = (s32)(spreadRange * Math.RandF() - spread);
		angles.y = (s32)((float)(angles.y << 15) / kPppRyjMegaBirthHalfTurnDegrees);
		angles.z = (s32)(spreadRange * Math.RandF() - spread);
		angles.z = (s32)((float)(angles.z << 15) / kPppRyjMegaBirthHalfTurnDegrees);
		if ((param->m_spawnMode == 2) || (param->m_spawnMode == 3)) {
			angles.x = 0;
			angles.y = 0;
		}

		pppGetRotMatrixXYZ(rot, &angles);
		PSMTXMultVecSR(rot.value, &baseDir, reinterpret_cast<Vec*>(particle->m_matrix[1]));
		reinterpret_cast<Vec*>(particle->m_matrix[1])->x *= param->m_directionScale.x;
		reinterpret_cast<Vec*>(particle->m_matrix[1])->y *= param->m_directionScale.y;
		reinterpret_cast<Vec*>(particle->m_matrix[1])->z *= param->m_directionScale.z;
		PSVECNormalize(reinterpret_cast<Vec*>(particle->m_matrix[1]), reinterpret_cast<Vec*>(particle->m_matrix[1]));
		break;
	}
	}

	switch (param->m_spawnMode) {
	default:
	{
		if (kPppRyjMegaBirthZero != param->m_directionSpeed) {
			float scale = param->m_directionSpeed;

			switch (param->m_randomMode) {
			case 1:
				Math.RandF();
				scale = param->m_directionSpeed * Math.RandF();
				break;
			case 2:
			{
				float rand1 = Math.RandF();
				scale = (param->m_directionSpeed * Math.RandF()) * rand1;
				break;
			}
			case 3:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				scale = param->m_directionSpeed - kPppRyjMegaBirthRandomSpeedScale * ((param->m_directionSpeed * rand2) * rand1);
				break;
			}
			case 4:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				float rand3 = Math.RandF();
				scale = Math.RandF() * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
				break;
			}
			case 5:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				float rand3 = Math.RandF();
				scale = param->m_directionSpeed - kPppRyjMegaBirthHalf * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
				break;
			}
			}

			PSVECScale(reinterpret_cast<Vec*>(particle->m_matrix[1]), reinterpret_cast<Vec*>(particle->m_matrix[0]), scale);
		}
		break;
	}

	case 4:
	case 5:
	{
		if (kPppRyjMegaBirthZero == param->m_directionSpeed) {
			break;
		}
		float speedRandHalf = kPppRyjMegaBirthHalf * param->m_directionSpeed;

		{
		float rand1;
		float rand2;
		float rand3;
		switch (param->m_randomMode) {
		default:
			particle->m_matrix[0][0] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][0] -= speedRandHalf;
			particle->m_matrix[0][1] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][1] -= speedRandHalf;
			particle->m_matrix[0][2] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		case 1:
			Math.RandF();
			particle->m_matrix[0][0] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][0] -= speedRandHalf;
			particle->m_matrix[0][1] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][1] -= speedRandHalf;
			particle->m_matrix[0][2] = param->m_directionSpeed * Math.RandF();
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		case 2:
			rand1 = Math.RandF();
			particle->m_matrix[0][0] = (param->m_directionSpeed * Math.RandF()) * rand1;
			particle->m_matrix[0][0] -= speedRandHalf;
			rand1 = Math.RandF();
			particle->m_matrix[0][1] = (param->m_directionSpeed * Math.RandF()) * rand1;
			particle->m_matrix[0][1] -= speedRandHalf;
			rand1 = Math.RandF();
			particle->m_matrix[0][2] = (param->m_directionSpeed * Math.RandF()) * rand1;
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		case 3:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			particle->m_matrix[0][0] = param->m_directionSpeed - kPppRyjMegaBirthRandomSpeedScale * ((param->m_directionSpeed * rand2) * rand1);
			particle->m_matrix[0][0] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			particle->m_matrix[0][1] = param->m_directionSpeed - kPppRyjMegaBirthRandomSpeedScale * ((param->m_directionSpeed * rand2) * rand1);
			particle->m_matrix[0][1] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			particle->m_matrix[0][2] = param->m_directionSpeed - kPppRyjMegaBirthRandomSpeedScale * ((param->m_directionSpeed * rand2) * rand1);
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		case 4:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][0] = Math.RandF() * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][0] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][1] = Math.RandF() * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][1] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][2] = Math.RandF() * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		case 5:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][0] = param->m_directionSpeed - kPppRyjMegaBirthHalf * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][0] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][1] = param->m_directionSpeed - kPppRyjMegaBirthHalf * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][1] -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			particle->m_matrix[0][2] = param->m_directionSpeed - kPppRyjMegaBirthHalf * (rand3 * ((param->m_directionSpeed * rand2) * rand1));
			particle->m_matrix[0][2] -= speedRandHalf;
			break;
		}
		}

		particle->m_matrix[0][0] *= param->m_directionScale.x;
		particle->m_matrix[0][1] *= param->m_directionScale.y;
		particle->m_matrix[0][2] *= param->m_directionScale.z;
		break;
	}

	case 6:
	case 7:
	case 8:
	case 9:
	{
		Vec* pathBase = pObject->m_drawMatrixPtr;

		if (param->m_pathIndex >= 0) {
			pppShapeGroupRaw* pathInfo = &ppvEnv->m_shapeGroupPtr[param->m_pathIndex];

			if (pathBase == 0) {
				pathBase = ppvEnv->m_mapMeshPtr[pathInfo->m_meshIndex]->m_vertices;
			}

			{
				float sampleT;

				switch (param->m_randomMode) {
				default:
					if ((int)work->m_meshEmitIndex >= pathInfo->m_vertexCount) {
						work->m_meshEmitIndex = 0;
					}

					if (pathBase != 0) {
						u16 sampleIndex = work->m_meshEmitIndex;
						u16* indices = pathInfo->m_vertexIndices;
						work->m_meshEmitIndex = sampleIndex + 1;

						Vec* pathVec = &pathBase[indices[sampleIndex]];
						vx = pathVec->x;
						vy = pathVec->y;
						vz = pathVec->z;
					}
					goto path_store;
				case 1:
					Math.RandF();
					sampleT = Math.RandF();
					break;
				case 2:
				{
					float r0 = Math.RandF();
					float r1 = Math.RandF();
					float r2 = Math.RandF();
					sampleT = r2 * (r1 * r0);
					break;
				}
				case 3:
				{
					float r0 = Math.RandF();
					float r1 = Math.RandF();
					float r2 = Math.RandF();
					sampleT = static_cast<float>(kPppRyjMegaBirthOneDouble - (r2 * (r1 * r0)));
					break;
				}
				case 4:
				{
					float r0 = Math.RandF();
					float r1 = Math.RandF();
					float r2 = Math.RandF();
					float r3 = Math.RandF();
					sampleT = r3 * (r2 * (r1 * r0));
					break;
				}
				case 5:
				{
					float r0 = Math.RandF();
					float r1 = Math.RandF();
					float r2 = Math.RandF();
					float r3 = Math.RandF();
					float r4 = Math.RandF();
					sampleT = static_cast<float>(kPppRyjMegaBirthOneDouble - (r4 * (r3 * (r2 * (r1 * r0)))));
					break;
				}
				}

				if ((int)work->m_meshEmitIndex >= pathInfo->m_vertexCount) {
					work->m_meshEmitIndex = 0;
				}

				if (pathBase != 0) {
					int sampleIndex = (int)(sampleT * (float)pathInfo->m_vertexCount);
					Vec* pathVec = &pathBase[pathInfo->m_vertexIndices[sampleIndex]];
					vx = pathVec->x;
					vy = pathVec->y;
					vz = pathVec->z;
				}
				path_store:

				particle->m_matrix[0][0] = vx * param->m_directionScale.x;
				particle->m_matrix[0][1] = vy * param->m_directionScale.y;
				particle->m_matrix[0][2] = vz * param->m_directionScale.z;

				if ((param->m_spawnMode == 8) || (param->m_spawnMode == 9)) {
					PSVECNormalize(reinterpret_cast<Vec*>(particle->m_matrix[0]), reinterpret_cast<Vec*>(particle->m_matrix[1]));
				}
			}
		}
		break;
	}

	}



	*u8_at(particlePayload, 0x24) = random_signed_byte_span(payload[0x4C]);
	*u8_at(particlePayload, 0x25) = random_signed_byte_span(payload[0x4D]);
	*u8_at(particlePayload, 0x26) = random_signed_byte_span(payload[0x4E]);
	*u8_at(particlePayload, 0x27) = random_signed_byte_span(payload[0x4F]);

	if (payload[0x28] != 0) {
		*f32_at(particlePayload, 0x54) = (float)color->m_color.rgba[3];
		*u8_at(particlePayload, 0x59) = payload[0x28];
	}
	if (payload[0x29] != 0) {
		*u8_at(particlePayload, 0x5A) = payload[0x29];
	}

	*f32_at(particlePayload, 0x28) = *f32_at(payload, 0x90);
	*f32_at(particlePayload, 0x2C) = *f32_at(payload, 0x94);

	if (payload[0xEB] != 0) {
		*f32_at(particlePayload, 0x30) = *f32_at(payload, 0x9C) * Math.RandF();
		u8 tailFlags = payload[0xEB];
		if (((tailFlags & 1) != 0) && ((tailFlags & 2) != 0)) {
			if (kPppRyjMegaBirthHalfDouble < (double)Math.RandF()) {
				float v30 = *f32_at(particlePayload, 0x30);
				*f32_at(particlePayload, 0x30) = v30 * kPppRyjMegaBirthSignFlipTable[0];
			}
		} else if ((tailFlags & 2) != 0) {
			float v30 = *f32_at(particlePayload, 0x30);
			*f32_at(particlePayload, 0x30) = v30 * kPppRyjMegaBirthSignFlipTable[0];
		}
	}
	if ((payload[0xEB] & 4) != 0) {
		*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + *f32_at(particlePayload, 0x30);
	}
	if ((payload[0xEB] & 8) != 0) {
		*f32_at(particlePayload, 0x2C) = *f32_at(particlePayload, 0x2C) + *f32_at(particlePayload, 0x30);
	}
	{
		const float& angleWrap = kPppRyjMegaBirthAngleWrapDegrees;
		const float& angleMax = kPppRyjMegaBirthHalfTurnDegrees;
		while (angleMax <= *f32_at(particlePayload, 0x28)) {
			*f32_at(particlePayload, 0x28) -= angleWrap;
		}
	}
	{
		const float& angleWrap = kPppRyjMegaBirthAngleWrapDegrees;
		const float& angleMin = kPppRyjMegaBirthNegativeHalfTurnDegrees;
		while (*f32_at(particlePayload, 0x28) < angleMin) {
			*f32_at(particlePayload, 0x28) += angleWrap;
		}
	}

	*f32_at(particlePayload, 0x34) = *f32_at(payload, 0x50);
	*f32_at(particlePayload, 0x38) = *f32_at(payload, 0x54);
	*f32_at(particlePayload, 0x3C) = *f32_at(payload, 0x60);
	*f32_at(particlePayload, 0x40) = *f32_at(payload, 0x64);

	if (payload[0xEA] != 0) {
		if ((payload[0xEA] & 0x20) != 0) {
			float randomRotation = *f32_at(payload, 0x80) * Math.RandF();
			*f32_at(particlePayload, 0x48) = randomRotation;
			*f32_at(particlePayload, 0x44) = randomRotation;
			u8 rotFlags = payload[0xEA];
			if (((rotFlags & 1) != 0) && ((rotFlags & 2) != 0)) {
				if (kPppRyjMegaBirthHalfDouble < (double)Math.RandF()) {
					float v44 = *f32_at(particlePayload, 0x44);
					*f32_at(particlePayload, 0x44) = v44 * kPppRyjMegaBirthSignFlipTable[0];
					float v48 = *f32_at(particlePayload, 0x48);
					*f32_at(particlePayload, 0x48) = v48 * kPppRyjMegaBirthSignFlipTable[0];
				}
			} else if ((rotFlags & 2) != 0) {
				float v44 = *f32_at(particlePayload, 0x44);
				*f32_at(particlePayload, 0x44) = v44 * kPppRyjMegaBirthSignFlipTable[0];
				float v48 = *f32_at(particlePayload, 0x48);
				*f32_at(particlePayload, 0x48) = v48 * kPppRyjMegaBirthSignFlipTable[0];
			}
		} else {
			*f32_at(particlePayload, 0x44) = *f32_at(payload, 0x80) * Math.RandF();
			*f32_at(particlePayload, 0x48) = *f32_at(payload, 0x84) * Math.RandF();
			apply_signed_randomization_2(particlePayload, 0x44, payload[0xEA]);
		}
	}
	if ((payload[0xEA] & 4) != 0) {
		*f32_at(particlePayload, 0x34) = *f32_at(particlePayload, 0x34) + *f32_at(particlePayload, 0x44);
		*f32_at(particlePayload, 0x38) = *f32_at(particlePayload, 0x38) + *f32_at(particlePayload, 0x48);
	}
	if ((payload[0xEA] & 8) != 0) {
		*f32_at(particlePayload, 0x3C) = *f32_at(particlePayload, 0x3C) + *f32_at(particlePayload, 0x44);
		*f32_at(particlePayload, 0x40) = *f32_at(particlePayload, 0x40) + *f32_at(particlePayload, 0x48);
	}

	*f32_at(particlePayload, 0x4C) = param->m_velocity;
	*f32_at(particlePayload, 0x50) = param->m_acceleration;
	if (kPppRyjMegaBirthZero != param->m_velocityRandom) {
		float rand1 = Math.RandF();
		*f32_at(particlePayload, 0x4C) +=
			(kPppRyjMegaBirthDouble * param->m_velocityRandom) * rand1 - param->m_velocityRandom;
	}

	life = *(u16*)(payload + 0x26);
	if (life == 0) {
		*(u16*)(particlePayload + 0x22) = 0xFFFF;
	} else {
		*(s16*)(particlePayload + 0x22) = life;
	}
	*(u8*)(particlePayload + 0x58) = 0;

	switch (payload[0xEC]) {
	case 1:
		PSMTXCopy(work->m_worldMatrix, worldMat->value);
		break;
	case 2:
		PSMTXCopy(pObject->m_localMatrix.value, worldMat->value);
		break;
	default:
		break;
	}

	if (colorData != NULL) {
		colorData->m_colorFrameDeltas[0] = *(float*)(payload + 0x2C);
		colorData->m_colorFrameDeltas[1] = *(float*)(payload + 0x30);
		colorData->m_colorFrameDeltas[2] = *(float*)(payload + 0x34);
		colorData->m_colorFrameDeltas[3] = *(float*)(payload + 0x38);
	}
}
