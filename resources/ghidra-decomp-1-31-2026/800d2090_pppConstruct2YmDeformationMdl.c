// Function: pppConstruct2YmDeformationMdl
// Entry: 800d2090
// Size: 48 bytes

void pppConstruct2YmDeformationMdl(pppYmDeformationMdl *pppYmDeformationMdl,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80330dac;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppYmDeformationMdl->field_0x8c + iVar2) = FLOAT_80330dac;
  *(float *)(&pppYmDeformationMdl->field_0x88 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationMdl->field_0x84 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationMdl->field_0x98 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationMdl->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationMdl->field_0x90 + iVar2) = fVar1;
  return;
}

