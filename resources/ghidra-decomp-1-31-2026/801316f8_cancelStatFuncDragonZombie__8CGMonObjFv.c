// Function: cancelStatFuncDragonZombie__8CGMonObjFv
// Entry: 801316f8
// Size: 256 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void cancelStatFuncDragonZombie__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 100) {
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0xe,0);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x13,4);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x16,0x1a);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x17,0x1b);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x18,0x1c);
    gMonObj->_bossBranchRelated = 1;
  }
  else {
    if (iVar1 < 100) {
      if (iVar1 != 4) {
        return;
      }
    }
    else if (0x65 < iVar1) {
      return;
    }
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0,0);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,4,4);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x1a,0x1a);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x1b,0x1b);
    SetAnimSlot__8CGObjectFii(&gMonObj->gObject,0x1c,0x1c);
    gMonObj->_bossBranchRelated = 0;
  }
  return;
}

