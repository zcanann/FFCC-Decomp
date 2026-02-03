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
    void** dataPtr = (void**)((char*)param2 + 0xC);
    void* data = *dataPtr;
    void* shapeData = (void*)((char*)param1 + *(int*)data + 0x80);
    
    *(short*)((char*)shapeData + 0x4) = 0;
    *(short*)((char*)shapeData + 0x2) = 0; 
    *(short*)((char*)shapeData + 0x0) = 0;
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
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    void** dataPtr = (void**)((char*)param3 + 0xC);
    int* indexPtr = (int*)*dataPtr;
    void* shapeData = (void*)((char*)param1 + *indexPtr + 0x80);
    
    short type = *(short*)((char*)param2 + 0x4);
    
    if ((unsigned short)type == 0xFFFF) {
        return;
    }
    
    void* globalData = lbl_8032ED54;
    void** shapeArray = (void**)((char*)globalData + 0xC);
    void* shapeInfo = (void*)((char*)*shapeArray + (type * 4));
    void* shapeSpec = *(void**)shapeInfo;
    
    short currentId = *(short*)((char*)shapeData + 0x2);
    *(short*)((char*)shapeData + 0x4) = currentId;
    
    short currentVal = *(short*)shapeData;
    int deltaVal = *(int*)((char*)param2 + 0x8);
    short newVal = currentVal + deltaVal;
    *(short*)shapeData = newVal;
    
    short maxVal = *(short*)((char*)shapeSpec + (currentId * 8) + 0x10 + 0x2);
    if (newVal >= maxVal) {
        newVal = newVal - maxVal;
        *(short*)shapeData = newVal;
    }
    
    short counter = *(short*)((char*)shapeData + 0x2);
    short newCounter = counter + 1;
    *(short*)((char*)shapeData + 0x2) = newCounter;
    
    short upperBound = *(short*)((char*)shapeSpec + 0x6);
    if (newCounter >= upperBound) {
        unsigned char flags = *(unsigned char*)((char*)shapeSpec + (currentId * 8) + 0x10 + 0x4);
        if (flags & 0x80) {
            *(short*)((char*)shapeData + 0x0) = 0;
            *(short*)((char*)shapeData + 0x2) = 0;
        } else {
            *(short*)shapeData = 0;
            *(short*)((char*)shapeData + 0x2) = counter;
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
    void** dataPtr = (void**)((char*)param3 + 0xC);
    int* indexPtr = (int*)*dataPtr;
    void* shapeData = (void*)((char*)param1 + *indexPtr + 0x80);
    void* posData = (void*)((char*)param1 + *(int*)((char*)*dataPtr + 0x4) + 0x80);
    
    short type = *(short*)((char*)param2 + 0x4);
    
    if ((unsigned short)type == 0xFFFF) {
        return;
    }
    
    void* globalData = lbl_8032ED54;
    void** shapeArray = (void**)((char*)globalData + 0xC);
    void* shapeInfo = (void*)((char*)*shapeArray + (type * 4));
    void* shapeSpec = *(void**)shapeInfo;
    
    short currentId = *(short*)((char*)shapeData + 0x4);
    void* currentShape = (void*)((char*)shapeSpec + (currentId * 8) + 0x10);
    
    void* materialData = *(void**)((char*)globalData + 0x4);
    
    float scale = *(float*)((char*)param2 + 0x10);
    unsigned char blendMode = *(unsigned char*)((char*)param2 + 0xD);
    unsigned char alpha = *(unsigned char*)((char*)param2 + 0xE);
    unsigned char r = *(unsigned char*)((char*)param2 + 0x14);
    unsigned char g = *(unsigned char*)((char*)param2 + 0x15);
    
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        posData, (void*)((char*)param1 + 0x40), scale, blendMode, alpha, blendMode, r, g, 0, 0);
    
    pppSetBlendMode__FUc(blendMode);
    
    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(currentShape, materialData, blendMode);
}