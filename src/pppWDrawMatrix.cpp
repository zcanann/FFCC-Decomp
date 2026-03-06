#include "ffcc/pppWDrawMatrix.h"
#include "ffcc/partMng.h"

#include <dolphin/mtx.h>

extern "C" {
extern Mtx ppvCameraMatrix02;
}

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
    char* base = (char*)object;

    PSMTXConcat(ppvCameraMatrix02, *(Mtx*)(base + 0x10), *(Mtx*)(base + 0x40));
    PSVECScale((Vec*)(base + 0x40), (Vec*)(base + 0x40), pppMngStPtr->m_scale.x);
    PSVECScale((Vec*)(base + 0x50), (Vec*)(base + 0x50), pppMngStPtr->m_scale.y);
    PSVECScale((Vec*)(base + 0x60), (Vec*)(base + 0x60), pppMngStPtr->m_scale.z);
}

