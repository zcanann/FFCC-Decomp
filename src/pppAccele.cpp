#include "ffcc/pppAccele.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppAccele(void)
{
	// TODO
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