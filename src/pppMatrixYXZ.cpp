#include "ffcc/pppMatrixYXZ.h"

/*
 * --INFO--
 * PAL Address: 0x800604c0
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppMatrixYXZ(void* matrix_ptr, void* param2, void* param3)
{
    // Extract pointer structure from param3
    void** ptr_array = (void**)param3;
    void** data_ptrs = (void**)ptr_array[3];  // offset 0xC
    
    void* ptr0 = data_ptrs[0];  // offset 0x0
    void* ptr1 = data_ptrs[1];  // offset 0x4  
    void* ptr2 = data_ptrs[2];  // offset 0x8
    
    // Calculate vector pointers (add 0x80 offset to each)
    float* vec0 = (float*)((char*)matrix_ptr + (int)ptr0 + 0x80);
    float* vec1 = (float*)((char*)matrix_ptr + (int)ptr1 + 0x80);
    float* vec2 = (float*)((char*)matrix_ptr + (int)ptr2 + 0x80);
    
    // Call pppGetRotMatrixYXZ with matrix+0x10 offset
    pppGetRotMatrixYXZ((void*)((char*)matrix_ptr + 0x10), vec0);
    
    // Create temporary vectors on stack for scaling operations
    float temp_vec1[3];
    float temp_vec2[3];  
    float temp_vec3[3];
    
    // First scaling operation using vec1[0]
    temp_vec1[0] = ((float*)matrix_ptr)[4];   // matrix offset 0x10
    temp_vec1[1] = ((float*)matrix_ptr)[8];   // matrix offset 0x20  
    temp_vec1[2] = ((float*)matrix_ptr)[12];  // matrix offset 0x30
    PSVECScale(temp_vec1, temp_vec1, vec1[0]);
    
    // Store results back to matrix
    ((float*)matrix_ptr)[4] = temp_vec1[0];   // matrix offset 0x10
    ((float*)matrix_ptr)[8] = temp_vec1[1];   // matrix offset 0x20
    ((float*)matrix_ptr)[12] = temp_vec1[2];  // matrix offset 0x30
    
    // Second scaling operation using vec1[1]  
    temp_vec2[0] = ((float*)matrix_ptr)[5];   // matrix offset 0x14
    temp_vec2[1] = ((float*)matrix_ptr)[9];   // matrix offset 0x24
    temp_vec2[2] = ((float*)matrix_ptr)[13];  // matrix offset 0x34
    PSVECScale(temp_vec2, temp_vec2, vec1[1]);
    
    // Store results back to matrix
    ((float*)matrix_ptr)[5] = temp_vec2[0];   // matrix offset 0x14
    ((float*)matrix_ptr)[9] = temp_vec2[1];   // matrix offset 0x24
    ((float*)matrix_ptr)[13] = temp_vec2[2];  // matrix offset 0x34
    
    // Third scaling operation using vec1[2]
    temp_vec3[0] = ((float*)matrix_ptr)[6];   // matrix offset 0x18
    temp_vec3[1] = ((float*)matrix_ptr)[10];  // matrix offset 0x28
    temp_vec3[2] = ((float*)matrix_ptr)[14];  // matrix offset 0x38
    PSVECScale(temp_vec3, temp_vec3, vec1[2]);
    
    // Store results back to matrix
    ((float*)matrix_ptr)[6] = temp_vec3[0];   // matrix offset 0x18
    ((float*)matrix_ptr)[10] = temp_vec3[1];  // matrix offset 0x28
    ((float*)matrix_ptr)[14] = temp_vec3[2];  // matrix offset 0x38
    
    // Copy vec2 data to matrix translation component
    ((float*)matrix_ptr)[7] = vec2[0];   // matrix offset 0x1C
    ((float*)matrix_ptr)[11] = vec2[1];  // matrix offset 0x2C
    ((float*)matrix_ptr)[15] = vec2[2];  // matrix offset 0x3C
}