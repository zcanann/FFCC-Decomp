#include "ffcc/pppAngAccele.h"

extern int lbl_8032ED70;

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int* serializedDataOffsets;
} pppAngAcceleObj;

typedef struct {
    int* graphIdPtr;
    int unk4;
    int x;
    int y;
    int z;
} pppAngAcceleData;

/*
 * --INFO--
 * PAL Address: 0x80064d3c
 * PAL Size: 156b
 */
void pppAngAccele(void* particleSystem, void* particleData)
{
    pppAngAcceleObj* obj = (pppAngAcceleObj*)particleSystem;
    pppAngAcceleData* data = (pppAngAcceleData*)particleData;
    int* offsets = obj->serializedDataOffsets;
    int* angularVelocity = (int*)((char*)obj + offsets[0] + 0x80);
    int* angularAccel = (int*)((char*)obj + offsets[1] + 0x80);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (*(data->graphIdPtr) == offsets[0]) {
        angularAccel[0] += data->x;
        angularAccel[1] += data->y;
        angularAccel[2] += data->z;
    }

    angularVelocity[0] += angularAccel[0];
    angularVelocity[1] += angularAccel[1];
    angularVelocity[2] += angularAccel[2];
}

/*
 * --INFO--
 * PAL Address: 0x80064d18
 * PAL Size: 36b
 */
void pppAngAcceleCon(void* particleSystem)
{
    void** systemData = (void**)((void**)particleSystem)[3];
    void* angularAccelerationPtr = systemData[1];
    
    char* ptr = (char*)particleSystem + (int)angularAccelerationPtr + 0x80;
    *(int*)(ptr + 0x8) = 0;
    *(int*)(ptr + 0x4) = 0;  
    *(int*)(ptr + 0x0) = 0;
}
