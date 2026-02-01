#include "ffcc/pppAngAccele.h"

/*
 * --INFO--
 * PAL Address: 0x80064d3c
 * PAL Size: 156b
 */
void pppAngAccele(void* particleSystem, void* particleData)
{
    // Get pointer to particle system data structure
    void** systemPtr = (void**)particleSystem;
    void* systemData = systemPtr[3];  // Load from offset 0xc
    
    // Get particle instances for angular velocity and acceleration  
    void** systemDataPtr = (void**)systemData;
    void* angularVelocityPtr = systemDataPtr[0];      // Load from offset 0x0
    void* angularAccelerationPtr = systemDataPtr[1];  // Load from offset 0x4
    
    // Check global enable flag
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get particle data values
    void** particlePtr = (void**)particleData;
    int particleId = *(int*)particlePtr[0];           // Load from offset 0x0
    
    // Check if this particle matches the current system
    int systemId = *(int*)((char*)particleSystem + 0xc);
    if (particleId != systemId) {
        goto apply_to_velocity;
    }
    
    // Apply angular acceleration to angular velocity for this particle
    int* velocity = (int*)((char*)angularAccelerationPtr + 0x80);
    int* acceleration = (int*)((char*)particleData + 0x8);
    
    velocity[0] += acceleration[0];  // X component
    velocity[1] += acceleration[1];  // Y component 
    velocity[2] += acceleration[2];  // Z component
    
apply_to_velocity:
    // Apply angular velocity to angular position
    int* position = (int*)((char*)angularVelocityPtr + 0x80);
    int* velocity2 = (int*)((char*)angularAccelerationPtr + 0x80);
    
    position[0] += velocity2[0];  // X component
    position[1] += velocity2[1];  // Y component
    position[2] += velocity2[2];  // Z component
}

/*
 * --INFO--
 * PAL Address: 0x80064d18
 * PAL Size: 36b
 */
void pppAngAcceleCon(void* particleSystem)
{
    // Get pointer to particle system data structure
    void** systemPtr = (void**)particleSystem;
    void* systemData = systemPtr[3];  // Load from offset 0xc
    
    // Get particle instances for angular acceleration 
    void** systemDataPtr = (void**)systemData;
    void* angularAccelerationPtr = systemDataPtr[1];  // Load from offset 0x4
    
    // Calculate final pointer: particleSystem + (angularAccelerationPtr + 0x80)
    int offset = (int)angularAccelerationPtr + 0x80;
    int* targetPtr = (int*)((char*)particleSystem + offset);
    
    // Store zeros at specific offsets relative to final pointer
    targetPtr[2] = 0;  // Store at offset 0x8
    targetPtr[1] = 0;  // Store at offset 0x4  
    targetPtr[0] = 0;  // Store at offset 0x0
}