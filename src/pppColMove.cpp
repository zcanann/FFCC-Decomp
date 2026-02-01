#include "ffcc/pppColMove.h"

/*
 * --INFO--
 * PAL Address: 0x80065028
 * PAL Size: 188b  
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMove(void* dst, void* src, void* params)
{
	// Implementation based on assembly analysis
	// Function performs color value operations with conditional logic
	// TODO: Complete implementation based on specific data structure layouts
}

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppColMoveCon(void* dst, void* params)
{
	// Constructor function that zeros out color structure
	// Match exact assembly: lwz r4, 0xc(r4); lwz r4, 0x4(r4); addi r4, r4, 0x80; add r4, r3, r4
	
	// Extract pointer from params structure (offset 0xc)
	void** paramStruct = (void**)((char*)params + 0xc);
	void** innerStruct = (void**)(*paramStruct);
	
	// Get the offset value and add 0x80 (to match addi r4, r4, 0x80)
	int offset = *((int*)((char*)innerStruct + 0x4));
	offset += 0x80;
	
	// Calculate final pointer (to match add r4, r3, r4)
	short* colorData = (short*)((char*)dst + offset);
	
	// Zero out 4 color components at offsets 0x0, 0x2, 0x4, 0x6
	colorData[0] = 0;  // offset 0x0
	colorData[1] = 0;  // offset 0x2 
	colorData[2] = 0;  // offset 0x4
	colorData[3] = 0;  // offset 0x6
}