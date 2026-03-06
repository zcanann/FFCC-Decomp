#include "ffcc/pppAngle.h"

extern int lbl_8032ED70;

struct _pppCtrlTableData {
    int m_workOffset;
    int m_workOffsetAlt;
    int m_ownerWorkOffset;
};

struct _pppCtrlTable {
    void* m_prog;
    int m_initialWork;
    int m_unk8;
    _pppCtrlTableData* m_serializedDef;
};

/*
 * --INFO--
 * PAL Address: 0x80064dfc
 * PAL Size: 96b
 */
void pppAngle(void* dest, void* src, _pppCtrlTable* ctrlTable)
{
    if (lbl_8032ED70 != 0) {
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
