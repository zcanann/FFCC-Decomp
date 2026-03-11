#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/p_camera.h"
#include "ffcc/util.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

extern float FLOAT_803331e0;
extern float FLOAT_803331e4;
extern float FLOAT_803331e8;

extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
extern "C" void GetDirectVector__5CUtilFP3VecP3Vec3Vec(void*, Vec*, Vec*, Vec);
extern "C" void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);

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
        float* value = (float*)((char*)param_1 + *param_3->m_serializedDataOffsets + 0x80);
        unsigned char* flags = (unsigned char*)&param_2->m_arg3;

        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            param_2->m_dataValIndex, param_1, param_2->m_graphId, value, value + 1, value + 2,
            &param_2->m_initWOrk, &param_2->m_stepValue);

        if ((gPppInConstructor != 1) && ((flags[1] != 0 || flags[0] != 0))) {
            _pppMngSt* pppMngSt = pppMngStPtr;
            Vec resultPos;
            Vec cameraDir;
            cameraDir.x = CameraPcs._236_4_;
            cameraDir.y = CameraPcs._240_4_;
            cameraDir.z = CameraPcs._244_4_;

            Mtx cameraMtx;
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);

            Vec cameraPos;
            cameraPos.x = CameraPcs._224_4_;
            cameraPos.y = CameraPcs._228_4_;
            cameraPos.z = CameraPcs._232_4_;
            float scale = FLOAT_803331e0 + ((CameraPcs._252_4_ - FLOAT_803331e4) / FLOAT_803331e4);

            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            float baseScale = FLOAT_803331e0;
            pppMngSt->m_scale.x = FLOAT_803331e8 * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = baseScale;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (flags[1] != 0) {
                PSMTXInverse(cameraMtx, pppMngStPtr->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            if (flags[0] != 0) {
                resultPos.x = cameraDir.x * *value + cameraPos.x;
                resultPos.y = cameraDir.y * *value + cameraPos.y;
                resultPos.z = cameraDir.z * *value + cameraPos.z;
            }

            float localX = param_1->m_pppPObject.m_localMatrix.value[0][3];
            float localY = param_1->m_pppPObject.m_localMatrix.value[1][3];

            Vec direct0;
            Vec direct1;
            GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&gUtil, &direct0, &direct1, cameraDir);

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

            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
