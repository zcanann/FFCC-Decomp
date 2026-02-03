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
void pppRandDownFV(void* param1, void* param2, void* param3)
{
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) return;
    
    u8* r29 = (u8*)param1;
    u8* r31 = (u8*)param2;  
    u8* r30 = (u8*)param3;
    
    u32 p2_field_c = *(u32*)(r31 + 0xc);
    if (p2_field_c == 0) {
        float f31;
        math.RandF();
        f31 = 0.0f;
        f31 = -f31;  // fneg
        
        u8 p2_field_18 = *(u8*)(r31 + 0x18);
        if (p2_field_18 != 0) {
            math.RandF();
            extern float lbl_8032FF40;
            float f1 = f31 - f1;  // fsubs f1, f31, f1
            f31 = f1 * lbl_8032FF40; // fmuls f31, f1, f0
        }
        
        u32* p3_field_c = (u32*)(r30 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 offset = *base_ptr + 0x80;
        float* target = (float*)(r29 + offset);
        *target = f31;
        
    } else {
        u32 p2_field_0 = *(u32*)r31;
        if (p2_field_0 != p2_field_c) return;
        
        u32* p3_field_c = (u32*)(r30 + 0xc);
        u32* base_ptr = (u32*)*p3_field_c;
        u32 base_offset = *base_ptr + 0x80;
        float* base_vec = (float*)(r29 + base_offset);
        
        s32 p2_field_4 = *(s32*)(r31 + 4);
        float* target_vec;
        
        if (p2_field_4 == -1) {
            extern float lbl_801EADC8;
            target_vec = &lbl_801EADC8;
        } else {
            target_vec = (float*)(r29 + p2_field_4 + 0x80);
        }
        
        float force_x = *(float*)(r31 + 0x8);
        float force_y = *(float*)(r31 + 0xc);  
        float force_z = *(float*)(r31 + 0x10);
        
        float scale_factor = *base_vec;
        force_x *= scale_factor;
        target_vec[0] += force_x;
        force_y *= scale_factor;
        target_vec[1] += force_y;
        force_z *= scale_factor;
        target_vec[2] += force_z;
    }
}