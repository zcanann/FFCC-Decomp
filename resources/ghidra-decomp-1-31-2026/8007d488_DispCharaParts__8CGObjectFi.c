// Function: DispCharaParts__8CGObjectFi
// Entry: 8007d488
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DispCharaParts__8CGObjectFi(CGObject *gObject,uint32_t param_2)

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
  pCVar2->m_model->m_meshVisibleMask = param_2;
  return;
}

