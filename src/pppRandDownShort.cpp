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
    // Check global flag first - early return if zero
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) return;
    
    // Cast parameters based on register usage (r3->r30, r4->r31, r5->r29) 
    u8* param1 = (u8*)r3;  // r30
    u8* param2 = (u8*)r4;  // r31
    u8* param3 = (u8*)r5;  // r29
    
    // Check param1[0xc] - branch based on zero/non-zero
    u32 p1_field_c = *(u32*)(param1 + 0xc);
    if (p1_field_c == 0) {
        // First branch: param1[0xc] == 0
        math.RandF();  // Generates value in f1
        f32 result = -0.0f;  // fneg f31, f1 - placeholder for negative of random value
        
        // Check param2[0xa] byte
        u8 p2_field_a = *(u8*)(param2 + 0xa);
        if (p2_field_a != 0) {
            math.RandF();  // Second random call
            extern f32 lbl_8032FF78;
            f32 temp = result - 1.0f;  // fsubs f1, f31, f1 
            result = temp * lbl_8032FF78;  // fmuls f31, f1, f0
        }
        
        // Store result at calculated address
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 offset = *base_ptr + 0x80;
        f32* target = (f32*)(param1 + offset);
        *target = result;
        
    } else {
        // Second branch: param1[0xc] != 0
        // Check if param2[0] matches param1[0xc]
        u32 p2_field_0 = *(u32*)param2;
        if (p2_field_0 != p1_field_c) return;
        
        // Calculate base address
        u32* p3_field_c = (u32*)(param3 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 base_offset = *base_ptr + 0x80;
        
        // Determine target pointer based on param2[4]
        s32 p2_field_4 = *(s32*)(param2 + 4);
        s16* target_ptr;
        
        if (p2_field_4 == -1) {
            extern s16 lbl_801EADC8;
            target_ptr = &lbl_801EADC8;
        } else {
            target_ptr = (s16*)(param1 + p2_field_4 + 0x80);
        }
        
        // Get multiplier and current values
        u16 multiplier = *(u16*)(param2 + 8);
        f32 base_val = *(f32*)(param1 + base_offset);
        s16 current_short = *target_ptr;
        
        // Float arithmetic following assembly pattern
        f32 mult_f = (f32)multiplier;
        f32 product = mult_f * base_val;
        s16 delta = (s16)product;
        
        // Update target
        *target_ptr = current_short + delta;
    }
}