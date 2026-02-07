#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800905dc
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrix(_pppPObject* pppPObject)
{
    register char* p = (char*)pppPObject;

    PSMTXConcat(ppvCameraMatrix0, *(Mtx*)(p + 0x10), *(Mtx*)(p + 0x40));
    PSVECScale((Vec*)(p + 0x40), (Vec*)(p + 0x40),
               *(float*)((char*)pppMngStPtr + 0x28));
    PSVECScale((Vec*)(p + 0x50), (Vec*)(p + 0x50),
               *(float*)((char*)pppMngStPtr + 0x2c));
    PSVECScale((Vec*)(p + 0x60), (Vec*)(p + 0x60),
               *(float*)((char*)pppMngStPtr + 0x30));
}
