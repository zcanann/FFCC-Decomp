#include "ffcc/pppSDrawMatrix.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"

#ifdef __cplusplus
extern "C" {
extern Mtx ppvCameraMatrix02;
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
void pppSDrawMatrix(_pppPObject* object, void*, _pppCtrlTable*)
{
	PSMTXConcat(ppvCameraMatrix02,
	           *(Mtx*)((u8*)object + 0x10),
	           *(Mtx*)((u8*)object + 0x40));
}

#ifdef __cplusplus
}
#endif
