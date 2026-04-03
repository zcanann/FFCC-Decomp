#include "ffcc/pppYmMiasma.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/ppp_constants.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <string.h>

extern int rand();
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
extern float pppVectorLength__F3Vec(Vec*);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" void pppSetBlendMode(unsigned char);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);

struct VYmMiasma {
    void* m_particles;
    float m_unknown4;
    float m_unknown8;
    float m_unknownC;
    Vec m_impulse;
    float m_radius;
    Vec m_prevPosition;
    u8 m_emitTimer;
    u8 m_pad35[3];
};

struct PYmMiasma {
    u32 m_flags;
    s32 m_dataValIndex;
    s16 m_shapeFrameStep;
    s16 m_pad0A;
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

struct YmMiasmaRenderStep {
    u8 m_pad0[4];
    u16 m_dataValIndex;
    u8 m_pad6[6];
    u16 m_particleCount;
    u8 m_pad0E[0x24];
    u8 m_blendMode;
    u8 m_pad33[0x41];
    u8 m_drawEnvA;
    u8 m_drawEnvB;
};

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
    u32 angle;
    float trigCos;
    u32 randomValue;
    int shapeRandom;
    short shapeCount;
    long* shapeTable;
    double randomHeight;
    double radiusJitter;
    double trigSin;
    double randomScale;
    Vec basePos;
    Vec particlePos;
    Vec normalizedPos;
    u32 highWord;
    u32 lowWord;
    long long local_50;
    union {
        unsigned long long ull;
        double d;
    } temp;

    (void)pppPObject;

    randomValue = rand();
    lowWord = randomValue ^ 0x80000000;
    highWord = 0x43300000;
    temp.ull = ((unsigned long long)highWord << 32) | (unsigned long long)lowWord;
    randomScale = (double)(FLOAT_8033065c * (float)(temp.d - DOUBLE_80330648));
    shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + pYmMiasma->m_dataValIndex * 4);
    shapeTable = (long*)*shapeTable;
    shapeRandom = rand();
    shapeCount = *(short*)((u8*)shapeTable + 6);
    angle =
        (u32)(FLOAT_80330650 * FLOAT_80330654 * (float)((double)FLOAT_80330660 * randomScale) - FLOAT_80330664);
    local_50 = (long long)(int)angle;
    shapeCount = (short)(shapeRandom % shapeCount);
    state->m_shapeDrawFrame = shapeCount;
    state->m_shapeCurrentFrame = shapeCount;
    trigCos = *(float*)((u8*)gPppTrigTable + ((angle + 0x4000) & 0xFFFC));
    trigSin = (double)*(float*)((u8*)gPppTrigTable + (angle & 0xFFFC));
    *(short*)((u8*)&particleData->m_velocity.x + 8) = (short)(randomValue % 0x168);
    radiusJitter = (double)(float)(randomScale * (double)pYmMiasma->m_radiusJitter);
    trigCos = trigCos * (float)((double)vYmMiasma->m_radius + radiusJitter);
    particleData->m_matrix[0][0] = trigCos;
    particleData->m_matrix[1][0] = trigCos;
    randomHeight = (double)Math.RandF(pYmMiasma->m_spawnHeightJitter);
    particleData->m_matrix[0][1] = (float)randomHeight;
    particleData->m_matrix[1][1] = (float)randomHeight;
    trigCos = (float)(trigSin * (double)(float)((double)vYmMiasma->m_radius + radiusJitter));
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
        particlePos.x = particleData->m_matrix[0][0];
        particlePos.y = particleData->m_matrix[0][1];
        particlePos.z = particleData->m_matrix[0][2];
        pppAddVector(*(Vec*)particleData, particlePos, basePos);
    }
    state->m_lifeFrames = (u16)pYmMiasma->m_lifeBase + (short)(randomValue % pYmMiasma->m_lifeRange);
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
    randomScale = randomScale * (double)pYmMiasma->m_speedVariance;
    trigCos = (float)randomScale;
    angle = (u32)randomScale;
    randomValue = angle >> 0x1f;
    if (((angle & 1) ^ randomValue) != randomValue) {
        trigCos = trigCos * FLOAT_80330668;
    }
    state->m_speed = pYmMiasma->m_baseSpeed + trigCos;
    state->m_fadeFrames = (u16)pYmMiasma->m_fadeFrames;
    state->m_colorDecayFrames = (u16)pYmMiasma->m_colorDecayFrames;
    state->m_hasImpulse = 0;
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
    Vec particlePos;
    Vec worldPos;
    Vec basePos;
    Vec delta;
    Vec impulse;
    Vec currentPos;
    long** shapeTable;

    frameCount = state->m_fadeFrames;
    if (frameCount > 0) {
        state->m_color.m_a =
            state->m_color.m_a + (u8)(pYmMiasma->m_colorStartA - state->m_color.m_a) / frameCount;
        state->m_fadeFrames = state->m_fadeFrames - 1;
    }

    decayCount = state->m_colorDecayFrames;
    if (state->m_lifeFrames <= decayCount && state->m_hasImpulse == 0) {
        state->m_color.m_a = state->m_color.m_a - (state->m_color.m_a / decayCount);
        state->m_colorDecayFrames = state->m_colorDecayFrames - 1;
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

    particlePos.x = particleData->m_matrix[0][0];
    particlePos.y = particleData->m_matrix[0][1];
    particlePos.z = particleData->m_matrix[0][2];
    pppCopyVector(worldPos, particlePos);
    PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

    if ((s32)Game.m_currentSceneId != 7) {
        basePos.x = pppMngStPtr->m_matrix.value[0][3];
        basePos.y = pppMngStPtr->m_matrix.value[1][3];
        basePos.z = pppMngStPtr->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &basePos, &basePos);
    } else {
        pppCopyVector(basePos, worldPos);
    }

    pppSubVector(delta, basePos, worldPos);
    if (pppVectorLength__F3Vec(&delta) < vData->m_radius - pYmMiasma->m_minDistance) {
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

    if (vData->m_unknown4 != FLOAT_80330644 && state->m_hasImpulse == 0) {
        impulse = vData->m_impulse;
        PSVECScale(&impulse, &impulse, state->m_speedDecay);
        currentPos.x = particleData->m_matrix[0][0];
        currentPos.y = particleData->m_matrix[0][1];
        currentPos.z = particleData->m_matrix[0][2];
        pppAddVector(*(Vec*)particleData, currentPos, impulse);
    }

    if ((u16)pYmMiasma->m_dataValIndex != 0xffff) {
        shapeTable = (long**)*(u32*)&pppEnvStPtr->m_particleColors[0];
        pppCalcFrameShape(
            shapeTable[pYmMiasma->m_dataValIndex],
            state->m_shapeCurrentFrame,
            state->m_shapeDrawFrame,
            state->m_shapeFrameTime,
            (short)pYmMiasma->m_shapeFrameStep);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void RenderParticle(_pppPObject* pppPObject, PYmMiasma* pYmMiasma, PARTICLE_DATA* particleData)
{
    // Basic rendering setup
    if (!particleData) return;
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
 * PAL Address: 0x80090d90
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkC* param_2)
{
    void** workPtr = (void**)((u8*)pppYmMiasma_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    void* heap = *workPtr;

    if (heap != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(heap);
    }
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkB* param_2, pppYmMiasmaUnkC* param_3)
{
    static char sPppYmMiasmaCpp[] = "pppYmMiasma.cpp";
    u8* step = (u8*)param_2;
    u8* workBytes;
    float* work;
    int i;
    u8* particle;
    int count;
    Vec matrixPos;
    Vec oldPos;
    Vec delta;
    union {
        unsigned long long ull;
        double d;
    } temp;

    if (gPppCalcDisabled != 0) {
        return;
    }

    workBytes = (u8*)pppYmMiasma_ + 0x80 + param_3->m_serializedDataOffsets[2];
    work = (float*)workBytes;

    if (*(int*)step == *(int*)pppYmMiasma_) {
        work[7] = work[7] + *(float*)(step + 0x58);
        work[8] = work[8] + *(float*)(step + 0x5c);
        work[9] = work[9] + *(float*)(step + 0x60);
    }

    count = (int)*(u16*)(step + 0xc);
    if (*(u32*)workBytes == 0) {
        *(u32*)workBytes = (u32)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (unsigned long)count * 0x50, pppEnvStPtr->m_stagePtr, sPppYmMiasmaCpp, 0x18d);
        particle = (u8*)(u32) * (u32*)workBytes;
        for (i = 0; i < count; i++) {
            InitParticleData((VYmMiasma*)workBytes, (_pppPObject*)pppYmMiasma_, (PYmMiasma*)step, (PARTICLE_DATA*)particle);
            particle += 0x50;
        }
    }

    workBytes[8] = (u8)(workBytes[8] + 1);
    work[1] = work[1] - *(float*)(step + 0x6c);
    if (work[1] < FLOAT_80330644) {
        work[1] = FLOAT_80330644;
    }

    if (*(u8*)(step + 0x64) < workBytes[8]) {
        int r;
        s16 angleDelta;
        u32 signBit;
        u32 angleIdx;
        u32 local_28;
        u32 uStack_24;

        workBytes[8] = 0;
        work[1] = *(float*)(step + 0x18);

        r = rand();
        angleDelta = (s16)r - (s16)(r / (int)*(s16*)(step + 0x68)) * *(s16*)(step + 0x68);
        signBit = (u32)(int)angleDelta >> 31;
        if ((((int)angleDelta & 1U) ^ signBit) == signBit) {
            angleDelta = -angleDelta;
        }

        local_28 = 0x43300000;
        uStack_24 = (u32)(s16)(angleDelta + *(s16*)(step + 0x66)) ^ 0x80000000;
        temp.ull = ((unsigned long long)local_28 << 32) | (unsigned long long)uStack_24;
        angleIdx = (u32)((FLOAT_80330650 * FLOAT_80330640 * (float)(temp.d - DOUBLE_80330648)) / FLOAT_80330654);
        work[4] = *(float*)((u8*)gPppTrigTable + ((angleIdx + 0x4000) & 0xfffc));
        work[5] = FLOAT_80330644;
        work[6] = *(float*)((u8*)gPppTrigTable + (angleIdx & 0xfffc));
    }

    work[8] = work[8] + work[9];
    work[7] = work[7] + work[8];

    particle = (u8*)(u32) * (u32*)workBytes;
    for (i = 0; i < count; i++) {
        UpdateParticleData((_pppPObject*)pppYmMiasma_, (_pppCtrlTable*)param_3, (PYmMiasma*)step, (PARTICLE_DATA*)particle);
        particle += 0x50;
    }

    matrixPos.x = pppMngStPtr->m_matrix.value[0][3];
    matrixPos.y = pppMngStPtr->m_matrix.value[1][3];
    matrixPos.z = pppMngStPtr->m_matrix.value[2][3];
    oldPos.x = work[10];
    oldPos.y = work[11];
    oldPos.z = work[12];

    pppSubVector(delta, matrixPos, oldPos);
    if ((double)PSVECDistance(&matrixPos, (Vec*)(work + 10)) == (double)FLOAT_80330644) {
        workBytes[0x34] = 0;
    } else {
        workBytes[0x34] = 0xff;
    }

    pppCopyVector(*(Vec*)(work + 10), matrixPos);
}

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
            YmMiasmaParticleState* state = (YmMiasmaParticleState*)particleData;
            long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + step->m_dataValIndex * 4);
            pppFMATRIX model;
            pppFMATRIX scaleMatrix;
            pppFMATRIX rotMatrix;
            Vec srcPos;
            Vec worldPos;
            GXColor amb;
            u8 blend = step->m_blendMode;

            pppUnitMatrix(model);
            model.value[2][2] = state->m_speed;
            model.value[0][0] = pppMngStPtr->m_scale.x * model.value[2][2];
            model.value[1][1] = pppMngStPtr->m_scale.y * model.value[2][2];
            model.value[2][2] = pppMngStPtr->m_scale.z * model.value[2][2];

            PSMTXRotRad(rotMatrix.value, 'z', FLOAT_80330640 * (float)(double)state->m_shapeAngle);
            scaleMatrix = model;
            pppMulMatrix(model, rotMatrix, scaleMatrix);

            srcPos.x = particleData->m_matrix[0][0];
            srcPos.y = particleData->m_matrix[0][1];
            srcPos.z = particleData->m_matrix[0][2];
            pppCopyVector(worldPos, srcPos);
            if (Game.m_currentSceneId == 7) {
                PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);
            } else {
                PSMTXMultVec(ppvCameraMatrix0, &worldPos, &worldPos);
            }

            model.value[0][3] = worldPos.x;
            model.value[1][3] = worldPos.y;
            model.value[2][3] = worldPos.z;

            pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                0, &model, FLOAT_80330644, step->m_drawEnvB, step->m_drawEnvA, blend, 0, 1, 1, 0);

            amb.r = state->m_color.m_r;
            amb.g = state->m_color.m_g;
            amb.b = state->m_color.m_b;
            amb.a = state->m_color.m_a;
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppSetBlendMode(blend);
            pppDrawShp__FPlsP12CMaterialSetUc(
                shapeTable, state->m_shapeDrawFrame, pppEnvStPtr->m_materialSetPtr, blend);
        }

        particleData = (PARTICLE_DATA*)((u8*)particleData + 0x50);
    }
}
