#include "ffcc/pppColMove.h"

extern int lbl_8032ED70;

typedef struct {
    short x;
    short y;
    short z;
    short w;
} pppColMoveVec4S;

typedef struct {
    int id;
    int pad;
    pppColMoveVec4S move;
} pppColMoveInput;

/*
 * --INFO--
 * PAL Address: 0x80065000
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMoveCon(void* param1, void* param2)
{
    int* data = ((int**)param2)[3];
    pppColMoveVec4S* target = (pppColMoveVec4S*)((char*)param1 + data[1] + 0x80);

    target->w = 0;
    target->z = 0;
    target->y = 0;
    target->x = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80065028
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColMove(void* param1, void* param2, void* param3)
{
    extern int lbl_8032ED70;
    
    int** ptr_array = (int**)param3;
    int* ptr0 = ptr_array[3];  // Load from offset 0xC

    int* ptr_src = (int*)ptr0[0]; // Load from offset 0x0
    int* ptr_dest = (int*)ptr0[1]; // Load from offset 0x4
    
    // Calculate offsets
    ptr_src = (int*)((char*)ptr_src + 0x80);
    ptr_dest = (int*)((char*)ptr_dest + 0x80);
    short* src = (short*)((char*)param1 + (int)ptr_src);
    short* dest = (short*)((char*)param1 + (int)ptr_dest);

    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* param2_int = (int*)param2;
    int* param1_int = (int*)param1;
    
    if (param2_int[0] == param1_int[3]) {
        // Update movement values
        short* movement = (short*)((char*)param2 + 0x8);
        
        dest[0] += movement[0];  // x
        dest[1] += movement[1];  // y
        dest[2] += movement[2];  // z
        dest[3] += movement[3];  // w
    }

    src[0] += dest[0];  // x
    src[1] += dest[1];  // y  
    src[2] += dest[2];  // z
    src[3] += dest[3];  // w
}
