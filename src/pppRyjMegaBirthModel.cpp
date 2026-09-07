#include "global.h"
#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include <stddef.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

extern const float kPppRyjMegaBirthSharedZero;
extern const float kPppRyjMegaBirthModelInitialY;
extern const float kPppRyjMegaBirthPi;
extern const float kPppRyjMegaBirthAngleIndexScale;

static _PARTICLE_WMAT g_matKeep;
static _PARTICLE_WMAT g_matTmp;

static const char s_pppRyjMegaBirthModel_cpp[] = "pppRyjMegaBirthModel.cpp";

STATIC_ASSERT(sizeof(RyjMegaBirthModelDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(RyjMegaBirthModelDataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(RyjMegaBirthModelDataOffsets, m_workOffset) == 0x8);

static inline RyjMegaBirthModelDataOffsets* GetRyjMegaBirthModelDataOffsets(PRyjMegaBirthModelOffsets* offsets)
{
    return reinterpret_cast<RyjMegaBirthModelDataOffsets*>(offsets->m_serializedDataOffsets);
}

static inline RyjMegaBirthModelDataOffsets* GetRyjMegaBirthModelDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<RyjMegaBirthModelDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

extern const float kPppRyjMegaBirthModelDegToRad = 0.017453292f;
extern const double kPppRyjMegaBirthModelSignedIntBias = 4503601774854144.0;
extern const double kPppRyjMegaBirthModelUnsignedIntBias = 4503599627370496.0;
extern const float kPppRyjMegaBirthModelTwoF = 2.0f;
extern const float kPppRyjMegaBirthModelDegrees180 = 180.0f;
extern const float kPppRyjMegaBirthModelOneF = 1.0f;
extern const float kPppRyjMegaBirthModelSpeedFalloff = 0.7f;
extern const float kPppRyjMegaBirthModelHalfF = 0.5f;
extern const double kPppRyjMegaBirthModelOneF64 = 1.0;
extern const double kPppRyjMegaBirthModelHalfF64 = 0.5;
extern const float kPppRyjMegaBirthModelNegativeOne = -1.0f;

STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_modelIndex) == 0x04);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_fogIndex) == 0x09);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_useEnvDepth) == 0x0D);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_drawDepth) == 0x18);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_maxParticles) == 0x20);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_emitCount) == 0x22);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_emitInterval) == 0x24);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_life) == 0x26);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_fadeOutFrames) == 0x28);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_fadeInFrames) == 0x29);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_spawnMode) == 0x2A);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_spread) == 0x2B);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_colorRandom) == 0x2C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_colorDeltaAdds) == 0x3C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_colorFrameDeltas) == 0xBC);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollUStepDelta) == 0xD8);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollVStart) == 0xDC);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollUStep) == 0xE0);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollVStep) == 0xE4);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_baseDirection) == 0xE8);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_accelerationAxis) == 0xF8);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_directionVelocityStart) == 0x108);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_directionVelocityStep) == 0x10C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_directionVelocityRandom) == 0x110);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_acceleration) == 0x114);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_accelerationStep) == 0x118);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_directionScale) == 0x120);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_speed) == 0x11C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_speedMode) == 0x130);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_enableParticleColor) == 0x131);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_rotationRandomFlags) == 0x132);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_scaleRandomFlags) == 0x133);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScaleRandomMode) == 0x134);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_matrixMode) == 0x135);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_enableWorldMatrix) == 0x136);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_matrixFinalizeMode) == 0x137);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_zEnable) == 0x13A);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_clampDirectionalSpeed) == 0x13B);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_blendMode) == 0x13C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_cullMode) == 0x13D);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_lightTarget) == 0x13F);
STATIC_ASSERT(sizeof(PRyjMegaBirthModel) == 0x140);

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
    return kPppRyjMegaBirthModelSpeedFalloff;
}

static inline float MegaBirthHalf()
{
    return kPppRyjMegaBirthModelHalfF;
}

static inline double MegaBirthHalfDouble()
{
    return kPppRyjMegaBirthModelHalfF64;
}

static inline void wrap_particle_rotation_triplet_s32(u8* particleBytes, s32 offset)
{
    s32 count;
    for (count = 3; count != 0; count--) {
        s32* value = s32_at(particleBytes, offset);
        if (*value >= 0x8000) {
            while (*value >= 0x8000) { *value -= 0x10000; }
        } else if (*value < -0x8000) {
            while (*value < -0x8000) { *value += 0x10000; }
        }
        particleBytes += 4;
    }
}

static inline void wrap_birth_angle(s32* value, s32 limit)
{
    s32 v = *value;
    if ((v >= limit) || (v < -0x8000)) {
        s32 w = *value;
        u32 shifted = (u32)(w << 0x11);
        u32 sign = (u32)w >> 0x1F;
        u32 y = shifted - sign;
        u32 rotated = __rlwinm(y, 0xF, 0, 0x1F);
        *value = (s32)(rotated + sign);
    }
}

static inline signed char random_signed_byte_span(u8 span)
{
    (void)Math.RandF();
    return (signed char)((s32)((float)(span << 1) * Math.RandF() - (float)(span >> 1)));
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
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + GetRyjMegaBirthModelDataOffsets(offsets)->m_workOffset);
    VColor* color =
        reinterpret_cast<VColor*>(pObject->m_workArea + GetRyjMegaBirthModelDataOffsets(offsets)->m_colorOffset);
    u8* payload = (u8*)params;

    if (work->m_particleBlock == 0) {
        work->m_numParticles = params->m_maxParticles;
        work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_numParticles * 0xA0, ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0x8D);
        if (work->m_particleBlock != NULL) {
            memset(work->m_particleBlock, 0, work->m_numParticles * 0xA0);
        }

        if (params->m_enableWorldMatrix != 0) {
            work->m_worldMatrixBlock = (_PARTICLE_WMAT*)pppMemAlloc(
                work->m_numParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0x97);
            if (work->m_worldMatrixBlock != NULL) {
                memset(work->m_worldMatrixBlock, 0, work->m_numParticles * sizeof(_PARTICLE_WMAT));
            }
        }

        if (params->m_enableParticleColor != 0) {
            work->m_colorBlock = (_PARTICLE_COLOR*)pppMemAlloc(
                work->m_numParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr,
                const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0xA2);
            if (work->m_colorBlock != NULL) {
                memset(work->m_colorBlock, 0, work->m_numParticles * sizeof(_PARTICLE_COLOR));
            }
        }

        work->m_accelerationAxis = params->m_accelerationAxis;
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
    } else if ((params->m_enableWorldMatrix != 0) && (work->m_worldMatrixBlock == 0)) {
        hasRequiredMemory = false;
    } else if ((params->m_enableParticleColor != 0) && (work->m_colorBlock == 0)) {
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
    particleWMat = work->m_worldMatrixBlock;
    particleColor = work->m_colorBlock;
    maxParticles = work->m_numParticles;
    emitTimer = &work->m_emitTimer;

    if (ppvUserStopPartF == 0) {
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
                if ((params->m_emitInterval <= *emitTimer) && (emitted < (s32)(u32)params->m_emitCount)) {
                    birth(pObject, work, params, color, particleData, particleWMat, particleColor);
                    emitted = emitted + 1;
                }
            }

            if (particleWMat) {
                particleWMat++;
            }
            if (particleColor) {
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
#pragma push
#pragma optimization_level 3
#pragma global_optimizer off
void birth(
    _pppPObject* pObject, VRyjMegaBirthModel* work, PRyjMegaBirthModel* params, VColor* color,
    _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    (void)pObject;
    Vec rowX;
    Vec rowY;
    Vec rowZ;
    Vec rowPos;
    u8* payload = (u8*)params;
    float spread = (float)params->m_spread;
    float halfSpread = spread;
    float randomRange = kPppRyjMegaBirthModelTwoF * spread;

    memset(particleData, 0, 0xA0);
    if (particleWMat) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    pppUnitMatrix(*(pppFMATRIX*)&particleData->m_matrix);

    if ((s32)params->m_spawnMode < 8 && (s32)params->m_spawnMode >= 0) {
        Vec baseDirection;
        Vec angles;
        pppFMATRIX rotMatrix;

        baseDirection.x = params->m_baseDirection.x;
        baseDirection.y = params->m_baseDirection.y;
        baseDirection.z = params->m_baseDirection.z;
        angles.x = (float)(randomRange * Math.RandF() - halfSpread);
        angles.x = (kPppRyjMegaBirthAngleIndexScale * angles.x) / kPppRyjMegaBirthModelDegrees180;
        angles.y = (float)(randomRange * Math.RandF() - halfSpread);
        angles.y = (kPppRyjMegaBirthAngleIndexScale * angles.y) / kPppRyjMegaBirthModelDegrees180;
        angles.z = (float)(randomRange * Math.RandF() - halfSpread);
        angles.z = (kPppRyjMegaBirthAngleIndexScale * angles.z) / kPppRyjMegaBirthModelDegrees180;

        if ((params->m_spawnMode == 2) || (params->m_spawnMode == 3)) {
            angles.x = kPppRyjMegaBirthSharedZero;
            angles.y = kPppRyjMegaBirthSharedZero;
        }

        pppUnitMatrix(rotMatrix);
        pppRotMatrix(rotMatrix, rotMatrix, angles);

        rowY.x = particleData->m_matrix[0][1];
        rowY.y = particleData->m_matrix[1][1];
        rowY.z = particleData->m_matrix[2][1];
        pppApplyMatrix(rowY, rotMatrix, baseDirection);
        rowY.x *= params->m_directionScale.x;
        rowY.y *= params->m_directionScale.y;
        rowY.z *= params->m_directionScale.z;
        particleData->m_matrix[0][1] = rowY.x;
        particleData->m_matrix[1][1] = rowY.y;
        particleData->m_matrix[2][1] = rowY.z;
        pppGetRowVector(*(pppFMATRIX*)&particleData->m_matrix, rowX, rowY, rowZ, rowPos);
        pppNormalize(rowY, rowY);
        pppOuterProduct(rowZ, rowY, rowX);
        pppNormalize(rowZ, rowZ);
        pppOuterProduct(rowX, rowZ, rowY);
        pppNormalize(rowX, rowX);
        pppSetRowVector(*(pppFMATRIX*)&particleData->m_matrix, rowX, rowY, rowZ, rowPos);

        pppFMATRIX basis;
        Vec direction;
        Vec right;
        Vec directionCopy;
        Vec worldUp;
        float translationX;
        float translationY;
        float translationZ;

        pppUnitMatrix(basis);
        direction.x = particleData->m_matrix[0][1];
        direction.y = particleData->m_matrix[1][1];
        direction.z = particleData->m_matrix[2][1];
        translationX = particleData->m_matrix[0][3];
        translationY = particleData->m_matrix[1][3];
        translationZ = particleData->m_matrix[2][3];
        pppNormalize(direction, direction);
        pppCopyVector(directionCopy, direction);

        worldUp.x = kPppRyjMegaBirthSharedZero;
        worldUp.y = kPppRyjMegaBirthSharedZero;
        worldUp.z = kPppRyjMegaBirthModelOneF;
        pppOuterProduct(right, directionCopy, worldUp);
        pppNormalize(right, right);
        pppOuterProduct(worldUp, right, direction);
        pppNormalize(worldUp, worldUp);

        pppUnitMatrix(basis);
        basis.value[0][0] = right.x;
        basis.value[1][0] = right.y;
        basis.value[2][0] = right.z;
        basis.value[0][1] = direction.x;
        basis.value[1][1] = direction.y;
        basis.value[2][1] = direction.z;
        basis.value[0][2] = worldUp.x;
        basis.value[1][2] = worldUp.y;
        basis.value[2][2] = worldUp.z;
        basis.value[0][3] = translationX;
        basis.value[1][3] = translationY;
        basis.value[2][3] = translationZ;
        pppCopyMatrix(*(pppFMATRIX*)&particleData->m_matrix, basis);
    }

    s32 mode = params->m_spawnMode;
    if (mode < 6) {
        if (mode >= 4) {
            goto spawn_speed_block;
        }
    } else if (mode < 10) {
        goto mesh_block;
    }

        float speedScalar = params->m_speed;
        if (kPppRyjMegaBirthSharedZero != speedScalar) {
            float dr1;
            float dr2;
            float dr3;

            switch (params->m_speedMode) {
            case 1:
                (void)Math.RandF();
                speedScalar = params->m_speed * Math.RandF();
                break;
            case 2:
                dr3 = Math.RandF();
                speedScalar = (params->m_speed * Math.RandF()) * dr3;
                break;
            case 3:
                dr3 = Math.RandF();
                speedScalar = -(MegaBirthSpeedFalloff() * ((params->m_speed * Math.RandF()) * dr3) - params->m_speed);
                break;
            case 4:
                dr1 = Math.RandF();
                dr2 = Math.RandF();
                dr3 = Math.RandF();
                speedScalar = Math.RandF() * (dr3 * ((params->m_speed * dr2) * dr1));
                break;
            case 5:
                dr2 = Math.RandF();
                dr3 = Math.RandF();
                speedScalar = -(MegaBirthHalf() * (Math.RandF() * ((params->m_speed * dr3) * dr2)) - params->m_speed);
                break;
            default:
                break;
            }

            rowY.x = particleData->m_matrix[0][1];
            rowY.y = particleData->m_matrix[1][1];
            rowY.z = particleData->m_matrix[2][1];
            rowPos.x = particleData->m_matrix[0][3];
            rowPos.y = particleData->m_matrix[1][3];
            rowPos.z = particleData->m_matrix[2][3];
            pppScaleVectorXYZ(rowPos, rowY, speedScalar);
            particleData->m_matrix[0][3] = rowPos.x;
            particleData->m_matrix[1][3] = rowPos.y;
            particleData->m_matrix[2][3] = rowPos.z;
        }
    goto join_position;

spawn_speed_block:
    if (kPppRyjMegaBirthSharedZero != params->m_speed) {
            float halfSpeed = MegaBirthHalf() * params->m_speed;
            u8 speedMode = params->m_speedMode;
            float t;
            float r1;
            float r2;
            float r3;

            switch (speedMode) {
            default:
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                rowPos.x = params->m_speed * Math.RandF();
                rowPos.x -= halfSpeed;
                rowPos.y = params->m_speed * Math.RandF();
                rowPos.y -= halfSpeed;
                rowPos.z = params->m_speed * Math.RandF();
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            case 1:
                (void)Math.RandF();
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                rowPos.x = params->m_speed * Math.RandF();
                rowPos.x -= halfSpeed;
                rowPos.y = params->m_speed * Math.RandF();
                rowPos.y -= halfSpeed;
                rowPos.z = params->m_speed * Math.RandF();
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            case 2:
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                r3 = Math.RandF();
                rowPos.x = (params->m_speed * Math.RandF()) * r3;
                rowPos.x -= halfSpeed;
                r3 = Math.RandF();
                rowPos.y = (params->m_speed * Math.RandF()) * r3;
                rowPos.y -= halfSpeed;
                r3 = Math.RandF();
                rowPos.z = (params->m_speed * Math.RandF()) * r3;
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            case 3:
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                r3 = Math.RandF();
                rowPos.x = -(MegaBirthSpeedFalloff() * ((params->m_speed * Math.RandF()) * r3) - params->m_speed);
                rowPos.x -= halfSpeed;
                r3 = Math.RandF();
                rowPos.y = -(MegaBirthSpeedFalloff() * ((params->m_speed * Math.RandF()) * r3) - params->m_speed);
                rowPos.y -= halfSpeed;
                r3 = Math.RandF();
                rowPos.z = -(MegaBirthSpeedFalloff() * ((params->m_speed * Math.RandF()) * r3) - params->m_speed);
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            case 4:
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                r1 = Math.RandF();
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.x = Math.RandF() * (r3 * ((params->m_speed * r2) * r1));
                rowPos.x -= halfSpeed;
                r1 = Math.RandF();
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.y = Math.RandF() * (r3 * ((params->m_speed * r2) * r1));
                rowPos.y -= halfSpeed;
                r1 = Math.RandF();
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.z = Math.RandF() * (r3 * ((params->m_speed * r2) * r1));
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            case 5:
                t = particleData->m_matrix[0][3];
                rowPos.x = t;
                t = particleData->m_matrix[1][3];
                rowPos.y = t;
                t = particleData->m_matrix[2][3];
                rowPos.z = t;
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.x = -(MegaBirthHalf() * (Math.RandF() * ((params->m_speed * r3) * r2)) - params->m_speed);
                rowPos.x -= halfSpeed;
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.y = -(MegaBirthHalf() * (Math.RandF() * ((params->m_speed * r3) * r2)) - params->m_speed);
                rowPos.y -= halfSpeed;
                r2 = Math.RandF();
                r3 = Math.RandF();
                rowPos.z = -(MegaBirthHalf() * (Math.RandF() * ((params->m_speed * r3) * r2)) - params->m_speed);
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            }

            float speedY = particleData->m_matrix[1][3];
            float scaleY = params->m_directionScale.y;
            float speedZ = particleData->m_matrix[2][3];
            float scaleZ = params->m_directionScale.z;
            particleData->m_matrix[0][3] = particleData->m_matrix[0][3] * params->m_directionScale.x;
            particleData->m_matrix[1][3] = speedY * scaleY;
            particleData->m_matrix[2][3] = speedZ * scaleZ;
        }
    goto join_position;

mesh_block:
    {

        s16 pathIndex = *(s16*)(payload + 0x138);
        Vec* pathBase = pObject->m_drawMatrixPtr;

        if (pathIndex >= 0) {
            s16* pathInfo = reinterpret_cast<s16*>(ppvEnv->m_shapeGroupPtr + (pathIndex));
            float t;
            float vx;
            float vy;
            float vz;
            float m1;
            float m2;
            float m3;
            float m4;

            if (!pathBase) {
                pathBase = (Vec*)ppvEnv->m_mapMeshPtr[pathInfo[0]]->m_vertices;
            }

            switch (params->m_speedMode) {
            default: {
                if ((s32)work->m_unused1E >= (s32)pathInfo[1]) {
                    work->m_unused1E = 0;
                }
                u16 sampleIndex = work->m_unused1E;
                u16* indices = (u16*)*(int*)(pathInfo + 2);
                work->m_unused1E = sampleIndex + 1;
                Vec* pathVec = pathBase + indices[sampleIndex];
                vx = pathVec->x;
                vy = pathVec->y;
                vz = pathVec->z;
                goto have_vec;
            }
            case 1:
                (void)Math.RandF();
                t = Math.RandF();
                break;
            case 2:
                m2 = Math.RandF();
                m3 = Math.RandF();
                t = Math.RandF() * (m3 * m2);
                break;
            case 3:
                m2 = Math.RandF();
                m3 = Math.RandF();
                t = (float)(kPppRyjMegaBirthModelOneF64 - (double)(Math.RandF() * (m3 * m2)));
                break;
            case 4:
                m1 = Math.RandF();
                m2 = Math.RandF();
                m3 = Math.RandF();
                t = Math.RandF() * (m3 * (m2 * m1));
                break;
            case 5:
                m1 = Math.RandF();
                m2 = Math.RandF();
                m3 = Math.RandF();
                m4 = Math.RandF();
                t = (float)(kPppRyjMegaBirthModelOneF64 - (double)(Math.RandF() * (m4 * (m3 * (m2 * m1)))));
                break;
            }
            {
                if ((s32)work->m_unused1E >= (s32)pathInfo[1]) {
                    work->m_unused1E = 0;
                }
                s32 sampleIndex = (s32)(t * (float)pathInfo[1]);
                Vec* pathVec = pathBase + ((u16*)*(int*)(pathInfo + 2))[sampleIndex];
                vx = pathVec->x;
                vy = pathVec->y;
                vz = pathVec->z;
            }
        have_vec:
            t = particleData->m_matrix[0][3];
            rowPos.x = t;
            t = particleData->m_matrix[1][3];
            rowPos.y = t;
            t = particleData->m_matrix[2][3];
            rowPos.z = t;
            rowPos.x = vx * params->m_directionScale.x;
            rowPos.y = vy * params->m_directionScale.y;
            rowPos.z = vz * params->m_directionScale.z;
            particleData->m_matrix[0][3] = rowPos.x;
            particleData->m_matrix[1][3] = rowPos.y;
            particleData->m_matrix[2][3] = rowPos.z;

            u8 finalizeMode = params->m_spawnMode;
            if ((finalizeMode == 8) || (finalizeMode == 9)) {
                pppGetRowVector(*(pppFMATRIX*)&particleData->m_matrix, rowX, rowY, rowZ, rowPos);
                pppNormalize(rowY, rowPos);
                rowY.x = rowY.x * params->m_directionScale.x;
                rowY.y = rowY.y * params->m_directionScale.y;
                rowY.z = rowY.z * params->m_directionScale.z;
                particleData->m_matrix[0][1] = rowY.x;
                particleData->m_matrix[1][1] = rowY.y;
                particleData->m_matrix[2][1] = rowY.z;
                pppNormalize(rowY, rowY);
                pppOuterProduct(rowZ, rowY, rowX);
                pppNormalize(rowZ, rowZ);
                pppOuterProduct(rowX, rowZ, rowY);
                pppNormalize(rowX, rowX);
                pppSetRowVector(*(pppFMATRIX*)&particleData->m_matrix, rowX, rowY, rowZ, rowPos);
            }
        }
        goto join_position;
    }

join_position:
    {
        u8* particleBytes = (u8*)particleData;

        particleBytes[0x32] = random_signed_byte_span(payload[0x4C]);
        particleBytes[0x33] = random_signed_byte_span(payload[0x4D]);
        particleBytes[0x34] = random_signed_byte_span(payload[0x4E]);
        particleBytes[0x35] = random_signed_byte_span(payload[0x4F]);
    }

    if (params->m_fadeOutFrames != 0) {
        *f32_at(particleData, 0x98) = static_cast<float>(color->m_alpha);
        *u8_at(particleData, 0x9D) = params->m_fadeOutFrames;
    }
    if (params->m_fadeInFrames != 0) {
        *u8_at(particleData, 0x9E) = params->m_fadeInFrames;
    }

    *s32_at(particleData, 0x38) = *(s32*)(payload + 0x50);
    *s32_at(particleData, 0x3C) = *(s32*)(payload + 0x54);
    *s32_at(particleData, 0x40) = *(s32*)(payload + 0x58);
    *s32_at(particleData, 0x44) = *(s32*)(payload + 0x60);
    *s32_at(particleData, 0x48) = *(s32*)(payload + 0x64);
    *s32_at(particleData, 0x4C) = *(s32*)(payload + 0x68);

    if (params->m_scaleRandomFlags != 0) {
        if ((params->m_scaleRandomFlags & 0x20) != 0) {
            s32 randomized = (s32)((float)*(s32*)(payload + 0x80) * Math.RandF());
            *s32_at(particleData, 0x58) = randomized;
            *s32_at(particleData, 0x54) = randomized;
            *s32_at(particleData, 0x50) = randomized;

            u8 scaleBits = params->m_scaleRandomFlags;
            if (((scaleBits & 1) != 0) && ((scaleBits & 2) != 0)) {
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    *s32_at(particleData, 0x50) = *s32_at(particleData, 0x50) * -1;
                    *s32_at(particleData, 0x54) = *s32_at(particleData, 0x54) * -1;
                    *s32_at(particleData, 0x58) = *s32_at(particleData, 0x58) * -1;
                }
            } else if ((scaleBits & 2) != 0) {
                *s32_at(particleData, 0x50) = *s32_at(particleData, 0x50) * -1;
                *s32_at(particleData, 0x54) = *s32_at(particleData, 0x54) * -1;
                *s32_at(particleData, 0x58) = *s32_at(particleData, 0x58) * -1;
            }
        } else {
            *s32_at(particleData, 0x50) = (s32)((float)*(s32*)(payload + 0x80) * Math.RandF());
            *s32_at(particleData, 0x54) = (s32)((float)*(s32*)(payload + 0x84) * Math.RandF());
            *s32_at(particleData, 0x58) = (s32)((float)*(s32*)(payload + 0x88) * Math.RandF());

            u8 scaleBits = params->m_scaleRandomFlags;
            if (((scaleBits & 1) != 0) && ((scaleBits & 2) != 0)) {
                double h = MegaBirthHalfDouble();
                u8* base = (u8*)particleData;
                s32 i;
                for (i = 0; i < 3; i++) {
                    if (h < (double)Math.RandF()) {
                        *(s32*)(base + 0x50) = *(s32*)(base + 0x50) * -1;
                    }
                    base += 4;
                }
            } else if ((scaleBits & 2) != 0) {
                *s32_at(particleData, 0x50) = *s32_at(particleData, 0x50) * -1;
                *s32_at(particleData, 0x54) = *s32_at(particleData, 0x54) * -1;
                *s32_at(particleData, 0x58) = *s32_at(particleData, 0x58) * -1;
            }
        }

        if ((params->m_scaleRandomFlags & 4) != 0) {
            *s32_at(particleData, 0x38) += *s32_at(particleData, 0x50);
            *s32_at(particleData, 0x3C) += *s32_at(particleData, 0x54);
            *s32_at(particleData, 0x40) += *s32_at(particleData, 0x58);
        }

        if ((params->m_scaleRandomFlags & 8) != 0) {
            *s32_at(particleData, 0x44) += *s32_at(particleData, 0x50);
            *s32_at(particleData, 0x48) += *s32_at(particleData, 0x54);
            *s32_at(particleData, 0x4C) += *s32_at(particleData, 0x58);
        }
    }

    {
        s32 wrapLimit = 0x8000;
        wrap_birth_angle(s32_at(particleData, 0x38), wrapLimit);
        wrap_birth_angle(s32_at(particleData, 0x3C), wrapLimit);
        wrap_birth_angle(s32_at(particleData, 0x40), wrapLimit);
    }

    *f32_at(particleData, 0x5C) = *(float*)(payload + 0x90);
    *f32_at(particleData, 0x60) = *(float*)(payload + 0x94);
    *f32_at(particleData, 0x64) = *(float*)(payload + 0x98);
    *f32_at(particleData, 0x68) = *(float*)(payload + 0xA0);
    *f32_at(particleData, 0x6C) = *(float*)(payload + 0xA4);
    *f32_at(particleData, 0x70) = *(float*)(payload + 0xA8);

    if (params->m_rotationRandomFlags != 0) {
        if ((params->m_rotationRandomFlags & 0x20) != 0) {
            float randomizedScale = *(float*)(payload + 0xC0) * Math.RandF();
            *f32_at(particleData, 0x7C) = randomizedScale;
            *f32_at(particleData, 0x78) = randomizedScale;
            *f32_at(particleData, 0x74) = randomizedScale;

            u8 rotBits = params->m_rotationRandomFlags;
            if (((rotBits & 1) != 0) && ((rotBits & 2) != 0)) {
                if (MegaBirthHalfDouble() < (double)Math.RandF()) {
                    float v74 = *f32_at(particleData, 0x74);
                    *f32_at(particleData, 0x74) = v74 * kPppRyjMegaBirthModelNegativeOne;
                    float v78 = *f32_at(particleData, 0x78);
                    *f32_at(particleData, 0x78) = v78 * kPppRyjMegaBirthModelNegativeOne;
                    float v7C = *f32_at(particleData, 0x7C);
                    *f32_at(particleData, 0x7C) = v7C * kPppRyjMegaBirthModelNegativeOne;
                }
            } else if ((rotBits & 2) != 0) {
                float v74 = *f32_at(particleData, 0x74);
                *f32_at(particleData, 0x74) = v74 * kPppRyjMegaBirthModelNegativeOne;
                float v78 = *f32_at(particleData, 0x78);
                *f32_at(particleData, 0x78) = v78 * kPppRyjMegaBirthModelNegativeOne;
                float v7C = *f32_at(particleData, 0x7C);
                *f32_at(particleData, 0x7C) = v7C * kPppRyjMegaBirthModelNegativeOne;
            }
        } else {
            *f32_at(particleData, 0x74) = *(float*)(payload + 0xC0) * Math.RandF();
            *f32_at(particleData, 0x78) = *(float*)(payload + 0xC4) * Math.RandF();
            *f32_at(particleData, 0x7C) = *(float*)(payload + 0xC8) * Math.RandF();

            u8 rotBits = params->m_rotationRandomFlags;
            if (((rotBits & 1) != 0) && ((rotBits & 2) != 0)) {
                double h = MegaBirthHalfDouble();
                u8* base = (u8*)particleData;
                s32 i;
                for (i = 0; i < 3; i++) {
                    if (h < (double)Math.RandF()) {
                        *(float*)(base + 0x74) = *(float*)(base + 0x74) * kPppRyjMegaBirthModelNegativeOne;
                    }
                    base += 4;
                }
            } else if ((rotBits & 2) != 0) {
                float v74 = *f32_at(particleData, 0x74);
                *f32_at(particleData, 0x74) = v74 * kPppRyjMegaBirthModelNegativeOne;
                float v78 = *f32_at(particleData, 0x78);
                *f32_at(particleData, 0x78) = v78 * kPppRyjMegaBirthModelNegativeOne;
                float v7C = *f32_at(particleData, 0x7C);
                *f32_at(particleData, 0x7C) = v7C * kPppRyjMegaBirthModelNegativeOne;
            }
        }

        if ((params->m_rotationRandomFlags & 4) != 0) {
            *f32_at(particleData, 0x5C) = *f32_at(particleData, 0x5C) + *f32_at(particleData, 0x74);
            *f32_at(particleData, 0x60) = *f32_at(particleData, 0x60) + *f32_at(particleData, 0x78);
            *f32_at(particleData, 0x64) = *f32_at(particleData, 0x64) + *f32_at(particleData, 0x7C);
        }

        if ((params->m_rotationRandomFlags & 8) != 0) {
            *f32_at(particleData, 0x68) = *f32_at(particleData, 0x68) + *f32_at(particleData, 0x74);
            *f32_at(particleData, 0x6C) = *f32_at(particleData, 0x6C) + *f32_at(particleData, 0x78);
            *f32_at(particleData, 0x70) = *f32_at(particleData, 0x70) + *f32_at(particleData, 0x7C);
        }
    }

    *f32_at(particleData, 0x80) = params->m_directionVelocityStart;
    *f32_at(particleData, 0x84) = params->m_acceleration;
    if (params->m_directionVelocityRandom != kPppRyjMegaBirthSharedZero) {
        *f32_at(particleData, 0x80) =
            *f32_at(particleData, 0x80) +
            (kPppRyjMegaBirthModelTwoF * params->m_directionVelocityRandom * Math.RandF() - params->m_directionVelocityRandom);
    }

    *f32_at(particleData, 0x88) = *(float*)(payload + 0xD0);
    *f32_at(particleData, 0x8C) = *(float*)(payload + 0xDC);
    *f32_at(particleData, 0x90) = *(float*)(payload + 0xD4);
    *f32_at(particleData, 0x94) = *(float*)(payload + 0xE0);

    switch (params->m_texScaleRandomMode) {
    case 1:
        *f32_at(particleData, 0x88) *= Math.RandF();
        break;
    case 2:
        *f32_at(particleData, 0x8C) *= Math.RandF();
        break;
    case 3:
        *f32_at(particleData, 0x88) *= Math.RandF();
        *f32_at(particleData, 0x8C) *= Math.RandF();
        break;
    case 4: {
        float r = Math.RandF();
        *f32_at(particleData, 0x88) *= r;
        *f32_at(particleData, 0x8C) *= r;
        break;
    }
    default:
        break;
    }

    if (*u16_at(params, 0x26) == 0) {
        s32 noSpriteId = 0xFFFF;
        *s16_at(particleData, 0x30) = noSpriteId;
    } else {
        *s16_at(particleData, 0x30) = *u16_at(params, 0x26);
    }
    *u8_at(particleData, 0x9c) = 0;

    if (particleWMat) {
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, ppvMng->m_matrix);
    }

    if (particleColor) {
        particleColor->m_colorFrameDeltas[0] = *(float*)(payload + 0x2C);
        particleColor->m_colorFrameDeltas[1] = *(float*)(payload + 0x30);
        particleColor->m_colorFrameDeltas[2] = *(float*)(payload + 0x34);
        particleColor->m_colorFrameDeltas[3] = *(float*)(payload + 0x38);
    }
}
#pragma pop

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

    if (particleColor) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] = particleColor->m_colorFrameDeltas[0] + pRyjMegaBirthModel->m_colorDeltaAdds[0];
        particleColor->m_colorFrameDeltas[1] = particleColor->m_colorFrameDeltas[1] + pRyjMegaBirthModel->m_colorDeltaAdds[1];
        particleColor->m_colorFrameDeltas[2] = particleColor->m_colorFrameDeltas[2] + pRyjMegaBirthModel->m_colorDeltaAdds[2];
        particleColor->m_colorFrameDeltas[3] = particleColor->m_colorFrameDeltas[3] + pRyjMegaBirthModel->m_colorDeltaAdds[3];
        alpha = (int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    *s32_at(p, 0x38) += *s32_at(p, 0x44);
    *s32_at(p, 0x3C) += *s32_at(p, 0x48);
    *s32_at(p, 0x40) += *s32_at(p, 0x4C);

    if ((pRyjMegaBirthModel->m_scaleRandomFlags & 0x10) != 0) {
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

    if ((pRyjMegaBirthModel->m_rotationRandomFlags & 0x10) != 0) {
        *f32_at(p, 0x68) += *(float*)(payload + 0xB0) + *f32_at(p, 0x74);
        *f32_at(p, 0x6C) += *(float*)(payload + 0xB4) + *f32_at(p, 0x78);
        *f32_at(p, 0x70) += *(float*)(payload + 0xB8) + *f32_at(p, 0x7C);
    } else {
        *f32_at(p, 0x68) += *(float*)(payload + 0xB0);
        *f32_at(p, 0x6C) += *(float*)(payload + 0xB4);
        *f32_at(p, 0x70) += *(float*)(payload + 0xB8);
    }

    *f32_at(p, 0x80) += pRyjMegaBirthModel->m_directionVelocityStep;
    if (pRyjMegaBirthModel->m_clampDirectionalSpeed == 0) {
        if ((kPppRyjMegaBirthSharedZero < pRyjMegaBirthModel->m_directionVelocityStart) &&
            (pRyjMegaBirthModel->m_directionVelocityStep < kPppRyjMegaBirthSharedZero)) {
            if (*f32_at(p, 0x80) < kPppRyjMegaBirthSharedZero) {
                *f32_at(p, 0x80) = kPppRyjMegaBirthSharedZero;
            }
        } else {
            if ((pRyjMegaBirthModel->m_directionVelocityStart < kPppRyjMegaBirthSharedZero) &&
                (kPppRyjMegaBirthSharedZero < pRyjMegaBirthModel->m_directionVelocityStep) &&
                (kPppRyjMegaBirthSharedZero < *f32_at(p, 0x80))) {
                *f32_at(p, 0x80) = kPppRyjMegaBirthSharedZero;
            }
        }
    }

    *f32_at(p, 0x84) += pRyjMegaBirthModel->m_accelerationStep;
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
    *f32_at(p, 0x90) += pRyjMegaBirthModel->m_texScrollUStepDelta;
    *f32_at(p, 0x94) += pRyjMegaBirthModel->m_texScrollVStep;

    if (pRyjMegaBirthModel->m_life != 0) {
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
        float fadeFrameCount = (float)(unsigned int)pRyjMegaBirthModel->m_fadeInFrames;
        float particleAlpha = *f32_at(p, 0x98);

        *f32_at(p, 0x98) = particleAlpha + fadeAlpha / fadeFrameCount;
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
static inline void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirthModel* params, _PARTICLE_WMAT* worldMatrixBlock)
{
    pppUnitMatrix(out);
    switch (params->m_spawnMode) {
    default:
        if (worldMatrixBlock == NULL) {
            pppMulMatrix(out, *(pppFMATRIX*)&ppvWorldMatrix, pObject->m_localMatrix);
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9:
        pppMulMatrix(out, *(pppFMATRIX*)&ppvWorldMatrix, pObject->m_localMatrix);
        break;
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
void pppRyjDrawMegaBirthModel(_pppPObject* obj, PRyjMegaBirthModel* stepData, _pppCtrlTable* ctrlTable)
{
    PRyjMegaBirthModel* params = (PRyjMegaBirthModel*)stepData;
    RyjMegaBirthModelDataOffsets* offsets = GetRyjMegaBirthModelDataOffsets(ctrlTable);
    VRyjMegaBirthModel* work =
        (VRyjMegaBirthModel*)(obj->m_workArea + offsets->m_workOffset);
    VColor* baseColor = (VColor*)(obj->m_workArea + offsets->m_colorOffset);
    _PARTICLE_DATA* particle = work->m_particleBlock;
    s32 numParticles = work->m_numParticles;
    _PARTICLE_WMAT* particleWorldMatrix = work->m_worldMatrixBlock;
    _PARTICLE_COLOR* particleColor = work->m_colorBlock;
    s8 hasRequiredMemory;

    if (particle == NULL) {
        hasRequiredMemory = 0;
    } else if ((params->m_enableWorldMatrix != 0) && (particleWorldMatrix == NULL)) {
        hasRequiredMemory = 0;
    } else if ((params->m_enableParticleColor != 0) && (particleColor == NULL)) {
        hasRequiredMemory = 0;
    } else {
        hasRequiredMemory = 1;
    }

    if (!hasRequiredMemory) {
        return;
    }

    int modelIndex = params->m_modelIndex;
    if (modelIndex == 0xFFFF) {
        return;
    }

    pppFMATRIX emitterMatrix;
    pppFMATRIX scratchMatrix;

    init_matrix(obj, emitterMatrix, params, particleWorldMatrix);

    int baseRed = baseColor->m_red;
    int baseGreen = baseColor->m_green;
    int baseBlue = baseColor->m_blue;
    int baseAlpha = baseColor->m_alpha;

    for (int i = 0; i < numParticles; i++) {
        if (*u16_at(particle, 0x30) != 0) {

        pppFMATRIX drawMatrix;

        pppUnitMatrix(scratchMatrix);
        set_matrix(obj, emitterMatrix, scratchMatrix, params, particle, particleWorldMatrix, drawMatrix, params->m_useEnvDepth);

        int red = baseRed + (int)*(s8*)((u8*)particle + 0x32);
        int green = baseGreen + (int)*(s8*)((u8*)particle + 0x33);
        int blue = baseBlue + (int)*(s8*)((u8*)particle + 0x34);
        int alpha = (int)((float)baseAlpha + (float)(int)*(s8*)((u8*)particle + 0x35) - *f32_at(particle, 0x98));

        if (particleColor) {
            red += (int)particleColor->m_color[0];
            green += (int)particleColor->m_color[1];
            blue += (int)particleColor->m_color[2];
            alpha += (int)particleColor->m_color[3];
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
        pppCVECTOR drawColor;
        drawColor.rgba[0] = (u8)red;
        drawColor.rgba[1] = (u8)green;
        drawColor.rgba[2] = (u8)blue;
        drawColor.rgba[3] = (u8)alpha;

        GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)drawColor.rgba);

        pppCopyMatrix(*(pppFMATRIX*)&g_matTmp, obj->m_localMatrix);
        pppMulMatrix(obj->m_localMatrix, obj->m_localMatrix, *(pppFMATRIX*)&g_matKeep);

        pppSetDrawEnv(&drawColor, &obj->m_drawMatrix,
                      params->m_useEnvDepth != 0 ? params->m_drawDepth : kPppRyjMegaBirthSharedZero,
                      params->m_lightTarget, params->m_fogIndex, params->m_blendMode, params->m_cullMode,
                      params->m_zEnable, 1, 0);
        MaterialMan.SetTexScroll(*f32_at(particle, 0x88) + *f32_at(particle, 0x90),
                                 *f32_at(particle, 0x8C) + *f32_at(particle, 0x94),
                                 kPppRyjMegaBirthSharedZero, kPppRyjMegaBirthSharedZero);
        pppSetBlendMode(params->m_blendMode);
        pppDrawMesh((pppModelSt*)ppvEnv->m_mapMeshPtr[params->m_modelIndex], obj->m_drawMatrixPtr, 1);
        pppCopyMatrix(obj->m_localMatrix, *(pppFMATRIX*)&g_matTmp);

        }

        if (particleWorldMatrix != NULL) {
            particleWorldMatrix++;
        }
        if (particleColor) {
            particleColor++;
        }
        particle = (_PARTICLE_DATA*)((u8*)particle + 0xA0);
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
#pragma push
#pragma opt_common_subs off
void set_matrix(_pppPObject* pObject, pppFMATRIX mtxA, pppFMATRIX mtxB, PRyjMegaBirthModel* params,
                _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, pppFMATRIX& out, unsigned char copyOut)
{
    Mtx scale;
    Vec sharedPos;

    if (params->m_matrixMode != 0) {
        pppCopyMatrix(mtxB, *(pppFMATRIX*)&particleData->m_matrix);
    } else {
        pppUnitMatrix(mtxB);
        sharedPos.x = particleData->m_matrix[0][3];
        sharedPos.y = particleData->m_matrix[1][3];
        sharedPos.z = particleData->m_matrix[2][3];
        mtxB.value[0][3] = sharedPos.x;
        mtxB.value[1][3] = sharedPos.y;
        mtxB.value[2][3] = sharedPos.z;
    }

    if (*s32_at(particleData, 0x38) != 0 ||
        *s32_at(particleData, 0x3C) != 0 ||
        *s32_at(particleData, 0x40) != 0) {
        Vec rot;
        rot.x = (kPppRyjMegaBirthPi * (float)*s32_at(particleData, 0x38)) / kPppRyjMegaBirthAngleIndexScale;
        rot.y = (kPppRyjMegaBirthPi * (float)*s32_at(particleData, 0x3C)) / kPppRyjMegaBirthAngleIndexScale;
        rot.z = (kPppRyjMegaBirthPi * (float)*s32_at(particleData, 0x40)) / kPppRyjMegaBirthAngleIndexScale;
        pppFMATRIX r;
        pppUnitMatrix(r);
        pppRotMatrix(r, r, rot);
        pppMulMatrix(mtxB, mtxB, r);
    }

    PSMTXScale(scale, *f32_at(particleData, 0x5C), *f32_at(particleData, 0x60), *f32_at(particleData, 0x64));
    pppMulMatrix(mtxB, mtxB, *(pppFMATRIX*)&scale);
    pppCopyMatrix(*(pppFMATRIX*)&g_matKeep, mtxB);

    switch (params->m_spawnMode) {
    default:
        if (particleWMat == NULL) {
            pppMulMatrix(mtxB, *(pppFMATRIX*)&pObject->m_localMatrix, mtxB);
            pppMulMatrix(mtxB, ppvMng->m_matrix, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvCameraMatrix, mtxB);
            pppCopyMatrix(pObject->m_drawMatrix, mtxB);
        } else {
            pppMulMatrix(mtxB, *(pppFMATRIX*)&pObject->m_localMatrix, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)particleWMat, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvCameraMatrix, mtxB);
            pppCopyMatrix(pObject->m_drawMatrix, mtxB);
        }
        if (copyOut != 0) {
            pppCopyMatrix(out, mtxB);
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9: {
        Vec transformedPos;

        sharedPos.x = mtxB.value[0][3];
        sharedPos.y = mtxB.value[1][3];
        sharedPos.z = mtxB.value[2][3];
        pppApplyMatrix(transformedPos, mtxA, sharedPos);

        pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvWorldMatrixWood, mtxB);
        mtxB.value[0][3] = transformedPos.x;
        mtxB.value[1][3] = transformedPos.y;
        mtxB.value[2][3] = transformedPos.z;
        if (copyOut != 0) {
            pppCopyMatrix(out, mtxB);
        }
        break;
    }
    }

    if (params->m_matrixFinalizeMode != 0) {
        Vec objectPos;
        Vec endPos;

        endPos.x = mtxB.value[0][3];
        endPos.y = mtxB.value[1][3];
        endPos.z = mtxB.value[2][3];

        objectPos.x = pObject->m_localMatrix.value[0][3];
        objectPos.y = pObject->m_localMatrix.value[1][3];
        objectPos.z = pObject->m_localMatrix.value[2][3];
        pppAddVector(endPos, endPos, objectPos);

        pppUnitMatrix(mtxB);
        PSMTXScaleApply(mtxB.value, pObject->m_drawMatrix.value,
                        mtxB.value[0][0] * *f32_at(particleData, 0x5C) * ppvMng->m_scale.x,
                        mtxB.value[1][1] * *f32_at(particleData, 0x60) * ppvMng->m_scale.y,
                        mtxB.value[2][2] * *f32_at(particleData, 0x64) * ppvMng->m_scale.z);
        PSMTXMultVec(ppvWorldMatrix, &endPos, &endPos);

        pppFMATRIX rot;

        PSMTXRotRad(rot.value, 'z', kPppRyjMegaBirthModelDegToRad * (float)*s32_at(particleData, 0x40));
        pppMulMatrix(pObject->m_drawMatrix, rot, pObject->m_drawMatrix);

        pObject->m_drawMatrix.value[0][3] = endPos.x;
        pObject->m_drawMatrix.value[1][3] = endPos.y;
        pObject->m_drawMatrix.value[2][3] = endPos.z;
    }
}
#pragma pop

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
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + GetRyjMegaBirthModelDataOffsets(offsets)->m_workOffset);
    float value1;
    float value0;

    memset(&work->m_accelerationAxis, 0, sizeof(work->m_accelerationAxis));
    work->m_particleBlock = 0;
    value0 = kPppRyjMegaBirthSharedZero;
    work->m_worldMatrixBlock = 0;
    value1 = kPppRyjMegaBirthModelInitialY;
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
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + GetRyjMegaBirthModelDataOffsets(offsets)->m_workOffset);

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
