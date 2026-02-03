#include "ffcc/pppPoint.h"

// Based on assembly analysis - global enabled state
static int pppPointEnabled = 0;

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 */
void pppPointCon(PppData* a, PppData* b)
{
	// Assembly shows access to b offset 0xc (which is &values[2]), then deref as pointer
	void** ptrLoc = (void**)&b->values[2];
	void* ptr = *ptrLoc;
	float* dst = (float*)((char*)ptr + 0x80);
	
	dst[0] = 0.0f; 
	dst[1] = 0.0f; 
	dst[2] = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80065cfc
 * PAL Size: 96b
 */
void pppPoint(PppData* a, PppData* b, PppData* c)
{
	// Original checks global enabled state
	if (pppPointEnabled == 0) {
		return;
	}
	
	// Compare b->id with a->values[2] (reinterpreted as int)
	if (b->id != *(int*)&a->values[2]) {
		return;
	}
	
	// Access c pointer stored at values[2] location + 0x80 offset
	void** ptrLoc = (void**)&c->values[2];
	void* ptr = *ptrLoc;
	float* dst = (float*)((char*)ptr + 0x80);
	
	// Vector addition
	dst[0] += b->values[2]; // x 
	dst[1] += b->values[3]; // y  
	dst[2] += b->values[2]; // z - reuses values[2]
}
