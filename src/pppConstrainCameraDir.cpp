#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
extern struct {
    float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
    Mtx m_cameraMatrix;
} CameraPcs;
extern float lbl_803320B8;
extern float lbl_803320BC;
extern float lbl_803320C0;
extern float lbl_803320C4;
extern "C" void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, void*, int, float*, float*, float*, float*, float*);
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
    float uVar1 = lbl_803320C4;
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
    float uVar1 = lbl_803320C4;
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
    _pppMngSt* pppMngSt = pppMngStPtr;

    if (gPppCalcDisabled == 0) {
        float* value = (float*)((char*)pppConstrainCameraDir + *param_3->m_serializedDataOffsets + 0x80);
        unsigned char* flags = (unsigned char*)&param_2->m_arg3;
        float fVar2;
        float fVar3;
        float fVar4;
        float fVar5;
        float fVar6;

        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            param_2->m_dataValIndex, pppConstrainCameraDir, param_2->m_graphId,
            value, value + 1, value + 2, &param_2->m_initWOrk, &param_2->m_stepValue);
        
        if ((gPppInConstructor != 1) && ((flags[1] != 0 || flags[0] != 0))) {
            float fVar7 = CameraPcs._236_4_;
            float fVar8 = CameraPcs._240_4_;
            float fVar9 = CameraPcs._244_4_;
            
            Mtx MStack_b8;
            PSMTXCopy(CameraPcs.m_cameraMatrix, MStack_b8);
            
            fVar6 = CameraPcs._224_4_;
            fVar5 = CameraPcs._228_4_;
            fVar4 = CameraPcs._232_4_;
            fVar3 = lbl_803320B8 + ((CameraPcs._252_4_ - lbl_803320BC) / lbl_803320BC);
            
            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            
            fVar2 = lbl_803320B8;
            pppMngSt->m_scale.x = lbl_803320C0 * fVar3;
            pppMngSt->m_scale.y = fVar3;
            pppMngSt->m_scale.z = fVar2;
            
            Mtx MStack_e8;
            PSMTXScale(MStack_e8, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
            
            if (flags[1] != 0) {
                PSMTXInverse(MStack_b8, pppMngStPtr->m_matrix.value);
            }
            
            PSMTXConcat((MtxPtr)MStack_e8, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
            
            if (flags[0] != 0) {
                fVar3 = *value;
                pppMngStPtr->m_matrix.value[0][3] = fVar7 * fVar3 + fVar6;
                pppMngStPtr->m_matrix.value[1][3] = fVar8 * fVar3 + fVar5;
                pppMngStPtr->m_matrix.value[2][3] = fVar9 * fVar3 + fVar4;
            }
            
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
