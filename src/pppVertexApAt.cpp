#include "ffcc/pppVertexApAt.h"
#include "ffcc/math.h"

extern CMath math;
extern struct _pppMngSt* lbl_8032ED50;
extern int lbl_8032ED70;
extern double lbl_803300E0;

struct _pppPDataVal;
_pppPObject* pppCreatePObject(struct _pppMngSt*, struct _pppPDataVal*);

/*
 * --INFO--
 * PAL Address: 0x80064cc8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAtCon(_pppPObject* obj, PVertexApAt* data)
{
	void* dataPtr = *(void**)((char*)data + 0xc);
	int baseOffset = *(int*)dataPtr;
	void* targetPtr = (char*)obj + baseOffset + 0x80;
	
	*(short*)targetPtr = 0;
	*((short*)targetPtr + 1) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apea(_pppPObject*, PVertexApAt*, unsigned short)
{
	// Empty function
}

/*
 * --INFO--
 * PAL Address: 0x80064b08
 * PAL Size: 448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApAt(_pppPObject* obj, PVertexApAt* data, void* param3)
{
	// Based on objdiff analysis - basic structure with proper memory access
	void* dataPtr = *(void**)((char*)data + 0xc);
	void* basePtr = *(void**)dataPtr;
	void* targetPtr = (char*)obj + (int)basePtr + 0x80;
	
	// Check global flag (assembly shows bne to end if 0)
	if (lbl_8032ED70 == 0) {
		// Early return path - sets final timer value and decrements
		goto end_function;
	}
	
	// Check input validation
	short inputValue = *(short*)((char*)data + 0x4);
	if (inputValue < 0) return;
	
	// Check if already active
	unsigned short activeFlag = *(unsigned short*)((char*)targetPtr + 0x2);
	if (activeFlag != 0) return;
	
	// Get loop count and mode
	unsigned char loopCount = *(unsigned char*)((char*)data + 0x6);
	unsigned char mode = *(unsigned char*)((char*)data + 0x8);
	
	// Mode-based processing (assembly shows beq/bge branching)
	if (mode == 1) {
		// Mode 1: simpler processing
		for (unsigned char i = 0; i < loopCount; i++) {
			// Call random function (assembly shows math calls)
			math.RandF();
			
			// Check data validity
			int testValue = *(int*)((char*)data + 0xc);
			if ((testValue + 1) == 0xFFFF) continue;
			
			// Create object if conditions met
			_pppPObject* newObj = pppCreatePObject(lbl_8032ED50, (struct _pppPDataVal*)param3);
			if (newObj == 0) continue;
			
			// Set parent reference
			*(void**)((char*)newObj + 0x4) = obj;
			
			// Update vertex count
			short count = *(short*)((char*)targetPtr + 0x0);
			count++;
			*(short*)((char*)targetPtr + 0x0) = count;
			
			// Store vertex data
			void* targetData = *(void**)((char*)data + 0x10);
			*(short*)((char*)newObj + (int)targetData + 0x80) = count;
		}
	} else {
		// Mode 0/other: complex random vertex generation
		for (unsigned char i = 0; i < loopCount; i++) {
			// Generate random value with floating point conversion
			math.RandF();
			
			// Get range from param3
			short range = *(short*)((char*)param3 + 0x2);
			
			// Check data validity
			int testValue = *(int*)((char*)data + 0xc);
			if ((testValue + 1) == 0xFFFF) continue;
			
			// Create particle object
			_pppPObject* newObj = pppCreatePObject(lbl_8032ED50, (struct _pppPDataVal*)param3);
			if (newObj == 0) continue;
			
			// Set parent reference
			*(void**)((char*)newObj + 0x4) = obj;
			
			// Store computed vertex index
			void* targetData = *(void**)((char*)data + 0x10);
			*(short*)((char*)newObj + (int)targetData + 0x80) = range; // Simplified for now
		}
	}

end_function:
	// Set final countdown value from data
	unsigned char countdown = *(unsigned char*)((char*)data + 0x7);
	*(short*)((char*)targetPtr + 0x2) = countdown;
	
	// Decrement if positive (assembly shows this pattern)
	short currentTimer = *(short*)((char*)targetPtr + 0x2);
	if (currentTimer > 0) {
		*(short*)((char*)targetPtr + 0x2) = currentTimer - 1;
	}
}
