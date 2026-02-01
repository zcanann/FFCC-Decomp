// Function: IsDispRader__8CGMonObjFv
// Entry: 80113efc
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 IsDispRader__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  iVar1 = IsDispRader__8CGObjectFv(&gMonObj->gObject);
  if ((iVar1 != 0) && ((int)((uint)*(byte *)&(gMonObj->gObject).m_weaponNodeFlags << 0x18) < 0)) {
    uVar2 = 1;
  }
  return uVar2;
}

