#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

/*
 * --INFO--
 * PAL Address: 0x8016ca80
 * PAL Size: 688b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConstrainCameraDir2(pppConstrainCameraDir* param_1, pppConstrainCameraDirUnkB* param_2,
                                 _pppCtrlTable* param_3)
{
    if (gPppCalcDisabled == 0) {
        _pppMngSt* pppMngSt = pppMngStPtr;
        float* value = (float*)((char*)param_1 + *param_3->m_serializedDataOffsets + 0x80);

        CalcGraphValue((_pppPObject*)param_1, param_2->m_graphId, value[0], value[1], value[2], param_2->m_dataValIndex,
                       param_2->m_initWOrk, param_2->m_stepValue);

        if ((gPppInConstructor != 1) && ((param_2->m_applyCameraInverse != 0 || param_2->m_applyPosition != 0))) {
            Vec resultPos;
            Vec cameraDir;
            cameraDir.x = CameraPcs.m_directionX;
            cameraDir.y = CameraPcs.m_directionY;
            cameraDir.z = CameraPcs.m_directionZ;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            float cameraPosX = CameraPcs.m_positionX;
            float cameraPosY = CameraPcs.m_positionY;
            float cameraPosZ = CameraPcs.m_positionZ;
            float localX;
            float localY;
            float scale = ((CameraPcs.m_fov - 0.8f) / 0.8f) + 64.0f;

            PSMTXIdentity(pppMngStPtr->m_matrix.value);

            pppMngSt->m_scale.x = 56.0f * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = 64.0f;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (param_2->m_applyCameraInverse != 0) {
                PSMTXInverse(cameraMtx, pppMngStPtr->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            if (param_2->m_applyPosition != 0) {
                resultPos.x = cameraPosX;
                resultPos.y = cameraPosY;
                resultPos.z = cameraPosZ;
                resultPos.x = cameraDir.x * *value + resultPos.x;
                resultPos.y = cameraDir.y * *value + resultPos.y;
                resultPos.z = cameraDir.z * *value + resultPos.z;
            }

            localX = param_1->m_localMatrix.value[0][3];
            localY = param_1->m_localMatrix.value[1][3];

            Vec direct0;
            Vec direct1;
            gUtil.GetDirectVector(&direct0, &direct1, cameraDir);

            Vec localOffset0;
            localOffset0.x = localX * direct0.x;
            localOffset0.y = localX * direct0.y;
            localOffset0.z = localX * direct0.z;

            Vec localOffset1;
            localOffset1.x = localY * direct1.x;
            localOffset1.y = localY * direct1.y;
            localOffset1.z = localY * direct1.z;

            PSVECAdd(&resultPos, &localOffset0, &resultPos);
            PSVECAdd(&resultPos, &localOffset1, &resultPos);

            pppMngStPtr->m_matrix.value[0][3] = resultPos.x;
            pppMngStPtr->m_matrix.value[1][3] = resultPos.y;
            pppMngStPtr->m_matrix.value[2][3] = resultPos.z;

            pppSetFpMatrix(pppMngSt);
        }
    }
}
