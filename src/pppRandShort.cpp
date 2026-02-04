#include "ffcc/pppRandShort.h"
#include "ffcc/math.h"

extern "C" {

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FFC8;
extern short lbl_801EADC8[];

/*
 * --INFO--
 * PAL Address: 0x8006249c
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandShort(void* arg0, void* arg1, void* arg2)
{
    if (lbl_8032ED70 == 0) {
        return;
    }
    
    int* p0 = (int*)arg0;
    int* p1 = (int*)arg1;
    int** p2 = (int**)arg2;
    
    int val = p0[3];
    
    if (val == 0) {
        math.RandF();
        float f = 0.0f; // Placeholder for random value
        
        if (*(unsigned char*)((char*)arg1 + 10) != 0) {
            math.RandF();
            f += 0.0f; // Add second random value
        } else {
            f *= lbl_8032FFC8;
        }
        
        int** base = (int**)((char*)arg2 + 12);
        float* target = (float*)((char*)*base + val + 0x80);
        *target = f;
        return;
    }
    
    if (p1[0] != val) {
        return;
    }
    
    short* addr;
    if (p1[1] == -1) {
        addr = lbl_801EADC8;
    } else {
        int** base = (int**)((char*)arg2 + 12);
        addr = (short*)((char*)*base + p1[1] + 0x80);
    }
    
    short current = *addr;
    short range = *(short*)((char*)arg1 + 8);
    
    int** base = (int**)((char*)arg2 + 12);
    float memVal = *(float*)((char*)*base + val + 0x80);
    
    float result = (float)current + ((float)range * memVal - (float)current);
    *addr = (short)result;
}

}