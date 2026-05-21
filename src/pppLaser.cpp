#include "ffcc/pppLaser.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
extern "C" {
extern const f32 kPppLaserZero;
extern int gPppCalcDisabled;
}
#include "ffcc/util.h"

#include <string.h>

extern const f32 FLOAT_80333448;
extern const f32 FLOAT_8033344c;
extern const f32 FLOAT_80333450;
extern const f32 FLOAT_80333454;
extern const f32 FLOAT_80333458;
extern const f32 FLOAT_8033345c;
extern const f32 FLOAT_8033342c;
extern const f32 FLOAT_80333430;

void pppInitBlendMode(void);
void pppSetBlendMode(unsigned char);

extern "C" {
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
int GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(CGame*, PPPIFPARAM*, int*, int*);
void GetTargetCursor__5CGameFiR3VecR3Vec(CGame*, int, Vec*, Vec*);
void* GetPartyObj__5CGameFi(CGame*, int);
void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void ParticleFrameCallback__5CGameFiiiiiP3Vec(CGame*, int, int, int, int, int, Vec*);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);

void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
    int, int, int, int, int, int);
void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(
    int, int, int, int, int, int);
}

extern "C" const char s_pppLaser_cpp_801E3048[] = "pppLaser.cpp";

struct CMapCylinderRaw {
    Vec m_bottom;
    u8 m_pad0C[0x0C];
    Vec m_direction;
    f32 m_radius;
    Vec m_top;
    Vec m_direction2;
};

struct LaserWork {
    float m_length;
    float m_lengthStep;
    float m_graphValue0;
    float m_graphValue1;
    float m_halfWidth;
    float m_graphValue2;
    float m_graphValue3;
    Vec* m_points;
    Vec m_origin;
    u8 m_shapeReady;
    u8 m_hitFrame;
    u8 m_unused2E;
    u8 m_unused2F;
    s16 m_shapeArg0;
    s16 m_shapeArg1;
    s16 m_shapeArg2;
    s16 m_unused36;
    float m_shapeRotation;
    float m_maxLength;
    Vec m_targetPosition;
    u8 m_spawnEnabled;
};

struct LaserColorData {
    u8 m_pad0[8];
    pppCVECTOR m_color;
};

/*
 * --INFO--
 * PAL Address: 801766ec
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLaser(struct pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    f32 fVar1 = kPppLaserZero;
    LaserWork* work = (LaserWork*)((u8*)pppLaser + 0x80 + param_2->m_serializedDataOffsets[2]);
    int local_24;
    int local_28;
    int iVar2;
    Vec local_14;
    Vec local_20;

    work->m_length = kPppLaserZero;
    work->m_graphValue3 = fVar1;
    work->m_graphValue2 = fVar1;
    work->m_halfWidth = fVar1;
    work->m_graphValue1 = fVar1;
    work->m_graphValue0 = fVar1;
    work->m_lengthStep = fVar1;
    work->m_points = 0;
    work->m_origin.z = fVar1;
    work->m_origin.y = fVar1;
    work->m_origin.x = fVar1;

    work->m_shapeReady = 0;
    work->m_hitFrame = 0;
    work->m_unused2E = 0;
    work->m_shapeArg0 = 0;
    work->m_shapeArg2 = 0;
    work->m_shapeArg1 = 0;

    work->m_shapeRotation = Math.RandF(FLOAT_8033345c);
    work->m_spawnEnabled = 1;

    iVar2 = GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(
        &Game, (PPPIFPARAM*)((u8*)pppMngStPtr + 0x130), &local_24, &local_28);
    if (iVar2 != 0) {
        GetTargetCursor__5CGameFiR3VecR3Vec(&Game, local_28, &work->m_targetPosition, &local_20);

        iVar2 = (int)GetPartyObj__5CGameFi(&Game, local_28);
        local_14.x = *(f32*)(iVar2 + 0x15c);
        local_14.y = *(f32*)(iVar2 + 0x160);
        local_14.z = *(f32*)(iVar2 + 0x164);
        if (local_24 == 0x200) {
            work->m_maxLength = PSVECDistance(&work->m_targetPosition, &local_14);
        } else {
            work->m_maxLength = FLOAT_80333448;
        }
    } else {
        work->m_maxLength = FLOAT_80333448;
        *(u8*)((u8*)pppMngStPtr + 0xe8) = 1;
        pppStopSe__FP9_pppMngStP7PPPSEST(pppMngStPtr, (PPPSEST*)((u8*)pppMngStPtr + 0x11c));
    }
}

/*
 * --INFO--
 * PAL Address: 801766a8
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2Laser(struct pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    f32 fVar1 = kPppLaserZero;
    LaserWork* work = (LaserWork*)((u8*)pppLaser + 0x80 + param_2->m_serializedDataOffsets[2]);

    work->m_graphValue3 = kPppLaserZero;
    work->m_graphValue2 = fVar1;
    work->m_halfWidth = fVar1;
    work->m_graphValue1 = fVar1;
    work->m_graphValue0 = fVar1;
    work->m_lengthStep = fVar1;
    work->m_origin.z = fVar1;
    work->m_origin.y = fVar1;
    work->m_origin.x = fVar1;
    work->m_shapeReady = 0;
}

/*
 * --INFO--
 * PAL Address: 8017665c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructLaser(struct pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    LaserWork* work = (LaserWork*)((u8*)pppLaser + 0x80 + param_2->m_serializedDataOffsets[2]);
    void* alloc = work->m_points;
    if (alloc != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(alloc);
        work->m_points = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 801760a0
 * PAL Size: 1468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameLaser(struct pppLaser *pppLaser, struct pppLaserUnkB *param_2, _pppCtrlTable *param_3)
{
    pppLaserUnkB* step = param_2;
    LaserWork* work;
    Vec localB;
    Vec localA;
    Mtx tempMtx;
    Mtx charaMtx;
    CMapCylinderRaw cyl;

    int emptyHistory;
    int fillIndex;

    if (gPppCalcDisabled != 0) {
        return;
    }
    if (step->m_stepValue == 0xFFFF) {
        return;
    }

    work = (LaserWork*)((u8*)pppLaser + 0x80 + param_3->m_serializedDataOffsets[2]);
    emptyHistory = 0;
    if (FLOAT_80333448 == work->m_maxLength) {
        return;
    }

    if (work->m_points == 0) {
        work->m_points = (Vec*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)step->m_laser.m_pointCount * 0xc, pppEnvStPtr->m_stagePtr, const_cast<char*>(s_pppLaser_cpp_801E3048), 0x7d);
        memset(work->m_points, 0, (u32)step->m_laser.m_pointCount * 0xc);
        emptyHistory = 1;
    }

    CalcGraphValue((_pppPObject*)pppLaser, step->m_graphId, work->m_halfWidth, work->m_graphValue2, work->m_graphValue3,
        step->m_laser.m_halfWidthBase, step->m_laser.m_halfWidthVelocity, step->m_laser.m_halfWidthAccel);
    CalcGraphValue((_pppPObject*)pppLaser, step->m_graphId, work->m_lengthStep, work->m_graphValue0, work->m_graphValue1,
        step->m_laser.m_lengthStepBase, step->m_laser.m_lengthStepVelocity, step->m_laser.m_lengthStepAccel);

    pppCalcFrameShape(
        **(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4), work->m_shapeArg1,
        work->m_shapeArg2, work->m_shapeArg0, step->m_laser.m_shapeFrameStep);

    for (int i = 0; i < (int)(u32)(step->m_laser.m_historyFrameCount + 1); i++) {
        int max = (int)step->m_laser.m_pointCount - 2;

        for (int j = max; (int)i <= j; j--) {
            pppCopyVector(work->m_points[j + 1], work->m_points[j]);
        }

        localB.x = kPppLaserZero;
        localB.y = kPppLaserZero;
        localB.z = work->m_length;

        if (i == 0) {
            PSMTXConcat(pppMngStPtr->m_matrix.value, pppLaser->m_localMatrix.value, tempMtx);
            work->m_origin.x = tempMtx[0][3];
            work->m_origin.y = tempMtx[1][3];
            work->m_origin.z = tempMtx[2][3];
            PSMTXMultVec(tempMtx, &localB, work->m_points);
        } else {
            if (emptyHistory) {
                continue;
            }
            s32 frameCount = step->m_laser.m_historyFrameCount + 1;
            float t = FLOAT_80333448 / (float)frameCount;
            t *= (float)i;
            if (GetCharaNodeFrameMatrix(pppMngStPtr, t, charaMtx) == 0) {
                emptyHistory = 1;
                continue;
            } else {
                PSMTXConcat(charaMtx, pppLaser->m_localMatrix.value, charaMtx);
                PSMTXMultVec(charaMtx, &localB, &work->m_points[i]);
            }
        }

        pppSubVector(localA, work->m_points[i], work->m_origin);
        PSVECScale(&localA, &localA, FLOAT_8033344c);

        cyl.m_top.z = FLOAT_80333450;
        cyl.m_top.y = FLOAT_80333450;
        cyl.m_top.x = FLOAT_80333450;
        cyl.m_direction2.z = FLOAT_80333454;
        cyl.m_direction2.y = FLOAT_80333454;
        cyl.m_direction2.x = FLOAT_80333454;
        cyl.m_bottom = work->m_origin;
        cyl.m_direction = localA;
        cyl.m_radius = kPppLaserZero;

        int check = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &cyl, &localA, 0xffffffff);
        int hit = 0;
        if (check != 0) {
            hit = 1;
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &work->m_points[i]);
            work->m_length = PSVECDistance(&work->m_points[i], &work->m_origin);
        } else if (i == 0) {
            if (work->m_spawnEnabled != 0) {
                if (work->m_maxLength - FLOAT_80333458 < work->m_length) {
                    _pppMngSt* mngSt = pppMngStPtr;
                    s32 partIndex = ((s32)((u8*)mngSt - (reinterpret_cast<u8*>(&PartMng) + 0x2A18))) / 0x158;
                    work->m_length = work->m_maxLength - FLOAT_80333458;
                    ParticleFrameCallback__5CGameFiiiiiP3Vec(
                        &Game, partIndex, (int)mngSt->m_kind, (int)mngSt->m_nodeIndex, 3,
                        pppLaser->m_graphId / 0x1000, work->m_points);
                    work->m_spawnEnabled = 0;
                }
            }
            if (work->m_spawnEnabled != 0) {
                work->m_length += work->m_lengthStep;
            }
        }

        if (i == 0) {
            localB.x = kPppLaserZero;
            localB.y = kPppLaserZero;
            localB.z = work->m_length;
            PSMTXMultVec(tempMtx, &localB, &work->m_points[i]);
        }

        if (step->m_laser.m_disableHitCylinder == 0) {
            pppHitCylinderSendSystem(
                pppMngStPtr, &work->m_origin, &localA,
                pppMngStPtr->m_previousPosition.z * step->m_laser.m_hitScale,
                step->m_laser.m_hitRadius);
        }

        if (step->m_laser.m_disableHitObject == 0) {
            int createHitObject = 0;
            if (step->m_arg3 != -1) {
                createHitObject = 1;
            }
            if (!hit) {
                createHitObject = 0;
            }

            if (work->m_hitFrame < step->m_laser.m_hitInterval) {
                work->m_hitFrame++;
                createHitObject = 0;
            } else {
                work->m_hitFrame = 0;
            }

            if (createHitObject != 0) {
                _pppPDataVal* dataVal = pppMngStPtr->m_pppPDataVals + step->m_arg3;
                _pppPObject* created;
                if (dataVal == 0) {
                    created = 0;
                } else {
                    created = pppCreatePObject(pppMngStPtr, dataVal);
                    *(_pppPObject**)((u8*)created + 4) = (_pppPObject*)pppLaser;
                }

                Vec* createdPos = (Vec*)((u8*)created + step->m_laser.m_spawnPositionOffset + 0x80);
                createdPos->x = work->m_points[i].x;
                createdPos->y = work->m_points[i].y + step->m_laser.m_spawnYOffset;
                createdPos->z = work->m_points[i].z;
            }
        }
    }

    if (emptyHistory) {
        for (fillIndex = 0; fillIndex < (int)(u32)step->m_laser.m_pointCount; fillIndex++) {
            pppCopyVector(work->m_points[fillIndex], work->m_points[0]);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 801754e0
 * PAL Size: 3008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRenderLaser(struct pppLaser *pppLaser, struct pppLaserUnkB *param_2, _pppCtrlTable *param_3)
{
    pppLaserUnkB* step = param_2;
    int* serializedDataOffsets = param_3->m_serializedDataOffsets;
    LaserWork* work = (LaserWork*)((u8*)pppLaser + 0x80 + serializedDataOffsets[2]);
    int colorOffset = serializedDataOffsets[1];
    LaserColorData* colorData = (LaserColorData*)((u8*)pppLaser + 0x80 + colorOffset);
    s32 dataValIndex = step->m_dataValIndex;
    u32 count;
    s32 i;
    s32 alphaStep;
    char alphaMax;
    float negHalfWidth;
    float length;
    float halfWidth;
    float u0;
    float u1;
    float uvStep;
    pppFMATRIX mtxOut;
    pppFMATRIX unitMtx;
    Mtx shapeMtx;
    Mtx rotateMtx;
    Mtx debugMtx ATTRIBUTE_ALIGN(8);
    Mtx pointMtx;
    Mtx sphereMtx;
    pppFMATRIX managerMtx;
    pppFMATRIX localMtx;
    pppFMATRIX cameraMtx;
    pppFMATRIX modelMtx;
    Vec shapePos;
    Vec spherePos;
    Vec debugSource;
    _GXColor color;
    int tex;

    if (dataValIndex == 0xFFFF) {
        return;
    }

    tex = GetTextureFromRSD__FiP9_pppEnvSt(dataValIndex, pppEnvStPtr);
    pppSetBlendMode(step->m_laser.m_blendMode);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        &colorData->m_color, &pppLaser->m_localMatrix, kPppLaserZero, step->m_laser.m_drawEnvColor1,
        step->m_laser.m_drawEnvColor0, step->m_laser.m_blendMode, 0, 1, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetCullMode(GX_CULL_NONE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
    color = *(_GXColor*)&colorData->m_color;
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
        0, 0xF, 8, 0xA, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
        0, 7, 7, 7, 5);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    gUtil.SetVtxFmt_POS_CLR_TEX();
    GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);

    halfWidth = work->m_halfWidth;
    length = work->m_length;
    negHalfWidth = -halfWidth;

    pppUnitMatrix(unitMtx);
    localMtx = pppLaser->m_localMatrix;
    managerMtx = pppMngStPtr->m_matrix;
    pppMulMatrix(mtxOut, managerMtx, localMtx);
    modelMtx = mtxOut;
    cameraMtx = *(pppFMATRIX*)&ppvCameraMatrix;
    pppMulMatrix(mtxOut, cameraMtx, modelMtx);
    GXLoadPosMtxImm(mtxOut.value, 0);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(negHalfWidth, kPppLaserZero, kPppLaserZero);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(kPppLaserZero, kPppLaserZero);
    GXPosition3f32(negHalfWidth, kPppLaserZero, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(kPppLaserZero, work->m_length);
    GXPosition3f32(halfWidth, kPppLaserZero, kPppLaserZero);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(FLOAT_8033342c, kPppLaserZero);
    GXPosition3f32(halfWidth, kPppLaserZero, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(FLOAT_8033342c, work->m_length);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(kPppLaserZero, negHalfWidth, kPppLaserZero);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(kPppLaserZero, kPppLaserZero);
    GXPosition3f32(kPppLaserZero, negHalfWidth, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(kPppLaserZero, work->m_length);
    GXPosition3f32(kPppLaserZero, halfWidth, kPppLaserZero);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(FLOAT_8033342c, kPppLaserZero);
    GXPosition3f32(kPppLaserZero, halfWidth, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(FLOAT_8033342c, work->m_length);

    if (step->m_stepValue != 0xFFFF) {
        long** shapeTable = *(long***)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4);
        PSMTXIdentity(shapeMtx);
        shapeMtx[0][0] = step->m_laser.m_shapeScale * pppMngStPtr->m_scale.x;
        shapeMtx[1][1] = step->m_laser.m_shapeScale * pppMngStPtr->m_scale.y;
        shapeMtx[2][2] = shapeMtx[0][0];
        if (kPppLaserZero != work->m_shapeRotation) {
            PSMTXRotRad(rotateMtx, 'z', work->m_shapeRotation);
            PSMTXConcat(shapeMtx, rotateMtx, shapeMtx);
        }
        PSMTXMultVec(ppvCameraMatrix, work->m_points, &shapePos);
        shapeMtx[0][3] = shapePos.x;
        shapeMtx[1][3] = shapePos.y;
        shapeMtx[2][3] = shapePos.z;
        GXLoadPosMtxImm(shapeMtx, GX_PNMTX0);
        pppDrawShp(*shapeTable, work->m_shapeArg2, pppEnvStPtr->m_materialSetPtr, step->m_laser.m_blendMode);

        count = step->m_laser.m_pointCount;
        uvStep = FLOAT_8033342c / (float)count;
        if (step->m_initWOrk == 0xFFFF) {
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
            _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        } else {
            tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_initWOrk, pppEnvStPtr);
            _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
            GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);
        }

        GXLoadPosMtxImm(ppvCameraMatrix, GX_PNMTX0);
        alphaMax = step->m_laser.m_trailAlpha;
        alphaStep = (u8)((u8)alphaMax / (s32)step->m_laser.m_pointCount);
        color.r = step->m_laser.m_trailColorR;
        color.g = step->m_laser.m_trailColorG;
        color.b = step->m_laser.m_trailColorB;
        color.a = alphaMax;

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((step->m_laser.m_pointCount - 1) * 3));
        int alpha = 0;
        u8 trailColorR = color.r;
        u8 trailColorG = color.g;
        u8 trailColorB = color.b;
        for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
            u0 = uvStep * (float)j;
            u1 = uvStep * (float)(j + 1);
            _GXColor trailStartColor;
            trailStartColor.r = trailColorR;
            trailStartColor.g = trailColorG;
            trailStartColor.b = trailColorB;
            trailStartColor.a = (u8)alphaMax - alpha;
            alpha += alphaStep;

            GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
            GXColor1u32(*(u32*)&trailStartColor);
            GXTexCoord2f32(u0, FLOAT_8033342c);

            GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
            GXColor1u32(*(u32*)&trailStartColor);
            GXTexCoord2f32(u0, kPppLaserZero);

            _GXColor trailEndColor;
            trailEndColor.r = trailColorR;
            trailEndColor.g = trailColorG;
            trailEndColor.b = trailColorB;
            trailEndColor.a = (u8)alphaMax - alphaStep * (j + 1);
            GXPosition3f32(work->m_points[j + 1].x, work->m_points[j + 1].y, work->m_points[j + 1].z);
            GXColor1u32(*(u32*)&trailEndColor);
            GXTexCoord2f32(u1, kPppLaserZero);
        }

        u8* cflat = CFlat;
        if ((*reinterpret_cast<u32*>(cflat + 0x129c) & 0x200000) != 0) {
            gUtil.SetVtxFmt_POS_CLR();
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
            _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
            GXSetNumTexGens(0);
            pppSetBlendMode(1);

            color.r = 0x80;
            color.g = 0xFF;
            color.b = 0x80;
            color.a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, color);
            GXSetPointSize(0x28, GX_TO_ZERO);
            GXBegin(GX_POINTS, GX_VTXFMT7, (u16)(step->m_laser.m_pointCount - 1));
            for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
                GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
                GXColor1u32(*(u32*)&color);
            }

            color.r = 0x80;
            color.g = 0x80;
            color.b = 0xFF;
            color.a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, color);
            GXSetLineWidth(0x14, GX_TO_ZERO);
            GXBegin(GX_LINES, GX_VTXFMT7, (u16)((step->m_laser.m_pointCount - 1) * 4));
            for (int j = 0; j < (int)(step->m_laser.m_pointCount - 1); j++) {
                GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
                GXColor1u32(*(u32*)&color);
                GXPosition3f32(work->m_points[j + 1].x, work->m_points[j + 1].y, work->m_points[j + 1].z);
                GXColor1u32(*(u32*)&color);
                GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
                GXColor1u32(*(u32*)&color);
                GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
                GXColor1u32(*(u32*)&color);
            }

            GXSetLineWidth(8, GX_TO_ZERO);
            GXSetPointSize(8, GX_TO_ZERO);
            GXSetZMode(1, GX_LEQUAL, 0);

            if ((*reinterpret_cast<u32*>(cflat + 0x129c) & 0x200000) != 0) {
                float radius = pppMngStPtr->m_previousPosition.z * step->m_laser.m_hitScale;
                float distance = PSVECDistance(work->m_points, &work->m_origin);
                debugSource.x = kPppLaserZero;
                debugSource.y = kPppLaserZero;
                debugSource.z = FLOAT_8033342c;
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0xFF;
                color.a = 0xFF;
                PSMTXIdentity(debugMtx);
                debugMtx[0][0] = radius;
                debugMtx[1][1] = radius;
                debugMtx[2][2] = distance;
                PSMTXConcat(pppLaser->m_localMatrix.value, debugMtx, debugMtx);
                PSMTXConcat(pppMngStPtr->m_matrix.value, debugMtx, debugMtx);
                PSMTXConcat(ppvCameraMatrix, debugMtx, debugMtx);
                PSMTXMultVec(debugMtx, &debugSource, &spherePos);
                debugMtx[0][3] = spherePos.x;
                debugMtx[1][3] = spherePos.y;
                debugMtx[2][3] = spherePos.z;
                Graphic.DrawSphere(debugMtx, color);
            }

            GXLoadPosMtxImm(pppLaser->m_drawMatrix.value, GX_PNMTX0);
            color.r = 0xFF;
            color.g = 0xFF;
            color.b = 0xFF;
            color.a = 0xFF;
            for (i = 0; i < (int)(u32)step->m_laser.m_pointCount; i++) {
                if ((work->m_points[i].x == kPppLaserZero) && (work->m_points[i].y == kPppLaserZero) && (work->m_points[i].z == kPppLaserZero)) {
                    continue;
                }
                PSMTXScale(pointMtx, FLOAT_80333430, FLOAT_80333430, FLOAT_80333430);
                pointMtx[0][3] = work->m_points[i].x;
                pointMtx[1][3] = work->m_points[i].y;
                pointMtx[2][3] = work->m_points[i].z;
                PSMTXConcat(ppvCameraMatrix, pointMtx, sphereMtx);
                Graphic.DrawSphere(sphereMtx, color);
            }

            pointMtx[0][3] = work->m_origin.x;
            pointMtx[1][3] = work->m_origin.y;
            pointMtx[2][3] = work->m_origin.z;
            PSMTXConcat(ppvCameraMatrix, pointMtx, sphereMtx);
            Graphic.DrawSphere(sphereMtx, color);
            pppInitBlendMode();
        }
    }
}
