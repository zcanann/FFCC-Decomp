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
extern float FLOAT_80330658;
extern double DOUBLE_80330648;
extern float RandF__5CMathFf(float, void*);
extern void pppNormalize__FR3Vec3Vec(float*, Vec*);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
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
    u32 uVar1;
    float fVar2;
    u32 uVar3;
    int iVar4;
    short sVar5;
    int iVar6;
    double dVar7;
    double dVar8;
    double dVar9;
    double dVar10;
    float local_88;
    float local_84;
    float local_80;
    float local_7c;
    float local_78;
    float local_74;
    float local_70;
    float local_6c;
    float local_68;
    float local_64;
    float local_60;
    float local_5c;
    u32 local_58;
    u32 uStack_54;
    long long local_50;
    union {
        unsigned long long ull;
        double d;
    } temp;

    (void)pppPObject;

    uVar3 = rand();
    uStack_54 = uVar3 ^ 0x80000000;
    local_58 = 0x43300000;
    temp.ull = ((unsigned long long)local_58 << 32) | (unsigned long long)uStack_54;
    dVar10 = (double)(FLOAT_8033065c * (float)(temp.d - DOUBLE_80330648));
    iVar6 = **(int**)(*(int*)&pppEnvStPtr->m_particleColors[0] + *(int*)(ymData + 4) * 4);
    iVar4 = rand();
    sVar5 = *(short*)(iVar6 + 6);
    uVar1 = (u32)(FLOAT_80330650 * FLOAT_80330654 * (float)((double)FLOAT_80330660 * dVar10) - FLOAT_80330664);
    local_50 = (long long)(int)uVar1;
    sVar5 = (short)iVar4 - (short)(iVar4 / (int)sVar5) * sVar5;
    *(short*)(particle + 0x2a) = sVar5;
    *(short*)(particle + 0x28) = sVar5;
    fVar2 = ppvSinTbl[(uVar1 + 0x4000 & 0xffff) >> 2];
    dVar9 = (double)ppvSinTbl[(uVar1 & 0xffff) >> 2];
    *(short*)(particle + 0x38) =
        (short)uVar3 +
        ((short)((unsigned long long)((long long)(int)uVar3 * 0xb60b60b7) >> 0x28) -
         (short)(((int)uVar3 / 0x168 + ((int)uVar3 >> 0x1f)) >> 0x1f)) *
            (short)-0x168;
    dVar8 = (double)(float)(dVar10 * (double)*(float*)(ymData + 0x3c));
    fVar2 = fVar2 * (float)((double)*(float*)(vData + 0x1c) + dVar8);
    *(float*)(particle + 0x00) = fVar2;
    *(float*)(particle + 0x10) = fVar2;
    dVar7 = (double)RandF__5CMathFf(*(float*)(ymData + 0x40), &Math);
    *(float*)(particle + 0x04) = (float)dVar7;
    *(float*)(particle + 0x14) = (float)dVar7;
    fVar2 = (float)(dVar9 * (double)(float)((double)*(float*)(vData + 0x1c) + dVar8));
    *(float*)(particle + 0x08) = fVar2;
    *(float*)(particle + 0x18) = fVar2;
    local_70 = *(float*)(particle + 0x10);
    local_6c = *(float*)(particle + 0x14);
    local_68 = *(float*)(particle + 0x18);
    pppNormalize__FR3Vec3Vec((float*)(particle + 0x10), (Vec*)&local_70);
    if (Game.game.m_currentSceneId != 7) {
        local_88 = pppMngStPtr->m_matrix.value[0][3];
        local_84 = pppMngStPtr->m_matrix.value[1][3];
        local_80 = pppMngStPtr->m_matrix.value[2][3];
        local_7c = *(float*)(particle + 0x00);
        local_78 = *(float*)(particle + 0x04);
        local_74 = *(float*)(particle + 0x08);
        local_64 = local_88;
        local_60 = local_84;
        local_5c = local_80;
        pppAddVector__FR3Vec3Vec3Vec((Vec*)particle, (Vec*)&local_7c, (Vec*)&local_88);
    }
    *(u16*)(particle + 0x28) =
        (u16)*(u8*)(ymData + 0x48) +
        ((short)uVar3 - (short)((int)uVar3 / (int)(u32)*(u8*)(ymData + 0x49)) * (u16)*(u8*)(ymData + 0x49));
    *(u16*)(particle + 0x20) = (u16)*(u8*)(ymData + 0x24);
    *(u16*)(particle + 0x22) = (u16)*(u8*)(ymData + 0x25);
    *(u16*)(particle + 0x24) = (u16)*(u8*)(ymData + 0x26);
    *(u16*)(particle + 0x26) = 0;
    *(short*)(particle + 0x30) = *(short*)(ymData + 0x28) >> 7;
    *(u16*)(particle + 0x30) = *(short*)(particle + 0x30) - (u16)*(u8*)(ymData + 0x24);
    *(short*)(particle + 0x30) = *(short*)(particle + 0x30) / *(short*)(ymData + 0x30);
    *(short*)(particle + 0x32) = *(short*)(ymData + 0x2a) >> 7;
    *(u16*)(particle + 0x32) = *(short*)(particle + 0x32) - (u16)*(u8*)(ymData + 0x25);
    *(short*)(particle + 0x32) = *(short*)(particle + 0x32) / *(short*)(ymData + 0x30);
    *(short*)(particle + 0x34) = *(short*)(ymData + 0x2c) >> 7;
    *(u16*)(particle + 0x34) = *(short*)(particle + 0x34) - (u16)*(u8*)(ymData + 0x26);
    *(short*)(particle + 0x34) = *(short*)(particle + 0x34) / *(short*)(ymData + 0x30);
    *(short*)(particle + 0x36) = *(short*)(ymData + 0x2e) >> 7;
    *(u16*)(particle + 0x36) = *(short*)(particle + 0x36) - (u16)*(u8*)(ymData + 0x27);
    *(short*)(particle + 0x36) = *(short*)(particle + 0x36) / *(short*)(ymData + 0x30);
    *(float*)(particle + 0x3c) = *(float*)(ymData + 0x34);
    dVar10 = dVar10 * (double)*(float*)(ymData + 0x14);
    fVar2 = (float)dVar10;
    uVar1 = (u32)dVar10;
    uVar3 = uVar1 >> 0x1f;
    if (((uVar1 & 1) ^ uVar3) != uVar3) {
        fVar2 = fVar2 * FLOAT_80330668;
    }
    *(float*)(particle + 0x40) = *(float*)(ymData + 0x10) + fVar2;
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
    u8* vData = (u8*)pppPObject + ((pppYmMiasmaUnkC*)pppCtrlTable)->m_serializedDataOffsets[2] + 0x80;
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
void pppConstructYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkC* param_2)
{
    u8* workBytes = (u8*)pppYmMiasma_ + 0x80 + param_2->m_serializedDataOffsets[2];
    float fVar1 = FLOAT_80330644;
    float* work = (float*)workBytes;

    *(u32*)workBytes = 0;
    work[7] = fVar1;
    work[8] = fVar1;
    work[9] = fVar1;
    workBytes[8] = 0;
    work[4] = FLOAT_80330658;
    work[5] = fVar1;
    work[6] = fVar1;
    work[0xc] = fVar1;
    work[0xb] = fVar1;
    work[10] = fVar1;
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
void pppRenderYmMiasma(pppYmMiasma* pppYmMiasma_, pppYmMiasmaUnkB* param_2, pppYmMiasmaUnkC* param_3)
{
    float* particle = (float*)((u8*)pppYmMiasma_ + 0x80 + param_3->m_serializedDataOffsets[2]);
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
            pppCopyVector__FR3Vec3Vec(&pos, &pos);
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
