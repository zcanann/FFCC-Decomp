#include "ffcc/pppRandUpShort.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_80330038; 
extern double lbl_80330040;
extern short lbl_801EADC8;

/*
 * --INFO--
 * PAL Address: 0x80062fa0
 * PAL Size: 300b
 */
void pppRandUpShort(void* param1, void* param2, void* param3)
{
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    int* p1 = (int*)param1;
    unsigned char* p2 = (unsigned char*)param2;
    void** p3 = (void**)param3;
    
    if (p1[3] == 0) {
        register float f31 asm("f31");
        
        math.RandF();
        // Assume f31 gets the result from RandF()
        
        if (p2[0xA] != 0) {
            math.RandF();
            // f31 += second RandF result
        }
        
        f31 *= lbl_80330038;
        
        void** ptr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*ptr;
        int offset = *indexPtr + 0x80;
        ((float*)param1)[offset/4] = f31;
        
    } else {
        int field0 = ((int*)param2)[0];
        if (field0 != p1[3]) {
            return;
        }
        
        void** ptr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*ptr;
        int offset = *indexPtr + 0x80;
        float* sourceAddr = (float*)((char*)param1 + offset);
        
        int field4 = ((int*)param2)[1];
        short* targetShort;
        if (field4 == -1) {
            targetShort = &lbl_801EADC8;
        } else {
            targetShort = (short*)((char*)param1 + field4 + 0x80);
        }
        
        short multiplier = ((short*)param2)[4];
        float sourceValue = *sourceAddr;
        short currentValue = *targetShort;
        
        double multiplierD = (double)multiplier;
        double result = (multiplierD - lbl_80330040) * sourceValue;
        *targetShort = currentValue + (short)(int)result;
    }
}