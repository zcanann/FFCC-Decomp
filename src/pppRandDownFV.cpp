#include "ffcc/pppRandDownFV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80061664
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownFV(void* r3, void* r4, void* r5)
{
    // Check global initialization flag first
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) return;
    
    u8* param1 = (u8*)r3;  // r29
    u8* param2 = (u8*)r4;  // r31  
    u8* param3 = (u8*)r5;  // r30
    
    // Check param2[0xc] - if zero, generate random value
    u32 p2_field_c = *(u32*)(param2 + 0xc);
    if (p2_field_c == 0) {
        // Generate random number
        math.RandF();
        float randomVal = -0.0f;  // fneg f31, f1
        
        // Check param2[0x18] byte for second condition
        u8 p2_field_18 = *(u8*)(param2 + 0x18);
        if (p2_field_18 != 0) {
            math.RandF();
            // fsubs f1, f31, f1; fmuls f31, f1, f0
            extern float lbl_8032FF40;
            randomVal = randomVal * lbl_8032FF40;
        }
        
        // Calculate target address and store result
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 offset = *base_ptr + 0x80;
        float* target = (float*)(param1 + offset);
        *target = randomVal;
        
    } else {
        // Check if param2[0] matches param2[0xc]
        u32 p2_field_0 = *(u32*)param2;
        if (p2_field_0 != p2_field_c) return;
        
        // Calculate target memory location for vector operations
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 base_offset = *base_ptr + 0x80;
        float* base_vec = (float*)(param1 + base_offset);
        
        // Get param2[4] for vector selection
        s32 p2_field_4 = *(s32*)(param2 + 4);
        float* target_vec;
        
        if (p2_field_4 == -1) {
            extern float lbl_801EADC8;
            target_vec = &lbl_801EADC8;
        } else {
            target_vec = (float*)(param1 + p2_field_4 + 0x80);
        }
        
        // Load force values from param2[0x8, 0xc, 0x10]
        float force_x = *(float*)(param2 + 0x8);
        float force_y = *(float*)(param2 + 0xc);  
        float force_z = *(float*)(param2 + 0x10);
        
        // Apply force to vector components (x, y, z at offsets 0, 4, 8)
        float scale_factor = *(float*)base_vec;
        target_vec[0] = target_vec[0] + (force_x * scale_factor);
        target_vec[1] = target_vec[1] + (force_y * scale_factor);
        target_vec[2] = target_vec[2] + (force_z * scale_factor);
    }
}