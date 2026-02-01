// Function: GetCharaHandlePtr__FP8CGObjectl
// Entry: 800e57f0
// Size: 104 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

CCharaPcsCHandle * GetCharaHandlePtr__FP8CGObjectl(CGObject *gObject,int param_2)

{
  if (gObject == (CGObject *)0x0) {
    return (CCharaPcsCHandle *)0x0;
  }
  if (param_2 == 1) {
    if (gObject->m_weaponModelHandle != (CCharaPcsCHandle *)0x0) {
      return gObject->m_weaponModelHandle;
    }
  }
  else if (param_2 < 1) {
    if ((-1 < param_2) && (gObject->m_charaModelHandle != (CCharaPcsCHandle *)0x0)) {
      return gObject->m_charaModelHandle;
    }
  }
  else if ((param_2 < 3) && (gObject->m_shieldModelHandle != (CCharaPcsCHandle *)0x0)) {
    return gObject->m_shieldModelHandle;
  }
  return (CCharaPcsCHandle *)0x0;
}

