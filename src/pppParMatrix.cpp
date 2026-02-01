#include "ffcc/pppParMatrix.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x80065b18
 * PAL Size: 108b
 */
void pppParMatrix(void* obj)
{
	Vec local_vec;
	
	// Load vector components from object
	local_vec.x = *(f32*)((char*)obj + 0x1c);
	local_vec.y = *(f32*)((char*)obj + 0x2c);  
	local_vec.z = *(f32*)((char*)obj + 0x3c);
	
	// Get matrix from object and multiply vector
	Mtx* matrix = (Mtx*)(*(void**)((char*)obj + 4) + 0x10);
	PSMTXMultVec(*matrix, &local_vec, &local_vec);
	
	// Store results back to object
	*(f32*)((char*)obj + 0x1c) = local_vec.x;
	*(f32*)((char*)obj + 0x2c) = local_vec.y;
	*(f32*)((char*)obj + 0x3c) = local_vec.z;
}