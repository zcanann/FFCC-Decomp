#include "global.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppYmEnv.h"
#include <dolphin/mtx.h>

extern "C" {
extern const float kDrawAStarSphereRadius = 10.0f;
extern const float kInfiniteCost = 10000000.0f;
extern const char kAStarStepDebugFormat[] = "%d ";
extern const char kAStarNewLine[4] = "\n";
}

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
void pppFrameConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, pppConstrainCameraDirUnkB* param_2,
                                _pppCtrlTable* param_3)
{
    if (ppvUserStopPartF == 0) {
        _pppMngSt* pppMngSt = ppvMng;
        float* value = (float*)(pppConstrainCameraDir->m_workArea + *param_3->m_serializedDataOffsets);

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
            float baseFov = kConstrainCameraDirBaseFov;
            float scale = ((CameraPcs.m_fov - baseFov) / baseFov) + kConstrainCameraDirScaleOne;

            PSMTXIdentity(ppvMng->m_matrix.value);

            pppMngSt->m_scale.x = kConstrainCameraDirWideAspect * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = kConstrainCameraDirScaleOne;

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
    float uVar1 = kConstrainCameraDirZero;
    float* puVar2 = (float*)(pppConstrainCameraDir->m_workArea + *param_2->m_serializedDataOffsets);
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
    float uVar1 = kConstrainCameraDirZero;
    float* puVar2 = (float*)(pppConstrainCameraDir->m_workArea + *param_2->m_serializedDataOffsets);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
}
