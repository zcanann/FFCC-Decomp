#include "ffcc/pppConstrainCameraDir.h"
#include "ffcc/partMng.h"

/*
 * --INFO--
 * PAL Address: 801432bc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, UnkC* param_2)
{
    extern float DAT_803320c4;
    
    float uVar1 = DAT_803320c4;
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
    puVar2[2] = DAT_803320c4;
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
void pppConstruct2ConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, UnkC* param_2)
{
    extern float DAT_803320c4;
    
    float uVar1 = DAT_803320c4;
    float* puVar2 = (float*)((char*)pppConstrainCameraDir + *param_2->m_serializedDataOffsets + 0x80);
    puVar2[2] = DAT_803320c4;
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
void pppDestructConstrainCameraDir(void)
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
void pppFrameConstrainCameraDir(pppConstrainCameraDir* pppConstrainCameraDir, UnkB* param_2, UnkC* param_3)
{
    extern int DAT_8032ed70;
    extern char DAT_8032ed78;
    extern struct {
        float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
        float m_cameraMatrix[3][4];
    } CameraPcs;
    extern float FLOAT_803320b8, FLOAT_803320bc, FLOAT_803320c0;
    
    _pppMngSt* pppMngSt = pppMngStPtr;

    if (DAT_8032ed70 == 0) {
        float* value = (float*)((char*)pppConstrainCameraDir + *param_3->m_serializedDataOffsets + 0x80);
        
        // Call CalcGraphValue function
        extern void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, float*, int, float*, float*, float*, float*, float*);
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            param_2->m_dataValIndex, &pppConstrainCameraDir->field0_0x0, param_2->m_graphId,
            value, value + 1, value + 2, &param_2->m_initWOrk, &param_2->m_stepValue);
        
        if ((DAT_8032ed78 != 1) && 
            ((*(char*)((int)&param_2->m_arg3 + 1) != 0 || *(char*)&param_2->m_arg3 != 0))) {
            
            double dVar8 = (double)CameraPcs._236_4_;
            double dVar7 = (double)CameraPcs._240_4_;
            double dVar6 = (double)CameraPcs._244_4_;
            
            Mtx MStack_b8;
            PSMTXCopy(CameraPcs.m_cameraMatrix, MStack_b8);
            
            double dVar5 = (double)CameraPcs._224_4_;
            double dVar4 = (double)CameraPcs._228_4_;
            double dVar3 = (double)CameraPcs._232_4_;
            double dVar2 = (double)(FLOAT_803320b8 + ((CameraPcs._252_4_ - FLOAT_803320bc) / FLOAT_803320bc));
            
            PSMTXIdentity(pppMngStPtr->m_matrix.value);
            
            float fVar1 = FLOAT_803320b8;
            pppMngSt->m_scale.x = (float)((double)FLOAT_803320c0 * dVar2);
            pppMngSt->m_scale.y = (float)dVar2;
            pppMngSt->m_scale.z = fVar1;
            
            Mtx MStack_e8;
            PSMTXScale(MStack_e8, pppMngSt->m_scale.x, pppMngSt->m_scale.y, pppMngSt->m_scale.z);
            
            if (*(char*)((int)&param_2->m_arg3 + 1) != 0) {
                PSMTXInverse(MStack_b8, pppMngStPtr->m_matrix.value);
            }
            
            PSMTXConcat(MStack_e8, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);
            
            if (*(char*)&param_2->m_arg3 != 0) {
                dVar2 = (double)*value;
                pppMngStPtr->m_matrix.value[0][3] = (float)(dVar8 * dVar2 + dVar5);
                pppMngStPtr->m_matrix.value[1][3] = (float)(dVar7 * dVar2 + dVar4);
                pppMngStPtr->m_matrix.value[2][3] = (float)(dVar6 * dVar2 + dVar3);
            }
            
            extern void pppSetFpMatrix__FP9_pppMngSt(void*);
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
