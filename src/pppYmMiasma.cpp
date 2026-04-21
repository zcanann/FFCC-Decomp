#include "ffcc/pppYmMiasma.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <string.h>

extern "C" int rand(void);
extern float FLOAT_80330640;
extern float FLOAT_80330644;
extern float FLOAT_80330650;
extern float FLOAT_80330654;
extern float FLOAT_8033065c;
extern float FLOAT_80330660;
extern float FLOAT_80330664;
extern float FLOAT_80330668;
extern float FLOAT_80330658;
extern double DOUBLE_80330648;
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" void pppSetBlendMode(unsigned char);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);

struct VYmMiasma {
    PARTICLE_DATA* m_particles;
    float m_speedDecay;
    u8 m_emitTimer;
    u8 m_pad09[7];
    Vec m_impulse;
    float m_radius;
    float m_radiusVelocity;
    float m_radiusAcceleration;
    Vec m_prevPosition;
    u8 m_prevPositionChanged;
    u8 m_pad35[3];
};

struct PYmMiasma {
    s32 m_graphId;
    s32 m_dataValIndex;
    s32 m_shapeFrameStep;
    u16 m_particleCount;
    u16 m_pad0E;
    float m_baseSpeed;
    float m_speedVariance;
    float m_unk18;
    float m_minDistance;
    float m_gravity;
    u8 m_colorStartR;
    u8 m_colorStartG;
    u8 m_colorStartB;
    u8 m_colorStartA;
    s16 m_colorEndR;
    s16 m_colorEndG;
    s16 m_colorEndB;
    s16 m_colorEndA;
    s16 m_colorStepFrames;
    s16 m_pad32;
    float m_initialSpeedDecay;
    float m_speedDecay;
    float m_radiusJitter;
    float m_spawnHeightJitter;
    float m_heightJitter;
    u8 m_lifeBase;
    u8 m_lifeRange;
    u8 m_pad4A[2];
    float m_minSpeed;
    s16 m_fadeFrames;
    s16 m_colorDecayFrames;
};

struct YmMiasmaParticleColor {
    s16 m_r;
    s16 m_g;
    s16 m_b;
    s16 m_a;
};

struct YmMiasmaParticleState {
    u8 m_pad0[0x20];
    YmMiasmaParticleColor m_color;
    s16 m_lifeFrames;
    s16 m_shapeAngle;
    u8 m_pad2c[4];
    YmMiasmaParticleColor m_colorStep;
    u8 m_pad38[4];
    float m_speedDecay;
    float m_speed;
    s16 m_fadeFrames;
    s16 m_colorDecayFrames;
    u8 m_hasImpulse;
    u8 m_pad49;
    s16 m_shapeFrameTime;
    s16 m_shapeCurrentFrame;
    s16 m_shapeDrawFrame;
};

struct YmMiasmaRenderParticleState {
    Vec m_position;
    u8 m_pad0C[0x14];
    YmMiasmaParticleColor m_color;
    u8 m_pad28[0x10];
    s16 m_shapeAngle;
    u8 m_pad3A[6];
    float m_speed;
    u8 m_pad44[0xA];
    s16 m_shapeDrawFrame;
};

struct YmMiasmaRenderStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_pad8[4];
    u16 m_particleCount;
    u8 m_pad0E[0x10];
    u8 m_blendMode;
    u8 m_pad33[0x41];
    u8 m_drawEnvA;
    u8 m_drawEnvB;
};

struct YmMiasmaFrameStep : PYmMiasma {
    u8 m_pad54[4];
    float m_radiusDelta;
    float m_radiusVelocity;
    float m_radiusAcceleration;
    u8 m_emitInterval;
    u8 m_pad65;
    s16 m_baseAngle;
    s16 m_angleRange;
    u8 m_pad6A[2];
    float m_speedDecayStep;
};

/*
 * --INFO--
 * PAL Address: 0x800907c4
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkB* param_2, pppYmMiasmaUnkC* param_3)
{
    u8* workBytes = (u8*)pppYmMiasma_ + 0x80 + param_3->m_serializedDataOffsets[2];
    PARTICLE_DATA* particleData = (PARTICLE_DATA*)(u32) * (u32*)workBytes;
    YmMiasmaRenderStep* step = (YmMiasmaRenderStep*)param_2;
    int i;

    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);

    for (i = 0; i < (int)step->m_particleCount; i++) {
        if (step->m_dataValIndex != 0xffff) {
            YmMiasmaRenderParticleState* state = (YmMiasmaRenderParticleState*)particleData;
            long* shape = (*(long***)pppEnvStPtr->m_particleColors)[step->m_dataValIndex];
            pppFMATRIX model;
            pppFMATRIX scaleMatrix;
            pppFMATRIX rotMatrix;
            Vec worldPos;
            GXColor amb;
            float scale;
            s16 shapeAngle;

            pppUnitMatrix(model);
            scale = state->m_speed;
            model.value[0][0] = pppMngStPtr->m_scale.x * scale;
            model.value[1][1] = pppMngStPtr->m_scale.y * scale;
            model.value[2][2] = pppMngStPtr->m_scale.z * scale;

            shapeAngle = state->m_shapeAngle;
            PSMTXRotRad(rotMatrix.value, 'z', FLOAT_80330640 * (float)shapeAngle);
            scaleMatrix = model;
            pppMulMatrix(model, rotMatrix, scaleMatrix);

            pppCopyVector(worldPos, state->m_position);
            if (Game.m_currentSceneId == 7) {
                PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);
            } else {
                PSMTXMultVec(ppvCameraMatrix02, &worldPos, &worldPos);
            }

            model.value[0][3] = worldPos.x;
            model.value[1][3] = worldPos.y;
            model.value[2][3] = worldPos.z;

            pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                0, &model, FLOAT_80330644, step->m_drawEnvB, step->m_drawEnvA, step->m_blendMode, 0, 1, 1, 0);

            amb.r = state->m_color.m_r;
            amb.g = state->m_color.m_g;
            amb.b = state->m_color.m_b;
            amb.a = state->m_color.m_a;
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppSetBlendMode(step->m_blendMode);
            pppDrawShp__FPlsP12CMaterialSetUc(
                shape, state->m_shapeDrawFrame, pppEnvStPtr->m_materialSetPtr, step->m_blendMode);
        }

        particleData = (PARTICLE_DATA*)((u8*)particleData + 0x50);
    }
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkB* param_2, pppYmMiasmaUnkC* param_3)
{
    static const char sPppYmMiasmaCpp[] = "pppYmMiasma.cpp";
    YmMiasmaFrameStep* step = (YmMiasmaFrameStep*)param_2;
    VYmMiasma* work;
    int i;
    PARTICLE_DATA* particle;
    Vec matrixPos;
    Vec delta;
    union {
        unsigned long long ull;
        double d;
    } temp;

    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (VYmMiasma*)((u8*)pppYmMiasma_ + 0x80 + param_3->m_serializedDataOffsets[2]);

    if (step->m_graphId == pppYmMiasma_->m_graphId) {
        work->m_radius = work->m_radius + step->m_radiusDelta;
        work->m_radiusVelocity = work->m_radiusVelocity + step->m_radiusVelocity;
        work->m_radiusAcceleration = work->m_radiusAcceleration + step->m_radiusAcceleration;
    }

    if (work->m_particles == 0) {
        work->m_particles = (PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)step->m_particleCount * 0x50, pppEnvStPtr->m_stagePtr, const_cast<char*>(sPppYmMiasmaCpp),
            0x18d);
        particle = work->m_particles;
        for (i = 0; i < step->m_particleCount; i++) {
            InitParticleData(work, (_pppPObject*)pppYmMiasma_, step, particle);
            particle = (PARTICLE_DATA*)((u8*)particle + 0x50);
        }
    }

    work->m_emitTimer = work->m_emitTimer + 1;
    work->m_speedDecay = work->m_speedDecay - step->m_speedDecayStep;
    if (work->m_speedDecay < FLOAT_80330644) {
        work->m_speedDecay = FLOAT_80330644;
    }

    if (work->m_emitTimer > step->m_emitInterval) {
        int r;
        s16 angleDelta;
        u32 signBit;
        s32 angleIdx;
        u32 local_28;
        u32 uStack_24;

        work->m_emitTimer = 0;
        work->m_speedDecay = step->m_unk18;

        r = rand();
        angleDelta = (s16)(r - (r / (int)step->m_angleRange) * step->m_angleRange);
        signBit = (u32)(int)angleDelta >> 31;
        if (((((int)angleDelta & 1U) ^ signBit) - signBit) == 0) {
            angleDelta = angleDelta * -1;
        }

        local_28 = 0x43300000;
        uStack_24 = (u32)(s16)(angleDelta + step->m_baseAngle) ^ 0x80000000;
        temp.ull = ((unsigned long long)local_28 << 32) | (unsigned long long)uStack_24;
        angleIdx = (s32)((((float)(temp.d - DOUBLE_80330648) * FLOAT_80330640) * FLOAT_80330650) / FLOAT_80330654);
        work->m_impulse.x = *(float*)((u8*)gPppTrigTable + ((angleIdx + 0x4000) & 0xfffc));
        work->m_impulse.y = FLOAT_80330644;
        work->m_impulse.z = *(float*)((u8*)gPppTrigTable + (angleIdx & 0xfffc));
    }

    work->m_radiusVelocity = work->m_radiusVelocity + work->m_radiusAcceleration;
    work->m_radius = work->m_radius + work->m_radiusVelocity;

    particle = work->m_particles;
    for (i = 0; i < step->m_particleCount; i++) {
        UpdateParticleData((_pppPObject*)pppYmMiasma_, (_pppCtrlTable*)param_3, step, particle);
        particle = (PARTICLE_DATA*)((u8*)particle + 0x50);
    }

    matrixPos.x = pppMngStPtr->m_matrix.value[0][3];
    matrixPos.y = pppMngStPtr->m_matrix.value[1][3];
    matrixPos.z = pppMngStPtr->m_matrix.value[2][3];

    pppSubVector(delta, matrixPos, work->m_prevPosition);
    if (PSVECDistance(&matrixPos, &work->m_prevPosition) != FLOAT_80330644) {
        work->m_prevPositionChanged = 0xff;
    } else {
        work->m_prevPositionChanged = 0;
    }

    pppCopyVector(work->m_prevPosition, matrixPos);
}

/*
 * --INFO--
 * PAL Address: 0x80090d90
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkC* param_2)
{
    VYmMiasma* work = (VYmMiasma*)((u8*)pppYmMiasma_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    void* heap = work->m_particles;

    if (heap != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(heap);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80090dc8
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkC* param_2)
{
    u8* workBytes = (u8*)pppYmMiasma_ + 0x80 + param_2->m_serializedDataOffsets[2];
    float fVar1 = FLOAT_80330644;

    *(float*)(workBytes + 0x1c) = FLOAT_80330644;
    *(float*)(workBytes + 0x20) = fVar1;
    *(float*)(workBytes + 0x24) = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80090dec
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkC* param_2)
{
    u8* workBytes = (u8*)pppYmMiasma_ + 0x80 + param_2->m_serializedDataOffsets[2];
    float fVar1;
    float fVar2 = FLOAT_80330644;
    float* work = (float*)workBytes;

    fVar1 = FLOAT_80330658;

    *(u32*)workBytes = 0;
    work[7] = fVar2;
    work[8] = fVar2;
    work[9] = fVar2;
    workBytes[8] = 0;
    work[4] = fVar1;
    work[5] = fVar2;
    work[6] = fVar2;
    work[0xc] = fVar2;
    work[0xb] = fVar2;
    work[10] = fVar2;
    workBytes[0x34] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80090e3c
 * PAL Size: 1016b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateParticleData(_pppPObject* pppPObject, _pppCtrlTable* pppCtrlTable, PYmMiasma* pYmMiasma, PARTICLE_DATA* particleData)
{
    VYmMiasma* vData = (VYmMiasma*)((u8*)pppPObject + ((pppYmMiasmaUnkC*)pppCtrlTable)->m_serializedDataOffsets[2] + 0x80);
    YmMiasmaParticleState* state = (YmMiasmaParticleState*)particleData;
    s16 frameCount;
    s16 decayCount;
    s16 alpha;
    Vec basePos;
    Vec worldPos;

    frameCount = state->m_fadeFrames;
    if (frameCount > 0) {
        alpha = state->m_color.m_a;
        alpha = alpha + (pYmMiasma->m_colorStartA - alpha) / frameCount;
        state->m_color.m_a = alpha;
        state->m_fadeFrames = state->m_fadeFrames - 1;
    }

    decayCount = state->m_colorDecayFrames;
    if (state->m_lifeFrames <= decayCount) {
        if (state->m_hasImpulse == 0) {
            state->m_color.m_a = state->m_color.m_a - (state->m_color.m_a / decayCount);
            state->m_colorDecayFrames = state->m_colorDecayFrames - 1;
        }
    }

    if (state->m_hasImpulse != 0) {
        state->m_color.m_r = state->m_color.m_r + state->m_colorStep.m_r;
        state->m_color.m_g = state->m_color.m_g + state->m_colorStep.m_g;
        state->m_color.m_b = state->m_color.m_b + state->m_colorStep.m_b;
        state->m_color.m_a = state->m_color.m_a + state->m_colorStep.m_a;

        if (state->m_color.m_r > 0xff) {
            state->m_color.m_r = 0xff;
        }
        if (state->m_color.m_g > 0xff) {
            state->m_color.m_g = 0xff;
        }
        if (state->m_color.m_b > 0xff) {
            state->m_color.m_b = 0xff;
        }
        if (state->m_color.m_a > 0xff) {
            state->m_color.m_a = 0xff;
        }

        if (state->m_color.m_r < 0) {
            state->m_color.m_r = 0;
        }
        if (state->m_color.m_g < 0) {
            state->m_color.m_g = 0;
        }
        if (state->m_color.m_b < 0) {
            state->m_color.m_b = 0;
        }
        if (state->m_color.m_a < 0) {
            state->m_color.m_a = 0;
            state->m_lifeFrames = 0;
        }
    }

    state->m_lifeFrames = state->m_lifeFrames - 1;
    if (state->m_lifeFrames < 0) {
        InitParticleData(vData, pppPObject, pYmMiasma, particleData);
    }

    pppCopyVector(worldPos, *(Vec*)particleData);
    PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

    if ((s32)Game.m_currentSceneId != 7) {
        basePos.x = pppMngStPtr->m_matrix.value[0][3];
        basePos.y = pppMngStPtr->m_matrix.value[1][3];
        basePos.z = pppMngStPtr->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &basePos, &basePos);
    } else {
        basePos = worldPos;
    }

    pppSubVector(basePos, worldPos, basePos);
    if (pppVectorLength(basePos) < (vData->m_radius - pYmMiasma->m_minDistance)) {
        state->m_speedDecay = state->m_speedDecay + pYmMiasma->m_gravity;
        state->m_hasImpulse = 1;
    }

    if (state->m_speedDecay < pYmMiasma->m_minSpeed) {
        state->m_speedDecay = pYmMiasma->m_minSpeed;
    }

    particleData->m_matrix[0][0] = particleData->m_matrix[0][0] + state->m_speedDecay * particleData->m_matrix[1][0];
    particleData->m_matrix[0][1] = particleData->m_matrix[0][1] + pYmMiasma->m_heightJitter;
    particleData->m_matrix[0][2] = particleData->m_matrix[0][2] + state->m_speedDecay * particleData->m_matrix[1][2];
    state->m_speedDecay = state->m_speedDecay - pYmMiasma->m_speedDecay;

    if (vData->m_speedDecay != FLOAT_80330644) {
        if (state->m_hasImpulse == 0) {
            Vec impulse;

            impulse = vData->m_impulse;
            PSVECScale(&impulse, &impulse, state->m_speedDecay);
            pppAddVector(*(Vec*)particleData, *(Vec*)particleData, impulse);
        }
    }

    if (pYmMiasma->m_dataValIndex != 0xffff) {
        long** shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + pYmMiasma->m_dataValIndex * 4);

        pppCalcFrameShape(*shapeTable, state->m_shapeCurrentFrame, state->m_shapeDrawFrame, state->m_shapeFrameTime,
            (short)pYmMiasma->m_shapeFrameStep);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80091234
 * PAL Size: 872b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitParticleData(VYmMiasma* vYmMiasma, _pppPObject* pppPObject, PYmMiasma* pYmMiasma, PARTICLE_DATA* particleData)
{
    YmMiasmaParticleState* state = (YmMiasmaParticleState*)particleData;
    s32 angle;
    float trigCos;
    float trigSin;
    u32 randomValue;
    int shapeRandom;
    short shapeCount;
    long** shapeTable;
    float randomHeight;
    float radiusJitter;
    float randomScale;
    Vec basePos;
    Vec normalizedPos;
    u32 angleBase;
    u32 signBit;
    float speedJitter;
    union {
        unsigned long long ull;
        double d;
    } temp;

    (void)pppPObject;

    randomValue = rand();
    temp.ull = (0x4330000000000000ULL | (u32)(randomValue ^ 0x80000000));
    randomScale = FLOAT_8033065c * (float)(temp.d - DOUBLE_80330648);
    shapeTable = *(long***)(*(int*)&pppEnvStPtr->m_particleColors[0] + pYmMiasma->m_dataValIndex * 4);
    shapeRandom = rand();
    shapeCount = *(short*)((u8*)*shapeTable + 6);
    angle = (s32)(FLOAT_80330650 * (FLOAT_80330654 * (FLOAT_80330660 * randomScale)) - FLOAT_80330664);
    shapeCount = (short)(shapeRandom - (shapeRandom / (int)shapeCount) * shapeCount);
    state->m_shapeDrawFrame = shapeCount;
    state->m_shapeCurrentFrame = shapeCount;
    trigCos = *(float*)((u8*)gPppTrigTable + (((u16)(angle + 0x4000) >> 2) << 2));
    trigSin = *(float*)((u8*)gPppTrigTable + (((u16)angle >> 2) << 2));
    *(short*)((u8*)&particleData->m_velocity.x + 8) = (short)(randomValue % 0x168);
    radiusJitter = randomScale * pYmMiasma->m_radiusJitter;
    trigCos = trigCos * (vYmMiasma->m_radius + radiusJitter);
    particleData->m_matrix[0][0] = trigCos;
    particleData->m_matrix[1][0] = trigCos;
    randomHeight = Math.RandF(pYmMiasma->m_spawnHeightJitter);
    particleData->m_matrix[0][1] = randomHeight;
    particleData->m_matrix[1][1] = randomHeight;
    trigCos = trigSin * (vYmMiasma->m_radius + radiusJitter);
    particleData->m_matrix[0][2] = trigCos;
    particleData->m_matrix[1][2] = trigCos;
    normalizedPos.x = particleData->m_matrix[1][0];
    normalizedPos.y = particleData->m_matrix[1][1];
    normalizedPos.z = particleData->m_matrix[1][2];
    pppNormalize__FR3Vec3Vec(particleData->m_matrix[1], &normalizedPos);
    if ((s32)Game.m_currentSceneId != 7) {
        basePos.x = pppMngStPtr->m_matrix.value[0][3];
        basePos.y = pppMngStPtr->m_matrix.value[1][3];
        basePos.z = pppMngStPtr->m_matrix.value[2][3];
        pppAddVector(*(Vec*)particleData, *(Vec*)particleData->m_matrix[0], basePos);
    }
    state->m_lifeFrames = (short)(pYmMiasma->m_lifeBase
        + ((int)randomValue - ((int)randomValue / (int)pYmMiasma->m_lifeRange) * pYmMiasma->m_lifeRange));
    state->m_color.m_r = (u16)pYmMiasma->m_colorStartR;
    state->m_color.m_g = (u16)pYmMiasma->m_colorStartG;
    state->m_color.m_b = (u16)pYmMiasma->m_colorStartB;
    state->m_color.m_a = 0;
    state->m_colorStep.m_r = pYmMiasma->m_colorEndR >> 7;
    state->m_colorStep.m_r = state->m_colorStep.m_r - (u16)pYmMiasma->m_colorStartR;
    state->m_colorStep.m_r = state->m_colorStep.m_r / pYmMiasma->m_colorStepFrames;
    state->m_colorStep.m_g = pYmMiasma->m_colorEndG >> 7;
    state->m_colorStep.m_g = state->m_colorStep.m_g - (u16)pYmMiasma->m_colorStartG;
    state->m_colorStep.m_g = state->m_colorStep.m_g / pYmMiasma->m_colorStepFrames;
    state->m_colorStep.m_b = pYmMiasma->m_colorEndB >> 7;
    state->m_colorStep.m_b = state->m_colorStep.m_b - (u16)pYmMiasma->m_colorStartB;
    state->m_colorStep.m_b = state->m_colorStep.m_b / pYmMiasma->m_colorStepFrames;
    state->m_colorStep.m_a = pYmMiasma->m_colorEndA >> 7;
    state->m_colorStep.m_a = state->m_colorStep.m_a - (u16)pYmMiasma->m_colorStartA;
    state->m_colorStep.m_a = state->m_colorStep.m_a / pYmMiasma->m_colorStepFrames;
    state->m_speedDecay = pYmMiasma->m_initialSpeedDecay;
    speedJitter = randomScale * pYmMiasma->m_speedVariance;
    angleBase = (u32)(int)speedJitter;
    signBit = angleBase >> 0x1f;
    if (((angleBase & 1U) ^ signBit) != signBit) {
        speedJitter = speedJitter * FLOAT_80330668;
    }
    state->m_speed = pYmMiasma->m_baseSpeed + speedJitter;
    state->m_fadeFrames = (u16)pYmMiasma->m_fadeFrames;
    state->m_colorDecayFrames = (u16)pYmMiasma->m_colorDecayFrames;
    state->m_hasImpulse = 0;
}
