#include "ffcc/ptrarray.h"
#include "global.h"
#include "ffcc/pppLaser.h"
#include "ffcc/pppLaserCommon.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/game.h"
#include "ffcc/gobject.h"
#include "ffcc/partyobj.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"

#include <string.h>

static const f32 kPppLaserZero = 0.0f;
static const f32 kPppLaserOne = 1.0f;
static const f32 kPppLaserDebugPointScale = 2.0f;
static const f32 kPppLaserMaxLengthDisabled = -1.0f;
static const f32 kPppLaserAxisScale = 1.2f;
static const f32 kPppLaserBoundsMax = 10000000000.0f;
static const f32 kPppLaserBoundsMin = -10000000000.0f;
static const f32 kPppLaserMaxLengthMargin = 15.5f;
static const f32 kPppLaserTau = 6.2831855f;

static const char s_pppLaser_cpp[] = "pppLaser.cpp";

typedef pppLaserWork LaserWork;
typedef pppLaserColorBlock LaserColorData;

STATIC_ASSERT(offsetof(pppLaserDataOffsets, m_colorBlockOffset) == 0x4);
STATIC_ASSERT(offsetof(pppLaserDataOffsets, m_workOffset) == 0x8);
STATIC_ASSERT(offsetof(CMapCylinder, m_bottom) == 0x0);
STATIC_ASSERT(offsetof(CMapCylinder, m_axis) == 0x18);
STATIC_ASSERT(offsetof(CMapCylinder, m_radius) == 0x24);
STATIC_ASSERT(offsetof(CMapCylinder, m_bound) == 0x28);

static inline f32 LaserConst(const f32& value)
{
    return *reinterpret_cast<const f32*>(&value);
}

static inline pppLaserDataOffsets* GetLaserDataOffsets(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<pppLaserDataOffsets*>(ctrlTable->m_serializedDataOffsets);
}

static inline LaserWork* GetLaserWork(pppLaser* laser, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<LaserWork*>(laser->m_workArea + GetLaserDataOffsets(ctrlTable)->m_workOffset);
}

static inline LaserColorData* GetLaserColorData(pppLaser* laser, _pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<LaserColorData*>(laser->m_workArea + GetLaserDataOffsets(ctrlTable)->m_colorBlockOffset);
}

STATIC_ASSERT(offsetof(pppLaser, m_workArea) == 0x80);

/*
 * --INFO--
 * PAL Address: 801766ec
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructLaser(pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    f32 fVar1 = LaserConst(kPppLaserZero);
    LaserWork* work = GetLaserWork(pppLaser, param_2);
    int local_24;
    int local_28;
    int iVar2;
    Vec local_14;
    Vec local_20;

    work->m_length = LaserConst(kPppLaserZero);
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

    work->m_shapeRotation = Math.RandF(LaserConst(kPppLaserTau));
    work->m_spawnEnabled = 1;

    iVar2 = Game.GetParticleSpecialInfo(ppvMng->m_hitParams, local_24, local_28);
    if (iVar2 != 0) {
        Game.GetTargetCursor(local_28, work->m_targetPosition, local_20);

        CGPartyObj* partyObj = Game.GetPartyObj(local_28);
        local_14 = partyObj->m_worldPosition;
        if (local_24 == 0x200) {
            work->m_maxLength = PSVECDistance(&work->m_targetPosition, &local_14);
        } else {
            work->m_maxLength = LaserConst(kPppLaserMaxLengthDisabled);
        }
    } else {
        work->m_maxLength = LaserConst(kPppLaserMaxLengthDisabled);
        ppvMng->m_hitBgFlag = 1;
        pppStopSe(ppvMng, &ppvMng->m_soundEffectData);
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
void pppConstruct2Laser(pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    f32 fVar1 = LaserConst(kPppLaserZero);
    LaserWork* work = GetLaserWork(pppLaser, param_2);

    work->m_graphValue3 = LaserConst(kPppLaserZero);
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
void pppDestructLaser(pppLaser *pppLaser, _pppCtrlTable *param_2)
{
    LaserWork* work = GetLaserWork(pppLaser, param_2);
    void* alloc = work->m_points;
    if (alloc != 0) {
        pppHeapUseRate(static_cast<CMemory::CStage*>(alloc));
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
extern "C" void pppFrameLaser(pppLaser *pppLaser, pppLaserStep *param_2, _pppCtrlTable *param_3)
{
    pppLaserStep* step = param_2;
    LaserWork* work;
    Vec localB;
    Vec localA;
    Mtx tempMtx;
    Mtx charaMtx;

    int emptyHistory;
    int fillIndex;

    if (ppvUserStopPartF != 0) {
        return;
    }
    if (step->m_stepValue == 0xFFFF) {
        return;
    }

    work = GetLaserWork(pppLaser, param_3);
    emptyHistory = 0;
    f32 maxLengthDisabled = LaserConst(kPppLaserMaxLengthDisabled);
    if (maxLengthDisabled == work->m_maxLength) {
        return;
    }

    if (work->m_points == 0) {
        work->m_points = (Vec*)pppMemAlloc(
            (u32)step->m_laser.m_pointCount * 0xc, ppvEnv->m_stagePtr, const_cast<char*>(s_pppLaser_cpp), 0x7d);
        memset(work->m_points, 0, (u32)step->m_laser.m_pointCount * 0xc);
        emptyHistory = 1;
    }

    CalcGraphValue((_pppPObject*)pppLaser, step->m_graphId, work->m_halfWidth, work->m_graphValue2, work->m_graphValue3,
        step->m_laser.m_halfWidthBase, step->m_laser.m_halfWidthVelocity, step->m_laser.m_halfWidthAccel);
    CalcGraphValue((_pppPObject*)pppLaser, step->m_graphId, work->m_lengthStep, work->m_graphValue0, work->m_graphValue1,
        step->m_laser.m_lengthStepBase, step->m_laser.m_lengthStepVelocity, step->m_laser.m_lengthStepAccel);

    pppCalcFrameShape(
        static_cast<long*>(ppvEnv->m_resourceTables.m_shapeTablePtr[step->m_stepValue]->m_animData), work->m_shapeArg1,
        work->m_shapeArg2, work->m_shapeArg0, step->m_laser.m_shapeFrameStep);

    for (int i = 0; i < (int)(u32)(step->m_laser.m_historyFrameCount + 1); i++) {
        int max = (int)step->m_laser.m_pointCount - 2;

        for (int j = max; (int)i <= j; j--) {
            pppCopyVector(work->m_points[j + 1], work->m_points[j]);
        }

        localB.x = LaserConst(kPppLaserZero);
        localB.y = LaserConst(kPppLaserZero);
        localB.z = work->m_length;

        if (i == 0) {
            PSMTXConcat(ppvMng->m_matrix.value, pppLaser->m_localMatrix.value, tempMtx);
            work->m_origin.x = tempMtx[0][3];
            work->m_origin.y = tempMtx[1][3];
            work->m_origin.z = tempMtx[2][3];
            PSMTXMultVec(tempMtx, &localB, work->m_points);
        } else {
            if (emptyHistory) {
                continue;
            }
            s32 frameCount = step->m_laser.m_historyFrameCount + 1;
            float t = LaserConst(kPppLaserMaxLengthDisabled) / (float)frameCount;
            t *= (float)i;
            if (GetCharaNodeFrameMatrix(ppvMng, t, charaMtx) == 0) {
                emptyHistory = 1;
                continue;
            } else {
                PSMTXConcat(charaMtx, pppLaser->m_localMatrix.value, charaMtx);
                PSMTXMultVec(charaMtx, &localB, &work->m_points[i]);
            }
        }

        pppSubVector(localA, work->m_points[i], work->m_origin);
        PSVECScale(&localA, &localA, LaserConst(kPppLaserAxisScale));

        f32 boundsMax = LaserConst(kPppLaserBoundsMax);
        f32 boundsMin = LaserConst(kPppLaserBoundsMin);
        CMapCylinder cyl(boundsMax, boundsMin);
        cyl.m_bottom = work->m_origin;
        cyl.m_axis = localA;
        cyl.m_radius = LaserConst(kPppLaserZero);

        int check = MapMng.CheckHitCylinderNear(&cyl, &localA, 0xffffffff);
        int hit = 0;
        if (check != 0) {
            hit = 1;
            MapMng.m_hitMapObj->CalcHitPosition(&work->m_points[i]);
            work->m_length = PSVECDistance(&work->m_points[i], &work->m_origin);
        } else if (i == 0) {
            if (work->m_spawnEnabled != 0) {
                if (work->m_maxLength - LaserConst(kPppLaserMaxLengthMargin) < work->m_length) {
                    _pppMngSt* mngSt = ppvMng;
                    s32 partIndex = static_cast<s32>(mngSt - PartMng.m_pppMng);
                    work->m_length = work->m_maxLength - LaserConst(kPppLaserMaxLengthMargin);
                    Game.ParticleFrameCallback(
                        partIndex, (int)mngSt->m_kind, (int)mngSt->m_nodeIndex, 3, pppLaser->m_graphId / 0x1000,
                        work->m_points);
                    work->m_spawnEnabled = 0;
                }
            }
            if (work->m_spawnEnabled != 0) {
                work->m_length += work->m_lengthStep;
            }
        }

        if (i == 0) {
            localB.x = LaserConst(kPppLaserZero);
            localB.y = LaserConst(kPppLaserZero);
            localB.z = work->m_length;
            PSMTXMultVec(tempMtx, &localB, &work->m_points[i]);
        }

        if (step->m_laser.m_disableHitCylinder == 0) {
            pppHitCylinderSendSystem(
                ppvMng, &work->m_origin, &localA,
                ppvMng->m_hitScale * step->m_laser.m_hitScale,
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
                _pppPDataVal* dataVal = ppvMng->m_pppPDataVals + step->m_arg3;
                _pppPObject* created;
                if (dataVal == 0) {
                    created = 0;
                } else {
                    created = pppCreatePObject(ppvMng, dataVal);
                    created->m_link.m_previous = &pppLaser->m_link;
                }

                Vec* createdPos = (Vec*)(created->m_workArea + step->m_laser.m_spawnPositionOffset);
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
extern "C" void pppRenderLaser(pppLaser *pppLaser, pppLaserStep *param_2, _pppCtrlTable *param_3)
{
    pppLaserStep* step = param_2;
    LaserWork* work = GetLaserWork(pppLaser, param_3);
    LaserColorData* colorData = GetLaserColorData(pppLaser, param_3);
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
    Vec shapePos;
    Vec spherePos;
    Vec debugSource;
    _GXColor color;
    CTexture* texture;

    if (dataValIndex == 0xFFFF) {
        return;
    }

    texture = GetTextureFromRSD(dataValIndex, ppvEnv);
    pppSetBlendMode(step->m_laser.m_blendMode);
    _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    pppSetDrawEnv(
        &colorData->m_color, &pppLaser->m_localMatrix, LaserConst(kPppLaserZero), step->m_laser.m_drawEnvColor1,
        step->m_laser.m_drawEnvColor0, step->m_laser.m_blendMode, 0, 1, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetCullMode(GX_CULL_NONE);
    _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    color = *(_GXColor*)&colorData->m_color;
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    _GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    _GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    gUtil.SetVtxFmt_POS_CLR_TEX();
    GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);

    halfWidth = work->m_halfWidth;
    length = work->m_length;
    negHalfWidth = -halfWidth;

    pppUnitMatrix(unitMtx);
    pppMulMatrix(mtxOut, ppvMng->m_matrix, pppLaser->m_localMatrix);
    pppMulMatrix(mtxOut, *(pppFMATRIX*)&ppvCameraMatrix, mtxOut);
    GXLoadPosMtxImm(mtxOut.value, 0);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(negHalfWidth, LaserConst(kPppLaserZero), LaserConst(kPppLaserZero));
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserZero), LaserConst(kPppLaserZero));
    GXPosition3f32(negHalfWidth, LaserConst(kPppLaserZero), length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserZero), work->m_length);
    GXPosition3f32(halfWidth, LaserConst(kPppLaserZero), LaserConst(kPppLaserZero));
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserOne), LaserConst(kPppLaserZero));
    GXPosition3f32(halfWidth, LaserConst(kPppLaserZero), length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserOne), work->m_length);

    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT7, 4);
    GXPosition3f32(LaserConst(kPppLaserZero), negHalfWidth, LaserConst(kPppLaserZero));
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserZero), LaserConst(kPppLaserZero));
    GXPosition3f32(LaserConst(kPppLaserZero), negHalfWidth, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserZero), work->m_length);
    GXPosition3f32(LaserConst(kPppLaserZero), halfWidth, LaserConst(kPppLaserZero));
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserOne), LaserConst(kPppLaserZero));
    GXPosition3f32(LaserConst(kPppLaserZero), halfWidth, length);
    GXColor1u32(*(u32*)&color);
    GXTexCoord2f32(LaserConst(kPppLaserOne), work->m_length);

    if (step->m_stepValue != 0xFFFF) {
        pppShapeSt* shape = ppvEnv->m_resourceTables.m_shapeTablePtr[step->m_stepValue];
        PSMTXIdentity(shapeMtx);
        shapeMtx[0][0] = step->m_laser.m_shapeScale * ppvMng->m_scale.x;
        shapeMtx[1][1] = step->m_laser.m_shapeScale * ppvMng->m_scale.y;
        shapeMtx[2][2] = shapeMtx[0][0];
        if (LaserConst(kPppLaserZero) != work->m_shapeRotation) {
            PSMTXRotRad(rotateMtx, 'z', work->m_shapeRotation);
            PSMTXConcat(shapeMtx, rotateMtx, shapeMtx);
        }
        PSMTXMultVec(ppvCameraMatrix, work->m_points, &shapePos);
        shapeMtx[0][3] = shapePos.x;
        shapeMtx[1][3] = shapePos.y;
        shapeMtx[2][3] = shapePos.z;
        GXLoadPosMtxImm(shapeMtx, GX_PNMTX0);
        pppDrawShp(static_cast<long*>(shape->m_animData), work->m_shapeArg2, ppvEnv->m_materialSetPtr,
                   step->m_laser.m_blendMode);

        count = step->m_laser.m_pointCount;
        uvStep = LaserConst(kPppLaserOne) / (float)count;
        if (step->m_initWOrk == 0xFFFF) {
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        } else {
            texture = GetTextureFromRSD(step->m_initWOrk, ppvEnv);
            _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            GXLoadTexObj(&texture->m_texObj, GX_TEXMAP0);
        }

        GXLoadPosMtxImm(ppvCameraMatrix, GX_PNMTX0);
        alphaMax = step->m_laser.m_trailAlpha;
        alphaStep = (u8)((u8)alphaMax / (s32)step->m_laser.m_pointCount);
        color.r = step->m_laser.m_trailColorR;
        color.g = step->m_laser.m_trailColorG;
        color.b = step->m_laser.m_trailColorB;
        color.a = alphaMax;

        GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((step->m_laser.m_pointCount - 1) * 3));
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
            trailStartColor.a = (u8)alphaMax - alphaStep * j;

            GXPosition3f32(work->m_origin.x, work->m_origin.y, work->m_origin.z);
            GXColor1u32(*(u32*)&trailStartColor);
            GXTexCoord2f32(u0, LaserConst(kPppLaserOne));

            GXPosition3f32(work->m_points[j].x, work->m_points[j].y, work->m_points[j].z);
            GXColor1u32(*(u32*)&trailStartColor);
            GXTexCoord2f32(u0, LaserConst(kPppLaserZero));

            _GXColor trailEndColor;
            trailEndColor.r = trailColorR;
            trailEndColor.g = trailColorG;
            trailEndColor.b = trailColorB;
            trailEndColor.a = (u8)alphaMax - alphaStep * (j + 1);
            GXPosition3f32(work->m_points[j + 1].x, work->m_points[j + 1].y, work->m_points[j + 1].z);
            GXColor1u32(*(u32*)&trailEndColor);
            GXTexCoord2f32(u1, LaserConst(kPppLaserZero));
        }

        if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
            gUtil.SetVtxFmt_POS_CLR();
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
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

            if ((CFlatRuntimeDebugFlags() & CFlatRuntimeDebugFlag_ParticleHitSpheres) != 0) {
                float radius = ppvMng->m_hitScale * step->m_laser.m_hitScale;
                float distance = PSVECDistance(work->m_points, &work->m_origin);
                debugSource.x = LaserConst(kPppLaserZero);
                debugSource.y = LaserConst(kPppLaserZero);
                debugSource.z = LaserConst(kPppLaserOne);
                color.r = 0xFF;
                color.g = 0xFF;
                color.b = 0xFF;
                color.a = 0xFF;
                PSMTXIdentity(debugMtx);
                debugMtx[0][0] = radius;
                debugMtx[1][1] = radius;
                debugMtx[2][2] = distance;
                PSMTXConcat(pppLaser->m_localMatrix.value, debugMtx, debugMtx);
                PSMTXConcat(ppvMng->m_matrix.value, debugMtx, debugMtx);
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
                if ((work->m_points[i].x == LaserConst(kPppLaserZero)) && (work->m_points[i].y == LaserConst(kPppLaserZero)) && (work->m_points[i].z == LaserConst(kPppLaserZero))) {
                    continue;
                }
                PSMTXScale(
                    pointMtx, LaserConst(kPppLaserDebugPointScale), LaserConst(kPppLaserDebugPointScale),
                    LaserConst(kPppLaserDebugPointScale));
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
