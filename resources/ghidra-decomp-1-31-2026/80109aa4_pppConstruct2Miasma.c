// Function: pppConstruct2Miasma
// Entry: 80109aa4
// Size: 100 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2Miasma(pppMiasma *pppMiasma,UnkC *param_2)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)((int)(&pppMiasma->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  memset(puVar1,0,8);
  memset(puVar1 + 8,0,8);
  memset(puVar1 + 0x10,0,8);
  return;
}

