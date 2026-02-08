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
int CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void*)
{
    float* params = (float*)param_2;
    float sceneValue = params[0];
    float camDirX = *(float*)((char*)&CameraPcs + 0xec);
    float camDirY = *(float*)((char*)&CameraPcs + 0xf0);
    float camDirZ = *(float*)((char*)&CameraPcs + 0xf4);
    float* graph = *(float**)((char*)params + 0x40);
    float graphForward = graph[7];
    float graphUp = graph[11];
    Vec cameraPos;
    Vec cameraDir;
    Vec offset;
    Vec forwardDir;
    Vec upDir;
    Vec scaledForward;
    Vec scaledUp;
    Mtx cameraMtx;
    Mtx inverseMtx;

    cameraPos.x = *(float*)((char*)&CameraPcs + 0xe0);
    cameraPos.y = *(float*)((char*)&CameraPcs + 0xe4);
    cameraPos.z = *(float*)((char*)&CameraPcs + 0xe8);
    cameraDir.x = camDirX;
    cameraDir.y = camDirY;
    cameraDir.z = camDirZ;

    PSMTXCopy(*(Mtx*)((char*)&CameraPcs + 4), cameraMtx);

    offset.x = sceneValue * camDirX;
    offset.y = sceneValue * camDirY;
    offset.z = sceneValue * camDirZ;

    if (Game.game.m_currentSceneId == 7) {
        PSMTXInverse(ppvCameraMatrix0, inverseMtx);
    } else {
        PSMTXInverse(cameraMtx, inverseMtx);
    }

    PSMTXIdentity(*(Mtx*)((char*)model + 0x68));
    PSMTXIdentity(*(Mtx*)((char*)model + 0x38));
    PSMTXConcat(inverseMtx, *(Mtx*)((char*)model + 0x38), *(Mtx*)((char*)model + 0x38));

    PSVECAdd(&cameraPos, &offset, &offset);

    GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&DAT_8032ec70, &forwardDir, &upDir, &cameraDir);

    scaledForward.x = graphForward * forwardDir.x;
    scaledForward.y = graphForward * forwardDir.y;
    scaledForward.z = graphForward * forwardDir.z;
    scaledUp.x = graphUp * upDir.x;
    scaledUp.y = graphUp * upDir.y;
    scaledUp.z = graphUp * upDir.z;

    PSVECAdd(&offset, &scaledForward, &offset);
    PSVECAdd(&offset, &scaledUp, &offset);

    *(float*)((char*)model + 0x44) = FLOAT_803331a8;
    *(float*)((char*)model + 0x54) = FLOAT_803331a8;
    *(float*)((char*)model + 0x64) = FLOAT_803331a8;

    if (Game.game.m_currentSceneId == 7) {
        *(float*)((char*)model + 0x74) = FLOAT_803331a8;
        *(float*)((char*)model + 0x84) = FLOAT_803331a8;
        *(float*)((char*)model + 0x94) = FLOAT_803331a8;
    } else {
        *(float*)((char*)model + 0x74) = offset.x;
        *(float*)((char*)model + 0x84) = offset.y;
        *(float*)((char*)model + 0x94) = offset.z;
    }

    PSMTXCopy(*(Mtx*)((char*)model + 0x38), *(Mtx*)((char*)params + 0x10));

    params[7] = offset.x;
    params[11] = offset.y;
    params[15] = offset.z;
    return 1;
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
		float* value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
		CGObject* obj = *(CGObject**)((char*)pppMngStPtr + 0xd8);
		int modelPtr = GetModelPtr__FP8CGObject(obj);
		*(float**)(modelPtr + 0xe4) = value;
		*(pppConstrainCameraForLocParams**)(modelPtr + 0xe8) = params;
		*(void**)(modelPtr + 0xec) = (void*)CC_BeforeCalcMatrixCallback;

		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(params->m_dataValIndex, constrainCameraForLoc,
		                                             params->m_graphId, value, value + 1, value + 2,
		                                             &params->m_initWork, &params->m_stepValue);
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
