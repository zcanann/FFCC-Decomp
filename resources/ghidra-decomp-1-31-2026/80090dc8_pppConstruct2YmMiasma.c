// Function: pppConstruct2YmMiasma
// Entry: 80090dc8
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2YmMiasma(pppYmMiasma *pppYmMiasma,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80330644;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppYmMiasma->field_0x9c + iVar2) = FLOAT_80330644;
  *(float *)(&pppYmMiasma->field_0xa0 + iVar2) = fVar1;
  *(float *)(&pppYmMiasma->field_0xa4 + iVar2) = fVar1;
  return;
}

