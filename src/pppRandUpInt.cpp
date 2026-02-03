#include "ffcc/pppRandUpInt.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80062ce0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpInt(int index, void* param2, void* param3)
{
    if (param2 == 0 || param3 == 0) {
        return;
    }
    
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;
    
    // Check condition at offset 0xc of param2  
    if (p2[3] == 0) {
        // First RandF call - generates random float
        math.RandF();
        
        // Check byte at offset 0xc of param2
        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[12] != 0) {
            // Second RandF call 
            math.RandF();
        }
        
        // Work with param3 data
        int* param3_data = (int*)p3[3];
        int* param3_base = (int*)(*param3_data);
        int offset = param3_base[0] + 0x80;
        float* target_location = (float*)((char*)index + offset);
        // Store some calculated value (implementation details unclear)
    } else {
        // Different branch when p2[3] != 0
        int p2_val = p2[0];
        if (p2_val == p2[3]) {
            int* param3_data = (int*)p3[3];
            int* param3_base = (int*)(*param3_data);
            int offset = param3_base[0] + 0x80;
            float* target_location = (float*)((char*)index + offset);
            
            int p2_field = p2[1];
            void* data_source;
            if (p2_field == -1) {
                // Use some default data location
                extern void* lbl_801EADC8;
                data_source = &lbl_801EADC8;
            } else {
                // Calculate with p2_field + 0x80
                data_source = (void*)((char*)index + p2_field + 0x80);
            }
            
            int multiplier = p2[2];
            
            // Load float from data source and perform conversion
            float source_value = *(float*)data_source;
            
            // Convert multiplier to double via 4330 magic number method
            union {
                struct { unsigned int hi, lo; } parts;
                double d;
            } temp;
            temp.parts.hi = 0x43300000;
            temp.parts.lo = (unsigned int)multiplier;
            
            // Magic number subtraction for integer to double conversion
            double double_multiplier = temp.d - 4503599627370496.0; // 0x43300000 00000000
            
            // Final calculation
            float result = (float)double_multiplier * source_value;
            
            // Convert to integer and back for truncation
            int int_result = (int)result;
            int existing_value = *(int*)data_source;
            int final_result = existing_value + int_result;
            *(int*)data_source = final_result;
        }
    }
}