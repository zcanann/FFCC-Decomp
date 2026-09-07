#include "global.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/pppConstrainCameraDir_internal.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppYmEnv.h"
#include <dolphin/mtx.h>

STATIC_ASSERT(offsetof(pppConstrainCameraDir, m_workArea) == 0x80);

STATIC_ASSERT(sizeof(ConstrainCameraDirDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(ConstrainCameraDirDataOffsets, m_workOffset) == 0x0);

static inline ConstrainCameraDirDataOffsets* GetConstrainCameraDirDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<ConstrainCameraDirDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 80143098
 * PAL Size: 508b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, pppConstrainCameraDirStep* param_2,
                                _pppCtrlTable* param_3)
{
    if (ppvUserStopPartF == 0) {
        _pppMngSt* pppMngSt = ppvMng;
        float* value =
            (float*)(pppConstrainCameraDir->m_workArea + GetConstrainCameraDirDataOffsets(param_3)->m_workOffset);

        CalcGraphValue((_pppPObject*)pppConstrainCameraDir, param_2->m_graphId, value[0], value[1], value[2],
                       param_2->m_dataValIndex, param_2->m_initWOrk, param_2->m_stepValue);

        if ((ppvIsLoopCalc != 1) && ((param_2->m_applyCameraInverse != 0 || param_2->m_applyPosition != 0))) {
            float cameraDirX = CameraPcs.m_directionX;
            float cameraDirY = CameraPcs.m_directionY;
            float cameraDirZ = CameraPcs.m_directionZ;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            float cameraPosX = CameraPcs.m_positionX;
            float cameraPosY = CameraPcs.m_positionY;
            float cameraPosZ = CameraPcs.m_positionZ;
            float scale = 1.0f;
            float baseFov = 25.0f;
            scale += (CameraPcs.m_fov - baseFov) / baseFov;

            PSMTXIdentity(ppvMng->m_matrix.value);

            pppMngSt->m_scale.x = 1.3333f * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = 1.0f;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (param_2->m_applyCameraInverse != 0) {
                PSMTXInverse(cameraMtx, ppvMng->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);

            if (param_2->m_applyPosition != 0) {
                float resultZ = cameraDirZ * *value + cameraPosZ;
                float resultY = cameraDirY * *value + cameraPosY;
                float resultX = cameraDirX * *value + cameraPosX;
                ppvMng->m_matrix.value[0][3] = resultX;
                ppvMng->m_matrix.value[1][3] = resultY;
                ppvMng->m_matrix.value[2][3] = resultZ;
            }

            pppSetFpMatrix(pppMngSt);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 80143294
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructConstrainCameraDir(_pppPObjLink*, _pppCtrlTable*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 80143298
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, _pppCtrlTable* param_2)
{
    float uVar1 = 0.0f;
    float* puVar2 =
        (float*)(pppConstrainCameraDir->m_workArea + GetConstrainCameraDirDataOffsets(param_2)->m_workOffset);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
}

/*
 * --INFO--
 * PAL Address: 801432bc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, _pppCtrlTable* param_2)
{
    float uVar1 = 0.0f;
    float* puVar2 =
        (float*)(pppConstrainCameraDir->m_workArea + GetConstrainCameraDirDataOffsets(param_2)->m_workOffset);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
}
