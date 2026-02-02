#include "ffcc/pppRandDownInt.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;

// Forward declaration to handle return type mismatch
extern "C" float RandF__5CMathFv();

/*
 * --INFO--
 * PAL Address: 0x80066ab4
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownInt(int index, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;
    
    // Check if p2[3] (fieldC) is null
    if (p2[3] == 0) {
        // Generate random value
        float randValue = RandF__5CMathFv();
        randValue = -randValue;
        
        // Check byte at offset 0xC of param2
        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[0xC] != 0) {
            float rand2 = RandF__5CMathFv();
            randValue = randValue - rand2;
            randValue = randValue * 100.0f; // Constant from lbl_8032FF58
        }
        
        // Store result
        if (p3[3] != 0) { // If p3->fieldC exists
            int* p3_data = (int*)p3[3]; // p3->fieldC
            int offset = p3_data[0] + 0x80;
            float* target = (float*)((char*)&index + offset);
            *target = randValue;
        }
    } else {
        // Check if p2[0] matches value from p2[3]
        int* p2_data = (int*)p2[3];
        if (p2[0] == p2_data[0]) {
            if (p3[3] != 0) {
                int* p3_data = (int*)p3[3];
                int offset = p3_data[0] + 0x80;
                // Store result here too
            }
        }
    }
    
    // Process p2[1] (field4)
    if (p2[1] != -1) {
        int offset1 = p2[1] + 0x80;
        int* target = (int*)((char*)&index + offset1);
        
        int multiplier = p2[2]; // field8
        
        // Get value from p3 structure
        int* p3_data = (int*)p3[3];
        int offset2 = p3_data[0] + 0x80;
        float* source = (float*)((char*)p3_data + offset2);
        
        // Calculate result
        int result = (int)(*source * (float)multiplier) + *target;
        *target = result;
    }
}