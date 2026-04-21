#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/p_camera.h"
extern "C" {
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
#include "ffcc/pppYmEnv.h"
#include "ffcc/util.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

void pppSetFpMatrix(_pppMngSt*);

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
        unsigned char* flags = (unsigned char*)&param_2->m_arg3;

        CalcGraphValue(&param_1->m_pppPObject, param_2->m_graphId, value[0], value[1], value[2], param_2->m_dataValIndex,
                       param_2->m_initWOrk, param_2->m_stepValue);

        if ((gPppInConstructor != 1) && ((flags[1] != 0 || flags[0] != 0))) {
            Vec resultPos;
            Vec cameraDir;
            cameraDir.x = CameraPcs._236_4_;
            cameraDir.y = CameraPcs._240_4_;
            cameraDir.z = CameraPcs._244_4_;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            float cameraPosX = CameraPcs._224_4_;
            float cameraPosY = CameraPcs._228_4_;
            float cameraPosZ = CameraPcs._232_4_;
            float scale = ((CameraPcs._252_4_ - 0.8f) / 0.8f) + 64.0f;

            PSMTXIdentity(pppMngStPtr->m_matrix.value);

            pppMngSt->m_scale.x = 56.0f * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = 64.0f;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (flags[1] != 0) {
                PSMTXInverse(cameraMtx, pppMngStPtr->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            if (flags[0] != 0) {
                resultPos.x = cameraPosX;
                resultPos.y = cameraPosY;
                resultPos.z = cameraPosZ;
                resultPos.x = cameraDir.x * *value + resultPos.x;
                resultPos.y = cameraDir.y * *value + resultPos.y;
                resultPos.z = cameraDir.z * *value + resultPos.z;
            }

            float localY = param_1->m_object.m_localMatrix.value[1][3];
            float localX = param_1->m_object.m_localMatrix.value[0][3];

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
