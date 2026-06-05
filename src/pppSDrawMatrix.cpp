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
void pppSDrawMatrix(_pppPObject* object, pppNoStep*, _pppCtrlTable*)
{
	PSMTXConcat(ppvCameraMatrix,
	           object->m_localMatrix.value,
	           object->m_drawMatrix.value);
}

#ifdef __cplusplus
}
#endif
