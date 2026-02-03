#include "ffcc/pppLaser.h"

extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);

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
    f32 fVar1 = 1.0f;
    int iVar2 = param_2->m_serializedDataOffsets[2];
    f32 *pfVar3 = (f32*)((u8*)&pppLaser->field_0x88 + iVar2);
    
    // Initialize all float values to 1.0 or 0.0
    *pfVar3 = 1.0f;
    pfVar3[1] = fVar1;
    pfVar3[2] = fVar1;
    pfVar3[3] = fVar1;
    pfVar3[4] = fVar1;
    pfVar3[5] = fVar1;
    pfVar3[6] = fVar1;
    pfVar3[7] = 0.0f;
    pfVar3[8] = fVar1;
    pfVar3[9] = fVar1;
    pfVar3[10] = fVar1;
    
    // Initialize byte values to 0
    *((u8*)pfVar3 + 0x2c) = 0;
    *((u8*)pfVar3 + 0x2d) = 0;
    *((u8*)pfVar3 + 0x2e) = 0;
    *((u16*)pfVar3 + 0x18) = 0;
    *((u16*)pfVar3 + 0x1a) = 0;
    *((u16*)pfVar3 + 0x19) = 0;
    
    // Set some random value and flags
    pfVar3[14] = 50.0f; // simplified random
    *((u8*)pfVar3 + 0x4c) = 1;
    
    // Set distance value
    pfVar3[15] = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstruct2Laser(struct pppLaser *pppLaser, struct UnkC *param_2)
{
    f32 fVar1 = 1.0f; // FLOAT_80333428 placeholder
    int iVar2 = param_2->m_serializedDataOffsets[2];
    
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
    int iVar1 = param_2->m_serializedDataOffsets[2];
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
