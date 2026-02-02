#include "ffcc/pppSDrawMatrix.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * --INFO--
 * PAL Address: 0x800d25e0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSDrawMatrix(_pppPObject* obj)
{
	// Based on assembly analysis: PSMTXConcat(&ppvCameraMatrix0, obj+0x10, obj+0x40)
	// The offsets suggest a different struct layout than expected
	PSMTXConcat(ppvCameraMatrix0, 
	           *(Mtx*)((u8*)obj + 0x10), 
	           *(Mtx*)((u8*)obj + 0x40));
}

#ifdef __cplusplus
}
#endif