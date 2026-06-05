#include "ffcc/pppAngMove.h"
#include "ffcc/partMng.h"


struct PppAngMoveObj {
    int x;
    int y;
    int z;
};

/*
 * --INFO--
 * PAL Address: 0x80064e5c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngMoveCon(_pppPObject* dest, _pppCtrlTable* ctrlTable)
{
    int offset = ctrlTable->m_serializedDataOffsets[1];
    PppAngMoveObj* work = (PppAngMoveObj*)(dest->m_workArea + offset);
    work->z = 0;
    work->y = 0;
    work->x = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064e80
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngMove(_pppPObject* basePtr, PppAngMoveInput* inputData, _pppCtrlTable* ctrlTable)
{
    PppAngMoveOffsets* offsets = (PppAngMoveOffsets*)ctrlTable->m_serializedDataOffsets;
    PppAngMoveObj* a = (PppAngMoveObj*)(basePtr->m_workArea + offsets->m_angleOffset);
    PppAngMoveObj* b = (PppAngMoveObj*)(basePtr->m_workArea + offsets->m_velocityOffset);

    if (ppvUserStopPartF != 0) {
        return;
    }

    int inputId = inputData->m_graphId;
    int baseId = basePtr->m_graphId;

    if (inputId == baseId) {
        b->x += inputData->x;
        b->y += inputData->y;
        b->z += inputData->z;
    }

    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}
