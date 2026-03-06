#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern "C" float ppvCameraMatrix02[3][4];
extern unsigned char* lbl_8032ED50;

/*
 * --INFO--
 * PAL Address: 0x800905dc
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppWDrawMatrix(_pppPObject* object, void*, _pppCtrlTable*)
{
    register char* p = (char*)object;

    PSMTXConcat(ppvCameraMatrix02, *(Mtx*)(p + 0x10), *(Mtx*)(p + 0x40));
    PSVECScale((Vec*)(p + 0x40), (Vec*)(p + 0x40),
               *(float*)(lbl_8032ED50 + 0x28));
    PSVECScale((Vec*)(p + 0x50), (Vec*)(p + 0x50),
               *(float*)(lbl_8032ED50 + 0x2c));
    PSVECScale((Vec*)(p + 0x60), (Vec*)(p + 0x60),
               *(float*)(lbl_8032ED50 + 0x30));
}
