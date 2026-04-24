#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include <string.h>
#include "ffcc/ppp_linkage.h"

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);

extern float FLOAT_80330498;
extern float FLOAT_8033049c;
extern float FLOAT_803304a0;
extern float FLOAT_803304a4;
extern float FLOAT_803304a8;
extern float FLOAT_803304b4;
extern float FLOAT_803304bc;
extern float FLOAT_803304c0;
extern float FLOAT_803304c4;
extern float FLOAT_803304c8;

PARTICLE_WMAT g_matKeep;
PARTICLE_WMAT g_matTmp;

static const char s_pppRyjMegaBirthModel_cpp_801d9c18[] = "pppRyjMegaBirthModel.cpp";

static inline float* f32_at(void* base, s32 off)
{
    return (float*)((u8*)base + off);
}

static inline s16* s16_at(void* base, s32 off)
{
    return (s16*)((u8*)base + off);
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

static float calc_spawn_speed(float speedMag, u8 speedMode)
{
    switch (speedMode) {
    case 1:
        (void)Math.RandF();
        return Math.RandF() * speedMag;
    case 2:
        return Math.RandF() * Math.RandF() * speedMag;
    case 3:
        return -(Math.RandF() * Math.RandF() * speedMag - speedMag);
    case 4:
        return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speedMag;
    case 5:
        return -(Math.RandF() * Math.RandF() * Math.RandF() * speedMag - speedMag);
    default:
        return Math.RandF() * speedMag;
    }
}

static void orthonormalize_particle_matrix(_PARTICLE_DATA* particleData)
{
    pppFMATRIX model;
    Vec rowX;
    Vec rowY;
    Vec rowZ;
    Vec rowPos;

    PSMTXCopy(particleData->m_matrix, model.value);
    pppGetRowVector(model, rowX, rowY, rowZ, rowPos);
    pppNormalize(rowY, rowY);
    pppOuterProduct(rowZ, rowY, rowX);
    pppNormalize(rowZ, rowZ);
    pppOuterProduct(rowX, rowZ, rowY);
    pppNormalize(rowX, rowX);
    pppSetRowVector(model, rowX, rowY, rowZ, rowPos);
    PSMTXCopy(model.value, particleData->m_matrix);
}

static void wrap_particle_rotation_triplet(u8* particleBytes, s32 offset)
{
    for (int i = 0; i < 3; i++) {
        float* value = f32_at(particleBytes, offset + i * 4);
        while ((s32)*value > 0x7FFF) {
            *value = (float)((s32)*value - 0x10000);
        }
        while ((s32)*value < -0x8000) {
            *value = (float)((s32)*value + 0x10000);
        }
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void get_rand(void)
{
    (void)Math.RandF();
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void get_noise(unsigned char count)
{
    while (count > 0) {
        (void)Math.RandF();
        count--;
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void alloc_check(VRyjMegaBirthModel* work, PRyjMegaBirthModel* params)
{
    u8* payload = (u8*)params;
    if (work->m_particleBlock == NULL) {
        work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_numParticles * 0xA0, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirthModel_cpp_801d9c18), 0x8D);
        if (work->m_particleBlock != NULL) {
            memset(work->m_particleBlock, 0, work->m_numParticles * 0xA0);
        }
    }

    if ((payload[0x136] != 0) && (work->m_worldMatrixBlock == NULL)) {
        work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_numParticles * 0x30, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirthModel_cpp_801d9c18), 0x97);
        if (work->m_worldMatrixBlock != NULL) {
            memset(work->m_worldMatrixBlock, 0, work->m_numParticles * 0x30);
        }
    }

    if ((payload[0x131] != 0) && (work->m_colorBlock == NULL)) {
        work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            work->m_numParticles << 5, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppRyjMegaBirthModel_cpp_801d9c18), 0xA2);
        if (work->m_colorBlock != NULL) {
            memset(work->m_colorBlock, 0, work->m_numParticles << 5);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80087ce8
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModel(_pppPObject* pObject, PRyjMegaBirthModel* params, PRyjMegaBirthModelOffsets* offsets)
{
    float posX;
    float posY;
    float posZ;
    bool hasRequiredMemory;
    s32 colorOffset = offsets->m_serializedDataOffsets[1];
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];
    u8* payload = (u8*)params;

    if (*(void**)(work + 0xC) == 0) {
        ((VRyjMegaBirthModel*)work)->m_numParticles = *(u16*)(payload + 0x20);
        alloc_check((VRyjMegaBirthModel*)work, params);

        *(float*)(work + 0x0) = *(float*)(payload + 0xF8);
        *(float*)(work + 0x4) = *(float*)(payload + 0xFC);
        *(float*)(work + 0x8) = *(float*)(payload + 0x100);
        PSVECNormalize((Vec*)(work + 0x0), (Vec*)(work + 0x0));

        posX = *f32_at(pObject, 0x1C);
        posY = *f32_at(pObject, 0x2C);
        posZ = *f32_at(pObject, 0x3C);
        *(float*)(work + 0x20) = posX;
        *(float*)(work + 0x24) = posY;
        *(float*)(work + 0x28) = posZ;
        *(float*)(work + 0x2C) = posX;
        *(float*)(work + 0x30) = posY;
        *(float*)(work + 0x34) = posZ;
    }

    if (*(void**)(work + 0xC) == 0) {
        hasRequiredMemory = false;
    } else {
        if ((*(u8*)(payload + 0x136) == 0) || (*(void**)(work + 0x10) != 0)) {
            if ((*(u8*)(payload + 0x131) == 0) || (*(void**)(work + 0x14) != 0)) {
                hasRequiredMemory = true;
            } else {
                hasRequiredMemory = false;
            }
        } else {
            hasRequiredMemory = false;
        }
    }

    if (hasRequiredMemory) {
        calc_particle(pObject, (VRyjMegaBirthModel*)work, params, (VColor*)((u8*)pObject + 0x80 + colorOffset));
    }
}

/*
 * --INFO--
 * PAL Address: 0x80087bac
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc_particle(_pppPObject* pObject, VRyjMegaBirthModel* work, PRyjMegaBirthModel* params, VColor* color)
{
    s32 i;
    s32 emitted;
    s32 maxParticles;
    u8* payload;
    _PARTICLE_DATA* particleData;
    _PARTICLE_WMAT* particleWMat;
    _PARTICLE_COLOR* particleColor;
    u16* emitTimer;

    emitted = 0;
    payload = (u8*)params;
    particleData = *(_PARTICLE_DATA**)((u8*)work + 0xC);
    particleWMat = *(_PARTICLE_WMAT**)((u8*)work + 0x10);
    particleColor = *(_PARTICLE_COLOR**)((u8*)work + 0x14);
    maxParticles = *(s32*)((u8*)work + 0x18);
    emitTimer = (u16*)((u8*)work + 0x1C);

    if (gPppCalcDisabled == 0) {
        *(float*)((u8*)work + 0x20) = *(float*)((u8*)work + 0x2C);
        *(float*)((u8*)work + 0x24) = *(float*)((u8*)work + 0x30);
        *(float*)((u8*)work + 0x28) = *(float*)((u8*)work + 0x34);
        *(float*)((u8*)work + 0x2C) = pObject->m_localMatrix.value[0][3];
        *(float*)((u8*)work + 0x30) = pObject->m_localMatrix.value[1][3];
        *(float*)((u8*)work + 0x34) = pObject->m_localMatrix.value[2][3];
        *emitTimer = *emitTimer + 1;

        for (i = 0; i < maxParticles; i = i + 1) {
            if (*(s16*)&particleData->m_directionTail.x == 0) {
                if ((*(u16*)(payload + 0x24) <= *emitTimer) && (emitted < (s32)(u32)*(u16*)(payload + 0x22))) {
                    birth(pObject, work, params, color, particleData, particleWMat, particleColor);
                    emitted = emitted + 1;
                }
            } else {
                calc(pObject, work, params, particleData, color, particleColor);
            }

            if (particleWMat != NULL) {
                particleWMat = (_PARTICLE_WMAT*)((u8*)particleWMat + 0x30);
            }
            if (particleColor != NULL) {
                particleColor = particleColor + 1;
            }
            particleData = (_PARTICLE_DATA*)((u8*)particleData + 0xA0);
        }

        if (emitted > 0) {
            *emitTimer = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80085fd0
 * PAL Size: 7128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(
    _pppPObject* pObject, VRyjMegaBirthModel* work, PRyjMegaBirthModel* params, VColor* color,
    _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    u8* payload = (u8*)params;
    u8 mode = payload[0x2A];
    float spread = (float)payload[0x2B];
    float halfSpread = spread;
    float randomRange = FLOAT_803304c0 * spread;
    float speedMag = *(float*)(payload + 0x130);
    u8 speedMode = payload[0x130];
    Vec pos;

    memset(particleData, 0, 0xA0);
    if (particleWMat != NULL) {
        memset(particleWMat, 0, 0x30);
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, 0x20);
    }

    pppUnitMatrix(*(pppFMATRIX*)&particleData->m_matrix);

    pos.x = pObject->m_localMatrix.value[0][3];
    pos.y = pObject->m_localMatrix.value[1][3];
    pos.z = pObject->m_localMatrix.value[2][3];

    if (mode < 8) {
        float baseDirectionX = *(float*)(payload + 0x48);
        float baseDirectionY = *(float*)(payload + 0x4C);
        float baseDirectionZ = *(float*)(payload + 0x50);
        float randX = (FLOAT_803304a4 * (float)(randomRange * Math.RandF() - halfSpread)) / FLOAT_803304c4;
        float randY = (FLOAT_803304a4 * (float)(randomRange * Math.RandF() - halfSpread)) / FLOAT_803304c4;
        float randZ = (FLOAT_803304a4 * (float)(randomRange * Math.RandF() - halfSpread)) / FLOAT_803304c4;

        if ((mode == 2) || (mode == 3)) {
            randX = FLOAT_80330498;
            randY = FLOAT_80330498;
        }

        particleData->m_directionTail.x = baseDirectionX;
        particleData->m_directionTail.y = baseDirectionY;
        particleData->m_directionTail.z = baseDirectionZ;
        particleData->m_colorDeltaAdd[0] = randX;
        particleData->m_colorDeltaAdd[1] = randY;
        particleData->m_colorDeltaAdd[2] = randZ;

        pppFMATRIX baseMatrix;
        pppFMATRIX rotatedMatrix;
        Vec rot;
        Vec forward;

        pppUnitMatrix(baseMatrix);
        rot.x = randX;
        rot.y = randY;
        rot.z = randZ;
        pppRotMatrix(rotatedMatrix, baseMatrix, rot);

        forward.x = baseDirectionX;
        forward.y = baseDirectionY;
        forward.z = baseDirectionZ;
        pppApplyMatrix(forward, rotatedMatrix, forward);
        forward.x *= *(float*)(payload + 0x54);
        forward.y *= *(float*)(payload + 0x58);
        forward.z *= *(float*)(payload + 0x5C);
        particleData->m_matrix[0][1] = forward.x;
        particleData->m_matrix[1][1] = forward.y;
        particleData->m_matrix[2][1] = forward.z;
        orthonormalize_particle_matrix(particleData);
    } else if (mode == 8 || mode == 9) {
        Vec spawnPoint;

        spawnPoint.x = work->m_currentPosition.x;
        spawnPoint.y = work->m_currentPosition.y;
        spawnPoint.z = work->m_currentPosition.z;

        if (mode == 8) {
            float t = (float)(work->m_unused1E & 0xFF) / 255.0f;
            spawnPoint.x = work->m_previousPosition.x +
                           (work->m_currentPosition.x - work->m_previousPosition.x) * t;
            spawnPoint.y = work->m_previousPosition.y +
                           (work->m_currentPosition.y - work->m_previousPosition.y) * t;
            spawnPoint.z = work->m_previousPosition.z +
                           (work->m_currentPosition.z - work->m_previousPosition.z) * t;
            work->m_unused1E = (u16)(work->m_unused1E + 0x21);
        } else {
            Vec delta;
            delta.x = work->m_currentPosition.x - work->m_previousPosition.x;
            delta.y = work->m_currentPosition.y - work->m_previousPosition.y;
            delta.z = work->m_currentPosition.z - work->m_previousPosition.z;
            spawnPoint.x += delta.x * Math.RandF();
            spawnPoint.y += delta.y * Math.RandF();
            spawnPoint.z += delta.z * Math.RandF();
        }

        spawnPoint.x *= *(float*)(payload + 0x54);
        spawnPoint.y *= *(float*)(payload + 0x58);
        spawnPoint.z *= *(float*)(payload + 0x5C);
        pos = spawnPoint;

        particleData->m_matrix[0][1] = work->m_accelerationAxis.x;
        particleData->m_matrix[1][1] = work->m_accelerationAxis.y;
        particleData->m_matrix[2][1] = work->m_accelerationAxis.z;
        orthonormalize_particle_matrix(particleData);
    }

    particleData->m_matrix[0][3] = pos.x;
    particleData->m_matrix[1][3] = pos.y;
    particleData->m_matrix[2][3] = pos.z;

    if (speedMag != FLOAT_80330498) {
        float speedX = calc_spawn_speed(speedMag, speedMode);
        float speedY = calc_spawn_speed(speedMag, speedMode);
        float speedZ = calc_spawn_speed(speedMag, speedMode);
        float halfSpeed = speedMag * 0.5f;

        if (mode < 6) {
            particleData->m_matrix[0][3] = (speedX - halfSpeed) * *(float*)(payload + 0x54);
            particleData->m_matrix[1][3] = (speedY - halfSpeed) * *(float*)(payload + 0x58);
            particleData->m_matrix[2][3] = (speedZ - halfSpeed) * *(float*)(payload + 0x5C);
        } else {
            particleData->m_velocity.x = speedX - halfSpeed;
            particleData->m_velocity.y = speedY - halfSpeed;
            particleData->m_velocity.z = speedZ - halfSpeed;
        }
    }

    particleData->m_sizeStart = *(float*)(payload + 0x84);
    particleData->m_sizeEnd = *(float*)(payload + 0x88);
    particleData->m_sizeVal = *(float*)(payload + 0x8C);
    particleData->m_directionTail.z = *(float*)(payload + 0x8C);
    particleData->m_colorDeltaAdd[0] = *(float*)(payload + 0x90);
    particleData->m_colorDeltaAdd[1] = *(float*)(payload + 0x94);
    particleData->m_colorDeltaAdd[2] = *(float*)(payload + 0x98);
    particleData->m_colorDeltaAdd[3] = *(float*)(payload + 0x9C);
    particleData->m_sizeStart = *(float*)(payload + 0xA0);

    *s16_at(particleData, 0x22) = (*(s16*)(payload + 0x26) == 0) ? -1 : *(s16*)(payload + 0x26);
    *s16_at(particleData, 0x1C) = 0;
    *s16_at(particleData, 0x1E) = 0;
    *u8_at(particleData, 0x9c) = 0;
    *u8_at(particleData, 0x9d) = payload[0x9d];
    *u8_at(particleData, 0x9e) = payload[0x9e];

    if (payload[0x131] != 0) {
        *f32_at(particleData, 0x98) = (float)color->m_alpha;
    } else {
        *f32_at(particleData, 0x98) = *(float*)(payload + 0x98);
    }

    if (particleWMat != NULL) {
        PSMTXCopy(pppMngStPtr->m_matrix.value, *(Mtx*)particleWMat);
    }

    if (particleColor != NULL) {
        particleColor->m_colorFrameDeltas[0] = *(float*)(payload + 0xBC);
        particleColor->m_colorFrameDeltas[1] = *(float*)(payload + 0xC0);
        particleColor->m_colorFrameDeltas[2] = *(float*)(payload + 0xC4);
        particleColor->m_colorFrameDeltas[3] = *(float*)(payload + 0xC8);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80085a38
 * PAL Size: 1432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VRyjMegaBirthModel* vRyjMegaBirthModel,
          PRyjMegaBirthModel* pRyjMegaBirthModel, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    (void)pppPObject;

    u32 alpha = vColor->m_alpha;
    u8* payload = (u8*)pRyjMegaBirthModel;
    u8* p = (u8*)particleData;

    if (particleColor != NULL) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] = particleColor->m_colorFrameDeltas[0] + pRyjMegaBirthModel->m_colorDeltaAdd[0];
        particleColor->m_colorFrameDeltas[1] = particleColor->m_colorFrameDeltas[1] + pRyjMegaBirthModel->m_colorDeltaAdd[1];
        particleColor->m_colorFrameDeltas[2] = particleColor->m_colorFrameDeltas[2] + pRyjMegaBirthModel->m_colorDeltaAdd[2];
        particleColor->m_colorFrameDeltas[3] = particleColor->m_colorFrameDeltas[3] + pRyjMegaBirthModel->m_colorDeltaAdd[3];
        alpha += (u32)(s32)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    particleData->m_directionTail.z = (float)((s32)particleData->m_directionTail.z + (s32)particleData->m_colorDeltaAdd[2]);
    particleData->m_colorDeltaAdd[0] = (float)((s32)particleData->m_colorDeltaAdd[0] + (s32)particleData->m_colorDeltaAdd[3]);
    particleData->m_colorDeltaAdd[1] = (float)((s32)particleData->m_colorDeltaAdd[1] + (s32)particleData->m_sizeStart);

    if ((payload[0x8B] & 0x10) == 0) {
        particleData->m_colorDeltaAdd[2] = (float)((s32)particleData->m_colorDeltaAdd[2] + (s32)*(float*)(payload + 0x98));
        particleData->m_colorDeltaAdd[3] = (float)((s32)particleData->m_colorDeltaAdd[3] + (s32)*(float*)(payload + 0x9C));
        particleData->m_sizeStart = (float)((s32)particleData->m_sizeStart + (s32)*(float*)(payload + 0xA0));
    } else {
        particleData->m_colorDeltaAdd[2] = (float)((s32)*(float*)(payload + 0x98) + (s32)*(float*)(p + 0x60) + (s32)particleData->m_colorDeltaAdd[2]);
        particleData->m_colorDeltaAdd[3] = (float)((s32)*(float*)(payload + 0x9C) + (s32)*(float*)(p + 0x64) + (s32)particleData->m_colorDeltaAdd[3]);
        particleData->m_sizeStart = (float)((s32)*(float*)(payload + 0xA0) + (s32)*(float*)(p + 0x68) + (s32)particleData->m_sizeStart);
    }

    wrap_particle_rotation_triplet(p, 0x58);

    *f32_at(p, 0x40) = *f32_at(p, 0x40) + *f32_at(p, 0x48);
    *f32_at(p, 0x44) = *f32_at(p, 0x44) + *f32_at(p, 0x4C);
    *f32_at(p, 0x50) = *f32_at(p, 0x50) + *f32_at(payload, 0x84);
    *f32_at(p, 0x54) = *f32_at(p, 0x54) + *f32_at(payload, 0x88);

    particleData->m_sizeVal = particleData->m_sizeVal + *(float*)(payload + 0xA8);
    if (payload[0x8E] == 0) {
        if (((*(float*)(payload + 0xAC) < FLOAT_80330498) && (FLOAT_80330498 < *(float*)(payload + 0xA8)) &&
             (FLOAT_80330498 < particleData->m_sizeVal)) ||
            ((*(float*)(payload + 0xAC) > FLOAT_80330498) && (FLOAT_80330498 > *(float*)(payload + 0xA8)) &&
             (particleData->m_sizeVal < FLOAT_80330498))) {
            particleData->m_sizeVal = FLOAT_80330498;
        }
    }

    *f32_at(p, 0x6C) = *f32_at(p, 0x6C) + *f32_at(p, 0x78);
    *f32_at(p, 0x70) = *f32_at(p, 0x70) + *f32_at(p, 0x7C);
    *f32_at(p, 0x74) = *f32_at(p, 0x74) + *f32_at(p, 0x80);

    if ((payload[0x8A] & 0x10) == 0) {
        *f32_at(p, 0x78) = *f32_at(p, 0x78) + *(float*)(payload + 0xB0);
        *f32_at(p, 0x7C) = *f32_at(p, 0x7C) + *(float*)(payload + 0xB4);
        *f32_at(p, 0x80) = *f32_at(p, 0x80) + *(float*)(payload + 0xB8);
    } else {
        *f32_at(p, 0x78) = *f32_at(p, 0x78) + *(float*)(payload + 0xB0) + *f32_at(p, 0x84);
        *f32_at(p, 0x7C) = *f32_at(p, 0x7C) + *(float*)(payload + 0xB4) + *f32_at(p, 0x88);
        *f32_at(p, 0x80) = *f32_at(p, 0x80) + *(float*)(payload + 0xB8) + *f32_at(p, 0x8C);
    }

    *f32_at(p, 0x8C) = *f32_at(p, 0x8C) + *(float*)(payload + 0xBC);
    if (payload[0x8F] == 0) {
        if (((*(float*)(payload + 0xC0) <= FLOAT_80330498) && (FLOAT_80330498 <= *(float*)(payload + 0xBC))) ||
            ((*(float*)(payload + 0xC0) < FLOAT_80330498) && (FLOAT_80330498 < *(float*)(payload + 0xBC) &&
                                                              FLOAT_80330498 < *f32_at(p, 0x8C)))) {
            *f32_at(p, 0x8C) = FLOAT_80330498;
        } else if ((*(float*)(payload + 0xC0) > FLOAT_80330498) && (FLOAT_80330498 > *(float*)(payload + 0xBC)) &&
                   (*f32_at(p, 0x8C) < FLOAT_80330498)) {
            *f32_at(p, 0x8C) = FLOAT_80330498;
        }
    }

    *f32_at(p, 0x90) = *f32_at(p, 0x90) + *(float*)(payload + 0xC4);
    Vec direction = {particleData->m_matrix[0][1], particleData->m_matrix[1][1], particleData->m_matrix[2][1]};
    Vec position = {particleData->m_matrix[0][3], particleData->m_matrix[1][3], particleData->m_matrix[2][3]};
    Vec step;

    pppScaleVectorXYZ(step, direction, *f32_at(p, 0x8C));
    pppAddVector(position, position, step);
    pppScaleVectorXYZ(step, vRyjMegaBirthModel->m_accelerationAxis, *f32_at(p, 0x90));
    pppAddVector(position, position, step);

    particleData->m_matrix[0][3] = position.x;
    particleData->m_matrix[1][3] = position.y;
    particleData->m_matrix[2][3] = position.z;

    *f32_at(p, 0x8C) = *f32_at(p, 0x8C) + *f32_at(p, 0x90);
    *f32_at(p, 0x90) = *f32_at(p, 0x90) + *(float*)(payload + 0xE0);
    *f32_at(p, 0x94) = *f32_at(p, 0x94) + *(float*)(payload + 0xE4);

    particleData->m_lifeTime = particleData->m_lifeTime + 1;
    if (*(s16*)(payload + 0x26) != 0) {
        *s16_at(p, 0x22) = *s16_at(p, 0x22) - 1;
    }

    *u8_at(p, 0x9c) = *u8_at(p, 0x9c) + 1;

    if ((*u8_at(p, 0x9d) != 0) && (*u8_at(p, 0x9c) <= *u8_at(p, 0x9d))) {
        *f32_at(p, 0x98) -= (float)alpha / (float)*u8_at(p, 0x9d);
    }

    if ((*u8_at(p, 0x9e) != 0) && ((u16)*s16_at(p, 0x22) <= *u8_at(p, 0x9e))) {
        *f32_at(p, 0x98) += (float)alpha / (float)payload[0x9E];
    }

    *f32_at((u8*)vRyjMegaBirthModel, 0x20) = *f32_at((u8*)vRyjMegaBirthModel, 0x2C);
    *f32_at((u8*)vRyjMegaBirthModel, 0x24) = *f32_at((u8*)vRyjMegaBirthModel, 0x30);
    *f32_at((u8*)vRyjMegaBirthModel, 0x28) = *f32_at((u8*)vRyjMegaBirthModel, 0x34);
}

/*
 * --INFO--
 * PAL Address: 0x8008521c
 * PAL Size: 2076b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjDrawMegaBirthModel(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable)
{
    PRyjMegaBirthModel* params = (PRyjMegaBirthModel*)stepData;
    VRyjMegaBirthModel* work =
        (VRyjMegaBirthModel*)((u8*)obj + 0x80 + ctrlTable->m_serializedDataOffsets[2]);
    int modelIndex = *(int*)((u8*)params + 4);

    if (modelIndex == 0xFFFF || work->m_particleBlock == NULL) {
        return;
    }

    if ((*(u8*)((u8*)params + 0x136) != 0) && (work->m_worldMatrixBlock == NULL)) {
        return;
    }

    if ((*(u8*)((u8*)params + 0x131) != 0) && (work->m_colorBlock == NULL)) {
        return;
    }

    pppModelSt* model = (pppModelSt*)pppEnvStPtr->m_mapMeshPtr[modelIndex];
    if (model == NULL) {
        return;
    }

    pppFMATRIX emitterMatrix;
    pppFMATRIX scratchMatrix;

    init_matrix(obj, emitterMatrix, params, work);
    pppUnitMatrix(scratchMatrix);
    pppInitBlendMode();
    pppSetBlendMode(0);

    for (int i = 0; i < work->m_numParticles; i++) {
        _PARTICLE_DATA* particle = (_PARTICLE_DATA*)((u8*)work->m_particleBlock + i * 0xA0);
        _PARTICLE_WMAT* particleWorldMatrix = 0;
        _PARTICLE_COLOR* particleColor = 0;

        if (*s16_at(particle, 0x22) == 0) {
            continue;
        }

        if (work->m_worldMatrixBlock != NULL) {
            particleWorldMatrix = (_PARTICLE_WMAT*)(work->m_worldMatrixBlock + i);
        }
        if (work->m_colorBlock != NULL) {
            particleColor = work->m_colorBlock + i;
        }

        pppFMATRIX drawMatrix;
        pppCVECTOR drawColor = {{0xFF, 0xFF, 0xFF, clamp_u8(*f32_at(particle, 0x98))}};

        if (particleColor != NULL) {
            drawColor.rgba[0] = clamp_u8(particleColor->m_color[0]);
            drawColor.rgba[1] = clamp_u8(particleColor->m_color[1]);
            drawColor.rgba[2] = clamp_u8(particleColor->m_color[2]);
        }

        set_matrix(obj, emitterMatrix, scratchMatrix, params, particle, particleWorldMatrix, drawMatrix, 0);
        pppSetDrawEnv(&drawColor, &drawMatrix, 0.0f, 0, 0, 0, 0, 1, 1, 0);
        pppDrawMesh(model, 0, 1);
    }

    PSMTXCopy(g_matKeep, g_matTmp);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirthModel* params, VRyjMegaBirthModel* work)
{
    (void)pObject;
    u8* payload = (u8*)params;
    switch (payload[0x2A]) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        PSMTXIdentity(out.value);
        out.value[0][0] = pppMngStPtr->m_scale.x;
        out.value[1][1] = pppMngStPtr->m_scale.y;
        out.value[2][2] = pppMngStPtr->m_scale.z;
        out.value[0][3] = pppMngStPtr->m_position.x;
        out.value[1][3] = pppMngStPtr->m_position.y;
        out.value[2][3] = pppMngStPtr->m_position.z;
        break;
    case 8:
        PSMTXIdentity(out.value);
        out.value[0][3] = *f32_at((u8*)work, 0x2C);
        out.value[1][3] = *f32_at((u8*)work, 0x30);
        out.value[2][3] = *f32_at((u8*)work, 0x34);
        break;
    default:
        PSMTXCopy(pppMngStPtr->m_matrix.value, out.value);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800842e4
 * PAL Size: 3896b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void set_matrix(_pppPObject* pObject, pppFMATRIX mtxA, pppFMATRIX mtxB, PRyjMegaBirthModel* params,
                _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, pppFMATRIX& out, unsigned char copyOut)
{
    u8* payload = (u8*)params;
    const u8 matrixMode = payload[0x2A];
    const u8 flagsEnd = payload[0x137];
    pppFMATRIX local;
    pppFMATRIX world;
    pppFMATRIX tmp;
    Mtx scale;

    if (matrixMode == 0) {
        pppUnitMatrix(local);
        local.value[0][3] = particleData->m_matrix[0][3];
        local.value[1][3] = particleData->m_matrix[1][3];
        local.value[2][3] = particleData->m_matrix[2][3];
    } else {
        pppCopyMatrix(local, *(pppFMATRIX*)&particleData->m_matrix);
    }

    if (particleData->m_directionTail.z != FLOAT_80330498 ||
        particleData->m_colorDeltaAdd[0] != FLOAT_80330498 ||
        particleData->m_colorDeltaAdd[1] != FLOAT_80330498) {
        Vec rot;
        rot.x = -particleData->m_directionTail.z * (FLOAT_803304a0 / FLOAT_803304a4);
        rot.y = -particleData->m_colorDeltaAdd[0] * (FLOAT_803304a0 / FLOAT_803304a4);
        rot.z = -particleData->m_colorDeltaAdd[1] * (FLOAT_803304a0 / FLOAT_803304a4);
        pppFMATRIX r;
        pppUnitMatrix(r);
        pppRotMatrix(r, r, rot);
        pppCopyMatrix(tmp, local);
        pppMulMatrix(local, tmp, r);
    }

    PSMTXScale(scale, particleData->m_sizeStart, particleData->m_sizeEnd, particleData->m_sizeVal);
    pppCopyMatrix(tmp, local);
    pppMulMatrix(local, tmp, *(pppFMATRIX*)&scale);

    switch (matrixMode) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        pppCopyMatrix(world, mtxA);
        pppCopyMatrix(tmp, world);
        pppMulMatrix(world, tmp, local);
        break;
    default:
        if (particleWMat != NULL) {
            pppCopyMatrix(world, *(pppFMATRIX*)particleWMat);
            pppCopyMatrix(tmp, world);
            pppMulMatrix(world, tmp, local);
        } else {
            pppCopyMatrix(world, *(pppFMATRIX*)&pObject->m_localMatrix);
            pppCopyMatrix(tmp, world);
            pppMulMatrix(world, tmp, local);

            if (payload[0x136] != 0) {
                pppCopyMatrix(tmp, world);
                pppMulMatrix(world, pppMngStPtr->m_matrix, tmp);
            }
        }
        break;
    }

    pppCopyMatrix(*(pppFMATRIX*)&g_matKeep, world);
    PSMTXConcat(ppvCameraMatrix0, world.value, g_matTmp);
    PSMTXCopy(g_matTmp, out.value);

    if (copyOut != 0) {
        pppCopyMatrix(mtxB, out);
    }

    if (flagsEnd != 0) {
        Vec objectPos;
        Vec endPos;
        pppFMATRIX* endMatrix = (pppFMATRIX*)(pObject + 1);

        objectPos.x = pObject->m_localMatrix.value[0][3];
        objectPos.y = pObject->m_localMatrix.value[1][3];
        objectPos.z = pObject->m_localMatrix.value[2][3];

        endPos.x = world.value[0][3];
        endPos.y = world.value[1][3];
        endPos.z = world.value[2][3];
        pppAddVector(endPos, endPos, objectPos);

        pppUnitMatrix(*endMatrix);
        PSMTXScaleApply(endMatrix->value, endMatrix->value, particleData->m_sizeStart * pppMngStPtr->m_scale.x,
                        particleData->m_sizeEnd * pppMngStPtr->m_scale.y,
                        particleData->m_sizeVal * pppMngStPtr->m_scale.z);

        if (particleData->m_colorDeltaAdd[1] != FLOAT_80330498) {
            pppFMATRIX rot;

            PSMTXRotRad(rot.value, 'z', FLOAT_803304a8 * -particleData->m_colorDeltaAdd[1]);
            pppCopyMatrix(tmp, *endMatrix);
            pppMulMatrix(*endMatrix, rot, tmp);
        }

        PSMTXMultVec(ppvWorldMatrix, &endPos, &endPos);
        endMatrix->value[0][3] = endPos.x;
        endMatrix->value[1][3] = endPos.y;
        endMatrix->value[2][3] = endPos.z;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80084260
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModelCon(_pppPObject* pObject, PRyjMegaBirthModelOffsets* offsets)
{
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];
    float value1;
    float value0;

    memset((void*)work, 0, 0xC);
    *(u32*)(work + 0xC) = 0;
    value0 = FLOAT_80330498;
    *(u32*)(work + 0x10) = 0;
    value1 = FLOAT_8033049c;
    *(u32*)(work + 0x14) = 0;
    *(u32*)(work + 0x18) = 0;
    *(u16*)(work + 0x1C) = 10000;
    *(u16*)(work + 0x1E) = 0;
    *(float*)(work + 0x20) = value0;
    *(float*)(work + 0x24) = value1;
    *(float*)(work + 0x28) = value0;
    *(float*)(work + 0x2C) = value0;
    *(float*)(work + 0x30) = value1;
    *(float*)(work + 0x34) = value0;
}

/*
 * --INFO--
 * PAL Address: 0x800841e4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRyjMegaBirthModelDes(_pppPObject* pObject, PRyjMegaBirthModelOffsets* offsets)
{
    u8* work = (u8*)pObject + 0x80 + offsets->m_serializedDataOffsets[2];

    if (*(void**)(work + 0xC) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0xC));
        *(void**)(work + 0xC) = 0;
    }

    if (*(void**)(work + 0x10) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x10));
        *(void**)(work + 0x10) = 0;
    }

    if (*(void**)(work + 0x14) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)(work + 0x14));
        *(void**)(work + 0x14) = 0;
    }
}
