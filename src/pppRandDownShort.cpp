#include "ffcc/pppRandDownShort.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80061c1c
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownShort(void* r3, void* r4, void* r5)
{
    // Check global flag first - assembly shows early return if this is 0
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) return;
    
    // Cast parameters based on register usage (r3->r30, r4->r31, r5->r29)
    u8* param1 = (u8*)r3;  // r30
    u8* param2 = (u8*)r4;  // r31  
    u8* param3 = (u8*)r5;  // r29
    
    // Check param1[0xc] - if zero, take first branch
    u32 p1_field_c = *(u32*)(param1 + 0xc);
    if (p1_field_c == 0) {
        // Generate random numbers
        math.RandF();
        f32 randomVal = 0.0f; // Placeholder since RandF() is void
        
        // Check param2[0xa] byte
        u8 p2_field_a = *(u8*)(param2 + 0xa);
        if (p2_field_a != 0) {
            math.RandF();
            // Do some calculation with second random
            extern f32 lbl_8032FF78;
            randomVal = randomVal * lbl_8032FF78;
        }
        
        // Calculate target address and store result
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 offset = *base_ptr + 0x80;
        f32* target = (f32*)(param1 + offset);
        *target = randomVal;
        
    } else {
        // Check if param2[0] matches param1[0xc]
        u32 p2_field_0 = *(u32*)param2;
        if (p2_field_0 != p1_field_c) return;
        
        // Calculate target memory location
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 base_offset = *base_ptr + 0x80;
        
        // Get param2[4]
        s32 p2_field_4 = *(s32*)(param2 + 4);
        s16* target_ptr;
        
        if (p2_field_4 == -1) {
            extern s16 lbl_801EADC8;
            target_ptr = &lbl_801EADC8;
        } else {
            target_ptr = (s16*)(param1 + p2_field_4 + 0x80);
        }
        
        // Get param2[8] (multiplier)
        u16 multiplier = *(u16*)(param2 + 8);
        
        // Load current values and do arithmetic
        f32 mem_val = *(f32*)(param1 + base_offset);
        s16 current_short = *target_ptr;
        
        // Float conversion and arithmetic from assembly
        extern f64 lbl_8032FF80;  // Used for float conversion
        f32 mult_f = (f32)multiplier;
        f32 result = mult_f * mem_val;
        s16 delta = (s16)result;
        
        // Store result back
        *target_ptr = current_short + delta;
    }
}