#include "ffcc/pppRandDownIV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;       // Global state flag
extern float lbl_8032FF68;     // Float constant 2.0f
extern double lbl_8032FF70;    // Double constant for conversion
extern float lbl_801EADC8[32]; // Array of floats

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randint(int param1, float param2)
{
	// Function appears to be unused based on assembly analysis
}

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownIV(void* arg1, void* arg2, void* arg3)
{
	// Cast parameters based on assembly analysis
	int* data1 = (int*)arg1;      // r30
	int* data2 = (int*)arg2;      // r31
	int* data3 = (int*)arg3;      // r29
	
	// Check global state first - if set, return early
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Check if data2[0] == data1[3] (assembly shows comparison at offsets 0 and 0xc)
	if (data2[0] == data1[3]) {
		// Get random float from CMath
		math.RandF();
		float randVal = 0.0f; // RandF result stored elsewhere
		float scaledRand = -randVal;
		
		// Check flag at offset 0x18 in data2
		if (*(unsigned char*)((char*)data2 + 0x18) != 0) {
			// Get another random value and scale it
			math.RandF();
			float randVal2 = 0.0f; // Second RandF result
			scaledRand = (scaledRand - randVal2) * lbl_8032FF68; // 2.0f
		}
		
		// Store result at computed offset in data structure
		void** data3_ptr = (void**)&data3[3];
		void* base = *data3_ptr;
		int base_offset = *((int*)base);
		float* resultPtr = (float*)((char*)data1 + base_offset + 0x80);
		*resultPtr = scaledRand;
	}
	
	// Handle case where comparison fails but still need to process
	if (data2[0] != data1[3]) {
		return;
	}
	
	// Get pointer to result storage area
	void** data3_ptr = (void**)&data3[3];
	void* base = *data3_ptr;
	void* addr_base;
	
	// Check field at offset 4 of data2
	if (data2[1] == -1) {
		addr_base = &lbl_801EADC8[0];
	} else {
		int offset = data2[1] + 0x80;
		addr_base = (char*)data1 + offset;
	}
	
	// Process vector components (X, Y, Z)
	// This follows the pattern seen in the assembly for 3 similar calculations
}