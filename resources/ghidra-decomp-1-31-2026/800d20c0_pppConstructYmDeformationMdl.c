// Function: pppConstructYmDeformationMdl
// Entry: 800d20c0
// Size: 64 bytes

void pppConstructYmDeformationMdl(pppYmDeformationMdl *pppYmDeformationMdl_,UnkC *param_2)

{
  float fVar1;
  undefined2 *puVar2;
  
  fVar1 = FLOAT_80330dac;
  puVar2 = (undefined2 *)(&pppYmDeformationMdl_->field_0x80 + param_2->m_serializedDataOffsets[2]);
  *puVar2 = 0;
  *(undefined *)(puVar2 + 1) = 1;
  *(float *)(puVar2 + 6) = fVar1;
  *(float *)(puVar2 + 4) = fVar1;
  *(float *)(puVar2 + 2) = fVar1;
  *(float *)(puVar2 + 0xc) = fVar1;
  *(float *)(puVar2 + 10) = fVar1;
  *(float *)(puVar2 + 8) = fVar1;
  return;
}

