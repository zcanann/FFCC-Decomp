// Function: pppConCharaZEnvCtrl
// Entry: 8013e638
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConCharaZEnvCtrl(void)

{
  CCharaPcsCHandle *handle;
  
  handle = (CCharaPcsCHandle *)
           GetCharaHandlePtr__FP8CGObjectl((CGObject *)(pppMngStPtr->m_velocity).x,0);
  GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  return;
}

