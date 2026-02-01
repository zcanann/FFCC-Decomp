// Function: pppFrameCharaZEnvCtrl
// Entry: 8013e584
// Size: 116 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppFrameCharaZEnvCtrl(pppCharaZEnvCtrl *pppCharaZEnvCtrl,UnkB *param_2,UnkC *param_3)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  int iVar2;
  
  if (DAT_8032ed70 == 0) {
    iVar2 = *param_3->m_serializedDataOffsets;
    handle = (CCharaPcsCHandle *)
             GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
    iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(undefined **)(iVar1 + 0xe4) = (undefined *)((int)(&pppCharaZEnvCtrl->field0_0x0 + 2) + iVar2);
    *(UnkB **)(iVar1 + 0xe8) = param_2;
    *(code **)(iVar1 + 0xf4) = CharaZEnvCtrl_BeforeMeshLockEnvCallback__FPQ26CChara6CModelPvPvi;
  }
  return;
}

