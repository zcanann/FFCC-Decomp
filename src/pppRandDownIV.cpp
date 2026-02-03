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
	int* data1 = (int*)arg1;
	int* data2 = (int*)arg2;
	int* data3 = (int*)arg3;
	float randVal;
	
	// Early exit if global flag is set
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Check if data2[0] == data1[3]
	if (data2[0] == data1[3]) {
		// Get random float - assume RandF stores result in a member or global
		math.RandF();
		// Assume the random value is available somehow - use placeholder
		randVal = -1.0f; // Negative placeholder for now
		
		// Check flag at offset 0x18 in data2
		if (*(unsigned char*)((char*)data2 + 0x18) != 0) {
			math.RandF();
			float randVal2 = -1.0f; // Second random placeholder
			randVal = (randVal - randVal2) * lbl_8032FF68; // 2.0f
		}
		
		// Get base pointer from data3[3] and store result
		void** data3_ptr = (void**)&data3[3];
		void* base = *data3_ptr;
		int base_offset = *((int*)base);
		float* resultPtr = (float*)((char*)data1 + base_offset + 0x80);
		*resultPtr = randVal;
		return;
	}
	
	// Get base address for vector operations
	void* addr_base;
	if (data2[1] == -1) {
		addr_base = &lbl_801EADC8[0];
	} else {
		int offset = data2[1] + 0x80;
		addr_base = (char*)data1 + offset;
	}
	
	// Process vector component operations
	int sourceVal = data2[2]; // Get value from offset 8
	
	// Convert signed integer to float with bias adjustment
	float signedVal = (float)((int)(sourceVal ^ 0x80000000)) - (float)lbl_8032FF70;
	
	// Get current component value from addr_base
	float currentVal = *((float*)addr_base);
	
	// Multiply and convert back to int
	float result = signedVal * currentVal;
	int resultInt = (int)result;
	
	// Store back to source array
	*((int*)addr_base) += resultInt;
	
	// Process Y component
	sourceVal = data2[3]; // Get value from offset 0xc
	signedVal = (float)((int)(sourceVal ^ 0x80000000)) - (float)lbl_8032FF70;
	currentVal = *((float*)((char*)addr_base + 4));
	result = signedVal * currentVal;
	resultInt = (int)result;
	*((int*)((char*)addr_base + 4)) += resultInt;
	
	// Process Z component  
	sourceVal = data2[4]; // Get value from offset 0x10
	signedVal = (float)((int)(sourceVal ^ 0x80000000)) - (float)lbl_8032FF70;
	currentVal = *((float*)((char*)addr_base + 8));
	result = signedVal * currentVal;
	resultInt = (int)result;
	*((int*)((char*)addr_base + 8)) += resultInt;
}