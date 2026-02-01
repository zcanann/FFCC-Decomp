#include "ffcc/pppAccele.h"

/*
 * --INFO--
 * PAL Address: 0x80064c7c
 * PAL Size: 156b
 */
void pppAccele(void* obj, void* param2, void* param3)
{
	// Get pointers to position/velocity data from param3 offsets
	void* dataPtr = *((void**)((char*)param3 + 0x0c));
	int* offsets = (int*)((char*)dataPtr + 0x04);
	
	float* positionVector = (float*)((char*)obj + offsets[0] + 0x80);
	float* accelerationVector = (float*)((char*)obj + offsets[1] + 0x80);
	
	// Check global flag - return early if disabled
	// Note: DAT_8032ed70 appears to be a global disable flag
	// TODO: Replace with actual global variable reference
	// if (globalDisableFlag != 0) return;
	
	// Check if graph IDs match between param2 and obj
	int param2GraphId = *((int*)((char*)param2 + 0x08)); // m_graphId offset
	int objGraphId = *((int*)((char*)obj + 0x08));       // m_graphId offset
	
	if (param2GraphId == objGraphId) {
		// Add parameter values to acceleration vector
		accelerationVector[0] += (float)*((int*)((char*)param2 + 0x0c)); // m_initWOrk
		accelerationVector[1] += *((float*)((char*)param2 + 0x10));      // m_stepValue  
		accelerationVector[2] += (float)*((int*)((char*)param2 + 0x14)); // m_arg3
	}
	
	// Add acceleration to position
	positionVector[0] += accelerationVector[0];
	positionVector[1] += accelerationVector[1]; 
	positionVector[2] += accelerationVector[2];
}

/*
 * --INFO--
 * PAL Address: 0x80064c58 
 * PAL Size: 36b
 */
void pppAcceleCon(void* obj, void* param)
{
	// Get structure pointer and offset to acceleration data  
	void* data = *((void**)((char*)param + 0x0c));
	int offset = *((int*)((char*)data + 0x04));
	float* accel = (float*)((char*)obj + offset + 0x80);
	
	// Initialize acceleration vector to zero (in reverse order to match assembly)
	accel[2] = 0.0f;  // z
	accel[1] = 0.0f;  // y  
	accel[0] = 0.0f;  // x
}