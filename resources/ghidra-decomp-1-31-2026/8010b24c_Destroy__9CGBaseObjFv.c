// Function: Destroy__9CGBaseObjFv
// Entry: 8010b24c
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Destroy__9CGBaseObjFv(CGBaseObj *gBaseObj)

{
  (**(code **)((int)(gBaseObj->object).m_vtable + 0x20))();
  return;
}

