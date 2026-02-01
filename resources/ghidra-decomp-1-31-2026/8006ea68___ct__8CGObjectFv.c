// Function: __ct__8CGObjectFv
// Entry: 8006ea68
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __ct__8CGObjectFv(CGObject *gObject)

{
  (gObject->base_object).object.m_vtable = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
  (gObject->base_object).object.m_flags = (gObject->base_object).object.m_flags & 0xef;
  (gObject->base_object).object.m_vtable = &PTR_PTR_s_CGBaseObj_802112f4;
  (gObject->base_object).object.m_vtable = &PTR_PTR_s_CGObject_801fd360;
  return;
}

