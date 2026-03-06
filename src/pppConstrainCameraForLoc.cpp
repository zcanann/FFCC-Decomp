#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"
#include <dolphin/mtx.h>

// External references
extern int gUtil;
extern void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec*);
extern struct {
    int field0_0x0;
    Mtx m_cameraMatrix;
    unsigned char field34_0xe0[0xAC];
    float _224_4_;
    float _228_4_;
    float _232_4_;
    float _236_4_;
    float _240_4_;
    float _244_4_;
} CameraPcs;

// Function signatures from Ghidra decomp
extern "C" int GetModelPtr__FP8CGObject(CGObject*);
extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(pppConstrainCameraForLoc*, int, float*,
                                                             float*, float*, float, float*, float*);

/*
 * --INFO--
 * PAL Address: 80167eec
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* param_2, void*)
{
    struct ConstrainCameraForLocModel {
        unsigned char field0_0x0[0x38];
        Mtx m_worldBaseMtx;
        Mtx m_drawMtx;
    };
    struct ConstrainCameraForLocWork {
        float field0_0x0;
        float field4_0x4;
        float field8_0x8;
        float fieldc_0xc;
        Mtx m_worldBaseMtx;
        void* m_owner;
    };

    ConstrainCameraForLocWork* work = (ConstrainCameraForLocWork*)param_2;
    ConstrainCameraForLocModel* constrainModel = (ConstrainCameraForLocModel*)model;
    unsigned char* owner = (unsigned char*)work->m_owner;
    float fVar1;
    float fVar2;
    float fVar3;
    float local_f8;
    float local_f4;
    float local_f0;
    Vec local_ec;
    Vec local_e0;
    Vec local_d4;
    Vec local_c8;
    Vec local_bc;
    Vec local_a4;
    Mtx local_98;
    Mtx local_68;

    local_f8 = CameraPcs._236_4_;
    local_f4 = CameraPcs._240_4_;
    local_f0 = CameraPcs._244_4_;
    local_bc.x = CameraPcs._224_4_;
    local_bc.y = CameraPcs._228_4_;
    local_bc.z = CameraPcs._232_4_;
    PSMTXCopy(CameraPcs.m_cameraMatrix, local_68);

    local_a4.z = work->field0_0x0;
    local_a4.x = local_a4.z * local_f8;
    local_a4.y = local_a4.z * local_f4;
    local_a4.z = local_a4.z * local_f0;
    if (Game.game.m_currentSceneId == 7) {
        PSMTXInverse(ppvCameraMatrix0, local_98);
    } else {
        PSMTXInverse(local_68, local_98);
    }

    PSMTXIdentity(constrainModel->m_drawMtx);
    PSMTXIdentity(constrainModel->m_worldBaseMtx);
    PSMTXConcat(local_98, constrainModel->m_worldBaseMtx, constrainModel->m_worldBaseMtx);
    PSVECAdd(&local_bc, &local_a4, &local_a4);

    fVar3 = *(float*)(owner + 0x1c);
    fVar2 = *(float*)(owner + 0x2c);
    GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&gUtil, &local_c8, &local_d4, (Vec*)&local_f8);

    local_e0.x = fVar3 * local_c8.x;
    local_e0.y = fVar3 * local_c8.y;
    local_e0.z = fVar3 * local_c8.z;
    local_ec.x = fVar2 * local_d4.x;
    local_ec.y = fVar2 * local_d4.y;
    local_ec.z = fVar2 * local_d4.z;
    PSVECAdd(&local_a4, &local_e0, &local_a4);
    PSVECAdd(&local_a4, &local_ec, &local_a4);

    fVar1 = kPppConstrainCameraForLocZero;
    constrainModel->m_worldBaseMtx[0][3] = kPppConstrainCameraForLocZero;
    constrainModel->m_worldBaseMtx[1][3] = fVar1;
    constrainModel->m_worldBaseMtx[2][3] = fVar1;
    if (Game.game.m_currentSceneId == 7) {
        constrainModel->m_drawMtx[0][3] = fVar1;
        constrainModel->m_drawMtx[1][3] = fVar1;
        constrainModel->m_drawMtx[2][3] = fVar1;
    } else {
        constrainModel->m_drawMtx[0][3] = local_a4.x;
        constrainModel->m_drawMtx[1][3] = local_a4.y;
        constrainModel->m_drawMtx[2][3] = local_a4.z;
    }

    PSMTXCopy(constrainModel->m_worldBaseMtx, work->m_worldBaseMtx);
    work->m_worldBaseMtx[0][3] = local_a4.x;
    work->m_worldBaseMtx[1][3] = local_a4.y;
    work->m_worldBaseMtx[2][3] = local_a4.z;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80167E70
 * PAL Size: 48b
 */
void pppConstructConstrainCameraForLoc(_pppPObjLink*, _pppCtrlTable*)
{
	CGObject* obj = *(CGObject**)((u8*)pppMngStPtr + 0xD8);
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
                                        _pppCtrlTable* data)
{
    float fVar1 = kPppConstrainCameraForLocZero;
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
                                      _pppCtrlTable* data)
{
	float* value;
	int modelPtr;

	if (gPppCalcDisabled == 0) {
		value = (float*)((char*)constrainCameraForLoc + 0x80 + data->m_serializedDataOffsets[2]);
		CGObject* obj = *(CGObject**)((u8*)pppMngStPtr + 0xD8);
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
void pppConstruct3ConstrainCameraForLoc(pppConstrainCameraForLoc* constrainCameraForLoc, _pppCtrlTable* data)
{
    float fVar1 = kPppConstrainCameraForLocZero;
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
void pppFrameConstrainCameraForLoc(_pppPObject*, void*, _pppCtrlTable*)
{
	// TODO - frame processing function
}
