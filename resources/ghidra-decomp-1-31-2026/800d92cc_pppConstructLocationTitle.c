// Function: pppConstructLocationTitle
// Entry: 800d92cc
// Size: 48 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppConstructLocationTitle(pppLocationTitle *pppLocationTitle,UnkC *param_2)

{
  float fVar1;
  undefined4 *puVar2;
  
  fVar1 = FLOAT_80330ee0;
  puVar2 = (undefined4 *)
           ((int)(&pppLocationTitle->field0_0x0 + 2) + *param_2->m_serializedDataOffsets);
  *puVar2 = 0;
  *(undefined2 *)(puVar2 + 1) = 0;
  puVar2[4] = fVar1;
  puVar2[3] = fVar1;
  puVar2[2] = fVar1;
  return;
}

