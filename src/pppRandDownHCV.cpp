#include "ffcc/pppRandDownHCV.h"
#include "ffcc/math.h"

extern CMath math;

extern "C" {

/*
 * --INFO--
 * Address: TODO
 * Size: TODO
 */
void randshort(short value, float multiplier)
{
    // Simple random short generation function
}

/*
 * --INFO--
 * PAL Address: 80061794
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownHCV(void* param1, void* param2, void* param3)
{
    // External references from assembly
    extern int lbl_8032ED70;
    extern short lbl_801EADC8[4]; // Vector data from assembly
    extern float lbl_8032FF48;    // Constant 0.5f from assembly
    extern float lbl_8032FF50;    // Double constant from assembly
    
    // Parameter register assignments from assembly
    void* r30 = param1;  // r30 in original
    void* r31 = param2;  // r31 in original  
    void* r29 = param3;  // r29 in original
    
    // Check global flag - matches assembly cmpwi r0, 0x0 + bne
    if (lbl_8032ED70 == 0) {
        return;
    }
    
    // Assembly: lwz r3, 0x0(r31) vs lwz r0, 0xc(r30) + cmpw
    int* r31_int = (int*)r31;
    int* r30_int = (int*)r30; 
    if (r31_int[0] == r30_int[3]) {
        // First branch - random generation path
        math.RandF(); // bl RandF__5CMathFv
        float randVal = -1.0f; // fneg f31, f1 (placeholder for RandF result)
        
        // Assembly: lbz r0, 0x10(r31) + cmplwi r0, 0x0 + beq
        unsigned char* r31_bytes = (unsigned char*)r31;
        if (r31_bytes[0x10] != 0) {
            math.RandF(); // Second RandF call
            float randVal2 = 1.0f; // Placeholder for second RandF
            randVal = (-randVal - randVal2) * lbl_8032FF48; // fsubs + fmuls with 0.5f
        }
        
        // Assembly: lwz r3, 0xc(r29) + lwz r3, 0x0(r3) + addi r5, r3, 0x80
        int** r29_ptr = (int**)((char*)r29 + 0xc);
        int* base = *r29_ptr;
        int offset = *base + 0x80;
        float* target = (float*)((char*)r30 + offset);
        
        // Assembly: stfs f31, 0x0(r5)
        *target = randVal;
        
    } else if (r31_int[0] != r30_int[3]) {
        // Second branch - direct coordinate manipulation 
        int** r29_ptr = (int**)((char*)r29 + 0xc);
        int* base = *r29_ptr;
        int offset = *base + 0x80;
        
        // Assembly: lwz r3, 0x4(r31) + cmpwi r3, -0x1
        short* sourceData;
        if (r31_int[1] == -1) {
            sourceData = lbl_801EADC8; // Global constant vector
        } else {
            sourceData = (short*)((char*)r30 + r31_int[1] + 0x80);
        }
        
        // Get scale factor for coordinate transformations
        float* scalePtr = (float*)((char*)r30 + offset);
        float scale = *scalePtr;
        
        // Process each coordinate component (assembly shows 4 identical patterns)
        char* r31_bytes = (char*)r31;
        
        // X: lha r3, 0x8(r31) + math operations + sth r0, 0x0(r4)
        short srcX = *(short*)(r31_bytes + 0x8);
        short result = sourceData[0] + (short)(srcX * scale);
        sourceData[0] = result;
        
        // Y: lha r0, 0xa(r31) + math operations + sth r0, 0x2(r4)  
        short srcY = *(short*)(r31_bytes + 0xa);
        result = sourceData[1] + (short)(srcY * scale);
        sourceData[1] = result;
        
        // Z: lha r0, 0xc(r31) + math operations + sth r0, 0x4(r4)
        short srcZ = *(short*)(r31_bytes + 0xc);
        result = sourceData[2] + (short)(srcZ * scale);
        sourceData[2] = result;
        
        // W: lha r0, 0xe(r31) + math operations + sth r0, 0x6(r4)
        short srcW = *(short*)(r31_bytes + 0xe);
        result = sourceData[3] + (short)(srcW * scale);
        sourceData[3] = result;
    }
}

}