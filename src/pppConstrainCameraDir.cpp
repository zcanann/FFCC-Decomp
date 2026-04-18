#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppYmEnv.h"
#include <dolphin/mtx.h>

extern "C" void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);

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
    if (gPppCalcDisabled == 0) {
        _pppMngSt* pppMngSt = pppMngStPtr;
        float* value = (float*)((char*)pppConstrainCameraDir + *param_3->m_serializedDataOffsets + 0x80);
        unsigned char* flags = (unsigned char*)&param_2->m_arg3;

        CalcGraphValue(&pppConstrainCameraDir->m_pppPObject, param_2->m_graphId, value[0], value[1], value[2],
                       param_2->m_dataValIndex, param_2->m_initWOrk, param_2->m_stepValue);

        if ((gPppInConstructor != 1) && ((flags[1] != 0 || flags[0] != 0))) {
            float cameraDirX = CameraPcs._236_4_;
            float cameraDirY = CameraPcs._240_4_;
            float cameraDirZ = CameraPcs._244_4_;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            float cameraPosX = CameraPcs._224_4_;
            float cameraPosY = CameraPcs._228_4_;
            float cameraPosZ = CameraPcs._232_4_;
            float scale = ((CameraPcs._252_4_ - 25.0f) / 25.0f) + 1.0f;

            PSMTXIdentity(pppMngStPtr->m_matrix.value);

            pppMngSt->m_scale.x = 1.3333f * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = 1.0f;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (flags[1] != 0) {
                PSMTXInverse(cameraMtx, pppMngStPtr->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            if (flags[0] != 0) {
                float resultZ = cameraDirZ * *value + cameraPosZ;
                float resultY = cameraDirY * *value + cameraPosY;
                float resultX = cameraDirX * *value + cameraPosX;
                pppMngStPtr->m_matrix.value[0][3] = resultX;
                pppMngStPtr->m_matrix.value[1][3] = resultY;
                pppMngStPtr->m_matrix.value[2][3] = resultZ;
            }

            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
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
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
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
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
}
