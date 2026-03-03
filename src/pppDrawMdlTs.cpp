#include "ffcc/pppDrawMdlTs.h"
#include "ffcc/materialman.h"
#include "ffcc/pppPart.h"
#include "dolphin/types.h"

extern "C" {
extern int lbl_8032ED70;
extern void* lbl_8032ED54;
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
    void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void pppSetBlendMode__FUc(unsigned char);
void pppDrawMesh__FP10pppModelStP3Veci(void*, void*, int);
}

extern CMaterialMan MaterialMan;

// Use simple forward declarations and casting approach

/*
 * --INFO--
 * PAL Address: 0x800880c0
 * PAL Size: 48b
 */
void pppDrawMdlTsCon(struct _pppPObject* obj, struct PDrawMdlTs* data)
{
    // Access nested structure: data->field_at_0xc->field_at_0x8 + 0x80
    void* inner = *((void**)((char*)data + 0xc));
    void* inner2 = *((void**)((char*)inner + 0x8));
    float* texCoords = (float*)((char*)obj + (int)inner2 + 0x80);
    
    // Initialize all 6 texture coordinates to 0.0
    texCoords[0] = 0.0f; // offset 0x0
    texCoords[1] = 0.0f; // offset 0x4  
    texCoords[2] = 0.0f; // offset 0x8
    texCoords[3] = 0.0f; // offset 0xc
    texCoords[4] = 0.0f; // offset 0x10
    texCoords[5] = 0.0f; // offset 0x14
}

/*
 * --INFO--
 * PAL Address: 0x800880a0  
 * PAL Size: 32b
 */
void pppDrawMdlTsCon3(struct _pppPObject* obj, struct PDrawMdlTs* data)
{
    // Access nested structure: data->field_at_0xc->field_at_0x8 + 0x80
    void* inner = *((void**)((char*)data + 0xc));
    void* inner2 = *((void**)((char*)inner + 0x8));  
    float* texCoords = (float*)((char*)obj + (int)inner2 + 0x80);
    
    // Initialize specific texture coordinates to 0.0
    texCoords[2] = 0.0f; // offset 0x8  
    texCoords[5] = 0.0f; // offset 0x14
}

/*
 * --INFO--
 * PAL Address: 0x80087fd0
 * PAL Size: 208b
 */
void pppDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct PDrawMdlTs* param)
{
    struct PDrawMdlTs* stream = param;
    struct PDrawMdlTs* input = data;

    // Get texture coordinate offset 
    void* inner = *((void**)((char*)stream + 0xc));
    void* inner2 = *((void**)((char*)inner + 0x8));
    float* texCoords = (float*)((char*)obj + (int)inner2 + 0x80);
    
    // Check global flag - return early if set
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    // Update texture coordinates by adding param values
    texCoords[1] += texCoords[2];  // offset 0x4 += offset 0x8
    texCoords[0] += texCoords[1];  // offset 0x0 += offset 0x4
    texCoords[4] += texCoords[5];  // offset 0x10 += offset 0x14
    texCoords[3] += texCoords[4];  // offset 0xc += offset 0x10
    
    // Check if object id matches
    int objId = *((int*)input);
    int objFieldC = *((int*)((char*)obj + 0xc));
    if (objId != objFieldC) {
        return;
    }
    
    // Apply parameter offsets to texture coordinates
    texCoords[0] += *((float*)((char*)input + 0x14));  // offset 0x0
    texCoords[1] += *((float*)((char*)input + 0x18));  // offset 0x4
    texCoords[2] += *((float*)((char*)input + 0x1c));  // offset 0x8
    texCoords[3] += *((float*)((char*)input + 0x20));  // offset 0xc
    texCoords[4] += *((float*)((char*)input + 0x24));  // offset 0x10
    texCoords[5] += *((float*)((char*)input + 0x28));  // offset 0x14
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawDrawMdlTs0(_pppPObject*, PDrawMdlTs*, _pppCtrlTable*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80087ef0 
 * PAL Size: 224b
 */
void pppDrawDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl)
{
    if ((*(u32*)((u8*)data + 4) >> 16) == 0xFFFF) {
        return;
    }

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)obj + *(int*)*(int**)((u8*)ctrl + 0xC) + 0x88,
        (u8*)obj + 0x40,
        *(float*)((u8*)data + 0x10),
        *(u8*)((u8*)data + 0x2C),
        *(u8*)((u8*)data + 0xA),
        *(u8*)((u8*)data + 0x9),
        *(u8*)((u8*)data + 0xB),
        *(u8*)((u8*)data + 0xC),
        *(u8*)((u8*)data + 0xD),
        *(u8*)((u8*)data + 0xE));

    float* texCoords = (float*)((u8*)obj + *(int*)*(int**)((u8*)ctrl + 0xC + 0x8) + 0x80);
    MaterialMan.SetTexScroll(texCoords[0], texCoords[3], 0.0f, 0.0f);

    pppSetBlendMode__FUc(*(u8*)((u8*)data + 0x9));

    void** modelsArray = *(void***)((u8*)lbl_8032ED54 + 0x8);
    pppDrawMesh__FP10pppModelStP3Veci(modelsArray[*(u32*)((u8*)data + 0x4)], (u8*)obj + 0x70, 1);
}
