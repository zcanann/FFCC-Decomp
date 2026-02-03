#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330038; 
extern double lbl_80330040;
extern short lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 */
void pppRandUpShort(void* param1, void* param2, void* param3)
{
    // Cast parameters based on assembly analysis
    int* p1 = (int*)param1;
    
    struct ParamStruct2 {
        int field0;           // offset 0
        int field4;           // offset 4
        short field8;         // offset 8 
        unsigned char fieldA; // offset 10
    }* p2 = (struct ParamStruct2*)param2;
    
    struct ParamStruct3 {
        void* fieldC;         // offset 12
    }* p3 = (struct ParamStruct3*)param3;
    
    // Check global flag first
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Check field at offset 12 of first parameter
    if (p1[3] == 0) {
        // Generate random float - result in f1, copy to f31
        float f31Val;
        math.RandF();
        // f31Val = result from f1
        
        // Check if second random needed
        if (p2->fieldA != 0) {
            math.RandF();
            // f31Val += result from f1
        }
        
        // Scale by constant
        f31Val *= lbl_80330038;
        
        // Store to calculated memory location
        void** basePtr = (void**)&p3->fieldC;
        int* indexPtr = (int*)*basePtr;
        int offset = *indexPtr + 0x80;
        float* targetAddr = (float*)((char*)param1 + offset);
        *targetAddr = f31Val;
        
    } else {
        // Check if fields match
        if (p2->field0 != p1[3]) {
            return;
        }
        
        // Calculate target address for final operation
        void** basePtr = (void**)&p3->fieldC;
        int* indexPtr = (int*)*basePtr;
        int offset = *indexPtr + 0x80;
        float* sourceAddr = (float*)((char*)param1 + offset);
        
        short* targetShort;
        if (p2->field4 == -1) {
            targetShort = &lbl_801EADC8;
        } else {
            targetShort = (short*)((char*)param1 + (p2->field4 + 0x80));
        }
        
        // Perform floating point to integer conversion and arithmetic
        short multiplier = p2->field8;
        float sourceValue = *sourceAddr;
        
        // Convert multiplier to double, subtract magic constant, multiply by source
        double multiplierD = (double)multiplier;
        double result = multiplierD - lbl_80330040;
        result *= sourceValue;
        
        // Convert to integer and add to existing value
        int intResult = (int)result;
        short currentValue = *targetShort;
        *targetShort = currentValue + (short)intResult;
    }
}