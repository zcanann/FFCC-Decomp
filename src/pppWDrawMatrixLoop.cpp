#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

/*
 * --INFO--
 * PAL Address: 0x800c4dd8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixLoop(_pppPObject* param_1)
{
    char* base = (char*)param_1;

    PSMTXConcat(ppvCameraMatrix0, *(Mtx*)(base + 0x4), *(Mtx*)(base + 0x38));
    PSVECScale((Vec*)(base + 0x40), (Vec*)(base + 0x40), *(float*)((char*)pppMngStPtr + 0x64));
    PSVECScale((Vec*)(base + 0x50), (Vec*)(base + 0x50), *(float*)((char*)pppMngStPtr + 0x68));
    PSVECScale((Vec*)(base + 0x60), (Vec*)(base + 0x60), *(float*)((char*)pppMngStPtr + 0x6c));
}
