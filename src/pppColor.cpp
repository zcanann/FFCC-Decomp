#include "ffcc/pppColor.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 */
void pppColor(void* param1, void* param2, void* param3)
{
    void** ptr_struct2 = (void**)param3;
    void* work_ptr = ((void**)ptr_struct2[3])[0];
    _pppColorWork* work = (_pppColorWork*)((char*)param1 + (u32)work_ptr + 0x80);
    
    if (lbl_8032ED70 == 0) {
        goto shift_result;
    }

    {
        u32 id1 = *(u32*)param2;
        u32 id2 = *(u32*)((char*)param1 + 12);

        if (id1 == id2) {
            short* src_colors = (short*)((char*)param2 + 8);
            work->r += src_colors[0];
            work->g += src_colors[1];
            work->b += src_colors[2];
            work->a += src_colors[3];
        }

        if (((u8*)lbl_8032ED50)[0xef] == 0) {
            goto shift_result;
        }

        work->result.r = (u8)((float)(work->r >> 7) * ((float*)lbl_8032ED50)[14]);
        work->result.g = (u8)((float)(work->g >> 7) * ((float*)lbl_8032ED50)[15]);
        work->result.b = (u8)((float)(work->b >> 7) * ((float*)lbl_8032ED50)[16]);
        work->result.a = (u8)((float)(work->a >> 7) * ((float*)lbl_8032ED50)[17]);
        return;
    }

shift_result:
    work->result.r = (u8)(work->r >> 7);
    work->result.g = (u8)(work->g >> 7);
    work->result.b = (u8)(work->b >> 7);
    work->result.a = (u8)(work->a >> 7);
}

/*
 * --INFO--
 * PAL Address: 0x8005FF8C  
 * PAL Size: 40b
 */
void pppColorCon(void* param1, void* param2)
{
    void** ptr_struct = (void**)param2;
    void* work_ptr = ((void**)ptr_struct[3])[0];
    _pppColorWork* work = (_pppColorWork*)((char*)param1 + (u32)work_ptr + 0x80);
    
    work->a = 0;
    work->b = 0;
    work->g = 0;
    work->r = 0;
}
