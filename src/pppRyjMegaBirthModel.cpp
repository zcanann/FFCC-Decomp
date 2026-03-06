#include "ffcc/pppRyjMegaBirthModel.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include <string.h>

extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern "C" float RandF__5CMathFv(CMath*);
extern "C" void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);

extern s32 DAT_8032ed70;
extern float FLOAT_80330498;
extern float FLOAT_8033049c;
extern float FLOAT_803304a0;
extern float FLOAT_803304a4;
extern float FLOAT_803304b4;
extern float FLOAT_803304bc;
extern float FLOAT_803304c0;
extern float FLOAT_803304c4;
extern float FLOAT_803304c8;
extern CMath Math;
extern _pppMngSt* pppMngStPtr;
extern Mtx ppvCameraMatrix0;

static char s_pppRyjMegaBirthModel_cpp_801d9c18[] = "pppRyjMegaBirthModel.cpp";

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

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void get_rand(void)
{
    (void)RandF__5CMathFv(&Math);
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void get_noise(unsigned char count)
{
    while (count > 0) {
        (void)RandF__5CMathFv(&Math);
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
    bool ok = (*(void**)((u8*)work + 0xC) != NULL);
    if ((payload[0x136] != 0) && (*(void**)((u8*)work + 0x10) == NULL)) {
        ok = false;
    }
    if ((payload[0x131] != 0) && (*(void**)((u8*)work + 0x14) == NULL)) {
        ok = false;
    }
    if (!ok) {
        pppRyjMegaBirthModelDes((_pppPObject*)((u8*)work - 0x80), (PRyjMegaBirthModelOffsets*)payload);
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
        *(u32*)(work + 0x18) = *(u16*)(payload + 0x20);
        *(void**)(work + 0xC) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
            *(u32*)(work + 0x18) * 0xA0, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0x8D);
        if (*(void**)(work + 0xC) != 0) {
            memset(*(void**)(work + 0xC), 0, *(u32*)(work + 0x18) * 0xA0);
        }

        if (*(u8*)(payload + 0x136) != 0) {
            *(void**)(work + 0x10) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                *(u32*)(work + 0x18) * 0x30, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0x97);
            if (*(void**)(work + 0x10) != 0) {
                memset(*(void**)(work + 0x10), 0, *(u32*)(work + 0x18) * 0x30);
            }
        }

        if (*(u8*)(payload + 0x131) != 0) {
            *(void**)(work + 0x14) = pppMemAlloc__FUlPQ27CMemory6CStagePci(
                *(u32*)(work + 0x18) << 5, pppEnvStPtr->m_stagePtr, s_pppRyjMegaBirthModel_cpp_801d9c18, 0xA2);
            if (*(void**)(work + 0x14) != 0) {
                memset(*(void**)(work + 0x14), 0, *(u32*)(work + 0x18) << 5);
            }
        }

        *(float*)(work + 0x0) = *(float*)(payload + 0xF8);
        *(float*)(work + 0x4) = *(float*)(payload + 0xFC);
        *(float*)(work + 0x8) = *(float*)(payload + 0x100);
        PSVECNormalize((Vec*)(work + 0x0), (Vec*)(work + 0x0));

        posX = pObject->m_localMatrix.value[0][3];
        posY = pObject->m_localMatrix.value[1][3];
        posZ = pObject->m_localMatrix.value[2][3];
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

    if (DAT_8032ed70 == 0) {
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
    (void)work;

    u8* payload = (u8*)params;
    u8 mode = payload[0x2A];
    float spread = (float)payload[0x2B];
    float halfSpread = spread;
    float randomRange = FLOAT_803304c0 * spread;
    float speedMag = *(float*)(payload + 0x130);
    Vec pos;

    memset(particleData, 0, 0xA0);
    if (particleWMat != NULL) {
        memset(particleWMat, 0, 0x30);
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, 0x20);
    }

    pppUnitMatrix__FR10pppFMATRIX((pppFMATRIX*)&particleData->m_matrix);

    pos.x = pObject->m_localMatrix.value[0][3];
    pos.y = pObject->m_localMatrix.value[1][3];
    pos.z = pObject->m_localMatrix.value[2][3];

    if (mode < 8) {
        float baseDirectionX = *(float*)(payload + 0x48);
        float baseDirectionY = *(float*)(payload + 0x4C);
        float baseDirectionZ = *(float*)(payload + 0x50);
        float randX = (FLOAT_803304a4 * (float)(randomRange * RandF__5CMathFv(&Math) - halfSpread)) / FLOAT_803304c4;
        float randY = (FLOAT_803304a4 * (float)(randomRange * RandF__5CMathFv(&Math) - halfSpread)) / FLOAT_803304c4;
        float randZ = (FLOAT_803304a4 * (float)(randomRange * RandF__5CMathFv(&Math) - halfSpread)) / FLOAT_803304c4;

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
    }

    particleData->m_matrix[0][3] = pos.x;
    particleData->m_matrix[1][3] = pos.y;
    particleData->m_matrix[2][3] = pos.z;

    if (speedMag != FLOAT_80330498) {
        float halfSpeed = speedMag * 0.5f;
        particleData->m_velocity.x = RandF__5CMathFv(&Math) * speedMag - halfSpeed;
        particleData->m_velocity.y = RandF__5CMathFv(&Math) * speedMag - halfSpeed;
        particleData->m_velocity.z = RandF__5CMathFv(&Math) * speedMag - halfSpeed;
    }

    particleData->m_sizeStart = *(float*)(payload + 0x84);
    particleData->m_sizeEnd = *(float*)(payload + 0x88);
    particleData->m_sizeVal = *(float*)(payload + 0x8C);

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

    if ((particleWMat != NULL) && (payload[0x136] != 0)) {
        PSMTXCopy(pObject->m_localMatrix.value, *(Mtx*)particleWMat);
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

    while ((s32)particleData->m_directionTail.z > 0x7FFF) {
        particleData->m_directionTail.z = (float)((s32)particleData->m_directionTail.z - 0x10000);
    }
    while ((s32)particleData->m_directionTail.z < -0x8000) {
        particleData->m_directionTail.z = (float)((s32)particleData->m_directionTail.z + 0x10000);
    }

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
    (void)obj;
    (void)stepData;
    (void)ctrlTable;
    // Decomp fill pass: draw path kept intentionally minimal until full renderer mapping is in place.
}

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void init_matrix(_pppPObject* pObject, pppFMATRIX& out, PRyjMegaBirthModel* params, VRyjMegaBirthModel* work)
{
    u8* payload = (u8*)params;
    if (payload[0x2A] == 0) {
        PSMTXCopy(pObject->m_localMatrix.value, out.value);
    } else if (payload[0x2A] == 1 || payload[0x2A] == 3 || payload[0x2A] == 5 || payload[0x2A] == 7) {
        PSMTXIdentity(out.value);
        out.value[0][0] = pppMngStPtr->m_scale.x;
        out.value[1][1] = pppMngStPtr->m_scale.y;
        out.value[2][2] = pppMngStPtr->m_scale.z;
        out.value[0][3] = pppMngStPtr->m_position.x;
        out.value[1][3] = pppMngStPtr->m_position.y;
        out.value[2][3] = pppMngStPtr->m_position.z;
    } else {
        PSMTXIdentity(out.value);
        out.value[0][3] = *f32_at((u8*)work, 0x2C);
        out.value[1][3] = *f32_at((u8*)work, 0x30);
        out.value[2][3] = *f32_at((u8*)work, 0x34);
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
    (void)mtxA;

    u8* payload = (u8*)params;
    pppFMATRIX model;
    pppFMATRIX tmp;
    Mtx scale;

    if (payload[0x2A] == 0) {
        pppUnitMatrix__FR10pppFMATRIX(&model);
        model.value[0][3] = particleData->m_matrix[0][3];
        model.value[1][3] = particleData->m_matrix[1][3];
        model.value[2][3] = particleData->m_matrix[2][3];
    } else {
        PSMTXCopy(particleData->m_matrix, model.value);
    }

    if (particleData->m_directionTail.z != FLOAT_80330498 ||
        particleData->m_colorDeltaAdd[0] != FLOAT_80330498 ||
        particleData->m_colorDeltaAdd[1] != FLOAT_80330498) {
        Vec rot;
        rot.x = -particleData->m_directionTail.z * (FLOAT_803304a0 / FLOAT_803304a4);
        rot.y = -particleData->m_colorDeltaAdd[0] * (FLOAT_803304a0 / FLOAT_803304a4);
        rot.z = -particleData->m_colorDeltaAdd[1] * (FLOAT_803304a0 / FLOAT_803304a4);
        pppFMATRIX r;
        pppFMATRIX src;
        pppUnitMatrix__FR10pppFMATRIX(&r);
        pppUnitMatrix__FR10pppFMATRIX(&src);
        PSMTXCopy(model.value, src.value);
        pppRotMatrix(r, src, rot);
        PSMTXCopy(r.value, model.value);
    }

    PSMTXScale(scale, particleData->m_sizeStart, particleData->m_sizeEnd, particleData->m_sizeVal);
    PSMTXConcat(model.value, scale, model.value);

    if (particleWMat != NULL) {
        PSMTXConcat(*(Mtx*)particleWMat, model.value, model.value);
    } else {
        PSMTXConcat(pObject->m_localMatrix.value, model.value, model.value);
    }

    if (payload[0x136] != 0) {
        PSMTXConcat(pppMngStPtr->m_matrix.value, model.value, model.value);
    }

    PSMTXConcat(ppvCameraMatrix0, model.value, tmp.value);
    PSMTXCopy(tmp.value, out.value);

    if (copyOut != 0) {
        PSMTXCopy(out.value, mtxB.value);
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
    float value0;
    float value1;

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
