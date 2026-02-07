#include "ffcc/pppVertexApMtx.h"

/*
 * --INFO--
 * PAL Address: 0x800de6d0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx)
{
	int offset = **(int**)((char*)vtx + 0xc);
	char* target = (char*)obj + offset + 0x80;

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
