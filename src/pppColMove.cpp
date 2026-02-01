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
	// Match assembly structure: lwz r6,0xc(r5); lwz r0,lbl_8032ED70@sda21; lwz r5,0x0(r6); lwz r6,0x4(r6)
	void** paramStruct = (void**)((char*)params + 0xc);  // lwz r6, 0xc(r5)
	
	// Check global flag first  
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) return;  // bnelr
	
	// Get two offset values from param structure
	void* param0Ptr = *paramStruct;  // lwz r5, 0x0(r6)
	void* param4Ptr = *((void**)((char*)paramStruct + 0x4));  // lwz r6, 0x4(r6)
	
	// Calculate color pointers with +0x80 offsets  
	int offset0 = *((int*)((char*)param0Ptr + 0x4)) + 0x80;  // addi r5, r5, 0x80
	int offset4 = *((int*)((char*)param4Ptr + 0x4)) + 0x80;  // addi r7, r6, 0x80
	
	short* color0 = (short*)((char*)dst + offset0);  // add r5, r3, r5  
	short* color4 = (short*)((char*)dst + offset4);  // add r7, r3, r7
	
	// ID comparison: lwz r6,0x0(r4); lwz r0,0xc(r3); cmpw r6,r0; bne 0xa0
	int srcId = *((int*)src);
	int dstId = *((int*)((char*)dst + 0xc));
	
	if (srcId != dstId) {
		// Add src deltas (offset 0x8) to color4: lha r3,0x0(r7); lha r0,0x8(r4); add r0,r3,r0; sth r0,0x0(r7)
		short* srcDeltas = (short*)((char*)src + 0x8);
		color4[0] += srcDeltas[0];  // R
		color4[1] += srcDeltas[1];  // G  
		color4[2] += srcDeltas[2];  // B
		color4[3] += srcDeltas[3];  // A
	}
	
	// Always add color4 to color0: lha r3,0x0(r5); lha r0,0x0(r7); add r0,r3,r0; sth r0,0x0(r5)
	color0[0] += color4[0];
	color0[1] += color4[1];
	color0[2] += color4[2];
	color0[3] += color4[3];
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
	// Follow exact assembly: lwz r4,0xc(r4); li r0,0x0; lwz r4,0x4(r4); addi r4,r4,0x80; add r4,r3,r4
	char* param = (char*)params;  // r4 = params
	param = (char*)*((void**)(param + 0xc));  // lwz r4, 0xc(r4) 
	int offset = *((int*)(param + 0x4));  // lwz r4, 0x4(r4) 
	offset += 0x80;  // addi r4, r4, 0x80
	short* colorPtr = (short*)((char*)dst + offset);  // add r4, r3, r4
	
	// Store 0 in exact order: 0x6, 0x4, 0x2, 0x0
	*(colorPtr + 3) = 0;  // sth r0, 0x6(r4)  
	*(colorPtr + 2) = 0;  // sth r0, 0x4(r4)
	*(colorPtr + 1) = 0;  // sth r0, 0x2(r4)
	*(colorPtr + 0) = 0;  // sth r0, 0x0(r4)
}