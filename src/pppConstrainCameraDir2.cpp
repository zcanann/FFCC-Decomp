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
    float* value;
    double dVar2;
    double dVar3;
    double dVar4;
    double dVar5;
    float local_108;
    float local_104;
    float local_100;
    Vec local_fc;
    Vec local_f0;
    float local_e4;
    float local_e0;
    float local_dc;
    float local_d8;
    float local_d4;
    float local_d0;
    float local_cc;
    float local_c8;
    float local_c4;
    Vec local_c0;
    Mtx MStack_b4;
    Mtx MStack_84;
    u8* camera = reinterpret_cast<u8*>(&CameraPcs);

    if (gPppCalcDisabled == 0) {
        value = reinterpret_cast<float*>((reinterpret_cast<char*>(param_1) + 0x80) + *param_3->m_serializedDataOffsets);
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(param_2->m_dataValIndex, param_1, param_2->m_graphId, value, value + 1,
                                                     value + 2, &param_2->m_initWOrk, &param_2->m_stepValue);
        if ((gPppInConstructor != 1) && ((*reinterpret_cast<char*>(&param_2->m_arg3 + 1) != '\0' ||
                                          (*reinterpret_cast<char*>(&param_2->m_arg3) != '\0')))) {
            local_cc = *reinterpret_cast<float*>(camera + 0xEC);
            local_c8 = *reinterpret_cast<float*>(camera + 0xF0);
            local_c4 = *reinterpret_cast<float*>(camera + 0xF4);
            PSMTXCopy(reinterpret_cast<MtxPtr>(camera + 0x4), MStack_84);
            dVar5 = (double)*reinterpret_cast<float*>(camera + 0xE0);
            dVar4 = (double)*reinterpret_cast<float*>(camera + 0xE4);
            dVar3 = (double)*reinterpret_cast<float*>(camera + 0xE8);
            dVar2 = (double)(FLOAT_803331e0 + ((*reinterpret_cast<float*>(camera + 0xFC) - FLOAT_803331e4) / FLOAT_803331e4));
            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            pppMngSt->m_scale.x = static_cast<float>((double)FLOAT_803331e8 * dVar2);
            pppMngSt->m_scale.y = static_cast<float>(dVar2);
            pppMngSt->m_scale.z = FLOAT_803331e0;
            PSMTXScale(MStack_b4, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
            if (*reinterpret_cast<char*>(&param_2->m_arg3 + 1) != '\0') {
                PSMTXInverse(MStack_84, pppMngStPtr->m_matrix.value);
            }
            PSMTXConcat(MStack_b4, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
            if (*reinterpret_cast<char*>(&param_2->m_arg3) != '\0') {
                dVar2 = (double)*value;
                local_c0.x = static_cast<float>((double)local_cc * dVar2 + dVar5);
                local_c0.y = static_cast<float>((double)local_c8 * dVar2 + dVar4);
                local_c0.z = static_cast<float>((double)local_c4 * dVar2 + dVar3);
            }
            dVar2 = (double)((_pppPObject*)param_1)->m_localMatrix.value[0][3];
            dVar3 = (double)((_pppPObject*)param_1)->m_localMatrix.value[1][3];
            local_108 = local_cc;
            local_104 = local_c8;
            local_100 = local_c4;
            GetDirectVector__5CUtilFP3VecP3Vec3Vec((void*)&gUtil, (Vec*)&local_d8, (Vec*)&local_e4,
                                                   *reinterpret_cast<Vec*>(&local_108));
            local_f0.x = static_cast<float>(dVar2 * (double)local_d8);
            local_f0.y = static_cast<float>(dVar2 * (double)local_d4);
            local_f0.z = static_cast<float>(dVar2 * (double)local_d0);
            local_fc.x = static_cast<float>(dVar3 * (double)local_e4);
            local_fc.y = static_cast<float>(dVar3 * (double)local_e0);
            local_fc.z = static_cast<float>(dVar3 * (double)local_dc);
            PSVECAdd(&local_c0, &local_f0, &local_c0);
            PSVECAdd(&local_c0, &local_fc, &local_c0);
            pppMngStPtr->m_matrix.value[0][3] = local_c0.x;
            pppMngStPtr->m_matrix.value[1][3] = local_c0.y;
            pppMngStPtr->m_matrix.value[2][3] = local_c0.z;
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
