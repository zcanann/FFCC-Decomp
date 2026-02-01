// Function: pppConstruct2YmDeformationScreen
// Entry: 80091de8
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstruct2YmDeformationScreen(pppYmDeformationScreen *pppYmDeformationScreen,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80330670;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppYmDeformationScreen->field_0x90 + iVar2) = FLOAT_80330670;
  *(float *)(&pppYmDeformationScreen->field_0x8c + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x9c + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x98 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x94 + iVar2) = fVar1;
  return;
}

