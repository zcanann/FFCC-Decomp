#include "ffcc/pppColAccele.h"

extern int lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x8005fdec
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColAccele(_pppPObject* obj1, void* data1, _pppPObject* obj2)
{
    // Access pointer chain: obj2 + 0xC -> [0] and [4]
    void** objPtr = (void**)((char*)obj2 + 0xC);
    void* ptr0 = ((void**)*objPtr)[0];
    void* ptr4 = ((void**)*objPtr)[1];
    
    // Calculate acceleration buffer addresses
    short* accel1 = (short*)((char*)obj1 + (int)ptr0 + 0x80);
    short* accel2 = (short*)((char*)obj1 + (int)ptr4 + 0x80);
    
    // Early return if global flag is set
    if (lbl_8032ED70 != 0)
        return;
    
    // Check frame data match
    int frameData = *(int*)data1;
    int objFrame = *(int*)((char*)obj1 + 0xC);
    if (frameData != objFrame) {
        // Skip the acceleration application but still do accumulation
        goto accumulate;
    }
    
    // Apply acceleration from data1 to accel2
    short* inputAccel = (short*)((char*)data1 + 8);
    accel2[0] += inputAccel[0];
    accel2[1] += inputAccel[1];
    accel2[2] += inputAccel[2];
    accel2[3] += inputAccel[3];
    
accumulate:
    // Accumulate from accel2 to accel1
    accel1[0] += accel2[0];
    accel1[1] += accel2[1];
    accel1[2] += accel2[2];
    accel1[3] += accel2[3];
}

/*
 * --INFO--
 * PAL Address: 0x8005fdc4
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColAcceleCon(_pppPObject* obj, void* data)
{
    // Access pointer chain: data + 0xC -> [4] + 0x80
    void** dataPtr = (void**)((char*)data + 0xC);
    void* workPtr = ((void**)*dataPtr)[1];
    short* accel = (short*)((char*)obj + (int)workPtr + 0x80);
    
    // Zero out acceleration values
    accel[0] = 0;
    accel[1] = 0;
    accel[2] = 0;
    accel[3] = 0;
}