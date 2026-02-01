// Function: ResetDynamics__8CGObjectFv
// Entry: 8007c37c
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ResetDynamics__8CGObjectFv(CGObject *gObject)

{
  bool bVar1;
  CCharaPcsCHandle *pCVar2;
  
  pCVar2 = gObject->m_charaModelHandle;
  bVar1 = false;
  if ((pCVar2 != (CCharaPcsCHandle *)0x0) && (pCVar2->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (!bVar1) {
    return;
  }
  pCVar2->m_model->m_flags0x10C = pCVar2->m_model->m_flags0x10C & 0x7f | 0x80;
  return;
}

