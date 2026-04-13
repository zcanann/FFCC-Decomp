#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppYmEnv.h"
#include <dolphin/mtx.h>

static const float kPppConstrainCameraDirScaleBase = 1.0f;
static const float kPppConstrainCameraDirDistanceBase = 25.0f;
static const float kPppConstrainCameraDirScaleMul = 1.3333f;
static const float kPppConstrainCameraDirInitScale = 0.0f;

static inline float CameraPosX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE0); }
static inline float CameraPosY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE4); }
static inline float CameraPosZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xE8); }
static inline float CameraDirX() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xEC); }
static inline float CameraDirY() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF0); }
static inline float CameraDirZ() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xF4); }
static inline float CameraDistance() { return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0xFC); }
static inline MtxPtr CameraMatrix() { return reinterpret_cast<MtxPtr>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4); }
extern "C" void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);

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
    float uVar1 = kPppConstrainCameraDirInitScale;
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
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
    float uVar1 = kPppConstrainCameraDirInitScale;
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
    puVar2[2] = uVar1;
    puVar2[1] = uVar1;
    puVar2[0] = uVar1;
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
            float cameraDirX = CameraDirX();
            float cameraDirY = CameraDirY();
            float cameraDirZ = CameraDirZ();
            
            Mtx MStack_b8;
            PSMTXCopy(CameraMatrix(), MStack_b8);
            
            float cameraPosX = CameraPosX();
            float cameraPosY = CameraPosY();
            float cameraPosZ = CameraPosZ();
            float distanceBase = kPppConstrainCameraDirDistanceBase;
            float scale = ((CameraDistance() - distanceBase) / distanceBase) + kPppConstrainCameraDirScaleBase;
            
            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            
            pppMngSt->m_scale.x = kPppConstrainCameraDirScaleMul * scale;
            pppMngSt->m_scale.y = scale;
            pppMngSt->m_scale.z = kPppConstrainCameraDirScaleBase;
            
            Mtx MStack_e8;
            PSMTXScale(MStack_e8, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
            
            if (flags[1] != 0) {
                PSMTXInverse(MStack_b8, pppMngStPtr->m_matrix.value);
            }
            
            PSMTXConcat(MStack_e8, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
            
            if (flags[0] != 0) {
                float graphValue = value[0];
                pppMngStPtr->m_matrix.value[0][3] = cameraDirX * graphValue + cameraPosX;
                pppMngStPtr->m_matrix.value[1][3] = cameraDirY * graphValue + cameraPosY;
                pppMngStPtr->m_matrix.value[2][3] = cameraDirZ * graphValue + cameraPosZ;
            }
            
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
