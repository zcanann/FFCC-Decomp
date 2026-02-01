// Function: pppConstructYmDeformationScreen
// Entry: 80091e18
// Size: 64 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmDeformationScreen(pppYmDeformationScreen *pppYmDeformationScreen,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80330670;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(undefined2 *)(&pppYmDeformationScreen->field_0x84 + iVar2) = 0;
  (&pppYmDeformationScreen->field_0x86)[iVar2] = 1;
  *(float *)(&pppYmDeformationScreen->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x8c + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x9c + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x98 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationScreen->field_0x94 + iVar2) = fVar1;
  return;
}

