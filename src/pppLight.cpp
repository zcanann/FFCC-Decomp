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
	// Based on assembly analysis - complex lighting calculation function
	char* r28 = (char*)param1;
	char* r29 = (char*)param2;
	
	// Get base pointer from param3 structure  
	void** ptr1 = (void**)((char*)param3 + 0xc);
	void** ptr2 = (void**)*ptr1;
	void* ptr3 = *ptr2;
	char* r30 = r28 + (int)ptr3 + 0x80;
	
	// Early return check - appears to check some global flag
	// if (some_global_flag != 0) return;
	
	// Float accumulation operations from assembly
	float f1, f0;
	
	// Load and accumulate float values at various offsets
	f1 = *(float*)(r30 + 0x1c);
	f0 = *(float*)(r30 + 0x20);
	f0 = f1 + f0;
	*(float*)(r30 + 0x1c) = f0;
	
	f1 = *(float*)(r30 + 0x18);
	f0 = *(float*)(r30 + 0x1c);
	f0 = f1 + f0;
	*(float*)(r30 + 0x18) = f0;
	
	f1 = *(float*)(r30 + 0x28);
	f0 = *(float*)(r30 + 0x2c);
	f0 = f1 + f0;
	*(float*)(r30 + 0x28) = f0;
	
	f1 = *(float*)(r30 + 0x24);
	f0 = *(float*)(r30 + 0x28);
	f0 = f1 + f0;
	*(float*)(r30 + 0x24) = f0;
	
	// More float accumulations for additional offsets
	f1 = *(float*)(r30 + 0x34);
	f0 = *(float*)(r30 + 0x38);
	f0 = f1 + f0;
	*(float*)(r30 + 0x34) = f0;
	
	f1 = *(float*)(r30 + 0x30);
	f0 = *(float*)(r30 + 0x34);
	f0 = f1 + f0;
	*(float*)(r30 + 0x30) = f0;
	
	f1 = *(float*)(r30 + 0x40);
	f0 = *(float*)(r30 + 0x44);
	f0 = f1 + f0;
	*(float*)(r30 + 0x40) = f0;
	
	f1 = *(float*)(r30 + 0x3c);
	f0 = *(float*)(r30 + 0x40);
	f0 = f1 + f0;
	*(float*)(r30 + 0x3c) = f0;
	
	// Integer accumulation operations with half-word loads
	short r3, r0;
	
	r3 = *(short*)(r30 + 0x8);
	r0 = *(short*)(r30 + 0x10);
	r0 = r3 + r0;
	*(short*)(r30 + 0x8) = r0;
	
	r3 = *(short*)(r30 + 0xa);
	r0 = *(short*)(r30 + 0x12);
	r0 = r3 + r0;
	*(short*)(r30 + 0xa) = r0;
	
	r3 = *(short*)(r30 + 0xc);
	r0 = *(short*)(r30 + 0x14);
	r0 = r3 + r0;
	*(short*)(r30 + 0xc) = r0;
	
	r3 = *(short*)(r30 + 0xe);
	r0 = *(short*)(r30 + 0x16);
	r0 = r3 + r0;
	*(short*)(r30 + 0xe) = r0;
	
	// Check if we should process param2 data
	int r3_int = *(int*)(r29 + 0x0);
	int r0_int = *(int*)(r28 + 0xc);
	if (r3_int != r0_int) {
		return; // Early exit if IDs don't match
	}
	
	// Process input deltas from param2
	r3 = *(short*)(r30 + 0x0);
	r0 = *(short*)(r29 + 0x8);
	r0 = r3 + r0;
	*(short*)(r30 + 0x0) = r0;
	
	r3 = *(short*)(r30 + 0x2);
	r0 = *(short*)(r29 + 0xa);
	r0 = r3 + r0;
	*(short*)(r30 + 0x2) = r0;
	
	r3 = *(short*)(r30 + 0x4);
	r0 = *(short*)(r29 + 0xc);
	r0 = r3 + r0;
	*(short*)(r30 + 0x4) = r0;
	
	r3 = *(short*)(r30 + 0x6);
	r0 = *(short*)(r29 + 0xe);
	r0 = r3 + r0;
	*(short*)(r30 + 0x6) = r0;
	
	// Additional accumulations with more param2 offsets
	r3 = *(short*)(r30 + 0x8);
	r0 = *(short*)(r29 + 0x10);
	r0 = r3 + r0;
	*(short*)(r30 + 0x8) = r0;
	
	r3 = *(short*)(r30 + 0xa);
	r0 = *(short*)(r29 + 0x12);
	r0 = r3 + r0;
	*(short*)(r30 + 0xa) = r0;
	
	// Float operations with param2 data
	f1 = *(float*)(r30 + 0x18);
	f0 = *(float*)(r29 + 0x20);
	f0 = f1 + f0;
	*(float*)(r30 + 0x18) = f0;
	
	f1 = *(float*)(r30 + 0x1c);
	f0 = *(float*)(r29 + 0x24);
	f0 = f1 + f0;
	*(float*)(r30 + 0x1c) = f0;
	
	f1 = *(float*)(r30 + 0x20);
	f0 = *(float*)(r29 + 0x28);
	f0 = f1 + f0;
	*(float*)(r30 + 0x20) = f0;
	
	f1 = *(float*)(r30 + 0x24);
	f0 = *(float*)(r29 + 0x2c);
	f0 = f1 + f0;
	*(float*)(r30 + 0x24) = f0;
	
	f1 = *(float*)(r30 + 0x28);
	f0 = *(float*)(r29 + 0x30);
	f0 = f1 + f0;
	*(float*)(r30 + 0x28) = f0;
	
	f1 = *(float*)(r30 + 0x2c);
	f0 = *(float*)(r29 + 0x34);
	f0 = f1 + f0;
	*(float*)(r30 + 0x2c) = f0;
	
	f1 = *(float*)(r30 + 0x30);
	f0 = *(float*)(r29 + 0x38);
	f0 = f1 + f0;
	*(float*)(r30 + 0x30) = f0;
	
	f1 = *(float*)(r30 + 0x34);
	f0 = *(float*)(r29 + 0x3c);
	f0 = f1 + f0;
	*(float*)(r30 + 0x34) = f0;
	
	f1 = *(float*)(r30 + 0x38);
	f0 = *(float*)(r29 + 0x40);
	f0 = f1 + f0;
	*(float*)(r30 + 0x38) = f0;
	
	f1 = *(float*)(r30 + 0x3c);
	f0 = *(float*)(r29 + 0x4c);
	f0 = f1 + f0;
	*(float*)(r30 + 0x3c) = f0;
	
	f1 = *(float*)(r30 + 0x40);
	f0 = *(float*)(r29 + 0x50);
	f0 = f1 + f0;
	*(float*)(r30 + 0x40) = f0;
	
	f1 = *(float*)(r30 + 0x44);
	f0 = *(float*)(r29 + 0x54);
	f0 = f1 + f0;
	*(float*)(r30 + 0x44) = f0;
	
	// Color processing - convert signed 16-bit to 8-bit values  
	// Assembly showed shift-right by 7 operations
	unsigned char color_vals[4];
	color_vals[0] = (unsigned char)(*(short*)(r30 + 0x0) >> 7);
	color_vals[1] = (unsigned char)(*(short*)(r30 + 0x2) >> 7);
	color_vals[2] = (unsigned char)(*(short*)(r30 + 0x4) >> 7);
	color_vals[3] = (unsigned char)(*(short*)(r30 + 0x6) >> 7);
	
	// Various flag checks observed in assembly
	unsigned char flag1 = *(unsigned char*)(r29 + 0x5a);
	unsigned char flag2 = *(unsigned char*)(r29 + 0x5b);
	unsigned char flag3 = *(unsigned char*)(r29 + 0x58);
	
	if (flag1 != 0) {
		// Store color values
		color_vals[0] = (unsigned char)(*(short*)(r30 + 0x0) >> 7);
		color_vals[1] = (unsigned char)(*(short*)(r30 + 0x2) >> 7); 
		color_vals[2] = (unsigned char)(*(short*)(r30 + 0x4) >> 7);
		color_vals[3] = (unsigned char)(*(short*)(r30 + 0x6) >> 7);
	}
	
	// Matrix transformation operations that were in the assembly
	// This looks like setting up a 3x4 matrix and doing vector operations
	float matrix_pos[3];
	matrix_pos[0] = *(float*)(r28 + 0x1c);
	matrix_pos[1] = *(float*)(r28 + 0x2c);
	matrix_pos[2] = *(float*)(r28 + 0x3c);
}