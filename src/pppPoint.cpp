#include "ffcc/pppPoint.h"

/*
 * --INFO--
 * PAL Address: 0x80065cfc
 * PAL Size: 96b
 */
void pppPoint(void* obj, void* param1, void* param2)
{
	// Check global flag first
	extern int lbl_8032ED70; // Global flag
	if (lbl_8032ED70 != 0) {
		return;
	}
	
	// Check object IDs match
	int param1_id = *((int*)param1);
	int obj_id = *((int*)((char*)obj + 0x0c));
	if (param1_id != obj_id) {
		return;
	}
	
	// Get position data structures
	void* param2_data = *((void**)((char*)param2 + 0x0c));
	int position_offset = *((int*)param2_data);
	float* obj_position = (float*)((char*)obj + position_offset + 0x80);
	
	// Add position deltas (x, y, z)
	float* param1_deltas = (float*)((char*)param1 + 0x08);
	
	obj_position[0] += param1_deltas[0]; // x
	obj_position[1] += param1_deltas[1]; // y  
	obj_position[2] += param1_deltas[2]; // z
}

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 */
void pppPointCon(void* obj, void* param)
{
	// Get structure pointer and offset to position data
	void* data = *((void**)((char*)param + 0x0c));
	int offset = *((int*)data);
	float* position = (float*)((char*)obj + offset + 0x80);
	
	// Initialize position vector to zero (in reverse order to match assembly)
	position[2] = 0.0f; // z
	position[1] = 0.0f; // y
	position[0] = 0.0f; // x
}