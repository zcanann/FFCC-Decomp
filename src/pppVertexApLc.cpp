#include "ffcc/pppVertexApLc.h"

/*
 * --INFO--
 * PAL Address: 0x80064f4c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApLcCon(_pppPObject* obj, PVertexApLc* apLc)
{
    // Initialize vertex application light counter data
    void** apLc_data = (void**)((char*)apLc + 0xc);
    void** data_base = (void**)*apLc_data;
    void* data_ptr = *data_base;
    data_ptr = (char*)data_ptr + 0x80;
    short* target = (short*)((char*)obj + (int)data_ptr);
    target[0] = 0;
    target[1] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80064ce8  
 * PAL Size: 612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppVertexApLc(_pppPObject* obj, PVertexApLc* apLc, Vec* vec)
{
    void** apLc_data = (void**)((char*)apLc + 0xc);
    void* vertex_data = *(void**)(*apLc_data);
    
    // Early return if no vertex data
    if (!vertex_data) {
        return;
    }
    
    // Early return if vertex index is negative
    short vertex_index = *(short*)((char*)apLc + 4);
    if (vertex_index < 0) return;
    
    unsigned char vertex_count = *(unsigned char*)((char*)apLc + 6);
    unsigned char i = 0;
    
    while (i < vertex_count) {
        vertex_count--;
        if (vertex_count == 0) return;
        i++;
    }
}
