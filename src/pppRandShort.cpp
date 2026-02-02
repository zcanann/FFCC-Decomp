#include "ffcc/pppRandShort.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;       // Global state flag
extern float lbl_8032FFC8;     // Float constant 0x8032FFC8
extern double lbl_8032FFD0;    // Double constant 0x8032FFD0
extern float lbl_801EADC8[32]; // Array of floats at 0x801EADC8

/*
 * --INFO--
 * PAL Address: 0x8006249c
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandShort(void* r3, void* r4, void* r5)
{
    // Cast parameters based on memory access patterns from assembly
    int* p1 = (int*)r3;  
    
    struct ParamStruct2 {
        int field0;           // offset 0
        int field4;           // offset 4  
        short field8;         // offset 8 - halfword
        unsigned char fieldA; // offset 10 - byte
    }* p2 = (struct ParamStruct2*)r4; 
    
    struct ParamStruct3 {
        void* field0;
        void* field4;
        void* field8;
        void* fieldC;
    }* p3 = (struct ParamStruct3*)r5; 
    
    // Check global state first - if set, return early
    if (lbl_8032ED70 != 0) {
        return; 
    }
    
    // Check field at offset 12 of first parameter
    if (p1[3] == 0) { 
        // Generate random float
        math.RandF(); 
        float randVal = 0.0f; // Placeholder - RandF result stored elsewhere
        
        // Check byte at offset 10 of second parameter  
        if (p2->fieldA != 0) { 
            // Generate second random and add them
            math.RandF();
            randVal += 0.0f; // Second placeholder
        } else {
            // Multiply by constant at lbl_8032FFC8
            randVal *= lbl_8032FFC8;
        }
        
        // Get memory location to store result  
        void** p3_data = (void**)p3->fieldC;
        void* base = *p3_data;
        // Assembly: addi r5, r3, 0x80; add r5, r30, r5  
        // This means: offset = p1[3] + 0x80, then add base address from r30
        int offset = p1[3] + 0x80;
        float* target = (float*)((char*)r3 + offset);  
        *target = randVal;
        
        return;
    }
    
    // Check if first field of second param matches field at offset 12 of first param
    if (p2->field0 != p1[3]) {
        return;
    }
    
    // Calculate target memory location
    void** p3_data = (void**)p3->fieldC;
    void* base = *p3_data;
    void* addr_base;
    
    // Check field at offset 4 of second parameter
    if (p2->field4 == -1) {
        addr_base = &lbl_801EADC8[0];
    } else {
        int offset = p2->field4 + 0x80;
        addr_base = (char*)r3 + offset;
    }
    
    // Load current value and do floating point calculation
    short current_val = *(short*)addr_base;
    short range = p2->field8;
    int mem_offset = p1[3] + 0x80;
    float* memory_loc = (float*)((char*)r3 + mem_offset);
    float mem_val = *memory_loc;
    
    // Convert to floating point and do calculation:
    // result = current_val + (range * mem_val - current_val)
    double range_d = (double)range;
    double current_d = (double)current_val;
    double result = current_d + (range_d * mem_val - current_d);
    
    // Convert back to short and store
    short final_result = (short)result;
    *(short*)addr_base = final_result;
}