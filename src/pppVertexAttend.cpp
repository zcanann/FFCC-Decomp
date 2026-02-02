#include "ffcc/pppVertexAttend.h"
#include "dolphin/mtx.h"

/*
 * --INFO--
 * PAL Address: 0x80064f6c
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexAttend(void* r3, void* r4, void* r5)
{
    s16 count = *(s16*)((u8*)r4 + 0xc);
    if (count < 0) {
        return;
    }
    
    void** data = (void**)((u8*)r5 + 0xc);
    void* data1 = data[0];
    void* data2 = data[1];
    
    void* lbl_8032ED54 = *(void**)((u8*)r5 + 0x10);
    void* matrix_ptr = (void*)((u8*)lbl_8032ED54 + (count << 3));
    
    s16 matrix_index = *(s16*)matrix_ptr;
    void* matrix_data_ptr = (void*)((u32*)((u8*)lbl_8032ED54 + 8) + (matrix_index << 2));
    void* vertex_data = (void*)((u32*)matrix_data_ptr + 11);
    
    u16 vertex_index = *(u16*)((u8*)r3 + (*(u32*)data1 + 0x80));
    vertex_index <<= 1;
    
    u16 vertex_offset = *(u16*)((u8*)data2 + vertex_index);
    vertex_offset *= 12;
    
    Vec* vertex_src = (Vec*)((u8*)vertex_data + vertex_offset);
    Vec result;
    Mtx* matrix = (Mtx*)((u8*)r3 + 4 + 16);
    
    PSMTXMultVec(*matrix, vertex_src, &result);
    
    Vec* output = (Vec*)((u8*)r3 + (*(u32*)data2 + 0x80));
    *output = result;
}