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
    char* base = (char*)pppPObject;
    Mtx* worldMtx = (Mtx*)(base + 0x40);

    PSMTXConcat(ppvCameraMatrix0, *(Mtx*)(base + 0x4), *worldMtx);

    PSVECScale((Vec*)worldMtx, (Vec*)worldMtx, *(float*)((char*)pppMngStPtr + 0x64));
    PSVECScale((Vec*)(base + 0x50), (Vec*)(base + 0x50), *(float*)((char*)pppMngStPtr + 0x68));
    PSVECScale((Vec*)(base + 0x60), (Vec*)(base + 0x60), *(float*)((char*)pppMngStPtr + 0x6c));
}
