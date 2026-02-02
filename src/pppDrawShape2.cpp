#include "ffcc/pppDrawShape2.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);

/*
 * --INFO--
 * PAL Address: 0x800daadc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2Construct(void* param1, void* param2)
{
    // Get data structure and initialize shape values to 0
    void** dataPtr = (void**)((char*)param2 + 0xC);
    void* data = *dataPtr;
    void* shapeData = (void*)((char*)param1 + *(int*)data + 0x80);
    
    // Initialize shape counters
    *(short*)((char*)shapeData + 0x0) = 0;
    *(short*)((char*)shapeData + 0x2) = 0; 
    *(short*)((char*)shapeData + 0x4) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800daa10
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcShape2(void* param1, void* param2, void* param3)
{
    // Check global disable flag
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Get shape data 
    void** dataPtr = (void**)((char*)param3 + 0xC);
    int* indexPtr = (int*)*dataPtr;
    void* shapeData = (void*)((char*)param1 + *indexPtr + 0x80);
    
    // Get type from param2
    int type = *(int*)((char*)param2 + 0x4);
    
    // Check if type is valid (not 0xFFFF)
    if ((unsigned short)type == 0xFFFF) {
        return;
    }
    
    // Get shape info from global data
    void* globalData = lbl_8032ED54;
    void** shapeArray = (void**)((char*)globalData + 0xC);
    void* shapeInfo = (void*)((char*)*shapeArray + (type * 4));
    void* shapeSpec = *(void**)shapeInfo;
    
    // Update shape id
    short currentId = *(short*)((char*)shapeData + 0x2);
    *(short*)((char*)shapeData + 0x4) = currentId;
    
    // Get current and target values  
    short currentVal = *(short*)shapeData;
    int deltaVal = *(int*)((char*)param2 + 0x8);
    short newVal = currentVal + deltaVal;
    *(short*)shapeData = newVal;
    
    // Check bounds
    short maxVal = *(short*)((char*)shapeSpec + ((currentId * 8) + 0x10) + 0x2);
    if (newVal >= maxVal) {
        newVal = newVal - maxVal;
        *(short*)shapeData = newVal;
    }
    
    // Update counter
    short counter = *(short*)((char*)shapeData + 0x2);
    *(short*)((char*)shapeData + 0x2) = counter + 1;
    
    // Check upper bound  
    short upperBound = *(short*)((char*)shapeSpec + 0x6);
    if (counter + 1 >= upperBound) {
        // Check reset flag
        unsigned char flags = *(unsigned char*)((char*)shapeSpec + ((currentId * 8) + 0x10) + 0x4);
        if (flags & 0x80) {
            // Reset both counters
            *(short*)((char*)shapeData + 0x0) = 0;
            *(short*)((char*)shapeData + 0x2) = 0;
        } else {
            // Just reset main counter, decrement secondary
            *(short*)shapeData = 0;
            *(short*)((char*)shapeData + 0x2) = counter - 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800da93c  
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2(void* param1, void* param2, void* param3)
{
    // Get shape data
    void** dataPtr = (void**)((char*)param3 + 0xC);
    int* indexPtr = (int*)*dataPtr;
    int baseOffset = *indexPtr + 0x80;
    int nextOffset = *(int*)((char*)*dataPtr + 0x4) + 0x80;
    
    void* shapeData = (void*)((char*)param1 + baseOffset);
    void* posData = (void*)((char*)param1 + nextOffset);
    
    // Get type from param2  
    int type = *(int*)((char*)param2 + 0x4);
    
    // Check if type is valid
    if ((unsigned short)type == 0xFFFF) {
        return;
    }
    
    // Get shape info
    void* globalData = lbl_8032ED54;
    void** shapeArray = (void**)((char*)globalData + 0xC);
    void* shapeInfo = (void*)((char*)*shapeArray + (type * 4)); 
    void* shapeSpec = *(void**)shapeInfo;
    
    // Get current shape ID and calculate shape pointer
    short currentId = *(short*)((char*)shapeData + 0x4);
    void* currentShape = (void*)((char*)shapeSpec + (currentId * 8) + 0x10);
    
    // Get material set
    void* materialData = *(void**)((char*)globalData + 0x4);
    
    // Set up drawing environment  
    float scale = *(float*)((char*)param2 + 0x10);
    unsigned char blendMode = *(unsigned char*)((char*)param2 + 0xD);
    unsigned char alpha = *(unsigned char*)((char*)param2 + 0xE);
    unsigned char r = *(unsigned char*)((char*)param2 + 0x14);
    unsigned char g = *(unsigned char*)((char*)param2 + 0x15);
    
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        posData, (void*)((char*)param1 + 0x40), scale, blendMode, alpha, blendMode, r, g, 0, 0);
    
    // Set blend mode
    pppSetBlendMode__FUc(blendMode);
    
    // Draw the shape
    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(currentShape, materialData, blendMode);
}