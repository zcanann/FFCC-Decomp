#include "ffcc/pppRandUpHCV.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern "C" void randshort(short, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80062B18
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandUpHCV(void* param1, void* param2, void* param3)
{
	// Assembly shows r30=param1, r31=param2, r29=param3
	// Check global state - similar to other ppp* functions
	// Access character data at various offsets
	
	// Get random values for character attribute modification  
	math.RandF(); // Generate random - stored in math object state
	math.RandF(); // Generate second random value
	
	// Character data access patterns from assembly:
	// param2+0x0, param2+0x4, param2+0x8, param2+0xa, param2+0xc, param2+0xe, param2+0x10
	// param1+0xc (character data index)
	// param3+0xc -> +0x0 (object data access)
	
	// Complex floating-point calculations for attribute randomization
}