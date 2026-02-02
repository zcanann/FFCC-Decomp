#include "ffcc/pppRandUpFV.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330000;
extern float lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x800629e8
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void randf(float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800629e8
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpFV(void* param1, void* param2, void* param3)
{
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;

    // Check global flag first
    if (lbl_8032ED70 != 0) {
        return;
    }

    // Check field at offset 0xC of param1 
    if (p1[3] == 0) {
        // Generate random float
        math.RandF();
        float randVal = 0.5f; // Positive placeholder for "up" version
        
        // Check byte at offset 0x18 of param2
        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[0x18] != 0) {
            // Generate second random and add
            math.RandF();
            float randVal2 = 0.5f; // Second placeholder
            randVal = (randVal + randVal2) * lbl_80330000;
        }
        
        // Store result based on param3
        void** basePtr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*basePtr;
        int offset = *indexPtr + 0x80;
        float* target = (float*)((char*)param1 + offset);
        *target = randVal;
        
    } else {
        // Check if param2[0] matches param1[3]
        if (p2[0] != p1[3]) {
            return;
        }
        
        // Get addresses
        void** basePtr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*basePtr;
        int destOffset = *indexPtr + 0x80;
        float* destAddr = (float*)((char*)param1 + destOffset);
        
        // Determine source address
        float* srcAddr;
        if (p2[1] == -1) {
            srcAddr = &lbl_801EADC8;
        } else {
            srcAddr = (float*)((char*)param1 + p2[1] + 0x80);
        }
        
        // Load values and perform arithmetic
        float multiplier1 = *(float*)((char*)param2 + 8);
        float destVal = *destAddr;
        float srcVal1 = *srcAddr;
        
        // Update first component
        float result1 = srcVal1 + (multiplier1 * destVal);
        *srcAddr = result1;
        
        // Update second component 
        float multiplier2 = *(float*)((char*)param2 + 12);
        float srcVal2 = *(float*)((char*)srcAddr + 4);
        float result2 = srcVal2 + (multiplier2 * destVal);
        *(float*)((char*)srcAddr + 4) = result2;
        
        // Update third component
        float multiplier3 = *(float*)((char*)param2 + 16);
        float srcVal3 = *(float*)((char*)srcAddr + 8);
        float result3 = srcVal3 + (multiplier3 * destVal);
        *(float*)((char*)srcAddr + 8) = result3;
    }
}