// Function: pppConstruct2Emission
// Entry: 800e6530
// Size: 36 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2Emission(pppEmission *pppEmission,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_803311f8;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppEmission->field_0x94 + iVar2) = FLOAT_803311f8;
  *(float *)(&pppEmission->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppEmission->field_0x8c + iVar2) = fVar1;
  return;
}

