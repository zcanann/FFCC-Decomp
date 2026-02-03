#include "ffcc/pppLaser.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructLaser(struct pppLaser *pppLaser, struct UnkC *param_2)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructLaser(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameLaser(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderLaser(void)
{
	// TODO
}
