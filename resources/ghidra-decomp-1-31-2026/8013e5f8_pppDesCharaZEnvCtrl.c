// Function: pppDesCharaZEnvCtrl
// Entry: 8013e5f8
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDesCharaZEnvCtrl(void)

{
  CCharaPcsCHandle *handle;
  int iVar1;
  
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  iVar1 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(undefined4 *)(iVar1 + 0xe4) = 0;
  *(undefined4 *)(iVar1 + 0xe8) = 0;
  *(undefined4 *)(iVar1 + 0xf4) = 0;
  return;
}

