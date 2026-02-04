#include "ffcc/pppColMove.h"

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 */
void pppColMoveCon(void* param1, void* param2)
{
    int** ptr_array = (int**)param2;
    int* temp_ptr = ptr_array[3];  // Load from offset 0xC
    temp_ptr = (int*)temp_ptr[1]; // Load from offset 0x4 
    short* target = (short*)((char*)param1 + (int)temp_ptr + 0x80);
    
    target[3] = 0;  // offset 0x6
    target[2] = 0;  // offset 0x4
    target[1] = 0;  // offset 0x2 
    target[0] = 0;  // offset 0x0
}

/*
 * --INFO--
 * PAL Address: 0x80065028
 * PAL Size: 188b
 */
void pppColMove(void* param1, void* param2, void* param3)
{
    extern int lbl_8032ED70;
    
    int** ptr_array = (int**)param3;
    int* ptr0 = ptr_array[3];  // Load from offset 0xC
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* ptr_src = (int*)ptr0[0]; // Load from offset 0x0
    int* ptr_dest = (int*)ptr0[1]; // Load from offset 0x4
    
    // Calculate offsets
    ptr_src = (int*)((char*)ptr_src + 0x80);
    ptr_dest = (int*)((char*)ptr_dest + 0x80);
    short* src = (short*)((char*)param1 + (int)ptr_src);
    short* dest = (short*)((char*)param1 + (int)ptr_dest);
    
    int* param2_int = (int*)param2;
    int* param1_int = (int*)param1;
    
    if (param2_int[0] == param1_int[3]) {  // Inverted comparison
        // Skip the movement update section
        goto do_final_add;
    }
    
    // Update movement values
    short* movement = (short*)((char*)param2 + 0x8);
    
    dest[0] += movement[0];  // x
    dest[1] += movement[1];  // y
    dest[2] += movement[2];  // z
    dest[3] += movement[3];  // w

do_final_add:
    // Always perform this addition
    src[0] += dest[0];  // x
    src[1] += dest[1];  // y  
    src[2] += dest[2];  // z
    src[3] += dest[3];  // w
}