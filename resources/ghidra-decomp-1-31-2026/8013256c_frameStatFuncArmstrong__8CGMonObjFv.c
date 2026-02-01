// Function: frameStatFuncArmstrong__8CGMonObjFv
// Entry: 8013256c
// Size: 148 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void frameStatFuncArmstrong__8CGMonObjFv(CGMonObj *gMonObj)

{
  int iVar1;
  undefined4 in_r4;
  
  iVar1 = *(int *)&gMonObj->field_0x520;
  if (iVar1 == 100) {
    if (*(int *)&gMonObj->field_0x528 == 0) {
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,0);
    }
    else if (*(int *)&gMonObj->field_0x528 == 0x29) {
      (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
    }
    _statAttack__10CGCharaObjFv((CGCharaObj *)gMonObj);
  }
  else if ((99 < iVar1) && (iVar1 < 0x69)) {
    frameStatFuncGiantCrab__8CGMonObjFv(gMonObj,in_r4);
  }
  return;
}

