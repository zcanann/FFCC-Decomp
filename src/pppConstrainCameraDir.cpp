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

/*
 * --INFO--
 * PAL Address: 80143098
 * PAL Size: 508b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, pppConstrainCameraDirStep* step,
                                _pppCtrlTable* ctrl)
{
    if (ppvUserStopPartF == 0) {
        _pppMngSt* pppMngSt = ppvMng;
        float* value = (float*)(constrainCameraDir->m_workArea + ctrl->m_serializedDataOffsets[0]);

        CalcGraphValue(constrainCameraDir, step->m_graphId, value[0], value[1], value[2], step->m_dataValIndex,
                       step->m_initWOrk, step->m_stepValue);

        if ((ppvIsLoopCalc != 1) && ((step->m_applyCameraInverse != 0 || step->m_applyPosition != 0))) {
            float cameraDirX = CameraPcs.m_direction.x;
            float cameraDirY = CameraPcs.m_direction.y;
            float cameraDirZ = CameraPcs.m_direction.z;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            float cameraPosX = CameraPcs.m_position.x;
            float cameraPosY = CameraPcs.m_position.y;
            float cameraPosZ = CameraPcs.m_position.z;
            float scale = 1.0f + (CameraPcs.m_fov - 25.0f) / 25.0f;

            PSMTXIdentity(ppvMng->m_matrix.value);

            pppMngSt->m_scale.x = 1.3333f * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = 1.0f;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (step->m_applyCameraInverse != 0) {
                PSMTXInverse(cameraMtx, ppvMng->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);

            if (step->m_applyPosition != 0) {
                float resultX = cameraPosX;
                float resultY = cameraPosY;
                float resultZ = cameraPosZ;
                float v = *value;
                resultX = cameraDirX * v + resultX;
                resultY = cameraDirY * v + resultY;
                resultZ = cameraDirZ * v + resultZ;
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
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, _pppCtrlTable* ctrl)
{
    float* value = (float*)(constrainCameraDir->m_workArea + ctrl->m_serializedDataOffsets[0]);
    value[0] = value[1] = value[2] = 0.0f;
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
void pppConstructConstrainCameraDir(pppConstrainCameraDir* constrainCameraDir, _pppCtrlTable* ctrl)
{
    float* value = (float*)(constrainCameraDir->m_workArea + ctrl->m_serializedDataOffsets[0]);
    value[0] = value[1] = value[2] = 0.0f;
}
