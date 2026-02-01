// Function: GetModelPtr__FP8CGObject
// Entry: 800e602c
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CModel * GetModelPtr__FP8CGObject(CGObject *gObject)

{
  CCharaPcsCHandle *pCVar1;
  
  if (gObject == (CGObject *)0x0) {
    return (CModel *)0x0;
  }
  pCVar1 = gObject->m_charaModelHandle;
  if (pCVar1 == (CCharaPcsCHandle *)0x0) {
    return (CModel *)0x0;
  }
  if (pCVar1 != (CCharaPcsCHandle *)0x0) {
    return pCVar1->m_model;
  }
  return (CModel *)0x0;
}

