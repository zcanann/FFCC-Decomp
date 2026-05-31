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

extern const float FLOAT_80330458;
extern float FLOAT_8033044C;
extern const float FLOAT_8033045c;
extern const float FLOAT_80330460;
extern const float FLOAT_80330470;
extern const float FLOAT_80330474;
extern const float FLOAT_80330478;
extern const double DOUBLE_80330480;
extern const double DOUBLE_80330488;
extern const float FLOAT_80330490[2];

Mtx g_matUnit;

extern "C" const char s_pppRyjMegaBirth_cpp[] = "pppRyjMegaBirth.cpp";

extern const float FLOAT_80330458 = 360.0f;
extern const float FLOAT_8033045c = 180.0f;
extern const float FLOAT_80330460 = -180.0f;
extern const double DOUBLE_80330468 = 4503599627370496.0;
extern const float FLOAT_80330470 = 2.0f;
extern const float FLOAT_80330474 = 0.7f;
extern const float FLOAT_80330478 = 0.5f;
extern const double DOUBLE_80330480 = 1.0;
extern const double DOUBLE_80330488 = 0.5;
extern const float FLOAT_80330490[2] = { -1.0f, 0.0f };
extern const float FLOAT_80330498 = 0.0f;
extern const float FLOAT_8033049c = 30.0f;
extern const float FLOAT_803304a0 = 3.1415927f;
extern const float FLOAT_803304a4 = 32768.0f;

static inline float RyjZero()
{
	return *reinterpret_cast<const float*>(&kPppRyjMegaBirthZero);
}

static inline float RyjLoadFloat(const float& value)
{
	return value;
}

static inline double RyjLoadDouble(const double& value)
{
	return value;
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

static inline unsigned char clamp_u8_int(int value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 0xFF) {
		return 0xFF;
	}
	return (unsigned char)value;
}

static inline unsigned char clamp_alpha_7f(int value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 0x7F) {
		return 0x7F;
	}
	return (unsigned char)value;
}

static inline float calc_mesh_sample_t(u8 mode)
{
	switch (mode) {
	case 1:
		(void)Math.RandF();
		return Math.RandF();
	case 2:
		return Math.RandF() * Math.RandF();
	case 3:
		return (float)(RyjLoadDouble(DOUBLE_80330480) - (double)(Math.RandF() * Math.RandF() * Math.RandF()));
	case 4:
		return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF();
	case 5:
		return (float)(RyjLoadDouble(DOUBLE_80330480) -
			(double)(Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF()));
	default:
		return Math.RandF();
	}
}

static inline float calc_spawn_speed(float speed, u8 mode)
{
	float halfSpeed = RyjLoadFloat(FLOAT_80330478) * speed;

	switch (mode) {
	case 1:
		(void)Math.RandF();
		return speed * Math.RandF() - halfSpeed;
	case 2:
		return speed * Math.RandF() * Math.RandF() - halfSpeed;
	case 3:
		return -(RyjLoadFloat(FLOAT_80330474) * (speed * Math.RandF() * Math.RandF()) - speed) - halfSpeed;
	case 4:
		return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed - halfSpeed;
	case 5:
		return -(RyjLoadFloat(FLOAT_80330478) * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed) - halfSpeed;
	default:
		return speed * Math.RandF() - halfSpeed;
	}
}

static inline float calc_direction_speed(float speed, u8 mode)
{
	switch (mode) {
	case 1:
		(void)Math.RandF();
		return speed * Math.RandF();
	case 2:
		return speed * Math.RandF() * Math.RandF();
	case 3:
		return -(RyjLoadFloat(FLOAT_80330474) * (speed * Math.RandF() * Math.RandF()) - speed);
	case 4:
		return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed;
	case 5:
		return -(RyjLoadFloat(FLOAT_80330478) * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed);
	default:
		return speed;
	}
}

static inline void calc_spawn_position(Vec* out, float speed, u8 mode)
{
	float halfSpeed = RyjLoadFloat(FLOAT_80330478) * speed;

	switch (mode) {
	case 1:
		(void)Math.RandF();
		out->x = speed * Math.RandF() - halfSpeed;
		out->y = speed * Math.RandF() - halfSpeed;
		out->z = speed * Math.RandF() - halfSpeed;
		break;
	case 2:
		out->x = speed * Math.RandF() * Math.RandF() - halfSpeed;
		out->y = speed * Math.RandF() * Math.RandF() - halfSpeed;
		out->z = speed * Math.RandF() * Math.RandF() - halfSpeed;
		break;
	case 3:
		out->x = -(RyjLoadFloat(FLOAT_80330474) * (speed * Math.RandF() * Math.RandF()) - speed) - halfSpeed;
		out->y = -(RyjLoadFloat(FLOAT_80330474) * (speed * Math.RandF() * Math.RandF()) - speed) - halfSpeed;
		out->z = -(RyjLoadFloat(FLOAT_80330474) * (speed * Math.RandF() * Math.RandF()) - speed) - halfSpeed;
		break;
	case 4:
		out->x = Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed - halfSpeed;
		out->y = Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed - halfSpeed;
		out->z = Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed - halfSpeed;
		break;
	case 5:
		out->x = -(RyjLoadFloat(FLOAT_80330478) * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed) - halfSpeed;
		out->y = -(RyjLoadFloat(FLOAT_80330478) * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed) - halfSpeed;
		out->z = -(RyjLoadFloat(FLOAT_80330478) * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed) - halfSpeed;
		break;
	default:
		out->x = speed * Math.RandF() - halfSpeed;
		out->y = speed * Math.RandF() - halfSpeed;
		out->z = speed * Math.RandF() - halfSpeed;
		break;
	}
}

static inline signed char random_signed_byte_span(u8 span)
{
	return (signed char)((s32)((float)(span << 1) * Math.RandF() - (float)(span >> 1)));
}

static inline void apply_signed_randomization_2(u8* particle, s32 offset, u8 flags)
{
	if (((flags & 1) != 0) && ((flags & 2) != 0)) {
		if (RyjLoadDouble(DOUBLE_80330488) < (double)Math.RandF()) {
			*f32_at(particle, offset) = *f32_at(particle, offset) * FLOAT_80330490[0];
		}
		if (RyjLoadDouble(DOUBLE_80330488) < (double)Math.RandF()) {
			*f32_at(particle, offset + 4) = *f32_at(particle, offset + 4) * FLOAT_80330490[0];
		}
	} else if ((flags & 2) != 0) {
		*f32_at(particle, offset) = *f32_at(particle, offset) * FLOAT_80330490[0];
		*f32_at(particle, offset + 4) = *f32_at(particle, offset + 4) * FLOAT_80330490[0];
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
		reinterpret_cast<VRyjMegaBirth*>(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);

	if (work->m_particleBlock != 0)
	{
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_particleBlock));
		work->m_particleBlock = 0;
	}

	if (work->m_worldMatrixBlock != 0)
	{
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_worldMatrixBlock));
		work->m_worldMatrixBlock = 0;
	}

	if (work->m_colorBlock != 0)
	{
		pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_colorBlock));
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
	VRyjMegaBirth* work = (VRyjMegaBirth*)(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);
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
void pppRyjDrawMegaBirth(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
	PRyjMegaBirth* params = (PRyjMegaBirth*)stepData;
	u8* payload = (u8*)params;
	int* offsets = ctrlTable->m_serializedDataOffsets;
	VRyjMegaBirth* work = (VRyjMegaBirth*)(obj->m_workArea + offsets[2]);
	VColor* baseColor = (VColor*)(obj->m_workArea + offsets[1]);
	_PARTICLE_DATA* particleBlock = work->m_particleBlock;
	PARTICLE_WMAT* particleWorldMatBlock = work->m_worldMatrixBlock;
	_PARTICLE_COLOR* colorBlock = work->m_colorBlock;
	_PARTICLE_DATA* particle = particleBlock;
	PARTICLE_WMAT* particleWorldMat = particleWorldMatBlock;
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
	default:
		break;
	}

	long** animDataSet = *(long***)(*(u32*)&ppvEnv->m_particleColors[0] + params->m_shapeIndex * 4);
	int useTexture = params->m_textureMode == 0;
	float drawScale = params->m_drawDepthEnabled != 0 ? params->m_drawDepth : kPppRyjMegaBirthZero;

	pppSetDrawEnv(
		(pppCVECTOR*)0, (pppFMATRIX*)0, drawScale, params->m_lightTarget, params->m_fogIndex, params->m_blendMode, 0, useTexture, 1,
		0);

	long* animData = *animDataSet;
	int baseRed = baseColor->m_red;
	int baseGreen = baseColor->m_green;
	int baseBlue = baseColor->m_blue;
	int baseAlpha = baseColor->m_alpha;

	for (int i = 0; i < numParticles; i++) {
		if (*u16_at(particle, 0x22) != 0) {
			Mtx drawMatrix;
			pppCVECTOR drawColor;
			int red;
			int green;
			int blue;
			int alpha;
			pppFMATRIX viewMatrix;

			PSMTXIdentity(drawMatrix);
			drawMatrix[0][0] = *f32_at(particle, 0x34) * ppvMng->m_scale.x;
			drawMatrix[1][1] = *f32_at(particle, 0x38) * ppvMng->m_scale.y;
			drawMatrix[2][2] = drawMatrix[0][0];

			if (*f32_at(particle, 0x28) != kPppRyjMegaBirthZero) {
				Mtx rotMatrix;

				PSMTXRotRad(rotMatrix, 'Z', FLOAT_8033044C * *f32_at(particle, 0x28));
				PSMTXConcat(drawMatrix, rotMatrix, drawMatrix);
			}

			{
				Vec drawPos;
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
				Vec viewPos;

				viewPos.x = drawMatrix[0][3];
				viewPos.y = drawMatrix[1][3];
				viewPos.z = drawMatrix[2][3];
				PSMTXMultVec(baseViewMatrix.value, &viewPos, &viewPos);
				drawMatrix[0][3] = viewPos.x;
				drawMatrix[1][3] = viewPos.y;
				drawMatrix[2][3] = viewPos.z;
				break;
			}
			case 1: {
				Vec viewPos;

				PSMTXConcat(*(Mtx*)particleWorldMat, obj->m_localMatrix.value, viewMatrix.value);
				PSMTXConcat(ppvCameraMatrix, viewMatrix.value, viewMatrix.value);
				viewPos.x = drawMatrix[0][3];
				viewPos.y = drawMatrix[1][3];
				viewPos.z = drawMatrix[2][3];
				PSMTXMultVec(viewMatrix.value, &viewPos, &viewPos);
				drawMatrix[0][3] = viewPos.x;
				drawMatrix[1][3] = viewPos.y;
				drawMatrix[2][3] = viewPos.z;
				break;
			}
			case 2: {
				Vec viewPos;

				PSMTXConcat(work->m_worldMatrix, *(Mtx*)particleWorldMat, viewMatrix.value);
				PSMTXConcat(ppvCameraMatrix, viewMatrix.value, viewMatrix.value);
				viewPos.x = drawMatrix[0][3];
				viewPos.y = drawMatrix[1][3];
				viewPos.z = drawMatrix[2][3];
				PSMTXMultVec(viewMatrix.value, &viewPos, &viewPos);
				drawMatrix[0][3] = viewPos.x;
				drawMatrix[1][3] = viewPos.y;
				drawMatrix[2][3] = viewPos.z;
				break;
			}
			default:
				break;
			}

			GXLoadPosMtxImm(drawMatrix, 0);

			short frame = *s16_at(particle, 0x20);
			tagOAN3_SHAPE* shape = (tagOAN3_SHAPE*)((u8*)animData + *(s16*)((u8*)animData + frame * 8 + 0x10));

			red = baseRed + (int)*(s8*)((u8*)particle + 0x24);
			green = baseGreen + (int)*(s8*)((u8*)particle + 0x25);
			blue = baseBlue + (int)*(s8*)((u8*)particle + 0x26);
			alpha = (int)(
				(float)(baseAlpha + (int)*(s8*)((u8*)particle + 0x27)) - *f32_at(particle, 0x54));

			if (colorData != NULL) {
				red += (int)colorData->m_color[0];
				green += (int)colorData->m_color[1];
				blue += (int)colorData->m_color[2];
				alpha += (int)colorData->m_color[3];
			}

			unsigned char clampedRed = clamp_u8_int(red);
			unsigned char clampedGreen = clamp_u8_int(green);
			unsigned char clampedBlue = clamp_u8_int(blue);
			unsigned char clampedAlpha = clamp_alpha_7f(alpha);
			drawColor.rgba[0] = clampedRed;
			drawColor.rgba[1] = clampedGreen;
			drawColor.rgba[2] = clampedBlue;
			drawColor.rgba[3] = clampedAlpha;

			GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)drawColor.rgba);
			pppSetBlendMode(params->m_blendMode);
			pppDrawShp(shape, ppvEnv->m_materialSetPtr, params->m_blendMode);
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
	s32* serializedDataOffsets;
	s32 workOffset;
	s32 colorOffset;
	VRyjMegaBirth* work;
	VColor* color;

	serializedDataOffsets = offsets->m_serializedDataOffsets;
	workOffset = serializedDataOffsets[2];
	colorOffset = serializedDataOffsets[1];
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
			work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc(
				work->m_numParticles * sizeof(PARTICLE_WMAT), ppvEnv->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp), 0x269);
			if (work->m_worldMatrixBlock != NULL)
			{
				memset(work->m_worldMatrixBlock, 0, work->m_numParticles * sizeof(PARTICLE_WMAT));
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
	s32 colorSet;
	s32 frameData;
	_PARTICLE_DATA* particle;
	PARTICLE_WMAT* worldMats;
	_PARTICLE_COLOR* colorData;
	s32 maxParticles;
	s32 emitCount;
	s32 i;

	emitCount = 0;
	particle = (_PARTICLE_DATA*)work->m_particleBlock;
	worldMats = work->m_worldMatrixBlock;
	colorData = work->m_colorBlock;
	maxParticles = work->m_numParticles;

	if ((gPppCalcDisabled == 0) && (param->m_shapeIndex != 0xFFFF))
	{
		work->m_emitTimer = work->m_emitTimer + 1;

		for (i = 0; i < maxParticles; i = i + 1)
		{
			if (*(u16*)((u8*)particle + 0x22) != 0)
			{
				calc(work, param, particle, color, colorData);

				frame = *(u16*)((u8*)particle + 0x1E);
				colorSet = (s32)**(s32***)(*(s32*)&ppvEnv->m_particleColors[0] + param->m_shapeIndex * 4);
				*(u16*)((u8*)particle + 0x20) = frame;
				frameData = colorSet + (u32)frame * 8 + 0x10;

				*(u16*)((u8*)particle + 0x1C) = *(u16*)((u8*)particle + 0x1C) + param->m_frameStep;
				frame = *(u16*)((u8*)particle + 0x1C);
				duration = *(s16*)(frameData + 2);

				if ((s32)frame >= (s32)duration)
				{
					*(u16*)((u8*)particle + 0x1C) = frame - duration;
					*(u16*)((u8*)particle + 0x1E) = *(u16*)((u8*)particle + 0x1E) + 1;

					if ((s32)*(u16*)((u8*)particle + 0x1E) >= (s32)*(s16*)(colorSet + 6))
					{
						if ((*(u8*)(frameData + 4) & 0x80) != 0)
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
				birth(pObject, work, param, color, particle, (_PARTICLE_WMAT*)worldMats, colorData);
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

	alpha = vColor->m_alpha;
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
		alpha = (int)vColor->m_alpha + (int)colorData->m_color[3];
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
		const float& angleWrap = FLOAT_80330458;
		const float& angleMax = FLOAT_8033045c;
		volatile float* angle = f32_at(particlePayload, 0x28);
		while (angleMax <= *angle)
		{
			*angle = *angle - angleWrap;
		}
	}
	{
		const float& angleWrap = FLOAT_80330458;
		const float& angleMin = FLOAT_80330460;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(
    _pppPObject* pObject, VRyjMegaBirth* work, PRyjMegaBirth* param, VColor* color, _PARTICLE_DATA* particle,
    _PARTICLE_WMAT* worldMat, _PARTICLE_COLOR* colorData)
{
	u8* payload;
	u8* particlePayload;
	float speed;
	s16 life;

	payload = (u8*)param;
	particlePayload = (u8*)particle;
	float spread = (float)payload[0x2B];
	float range = RyjLoadFloat(FLOAT_80330470) * spread;

	memset(particle, 0, 0x60);
	if (worldMat != NULL) {
		memset(worldMat, 0, sizeof(_PARTICLE_WMAT));
	}
	if (colorData != NULL) {
		memset(colorData, 0, sizeof(_PARTICLE_COLOR));
	}

	if (*(s8*)(payload + 0x2A) < 8) {
		Vec baseDirection;
		Vec* direction;
		s32 angle[4];
		pppFMATRIX rot;

		baseDirection.x = *f32_at(payload, 0xA0);
		baseDirection.y = *f32_at(payload, 0xA4);
		baseDirection.z = *f32_at(payload, 0xA8);

		angle[0] = (s32)((float)((s32)(range * Math.RandF() - spread) << 15) / RyjLoadFloat(FLOAT_8033045c));
		angle[1] = (s32)((float)((s32)(range * Math.RandF() - spread) << 15) / RyjLoadFloat(FLOAT_8033045c));
		angle[2] = (s32)((float)((s32)(range * Math.RandF() - spread) << 15) / RyjLoadFloat(FLOAT_8033045c));
		angle[3] = 0;

		if ((payload[0x2A] == 2) || (payload[0x2A] == 3)) {
			angle[0] = 0;
			angle[1] = 0;
		}

		pppGetRotMatrixXYZ(rot, (pppIVECTOR4*)angle);
		direction = (Vec*)(particlePayload + 0x10);
		PSMTXMultVecSR(rot.value, &baseDirection, direction);
		direction->x = direction->x * *f32_at(payload, 0xD8);
		direction->y = direction->y * *f32_at(payload, 0xDC);
		direction->z = direction->z * *f32_at(payload, 0xE0);
		PSVECNormalize(direction, direction);
	}

	speed = *f32_at(payload, 0xD4);
	if ((*(s8*)(payload + 0x2A) < 4) || (*(s8*)(payload + 0x2A) >= 10)) {
		if (speed != kPppRyjMegaBirthZero) {
			u8 speedMode = payload[0xE8];

			Vec* direction = (Vec*)(particlePayload + 0x10);
			Vec* position = (Vec*)particlePayload;
			PSVECScale(direction, position, calc_direction_speed(speed, speedMode));
		}
	} else if (*(s8*)(payload + 0x2A) < 6) {
		if (speed != kPppRyjMegaBirthZero) {
			u8 speedMode = payload[0xE8];

			calc_spawn_position((Vec*)particlePayload, speed, speedMode);
			*f32_at(particlePayload, 0x00) = *f32_at(particlePayload, 0x00) * *f32_at(payload, 0xD8);
			*f32_at(particlePayload, 0x04) = *f32_at(particlePayload, 0x04) * *f32_at(payload, 0xDC);
			*f32_at(particlePayload, 0x08) = *f32_at(particlePayload, 0x08) * *f32_at(payload, 0xE0);
		}
	} else if (*(s8*)(payload + 0x2A) < 10) {
		u8 speedMode = payload[0xE8];
		s16 pathIndex = *s16_at(payload, 0xF0);
		Vec* pathBase = *(Vec**)((u8*)pObject + 0x70);

		if (pathIndex >= 0) {
			s16* pathInfo = (s16*)(*(int*)&ppvEnv->m_particleColors[1] + pathIndex * 8);

			if (pathBase == NULL) {
				pathBase = (Vec*)ppvEnv->m_mapMeshPtr[pathInfo[0]]->m_vertices;
			}

			if (pathBase != NULL) {
				u16 sampleIndex;

				if ((u16)work->m_meshEmitIndex >= (u16)pathInfo[1]) {
					work->m_meshEmitIndex = 0;
				}

				if ((speedMode == 0) || (speedMode >= 6)) {
					sampleIndex = work->m_meshEmitIndex;
					work->m_meshEmitIndex = sampleIndex + 1;
				} else {
					sampleIndex = (u16)((int)(calc_mesh_sample_t(speedMode) * (float)pathInfo[1]));
				}

				Vec* pathVec = pathBase + ((u16*)*(int*)(pathInfo + 2))[sampleIndex];
				*f32_at(particlePayload, 0x00) = pathVec->x * *f32_at(payload, 0xD8);
				*f32_at(particlePayload, 0x04) = pathVec->y * *f32_at(payload, 0xDC);
				*f32_at(particlePayload, 0x08) = pathVec->z * *f32_at(payload, 0xE0);
				if ((payload[0x2A] == 8) || (payload[0x2A] == 9)) {
					PSVECNormalize((Vec*)particlePayload, (Vec*)(particlePayload + 0x10));
				}
			}
		}
	}

	*u8_at(particlePayload, 0x24) = random_signed_byte_span(payload[0x58]);
	*u8_at(particlePayload, 0x25) = random_signed_byte_span(payload[0x59]);
	*u8_at(particlePayload, 0x26) = random_signed_byte_span(payload[0x5A]);
	*u8_at(particlePayload, 0x27) = random_signed_byte_span(payload[0x5B]);

	if (payload[0x22] != 0) {
		*f32_at(particlePayload, 0x54) = (float)color->m_alpha;
		*u8_at(particlePayload, 0x59) = payload[0x22];
	}
	if (payload[0x29] != 0) {
		*u8_at(particlePayload, 0x5A) = payload[0x29];
	}

	*f32_at(particlePayload, 0x28) = *f32_at(payload, 0x90);
	*f32_at(particlePayload, 0x2C) = *f32_at(payload, 0x94);

	if (payload[0xEB] != 0) {
		*f32_at(particlePayload, 0x30) = *f32_at(payload, 0x9C) * Math.RandF();
		if (((payload[0xEB] & 1) != 0) && ((payload[0xEB] & 2) != 0)) {
			if (RyjLoadDouble(DOUBLE_80330488) < (double)Math.RandF()) {
				*f32_at(particlePayload, 0x30) = *f32_at(particlePayload, 0x30) * FLOAT_80330490[0];
			}
		} else if ((payload[0xEB] & 2) != 0) {
			*f32_at(particlePayload, 0x30) = *f32_at(particlePayload, 0x30) * FLOAT_80330490[0];
		}
	}
	if ((payload[0xEB] & 4) != 0) {
		*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + *f32_at(particlePayload, 0x30);
	}
	if ((payload[0xEB] & 8) != 0) {
		*f32_at(particlePayload, 0x2C) = *f32_at(particlePayload, 0x2C) + *f32_at(particlePayload, 0x30);
	}
	{
		const float& angleWrap = FLOAT_80330458;
		const float& angleMax = FLOAT_8033045c;
		while (angleMax <= *f32_at(particlePayload, 0x28)) {
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) - angleWrap;
		}
	}
	{
		const float& angleWrap = FLOAT_80330458;
		const float& angleMin = FLOAT_80330460;
		while (*f32_at(particlePayload, 0x28) < angleMin) {
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + angleWrap;
		}
	}

	*f32_at(particlePayload, 0x34) = *f32_at(payload, 0x50);
	*f32_at(particlePayload, 0x38) = *f32_at(payload, 0x54);
	*f32_at(particlePayload, 0x3C) = *f32_at(payload, 0x60);
	*f32_at(particlePayload, 0x40) = *f32_at(payload, 0x64);

	if (payload[0xEA] != 0) {
		if ((payload[0xEA] & 0x20) == 0) {
			*f32_at(particlePayload, 0x44) = *f32_at(payload, 0x80) * Math.RandF();
			*f32_at(particlePayload, 0x48) = *f32_at(payload, 0x84) * Math.RandF();
		} else {
			float randomRotation = *f32_at(payload, 0x80) * Math.RandF();
			*f32_at(particlePayload, 0x44) = randomRotation;
			*f32_at(particlePayload, 0x48) = randomRotation;
		}
		apply_signed_randomization_2(particlePayload, 0x44, payload[0xEA]);
	}
	if ((payload[0xEA] & 4) != 0) {
		*f32_at(particlePayload, 0x34) = *f32_at(particlePayload, 0x34) + *f32_at(particlePayload, 0x44);
		*f32_at(particlePayload, 0x38) = *f32_at(particlePayload, 0x38) + *f32_at(particlePayload, 0x48);
	}
	if ((payload[0xEA] & 8) != 0) {
		*f32_at(particlePayload, 0x3C) = *f32_at(particlePayload, 0x3C) + *f32_at(particlePayload, 0x44);
		*f32_at(particlePayload, 0x40) = *f32_at(particlePayload, 0x40) + *f32_at(particlePayload, 0x48);
	}

	*f32_at(particlePayload, 0x4C) = *f32_at(payload, 0xC0);
	*f32_at(particlePayload, 0x50) = *f32_at(payload, 0xCC);
	if (*f32_at(payload, 0xC8) != kPppRyjMegaBirthZero) {
		*f32_at(particlePayload, 0x4C) =
			*f32_at(particlePayload, 0x4C) + RyjLoadFloat(FLOAT_80330470) * *f32_at(payload, 0xC8) * Math.RandF() -
			*f32_at(payload, 0xC8);
	}

	life = *(s16*)(payload + 0x26);
	if (life == 0) {
		*(s16*)(particlePayload + 0x22) = -1;
	} else {
		*(s16*)(particlePayload + 0x22) = life;
	}
	*(u8*)(particlePayload + 0x58) = 0;

	if (worldMat != NULL) {
		switch (payload[0xEC]) {
		case 1:
			PSMTXCopy(work->m_worldMatrix, *(PARTICLE_WMAT*)worldMat);
			break;
		case 2:
			PSMTXCopy(pObject->m_localMatrix.value, *(PARTICLE_WMAT*)worldMat);
			break;
		default:
			break;
		}
	}

	if (colorData != NULL) {
		colorData->m_colorFrameDeltas[0] = *(float*)(payload + 0x2C);
		colorData->m_colorFrameDeltas[1] = *(float*)(payload + 0x30);
		colorData->m_colorFrameDeltas[2] = *(float*)(payload + 0x34);
		colorData->m_colorFrameDeltas[3] = *(float*)(payload + 0x38);
	}
}
