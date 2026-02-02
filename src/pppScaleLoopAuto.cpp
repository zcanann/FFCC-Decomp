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
	
	int* arg2Data = (int*)arg2;
	int* arg3Data0 = (int*)((int**)arg3)[0];
	int* arg1Data = (int*)arg1;
	
	// Check condition for first operation
	if (arg2Data[0] == arg1Data[3]) {
		float* targetPtr = (float*)((char*)arg1 + (int)arg3Data0 + 0x80);
		float* arg2Float = (float*)arg2;
		targetPtr[0] += arg2Float[2];
		targetPtr[1] += arg2Float[3];
		targetPtr[2] += arg2Float[4];
	}
	
	// Load scale data structure
	int** arg3Ptrs = (int**)arg3;
	int* scaleDataPtr = (int*)arg3Ptrs[3][0];
	char* scaleTarget = (char*)arg1 + (int)scaleDataPtr + 0x80;
	float* scaleData = (float*)scaleTarget;
	
	// Check initialization flag
	if (scaleTarget[28] == 0) {
		scaleTarget[28] = 1;
		scaleData[4] = scaleData[0];
		scaleData[5] = scaleData[1];
		scaleData[6] = scaleData[2];
		scaleTarget[32] = ((char*)arg2)[29];
		scaleTarget[33] = ((char*)arg2)[30];
		return;
	}
	
	short currentAngle = *(short*)(scaleTarget + 30);
	if (currentAngle < 90) {
		signed char counter = scaleTarget[32];
		if (counter > 0) {
			scaleTarget[32] = counter - 1;
			float deltaValue = scaleData[9];
			scaleData[0] += deltaValue;
			scaleData[1] += deltaValue;
			scaleData[2] += deltaValue;
		}
		return;
	}
	
	if (currentAngle < 270) {
		signed char counter = scaleTarget[33];
		if (counter > 0) {
			scaleTarget[33] = counter - 1;
			float deltaValue = scaleData[9];
			scaleData[0] += deltaValue;
			scaleData[1] += deltaValue;
			scaleData[2] += deltaValue;
		}
		return;
	}
	
	// Handle cycle completion
	scaleTarget[29]++;
	unsigned char cycleLimit = ((char*)arg2)[28];
	signed char currentCycle = scaleTarget[29];
	if ((unsigned char)currentCycle >= cycleLimit) {
		scaleTarget[29] = 0;
		*(short*)(scaleTarget + 30) = 0;
		scaleTarget[32] = ((char*)arg2)[29];
		scaleTarget[33] = ((char*)arg2)[30];
		return;
	}
	
	// Calculate angle increment and update angle
	int angleIncrement = 360 / (int)cycleLimit;
	currentAngle += angleIncrement;
	*(short*)(scaleTarget + 30) = currentAngle;
	
	// Advanced sine table lookup using fixed-point arithmetic
	extern float lbl_801EC9F0[];
	int angleScaled = currentAngle * 32768;
	int angleNormalized = angleScaled / 360;
	int tableLookup = (angleNormalized & 0x3FFC) >> 2;
	float sineValue = lbl_801EC9F0[tableLookup];
	
	float baseScale = ((float*)arg2)[6];
	float scaleRange = ((float*)arg2)[8];
	float scaleFactor = baseScale * sineValue * scaleRange;
	
	scaleData[9] = scaleFactor;
	scaleData[0] += scaleFactor;
	scaleData[1] += scaleFactor;
	scaleData[2] += scaleFactor;
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
	
	void* targetPtr = (void*)((char*)arg1 + (int)ptr + 0x80);
	float* targetData = (float*)targetPtr;
	char* targetBytes = (char*)targetPtr;
	
	// Initialize float values to 0.0f
	targetData[0] = 0.0f;
	targetData[1] = 0.0f;
	targetData[2] = 0.0f;
	targetData[4] = 0.0f;
	targetData[5] = 0.0f;
	targetData[6] = 0.0f;
	targetData[9] = 0.0f;
	
	// Initialize byte values to 0
	targetBytes[28] = 0;
	targetBytes[29] = 0;
	targetBytes[30] = 0;
	targetBytes[31] = 0;
	targetBytes[32] = 0;
	targetBytes[33] = 0;
}