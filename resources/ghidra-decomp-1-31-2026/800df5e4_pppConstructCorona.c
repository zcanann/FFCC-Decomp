// Function: pppConstructCorona
// Entry: 800df5e4
// Size: 52 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructCorona(pppCorona *pppCorona,UnkC *param_2)

{
  float fVar1;
  undefined2 *puVar2;
  
  fVar1 = FLOAT_803310c8;
  puVar2 = (undefined2 *)((int)(&pppCorona->field0_0x0 + 2) + param_2->m_serializedDataOffsets[3]);
  puVar2[2] = 0;
  puVar2[1] = 0;
  *puVar2 = 0;
  *(float *)(puVar2 + 8) = fVar1;
  *(float *)(puVar2 + 6) = fVar1;
  *(float *)(puVar2 + 4) = fVar1;
  return;
}

