#include "ffcc/pppRandFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF90;
extern float lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80061e54
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFV(void* param1, void* param2, void* param3)
{
    // Cast parameters based on assembly analysis  
    int* p1 = (int*)param1;     // r29
    int* p2 = (int*)param2;     // r31 (was r30 in my code)
    void** p3 = (void**)param3; // r30 (was r31 in my code)
    
    // Check global state first (assembly: lwz r0, lbl_8032ED70@sda21)
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Check field at offset 12 of first parameter (assembly: lwz r3, 0xc(r29))
    if (p1[3] == 0) {
        // Generate first random float (assembly: bl RandF__5CMathFv)
        math.RandF();
        float randVal1 = 1.0f; // Placeholder for RandF() return value
        
        // Check byte at offset 24 of second parameter (assembly: lbz r0, 0x18(r31))
        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[0x18] != 0) {
            // Generate second random float and add (assembly: bl RandF__5CMathFv + fadds)
            math.RandF();
            float randVal2 = 1.0f; // Placeholder
            randVal1 = randVal1 + randVal2;
        } else {
            // Multiply by constant instead (assembly: fmuls f0, f31, f0)
            randVal1 = randVal1 * lbl_8032FF90;
        }
        
        // Calculate destination address and store (assembly: lwz r3, 0xc(r30))
        void** basePtr = (void**)((char*)p3 + 0xC);  // lwz r3, 0xc(r30)
        if (basePtr && *basePtr) {
            int* indexPtr = (int*)*basePtr;       // lwz r3, 0x0(r3)
            float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80)); // addi + add
            *destAddr = randVal1; // stfs f0, 0x0(r4)
        }
        
    } else {
        // Different branch - check second parameter fields (assembly: lwz r0, 0x0(r31) + cmpw)
        if (p2[0] == p1[3]) {
            // Calculate destination address (assembly: lwz r3, 0xc(r30))
            void** basePtr = (void**)((char*)p3 + 0xC);
            if (basePtr && *basePtr) {
                int* indexPtr = (int*)*basePtr;
                float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));
                
                // Check field4 for special case (assembly: lwz r3, 0x4(r31) + cmpwi r3, -0x1)
                float* srcAddr;
                if (p2[1] == -1) {
                    // Use constant address (assembly: lis + addi for lbl_801EADC8)
                    srcAddr = &lbl_801EADC8;
                } else {
                    // Use computed address (assembly: addi r3, r3, 0x80 + add)
                    srcAddr = (float*)((char*)p1 + (p2[1] + 0x80));
                }
                
                // Complex floating point operations for X component
                float multiplier1 = *(float*)((char*)p2 + 8);   // lfs f0, 0x8(r31)
                float destVal = *destAddr;        // lfs f2, 0x0(r4) 
                float srcVal1 = *srcAddr;         // lfs f1, 0x0(r3)
                
                // Assembly: fmsubs f0, f0, f2, f0 + fadds f0, f1, f0
                float result1 = srcVal1 + (multiplier1 * destVal - multiplier1);
                *srcAddr = result1;
                
                // Y component operations (assembly: lfs f0, 0xc(r31) + lfs f1, 0x4(r3))
                float multiplier2 = *(float*)((char*)p2 + 12);
                float srcVal2 = *(float*)((char*)srcAddr + 4);  // +4 offset
                float result2 = srcVal2 + (multiplier2 * destVal - multiplier2);
                *(float*)((char*)srcAddr + 4) = result2;
                
                // Z component operations (assembly: lfs f0, 0x10(r31) + lfs f1, 0x8(r3))
                float multiplier3 = *(float*)((char*)p2 + 16);
                float srcVal3 = *(float*)((char*)srcAddr + 8);  // +8 offset
                float result3 = srcVal3 + (multiplier3 * destVal - multiplier3);
                *(float*)((char*)srcAddr + 8) = result3;
            }
        }
    }
}
