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
    int destOffset = param2Ptr[0];
    int srcOffset = param2Ptr[1];
    int* destPtr = (int*)((char*)dest + destOffset + 0x80);
    int* srcPtr = (int*)((char*)dest + srcOffset + 0x80);
    
    if (param1 != 0) {
        int* param1Ptr = (int*)param1;
        if (param1Ptr[3] == ((int*)dest)[3]) {
            srcPtr[0] += param1Ptr[2];
            srcPtr[1] += param1Ptr[3]; 
            srcPtr[2] += param1Ptr[4];
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
    int offset = paramPtr[3];
    int* ptr = (int*)((char*)dest + offset + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}