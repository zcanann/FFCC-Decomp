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
 * PAL Address: 0x80065588
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcShape(void* pppShape, void* data, void* additionalData)
{
	// Check a global flag - return early if set
	extern u32 lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}

	// Get data pointers
	void** dataPtr = (void**)data;
	u32* addDataPtr = (u32*)additionalData;
	void* basePtr = dataPtr[3];
	u32 indexVal = addDataPtr[1];
	void* shapePtr = ((void**)basePtr)[0];
	
	// Check if shape index is valid
	if ((indexVal >> 16) == 0xFFFF) {
		return;
	}

	// Access shape data and perform calculations
	u16* shapeData = (u16*)((u8*)pppShape + (u32)shapePtr + 0x80);
	// More complex logic would go here...
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