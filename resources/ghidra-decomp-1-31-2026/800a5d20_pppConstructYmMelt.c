// Function: pppConstructYmMelt
// Entry: 800a5d20
// Size: 60 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructYmMelt(pppYmMelt *pppYmMelt,UnkC *param_2)

{
  float fVar1;
  undefined4 *puVar2;
  
  fVar1 = FLOAT_80330af0;
  puVar2 = (undefined4 *)((int)(&pppYmMelt->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  *puVar2 = 0;
  *(undefined2 *)(puVar2 + 1) = 0;
  *(undefined2 *)((int)puVar2 + 10) = 0;
  *(undefined2 *)(puVar2 + 2) = 0;
  *(undefined2 *)((int)puVar2 + 6) = 0;
  puVar2[5] = fVar1;
  puVar2[4] = fVar1;
  puVar2[3] = fVar1;
  return;
}

