// Function: IsDispRader__10CGPartyObjFv
// Entry: 8011c678
// Size: 112 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 IsDispRader__10CGPartyObjFv(CGObject *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = IsDispRader__8CGObjectFv(param_1);
  if (iVar1 != 0) {
    if (((int)((uint)*(byte *)&param_1->m_weaponNodeFlags << 0x18) < 0) &&
       ((int)((uint)*(byte *)((int)&param_1->m_weaponNodeFlags + 1) << 0x18) < 0)) {
      uVar2 = 1;
    }
  }
  return uVar2;
}

