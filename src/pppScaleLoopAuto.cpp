#include "ffcc/pppScaleLoopAuto.h"

/*
 * --INFO--
 * PAL Address: 0x8012b4f4
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAuto(void* arg1, void* arg2, void* arg3)
{
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	int** arg3Data = (int**)arg3;
	int* arg2Data = (int*)arg2;
	int* arg1Data = (int*)arg1;
	
	// Load first data pointer and check condition
	int* data1 = arg3Data[0];
	if (arg2Data[0] == arg1Data[3]) {
		// Calculate pointer and add values
		float* ptr1 = (float*)((char*)arg1 + (int)data1 + 0x80);
		ptr1[0] += ((float*)arg2)[2];
		ptr1[1] += ((float*)arg2)[3];
		ptr1[2] += ((float*)arg2)[4];
	}
	
	// Load scale data pointer
	int* data3 = arg3Data[3];
	int* data3_ptr = (int*)data3[0];
	float* scaleData = (float*)((char*)arg1 + (int)data3_ptr + 0x80);
	char* scaleBytes = (char*)scaleData;
	
	// Check if initialization needed
	if (scaleBytes[28] == 0) {
		scaleBytes[28] = 1;
		scaleData[4] = scaleData[0];
		scaleData[5] = scaleData[1];
		scaleData[6] = scaleData[2];
		scaleBytes[32] = ((char*)arg2)[29];
		scaleBytes[33] = ((char*)arg2)[30];
		return;
	}
	
	short angle = *(short*)(scaleBytes + 30);
	if (angle < 90) {
		signed char counter = scaleBytes[32];
		if (counter > 0) {
			scaleBytes[32] = counter - 1;
			float delta = scaleData[9];
			scaleData[0] += delta;
			scaleData[1] += delta;
			scaleData[2] += delta;
		}
	} else if (angle < 270) {
		signed char counter = scaleBytes[33];
		if (counter > 0) {
			scaleBytes[33] = counter - 1;
			float delta = scaleData[9];
			scaleData[0] += delta;
			scaleData[1] += delta;
			scaleData[2] += delta;
		}
	} else {
		scaleBytes[29]++;
		unsigned char cycleLimit = ((char*)arg2)[28];
		if (scaleBytes[29] >= cycleLimit) {
			scaleBytes[29] = 0;
			*(short*)(scaleBytes + 30) = 0;
			scaleBytes[32] = ((char*)arg2)[29];
			scaleBytes[33] = ((char*)arg2)[30];
		} else {
			// Calculate angle increment and sine lookup
			int angleIncrement = 360 / cycleLimit;
			angle += angleIncrement;
			*(short*)(scaleBytes + 30) = angle;
			
			// Sine table lookup and scaling
			extern float lbl_801EC9F0[];
			int tableIndex = (angle * 32768) / 360;
			float sine = lbl_801EC9F0[(tableIndex & 0x3FFC) >> 2];
			
			float baseScale = ((float*)arg2)[6];
			float scaleRange = ((float*)arg2)[8];
			float delta = baseScale * sine * scaleRange;
			
			scaleData[9] = delta;
			scaleData[0] += delta;
			scaleData[1] += delta;
			scaleData[2] += delta;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012b4a8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAutoCon(void* arg1, void* arg2)
{
	int** arg2Data = (int**)arg2;
	int* data = arg2Data[3];
	int* ptr = (int*)data[0];
	
	float* targetData = (float*)((char*)arg1 + (int)ptr + 0x80);
	char* targetBytes = (char*)targetData;
	
	// Initialize float values
	targetData[0] = 0.0f;
	targetData[1] = 0.0f;
	targetData[2] = 0.0f;
	targetData[4] = 0.0f;
	targetData[5] = 0.0f;
	targetData[6] = 0.0f;
	targetData[9] = 0.0f;
	
	// Initialize byte values
	targetBytes[28] = 0;
	targetBytes[29] = 0;
	targetBytes[30] = 0;
	targetBytes[31] = 0;
	targetBytes[32] = 0;
	targetBytes[33] = 0;
}