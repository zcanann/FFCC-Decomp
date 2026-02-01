// Function: Draw__9CGBaseObjFv
// Entry: 8010b1f4
// Size: 44 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__9CGBaseObjFv(CGBaseObj *gBaseObj)

{
  (**(code **)((int)(gBaseObj->object).m_vtable + 0x28))();
  return;
}

