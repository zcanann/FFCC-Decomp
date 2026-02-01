// Function: Frame__9CGBaseObjFv
// Entry: 8010b220
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Frame__9CGBaseObjFv(CGBaseObj *gBaseObj)

{
  (**(code **)((int)(gBaseObj->object).m_vtable + 0x24))();
  return;
}

