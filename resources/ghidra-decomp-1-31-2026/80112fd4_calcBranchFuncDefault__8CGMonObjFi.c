// Function: calcBranchFuncDefault__8CGMonObjFi
// Entry: 80112fd4
// Size: 152 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4 calcBranchFuncDefault__8CGMonObjFi(CGMonObj *gMonObj,int param_2)

{
  void **ppvVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  if (param_2 == 1) {
    ppvVar1 = (gMonObj->gObject).m_scriptHandle;
    if (*(ushort *)(ppvVar1 + 7) < *(ushort *)((int)ppvVar1 + 0x1a) >> 1) {
      uVar4 = 1;
    }
  }
  else if (param_2 == 2) {
    ppvVar1 = (gMonObj->gObject).m_scriptHandle;
    uVar2 = (uint)*(ushort *)((int)ppvVar1 + 0x1a);
    uVar3 = (uint)*(ushort *)(ppvVar1 + 7);
    if (uVar3 < uVar2 / 3) {
      uVar4 = 2;
    }
    else if (uVar3 < (uVar2 << 1) / 3) {
      uVar4 = 1;
    }
  }
  else if (param_2 != 0) {
    uVar4 = 0;
  }
  return uVar4;
}

