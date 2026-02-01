// Function: pppConstructConstrainCameraForLoc
// Entry: 80167e70
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructConstrainCameraForLoc(void)

{
  int iVar1;
  
  iVar1 = GetModelPtr__FP8CGObject((CGObject *)(pppMngStPtr->m_velocity).x);
  *(undefined4 *)(iVar1 + 0xec) = 0;
  return;
}

