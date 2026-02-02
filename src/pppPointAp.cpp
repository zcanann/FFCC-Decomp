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
    int offset = data[1] + 0x81;
    ((char*)param1)[offset] = 0;
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
    int** data = (int**)((char*)param3 + 0xc);
    int* data_ptr = *data;
    float* coords1 = (float*)(data_ptr + 0);
    float* coords2 = (float*)(data_ptr + 1);
    
    // Calculate base pointers with offset 0x80
    char* base1 = (char*)param1 + (int)coords1[0] + 0x80;  
    char* base2 = (char*)param1 + (int)coords2[0] + 0x80;
    
    // Check for global condition
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) {
        // Check flag at offset +1 from base2
        if (*(base2 + 1) == 0) {
            // Check for valid object ID
            int obj_id = ((int*)param2)[1];
            if (obj_id != 0xFFFF) {
                // Create object
                extern int lbl_8032ED50;
                int* mgr = (int*)&lbl_8032ED50;
                void* obj_data = (void*)(mgr[0x34/4] + (obj_id * 16));
                if (obj_data) {
                    // Call object creation function
                    extern void* pppCreatePObject__FP9_pppMngStP12_pppPDataVal(void* mgr, void* data);
                    void* obj = pppCreatePObject__FP9_pppMngStP12_pppPDataVal(mgr, obj_data);
                    if (obj) {
                        ((void**)obj)[1] = param1;
                        
                        // Handle coordinate transformation
                        char transform_flag = ((char*)param2)[0xd];
                        int offset = ((int*)param2)[2];
                        float* dest_coords = (float*)((char*)obj + offset + 0x80);
                        
                        if (transform_flag == 0) {
                            // Direct copy of 3 floats
                            dest_coords[0] = coords1[0];
                            dest_coords[1] = coords1[1]; 
                            dest_coords[2] = coords1[2];
                        } else {
                            // Matrix transformation
                            extern void PSMTXMultVec(void* mtx, void* src, void* dst);
                            PSMTXMultVec((void*)((char*)&lbl_8032ED50 + 0x78), coords1, dest_coords);
                        }
                        
                        // Set flag from param2
                        char flag_val = ((char*)param2)[0xc];
                        *(base2 + 1) = flag_val;
                    }
                }
            }
        }
        
        // Decrement counter flag
        char* counter_ptr = base2 + 1;
        if (*counter_ptr > 0) {
            (*counter_ptr)--;
        }
    }
}