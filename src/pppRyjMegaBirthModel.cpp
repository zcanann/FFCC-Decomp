#include "global.h"
#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include <stddef.h>
#include <string.h>
#include "ffcc/ppp_linkage.h"

struct _PARTICLE_DATA
{
    Mtx m_matrix;              // 0x00
    u16 m_life;                // 0x30
    s8 m_colorOffset[4];       // 0x32
    u8 _pad36[0x02];
    s32 m_rotation[3];         // 0x38
    s32 m_rotationVelocity[3]; // 0x44
    s32 m_rotationRandom[3];   // 0x50
    Vec m_scale;               // 0x5c
    Vec m_scaleVelocity;       // 0x68
    Vec m_scaleRandom;         // 0x74
    float m_velocity;          // 0x80
    float m_acceleration;      // 0x84
    float m_texScrollU;        // 0x88
    float m_texScrollV;        // 0x8c
    float m_texScrollUStep;    // 0x90
    float m_texScrollVStep;    // 0x94
    float m_alphaFade;         // 0x98
    u8 m_age;                  // 0x9c
    u8 m_fadeInFrames;         // 0x9d
    u8 m_fadeOutFrames;        // 0x9e
    u8 _pad9F;
}; // Size 0xa0

STATIC_ASSERT(sizeof(_PARTICLE_DATA) == 0xa0);
STATIC_ASSERT(offsetof(_PARTICLE_DATA, m_alphaFade) == 0x98);

static void calc_particle(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*);
static void birth(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, VColor*, _PARTICLE_DATA*, _PARTICLE_WMAT*, _PARTICLE_COLOR*);
static void calc(_pppPObject*, VRyjMegaBirthModel*, PRyjMegaBirthModel*, _PARTICLE_DATA*, VColor*, _PARTICLE_COLOR*);
static void set_matrix(_pppPObject*, pppFMATRIX, pppFMATRIX, PRyjMegaBirthModel*, _PARTICLE_DATA*, _PARTICLE_WMAT*, pppFMATRIX&, unsigned char);

static _PARTICLE_WMAT g_matKeep;
static _PARTICLE_WMAT g_matTmp;

static const char s_pppRyjMegaBirthModel_cpp[] = "pppRyjMegaBirthModel.cpp";

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
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_colorFrameDeltas) == 0x2C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_colorDeltaAdds) == 0x3C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_scaleRandom) == 0xC0);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollUAcceleration) == 0xD8);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollV) == 0xDC);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollVStep) == 0xE0);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScrollVAcceleration) == 0xE4);
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
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_scaleRandomFlags) == 0x132);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_rotationRandomFlags) == 0x133);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_texScaleRandomMode) == 0x134);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_matrixMode) == 0x135);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_enableWorldMatrix) == 0x136);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_matrixFinalizeMode) == 0x13E);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_pathIndex) == 0x138);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_zEnable) == 0x13A);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_clampDirectionalSpeed) == 0x13B);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_blendMode) == 0x13C);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_cullMode) == 0x13D);
STATIC_ASSERT(offsetof(PRyjMegaBirthModel, m_lightTarget) == 0x13F);
STATIC_ASSERT(sizeof(PRyjMegaBirthModel) == 0x140);

static inline void wrap_particle_rotation_triplet_s32(s32* rotation)
{
    for (s32 i = 0; i < 3; i++) {
        if (rotation[i] >= 0x8000) {
            while (rotation[i] >= 0x8000) { rotation[i] -= 0x10000; }
        } else if (rotation[i] < -0x8000) {
            while (rotation[i] >= 0x8000) { rotation[i] += 0x10000; }
        }
    }
}

static inline float get_rand()
{
    float r = Math.RandF();
    return r;
}

static inline signed char get_noise(u8 span)
{
    get_rand();
    return (signed char)((float)(span * 2) * get_rand() - (float)(span >> 1));
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
        pppMemFree(work->m_particleBlock);
        work->m_particleBlock = 0;
    }

    if (work->m_worldMatrixBlock != 0) {
        pppMemFree(work->m_worldMatrixBlock);
        work->m_worldMatrixBlock = 0;
    }

    if (work->m_colorBlock != 0) {
        pppMemFree(work->m_colorBlock);
        work->m_colorBlock = 0;
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
    value0 = 0.0f;
    work->m_worldMatrixBlock = 0;
    value1 = 30.0f;
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
 * PAL Address: 0x800842e4
 * PAL Size: 3896b
 * EN Address: 0x80098294
 * EN Size: 4168b
 * JP Address: TODO
 * JP Size: TODO
 */
static void set_matrix(_pppPObject* pObject, pppFMATRIX mtxA, pppFMATRIX mtxB, PRyjMegaBirthModel* params,
                _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, pppFMATRIX& out, unsigned char copyOut)
{
    pppFMATRIX r;
    Mtx scale;
    Vec sharedPos ATTRIBUTE_ALIGN(8);
    Vec transformedPos ATTRIBUTE_ALIGN(8);
    Vec rot ATTRIBUTE_ALIGN(8);

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

    if (particleData->m_rotation[0] || particleData->m_rotation[1] || particleData->m_rotation[2]) {
        rot.x = (3.1415927f * (float)particleData->m_rotation[0]) / 32768.0f;
        rot.y = (3.1415927f * (float)particleData->m_rotation[1]) / 32768.0f;
        rot.z = (3.1415927f * (float)particleData->m_rotation[2]) / 32768.0f;
        pppUnitMatrix(r);
        pppRotMatrix(r, r, rot);
        pppMulMatrix(mtxB, mtxB, r);
    }

    PSMTXScale(scale, particleData->m_scale.x, particleData->m_scale.y, particleData->m_scale.z);
    pppMulMatrix(mtxB, mtxB, *(pppFMATRIX*)&scale);
    pppCopyMatrix(*(pppFMATRIX*)&g_matKeep, mtxB);

    switch (params->m_spawnMode) {
    default:
        if (particleWMat == NULL) {
            pppMulMatrix(mtxB, pObject->m_localMatrix, mtxB);
            pppMulMatrix(mtxB, ppvMng->m_matrix, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvCameraMatrix, mtxB);
            pppCopyMatrix(pObject->m_drawMatrix, mtxB);
        } else {
            pppMulMatrix(mtxB, pObject->m_localMatrix, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)particleWMat, mtxB);
            pppMulMatrix(mtxB, *(pppFMATRIX*)&ppvCameraMatrix, mtxB);
            pppCopyMatrix(pObject->m_drawMatrix, mtxB);
            if (copyOut != 0) {
                pppCopyMatrix(out, mtxB);
            }
        }
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 9: {

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
        Vec endPos ATTRIBUTE_ALIGN(8);
        Vec objectPos;

        endPos.x = mtxB.value[0][3];
        endPos.y = mtxB.value[1][3];
        endPos.z = mtxB.value[2][3];

        objectPos.x = pObject->m_localMatrix.value[0][3];
        objectPos.y = pObject->m_localMatrix.value[1][3];
        objectPos.z = pObject->m_localMatrix.value[2][3];
        pppAddVector(endPos, endPos, objectPos);

        pppUnitMatrix(mtxB);
        Vec* particleScale = &particleData->m_scale;
        PSMTXScaleApply(mtxB.value, pObject->m_drawMatrix.value,
                        mtxB.value[0][0] * (particleScale->x * ppvMng->m_scale.x),
                        mtxB.value[1][1] * (particleScale->y * ppvMng->m_scale.y),
                        mtxB.value[2][2] * (particleScale->z * ppvMng->m_scale.z));
        PSMTXMultVec(ppvWorldMatrix, &endPos, &endPos);

        pppFMATRIX rot;

        PSMTXRotRad(rot.value, 'z', 0.017453292f * (float)particleData->m_rotation[2]);
        pppMulMatrix(pObject->m_drawMatrix, rot, pObject->m_drawMatrix);

        pObject->m_drawMatrix.value[0][3] = endPos.x;
        pObject->m_drawMatrix.value[1][3] = endPos.y;
        pObject->m_drawMatrix.value[2][3] = endPos.z;
    }
}

static inline s8 alloc_check(VRyjMegaBirthModel* work, PRyjMegaBirthModel* params)
{
    if (work->m_particleBlock == NULL) {
        return 0;
    }
    if ((params->m_enableWorldMatrix != 0) && (work->m_worldMatrixBlock == NULL)) {
        return 0;
    }
    if ((params->m_enableParticleColor != 0) && (work->m_colorBlock == NULL)) {
        return 0;
    }
    return 1;
}

static inline void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirthModel* params, VRyjMegaBirthModel* work)
{
    _PARTICLE_WMAT* worldMatrixBlock = work->m_worldMatrixBlock;

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
void pppRyjDrawMegaBirthModel(_pppPObject* obj, PRyjMegaBirthModel* params, _pppCtrlTable* ctrlTable)
{
    int* offsets = ctrlTable->m_serializedDataOffsets;
    VRyjMegaBirthModel* work =
        (VRyjMegaBirthModel*)(obj->m_workArea + offsets[2]);
    _PARTICLE_DATA* particleBlock = work->m_particleBlock;
    _PARTICLE_WMAT* worldMatrixBlock = work->m_worldMatrixBlock;
    _PARTICLE_COLOR* colorBlock = work->m_colorBlock;
    VColor* baseColor = (VColor*)(obj->m_workArea + offsets[1]);
    _PARTICLE_DATA* particle = particleBlock;
    _PARTICLE_WMAT* particleWorldMatrix = worldMatrixBlock;
    _PARTICLE_COLOR* particleColor = colorBlock;
    s32 numParticles = work->m_numParticles;

    if (!alloc_check(work, params)) {
        return;
    }

    int modelIndex = params->m_modelIndex;
    if (modelIndex == 0xFFFF) {
        return;
    }

    pppFMATRIX emitterMatrix;
    pppFMATRIX scratchMatrix;

    init_matrix(obj, emitterMatrix, params, work);

    int baseRed = baseColor->m_color.rgba[0];
    int baseGreen = baseColor->m_color.rgba[1];
    int baseBlue = baseColor->m_color.rgba[2];
    int baseAlpha = baseColor->m_color.rgba[3];

    for (int i = 0; i < numParticles; i++) {
        if (particle->m_life != 0) {

        pppFMATRIX drawMatrix;
        VColor drawColor ATTRIBUTE_ALIGN(8);
        pppCVECTOR ambColor;

        pppUnitMatrix(scratchMatrix);
        set_matrix(obj, emitterMatrix, scratchMatrix, params, particle, particleWorldMatrix, drawMatrix, params->m_useEnvDepth);

        int red = baseRed + (int)particle->m_colorOffset[0];
        int green = baseGreen + (int)particle->m_colorOffset[1];
        int blue = baseBlue + (int)particle->m_colorOffset[2];
        int alpha = (int)((float)baseAlpha + (float)(int)particle->m_colorOffset[3] - particle->m_alphaFade);

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
        ambColor.rgba[0] = (u8)red;
        ambColor.rgba[1] = (u8)green;
        ambColor.rgba[2] = (u8)blue;
        ambColor.rgba[3] = (u8)alpha;

        GXSetChanAmbColor(GX_COLOR0A0, *(_GXColor*)ambColor.rgba);

        pppCopyMatrix(*(pppFMATRIX*)&g_matTmp, obj->m_localMatrix);
        pppMulMatrix(obj->m_localMatrix, obj->m_localMatrix, *(pppFMATRIX*)&g_matKeep);

        drawColor.m_color.rgba[0] = (u8)red;
        drawColor.m_color.rgba[1] = (u8)green;
        drawColor.m_color.rgba[2] = (u8)blue;
        drawColor.m_color.rgba[3] = (u8)alpha;

        pppSetDrawEnv(&drawColor.m_color, &obj->m_drawMatrix,
                      params->m_useEnvDepth != 0 ? params->m_drawDepth : 0.0f,
                      params->m_lightTarget, params->m_fogIndex, params->m_blendMode, params->m_cullMode,
                      params->m_zEnable, 1, 0);
        MaterialMan.SetTexScroll(particle->m_texScrollU + particle->m_texScrollUStep,
                                 particle->m_texScrollV + particle->m_texScrollVStep,
                                 0.0f, 0.0f);
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
        particle++;
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
static void calc(_pppPObject* pppPObject, VRyjMegaBirthModel* vRyjMegaBirthModel,
          PRyjMegaBirthModel* pRyjMegaBirthModel, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    (void)pppPObject;

    int alpha = vColor->m_color.rgba[3];
    Vec direction ATTRIBUTE_ALIGN(8);
    Vec position ATTRIBUTE_ALIGN(8);
    Vec step ATTRIBUTE_ALIGN(8);

    if (particleColor) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] = particleColor->m_colorFrameDeltas[0] + pRyjMegaBirthModel->m_colorDeltaAdds[0];
        particleColor->m_colorFrameDeltas[1] = particleColor->m_colorFrameDeltas[1] + pRyjMegaBirthModel->m_colorDeltaAdds[1];
        particleColor->m_colorFrameDeltas[2] = particleColor->m_colorFrameDeltas[2] + pRyjMegaBirthModel->m_colorDeltaAdds[2];
        particleColor->m_colorFrameDeltas[3] = particleColor->m_colorFrameDeltas[3] + pRyjMegaBirthModel->m_colorDeltaAdds[3];
        alpha = (int)vColor->m_color.rgba[3] + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    particleData->m_rotation[0] += particleData->m_rotationVelocity[0];
    particleData->m_rotation[1] += particleData->m_rotationVelocity[1];
    particleData->m_rotation[2] += particleData->m_rotationVelocity[2];

    if ((pRyjMegaBirthModel->m_rotationRandomFlags & 0x10) != 0) {
        particleData->m_rotationVelocity[0] += pRyjMegaBirthModel->m_rotationAcceleration[0] + particleData->m_rotationRandom[0];
        particleData->m_rotationVelocity[1] += pRyjMegaBirthModel->m_rotationAcceleration[1] + particleData->m_rotationRandom[1];
        particleData->m_rotationVelocity[2] += pRyjMegaBirthModel->m_rotationAcceleration[2] + particleData->m_rotationRandom[2];
    } else {
        particleData->m_rotationVelocity[0] += pRyjMegaBirthModel->m_rotationAcceleration[0];
        particleData->m_rotationVelocity[1] += pRyjMegaBirthModel->m_rotationAcceleration[1];
        particleData->m_rotationVelocity[2] += pRyjMegaBirthModel->m_rotationAcceleration[2];
    }

    wrap_particle_rotation_triplet_s32(particleData->m_rotation);

    particleData->m_scale.x = particleData->m_scale.x + particleData->m_scaleVelocity.x;
    particleData->m_scale.y = particleData->m_scale.y + particleData->m_scaleVelocity.y;
    particleData->m_scale.z = particleData->m_scale.z + particleData->m_scaleVelocity.z;

    if ((pRyjMegaBirthModel->m_scaleRandomFlags & 0x10) != 0) {
        particleData->m_scaleVelocity.x += pRyjMegaBirthModel->m_scaleAcceleration.x + particleData->m_scaleRandom.x;
        particleData->m_scaleVelocity.y += pRyjMegaBirthModel->m_scaleAcceleration.y + particleData->m_scaleRandom.y;
        particleData->m_scaleVelocity.z += pRyjMegaBirthModel->m_scaleAcceleration.z + particleData->m_scaleRandom.z;
    } else {
        particleData->m_scaleVelocity.x += pRyjMegaBirthModel->m_scaleAcceleration.x;
        particleData->m_scaleVelocity.y += pRyjMegaBirthModel->m_scaleAcceleration.y;
        particleData->m_scaleVelocity.z += pRyjMegaBirthModel->m_scaleAcceleration.z;
    }

    particleData->m_velocity += pRyjMegaBirthModel->m_directionVelocityStep;
    if (pRyjMegaBirthModel->m_clampDirectionalSpeed == 0) {
        if ((0.0f < pRyjMegaBirthModel->m_directionVelocityStart) &&
            (pRyjMegaBirthModel->m_directionVelocityStep < 0.0f)) {
            if (particleData->m_velocity < 0.0f) {
                particleData->m_velocity = 0.0f;
            }
        } else {
            if ((pRyjMegaBirthModel->m_directionVelocityStart < 0.0f) &&
                (0.0f < pRyjMegaBirthModel->m_directionVelocityStep) &&
                (0.0f < particleData->m_velocity)) {
                particleData->m_velocity = 0.0f;
            }
        }
    }

    particleData->m_acceleration += pRyjMegaBirthModel->m_accelerationStep;
    direction.x = particleData->m_matrix[0][1];
    direction.y = particleData->m_matrix[1][1];
    direction.z = particleData->m_matrix[2][1];
    pppScaleVectorXYZ(step, direction, particleData->m_velocity);
    position.x = particleData->m_matrix[0][3];
    position.y = particleData->m_matrix[1][3];
    position.z = particleData->m_matrix[2][3];
    pppAddVector(position, position, step);
    pppScaleVectorXYZ(step, vRyjMegaBirthModel->m_accelerationAxis, particleData->m_acceleration);
    pppAddVector(position, position, step);
    particleData->m_matrix[0][3] = position.x;
    particleData->m_matrix[1][3] = position.y;
    particleData->m_matrix[2][3] = position.z;

    particleData->m_texScrollU += particleData->m_texScrollUStep;
    particleData->m_texScrollV += particleData->m_texScrollVStep;
    particleData->m_texScrollUStep += pRyjMegaBirthModel->m_texScrollUAcceleration;
    particleData->m_texScrollVStep += pRyjMegaBirthModel->m_texScrollVAcceleration;

    if (pRyjMegaBirthModel->m_life != 0) {
        particleData->m_life = particleData->m_life - 1;
    }

    particleData->m_age = particleData->m_age + 1;

    if ((particleData->m_fadeInFrames != 0) && (particleData->m_age <= particleData->m_fadeInFrames)) {
        float fadeAlpha = (float)alpha;
        float fadeFrameCount = (float)(unsigned int)particleData->m_fadeInFrames;
        float particleAlpha = particleData->m_alphaFade;

        particleData->m_alphaFade = particleAlpha - fadeAlpha / fadeFrameCount;
    }

    if ((particleData->m_fadeOutFrames != 0) && (particleData->m_life <= particleData->m_fadeOutFrames)) {
        float fadeAlpha = (float)alpha;
        float fadeFrameCount = (float)(unsigned int)pRyjMegaBirthModel->m_fadeInFrames;
        float particleAlpha = particleData->m_alphaFade;

        particleData->m_alphaFade = particleAlpha + fadeAlpha / fadeFrameCount;
    }
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
/*
 * --INFO--
 * PAL Address: 0x80085fd0
 * PAL Size: 7132b
 * EN Address: 0x8008596C
 * EN Size: 7132b
 * JP Address: TODO
 * JP Size: TODO
 */
static void birth(
    _pppPObject* pObject, VRyjMegaBirthModel* work, PRyjMegaBirthModel* params, VColor* color,
    _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat, _PARTICLE_COLOR* particleColor)
{
    (void)pObject;
    Vec baseDirection ATTRIBUTE_ALIGN(8);
    Vec angles ATTRIBUTE_ALIGN(8);
    Vec rowX ATTRIBUTE_ALIGN(8);
    Vec rowY ATTRIBUTE_ALIGN(8);
    Vec rowZ ATTRIBUTE_ALIGN(8);
    Vec rowPos ATTRIBUTE_ALIGN(8);
    Vec direction ATTRIBUTE_ALIGN(8);
    Vec right ATTRIBUTE_ALIGN(8);
    Vec directionCopy ATTRIBUTE_ALIGN(8);
    Vec worldUp ATTRIBUTE_ALIGN(8);
    float spread = (float)params->m_spread;
    float randomRange = 2.0f * spread;

    memset(particleData, 0, sizeof(_PARTICLE_DATA));
    if (particleWMat) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    pppUnitMatrix(*(pppFMATRIX*)&particleData->m_matrix);

    switch (params->m_spawnMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        pppFMATRIX rotMatrix;

        baseDirection.x = params->m_baseDirection.x;
        baseDirection.y = params->m_baseDirection.y;
        baseDirection.z = params->m_baseDirection.z;
        angles.x = (float)(randomRange * Math.RandF() - spread);
        angles.x = (32768.0f * angles.x) / 180.0f;
        angles.y = (float)(randomRange * Math.RandF() - spread);
        angles.y = (32768.0f * angles.y) / 180.0f;
        angles.z = (float)(randomRange * Math.RandF() - spread);
        angles.z = (32768.0f * angles.z) / 180.0f;

        if ((params->m_spawnMode == 2) || (params->m_spawnMode == 3)) {
            angles.x = 0.0f;
            angles.y = 0.0f;
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

        worldUp.x = 0.0f;
        worldUp.y = 0.0f;
        worldUp.z = 1.0f;
        pppOuterProduct(right, directionCopy, worldUp);
        pppNormalize(right, right);
        pppOuterProduct(worldUp, right, directionCopy);
        pppNormalize(worldUp, worldUp);

        pppUnitMatrix(basis);
        basis.value[0][0] = right.x;
        basis.value[1][0] = right.y;
        basis.value[2][0] = right.z;
        basis.value[0][1] = directionCopy.x;
        basis.value[1][1] = directionCopy.y;
        basis.value[2][1] = directionCopy.z;
        basis.value[0][2] = worldUp.x;
        basis.value[1][2] = worldUp.y;
        basis.value[2][2] = worldUp.z;
        basis.value[0][3] = translationX;
        basis.value[1][3] = translationY;
        basis.value[2][3] = translationZ;
        pppCopyMatrix(*(pppFMATRIX*)&particleData->m_matrix, basis);
        break;
    }
    }

    switch (params->m_spawnMode) {
    default:
        if (0.0f != params->m_speed) {
            float speedScalar;

            switch (params->m_speedMode) {
            default:
                speedScalar = params->m_speed;
                break;
            case 1:
                Math.RandF();
                speedScalar = params->m_speed * Math.RandF();
                break;
            case 2: {
                speedScalar = params->m_speed * Math.RandF() * Math.RandF();
                break;
            }
            case 3: {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                speedScalar = params->m_speed * rand2;
                speedScalar = params->m_speed - 0.7f * (speedScalar * rand1);
                break;
            }
            case 4: {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                float rand4 = Math.RandF();
                speedScalar = params->m_speed * rand2;
                speedScalar = rand4 * (rand3 * (speedScalar * rand1));
                break;
            }
            case 5: {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                speedScalar = params->m_speed * rand2;
                speedScalar = params->m_speed - 0.5f * (rand3 * (speedScalar * rand1));
                break;
            }
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
        break;

    case 4:
    case 5:
        if (0.0f != params->m_speed) {
            float halfSpeed = 0.5f * params->m_speed;
            u8 speedMode = params->m_speedMode;
            float t;
            float r1;
            float r2;
            float r3;
            float r4;

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
                rowPos.x = params->m_speed * Math.RandF() * Math.RandF();
                rowPos.x -= halfSpeed;
                rowPos.y = params->m_speed * Math.RandF() * Math.RandF();
                rowPos.y -= halfSpeed;
                rowPos.z = params->m_speed * Math.RandF() * Math.RandF();
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
                r2 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.x = params->m_speed - 0.7f * (r2 * r3);
                rowPos.x -= halfSpeed;
                r3 = Math.RandF();
                r2 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.y = params->m_speed - 0.7f * (r2 * r3);
                rowPos.y -= halfSpeed;
                r3 = Math.RandF();
                r2 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.z = params->m_speed - 0.7f * (r2 * r3);
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
                r4 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.x = r4 * (r3 * (r2 * r1));
                rowPos.x -= halfSpeed;
                r1 = Math.RandF();
                r2 = Math.RandF();
                r3 = Math.RandF();
                r4 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.y = r4 * (r3 * (r2 * r1));
                rowPos.y -= halfSpeed;
                r1 = Math.RandF();
                r2 = Math.RandF();
                r3 = Math.RandF();
                r4 = Math.RandF();
                r2 = params->m_speed * r2;
                rowPos.z = r4 * (r3 * (r2 * r1));
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
                r1 = Math.RandF();
                r3 = params->m_speed * r3;
                rowPos.x = params->m_speed - 0.5f * (r1 * (r3 * r2));
                rowPos.x -= halfSpeed;
                r2 = Math.RandF();
                r3 = Math.RandF();
                r1 = Math.RandF();
                r3 = params->m_speed * r3;
                rowPos.y = params->m_speed - 0.5f * (r1 * (r3 * r2));
                rowPos.y -= halfSpeed;
                r2 = Math.RandF();
                r3 = Math.RandF();
                r1 = Math.RandF();
                r3 = params->m_speed * r3;
                rowPos.z = params->m_speed - 0.5f * (r1 * (r3 * r2));
                rowPos.z -= halfSpeed;
                t = rowPos.x;
                particleData->m_matrix[0][3] = t;
                t = rowPos.y;
                particleData->m_matrix[1][3] = t;
                t = rowPos.z;
                particleData->m_matrix[2][3] = t;
                break;
            }

            float x = particleData->m_matrix[0][3];
            float y = particleData->m_matrix[1][3];
            float z = particleData->m_matrix[2][3];
            x *= params->m_directionScale.x;
            y *= params->m_directionScale.y;
            z *= params->m_directionScale.z;
            particleData->m_matrix[0][3] = x;
            particleData->m_matrix[1][3] = y;
            particleData->m_matrix[2][3] = z;
        }
        break;

    case 6:
    case 7:
    case 8:
    case 9: {

        Vec* pathBase = pObject->m_drawMatrixPtr;

        if (params->m_pathIndex >= 0) {
            pppShapeGroupRaw* pathInfo = &ppvEnv->m_shapeGroupPtr[params->m_pathIndex];
            float t;
            float vx;
            float vy;
            float vz;
            float m1;
            float m2;
            float m3;
            float m4;
            float m5;

            if (!pathBase) {
                pathBase = ppvEnv->m_mapMeshPtr[pathInfo->m_meshIndex]->m_vertices;
            }

            switch (params->m_speedMode) {
            default: {
                if ((s32)work->m_unused1E >= (s32)pathInfo->m_vertexCount) {
                    work->m_unused1E = 0;
                }
                u16 sampleIndex = work->m_unused1E;
                u16* indices = pathInfo->m_vertexIndices;
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
                m4 = Math.RandF();
                t = m4 * (m3 * m2);
                break;
            case 3:
                m2 = Math.RandF();
                m3 = Math.RandF();
                m4 = Math.RandF();
                t = (float)(1.0 - (m4 * (m3 * m2)));
                break;
            case 4:
                m1 = Math.RandF();
                m2 = Math.RandF();
                m3 = Math.RandF();
                m4 = Math.RandF();
                t = m4 * (m3 * (m2 * m1));
                break;
            case 5:
                m1 = Math.RandF();
                m2 = Math.RandF();
                m3 = Math.RandF();
                m4 = Math.RandF();
                m5 = Math.RandF();
                t = (float)(1.0 - (m5 * (m4 * (m3 * (m2 * m1)))));
                break;
            }
            {
                if ((s32)work->m_unused1E >= (s32)pathInfo->m_vertexCount) {
                    work->m_unused1E = 0;
                }
                s32 sampleIndex = (s32)(t * (float)pathInfo->m_vertexCount);
                Vec* pathVec = pathBase + pathInfo->m_vertexIndices[sampleIndex];
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
        break;
    }
    }

    {
        particleData->m_colorOffset[0] = get_noise(params->m_colorOffsetRange[0]);
        particleData->m_colorOffset[1] = get_noise(params->m_colorOffsetRange[1]);
        particleData->m_colorOffset[2] = get_noise(params->m_colorOffsetRange[2]);
        particleData->m_colorOffset[3] = get_noise(params->m_colorOffsetRange[3]);
    }

    if (params->m_fadeOutFrames != 0) {
        particleData->m_alphaFade = static_cast<float>(color->m_color.rgba[3]);
        particleData->m_fadeInFrames = params->m_fadeOutFrames;
    }
    if (params->m_fadeInFrames != 0) {
        particleData->m_fadeOutFrames = params->m_fadeInFrames;
    }

    particleData->m_rotation[0] = params->m_rotation[0];
    particleData->m_rotation[1] = params->m_rotation[1];
    particleData->m_rotation[2] = params->m_rotation[2];
    particleData->m_rotationVelocity[0] = params->m_rotationVelocity[0];
    particleData->m_rotationVelocity[1] = params->m_rotationVelocity[1];
    particleData->m_rotationVelocity[2] = params->m_rotationVelocity[2];

    if (params->m_rotationRandomFlags != 0) {
        if ((params->m_rotationRandomFlags & 0x20) != 0) {
            s32 randomized = (s32)((float)params->m_rotationRandom[0] * Math.RandF());
            particleData->m_rotationRandom[2] = randomized;
            particleData->m_rotationRandom[1] = randomized;
            particleData->m_rotationRandom[0] = randomized;

            u8 rotBits = params->m_rotationRandomFlags;
            if (((rotBits & 1) != 0) && ((rotBits & 2) != 0)) {
                if (0.5 < (double)Math.RandF()) {
                    particleData->m_rotationRandom[0] *= -1;
                    particleData->m_rotationRandom[1] *= -1;
                    particleData->m_rotationRandom[2] *= -1;
                }
            } else if ((rotBits & 2) != 0) {
                particleData->m_rotationRandom[0] *= -1;
                particleData->m_rotationRandom[1] *= -1;
                particleData->m_rotationRandom[2] *= -1;
            }
        } else {
            particleData->m_rotationRandom[0] = (s32)((float)params->m_rotationRandom[0] * Math.RandF());
            particleData->m_rotationRandom[1] = (s32)((float)params->m_rotationRandom[1] * Math.RandF());
            particleData->m_rotationRandom[2] = (s32)((float)params->m_rotationRandom[2] * Math.RandF());

            u8 rotBits = params->m_rotationRandomFlags;
            if (((rotBits & 1) != 0) && ((rotBits & 2) != 0)) {
                double h = 0.5;
                s32 i;
                for (i = 0; i < 3; i++) {
                    if (h < (double)Math.RandF()) {
                        particleData->m_rotationRandom[i] *= -1;
                    }
                }
            } else if ((rotBits & 2) != 0) {
                particleData->m_rotationRandom[0] *= -1;
                particleData->m_rotationRandom[1] *= -1;
                particleData->m_rotationRandom[2] *= -1;
            }
        }
    }

    if ((params->m_rotationRandomFlags & 4) != 0) {
        particleData->m_rotation[0] += particleData->m_rotationRandom[0];
        particleData->m_rotation[1] += particleData->m_rotationRandom[1];
        particleData->m_rotation[2] += particleData->m_rotationRandom[2];
    }

    if ((params->m_rotationRandomFlags & 8) != 0) {
        particleData->m_rotationVelocity[0] += particleData->m_rotationRandom[0];
        particleData->m_rotationVelocity[1] += particleData->m_rotationRandom[1];
        particleData->m_rotationVelocity[2] += particleData->m_rotationRandom[2];
    }

    {
        s32* angle = particleData->m_rotation;
        for (s32 i = 0; i < 3; i++) {
            if (angle[i] >= 0x8000 || angle[i] < -0x8000) {
                angle[i] %= 0x8000;
            }
        }
    }

    particleData->m_scale.x = params->m_scale.x;
    particleData->m_scale.y = params->m_scale.y;
    particleData->m_scale.z = params->m_scale.z;
    particleData->m_scaleVelocity.x = params->m_scaleVelocity.x;
    particleData->m_scaleVelocity.y = params->m_scaleVelocity.y;
    particleData->m_scaleVelocity.z = params->m_scaleVelocity.z;

    if (params->m_scaleRandomFlags != 0) {
        if ((params->m_scaleRandomFlags & 0x20) != 0) {
            float randomizedScale = params->m_scaleRandom.x * Math.RandF();
            particleData->m_scaleRandom.z = randomizedScale;
            particleData->m_scaleRandom.y = randomizedScale;
            particleData->m_scaleRandom.x = randomizedScale;

            u8 scaleBits = params->m_scaleRandomFlags;
            if (((scaleBits & 1) != 0) && ((scaleBits & 2) != 0)) {
                if (0.5 < (double)Math.RandF()) {
                    particleData->m_scaleRandom.x *= -1.0f;
                    particleData->m_scaleRandom.y *= -1.0f;
                    particleData->m_scaleRandom.z *= -1.0f;
                }
            } else if ((scaleBits & 2) != 0) {
                particleData->m_scaleRandom.x *= -1.0f;
                particleData->m_scaleRandom.y *= -1.0f;
                particleData->m_scaleRandom.z *= -1.0f;
            }
        } else {
            particleData->m_scaleRandom.x = params->m_scaleRandom.x * Math.RandF();
            particleData->m_scaleRandom.y = params->m_scaleRandom.y * Math.RandF();
            particleData->m_scaleRandom.z = params->m_scaleRandom.z * Math.RandF();

            u8 scaleBits = params->m_scaleRandomFlags;
            if (((scaleBits & 1) != 0) && ((scaleBits & 2) != 0)) {
                double h = 0.5;
                s32 i;
                for (i = 0; i < 3; i++) {
                    if (h < (double)Math.RandF()) {
                        (&particleData->m_scaleRandom.x)[i] *= -1.0f;
                    }
                }
            } else if ((scaleBits & 2) != 0) {
                particleData->m_scaleRandom.x *= -1.0f;
                particleData->m_scaleRandom.y *= -1.0f;
                particleData->m_scaleRandom.z *= -1.0f;
            }
        }
    }

    if ((params->m_scaleRandomFlags & 4) != 0) {
        particleData->m_scale.x = particleData->m_scale.x + particleData->m_scaleRandom.x;
        particleData->m_scale.y = particleData->m_scale.y + particleData->m_scaleRandom.y;
        particleData->m_scale.z = particleData->m_scale.z + particleData->m_scaleRandom.z;
    }

    if ((params->m_scaleRandomFlags & 8) != 0) {
        particleData->m_scaleVelocity.x = particleData->m_scaleVelocity.x + particleData->m_scaleRandom.x;
        particleData->m_scaleVelocity.y = particleData->m_scaleVelocity.y + particleData->m_scaleRandom.y;
        particleData->m_scaleVelocity.z = particleData->m_scaleVelocity.z + particleData->m_scaleRandom.z;
    }

    particleData->m_velocity = params->m_directionVelocityStart;
    particleData->m_acceleration = params->m_acceleration;
    if (0.0f != params->m_directionVelocityRandom) {
        float rand1 = Math.RandF();
        particleData->m_velocity +=
            (2.0f * params->m_directionVelocityRandom) * rand1 - params->m_directionVelocityRandom;
    }

    particleData->m_texScrollU = params->m_texScrollU;
    particleData->m_texScrollV = params->m_texScrollV;
    particleData->m_texScrollUStep = params->m_texScrollUStep;
    particleData->m_texScrollVStep = params->m_texScrollVStep;

    switch (params->m_texScaleRandomMode) {
    case 1:
        particleData->m_texScrollU *= Math.RandF();
        break;
    case 2:
        particleData->m_texScrollV *= Math.RandF();
        break;
    case 4:
        particleData->m_texScrollU *= Math.RandF();
        particleData->m_texScrollV *= Math.RandF();
        break;
    case 3: {
        float r = Math.RandF();
        particleData->m_texScrollU *= r;
        particleData->m_texScrollV *= r;
        break;
    }
    default:
        break;
    }

    if (params->m_life == 0) {
        particleData->m_life = 0xFFFF;
    } else {
        particleData->m_life = params->m_life;
    }
    particleData->m_age = 0;

    if (particleWMat) {
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, ppvMng->m_matrix);
    }

    if (particleColor) {
        particleColor->m_colorFrameDeltas[0] = params->m_colorFrameDeltas[0];
        particleColor->m_colorFrameDeltas[1] = params->m_colorFrameDeltas[1];
        particleColor->m_colorFrameDeltas[2] = params->m_colorFrameDeltas[2];
        particleColor->m_colorFrameDeltas[3] = params->m_colorFrameDeltas[3];
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
static void calc_particle(_pppPObject* pObject, VRyjMegaBirthModel* work, PRyjMegaBirthModel* params, VColor* color)
{
    _PARTICLE_DATA* particleData;
    _PARTICLE_WMAT* particleWMat;
    _PARTICLE_COLOR* particleColor;
    s32 maxParticles;
    s32 emitted;
    s32 i;
    u16* emitTimer;

    emitted = 0;
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
            if (particleData->m_life != 0) {
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
            particleData++;
        }

        if (emitted > 0) {
            *emitTimer = 0;
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
    s8 hasRequiredMemory;
    VRyjMegaBirthModel* work =
        reinterpret_cast<VRyjMegaBirthModel*>(pObject->m_workArea + offsets->m_serializedDataOffsets[2]);
    VColor* color =
        reinterpret_cast<VColor*>(pObject->m_workArea + offsets->m_serializedDataOffsets[1]);

    if (work->m_particleBlock == 0) {
        work->m_numParticles = params->m_maxParticles;
        work->m_particleBlock = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_numParticles * sizeof(_PARTICLE_DATA), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppRyjMegaBirthModel_cpp), 0x8D);
        if (work->m_particleBlock != NULL) {
            memset(work->m_particleBlock, 0, work->m_numParticles * sizeof(_PARTICLE_DATA));
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

        posX = pObject->m_localMatrix.value[0][3];
        posY = pObject->m_localMatrix.value[1][3];
        posZ = pObject->m_localMatrix.value[2][3];
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
