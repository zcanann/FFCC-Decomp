#include "ffcc/pppAngle.h"

extern int lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x80064dfc
 * PAL Size: 96b
 */
void pppAngle(void* dest, void* src, void* param1, void* param2)
{
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    if (((int*)src)[0] != ((int*)dest)[3]) {
        return;
    }
    
    int* destPtr = (int*)((char*)dest + ((int*)param2)[3] + 0x80);
    int* srcPtr = (int*)((char*)src + 0x8);
    
    destPtr[0] += srcPtr[0];
    destPtr[1] += srcPtr[1]; 
    destPtr[2] += srcPtr[2];
}

/*
 * --INFO--
 * PAL Address: 0x80064dd8
 * PAL Size: 36b
 */
void pppAngleCon(void* dest, void* param)
{
    ((int*)param)[3]; // Access param[3] first to match target assembly
    asm(""); // Prevent optimization
    int* ptr = (int*)((char*)dest + ((int*)param)[0] + 0x80);
    ptr[2] = 0;
    ptr[1] = 0;
    ptr[0] = 0;
}