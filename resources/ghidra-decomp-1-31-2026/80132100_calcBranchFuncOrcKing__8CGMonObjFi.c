// Function: calcBranchFuncOrcKing__8CGMonObjFi
// Entry: 80132100
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 calcBranchFuncOrcKing__8CGMonObjFi(CGMonObj *gMonObj)

{
  undefined4 uVar1;
  void **ppvVar2;
  
  ppvVar2 = (gMonObj->gObject).m_scriptHandle;
  if ((uint)*(ushort *)(ppvVar2 + 7) < *(ushort *)((int)ppvVar2 + 0x1a) / 5) {
    uVar1 = 2;
  }
  else {
    uVar1 = calcBranchFuncDefault__8CGMonObjFi(gMonObj,1);
  }
  return uVar1;
}

