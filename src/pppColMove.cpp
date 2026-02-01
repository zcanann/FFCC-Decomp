#include "ffcc/pppColMove.h"

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 */
void pppColMoveCon(void* param1, void* param2)
{
    int** ptr_array = (int**)param2;
    int* target_ptr = ptr_array[3];  // Load from offset 0xC
    target_ptr = (int*)target_ptr[1]; // Load from offset 0x4 
    target_ptr = (int*)((char*)target_ptr + 0x80);
    short* target = (short*)((char*)param1 + (int)target_ptr);
    
    target[0] = 0;  // offset 0x0
    target[1] = 0;  // offset 0x2 
    target[2] = 0;  // offset 0x4
    target[3] = 0;  // offset 0x6
}

/*
 * --INFO--
 * PAL Address: 0x80065028
 * PAL Size: 188b
 */
void pppColMove(void* param1, void* param2, void* param3)
{
    extern int lbl_8032ED70;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* param2_int = (int*)param2;
    int* param1_int = (int*)param1;
    
    if (param2_int[0] == param1_int[3]) {  // Compare param2[0] with param1[0xC]
        // Skip the movement update block
    } else {
        // Update movement values
        short* movement = (short*)((char*)param2 + 0x8);
        
        int** ptr_array = (int**)param3;
        int* ptr0 = ptr_array[3];  // Load from offset 0xC
        int* ptr1 = (int*)ptr0[1]; // Load from offset 0x4
        ptr1 = (int*)((char*)ptr1 + 0x80);
        short* target = (short*)((char*)param1 + (int)ptr1);
        
        target[0] += movement[0];  // x
        target[1] += movement[1];  // y
        target[2] += movement[2];  // z
        target[3] += movement[3];  // w
    }
    
    // Always perform this addition
    int** ptr_array = (int**)param3;
    int* ptr0 = ptr_array[3];  // Load from offset 0xC
    int* ptr_src = (int*)ptr0[0]; // Load from offset 0x0
    int* ptr_dest = (int*)ptr0[1]; // Load from offset 0x4
    ptr_src = (int*)((char*)ptr_src + 0x80);
    ptr_dest = (int*)((char*)ptr_dest + 0x80);
    
    short* src = (short*)((char*)param1 + (int)ptr_src);
    short* dest = (short*)((char*)param1 + (int)ptr_dest);
    
    src[0] += dest[0];  // x
    src[1] += dest[1];  // y  
    src[2] += dest[2];  // z
    src[3] += dest[3];  // w
}