#include "ffcc/pppCrystal2.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void ImageBufferSetPixel_IA8(HSD_ImageBuffer*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void MakeRefractionMap(HSD_ImageBuffer*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8013ef74
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
{
    s32 iVar1 = param_2->m_serializedDataOffsets[2];
    *(u32*)((char*)&pppCrystal2->field0_0x0 + 2*4 + iVar1) = 0;
    *(u32*)((char*)&pppCrystal2->field0_0x0 + 2*4 + iVar1 + 4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8013eeec
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal2(pppCrystal2* pppCrystal2, UnkC* param_2)
{
    // TODO: Implement memory cleanup
}

/*
 * --INFO--
 * PAL Address: 0x8013eb50
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    // TODO: Implement frame logic
}

/*
 * --INFO--
 * PAL Address: 0x8013e694
 * PAL Size: 1212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCrystal2(pppCrystal2* pppCrystal2, UnkB* param_2, UnkC* param_3)
{
    // TODO: Implement rendering logic
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}
