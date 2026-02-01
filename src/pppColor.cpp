#include "ffcc/pppColor.h"

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 */
void pppColor(void* param1, void* param2, void* param3)
{
    // Complex color processing function - needs proper implementation
    // Based on assembly, processes color blending and format conversion
}

/*
 * --INFO--
 * PAL Address: 0x8005FF8C  
 * PAL Size: 40b
 */
void pppColorCon(void* param1, void* param2)
{
    // Constructor function that initializes color work structure
    // Zeros out 4 short values based on assembly analysis
    void** ptr_struct = (void**)param2;
    void* work_ptr = ((void**)ptr_struct[3])[0];
    unsigned char* base = (unsigned char*)param1;
    unsigned int offset = (unsigned int)work_ptr + 0x80;
    _pppColorWork* color_work = (_pppColorWork*)(base + offset);
    
    color_work->a = 0;
    color_work->b = 0; 
    color_work->g = 0;
    color_work->r = 0;
}