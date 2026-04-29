#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/partMng.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppRyjMegaBirthZero;
extern int gPppCalcDisabled;
}
#include <string.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern float FLOAT_80330458;
extern float FLOAT_8033045c;
extern float FLOAT_80330460;
extern float FLOAT_80330470;
extern float FLOAT_80330474;
extern float FLOAT_80330478;
extern double DOUBLE_80330488;
extern float FLOAT_80330490;

static Mtx g_matUnit;

extern "C" const char s_pppRyjMegaBirth_cpp_801D9C00[] = "pppRyjMegaBirth.cpp";

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

static inline float calc_spawn_speed(float speed, u8 mode)
{
	float halfSpeed = FLOAT_80330478 * speed;

	switch (mode) {
	case 1:
		(void)Math.RandF();
		return speed * Math.RandF() - halfSpeed;
	case 2:
		return speed * Math.RandF() * Math.RandF() - halfSpeed;
	case 3:
		return -(FLOAT_80330474 * (speed * Math.RandF() * Math.RandF()) - speed) - halfSpeed;
	case 4:
		return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speed - halfSpeed;
	case 5:
		return -(FLOAT_80330478 * (Math.RandF() * (speed * Math.RandF() * Math.RandF())) - speed) - halfSpeed;
	default:
		return speed * Math.RandF() - halfSpeed;
	}
}

static inline signed char random_signed_byte_span(u8 span)
{
	return (signed char)((s32)((float)(span << 1) * Math.RandF() - (float)(span >> 1)));
}

static inline void apply_signed_randomization_2(u8* particle, s32 offset, u8 flags)
{
	if (((flags & 1) != 0) && ((flags & 2) != 0)) {
		if (DOUBLE_80330488 < (double)Math.RandF()) {
			*f32_at(particle, offset) = *f32_at(particle, offset) * FLOAT_80330490;
		}
		if (DOUBLE_80330488 < (double)Math.RandF()) {
			*f32_at(particle, offset + 4) = *f32_at(particle, offset + 4) * FLOAT_80330490;
		}
	} else if ((flags & 2) != 0) {
		*f32_at(particle, offset) = *f32_at(particle, offset) * FLOAT_80330490;
		*f32_at(particle, offset + 4) = *f32_at(particle, offset + 4) * FLOAT_80330490;
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
	u8 mode;
	float speed;
	s16 life;

	payload = (u8*)param;
	particlePayload = (u8*)particle;
	mode = payload[0x2A];

	memset(particle, 0, 0x60);
	if (worldMat != NULL) {
		memset(worldMat, 0, 0x30);
	}
	if (colorData != NULL) {
		memset(colorData, 0, 0x20);
	}

	if (mode < 8) {
		Vec baseDirection;
		Vec* direction;
		pppIVECTOR4 angle;
		pppFMATRIX rot;
		float spread;
		float range;

		baseDirection.x = *f32_at(payload, 0xA0);
		baseDirection.y = *f32_at(payload, 0xA4);
		baseDirection.z = *f32_at(payload, 0xA8);
		spread = (float)payload[0x2B];
		range = FLOAT_80330470 * spread;

		angle.x = (s16)(range * Math.RandF() - spread);
		angle.y = (s16)(range * Math.RandF() - spread);
		angle.z = (s16)(range * Math.RandF() - spread);
		angle.w = 0;

		if ((mode == 2) || (mode == 3)) {
			angle.x = 0;
			angle.y = 0;
			angle.z = 0;
			angle.w = 0;
		}

		pppGetRotMatrixXYZ(rot, &angle);
		direction = (Vec*)(particlePayload + 0x10);
		PSMTXMultVecSR(rot.value, &baseDirection, direction);
		direction->x = direction->x * *f32_at(payload, 0xB0);
		direction->y = direction->y * *f32_at(payload, 0xB4);
		direction->z = direction->z * *f32_at(payload, 0xB8);
		PSVECNormalize(direction, direction);
	}

	speed = *f32_at(payload, 0xBC);
	if (speed != kPppRyjMegaBirthZero) {
		u8 speedMode = payload[0xE8];

		if (mode < 6) {
			*f32_at(particlePayload, 0x00) = calc_spawn_speed(speed, speedMode) * *f32_at(payload, 0xB0);
			*f32_at(particlePayload, 0x04) = calc_spawn_speed(speed, speedMode) * *f32_at(payload, 0xB4);
			*f32_at(particlePayload, 0x08) = calc_spawn_speed(speed, speedMode) * *f32_at(payload, 0xB8);
		} else if (mode >= 10) {
			Vec* direction = (Vec*)(particlePayload + 0x10);
			Vec* position = (Vec*)particlePayload;
			PSVECScale(direction, position, calc_spawn_speed(speed, speedMode));
		}
	}

	*u8_at(particlePayload, 0x21) = random_signed_byte_span(payload[0x58]);
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
			if (DOUBLE_80330488 < (double)Math.RandF()) {
				*f32_at(particlePayload, 0x30) = *f32_at(particlePayload, 0x30) * FLOAT_80330490;
			}
		} else if ((payload[0xEB] & 2) != 0) {
			*f32_at(particlePayload, 0x30) = *f32_at(particlePayload, 0x30) * FLOAT_80330490;
		}
	}
	if ((payload[0xEB] & 4) != 0) {
		*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + *f32_at(particlePayload, 0x30);
	}
	if ((payload[0xEB] & 8) != 0) {
		*f32_at(particlePayload, 0x2C) = *f32_at(particlePayload, 0x2C) + *f32_at(particlePayload, 0x30);
	}
	{
		float angleWrap = FLOAT_80330458;
		float angleMax = FLOAT_8033045c;
		while (angleMax <= *f32_at(particlePayload, 0x28)) {
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) - angleWrap;
		}
	}
	{
		float angleWrap = FLOAT_80330458;
		float angleMin = FLOAT_80330460;
		while (*f32_at(particlePayload, 0x28) < angleMin) {
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + angleWrap;
		}
	}

	*f32_at(particlePayload, 0x34) = *f32_at(payload, 0x60);
	*f32_at(particlePayload, 0x38) = *f32_at(payload, 0x5C);
	*f32_at(particlePayload, 0x3C) = *f32_at(payload, 0x68);
	*f32_at(particlePayload, 0x40) = *f32_at(payload, 0x6C);

	if (payload[0xEA] != 0) {
		if ((payload[0xEA] & 0x20) == 0) {
			*f32_at(particlePayload, 0x44) = *f32_at(payload, 0x78) * Math.RandF();
			*f32_at(particlePayload, 0x48) = *f32_at(payload, 0x7C) * Math.RandF();
		} else {
			float randomRotation = *f32_at(payload, 0x78) * Math.RandF();
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
			*f32_at(particlePayload, 0x4C) + FLOAT_80330470 * *f32_at(payload, 0xC8) * Math.RandF() -
			*f32_at(payload, 0xC8);
	}

	life = *(s16*)(payload + 0x26);
	if (life == 0) {
		*(s16*)(particlePayload + 0x22) = -1;
	} else {
		*(s16*)(particlePayload + 0x22) = life;
	}
	*(u16*)(particlePayload + 0x1C) = 0;
	*(u16*)(particlePayload + 0x1E) = 0;
	*(u16*)(particlePayload + 0x20) = 0;
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
		float angleWrap = FLOAT_80330458;
		float angleMax = FLOAT_8033045c;
		while (angleMax <= *f32_at(particlePayload, 0x28))
		{
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) - angleWrap;
		}
	}
	{
		float angleWrap = FLOAT_80330458;
		float angleMin = FLOAT_80330460;
		while (*f32_at(particlePayload, 0x28) < angleMin)
		{
			*f32_at(particlePayload, 0x28) = *f32_at(particlePayload, 0x28) + angleWrap;
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
			float zero = kPppRyjMegaBirthZero;
			if ((*f32_at(paramPayload, 0xC0) < zero) && (zero < *f32_at(paramPayload, 0xC4)) &&
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
	u8* paramPayload;

	emitCount = 0;
	particle = (_PARTICLE_DATA*)work->m_particleBlock;
	worldMats = work->m_worldMatrixBlock;
	colorData = work->m_colorBlock;
	maxParticles = work->m_numParticles;
	paramPayload = (u8*)param;

	if ((gPppCalcDisabled == 0) && (*(s32*)(paramPayload + 4) != 0xFFFF))
	{
		work->m_emitTimer = work->m_emitTimer + 1;

		for (i = 0; i < maxParticles; i = i + 1)
		{
			if (*(u16*)((u8*)particle + 0x22) != 0)
			{
				calc(work, param, particle, color, colorData);

				frame = *(u16*)((u8*)particle + 0x1E);
				colorSet = (s32)**(s32***)(*(s32*)&pppEnvStPtr->m_particleColors[0] + *(s32*)(paramPayload + 4) * 4);
				*(u16*)((u8*)particle + 0x20) = frame;
				frameData = colorSet + (u32)frame * 8 + 0x10;

				*(u16*)((u8*)particle + 0x1C) = *(u16*)((u8*)particle + 0x1C) + *(u32*)(paramPayload + 0x08);
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
			else if ((*(u16*)(paramPayload + 0x24) <= work->m_emitTimer) &&
			         (emitCount < (s32)*(u16*)(paramPayload + 0x22)))
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
	u8* particleDataBytes;
	s32* serializedDataOffsets;
	s32 workOffset;
	s32 colorOffset;
	VRyjMegaBirth* work;
	VColor* color;

	particleDataBytes = (u8*)particleData;
	serializedDataOffsets = offsets->m_serializedDataOffsets;
	workOffset = serializedDataOffsets[2];
	colorOffset = serializedDataOffsets[1];
	work = (VRyjMegaBirth*)((u8*)pObject + 0x80 + workOffset);
	color = (VColor*)((u8*)pObject + 0x80 + colorOffset);

	if (work->m_particleBlock == NULL)
	{
		work->m_numParticles = *(u16*)(particleDataBytes + 0x20);
		work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			work->m_numParticles * 0x60, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp_801D9C00), 0x262);
		if (work->m_particleBlock != NULL)
		{
			memset(work->m_particleBlock, 0, work->m_numParticles * 0x60);
		}

		if ((particleDataBytes[0xEC] == 1) || (particleDataBytes[0xEC] == 2))
		{
			work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles * 0x30, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp_801D9C00), 0x269);
			if (work->m_worldMatrixBlock != NULL)
			{
				memset(work->m_worldMatrixBlock, 0, work->m_numParticles * 0x30);
			}
		}

		if (particleDataBytes[0xE9] != 0)
		{
			work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles << 5, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirth_cpp_801D9C00), 0x271);
			if (work->m_colorBlock != NULL)
			{
				memset(work->m_colorBlock, 0, work->m_numParticles << 5);
			}
		}

		work->m_accelerationAxis.x = *(float*)(particleDataBytes + 0xB0);
		work->m_accelerationAxis.y = *(float*)(particleDataBytes + 0xB4);
		work->m_accelerationAxis.z = *(float*)(particleDataBytes + 0xB8);
		PSVECNormalize(&work->m_accelerationAxis, &work->m_accelerationAxis);
	}

	if (work->m_particleBlock == NULL)
	{
		hasRequiredMemory = 0;
	}
	else if (((particleDataBytes[0xEC] == 1) || (particleDataBytes[0xEC] == 2)) &&
	         (work->m_worldMatrixBlock == NULL))
	{
		hasRequiredMemory = 0;
	}
	else if ((particleDataBytes[0xE9] != 0) && (work->m_colorBlock == NULL))
	{
		hasRequiredMemory = 0;
	}
	else
	{
		hasRequiredMemory = 1;
	}

	if (hasRequiredMemory)
	{
		switch (particleDataBytes[0x2A])
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
			PSMTXIdentity(work->m_worldMatrix);
			work->m_worldMatrix[0][0] = pppMngStPtr->m_scale.x;
			work->m_worldMatrix[1][1] = pppMngStPtr->m_scale.y;
			work->m_worldMatrix[2][2] = pppMngStPtr->m_scale.z;
			work->m_worldMatrix[0][3] = pppMngStPtr->m_position.x;
			work->m_worldMatrix[1][3] = pppMngStPtr->m_position.y;
			work->m_worldMatrix[2][3] = pppMngStPtr->m_position.z;
			break;
		default:
			PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_worldMatrix);
			break;
		}

		calc_particle(pObject, work, particleData, color);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
static inline void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirth* params, VRyjMegaBirth* work)
{
	u8* payload = (u8*)params;
	u8 mode = payload[0x2A];

	if ((mode == 1) || (mode == 3) || (mode == 5) || (mode == 7) || (mode == 9)) {
		PSMTXIdentity(out.value);
		out.value[0][0] = pppMngStPtr->m_scale.x;
		out.value[1][1] = pppMngStPtr->m_scale.y;
		out.value[2][2] = pppMngStPtr->m_scale.z;
		out.value[0][3] = pppMngStPtr->m_position.x;
		out.value[1][3] = pppMngStPtr->m_position.y;
		out.value[2][3] = pppMngStPtr->m_position.z;
	} else {
		PSMTXCopy(pppMngStPtr->m_matrix.value, out.value);
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
	VRyjMegaBirth* work = (VRyjMegaBirth*)(obj->m_workArea + ctrlTable->m_serializedDataOffsets[2]);
	u8* payload = (u8*)params;
	int dataValIndex = *(int*)(payload + 4);

	if ((dataValIndex == 0xFFFF) || (work->m_particleBlock == 0)) {
		return;
	}

	if (((payload[0xEC] == 1) || (payload[0xEC] == 2)) && (work->m_worldMatrixBlock == 0)) {
		return;
	}

	if ((payload[0xE9] != 0) && (work->m_colorBlock == 0)) {
		return;
	}

	long* animData = **(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
	if (animData == 0) {
		return;
	}

	pppInitBlendMode();
	pppSetBlendMode(0);

	for (int i = 0; i < work->m_numParticles; i++) {
		_PARTICLE_DATA* particle = (_PARTICLE_DATA*)((u8*)work->m_particleBlock + i * 0x60);
		_PARTICLE_WMAT* particleWorldMat = 0;
		_PARTICLE_COLOR* colorData = 0;

		if (*s16_at(particle, 0x22) == 0) {
			continue;
		}

		if (work->m_worldMatrixBlock != 0) {
			particleWorldMat = (_PARTICLE_WMAT*)(work->m_worldMatrixBlock + i);
		}
		if (work->m_colorBlock != 0) {
			colorData = work->m_colorBlock + i;
		}

		pppFMATRIX drawMatrix;
		pppCVECTOR drawColor = {{0xFF, 0xFF, 0xFF, clamp_u8(*f32_at(particle, 0x54))}};

		if (colorData != 0) {
			drawColor.rgba[0] = clamp_u8(colorData->m_color[0]);
			drawColor.rgba[1] = clamp_u8(colorData->m_color[1]);
			drawColor.rgba[2] = clamp_u8(colorData->m_color[2]);
		}

		set_matrix(obj, drawMatrix, params, work, particle, particleWorldMat);
		pppSetDrawEnv(&drawColor, &drawMatrix, 0.0f, 0, 0, 0, 0, 1, 1, 0);
		pppDrawShp(animData, *s16_at(particle, 0x20), pppEnvStPtr->m_materialSetPtr, 0);
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
 * PAL Address: 0x80082278
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthDes(_pppPObject* pObject, PRyjMegaBirthOffsets* offsets)
{
	u8* work = pObject->m_workArea + offsets->m_serializedDataOffsets[2];

	if (*(void**)(work + 0x3C) != 0)
	{
		pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x3C));
		*(void**)(work + 0x3C) = 0;
	}

	if (*(void**)(work + 0x40) != 0)
	{
		pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x40));
		*(void**)(work + 0x40) = 0;
	}

	if (*(void**)(work + 0x44) != 0)
	{
		pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x44));
		*(void**)(work + 0x44) = 0;
	}
}
