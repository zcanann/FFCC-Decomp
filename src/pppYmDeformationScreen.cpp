#include "ffcc/pppYmDeformationScreen.h"

struct pppYmDeformationScreen;

/*
 * --INFO--
 * PAL Address: 0x80098a94
 * PAL Size: 64b
 */
void pppConstructYmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	// Get offset directly from param2 structure
	int offset = *(int*)((char*)param2 + 8);
	char* basePtr = (char*)obj + offset;
	float zero = 0.0f;
	
	// Initialize fields
	*(short*)(basePtr + 0x84) = 0;
	*(char*)(basePtr + 0x86) = 1;
	*(float*)(basePtr + 0x88) = zero;
	*(float*)(basePtr + 0x8c) = zero;
	*(float*)(basePtr + 0x90) = zero;
	*(float*)(basePtr + 0x94) = zero;
	*(float*)(basePtr + 0x98) = zero;
	*(float*)(basePtr + 0x9c) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a64
 * PAL Size: 48b
 */
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen* obj, void* param2)
{
	// Get offset directly from param2 structure
	int offset = *(int*)((char*)param2 + 8);
	char* basePtr = (char*)obj + offset;
	float zero = 0.0f;
	
	// Initialize float fields only
	*(float*)(basePtr + 0x88) = zero;
	*(float*)(basePtr + 0x8c) = zero;
	*(float*)(basePtr + 0x90) = zero;
	*(float*)(basePtr + 0x94) = zero;
	*(float*)(basePtr + 0x98) = zero;
	*(float*)(basePtr + 0x9c) = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80098a60
 * PAL Size: 4b
 */
void pppDestructYmDeformationScreen(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8009885c
 * PAL Size: 516b
 */
void pppFrameYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * PAL Address: 0x800981a8
 * PAL Size: 1716b
 */
void pppRenderYmDeformationScreen(pppYmDeformationScreen* param1, void* param2, void* param3)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SetUpIndWarp(VYmDeformationScreen*)
{
	// TODO
}