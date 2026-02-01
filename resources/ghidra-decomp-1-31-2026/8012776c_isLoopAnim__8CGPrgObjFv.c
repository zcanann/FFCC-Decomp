// Function: isLoopAnim__8CGPrgObjFv
// Entry: 8012776c
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 isLoopAnim__8CGPrgObjFv(CGPrgObj *gPrgObj)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  
  bVar1 = gPrgObj->m_animFlags;
  if ((((int)((uint)bVar1 << 0x19 | (uint)(bVar1 >> 7)) < 0) || ((int)((uint)bVar1 << 0x18) < 0)) ||
     (iVar2 = IsLoopAnim__8CGObjectFi(&gPrgObj->object,2), iVar2 == 0)) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

