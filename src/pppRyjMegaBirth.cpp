#include "global.h"
#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/partMng.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include <string.h>

struct _PARTICLE_DATA
{
	Vec m_position;            // 0x00
	u8 _pad0C[0x04];
	Vec m_direction;           // 0x10
	u16 m_frameTimer;          // 0x1c
	u16 m_shapeFrame;          // 0x1e
	u16 m_drawFrame;           // 0x20
	u16 m_life;                // 0x22
	s8 m_colorOffset[4];       // 0x24
	float m_angle;             // 0x28
	float m_angleVelocity;     // 0x2c
	float m_angleRandom;       // 0x30
	float m_sizeX;             // 0x34
	float m_sizeY;             // 0x38
	float m_sizeVelocityX;     // 0x3c
	float m_sizeVelocityY;     // 0x40
	float m_sizeRandomX;       // 0x44
	float m_sizeRandomY;       // 0x48
	float m_velocity;          // 0x4c
	float m_acceleration;      // 0x50
	float m_alphaFade;         // 0x54
	u8 m_age;                  // 0x58
	u8 m_fadeInFrames;         // 0x59
	u8 m_fadeOutFrames;        // 0x5a
	u8 _pad5B[0x05];
}; // Size 0x60

STATIC_ASSERT(sizeof(_PARTICLE_DATA) == 0x60);
STATIC_ASSERT(offsetof(_PARTICLE_DATA, m_life) == 0x22);
STATIC_ASSERT(offsetof(_PARTICLE_DATA, m_alphaFade) == 0x54);

static void birth(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
static void calc(VRyjMegaBirth*, PRyjMegaBirth*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
static void calc_particle(_pppPObject*, VRyjMegaBirth*, PRyjMegaBirth*, VColor*);

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

static inline float get_rand()
{
	float r = Math.RandF();
	return r;
}

static inline signed char get_noise(u8 span)
{
	return (signed char)((float)(span * 2) * get_rand() - (float)(span >> 1));
}

static inline void apply_signed_randomization_2(float* x, float* y, u8 flags)
{
	if (((flags & 1) != 0) && ((flags & 2) != 0)) {
		if (0.5 < (double)Math.RandF()) {
			*x *= -1.0f;
		}
		if (0.5 < (double)Math.RandF()) {
			*y *= -1.0f;
		}
	} else if ((flags & 2) != 0) {
		*x *= -1.0f;
		*y *= -1.0f;
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
 * EN Address: 0x80081C90
 * EN Size: 124b
 * JP Address: 0x800816C4
 * JP Size: 124b
 */
void pppRyjMegaBirthCon(_pppPObject* pObject, PRyjMegaBirthOffsets* offsets)
{
	VRyjMegaBirth* work = (VRyjMegaBirth*)(pObject->m_workArea + GetRyjMegaBirthDataOffsets(offsets)->m_workOffset);
	PSMTXIdentity(work->m_worldMatrix);
	work->m_accelerationAxis.x = work->m_accelerationAxis.y = work->m_accelerationAxis.z = 0.0f;
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
	local.value[0][3] = particle->m_position.x;
	local.value[1][3] = particle->m_position.y;
	local.value[2][3] = particle->m_position.z;

	PSMTXScale(scale, particle->m_sizeX, particle->m_sizeY, particle->m_sizeX);
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
	float drawScale = params->m_drawDepthEnabled != 0 ? params->m_drawDepth : 0.0f;

	pppSetDrawEnv(
		(pppCVECTOR*)0, (pppFMATRIX*)0, drawScale, params->m_lightTarget, params->m_fogIndex, params->m_blendMode, 0, useTexture, 1,
		0);

	long* animData = static_cast<long*>(shape->m_animData);
	int baseRed = baseColor->m_color.rgba[0];
	int baseGreen = baseColor->m_color.rgba[1];
	int baseBlue = baseColor->m_color.rgba[2];
	int baseAlpha = baseColor->m_color.rgba[3];

	for (int i = 0; i < numParticles; i++) {
		if (particle->m_life != 0) {
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
			drawMatrix[0][0] = particle->m_sizeX * ppvMng->m_scale.x;
			drawMatrix[1][1] = particle->m_sizeY * ppvMng->m_scale.y;
			drawMatrix[2][2] = drawMatrix[0][0];

			if (particle->m_angle != 0.0f) {
				PSMTXRotRad(rotMatrix, 'Z', 0.017453292f * particle->m_angle);
				PSMTXConcat(drawMatrix, rotMatrix, drawMatrix);
			}

			{
				drawPos.x = drawMatrix[0][3];
				drawPos.y = drawMatrix[1][3];
				drawPos.z = drawMatrix[2][3];
				PSVECAdd(&drawPos, &particle->m_position, &drawPos);
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

			u16 frame = particle->m_drawFrame;
			pppShapeAnimData* shapeAnim = reinterpret_cast<pppShapeAnimData*>(animData);
			drawShape = (tagOAN3_SHAPE*)((u8*)shapeAnim + shapeAnim->m_frames[frame].m_shapeOffset);

			red = baseRed + (int)particle->m_colorOffset[0];
			green = baseGreen + (int)particle->m_colorOffset[1];
			blue = baseBlue + (int)particle->m_colorOffset[2];
			alpha = (int)((float)baseAlpha + (float)(int)particle->m_colorOffset[3] - particle->m_alphaFade);

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
		particle++;
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
static void calc_particle(_pppPObject* pObject, VRyjMegaBirth* work, PRyjMegaBirth* param, VColor* color)
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
			if (particle->m_life != 0)
			{
				calc(work, param, particle, color, colorData);

				frame = particle->m_shapeFrame;
				shapeAnim =
					static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[param->m_shapeIndex]->m_animData);
				particle->m_drawFrame = frame;
				frameData = &shapeAnim->m_frames[frame];

				particle->m_frameTimer = particle->m_frameTimer + param->m_frameStep;
				frame = particle->m_frameTimer;
				duration = frameData->m_duration;

				if ((s32)frame >= (s32)duration)
				{
					particle->m_frameTimer = frame - duration;
					particle->m_shapeFrame = particle->m_shapeFrame + 1;

					if ((s32)particle->m_shapeFrame >= (s32)shapeAnim->m_frameCount)
					{
						if ((frameData->m_flags & 0x80) != 0)
						{
							particle->m_shapeFrame = 0;
							particle->m_frameTimer = 0;
						}
						else
						{
							particle->m_frameTimer = 0;
							particle->m_shapeFrame = particle->m_shapeFrame - 1;
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

			particle++;
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
static void calc(
	VRyjMegaBirth* work, PRyjMegaBirth* param, _PARTICLE_DATA* particle, VColor* vColor,
	_PARTICLE_COLOR* colorData)
{
	int alpha;
	u32 frameCount;
	Vec step;

	alpha = vColor->m_color.rgba[3];

	if (colorData != NULL)
	{
		colorData->m_color[0] = colorData->m_color[0] + colorData->m_colorFrameDeltas[0];
		colorData->m_color[1] = colorData->m_color[1] + colorData->m_colorFrameDeltas[1];
		colorData->m_color[2] = colorData->m_color[2] + colorData->m_colorFrameDeltas[2];
		colorData->m_color[3] = colorData->m_color[3] + colorData->m_colorFrameDeltas[3];
		colorData->m_colorFrameDeltas[0] = colorData->m_colorFrameDeltas[0] + param->m_colorDeltaAdds[0];
		colorData->m_colorFrameDeltas[1] = colorData->m_colorFrameDeltas[1] + param->m_colorDeltaAdds[1];
		colorData->m_colorFrameDeltas[2] = colorData->m_colorFrameDeltas[2] + param->m_colorDeltaAdds[2];
		colorData->m_colorFrameDeltas[3] = colorData->m_colorFrameDeltas[3] + param->m_colorDeltaAdds[3];
		alpha = (int)vColor->m_color.rgba[3] + (int)colorData->m_color[3];
		if (alpha > 0xFF)
		{
			alpha = 0xFF;
		}
	}

	particle->m_angle = particle->m_angle + particle->m_angleVelocity;
	if ((param->m_angleFlags & 0x10) != 0)
	{
		particle->m_angleVelocity =
			particle->m_angleVelocity + (param->m_angleAcceleration + particle->m_angleRandom);
	}
	else
	{
		particle->m_angleVelocity = particle->m_angleVelocity + param->m_angleAcceleration;
	}

	while (180.0f <= particle->m_angle)
	{
		particle->m_angle -= 360.0f;
	}
	while (particle->m_angle < -180.0f)
	{
		particle->m_angle += 360.0f;
	}

	particle->m_sizeX = particle->m_sizeX + particle->m_sizeVelocityX;
	particle->m_sizeY = particle->m_sizeY + particle->m_sizeVelocityY;
	if ((param->m_sizeFlags & 0x10) != 0)
	{
		particle->m_sizeVelocityX =
			particle->m_sizeVelocityX + (param->m_sizeAccelerationX + particle->m_sizeRandomX);
		particle->m_sizeVelocityY =
			particle->m_sizeVelocityY + (param->m_sizeAccelerationY + particle->m_sizeRandomY);
	}
	else
	{
		particle->m_sizeVelocityX = particle->m_sizeVelocityX + param->m_sizeAccelerationX;
		particle->m_sizeVelocityY = particle->m_sizeVelocityY + param->m_sizeAccelerationY;
	}

	particle->m_velocity = particle->m_velocity + param->m_velocityStep;
	if (param->m_clampMode == 0)
	{
		if ((0.0f < param->m_velocity) &&
		    (param->m_velocityStep < 0.0f))
		{
			if (particle->m_velocity < 0.0f)
			{
				particle->m_velocity = 0.0f;
			}
		}
		else
		{
			float zero = 0.0f;
			if ((param->m_velocity < zero) &&
			    (zero < param->m_velocityStep) &&
			    (zero < particle->m_velocity))
			{
				particle->m_velocity = zero;
			}
		}
	}

	particle->m_acceleration = particle->m_acceleration + param->m_accelerationStep;
	PSVECScale(&particle->m_direction, &step, particle->m_velocity);
	PSVECAdd(&step, &particle->m_position, &particle->m_position);
	PSVECScale(&work->m_accelerationAxis, &step, particle->m_acceleration);
	PSVECAdd(&particle->m_position, &step, &particle->m_position);

	if (param->m_life != 0)
	{
		particle->m_life = particle->m_life - 1;
	}

	particle->m_age = particle->m_age + 1;
	frameCount = particle->m_fadeInFrames;
	if ((frameCount != 0) && ((u32)particle->m_age <= frameCount))
	{
		particle->m_alphaFade = particle->m_alphaFade - (float)alpha / (float)frameCount;
	}

	frameCount = particle->m_fadeOutFrames;
	if ((frameCount != 0) && ((int)particle->m_life <= (int)frameCount))
	{
		float fadeAlpha = (float)alpha;
		float fadeFrameCount = (float)(unsigned int)param->m_fadeOutFrames;
		float particleAlpha = particle->m_alphaFade;

		particle->m_alphaFade = particleAlpha + fadeAlpha / fadeFrameCount;
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
static void birth(
    _pppPObject* pObject, VRyjMegaBirth* work, PRyjMegaBirth* param, VColor* color, _PARTICLE_DATA* particle,
    _PARTICLE_WMAT* worldMat, _PARTICLE_COLOR* colorData)
{
	u16 life;
	float vx;
	float vy;
	float vz;

	float spread = (float)param->m_spread;
	float spreadRange = 2.0f * spread;

	memset(particle, 0, sizeof(_PARTICLE_DATA));
	if (worldMat != NULL) {
		memset(worldMat, 0, sizeof(_PARTICLE_WMAT));
	}
	if (colorData != NULL) {
		memset(colorData, 0, sizeof(_PARTICLE_COLOR));
	}

	switch (param->m_spawnMode) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7: {
		pppFVECTOR4 baseDir;
		pppIVECTOR4 angles;
		pppFMATRIX rot;

		baseDir.x = param->m_baseDirection.x;
		baseDir.y = param->m_baseDirection.y;
		baseDir.z = param->m_baseDirection.z;
		angles.x = (s32)(spreadRange * Math.RandF() - spread);
		angles.x = (s32)((float)(angles.x << 15) / 180.0f);
		angles.y = (s32)(spreadRange * Math.RandF() - spread);
		angles.y = (s32)((float)(angles.y << 15) / 180.0f);
		angles.z = (s32)(spreadRange * Math.RandF() - spread);
		angles.z = (s32)((float)(angles.z << 15) / 180.0f);
		if ((param->m_spawnMode == 2) || (param->m_spawnMode == 3)) {
			angles.x = 0;
			angles.y = 0;
		}

		pppGetRotMatrixXYZ(rot, &angles);
		PSMTXMultVecSR(rot.value, (Vec*)&baseDir, &particle->m_direction);
		particle->m_direction.x *= param->m_directionScale.x;
		particle->m_direction.y *= param->m_directionScale.y;
		particle->m_direction.z *= param->m_directionScale.z;
		PSVECNormalize(&particle->m_direction, &particle->m_direction);
		break;
	}
	}

	switch (param->m_spawnMode) {
	default:
	{
		if (0.0f != param->m_directionSpeed) {
			float scale;

			switch (param->m_randomMode) {
			default:
				scale = param->m_directionSpeed;
				break;
			case 1:
				Math.RandF();
				scale = param->m_directionSpeed * Math.RandF();
				break;
			case 2:
			{
				scale = param->m_directionSpeed * Math.RandF() * Math.RandF();
				break;
			}
			case 3:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				scale = param->m_directionSpeed * rand2;
				scale = param->m_directionSpeed - 0.7f * (scale * rand1);
				break;
			}
			case 4:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				float rand3 = Math.RandF();
				float rand4 = Math.RandF();
				scale = param->m_directionSpeed * rand2;
				scale = rand4 * (rand3 * (scale * rand1));
				break;
			}
			case 5:
			{
				float rand1 = Math.RandF();
				float rand2 = Math.RandF();
				float rand3 = Math.RandF();
				scale = param->m_directionSpeed * rand2;
				scale = param->m_directionSpeed - 0.5f * (rand3 * (scale * rand1));
				break;
			}
			}

			PSVECScale(&particle->m_direction, &particle->m_position, scale);
		}
		break;
	}

	case 4:
	case 5:
	{
		if (0.0f == param->m_directionSpeed) {
			break;
		}
		float speedRandHalf = 0.5f * param->m_directionSpeed;

		{
		float rand1;
		float rand2;
		float rand3;
		float rand4;
		switch (param->m_randomMode) {
		default:
			particle->m_position.x = param->m_directionSpeed * Math.RandF();
			particle->m_position.x -= speedRandHalf;
			particle->m_position.y = param->m_directionSpeed * Math.RandF();
			particle->m_position.y -= speedRandHalf;
			particle->m_position.z = param->m_directionSpeed * Math.RandF();
			particle->m_position.z -= speedRandHalf;
			break;
		case 1:
			Math.RandF();
			particle->m_position.x = param->m_directionSpeed * Math.RandF();
			particle->m_position.x -= speedRandHalf;
			particle->m_position.y = param->m_directionSpeed * Math.RandF();
			particle->m_position.y -= speedRandHalf;
			particle->m_position.z = param->m_directionSpeed * Math.RandF();
			particle->m_position.z -= speedRandHalf;
			break;
		case 2:
			particle->m_position.x = param->m_directionSpeed * Math.RandF() * Math.RandF();
			particle->m_position.x -= speedRandHalf;
			particle->m_position.y = param->m_directionSpeed * Math.RandF() * Math.RandF();
			particle->m_position.y -= speedRandHalf;
			particle->m_position.z = param->m_directionSpeed * Math.RandF() * Math.RandF();
			particle->m_position.z -= speedRandHalf;
			break;
		case 3:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.x = param->m_directionSpeed - 0.7f * (rand2 * rand1);
			particle->m_position.x -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.y = param->m_directionSpeed - 0.7f * (rand2 * rand1);
			particle->m_position.y -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.z = param->m_directionSpeed - 0.7f * (rand2 * rand1);
			particle->m_position.z -= speedRandHalf;
			break;
		case 4:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand4 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.x = rand4 * (rand3 * (rand2 * rand1));
			particle->m_position.x -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand4 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.y = rand4 * (rand3 * (rand2 * rand1));
			particle->m_position.y -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand4 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.z = rand4 * (rand3 * (rand2 * rand1));
			particle->m_position.z -= speedRandHalf;
			break;
		case 5:
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.x = param->m_directionSpeed - 0.5f * (rand3 * (rand2 * rand1));
			particle->m_position.x -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.y = param->m_directionSpeed - 0.5f * (rand3 * (rand2 * rand1));
			particle->m_position.y -= speedRandHalf;
			rand1 = Math.RandF();
			rand2 = Math.RandF();
			rand3 = Math.RandF();
			rand2 = param->m_directionSpeed * rand2;
			particle->m_position.z = param->m_directionSpeed - 0.5f * (rand3 * (rand2 * rand1));
			particle->m_position.z -= speedRandHalf;
			break;
		}
		}

		particle->m_position.x *= param->m_directionScale.x;
		particle->m_position.y *= param->m_directionScale.y;
		particle->m_position.z *= param->m_directionScale.z;
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
					sampleT = static_cast<float>(1.0 - (r2 * (r1 * r0)));
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
					sampleT = static_cast<float>(1.0 - (r4 * (r3 * (r2 * (r1 * r0)))));
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

				particle->m_position.x = vx * param->m_directionScale.x;
				particle->m_position.y = vy * param->m_directionScale.y;
				particle->m_position.z = vz * param->m_directionScale.z;

				if ((param->m_spawnMode == 8) || (param->m_spawnMode == 9)) {
					PSVECNormalize(&particle->m_position, &particle->m_direction);
				}
			}
		}
		break;
	}

	}



	particle->m_colorOffset[0] = get_noise(param->m_colorOffsetRange[0]);
	particle->m_colorOffset[1] = get_noise(param->m_colorOffsetRange[1]);
	particle->m_colorOffset[2] = get_noise(param->m_colorOffsetRange[2]);
	particle->m_colorOffset[3] = get_noise(param->m_colorOffsetRange[3]);

	if (param->m_fadeInFrames != 0) {
		particle->m_alphaFade = (float)color->m_color.rgba[3];
		particle->m_fadeInFrames = param->m_fadeInFrames;
	}
	if (param->m_fadeOutFrames != 0) {
		particle->m_fadeOutFrames = param->m_fadeOutFrames;
	}

	particle->m_angle = param->m_angleStart;
	particle->m_angleVelocity = param->m_angleVelocity;

	if (param->m_angleFlags != 0) {
		particle->m_angleRandom = param->m_angleRandom * Math.RandF();
		u8 tailFlags = param->m_angleFlags;
		if (((tailFlags & 1) != 0) && ((tailFlags & 2) != 0)) {
			if (0.5 < (double)Math.RandF()) {
				particle->m_angleRandom *= -1.0f;
			}
		} else if ((tailFlags & 2) != 0) {
			particle->m_angleRandom *= -1.0f;
		}
	}
	if ((param->m_angleFlags & 4) != 0) {
		particle->m_angle = particle->m_angle + particle->m_angleRandom;
	}
	if ((param->m_angleFlags & 8) != 0) {
		particle->m_angleVelocity = particle->m_angleVelocity + particle->m_angleRandom;
	}
	while (180.0f <= particle->m_angle) {
		particle->m_angle -= 360.0f;
	}
	while (particle->m_angle < -180.0f) {
		particle->m_angle += 360.0f;
	}

	particle->m_sizeX = param->m_sizeX;
	particle->m_sizeY = param->m_sizeY;
	particle->m_sizeVelocityX = param->m_sizeVelocityX;
	particle->m_sizeVelocityY = param->m_sizeVelocityY;

	if (param->m_sizeFlags != 0) {
		if ((param->m_sizeFlags & 0x20) != 0) {
			float randomRotation = param->m_sizeRandomX * Math.RandF();
			particle->m_sizeRandomY = randomRotation;
			particle->m_sizeRandomX = randomRotation;
			u8 rotFlags = param->m_sizeFlags;
			if (((rotFlags & 1) != 0) && ((rotFlags & 2) != 0)) {
				if (0.5 < (double)Math.RandF()) {
					particle->m_sizeRandomX *= -1.0f;
					particle->m_sizeRandomY *= -1.0f;
				}
			} else if ((rotFlags & 2) != 0) {
				particle->m_sizeRandomX *= -1.0f;
				particle->m_sizeRandomY *= -1.0f;
			}
		} else {
			particle->m_sizeRandomX = param->m_sizeRandomX * Math.RandF();
			particle->m_sizeRandomY = param->m_sizeRandomY * Math.RandF();
			apply_signed_randomization_2(&particle->m_sizeRandomX, &particle->m_sizeRandomY, param->m_sizeFlags);
		}
	}
	if ((param->m_sizeFlags & 4) != 0) {
		particle->m_sizeX = particle->m_sizeX + particle->m_sizeRandomX;
		particle->m_sizeY = particle->m_sizeY + particle->m_sizeRandomY;
	}
	if ((param->m_sizeFlags & 8) != 0) {
		particle->m_sizeVelocityX = particle->m_sizeVelocityX + particle->m_sizeRandomX;
		particle->m_sizeVelocityY = particle->m_sizeVelocityY + particle->m_sizeRandomY;
	}

	particle->m_velocity = param->m_velocity;
	particle->m_acceleration = param->m_acceleration;
	if (0.0f != param->m_velocityRandom) {
		float rand1 = Math.RandF();
		particle->m_velocity +=
			(2.0f * param->m_velocityRandom) * rand1 - param->m_velocityRandom;
	}

	life = param->m_life;
	if (life == 0) {
		particle->m_life = 0xFFFF;
	} else {
		particle->m_life = life;
	}
	particle->m_age = 0;

	switch (param->m_matrixMode) {
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
		colorData->m_colorFrameDeltas[0] = param->m_colorFrameDeltas[0];
		colorData->m_colorFrameDeltas[1] = param->m_colorFrameDeltas[1];
		colorData->m_colorFrameDeltas[2] = param->m_colorFrameDeltas[2];
		colorData->m_colorFrameDeltas[3] = param->m_colorFrameDeltas[3];
	}
}
