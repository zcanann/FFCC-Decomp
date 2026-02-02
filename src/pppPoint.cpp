#include "ffcc/pppPoint.h"

// Based on assembly analysis - these seem to be accessed as parameters but stored globally
static int pppPointEnabled = 0;

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 */
void pppPointCon(PppData* a, PppData* b)
{
	// Assembly shows access to b->ptr + 0x80, stores 0.0f constants
	void* ptr = b->ptr;
	float* dst = (float*)((char*)ptr + 0x80);
	
	dst[0] = 0.0f; // x
	dst[1] = 0.0f; // y
	dst[2] = 0.0f; // z
}

/*
 * --INFO--
 * PAL Address: 0x80065cfc
 * PAL Size: 96b
 */
void pppPoint(PppData* a, PppData* b, PppData* c)
{
	// Original checks some global enabled state first
	if (pppPointEnabled == 0) {
		return;
	}
	
	// ID comparison from assembly pattern - a->id vs c->id  
	if (b->id != c->id) {
		return;
	}
	
	// Assembly shows access to c->ptr + 0x80 
	void* ptr = c->ptr;
	float* dst = (float*)((char*)ptr + 0x80);
	
	// Vector addition from b->values[2+] (offset 0x8)
	dst[0] += b->values[2]; // x 
	dst[1] += b->values[3]; // y  
	dst[2] += b->values[2]; // z - assembly pattern shows reuse
}
