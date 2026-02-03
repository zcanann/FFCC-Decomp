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
    
    if (((int*)param1)[3] == 0) {
        float f31;
        
        math.RandF();
        // f31 = f1 result from RandF
        
        if (((unsigned char*)param2)[0xA] != 0) {
            math.RandF();
            // f31 += f1 result from second RandF
        }
        
        // f31 *= lbl_80330038
        // Store result at calculated address
        void** ptr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*ptr;
        int index = *indexPtr;
        ((float*)((char*)param1 + index + 0x80))[0] = f31;
        
    } else {
        int field0 = ((int*)param2)[0];
        int param1_field3 = ((int*)param1)[3];
        
        if (field0 != param1_field3) {
            return;
        }
        
        void** ptr = (void**)((char*)param3 + 0xC);
        int* indexPtr = (int*)*ptr;
        int index = *indexPtr;
        float* sourceAddr = (float*)((char*)param1 + index + 0x80);
        
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
        
        *targetShort = currentValue + (short)(int)((double)multiplier - lbl_80330040) * sourceValue;
    }
}