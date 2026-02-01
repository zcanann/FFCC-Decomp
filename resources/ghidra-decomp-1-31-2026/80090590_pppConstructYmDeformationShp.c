// Function: pppConstructYmDeformationShp
// Entry: 80090590
// Size: 76 bytes

void pppConstructYmDeformationShp(pppYmDeformationShp *pppYmDeformationShp,UnkC *param_2)

{
  float fVar1;
  undefined4 *puVar2;
  
  fVar1 = FLOAT_803305f4;
  puVar2 = (undefined4 *)(&pppYmDeformationShp->field_0x80 + param_2->m_serializedDataOffsets[2]);
  *puVar2 = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  *(undefined2 *)(puVar2 + 3) = 0;
  *(undefined *)((int)puVar2 + 0xe) = 1;
  puVar2[6] = fVar1;
  puVar2[5] = fVar1;
  puVar2[4] = fVar1;
  puVar2[9] = fVar1;
  puVar2[8] = fVar1;
  puVar2[7] = fVar1;
  return;
}

