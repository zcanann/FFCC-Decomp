#include "ffcc/pppRandDownFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70; // Global state flag
extern float lbl_8032FF38; // Float constant  
extern float lbl_801EADC8; // Another float constant

/*
 * --INFO--
 * PAL Address: 0x8006155c
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
void pppRandDownFloat(void* r3, void* r4, void* r5)
{
    // Cast parameters based on memory access patterns from assembly
    int* p1 = (int*)r3;  
    struct ParamStruct2 {
        int field0;           
        int field4;           
        float field8;         
        unsigned char fieldC; 
    }* p2 = (struct ParamStruct2*)r4; 
    
    struct ParamStruct3 {
        void* field0;    
        void* field4;    
        void* field8;    
        void* fieldC;    
    }* p3 = (struct ParamStruct3*)r5; 
    
    // Check global state first
    if (lbl_8032ED70 != 0) {
        return; 
    }
    
    // Check field at offset 12 of first parameter
    if (p1[3] == 0) { 
        // Generate random float - using placeholder for now
        math.RandF(); 
        float randVal = -0.5f; // Negative placeholder for "down" version
        
        // Check byte at offset 12 of second parameter  
        if (p2->fieldC != 0) { 
            // Generate second random and do arithmetic
            math.RandF();
            float randVal2 = 0.5f; // Second placeholder
            randVal = randVal - randVal2;
            // Then multiply by constant 
            randVal = randVal * lbl_8032FF38;
        }
        
        // Calculate destination and store
        void** basePtr = (void**)p3->fieldC; 
        if (basePtr) {
            int* indexPtr = (int*)*basePtr;       
            float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80)); 
            *destAddr = randVal; 
        }
        
    } else {
        // Different branch - check second parameter fields
        if (p2->field0 == p1[3]) { 
            // Calculate destination address
            void** basePtr = (void**)p3->fieldC;
            if (basePtr) {
                int* indexPtr = (int*)*basePtr;
                
                // Determine source address based on field4 
                float* srcAddr;
                if (p2->field4 == -1) { 
                    // Use constant address
                    srcAddr = &lbl_801EADC8;
                } else {
                    // Use computed address 
                    srcAddr = (float*)((char*)p1 + (p2->field4 + 0x80));
                }
                
                float* destAddr = (float*)((char*)p1 + (*indexPtr + 0x80));
                
                // Load values and perform arithmetic
                float val1 = p2->field8;     
                float val0 = *destAddr;      
                float val2 = *srcAddr;       
                
                // Multiply and add
                float result = val2 + (val1 * val0);
                *srcAddr = result; 
            }
        }
    }
}