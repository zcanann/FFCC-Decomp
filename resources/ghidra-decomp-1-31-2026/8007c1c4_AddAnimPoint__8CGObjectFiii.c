// Function: AddAnimPoint__8CGObjectFiii
// Entry: 8007c1c4
// Size: 108 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void AddAnimPoint__8CGObjectFiii
               (CGObject *gObject,int param_2,undefined2 param_3,undefined2 param_4)

{
  bool bVar1;
  CRef *pCVar2;
  CCharaPcsCHandle *pCVar3;
  
  pCVar3 = gObject->m_charaModelHandle;
  bVar1 = false;
  if ((pCVar3 != (CCharaPcsCHandle *)0x0) && (pCVar3->m_model != (CModel *)0x0)) {
    bVar1 = true;
  }
  if (!bVar1) {
    return;
  }
  pCVar2 = pCVar3->m_animSlot[param_2];
  if (pCVar2 == (CRef *)0x0) {
    return;
  }
  *(undefined2 *)((int)&pCVar2[5].refCount + (uint)*(ushort *)&pCVar2[5].refCount * 4 + 2) = param_4
  ;
  *(undefined2 *)(&pCVar2[6].vtable + *(ushort *)&pCVar2[5].refCount) = param_3;
  *(short *)&pCVar2[5].refCount = *(short *)&pCVar2[5].refCount + 1;
  return;
}

