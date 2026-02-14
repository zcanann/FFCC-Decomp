#include "ffcc/pppLaser.h"
#include "ffcc/math.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"

#include <string.h>

extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern struct _pppMngSt* pppMngStPtr;
extern CMath Math;
extern f32 FLOAT_80333428;
extern f32 FLOAT_80333448;
extern f32 FLOAT_8033344c;
extern f32 FLOAT_80333450;
extern f32 FLOAT_80333454;
extern f32 FLOAT_80333458;
extern f32 FLOAT_8033345c;
extern f64 DOUBLE_80333440;
extern s32 DAT_8032ed70;
extern CMapMng MapMng;

extern "C" {
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
    f32 fVar1 = FLOAT_80333428;
    f32* pfVar3 = (f32*)((u8*)&pppLaser->field_0x88 + param_2->offsets->m_serializedDataOffsets[2]);
    int local_24;
    int local_28;
    Vec local_20;
    Vec local_14;

    *pfVar3 = FLOAT_80333428;
    pfVar3[6] = fVar1;
    pfVar3[5] = fVar1;
    pfVar3[4] = fVar1;
    pfVar3[3] = fVar1;
    pfVar3[2] = fVar1;
    pfVar3[1] = fVar1;
    pfVar3[7] = 0.0f;
    pfVar3[10] = fVar1;
    pfVar3[9] = fVar1;
    pfVar3[8] = fVar1;

    *((u8*)pfVar3 + 0x2c) = 0;
    *((u8*)pfVar3 + 0x2d) = 0;
    *((u8*)pfVar3 + 0x2e) = 0;
    *((u16*)pfVar3 + 0x18) = 0;
    *((u16*)pfVar3 + 0x19) = 0;
    *((u16*)pfVar3 + 0x1a) = 0;

    pfVar3[14] = RandF__5CMathFf(FLOAT_8033345c, &Math);
    *((u8*)pfVar3 + 0x4c) = 1;

    if (GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(&Game.game, (PPPIFPARAM*)((u8*)pppMngStPtr + 0x130), &local_24, &local_28) == 0) {
        pfVar3[15] = FLOAT_80333448;
        *(u8*)((u8*)pppMngStPtr + 0x118) = 1;
        pppStopSe__FP9_pppMngStP7PPPSEST(pppMngStPtr, (PPPSEST*)((u8*)pppMngStPtr + 0x11c));
    } else {
        GetTargetCursor__5CGameFiR3VecR3Vec(&Game.game, local_28, (Vec*)(pfVar3 + 0x10), &local_20);

        {
            u8* partyObj = (u8*)GetPartyObj__5CGameFi(&Game.game, local_28);
            local_14.x = *(f32*)(partyObj + 0x15c);
            local_14.y = *(f32*)(partyObj + 0x160);
            local_14.z = *(f32*)(partyObj + 0x164);
        }

        if (local_24 == 0x200) {
            pfVar3[15] = PSVECDistance((Vec*)(pfVar3 + 0x10), &local_14);
        } else {
            pfVar3[15] = FLOAT_80333448;
        }
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
    int iVar2 = param_2->offsets->m_serializedDataOffsets[2];
    
    *(f32*)((u8*)&pppLaser->field_0x98 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0x94 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0x90 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0x8c + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0x88 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0x84 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0xa8 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0xa4 + iVar2) = fVar1;
    *(f32*)((u8*)&pppLaser->field_0xa0 + iVar2) = fVar1;
    *((u8*)&pppLaser->field_0xac + iVar2) = 0;
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
    int iVar1 = param_2->offsets->m_serializedDataOffsets[2];
    void *pfVar3 = *(void **)((u8*)&pppLaser->field_0x9c + iVar1);
    if (pfVar3 != 0) {
        pppHeapUseRate__FPQ27CMemory6CStage(pfVar3);
        *(void **)((u8*)&pppLaser->field_0x9c + iVar1) = 0;
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

    if (work[7] == 0.0f) {
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
        } else {
            double denom = ((double)(int)step->m_payload[0x3a] + 1.0) - DOUBLE_80333440;
            double t = (FLOAT_80333448 / (float)denom) * ((double)(int)i - DOUBLE_80333440);
            if (GetCharaNodeFrameMatrix__FP9_pppMngStfPA4_f((float)t, pppMngStPtr, charaMtx) == 0) {
                for (int k = 0; k < (int)(u32)step->m_payload[0x1e]; k++) {
                    points[k] = points[0];
                }
                return;
            }
            PSMTXConcat(charaMtx, baseObj->m_localMatrix.value, charaMtx);
            PSMTXMultVec(charaMtx, &localB, &points[i]);
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
	// TODO
}
