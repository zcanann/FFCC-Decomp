#include "ffcc/pppColor.h"

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 */
void pppColor(void* param1, void* param2, void* param3)
{
    void** ptr_struct2 = (void**)param2;
    void* work_ptr = ((void**)ptr_struct2[3])[0];
    unsigned char* base_ptr = (unsigned char*)param1 + (unsigned int)work_ptr;
    
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        unsigned int id1 = *(unsigned int*)param2;
        unsigned int id2 = *(unsigned int*)((unsigned char*)param1 + 12);
        
        if (id1 == id2) {
            short* src_colors = (short*)((unsigned char*)param2 + 8);
            *(short*)(base_ptr + 0) += src_colors[0];
            *(short*)(base_ptr + 2) += src_colors[1]; 
            *(short*)(base_ptr + 4) += src_colors[2];
            *(short*)(base_ptr + 6) += src_colors[3];
        }
        
        extern float lbl_8032ED50;
        float* scale_data = &lbl_8032ED50;
        
        *(unsigned char*)(base_ptr + 8) = (unsigned char)((float)(*(short*)(base_ptr + 0)) / 128.0f * scale_data[14]);
        *(unsigned char*)(base_ptr + 9) = (unsigned char)((float)(*(short*)(base_ptr + 2)) / 128.0f * scale_data[15]);
        *(unsigned char*)(base_ptr + 10) = (unsigned char)((float)(*(short*)(base_ptr + 4)) / 128.0f * scale_data[16]);
        *(unsigned char*)(base_ptr + 11) = (unsigned char)((float)(*(short*)(base_ptr + 6)) / 128.0f * scale_data[17]);
    } else {
        *(unsigned char*)(base_ptr + 8) = (unsigned char)(*(short*)(base_ptr + 0) >> 7);
        *(unsigned char*)(base_ptr + 9) = (unsigned char)(*(short*)(base_ptr + 2) >> 7);
        *(unsigned char*)(base_ptr + 10) = (unsigned char)(*(short*)(base_ptr + 4) >> 7);
        *(unsigned char*)(base_ptr + 11) = (unsigned char)(*(short*)(base_ptr + 6) >> 7);
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
    unsigned char* base_ptr = (unsigned char*)param1 + (unsigned int)work_ptr;
    
    *(short*)(base_ptr + 0) = 0;
    *(short*)(base_ptr + 2) = 0;
    *(short*)(base_ptr + 4) = 0;
    *(short*)(base_ptr + 6) = 0;
}