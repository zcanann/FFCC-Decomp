// Function: isLoopAnimDirect__8CGPrgObjFv
// Entry: 80127720
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 isLoopAnimDirect__8CGPrgObjFv(CGPrgObj *gProjObj)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((int)((uint)gProjObj->m_animFlags << 0x18) < 0) ||
     (iVar1 = IsLoopAnim__8CGObjectFi(&gProjObj->object,2), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

