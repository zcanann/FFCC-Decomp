// Function: pppFrameBlurChara
// Entry: 800de0ac
// Size: 232 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameBlurChara(pppBlurChara *pppBlurChara,UnkB *param_2,UnkC *param_3)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  if (DAT_8032ed70 == 0) {
    piVar4 = (int *)((int)(&pppBlurChara->field0_0x0 + 2) + param_3->m_serializedDataOffsets[2]);
    handle = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).y,0);
    iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(int **)(iVar1 + 0xe4) = piVar4;
    *(UnkB **)(iVar1 + 0xe8) = param_2;
    if (*piVar4 == 0) {
      uVar2 = GXGetTexBufferSize(0x140,0xe0,1,0,0);
      iVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        (uVar2,pppEnvStPtr->m_stagePtr,s_pppBlurChara_cpp_801db620,0xd5);
      *piVar4 = iVar3;
      iVar3 = pppMemAlloc__FUlPQ27CMemory6CStagePci
                        (0x20,pppEnvStPtr->m_stagePtr,s_pppBlurChara_cpp_801db620,0xd7);
      piVar4[2] = iVar3;
      *(int **)(iVar1 + 0xe4) = piVar4;
      *(UnkB **)(iVar1 + 0xe8) = param_2;
      *(code **)(iVar1 + 0xf4) = BlurChara_SetBeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
    }
  }
  return;
}

