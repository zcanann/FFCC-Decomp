#include "ffcc/pppConstrainCameraDir2.h"
#include "ffcc/partMng.h"
#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/p_camera.h"
#include "ffcc/util.h"
#include <dolphin/mtx.h>
#include "ffcc/ppp_linkage.h"

static inline float CameraPosX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE0); }
static inline float CameraPosY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE4); }
static inline float CameraPosZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE8); }
static inline float CameraDirX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xEC); }
static inline float CameraDirY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF0); }
static inline float CameraDirZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF4); }
static inline float CameraDistance() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xFC); }
static inline MtxPtr CameraMatrix() { return reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4); }
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
    _pppMngSt* pppMngSt = pppMngStPtr;

    if (gPppCalcDisabled == 0) {
        float* value = (float*)((char*)param_1 + *param_3->m_serializedDataOffsets + 0x80);
        unsigned char* flags = (unsigned char*)&param_2->m_arg3;

        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            param_2->m_dataValIndex, param_1, param_2->m_graphId, value, value + 1, value + 2,
            &param_2->m_initWOrk, &param_2->m_stepValue);

        if ((gPppInConstructor != 1) && ((flags[1] != 0 || flags[0] != 0))) {
            float cameraDirX = CameraDirX();
            float cameraDirY = CameraDirY();
            float cameraDirZ = CameraDirZ();

            Mtx cameraMtx;
            PSMTXCopy(CameraMatrix(), cameraMtx);

            float cameraPosX = CameraPosX();
            float cameraPosY = CameraPosY();
            float cameraPosZ = CameraPosZ();
            float scale = FLOAT_803331e0 + ((CameraDistance() - FLOAT_803331e4) / FLOAT_803331e4);

            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            pppMngSt->m_scale.x = FLOAT_803331e8 * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = FLOAT_803331e0;

            Mtx scaleMtx;
            PSMTXScale(scaleMtx, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);

            if (flags[1] != 0) {
                PSMTXInverse(cameraMtx, pppMngStPtr->m_matrix.value);
            }

            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            Vec resultPos;
            if (flags[0] != 0) {
                float distance = value[0];
                resultPos.x = cameraDirX * distance + cameraPosX;
                resultPos.y = cameraDirY * distance + cameraPosY;
                resultPos.z = cameraDirZ * distance + cameraPosZ;
            }

            float localX = ((_pppPObject*)param_1)->m_localMatrix.value[0][3];
            float localY = ((_pppPObject*)param_1)->m_localMatrix.value[1][3];

            Vec cameraDir;
            cameraDir.x = cameraDirX;
            cameraDir.y = cameraDirY;
            cameraDir.z = cameraDirZ;

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
