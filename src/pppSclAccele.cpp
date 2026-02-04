#include "ffcc/pppSclAccele.h"

/*
 * --INFO--
 * PAL Address: 0x80063150
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAcceleCon(void* arg1, void* arg2)
{
	int** dataPtr = (int**)arg2;
	int* targetPtr = dataPtr[3]; // Load from offset 0xc
	
	// Calculate final pointer: arg1 + targetPtr + 0x80
	float* finalPtr = (float*)((char*)arg1 + (int)targetPtr + 0x80);
	
	// Store 0.0f to three consecutive float positions in reverse order
	finalPtr[2] = 0.0f;  // offset 0x8
	finalPtr[1] = 0.0f;  // offset 0x4  
	finalPtr[0] = 0.0f;  // offset 0x0
}

/*
 * --INFO--
 * PAL Address: 0x80063174
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAccele(void* arg1, void* arg2, void* arg3)
{
	int** dataPtr = (int**)arg3;
	int* data1 = dataPtr[0]; // Load from offset 0x0
	int* data2 = dataPtr[1]; // Load from offset 0x4
	
	// Check global flag
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Calculate final pointers: arg1 + dataPtr + 0x80
	float* ptr1 = (float*)((char*)arg1 + (int)data1 + 0x80);
	float* ptr2 = (float*)((char*)arg1 + (int)data2 + 0x80);
	
	// Get acceleration data from arg2
	int* accelData = (int*)arg2;
	int* arg1Data = (int*)arg1;
	
	// Check if first element matches
	if (accelData[0] == arg1Data[3]) {
		// Add acceleration to velocity (ptr2)
		ptr2[0] += ((float*)arg2)[2];  // X component
		ptr2[1] += ((float*)arg2)[3];  // Y component  
		ptr2[2] += ((float*)arg2)[4];  // Z component
	}
	
	// Add velocity to position (ptr1)
	ptr1[0] += ptr2[0];  // X component
	ptr1[1] += ptr2[1];  // Y component
	ptr1[2] += ptr2[2];  // Z component
}