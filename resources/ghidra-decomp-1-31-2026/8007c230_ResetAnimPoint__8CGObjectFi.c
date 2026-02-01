// Function: ResetAnimPoint__8CGObjectFi
// Entry: 8007c230
// Size: 72 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ResetAnimPoint__8CGObjectFi(CGObject *gObject,int param_2)

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
  if (pCVar2->m_animSlot[param_2] == (CRef *)0x0) {
    return;
  }
  *(undefined2 *)&pCVar2->m_animSlot[param_2][5].refCount = 0;
  return;
}

