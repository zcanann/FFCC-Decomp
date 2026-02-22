#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

// External references
extern int DAT_8032ec70;
extern float lbl_803331A8;
extern void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec*);

// Function signatures from Ghidra decomp
extern "C" int GetModelPtr__FP8CGObject(CGObject*);
extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(pppConstrainCameraForLoc*, int, float*,
                                                             float*, float*, float, float*, float*);

/*
 * --INFO--
 * PAL Address: 80167eec
 * PAL Size: 580b
 */
int CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void*)
{
    float* params = (float*)param_2;
    float fVar1 = params[0x10];
    double dVar2;
    double dVar3;
    float local_f8;
    float local_f4;
    float local_f0;
    Vec local_ec;
    Vec local_e0;
    Vec local_bc;
    Vec local_a4;
    Mtx local_98;
    Mtx local_68;

    local_f8 = *(float*)((char*)&CameraPcs + 0xec);
    local_f4 = *(float*)((char*)&CameraPcs + 0xf0);
    local_f0 = *(float*)((char*)&CameraPcs + 0xf4);
    local_bc.x = *(float*)((char*)&CameraPcs + 0xe0);
    local_bc.y = *(float*)((char*)&CameraPcs + 0xe4);
    local_bc.z = *(float*)((char*)&CameraPcs + 0xe8);
    PSMTXCopy(*(Mtx*)((char*)&CameraPcs + 4), local_68);

    local_a4.z = params[0];
    local_a4.x = local_a4.z * local_f8;
    local_a4.y = local_a4.z * local_f4;
    local_a4.z = local_a4.z * local_f0;
    if (Game.game.m_currentSceneId == 7) {
        PSMTXInverse(ppvCameraMatrix0, local_98);
    } else {
        PSMTXInverse(local_68, local_98);
    }

    PSMTXIdentity(*(Mtx*)((char*)model + 0x68));
    PSMTXIdentity(*(Mtx*)((char*)model + 0x38));
    PSMTXConcat(local_98, *(Mtx*)((char*)model + 0x38), *(Mtx*)((char*)model + 0x38));
    PSVECAdd(&local_bc, &local_a4, &local_a4);

    dVar3 = (double)*(float*)((int)fVar1 + 0x1c);
    dVar2 = (double)*(float*)((int)fVar1 + 0x2c);
    GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&DAT_8032ec70, (Vec*)&local_e0, (Vec*)&local_ec, (Vec*)&local_f8);

    local_e0.x = (float)(dVar3 * (double)local_e0.x);
    local_e0.y = (float)(dVar3 * (double)local_e0.y);
    local_e0.z = (float)(dVar3 * (double)local_e0.z);
    local_ec.x = (float)(dVar2 * (double)local_ec.x);
    local_ec.y = (float)(dVar2 * (double)local_ec.y);
    local_ec.z = (float)(dVar2 * (double)local_ec.z);
    PSVECAdd(&local_a4, &local_e0, &local_a4);
    PSVECAdd(&local_a4, &local_ec, &local_a4);

    fVar1 = lbl_803331A8;
    *(float*)((char*)model + 0x44) = lbl_803331A8;
    *(float*)((char*)model + 0x54) = fVar1;
    *(float*)((char*)model + 0x64) = fVar1;
    if (Game.game.m_currentSceneId == 7) {
        *(float*)((char*)model + 0x74) = fVar1;
        *(float*)((char*)model + 0x84) = fVar1;
        *(float*)((char*)model + 0x94) = fVar1;
    } else {
        *(float*)((char*)model + 0x74) = local_a4.x;
        *(float*)((char*)model + 0x84) = local_a4.y;
        *(float*)((char*)model + 0x94) = local_a4.z;
    }

    PSMTXCopy(*(Mtx*)((char*)model + 0x38), *(Mtx*)((char*)params + 0x10));
    params[7] = local_a4.x;
    params[0xb] = local_a4.y;
    params[0xf] = local_a4.z;
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
	CGObject* obj = *(CGObject**)(lbl_8032ED50 + 0xd8);
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
    float fVar1 = lbl_803331A8;
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

	if (lbl_8032ED70 == 0) {
		value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
		CGObject* obj = *(CGObject**)(lbl_8032ED50 + 0xd8);
		modelPtr = GetModelPtr__FP8CGObject(obj);
		*(float**)(modelPtr + 0xe4) = value;
		*(pppConstrainCameraForLocParams**)(modelPtr + 0xe8) = params;
		*(void**)(modelPtr + 0xec) = (void*)CC_BeforeCalcMatrixCallback;

		CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(constrainCameraForLoc, params->m_graphId, value,
		                                             value + 1, value + 2, params->m_dataValIndex,
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
    float fVar1 = lbl_803331A8;
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
