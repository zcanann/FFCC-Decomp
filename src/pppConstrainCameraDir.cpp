#include "ffcc/pppConstrainCameraDir.h"

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
    float* puVar2 = (float*)((int)(&pppConstrainCameraDir->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
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
    float* puVar2 = (float*)((int)(&pppConstrainCameraDir->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
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
    extern void* pppMngStPtr;
    extern struct {
        float _224_4_, _228_4_, _232_4_, _236_4_, _240_4_, _244_4_, _252_4_;
        float m_cameraMatrix[3][4];
    } CameraPcs;
    extern float FLOAT_803320b8, FLOAT_803320bc, FLOAT_803320c0;
    
    if (DAT_8032ed70 == 0) {
        float* value = (float*)((int)(&pppConstrainCameraDir->field0_0x0 + 2) + *param_3->m_serializedDataOffsets);
        
        // Call CalcGraphValue function
        extern void CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(float, float*, int, float*, float*, float*, float*, float*);
        CalcGraphValue__FP11_pppPObjectlRfRfRffRfRf(
            param_2->m_dataValIndex, &pppConstrainCameraDir->field0_0x0, param_2->m_graphId,
            value, value + 1, value + 2, &param_2->m_initWOrk, &param_2->m_stepValue);
        
        if ((DAT_8032ed78 != 1) && 
            ((*(char*)((int)&param_2->m_arg3 + 1) != 0 || *(char*)&param_2->m_arg3 != 0))) {
            
            float dVar8 = CameraPcs._236_4_;
            float dVar7 = CameraPcs._240_4_;
            float dVar6 = CameraPcs._244_4_;
            
            extern void PSMTXCopy(void*, void*);
            float MStack_b8[3][4];
            PSMTXCopy(&CameraPcs.m_cameraMatrix, &MStack_b8);
            
            float dVar5 = CameraPcs._224_4_;
            float dVar4 = CameraPcs._228_4_;
            float dVar3 = CameraPcs._232_4_;
            float dVar2 = FLOAT_803320b8 + ((CameraPcs._252_4_ - FLOAT_803320bc) / FLOAT_803320bc);
            
            extern void PSMTXIdentity(void*);
            extern struct {
                float m_matrix[3][4];
                struct { float x, y, z; } m_scale;
            }* pppMngStPtr;
            
            PSMTXIdentity(&pppMngStPtr->m_matrix);
            
            pppMngStPtr->m_scale.x = FLOAT_803320c0 * dVar2;
            pppMngStPtr->m_scale.y = dVar2;
            pppMngStPtr->m_scale.z = FLOAT_803320b8;
            
            extern void PSMTXScale(float, float, float, void*);
            float MStack_e8[3][4];
            PSMTXScale(pppMngStPtr->m_scale.x, pppMngStPtr->m_scale.y, pppMngStPtr->m_scale.z, &MStack_e8);
            
            if (*(char*)((int)&param_2->m_arg3 + 1) != 0) {
                extern void PSMTXInverse(void*, void*);
                PSMTXInverse(&MStack_b8, &pppMngStPtr->m_matrix);
            }
            
            extern void PSMTXConcat(void*, void*, void*);
            PSMTXConcat(&MStack_e8, &pppMngStPtr->m_matrix, &pppMngStPtr->m_matrix);
            
            if (*(char*)&param_2->m_arg3 != 0) {
                float dVar2 = *value;
                pppMngStPtr->m_matrix[0][3] = dVar8 * dVar2 + dVar5;
                pppMngStPtr->m_matrix[1][3] = dVar7 * dVar2 + dVar4;
                pppMngStPtr->m_matrix[2][3] = dVar6 * dVar2 + dVar3;
            }
            
            extern void pppSetFpMatrix__FP9_pppMngSt(void*);
            pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
        }
    }
}