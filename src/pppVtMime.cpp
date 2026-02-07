#include "ffcc/pppVtMime.h"

/*
 * --INFO--
 * PAL Address: 800652d0
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMime(void* param1, void* param2, void* param3)
{
	// Get data structure from param3 and param1
	void** dataPtr = (void**)((char*)param3 + 0xC);
	void* data = *dataPtr;
	void* dataBase = *(void**)data;
	
	// Calculate offset and get target structure  
	char* target = (char*)param1 + (int)dataBase + 0x80;
	
	// Check if global flag is set (early return if not zero)
	extern int lbl_8032ED70;
	if (lbl_8032ED70 != 0) return;
	
	// Add values from target structure (looks like accumulation)
	float* targetFloats = (float*)target;
	targetFloats[1] += targetFloats[2];  // f1 + f0 -> f1  
	targetFloats[0] += targetFloats[1];  // f1 + f0 -> f0
	
	// Get values from param2 and add to target
	int* param2Ints = (int*)param2;
	if (param2Ints[0] == *(int*)((char*)param1 + 0xC)) {
		float* param2Floats = (float*)param2;
		targetFloats[0] += param2Floats[3];  // param2[0xC] -> target[0x0]
		targetFloats[1] += param2Floats[4];  // param2[0x10] -> target[0x4] 
		targetFloats[2] += param2Floats[5];  // param2[0x14] -> target[0x8]
	}
}

/*
 * --INFO--
 * PAL Address: 800650ec
 * PAL Size: 484b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawVtMime(void* param1, void* param2, void* param3)
{
	// Clear result pointer
	*(void**)((char*)param1 + 0x70) = 0;
	
	// Check validity of vertex data indices
	int vertIdx1 = *(int*)((char*)param2 + 0x4);
	int vertIdx2 = *(int*)((char*)param2 + 0x8);
	
	if ((vertIdx1 & 0xFFFF0000) == 0xFFFF0000) return;
	if ((vertIdx2 & 0xFFFF0000) == 0xFFFF0000) return;
	
	// Get data structures
	void** dataPtr = (void**)((char*)param3 + 0xC);
	void* data = *dataPtr;
	void* dataBase = *(void**)data;
	char* target = (char*)param1 + (int)dataBase + 0x80;
	
	// Get global vertex data pointers
	extern void* lbl_8032ED54;
	void* globalData = *(void**)((char*)lbl_8032ED54 + 0x8);
	
	// Get vertex data for interpolation
	void* vert1Data = *(void**)((char*)globalData + (vertIdx1 * 4));
	void* vert2Data = *(void**)((char*)globalData + (vertIdx2 * 4));
	
	float* vert1Pos = (float*)((char*)vert1Data + 0x2C);
	float* vert2Pos = (float*)((char*)vert2Data + 0x2C);
	
	short vertCount = *(signed short*)vert1Data;
	
	// Check if memory needs allocation
	void** memPtr = (void**)((char*)target + 0xC);
	if (*memPtr == 0) {
		// Allocate memory for vertex data
		extern void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long size, void* stage, char* info, int param);
		extern void* lbl_8032ED54;
		void* stage = *(void**)lbl_8032ED54;
		
		*memPtr = pppMemAlloc__FUlPQ27CMemory6CStagePci(vertCount * 0xC, stage, "Unknown", 0x2B);
	}
	
	// Perform vertex interpolation
	if (vertCount > 0) {
		float* outputVerts = (float*)*memPtr;
		float interpFactor = *(float*)target;
		
		// Loop through vertices and interpolate
		int i;
		for (i = 0; i < vertCount; i++) {
			// Interpolate X, Y, Z coordinates
			float v1X = vert1Pos[i * 6 + 0];
			float v2X = vert2Pos[i * 6 + 0];
			outputVerts[i * 3 + 0] = v1X + interpFactor * (v2X - v1X);
			
			float v1Y = vert1Pos[i * 6 + 1];
			float v2Y = vert2Pos[i * 6 + 1];
			outputVerts[i * 3 + 1] = v1Y + interpFactor * (v2Y - v1Y);
			
			float v1Z = vert1Pos[i * 6 + 2];
			float v2Z = vert2Pos[i * 6 + 2];
			outputVerts[i * 3 + 2] = v1Z + interpFactor * (v2Z - v1Z);
		}
		
		// Flush data cache
		extern void DCFlushRange(void* ptr, unsigned long size);
		DCFlushRange(*memPtr, vertCount * 0xC);
	}
	
	// Set result pointer
	*(void**)((char*)param1 + 0x70) = *memPtr;
}

/*
 * --INFO--
 * PAL Address: 800650c0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeCon(void* param1, void* param2, void* param3)
{
	// Get data structure from param2 and param1
	void** dataPtr = (void**)((char*)param2 + 0xC);
	void* data = *dataPtr;
	void* dataBase = *(void**)data;
	
	// Calculate offset and get target structure  
	char* target = (char*)param1 + (int)dataBase + 0x80;
	
	// Initialize three consecutive float values to 0.0f
	*(float*)((char*)target + 0x0) = 0.0f;
	*(float*)((char*)target + 0x4) = 0.0f;
	*(float*)((char*)target + 0x8) = 0.0f;
	
	// Also set integer value at offset 0xC to 0
	*(int*)((char*)target + 0xC) = 0;
}

/*
 * --INFO--
 * PAL Address: 8006509c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeCon2(void* param1, void* param2, void* param3)
{
	// Get data structure from param2 and param1
	void** dataPtr = (void**)((char*)param2 + 0xC);
	void* data = *dataPtr;
	void* dataBase = *(void**)data;
	
	// Calculate offset and get target structure  
	char* target = (char*)param1 + (int)dataBase + 0x80;
	
	// Initialize three consecutive float values to 0.0f
	*(float*)((char*)target + 0x0) = 0.0f;
	*(float*)((char*)target + 0x4) = 0.0f;
	*(float*)((char*)target + 0x8) = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 80065034
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVtMimeDes(void* param1, void* param2)
{
	// Get data structure from param2
	void** dataPtr = (void**)((char*)param2 + 0xC);
	void* data = *dataPtr;
	void* dataBase = *(void**)data;
	
	// Calculate target offset and check memory allocation
	int offset = (int)dataBase + 0x80 + 0xC; // Direct offset calculation
	void** memPtr = (void**)((char*)param1 + offset);
	
	// Check if memory is allocated
	if (*memPtr != 0) {
		// Graphics wait and memory cleanup
		extern void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
		extern void* Graphic;
		_WaitDrawDone__8CGraphicFPci(Graphic, "Unknown", 0x50);
		
		// Heap usage reporting
		extern void pppHeapUseRate__FPQ27CMemory6CStage(void*);
		pppHeapUseRate__FPQ27CMemory6CStage(*memPtr);
		
		// Clear the pointer
		*memPtr = 0;
	}
}
