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
        // First RandF call
        math.RandF();
        
        // Check byte at offset 0xc of param2 (second parameter)
        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[12] != 0) {
            // Second RandF call
            math.RandF();
        }
        
        // Work with param3 data
        int* param3_data = (int*)p3[3]; // lwz r3, 0xc(r29) then lwz r3, 0x0(r3)
        if (param3_data) {
            int offset = param3_data[0] + 0x80; // addi r5, r3, 0x80
            float* target_location = (float*)((char*)index + offset); // add r5, r30, r5
            // Store some calculated floating point value
        }
    } else {
        // Different branch when p2[3] != 0
        int p2_val = p2[0]; // lwz r0, 0x0(r31)
        if (p2_val == p2[3]) {
            // Process param3 differently
            int* param3_data = (int*)p3[3];
            if (param3_data) {
                // More complex calculations
                int p2_field = p2[1]; // lwz r3, 0x4(r31)
                if (p2_field == -1) {
                    // Use some default data
                } else {
                    // Calculate with p2_field + 0x80
                    int calculated_offset = p2_field + 0x80;
                    // Use calculated offset
                }
                
                // Integer conversion operations (fctiwz in assembly)
                int p2_mult = p2[2]; // lwz r3, 0x8(r31)
                // Complex floating point to integer conversion
            }
        }
    }
}