#include "ffcc/pppLaser.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/graphic.h"

#include <string.h>

extern struct _pppMngSt* pppMngStPtr;
extern CMath math;
extern f32 FLOAT_80333428;
extern f32 FLOAT_80333448;
extern f32 FLOAT_8033344c;
extern f32 FLOAT_80333450;
extern f32 FLOAT_80333454;
extern f32 FLOAT_80333458;
extern f32 FLOAT_8033345c;
extern f32 FLOAT_8033342c;
extern f32 FLOAT_80333430;
extern f64 DOUBLE_80333440;
extern f64 DOUBLE_80333438;
extern s32 DAT_8032ed70;
extern void* DAT_8032ec70;
extern u32 CFlatFlags;
extern CMapMng MapMng;
extern Mtx ppvCameraMatrix0;
extern CGraphic Graphic;

extern "C" {
void pppHeapUseRate__FPQ27CMemory6CStage(void*);
f32 RandF__5CMathFf(f32, CMath*);
int GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(CGame*, PPPIFPARAM*, int*, int*);
void GetTargetCursor__5CGameFiR3VecR3Vec(CGame*, int, Vec*, Vec*);
void* GetPartyObj__5CGameFi(CGame*, int);
void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
void pppCalcFrameShape__FPlRsRsRss(long*, short&, short&, short&, short);
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void ParticleFrameCallback__5CGameFiiiiiP3Vec(CGame*, int, int, int, int, int);
int GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f(float, _pppMngSt*, Mtx);
int pppCreatePObject__FP9_pppMngStP12_pppPDataVal(_pppMngSt*, void*);
void pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(_pppMngSt*, Vec*, Vec*, float, float);
int GetTextureFromRSD__FiP9_pppEnvSt(int, _pppEnvSt*);
void pppSetBlendMode__FUc(u8);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void SetVtxFmt_POS_CLR__5CUtilFv(void*);
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
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX*, pppFMATRIX*, pppFMATRIX*);
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX*);
void pppDrawShp__FPlsP12CMaterialSetUc(long*, short, CMaterialSet*, u8);
void pppInitBlendMode__Fv(void);
}

static char s_pppLaser_cpp[] = "pppLaser.cpp";

struct LaserStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_stepValue;
    s32 m_arg3;
    u8* m_payload;
};

struct CMapCylinderRaw {
    Vec m_bottom;
    Vec m_direction;
    float m_radius;
    float m_height;
    Vec m_top;
    Vec m_direction2;
    float m_radius2;
    float m_height2;
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
void pppConstructLaser(struct pppLaser *pppLaser, struct UnkC *param_2)
{
    f32* pfVar3 = (f32*)((u8*)pppLaser + 0x80 + param_2->offsets->m_serializedDataOffsets[2]);
    int local_28;
    int local_24;
    Vec local_14;
    Vec local_20;

    *pfVar3 = FLOAT_80333428;
    pfVar3[6] = FLOAT_80333428;
    pfVar3[5] = FLOAT_80333428;
    pfVar3[4] = FLOAT_80333428;
    pfVar3[3] = FLOAT_80333428;
    pfVar3[2] = FLOAT_80333428;
    pfVar3[1] = FLOAT_80333428;
    *(u32*)((u8*)pfVar3 + 0x1c) = 0;
    pfVar3[10] = FLOAT_80333428;
    pfVar3[9] = FLOAT_80333428;
    pfVar3[8] = FLOAT_80333428;

    *((u8*)pfVar3 + 0x2c) = 0;
    *((u8*)pfVar3 + 0x2d) = 0;
    *((u8*)pfVar3 + 0x2e) = 0;
    *((u16*)((u8*)pfVar3 + 0x30)) = 0;
    *((u16*)((u8*)pfVar3 + 0x34)) = 0;
    *((u16*)((u8*)pfVar3 + 0x32)) = 0;

    pfVar3[14] = RandF__5CMathFf(FLOAT_8033345c, &math);
    *((u8*)pfVar3 + 0x4c) = 1;

    if (GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(&Game.game, (PPPIFPARAM*)((u8*)pppMngStPtr + 0x130), &local_24, &local_28) != 0) {
        GetTargetCursor__5CGameFiR3VecR3Vec(&Game.game, local_28, (Vec*)(pfVar3 + 0x10), &local_20);

        u8* partyObj = (u8*)GetPartyObj__5CGameFi(&Game.game, local_28);
        local_14.x = *(f32*)(partyObj + 0x15c);
        local_14.y = *(f32*)(partyObj + 0x160);
        local_14.z = *(f32*)(partyObj + 0x164);
        if (local_24 == 0x200) {
            pfVar3[15] = PSVECDistance((Vec*)(pfVar3 + 0x10), &local_14);
        } else {
            pfVar3[15] = FLOAT_80333448;
        }
    } else {
        pfVar3[15] = FLOAT_80333448;
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
void pppConstruct2Laser(struct pppLaser *pppLaser, struct UnkC *param_2)
{
    f32 fVar1 = FLOAT_80333428;
    u8* work = (u8*)pppLaser + param_2->offsets->m_serializedDataOffsets[2] + 0x80;

    *(f32*)(work + 0x18) = FLOAT_80333428;
    *(f32*)(work + 0x14) = fVar1;
    *(f32*)(work + 0x10) = fVar1;
    *(f32*)(work + 0x0C) = fVar1;
    *(f32*)(work + 0x08) = fVar1;
    *(f32*)(work + 0x04) = fVar1;
    *(f32*)(work + 0x28) = fVar1;
    *(f32*)(work + 0x24) = fVar1;
    *(f32*)(work + 0x20) = fVar1;
    *(work + 0x2C) = 0;
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
void pppDestructLaser(struct pppLaser *pppLaser, struct UnkC *param_2)
{
    f32* work = (f32*)((u8*)pppLaser + 0x80 + param_2->offsets->m_serializedDataOffsets[2]);
    void* alloc = *(void**)(work + 7);
    if (alloc != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(alloc);
        *(void**)(work + 7) = 0;
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
void pppFrameLaser(struct pppLaser *pppLaser, struct UnkB *param_2, struct UnkC *param_3)
{
    LaserStep* step = (LaserStep*)param_2;
    float* work;
    _pppPObject* baseObj = (_pppPObject*)pppLaser;
    Vec localA;
    Vec localB;
    Vec localPos;
    CMapCylinderRaw cyl;
    Mtx charaMtx;
    Mtx tempMtx;

    if ((DAT_8032ed70 != 0) || (step->m_stepValue == 1)) {
        return;
    }

    work = (float*)((u8*)&pppLaser->field_0x88 + param_3->offsets->m_serializedDataOffsets[2]);
    if (work[0xf] == FLOAT_80333448) {
        return;
    }

    bool resetPoints = (work[7] == FLOAT_80333428);
    if (resetPoints) {
        work[7] = (float)(u32)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)step->m_payload[0x1e] * 0xc, pppEnvStPtr->m_stagePtr, s_pppLaser_cpp, 0x7d);
        memset((void*)(u32)work[7], 0, (u32)step->m_payload[0x1e] * 0xc);
    }

    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
        *(float*)(step->m_payload + 0x10), baseObj, step->m_graphId, work + 4, work + 5, work + 6,
        (float*)(step->m_payload + 0x14), (float*)(step->m_payload + 0x18));
    CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
        *(float*)(step->m_payload + 4), baseObj, step->m_graphId, work + 1, work + 2, work + 3,
        (float*)(step->m_payload + 8), (float*)(step->m_payload + 0xc));

    pppCalcFrameShape__FPlRsRsRss(
        *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4), *(short*)((u8*)work + 0x32),
        *(short*)(work + 0xd), *(short*)(work + 0xc), *(short*)(step->m_payload + 0x2c));

    for (u32 i = 0; i < (u32)step->m_payload[0x3a] + 1; i++) {
        Vec* points = (Vec*)(u32)work[7];
        int max = (int)step->m_payload[0x1e] - 2;

        for (int j = max; (int)i <= j; j--) {
            localA = points[j];
            pppCopyVector__FR3Vec3Vec(&points[j + 1], &localA);
        }

        localB.x = FLOAT_80333428;
        localB.y = FLOAT_80333428;
        localB.z = work[0];

        if (i == 0) {
            PSMTXConcat(pppMngStPtr->m_matrix.value, baseObj->m_localMatrix.value, tempMtx);
            work[8] = tempMtx[0][3];
            work[9] = tempMtx[1][3];
            work[10] = tempMtx[2][3];
            PSMTXMultVec(tempMtx, &localB, points);
        } else if (!resetPoints) {
            double denom = ((double)(int)step->m_payload[0x3a] + 1.0) - DOUBLE_80333440;
            double t = (FLOAT_80333448 / (float)denom) * ((double)(int)i - DOUBLE_80333440);
            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f((float)t, pppMngStPtr, charaMtx) == 0) {
                resetPoints = true;
            } else {
                PSMTXConcat(charaMtx, baseObj->m_localMatrix.value, charaMtx);
                PSMTXMultVec(charaMtx, &localB, &points[i]);
            }
        }

        if ((i != 0) && resetPoints) {
            continue;
        }

        localPos.x = work[8];
        localPos.y = work[9];
        localPos.z = work[10];
        pppSubVector__FR3Vec3Vec3Vec(&localA, &points[i], &localPos);
        PSVECScale(&localA, &localA, FLOAT_8033344c);

        cyl.m_bottom = localPos;
        cyl.m_direction = localA;
        cyl.m_radius = FLOAT_80333428;
        cyl.m_height = FLOAT_80333450;
        cyl.m_radius2 = FLOAT_80333454;
        cyl.m_height2 = FLOAT_80333454;

        bool hit = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                       &MapMng, &cyl, &cyl.m_direction, 0xffffffff) != 0;
        if (hit) {
            CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &points[i]);
            work[0] = PSVECDistance(&points[i], (Vec*)(work + 8));
        } else if (i == 0 && *((u8*)work + 0x4c) != 0) {
            if (work[0xf] - FLOAT_80333458 < work[0]) {
                work[0] = work[0xf] - FLOAT_80333458;
                ParticleFrameCallback__5CGameFiiiiiP3Vec(
                    &Game.game, 0, (int)pppMngStPtr->m_kind, (int)pppMngStPtr->m_nodeIndex, 3,
                    (int)((u32)baseObj->m_graphId >> 12));
                *((u8*)work + 0x4c) = 0;
            }
            if (*((u8*)work + 0x4c) != 0) {
                work[0] += work[1];
            }
        }

        if (i == 0) {
            localB.z = work[0];
            PSMTXMultVec(tempMtx, &localB, &points[0]);
        }

        if (step->m_payload[0x3b] == 0) {
            pppHitCylinderSendSystem__FP9_pppMngStP3VecP3Vecff(
                pppMngStPtr, (Vec*)(work + 8), &localA, pppMngStPtr->m_ownerScale * *(float*)(step->m_payload + 0x24),
                *(float*)(step->m_payload + 0x20));
        }

        if ((step->m_payload[0x3c] == 0) && hit && step->m_arg3 != -1) {
            u8* hitFrame = ((u8*)work + 0x2d);
            if (*hitFrame >= step->m_payload[0x1d]) {
                *hitFrame = 0;
                u8* dataVals = *(u8**)((u8*)pppMngStPtr + 0xc8);
                if (dataVals != 0) {
                    int created =
                        pppCreatePObject__FP9_pppMngStP12_pppPDataVal(pppMngStPtr, dataVals + step->m_arg3 * 0x10);
                    if (created != 0) {
                        *(struct pppLaser**)(created + 4) = pppLaser;
                        *(Vec*)(created + *(int*)step->m_payload + 0x80) = points[i];
                        *(float*)(created + *(int*)step->m_payload + 0x84) += *(float*)(step->m_payload + 0x34);
                    }
                }
            } else {
                (*hitFrame)++;
            }
        }
    }

    if (resetPoints) {
        Vec* points = (Vec*)(u32)work[7];
        for (int i = 0; i < (int)(u32)step->m_payload[0x1e]; i++) {
            pppCopyVector__FR3Vec3Vec(&points[i], &points[0]);
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
void pppRenderLaser(struct pppLaser *pppLaser, struct UnkB *param_2, struct UnkC *param_3)
{
    LaserStep* step = (LaserStep*)param_2;
    _pppPObject* baseObj = (_pppPObject*)pppLaser;
    Vec* points;
    int colorOffset = param_3->offsets->m_serializedDataOffsets[1];
    float* work = (float*)((u8*)&pppLaser->field_0x88 + param_3->offsets->m_serializedDataOffsets[2]);
    u32 count;
    u32 i;
    u32 color;
    u32 colorBase;
    u32 color0;
    u32 color1;
    u8 alpha0;
    u8 alphaStep;
    u8 alphaMax;
    float halfWidth;
    float length;
    float u0;
    float u1;
    float uvStep;
    pppFMATRIX localMtx;
    pppFMATRIX worldMtx;
    pppFMATRIX viewMtx;
    pppFMATRIX modelView;
    pppFMATRIX mtxOut;
    pppFMATRIX shapeMtx;
    Mtx tempMtx;
    Vec shapePos;
    _GXColor debugColor;
    int tex;

    if (step->m_dataValIndex == 0xFFFF) {
        return;
    }

    tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_dataValIndex, pppEnvStPtr);
    pppSetBlendMode__FUc(step->m_payload[0x1c]);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)&pppLaser->field_0x88 + colorOffset, &baseObj->m_localMatrix, FLOAT_80333428, step->m_payload[0x39],
        step->m_payload[0x38], step->m_payload[0x1c], 0, 1, 1, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetCullMode(GX_CULL_NONE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 1, 7, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, GX_FALSE, 0x7D);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
        0, 0xF, 8, 0xA, 0xF);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
        0, 7, 7, 7, 5);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);

    color = *(u32*)((u8*)&pppLaser->field_0x88 + colorOffset);
    halfWidth = work[4];
    length = work[0];

    localMtx = baseObj->m_localMatrix;
    worldMtx = pppMngStPtr->m_matrix;
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&modelView, &worldMtx, &localMtx);
    viewMtx = *(pppFMATRIX*)&ppvCameraMatrix0;
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&mtxOut, &viewMtx, &modelView);
    GXLoadPosMtxImm(mtxOut.value, 0);

    GXBegin(GX_QUADS, GX_VTXFMT7, 4);
    GXPosition3f32(-halfWidth, FLOAT_80333428, FLOAT_80333428);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_80333428, FLOAT_80333428);
    GXPosition3f32(-halfWidth, FLOAT_80333428, length);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_80333428, work[0]);
    GXPosition3f32(halfWidth, FLOAT_80333428, FLOAT_80333428);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_8033342c, FLOAT_80333428);
    GXPosition3f32(halfWidth, FLOAT_80333428, length);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_8033342c, work[0]);

    GXBegin(GX_QUADS, GX_VTXFMT7, 4);
    GXPosition3f32(FLOAT_80333428, -halfWidth, FLOAT_80333428);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_80333428, FLOAT_80333428);
    GXPosition3f32(FLOAT_80333428, -halfWidth, length);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_80333428, work[0]);
    GXPosition3f32(FLOAT_80333428, halfWidth, FLOAT_80333428);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_8033342c, FLOAT_80333428);
    GXPosition3f32(FLOAT_80333428, halfWidth, length);
    GXColor1u32(color);
    GXTexCoord2f32(FLOAT_8033342c, work[0]);

    if (step->m_stepValue != 0) {
        long* shape = *(long**)(*(u32*)&pppEnvStPtr->m_particleColors[0] + (u32)step->m_stepValue * 4);
        pppUnitMatrix__FR10pppFMATRIX(&shapeMtx);
        shapeMtx.value[0][0] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.x;
        shapeMtx.value[1][1] = *(float*)(step->m_payload + 0x30) * pppMngStPtr->m_scale.y;
        shapeMtx.value[2][2] = shapeMtx.value[0][0];
        if (work[0xe] != FLOAT_80333428) {
            PSMTXRotRad(tempMtx, 'z', work[0xe]);
            PSMTXConcat(shapeMtx.value, tempMtx, shapeMtx.value);
        }
        PSMTXMultVec(ppvCameraMatrix0, (Vec*)(u32)work[7], &shapePos);
        shapeMtx.value[0][3] = shapePos.x;
        shapeMtx.value[1][3] = shapePos.y;
        shapeMtx.value[2][3] = shapePos.z;
        GXLoadPosMtxImm(shapeMtx.value, GX_PNMTX0);
        pppDrawShp__FPlsP12CMaterialSetUc(shape, *(s16*)(work + 0xd), pppEnvStPtr->m_materialSetPtr, step->m_payload[0x1c]);

        count = (u32)step->m_payload[0x1e];
        if (count > 1) {
            uvStep = FLOAT_8033342c / ((float)(double)count - (float)DOUBLE_80333438);
            if (step->m_initWOrk == 0xFFFF) {
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
            } else {
                tex = GetTextureFromRSD__FiP9_pppEnvSt(step->m_initWOrk, pppEnvStPtr);
                _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
                GXLoadTexObj((GXTexObj*)(tex + 0x28), GX_TEXMAP0);
            }

            GXLoadPosMtxImm(ppvCameraMatrix0, GX_PNMTX0);
            alphaMax = step->m_payload[0x2b];
            alphaStep = (u8)((u32)alphaMax / count);
            colorBase = *(u32*)(step->m_payload + 0x28) & 0xFFFFFF00;
            points = (Vec*)(u32)work[7];

            GXBegin(GX_TRIANGLES, GX_VTXFMT7, (u16)((count - 1) * 3));
            for (i = 0; i < count - 1; i++) {
                alpha0 = (u8)(alphaMax - (u8)(alphaStep * i));
                color0 = colorBase | alpha0;
                color1 = colorBase | (u8)(alphaMax - (u8)(alphaStep * (i + 1)));
                u0 = (float)i * uvStep;
                u1 = (float)(i + 1) * uvStep;

                GXPosition3f32(work[8], work[9], work[10]);
                GXColor1u32(color0);
                GXTexCoord2f32(u0, FLOAT_8033342c);

                GXPosition3f32(points[i].x, points[i].y, points[i].z);
                GXColor1u32(color0);
                GXTexCoord2f32(u0, FLOAT_80333428);

                GXPosition3f32(points[i + 1].x, points[i + 1].y, points[i + 1].z);
                GXColor1u32(color1);
                GXTexCoord2f32(u1, FLOAT_80333428);
            }
        }

        if ((CFlatFlags & 0x200000) != 0) {
            SetVtxFmt_POS_CLR__5CUtilFv(&DAT_8032ec70);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
            _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
            GXSetNumTexGens(0);
            pppSetBlendMode__FUc(1);

            debugColor.r = 0x80;
            debugColor.g = 0xFF;
            debugColor.b = 0x80;
            debugColor.a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, debugColor);
            GXSetPointSize(0x28, GX_TO_ZERO);
            GXBegin(GX_POINTS, GX_VTXFMT7, (u16)(count - 1));
            for (i = 0; i < count - 1; i++) {
                GXPosition3f32(points[i].x, points[i].y, points[i].z);
                GXColor1u32(*(u32*)&debugColor);
            }

            debugColor.r = 0x80;
            debugColor.g = 0x80;
            debugColor.b = 0xFF;
            debugColor.a = 0xFF;
            GXSetChanAmbColor(GX_COLOR0A0, debugColor);
            GXSetLineWidth(0x14, GX_TO_ZERO);
            GXBegin(GX_LINES, GX_VTXFMT7, (u16)((count - 1) * 4));
            for (i = 0; i < count - 1; i++) {
                GXPosition3f32(points[i].x, points[i].y, points[i].z);
                GXColor1u32(*(u32*)&debugColor);
                GXPosition3f32(points[i + 1].x, points[i + 1].y, points[i + 1].z);
                GXColor1u32(*(u32*)&debugColor);
                GXPosition3f32(points[i].x, points[i].y, points[i].z);
                GXColor1u32(*(u32*)&debugColor);
                GXPosition3f32(work[8], work[9], work[10]);
                GXColor1u32(*(u32*)&debugColor);
            }

            GXSetLineWidth(8, GX_TO_ZERO);
            GXSetPointSize(8, GX_TO_ZERO);
            GXSetZMode(1, GX_LEQUAL, 0);

            PSMTXIdentity(tempMtx);
            tempMtx[0][0] = *(float*)((u8*)pppMngStPtr + 0x64) * *(float*)(step->m_payload + 0x24);
            tempMtx[1][1] = tempMtx[0][0];
            tempMtx[2][2] = PSVECDistance((Vec*)(u32)work[7], (Vec*)(work + 8));
            PSMTXConcat(baseObj->m_localMatrix.value, tempMtx, tempMtx);
            PSMTXConcat(pppMngStPtr->m_matrix.value, tempMtx, tempMtx);
            PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
            shapePos.x = FLOAT_80333428;
            shapePos.y = FLOAT_80333428;
            shapePos.z = FLOAT_8033342c;
            PSMTXMultVec(tempMtx, &shapePos, &shapePos);
            tempMtx[0][3] = shapePos.x;
            tempMtx[1][3] = shapePos.y;
            tempMtx[2][3] = shapePos.z;
            debugColor.r = 0xFF;
            debugColor.g = 0xFF;
            debugColor.b = 0xFF;
            debugColor.a = 0xFF;
            Graphic.DrawSphere(tempMtx, debugColor);

            for (i = 0; i < count; i++) {
                if ((points[i].x == FLOAT_80333428) && (points[i].y == FLOAT_80333428) && (points[i].z == FLOAT_80333428)) {
                    continue;
                }
                PSMTXIdentity(tempMtx);
                tempMtx[0][0] = FLOAT_80333430;
                tempMtx[1][1] = FLOAT_80333430;
                tempMtx[2][2] = FLOAT_80333430;
                tempMtx[0][3] = points[i].x;
                tempMtx[1][3] = points[i].y;
                tempMtx[2][3] = points[i].z;
                PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
                Graphic.DrawSphere(tempMtx, debugColor);
            }

            PSMTXIdentity(tempMtx);
            tempMtx[0][0] = FLOAT_80333430;
            tempMtx[1][1] = FLOAT_80333430;
            tempMtx[2][2] = FLOAT_80333430;
            tempMtx[0][3] = work[8];
            tempMtx[1][3] = work[9];
            tempMtx[2][3] = work[10];
            PSMTXConcat(ppvCameraMatrix0, tempMtx, tempMtx);
            Graphic.DrawSphere(tempMtx, debugColor);
            pppInitBlendMode__Fv();
        }
    }
}
