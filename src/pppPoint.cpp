#include "ffcc/pppPoint.h"
#include <stddef.h>

// Global state - assembly shows access to static data 
static int pppPointEnabled = 0;
static PppData* gPppData1 = NULL;
static PppData* gPppData2 = NULL; 
static PppData* gPppCtx = NULL;

/*
 * --INFO--
 * PAL Address: 0x80065cfc
 * PAL Size: 96b
 */
void pppPoint(void)
{
	if (pppPointEnabled == 0) {
		return;
	}
	
	if (!gPppData1 || !gPppData2 || !gPppCtx) {
		return;
	}
	
	// ID comparison from assembly pattern 
	if (gPppData1->id != gPppCtx->id) {
		return;
	}
	
	// Vector addition pattern from assembly
	float* src = &gPppData1->values[2]; // offset 0x8 (z component)
	float* dst = (float*)((char*)gPppCtx->ptr + 0x80); // offset +0x80 from pointer
	
	dst[0] += src[0]; // x
	dst[1] += src[1]; // y  
	dst[2] += src[2]; // z
}

/*
 * --INFO--
 * PAL Address: 0x80065cd8
 * PAL Size: 36b
 */
void pppPointCon(void)
{
	if (!gPppData2 || !gPppCtx) {
		return;
	}
	
	// Load 0.0f constant and initialize vector
	float zero = 0.0f;
	float* dst = (float*)((char*)gPppCtx->ptr + 0x80);
	
	dst[0] = zero; // x
	dst[1] = zero; // y
	dst[2] = zero; // z
}
