#include "ffcc/pppYmMegaBirthShpTail3.h"
#include "ffcc/math.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"
extern "C" {
extern const float kPppYmMegaBirthShpTail3Zero;
extern const float FLOAT_803305A0;
extern const float FLOAT_803305A8;
extern const float FLOAT_803305AC;
extern const float FLOAT_803305B0;
extern const float FLOAT_803305C8;
extern const float FLOAT_803305CC;
extern const float FLOAT_803305D0;
extern const float FLOAT_803305D4;
}
#include "dolphin/mtx.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>

static pppFMATRIX g_matUnit3;

extern "C" const char s_pppYmMegaBirthShpTail3_cpp[] = "pppYmMegaBirthShpTail3.cpp";
/*
 * --INFO--
 * PAL Address: 8008ca98
 * PAL Size: 2316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, pppYmMegaBirthShpTail3UnkB* stepData, pppYmMegaBirthShpTail3UnkC* offsets)
{
    u8* step = (u8*)stepData;
    u8* payload = step + 0x14;
    const u32 dataValIndex = *(u32*)(step + 4);
    const s32 colorOffset = offsets->m_serializedDataOffsets[1];
    const s32 particleDataOffset = offsets->m_serializedDataOffsets[2];
    VColor* colorWork = (VColor*)((u8*)object + 0x80 + colorOffset);
    _PARTICLE_DATA* particles = *(_PARTICLE_DATA**)((u8*)&object->field_0xbc + particleDataOffset);
    _PARTICLE_WMAT* wmats = *(_PARTICLE_WMAT**)((u8*)&object->field_0xc0 + particleDataOffset);
    _PARTICLE_COLOR* colors = *(_PARTICLE_COLOR**)((u8*)&object->field_0xc4 + particleDataOffset);
    const u32 maxParticles = *(u32*)((u8*)&object->field_0xc8 + particleDataOffset);
    bool hasRequiredMemory = false;

    if (particles != 0 && wmats != 0) {
        hasRequiredMemory = true;
    }
    if (!hasRequiredMemory || dataValIndex == 0xFFFF) {
        return;
    }

    int shapeTable = **(int**)(*(int*)&ppvEnv->m_particleColors[0] + dataValIndex * 4);
    u16 workRand = *(u16*)((u8*)object + 0x80 + particleDataOffset + 0x78);
    const u8 zEnable = (u8)(((u32)__cntlzw((u32)payload[0x55])) >> 5);
    pppSetDrawEnv(
        0, &object->field_0x40, *(float*)(payload + 0xA0), payload[0xA4], step[0x0C],
        payload[0x58], 0, zEnable, 1, 0);
    pppSetBlendMode(payload[0x58]);

    for (u32 i = 0; i < maxParticles; i++) {
        u8* particle = (u8*)particles + i * 0x1F8;
        if (*(s16*)(particle + 0x22) != 0) {
            const u16 frameCountRaw = *(u16*)(payload + 0x9C);
                pppFMATRIX drawMtx;
                Vec drawPos;
                Vec cameraPos;
                Vec managerPos;
                Vec zeroVec;
                GXColor amb;
                const s16 shapeOffset = *(s16*)(shapeTable + (u16)*(u16*)(particle + 0x1C) * 8 + 0x10);
                const u8 trailReadIndex = *(u8*)(particle + 0x38);
                const u8 trailMaxIndex = (u8)(*(u8*)(particle + 0x37) - 1);
                u8 trailNextIndex = (u8)(trailReadIndex + 1);
                float drawScale = *(float*)(payload + 0x5C);
                const float alphaScale = (float)*(s16*)((u8*)colorWork + 6) / FLOAT_803305A0;
                const float stepDivisor = (float)((s32)frameCountRaw - 1);
                const float drawScaleStep =
                    (drawScale - *(float*)(payload + 0x60)) / stepDivisor;
                float fadeR = (float)(*(s16*)((u8*)&object->m_data[4] + particleDataOffset) >> 7);
                float fadeG = (float)(*(s16*)((u8*)&object->m_data[6] + particleDataOffset) >> 7);
                float fadeB = (float)(*(s16*)((u8*)&object->m_data[8] + particleDataOffset) >> 7);
                float fadeA = (float)(*(s16*)((u8*)&object->m_data[10] + particleDataOffset) >> 7) * alphaScale;
                float fadeRStep = kPppYmMegaBirthShpTail3Zero;
                float fadeGStep = kPppYmMegaBirthShpTail3Zero;
                float fadeBStep = kPppYmMegaBirthShpTail3Zero;
                float fadeAStep = kPppYmMegaBirthShpTail3Zero;
                if (stepDivisor != kPppYmMegaBirthShpTail3Zero) {
                    fadeRStep =
                        (fadeR - (float)(*(s16*)((u8*)&object->m_data[16] + particleDataOffset) >> 7)) / stepDivisor;
                    fadeGStep =
                        (fadeG - (float)(*(s16*)((u8*)&object->m_data[18] + particleDataOffset) >> 7)) / stepDivisor;
                    fadeBStep =
                        (fadeB - (float)(*(s16*)((u8*)&object->m_data[20] + particleDataOffset) >> 7)) / stepDivisor;
                    fadeAStep =
                        (fadeA - (float)(*(s16*)((u8*)&object->m_data[22] + particleDataOffset) >> 7) * alphaScale) /
                        stepDivisor;
                }
                const float spacing = *(float*)(payload + 0x98);
                Vec* history = (Vec*)(particle + 0x80);
                Vec segVec;
                float segLen;
                float segProgress = kPppYmMegaBirthShpTail3Zero;
                u16 frameCount = frameCountRaw;
                u16 particleShapeFrame = *(u16*)(particle + 0x1C);
                const u16 shapeFrameStep = *(u16*)(shapeTable + 0x12);
                const s16 shapeFrameCount = *(s16*)(shapeTable + 6);

                if (trailReadIndex == trailMaxIndex) {
                    trailNextIndex = 0;
                }

                drawPos = history[trailReadIndex];
                cameraPos = history[trailNextIndex];
                segVec.x = cameraPos.x - drawPos.x;
                segVec.y = cameraPos.y - drawPos.y;
                segVec.z = cameraPos.z - drawPos.z;
                zeroVec.x = kPppYmMegaBirthShpTail3Zero;
                zeroVec.y = kPppYmMegaBirthShpTail3Zero;
                zeroVec.z = kPppYmMegaBirthShpTail3Zero;
                segLen = PSVECDistance(&zeroVec, &segVec);

                if (payload[0x9E] == 0) {
                    continue;
                }

                while (frameCount != 0) {
                    Vec trailPos = drawPos;
                    bool canDraw = (trailPos.x != kPppYmMegaBirthShpTail3Zero) ||
                                   (trailPos.y != kPppYmMegaBirthShpTail3Zero) ||
                                   (trailPos.z != kPppYmMegaBirthShpTail3Zero);
                    if (canDraw) {
                        workRand = (u16)((u32)workRand * 0x80d + 7);
                        const u32 shapeFrame = (u32)(particleShapeFrame + workRand) / shapeFrameStep;
                        const s16 shapeOffset = *(s16*)(shapeTable + (shapeFrame % (u32)shapeFrameCount) * 8 + 0x10);

                        pppUnitMatrix(drawMtx);
                        drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                        drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                        drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;

                        if (*(s16*)(payload + 0x94) != 0) {
                            pppFMATRIX rotMtx;
                            pppFMATRIX tmpMtx;
                            PSMTXRotRad(rotMtx.value, 'z',
                                        FLOAT_803305A8 *
                                            (float)*(u16*)(particle + frameCount * sizeof(u16) + 0x40));
                            tmpMtx = drawMtx;
                            pppMulMatrix(drawMtx, rotMtx, tmpMtx);
                        }

                        if (payload[0xA5] == 0) {
                            PSMTXMultVec(ppvWorldMatrix, &trailPos, &cameraPos);
                        } else if (payload[0xA5] == 1) {
                            managerPos.x = ppvMng->m_matrix.value[0][3];
                            managerPos.y = ppvMng->m_matrix.value[1][3];
                            managerPos.z = ppvMng->m_matrix.value[2][3];
                            PSVECAdd(&trailPos, &managerPos, &trailPos);
                            PSMTXMultVec(ppvCameraMatrix, &trailPos, &cameraPos);
                        } else {
                            cameraPos = trailPos;
                        }

                        drawMtx.value[0][3] = cameraPos.x;
                        drawMtx.value[1][3] = cameraPos.y;
                        drawMtx.value[2][3] = cameraPos.z;
                        GXLoadPosMtxImm(drawMtx.value, 0);

                        amb.r = (u8)fadeR;
                        amb.g = (u8)fadeG;
                        amb.b = (u8)fadeB;
                        amb.a = (u8)(fadeA * (FLOAT_803305AC * (FLOAT_803305B0 - *(float*)(particle + 0x30))));
                        if (amb.a > 0x7F) {
                            amb.a = 0x7F;
                        }
                        GXSetChanAmbColor(GX_COLOR0A0, amb);
                        pppDrawShp(
                            reinterpret_cast<tagOAN3_SHAPE*>(shapeTable + shapeOffset), ppvEnv->m_materialSetPtr, payload[0x58]);
                    }

                    frameCount--;
                    if (frameCount == 0 || spacing <= kPppYmMegaBirthShpTail3Zero) {
                        break;
                    }

                    drawScale -= drawScaleStep;
                    fadeR -= fadeRStep;
                    fadeG -= fadeGStep;
                    fadeB -= fadeBStep;
                    fadeA -= fadeAStep;
                    if (drawScale <= kPppYmMegaBirthShpTail3Zero) {
                        break;
                    }

                    segProgress += spacing;
                    while (segLen > kPppYmMegaBirthShpTail3Zero && segProgress > segLen) {
                        const float overflow = segProgress - segLen;
                        trailNextIndex++;
                        if (trailNextIndex > trailMaxIndex) {
                            trailNextIndex = 0;
                        }
                        if (trailNextIndex == trailReadIndex) {
                            frameCount = 0;
                            break;
                        }

                        drawPos = history[trailNextIndex];
                        {
                            u8 nextTrail = (u8)(trailNextIndex + 1);
                            if (trailNextIndex == trailMaxIndex) {
                                nextTrail = 0;
                            }
                            cameraPos = history[nextTrail];
                        }
                        segVec.x = cameraPos.x - drawPos.x;
                        segVec.y = cameraPos.y - drawPos.y;
                        segVec.z = cameraPos.z - drawPos.z;
                        segLen = PSVECDistance(&zeroVec, &segVec);
                        segProgress = overflow;
                    }
                    if (frameCount == 0 || segLen <= kPppYmMegaBirthShpTail3Zero) {
                        break;
                    }

                    {
                        const float t = segProgress / segLen;
                        drawPos.x = history[trailNextIndex].x + segVec.x * t;
                        drawPos.y = history[trailNextIndex].y + segVec.y * t;
                        drawPos.z = history[trailNextIndex].z + segVec.z * t;
                    }
                }
        }

        if (wmats != 0) {
            wmats = wmats + 1;
        }
        if (colors != 0) {
            colors = colors + 1;
        }
        *(s16*)(particle + 0x1C) += *(s16*)(step + 0xA);
    }
}

/*
 * --INFO--
 * PAL Address: 8008d3a4
 * PAL Size: 1620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* object, PYmMegaBirthShpTail3* param, pppYmMegaBirthShpTail3UnkC* offsets)
{
    s8 hasRequiredMemory;
    u32 i;
    u8* paramPayload;
    int colorOffset;
    u8* particleData;
    _PARTICLE_COLOR* particleColor;
    _PARTICLE_WMAT* worldMat;
    int spawnCount;

    colorOffset = offsets->m_serializedDataOffsets[1];
    VYmMegaBirthShpTail3* const work =
        (VYmMegaBirthShpTail3*)((u8*)object + 0x80 + offsets->m_serializedDataOffsets[2]);
    VColor* const colorWork = (VColor*)((u8*)object + 0x80 + colorOffset);
    paramPayload = (u8*)param;

    if (work->m_particles == 0) {
        work->m_maxParticles = *(u16*)(paramPayload + 0xe);
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_maxParticles * 0x1f8, ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmMegaBirthShpTail3_cpp), 0x2db);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * 0x1f8);
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc(
            work->m_maxParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppYmMegaBirthShpTail3_cpp), 0x2e3);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * sizeof(_PARTICLE_WMAT));
        }

        work->m_tailScaleDirection = param->m_directionTail;
        pppNormalize(work->m_tailScaleDirection, work->m_tailScaleDirection);
    }

    if (work->m_particles == 0) {
        hasRequiredMemory = false;
    } else if (work->m_wmats == 0) {
        hasRequiredMemory = false;
    } else {
        hasRequiredMemory = true;
    }
    if (hasRequiredMemory) {
        *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(work[1].m_emitterMatrix.value[1] + 2);
        *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)work[1].m_emitterMatrix.value[1];

        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2);

        *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 3);
        *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(work[1].m_emitterMatrix.value[1] + 1);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6);

        *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(work[1].m_emitterMatrix.value[2] + 2);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 8) += *(s16*)work[1].m_emitterMatrix.value[2];

        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2);

        *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(work[1].m_emitterMatrix.value[2] + 3);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xc) += *(s16*)(work[1].m_emitterMatrix.value[2] + 1);

        *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe);
        *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6);

        if (object->m_graphId == *(s32*)paramPayload) {
            *(s16*)work[1].m_emitterMatrix.value[0] += *(s16*)(paramPayload + 0x78);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x7a);
            *(s16*)(work[1].m_emitterMatrix.value[0] + 1) += *(s16*)(paramPayload + 0x7c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 6) += *(s16*)(paramPayload + 0x7e);

            *(s16*)work[1].m_emitterMatrix.value[1] += *(s16*)(paramPayload + 0x88);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x8a);
            *(s16*)(work[1].m_emitterMatrix.value[1] + 1) += *(s16*)(paramPayload + 0x8c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 6) += *(s16*)(paramPayload + 0x8e);

            *(s16*)(work[1].m_emitterMatrix.value[1] + 2) += *(s16*)(paramPayload + 0x90);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xa) += *(s16*)(paramPayload + 0x92);
            *(s16*)(work[1].m_emitterMatrix.value[1] + 3) += *(s16*)(paramPayload + 0x94);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[1] + 0xe) += *(s16*)(paramPayload + 0x96);

            *(s16*)(work[1].m_emitterMatrix.value[0] + 2) += *(s16*)(paramPayload + 0x80);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xa) += *(s16*)(paramPayload + 0x82);
            *(s16*)(work[1].m_emitterMatrix.value[0] + 3) += *(s16*)(paramPayload + 0x84);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[0] + 0xe) += *(s16*)(paramPayload + 0x86);

            *(s16*)work[1].m_emitterMatrix.value[2] += *(s16*)(paramPayload + 0x98);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0x9a);
            *(s16*)(work[1].m_emitterMatrix.value[2] + 1) += *(s16*)(paramPayload + 0x9c);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 6) += *(s16*)(paramPayload + 0x9e);

            *(s16*)(work[1].m_emitterMatrix.value[2] + 2) += *(s16*)(paramPayload + 0xa0);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xa) += *(s16*)(paramPayload + 0xa2);
            *(s16*)(work[1].m_emitterMatrix.value[2] + 3) += *(s16*)(paramPayload + 0xa4);
            *(s16*)((u8*)work[1].m_emitterMatrix.value[2] + 0xe) += *(s16*)(paramPayload + 0xa6);
        }

        switch (*(paramPayload + 0x18)) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        {
            Vec firstCol;
            Vec secondCol;
            Vec thirdCol;

            PSMTXIdentity(work->m_emitterMatrix.value);
            firstCol.x = work->m_emitterMatrix.value[0][0];
            firstCol.y = work->m_emitterMatrix.value[1][0];
            firstCol.z = work->m_emitterMatrix.value[2][0];
            PSVECScale(&firstCol, &firstCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][0] = firstCol.x;
            work->m_emitterMatrix.value[1][0] = firstCol.y;
            work->m_emitterMatrix.value[2][0] = firstCol.z;

            secondCol.x = work->m_emitterMatrix.value[0][1];
            secondCol.y = work->m_emitterMatrix.value[1][1];
            secondCol.z = work->m_emitterMatrix.value[2][1];
            PSVECScale(&secondCol, &secondCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][1] = secondCol.x;
            work->m_emitterMatrix.value[1][1] = secondCol.y;
            work->m_emitterMatrix.value[2][1] = secondCol.z;

            thirdCol.x = work->m_emitterMatrix.value[0][2];
            thirdCol.y = work->m_emitterMatrix.value[1][2];
            thirdCol.z = work->m_emitterMatrix.value[2][2];
            PSVECScale(&thirdCol, &thirdCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][2] = thirdCol.x;
            work->m_emitterMatrix.value[1][2] = thirdCol.y;
            work->m_emitterMatrix.value[2][2] = thirdCol.z;

            work->m_emitterMatrix.value[0][3] = ppvMng->m_position.x;
            work->m_emitterMatrix.value[1][3] = ppvMng->m_position.y;
            work->m_emitterMatrix.value[2][3] = ppvMng->m_position.z;
            break;
        }
        default:
            pppCopyMatrix(work->m_emitterMatrix, ppvMng->m_matrix);
            break;
        }

        i = 0;
        particleData = (u8*)work->m_particles;
        worldMat = work->m_wmats;
        particleColor = work->m_colors;
        spawnCount = i;

        if ((gPppCalcDisabled == 0) && (*(s32*)(paramPayload + 4) != 0xffff)) {
            work->m_lifeLimit = work->m_lifeLimit + 1;
            for (; i < work->m_maxParticles; i++) {
                if (*(u16*)(particleData + 0x22) != 0) {
                    calc((_pppPObject*)object, work, param, (_PARTICLE_DATA*)particleData, colorWork, particleColor);
                } else {
                    if ((*(u16*)(paramPayload + 0x12) <= work->m_lifeLimit) && (spawnCount < *(u16*)(paramPayload + 0x10))) {
                        birth((_pppPObject*)object, work, param, colorWork, (_PARTICLE_DATA*)particleData, worldMat, particleColor);
                        spawnCount = spawnCount + 1;
                    }
                }

                if (worldMat != 0) {
                    worldMat = worldMat + 1;
                }
                if (particleColor != 0) {
                    particleColor = particleColor + 1;
                }
                particleData = particleData + 0x1f8;
            }

            if (spawnCount > 0) {
                work->m_lifeLimit = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 8008d9f8
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
          PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    int alpha = vColor->m_alpha;
    u8* particleBytes = (u8*)particleData;
    float* blend = (float*)(particleBytes + 0x30);
    float* velocityScale = (float*)(particleBytes + 0x28);
    float* tailScale = (float*)(particleBytes + 0x2c);
    u8* frameState = particleBytes + 0x30;

    if (particleColor != nullptr) {
        particleColor->m_color[0] = particleColor->m_color[0] + particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] = particleColor->m_color[1] + particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] = particleColor->m_color[2] + particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] = particleColor->m_color[3] + particleColor->m_colorFrameDeltas[3];

        alpha = vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xff) {
            alpha = 0xff;
        }
    }

    *velocityScale = *velocityScale + pYmMegaBirthShpTail3->m_colorDeltaAdd[2];
    *tailScale = *tailScale + pYmMegaBirthShpTail3->m_sizeVal;

    Vec scaled;
    pppScaleVectorXYZ(scaled, *(Vec*)(particleBytes + 0x10), *velocityScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail3->m_tailScaleDirection, *tailScale);
    pppAddVector(*(Vec*)particleData, *(Vec*)particleData, scaled);

    if (*(u16*)((u8*)&pYmMegaBirthShpTail3->m_matrix[1] + 0x4) != 0) {
        *(u16*)(particleBytes + 0x22) = *(u16*)(particleBytes + 0x22) - 1;
    }

    frameState[4] = frameState[4] + 1;

    unsigned int fadeTime = (unsigned int)frameState[5];
    if (fadeTime != 0 && frameState[4] <= fadeTime) {
        *blend = *blend -
            (float)alpha / (float)fadeTime;
        if (*blend < 0.0f) {
            *blend = 0.0f;
        }
    }

    unsigned int fadeTime2 = frameState[6];
    if (fadeTime2 != 0 && *(u16*)(particleBytes + 0x22) <= static_cast<int>(fadeTime2)) {
        unsigned char fadeInFrames = *((unsigned char*)&pYmMegaBirthShpTail3->m_matrix[1] + 7);
        *blend = *blend +
            (float)alpha / (float)fadeInFrames;
        if (*blend > 1.0f) {
            *blend = 1.0f;
        }
    }

    if (frameState[8] == 0) {
        frameState[8] = frameState[7];
    }
    frameState[8] = frameState[8] - 1;

    PSMTXMultVec(pppPObject->m_localMatrix.value, (Vec*)particleData,
                 (Vec*)(particleBytes + (unsigned int)frameState[8] * sizeof(Vec) + 0x80));
}

/*
 * --INFO--
 * PAL Address: 8008dcc8
 * PAL Size: 3704b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail3* vYmMegaBirthShpTail3,
           PYmMegaBirthShpTail3* pYmMegaBirthShpTail3, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat,
           _PARTICLE_COLOR* particleColor)
{
    u8* paramBytes = (u8*)pYmMegaBirthShpTail3;
    u8* particleBytes = (u8*)particleData;
    u8 mode = paramBytes[0x18];
    float spread = (float)paramBytes[0x19];
    float spreadRange = FLOAT_803305C8 * spread;

    memset(particleData, 0, 0x1f8);
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    if (mode < 8) {
        Vec baseDir = *(Vec*)(paramBytes + 0x20);
        s32 angles[4];
        pppFMATRIX rot;
        Vec tempVec;

        angles[0] = (s32)((float)((s32)(spreadRange * Math.RandF() - spread) << 15) / FLOAT_803305CC);
        angles[1] = (s32)((float)((s32)(spreadRange * Math.RandF() - spread) << 15) / FLOAT_803305CC);
        angles[2] = (s32)((float)((s32)(spreadRange * Math.RandF() - spread) << 15) / FLOAT_803305CC);
        angles[3] = 0;
        if ((mode == 2) || (mode == 3)) {
            angles[0] = 0;
            angles[1] = 0;
            angles[2] = 0;
            angles[3] = 0;
        }

        pppGetRotMatrixXYZ(rot, (pppIVECTOR4*)angles);
        PSMTXMultVecSR(rot.value, &baseDir, &particleData->m_velocity);
        particleData->m_velocity.x *= pYmMegaBirthShpTail3->field_0x58;
        particleData->m_velocity.y *= pYmMegaBirthShpTail3->m_speedScale.x;
        particleData->m_velocity.z *= pYmMegaBirthShpTail3->m_speedScale.y;
        tempVec = particleData->m_velocity;
        pppNormalize(particleData->m_velocity, tempVec);
    }

    if ((mode < 6) && (pYmMegaBirthShpTail3->m_speedRandRange != 0.0f)) {
        float speedRandRange = pYmMegaBirthShpTail3->m_speedRandRange;
        float speedRandHalf = FLOAT_803305D4 * speedRandRange;
        u8 randType = paramBytes[0x6a];

        if (randType <= 1) {
            if (randType == 1) {
                Math.RandF();
            }
            particleData->m_matrix[0][0] = speedRandRange * Math.RandF() - speedRandHalf;
            particleData->m_matrix[0][1] = speedRandRange * Math.RandF() - speedRandHalf;
            particleData->m_matrix[0][2] = speedRandRange * Math.RandF() - speedRandHalf;
        } else if (randType == 3) {
            particleData->m_matrix[0][0] =
                -(FLOAT_803305D0 * (speedRandRange * Math.RandF() * Math.RandF()) - speedRandRange) -
                speedRandHalf;
            particleData->m_matrix[0][1] =
                -(FLOAT_803305D0 * (speedRandRange * Math.RandF() * Math.RandF()) - speedRandRange) -
                speedRandHalf;
            particleData->m_matrix[0][2] =
                -(FLOAT_803305D0 * (speedRandRange * Math.RandF() * Math.RandF()) - speedRandRange) -
                speedRandHalf;
        } else if (randType == 5) {
            particleData->m_matrix[0][0] = -(FLOAT_803305D4 * (Math.RandF() *
                                                     (speedRandRange * Math.RandF() *
                                                      Math.RandF())) -
                                             speedRandRange) -
                                            speedRandHalf;
            particleData->m_matrix[0][1] = -(FLOAT_803305D4 * (Math.RandF() *
                                                     (speedRandRange * Math.RandF() *
                                                      Math.RandF())) -
                                             speedRandRange) -
                                            speedRandHalf;
            particleData->m_matrix[0][2] = -(FLOAT_803305D4 * (Math.RandF() *
                                                     (speedRandRange * Math.RandF() *
                                                      Math.RandF())) -
                                             speedRandRange) -
                                            speedRandHalf;
        } else {
            particleData->m_matrix[0][0] =
                Math.RandF() * (speedRandRange * Math.RandF()) - speedRandHalf;
            particleData->m_matrix[0][1] =
                Math.RandF() * (speedRandRange * Math.RandF()) - speedRandHalf;
            particleData->m_matrix[0][2] =
                Math.RandF() * (speedRandRange * Math.RandF()) - speedRandHalf;
        }

        particleData->m_matrix[0][0] *= pYmMegaBirthShpTail3->field_0x58;
        particleData->m_matrix[0][1] *= pYmMegaBirthShpTail3->m_speedScale.x;
        particleData->m_matrix[0][2] *= pYmMegaBirthShpTail3->m_speedScale.y;
    } else if (mode < 10) {
        float* pathBase = *reinterpret_cast<float**>((u8*)pppPObject + 0x70);

        if (pYmMegaBirthShpTail3->m_pathIndex >= 0) {
            short* pathInfo = (short*)(*(int*)&ppvEnv->m_particleColors[1] + pYmMegaBirthShpTail3->m_pathIndex * 8);

            if (pathBase == 0) {
                pathBase = (float*)((u8*)ppvEnv->m_mapMeshPtr[*pathInfo] + 0x2C);
            }

            if (pathBase != 0) {
                float vx;
                float vy;
                float vz;

                if (paramBytes[0x6A] == 0) {
                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (u16)pathInfo[1]) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    u16 sampleIndex = (u16)vYmMegaBirthShpTail3->m_pathIndex;
                    vYmMegaBirthShpTail3->m_pathIndex = sampleIndex + 1;

                    float* pathVec = (float*)((u8*)pathBase + *(u16*)(*(int*)(pathInfo + 2) + sampleIndex * 2) * sizeof(Vec));
                    vx = pathVec[0];
                    vy = pathVec[1];
                    vz = pathVec[2];
                } else {
                    float sampleT;

                    if (paramBytes[0x6A] == 1) {
                        Math.RandF();
                        sampleT = Math.RandF();
                    } else if (paramBytes[0x6A] == 3) {
                        sampleT = FLOAT_803305B0 - (Math.RandF() * Math.RandF() * Math.RandF());
                    } else if (paramBytes[0x6A] == 5) {
                        sampleT = FLOAT_803305B0 - (Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF());
                    } else if (paramBytes[0x6A] < 5) {
                        sampleT = Math.RandF() * Math.RandF() * Math.RandF() * Math.RandF();
                    } else {
                        sampleT = Math.RandF() * Math.RandF() * Math.RandF();
                    }

                    if ((u16)vYmMegaBirthShpTail3->m_pathIndex >= (u16)pathInfo[1]) {
                        vYmMegaBirthShpTail3->m_pathIndex = 0;
                    }

                    int sampleIndex = (int)(sampleT * (float)pathInfo[1]);
                    float* pathVec = (float*)((u8*)pathBase + *(u16*)(*(int*)(pathInfo + 2) + sampleIndex * 2) * sizeof(Vec));
                    vx = pathVec[0];
                    vy = pathVec[1];
                    vz = pathVec[2];
                }

                particleData->m_matrix[0][0] = vx * pYmMegaBirthShpTail3->field_0x58;
                particleData->m_matrix[0][1] = vy * pYmMegaBirthShpTail3->m_speedScale.x;
                particleData->m_matrix[0][2] = vz * pYmMegaBirthShpTail3->m_speedScale.y;

                if ((mode == 8) || (mode == 9)) {
                    Vec velocity = particleData->m_velocity;
                    pppNormalize(particleData->m_velocity, velocity);
                }
            }
        }
    } else if (pYmMegaBirthShpTail3->m_speedRandRange != 0.0f) {
        float speedRandRange = pYmMegaBirthShpTail3->m_speedRandRange;
        u8 randType = paramBytes[0x6a];
        float scale = speedRandRange;

        if (randType == 3) {
            scale = -(FLOAT_803305D0 * (speedRandRange * Math.RandF() * Math.RandF()) - speedRandRange);
        } else if (randType == 1) {
            Math.RandF();
            scale = speedRandRange * Math.RandF();
        } else if (randType == 2) {
            scale = Math.RandF() * (speedRandRange * Math.RandF());
        } else if (randType == 4) {
            scale = Math.RandF() * (Math.RandF() * (speedRandRange * Math.RandF()));
        } else if (randType == 5) {
            scale = -(FLOAT_803305D4 * (Math.RandF() *
                              (speedRandRange * Math.RandF() * Math.RandF())) -
                      speedRandRange);
        }

        Vec velocity = particleData->m_velocity;
        pppScaleVectorXYZ(particleData->m_velocity, velocity, scale);
    }

    if (paramBytes[0x16] != 0) {
        *(float*)(particleBytes + 0x30) = (float)vColor->m_alpha;
        particleBytes[0x35] = paramBytes[0x16];
    }
    if (paramBytes[0x17] != 0) {
        particleBytes[0x36] = paramBytes[0x17];
    }

    particleData->m_matrix[2][2] = pYmMegaBirthShpTail3->m_colorDeltaAdd[1];
    particleData->m_matrix[2][3] = pYmMegaBirthShpTail3->m_sizeStart;
    if (pYmMegaBirthShpTail3->m_colorDeltaAdd[3] != 0.0f) {
        particleData->m_matrix[2][2] +=
            (FLOAT_803305C8 * pYmMegaBirthShpTail3->m_colorDeltaAdd[3]) * Math.RandF() -
            pYmMegaBirthShpTail3->m_colorDeltaAdd[3];
    }

    if (*(s16*)(paramBytes + 0x11) == 0) {
        *(u16*)((u8*)particleData + 0x22) = 0xFFFF;
    } else {
        *(s16*)((u8*)particleData + 0x22) = *(s16*)(paramBytes + 0x11);
    }
    particleBytes[0x34] = 0;

    if (pYmMegaBirthShpTail3->m_wmatCopyMode == 0) {
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail3->m_emitterMatrix);
    } else if (pYmMegaBirthShpTail3->m_wmatCopyMode == 1) {
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail3->m_emitterMatrix);
    }

    *(u16*)(particleBytes + 0x3a) = 0;
    *(u16*)(particleBytes + 0x3c) = 0;
    *(u16*)(particleBytes + 0x3e) = 0;
    particleBytes[0x38] = 0;
    particleBytes[0x37] = 0x1f;

    Vec zeroVec;
    zeroVec.x = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.z = 0.0f;
    Vec* history = (Vec*)((u8*)particleData + 0x80);
    for (int i = 0; i < 0x1f; i++) {
        pppCopyVector(history[i], zeroVec);
        *(s16*)((u8*)particleData + 0x4c + i * sizeof(u16)) = (s16)(rand() % 360);
    }

    particleBytes[0x38] = particleBytes[0x37] - 1;
    *(u16*)(particleData->m_matrix[1] + 3) = 0;
}

/*
 * --INFO--
 * PAL Address: 8008eb40
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, pppYmMegaBirthShpTail3UnkC* param_2)
{
    int offset = param_2->m_serializedDataOffsets[2];
    u8* work = (u8*)pppYmMegaBirthShpTail3_ + 0x80 + offset;
    void** ptrBc = (void**)(work + 0x3c);
    void** ptrC0 = (void**)(work + 0x40);
    void** ptrC4 = (void**)(work + 0x44);

    if (*ptrBc != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*ptrBc));
        *ptrBc = 0;
    }
    if (*ptrC0 != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*ptrC0));
        *ptrC0 = 0;
    }
    if (*ptrC4 != 0) {
        pppHeapUseRate(reinterpret_cast<CMemory::CStage*>(*ptrC4));
        *ptrC4 = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008ebbc
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3* pppYmMegaBirthShpTail3_, pppYmMegaBirthShpTail3UnkC* param_2)
{
    pppFMATRIX* work = (pppFMATRIX*)((u8*)pppYmMegaBirthShpTail3_ + 0x80 + param_2->m_serializedDataOffsets[2]);
    float initVal;

    pppUnitMatrix(*work);
    initVal = kPppYmMegaBirthShpTail3Zero;
    work[1].value[0][2] = kPppYmMegaBirthShpTail3Zero;
    work[1].value[0][1] = initVal;
    work[1].value[0][0] = initVal;
    *reinterpret_cast<u32*>(&work[1].value[0][3]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][0]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][1]) = 0;
    *reinterpret_cast<u32*>(&work[1].value[1][2]) = 0;
    *(u16*)(work[1].value[1] + 3) = 0;
    *(u16*)((u8*)work[1].value[1] + 0xe) = 0;
    *(u16*)(work[1].value[1] + 3) = 10000;
    *(u16*)work[2].value[2] = (u16)rand();
    pppUnitMatrix(g_matUnit3);
    memset(work[1].value + 2, 0, 8);
    memset(work[1].value[2] + 2, 0, 8);
    memset(work + 2, 0, 8);
    memset(work[2].value[0] + 2, 0, 8);
    memset(work[2].value + 1, 0, 8);
    memset(work[2].value[1] + 2, 0, 8);
}
