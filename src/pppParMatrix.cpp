#include "ffcc/pppParMatrix.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	108
 */
void pppParMatrix(void* param)
{
	MtxPtr matrix = *(MtxPtr*)((u32)param + 0x4);
	Vec source, destination;
	
	// Load source vector from offsets 0x1c, 0x2c, 0x3c
	source.x = *(f32*)((u32)param + 0x1c);
	source.y = *(f32*)((u32)param + 0x2c);  
	source.z = *(f32*)((u32)param + 0x3c);
	
	// Multiply matrix by vector (matrix + 0x10 in assembly)
	PSMTXMultVec((f32(*)[4])((u8*)matrix + 0x10), &source, &destination);
	
	// Store result back to same offsets
	*(f32*)((u32)param + 0x1c) = destination.x;
	*(f32*)((u32)param + 0x2c) = destination.y;
	*(f32*)((u32)param + 0x3c) = destination.z;
}