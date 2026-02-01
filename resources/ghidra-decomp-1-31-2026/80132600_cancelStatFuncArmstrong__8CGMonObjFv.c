// Function: cancelStatFuncArmstrong__8CGMonObjFv
// Entry: 80132600
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void cancelStatFuncArmstrong__8CGMonObjFv(CGMonObj *gMonObj)

{
  if (*(int *)&gMonObj->field_0x520 == 100) {
    (**(code **)((int)(gMonObj->gObject).base_object.object.m_vtable + 0x94))(gMonObj,1);
  }
  return;
}

