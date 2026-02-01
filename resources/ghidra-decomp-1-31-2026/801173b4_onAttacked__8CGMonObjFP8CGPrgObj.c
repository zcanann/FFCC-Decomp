// Function: onAttacked__8CGMonObjFP8CGPrgObj
// Entry: 801173b4
// Size: 88 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onAttacked__8CGMonObjFP8CGPrgObj(CGMonObj *gMonObj)

{
  int iVar1;
  
  gMonObj->field_0x6c0 = 1;
  iVar1 = __ptmf_test(*(int *)&gMonObj->field_0x708 + 0x78);
  if (iVar1 != 0) {
    __ptmf_scall(gMonObj,*(undefined4 *)&gMonObj->field_0x708);
  }
  return;
}

