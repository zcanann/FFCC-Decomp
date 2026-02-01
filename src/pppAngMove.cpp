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
    
    if (param1 && ((int*)param1)[3] == ((int*)dest)[3]) {
        int* destPtr = (int*)((char*)dest + ((int*)param2)[1] + 0x80);
        
        destPtr[0] += ((int*)((char*)param1 + 0x8))[0];
        destPtr[1] += ((int*)((char*)param1 + 0xc))[0]; 
        destPtr[2] += ((int*)((char*)param1 + 0x10))[0];
    }
    
    int* destPtr = (int*)((char*)dest + ((int*)param2)[0] + 0x80);
    int* srcPtr = (int*)((char*)dest + ((int*)param2)[1] + 0x80);
    
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
    ((int*)param)[3]; // Access param[3] first to match target assembly
    asm(""); // Prevent optimization
    int* ptr = (int*)((char*)dest + ((int*)param)[1] + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}