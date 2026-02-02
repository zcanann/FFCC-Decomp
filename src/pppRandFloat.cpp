#include "ffcc/pppRandFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70; // Global state flag from assembly
extern float lbl_8032FF88; // Float constant from assembly 
extern float lbl_801EADC8; // Another float constant

/*
 * --INFO--
 * PAL Address: 0x80061d48
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandFloat(void* param1, void* param2, void* param3)
{
    // Cast parameters based on memory access patterns in assembly
    int* p1 = (int*)param1;
    struct ParamStruct2 {
        int field0;      // offset 0 
        int field4;      // offset 4
        float field8;    // offset 8  
        unsigned char fieldC; // offset 12
    }* p2 = (struct ParamStruct2*)param2;
    
    struct ParamStruct3 {
        void* field0;    // offset 0
        void* field4;    // offset 4  
        void* field8;    // offset 8
        void* fieldC;    // offset 12
    }* p3 = (struct ParamStruct3*)param3;
    
    // Check global state first (like assembly does)
    if (lbl_8032ED70 != 0) {
        return; // Early exit condition
    }
    
    // Check field at offset 12 of first parameter
    if (p1[3] == 0) { // lwz r3, 0xc(r29)
        // Generate first random float
        math.RandF(); // This returns float in f1 register
        float randVal1 = 1.0f; // Placeholder - RandF() return value
        
        // Check byte at offset 12 of second parameter  
        if (p2->fieldC != 0) { // lbz r0, 0xc(r31) + cmplwi r0, 0x0
            // Generate second random float and add
            math.RandF();
            float randVal2 = 1.0f; // Placeholder
            randVal1 = randVal1 + randVal2; // fadds f0, f31, f1
        } else {
            // Multiply by constant instead
            randVal1 = randVal1 * lbl_8032FF88; // fmuls f0, f31, f0
        }
        
        // Calculate destination address and store
        void** basePtr = (void**)p3->fieldC;  // lwz r3, 0xc(r30)
        if (basePtr) {
            int* indexPtr = (int*)*basePtr;       // lwz r3, 0x0(r3)
            float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80)); // Calculate final address
            *destAddr = randVal1; // stfs f0, 0x0(r4)
        }
        
    } else {
        // Different branch - check second parameter fields
        if (p2->field0 == p1[3]) { // cmpw r0, r3 where r0 = lwz r0, 0x0(r31)
            // Calculate destination address differently
            void** basePtr = (void**)p3->fieldC;
            if (basePtr) {
                int* indexPtr = (int*)*basePtr;
                
                // Check field4 for special case
                if (p2->field4 == -1) { // cmpwi r3, -0x1
                    // Use constant address
                    float* srcAddr = &lbl_801EADC8;
                    float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));
                    
                    // Complex floating point operation: fmsubs f0, f2, f0, f2
                    float val2 = p2->field8;   // lfs f2, 0x8(r31)
                    float val0 = *destAddr;    // lfs f0, 0x0(r4) 
                    float val1 = *srcAddr;     // lfs f1, 0x0(r3)
                    
                    float result = val1 + (val2 * val0 - val2); // fmsubs + fadds
                    *srcAddr = result; // stfs f0, 0x0(r3)
                    
                } else {
                    // Use computed address
                    float* srcAddr = (float*)((char*)p1 + (p2->field4 + 0x80));
                    float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));
                    
                    float val2 = p2->field8;
                    float val0 = *destAddr;
                    float val1 = *srcAddr;
                    
                    float result = val1 + (val2 * val0 - val2);
                    *srcAddr = result;
                }
            }
        }
    }
}