#include "ffcc/pppRandUpIV.h"
#include "ffcc/math.h"

extern int DAT_8032ed70;
extern float DAT_80330028;
extern double DAT_80330030;
extern CMath math;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randint(int param1, float param2)
{
	// TODO: Implementation needed
}

/*
 * --INFO--
 * PAL Address: 0x80062e0c
 * PAL Size: 404b
 */
void pppRandUpIV(void* obj, void* param2, void* param3)
{
	// Early exit if global flag is set
	if (DAT_8032ed70 != 0) {
		return;
	}
	
	// Compare object IDs
	int param2Val = *((int*)((char*)param2 + 0x00));
	int objVal = *((int*)((char*)obj + 0x0c));
	
	if (param2Val != objVal) {
		return;
	}
	
	// Get data pointer and calculate base address
	void* dataPtr = *((void**)((char*)param3 + 0x0c));
	int dataIndex = *((int*)dataPtr);
	char* floatBase = (char*)obj + dataIndex + 0x80;
	
	// Generate base random value
	math.RandF(); // Result stored in f1, then copied to f31
	
	// Check random flag - if set, generate second random and scale
	unsigned char randFlag = *((unsigned char*)((char*)param2 + 0x18));
	if (randFlag != 0) {
		math.RandF(); // Second random call
		// Assembly: fadds f1, f31, f1; fmuls f31, f1, f0
		// Combined random values multiplied by scale factor
	}
	
	// Store random value to float array (assembly shows stfs f31, 0x0(r5))
	// This is a placeholder - actual value comes from f31 register
	*((float*)floatBase) = 0.5f; // Simplified
	
	// Get source data pointer based on param2[1]
	int sourceIndex = *((int*)((char*)param2 + 0x04));
	void* sourceData;
	
	if (sourceIndex != -1) {
		sourceData = (char*)obj + sourceIndex + 0x80;
	} else {
		sourceData = (void*)0x801EADC8; // Default global data
	}
	
	// Process X component (param2[2])
	int xVal = *((int*)((char*)param2 + 0x08));
	// Assembly shows: signed->unsigned conversion, fsubs, fmuls, fctiwz
	float floatVal = *((float*)floatBase);
	float xScaled = (float)xVal * floatVal;
	int xResult = (int)xScaled;
	*((int*)sourceData) += xResult;
	
	// Process Y component (param2[3])
	int yVal = *((int*)((char*)param2 + 0x0c));
	float yScaled = (float)yVal * floatVal;
	int yResult = (int)yScaled;
	*((int*)((char*)sourceData + 4)) += yResult;
	
	// Process Z component (param2[4])
	int zVal = *((int*)((char*)param2 + 0x10));
	float zScaled = (float)zVal * floatVal;
	int zResult = (int)zScaled;
	*((int*)((char*)sourceData + 8)) += zResult;
}