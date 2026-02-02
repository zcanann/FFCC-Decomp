#include "ffcc/pppDrawMdlTs.h"

/*
 * --INFO--
 * PAL Address: 0x800880c0
 * PAL Size: 48b
 */
void pppDrawMdlTsCon(struct _pppPObject* obj, struct PDrawMdlTs* data)
{
    // Access nested structure: data->field_at_0xc->field_at_0x8 + 0x80
    void* inner = *((void**)((char*)data + 0xc));
    void* inner2 = *((void**)((char*)inner + 0x8));
    float* texCoords = (float*)((char*)obj + (int)inner2 + 0x80);
    
    // Initialize all 6 texture coordinates to 0.0
    texCoords[0] = 0.0f; // offset 0x0
    texCoords[1] = 0.0f; // offset 0x4  
    texCoords[2] = 0.0f; // offset 0x8
    texCoords[3] = 0.0f; // offset 0xc
    texCoords[4] = 0.0f; // offset 0x10
    texCoords[5] = 0.0f; // offset 0x14
}

/*
 * --INFO--
 * PAL Address: 0x800880a0  
 * PAL Size: 32b
 */
void pppDrawMdlTsCon3(struct _pppPObject* obj, struct PDrawMdlTs* data)
{
    // Access nested structure: data->field_at_0xc->field_at_0x8 + 0x80
    void* inner = *((void**)((char*)data + 0xc));
    void* inner2 = *((void**)((char*)inner + 0x8));  
    float* texCoords = (float*)((char*)obj + (int)inner2 + 0x80);
    
    // Initialize specific texture coordinates to 0.0
    texCoords[2] = 0.0f; // offset 0x8  
    texCoords[5] = 0.0f; // offset 0x14
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMdlTs(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawDrawMdlTs0(_pppPObject*, PDrawMdlTs*, _pppCtrlTable*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawDrawMdlTs(void)
{
	// TODO
}
