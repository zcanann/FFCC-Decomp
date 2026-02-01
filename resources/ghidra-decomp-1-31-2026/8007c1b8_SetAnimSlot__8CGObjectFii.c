// Function: SetAnimSlot__8CGObjectFii
// Entry: 8007c1b8
// Size: 12 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void SetAnimSlot__8CGObjectFii(CGObject *gObject,int param_2,int param_3)

{
  gObject->m_animQueue[param_3 + -0x41] = (int8_t)param_2;
  return;
}

