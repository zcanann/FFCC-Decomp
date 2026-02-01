// Function: pppConstructColum
// Entry: 800df2f8
// Size: 40 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructColum(pppColum *pppColum,UnkC *param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)((int)(&pppColum->field0_0x0 + 2) + param_2->m_serializedDataOffsets[3]);
  puVar1[2] = 0;
  puVar1[1] = 0;
  *puVar1 = 0;
  *(undefined4 *)(puVar1 + 4) = 0;
  return;
}

