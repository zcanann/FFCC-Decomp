#include "ffcc/pppConstrainCameraForLoc.h"
#include "global.h"
#include "ffcc/game.h"
#include "ffcc/p_camera.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include <dolphin/mtx.h>

static const float kPppConstrainCameraForLocZero = 0.0f;

struct pppConstrainCameraForLocWork {
    Vec m_cameraOffset;
    float m_fieldC;
    Mtx m_worldBaseMtx;
    _pppPObject* m_owner;
};

STATIC_ASSERT(sizeof(pppConstrainCameraForLocDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(pppConstrainCameraForLocDataOffsets, m_workOffset) == 0x8);

static inline float CameraPosX() { return CameraPcs.m_positionX; }
static inline float CameraPosY() { return CameraPcs.m_positionY; }
static inline float CameraPosZ() { return CameraPcs.m_positionZ; }
static inline float CameraDirX() { return CameraPcs.m_directionX; }
static inline float CameraDirY() { return CameraPcs.m_directionY; }
static inline float CameraDirZ() { return CameraPcs.m_directionZ; }
static inline MtxPtr CameraMatrix() { return CameraPcs.m_cameraMatrix; }

static inline pppConstrainCameraForLocDataOffsets* GetConstrainCameraDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppConstrainCameraForLocDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline pppConstrainCameraForLocWork* GetConstrainCameraWork(
    pppConstrainCameraForLoc* constrainCameraForLoc, _pppCtrlTable* ctrl)
{
    pppConstrainCameraForLocDataOffsets* offsets = GetConstrainCameraDataOffsets(ctrl);
    return reinterpret_cast<pppConstrainCameraForLocWork*>(
        constrainCameraForLoc->m_workArea + offsets->m_workOffset);
}

static int CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* context, void*);

/*
 * --INFO--
 * PAL Address: 0x80167DD4
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConstrainCameraForLoc(pppConstrainCameraForLoc* constrainCameraForLoc,
                                   pppConstrainCameraForLocParams* params,
                                   _pppCtrlTable* data)
{
    pppConstrainCameraForLocWork* work;
    CChara::CModel* model;

    if (ppvUserStopPartF == 0) {
        work = GetConstrainCameraWork(constrainCameraForLoc, data);
        CGObject* obj = ppvMng->m_owner;
        model = GetModelPtr(obj);
        model->SetCallbackContext(work, params);
        model->SetBeforeCalcMatrixCallback(CC_BeforeCalcMatrixCallback);

        CalcGraphValue(constrainCameraForLoc, params->m_graphId, work->m_cameraOffset.x,
                       work->m_cameraOffset.y, work->m_cameraOffset.z, params->m_dataValIndex,
                       params->m_initWork, params->m_stepValue);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80167E70
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructConstrainCameraForLoc(_pppPObjLink*, _pppCtrlTable*)
{
    CGObject* obj = ppvMng->m_owner;
    CChara::CModel* model = GetModelPtr(obj);
    model->SetBeforeCalcMatrixCallback(0);
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
    float zero = kPppConstrainCameraForLocZero;
    pppConstrainCameraForLocWork* work = GetConstrainCameraWork(constrainCameraForLoc, data);
    work->m_cameraOffset.z = zero;
    work->m_cameraOffset.y = zero;
    work->m_cameraOffset.x = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80167EC4
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConstrainCameraForLoc(pppConstrainCameraForLoc* constrainCameraForLoc, _pppCtrlTable* data)
{
    float zero = kPppConstrainCameraForLocZero;
    pppConstrainCameraForLocWork* work = GetConstrainCameraWork(constrainCameraForLoc, data);
    work->m_cameraOffset.z = zero;
    work->m_cameraOffset.y = zero;
    work->m_cameraOffset.x = zero;
    work->m_owner = constrainCameraForLoc;
}

/*
 * --INFO--
 * PAL Address: 0x80167EEC
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static int CC_BeforeCalcMatrixCallback(CChara::CModel* model, void* context, void*)
{
    pppConstrainCameraForLocWork* work = (pppConstrainCameraForLocWork*)context;
    _pppPObject* owner = work->m_owner;
    float zero;
    float offsetY;
    float offsetX;
    Vec resultPos;
    Vec cameraDir;
    Vec cameraPos;
    Vec direct0;
    Vec direct1;
    Vec localOffset0;
    Vec localOffset1;
    Mtx cameraMtx;
    Mtx invCameraMtx;

    cameraDir.x = CameraDirX();
    cameraDir.y = CameraDirY();
    cameraDir.z = CameraDirZ();
    cameraPos.x = CameraPosX();
    cameraPos.y = CameraPosY();
    cameraPos.z = CameraPosZ();
    PSMTXCopy(CameraMatrix(), cameraMtx);

    offsetX = work->m_cameraOffset.x;
    resultPos.x = offsetX * cameraDir.x;
    resultPos.y = offsetX * cameraDir.y;
    resultPos.z = offsetX * cameraDir.z;
    if ((s32)Game.m_currentSceneId == 7) {
        PSMTXInverse(ppvCameraMatrix, invCameraMtx);
    } else {
        PSMTXInverse(cameraMtx, invCameraMtx);
    }

    PSMTXIdentity(model->m_drawMtx);
    PSMTXIdentity(model->m_worldBaseMtx);
    PSMTXConcat(invCameraMtx, model->m_worldBaseMtx, model->m_worldBaseMtx);
    PSVECAdd(&cameraPos, &resultPos, &resultPos);

    offsetX = owner->m_localMatrix.value[0][3];
    offsetY = owner->m_localMatrix.value[1][3];
    gUtil.GetDirectVector(&direct0, &direct1, cameraDir);

    localOffset0.x = offsetX * direct0.x;
    localOffset0.y = offsetX * direct0.y;
    localOffset0.z = offsetX * direct0.z;
    localOffset1.x = offsetY * direct1.x;
    localOffset1.y = offsetY * direct1.y;
    localOffset1.z = offsetY * direct1.z;
    PSVECAdd(&resultPos, &localOffset0, &resultPos);
    PSVECAdd(&resultPos, &localOffset1, &resultPos);

    zero = kPppConstrainCameraForLocZero;
    model->m_worldBaseMtx[0][3] = zero;
    model->m_worldBaseMtx[1][3] = zero;
    model->m_worldBaseMtx[2][3] = zero;
    if ((s32)Game.m_currentSceneId == 7) {
        model->m_drawMtx[0][3] = zero;
        model->m_drawMtx[1][3] = zero;
        model->m_drawMtx[2][3] = zero;
    } else {
        model->m_drawMtx[0][3] = resultPos.x;
        model->m_drawMtx[1][3] = resultPos.y;
        model->m_drawMtx[2][3] = resultPos.z;
    }

    PSMTXCopy(model->m_worldBaseMtx, work->m_worldBaseMtx);
    work->m_worldBaseMtx[0][3] = resultPos.x;
    work->m_worldBaseMtx[1][3] = resultPos.y;
    work->m_worldBaseMtx[2][3] = resultPos.z;
    return 1;
}
