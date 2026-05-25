#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include <string.h>
#include "ffcc/ppp_linkage.h"

extern const float FLOAT_80330498;
extern const float FLOAT_8033049c;
extern const float FLOAT_803304a0;
extern const float FLOAT_803304a4;
extern const float FLOAT_803304a8;
extern const float FLOAT_803304b4;
extern const float FLOAT_803304bc;
extern const float FLOAT_803304c0;
extern const float FLOAT_803304c4;
extern const float FLOAT_803304c8;
extern const float FLOAT_803304CC;
extern const float FLOAT_803304D0;
extern const double DOUBLE_803304E0;
extern const float FLOAT_803304E8[2];

PARTICLE_WMAT g_matKeep;
PARTICLE_WMAT g_matTmp;

extern "C" const char s_pppRyjMegaBirthModel_cpp[] = "pppRyjMegaBirthModel.cpp";

extern const float FLOAT_803304a8 = 0.017453292f;
extern const double DOUBLE_803304b0 = 4503601774854144.0;
extern const double DOUBLE_803304B8 = 4503599627370496.0;
extern const float FLOAT_803304c0 = 2.0f;
extern const float FLOAT_803304c4 = 180.0f;
extern const float FLOAT_803304c8 = 1.0f;
extern const float FLOAT_803304CC = 0.7f;
extern const float FLOAT_803304D0 = 0.5f;
extern const double DOUBLE_803304D8 = 1.0;
extern const double DOUBLE_803304E0 = 0.5;
extern const float FLOAT_803304E8[2] = { -1.0f, 0.0f };
extern const float FLOAT_803304F0[2] = { 0.0f, 0.0f };
extern const float FLOAT_803304F8 = 0.0f;

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

static inline s32* s32_at(void* base, s32 off)
{
    return (s32*)((u8*)base + off);
}

static inline u8* u8_at(void* base, s32 off)
{
    return (u8*)base + off;
}

static inline float MegaBirthSpeedFalloff()
{
    return *reinterpret_cast<const float*>(&FLOAT_803304CC);
}

static inline float MegaBirthHalf()
{
    return *reinterpret_cast<const float*>(&FLOAT_803304D0);
}

static inline double MegaBirthHalfDouble()
{
    return *reinterpret_cast<const double*>(&DOUBLE_803304E0);
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

static inline float calc_spawn_speed(float speedMag, u8 speedMode)
{
    const float halfSpeed = MegaBirthHalf() * speedMag;

    switch (speedMode) {
    case 0:
        return Math.RandF() * speedMag - halfSpeed;
    case 1:
        (void)Math.RandF();
        return Math.RandF() * speedMag - halfSpeed;
    case 2:
        return Math.RandF() * Math.RandF() * speedMag - halfSpeed;
    case 3:
        return -(MegaBirthSpeedFalloff() * (Math.RandF() * Math.RandF() * speedMag) - speedMag) - halfSpeed;
    case 4:
        return Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * speedMag - halfSpeed;
    case 5:
        return -(MegaBirthHalf() * (Math.RandF() * Math.RandF() * Math.RandF() * speedMag) - speedMag) - halfSpeed;
    default:
        return Math.RandF() * speedMag - halfSpeed;
    }
}

static inline void orthonormalize_particle_matrix(_PARTICLE_DATA* particleData)
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

static inline void wrap_particle_rotation_triplet(u8* particleBytes, s32 offset)
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

static inline void wrap_particle_rotation_triplet_s32(u8* particleBytes, s32 offset)
{
    s32 count = 3;
    s32* value = s32_at(particleBytes, offset);
    do {
        while (*value > 0x7FFF) {
            *value -= 0x10000;
        }
        while (*value < -0x8000) {
            *value += 0x10000;
        }
        value++;
        count--;
    } while (count != 0);
}

static inline void apply_signed_randomization(u8* particleBytes, s32 offset, u8 flags)
{
    if (((flags & 1) != 0) && ((flags & 2) != 0)) {
        for (int i = 0; i < 3; i++) {
            float* value = f32_at(particleBytes, offset + i * 4);
            if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                *value = *value * FLOAT_803304E8[0];
            }
        }
    } else if ((flags & 2) != 0) {
        for (int i = 0; i < 3; i++) {
            float* value = f32_at(particleBytes, offset + i * 4);
            *value = *value * FLOAT_803304E8[0];
        }
    }
}

static inline signed char random_signed_byte_span(u8 span)
{
    (void)Math.RandF();
    return (signed char)((s32)((float)(span << 1) * Math.RandF() - (float)(span >> 1)));
}

static inline void randomize_particle_triplet(u8* particleBytes, s32 offset, u8 flags, float rangeX, float rangeY, float rangeZ)
{
    if (flags == 0) {
        return;
    }

    if ((flags & 0x20) == 0) {
        *f32_at(particleBytes, offset + 0) = rangeX * Math.RandF();
        *f32_at(particleBytes, offset + 4) = rangeY * Math.RandF();
        *f32_at(particleBytes, offset + 8) = rangeZ * Math.RandF();
    } else {
        float shared = rangeX * Math.RandF();
        *f32_at(particleBytes, offset + 0) = shared;
        *f32_at(particleBytes, offset + 4) = shared;
        *f32_at(particleBytes, offset + 8) = shared;
    }

    apply_signed_randomization(particleBytes, offset, flags);
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
    s8 hasRequiredMemory;
    VRyjMegaBirthModel* work =
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);
    VColor* color = reinterpret_cast<VColor*>(pObject->m_workArea + offsets->m_serializedDataOffsets[1]);
    u8* payload = (u8*)params;

    if (work->m_particleBlock == 0) {
        work->m_numParticles = *(u16*)(payload + 0x20);
        work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_numParticles * 0xA0, ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0x8D);
        if (work->m_particleBlock != NULL) {
            memset(work->m_particleBlock, 0, work->m_numParticles * 0xA0);
        }

        if (payload[0x136] != 0) {
            work->m_worldMatrixBlock = (PARTICLE_WMAT*)pppMemAlloc(
                work->m_numParticles * sizeof(PARTICLE_WMAT), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0x97);
            if (work->m_worldMatrixBlock != NULL) {
                memset(work->m_worldMatrixBlock, 0, work->m_numParticles * sizeof(PARTICLE_WMAT));
            }
        }

        if (payload[0x131] != 0) {
            work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc(
                work->m_numParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0xA2);
            if (work->m_colorBlock != NULL) {
                memset(work->m_colorBlock, 0, work->m_numParticles * sizeof(_PARTICLE_COLOR));
            }
        }

        work->m_accelerationAxis.x = *(float*)(payload + 0xF8);
        work->m_accelerationAxis.y = *(float*)(payload + 0xFC);
        work->m_accelerationAxis.z = *(float*)(payload + 0x100);
        PSVECNormalize(&work->m_accelerationAxis, &work->m_accelerationAxis);

        posX = *f32_at(pObject, 0x1C);
        posY = *f32_at(pObject, 0x2C);
        posZ = *f32_at(pObject, 0x3C);
        work->m_previousPosition.x = posX;
        work->m_previousPosition.y = posY;
        work->m_previousPosition.z = posZ;
        work->m_currentPosition.x = posX;
        work->m_currentPosition.y = posY;
        work->m_currentPosition.z = posZ;
    }

    if (work->m_particleBlock == 0) {
        hasRequiredMemory = false;
    } else if ((*(u8*)(payload + 0x136) != 0) && (work->m_worldMatrixBlock == 0)) {
        hasRequiredMemory = false;
    } else if ((*(u8*)(payload + 0x131) != 0) && (work->m_colorBlock == 0)) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }

    if (hasRequiredMemory) {
        calc_particle(pObject, work, params, color);
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
    _PARTICLE_DATA* particleData;
    _PARTICLE_WMAT* particleWMat;
    _PARTICLE_COLOR* particleColor;
    s32 maxParticles;
    s32 emitted;
    s32 i;
    u8* payload;
    u16* emitTimer;

    emitted = 0;
    payload = (u8*)params;
    particleData = work->m_particleBlock;
    particleWMat = reinterpret_cast<_PARTICLE_WMAT*>(work->m_worldMatrixBlock);
    particleColor = work->m_colorBlock;
    maxParticles = work->m_numParticles;
    emitTimer = &work->m_emitTimer;

    if (gPppCalcDisabled == 0) {
        float posX = pObject->m_localMatrix.value[0][3];
        float posY = pObject->m_localMatrix.value[1][3];
        float posZ = pObject->m_localMatrix.value[2][3];

        work->m_previousPosition = work->m_currentPosition;
        work->m_currentPosition.x = posX;
        work->m_currentPosition.y = posY;
        work->m_currentPosition.z = posZ;
        *emitTimer = *emitTimer + 1;

        for (i = 0; i < maxParticles; i = i + 1) {
            if (*(u16*)((u8*)particleData + 0x30) != 0) {
                calc(pObject, work, params, particleData, color, particleColor);
            } else {
                if ((*(u16*)(payload + 0x24) <= *emitTimer) && (emitted < (s32)(u32)*(u16*)(payload + 0x22))) {
                    birth(pObject, work, params, color, particleData, particleWMat, particleColor);
                    emitted = emitted + 1;
                }
            }

            if (particleWMat != NULL) {
                particleWMat++;
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
    float speedMag = *(float*)(payload + 0x12C);
    u8 speedMode = payload[0x130];
    Vec pos;

    memset(particleData, 0, 0xA0);
    if (particleWMat != NULL) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    pppUnitMatrix(*(pppFMATRIX*)&particleData->m_matrix);

    pos.x = pObject->m_localMatrix.value[0][3];
    pos.y = pObject->m_localMatrix.value[1][3];
    pos.z = pObject->m_localMatrix.value[2][3];

    if (mode < 8) {
        float baseDirectionX = *(float*)(payload + 0xE8);
        float baseDirectionY = *(float*)(payload + 0xEC);
        float baseDirectionZ = *(float*)(payload + 0xF0);
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
        forward.x *= *(float*)(payload + 0x120);
        forward.y *= *(float*)(payload + 0x124);
        forward.z *= *(float*)(payload + 0x128);
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

        spawnPoint.x *= *(float*)(payload + 0x120);
        spawnPoint.y *= *(float*)(payload + 0x124);
        spawnPoint.z *= *(float*)(payload + 0x128);
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

        if (mode < 6) {
            particleData->m_matrix[0][3] = speedX * *(float*)(payload + 0x120);
            particleData->m_matrix[1][3] = speedY * *(float*)(payload + 0x124);
            particleData->m_matrix[2][3] = speedZ * *(float*)(payload + 0x128);
        } else {
            particleData->m_velocity.x = speedX;
            particleData->m_velocity.y = speedY;
            particleData->m_velocity.z = speedZ;
        }
    }

    *f32_at(particleData, 0x44) = *(float*)(payload + 0x8C);
    *f32_at(particleData, 0x48) = *(float*)(payload + 0x90);
    *f32_at(particleData, 0x4C) = *(float*)(payload + 0x94);
    *f32_at(particleData, 0x50) = *(float*)(payload + 0x98);
    *f32_at(particleData, 0x54) = *(float*)(payload + 0x9C);
    *f32_at(particleData, 0x58) = *(float*)(payload + 0xA0);

    *s16_at(particleData, 0x22) = (*(s16*)(payload + 0x26) == 0) ? -1 : *(s16*)(payload + 0x26);
    *s16_at(particleData, 0x1C) = 0;
    *s16_at(particleData, 0x1E) = 0;
    *u8_at(particleData, 0x9c) = 0;
    *u8_at(particleData, 0x9d) = 0;
    *u8_at(particleData, 0x9e) = 0;

    if (payload[0x131] != 0) {
        *f32_at(particleData, 0x98) = (float)color->m_alpha;
    } else {
        *f32_at(particleData, 0x98) = *(float*)(payload + 0x98);
    }

    if (payload[0x22] != 0) {
        *f32_at(particleData, 0x98) = static_cast<float>(color->m_alpha);
        *u8_at(particleData, 0x9D) = payload[0x22];
    }
    if (payload[0x29] != 0) {
        *u8_at(particleData, 0x9E) = payload[0x29];
    }

    if (particleWMat != NULL) {
        PSMTXCopy(ppvMng->m_matrix.value, *(Mtx*)particleWMat);
    }

    if (particleColor != NULL) {
        particleColor->m_colorFrameDeltas[0] = *(float*)(payload + 0xBC);
        particleColor->m_colorFrameDeltas[1] = *(float*)(payload + 0xC0);
        particleColor->m_colorFrameDeltas[2] = *(float*)(payload + 0xC4);
        particleColor->m_colorFrameDeltas[3] = *(float*)(payload + 0xC8);
    }

    if (payload[0x132] != 0) {
        if ((payload[0x132] & 0x20) == 0) {
            *f32_at(particleData, 0x74) = *(float*)(payload + 0xC0) * Math.RandF();
            *f32_at(particleData, 0x78) = *(float*)(payload + 0xC4) * Math.RandF();
            *f32_at(particleData, 0x7C) = *(float*)(payload + 0xC8) * Math.RandF();

            if ((payload[0x132] & 1) != 0 && (payload[0x132] & 2) != 0) {
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    *f32_at(particleData, 0x74) = *f32_at(particleData, 0x74) * FLOAT_803304E8[0];
                }
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    *f32_at(particleData, 0x78) = *f32_at(particleData, 0x78) * FLOAT_803304E8[0];
                }
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    *f32_at(particleData, 0x7C) = *f32_at(particleData, 0x7C) * FLOAT_803304E8[0];
                }
            } else if ((payload[0x132] & 2) != 0) {
                *f32_at(particleData, 0x74) = *f32_at(particleData, 0x74) * FLOAT_803304E8[0];
                *f32_at(particleData, 0x78) = *f32_at(particleData, 0x78) * FLOAT_803304E8[0];
                *f32_at(particleData, 0x7C) = *f32_at(particleData, 0x7C) * FLOAT_803304E8[0];
            }
        } else {
            float randomVelocity = *(float*)(payload + 0xC0) * Math.RandF();

            *f32_at(particleData, 0x74) = randomVelocity;
            *f32_at(particleData, 0x78) = randomVelocity;
            *f32_at(particleData, 0x7C) = randomVelocity;

            if ((payload[0x132] & 1) != 0 && (payload[0x132] & 2) != 0) {
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    *f32_at(particleData, 0x74) = *f32_at(particleData, 0x74) * FLOAT_803304E8[0];
                    *f32_at(particleData, 0x78) = *f32_at(particleData, 0x78) * FLOAT_803304E8[0];
                    *f32_at(particleData, 0x7C) = *f32_at(particleData, 0x7C) * FLOAT_803304E8[0];
                }
            } else if ((payload[0x132] & 2) != 0) {
                *f32_at(particleData, 0x74) = *f32_at(particleData, 0x74) * FLOAT_803304E8[0];
                *f32_at(particleData, 0x78) = *f32_at(particleData, 0x78) * FLOAT_803304E8[0];
                *f32_at(particleData, 0x7C) = *f32_at(particleData, 0x7C) * FLOAT_803304E8[0];
            }
        }

        if ((payload[0x132] & 4) != 0) {
            *f32_at(particleData, 0x44) = *f32_at(particleData, 0x44) + *f32_at(particleData, 0x74);
            *f32_at(particleData, 0x48) = *f32_at(particleData, 0x48) + *f32_at(particleData, 0x78);
            *f32_at(particleData, 0x4C) = *f32_at(particleData, 0x4C) + *f32_at(particleData, 0x7C);
        }

        if ((payload[0x132] & 8) != 0) {
            *f32_at(particleData, 0x50) = *f32_at(particleData, 0x50) + *f32_at(particleData, 0x74);
            *f32_at(particleData, 0x54) = *f32_at(particleData, 0x54) + *f32_at(particleData, 0x78);
            *f32_at(particleData, 0x58) = *f32_at(particleData, 0x58) + *f32_at(particleData, 0x7C);
        }
    }

    wrap_particle_rotation_triplet((u8*)particleData, 0x44);

    *f32_at(particleData, 0x6C) = *(float*)(payload + 0x90);
    *f32_at(particleData, 0x70) = *(float*)(payload + 0x94);
    *f32_at(particleData, 0x74) = *(float*)(payload + 0x98);
    *f32_at(particleData, 0x78) = *(float*)(payload + 0x9C);
    *f32_at(particleData, 0x7C) = *(float*)(payload + 0xA0);
    *f32_at(particleData, 0x80) = *(float*)(payload + 0xA4);

    if (payload[0x133] != 0) {
        if ((payload[0x133] & 0x20) == 0) {
            *f32_at(particleData, 0x84) = *(float*)(payload + 0xB0) * Math.RandF();
            *f32_at(particleData, 0x88) = *(float*)(payload + 0xB4) * Math.RandF();
            *f32_at(particleData, 0x8C) = *(float*)(payload + 0xB8) * Math.RandF();
        } else {
            float randomizedStep = *(float*)(payload + 0xB0) * Math.RandF();
            *f32_at(particleData, 0x84) = randomizedStep;
            *f32_at(particleData, 0x88) = randomizedStep;
            *f32_at(particleData, 0x8C) = randomizedStep;
        }

        apply_signed_randomization((u8*)particleData, 0x84, payload[0x133]);

        if ((payload[0x133] & 4) != 0) {
            *f32_at(particleData, 0x6C) = *f32_at(particleData, 0x6C) + *f32_at(particleData, 0x84);
            *f32_at(particleData, 0x70) = *f32_at(particleData, 0x70) + *f32_at(particleData, 0x88);
            *f32_at(particleData, 0x74) = *f32_at(particleData, 0x74) + *f32_at(particleData, 0x8C);
        }

        if ((payload[0x133] & 8) != 0) {
            *f32_at(particleData, 0x78) = *f32_at(particleData, 0x78) + *f32_at(particleData, 0x84);
            *f32_at(particleData, 0x7C) = *f32_at(particleData, 0x7C) + *f32_at(particleData, 0x88);
            *f32_at(particleData, 0x80) = *f32_at(particleData, 0x80) + *f32_at(particleData, 0x8C);
        }
    }

    u8* particleBytes = (u8*)particleData;

    particleBytes[0x32] = random_signed_byte_span(payload[0x2C]);
    particleBytes[0x33] = random_signed_byte_span(payload[0x2D]);
    particleBytes[0x34] = random_signed_byte_span(payload[0x2E]);
    particleBytes[0x35] = random_signed_byte_span(payload[0x2F]);

    randomize_particle_triplet(particleBytes, 0x5C, payload[0x132],
                               (float)*(s32*)(payload + 0xC8),
                               (float)*(s32*)(payload + 0xCC),
                               (float)*(s32*)(payload + 0xD0));
    if ((payload[0x132] & 4) != 0) {
        *f32_at(particleBytes, 0x44) = (float)((s32)*f32_at(particleBytes, 0x44) + (s32)*f32_at(particleBytes, 0x5C));
        *f32_at(particleBytes, 0x48) = (float)((s32)*f32_at(particleBytes, 0x48) + (s32)*f32_at(particleBytes, 0x60));
        *f32_at(particleBytes, 0x4C) = (float)((s32)*f32_at(particleBytes, 0x4C) + (s32)*f32_at(particleBytes, 0x64));
    }
    if ((payload[0x132] & 8) != 0) {
        *f32_at(particleBytes, 0x50) = (float)((s32)*f32_at(particleBytes, 0x50) + (s32)*f32_at(particleBytes, 0x5C));
        *f32_at(particleBytes, 0x54) = (float)((s32)*f32_at(particleBytes, 0x54) + (s32)*f32_at(particleBytes, 0x60));
        *f32_at(particleBytes, 0x58) = (float)((s32)*f32_at(particleBytes, 0x58) + (s32)*f32_at(particleBytes, 0x64));
    }

    wrap_particle_rotation_triplet(particleBytes, 0x38);

    *f32_at(particleBytes, 0x6C) = *(float*)(payload + 0x90);
    *f32_at(particleBytes, 0x70) = *(float*)(payload + 0x94);
    *f32_at(particleBytes, 0x74) = *(float*)(payload + 0x98);
    *f32_at(particleBytes, 0x78) = *(float*)(payload + 0xA0);
    *f32_at(particleBytes, 0x7C) = *(float*)(payload + 0xA4);
    *f32_at(particleBytes, 0x80) = *(float*)(payload + 0xA8);

    randomize_particle_triplet(particleBytes, 0x84, payload[0x133],
                               *(float*)(payload + 0xB0),
                               *(float*)(payload + 0xB4),
                               *(float*)(payload + 0xB8));
    if ((payload[0x133] & 4) != 0) {
        *f32_at(particleBytes, 0x6C) += *f32_at(particleBytes, 0x84);
        *f32_at(particleBytes, 0x70) += *f32_at(particleBytes, 0x88);
        *f32_at(particleBytes, 0x74) += *f32_at(particleBytes, 0x8C);
    }
    if ((payload[0x133] & 8) != 0) {
        *f32_at(particleBytes, 0x78) += *f32_at(particleBytes, 0x84);
        *f32_at(particleBytes, 0x7C) += *f32_at(particleBytes, 0x88);
        *f32_at(particleBytes, 0x80) += *f32_at(particleBytes, 0x8C);
    }

    *f32_at(particleBytes, 0x84) = *(float*)(payload + 0x10C);
    *f32_at(particleBytes, 0x88) = *(float*)(payload + 0x114);
    if (*(float*)(payload + 0x110) != FLOAT_80330498) {
        *f32_at(particleBytes, 0x84) += FLOAT_803304c0 * *(float*)(payload + 0x110) * Math.RandF() - *(float*)(payload + 0x110);
    }
    *f32_at(particleBytes, 0x8C) = *(float*)(payload + 0xDC);
    *f32_at(particleBytes, 0x90) = *(float*)(payload + 0xE0);
    *f32_at(particleBytes, 0x94) = *(float*)(payload + 0xE4);

    switch (payload[0x134]) {
    case 1:
        *f32_at(particleBytes, 0x8C) *= Math.RandF();
        break;
    case 2:
        *f32_at(particleBytes, 0x90) *= Math.RandF();
        break;
    case 3: {
        float r = Math.RandF();
        *f32_at(particleBytes, 0x8C) *= r;
        *f32_at(particleBytes, 0x90) *= r;
        break;
    }
    case 4:
        *f32_at(particleBytes, 0x8C) *= Math.RandF();
        *f32_at(particleBytes, 0x90) *= Math.RandF();
        break;
    default:
        break;
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

    int alpha = vColor->m_alpha;
    u8* payload = (u8*)pRyjMegaBirthModel;
    u8* p = (u8*)particleData;
    Vec direction;
    Vec position;
    Vec step;

    if (particleColor != NULL) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] = particleColor->m_colorFrameDeltas[0] + *f32_at(payload, 0x3C);
        particleColor->m_colorFrameDeltas[1] = particleColor->m_colorFrameDeltas[1] + *f32_at(payload, 0x40);
        particleColor->m_colorFrameDeltas[2] = particleColor->m_colorFrameDeltas[2] + *f32_at(payload, 0x44);
        particleColor->m_colorFrameDeltas[3] = particleColor->m_colorFrameDeltas[3] + *f32_at(payload, 0x48);
        alpha = (int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    *s32_at(p, 0x38) += *s32_at(p, 0x44);
    *s32_at(p, 0x3C) += *s32_at(p, 0x48);
    *s32_at(p, 0x40) += *s32_at(p, 0x4C);

    if ((payload[0x133] & 0x10) != 0) {
        *s32_at(p, 0x44) += *s32_at(payload, 0x70) + *s32_at(p, 0x50);
        *s32_at(p, 0x48) += *s32_at(payload, 0x74) + *s32_at(p, 0x54);
        *s32_at(p, 0x4C) += *s32_at(payload, 0x78) + *s32_at(p, 0x58);
    } else {
        *s32_at(p, 0x44) += *s32_at(payload, 0x70);
        *s32_at(p, 0x48) += *s32_at(payload, 0x74);
        *s32_at(p, 0x4C) += *s32_at(payload, 0x78);
    }

    wrap_particle_rotation_triplet_s32(p, 0x38);

    *f32_at(p, 0x5C) = *f32_at(p, 0x5C) + *f32_at(p, 0x68);
    *f32_at(p, 0x60) = *f32_at(p, 0x60) + *f32_at(p, 0x6C);
    *f32_at(p, 0x64) = *f32_at(p, 0x64) + *f32_at(p, 0x70);

    if ((payload[0x132] & 0x10) != 0) {
        *f32_at(p, 0x68) += *(float*)(payload + 0xB0) + *f32_at(p, 0x74);
        *f32_at(p, 0x6C) += *(float*)(payload + 0xB4) + *f32_at(p, 0x78);
        *f32_at(p, 0x70) += *(float*)(payload + 0xB8) + *f32_at(p, 0x7C);
    } else {
        *f32_at(p, 0x68) += *(float*)(payload + 0xB0);
        *f32_at(p, 0x6C) += *(float*)(payload + 0xB4);
        *f32_at(p, 0x70) += *(float*)(payload + 0xB8);
    }

    *f32_at(p, 0x80) += *(float*)(payload + 0x10C);
    if (payload[0x13B] == 0) {
        if ((FLOAT_80330498 < *(float*)(payload + 0x108)) &&
            (*(float*)(payload + 0x10C) < FLOAT_80330498)) {
            if (*f32_at(p, 0x80) < FLOAT_80330498) {
                *f32_at(p, 0x80) = FLOAT_80330498;
            }
        } else {
            if ((*(float*)(payload + 0x108) < FLOAT_80330498) &&
                (FLOAT_80330498 < *(float*)(payload + 0x10C)) &&
                (FLOAT_80330498 < *f32_at(p, 0x80))) {
                *f32_at(p, 0x80) = FLOAT_80330498;
            }
        }
    }

    *f32_at(p, 0x84) += *(float*)(payload + 0x118);
    direction.x = particleData->m_matrix[0][1];
    direction.y = particleData->m_matrix[1][1];
    direction.z = particleData->m_matrix[2][1];
    pppScaleVectorXYZ(step, direction, *f32_at(p, 0x80));
    position.x = particleData->m_matrix[0][3];
    position.y = particleData->m_matrix[1][3];
    position.z = particleData->m_matrix[2][3];
    pppAddVector(position, position, step);
    pppScaleVectorXYZ(step, vRyjMegaBirthModel->m_accelerationAxis, *f32_at(p, 0x84));
    pppAddVector(position, position, step);
    particleData->m_matrix[0][3] = position.x;
    particleData->m_matrix[1][3] = position.y;
    particleData->m_matrix[2][3] = position.z;

    *f32_at(p, 0x88) += *f32_at(p, 0x90);
    *f32_at(p, 0x8C) += *f32_at(p, 0x94);
    *f32_at(p, 0x90) += *(float*)(payload + 0xD8);
    *f32_at(p, 0x94) += *(float*)(payload + 0xE4);

    if (*(u16*)(payload + 0x26) != 0) {
        *u16_at(p, 0x30) = *u16_at(p, 0x30) - 1;
    }

    *u8_at(p, 0x9c) = *u8_at(p, 0x9c) + 1;

    if ((*u8_at(p, 0x9d) != 0) && (*u8_at(p, 0x9c) <= *u8_at(p, 0x9d))) {
        float fadeAlpha = (float)alpha;
        float fadeFrameCount = (float)(unsigned int)*u8_at(p, 0x9d);
        float particleAlpha = *f32_at(p, 0x98);

        *f32_at(p, 0x98) = particleAlpha - fadeAlpha / fadeFrameCount;
    }

    if ((*u8_at(p, 0x9e) != 0) && (*u16_at(p, 0x30) <= *u8_at(p, 0x9e))) {
        float fadeAlpha = (float)alpha;
        float fadeFrameCount = (float)(unsigned int)payload[0x29];
        float particleAlpha = *f32_at(p, 0x98);

        *f32_at(p, 0x98) = particleAlpha + fadeAlpha / fadeFrameCount;
    }
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
    u8* payload = (u8*)params;
    VColor* baseColor = (VColor*)(obj->m_workArea + ctrlTable->m_serializedDataOffsets[1]);
    VRyjMegaBirthModel* work =
        (VRyjMegaBirthModel*)(obj->m_workArea + ctrlTable->m_serializedDataOffsets[2]);
    _PARTICLE_DATA* particleBlock = work->m_particleBlock;
    PARTICLE_WMAT* particleWorldMatrixBlock = work->m_worldMatrixBlock;
    _PARTICLE_COLOR* colorBlock = work->m_colorBlock;
    s32 numParticles = work->m_numParticles;
    s8 hasRequiredMemory;

    if (particleBlock == NULL) {
        hasRequiredMemory = 0;
    } else if ((payload[0x136] != 0) && (particleWorldMatrixBlock == NULL)) {
        hasRequiredMemory = 0;
    } else if ((payload[0x131] != 0) && (colorBlock == NULL)) {
        hasRequiredMemory = 0;
    } else {
        hasRequiredMemory = 1;
    }

    if (!hasRequiredMemory) {
        return;
    }

    int modelIndex = *(int*)(payload + 4);
    if (modelIndex == 0xFFFF) {
        return;
    }

    pppFMATRIX emitterMatrix;
    pppFMATRIX scratchMatrix;

    init_matrix(obj, emitterMatrix, params, work);
    pppUnitMatrix(scratchMatrix);
    pppInitBlendMode();
    pppSetBlendMode(0);

    for (int i = 0; i < numParticles; i++) {
        _PARTICLE_DATA* particle = (_PARTICLE_DATA*)((u8*)particleBlock + i * 0xA0);
        _PARTICLE_WMAT* particleWorldMatrix = 0;
        _PARTICLE_COLOR* particleColor = 0;

        if (*s16_at(particle, 0x22) == 0) {
            continue;
        }

        if (particleWorldMatrixBlock != NULL) {
            particleWorldMatrix = (_PARTICLE_WMAT*)(particleWorldMatrixBlock + i);
        }
        if (colorBlock != NULL) {
            particleColor = colorBlock + i;
        }

        pppFMATRIX drawMatrix;
        int red = baseColor->m_red + (int)*(s8*)((u8*)particle + 0x32);
        int green = baseColor->m_green + (int)*(s8*)((u8*)particle + 0x33);
        int blue = baseColor->m_blue + (int)*(s8*)((u8*)particle + 0x34);
        int alpha = baseColor->m_alpha + (int)*(s8*)((u8*)particle + 0x35) - (int)*f32_at(particle, 0x98);

        if (particleColor != NULL) {
            red += (int)particleColor->m_color[0];
            green += (int)particleColor->m_color[1];
            blue += (int)particleColor->m_color[2];
            alpha += (int)particleColor->m_color[3];
        }

        pppCVECTOR drawColor = {{
            clamp_u8_int(red),
            clamp_u8_int(green),
            clamp_u8_int(blue),
            clamp_alpha_7f(alpha),
        }};

        set_matrix(obj, emitterMatrix, scratchMatrix, params, particle, particleWorldMatrix, drawMatrix, payload[0x0D]);
        GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)drawColor.rgba);

        pppCopyMatrix(*(pppFMATRIX*)&g_matTmp, obj->m_localMatrix);
        pppMulMatrix(obj->m_localMatrix, obj->m_localMatrix, *(pppFMATRIX*)&g_matKeep);

        pppSetDrawEnv(&drawColor, &obj->m_drawMatrix,
                      payload[0x0D] != 0 ? *(float*)(payload + 0x18) : FLOAT_80330498,
                      payload[0x13F], payload[0x09], payload[0x13C], payload[0x13D],
                      payload[0x13A], 1, 0);
        MaterialMan.SetTexScroll(*f32_at(particle, 0x88) + *f32_at(particle, 0x90),
                                 *f32_at(particle, 0x8C) + *f32_at(particle, 0x94),
                                 FLOAT_80330498, FLOAT_80330498);
        pppSetBlendMode(payload[0x13C]);
        pppDrawMesh((pppModelSt*)ppvEnv->m_mapMeshPtr[modelIndex], obj->m_drawMatrixPtr, 1);
        pppCopyMatrix(obj->m_localMatrix, *(pppFMATRIX*)&g_matTmp);
    }
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
        out.value[0][0] = ppvMng->m_scale.x;
        out.value[1][1] = ppvMng->m_scale.y;
        out.value[2][2] = ppvMng->m_scale.z;
        out.value[0][3] = ppvMng->m_position.x;
        out.value[1][3] = ppvMng->m_position.y;
        out.value[2][3] = ppvMng->m_position.z;
        break;
    case 8:
        PSMTXIdentity(out.value);
        out.value[0][3] = work->m_currentPosition.x;
        out.value[1][3] = work->m_currentPosition.y;
        out.value[2][3] = work->m_currentPosition.z;
        break;
    default:
        PSMTXCopy(ppvMng->m_matrix.value, out.value);
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
    const u8 flagsMatrix = payload[0x135];
    const u8 flagsEnd = payload[0x137];
    pppFMATRIX tmp;
    Mtx scale;
    pppFMATRIX* objectMatrix = &pObject->m_drawMatrix;
    bool copyOutMatrix = true;

    if (flagsMatrix == 0) {
        pppUnitMatrix(mtxB);
        mtxB.value[0][3] = particleData->m_matrix[0][3];
        mtxB.value[1][3] = particleData->m_matrix[1][3];
        mtxB.value[2][3] = particleData->m_matrix[2][3];
    } else {
        pppCopyMatrix(mtxB, *(pppFMATRIX*)&particleData->m_matrix);
    }

    if (*s32_at(particleData, 0x38) != 0 ||
        *s32_at(particleData, 0x3C) != 0 ||
        *s32_at(particleData, 0x40) != 0) {
        Vec rot;
        rot.x = (FLOAT_803304a0 * (float)-*s32_at(particleData, 0x38)) / FLOAT_803304a4;
        rot.y = (FLOAT_803304a0 * (float)-*s32_at(particleData, 0x3C)) / FLOAT_803304a4;
        rot.z = (FLOAT_803304a0 * (float)-*s32_at(particleData, 0x40)) / FLOAT_803304a4;
        pppFMATRIX r;
        pppUnitMatrix(r);
        pppRotMatrix(r, r, rot);
        pppCopyMatrix(tmp, mtxB);
        pppMulMatrix(mtxB, tmp, r);
    }

    PSMTXScale(scale, *f32_at(particleData, 0x5C), *f32_at(particleData, 0x60), *f32_at(particleData, 0x64));
    pppCopyMatrix(tmp, mtxB);
    pppMulMatrix(mtxB, tmp, *(pppFMATRIX*)&scale);
    pppCopyMatrix(*(pppFMATRIX*)&g_matKeep, mtxB);

    switch (matrixMode) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 9: {
        Vec localPos;
        Vec transformedPos;

        localPos.x = mtxB.value[0][3];
        localPos.y = mtxB.value[1][3];
        localPos.z = mtxB.value[2][3];
        pppApplyMatrix(transformedPos, mtxA, localPos);

        pppCopyMatrix(tmp, mtxB);
        pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvWorldMatrixWood, tmp);
        mtxB.value[0][3] = transformedPos.x;
        mtxB.value[1][3] = transformedPos.y;
        mtxB.value[2][3] = transformedPos.z;
        break;
    }
    default:
        pppCopyMatrix(tmp, mtxB);
        pppMulMatrix(mtxB, *(pppFMATRIX*)&pObject->m_localMatrix, tmp);

        if (particleWMat != NULL) {
            pppCopyMatrix(tmp, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)particleWMat, tmp);
        } else {
            pppCopyMatrix(tmp, mtxB);
            pppMulMatrix(mtxB, ppvMng->m_matrix, tmp);
            copyOutMatrix = false;
        }
        break;
    }

    if (matrixMode != 1 && matrixMode != 3 && matrixMode != 5 && matrixMode != 7 && matrixMode != 9) {
        pppCopyMatrix(tmp, mtxB);
        pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvCameraMatrix0, tmp);
        pppCopyMatrix(*objectMatrix, mtxB);
    }

    if ((copyOut != 0) && copyOutMatrix) {
        pppCopyMatrix(out, mtxB);
    }

    if (flagsEnd != 0) {
        Vec objectPos;
        Vec endPos;

        objectPos.x = pObject->m_localMatrix.value[0][3];
        objectPos.y = pObject->m_localMatrix.value[1][3];
        objectPos.z = pObject->m_localMatrix.value[2][3];

        endPos.x = mtxB.value[0][3];
        endPos.y = mtxB.value[1][3];
        endPos.z = mtxB.value[2][3];
        pppAddVector(endPos, endPos, objectPos);

        pppUnitMatrix(mtxB);
        PSMTXScaleApply(mtxB.value, objectMatrix->value, *f32_at(particleData, 0x5C) * ppvMng->m_scale.x,
                        *f32_at(particleData, 0x60) * ppvMng->m_scale.y,
                        *f32_at(particleData, 0x64) * ppvMng->m_scale.z);
        PSMTXMultVec(ppvWorldMatrix, &endPos, &endPos);

        pppFMATRIX rot;

        PSMTXRotRad(rot.value, 'z', FLOAT_803304a8 * (float)*s32_at(particleData, 0x40));
        pppCopyMatrix(tmp, *objectMatrix);
        pppMulMatrix(*objectMatrix, rot, tmp);

        objectMatrix->value[0][3] = endPos.x;
        objectMatrix->value[1][3] = endPos.y;
        objectMatrix->value[2][3] = endPos.z;
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
    VRyjMegaBirthModel* work =
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);
    float value1;
    float value0;

    memset(&work->m_accelerationAxis, 0, sizeof(work->m_accelerationAxis));
    work->m_particleBlock = 0;
    value0 = FLOAT_80330498;
    work->m_worldMatrixBlock = 0;
    value1 = FLOAT_8033049c;
    work->m_colorBlock = 0;
    work->m_numParticles = 0;
    work->m_emitTimer = 10000;
    work->m_unused1E = 0;
    work->m_previousPosition.x = value0;
    work->m_previousPosition.y = value1;
    work->m_previousPosition.z = value0;
    work->m_currentPosition.x = value0;
    work->m_currentPosition.y = value1;
    work->m_currentPosition.z = value0;
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
    VRyjMegaBirthModel* work =
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);

    if (work->m_particleBlock != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_particleBlock));
        work->m_particleBlock = 0;
    }

    if (work->m_worldMatrixBlock != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_worldMatrixBlock));
        work->m_worldMatrixBlock = 0;
    }

    if (work->m_colorBlock != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(work->m_colorBlock));
        work->m_colorBlock = 0;
    }
}
