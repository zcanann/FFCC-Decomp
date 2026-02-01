// Function: pppConstructCrystal
// Entry: 800dd404
// Size: 32 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructCrystal(pppCrystal *pppCrystal,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  *(undefined4 *)((int)(&pppCrystal->field0_0x0 + 2) + iVar1) = 0;
  ((undefined4 *)((int)(&pppCrystal->field0_0x0 + 2) + iVar1))[1] = 0;
  return;
}

