#include "ffcc/pppAngle.h"
#include "ffcc/partMng.h"


/*
 * --INFO--
 * PAL Address: 0x80064dd8
 * PAL Size: 36b
 */
void pppAngleCon(void* dest, _pppCtrlTable* ctrlTable)
{
    int offset = ((int*)ctrlTable->m_serializedDef)[0];
    
    int* ptr = (int*)((char*)dest + offset + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064dfc
 * PAL Size: 96b
 */
void pppAngle(void* dest, void* src, _pppCtrlTable* ctrlTable)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    if (*(int*)src != *((int*)dest + 3)) {
        return;
    }

    int offset = ((int*)ctrlTable->m_serializedDef)[0];
    int* destPtr = (int*)((char*)dest + offset + 0x80);
    int* srcPtr = (int*)((char*)src + 8);

    destPtr[0] += srcPtr[0];
    destPtr[1] += srcPtr[1];
    destPtr[2] += srcPtr[2];
}
