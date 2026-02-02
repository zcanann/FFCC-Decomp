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
    _pppPObject* obj = pObject;
    PDrawMdl* mdl = drawMdl;
    
    unsigned int value = *(unsigned int*)((char*)mdl + 0x4);
    if ((value >> 16) == 0xffff) {
        return;
    }
    
    void* ctrlPtr = *(void**)((char*)ctrlTable + 0xc);
    pppCVECTOR* vector = (pppCVECTOR*)((char*)obj + 0x40);
    unsigned char blendMode = *(unsigned char*)((char*)mdl + 0x9);
    
    pppFMATRIX* matrix = (pppFMATRIX*)(*(void**)ctrlPtr);
    unsigned char param10 = *(unsigned char*)((char*)mdl + 0xd);
    unsigned char saved_blend = blendMode;
    matrix = (pppFMATRIX*)((char*)matrix + 0x88);
    matrix = (pppFMATRIX*)((char*)obj + (int)matrix);
    
    float scale = *(float*)((char*)mdl + 0x10);
    unsigned char alpha = *(unsigned char*)((char*)mdl + 0xe);
    unsigned char param5 = *(unsigned char*)((char*)mdl + 0x14);
    unsigned char param6 = *(unsigned char*)((char*)mdl + 0xa);
    unsigned char param8 = *(unsigned char*)((char*)mdl + 0xb);
    unsigned char param9 = *(unsigned char*)((char*)mdl + 0xc);
    
    pppSetDrawEnv(vector, matrix, scale, alpha, param5, param6, saved_blend, param8, param9, param10);
    
    pppSetBlendMode(saved_blend);
    
    unsigned int modelIndex = *(unsigned int*)((char*)mdl + 0x4);
    extern void* lbl_8032ED54;
    void** modelsArray = (void**)*(void**)((char*)&lbl_8032ED54 + 0x8);
    Vec* vertexData = (Vec*)((char*)obj + 0x70);
    pppModelSt* model = (pppModelSt*)modelsArray[modelIndex];
    pppDrawMesh(model, vertexData, 1);
}
