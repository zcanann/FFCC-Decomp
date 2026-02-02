#include "ffcc/pppRandCV.h"
#include "ffcc/math.h"

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 */
void randchar(char range, float factor)
{
	// Helper function for random character generation
	// Implementation details based on usage context
}

/*
 * --INFO--
 * PAL Address: 0x80066194
 * PAL Size: 540b
 */
void pppRandCV(void* colorArray, void* colorParams, void* entityData)
{
	// Check global disable flag
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) return;
	
	// Cast parameters to appropriate types
	int* params = (int*)colorParams;
	int* entity = (int*)entityData;
	
	// Check if color indices match
	int currentIndex = params[0];
	int targetIndex = entity[3];
	if (currentIndex != targetIndex) return;
	
	CMath math;
	
	// Generate base random float
	math.RandF();
	// Note: RandF result stored in floating point register, need proper handling
	
	// Check random flag and generate scaling factor
	unsigned char randomFlag = *((unsigned char*)params + 0xC);
	float scalingFactor;
	if (randomFlag != 0) {
		math.RandF();
		// Add random values for intensity variation
		scalingFactor = 1.0f; // Placeholder - assembly shows complex float ops
	} else {
		// Use fixed scaling when randomFlag is 0
		extern float lbl_8032FF08;
		scalingFactor = lbl_8032FF08;
	}
	
	// Get color buffer pointer based on entity data
	int colorOffset = params[1];
	unsigned char* targetColors;
	if (colorOffset == -1) {
		// Use default color array
		extern unsigned char lbl_801EADC8[];
		targetColors = lbl_801EADC8;
	} else {
		targetColors = (unsigned char*)((char*)colorArray + 0x80 + colorOffset);
	}
	
	// Process RGBA components (4 bytes)
	for (int i = 0; i < 4; i++) {
		// Get the random adjustment value for this component
		char adjustment = *((char*)params + 8 + i);
		unsigned char currentValue = targetColors[i];
		
		// Complex floating point calculation matching assembly pattern:
		// Convert signed byte to double, apply scaling, convert back
		extern double lbl_8032FF10;
		double adjustmentDouble = (double)adjustment;
		double currentDouble = (double)currentValue;
		
		// fmsubs operation: multiply-subtract-single  
		double result = adjustmentDouble * scalingFactor - currentDouble;
		
		// Convert back to integer and add to current value
		int finalValue = (int)result + currentValue;
		targetColors[i] = (unsigned char)finalValue;
	}
	
	// Note: Above implementation is simplified - original assembly suggests more complex 
	// floating point operations with specific PowerPC instructions that don't map 
	// directly to C. The original likely processes components in pairs with optimized
	// floating point register usage.
}