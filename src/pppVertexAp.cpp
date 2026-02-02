#include "ffcc/pppVertexAp.h"

/*
 * --INFO--
 * PAL Address: 0x80064ae8
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApCon(_pppPObject* pobj, PVertexAp* vtxAp)
{
	int* vtxApPtr = (int*)vtxAp;
	int offset = vtxApPtr[3]; // 0xc offset (12 bytes / 4 = index 3)
	int* basePtr = (int*)offset;
	short* ptr = (short*)((char*)pobj + *basePtr + 0x80);
	ptr[0] = 0;
	ptr[1] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void apea(_pppPObject*, PVertexAp*, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppVertexAp(void)
{
	// TODO
}
