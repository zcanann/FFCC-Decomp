// Function: __ct__8CGMonObjFv
// Entry: 8006e960
// Size: 92 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void __ct__8CGMonObjFv(CGMonObj *gMonObj)

{
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
  (gMonObj->gObject).base_object.object.m_flags =
       (gMonObj->gObject).base_object.object.m_flags & 0xef;
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CGBaseObj_802112f4;
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CGObject_801fd360;
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CGPrgObj_8021210c;
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CGCharaObj_802113d0;
  (gMonObj->gObject).base_object.object.m_vtable = &PTR_PTR_s_CGMonObj_8021165c;
  return;
}

