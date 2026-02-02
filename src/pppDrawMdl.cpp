#include "ffcc/pppDrawMdl.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawMdl0(_pppPObject*, PDrawMdl*, _pppCtrlTable*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80065384
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMdl(_pppPObject* pObject, PDrawMdl* drawMdl, _pppCtrlTable* ctrlTable)
{
    // Load value from drawMdl offset 0x4 and check if high 16 bits are 0xffff
    unsigned int value = *(unsigned int*)((char*)drawMdl + 0x4);
    if ((value >> 16) == 0xffff) {
        return;
    }
    
    // Extract byte parameters from drawMdl structure at various offsets
    unsigned char alpha = *(unsigned char*)((char*)drawMdl + 0xe);
    unsigned char blendMode = *(unsigned char*)((char*)drawMdl + 0x9);
    unsigned char param5 = *(unsigned char*)((char*)drawMdl + 0x14);
    unsigned char param6 = *(unsigned char*)((char*)drawMdl + 0xa);
    unsigned char param7 = *(unsigned char*)((char*)drawMdl + 0x9);
    unsigned char param8 = *(unsigned char*)((char*)drawMdl + 0xb);
    unsigned char param9 = *(unsigned char*)((char*)drawMdl + 0xc);
    unsigned char param10 = *(unsigned char*)((char*)drawMdl + 0xd);
    
    // Load float parameter from offset 0x10
    float scale = *(float*)((char*)drawMdl + 0x10);
    
    // Get vector parameter (pObject + 0x40)
    pppCVECTOR* vector = (pppCVECTOR*)((char*)pObject + 0x40);
    
    // Get matrix parameter from ctrlTable structure
    void* ctrlPtr = *(void**)((char*)ctrlTable + 0xc);
    pppFMATRIX* matrix = (pppFMATRIX*)(*(void**)ctrlPtr);
    matrix = (pppFMATRIX*)((char*)matrix + 0x88);
    matrix = (pppFMATRIX*)((char*)pObject + (int)matrix);
    
    // Call pppSetDrawEnv with all parameters
    pppSetDrawEnv(vector, matrix, scale, alpha, param5, param6, param7, param8, param9, param10);
    
    // Set blend mode
    pppSetBlendMode(blendMode);
    
    // Get model array and draw mesh
    extern void* lbl_8032ED54;  // Global models array reference
    void** modelsArray = (void**)*(void**)((char*)&lbl_8032ED54 + 0x8);
    unsigned int modelIndex = *(unsigned int*)((char*)drawMdl + 0x4);
    pppModelSt* model = (pppModelSt*)modelsArray[modelIndex];
    Vec* vertexData = (Vec*)((char*)pObject + 0x70);
    pppDrawMesh(model, vertexData, 1);
}
