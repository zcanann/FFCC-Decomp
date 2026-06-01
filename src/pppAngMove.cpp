#include "ffcc/pppAngMove.h"
#include "ffcc/partMng.h"


struct PppAngMoveObj {
    int x;
    int y;
    int z;
};

struct PppAngMoveOffsets {
    int a;
    int b;
};

struct PppAngMoveInput {
    int field_0;
    int field_4;
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
    int* ptr = (int*)(dest->m_workArea + offset);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
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
void pppAngMove(_pppPObject* basePtr, void* input, _pppCtrlTable* ctrlTable)
{
    PppAngMoveOffsets* offsets = (PppAngMoveOffsets*)ctrlTable->m_serializedDataOffsets;
    PppAngMoveObj* a = (PppAngMoveObj*)(basePtr->m_workArea + offsets->a);
    PppAngMoveObj* b = (PppAngMoveObj*)(basePtr->m_workArea + offsets->b);
    PppAngMoveInput* inputData = (PppAngMoveInput*)input;

    if (gPppCalcDisabled != 0) {
        return;
    }

    int inputId = *(int*)inputData;
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
