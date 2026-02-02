#include "ffcc/pppLensFlare.h"

extern float FLOAT_80331060;

/*
 * --INFO--
 * PAL Address: 0x800dec14
 * PAL Size: 72b
 */
void pppConstructLensFlare(void* obj, void* param)
{
	void* dataPtr = *((void**)((char*)param + 0x0c));
	int offset = *((int*)((char*)dataPtr + 0x08));
	
	float initValue = FLOAT_80331060;
	
	// Initialize float fields
	*((float*)((char*)obj + offset + 0x98)) = initValue;
	*((float*)((char*)obj + offset + 0x94)) = initValue;
	*((float*)((char*)obj + offset + 0x90)) = initValue;
	*((float*)((char*)obj + offset + 0xa8)) = initValue;
	*((float*)((char*)obj + offset + 0xa4)) = initValue;
	*((float*)((char*)obj + offset + 0xa0)) = initValue;
	*((float*)((char*)obj + offset + 0xb4)) = initValue;
	
	// Initialize short fields
	*((short*)((char*)obj + offset + 0xb0)) = 0;
	*((short*)((char*)obj + offset + 0xae)) = 0;
	*((short*)((char*)obj + offset + 0xac)) = 0;
	
	// Initialize byte field
	*((char*)obj + offset + 0xb2) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800dec10
 * PAL Size: 4b
 */
void pppDestructLensFlare(void)
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800de8c4
 * PAL Size: 844b
 */
void pppFrameLensFlare(void* obj, void* param2, void* param3)
{
	// TODO: Complex frame logic
	return;
}

/*
 * --INFO--
 * PAL Address: 0x800de718
 * PAL Size: 428b
 */
void pppRenderLensFlare(void* obj, void* param2, void* param3)
{
	// TODO: Complex render logic
	return;
}