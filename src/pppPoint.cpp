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
	// Direct access pattern to match assembly
	float* dst = (float*)((char*)b->ptr + 0x80);
	
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
	
	// ID comparison from assembly pattern - b->id vs c->id  
	if (b->id != c->id) {
		return;
	}
	
	// Direct access to c->ptr + 0x80 
	float* dst = (float*)((char*)c->ptr + 0x80);
	
	// Vector addition from b->values
	dst[0] += b->values[1]; // x from values[1]
	dst[1] += b->values[1]; // y from values[1] (reused)
	dst[2] += b->values[1]; // z from values[1] (reused)
}
