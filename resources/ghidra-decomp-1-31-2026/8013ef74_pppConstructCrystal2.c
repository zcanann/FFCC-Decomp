// Function: pppConstructCrystal2
// Entry: 8013ef74
// Size: 32 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructCrystal2(pppCrystal2 *pppCrystal2,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  *(undefined4 *)((int)(&pppCrystal2->field0_0x0 + 2) + iVar1) = 0;
  ((undefined4 *)((int)(&pppCrystal2->field0_0x0 + 2) + iVar1))[1] = 0;
  return;
}

