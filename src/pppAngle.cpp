#include "ffcc/pppAngle.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 0x80064dd8
 * PAL Size: 36b
 */
void pppAngleCon(_pppPObject* dest, _pppCtrlTable* ctrlTable)
{
    int offset = (ctrlTable->m_serializedDataOffsets)[0];

    int* ptr = (int*)(dest->m_workArea + offset);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064dfc
 * PAL Size: 96b
 */
void pppAngle(_pppPObject* dest, PppAngleInput* srcData, _pppCtrlTable* ctrlTable)
{
    if (ppvUserStopPartF != 0) {
        return;
    }

    if (srcData->m_graphId != dest->m_graphId) {
        return;
    }

    int offset = (ctrlTable->m_serializedDataOffsets)[0];
    int* destPtr = (int*)(dest->m_workArea + offset);
    int* srcPtr = srcData->m_angle;

    destPtr[0] += srcPtr[0];
    destPtr[1] += srcPtr[1];
    destPtr[2] += srcPtr[2];
}
