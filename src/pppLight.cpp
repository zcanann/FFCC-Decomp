#include "ffcc/pppLight.h"

/*
 * --INFO--
 * PAL Address: 0x800dab00
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon3(void* param1, void* param2)
{
	// Based on assembly: accesses param2+0xc, then deref twice, then +0x80
	// Stores zeros and a float constant to various offsets
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	
	// Clear some integer values
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Set float values to 0.0f
	*(float*)((char*)base + 0x20) = 0.0f;
	*(float*)((char*)base + 0x2c) = 0.0f;
	*(float*)((char*)base + 0x38) = 0.0f;
	*(float*)((char*)base + 0x44) = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x800dab34
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLightCon(void* param1, void* param2)
{
	// Similar pattern to pppLightCon3 but clears more values
	void** ptr1 = (void**)((char*)param2 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* base = (char*)param1 + (int)ptr3 + 0x80;
	
	// Clear integer values
	*(int*)((char*)base + 0x0) = 0;
	*(int*)((char*)base + 0x4) = 0;
	*(int*)((char*)base + 0x8) = 0;
	*(int*)((char*)base + 0xc) = 0;
	*(int*)((char*)base + 0x10) = 0;
	*(int*)((char*)base + 0x14) = 0;
	
	// Clear float values
	*(float*)((char*)base + 0x18) = 0.0f;
	*(float*)((char*)base + 0x1c) = 0.0f;
	*(float*)((char*)base + 0x20) = 0.0f;
	*(float*)((char*)base + 0x24) = 0.0f;
	*(float*)((char*)base + 0x28) = 0.0f;
	*(float*)((char*)base + 0x2c) = 0.0f;
	*(float*)((char*)base + 0x30) = 0.0f;
	*(float*)((char*)base + 0x34) = 0.0f;
	*(float*)((char*)base + 0x38) = 0.0f;
	*(float*)((char*)base + 0x3c) = 0.0f;
	*(float*)((char*)base + 0x40) = 0.0f;
	*(float*)((char*)base + 0x44) = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x800dab98
 * PAL Size: 1276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppLight(void* param1, void* param2, void* param3)
{
	// Complex function - implementing basic structure for now
	// TODO: Implement full functionality based on assembly analysis
}