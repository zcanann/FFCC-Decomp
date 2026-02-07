#include "ffcc/pppAngMove.h"

extern int lbl_8032ED70;

struct PppAngMoveObj {
    int x;
    int y;
    int z;
};

struct PppAngMoveOffsets {
    int a;
    int b;
};

struct PppAngMoveData {
    void* field_0;
    void* field_4;
    int field_8;
    void* ptrData;
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
 * PAL Address: 0x80064e80
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngMove(void* basePtr, void* input, void* data1, void* data2)
{
    PppAngMoveOffsets* offsets = (PppAngMoveOffsets*)((PppAngMoveData*)data1)->ptrData;
    PppAngMoveObj* a = (PppAngMoveObj*)((char*)basePtr + offsets->a + 0x80);
    PppAngMoveObj* b = (PppAngMoveObj*)((char*)basePtr + offsets->b + 0x80);
    PppAngMoveInput* inputData = (PppAngMoveInput*)input;

    (void)data2;

    if (lbl_8032ED70 != 0) {
        return;
    }

    int inputId = *(int*)inputData;
    int baseId = *(int*)((char*)basePtr + 0xc);

    if (inputId == baseId) {
        b->x += inputData->x;
        b->y += inputData->y;
        b->z += inputData->z;
    }

    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}

/*
 * --INFO--
 * PAL Address: 0x80064e5c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppAngMoveCon(void* dest, void* param)
{
    int* paramPtr = (int*)param;
    int offset = ((int*)paramPtr[3])[1];
    int* ptr = (int*)((char*)dest + offset + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}
