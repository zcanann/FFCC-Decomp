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
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) return;
	
	void* param1 = *((void**)((char*)params + 0xc));
	void* param2 = *((void**)((char*)params + 0x10));
	
	int offset1 = *((int*)((char*)param1 + 0x4));
	int offset2 = *((int*)((char*)param2 + 0x4));
	
	short* color1 = (short*)((char*)dst + offset1);
	short* color2 = (short*)((char*)dst + offset2);
	
	// ID comparison
	int srcId = *((int*)src);
	int dstId = *((int*)((char*)dst + 0xc));
	
	if (srcId != dstId)
	{
		short* srcDeltas = (short*)((char*)src + 0x8);
		
		*((short*)((char*)color2 + 0x80) + 0) += srcDeltas[0]; // R
		*((short*)((char*)color2 + 0x80) + 1) += srcDeltas[1]; // G  
		*((short*)((char*)color2 + 0x80) + 2) += srcDeltas[2]; // B
		*((short*)((char*)color2 + 0x80) + 3) += srcDeltas[3]; // A
	}
	
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
	char* param = (char*)params;  

	param = (char*)*((void**)(param + 0xc));

	int offset = *((int*)(param + 0x4));
	char* colorBase = (char*)dst + offset;
	
	*((short*)(colorBase + 0x86)) = 0;
	*((short*)(colorBase + 0x84)) = 0;
	*((short*)(colorBase + 0x82)) = 0;
	*((short*)(colorBase + 0x80)) = 0;
}
