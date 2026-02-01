// Function: pppConstruct2YmDeformationShp
// Entry: 80090560
// Size: 48 bytes

void pppConstruct2YmDeformationShp(pppYmDeformationShp *pppYmDeformationShp,UnkC *param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_803305f4;
  iVar2 = param_2->m_serializedDataOffsets[2];
  *(float *)(&pppYmDeformationShp->field_0x98 + iVar2) = FLOAT_803305f4;
  *(float *)(&pppYmDeformationShp->field_0x94 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationShp->field_0x90 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationShp->field_0xa4 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationShp->field_0xa0 + iVar2) = fVar1;
  *(float *)(&pppYmDeformationShp->field_0x9c + iVar2) = fVar1;
  return;
}

