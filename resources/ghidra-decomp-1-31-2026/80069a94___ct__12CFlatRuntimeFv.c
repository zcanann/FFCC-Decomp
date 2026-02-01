// Function: __ct__12CFlatRuntimeFv
// Entry: 80069a94
// Size: 116 bytes

CFlatRuntime * __ct__12CFlatRuntimeFv(CFlatRuntime *flatRuntime)

{
  flatRuntime->vtable = &PTR_PTR_s_CFlatRuntime_801fc9f0;
  (flatRuntime->m_objRoot).m_vtable = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
  (flatRuntime->m_objRoot).m_flags = (flatRuntime->m_objRoot).m_flags & 0xef;
  (flatRuntime->m_objRoot2).m_vtable = &PTR_PTR_s_CFlatRuntime_CObject_801eae88;
  (flatRuntime->m_objRoot2).m_flags = (flatRuntime->m_objRoot2).m_flags & 0xef;
  flatRuntime->m_isCreated = 0;
  flatRuntime->m_unk0x1298 = 1;
  clear__12CFlatRuntimeFv(flatRuntime);
  return flatRuntime;
}

