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
void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, pppConstrainCameraForLoc*, int, float*,
                                                 float*, float*, float*, float*);

/*
 * --INFO--
 * PAL Address: 80167eec
 * PAL Size: 580b
 */
void CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void*)
{
    float* params = (float*)param_2;
    
    // Load scale parameter
    float scale = *params;
    
    // Load camera direction and position
    float dirX = *(float*)((char*)&CameraPcs + 0xec);
    float dirY = *(float*)((char*)&CameraPcs + 0xf0);
    float dirZ = *(float*)((char*)&CameraPcs + 0xf4);
    
    Vec cameraPos;
    cameraPos.x = *(float*)((char*)&CameraPcs + 0xe0);
    cameraPos.y = *(float*)((char*)&CameraPcs + 0xe4);
    cameraPos.z = *(float*)((char*)&CameraPcs + 0xe8);
    
    // Calculate scaled direction
    Vec scaledDir;
    scaledDir.x = scale * dirX;
    scaledDir.y = scale * dirY;
    scaledDir.z = scale * dirZ;
    
    // Add position to scaled direction
    Vec result;
    PSVECAdd(&cameraPos, &scaledDir, &result);
    
    // Store results in params 
    params[7] = result.x;
    params[11] = result.y;
    params[15] = result.z;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2ConstrainCameraForLoc(pppConstrainCameraForLoc* constrainCameraForLoc,
                                        pppConstrainCameraForLocData* data)
{
    float fVar1 = FLOAT_803331a8;
    float* value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
    value[2] = fVar1;
    value[1] = fVar1;
    value[0] = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x80167DD4
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructConstrainCameraForLoc(pppConstrainCameraForLoc* constrainCameraForLoc,
                                      pppConstrainCameraForLocParams* params,
                                      pppConstrainCameraForLocData* data)
{
	float* value;
	int modelPtr;

	if (DAT_8032ed70 == 0) {
		value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
		modelPtr = GetModelPtr__FP8CGObject(*(CGObject**)((char*)pppMngStPtr + 0xd8));
		*(float**)(modelPtr + 0xe4) = value;
		*(pppConstrainCameraForLocParams**)(modelPtr + 0xe8) = params;
		*(void**)(modelPtr + 0xec) = (void*)CC_BeforeCalcMatrixCallback;
		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
		    params->m_dataValIndex,
		    constrainCameraForLoc,
		    params->m_graphId,
		    value,
		    value + 1,
		    value + 2,
		    &params->m_initWork,
		    &params->m_stepValue);
	}
}

/*
 * --INFO--
 * PAL Address: 80167ec4  
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void fn_80167EC4(pppConstrainCameraForLoc* constrainCameraForLoc, pppConstrainCameraForLocData* data)
{
    float fVar1 = FLOAT_803331a8;
    float* value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
    value[2] = fVar1;
    value[1] = fVar1;
    value[0] = fVar1;
    *(pppConstrainCameraForLoc**)((char*)value + 0x40) = constrainCameraForLoc;
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
