#include "ffcc/pppYmBreath.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "dolphin/mtx.h"

#include <string.h>
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

extern "C" void pppHeapUseRate__FPQ27CMemory6CStage(void* stage);
extern "C" void pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(void* outMatrix, void* angle);
extern "C" void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppSetBlendMode(unsigned char);
extern "C" void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, unsigned char);
extern float FLOAT_80330c80;
extern float FLOAT_80330c84;
extern float FLOAT_80330C90;
extern float FLOAT_80330C98;
extern float FLOAT_80330CA8;
extern double DOUBLE_80330c88;
extern "C" void pppNormalize__FR3Vec3Vec(float*, Vec*);

struct pppYmBreathUnkC {
    unsigned char _pad[0xC];
    int* m_serializedDataOffsets;
};

struct pppYmBreath {
    unsigned char _pad[0x10];
    pppFMATRIX m_localMatrix;
};

struct YmBreathRenderStep {
    int m_graphId;
    int m_dataValIndex;
    int m_initWork;
    int m_stepValue;
    int m_arg3;
    unsigned char m_payload[1];
};

struct YmBreathParams {
    unsigned char _pad00[0x04];
    float m_groupRadius;
    float m_groupOwnerScale;
    int m_shapeStepValue;
    short m_shapeFrameArg;
    unsigned short m_slotCount;
    unsigned short m_groupCount;
    float m_groupSpeed;
    unsigned char _pad1C[0x02];
    unsigned short m_particleCount;
    unsigned short m_emitCount;
    unsigned short m_emitInterval;
    short m_particleLifetime;
    unsigned char m_fadeOutFrames;
    unsigned char m_fadeInFrames;
    unsigned char m_spread;
    unsigned char _pad29[0x03];
    float m_colorFrameDelta0;
    float m_colorFrameDelta1;
    float m_colorFrameDelta2;
    float m_colorFrameDelta3;
    float m_colorFrameAccel0;
    float m_colorFrameAccel1;
    float m_colorFrameAccel2;
    float m_colorFrameAccel3;
    unsigned char _pad48[0x08];
    float m_rotationStartX;
    float m_rotationStartY;
    unsigned char _pad58[0x08];
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    unsigned char _pad68[0x08];
    float m_rotationAccelX;
    float m_rotationAccelY;
    unsigned char _pad78[0x08];
    float m_rotationRandomX;
    float m_rotationRandomY;
    unsigned char _pad88[0x08];
    float m_angleStart;
    float m_angleStep;
    float m_angleAccel;
    float m_angleRandomRange;
    float m_scaleClampStart;
    float m_scaleAccel;
    float m_scaleRandomRange;
    float m_spawnOffset;
    float m_directionScaleX;
    float m_directionScaleY;
    float m_directionScaleZ;
    unsigned char _padBC[0x05];
    unsigned char m_rotationFlags;
    unsigned char m_angleFlags;
    unsigned char _padC3[0x05];
    unsigned char m_disableScaleClamp;
};

struct YmBreathParticleGroup {
    int active;
    signed char* particleIndices;
    signed char* particleStates;
    Vec position;
    Vec direction;
    float speed;
    float scale;
    Mtx matrix;
};

struct VYmBreath {
    Mtx m_matrix;
    _PARTICLE_DATA* m_particleData;
    Mtx* m_particleWmats;
    _PARTICLE_COLOR* m_particleColors;
    YmBreathParticleGroup* m_groups;
    int m_particleCount;
    unsigned short m_emitFrameCounter;
    unsigned short _pad46;
    Vec m_direction;
    short m_groupCount;
    short m_slotCount;
    unsigned char m_flags;
    unsigned char _pad59[3];
};

struct YmBreathParticleData {
    Vec m_position;
    Vec m_direction;
    unsigned char _pad18[0x08];
    short m_life;
    unsigned char _pad22[0x02];
    unsigned char m_fadeOutFrames;
    unsigned char m_fadeInFrames;
    unsigned char _pad26[0x02];
    float m_angle;
    float m_angleVelocity;
    float m_angleRandom;
    float m_rotationX;
    float m_rotationY;
    float m_rotationVelocityX;
    float m_rotationVelocityY;
    float m_rotationAccelX;
    float m_rotationAccelY;
    float m_alpha;
    float m_scale;
    unsigned char m_age;
    unsigned char _pad55[0x0B];
};

extern "C" const char s_pppYmBreath_cpp_801DA9B0[] = "pppYmBreath.cpp";

/*
 * --INFO--
 * PAL Address: 0x800bfe78
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppDestructYmBreath(pppYmBreath* ymBreath, pppYmBreathUnkC* dataOffsets)
{
    YmBreathParticleGroup* group;
    VYmBreath* state = (VYmBreath*)((unsigned char*)ymBreath + 0x80 + *dataOffsets->m_serializedDataOffsets);

    if (state->m_particleData != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleData);
        state->m_particleData = 0;
    }

    if (state->m_particleWmats != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleWmats);
        state->m_particleWmats = 0;
    }

    if (state->m_particleColors != NULL) {
        pppHeapUseRate__FPQ27CMemory6CStage(state->m_particleColors);
        state->m_particleColors = 0;
    }

    group = state->m_groups;
    if (group != NULL) {
        int i;

        for (i = 0; i < state->m_groupCount; i++) {
            if (group->particleIndices != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(group->particleIndices);
                group->particleIndices = 0;
            }

            if (group->particleStates != NULL) {
                pppHeapUseRate__FPQ27CMemory6CStage(group->particleStates);
                group->particleStates = 0;
            }

            group = (YmBreathParticleGroup*)((unsigned char*)group + 0x5C);
        }

        pppHeapUseRate__FPQ27CMemory6CStage(state->m_groups);
        state->m_groups = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800bff70
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmBreath(_pppPObject* obj)
{
    (void)obj;
}

/*
 * --INFO--
 * PAL Address: 0x800bff74
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmBreath(pppYmBreath* ymBreath, pppYmBreathUnkC* dataOffsets)
{
    VYmBreath* state = (VYmBreath*)((unsigned char*)ymBreath + 0x80 + *dataOffsets->m_serializedDataOffsets);
    float zero;

    PSMTXIdentity(state->m_matrix);
    zero = FLOAT_80330c80;

    state->m_direction.z = FLOAT_80330c80;
    state->m_direction.y = zero;
    state->m_direction.x = zero;

    state->m_particleData = 0;
    state->m_particleWmats = 0;
    state->m_particleColors = 0;
    state->m_groups = 0;
    state->m_particleCount = 0;

    state->m_emitFrameCounter = 10000;
    state->m_groupCount = 0;
    state->m_slotCount = 0;
    state->m_flags = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800bffec
 * PAL Size: 1292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, pppYmBreathUnkC* offsets)
{
    YmBreathRenderStep* step;
    int workOffset;
    int colorOffset;
    VYmBreath* work;
    VColor* color;
    Vec* source;
    Mtx* matrixList;
    float* colorDelta;
    int* groupData;
    int groupCount;
    long** shape;
    unsigned char colorR;
    unsigned char colorG;
    unsigned char colorB;
    unsigned char colorA;
    int i;

    step = (YmBreathRenderStep*)pYmBreath;
    workOffset = offsets->m_serializedDataOffsets[0];
    colorOffset = offsets->m_serializedDataOffsets[1];
    work = reinterpret_cast<VYmBreath*>(reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + workOffset);
    color = reinterpret_cast<VColor*>(reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + colorOffset);
    source = reinterpret_cast<Vec*>(work->m_particleData);
    matrixList = work->m_particleWmats;
    colorDelta = reinterpret_cast<float*>(work->m_particleColors);
    groupData = (int*)work->m_groups;
    groupCount = work->m_particleCount;

    if (step->m_stepValue == 0xFFFF) {
        return;
    }

    shape = *(long***)(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pppEnvStPtr) + 0xC) +
                       step->m_stepValue * 4);
    pppSetBlendMode(step->m_payload[8]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        0, 0, *reinterpret_cast<float*>(step->m_payload + 0xB0), step->m_payload[0xB6], step->m_payload[0xB5],
        step->m_payload[8], 0, 1, 1, 0);

    colorR = color->m_red;
    colorG = color->m_green;
    colorB = color->m_blue;
    colorA = color->m_alpha;

    for (i = 0; i < groupCount; i++) {
        if (*(short*)&source[2].z > 0) {
            _GXColor amb;
            Mtx drawMtx;
            Mtx rotMtx;
            Vec pos;
            pppFMATRIX viewMtx;
            int r;
            int g;
            int b;
            int a;

            PSMTXIdentity(drawMtx);
            drawMtx[0][0] = source[4].y * pppMngStPtr->m_scale.x;
            drawMtx[1][1] = source[4].z * pppMngStPtr->m_scale.y;
            drawMtx[2][2] = drawMtx[0][0];
            if (FLOAT_80330c80 != source[3].y) {
                PSMTXRotRad(rotMtx, 'z', FLOAT_80330c84 * source[3].y);
                PSMTXConcat(drawMtx, rotMtx, drawMtx);
            }

            pppUnitMatrix(viewMtx);
            PSMTXConcat(*matrixList, ymBreath->m_localMatrix.value, viewMtx.value);
            PSMTXConcat(ppvCameraMatrix0, viewMtx.value, viewMtx.value);
            PSMTXMultVec(viewMtx.value, source, &pos);
            drawMtx[0][3] = pos.x;
            drawMtx[1][3] = pos.y;
            drawMtx[2][3] = pos.z;
            GXLoadPosMtxImm(drawMtx, 0);

            r = colorR;
            g = colorG;
            b = colorB;
            a = (int)((float)(int)colorA - source[6].y);
            if (colorDelta != 0) {
                r += (int)colorDelta[0];
                g += (int)colorDelta[1];
                b += (int)colorDelta[2];
                a += (int)colorDelta[3];
            }

            if (r < 0) {
                r = 0;
            } else if (r > 0xFF) {
                r = 0xFF;
            }
            if (g < 0) {
                g = 0;
            } else if (g > 0xFF) {
                g = 0xFF;
            }
            if (b < 0) {
                b = 0;
            } else if (b > 0xFF) {
                b = 0xFF;
            }
            if (a < 0) {
                a = 0;
            } else if (a > 0x7F) {
                a = 0x7F;
            }

            amb.r = (unsigned char)r;
            amb.g = (unsigned char)g;
            amb.b = (unsigned char)b;
            amb.a = (unsigned char)a;
            GXSetChanAmbColor(GX_COLOR0A0, amb);
            pppDrawShp__FPlsP12CMaterialSetUc(*shape, *(short*)((unsigned char*)&source[7].y + 2),
                                              pppEnvStPtr->m_materialSetPtr,
                                              step->m_payload[8]);
        }

        if (matrixList != 0) {
            matrixList++;
        }
        if (colorDelta != 0) {
            colorDelta += 8;
        }
        source += 8;
    }

    if ((CFlatFlags & 0x200000) != 0) {
        for (i = 0; i < (int)*(unsigned short*)step->m_payload; i++) {
            if (groupData[0] == 1) {
                _GXColor debugColor;
                int firstParticle;
                int j;
                float scale;
                Mtx sphereMtx;
                Mtx tempMtx;
                Vec debugPos;

                switch (i) {
                case 0:
                case 2:
                    debugColor.r = 0x80;
                    debugColor.g = 0x00;
                    debugColor.b = 0x00;
                    debugColor.a = 0xFF;
                    break;
                case 1:
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0xFF;
                    debugColor.a = 0xFF;
                    break;
                case 3:
                    debugColor.r = 0x80;
                    debugColor.g = 0x80;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                    break;
                default:
                    debugColor.r = 0x00;
                    debugColor.g = 0x60;
                    debugColor.b = 0x80;
                    debugColor.a = 0xFF;
                    break;
                }

                firstParticle = -1;
                for (j = 0; j < (int)*(unsigned short*)((unsigned char*)&step->m_arg3 + 2); j++) {
                    if (*(signed char*)(groupData[2] + j) != -1) {
                        firstParticle = (int)*(signed char*)(groupData[1] + j);
                        break;
                    }
                }

                scale = *(float*)(groupData + 10);
                PSMTXIdentity(sphereMtx);
                sphereMtx[0][0] = scale;
                sphereMtx[1][1] = scale;
                sphereMtx[2][2] = scale;

                PSMTXConcat(work->m_particleWmats[firstParticle], ymBreath->m_localMatrix.value, tempMtx);
                PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
                PSMTXMultVec(tempMtx, (Vec*)(groupData + 3), &debugPos);
                sphereMtx[0][3] = debugPos.x;
                sphereMtx[1][3] = debugPos.y;
                sphereMtx[2][3] = debugPos.z;
                Graphic.DrawSphere(sphereMtx, debugColor);
            }
            groupData += 0x17;
        }

        pppSetBlendMode(1);
        pppSetBlendMode(0);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 2);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c04f8
 * PAL Size: 1264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmBreath(pppYmBreath* ymBreath, PYmBreath* pYmBreath, pppYmBreathUnkC* offsets)
{
    int colorOffset;
    int* dataOffsets;
    _pppMngSt* mngSt;
    VYmBreath* work;
    VColor* color;
    int* groupData;
    Mtx* particleWMat;
    Mtx* particleMtx;
    int i;
    int groupIndex;
    int firstParticle;
    int groupTable;
    int slotIndex;
    unsigned int slotCount;
    bool ready;
    float scaledOwner;
    Mtx scaleMtx;
    Mtx worldMtx;
    pppFMATRIX rotMtx;
    Vec origin;
    Vec dir;
    Vec dirNorm;
    Vec target;
    Vec hitVector;

    if (gPppCalcDisabled != 0) {
        return;
    }

    dataOffsets = offsets->m_serializedDataOffsets;
    mngSt = pppMngStPtr;
    colorOffset = dataOffsets[1];
    work = reinterpret_cast<VYmBreath*>(reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + dataOffsets[0]);
    color = (VColor*)(reinterpret_cast<unsigned char*>(ymBreath) + 0x80 + colorOffset);

    if (work->m_particleData == NULL) {
        int* groupTable;

        work->m_particleCount = (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x1E);
        work->m_slotCount = *(unsigned short*)((unsigned char*)pYmBreath + 0x12);
        work->m_groupCount = *(unsigned short*)((unsigned char*)pYmBreath + 0x14);

        work->m_particleData =
            (_PARTICLE_DATA*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount * 0x60),
                                                                  pppEnvStPtr->m_stagePtr,
                                                                  const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x243);
        if (work->m_particleData != NULL) {
            memset(work->m_particleData, 0, (unsigned long)(work->m_particleCount * 0x60));
        }

        work->m_particleWmats =
            (Mtx*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount * 0x30),
                                                       pppEnvStPtr->m_stagePtr,
                                                       const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x249);
        if (work->m_particleWmats != NULL) {
            memset(work->m_particleWmats, 0, (unsigned long)(work->m_particleCount * 0x30));
        }

        work->m_particleColors =
            (_PARTICLE_COLOR*)pppMemAlloc__FUlPQ27CMemory6CStagePci((unsigned long)(work->m_particleCount << 5),
                                                                   pppEnvStPtr->m_stagePtr,
                                                                   const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x24F);
        if (work->m_particleColors != NULL) {
            memset(work->m_particleColors, 0, (unsigned long)(work->m_particleCount << 5));
        }

        work->m_groups =
            (YmBreathParticleGroup*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                (unsigned long)((int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14) * 0x5C),
                pppEnvStPtr->m_stagePtr,
                const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x255);
        if (work->m_groups != NULL) {
            memset(work->m_groups, 0,
                   (unsigned long)((int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14) * 0x5C));

            groupTable = (int*)work->m_groups;
            for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); i++) {
                groupTable[1] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12),
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x260);
                void* particleIndices = (void*)groupTable[1];
                memset(particleIndices, -1,
                       (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12));

                groupTable[2] = (int)pppMemAlloc__FUlPQ27CMemory6CStagePci(
                    (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12),
                    pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppYmBreath_cpp_801DA9B0), 0x263);
                void* particleStates = (void*)groupTable[2];
                memset(particleStates, -1,
                       (unsigned long)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12));
                groupTable[0] = 0;
                groupTable += 0x17;
            }
        }

        work->m_direction.x = 0.0f;
        work->m_direction.y = 0.0f;
        work->m_direction.z = 1.0f;
        PSVECNormalize(&work->m_direction, &work->m_direction);
    }

    PSMTXCopy(mngSt->m_matrix.value, work->m_matrix);
    UpdateAllParticle(reinterpret_cast<_pppPObject*>(ymBreath), work, pYmBreath, color);

    particleWMat = work->m_particleWmats;
    groupData = (int*)work->m_groups;
    for (groupIndex = 0; groupIndex < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14);
         groupIndex++) {
        slotCount = (unsigned int)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
        groupTable = (int)groupData;
        for (slotIndex = 0; slotIndex < (int)slotCount; slotIndex++) {
            if ((*(signed char*)(*(int*)(groupTable + 4) + slotIndex) == -1) ||
                (*(signed char*)(*(int*)(groupTable + 8) + slotIndex) != 1)) {
                ready = false;
                goto group_ready;
            }
        }
        ready = true;
group_ready:
        if (ready) {
            firstParticle = -1;
            scaledOwner = mngSt->m_ownerScale * *(float*)((unsigned char*)pYmBreath + 8);
            for (slotIndex = 0; slotCount != 0; slotCount--) {
                if (*(signed char*)(*(int*)(groupTable + 8) + slotIndex) != -1) {
                    firstParticle = (int)*(signed char*)(*(int*)(groupTable + 4) + slotIndex);
                    break;
                }
                slotIndex++;
            }

            PSMTXIdentity(scaleMtx);
            scaleMtx[0][0] = scaledOwner;
            scaleMtx[1][1] = scaledOwner;
            scaleMtx[2][2] = scaledOwner;
            particleMtx = (Mtx*)((unsigned char*)particleWMat + firstParticle * 0x30);
            PSMTXConcat(*particleMtx, ymBreath->m_localMatrix.value, worldMtx);
            PSMTXMultVec(worldMtx, (Vec*)(groupTable + 0xC), &origin);
            pppCopyMatrix(rotMtx, *reinterpret_cast<pppFMATRIX*>(particleMtx));
            rotMtx.value[0][3] = FLOAT_80330c80;
            rotMtx.value[1][3] = FLOAT_80330c80;
            rotMtx.value[2][3] = FLOAT_80330c80;
            *(float*)(groupTable + 0x28) = scaledOwner;
            pppCopyVector(dir, *(Vec*)(groupTable + 0x18));
            PSMTXMultVec(rotMtx.value, &dir, &dir);
            pppCopyVector(dirNorm, dir);
            pppNormalize__FR3Vec3Vec(reinterpret_cast<float*>(&dir), &dirNorm);
            PSVECScale(&dir, &target, *(float*)(groupTable + 0x24));
            pppAddVector(target, origin, target);
            pppSubVector(hitVector, target, origin);
            pppHitCylinderSendSystem(mngSt, &origin, &hitVector, scaledOwner,
                                                                *(float*)((unsigned char*)pYmBreath + 4));
        }

        groupData += 0x17;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c09e8
 * PAL Size: 1072b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateAllParticle(_pppPObject* pppObject, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor)
{
    bool found;
    int spawnCount;
    int i;
    int j;
    int k;
    int group;
    int groupTableWork;
    YmBreathParticleGroup* groupTable;
    YmBreathParticleGroup* groupData;
    unsigned char* particleData;
    unsigned char* particleWmat;
    unsigned char* particleColor;
    int maxParticleCount;
    short foundSlot;
    short foundGroup;
    Vec stepVelocity;
    Vec unitVelocity;

    spawnCount = 0;
    particleData = (unsigned char*)vYmBreath->m_particleData;
    particleWmat = (unsigned char*)vYmBreath->m_particleWmats;
    particleColor = (unsigned char*)vYmBreath->m_particleColors;
    groupTable = vYmBreath->m_groups;
    maxParticleCount = vYmBreath->m_particleCount;

    if ((gPppCalcDisabled == 0) && (*(int*)((unsigned char*)pYmBreath + 0xC) != 0xFFFF)) {
        vYmBreath->m_emitFrameCounter = vYmBreath->m_emitFrameCounter + 1;

        for (i = 0; i < maxParticleCount; i++) {
            if (*(short*)(particleData + 0x50) >= 1) {
                UpdateParticle(vYmBreath, pYmBreath, (_PARTICLE_DATA*)particleData, vColor,
                               (_PARTICLE_COLOR*)particleColor);
                pppCalcFrameShape(**(long***)(*(int*)((unsigned char*)pppEnvStPtr + 0xC) +
                                             *(int*)((unsigned char*)pYmBreath + 0xC) * 4),
                                  *(short*)(particleData + 0x58), *(short*)(particleData + 0x5A),
                                  *(short*)(particleData + 0x56), *(short*)((unsigned char*)pYmBreath + 0x10));
            } else {
                float zero = FLOAT_80330c80;

                groupTableWork = (int)vYmBreath->m_groups;
                for (foundGroup = 0;
                     foundGroup < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14);
                     foundGroup++) {
                    for (foundSlot = 0;
                         foundSlot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                         foundSlot++) {
                        if ((int)(short)i == (int)*(signed char*)(*(int*)(groupTableWork + 4) + (int)foundSlot)) {
                            found = true;
                            goto found_index;
                        }
                    }
                    groupTableWork += 0x5C;
                }
                found = false;
                foundSlot = -1;
                foundGroup = -1;

                found_index:
                if (found) {
                    groupTable[(int)foundGroup].particleIndices[(int)foundSlot] = -1;
                }

                if ((int)foundGroup != -1) {
                    int slot;
                    unsigned int slotCount;

                    slot = 0;
                    group = (int)vYmBreath->m_groups + (int)foundGroup * 0x5C;
                    slotCount = *(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                    while (slotCount != 0) {
                        if ((*(signed char*)(*(int*)(group + 4) + slot) != -1) ||
                            (*(signed char*)(*(int*)(group + 8) + slot) != 1)) {
                            found = false;
                            goto group_checked;
                        }
                        slot++;
                        slotCount--;
                    }
                    found = true;

                group_checked:
                    if (found) {
                        groupData = &groupTable[(int)foundGroup];
                        for (slot = 0; slot < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                             slot++) {
                            groupData->particleStates[slot] = -1;
                            groupData->position.x = zero;
                            groupData->position.y = zero;
                            groupData->position.z = zero;
                            groupData->direction.x = zero;
                            groupData->direction.y = zero;
                            groupData->direction.z = zero;
                            groupData->speed = zero;
                        }
                        groupData->active = 0;
                    }
                }

                if ((*(unsigned short*)((unsigned char*)pYmBreath + 0x22) <= vYmBreath->m_emitFrameCounter) &&
                    (spawnCount < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x20))) {
                    BirthParticle(pppObject, vYmBreath, pYmBreath, vColor, (_PARTICLE_DATA*)particleData,
                                  (Mtx*)particleWmat, (_PARTICLE_COLOR*)particleColor);
                    found = true;
                    spawnCount += 1;
                    groupData = groupTable;
                    for (j = 0; j < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); j++) {
                        for (k = 0; k < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x12);
                             k++) {
                            if ((groupData->particleIndices[k] == -1) && (groupData->particleStates[k] == -1)) {
                                groupData->particleIndices[k] = (signed char)i;
                                found = false;
                                groupData->particleStates[k] = 1;
                            }
                            if (!found) {
                                break;
                            }
                        }
                        if (!found) {
                            break;
                        }
                        groupData += 1;
                    }
                }
            }

            if (particleWmat != NULL) {
                particleWmat += 0x30;
            }
            if (particleColor != NULL) {
                particleColor += 0x20;
            }
            particleData += 0x60;
        }

        if (spawnCount > 0) {
            vYmBreath->m_emitFrameCounter = 0;
        }

        groupData = groupTable;
        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); i++) {
            if ((groupData->active != 1) && (*groupData->particleIndices != -1) && (*groupData->particleStates == 1)) {
                unitVelocity.x = FLOAT_80330c80;
                unitVelocity.y = FLOAT_80330c80;
                unitVelocity.z = FLOAT_80330C90;
                groupData->speed = *(float*)((unsigned char*)pYmBreath + 0x18);
                pppCopyVector(groupData->direction, unitVelocity);
                groupData->position.x = 0.0f;
                groupData->position.y = 0.0f;
                groupData->position.z = 0.0f;
                PSMTXCopy(*(Mtx*)pppMngStPtr, groupData->matrix);
                groupData->active = 1;
            }
            groupData += 1;
        }

        for (i = 0; i < (int)(unsigned short)*(unsigned short*)((unsigned char*)pYmBreath + 0x14); i++) {
            if (groupTable->active != 0) {
                PSVECScale(&groupTable->direction, &stepVelocity, groupTable->speed);
                PSVECAdd(&stepVelocity, &groupTable->position, &groupTable->position);
            }
            groupTable += 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c0e18
 * PAL Size: 884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateParticle(VYmBreath* vYmBreath, PYmBreath* pYmBreath, _PARTICLE_DATA* particleData, VColor* vColor,
                    _PARTICLE_COLOR* particleColor)
{
    YmBreathParams* params = reinterpret_cast<YmBreathParams*>(pYmBreath);
    int alpha = vColor->m_alpha;
    YmBreathParticleData* particle = reinterpret_cast<YmBreathParticleData*>(particleData);
    char frameCount;
    Vec step;
    float angleRange;

    (void)vYmBreath;

    if (particleColor != NULL) {
        particleColor->m_color[0] += particleColor->m_colorFrameDeltas[0];
        particleColor->m_color[1] += particleColor->m_colorFrameDeltas[1];
        particleColor->m_color[2] += particleColor->m_colorFrameDeltas[2];
        particleColor->m_color[3] += particleColor->m_colorFrameDeltas[3];
        particleColor->m_colorFrameDeltas[0] += params->m_colorFrameAccel0;
        particleColor->m_colorFrameDeltas[1] += params->m_colorFrameAccel1;
        particleColor->m_colorFrameDeltas[2] += params->m_colorFrameAccel2;
        particleColor->m_colorFrameDeltas[3] += params->m_colorFrameAccel3;
        alpha = (int)vColor->m_alpha + (int)particleColor->m_color[3];
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
    }

    particle->m_angle += particle->m_angleVelocity;
    if (params->m_angleFlags & 0x10) {
        particle->m_angleVelocity = params->m_angleAccel + particle->m_angleRandom + particle->m_angleVelocity;
    } else {
        particle->m_angleVelocity += params->m_angleAccel;
    }

    angleRange = 6.2831855f;
    while (angleRange <= particle->m_angle) {
        particle->m_angle -= angleRange;
    }
    while (particle->m_angle < 0.0f) {
        particle->m_angle += angleRange;
    }

    particle->m_rotationX += particle->m_rotationVelocityX;
    particle->m_rotationY += particle->m_rotationVelocityY;
    if (params->m_rotationFlags & 0x10) {
        particle->m_rotationVelocityX = params->m_rotationAccelX + particle->m_rotationAccelX + particle->m_rotationVelocityX;
        particle->m_rotationVelocityY = params->m_rotationAccelY + particle->m_rotationAccelY + particle->m_rotationVelocityY;
    } else {
        particle->m_rotationVelocityX += params->m_rotationAccelX;
        particle->m_rotationVelocityY += params->m_rotationAccelY;
    }

    particle->m_scale += params->m_scaleAccel;
    if (params->m_disableScaleClamp == 0) {
        float zero = 0.0f;
        if (zero < params->m_scaleClampStart) {
            if (params->m_scaleAccel < zero) {
                if (particle->m_scale < zero) {
                    particle->m_scale = zero;
                }
            }
        } else if (params->m_scaleClampStart < zero) {
            if ((zero < params->m_scaleAccel) && (zero < particle->m_scale)) {
                particle->m_scale = zero;
            }
        }
    }

    PSVECScale(&particle->m_direction, &step, particle->m_scale);
    PSVECAdd(&step, &particle->m_position, &particle->m_position);

    if (params->m_particleLifetime != 0) {
        particle->m_life = particle->m_life - 1;
    }
    particle->m_age = particle->m_age + 1;

    frameCount = particle->m_fadeOutFrames;
    if ((frameCount != '\0') && ((int)(unsigned int)particle->m_age <= (int)frameCount)) {
        particle->m_alpha -= (float)alpha / (float)(int)frameCount;
    }

    frameCount = particle->m_fadeInFrames;
    if ((frameCount != '\0') && ((int)particle->m_life <= (int)frameCount)) {
        particle->m_alpha += (float)alpha / (float)(unsigned int)params->m_fadeInFrames;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800c118c
 * PAL Size: 1580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void BirthParticle(_pppPObject*, VYmBreath* vYmBreath, PYmBreath* pYmBreath, VColor* vColor, _PARTICLE_DATA* particleData,
                   Mtx* particleWmat, _PARTICLE_COLOR* particleColor)
{
    unsigned char* breath = (unsigned char*)pYmBreath;
    Vec* particle = reinterpret_cast<Vec*>(particleData);
    int angle[4];
    pppFMATRIX rotMtx;
    Vec baseDir;
    Vec directionNorm;
    float spread;
    float range;
    unsigned char flags;

    spread = (float)(unsigned int)*(unsigned char*)(breath + 0x28);
    range = FLOAT_80330CA8 * spread;

    memset(particleData, 0, 0x60);
    if (particleWmat != NULL) {
        memset(particleWmat, 0, 0x30);
    }
    if (particleColor != NULL) {
        memset(particleColor, 0, 0x20);
    }

    baseDir.x = 0.0f;
    baseDir.y = 0.0f;
    baseDir.z = FLOAT_80330C90;

    angle[0] = (int)((float)((int)(range * Math.RandF() - spread) << 15) / FLOAT_80330C98);
    angle[1] = (int)((float)((int)(range * Math.RandF() - spread) << 15) / FLOAT_80330C98);
    angle[2] = (int)((float)((int)(range * Math.RandF() - spread) << 15) / FLOAT_80330C98);
    angle[3] = 0;

    pppGetRotMatrixXYZ__FR10pppFMATRIXP11pppIVECTOR4(&rotMtx, &angle);
    PSMTXMultVecSR(rotMtx.value, &baseDir, &particle[1]);

    particle[1].x *= *(float*)(breath + 0xB0);
    particle[1].y *= *(float*)(breath + 0xB4);
    particle[1].z *= *(float*)(breath + 0xB8);

    directionNorm = particle[1];
    pppNormalize__FR3Vec3Vec(reinterpret_cast<float*>(&particle[1]), &directionNorm);

    if (*(float*)(breath + 0xAC) != 0.0f) {
        PSVECScale(&particle[1], &particle[0], *(float*)(breath + 0xAC));
    }

    if (*(char*)(breath + 0x26) != '\0') {
        particle[6].y = (float)(unsigned int)vColor->m_alpha;
        *(char*)&particle[3].x = *(char*)(breath + 0x26);
    }
    if (*(char*)(breath + 0x27) != '\0') {
        *(char*)((unsigned char*)&particle[3].x + 1) = *(char*)(breath + 0x27);
    }

    particle[3].y = *(float*)(breath + 0x90);
    particle[3].z = *(float*)(breath + 0x94);

    if (*(char*)(breath + 0xC2) != '\0') {
        particle[4].x = *(float*)(breath + 0x9C) * Math.RandF();
        flags = *(unsigned char*)(breath + 0xC2);
        if (((flags & 1) != 0) && ((flags & 2) != 0)) {
            if (Math.RandF() > 0.5f) {
                particle[4].x *= -1.0f;
            }
        } else if ((flags & 2) != 0) {
            particle[4].x *= -1.0f;
        }
    }

    if ((*(unsigned char*)(breath + 0xC2) & 4) != 0) {
        particle[3].y += particle[4].x;
    }
    if ((*(unsigned char*)(breath + 0xC2) & 8) != 0) {
        particle[3].z += particle[4].x;
    }

    while (particle[3].y >= 6.2831855f) {
        particle[3].y -= 6.2831855f;
    }
    while (particle[3].y < 0.0f) {
        particle[3].y += 6.2831855f;
    }

    particle[4].y = *(float*)(breath + 0x50);
    particle[4].z = *(float*)(breath + 0x54);
    particle[5].x = *(float*)(breath + 0x60);
    particle[5].y = *(float*)(breath + 0x64);

    if (*(unsigned char*)(breath + 0xC1) != 0) {
        flags = *(unsigned char*)(breath + 0xC1);
        if ((flags & 0x20) == 0) {
            particle[5].z = *(float*)(breath + 0x80) * Math.RandF();
            particle[6].x = *(float*)(breath + 0x84) * Math.RandF();
            if (((flags & 1) != 0) && ((flags & 2) != 0)) {
                if (Math.RandF() > 0.5f) {
                    particle[5].z *= -1.0f;
                }
                if (Math.RandF() > 0.5f) {
                    particle[6].x *= -1.0f;
                }
            } else if ((flags & 2) != 0) {
                particle[5].z *= -1.0f;
                particle[6].x *= -1.0f;
            }
        } else {
            particle[5].z = *(float*)(breath + 0x80) * Math.RandF();
            particle[6].x = particle[5].z;
            if (((flags & 1) != 0) && ((flags & 2) != 0)) {
                if (Math.RandF() > 0.5f) {
                    particle[5].z *= -1.0f;
                    particle[6].x *= -1.0f;
                }
            } else if ((flags & 2) != 0) {
                particle[5].z *= -1.0f;
                particle[6].x *= -1.0f;
            }
        }
    }

    if ((*(unsigned char*)(breath + 0xC1) & 4) != 0) {
        particle[4].y += particle[5].z;
        particle[4].z += particle[6].x;
    }
    if ((*(unsigned char*)(breath + 0xC1) & 8) != 0) {
        particle[5].x += particle[5].z;
        particle[5].y += particle[6].x;
    }

    particle[6].z = *(float*)(breath + 0x18);
    if (*(float*)(breath + 0xA8) != 0.0f) {
        spread = *(float*)(breath + 0xA8);
        particle[6].z += (spread + spread) * Math.RandF() - spread;
    }

    if (*(short*)(breath + 0x24) == 0) {
        *(short*)&particle[2].z = -1;
    } else {
        *(short*)&particle[2].z = *(short*)(breath + 0x24);
    }
    *(unsigned char*)&particle[7].x = 0;

    PSMTXCopy(*(Mtx*)vYmBreath, *(Mtx*)particleWmat);
    if (particleColor != NULL) {
        particleColor->m_colorFrameDeltas[0] = *(float*)(breath + 0x2C);
        particleColor->m_colorFrameDeltas[1] = *(float*)(breath + 0x30);
        particleColor->m_colorFrameDeltas[2] = *(float*)(breath + 0x34);
        particleColor->m_colorFrameDeltas[3] = *(float*)(breath + 0x38);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void get_rand()
{
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void SetParticleMatrix(_pppPObject*, VYmBreath*, _PARTICLE_DATA*, Mtx*)
{
	// TODO
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void IsDeadGroupBreath(PYmBreath* pYmBreath, VYmBreath* vBreathModel, short groupIndex)
{
    int i;
    int groupTable = *(int*)((unsigned char*)vBreathModel + 0x3C) + (int)groupIndex * 0x5C;
    bool isDead = true;
    float zero = 0.0f;
    int* groupData = (int*)groupTable;

    for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); i++) {
        if ((*(signed char*)(groupData[1] + i) != -1) || (*(signed char*)(groupData[2] + i) != 1)) {
            isDead = false;
            break;
        }
    }

    if (isDead) {
        for (i = 0; i < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); i++) {
            *(unsigned char*)(groupData[2] + i) = 0xFF;
            groupData[3] = (int)zero;
            groupData[4] = (int)zero;
            groupData[5] = (int)zero;
            groupData[6] = (int)zero;
            groupData[7] = (int)zero;
            groupData[8] = (int)zero;
            groupData[9] = (int)zero;
        }
        groupData[0] = 0;
    }
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void SearchIndex(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short& slotIndex, short& groupIndex, short particleIndex)
{
    int groupTable = *(int*)((unsigned char*)vYmBreath + 0x3C);
    short g;
    short s;

    for (g = 0; g < *(unsigned short*)((unsigned char*)pYmBreath + 0x14); g++) {
        for (s = 0; s < *(unsigned short*)((unsigned char*)pYmBreath + 0x12); s++) {
            if ((int)particleIndex == (int)*(signed char*)(*(int*)(groupTable + 4) + s)) {
                slotIndex = s;
                groupIndex = g;
                return;
            }
        }
        groupTable += 0x5C;
    }

    slotIndex = -1;
    groupIndex = -1;
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void IsExistGroupParticle(PYmBreath* pYmBreath, VYmBreath* vYmBreath, short particleIndex)
{
    short slotIndex;
    short groupIndex;
    int* groupArray;

    SearchIndex(pYmBreath, vYmBreath, slotIndex, groupIndex, particleIndex);
    if (groupIndex != -1) {
        groupArray = *(int**)((unsigned char*)vYmBreath + 0x3C);
        *(unsigned char*)(groupArray[groupIndex * 0x17 + 1] + slotIndex) = 0xFF;
    }
}
#endif
