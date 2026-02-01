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
    
    if (particleId != (int)angularVelocityPtr) {
        goto apply_velocity;
    }
    
    // Angular acceleration update
    *(int*)((char*)angularAccelerationPtr + 0x80) += *(int*)((char*)particleData + 0x8);
    *(int*)((char*)angularAccelerationPtr + 0x84) += *(int*)((char*)particleData + 0xc);
    *(int*)((char*)angularAccelerationPtr + 0x88) += *(int*)((char*)particleData + 0x10);
    
apply_velocity:
    // Angular velocity update
    *(int*)((char*)angularVelocityPtr + 0x80) += *(int*)((char*)angularAccelerationPtr + 0x80);
    *(int*)((char*)angularVelocityPtr + 0x84) += *(int*)((char*)angularAccelerationPtr + 0x84);
    *(int*)((char*)angularVelocityPtr + 0x88) += *(int*)((char*)angularAccelerationPtr + 0x88);
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
    
    char* ptr = (char*)angularAccelerationPtr + (int)particleSystem;
    *(int*)(ptr + 0x88) = 0;
    *(int*)(ptr + 0x84) = 0;  
    *(int*)(ptr + 0x80) = 0;
}