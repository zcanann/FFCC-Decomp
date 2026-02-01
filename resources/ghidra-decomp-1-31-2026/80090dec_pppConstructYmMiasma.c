// Function: pppConstructYmMiasma
// Entry: 80090dec
// Size: 80 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMiasma(pppYmMiasma *pppYmMiasma,UnkC *param_2)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  uVar2 = DAT_80330658;
  fVar1 = FLOAT_80330644;
  puVar3 = (undefined4 *)((int)(&pppYmMiasma->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2])
  ;
  *puVar3 = 0;
  puVar3[7] = fVar1;
  puVar3[8] = fVar1;
  puVar3[9] = fVar1;
  *(undefined *)(puVar3 + 2) = 0;
  puVar3[4] = uVar2;
  puVar3[5] = fVar1;
  puVar3[6] = fVar1;
  puVar3[0xc] = fVar1;
  puVar3[0xb] = fVar1;
  puVar3[10] = fVar1;
  *(undefined *)(puVar3 + 0xd) = 0;
  return;
}

