#include "ffcc/pppYmTraceMove.h"
#include "dolphin/mtx.h"

extern "C" {
	// Forward declarations for ppp vector functions
	void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
	void pppSubVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
}

/*
 * --INFO--
 * PAL Address: 800d4bd0
 * PAL Size: 172b
 */
void pppConstructYmTraceMove(void)
{
	// Vector initialization and manipulation based on Ghidra decomp patterns
	Vec local_38, local_2c, dest;
	Vec temp1, temp2, temp3;
	
	// Initialize saved position vectors
	local_2c.x = 0.0f;
	local_2c.y = 0.0f; 
	local_2c.z = 0.0f;
	
	// Initialize param vectors
	temp1.x = 1.0f;
	temp1.y = 1.0f;
	temp1.z = 1.0f;
	
	// Vector subtraction operation 
	pppSubVector__FR3Vec3Vec3Vec(&dest, &temp1, &local_2c);
	
	// Copy operations
	local_38.x = dest.x;
	local_38.y = dest.y;
	local_38.z = dest.z;
	
	pppCopyVector__FR3Vec3Vec(&dest, &local_38);
	
	// Float constant assignments like in decomp
	dest.x = 0.0f;
	dest.y = 0.0f;
	dest.z = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 800d4828  
 * PAL Size: 936b
 */
void pppFrameYmTraceMove(void)
{
	// Frame processing - basic framework with some vector operations
	Vec local_128, local_11c, local_98, local_8c;
	Vec local_2c, local_20;
	
	// Basic vector initialization patterns
	local_128.x = 0.0f;
	local_128.y = 0.0f;
	local_128.z = 0.0f;
	
	local_8c.x = 1.0f;
	local_8c.y = 1.0f; 
	local_8c.z = 1.0f;
	
	// Vector copy operations like in Ghidra decomp
	pppCopyVector__FR3Vec3Vec(&local_20, &local_8c);
	
	local_98.x = 0.0f;
	local_98.y = 0.0f;
	local_98.z = 1.0f;
	
	pppCopyVector__FR3Vec3Vec(&local_2c, &local_98);
}
