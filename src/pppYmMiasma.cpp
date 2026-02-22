#include "ffcc/pppYmMiasma.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"

#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <string.h>

extern int rand();
extern float ppvSinTbl[];
extern float FLOAT_80330640;
extern float FLOAT_80330644;
extern float FLOAT_80330650;
extern float FLOAT_80330654;
extern float FLOAT_8033065c;
extern float FLOAT_80330660;
extern float FLOAT_80330664;
extern float FLOAT_80330668;
extern u32 DAT_80330658;
extern int DAT_8032ed70;
extern double DOUBLE_80330648;
extern double RandF__5CMathFf(double, void*);
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern float pppVectorLength__F3Vec(Vec*);
extern void pppCalcFrameShape__FPlRsRsRss(long*, short*, short*, short*, short);
extern char Math;
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
extern "C" void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
extern "C" void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
extern "C" void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char,
    unsigned char);
extern "C" void pppSetBlendMode__FUc(unsigned char);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);

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
    u8* vData = (u8*)vYmMiasma;
    u8* ymData = (u8*)pYmMiasma;
    u8* particle = (u8*)particleData;
    u32 randomValue;
    u32 angleIndex;
    s16 life;
    int colorEntry;
    int randomLifeValue;
    Vec normalized;
    Vec managerPos;
    Vec particleOffset;
    double randScale;
    double scaledRadius;
    double sinValue;
    float spread;
    float parityScale;
    u32 parityBits;
    u32 paritySign;

    (void)pppPObject;

    randomValue = rand();
    randScale = (double)(FLOAT_8033065c * (float)randomValue);

    colorEntry = **(int**)(*(int*)&pppEnvStPtr->m_particleColors[0] + *(int*)(ymData + 4) * 4);
    randomLifeValue = rand();
    life = (s16)randomLifeValue - (s16)(randomLifeValue / (int)*(s16*)(colorEntry + 6)) * *(s16*)(colorEntry + 6);
    *(s16*)(particle + 0x2A) = life;
    *(s16*)(particle + 0x28) = life;

    angleIndex = (u32)(FLOAT_80330650 * FLOAT_80330654 * (float)((double)FLOAT_80330660 * randScale) -
                       FLOAT_80330664);
    *(s16*)(particle + 0x44) = (s16)(randomValue % 0x168);

    scaledRadius = randScale * (double)*(float*)(ymData + 0x3C);
    spread = (float)((double)*(float*)(vData + 0x1C) + scaledRadius);

    sinValue = (double)ppvSinTbl[(angleIndex & 0xFFFF) >> 2];
    *(float*)(particle + 0x00) = ppvSinTbl[((angleIndex + 0x4000) & 0xFFFF) >> 2] * spread;
    *(float*)(particle + 0x10) = *(float*)(particle + 0x00);
    *(float*)(particle + 0x04) = (float)RandF__5CMathFf((double)*(float*)(ymData + 0x40), &Math);
    *(float*)(particle + 0x14) = *(float*)(particle + 0x04);
    *(float*)(particle + 0x08) = (float)(sinValue * (double)spread);
    *(float*)(particle + 0x18) = *(float*)(particle + 0x08);

    normalized.x = *(float*)(particle + 0x10);
    normalized.y = *(float*)(particle + 0x14);
    normalized.z = *(float*)(particle + 0x18);
    pppNormalize__FR3Vec3Vec((float*)(particle + 0x10), &normalized);

    if (Game.game.m_currentSceneId != 7) {
        managerPos.x = pppMngStPtr->m_matrix.value[0][3];
        managerPos.y = pppMngStPtr->m_matrix.value[1][3];
        managerPos.z = pppMngStPtr->m_matrix.value[2][3];

        particleOffset.x = *(float*)(particle + 0x00);
        particleOffset.y = *(float*)(particle + 0x04);
        particleOffset.z = *(float*)(particle + 0x08);
        pppAddVector__FR3Vec3Vec3Vec((Vec*)particle, &particleOffset, &managerPos);
    }

    *(u16*)(particle + 0x22) = (u16)*(u8*)(ymData + 0x48) +
                               ((s16)randomValue - (s16)((int)randomValue / (int)(u32)*(u8*)(ymData + 0x49)) *
                                                        (u16)*(u8*)(ymData + 0x49));
    *(u16*)(particle + 0x20) = (u16)*(u8*)(ymData + 0x24);
    *(u16*)(particle + 0x22) = (u16)*(u8*)(ymData + 0x25);
    *(u16*)(particle + 0x24) = (u16)*(u8*)(ymData + 0x26);
    *(u16*)(particle + 0x26) = 0;

    *(s16*)(particle + 0x3C) = ((*(s16*)(ymData + 0x28) >> 7) - (u16)*(u8*)(ymData + 0x24)) / *(s16*)(ymData + 0x30);
    *(s16*)(particle + 0x3E) = ((*(s16*)(ymData + 0x2A) >> 7) - (u16)*(u8*)(ymData + 0x25)) / *(s16*)(ymData + 0x30);
    *(s16*)(particle + 0x40) = ((*(s16*)(ymData + 0x2C) >> 7) - (u16)*(u8*)(ymData + 0x26)) / *(s16*)(ymData + 0x30);
    *(s16*)(particle + 0x42) = ((*(s16*)(ymData + 0x2E) >> 7) - (u16)*(u8*)(ymData + 0x27)) / *(s16*)(ymData + 0x30);

    *(float*)(particle + 0x3C) = *(float*)(ymData + 0x34);

    scaledRadius = scaledRadius * (double)*(float*)(ymData + 0x14);
    parityScale = (float)scaledRadius;
    parityBits = (u32)scaledRadius;
    paritySign = parityBits >> 31;
    if (((parityBits & 1U) ^ paritySign) != paritySign) {
        parityScale = parityScale * FLOAT_80330668;
    }
    *(float*)(particle + 0x40) = *(float*)(ymData + 0x10) + parityScale;
    *(u16*)(particle + 0x44) = *(u16*)(ymData + 0x50);
    *(u16*)(particle + 0x46) = *(u16*)(ymData + 0x52);
    *(u8*)(particle + 0x48) = 0;
}

/*
 * --INFO--
 * Address:	80090e3c
 * Size:	1016b
 */
void UpdateParticleData(_pppPObject* pppPObject, _pppCtrlTable* pppCtrlTable, PYmMiasma* pYmMiasma, PARTICLE_DATA* particleData)
{
    u8* vData = (u8*)pppPObject + ((UnkC*)pppCtrlTable)->m_serializedDataOffsets[2] + 0x80;
    u8* particle = (u8*)particleData;
    u8* ymData = (u8*)pYmMiasma;
    s16 fadeFrames;
    s16 colorDecayFrames;
    Vec worldPos;
    Vec basePos;
    Vec delta;
    Vec impulse;
    long* shapeTable;
    float minDist;

    fadeFrames = *(s16*)(particle + 0x44);
    if (fadeFrames > 0) {
        *(s16*)(particle + 0x26) =
            *(s16*)(particle + 0x26) + (u8)(*(u8*)(ymData + 0x27) - *(s16*)(particle + 0x26)) / fadeFrames;
        *(s16*)(particle + 0x44) = fadeFrames - 1;
    }

    colorDecayFrames = *(s16*)(particle + 0x46);
    if (*(s16*)(particle + 0x28) <= colorDecayFrames && *(u8*)(particle + 0x48) == 0) {
        *(s16*)(particle + 0x26) = *(s16*)(particle + 0x26) - (*(s16*)(particle + 0x26) / colorDecayFrames);
        *(s16*)(particle + 0x46) = colorDecayFrames - 1;
    }

    if (*(u8*)(particle + 0x48) != 0) {
        *(s16*)(particle + 0x20) = *(s16*)(particle + 0x20) + *(s16*)(particle + 0x30);
        *(s16*)(particle + 0x22) = *(s16*)(particle + 0x22) + *(s16*)(particle + 0x32);
        *(s16*)(particle + 0x24) = *(s16*)(particle + 0x24) + *(s16*)(particle + 0x34);
        *(s16*)(particle + 0x26) = *(s16*)(particle + 0x26) + *(s16*)(particle + 0x36);

        if (*(s16*)(particle + 0x20) > 0xff) {
            *(s16*)(particle + 0x20) = 0xff;
        }
        if (*(s16*)(particle + 0x22) > 0xff) {
            *(s16*)(particle + 0x22) = 0xff;
        }
        if (*(s16*)(particle + 0x24) > 0xff) {
            *(s16*)(particle + 0x24) = 0xff;
        }
        if (*(s16*)(particle + 0x26) > 0xff) {
            *(s16*)(particle + 0x26) = 0xff;
        }

        if (*(s16*)(particle + 0x20) < 0) {
            *(s16*)(particle + 0x20) = 0;
        }
        if (*(s16*)(particle + 0x22) < 0) {
            *(s16*)(particle + 0x22) = 0;
        }
        if (*(s16*)(particle + 0x24) < 0) {
            *(s16*)(particle + 0x24) = 0;
        }
        if (*(s16*)(particle + 0x26) < 0) {
            *(s16*)(particle + 0x26) = 0;
            *(s16*)(particle + 0x28) = 0;
        }
    }

    *(s16*)(particle + 0x28) = *(s16*)(particle + 0x28) - 1;
    if (*(s16*)(particle + 0x28) < 0) {
        InitParticleData((VYmMiasma*)vData, pppPObject, pYmMiasma, particleData);
    }

    worldPos.x = *(float*)(particle + 0x00);
    worldPos.y = *(float*)(particle + 0x04);
    worldPos.z = *(float*)(particle + 0x08);
    pppCopyVector__FR3Vec3Vec(&worldPos, &worldPos);
    PSMTXMultVec(ppvWorldMatrix, &worldPos, &worldPos);

    if (Game.game.m_currentSceneId != 7) {
        basePos.x = pppMngStPtr->m_matrix.value[0][3];
        basePos.y = pppMngStPtr->m_matrix.value[1][3];
        basePos.z = pppMngStPtr->m_matrix.value[2][3];
        PSMTXMultVec(ppvWorldMatrix, &basePos, &basePos);
    }

    pppSubVector__FR3Vec3Vec3Vec(&delta, &basePos, &worldPos);
    minDist = *(float*)(vData + 0x1c) - *(float*)(ymData + 0x1c);
    if (pppVectorLength__F3Vec(&delta) < minDist) {
        *(float*)(particle + 0x3c) = *(float*)(particle + 0x3c) + *(float*)(ymData + 0x20);
        *(u8*)(particle + 0x48) = 1;
    }

    if (*(float*)(particle + 0x3c) < *(float*)(ymData + 0x4c)) {
        *(float*)(particle + 0x3c) = *(float*)(ymData + 0x4c);
    }

    *(float*)(particle + 0x00) = *(float*)(particle + 0x00) + *(float*)(particle + 0x3c) * *(float*)(particle + 0x10);
    *(float*)(particle + 0x04) = *(float*)(particle + 0x04) + *(float*)(ymData + 0x44);
    *(float*)(particle + 0x08) = *(float*)(particle + 0x08) + *(float*)(particle + 0x3c) * *(float*)(particle + 0x18);
    *(float*)(particle + 0x3c) = *(float*)(particle + 0x3c) - *(float*)(ymData + 0x38);

    if (*(float*)(vData + 0x04) != FLOAT_80330644 && *(u8*)(particle + 0x48) == 0) {
        impulse.x = *(float*)(vData + 0x10);
        impulse.y = *(float*)(vData + 0x14);
        impulse.z = *(float*)(vData + 0x18);
        PSVECScale(&impulse, &impulse, *(float*)(particle + 0x3c));
        pppAddVector__FR3Vec3Vec3Vec((Vec*)particle, (Vec*)particle, &impulse);
    }

    if ((u16)*(u32*)(ymData + 0x04) != 0xffff) {
        shapeTable = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + *(u32*)(ymData + 0x04) * 4);
        pppCalcFrameShape__FPlRsRsRss(
            shapeTable,
            (short*)(particle + 0x4c),
            (short*)(particle + 0x4e),
            (short*)(particle + 0x4a),
            (short)*(u32*)(ymData + 0x08));
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
void pppConstructYmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
{
    u32 value;
    float fVar1 = FLOAT_80330644;
    u32* work = (u32*)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]);

    value = DAT_80330658;
    work[0] = 0;
    ((float*)work)[7] = fVar1;
    ((float*)work)[8] = fVar1;
    ((float*)work)[9] = fVar1;
    *((u8*)(work + 2)) = 0;
    work[4] = value;
    ((float*)work)[5] = fVar1;
    ((float*)work)[6] = fVar1;
    ((float*)work)[0xc] = fVar1;
    ((float*)work)[0xb] = fVar1;
    ((float*)work)[10] = fVar1;
    *((u8*)(work + 0xd)) = 0;
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
void pppConstruct2YmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
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
void pppDestructYmMiasma(pppYmMiasma* pppYmMiasma_, UnkC* param_2)
{
    if (*(void**)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]) != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(*(void**)((u8*)pppYmMiasma_ + 8 + param_2->m_serializedDataOffsets[2]));
    }
}

/*
 * --INFO--
 * Address:	80090aa4
 * Size:	748b
 */
void pppFrameYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
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

    if (DAT_8032ed70 != 0) {
        return;
    }

    workBytes = (u8*)pppYmMiasma_ + 8 + param_3->m_serializedDataOffsets[2];
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

        workBytes[8] = 0;
        work[1] = *(float*)(step + 0x18);

        r = rand();
        angleDelta = (s16)r - (s16)(r / (int)*(s16*)(step + 0x68)) * *(s16*)(step + 0x68);
        signBit = (u32)(int)angleDelta >> 31;
        if ((((int)angleDelta & 1U) ^ signBit) == signBit) {
            angleDelta = -angleDelta;
        }

        angleIdx = (u32)((FLOAT_80330650 * FLOAT_80330640 * (float)(s16)(angleDelta + *(s16*)(step + 0x66))) /
                         FLOAT_80330654);
        work[4] = *(float*)((u8*)ppvSinTbl + ((angleIdx + 0x4000) & 0xfffc));
        work[5] = FLOAT_80330644;
        work[6] = *(float*)((u8*)ppvSinTbl + (angleIdx & 0xfffc));
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

    pppSubVector__FR3Vec3Vec3Vec(&delta, &matrixPos, &oldPos);
    if ((double)PSVECDistance(&matrixPos, (Vec*)(work + 10)) == (double)FLOAT_80330644) {
        workBytes[0x34] = 0;
    } else {
        workBytes[0x34] = 0xff;
    }

    pppCopyVector__FR3Vec3Vec((Vec*)(work + 10), &matrixPos);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmMiasma(pppYmMiasma* pppYmMiasma_, UnkB* param_2, UnkC* param_3)
{
    float* particle = (float*)((u8*)pppYmMiasma_ + 8 + param_3->m_serializedDataOffsets[2]);
    u8* step = (u8*)param_2;
    u16 count = *(u16*)(step + 0x10);

    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);

    for (int i = 0; i < (int)count; i++) {
        u16 dataValIndex = *(u16*)(step + 4);
        if (dataValIndex != 0xffff) {
            long* shapeTable = *(long**)(*(int*)&pppEnvStPtr->m_particleColors[0] + dataValIndex * 4);
            pppFMATRIX model;
            pppFMATRIX scaleMatrix;
            pppFMATRIX rotMatrix;
            Mtx rotMtx;
            Vec pos;
            GXColor amb;
            u8 blend = step[0x18 + 0x1e];

            pppUnitMatrix__FR10pppFMATRIX(&model);
            model.value[2][2] = particle[0x10];
            model.value[0][0] = pppMngStPtr->m_scale.x * model.value[2][2];
            model.value[1][1] = pppMngStPtr->m_scale.y * model.value[2][2];
            model.value[2][2] = pppMngStPtr->m_scale.z * model.value[2][2];

            PSMTXRotRad(rotMtx, 'z', FLOAT_80330640 * (float)*(s16*)((u8*)particle + 0x38));
            scaleMatrix = model;
            memcpy(rotMatrix.value, rotMtx, sizeof(Mtx));
            pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&model, &rotMatrix, &scaleMatrix);

            pos.x = particle[0];
            pos.y = particle[1];
            pos.z = particle[2];
            if (Game.game.m_currentSceneId == 7) {
                PSMTXMultVec(ppvWorldMatrix, &pos, &pos);
            } else {
                PSMTXMultVec(ppvCameraMatrix0, &pos, &pos);
            }

            model.value[0][3] = pos.x;
            model.value[1][3] = pos.y;
            model.value[2][3] = pos.z;

            pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
                0, &model, FLOAT_80330644, step[0x18 + 0x61], step[0x18 + 0x60], blend, 0, 1, 1, 0);

            amb.r = *(u8*)((u8*)particle + 0x20);
            amb.g = *(u8*)((u8*)particle + 0x22);
            amb.b = *(u8*)((u8*)particle + 0x24);
            amb.a = *(u8*)((u8*)particle + 0x26);
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppSetBlendMode__FUc(blend);
            pppDrawShp__FPlsP12CMaterialSetUc(
                shapeTable, *(s16*)((u8*)particle + 0x4e), pppEnvStPtr->m_materialSetPtr, blend);
        }

        particle += 0x14;
    }
}
