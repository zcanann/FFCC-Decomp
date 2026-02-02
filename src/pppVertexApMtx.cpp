#include "ffcc/pppVertexApMtx.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx)
{
	// Initialize vertex matrix state to zero
	int* vtx_base = (int*)((char*)vtx + 0xc);
	int* data_base = (int*)*vtx_base;
	int offset = (int)data_base + 0x80;
	char* ptr = (char*)obj + offset;
	*(short*)ptr = 0;
	*(short*)(ptr + 2) = 0;
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
