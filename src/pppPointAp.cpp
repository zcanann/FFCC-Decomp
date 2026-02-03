#include "ffcc/pppPointAp.h"

/*
 * --INFO--
 * PAL Address: 0x80060d08
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointApCon(void* param1, void* param2)
{
    int** param2_ptr = (int**)param2;
    int* data = (int*)param2_ptr[3];
    int base_addr = data[1];
    ((char*)param1 + base_addr)[0x81] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060c04
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppPointAp(void* param1, void* param2, void* param3)
{
    // Extract data from param3
    int** data_ptr = (int**)((char*)param3 + 0xc);
    float* src_data = (float*)*data_ptr;
    
    // Convert float to int for indexing - this generates fctiwz
    int index = (int)src_data[1];
    char* target_ptr = (char*)param1 + index + 0x80;
    
    // Check for global condition
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) {
        // Check flag at target location
        if (target_ptr[1] == 0) {
            // Check for valid object ID
            int obj_id = ((int*)param2)[1];
            if (obj_id != 0xFFFF) {
                // Create object
                extern int lbl_8032ED50;
                int* mgr_ptr = (int*)&lbl_8032ED50;
                void* obj_data = (void*)(mgr_ptr[0x34/4] + (obj_id * 16));
                if (obj_data) {
                    // Call object creation function
                    extern void* pppCreatePObject__FP9_pppMngStP12_pppPDataVal(void* mgr, void* data);
                    void* obj = pppCreatePObject__FP9_pppMngStP12_pppPDataVal(&lbl_8032ED50, obj_data);
                    if (obj) {
                        ((void**)obj)[1] = param1;
                        
                        // Handle coordinate transformation
                        signed char transform_flag = ((signed char*)param2)[0xd];
                        int offset = ((int*)param2)[2];
                        float* dest_coords = (float*)((char*)obj + offset + 0x80);
                        
                        if (transform_flag == 0) {
                            // Direct copy of 3 floats from source data
                            dest_coords[0] = src_data[0];
                            dest_coords[1] = src_data[1]; 
                            dest_coords[2] = src_data[2];
                        } else {
                            // Matrix transformation
                            extern void PSMTXMultVec(void* mtx, void* src, void* dst);
                            PSMTXMultVec((void*)((char*)&lbl_8032ED50 + 0x78), src_data, dest_coords);
                        }
                        
                        // Set flag from param2
                        unsigned char flag_val = ((unsigned char*)param2)[0xc];
                        target_ptr[1] = flag_val;
                    }
                }
            }
        }
        
        // Decrement counter flag
        signed char count = target_ptr[1];
        if (count > 0) {
            target_ptr[1] = count - 1;
        }
    }
}