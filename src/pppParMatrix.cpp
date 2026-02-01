#include "ffcc/pppParMatrix.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	108
 */
void pppParMatrix(int param)
{
	Vec local_vec;
	int* matrix_ptr = *(int**)(param + 4);
	
	local_vec.x = *(f32*)(param + 0x1c);
	local_vec.y = *(f32*)(param + 0x2c);
	local_vec.z = *(f32*)(param + 0x3c);
	
	PSMTXMultVec((f32(*)[4])((u8*)matrix_ptr + 0x10), &local_vec, &local_vec);
	
	*(f32*)(param + 0x1c) = local_vec.x;
	*(f32*)(param + 0x2c) = local_vec.y;
	*(f32*)(param + 0x3c) = local_vec.z;
}