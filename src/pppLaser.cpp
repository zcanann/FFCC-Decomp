#include "ffcc/pppLaser.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"

extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
extern struct _pppMngSt* pppMngStPtr;
extern CMath Math;
extern f32 FLOAT_80333428;
extern f32 FLOAT_80333448;
extern f32 FLOAT_8033345c;

extern "C" {
f32 RandF__5CMathFf(f32, CMath*);
int GetParticleSpecialInfo__5CGameFR10PPPIFPARAMRiRi(CGame*, PPPIFPARAM*, int*, int*);
void GetTargetCursor__5CGameFiR3VecR3Vec(CGame*, int, Vec*, Vec*);
void* GetPartyObj__5CGameFi(CGame*, int);
void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
}

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
	// TODO
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
