#include "ffcc/pppVertexApAt.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexApAtCon(_pppPObject* obj, PVertexApAt* data)
{
	// Based on assembly: lwz r4, 0xc(r4) -> lwz r4, 0x0(r4) -> addi r4, r4, 0x80 -> add r4, r3, r4
	void* dataPtr = *(void**)((char*)data + 0xc);
	int baseOffset = *(int*)dataPtr;
	void* targetPtr = (char*)obj + baseOffset + 0x80;
	
	*(short*)targetPtr = 0;
	*((short*)targetPtr + 1) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apea(_pppPObject*, PVertexApAt*, unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexApAt(_pppPObject* obj, PVertexApAt* data, void* param3)
{
	// Complex function with loops and randomization - placeholder for now
}
