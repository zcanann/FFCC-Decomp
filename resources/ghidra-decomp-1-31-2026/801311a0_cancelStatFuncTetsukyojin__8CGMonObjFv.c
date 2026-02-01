// Function: cancelStatFuncTetsukyojin__8CGMonObjFv
// Entry: 801311a0
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void cancelStatFuncTetsukyojin__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 0x66) {
    (gMonObj->gObject).m_bgColMask = (gMonObj->gObject).m_bgColMask | 0xc0002;
  }
  else {
    if (iVar1 < 0x66) {
      if (iVar1 != 100) {
        return;
      }
    }
    else if (0x67 < iVar1) {
      return;
    }
    FUN_801162b4();
  }
  return;
}

