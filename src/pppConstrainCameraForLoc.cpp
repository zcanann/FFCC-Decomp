#include "ffcc/pppConstrainCameraForLoc.h"
#include "ffcc/game.h"
#include "ffcc/p_camera.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
extern "C" {
extern const float kPppConstrainCameraForLocZero;
}
#include "ffcc/util.h"
#include <dolphin/mtx.h>

static inline float CameraPosX() { return CameraPcs.m_positionX; }
static inline float CameraPosY() { return CameraPcs.m_positionY; }
static inline float CameraPosZ() { return CameraPcs.m_positionZ; }
static inline float CameraDirX() { return CameraPcs.m_directionX; }
static inline float CameraDirY() { return CameraPcs.m_directionY; }
static inline float CameraDirZ() { return CameraPcs.m_directionZ; }
static inline MtxPtr CameraMatrix() { return CameraPcs.m_cameraMatrix; }

static inline float* GetConstrainCameraWork(pppConstrainCameraForLoc* constrainCameraForLoc,
                                            _pppCtrlTable* ctrl)
{
	return reinterpret_cast<float*>(constrainCameraForLoc->m_object.m_workArea +
	                                ctrl->m_serializedDataOffsets[2]);
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
	CChara::CModel* model;

	if (gPppCalcDisabled == 0) {
		value = GetConstrainCameraWork(constrainCameraForLoc, data);
		CGObject* obj = reinterpret_cast<CGObject*>(ppvMng->m_owner);
		model = GetModelPtr(obj);
		model->SetCallbackContext(value, params);
		model->m_beforeCalcMatrixCallback = CC_BeforeCalcMatrixCallback;

		CalcGraphValue(reinterpret_cast<_pppPObject*>(constrainCameraForLoc), params->m_graphId, value[0],
		               value[1], value[2], params->m_dataValIndex, params->m_initWork, params->m_stepValue);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80167E70
 * PAL Size: 48b
 */
void pppConstructConstrainCameraForLoc(_pppPObjLink*, _pppCtrlTable*)
{
	CGObject* obj = reinterpret_cast<CGObject*>(ppvMng->m_owner);
	CChara::CModel* model = GetModelPtr(obj);
	model->m_beforeCalcMatrixCallback = 0;
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
    float* value = GetConstrainCameraWork(constrainCameraForLoc, data);
    value[2] = fVar1;
    value[1] = fVar1;
    value[0] = fVar1;
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
    float* value = GetConstrainCameraWork(constrainCameraForLoc, data);
    value[2] = fVar1;
    value[1] = fVar1;
    value[0] = fVar1;
    *(pppConstrainCameraForLoc**)((char*)value + 0x40) = constrainCameraForLoc;
}

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
    Vec local_a4;
    Vec local_b0;
    Vec local_bc;
    Vec local_c8;
    Vec local_d4;
    Vec local_e0;
    Vec local_ec;
    Mtx local_68;
    Mtx local_98;

    local_b0.x = CameraDirX();
    local_b0.y = CameraDirY();
    local_b0.z = CameraDirZ();
    local_bc.x = CameraPosX();
    local_bc.y = CameraPosY();
    local_bc.z = CameraPosZ();
    PSMTXCopy(CameraMatrix(), local_68);

    fVar3 = work->field0_0x0;
    local_a4.x = fVar3 * local_b0.x;
    local_a4.y = fVar3 * local_b0.y;
    local_a4.z = fVar3 * local_b0.z;
    if ((s32)Game.m_currentSceneId == 7) {
        PSMTXInverse(ppvCameraMatrix, local_98);
    } else {
        PSMTXInverse(local_68, local_98);
    }

    PSMTXIdentity(constrainModel->m_drawMtx);
    PSMTXIdentity(constrainModel->m_worldBaseMtx);
    PSMTXConcat(local_98, constrainModel->m_worldBaseMtx, constrainModel->m_worldBaseMtx);
    PSVECAdd(&local_bc, &local_a4, &local_a4);

    fVar3 = *(float*)(owner + 0x1c);
    fVar2 = *(float*)(owner + 0x2c);
    gUtil.GetDirectVector(&local_c8, &local_d4, local_b0);

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
    if ((s32)Game.m_currentSceneId == 7) {
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
 * PAL Address: TODO
 * PAL Size: TODO
 */
void pppFrameConstrainCameraForLoc(_pppPObject*, void*, _pppCtrlTable*)
{
	// TODO - frame processing function
}
