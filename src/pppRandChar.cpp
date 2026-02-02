#include "ffcc/pppRandChar.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;         // Global state flag
extern float lbl_8032FEF8;       // Float constant 0.5
extern unsigned char lbl_801EADC8[32]; // Character array

/*
 * --INFO--
 * Address:	80060EFC
 * Size:	320 bytes (0x140)
 */
void pppRandChar(void* r3, void* r4, void* r5)
{
    // Cast parameters based on memory access patterns from assembly
    int* p1 = (int*)r3;
    
    struct ParamStruct2 {
        int field0;           // offset 0
        int field4;           // offset 4  
        unsigned char field8; // offset 8 - byte
        unsigned char field9; // offset 9 - byte  
    }* p2 = (struct ParamStruct2*)r4;
    
    struct ParamStruct3 {
        int fieldC;          // offset 0x0C
    }* p3_ptr = (struct ParamStruct3*)((char*)r5 + 0x0C);
    
    if (lbl_8032ED70 == 0) {
        int val = p1[3]; // offset 0x0C
        if (val == 0) {
            math.RandF(); // This returns float in f1 register  
            float randVal = 1.0f; // Placeholder - RandF() return value
            
            if (p2->field9 != 0) {
                math.RandF();
                float randVal2 = 1.0f; // Placeholder
                randVal = randVal + randVal2; // fadds f0, f31, f1
            } else {
                randVal = randVal * lbl_8032FEF8; // fmuls f0, f31, f0 (should be 0.5)
            }
            
            int* data = (int*)p3_ptr;
            int offset = data[0] + 0x80;
            float* target = (float*)((char*)r3 + offset);
            *target = randVal;
        } else {
            if (p2->field0 == val) {
                int* data = (int*)p3_ptr;
                int offset = data[0] + 0x80;
                float* source = (float*)((char*)r3 + offset);
                unsigned char* target;
                
                if (p2->field4 == -1) {
                    target = lbl_801EADC8;
                } else {
                    target = (unsigned char*)r3 + (p2->field4 + 0x80);
                }
                
                unsigned char charVal = p2->field8;
                float sourceVal = *source;
                unsigned char targetVal = target[0];
                
                // Floating point arithmetic as seen in assembly
                float charFloat = (float)charVal;
                float result = charFloat * sourceVal - (float)targetVal;
                int finalVal = (int)result;
                target[0] = (unsigned char)(targetVal + finalVal);
            }
        }
    }
}