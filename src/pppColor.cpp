#include "ffcc/pppColor.h"

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 */
void pppColor(void* param1, void* param2, void* param3)
{
    void** ptr_struct2 = (void**)param2;
    void** ptr_struct3 = (void**)param3;
    void* work_ptr2 = ((void**)ptr_struct2[3])[0];
    void* work_ptr3 = ((void**)ptr_struct3[3])[0];
    unsigned char* base = (unsigned char*)param1;
    
    _pppColorWork* color_work = (_pppColorWork*)((unsigned char*)work_ptr2 + 0x80 + (unsigned int)base);
    
    // Check global state flag from param3
    extern int lbl_8032ED70; // Global state flag
    if (lbl_8032ED70 != 0) {
        // Blend mode - add color values from param2 structure
        unsigned int id1 = *(unsigned int*)param2;
        unsigned int id2 = *(unsigned int*)((unsigned char*)param1 + 12);
        
        if (id1 == id2) {
            // IDs match, perform color addition
            short* src_colors = (short*)((unsigned char*)param2 + 8);
            color_work->r += src_colors[0];
            color_work->g += src_colors[1]; 
            color_work->b += src_colors[2];
            color_work->a += src_colors[3];
        }
        
        // Convert to byte values with scaling
        extern float lbl_8032ED50; // Color scaling data
        float* scale_data = &lbl_8032ED50;
        
        unsigned char r_byte = (unsigned char)((float)color_work->r / 128.0f * scale_data[14]);
        unsigned char g_byte = (unsigned char)((float)color_work->g / 128.0f * scale_data[15]);
        unsigned char b_byte = (unsigned char)((float)color_work->b / 128.0f * scale_data[16]);
        unsigned char a_byte = (unsigned char)((float)color_work->a / 128.0f * scale_data[17]);
        
        color_work->result.m_colorRGBA[0] = r_byte;
        color_work->result.m_colorRGBA[1] = g_byte;
        color_work->result.m_colorRGBA[2] = b_byte;
        color_work->result.m_colorRGBA[3] = a_byte;
    } else {
        // Simple mode - direct conversion
        color_work->result.m_colorRGBA[0] = (unsigned char)(color_work->r >> 7);
        color_work->result.m_colorRGBA[1] = (unsigned char)(color_work->g >> 7);
        color_work->result.m_colorRGBA[2] = (unsigned char)(color_work->b >> 7);
        color_work->result.m_colorRGBA[3] = (unsigned char)(color_work->a >> 7);
    }
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
    unsigned char* base = (unsigned char*)param1;
    _pppColorWork* color_work = (_pppColorWork*)((unsigned char*)work_ptr + 0x80 + (unsigned int)base);
    
    color_work->r = 0;
    color_work->g = 0;
    color_work->b = 0;
    color_work->a = 0;
}