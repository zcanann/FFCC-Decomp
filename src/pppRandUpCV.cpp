#include "ffcc/pppRandUpCV.h"
#include "ffcc/math.h"

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80062708
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpCV(void* param1, void* param2, void* param3) {
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;
    float multiplier;
    
    // Check global state variable
    extern int lbl_8032ED70;
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Check if first param matches third param offset
    if (p2[0] != p1[3]) {
        if (p2[0] == -1) {
            // Use global default color
            extern unsigned char lbl_801EADC8[4];
            unsigned char* color = lbl_801EADC8;
            
            // Process color components 
            if (((unsigned char*)p2)[12] != 0) {
                math.RandF();
                math.RandF();
                multiplier = 0.5f; // Simplified placeholder
            }
            
            // Get base value
            float* basePtr = (float*)((unsigned char*)p3[3] + 0x80 + p1[0]);
            float baseValue = *basePtr;
            
            // Update color components
            for (int i = 0; i < 4; i++) {
                signed char delta = ((signed char*)p2)[8 + i];
                unsigned char currentColor = color[i];
                
                float variation = (float)delta * baseValue;
                int newValue = currentColor + (int)variation;
                
                color[i] = (unsigned char)newValue;
            }
        } else {
            // Use computed base address
            unsigned char* base = (unsigned char*)p1 + 0x80 + p2[1];
            
            // Get base value
            float* basePtr = (float*)((unsigned char*)p3[3] + 0x80 + p1[0]);
            float baseValue = *basePtr;
            
            // Update color components
            for (int i = 0; i < 4; i++) {
                signed char delta = ((signed char*)p2)[8 + i];
                unsigned char currentColor = base[i];
                
                float variation = (float)delta * baseValue;
                int newValue = currentColor + (int)variation;
                
                base[i] = (unsigned char)newValue;
            }
        }
    }
}

/*
 * --INFO--
 * Address: TODO  
 * Size: TODO
 */
void randchar(char, float)
{
    // TODO - appears to be unused based on objdiff
}