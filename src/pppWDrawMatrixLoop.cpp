#include "ffcc/pppWDrawMatrixLoop.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern "C" {
extern unsigned char* lbl_8032ED50;
extern Mtx ppvCameraMatrix02;
}

/*
 * --INFO--
 * PAL Address: 0x800c4dd8
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrixLoop(_pppPObject* object, void*, _pppCtrlTable*)
{
    char* base = (char*)object;

    PSMTXConcat(ppvCameraMatrix02, *(Mtx*)(base + 0x10), *(Mtx*)(base + 0x40));

    PSVECScale((Vec*)(base + 0x40), (Vec*)(base + 0x40), *(float*)(lbl_8032ED50 + 0x28));
    PSVECScale((Vec*)(base + 0x50), (Vec*)(base + 0x50), *(float*)(lbl_8032ED50 + 0x2c));
    PSVECScale((Vec*)(base + 0x60), (Vec*)(base + 0x60), *(float*)(lbl_8032ED50 + 0x30));
}
