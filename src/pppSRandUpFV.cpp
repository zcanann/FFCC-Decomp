#include "ffcc/pppSRandUpFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_803300C0;
extern float lbl_801EADC8[];

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randfloat(float f1, float f2)
{
    // Basic random float implementation
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void randf(unsigned char param)
{
    // Basic random function with byte parameter
}

/*
 * --INFO--
 * PAL Address: 0x800643a4
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandUpFV(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) return;
    
    int* field_c = (int*)((char*)param1 + 0xC);
    if (*field_c == 0) {
        // Generate random vector using param3 for offset calculation
        int* param3_field_c = (int*)((char*)param3 + 0xC);
        int* param3_data = (int*)*param3_field_c;
        float* vector_ptr = (float*)((char*)param1 + *param3_data + 0x80);
        
        unsigned char flag = *((unsigned char*)param2 + 0x18);
        
        // X component - generate random value
        math.RandF();
        float rand_val = 1.0f; // Placeholder - will be filled by RandF
        if (flag != 0) {
            math.RandF(); 
            float rand_val2 = 1.0f; // Second random value
            rand_val = (rand_val + rand_val2) * lbl_803300C0;
        }
        vector_ptr[0] = rand_val;
        
        // Y component - reload flag and generate random
        flag = *((unsigned char*)param2 + 0x18);
        math.RandF();
        rand_val = 1.0f; // Placeholder - will be filled by RandF
        if (flag != 0) {
            math.RandF();
            float rand_val2 = 1.0f; // Second random value  
            rand_val = (rand_val + rand_val2) * lbl_803300C0;
        }
        vector_ptr[1] = rand_val;
        
        // Z component - reload flag and generate random
        flag = *((unsigned char*)param2 + 0x18);
        math.RandF();
        rand_val = 1.0f; // Placeholder - will be filled by RandF
        if (flag != 0) {
            math.RandF();
            float rand_val2 = 1.0f; // Second random value
            rand_val = (rand_val + rand_val2) * lbl_803300C0;
        }
        vector_ptr[2] = rand_val;
    } else {
        // Check param2 field matches param1 field
        int param2_field = *(int*)param2;
        if (param2_field != *field_c) return;
        
        // Use param3 for vector offset calculation
        int* param3_field_c = (int*)((char*)param3 + 0xC);
        int* param3_data = (int*)*param3_field_c;
        float* vector_ptr = (float*)((char*)param1 + *param3_data + 0x80);
        
        // Vector scaling operations - only in else branch
        int field_4 = *((int*)param2 + 1);
        float* scale_ptr;
        if (field_4 == -1) {
            scale_ptr = lbl_801EADC8;
        } else {
            scale_ptr = (float*)((char*)param1 + field_4 + 0x80);
        }
        
        // Apply vector operations with scale factors from param2
        float scale_x = *((float*)param2 + 2);
        float scale_y = *((float*)param2 + 3);  
        float scale_z = *((float*)param2 + 4);
        
        scale_ptr[0] += scale_x * vector_ptr[0];
        scale_ptr[1] += scale_y * vector_ptr[1];
        scale_ptr[2] += scale_z * vector_ptr[2];
    }
}