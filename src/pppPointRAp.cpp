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
    // Based on assembly: lwz r4, 0xc(r4); lwz r4, 0x4(r4); addi r0, r4, 0x81; stbx r5, r3, r0
    u32* dataPtr = (u32*)((char*)dataVal + 0xC);
    u32 innerValue = *(u32*)((char*)*dataPtr + 0x4);
    *((u8*)mngSt + innerValue + 0x81) = 0;
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
    
    // Calculate base particle pointer
    u32 particleOffset = dataValue + 0x80;
    u8* particlePtr = (u8*)mngSt + particleOffset;
    
    // Check particle lifetime counter at offset +1
    u8* lifetimePtr = particlePtr + 1;
    if (*lifetimePtr == 0) {
        // Initialize new particle if valid
        u32 checkValue = *(u32*)((char*)dataVal + 0xC);
        if ((checkValue + 0x10000) != 0xFFFF) {
            // Create particle object
            void* particleObj = nullptr; // Simplified - would call pppCreatePObject
            
            // Generate random values for positioning
            math.RandF();
            math.RandF();
            
            // Get scale values from dataVal
            float positionScale = *(float*)((char*)dataVal + 0x4);
            float velocityScale = *(float*)((char*)dataVal + 0x8);
            
            // Set up particle positions and velocities (simplified)
            // This would involve sine/cosine table lookups in full implementation
            
            // Set initial lifetime
            u8 initialLifetime = *(u8*)((char*)dataVal + 0x1C);
            *lifetimePtr = initialLifetime;
        }
    }
    
    // Decrement lifetime counter
    if (*lifetimePtr > 0) {
        *lifetimePtr = *lifetimePtr - 1;
    }
}