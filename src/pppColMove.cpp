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
	// Check global flag first - matches target assembly order
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) return;  // lwz r0,lbl_8032ED70@sda21; cmpwi r0,0x0; bnelr
	
	// Get param structure pointers - matches target assembly: lwz r6,0xc(r5); lwz r5,0x10(r5)
	void* param1 = *((void**)((char*)params + 0xc));  // lwz r6, 0xc(r5)
	void* param2 = *((void**)((char*)params + 0x10)); // lwz r5, 0x10(r5)
	
	// Get offsets and build pointers - target: lwz r0,0x4(r6); lwz r7,0x4(r5); add r5,r0,r3; add r7,r7,r3
	int offset1 = *((int*)((char*)param1 + 0x4));  // lwz r0, 0x4(r6)
	int offset2 = *((int*)((char*)param2 + 0x4));  // lwz r7, 0x4(r5)
	
	short* color1 = (short*)((char*)dst + offset1);  // add r5, r0, r3 (note: no +0x80)
	short* color2 = (short*)((char*)dst + offset2);  // add r7, r7, r3
	
	// ID comparison: lwz r6,0x0(r4); lwz r0,0xc(r3); cmpw r6,r0; beq 0x74
	int srcId = *((int*)src);
	int dstId = *((int*)((char*)dst + 0xc));
	
	if (srcId != dstId) {
		// Add src deltas to color2 with +0x80 offsets: lha r3,0x80(r7); lha r0,0x8(r4)...
		short* srcDeltas = (short*)((char*)src + 0x8);
		*((short*)((char*)color2 + 0x80) + 0) += srcDeltas[0];  // R
		*((short*)((char*)color2 + 0x80) + 1) += srcDeltas[1];  // G  
		*((short*)((char*)color2 + 0x80) + 2) += srcDeltas[2];  // B
		*((short*)((char*)color2 + 0x80) + 3) += srcDeltas[3];  // A
	}
	
	// Always add color2+0x80 to color1+0x80: lha r3,0x80(r5); lha r0,0x80(r7)...
	*((short*)((char*)color1 + 0x80) + 0) += *((short*)((char*)color2 + 0x80) + 0);
	*((short*)((char*)color1 + 0x80) + 1) += *((short*)((char*)color2 + 0x80) + 1);
	*((short*)((char*)color1 + 0x80) + 2) += *((short*)((char*)color2 + 0x80) + 2);
	*((short*)((char*)color1 + 0x80) + 3) += *((short*)((char*)color2 + 0x80) + 3);
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
	// Target assembly: lwz r4,0xc(r4); li r0,0x0; lwz r4,0x4(r4); add r3,r4,r3; sth r0,0x86(r3)...
	char* param = (char*)params;  
	param = (char*)*((void**)(param + 0xc));  // lwz r4, 0xc(r4) 
	int offset = *((int*)(param + 0x4));      // lwz r4, 0x4(r4) 
	char* colorBase = (char*)dst + offset;    // add r3, r4, r3
	
	// Store 0 with direct 0x80+ offsets in order: 0x86, 0x84, 0x82, 0x80  
	*((short*)(colorBase + 0x86)) = 0;  // sth r0, 0x86(r3)  
	*((short*)(colorBase + 0x84)) = 0;  // sth r0, 0x84(r3)
	*((short*)(colorBase + 0x82)) = 0;  // sth r0, 0x82(r3)
	*((short*)(colorBase + 0x80)) = 0;  // sth r0, 0x80(r3)
}