#include "ffcc/pppCrystal.h"
#include "ffcc/memory.h"

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
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800dd37c
 * PAL Size: 136b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCrystal(struct pppCrystal* pppCrystal, struct UnkC* param_2)
{
	void* stage;
	void** puVar1;
	
	puVar1 = (void**)((char*)(pppCrystal) + 8 + param_2->m_serializedDataOffsets[2]);
	stage = puVar1[0];
	if ((stage != 0) && (*(void**)stage != 0)) {
		// TODO: pppHeapUseRate((CMemory::CStage*)*(void**)stage);
		*(void**)stage = 0;
	}
	if (stage != 0) {
		// TODO: pppHeapUseRate((CMemory::CStage*)stage);
	}
	if (puVar1[1] != 0) {
		// TODO: pppHeapUseRate((CMemory::CStage*)puVar1[1]);
		puVar1[1] = 0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderCrystal(struct pppCrystal* pppCrystal, struct UnkB* param_2, struct UnkC* param_3)
{
	// TODO
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
