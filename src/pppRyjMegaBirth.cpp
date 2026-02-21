#include "ffcc/pppRyjMegaBirth.h"
#include "ffcc/math.h"
#include <string.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" float RandF__5CMathFv(CMath*);
extern s32 DAT_8032ed70;
extern float FLOAT_80330448;
extern float FLOAT_80330458;
extern float FLOAT_8033045c;
extern float FLOAT_80330460;
extern CMath Math;

static Mtx g_matUnit;

static char s_pppRyjMegaBirth_cpp[] = "pppRyjMegaBirth.cpp";

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_rand()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void get_noise(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void alloc_check(VRyjMegaBirth*, PRyjMegaBirth*)
{
	// TODO
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
    float halfSpeed;
    float directionSpeed;
    float randomYaw;
    float randomPitch;
    float randomRoll;
    s16 life;

    payload = (u8*)param;
    particlePayload = (u8*)particle;

    memset(particle, 0, 0x60);
    if (worldMat != NULL) {
        memset(worldMat, 0, 0x30);
    }
    if (colorData != NULL) {
        memset(colorData, 0, 0x20);
    }

    directionSpeed = *(float*)(payload + 0x94);
    halfSpeed = directionSpeed * 0.5f;
    randomYaw = RandF__5CMathFv(&Math) * directionSpeed - halfSpeed;
    randomPitch = RandF__5CMathFv(&Math) * directionSpeed - halfSpeed;
    randomRoll = RandF__5CMathFv(&Math) * directionSpeed - halfSpeed;

    particle->m_velocity.x = randomYaw * *(float*)(payload + 0xA0);
    particle->m_velocity.y = randomPitch * *(float*)(payload + 0xA4);
    particle->m_velocity.z = randomRoll * *(float*)(payload + 0xA8);

    particle->m_directionTail.x = *(float*)(payload + 0x90);
    particle->m_directionTail.y = *(float*)(payload + 0x94);
    particle->m_directionTail.z = *(float*)(payload + 0x98);
    particle->m_colorDeltaAdd[0] = *(float*)(payload + 0x9C);
    particle->m_colorDeltaAdd[1] = *(float*)(payload + 0xA0);

    particle->m_matrix[2][2] = *(float*)(payload + 0x90);
    particle->m_matrix[2][3] = *(float*)(payload + 0x94);
    particle->m_sizeStart = *(float*)(payload + 0xAC);
    particle->m_sizeVal = *(float*)(payload + 0xB0);
    particle->m_sizeEnd = *(float*)(payload + 0xB4);

    life = *(s16*)(payload + 0x96);
    if (life == 0) {
        *(s16*)(particlePayload + 0x22) = -1;
    } else {
        *(s16*)(particlePayload + 0x22) = life;
    }
    *(u16*)(particlePayload + 0x1C) = 0;
    *(u16*)(particlePayload + 0x1E) = 0;
    *(u16*)(particlePayload + 0x20) = 0;
    *(u8*)(particlePayload + 0x58) = 0;

    if (*(u8*)(payload + 0x8E) != 0) {
        *(u8*)(particlePayload + 0x59) = *(u8*)(payload + 0x8E);
        particle->m_sizeEnd = (float)color->m_alpha;
    }

    if (worldMat != NULL) {
        switch (payload[0x8B]) {
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
        colorData->m_colorFrameDeltas[0] = *(float*)(payload + 0xC0);
        colorData->m_colorFrameDeltas[1] = *(float*)(payload + 0xC4);
        colorData->m_colorFrameDeltas[2] = *(float*)(payload + 0xC8);
        colorData->m_colorFrameDeltas[3] = *(float*)(payload + 0xCC);
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
	s32 alpha;
	u8* paramPayload;
	u8* particlePayload;
	u8 fadeOutFrames;
	float particleAngle;

	alpha = (u8)((u8*)vColor)[0xB];
	paramPayload = (u8*)param;
	particlePayload = (u8*)particle;

	if (colorData != 0)
	{
		colorData->m_color[0] = colorData->m_color[0] + colorData->m_colorFrameDeltas[0];
		colorData->m_color[1] = colorData->m_color[1] + colorData->m_colorFrameDeltas[1];
		colorData->m_color[2] = colorData->m_color[2] + colorData->m_colorFrameDeltas[2];
		colorData->m_color[3] = colorData->m_color[3] + colorData->m_colorFrameDeltas[3];
		colorData->m_colorFrameDeltas[0] = colorData->m_colorFrameDeltas[0] + param->m_colorDeltaAdd[0];
		colorData->m_colorFrameDeltas[1] = colorData->m_colorFrameDeltas[1] + param->m_colorDeltaAdd[1];
		colorData->m_colorFrameDeltas[2] = colorData->m_colorFrameDeltas[2] + param->m_colorDeltaAdd[2];
		colorData->m_colorFrameDeltas[3] = colorData->m_colorFrameDeltas[3] + param->m_colorDeltaAdd[3];
			alpha = alpha + (s32)colorData->m_color[3];
			if (0xFF < alpha)
			{
				alpha = 0xFF;
			}
	}

	*(float*)(particlePayload + 0x28) = *(float*)(particlePayload + 0x28) + *(float*)(particlePayload + 0x2C);
	if ((paramPayload[0x8B] & 0x10) == 0)
	{
		*(float*)(particlePayload + 0x2C) = *(float*)(particlePayload + 0x2C) + *(float*)(paramPayload + 0x98);
	}
	else
	{
		*(float*)(particlePayload + 0x2C) = *(float*)(particlePayload + 0x2C) +
			*(float*)(paramPayload + 0x98) + *(float*)(particlePayload + 0x3C);
	}

	particleAngle = *(float*)(particlePayload + 0x28);
	while (FLOAT_8033045c <= particleAngle)
	{
		particleAngle = particleAngle - FLOAT_80330458;
	}
	while (particleAngle < FLOAT_80330460)
	{
		particleAngle = particleAngle + FLOAT_80330458;
	}
	*(float*)(particlePayload + 0x28) = particleAngle;

	*(float*)(particlePayload + 0x40) = *(float*)(particlePayload + 0x40) + *(float*)(particlePayload + 0x48);
	*(float*)(particlePayload + 0x44) = *(float*)(particlePayload + 0x44) + *(float*)(particlePayload + 0x4C);

	if ((paramPayload[0x8A] & 0x10) == 0)
	{
		*(float*)(particlePayload + 0x48) = *(float*)(particlePayload + 0x48) + *(float*)(paramPayload + 0x84);
		*(float*)(particlePayload + 0x4C) = *(float*)(particlePayload + 0x4C) + *(float*)(paramPayload + 0x88);
	}
	else
	{
		*(float*)(particlePayload + 0x48) = *(float*)(particlePayload + 0x48) +
			*(float*)(paramPayload + 0x84) + *(float*)(particlePayload + 0x50);
		*(float*)(particlePayload + 0x4C) = *(float*)(particlePayload + 0x4C) +
			*(float*)(paramPayload + 0x88) + *(float*)(particlePayload + 0x54);
	}

	*(float*)(particlePayload + 0x58) = *(float*)(particlePayload + 0x58) + *(float*)(paramPayload + 0xA8);
	if ((s8)paramPayload[0x8E] == 0)
	{
		if ((*(float*)(paramPayload + 0xAC) <= FLOAT_80330448) || (FLOAT_80330448 <= *(float*)(paramPayload + 0xA8)))
		{
			if ((*(float*)(paramPayload + 0xAC) < FLOAT_80330448) &&
				((FLOAT_80330448 < *(float*)(paramPayload + 0xA8)) &&
				 (FLOAT_80330448 < *(float*)(particlePayload + 0x58))))
			{
				*(float*)(particlePayload + 0x58) = FLOAT_80330448;
			}
		}
		else if (*(float*)(particlePayload + 0x58) < FLOAT_80330448)
		{
			*(float*)(particlePayload + 0x58) = FLOAT_80330448;
		}
	}

	fadeOutFrames = *(u8*)(particlePayload + 0x59);
	*(u8*)(particlePayload + 0x58) = *(u8*)(particlePayload + 0x58) + 1;
	if ((fadeOutFrames != 0) && (*(u8*)(particlePayload + 0x58) <= fadeOutFrames))
	{
		*(float*)(particlePayload + 0x5C) =
			*(float*)(particlePayload + 0x5C) - ((float)alpha / (float)fadeOutFrames);
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
	s32 i;
	s32 emitCount;
	s32 maxParticles;
	_PARTICLE_COLOR* colorData;
	PARTICLE_WMAT* worldMats;
	_PARTICLE_DATA* particle;
	u8* paramPayload;
	u16* particleLife;
	u16* particleFrameTimer;
	u16* particleFrameIndex;
	u16* emitRate;
	u16* emitPerFrame;

	emitCount = 0;
	particle = (_PARTICLE_DATA*)work->m_particleBlock;
	worldMats = work->m_worldMatrixBlock;
	colorData = work->m_colorBlock;
	maxParticles = work->m_numParticles;
	paramPayload = (u8*)param;
	emitRate = (u16*)(paramPayload + 0xB4);
	emitPerFrame = (u16*)(paramPayload + 0xB6);

	if ((DAT_8032ed70 == 0) && (paramPayload[0x16] != 0))
	{
		work->m_emitTimer = work->m_emitTimer + 1;

		for (i = 0; i < maxParticles; i = i + 1)
		{
			particleLife = (u16*)((u8*)particle + 0x22);
			particleFrameTimer = (u16*)((u8*)particle + 0x1C);
			particleFrameIndex = (u16*)((u8*)particle + 0x1E);

			if (*(s16*)particleLife == 0)
			{
				if ((*emitRate <= work->m_emitTimer) && (emitCount < (s32)(*emitPerFrame)))
				{
					birth(pObject, work, param, color, particle, (_PARTICLE_WMAT*)worldMats, colorData);
					emitCount = emitCount + 1;
				}
			}
			else
			{
				calc(work, param, particle, color, colorData);

				frame = *(u16*)((u8*)particle + 0x1E);
				colorSet = **(s32**)(*(s32*)&pppEnvStPtr->m_particleColors[0] +
				                     (s32)paramPayload[0x05] * 4);
				*(u16*)((u8*)particle + 0x20) = frame;
				frameData = colorSet + (u32)frame * 8 + 0x10;

				*(s16*)((u8*)particle + 0x1C) = *(s16*)((u8*)particle + 0x1C) + *(s16*)(paramPayload + 0x08);
				frame = *particleFrameTimer;
				duration = *(s16*)(frameData + 2);

				if ((s32)duration <= (s32)frame)
				{
					*particleFrameTimer = frame - duration;
					*particleFrameIndex = *particleFrameIndex + 1;

					if ((s32)*(s16*)(colorSet + 6) <= (s32)(*particleFrameIndex))
					{
						if ((*(u8*)(frameData + 4) & 0x80) == 0)
						{
							*particleFrameTimer = 0;
							*particleFrameIndex = *particleFrameIndex - 1;
						}
						else
						{
							*particleFrameIndex = 0;
							*particleFrameTimer = 0;
						}
					}
				}
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
	bool hasRequiredMemory;
	u8* payload = (u8*)particleData;
	s32 colorOffset = offsets->m_serializedDataOffsets[1];
	VRyjMegaBirth* work =
		(VRyjMegaBirth*)((u8*)pObject + 8 + offsets->m_serializedDataOffsets[2]);

	if (work->m_particleBlock == 0)
	{
		work->m_numParticles = *(u16*)(payload + 0xC);

		work->m_particleBlock = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
			work->m_numParticles * 0x60, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x262);
		if (work->m_particleBlock != 0)
		{
			memset(work->m_particleBlock, 0, work->m_numParticles * 0x60);
		}

		if ((payload[0xD8] == 1) || (payload[0xD8] == 2))
		{
			work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles * 0x30, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x269);
			if (work->m_worldMatrixBlock != 0)
			{
				memset(work->m_worldMatrixBlock, 0, work->m_numParticles * 0x30);
			}
		}

		if (payload[0xD5] != 0)
		{
			work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
				work->m_numParticles << 5, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirth_cpp, 0x271);
			if (work->m_colorBlock != 0)
			{
				memset(work->m_colorBlock, 0, work->m_numParticles << 5);
			}
		}

		work->m_accelerationAxis.x = *(float*)(payload + 0x9C);
		work->m_accelerationAxis.y = *(float*)(payload + 0xA0);
		work->m_accelerationAxis.z = *(float*)(payload + 0xA4);
		PSVECNormalize(&work->m_accelerationAxis, &work->m_accelerationAxis);
	}

	if (work->m_particleBlock == 0)
	{
		hasRequiredMemory = false;
	}
	else if (((payload[0xD8] == 1) || (payload[0xD8] == 2)) && (work->m_worldMatrixBlock == 0))
	{
		hasRequiredMemory = false;
	}
	else if ((payload[0xD5] == 0) || (work->m_colorBlock != 0))
	{
		hasRequiredMemory = true;
	}
	else
	{
		hasRequiredMemory = false;
	}

	if (hasRequiredMemory)
	{
		switch (payload[0x16])
		{
		default:
			PSMTXCopy(pppMngStPtr->m_matrix.value, work->m_worldMatrix);
			break;
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
		}

		calc_particle(
			pObject, work, particleData, (VColor*)((u8*)pObject + 8 + colorOffset));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void init_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void set_matrix(_pppPObject*, pppFMATRIX&, PRyjMegaBirth*, VRyjMegaBirth*, _PARTICLE_DATA*, _PARTICLE_WMAT*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRyjDrawMegaBirth(void)
{
	// TODO
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
	u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];

	PSMTXIdentity(*(Mtx*)work);
	*(f32*)(work + 0x30) = 0.0f;
	*(f32*)(work + 0x34) = 0.0f;
	*(f32*)(work + 0x38) = 0.0f;
	*(void**)(work + 0x3C) = 0;
	*(void**)(work + 0x40) = 0;
	*(void**)(work + 0x44) = 0;
	*(void**)(work + 0x48) = 0;
	*(u16*)(work + 0x4C) = 0;
	*(u16*)(work + 0x4E) = 0;
	*(u16*)(work + 0x4C) = 10000;

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
	u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];

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
