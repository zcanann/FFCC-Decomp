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
    
    int* srcData = (int*)src;
    int* destData = (int*)dest;
    
    if (srcData[0] != destData[3]) {
        return;
    }
    
    int* param2Data = (int*)param2;
    int* offsetPtr = (int*)param2Data[3];
    int offset = offsetPtr[0];
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
void pppAngleCon(void* dest, void* param)
{
    int* paramData = (int*)param;
    int* offsetPtr = (int*)paramData[3];
    int offset = offsetPtr[0];
    
    int* ptr = (int*)((char*)dest + offset + 0x80);
    ptr[0] = 0;
    ptr[1] = 0;
    ptr[2] = 0;
}