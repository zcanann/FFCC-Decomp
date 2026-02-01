#include "ffcc/pppAngMove.h"

extern int lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x80064e80
 * PAL Size: 156b
 */
void pppAngMove(void* dest, void* src, void* param1, void* param2)
{
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* param2Ptr = (int*)param2;
    int* destPtr = (int*)((char*)dest + param2Ptr[0] + 0x80);
    int* srcPtr = (int*)((char*)dest + param2Ptr[1] + 0x80);
    
    if (param1) {
        int* param1Ptr = (int*)param1;
        if (param1Ptr[3] == ((int*)dest)[3]) {
            srcPtr[0] += ((int*)((char*)param1 + 0x8))[0];
            srcPtr[1] += ((int*)((char*)param1 + 0xc))[0];
            srcPtr[2] += ((int*)((char*)param1 + 0x10))[0];
        }
    }
    
    destPtr[0] += srcPtr[0];
    destPtr[1] += srcPtr[1];
    destPtr[2] += srcPtr[2];
}

/*
 * --INFO--
 * PAL Address: 0x80064e5c
 * PAL Size: 36b
 */
void pppAngMoveCon(void* dest, void* param)
{
    int* paramPtr = (int*)param;
    paramPtr[3]; // Access param[3] first to match assembly 
    int offset = paramPtr[1]; // Then access param[1]
    int* ptr = (int*)((char*)dest + offset + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}