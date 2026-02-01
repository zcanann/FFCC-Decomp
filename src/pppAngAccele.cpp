#include "ffcc/pppAngAccele.h"

/*
 * --INFO--
 * PAL Address: 0x80064d3c
 * PAL Size: 156b
 */
void pppAngAccele(void* particleSystem, void* particleData)
{
    extern int lbl_8032ED70;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    void** systemPtr = (void**)particleSystem;
    void** particlePtr = (void**)particleData;
    void* systemData = systemPtr[3];
    void* particleIdPtr = particlePtr[0];
    void** systemDataPtr = (void**)systemData;
    void* angularVelocityPtr = systemDataPtr[0];
    int particleId = *(int*)particleIdPtr;
    void* angularAccelerationPtr = systemDataPtr[1];
    
    char* angularVelocityBase = (char*)particleSystem + (int)angularVelocityPtr + 0x80;
    char* angularAccelBase = (char*)particleSystem + (int)angularAccelerationPtr + 0x80;
    
    if (particleId == (int)angularVelocityPtr) {
        *(int*)(angularAccelBase + 0x0) += *(int*)((char*)particleData + 0x8);
        *(int*)(angularAccelBase + 0x4) += *(int*)((char*)particleData + 0xc);
        *(int*)(angularAccelBase + 0x8) += *(int*)((char*)particleData + 0x10);
    }
    
    *(int*)(angularVelocityBase + 0x0) += *(int*)(angularAccelBase + 0x0);
    *(int*)(angularVelocityBase + 0x4) += *(int*)(angularAccelBase + 0x4);
    *(int*)(angularVelocityBase + 0x8) += *(int*)(angularAccelBase + 0x8);
}

/*
 * --INFO--
 * PAL Address: 0x80064d18
 * PAL Size: 36b
 */
void pppAngAcceleCon(void* particleSystem)
{
    void** systemPtr = (void**)particleSystem;
    void* systemData = systemPtr[3];
    void** systemDataPtr = (void**)systemData;
    void* angularAccelerationPtr = systemDataPtr[1];
    
    char* ptr = (char*)particleSystem + (int)angularAccelerationPtr + 0x80;
    *(int*)(ptr + 0x8) = 0;
    *(int*)(ptr + 0x4) = 0;  
    *(int*)(ptr + 0x0) = 0;
}