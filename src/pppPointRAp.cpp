#include "ffcc/pppPointRAp.h"
#include "ffcc/pppPart.h"
#include "ffcc/math.h"
#include <dolphin/mtx.h>

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80060ee4
 * PAL Size: 24b
 */
void pppPointRApCon(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    u32* dataPtr = (u32*)((char*)dataVal + 0xC);
    u32 offset = *(u32*)((char*)*dataPtr + 0x4) + 0x81;
    *((u8*)mngSt + offset) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060d20
 * PAL Size: 452b
 */
void pppPointRAp(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    extern int lbl_8032ED70;
    
    // Early return if global flag is set
    if (lbl_8032ED70 != 0) return;
    
    // Get data pointer from dataVal + 0xC
    u32* dataPtr = (u32*)((char*)dataVal + 0xC);
    u32 dataValue = *(u32*)((char*)*dataPtr + 0x4);
    
    // Calculate base particle pointer with 0x80 offset
    u8* particlePtr = (u8*)mngSt + dataValue + 0x80;
    
    // Check particle lifetime counter at offset +1
    if (particlePtr[1] == 0) {
        // Check if valid for particle creation
        u32 checkValue = *(u32*)((char*)dataVal + 0xC);
        if ((checkValue + 0x10000) != 0xFFFF) {
            // Create particle object - would call pppCreatePObject(mngSt, dataVal)
            // void* particleObj = ...;
            // Store mngSt reference in created object
            
            // Generate random angle index
            math.RandF();
            
            // Get position scale from dataVal + 0x4
            float positionScale = *(float*)((char*)dataVal + 0x4);
            
            // Calculate sine/cosine values for positioning
            // Complex trigonometric calculations with lookup table
            
            // Second random call for additional positioning
            math.RandF();
            
            // Get velocity scale from dataVal + 0x8  
            float velocityScale = *(float*)((char*)dataVal + 0x8);
            
            // Set particle positions and velocities
            // (Complex floating-point math involving multiple particle objects)
            
            // Set initial lifetime from dataVal + 0x1C
            u8 initialLifetime = *(u8*)((char*)dataVal + 0x1C);
            particlePtr[1] = initialLifetime;
        }
    }
    
    // Decrement lifetime counter if > 0
    if (particlePtr[1] > 0) {
        particlePtr[1] = particlePtr[1] - 1;
    }
}