#include "ffcc/pppSclMove.h"

/*
 * --INFO--
 * PAL Address: 0x80063210
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMoveCon(void* param1, void* param2)
{
    void* ptr = (void*)((int*)((char*)param2 + 0xC))[0];
    ptr = (void*)((int*)((char*)ptr + 0x4))[0];
    float* data1 = (float*)((char*)param1 + (int)ptr + 0x80);
    float zero = 0.0f;
    data1[0] = zero;
    data1[1] = zero;
    data1[2] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80063234
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMove(void* param1, void* param2, void* param3)
{
    int* data2 = (int*)((char*)param3 + 0xC);
    int* globalFlag = (int*)0x8032ED70; // Referenced in assembly
    
    float* src = (float*)((char*)param1 + data2[0] + 0x80);
    float* dest = (float*)((char*)param1 + data2[1] + 0x80);
    
    if (*globalFlag != 0) {
        return;
    }
    
    int* param2Data = (int*)param2;
    int param1Data = *(int*)((char*)param1 + 0xC);
    
    if (param2Data[0] == param1Data) {
        // Vector addition for src
        float* movement = (float*)((char*)param2 + 0x8);
        src[0] += movement[0];
        src[1] += movement[1];
        src[2] += movement[2];
    }
    
    // Vector addition for dest
    dest[0] += src[0];
    dest[1] += src[1];
    dest[2] += src[2];
}