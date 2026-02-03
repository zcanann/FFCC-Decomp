#include "ffcc/pppVertexApMtx.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx)
{
	// Get base address from vtx offset 0xc
	char* base = *(char**)((char*)vtx + 0xc);
	// Calculate final address: obj + base + 0x80
	char* target = (char*)obj + (int)base + 0x80;
	// Zero out two shorts at the target location
	*(short*)target = 0;
	*(short*)(target + 2) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apea(_pppPObject*, PVertexApMtx*, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexApMtx(void)
{
	// TODO
}
