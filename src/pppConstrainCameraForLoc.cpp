#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

// External references
extern int DAT_8032ec70;
extern float FLOAT_803331a8;
extern void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec*);

extern int DAT_8032ed70;

// Function signatures from Ghidra decomp
extern "C" int GetModelPtr__FP8CGObject(CGObject*);
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, void*, void*, void*, void*, void*);

/*
 * --INFO--
 * PAL Address: 80167eec
 * PAL Size: 580b
 */
void CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void*)
{
    float* params = (float*)param_2;
    
    // Local variables matching Ghidra decompilation structure
    Vec local_a4, local_e0, local_ec;
    Vec local_bc;
    Mtx MStack_98, MStack_68;
    float local_b0, local_ac, local_a8;
    
    // Load scale parameter
    float scale = *params;
    
    // Get some basic CameraPcs data (simplified access)
    unsigned char* cameraPcsPtr = (unsigned char*)&CameraPcs;
    float* cameraDirPtr = (float*)(cameraPcsPtr + 0xec); // approximate offset for direction
    float* cameraPosPtr = (float*)(cameraPcsPtr + 0xe0); // approximate offset for position
    
    // Load direction values
    local_b0 = cameraDirPtr[0];
    local_ac = cameraDirPtr[1]; 
    local_a8 = cameraDirPtr[2];
    
    // Load position values  
    local_bc.x = cameraPosPtr[0];
    local_bc.y = cameraPosPtr[1];
    local_bc.z = cameraPosPtr[2];
    
    // Calculate scaled direction
    local_a4.x = scale * local_b0;
    local_a4.y = scale * local_ac;
    local_a4.z = scale * local_a8;
    
    // Add position to scaled direction
    PSVECAdd(&local_bc, &local_a4, &local_a4);
    
    // Get offset values from params
    float offsetX = *(float*)((char*)params + 0x1c);
    float offsetY = *(float*)((char*)params + 0x2c);
    
    // Simple offset calculations
    local_e0.x = offsetX;
    local_e0.y = offsetX;
    local_e0.z = offsetX;
    
    local_ec.x = offsetY;
    local_ec.y = offsetY;
    local_ec.z = offsetY;
    
    // Add offsets
    PSVECAdd(&local_a4, &local_e0, &local_a4);
    PSVECAdd(&local_a4, &local_ec, &local_a4);
    
    // Store results in params 
    params[7] = local_a4.x;
    params[11] = local_a4.y;
    params[15] = local_a4.z;
}

/*
 * --INFO--
 * PAL Address: 0x80167E70
 * PAL Size: 48b
 */
void pppConstructConstrainCameraForLoc(void)
{
	// pppMngStPtr points to a structure, access CGObject at offset 0xd8
	CGObject* obj = *(CGObject**)((char*)pppMngStPtr + 0xd8);
	int modelPtr = GetModelPtr__FP8CGObject(obj);
	*(int*)(modelPtr + 0xec) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80167EA0
 * PAL Size: 36b
 */
void pppConstruct2ConstrainCameraForLoc(void)
{
	// TODO - implement based on Ghidra decomp
}

/*
 * --INFO--
 * PAL Address: 0x80167DD4
 * PAL Size: 156b
 */
void pppDestructConstrainCameraForLoc(void)
{
	if (DAT_8032ed70 == 0) {
		// Based on Ghidra decomp pattern
		CGObject* obj = *(CGObject**)((char*)pppMngStPtr + 0xd8);
		int modelPtr = GetModelPtr__FP8CGObject(obj);
		
		// Set up callback
		*(void**)(modelPtr + 0xec) = (void*)CC_BeforeCalcMatrixCallback;
	}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 */
void pppFrameConstrainCameraForLoc(void)
{
	// TODO - frame processing function
}
