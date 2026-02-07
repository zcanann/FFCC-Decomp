#include "ffcc/pppDrawMdlTs.h"

// Basic types
typedef unsigned char u8;
typedef unsigned short u16;  
typedef unsigned int u32;

extern int lbl_8032ED70;  // Global state flag

// Forward declarations for external functions
extern void pppSetDrawEnv(void* pos, void* matrix, float scale, u8 r, u8 g, u8 b, u8 a, u8 e1, u8 e2, u8 e3);
extern void pppSetBlendMode(u8 mode);
extern void pppDrawMesh(void* model, void* pos, int flag);

// External structs/globals
struct MaterialManager {
    void SetTexScroll(float f1, float f2, float f3, float f4);
};
extern MaterialManager MaterialMan;

struct GlobalData {
    void** field_at_0x8;
};
extern GlobalData lbl_8032ED54;

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
    // Check if texture ID is valid (not 0xffff)
    short texId = *((short*)((char*)data + 0x4));
    if ((texId & 0xffff0000) == 0xffff0000) {
        return;
    }
    
    // Setup drawing environment using simple pointer arithmetic
    u8 blendMode = *((u8*)((char*)data + 0xe));
    void* position = (void*)((char*)obj + 0x40);
    
    void* inner = *((void**)((char*)ctrl + 0xc)); 
    void* inner2 = *((void**)inner);
    void* drawPos = (void*)((char*)inner2 + 0x88);
    void* finalPos = (void*)((char*)obj + (int)drawPos);
    
    float scale = *((float*)((char*)data + 0x10));
    u8 r = *((u8*)((char*)data + 0x2c));
    u8 g = *((u8*)((char*)data + 0xa));   
    u8 b = *((u8*)((char*)data + 0x9));   
    u8 a = *((u8*)((char*)data + 0xb));   
    u8 env1 = *((u8*)((char*)data + 0xc));   
    u8 env2 = *((u8*)((char*)data + 0xd));
    
    pppSetDrawEnv(finalPos, position, scale, r, g, b, a, env1, env2, blendMode);
    
    // Setup texture scrolling
    void* matInner = *((void**)((char*)ctrl + 0xc));
    void* texCoordPtr = *((void**)((char*)matInner + 0x8));
    float* texCoords = (float*)((char*)obj + (int)texCoordPtr + 0x80);
    
    MaterialMan.SetTexScroll(texCoords[0], texCoords[3], 0.0f, 0.0f);
    
    // Set blend mode
    pppSetBlendMode(blendMode);
    
    // Draw mesh
    int meshId = *((int*)((char*)data + 0x4));
    void* model = lbl_8032ED54.field_at_0x8[meshId];
    void* objPos = (void*)((char*)obj + 0x70);
    
    pppDrawMesh(model, objPos, 1);
}
