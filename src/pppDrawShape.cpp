#include "ffcc/pppDrawShape.h"
#include "dolphin/types.h"

/*
 * --INFO--
 * PAL Address: 0x80065654
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShapeConstruct(void* pppShape, void* data)
{
	void** dataPtr = (void**)data;
	void* basePtr = dataPtr[3];
	void* shapePtr = ((void**)basePtr)[0];
	u16* targetPtr = (u16*)((u8*)pppShape + (u32)shapePtr + 0x80);
	
	targetPtr[2] = 0;
	targetPtr[1] = 0;
	targetPtr[0] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCalcShape(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawShape(void)
{
	// TODO
}